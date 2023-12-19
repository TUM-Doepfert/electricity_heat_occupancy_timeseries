/**
 * ITI_fmiCSFunctions.c
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#include "ITI_crt.h"
#include "fmiPlatformTypes.h"
#include "ITI_fmiCSTypes.h"
#include "ITI_ModelInclude.h"
#include "ITI_PartitionEval.h"

#define MODEL_IDENTIFIER ITI_projectName
#include "fmiFunctions.h"

#include "ITI_Cvode_base.h"
#include "ITI_Cvode_FMI_CS.h"

#ifdef _WIN32
#if defined(_MSC_VER)
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#endif
#include "Windows.h"
#ifndef GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS
#define GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS (4)
#define GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT (2)
BOOL WINAPI GetModuleHandleExA(DWORD, LPCSTR, HMODULE*);
#endif
#endif

 
#if defined(STDC99)
#define HAVE_VSNPRINTF 1
#elif defined(__MINGW32__) || defined(__CYGWIN__)
#if __STDC_VERSION__ >= 199901L
#define HAVE_VSNPRINTF 1
#endif
#elif defined(__WATCOMC__)
#define HAVE_VSNPRINTF 1
#elif defined(__TURBOC__) && __TURBOC__ >= 0x550
#define HAVE_VSNPRINTF 1
#elif defined(MSDOS) && defined(__BORLANDC__) && (BORLANDC > 0x410)
#define HAVE_VSNPRINTF 1
#elif defined(_MSC_VER) && _MSC_VER >= 1900
#define HAVE_VSNPRINTF 1
#else
#undef HAVE_VSNPRINTF
#endif

#if !HAVE_VSNPRINTF
int rpl_vsnprintf(char *, size_t, const char *, va_list);
#define vsnprintf rpl_vsnprintf
#endif  

#define binaryGUID "{3A13D02B-8675-4259-B18E-D734CA52C063}"

static _ITI_INLINE fmiStatus splitValueRef(ITI_fmiCSComponent* c, const fmiValueReference vRef, enum ITI_fmiVarKind* kind, size_t* index);
static _ITI_INLINE fmiStatus setRealValue(ITI_fmiCSComponent* c, const fmiValueReference vRef, const enum ITI_fmiVarKind kind, const size_t index, const fmiReal v);
static _ITI_INLINE fmiStatus setIntegerValue(ITI_fmiCSComponent* c, const fmiValueReference vRef, const enum ITI_fmiVarKind kind, const size_t index, const fmiInteger v);
static _ITI_INLINE fmiStatus setStringValue(ITI_fmiCSComponent* c, const fmiValueReference vRef, const enum ITI_fmiVarKind kind, const size_t index, const fmiString v);

static _ITI_INLINE fmiStatus getRealValue(ITI_fmiCSComponent* c, const fmiValueReference vRef, const enum ITI_fmiVarKind kind, const size_t index, fmiReal* v);
static _ITI_INLINE fmiStatus getIntegerValue(ITI_fmiCSComponent* c, const fmiValueReference vRef, const enum ITI_fmiVarKind kind, const size_t index, fmiInteger* v);
static _ITI_INLINE fmiStatus getStringValue(ITI_fmiCSComponent* c, const fmiValueReference vRef, const enum ITI_fmiVarKind kind, const size_t index, fmiString* v);

static void formatLogger(fmiCallbackLogger logger, fmiComponent c, fmiString instanceName, fmiStatus status, fmiString category, fmiString message, ...);
void FMI_CS_TraceFunc(int iTab, int iKind, const char* strCapt, const char* strTxt, const void* pVoid);
void logTrace(ITI_fmiCSComponent* ci);
void logWarnings(ITI_fmiCSComponent* ci);

static fmiStatus allocateSlave(fmiComponent c);

DllExport const char* fmiGetTypesPlatform()
{
	return fmiPlatform;
}

DllExport const char* fmiGetVersion()
{
	return fmiVersion;
}

DllExport fmiComponent fmiInstantiateSlave(fmiString instanceName, fmiString fmuGUID, fmiString fmuLocation, fmiString mimetype, fmiReal timeout, fmiBoolean visible, fmiBoolean interactive, fmiCallbackFunctions functions, fmiBoolean loggingOn)
{
	size_t pid = 0;
	fmiComponent c;
	if(strcmp(fmuGUID, binaryGUID) != 0)
	{
		formatLogger(functions.logger, NULL, instanceName, fmiFatal, "Fatal Error", "The given GUID %s is not equal to the GUID of the binary (%s)!", fmuGUID, binaryGUID);
		return 0;
	}
	if(!fmuLocation)
	{
		formatLogger(functions.logger, NULL, instanceName, fmiFatal, "Fatal Error", "The function fmiInstantiateSlave() was called with a Null pointer as fmuLocation argument.!");
		return 0;
	}

	c = (fmiComponent)calloc(1, sizeof(struct ITI_fmiCSComponent));

	if (allocateSlave(c) == fmiOK) {
		ITI_fmiCSComponent* ci = (ITI_fmiCSComponent*)c;
		char strResourceFolder[1024];
		char strTmp[12];
		ci->functions = functions;
		strcpy(ci->instanceName, instanceName);

		if((fmuLocation[strlen(fmuLocation)] !='/') && (fmuLocation[strlen(fmuLocation)] !='\\'))
			strcpy(strTmp, "/resources/");
		else
			strcpy(strTmp, "resources/");

		if(strstr(fmuLocation, "file:///") == 0)
			sprintf(strResourceFolder, "%s%s", fmuLocation + strlen("file:///"), strTmp);
		else if(strstr(fmuLocation, "file://") == 0)
			sprintf(strResourceFolder, "%s%s", fmuLocation + strlen("file://"), strTmp);
		else
			sprintf(strResourceFolder, "%s%s", fmuLocation, strTmp);

		SetResourceFolder_CVode(ci->sd, strResourceFolder);
		ci->loggingOn = loggingOn;
		return c;
	}
	formatLogger(functions.logger, NULL, instanceName, fmiFatal, "Fatal Error", "The Slave could not be instantiated!");
	return 0;
}

DllExport fmiStatus fmiInitializeSlave(fmiComponent c, fmiReal tStart, fmiBoolean StopTimeDefined, fmiReal tStop)
{
	size_t pid = 0;
	ITI_fmiCSComponent* ci = (ITI_fmiCSComponent*)c;
	ITI_SolverState iRet = SOLVER_SUCCESS_END;
	 
	FILE* f;
	ITI_SolverSettings sSettings;

#ifdef _WIN32
	char currentDirectoryPath[_MAX_PATH];
#endif

	if (!ci)
		return fmiFatal;

	FillSolverSettings(&sSettings);

	f = fopen("solversettings.txt", "r+");
	if (f) {
		ReadSolverSettingsFromFile(f, &sSettings);
		fclose(f);
	}
	if (StopTimeDefined)
	{
		sSettings.tStop = tStop;
		sSettings.bStopAtStop = ITI_true;
	}
	else
	{
		sSettings.tStop = tStart - 1.0;
		sSettings.bStopAtStop = ITI_false;
	}

	sSettings.tStart = tStart;
	sSettings.saveMode = 10;  

	SetSolverSettings(ci->sd, &sSettings);

#if (defined(_MSC_VER) && _MSC_VER >= 1400) || (defined(_WIN32) && !defined(_MSC_VER))
	{
		char path[_MAX_PATH];
		HMODULE hm = NULL;
		GetCurrentDirectoryA(_MAX_PATH, currentDirectoryPath);
		if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)&fmiInitializeSlave, &hm)) {
			if (GetModuleFileNameA(hm, path, sizeof(path)) > 0) {
				char drive[_MAX_DRIVE];
				char dir[_MAX_DIR];
				char newPath[_MAX_PATH];
				_splitpath(path, drive, dir, NULL, NULL);
				sprintf(newPath, "%s%s", drive, dir);
				SetCurrentDirectoryA(newPath);
			}
		}
	}
#endif

	iRet = InitializeModel(ci->sd);

#ifdef _WIN32
	SetCurrentDirectoryA(currentDirectoryPath);
#endif

	if (iRet < SOLVER_SUCCESS_END) {
		formatLogger(ci->functions.logger, c, ci->instanceName, fmiError, "Error", "The Slave could not be initialized!");
		ci->mode = ITI_fmiCSError;
		return fmiError;
	}

	if (InitializeConditionsModelOnly(ci->sd) < SOLVER_SUCCESS_END) {
		formatLogger(ci->functions.logger, c, ci->instanceName, fmiError, "Error", "Consitent initial conditions could not be calculated.");
		ci->mode = ITI_fmiCSError;
		return fmiError;
	}

	if (CalcInitialDerivativesSafe(pid, ci->sd) < SOLVER_SUCCESS_END) {
		formatLogger(ci->functions.logger, c, ci->instanceName, fmiError, "Error", "Error during calculation of derivatives after initialization of FMU.");
		ci->mode = ITI_fmiCSError;
		return fmiError;
	}

	if (CalcModelOutputs(pid, ci->sd) < SOLVER_SUCCESS_END) {
		formatLogger(ci->functions.logger, c, ci->instanceName, fmiError, "Error", "Error during calculation of outputs after initialization of FMU.");
		ci->mode = ITI_fmiCSError;
		return fmiError;
	}

	 

	ci->mode = ITI_fmiCSInitialized;
	ci->tc0 = tStart;
	ci->bEventPending = fmiFalse;
	return fmiOK;
}

DllExport fmiStatus fmiDoStep(fmiComponent c, fmiReal currentCommunicationPoint, fmiReal communicationStepSize, fmiBoolean newStep)
{
	ITI_fmiCSComponent* ci = (ITI_fmiCSComponent*)c;
	size_t pid = 0;
	ITI_Partition* pPart = &ci->sd->partition[pid];

	if (!ci)
		return fmiFatal;

	if(ci->mode==ITI_fmiCSError)
	{
		formatLogger(ci->functions.logger, c, ci->instanceName, fmiError, "Error", "fmiDoStep: An error occurred in a previous call. Unable to proceed.");
		return fmiError;
	}
	if(ci->mode==ITI_fmiCSInitialized)
	{
		 
		if(ci->tc0!=currentCommunicationPoint)
		{
			formatLogger(ci->functions.logger, c, ci->instanceName, fmiError, "Error", "fmiDoStep: First communication time != tStart from fmiInitialize");
			ci->mode = ITI_fmiCSError;
			return fmiError;
		}
	}
	if(ci->mode==ITI_fmiCSStepping)
	{
		











		if(!newStep){
			formatLogger(ci->functions.logger, c, ci->instanceName, fmiError, "Error", "fmiDoStep: Step is rejected. This is not supported by this FMU.");
			ci->mode = ITI_fmiCSError;
			return fmiError;
		}
	}
	ci->tc0=currentCommunicationPoint;
	ci->tc1=currentCommunicationPoint+communicationStepSize;
	ci->H=communicationStepSize;

	if((ci->mode==ITI_fmiCSInitialized)||(ci->mode==ITI_fmiCSStepping))
	{
		if(communicationStepSize == 0.0)
		{
			if(ci->mode==ITI_fmiCSInitialized)
			{
				if(InitializeConditionsModelOnly(ci->sd) < SOLVER_SUCCESS_END)
				{
					ci->mode = ITI_fmiCSError;
					return fmiError;
				}
			}
			else
			{
				if(EventIterationPartition(pid,ci->sd) < SOLVER_SUCCESS_END)
				{
					ci->mode = ITI_fmiCSError;
					return fmiError;
				}
			}
			ci->bEventPending = fmiFalse;
		}
		else
		{
			if(ci->mode==ITI_fmiCSInitialized)
			{
				if (InitializeConditionsModelFinish(ci->sd) < SOLVER_SUCCESS_END) {
					formatLogger(ci->functions.logger, c, ci->instanceName, fmiError, "Error", "Error during initialization of FMU.");
					ci->mode = ITI_fmiCSError;
					return fmiError;
				}
				 
				if(InitializeSolver(ci->sd) < SOLVER_SUCCESS_END)
				{
					ci->mode = ITI_fmiCSError;
					return fmiError;
				}
			}
			ci->mode = ITI_fmiCSStepping;
			if(ci->bEventPending)
			{
				if(EventIterationPartition(pid,ci->sd) < SOLVER_SUCCESS_END)
				{
					ci->mode = ITI_fmiCSError;
					return fmiError;
				}
				ci->bEventPending = fmiFalse;
			}
			if(CalcOneStep(pid, ci->sd, 1, currentCommunicationPoint+communicationStepSize) < SOLVER_SUCCESS_END)
			{
				ci->mode = ITI_fmiCSError;
				return fmiError;
			}
		}
	}
	else
	{
		formatLogger(ci->functions.logger, c, ci->instanceName, fmiError, "Error", "fmiDoStep: fmiDoStep is called without a call to fmiInitialize before.");
		ci->mode = ITI_fmiCSError;
		return fmiError;
	}
	return fmiOK;
}

DllExport fmiStatus fmiCancelStep(fmiComponent c)
{
	ITI_fmiCSComponent* ci = (ITI_fmiCSComponent*)c;

	if (!ci)
		return fmiFatal;

	formatLogger(ci->functions.logger, c, ci->instanceName, fmiWarning, "Warning", "fmiCancelStep: The call is only allowed for asynchronuous fmiDoStep calls.");

	return fmiWarning;
}

DllExport fmiStatus fmiTerminateSlave(fmiComponent c)
{
	ITI_fmiCSComponent* ci = (ITI_fmiCSComponent*)c;

	if (!ci)
		return fmiFatal;

	if((ci->mode==ITI_fmiCSInitialized)||(ci->mode==ITI_fmiCSStepping))
	{
		if (TerminateModel(ci->sd) < SOLVER_SUCCESS_END) {
			formatLogger(ci->functions.logger, c, ci->instanceName, fmiError, "Error", "fmiTerminateSlave: Error during termination of the model.");
			ci->mode = ITI_fmiCSError;
			return fmiError;
		}
		if(ci->loggingOn)
		{
			char *strStat=NULL;
			BuildSolverStatisticsString(ci->sd, &strStat);
			formatLogger(ci->functions.logger, c, ci->instanceName, fmiOK, "Statistics", "\n%s", strStat);
			free(strStat);
		}
		ci->mode = ITI_fmiCSTerminated;
		return fmiOK;
	}

	return fmiOK;
}

DllExport fmiStatus fmiResetSlave(fmiComponent c)
{
	ITI_fmiCSComponent* ci = (ITI_fmiCSComponent*)c;

	if (!ci)
		return fmiFatal;

	if((ci->mode==ITI_fmiCSInitialized)||(ci->mode==ITI_fmiCSStepping))
	{
		if (TerminateModel(ci->sd) < SOLVER_SUCCESS_END) {
			formatLogger(ci->functions.logger, c, ci->instanceName, fmiError, "Error", "fmiResetSlave: Error during termination of the model.");
			ci->mode = ITI_fmiCSError;
			return fmiError;
		}
	}

	ci->mode = ITI_fmiCSInstantiated;

	return fmiOK;
}


DllExport void fmiFreeSlaveInstance(fmiComponent c)
{
	size_t i;
	ITI_fmiCSComponent* ci = (ITI_fmiCSComponent*)c;

	if (!ci)
		return;

	for(i=0; i<ITI_MAX_REAL_INPUT_DER_ORDER+1; i++)
		N_VDestroy_Serial(ci->ur[i]);

	N_VDestroy_Serial(ci->uModel);

	FreeSolverInstance(ci->sd);
	ci->sd = (void*)0;

	free(ci);
}

DllExport fmiStatus fmiSetDebugLogging  (fmiComponent c, fmiBoolean loggingOn)
{
	ITI_fmiCSComponent* ci = (ITI_fmiCSComponent*)c;

	if (!ci)
		return fmiFatal;

	ci->loggingOn = loggingOn;

	return fmiOK;
}

DllExport fmiStatus fmiSetReal(fmiComponent c, const fmiValueReference vr[], size_t nvr, const fmiReal value[])
{
	size_t i;
	size_t index;
	enum ITI_fmiVarKind kind;
	ITI_fmiCSComponent* ci = (ITI_fmiCSComponent*)c;

	if (!ci)
		return fmiFatal;

	for(i=0; i<nvr; i++)
	{
		fmiStatus status = splitValueRef(ci, vr[i], &kind, &index);
		if(status != fmiOK)
			return status;
		status = setRealValue(ci, vr[i], kind, index, value[i]);
		if(status != fmiOK)
			return status;
	}

	return fmiOK;
}

DllExport fmiStatus fmiSetInteger(fmiComponent c, const fmiValueReference vr[], size_t nvr, const fmiInteger value[])
{
	size_t i;
	size_t index;
	enum ITI_fmiVarKind kind;
	ITI_fmiCSComponent* ci = (ITI_fmiCSComponent*)c;

	if (!ci)
		return fmiFatal;

	for(i=0; i<nvr; i++)
	{
		fmiStatus status = splitValueRef(ci, vr[i], &kind, &index);
		if(status != fmiOK)
			return status;
		status = setIntegerValue(ci, vr[i], kind, index, value[i]);
		if(status != fmiOK)
			return status;
	}
	return fmiOK;
}

DllExport fmiStatus fmiSetBoolean(fmiComponent c, const fmiValueReference vr[], size_t nvr, const fmiBoolean value[])
{
	size_t i;
	size_t index;
	enum ITI_fmiVarKind kind;
	ITI_fmiCSComponent* ci = (ITI_fmiCSComponent*)c;

	if (!ci)
		return fmiFatal;

	for(i=0; i<nvr; i++)
	{
		fmiBoolean iTmp;
		fmiStatus status = splitValueRef(ci, vr[i], &kind, &index);
		if(status != fmiOK)
			return status;

		iTmp = (fmiInteger)value[i];
		status = setIntegerValue(ci, vr[i], kind, index, iTmp);
		if(status != fmiOK)
			return status;
	}
	return fmiOK;
}

DllExport fmiStatus fmiSetString(fmiComponent c, const fmiValueReference vr[], size_t nvr, const fmiString value[])
{
	size_t i;
	size_t index;
	enum ITI_fmiVarKind kind;
	ITI_fmiCSComponent* ci = (ITI_fmiCSComponent*)c;

	if (!ci)
		return fmiFatal;

	for(i=0; i<nvr; i++)
	{
		fmiStatus status = splitValueRef(ci, vr[i], &kind, &index);
		if(status != fmiOK)
			return status;
		status = setStringValue(ci, vr[i], kind, index, value[i]);
		if(status != fmiOK)
			return status;
	}
	return fmiOK;
}

DllExport fmiStatus fmiGetReal(fmiComponent c, const fmiValueReference vr[], size_t nvr, fmiReal value[])
{
	size_t i;
	size_t index;
	enum ITI_fmiVarKind kind;
	ITI_fmiCSComponent* ci = (ITI_fmiCSComponent*)c;

	if (!ci)
		return fmiFatal;

	for(i=0; i<nvr; i++)
	{
		fmiStatus status = splitValueRef(ci, vr[i], &kind, &index);
		if(status != fmiOK)
			return status;

		status = getRealValue(ci, vr[i], kind, index, &value[i]);
		if(status != fmiOK)
			return status;
	}
	return fmiOK;
}

DllExport fmiStatus fmiGetInteger(fmiComponent c, const fmiValueReference vr[], size_t nvr, fmiInteger value[])
{
	size_t i;
	size_t index;
	enum ITI_fmiVarKind kind;
	ITI_fmiCSComponent* ci = (ITI_fmiCSComponent*)c;

	if (!ci)
		return fmiFatal;

	for(i=0; i<nvr; i++)
	{
		fmiStatus status = splitValueRef(ci, vr[i], &kind, &index);
		if(status != fmiOK)
			return status;

		status = getIntegerValue(ci, vr[i], kind, index, &value[i]);
		if(status != fmiOK)
			return status;
	}
	return fmiOK;
}

DllExport fmiStatus fmiGetBoolean(fmiComponent c, const fmiValueReference vr[], size_t nvr, fmiBoolean value[])
{
	size_t i;
	size_t index;
	enum ITI_fmiVarKind kind;
	ITI_fmiCSComponent* ci = (ITI_fmiCSComponent*)c;
	fmiInteger iTmp;

	if (!ci)
		return fmiFatal;

	for(i=0; i<nvr; i++)
	{
		fmiStatus status = splitValueRef(ci, vr[i], &kind, &index);
		if(status != fmiOK)
			return status;

		status = getIntegerValue(ci, vr[i], kind, index, &iTmp);
		if(status != fmiOK)
			return status;

		value[i] = (fmiBoolean)iTmp;
	}
	return fmiOK;
}

DllExport fmiStatus fmiGetString (fmiComponent c, const fmiValueReference vr[], size_t nvr, fmiString  value[])
{
	size_t i;
	size_t index;
	enum ITI_fmiVarKind kind;
	ITI_fmiCSComponent* ci = (ITI_fmiCSComponent*)c;

	if (!ci)
		return fmiFatal;

	for(i=0; i<nvr; i++)
	{
		fmiStatus status = splitValueRef(ci, vr[i], &kind, &index);
		if(status != fmiOK)
			return status;

		status = getStringValue(ci, vr[i], kind, index, &value[i]);
		if(status != fmiOK)
			return status;
	}
	return fmiOK;
}

DllExport fmiStatus fmiGetRealOutputDerivatives(fmiComponent c, const fmiValueReference vr[], size_t nvr, const fmiInteger order[], fmiReal value[])
{
	ITI_fmiCSComponent* ci = (ITI_fmiCSComponent*)c;

	if (!ci)
		return fmiFatal;

	formatLogger(ci->functions.logger, c, ci->instanceName, fmiWarning, "Warning", "fmiGetRealOutputDerivatives(): Real Output Derivatives are not provided!");
	return fmiWarning;
}

DllExport fmiStatus fmiSetRealInputDerivatives(fmiComponent c, const fmiValueReference vr[], size_t nvr, const fmiInteger order[], const fmiReal value[]){
	char strError[255];
	size_t pid = 0;
	size_t i;
	size_t index;
	enum ITI_fmiVarKind kind;
	ITI_fmiCSComponent* ci = (ITI_fmiCSComponent*)c;
	ITI_Partition* pPart;
	fmiStatus status = fmiOK;

	if (!ci)
		return fmiFatal;

	pPart = &ci->sd->partition[0];

	for(i=0; i<nvr; i++){
		fmiStatus retStatus = splitValueRef(ci, vr[i], &kind, &index);
		if(retStatus != fmiOK)	{
			status = fmiWarning;
		}
		if((kind==ITI_fmiInput) && (index<(size_t)pPart->curr->size.iu_real) && (order[i]<=2))		{
			Ith(ci->ur[order[i]],index)=value[i];
		}
		else{
			if(kind!=ITI_fmiInput)
				strcpy(strError, "ValueReference is no real input.\n");
			if(index>=(size_t)pPart->curr->size.iu_real)
				strcpy(strError, "ValueReference is unknown.\n");
			if(order[i]>2)
				strcpy(strError, "Order is greater 2.\n");
			formatLogger(ci->functions.logger, c, ci->instanceName, fmiWarning, "Warning", "fmiSetRealInputDerivatives(): %s fmiValueReference = %u", strError, vr[i]);
			status = fmiWarning;
		}
	}
	return status;
}

DllExport fmiStatus fmiGetStatus(fmiComponent c, const fmiStatusKind s, fmiStatus* value)
{
	return fmiDiscard;
}

DllExport fmiStatus fmiGetRealStatus(fmiComponent c, const fmiStatusKind s, fmiReal* value)
{
	return fmiDiscard;
}

DllExport fmiStatus fmiGetIntegerStatus(fmiComponent c, const fmiStatusKind s, fmiInteger* value)
{
	return fmiDiscard;
}

DllExport fmiStatus fmiGetBooleanStatus(fmiComponent c, const fmiStatusKind s, fmiBoolean* value)
{
	return fmiDiscard;
}

DllExport fmiStatus fmiGetStringStatus (fmiComponent c, const fmiStatusKind s, fmiString* value)
{
	return fmiDiscard;
}

 

static _ITI_INLINE fmiStatus splitValueRef(ITI_fmiCSComponent* ci, const fmiValueReference vRef, enum ITI_fmiVarKind* kind, size_t* index)
{
	*kind = vRef>>28;
	if(*kind > ITI_fmiDiscInput)
	{
		formatLogger(ci->functions.logger, (fmiComponent)ci, ci->instanceName, fmiError, "Error", "fmiSetXXX(..) or fmiGetXXX(..) was called with the invalid fmiValueReference: %u", vRef);
		return fmiError;
	}
	*index = vRef&0x0FFFFF;
	return fmiOK;
}

static _ITI_INLINE fmiStatus setRealValue(ITI_fmiCSComponent* c, const fmiValueReference vRef, const enum ITI_fmiVarKind kind, const size_t index, const fmiReal v)
{
	char strError[255] = "";
	size_t pid = 0;
	ITI_SolverData* cvd = (ITI_SolverData*)c->pData;
	ITI_Partition* pPart = &c->sd->partition[0];

	switch(kind)
	{
	case ITI_fmiContVariable:
		strcpy(strError, "It is not allowed to set a continuous internal real variable!");
		break;
	case ITI_fmiDiscVariable:
		strcpy(strError, "It is not allowed to set a discrete internal real variable!");
		break;
	case ITI_fmiDiscInput:
		if (index<(size_t)pPart->curr->size.iu_real)
		{
			if (Ith(c->ur[0], index) != v) {
				c->bEventPending = fmiTrue;
				c->uInterpolationValid = fmiFalse;
				Ith(c->ur[0], index) = v;
			}
			return fmiOK;
		}
		else
			strcpy(strError, "Invalid valueReference!");
		break;
	case ITI_fmiInput:
		if(index<(size_t)pPart->curr->size.iu_real)
		{
			if(Ith(c->ur[0],index)!=v){
				if(c->mode==ITI_fmiCSInitialized)
					c->bEventPending = fmiTrue;
				c->uInterpolationValid = fmiFalse;
				Ith(c->ur[0],index)=v;
			}
			return fmiOK;
		}
		else
			strcpy(strError, "Invalid valueReference!");
		break;
	case ITI_fmiOutput:
		strcpy(strError, "It is not allowed to set a real output!");
		break;
	case ITI_fmiParameter:
		if(c->mode == ITI_fmiCSInstantiated)
		{
			if(index<(size_t)pPart->transient->size.ip_real)
			{
				if(pPart->transient->p.realData[index] != v)
				{
					pPart->transient->p.realData[index] = v;
				}
				return fmiOK;
			}
			else
				strcpy(strError, "Invalid valueReference!");
		}
		else
			strcpy(strError, "It is not allowed to set a parameter after fmiInitializeSlave(..) was called!");
		break;
	}
	if (strlen(strError) > 0)
	{
		formatLogger(c->functions.logger, (fmiComponent)c, c->instanceName, fmiError, "Error", "Error in fmiSetReal(): %s fmiValueReference = %u", strError, vRef);
		return fmiError;
	}
	else
		return fmiOK;
}

static _ITI_INLINE fmiStatus setIntegerValue(ITI_fmiCSComponent* c, const fmiValueReference vRef, const enum ITI_fmiVarKind kind, const size_t index, const fmiInteger v)
{
	char strError[255] = "";
	size_t pid = 0;
	ITI_SolverData* cvd = (ITI_SolverData*)c->pData;
	ITI_Partition* pPart = &c->sd->partition[0];

	switch(kind)
	{
	case ITI_fmiContVariable:
		strcpy(strError, "Invalid valueReference!");
		break;
	case ITI_fmiDiscVariable:
		strcpy(strError, "It is not allowed to set a discrete internal integer variable!");
		break;
	case ITI_fmiDiscInput:
	case ITI_fmiInput:
		if(index<(size_t)pPart->curr->size.iu_int)
		{
			if(pPart->curr->u.intData[index] != v)
			{
				pPart->curr->u.intData[index] = v;
				c->bEventPending = fmiTrue;
			}
			return fmiOK;
		}
		else
			strcpy(strError, "Invalid valueReference!");
		break;
	case ITI_fmiOutput:
		strcpy(strError, "It is not allowed to set an integer output!");
		break;
	case ITI_fmiParameter:
		if(c->mode == ITI_fmiCSInstantiated)
		{
			if(index<(size_t)pPart->transient->size.ip_int)
			{
				if(pPart->transient->p.intData[index] != v)
				{
					pPart->transient->p.intData[index] = v;
				}
				return fmiOK;
			}
			else
				strcpy(strError, "Invalid valueReference!");
		}
		else
			strcpy(strError, "It is not allowed to set a parameter after fmiInitializeSlave(..) was called!");
		break;
	}
	if (strlen(strError) > 0)
	{
		formatLogger(c->functions.logger, (fmiComponent)c, c->instanceName, fmiError, "Error", "Error in fmiSetInteger(): %s fmiValueReference = %u", strError, vRef);
		return fmiError;
	}
	else
		return fmiOK;
}

static _ITI_INLINE fmiStatus setStringValue(ITI_fmiCSComponent* c, const fmiValueReference vRef, const enum ITI_fmiVarKind kind, const size_t index, const fmiString v)
{
	char strError[255] = "";

	size_t pid = 0;
	ITI_SolverData* cvd = (ITI_SolverData*)c->pData;
	ITI_Partition* pPart = &c->sd->partition[0];

	switch(kind)
	{
	case ITI_fmiContVariable:
		strcpy(strError, "Invalid valueReference!");
		break;
	case ITI_fmiDiscVariable:
		strcpy(strError, "It is not allowed to set a discrete internal string variable!");
		break;
	case ITI_fmiDiscInput:
	case ITI_fmiInput:
		if(index<(size_t)pPart->curr->size.iu_str)
		{
			 
			pPart->curr->u.strData[index] = (ITI_char*)v;

			return fmiOK;
		}
		else
			strcpy(strError, "Invalid valueReference!");
		break;
	case ITI_fmiOutput:
		strcpy(strError, "It is not allowed to set a string output!");
		break;
	case ITI_fmiParameter:
		if(c->mode == ITI_fmiCSInstantiated)
		{
			if(index<(size_t)pPart->curr->size.ip_str)
			{
				AssignAdaptString_calloc(&pPart->transient->p, v, index, 0, 0);
				return fmiOK;
			}
			else
				strcpy(strError, "Invalid valueReference!");
		}
		else
			strcpy(strError, "It is not allowed to set a parameter after fmiInitializeSlave(..) was called!");
		break;
	}
	if (strlen(strError) > 0)
	{
		formatLogger(c->functions.logger, (fmiComponent)c, c->instanceName, fmiError, "Error", "Error in fmiSetString(): %s fmiValueReference = %u", strError, vRef);
		return fmiError;
	}
	else
		return fmiOK;
}

static _ITI_INLINE fmiStatus getRealValue(ITI_fmiCSComponent* c, const fmiValueReference vRef, const enum ITI_fmiVarKind kind, const size_t index, fmiReal* v)
{
	size_t pid = 0;
	ITI_SolverData* cvd = (ITI_SolverData*)c->pData;
	ITI_Partition* pPart = &c->sd->partition[0];

	size_t size;
	ITI_real* pv;

	switch(kind)
	{
	case ITI_fmiContVariable:
		size = (size_t)pPart->curr->size.iv_real;
		pv = pPart->curr->v.realData;
		break;
	case ITI_fmiDiscVariable:
		size = (size_t)pPart->curr->size.iz_real;
		pv = pPart->curr->z.realData;
		break;
	case ITI_fmiDiscInput:
	case ITI_fmiInput:
		size = (size_t)pPart->curr->size.iu_real;
		pv = pPart->curr->u.realData;
		break;
	case ITI_fmiOutput:
		size = (size_t)pPart->curr->size.iy_real;
		pv = pPart->curr->y.realData;
		break;
	case ITI_fmiParameter:
		size = (size_t)pPart->curr->size.ip_real;
		pv = pPart->curr->p.realData;
		break;
	}

	if(index<size)
	{
		*v = pv[index];
		return fmiOK;
	}
	else
	{
		char strError[] = "Invalid valueReference!";
		formatLogger(c->functions.logger, (fmiComponent)c, c->instanceName, fmiError, "Error", "Error in fmiGetReal(): %s fmiValueReference = %u", strError, vRef);
		return fmiError;
	}
}

static _ITI_INLINE fmiStatus getIntegerValue(ITI_fmiCSComponent* c, const fmiValueReference vRef, const enum ITI_fmiVarKind kind, const size_t index, fmiInteger* v)
{
	size_t pid = 0;
	ITI_SolverData* cvd = (ITI_SolverData*)c->pData;
	ITI_Partition* pPart = &c->sd->partition[0];

	size_t size;
	ITI_int* pv;

	switch(kind)
	{
	case ITI_fmiContVariable:
		size = (size_t)pPart->curr->size.iv_int;
		pv = pPart->curr->v.intData;
		break;
	case ITI_fmiDiscVariable:
		size = (size_t)pPart->curr->size.iz_int;
		pv = pPart->curr->z.intData;
		break;
	case ITI_fmiDiscInput:
	case ITI_fmiInput:
		size = (size_t)pPart->curr->size.iu_int;
		pv = pPart->curr->u.intData;
		break;
	case ITI_fmiOutput:
		size = (size_t)pPart->curr->size.iy_int;
		pv = pPart->curr->y.intData;
		break;
	case ITI_fmiParameter:
		size = (size_t)pPart->curr->size.ip_int;
		pv = pPart->curr->p.intData;
		break;
	}

	if(index<size)
	{
		*v = pv[index];
		return fmiOK;
	}
	else
	{
		char strError[] = "Invalid valueReference!";
		formatLogger(c->functions.logger, (fmiComponent)c, c->instanceName, fmiError, "Error", "Error in fmiGetInteger(): %s fmiValueReference = %u", strError, vRef);
		return fmiError;
	}
}

static _ITI_INLINE fmiStatus getStringValue(ITI_fmiCSComponent* c, const fmiValueReference vRef, const enum ITI_fmiVarKind kind, const size_t index, fmiString* v)
{
	size_t pid = 0;
	ITI_SolverData* cvd = (ITI_SolverData*)c->pData;
	ITI_Partition* pPart = &c->sd->partition[0];

	size_t size;
	fmiString* pv;

	switch(kind)
	{
	case ITI_fmiContVariable:
		size = (size_t)pPart->curr->size.iv_str;
		pv = (fmiString*)pPart->curr->v.strData;
		break;
	case ITI_fmiDiscVariable:
		size = (size_t)pPart->curr->size.iz_str;
		pv = (fmiString*)pPart->curr->z.strData;
		break;
	case ITI_fmiDiscInput:
	case ITI_fmiInput:
		size = (size_t)pPart->curr->size.iu_str;
		pv = (fmiString*)pPart->curr->u.strData;
		break;
	case ITI_fmiOutput:
		size = (size_t)pPart->curr->size.iy_str;
		pv = (fmiString*)pPart->curr->y.strData;
		break;
	case ITI_fmiParameter:
		size = (size_t)pPart->curr->size.ip_str;
		pv = (fmiString*)pPart->curr->p.strData;
		break;
	}

	if(index<size)
	{
		*v = pv[index];
		return fmiOK;
	}
	else
	{
		char strError[] = "Invalid valueReference!";
		formatLogger(c->functions.logger, (fmiComponent)c, c->instanceName, fmiError, "Error", "Error in getStringValue(): %s fmiValueReference = %u", strError, vRef);
		return fmiError;
	}
}

void FMI_CS_TraceFunc(int iTab, int iKind, const char* strCapt, const char* strTxt, const void* pVoid)
{
	if(pVoid)
	{
		ITI_SolverInfo* psInfo = (ITI_SolverInfo*)pVoid;
		if(psInfo->pContainer)
		{
			ITI_fmiCSComponent* ci = (ITI_fmiCSComponent*)psInfo->pContainer;
			char strKind[12];
			fmiStatus status;
			switch(iKind)
			{
			case Info:
				strcpy(strKind, "Information");
				status = fmiOK;
				break;
			case Warning:
				strcpy(strKind, "Warning");
				status = fmiWarning;
				break;
			case Error:
				strcpy(strKind, "Error");
				status = fmiError;
				break;
			case Debug:
				strcpy(strKind, "Debug");
				status = fmiOK;
				break;
			}

			if(strlen(strTxt) == 0)
				formatLogger(ci->functions.logger, (fmiComponent)ci, ci->instanceName, status, strKind, strCapt);
			else
				formatLogger(ci->functions.logger, (fmiComponent)ci, ci->instanceName, status, strKind, "%s: %s", strCapt, strTxt);
		}
	}
}

static void formatLogger(fmiCallbackLogger logger, fmiComponent c, fmiString instanceName, fmiStatus status, fmiString category, fmiString message, ...)
{
	if (logger)
	{
		char msg[10000];
		va_list argList;

		va_start(argList, message);
		vsnprintf(msg, 10000, message, argList);
		logger(c, instanceName, status, category, msg);
		va_end(argList);
	}
}

 
static fmiStatus allocateSlave(fmiComponent c)
{
	ITI_fmiCSComponent* ci = (ITI_fmiCSComponent*)c;

	if (CreateSolverInstance(&ci->sd, NULL, 0, 0, &FMI_CS_TraceFunc) > SOLVER_SUCCESS_END) {
		ITI_Partition* pPart = &ci->sd->partition[0];
		size_t i;
		pPart->curr->sInfo.pContainer = (void*)c;

		ci->uInterpolationValid = fmiFalse;
		ci->tLastInputInterpolation = -1.123456789;

		for (i = 0; i < ITI_MAX_REAL_INPUT_DER_ORDER + 1; i++)
		{
			ci->ur[i] = N_VNew_Serial(pPart->curr->size.iu_real);
			N_VConst(0.0, ci->ur[i]);
		}
		ci->uModel = N_VNewEmpty_Serial(pPart->curr->size.iu_real);

		SetInterfaceFunctions(0, ci->sd,
			&FMI_CS_OnPrepareSaveOutputs,
			&FMI_CS_OnSaveOutputs,
			&FMI_CS_OnFinishSaveOutputs,
			NULL,
			NULL);
		SetSetInputsFunction(ci->sd, &FMI_CS_OnSetInputs);

		ci->mode = ITI_fmiCSInstantiated;
		ci->bEventPending = fmiFalse;
		return fmiOK;
	}
	return fmiError;
}
