/**
 * ITI_Cvode_model_if.c
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

#include "ITI_Cvode_base.h"
#include "ITI_Cvode_model_if.h"
#include "ITI_Functions.h"
#include "ITI_Tracing.h"

#include "sundials/include/nvector/nvector_serial.h"
#include "sundials/src/cvode/cvode_impl.h"
#include "sundials/src/cvode/cvode_dense_impl.h"
#include "sundials/include/sundials/sundials_math.h"

void ErrHandler(int error_code, const char *module, const char *function,char *msg, void *eh_data)
{
	ITI_CVodeContainer* cvcontainer = (ITI_CVodeContainer*)eh_data;
	ITI_SolverData* cvd = cvcontainer->cvd;
	ITI_Partition* pPart = cvcontainer->pPart;
	ITI_char longMsg[500];

	sprintf(longMsg, "   Module: %s\n   Function: %s\n   %s", module, function, msg);

	if (error_code == CV_WARNING)
	{
		traceWarning(longMsg, &pPart->transient->sInfo);
	}
	else
	{
		traceErrorWarning(longMsg, &pPart->transient->sInfo);
		HandleWarnings(&pPart->transient->sInfo);
	}
}

#ifdef ITI_COMP_SIM
#define ITI_realVar *cvd->pData[0].v.realData
#define ITI_PRINT_MAX \
sprintf(msg,"t=%.16g: the value %-.17g exceeds the maximum (%-.17g) of the state %s.\n", t, cvd->pData[0].x[cvd->model.stateAttributes[i].stateIdx], ITI_realVar[cvd->model.stateAttributes[i].maxIdx] + cvc->absTol, cvd->model.dataX[cvd->model.stateAttributes[i].stateIdx].name);\

#define ITI_PRINT_MAXNOTREACHED \
sprintf(msg,"t=%.16g: the value %-.17g exceeds the maximum (%-.17g) of the state %s.\n", t, cvd->pData[0].x[cvd->model.stateAttributes[i].stateIdx], ITI_realVar[cvd->model.stateAttributes[i].maxIdx], cvd->model.dataX[cvd->model.stateAttributes[i].stateIdx].name);\

#define ITI_PRINT_MIN \
sprintf(msg,"t=%.16g: the value %-.17g is below the minimum (%-.17g) of the state %s.\n", t, cvd->pData[0].x[cvd->model.stateAttributes[i].stateIdx], ITI_realVar[cvd->model.stateAttributes[i].minIdx] - cvc->absTol, cvd->model.dataX[cvd->model.stateAttributes[i].stateIdx].name);\

#define ITI_PRINT_MINNOTREACHED \
sprintf(msg,"t=%.16g: the value %-.17g is below the minimum (%-.17g) of the state %s.\n", t, cvd->pData[0].x[cvd->model.stateAttributes[i].stateIdx], ITI_realVar[cvd->model.stateAttributes[i].minIdx], cvd->model.dataX[cvd->model.stateAttributes[i].stateIdx].name);\

#define TRACEFLAGS	(&cvd->modelData.traceFlags)

#else
#define ITI_realVar cvd->pData[0].v.realData
#define ITI_PRINT_MAX sprintf(msg, "t=%.12g: the value %-.12g exceeds the maximum (%-.12g) of state(%d).\n", t, cvd->pData[0].x[cvd->model.stateAttributes[i].stateIdx], ITI_realVar[cvd->model.stateAttributes[i].maxIdx] + cvd->ss.absTol, cvd->model.stateAttributes[i].stateIdx);
#define ITI_PRINT_MAXNOTREACHED sprintf(msg, "t=%.12g: the value %-.12g exceeds the maximum (%.-.12g) of state(%d).\n", t, cvd->pData[0].x[cvd->model.stateAttributes[i].stateIdx], ITI_realVar[cvd->model.stateAttributes[i].maxIdx], cvd->model.stateAttributes[i].stateIdx);
#define ITI_PRINT_MIN sprintf(msg, "t=%.12g: the value %-.12g is below the minimum (%-.12g) of state(%d).\n", t, cvd->pData[0].x[cvd->model.stateAttributes[i].stateIdx], ITI_realVar[cvd->model.stateAttributes[i].minIdx] - cvd->ss.absTol, cvd->model.stateAttributes[i].stateIdx);
#define ITI_PRINT_MINNOTREACHED sprintf(msg, "t=%.12g: the value %-.12g is below the minimum (%-.12g) of state(%d).\n", t, cvd->pData[0].x[cvd->model.stateAttributes[i].stateIdx], ITI_realVar[cvd->model.stateAttributes[i].minIdx], cvd->model.stateAttributes[i].stateIdx);

#endif


#define ITI_TRACE_MAX_EXCEEDED \
ITI_char msg[255];\
ITI_PRINT_MAX \
traceWarning(msg, &cvd->pData[0].sInfo);

#define ITI_TRACE_MAXNOTREACHED_EXCEEDED \
ITI_char msg[255];\
ITI_PRINT_MAXNOTREACHED \
traceWarning(msg, &cvd->pData[0].sInfo);

#define ITI_TRACE_MIN_EXCEEDED \
ITI_char msg[255];\
ITI_PRINT_MIN \
traceWarning(msg, &cvd->pData[0].sInfo);

#define ITI_TRACE_MINNOTREACHED_EXCEEDED \
ITI_char msg[255];\
ITI_PRINT_MINNOTREACHED \
traceWarning(msg, &cvd->pData[0].sInfo);

int CalcRHS(realtype t, N_Vector x, N_Vector xdot, void* data)
{
	ITI_int i = 0;
	ITI_SolverState iRet = SOLVER_SUCCESS_END;
	ITI_CVodeContainer* cvcontainer= (ITI_CVodeContainer*)data;
	ITI_SolverData* cvd = cvcontainer->cvd;
	ITI_Partition* pPart = cvcontainer->pPart;
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)cvd->sc[pPart->pid];
	ITI_PartFunctions* pPartFunctions = &cvd->model.partFunctions[pPart->pid];

	pPart->curr->x = NV_DATA_S(x);
	pPart->curr->xdot = NV_DATA_S(xdot);
	pPart->curr->t = t;
	pPart->curr->sInfo.dt = t - pPart->curr->tLastStep;
	if (cvd->ss.parJac == 0 || strcmp(pPart->curr->sInfo.strAnalysisTypeDetail, "jacobian") != 0)
		cvd->stat[pPart->pid].iRhsCalls++;

	pPart->curr->xdot[0] = 0.0;

#ifdef _CALC_MESSAGES
	fprintf(stdout, "\nRHS:\t%.32f", t);
#endif

	if (!cvd->ss.ignoreMinMax) {
		for (i = 0; i < pPart->curr->smm->nMin; i++) {
			if (pPart->curr->x[pPart->curr->smm->minInd[i]] < pPart->curr->smm->minVal[i]) {
				ITI_char msg[255];
#ifdef ITI_COMP_SIM
				sprintf(msg, "t=%.16g: The value %-.17g is below the minimum (%-.17g) of the state %s.\n", t, pPart->curr->x[pPart->curr->smm->minInd[i]], pPart->curr->smm->minVal[i], pPartFunctions->dataX[pPart->curr->smm->minInd[i]].name);
#else
				sprintf(msg, "t=%.16g: The value %-.17g is below the minimum (%-.17g) of the state %s.\n", t, pPart->curr->x[pPart->curr->smm->minInd[i]], pPart->curr->smm->minVal[i], pPart->curr->stateNames[pPart->curr->smm->minInd[i]]);
#endif
				traceWarning(msg, &pPart->transient->sInfo);

#ifdef TRACE_STATEBOUNDS
				TRACE_STATEBOUNDS
					ITI_char str[255];
#ifdef ITI_COMP_SIM
					sprintf(str, "The value of the state %s is below the minimum.\n", pPartFunctions->dataX[pPart->curr->smm->minInd[i]].name);
#else
					sprintf(str, "The value of the state %s is below the minimum.\n", pPart->curr->stateNames[pPart->curr->smm->minInd[i]]);
#endif
					pPart->transient->sInfo.trace(0, Debug, str, msg, (void*)&pPart->transient->sInfo);
				END_TRACE
#endif

				return (int)SOLVER_SUCCESS_CONTINUE;
			}
		}
		for (i = 0; i < pPart->curr->smm->nMax; i++) {
			if (pPart->curr->x[pPart->curr->smm->maxInd[i]] > pPart->curr->smm->maxVal[i]) {
				ITI_char msg[255];
#ifdef ITI_COMP_SIM
				sprintf(msg, "t=%.16g: The value %-.17g exceeds the maximum (%-.17g) of the state %s.\n", t, pPart->curr->x[pPart->curr->smm->maxInd[i]], pPart->curr->smm->maxVal[i], pPartFunctions->dataX[pPart->curr->smm->maxInd[i]].name);
#else
				sprintf(msg, "t=%.16g: The value %-.17g exceeds the maximum (%-.17g) of the state %s.\n", t, pPart->curr->x[pPart->curr->smm->maxInd[i]], pPart->curr->smm->maxVal[i], pPart->curr->stateNames[pPart->curr->smm->maxInd[i]]);
#endif
				traceWarning(msg, &pPart->transient->sInfo);

#ifdef TRACE_STATEBOUNDS
				TRACE_STATEBOUNDS
					ITI_char str[255];
#ifdef ITI_COMP_SIM
					sprintf(str, "The value of the state %s exceeds the maximum.\n", pPartFunctions->dataX[pPart->curr->smm->maxInd[i]].name);
#else
					sprintf(str, "The value of the state %s exceeds the maximum.\n", pPart->curr->stateNames[pPart->curr->smm->maxInd[i]]);
#endif
					pPart->transient->sInfo.trace(0, Debug, str, msg, (void*)&pPart->transient->sInfo);
				END_TRACE
#endif

				return (int)SOLVER_SUCCESS_CONTINUE;
			}
		}
	}

	if (cvc->contextBase.OnSetInputs)
	{
		if(cvc->contextBase.OnSetInputs(cvd, pPart->curr->t, &pPart->curr->u) > 0)
		{
			return (int)SOLVER_SUCCESS_CONTINUE;
		}
	}

	if (strcmp(pPart->curr->sInfo.strAnalysisTypeDetail, "jacobian") != 0) {
#ifdef ITI_COMP_SIM
		CopyVarsCS(pPart->curr->bx, pPart->curr->bx_tmp, pPart->curr->size.bxind_cdfirst, pPart->curr->size.ibx);
#else
		CopyVars(pPart->curr->bx, pPart->curr->bx_tmp, pPart->curr->size.bxind_cdfirst, pPart->curr->size.ibx);
#endif
	}

	iRet = ExceptWrapper2((ModelFunc2)pPartFunctions->CalcDerivatives, pPart, &cvd->modelData);
	if (iRet > SOLVER_SUCCESS_END && pPart->curr->sInfo.MEcalled)  
		iRet = SOLVER_ERROR;

	cvd->model.ReleaseAllMemory(&(cvd->modelData.currMem));

	if((iRet > SOLVER_SUCCESS_END) && pPart->curr->sInfo.bAssertActive){
		if(CheckForZeroCrossing(pPart->curr)){
			pPart->curr->sInfo.bAssertActive = 0;
			iRet = ExceptWrapper2((ModelFunc2)pPartFunctions->CalcDerivatives, pPart, &cvd->modelData);
			cvd->model.ReleaseAllMemory(&(cvd->modelData.currMem));
			pPart->curr->sInfo.bAssertActive = pPart->curr->sInfo.bAssertOn;
		}
	}

#ifdef _SAVE_STATES
#ifdef _TDEBUG
	if(t>=_TDEBUG)
	{
		fprintf(cvc->sStates, "RHS\n");
		Write2Stream(cvc->sStates, &pPart->curr->t, NV_DATA_S(x), NV_DATA_S(xdot), 1, pPart->curr->size.ix, pPart->curr->size.ix, 32, 32, 32);
		fflush(cvc->sStates);
	}
#endif
#endif

#ifdef _SAVE_VARS_RHS
	{
		int i;
		FILE* vars = fopen("VarsRHS.txt", "w+");

		for(i = 0; i < pPart->curr->size.iv_real; i++)
		{
			fprintf(vars, "%f\n", *(pPart->curr->v.realData[i]));
		}
		fclose(vars);
	}

#endif
	return (int)iRet;
}

#undef ITI_realVar
#undef ITI_PRINT_MAX
#undef ITI_PRINT_MIN
#undef ITI_TRACE_MAX_EXCEEDED
#undef ITI_TRACE_MIN_EXCEEDED

int CalcZeros(realtype t, N_Vector x, realtype *gout, void *data, int type)
{
	ITI_CVodeContainer* cvcontainer = (ITI_CVodeContainer*)data;
	ITI_SolverData* cvd = cvcontainer->cvd;
	ITI_Partition* pPart = cvcontainer->pPart;
	ITI_PartFunctions* pPartFunctions = &cvd->model.partFunctions[pPart->pid];
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)cvd->sc[pPart->pid];
	ITI_SolverState iRet = SOLVER_SUCCESS_END;

	if (type == 0)
	{
		ITI_int i;
		pPart->curr->x = NV_DATA_S(x);
		 
		pPart->curr->xdot = pPart->curr->xdot_tmp;

		pPart->curr->t = t;
		pPart->curr->sInfo.dt = pPart->curr->tLastStep - t;

		cvd->stat[pPart->pid].iRhsCalls++;

		 
		Update_pre_zf(pPart->curr->pre_zf, pPart->curr->zf, pPart->curr->size.izf);

#ifdef _CALC_MESSAGES
		fprintf(stdout, "\nRoots:\t%.32f", t);
#endif

		if (cvc->contextBase.OnSetInputs)
		{
			if(cvc->contextBase.OnSetInputs(cvd, pPart->curr->t, &pPart->curr->u) > 0)
			{
				return (int)SOLVER_SUCCESS_CONTINUE;
			}
		}

		iRet = ExceptWrapper2((ModelFunc2)pPartFunctions->CalcDerivatives, pPart, &cvd->modelData);
		if (iRet > SOLVER_SUCCESS_END && pPart->curr->sInfo.MEcalled)  
			iRet = SOLVER_ERROR;

#ifdef TRACE_STATES
		TRACE_STATES
		traceStates(pPart->pid, pPart->curr, &cvd->modelData, IDS_CVODE_ZERO);
		END_TRACE
#endif
#ifdef TRACE_DER
		TRACE_DER
		traceDer(pPart->pid, pPart->curr, &cvd->modelData, IDS_CVODE_ZERO);
		END_TRACE
#endif

		cvd->model.ReleaseAllMemory(&(cvd->modelData.currMem));

		if((iRet > SOLVER_SUCCESS_END) && pPart->curr->sInfo.bAssertActive){
			if(CheckForZeroCrossing(pPart->curr)){
				pPart->curr->sInfo.bAssertActive = 0;
				iRet = ExceptWrapper2((ModelFunc2)pPartFunctions->CalcDerivatives, pPart, &cvd->modelData);
				cvd->model.ReleaseAllMemory(&(cvd->modelData.currMem));
				pPart->curr->sInfo.bAssertActive = pPart->curr->sInfo.bAssertOn;
			}
		}

	#ifdef _SAVE_STATES
	#ifdef _TDEBUG
		if(t>=_TDEBUG)
		{
			fprintf(cvc->sStates, "Roots\n");
			Write2Stream(cvc->sStates, &t, pPart->curr->x, pPart->curr->xdot, 1, pPart->curr->size.ix, pPart->curr->size.ix, 32, 32, 32);
			fflush(cvc->sStates);
		}
	#endif
	#endif
		


















			for (i = 0; i < pPart->curr->size.izf; i++)
				gout[i] = pPart->curr->zf[i];

		cvd->stat[pPart->pid].iRfcalls++;
	}
	else if (type == 1)
	{
#ifdef ITI_COMP_SIM
		CopyVarsCS(pPart->curr->bx, pPart->curr->bx_tmp, pPart->curr->size.bxind_cdfirst, pPart->curr->size.ibx);
#else
		CopyVars(pPart->curr->bx, pPart->curr->bx_tmp, pPart->curr->size.bxind_cdfirst, pPart->curr->size.ibx);
#endif
	}
	else
	{
#ifdef ITI_COMP_SIM
		CopyVarsCS(pPart->curr->bx_tmp, pPart->curr->bx, pPart->curr->size.bxind_cdfirst, pPart->curr->size.ibx);
#else
		CopyVars(pPart->curr->bx_tmp, pPart->curr->bx, pPart->curr->size.bxind_cdfirst, pPart->curr->size.ibx);
#endif
	}
	return (int)iRet;
}

void TraceFunction(char *msg, char *msl, void *tf_data)
{
	ITI_CVodeContainer* cvcontainer = (ITI_CVodeContainer*)tf_data;
	ITI_SolverData* cvd = cvcontainer->cvd;
	ITI_Partition* pPart = cvcontainer->pPart;

	int traceOn = 1;
	if (cvd->modelData.traceData.pTraceOn)
		traceOn = *(cvd->modelData.traceData.pTraceOn);
	pPart->transient->sInfo.trace(0, Debug, msg, msl, (void *)&pPart->transient->sInfo);
}
