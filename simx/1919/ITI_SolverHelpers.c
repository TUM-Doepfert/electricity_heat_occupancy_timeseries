/**
 * ITI_SolverHelpers.c
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#include "ITI_crt.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <stdarg.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>
#include "ITI_SolverHelpers.h"

#if defined ITI_SFuncSolver || defined ITI_FMI_CS2

#include "ITI_Declarations.h"
#include "ITI_ModelInclude.h"

#else

#ifndef ITI_COMP_SIM
#include "ITI_ModelInclude.h"
#endif

#endif

#if defined(_PERFMEA) && defined(_MSC_VER) && !defined(_WIN64)

#define cpuid __asm __emit 0fh __asm __emit 0a2h
#define rdtsc __asm __emit 0fh __asm __emit 031h

__int64 Measure_Cycl(void)
{
	unsigned int time_low, time_high;
	unsigned __int64 cycles;

	_asm{
		pushad
		cpuid
		rdtsc
		mov time_low, eax
		mov time_high, edx
		popad
		}

	cycles =(__int64)(((unsigned __int64)time_high << 32) | time_low);

	return cycles;


}

#endif

int str_case_cmp(const char* str1, const char* str2)
{
	while (*str1 && *str2 && tolower(*str1) == tolower(*str2)){
		str1++;
		str2++;
	}

	if (!*str1 && !*str2)
		return 0;
	else if (tolower(*str1) < tolower(*str2))
		return -1;
	else
		return 1;
}

void FillSolverSettings(ITI_SolverSettings* pSS)
{
#ifndef ITI_COMP_SIM
	pSS->tStart = ITI_tStart;
	pSS->tStop = ITI_tStop;
	pSS->dtMin = ITI_dtMin;
	pSS->dtMax = ITI_dtMax;
	pSS->dtDetect = ITI_dtDetect;
	pSS->absTol = ITI_absTol;
	pSS->relTol = ITI_relTol;
	pSS->dtProtMin = ITI_dtProtMin;
	pSS->mode = ITI_mode;
	pSS->ignoreMinMax = ITI_ignoreMinMax;
	pSS->minmax = ITI_minmax;
#if ITI_minmax == 1
	pSS->ignoreMinMax = ITI_false;
#endif
	pSS->zeros = ITI_zeros;
	pSS->saveMode = ITI_SaveOutputs_Approach;
	pSS->trace = _Trace_On;
	pSS->limitdtMin = ITI_limitdtMin;
	pSS->effJac = ITI_effJac;
	pSS->parJac = ITI_parJac;
	pSS->maxStepNumberBetweenJacobianEvaluations = ITI_maxStepNumberBetweenJacobianEvaluations;
	pSS->maxOrder = ITI_maxOrder;
	pSS->gltol = ITI_blockTol;
	pSS->linSolv = ITI_blockLinSolv;
	pSS->threadLimit = -1;
	pSS->hysteresis = ITI_hysteresis;
	pSS->scaleEpsilon = ITI_scaleEpsilon;
	pSS->adaptEpsilon = ITI_adaptEpsilon;
	pSS->epsilon = ITI_epsilon;
	pSS->maxEpsilon = ITI_maxEpsilon;
	pSS->adaptThreshold = ITI_adaptThreshold;
	pSS->adaptFactor = ITI_adaptFactor;
	pSS->bAssertOn = _Modelica_Assert_On;
	pSS->bAssertTraceOn = _Modelica_Assert_Trace_On;
	pSS->bStopAtStop = ITI_true;
	pSS->eventHandlingMode = ITI_EventHandlingMode;
	pSS->bStopOnError = ITI_false;
	pSS->consistentInitialConditions = ITI_true;
#endif
}

#if !defined(ITI_DSPACE)
int ReadSolverSettingsFromFile(FILE* file, ITI_SolverSettings* pSS)
{
	int nParameters = 0;

	if(file && pSS){
		char* line;
		int nChars;
		int nPos;

		 
		nPos = ftell(file);
		fseek(file, 0,SEEK_END);

		 
		nChars = ftell(file);

		 
		fseek(file, nPos, SEEK_SET);
		line = (char*)calloc(nChars, sizeof(char));

		while(fgets(line, nChars, file)){
			size_t iSep = 0;

			iSep = strcspn(line, "=\t\n\r");
			if(iSep>0){
				double dblVal;
				sscanf(line+iSep+1, "%lg", &dblVal);
				line[iSep] = '\0';
				while(iSep>1 && line[iSep-1]==0x20){
					 
					iSep--;
					line[iSep] = '\0';
				}

				if(str_case_cmp(line, "tStart")==0){
					pSS->tStart = dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "tStop")==0){
					pSS->tStop = dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "dtMin")==0){
					pSS->dtMin = dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "dtMax")==0){
					pSS->dtMax = dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "absTol")==0){
					pSS->absTol = dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "relTol")==0){
					pSS->relTol = dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "dtProtMin")==0){
					pSS->dtProtMin = dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "saveMode")==0){
					pSS->saveMode = (int)dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "mode")==0){
					pSS->mode = (int)dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "minmax")==0){
					pSS->minmax = (int)dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "ignoreMinMax")==0){
					pSS->ignoreMinMax = (int)dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "zeros")==0){
					pSS->zeros = (int)dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "traceOn")==0){
					pSS->trace = dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "limitdtMin")==0){
					pSS->limitdtMin = (int)dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "effJac")==0){
					pSS->effJac = (int)dblVal;
					nParameters++;
				}
				else if (str_case_cmp(line, "parJac") == 0) {
					pSS->parJac = (int)dblVal;
					nParameters++;
				}
				else if (str_case_cmp(line, "maxStepNumberBetweenJacobianEvaluations") == 0) {
					pSS->maxStepNumberBetweenJacobianEvaluations = (int)dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "maxOrder")==0){
					pSS->maxOrder = (int)dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "blockTol")==0){
					pSS->gltol = dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "blockLinSolv")==0){
					pSS->linSolv = (int)dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "threadLimit")==0){
					pSS->threadLimit = (int)dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "hysteresis")==0){
					pSS->hysteresis = (int)dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "scaleEpsilon")==0){
					pSS->scaleEpsilon = (int)dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "adaptEpsilon")==0){
					pSS->adaptEpsilon = (int)dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "epsilon")==0){
					pSS->epsilon = dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "maxEpsilon")==0){
					pSS->maxEpsilon = dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "adaptThreshold")==0){
					pSS->adaptThreshold = (int)dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "adaptFactor")==0){
					pSS->adaptFactor = (int)dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "assertOn")==0){
					pSS->bAssertOn = (int)dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "assertTraceOn")==0){
					pSS->bAssertTraceOn = (int)dblVal;
					nParameters++;
				}
				else if(str_case_cmp(line, "EventHandlingMode")==0){
					pSS->eventHandlingMode = (int)dblVal;
					nParameters++;
				}
				else if (str_case_cmp(line, "stopOnError") == 0) {
					pSS->bStopOnError = (ITI_ushort)dblVal;
					nParameters++;
				}
			}
		}
		free(line);
	}
	return nParameters;
}

int ReadVariationNumberFromStream(FILE* fp)
{
	int nVariations = 0;
#if !defined ITI_TWINCAT
	if (fp) {
		int bufLen = 64;
		char* buf = (char*)malloc(bufLen*sizeof(char));
		if (buf) {
			int nPos = ftell(fp);
			while (ReadLine(&buf, &bufLen, fp) == 0) {
				if (buf[0] == '/' && buf[1] == '/') {
					nVariations++;
				}
				else {
					char* token = buf;
					token = strtok(token, " \t\r");
					if (token) {
						char* endptr;
						double dblVal = strtod(token, &endptr);
						if (*endptr == 0) {
							 
							nVariations++;
						}
					}
				}
			}
			fseek(fp, nPos, SEEK_SET);
			free(buf);
		}
	}
#endif
	return nVariations;
}

int ReadParametersFromStream(char** buf, int* bufLen, FILE* fp, double **p, unsigned int* isCommented)
{
	int nParameters = 0;
	*isCommented = 0;
	*p = NULL;
#if !defined ITI_TWINCAT
	if (fp) {
		while (ReadLine(buf, bufLen, fp) == 0) {
			if ((*buf)[0] == '/' && (*buf)[1] == '/') {
				*isCommented = 1;
			}
			else {
				char* token = *buf;
				token = strtok(token, " \t\r");
				while (token) {
					char* endptr;
					double dblVal = strtod(token, &endptr);
					if (*endptr == 0) {
						nParameters++;
					}
					token = strtok(NULL, " \t\r");
				}
			}
			if (*isCommented == 0) {
				if (nParameters == 0) {
					 
					continue;
				}
				else {
					int i = 0;
					char* token = *buf;
					*p = (double*)calloc(nParameters, sizeof(double));
					if (!(*p)) {
						return 0;
					}
					while (i < nParameters) {
						char* endptr;
						double dblVal = strtod(token, &endptr);
						if (*endptr == 0) {
							(*p)[i++] = dblVal;
						}
						token += strlen(token) + 1;
						token += strspn(token, " \t\r");
					}
				}
			}
			break;
		}
	}
#endif
	return nParameters;
}

int ReadLine(char** buf, int* bufLen, FILE* fp)
{
	char* offset;
	int oldBufLen;
	char* p;

	if (fgets(*buf, *bufLen, fp) == NULL) {
		return EOF;
	}

	do {
		char* tmp;

		if ((p = strchr(*buf, '\n')) != NULL) {
			*p = '\0';
			return 0;
		}

		oldBufLen = *bufLen;
		*bufLen *= 2;
		tmp = (char*)realloc(*buf, (size_t)*bufLen);
		if (!tmp) {
			return 1;
		}
		*buf = tmp;
		offset = &((*buf)[oldBufLen - 1]);

	} while (fgets(offset, oldBufLen + 1, fp));

	return 0;
}
#endif

int GetNumberOfDecimalPlaces(const double dblVal)
{
	double dblHelp = dblVal;
	double dblErrBound = dblVal * 3e-16;
	int i = 0;
	 
	while(fabs(dblHelp - ceil(dblHelp-0.5)) > dblErrBound)
	{
		++i;
		dblHelp *= 10;
		dblErrBound *= 10;
	}
	return i;
}

 
void Write2Stream(FILE* stream, double* val1, double* val2, double* val3, int c1, int c2, int c3, int i1, int i2, int i3)
{
	int k;
	char charF1[255];
	char charF1t[255];
	sprintf(charF1, "%%.%df\t", i1);
	sprintf(charF1t, "%%.%df", i1);

	for(k=0; k<(c1-1); k++)
		fprintf(stream, charF1, val1[k]);
	fprintf(stream, charF1t, val1[k]);

	if(c2>0)
	{
		sprintf(charF1, "%%.%df\t", i2);
		sprintf(charF1t, "%%.%df", i2);
		fprintf(stream, "\t");
		for(k=0; k<(c2-1); k++)
			fprintf(stream, charF1, val2[k]);
		fprintf(stream, charF1t, val2[k]);
	}

	if(c3>0)
	{
		sprintf(charF1, "%%.%df\t", i3);
		sprintf(charF1t, "%%.%df", i3);
		fprintf(stream, "\t");
		for(k=0; k<(c3-1); k++)
			fprintf(stream, charF1, val3[k]);
		fprintf(stream, charF1t, val3[k]);
	}
	fprintf(stream, "\n");
}

void WriteOutput2Stream(FILE* stream, ITI_outputData* outputData, ITI_PartitionVar* pData, int ySize, int prec_t, int prec_y)
{
	int i = 0;
	char charF[255];
	char charFt[255];
	const char* charIt = "\t%d";
	const char* charSt = "\t%s";

	if (stream==0 || outputData==0)
		return;

	sprintf(charF, "%%.%df", prec_t);
	sprintf(charFt, "\t%%.%df", prec_y);

	fprintf(stream, charF, pData->t);

	for (i = 0; i < ySize; i++){
		switch (outputData[i].type){
			case SharedType_Int :
				fprintf(stream, charIt, pData->y.intData[outputData[i].typeIndex]);
				break;
			case SharedType_Real :
				fprintf(stream, charFt, pData->y.realData[outputData[i].typeIndex]);
				break;
			case SharedType_Str :
				fprintf(stream, charSt, pData->y.strData[outputData[i].typeIndex]);
				break;
			default:
				break;
		}
	}
	fprintf(stream, "\n");
}

void WriteOutputStreamHeader(FILE* stream , ITI_outputData* outputs, int iy)
{
	int i;
	fprintf(stream, "t [s]");

	for(i=0; i<iy; i++)
		fprintf(stream, "\t%s [%s]", outputs[i].name, outputs[i].unit);

	fprintf(stream, "\n");
}

 
void WriteStreamHeader(FILE* stream, const char* str1, const char* str2, const char* str3, int c1, int c2, int c3)
{
	int i;

	if(c1>1)
	{
		for(i=0; i<(c1-1); i++)
			fprintf(stream, "%s%d\t", str1, i);
		fprintf(stream, "%s%d", str1, i);
	}
	else
		fprintf(stream, "%s", str1);

	if(c2>0)
		fprintf(stream, "\t");
	if(c2>1)
	{
		for(i=0; i<(c2-1); i++)
			fprintf(stream, "%s%d\t", str2, i);
		fprintf(stream, "%s%d", str2, i);
	}
	else
		fprintf(stream, "%s", str2);

	if(c3>0)
		fprintf(stream, "\t");
	if(c3>1)
	{
		for(i=0; i<(c3-1); i++)
			fprintf(stream, "%s%d\t", str3, i);
		fprintf(stream, "%s%d", str3, i);
	}
	else
		fprintf(stream, "%s", str3);

	fprintf(stream, "\n");
}

void ShowActTime(clock_t* cLast, ITI_real t, ITI_real tStop, ITI_int iStart)
{
	clock_t cAct = clock();

	if(iStart || (double)(cAct - (*cLast)) /  CLOCKS_PER_SEC > 1.0)
	{
		fprintf(stdout, "%.3f / %.3f\r", t, tStop);
		fflush(stdout);
		*cLast = cAct;
	}
}

void WriteRootCounter(const char* strFile, int* rootctr, int iSize){
	int i;
	int iMax=0;
	int iSum=0;
	int iSwitching=0;

	FILE* fFile = fopen(strFile, "w+");
	for(i=0; i<iSize; i++)
	{
		iMax = FindMax(rootctr, iSize);
		if(iMax>-1)
		{
			fprintf(fFile, "zero(%d)\t%d\n", iMax, rootctr[iMax]);
			iSwitching++;
			iSum+=rootctr[iMax];
			rootctr[iMax]=0;
		}
		else
			break;
	}
	fprintf(fFile, "Sum = %d\n", iSum);
	fprintf(fFile, "%d from %d roots switched\n", iSwitching, iSize);
	fclose(fFile);
}

int FindMax(int* iData, int iSize)
{
	int i;
	int iActMax=0;
	int iIndex=-1;
	for(i=0; i<iSize; i++)
	{
		if(iData[i] > iActMax)
		{
			iActMax=iData[i];
			iIndex=i;
		}
	}
	return iIndex;
}

int Check_z_data_trDiscrVar(ITI_PartitionVar* pData, ITI_int intSize, ITI_int realSize, FILE* file, ITI_uint k)
{
	ITI_int i;
	ITI_int trc = 0;

	if (!pData)
		return 0;
	for (i = 0; i < intSize; i++)
		if (pData->pre_z.intData[i] != pData->z.intData[i]) {
			fprintf(file, "Event Iteration step %u: z_int[%d] = %i\tpre_z_int = %i\n", k, i, pData->z.intData[i], pData->pre_z.intData[i]);
			trc = 1;
		}
	for (i = 0; i < realSize; i++)
		if (pData->pre_z.realData[i] != pData->z.realData[i]) {
#ifdef ITI_COMP_SIM
			fprintf(file, "Event Iteration step %u: z_real[%d] = %.12f\tpre_z_real = %.12f\n", k, i, *(pData->z.realData[i]), *(pData->pre_z.realData[i]));
#else
			fprintf(file, "Event Iteration step %u: z_real[%d] = %.12f\tpre_z_real = %.12f\n", k, i, pData->z.realData[i], pData->pre_z.realData[i]);
#endif
			trc = 1;
		}
	return trc;
}

int Check_Update_oldsign_zf_trEvent(ITI_real* zf, ITI_real* old_sign_zf, ITI_int iSize, FILE* file, ITI_uint k)
{
	ITI_int i;
	ITI_int iRet = SOLVER_SUCCESS_END;
	for(i=0; i<iSize; i++)
	{
		if(old_sign_zf[i] != sign(zf[i]))
		{
			fprintf(file, "Event Iteration step %u: sign_zero(%d) = %g\told_sign_zf = %g\n", k, i, sign(zf[i]), old_sign_zf[i]);
			iRet = SOLVER_SUCCESS_CONTINUE;
		}
		old_sign_zf[i] = sign(zf[i]);
	}
	for(i=0; i<iSize; i++)
	{
		old_sign_zf[i] = sign(zf[i]);
	}
	return iRet;
}

void GetOutputFileName(char *fileNameOut, char *fileNameIn, int iVariation)
{
	if (fileNameIn == NULL) {
		if (iVariation < 0)
			strcpy(fileNameOut, "outputs.txt");
		else
			sprintf(fileNameOut, "outputs%d.txt", iVariation+1);
	} else {
		strncpy(fileNameOut, fileNameIn, FILENAME_MAX-1);
		fileNameOut[FILENAME_MAX-1] = '\0';
		if (iVariation >= 0) {
			char *pbs = strrchr(fileNameOut, '\\');
			char *ps = strrchr(fileNameOut, '/');
			char *pd  = strrchr(fileNameOut, '.');
			int fileNum = iVariation + 1;
			int numDigit = (int)floor(log10((double)fileNum)) + 1;
			size_t len = strlen(fileNameOut);
			if (pd > pbs || pd > ps) {
				char suffix[FILENAME_MAX];
				size_t sufLen;
				strcpy(suffix, pd);
				sufLen = strlen(suffix);
				if (len + sufLen + numDigit >= FILENAME_MAX)
					len = FILENAME_MAX - numDigit - sufLen - 1;
				else
					len -= sufLen;
				sprintf(&fileNameOut[len], "%d%s", fileNum, suffix);
			} else {
				if (len + numDigit >= FILENAME_MAX)
					len = FILENAME_MAX - numDigit - 1;
				sprintf(&fileNameOut[len], "%d", fileNum);
			}
		}
	}
}

#ifdef DSD_LENZE
#define BUFSIZE 4096

void GetITITempFileName(LPSTR lpTempFileName)
{
	DWORD dwBufSize=BUFSIZE;
	char lpPathBuffer[BUFSIZE];

	GetTempPathA(dwBufSize, lpPathBuffer);
	GetTempFileNameA(lpPathBuffer, "ITI", 0, lpTempFileName);
}
#endif

#ifdef ITI_COMP_SIM
void UpdateStates(ITI_xData* dataX, ITI_int size, ITI_WorkSpace ws, ITI_real* x)
{
	ITI_int i;

	for (i = 0; i < size; i++)
	{
		if (dataX[i].kind != VDK_OdeStateDp)
			*ws.px[i] = x[i];

		 
	}
}

void RememberVarData(ITI_PartitionVar pData, ITI_WorkSpace ws)
{
#ifndef ITI_COMP_SIM
	 
	assert (0);
	return;
#endif
	ITI_int i;

	for (i = 0; i < pData.size.iv_real; i++){
		*(ws.vtmp.realData[i]) = *(pData.v.realData[i]);
	}
	memcpy(ws.vtmp.intData, pData.v.intData, pData.size.iv_int * sizeof(ITI_int));
	memcpy(ws.vtmp.strData, pData.v.strData, pData.size.iv_str * sizeof(ITI_char*));
	memcpy(ws.vtmp.strSize, pData.v.strSize, pData.size.iv_str * sizeof(ITI_int));
}

void RestoreVarData(ITI_PartitionVar pData, ITI_WorkSpace ws)
{
#ifndef ITI_COMP_SIM
	 
	assert (0);
	return;
#endif
	ITI_int i;

	for (i = 0; i < pData.size.iv_real; i++){
		*(pData.v.realData[i]) = *(ws.vtmp.realData[i]);
	}
	memcpy(pData.v.intData, ws.vtmp.intData, pData.size.iv_int * sizeof(ITI_int));
	memcpy(pData.v.strData, ws.vtmp.strData, pData.size.iv_str * sizeof(ITI_char*));
	memcpy(pData.v.strSize, ws.vtmp.strSize, pData.size.iv_str * sizeof(ITI_int));
}

void InitSynchStrsData(ITI_SynchStrsDataItem* strData, ITI_int size, ITI_uint forParameters)
{
	strData->modelStrs = (ITI_char***)calloc(size, sizeof(ITI_char**));
	strData->simxStrs = (ITI_void**)calloc(size, sizeof(ITI_void*));
	if (forParameters)
		strData->simxStrVars = (ITI_void**)calloc(size, sizeof(ITI_void*));
	strData->simxStrSizes = (ITI_int*)calloc(size, sizeof(ITI_int));
	strData->size = size;
	strData->indices = (ITI_uint*)calloc(size, sizeof(ITI_uint));
}

void FreeSynchStrsData(ITI_SynchStrsDataItem* strData)
{
	if (!strData)
		return;
	free(strData->modelStrs); strData->modelStrs = NULL;
	free(strData->simxStrs); strData->simxStrs = NULL;
	free(strData->simxStrVars); strData->simxStrVars = NULL;
	free(strData->simxStrSizes); strData->simxStrSizes = NULL;
	free(strData->indices); strData->indices = NULL;
}

#endif

void SetContainerData(void* pData, void* pContainer)
{
	ITI_SolverData* sd = (ITI_SolverData*)pData;
	sd->partition[0].curr->sInfo.pContainer = pContainer;
}

void* GetContainerData(void* pData)
{
	return ((ITI_SolverData*)pData)->partition[0].curr->sInfo.pContainer;
}

