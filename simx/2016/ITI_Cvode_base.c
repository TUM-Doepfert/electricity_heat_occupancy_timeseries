/**
 * ITI_Cvode_base.c
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#ifdef ITI_COMP_SIM
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#include "Windows.h"
#endif

#include "ITI_crt.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <stdarg.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#include "ITI_Cvode_base.h"
#include "ITI_AllocClockInference.h"
#include "ITI_ClockEval.h"
#include "ITI_PartitionInterface.h"
#include "ITI_PartitionEval.h"
#include "ITI_PartitionInit.h"

#ifdef ITI_COMP_SIM
#include "ITI_NonLinSolver.h"
#include "ITI_Interface_Types.h"
#else
#include "ITI_NonLinSolver.h"
#endif

#include "ITI_SolverHelpers.h"

#include "ITI_Tracing.h"

#include "sundials/include/nvector/nvector_serial.h"
#include "sundials/src/cvode/cvode_impl.h"
#include "sundials/src/cvode/cvode_dense_impl.h"
#include "sundials/include/sundials/sundials_math.h"

#include "sundials/include/sundials/sundials_serialization.h"
#include "sundials/include/cvode/cvode_serialization.h"
#include "ITI_Cvode_sparse.h"

 
 
 

#ifndef ITI_COMP_SIM
#include "ITI_ModelInclude.h"
#endif

static ITI_SolverState handleValidTimeStep(size_t pid, void* pData);
static ITI_SolverState handleTimeEventEfficiently(size_t pid, void* pData);
static ITI_SolverState reinitCVode(size_t pid, void* pData);
static ITI_SolverState classifyEventNumerically(size_t pid, void* pData);
static ITI_SolverState calcNextHitTime(size_t pid, void* pData, ITI_real tCurr);
static ITI_SolverState checkInvalidateDerivatives(size_t pid, void* pData, const N_Vector nv1,  const N_Vector nv2);

#ifdef ITI_COMP_SIM
#define TRACEFLAGS	(&cvd->modelData.traceFlags)
#endif

void* CreateCVODE(size_t pid, ITI_SolverData* cvd, ITI_PartitionSolverMethod solverMethod) {
	ITI_Partition* pPart = &cvd->partition[pid];
	ITI_CVodeContext* cvc=(ITI_CVodeContext*)calloc(1, sizeof(ITI_CVodeContext));
	ITI_int size_ix;
	ITI_int i;

	cvc->cvodeMem = NULL;

	cvc->contextBase.CreateSolver = CreateCVODE;
	cvc->contextBase.InitializePrepareSolver = InitializePrepareCVODE;
	cvc->contextBase.InitializeFinishSolver = InitializeFinishCVODE;
	cvc->contextBase.PrepareTimeEventHandlingSolver = PrepareTimeEventHandlingCVODE;
	cvc->contextBase.OnPrepareSaveOutputs = NULL;
	cvc->contextBase.OnSaveOutputsSolver = NULL;
	cvc->contextBase.OnFinishSaveOutputs = NULL;
	cvc->contextBase.OnBeforeEventStepSolver = NULL;
	cvc->contextBase.OnValidEventStepSolver = NULL;
	cvc->contextBase.CalcOneStepSolver = CalcOneStepCVODE;
	cvc->contextBase.FreeSolver = FreeCVode;
	cvc->contextBase.bFinishSaveOutputsNecessary = ITI_false;
	cvc->contextBase.bPerformEventIterationInPartitionFinish = ITI_true;

	 
	cvc->contextBase.solverMethod = solverMethod;

	cvc->pContainer = NULL;
	cvc->contextBase.OnSetInputs = NULL;

	cvc->OnCheckStop = NULL;
	cvc->OnValidTimeStep = NULL;
	cvc->OnCheckExternalEvent = NULL;

	size_ix = max(1, pPart->curr->size.ix);
	



	cvc->x = N_VNew_Serial(size_ix);
	pPart->curr->x = NV_DATA_S(cvc->x);

	cvc->pxData = N_VGetArrayPointer(cvc->x);

	cvc->xdot = N_VNew_Serial(size_ix);
	pPart->curr->xdot = NV_DATA_S(cvc->xdot);

	cvc->absTolVec = N_VNew_Serial(size_ix);

	cvc->xInter = N_VNew_Serial(size_ix);

	cvc->x_tE = N_VNew_Serial(size_ix);
	cvc->x_tEE = N_VNew_Serial(size_ix);
	cvc->x_tE1 = N_VNew_Serial(size_ix);
	cvc->xdot_tE = N_VNew_Serial(size_ix);
	cvc->xdot_tEE = N_VNew_Serial(size_ix);
	cvc->xdot_tE1 = N_VNew_Serial(size_ix);

	 
	cvc->eweight = N_VNew_Serial(size_ix);
	cvc->ele = N_VNew_Serial(size_ix);
	cvc->elesum = N_VNew_Serial(size_ix);
	N_VConst(ZERO, cvc->elesum);
	cvd->stat[pid].dblInfluence = NV_DATA_S(cvc->elesum);

	 
	cvc->contextBase.isvMax = pPart->curr->size.isv + 1;	 

	cvc->contextBase.timeEventMax = (ITI_bui*)calloc(cvc->contextBase.isvMax, sizeof(ITI_bui));
	cvc->contextBase.timeEventCounter = (ITI_bui*)calloc(cvc->contextBase.isvMax, sizeof(ITI_bui));

	for (i = 0; i < pPart->curr->size.isv; i++)
	{
		ITI_bui_reset(&cvc->contextBase.timeEventMax[i]);
		ITI_bui_reset(&cvc->contextBase.timeEventCounter[i]);
	}

	 
	cvc->pSortJac = (ITI_SortJac*)0;

	cvc->contextBase.lastCalcWasAnimation = ITI_false;

#ifdef _OPENMP
	cvc->parDat = NULL;
	cvc->maxThreads = 0;
#endif

	return cvc;
}

ITI_SolverState InitializePrepareCVODE(size_t pid, ITI_SolverData* sd) {
	size_t i;
	ITI_Partition *pPart = &sd->partition[pid];

	ITI_CVodeContext* cvc = (ITI_CVodeContext*)sd->sc[pid];
	size_t size_ix = max(1, pPart->curr->size.ix);

	realtype *absTolData = NV_DATA_S(cvc->absTolVec);

	if ((pid == 0) && sd->ss.bStopAtStop) {
		cvc->contextBase.isvMax = pPart->curr->size.isv + 1;	 
	}
	else {
		cvc->contextBase.isvMax = pPart->curr->size.isv;
	}

	cvc->contextBase.lastCalcWasAnimation = ITI_false;
	cvc->contextBase.bDPHappenedInEventiteration = ITI_false;

	cvc->contextBase.t = sd->ss.tStart;

	N_VSetArrayPointer(cvc->pxData, cvc->x);

	pPart->curr->xdot = NV_DATA_S(cvc->xdot);
	pPart->curr->xdot_tmp = NV_DATA_S(cvc->xdot);
#ifdef ITI_COMP_SIM
	pPart->curr->ws.xdot_tmp = NV_DATA_S(cvc->xdot);
#endif
	pPart->curr->x = NV_DATA_S(cvc->x);

	for (i = 0; i < size_ix; i++) {
		pPart->curr->xdot[i] = 0.0;
		pPart->curr->x[i] = 0.0;
	}

	 
	if (!cvc->contextBase.bFinishSaveOutputsNecessary) {
		cvc->contextBase.bFinishSaveOutputsNecessary = ITI_true;
		if (cvc->contextBase.OnPrepareSaveOutputs)
			cvc->contextBase.OnPrepareSaveOutputs(pid, sd);
	}
	return SOLVER_SUCCESS_CONTINUE;
}

ITI_SolverState InitializeFinishCVODE(size_t pid, ITI_SolverData* sd) {
	ITI_SolverData* cvd = sd;
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)cvd->sc[pid];
	ITI_Partition *pPart = &cvd->partition[pid];
	ITI_PartFunctions* pPartFunctions = &cvd->model.partFunctions[pid];
	ITI_CVodeContainer* cvcontainer;
	realtype *absTolData = NV_DATA_S(cvc->absTolVec);
	ITI_int i;

	CVodeMem cvMem;
	int cvodeTraceFlags = 0;

	ITI_int size_ix = max(1, pPart->curr->size.ix);

	cvc->contextBase.action = SOLVER_INITIALIZE_SOLVER;

	cvc->contextBase.relTol = sd->ss.relTol;
	cvc->contextBase.absTol = sd->ss.absTol;

	for (i = 0; i < size_ix; i++)
		absTolData[i] = cvc->contextBase.absTol;
	for (i = 0; i < pPart->curr->size.numStateAttr; i++) {
		if (pPartFunctions->stateAttributes[i].absTolIdx != -1)
#ifdef ITI_COMP_SIM
			absTolData[pPartFunctions->stateAttributes[i].stateIdx] = *pPart->curr->v.realData[pPartFunctions->stateAttributes[i].absTolIdx];
#else
			absTolData[pPartFunctions->stateAttributes[i].stateIdx] = pPart->curr->v.realData[pPartFunctions->stateAttributes[i].absTolIdx];
#endif
	}

	if (cvc->cvodeMem) {
		free(((CVodeMem)cvc->cvodeMem)->cv_f_data);
		CVodeFree(&cvc->cvodeMem);
	}

	if (cvd->ss.mode == 1)
		cvc->cvodeMem = CVodeCreate(CV_BDF, CV_NEWTON, cvd->ss.maxOrder);
	else
		cvc->cvodeMem = CVodeCreate(CV_ADAMS, CV_FUNCTIONAL, cvd->ss.maxOrder);

	CVodeMalloc(cvc->cvodeMem, CalcRHS, cvd->ss.tStart, cvc->x, CV_SV, cvc->contextBase.relTol, cvc->absTolVec);
	CVodeSetMaxStepNumberBetweenJacobianEvaluations(cvc->cvodeMem, cvd->ss.maxStepNumberBetweenJacobianEvaluations);

#ifndef _OPENMP
	if (cvd->ss.parJac) {
		pPart->transient->sInfo.trace(0, 1, "CVODE Warning", "The Jacobian will not be computed in parallel because OpenMP is not available.", (void*)&pPart->transient->sInfo);
		cvd->ss.parJac = ITI_false;
	}
#endif

#ifdef _OPENMP
	if (cvd->ss.parJac && !cvc->parDat) {
		cvc->maxThreads = omp_get_max_threads();
		if (cvc->maxThreads == 1) {
			pPart->transient->sInfo.trace(0, 1, "CVODE Warning", "The Jacobian will not be computed in parallel because only 1 thread is available.", (void*)&pPart->transient->sInfo);
			cvd->ss.parJac = ITI_false;
		}
		else if (pPart->curr->size.ix == 1) {
			pPart->transient->sInfo.trace(0, 1, "CVODE Warning", "The Jacobian will not be computed in parallel because there is only 1 ODE state.", (void*)&pPart->transient->sInfo);
			cvd->ss.parJac = ITI_false;
		}
		else if (cvd->ss.threadLimit == 1) {
			pPart->transient->sInfo.trace(0, 1, "CVODE Warning", "The Jacobian will not be computed in parallel because threadLimit == 1.", (void*)&pPart->transient->sInfo);
			cvd->ss.parJac = ITI_false;
		}
		else if (cvd->ss.threadLimit > 1 && cvc->maxThreads > cvd->ss.threadLimit) {
			cvc->maxThreads = cvd->ss.threadLimit;
		}
	}
#endif

	 
	if (cvd->ss.effJac == 0)
	{
		CVDense(cvc->cvodeMem, size_ix);
#ifdef _OPENMP
		if (cvd->ss.parJac)
			CVDenseSetJacFn(cvc->cvodeMem, CalcJacPar, cvc->cvodeMem);
		else
#endif
			CVDenseSetJacFn(cvc->cvodeMem, CalcJac, cvc->cvodeMem);
	}
	else
	{
		ITI_char* pat = (ITI_char*)calloc(size_ix*size_ix, sizeof(ITI_char));

		if (!cvc->pSortJac)
			cvc->pSortJac = (ITI_SortJac*)calloc(1, sizeof(ITI_SortJac));

		if (size_ix == 1)
			pat[0] = 1;
		else
			pPartFunctions->GetJacobianAPattern(pPart, &cvd->modelData, pat);

		 
		if (cvd->ss.effJac == 2)
		{
			 
			CVSparse(cvc->cvodeMem, size_ix);
			BuildEffJac((ITI_SparseData*)((CVodeMem)cvc->cvodeMem)->cv_lmem, cvc->pSortJac, pat, size_ix, &cvd->stat[pid].ngrp);
			SetIntoSparse((ITI_SparseData*)((CVodeMem)cvc->cvodeMem)->cv_lmem);
			SetSparsePrev((ITI_SparseData*)((CVodeMem)cvc->cvodeMem)->cv_lmem);
#ifdef _OPENMP
			if (cvd->ss.parJac && cvd->stat[pid].ngrp == 1) {
				pPart->transient->sInfo.trace(0, 1, "CVODE Warning", "The Jacobian will not be computed in parallel because there is only 1 group within the efficient Jacobian computation.", (void*)&pPart->transient->sInfo);
				cvd->ss.parJac = ITI_false;
			}
			if (cvd->ss.parJac)
				CVSparseSetJacFn(cvc->cvodeMem, ITI_CalcEffJacSparsePar, cvc->cvodeMem);
			else
#endif
				CVSparseSetJacFn(cvc->cvodeMem, ITI_CalcEffJacSparse, cvc->cvodeMem);
		}
		else
		{
			 
			ITI_SparseData* spd;
			AllocSparseData(&spd, size_ix);

			 
			BuildEffJac(spd, cvc->pSortJac, pat, size_ix, &cvd->stat[pid].ngrp);
			CVDense(cvc->cvodeMem, size_ix);
			FreeSparseData(&spd);
#ifdef _OPENMP
			if (cvd->ss.parJac && cvd->stat[pid].ngrp == 1) {
				pPart->transient->sInfo.trace(0, 1, "CVODE Warning", "The Jacobian will not be computed in parallel because there is only 1 group within the efficient Jacobian computation.", (void*)&pPart->transient->sInfo);
				cvd->ss.parJac = ITI_false;
			}
			if (cvd->ss.parJac)
				CVDenseSetJacFn(cvc->cvodeMem, ITI_CalcEffJacPar, cvc->cvodeMem);
			else
#endif
				CVDenseSetJacFn(cvc->cvodeMem, ITI_CalcEffJac, cvc->cvodeMem);
		}

		free(pat);
	}

#ifdef _OPENMP
	if (cvd->ss.parJac && !cvc->parDat) {
		if (cvc->maxThreads > pPart->curr->size.ix)
			cvc->maxThreads = pPart->curr->size.ix;
		if (cvd->ss.effJac && cvc->maxThreads > (int)cvd->stat[pid].ngrp)
			cvc->maxThreads = cvd->stat[pid].ngrp;
		omp_set_num_threads(cvc->maxThreads);

		InitParallelData(cvd);
	}
 
#ifdef ITI_COMP_SIM
	cvd->model.GetRecordSize = (GetRecordSizeFunc)GetProcAddress((HINSTANCE)cvd->model.hModel, "GetRecordSize");
#else
	cvd->model.GetRecordSize = (GetRecordSizeFunc)GetRecordSize;
#endif
#endif

	cvcontainer = (ITI_CVodeContainer*)calloc(1, sizeof(ITI_CVodeContainer));
	cvcontainer->cvd = cvd;
	cvcontainer->pPart = &cvd->partition[pid];
	CVodeSetFdata(cvc->cvodeMem, cvcontainer);

	 
	if (cvd->ss.zeros == 1)
	{
		CVodeRootInit(cvc->cvodeMem, pPart->curr->size.izf, CalcZeros, cvcontainer);
		CVodeSetSignGloData(cvc->cvodeMem, pPart->curr->oszf);
		CVodeSetRootHysteresis(cvc->cvodeMem, cvd->ss.hysteresis);
		CVodeSetRootEpsilon(cvc->cvodeMem, cvd->ss.epsilon);
	}

	pPart->curr->sInfo.isInitial = ITI_false;

	 
	if (cvd->ss.limitdtMin > 0)
		CVodeSetMinStep(cvc->cvodeMem, cvd->ss.dtMin);

	 
	CVodeSetMaxHnilWarns(cvc->cvodeMem, -1);
	CVodeSetMaxStep(cvc->cvodeMem, cvd->ss.dtMax);

	 
	CVodeSetErrHandlerFn(cvc->cvodeMem, ErrHandler, (void*)cvcontainer);

	 
	cvMem = (CVodeMem)cvc->cvodeMem;
#ifdef TRACE_STEPTRUE
	TRACE_STEPTRUE
		cvMem->trStepTrue = TRUE;
		cvodeTraceFlags = 1;
	END_TRACE
#endif
#ifdef TRACE_STEPFALSE
	TRACE_STEPFALSE
		cvMem->trStepFalse = TRUE;
		cvodeTraceFlags = 1;
	END_TRACE
#endif
	if (pPart->transient->size.ix != 0) {
#ifdef TRACE_RES
	TRACE_RES
		cvMem->trRes = TRUE;
		cvodeTraceFlags = 1;
	END_TRACE
#endif
#ifdef TRACE_STATES
	TRACE_STATES
		cvMem->trStates = TRUE;
		cvodeTraceFlags = 1;
	END_TRACE
#endif
#ifdef TRACE_DER
	TRACE_DER
		cvMem->trDer = TRUE;
		cvodeTraceFlags = 1;
	END_TRACE
#endif
#ifdef TRACE_NEWTONUPDATE
	TRACE_NEWTONUPDATE
		cvMem->trNewtonUpdate = TRUE;
		cvodeTraceFlags = 1;
	END_TRACE
#endif
#ifdef TRACE_JAC
	TRACE_JAC
		cvMem->trJac = TRUE;
		cvodeTraceFlags = 1;
	END_TRACE
#endif
#ifdef TRACE_RESTRUE
	TRACE_RESTRUE
		cvMem->trResTrue = TRUE;
		cvodeTraceFlags = 1;
	END_TRACE
#endif
#ifdef TRACE_STATESTRUE
	TRACE_STATESTRUE
		cvMem->trStatesTrue = TRUE;
		cvodeTraceFlags = 1;
	END_TRACE
#endif
#ifdef TRACE_DERTRUE
	TRACE_DERTRUE
		cvMem->trDerTrue = TRUE;
		cvodeTraceFlags = 1;
	END_TRACE
#endif
#ifdef TRACE_RESFALSE
	TRACE_RESFALSE
		cvMem->trResFalse = TRUE;
		cvodeTraceFlags = 1;
	END_TRACE
#endif
#ifdef TRACE_STATESFALSE
	TRACE_STATESFALSE
		cvMem->trStatesFalse = TRUE;
		cvodeTraceFlags = 1;
	END_TRACE
#endif
#ifdef TRACE_DERFALSE
	TRACE_DERFALSE
		cvMem->trDerFalse = TRUE;
		cvodeTraceFlags = 1;
	END_TRACE
#endif
#ifdef TRACE_NEWTONUPDATEFALSE
	TRACE_NEWTONUPDATEFALSE
		cvMem->trNewtonUpdateFalse = TRUE;
		cvodeTraceFlags = 1;
	END_TRACE
#endif
	}
	if (cvodeTraceFlags) {
		int i;
		cvMem->cv_tfun = TraceFunction;
		cvMem->cv_tf_data = cvcontainer;
		cvMem->cv_stateNames = pPart->curr->stateNames; 
		cvMem->cv_dstateNames = pPart->curr->dstateNames;
		cvMem->cv_trwidth = 0;
		cvMem->cv_dtrwidth = 0;
		for (i = 0; i < pPart->curr->size.ix; i++) {
			int len = (int)strlen(pPart->curr->stateNames[i]);
			if (len > cvMem->cv_trwidth)
				cvMem->cv_trwidth = len;
			len = (int)strlen(pPart->curr->dstateNames[i]);
			if (len > cvMem->cv_dtrwidth)
				cvMem->cv_dtrwidth = len;
		}
		pPart->curr->trwidth = cvMem->cv_trwidth;
		pPart->curr->dtrwidth = cvMem->cv_dtrwidth;
	}

	 
	CVodeSetMaxErrTestFails(cvc->cvodeMem, 12);

	 
	ITI_bi_setreal(&cvc->contextBase.i_tHit, cvd->ss.tStart, cvd->ss.dtMin);

	 
	if (cvd->ss.bStopAtStop && ((cvd->ss.tStop - cvd->ss.tStart) >= 0.0))
		ITI_bui_setreal(&cvc->contextBase.ui_dt_Max, cvd->ss.tStop - cvd->ss.tStart, cvd->ss.dtMin);
	else
		ITI_bui_setMax(&cvc->contextBase.ui_dt_Max);

	 
	cvc->contextBase.tHitSample = 1E300;
	cvc->contextBase.tHitClock = 1E300;
	cvc->contextBase.hitIsSample = ITI_true;	 

	calcNextHitTime(0, cvd, cvd->ss.tStart);
	cvc->contextBase.tHit = min(cvc->contextBase.tHitSample, cvc->contextBase.tHitClock);

	CVodeSetStopTime(cvc->cvodeMem, cvc->contextBase.tHit);
	CVodeSetInitStep(cvc->cvodeMem, cvd->ss.dtMin);

	cvc->contextBase.tProt = cvd->ss.tStart;

	if (cvd->ss.saveModeB & (SaveOutputsEquidistantBit | SaveOutputsEquidistantPostEventsBit | SaveOutputsEquidistantPrePostEventsBit | SaveOutputsEquidistantAllEventStepsBit))
	{
		 
		if (cvd->ss.dtProtMin < cvd->ss.dtMin)
		{
			ITI_char charMsg[255];
			ITI_char longMsg[255];
			sprintf(charMsg, "Warning: dtProtMin < dtMin for equidistant saving is not allowed! Using dtProtMin = dtMin = %%.%df.", GetNumberOfDecimalPlaces(cvd->ss.dtMin));
			sprintf(longMsg, charMsg, cvd->ss.dtMin);

			pPart->transient->sInfo.trace(0, 1, "CVODE Warning", longMsg, (void*)&pPart->transient->sInfo);
			cvd->ss.dtProtMin = cvd->ss.dtMin;
		}
		if (AbsRemainder(cvd->ss.dtProtMin, cvd->ss.dtMin) > DBL_EPSILON*cvd->ss.dtProtMin)
		{
			char charMsg[255];
			sprintf(charMsg, "\nWarning: dtProtMin is not a multiple of dtMin!\nThe solver will adjust dtProtMin automatically.\n\n");
			pPart->transient->sInfo.trace(0, 1, "CVODE Warning", charMsg, (void*)&pPart->transient->sInfo);
		}

		ITI_bui_setreal(&cvc->contextBase.ui_dtProt, cvd->ss.dtProtMin, cvd->ss.dtMin);
		ITI_bui_reset(&cvc->contextBase.ui_ProtCounter);
		ITI_bi_setreal(&cvc->contextBase.i_tProtNext, cvd->ss.tStart, cvd->ss.dtMin);
		ITI_bi_plus(&cvc->contextBase.i_tProtNext, &cvc->contextBase.ui_dtProt);
	}

#ifdef _OPENMP
	if (cvd->ss.parJac)
		CopySimData1st(cvd);
#endif

	 
	CVodeSetUserSerialization(cvc->cvodeMem, UserSerialize, UserDeserialize, UserSerializationSize, cvd);

	return SOLVER_SUCCESS_CONTINUE;
}

ITI_SolverState PrepareTimeEventHandlingCVODE(size_t pid, ITI_SolverData* sd) {
	return PrepareTimeEventHandlingPartition(pid, sd);
}

ITI_SolverState CreateSolverInstance(void** pData, const char* modelName, int nParams, double* pValues, TRACE_FUNC* pTraceFunc) {
	return CreateSolverInstanceExtParams(pData, modelName, nParams, pValues, pTraceFunc, NULL);
}

ITI_SolverState CreateSolverInstanceExtParams(void** pData, const char* modelName, int nParams, double* pValues, TRACE_FUNC* pTraceFunc, ITI_parameterData* params) {
	ITI_SolverData* sd = NULL;
	TRACE_FUNC* tracefunc = NULL;

	if (pTraceFunc)
		tracefunc = pTraceFunc;
	else
		tracefunc = (TRACE_FUNC*)&Trace_to_Screen;

	sd = CreateSolverDataExtParams(modelName, nParams, pValues, tracefunc, CreateCVODE, params);
	if (sd == NULL) {
		*pData = NULL;
		return SOLVER_ERROR_CREATE_INSTANCE;
	}
	*pData = sd;
	return SOLVER_SUCCESS_CONTINUE;
}




ITI_SolverState InitializeModel(void* pData){
	InitializePartitionVars(0, (ITI_SolverData*)pData);
	return InitializePartition(0, (ITI_SolverData*)pData);
}

ITI_SolverState InitializeConditionsModelOnly(void* pData) {
	return InitializeConditionsPartition(0, (ITI_SolverData*)pData);
}

ITI_SolverState InitializeConditionsModelFinish(void* pData){
	ITI_SolverState ret = InitializeConditionsPartitionFinish(0, (ITI_SolverData*)pData);
	 
	((ITI_SolverData *)pData)->sc[0]->action = SOLVER_OVERTIME;
	return ret;
}

ITI_SolverState InitializeSolver(void* pData) {
	return InitializeFinishCVODE(0, (ITI_SolverData*)pData);
}

ITI_SolverState TerminateModel(void* pData){
	ITI_SolverData* sd = (ITI_SolverData*)pData;
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)sd->sc[0];
	
	ITI_SolverState iRet = TerminateModelPartitions((ITI_SolverData*)pData);

	 
	if (cvc->contextBase.bFinishSaveOutputsNecessary && cvc->contextBase.OnFinishSaveOutputs) {
		cvc->contextBase.OnFinishSaveOutputs(pData);
	}
	cvc->contextBase.bFinishSaveOutputsNecessary = 0;

	return iRet;
}

void FreeCVode(void* pSolver) {
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)pSolver;
	
	 
	if (cvc->pSortJac) {
		FreeEffJacData(cvc->pSortJac);
		free(cvc->pSortJac); cvc->pSortJac = NULL;
		cvc->pSortJac = (ITI_SortJac*)0;
	}

	 
	N_VSetArrayPointer(cvc->pxData, cvc->x);
	N_VDestroy_Serial(cvc->x);
	N_VDestroy_Serial(cvc->xdot);
	N_VDestroy_Serial(cvc->absTolVec);
	N_VDestroy_Serial(cvc->xInter);
	N_VDestroy_Serial(cvc->ele);
	N_VDestroy_Serial(cvc->elesum);
	N_VDestroy_Serial(cvc->eweight);

	N_VDestroy_Serial(cvc->x_tE);
	N_VDestroy_Serial(cvc->x_tEE);
	N_VDestroy_Serial(cvc->x_tE1);
	N_VDestroy_Serial(cvc->xdot_tE);
	N_VDestroy_Serial(cvc->xdot_tEE);
	N_VDestroy_Serial(cvc->xdot_tE1);

	free(cvc->contextBase.timeEventMax);
	free(cvc->contextBase.timeEventCounter);

#ifdef _OPENMP
	FreeParallelData(pSolver);
#endif

	if (cvc->cvodeMem) {
		free(((CVodeMem)cvc->cvodeMem)->cv_f_data);
		CVodeFree(&cvc->cvodeMem);
	}

	free(cvc);
}

void FreeSolverInstance(void* pData) {
	ITI_SolverData* sd = (ITI_SolverData*)pData;	
	if (sd) {
		FreeSolverData(sd);
	}
}

ITI_SolverState SetSolverSettings(void* pData, ITI_SolverSettings* settings)
{
	ITI_SolverData* cvd = (ITI_SolverData*)pData;

	cvd->ss = *settings;
	cvd->ss.saveModeB = (int)(2<<(cvd->ss.saveMode));
	cvd->ss.consistentInitialConditions = 1;

	return SOLVER_SUCCESS_CONTINUE;
}

ITI_SolverState CalcOneStepCVODE(size_t pid, void* pData, double endTime) {
	return CalcOneStep(pid, pData, 1, endTime);
}

ITI_SolverState CalcOneStep(size_t pid, void* pData, int considerEndTime, double endTime)
{
	ITI_SolverData* cvd = (ITI_SolverData*)pData;
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)cvd->sc[pid];
	ITI_Partition *pPart = &cvd->partition[pid];
	ITI_SolverState iRet = SOLVER_SUCCESS_END;
	ITI_int tStopReached = 0;
	ITI_int leave = 0;
	ITI_real tEnd;
	ITI_long iVal=0;

	if (cvd->ss.bStopAtStop && cvd->ss.tStart == cvd->ss.tStop) {
		cvc->contextBase.state = SOLVER_SUCCESS_END;
		return cvc->contextBase.state;
	}

	cvc->contextBase.state = SOLVER_SUCCESS_CONTINUE;

	 
	pPart->curr->sInfo.tracingAllowed = ITI_false;

	do{
		 
		pPart->curr->sInfo.isEvent = ITI_false;
		pPart->curr->sInfo.isFirstEventStep = ITI_false;
		pPart->curr->sInfo.strAnalysisTypeDetail = "residuals";
		pPart->curr->sInfo.bDPAllowed = ITI_false;
		pPart->curr->sInfo.bSolverNeedsReset = ITI_false;
		cvd->stat[pid].iZero = 0;
		cvc->contextBase.bZeroFunc= ITI_false;
		cvc->contextBase.bTimeEvent = ITI_false;

		ResetWarningStack(&pPart->transient->sInfo);
		 
		if (pPart->curr->size.isv > 0 || pPart->curr->size.ipart)
			cvc->contextBase.tHit = min(cvc->contextBase.tHitSample, cvc->contextBase.tHitClock);
		else
			cvc->contextBase.tHit = 1E300;

		if(considerEndTime)
		{
			if(cvd->ss.eventHandlingMode == 1){
				tEnd = endTime;
			}
			else{
				if(cvc->contextBase.tHit < endTime)
					tEnd = cvc->contextBase.tHit;
				else
					tEnd = endTime;
			}
		}
		else{
			if(cvd->ss.eventHandlingMode == 1){
				if(cvd->ss.bStopAtStop)
					if(cvc->nextTimeEventStops)
						tEnd = cvd->ss.tStop;
					else
						tEnd = 1E300;
				else
					tEnd = 1E300;
			}
			else
				tEnd = cvc->contextBase.tHit;
		}

		 
		CVodeSetStopTime(cvc->cvodeMem, tEnd);
		cvc->flag = CVode(cvc->cvodeMem, tEnd, cvc->x, &cvc->contextBase.t, CV_ONE_STEP_TSTOP);

		CVodeGetNumErrTestFails(cvc->cvodeMem, &iVal);
		cvd->stat[pid].iErrTestFailStep = iVal;
		cvd->stat[pid].iErrTestFails += iVal;

#ifdef _STATES_TRACING
		TraceStates(cvd, simX, 1);
#endif
#ifdef _DERIVATIVES_TRACING
		TraceDerivatives(cvd, simX, 1);
#endif

		 
		if(cvc->flag<0)
		{
			cvc->contextBase.state = SOLVER_ERROR;
			return cvc->contextBase.state;
		}
		ResetWarningStack(&pPart->transient->sInfo);

		if(cvc->flag == CV_ROOT_RETURN){
			cvc->contextBase.bZeroFunc = ITI_true;
		}

		 
		if(cvd->ss.zeros == 0){
			if(CheckForZeroCrossing(pPart->curr)){
				cvc->contextBase.bZeroFunc = ITI_true;
			}
		}

#ifdef __ROOT_MESSAGE_FILE
		if(cvc->bZeroFunc){
			FILE* roots = fopen("roots.txt", "a");
			int *root = (int*)calloc(pPart->curr->size.izf, sizeof(int));
			fprintf(roots, "\nCVode found root at:\t%.15f\n", cvc->contextBase.t);
			CVodeGetRootInfo(cvc->cvodeMem, root);
			for (i = 0; i < pPart->curr->size.izf; i++){
				if(root[i]){
					fprintf(roots, "zf[%lu] = %.36f\tpre_zf = %.36f\n", (unsigned long)i, pPart->curr->zf[i], pPart->curr->pre_zf[i]);
				}
			}
			fclose(roots);
			 
			CVodeGetRootCounter(cvc->cvodeMem, root);
			WriteRootCounter("rootCounter.txt", root, pPart->curr->size.izf);
			free(root);
		}
#endif

		if(cvd->ss.eventHandlingMode == 1){
			if(handleTimeEventEfficiently(pid, pData) < SOLVER_SUCCESS_END){
				return cvc->contextBase.state;
			}
		}
		else{
			 
			pPart->curr->tLastStep = pPart->curr->t = cvc->contextBase.t;
			CVodeGetLastStep(cvc->cvodeMem, &pPart->transient->sInfo.dt);

			if(handleValidTimeStep(pid, pData) < SOLVER_SUCCESS_END){
				return cvc->contextBase.state;
			}

			leave = 0;
			cvc->contextBase.action = SOLVER_CHECK_EVENT;

			 
			if(cvc->contextBase.t == cvc->contextBase.tHitSample) {
				CheckSampleActive(pid, cvd);
				cvc->contextBase.hitIsSample = ITI_true;

				 
				 
				if ((pid == 0) && cvd->ss.bStopAtStop) {
					ITI_bui_minus(&cvc->contextBase.timeEventCounter[pPart->curr->size.isv], &cvc->contextBase.ui_dtHit);
					if (ITI_bui_is_zero(&cvc->contextBase.timeEventCounter[pPart->curr->size.isv]))
					{
						ITI_bui_reset(&cvc->contextBase.ui_dtHit);
						cvc->contextBase.bTerminateRequired = ITI_true;
						cvc->contextBase.bTimeEvent = ITI_true;
					}
				}
				 
				calcNextHitTime(pid, pData, cvc->contextBase.t);

				


				cvc->contextBase.hitIsSample = ITI_true;
			}
			if(cvc->contextBase.t == cvc->contextBase.tHitClock){
				cvc->contextBase.bTimeEvent = ITI_true;
				cvc->contextBase.hitIsClock = ITI_true;
			}
		}


		if(cvc->OnCheckExternalEvent)
		{
			iRet = cvc->OnCheckExternalEvent(pData);

			if(iRet > SOLVER_SUCCESS_END)
				pPart->curr->sInfo.bEventTriggered = ITI_true;
		}

		if (cvc->contextBase.bZeroFunc || pPart->curr->sInfo.bDPRequired || cvc->contextBase.bTimeEvent || pPart->curr->sInfo.bEventTriggered){
#ifdef TRACE_DUMMYPIVOTING
			TRACE_DUMMYPIVOTING
			if (pPart->curr->sInfo.bDPRequired)
				traceDummyPivoting(pPart->curr, &cvd->modelData);
			END_TRACE
#endif
#ifdef TRACE_ZEROFCT
			TRACE_ZEROFCT
			if (cvc->contextBase.bZeroFunc) {
				ITI_int *root = (ITI_int *)calloc(pPart->curr->size.izf, sizeof(ITI_int));
				CVodeGetRootInfo(cvc->cvodeMem, root);
				traceZeroFct(pid, pPart->curr, &cvd->modelData, &cvd->model, root);
				free(root);
			}
			END_TRACE
#endif
#ifdef _EVENT_STEP
			if (((cvc->contextBase.t >= _ROOT_PROT_BEGIN[0])&&(cvc->contextBase.t <= _ROOT_PROT_END[0])) || ((cvc->contextBase.t >= _ROOT_PROT_BEGIN[1])&&(cvc->contextBase.t <= _ROOT_PROT_END[1])) || ((cvc->contextBase.t >= _ROOT_PROT_BEGIN[2])&&(cvc->contextBase.t <= _ROOT_PROT_END[2])))
			{
				if(cvc->bZeroFunc)
				{
					FILE* roots = fopen("roots.txt", "a");
					fprintf(roots, "Root of Zerofunction at t=%.15f\n", cvc->contextBase.t);
					fclose(roots);
				}
				if(pPart->curr->sInfo.bDPRequired)
				{
					FILE* roots = fopen("roots.txt", "a");
					fprintf(roots, "New Dummy Derivative Pivoting at t=%.15f\n", cvc->contextBase.t);
					fclose(roots);
				}
				if(cvc->bTimeEvent)
				{
					FILE* roots = fopen("roots.txt", "a");
					fprintf(roots, "TimeEvent at t=%.15f\n", cvc->contextBase.t);
					fclose(roots);
				}
			}
#endif

			if(cvc->contextBase.bZeroFunc)
				cvd->stat[pid].iZeros++;
			if(cvc->contextBase.bTimeEvent)
				cvd->stat[pid].iTimeEvents++;
			if(pPart->curr->sInfo.bEventTriggered)
				cvd->stat[pid].iOtherEvents++;
			if(pPart->curr->sInfo.bDPRequired)
				cvd->stat[pid].iStateSelections++;

			pPart->curr->x = NV_DATA_S(cvc->x);
			cvc->contextBase.state = EventIterationPartition(pid, cvd);
			reinitCVode(pid, pData);

			if ((cvc->contextBase.hitIsSample) || (cvc->contextBase.hitIsClock)) {
				 
				calcNextHitTime(pid, pData, cvc->contextBase.t);
			}
			cvc->contextBase.hitIsClock = ITI_false;
			cvc->contextBase.bZeroFunc = ITI_false;
			cvc->contextBase.bTimeEvent = ITI_false;

			if(cvc->contextBase.state < SOLVER_SUCCESS_CONTINUE)
				return cvc->contextBase.state;
		}
		cvc->contextBase.action = SOLVER_CHECK_END_TIME;

		 
		if(considerEndTime && (cvc->contextBase.t == endTime))
		{
			if (HandleSaveOutputs(pid, cvd, SaveOutputsAfterDoStepBit, ITI_true) != SOLVER_SUCCESS_END)
			{
				HandleWarnings(&pPart->transient->sInfo);
				cvc->contextBase.state = SOLVER_ERROR;
				return cvc->contextBase.state;
			}
			leave = 1;
			cvc->contextBase.state = SOLVER_SUCCESS_CONTINUE;
			cvc->contextBase.action = SOLVER_OVERTIME;
		}
		if((pid == 0) && cvd->ss.bStopAtStop)
		{
			if (ITI_bui_is_zero(&cvc->contextBase.timeEventCounter[pPart->curr->size.isv]))
			{
				leave = 1;
				cvc->contextBase.state = SOLVER_SUCCESS_END;
				tStopReached = 1;
			}
		}
		if (!tStopReached && (pPart->curr->sInfo.isTerminate))
		{
			leave = 1;
			HandleWarnings(&pPart->transient->sInfo);
			cvc->contextBase.state = SOLVER_TERMINATED;
		}
		else
		{
			cvc->contextBase.action = SOLVER_OVERTIME;
#ifdef _FLUSH
			#ifdef _SAVE_OUTPUTS
			fflush(cvc->outputs);
			#endif
			#ifdef _SAVE_STATES
			fflush(cvc->sStates);
			#endif
#endif
		}
		if(cvc->OnCheckStop)
		{
			 
			if(cvc->OnCheckStop(pData))
			{
				return cvc->contextBase.state;
			}
		}
	}
	while(leave==0);

	if(cvc->contextBase.state >= SOLVER_SUCCESS_END)
	{
#ifdef TRACE_STATES
		TRACE_STATES
		traceStates(pid,pPart->curr, &cvd->modelData, IDS_END_SIM);
		END_TRACE
#endif
#ifdef TRACE_DER
		TRACE_DER
		traceDer(pid, pPart->curr, &cvd->modelData, IDS_END_SIM);
		END_TRACE
#endif

#ifdef _SAVE_STATES
		Write2Stream(cvc->sStates, &simX->t, pPart->curr->x, pPart->curr->xdot, 1, pPart->curr->size.ix, pPart->curr->size.ix, 32, 32, 32);
#endif
#ifdef _SAVE_OUTPUTS
		fclose(cvc->outputs);
#endif
#ifdef _SAVE_STATES
		fclose(cvc->sStates);
#endif

#ifdef __ROOT_MESSAGE_FILE
		{
			int *rootctr = (int*)calloc(pPart->curr->size.izf, sizeof(int));
			CVodeGetRootCounter(cvc->cvodeMem, rootctr);
			WriteRootCounter("rootCounter.txt", rootctr, pPart->curr->size.izf);
			free(rootctr);
		}
#endif
		 
		if((cvd->ss.saveModeB & (SaveOutputsAtleastwithdtProtBit)) && (cvc->contextBase.tProt != cvc->contextBase.t))
			iRet = HandleSaveOutputs(pid, cvd, SaveOutputsAtleastwithdtProtBit, ITI_true);
		else
			iRet = HandleSaveOutputs(pid, cvd, SaveOutputsLastValueBit, ITI_true);

		if (iRet != SOLVER_SUCCESS_END)
		{
			HandleWarnings(&pPart->transient->sInfo);
			cvc->contextBase.state = SOLVER_ERROR;
			return cvc->contextBase.state;
		}
	}
	cvd->model.ReleaseAllMemory(&cvd->modelData.currMem);
	return cvc->contextBase.state;
}

ITI_bool CheckBit(int var, int mask)
{
	return (var & mask) == mask;
}

void UpdateSolverStatistics(void* pData)
{
	size_t pid = 0;
	ITI_SolverData* cvd = (ITI_SolverData*)pData;
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)cvd->sc[pid];
	long iDecomp = 0;
	long iElim = 0;
	long iCodegen = 0;
	int iOrder = 0;

	if(cvc->cvodeMem)
	{
		if(cvc->contextBase.action > SOLVER_INITIALIZE_SOLVER)
		{
			CVodeGetLastOrder(cvc->cvodeMem, &iOrder);
			if(cvd->ss.effJac == 2)
			{
				CVSparseGetNumCodeGen(cvc->cvodeMem, &iCodegen);
				CVSparseGetNumDecomp(cvc->cvodeMem, &iDecomp);
				CVSparseGetNumElim(cvc->cvodeMem, &iElim);
			}
			else
			{
				iCodegen = 0;
				CVDenseGetNumDecomp(cvc->cvodeMem, &iDecomp);
				CVDenseGetNumElim(cvc->cvodeMem, &iElim);
			}
		}
	}

	cvd->stat[pid].iCodegen = (unsigned int)iCodegen;
	cvd->stat[pid].iDecomp = (unsigned int)(iDecomp);
	cvd->stat[pid].iElim = (unsigned int)iElim;
	cvd->stat[pid].iOrder = (unsigned int)iOrder;
}

void BuildSolverStatisticsStringPartition(void* pData, size_t pid, char* strStat)
{
	ITI_SolverData* cvd = (ITI_SolverData*)pData;
	ITI_PartitionVar* curr = cvd->partition[pid].curr;

	char strCodeGen[100] = "";
	char strGroups[100] = "";
	char strRTimeEvents[100] = "";
	char strPart[100] = "";

	UpdateSolverStatistics(pData);

	if (cvd->partition[0].transient->size.ipart > 1)
		sprintf(strPart, "Partition:\t%u\n", (unsigned int)pid);

	if (cvd->ss.effJac == 2)
		sprintf(strCodeGen, "    Code Gen.:\t%u\n", cvd->stat[pid].iCodegen);

	if (cvd->ss.effJac > 0)
		sprintf(strGroups, "    Groups:\t%u\n", cvd->stat[pid].ngrp);

	if (cvd->ss.eventHandlingMode == 1)
		sprintf(strRTimeEvents, " (R: %u)", cvd->stat[pid].iTimeEventsReinit);

	sprintf(strStat, "%s  Steps:\t%u\n    Valid:\t%u\n    Discarded:\t%u\n  Calculations:\n    Residuals:\t%u\n    Jacobian:\t%u\n  Events:\t%u\n    State:\t%u\n    Time:\t%u %s\n    State Sel.:\t%u\n    Other:\t%u\n  Matrix:\n%s    Decomp:\t%u\n    Solve:\t%u\n  States:\t%i\n%s\n",
		strPart,
		cvd->stat[pid].iValidSteps + cvd->stat[pid].iErrTestFails,
		cvd->stat[pid].iValidSteps,
		cvd->stat[pid].iErrTestFails,
		cvd->stat[pid].iRhsCalls,
		cvd->stat[pid].iJac,
		cvd->stat[pid].iZeros + cvd->stat[pid].iTimeEvents + cvd->stat[pid].iStateSelections + cvd->stat[pid].iOtherEvents,
		cvd->stat[pid].iZeros,
		cvd->stat[pid].iTimeEvents,
		strRTimeEvents,
		cvd->stat[pid].iStateSelections,
		cvd->stat[pid].iOtherEvents,
		strCodeGen,
		cvd->stat[pid].iDecomp,
		cvd->stat[pid].iElim,
		curr->size.ix,
		strGroups
	);
}

void BuildSolverStatisticsString(void* pData, char** strStat) {
	ITI_SolverData* cvd = (ITI_SolverData*)pData;
	ITI_int iPart = cvd->partition[0].curr->size.ipart;
	ITI_int pid;
	char pidStat[2000] = "";

	size_t allocSize = 2000 * iPart;

#ifdef _DETAILED_STATISTICS
	allocSize += 1000 * iPart;
#endif

#ifdef TRACE_BLOCKSTATISTICS
	for (pid = 0; pid < iPart; ++pid) {
		allocSize += cvd->stat[pid].numBlocks * 40 + 100 * iPart;
	}
#endif

	*strStat = (char*)calloc(allocSize, sizeof(char));
	if (!(*strStat))
		return;

	for (pid = 0; pid < iPart; ++pid) {
		BuildSolverStatisticsStringPartition(pData, pid, pidStat);
		strcat(*strStat, pidStat);
		break;  
#ifdef _DETAILED_STATISTICS
		{
			BuildDetailedSolverStatisticsString(pData, pid, (*strStat) + strlen(*strStat));
		}
#endif
#ifdef TRACE_BLOCKSTATISTICS
		TRACE_BLOCKSTATISTICS
		{
			int pos, n;
			ITI_uint i;
			ITI_SolverStatistic* stat = &cvd->stat[pid];
			char *buf = (*strStat) + strlen(*strStat);
			pos = sprintf(buf, "\nTime in CalcDerivatives: %.3f seconds\n\n", stat->calcDerivativesTime);
			n = sprintf(&buf[pos], "Block\tResidual calls\tJacobian calls\tTime (seconds)\n");
			pos += n;
			for (i = 0; i < stat->numBlocks; i++) {
				n = sprintf(&buf[pos], "%u\t%ld\t\t%ld\t\t%.3f\n", i, stat->numBlockRes[i], stat->numBlockJac[i], stat->blockTimes[i]);
				pos += n;
			}
			printf("%s", buf);
		}
		END_TRACE
#endif
	}
}

void BuildDetailedSolverStatisticsString(void* pData, size_t pid, char* strStat)
{
	ITI_SolverData* cvd = (ITI_SolverData*)pData;
	ITI_PartitionVar* curr = cvd->partition[pid].curr;

	char strJac[100];
	double dblJac = 0;

	strStat[0] = '\0';

	if ((curr->size.izf > 0) && (cvd->ss.zeros > 0))
	{
		long int locCalls;
		extern long int GetRootLocateCalls();
		double avRootLocate = 0;

		locCalls = GetRootLocateCalls();

		if (cvd->stat[pid].iZeros != 0)
			avRootLocate = (double)(locCalls) / (double)cvd->stat[pid].iZeros;

		sprintf(strStat, "  Details:\n    Root calls:\t\t%u\n    Root location:\t%li\n    Root detection:\t%li\n    Avg. root location:\t%.1f\n    Root location:\t%.1f %%\n    Root detection:\t%.1f %%\n",
			cvd->stat[pid].iRfcalls,
			locCalls,
			cvd->stat[pid].iRfcalls - locCalls,
			avRootLocate,
			100.0*(double)(locCalls) / (double)cvd->stat[pid].iRhsCalls,
			100.0*(double)(cvd->stat[pid].iRfcalls - locCalls) / (double)cvd->stat[pid].iRhsCalls
		);
	}

	if (cvd->stat[pid].iRhsCalls > 0)
	{
		if (cvd->ss.effJac > 0)
			dblJac = 100.0*(double)(cvd->stat[pid].iJac*cvd->stat[pid].ngrp) / (double)cvd->stat[pid].iRhsCalls;
		else
			dblJac = 100.0*(double)(cvd->stat[pid].iJac*curr->size.ix) / (double)cvd->stat[pid].iRhsCalls;
	}
	sprintf(strJac, "    RHS calls for Jac:\t%.1f %%\n", dblJac);
	strcat(strStat, strJac);
}

void WriteRootCounterFile(void* pData)
{
	size_t pid = 0;
	ITI_SolverData* cvd = (ITI_SolverData*)pData;
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)cvd->sc[pid];
	ITI_PartitionVar* curr = cvd->partition[0].curr;

	if((curr->size.izf > 0) && (cvd->ss.zeros > 0))
	{
		int* rootctr = (int*)calloc(curr->size.izf, sizeof(int));

		CVodeGetRootCounter(cvc->cvodeMem, rootctr);
		WriteRootCounter("rootCounter.txt", rootctr, curr->size.izf);
		free(rootctr);
	}
}

void PrintSolverStatistics(void* pData)
{
	ITI_SolverData *cvd = (ITI_SolverData *)pData;
	ITI_int iPart = cvd->partition[0].curr->size.ipart;
	char *strStat=NULL;

	BuildSolverStatisticsString(pData, &strStat);
	if (strStat) {
		printf("%s", strStat);
		free(strStat);
	}

}

void SetSetInputsFunction(void* pData, SolverInterfaceOnSetInputsFunc pOnSetInputs)
{
	size_t pid = 0;
	ITI_SolverData* cvd = (ITI_SolverData*)pData;
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)cvd->sc[pid];

	cvc->contextBase.OnSetInputs = pOnSetInputs;
}

void SetValidTimeStepFunc(void* pData, OnValidTimeStepFunc pOnValidTimeStepFunc)
{
	size_t pid = 0;
	ITI_SolverData* cvd = (ITI_SolverData*)pData;
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)cvd->sc[pid];

	cvc->OnValidTimeStep = pOnValidTimeStepFunc;
}

void SetCheckExternalEventFunc(void* pData, OnCheckExternalEventFunc pOnCheckExternalEventFunc)
{
	size_t pid = 0;
	ITI_SolverData* cvd = (ITI_SolverData*)pData;
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)cvd->sc[pid];

	cvc->OnCheckExternalEvent = pOnCheckExternalEventFunc;
}

void SetCheckStopFunc(void* pData, OnCheckStopFunc pOnCheckStopFunc)
{
	size_t pid = 0;
	ITI_SolverData* cvd = (ITI_SolverData*)pData;
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)cvd->sc[pid];

	cvc->OnCheckStop = pOnCheckStopFunc;
}

#ifndef ITI_COMP_SIM
void SetResourceFolder_CVode(void* pData, ITI_char* strFolder){
	ITI_SolverData* cvd = (ITI_SolverData*)pData;
	SetResourceFolder(cvd->partition[0].curr, strFolder);
}
#endif

ITI_SolverState HandleEquidistantOutput(size_t pid, ITI_SolverData* sd){
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)sd->sc[pid];
	ITI_Partition *pPart = &sd->partition[pid];
	ITI_PartFunctions* pPartFunctions = &sd->model.partFunctions[pid];

	ITI_SolverData* cvd = sd;  

	ITI_bi_setreal(&cvc->contextBase.i_t, cvc->contextBase.t-(0.5- DBL_EPSILON)*sd->ss.dtMin, sd->ss.dtMin);  
	if (!ITI_bi_gt(&cvc->contextBase.i_tProtNext, &cvc->contextBase.i_t))
	{
		ITI_real* xTmp;

		cvc->contextBase.action = SOLVER_INTERPOLATE;
		#ifdef ITI_COMP_SIM
		 
		 
		if (ExceptWrapper2((ModelFunc2)pPartFunctions->CalcOutputs, pPart, &sd->modelData) > SOLVER_SUCCESS_END)
			return SOLVER_SUCCESS_CONTINUE;
		ExceptWrapper2(pPartFunctions->SynchOutputs, pPart, &sd->modelData);

		 
		#endif
		#ifdef ITI_COMP_SIM
		CopyVarsCS(pPart->curr->bx, pPart->curr->bx_tmp, pPart->curr->size.bxind_cdfirst, pPart->curr->size.ibx);
		#else
		CopyVars(pPart->curr->bx, pPart->curr->bx_tmp, pPart->curr->size.bxind_cdfirst, pPart->curr->size.ibx);
		#endif
		xTmp = pPart->curr->x;
		cvc->contextBase.tTemp = pPart->curr->t;
		pPart->curr->x = NV_DATA_S(cvc->xInter);
		pPart->curr->xdot = pPart->curr->xdot_tmp;

		while (!ITI_bi_gt(&cvc->contextBase.i_tProtNext, &cvc->contextBase.i_t))
		{
			cvc->contextBase.tProt = ITI_bi_getreal(&cvc->contextBase.i_tProtNext, sd->ss.dtMin);
			 
			CVodeGetDky(cvc->cvodeMem, cvc->contextBase.tProt, 0, cvc->xInter);
			 
			sd->stat[pid].iRhsCalls++;
			pPart->curr->t = cvc->contextBase.tProt;

			if (cvc->contextBase.OnSetInputs)
			{
				cvc->contextBase.OnSetInputs(sd, pPart->curr->t, &pPart->curr->u);
			}

			pPart->transient->sInfo.bAssertActive = ITI_false;
			if (ExceptWrapper2((ModelFunc2)pPartFunctions->CalcDerivatives, pPart, &sd->modelData) > SOLVER_SUCCESS_END){
				pPart->curr->x = xTmp;
				return SOLVER_SUCCESS_CONTINUE;
			}
			sd->model.ReleaseAllMemory(&sd->modelData.currMem);
			pPart->transient->sInfo.bAssertActive = pPart->transient->sInfo.bAssertOn;

#ifdef TRACE_STATES
			TRACE_STATES
			traceStates(pid, pPart->transient, &cvd->modelData, IDS_OUTPUT);
			END_TRACE
#endif
#ifdef TRACE_DER
			TRACE_DER
			traceDer(pid, pPart->transient, &cvd->modelData, IDS_OUTPUT);
			END_TRACE
#endif

			if (HandleSaveOutputs(pid, sd, SaveOutputsEquidistantBit | SaveOutputsEquidistantPostEventsBit | SaveOutputsEquidistantPrePostEventsBit | SaveOutputsEquidistantAllEventStepsBit, ITI_true) != SOLVER_SUCCESS_END){
				pPart->curr->x = xTmp;
				return SOLVER_SUCCESS_CONTINUE;
			}

			 
			ITI_bi_plus(&cvc->contextBase.i_tProtNext, &cvc->contextBase.ui_dtProt);
		}
		pPart->curr->t = cvc->contextBase.tTemp;
		pPart->curr->x = xTmp;
		#ifdef ITI_COMP_SIM
		CopyVarsCS(pPart->curr->bx_tmp, pPart->curr->bx, pPart->curr->size.bxind_cdfirst, pPart->curr->size.ibx);
		#else
		CopyVars(pPart->curr->bx_tmp, pPart->curr->bx, pPart->curr->size.bxind_cdfirst, pPart->curr->size.ibx);
		#endif
		cvc->contextBase.action = SOLVER_UPDATE_DATA;
	}
	return SOLVER_SUCCESS_END;
}

size_t GetSize_ureal(size_t pid, void* pData)
{
	return ((ITI_SolverData*)pData)->partition[pid].curr->size.iu_real;
}

#ifdef _OPENMP

void InitData(ITI_SolverData *dst, ITI_SolverData *src)
{
	size_t pid = 0;  
	ITI_PartitionVar *pPart_dst, *pPart_src;
	ITI_int i;

	dst->sc   = src->sc;
	dst->model = src->model;
	dst->modelData = src->modelData;
	dst->ss    = src->ss;
	dst->stat  = src->stat;

	
















	dst->model.InitMemory(&dst->modelData.currMem, 0, 0);
	dst->model.InitMemory(&dst->modelData.funcMem, 0, 0);
	dst->model.InitMemory(&dst->modelData.strMem, 0, 0);

	dst->partition = malloc(sizeof(ITI_Partition));  
	dst->partition[pid].curr = malloc(sizeof(ITI_PartitionVar));
	dst->partition[pid].curr->solverData = dst;
	dst->partition[pid].base = NULL;
	dst->partition[pid].sub = NULL;
	dst->partition[pid].transient = dst->partition[pid].curr;
	dst->partition[pid].pid = 0;

	pPart_src = src->partition[pid].curr;
	pPart_dst = dst->partition[pid].curr;

	pPart_dst->size = pPart_src->size;
	pPart_dst->incCount = pPart_src->incCount;

#ifdef ITI_COMP_SIM
	pPart_dst->y.realData = malloc(pPart_dst->size.iy_real * sizeof(ITI_real*));
#else
	pPart_dst->y.realData = malloc(pPart_dst->size.iy_real * sizeof(ITI_real));
#endif
	pPart_dst->y.intData = malloc(pPart_dst->size.iy_int * sizeof(ITI_int));
	pPart_dst->y.strData = malloc(pPart_dst->size.iy_str * sizeof(ITI_char*));
	pPart_dst->y.strSize = malloc(pPart_dst->size.iy_str * sizeof(size_t));

#ifdef ITI_COMP_SIM
	pPart_dst->p.realData = malloc(pPart_dst->size.ip_real * sizeof(ITI_real*));
#else
	pPart_dst->p.realData = malloc(pPart_dst->size.ip_real * sizeof(ITI_real));
#endif
	pPart_dst->p.intData = malloc(pPart_dst->size.ip_int * sizeof(ITI_int));
	pPart_dst->p.strData = malloc(pPart_dst->size.ip_str * sizeof(ITI_char*));
	pPart_dst->p.strSize = malloc(pPart_dst->size.ip_str * sizeof(size_t));

#ifdef ITI_COMP_SIM
	pPart_dst->u.realData = malloc(pPart_dst->size.iu_real * sizeof(ITI_real*));
#else
	pPart_dst->u.realData = malloc(pPart_dst->size.iu_real * sizeof(ITI_real));
#endif
	pPart_dst->u.intData = malloc(pPart_dst->size.iu_int * sizeof(ITI_int));
	pPart_dst->u.strData = malloc(pPart_dst->size.iu_str * sizeof(ITI_char*));
	pPart_dst->u.strSize = malloc(pPart_dst->size.iu_str * sizeof(size_t));

#ifdef ITI_COMP_SIM
	pPart_dst->v.realData = malloc(pPart_dst->size.iv_real * sizeof(ITI_real*));  
 
	if (pPart_dst->size.iv_real > 0)
		pPart_dst->v.realData[0] = malloc(pPart_dst->size.iv_real * sizeof(ITI_real));
 
	for (i = 1; i < pPart_dst->size.iv_real; i++) {
		pPart_dst->v.realData[i] = pPart_dst->v.realData[0] + i;
 
	}
#else
	pPart_dst->v.realData = malloc(pPart_dst->size.iv_real * sizeof(ITI_real));
 
#endif
	pPart_dst->v.intData = malloc(pPart_dst->size.iv_int * sizeof(ITI_int));
 
	pPart_dst->v.strData = malloc(pPart_dst->size.iv_str * sizeof(ITI_char*));
	pPart_dst->v.strSize = malloc(pPart_dst->size.iv_str * sizeof(size_t));
	 

#ifdef ITI_COMP_SIM
	pPart_dst->z.realData = malloc(pPart_dst->size.iz_real * sizeof(ITI_real*));
	pPart_dst->pre_z.realData = malloc(pPart_dst->size.iz_real * sizeof(ITI_real*));
	if (pPart_dst->size.iz_real > 0) {
		pPart_dst->z.realData[0] = malloc(pPart_dst->size.iz_real * sizeof(ITI_real));
		pPart_dst->pre_z.realData[0] = malloc(pPart_dst->size.iz_real * sizeof(ITI_real));
	}
	for (i = 1; i < pPart_dst->size.iz_real; i++) {
		pPart_dst->z.realData[i] = pPart_dst->z.realData[0] + i;
		pPart_dst->pre_z.realData[i] = pPart_dst->pre_z.realData[0] + i;
	}
#else
	pPart_dst->z.realData = malloc(pPart_dst->size.iz_real * sizeof(ITI_real));
	pPart_dst->pre_z.realData = malloc(pPart_dst->size.iz_real * sizeof(ITI_real));
#endif
	pPart_dst->z.intData = malloc(pPart_dst->size.iz_int * sizeof(ITI_int));
	pPart_dst->z.strData = malloc(pPart_dst->size.iz_str * sizeof(ITI_char*));
	pPart_dst->z.strSize = malloc(pPart_dst->size.iz_str * sizeof(size_t));
	pPart_dst->pre_z.intData = malloc(pPart_dst->size.iz_int * sizeof(ITI_int));
	pPart_dst->pre_z.strData = malloc(pPart_dst->size.iz_str * sizeof(ITI_char*));
	pPart_dst->pre_z.strSize = malloc(pPart_dst->size.iz_str * sizeof(size_t));

#ifdef ITI_COMP_SIM
	pPart_dst->bx = malloc(pPart_dst->size.ibx * sizeof(ITI_real*));
	pPart_dst->bxd = malloc(pPart_src->size.ibx * sizeof(ITI_real));
	










	for (i = 0; i < pPart_dst->size.ibx; i++)
		pPart_dst->bx[i] = &pPart_dst->bxd[i];

#else
	pPart_dst->bx = malloc(pPart_dst->size.ibx * sizeof(ITI_real));
	pPart_dst->bx_tmp = malloc(pPart_dst->size.ibx * sizeof(ITI_real));
#endif

#ifdef ITI_COMP_SIM
	if (pPart_dst->size.iclocksv_real == 0)
		pPart_dst->clocksv.realData = NULL;
	else
		pPart_dst->clocksv.realData = malloc((pPart_dst->size.iclocksv_real + pPart_dst->size.iclocksv_int) * sizeof(ITI_real*));
	for (i = 0; i < pPart_dst->size.iclocksv_real; i++)
		pPart_dst->clocksv.realData[i] = pPart_dst->clocksv.realData[0] + i;
#else
	if (pPart_dst->size.iclocksv_real == 0)
		pPart_dst->clocksv.realData = NULL;
	else
		pPart_dst->clocksv.realData = malloc(pPart_dst->size.iclocksv_real * sizeof(ITI_real));
#endif
	if (pPart_dst->size.iclocksv_int == 0)
		pPart_dst->clocksv.intData = NULL;
	else
		pPart_dst->clocksv.intData = malloc(pPart_dst->size.iclocksv_int * sizeof(ITI_int));
	if (pPart_dst->size.iclocksv_str == 0) {
		pPart_dst->clocksv.strData = NULL;
		pPart_dst->clocksv.strSize = NULL;
	}
	else {
		pPart_dst->clocksv.strData = malloc(pPart_dst->size.iclocksv_str * sizeof(ITI_char*));
		pPart_dst->clocksv.strSize = malloc(pPart_dst->size.iclocksv_str * sizeof(size_t));
	}

	AllocZFData(pPart_dst, src->model.partFunctions[pid].dataZF, 0, 0);
	 
	pPart_dst->pre_zf = pPart_src->pre_zf;
	pPart_dst->oszf   = pPart_src->oszf;
	pPart_dst->czf    = pPart_src->czf;
	pPart_dst->ezf    = pPart_src->ezf;
	pPart_dst->relzf  = pPart_src->relzf;
	pPart_dst->epszf  = pPart_src->epszf;
	pPart_dst->sczf   = pPart_src->sczf;

	pPart_dst->sv = malloc(pPart_dst->size.isv * sizeof(ITI_int));

	pPart_dst->cNd = malloc(pPart_dst->size.icnd * sizeof(ITI_CurveData_ND));
	InitCurveDataND(pPart_dst->cNd, dst->model.partFunctions[pid].curveNDs, pPart_dst->size.icnd, NULL);

	pPart_dst->cSet = malloc(pPart_dst->size.icset * sizeof(ITI_CurveSetData));
	InitCurveSetData(pPart_dst->cSet, dst->model.partFunctions[pid].curveSets, pPart_dst->size.icset, NULL);

	dst->model.AllocateRecords(&dst->partition[pid]);

	pPart_dst->arrays = malloc(pPart_dst->size.iarr * sizeof(ITI_Array));
	InitDataArrays2(pPart_dst->arrays, pPart_dst->size.iarr, dst->model.partFunctions[pid].arrayData, 0);

	pPart_dst->cs = malloc(pPart_dst->size.ics * sizeof(ITI_CurveCallState));
	for (i = 0; i < pPart_dst->size.ics; i++) {
		ITI_uint j;
		pPart_dst->cs[i].pSeqCs = malloc(dst->model.partFunctions[pid].seqCsSizes[i] * sizeof(ITI_SeqCallState));
		for (j = 0; j < dst->model.partFunctions[0].seqCsSizes[i]; j++)
			pPart_dst->cs[i].pSeqCs[j].iPos = -1;
	}

	pPart_dst->hcs = malloc(pPart_dst->size.ihcs * sizeof(ITI_HystCurveCallState));

	pPart_dst->db = malloc(pPart_dst->size.idb * sizeof(ITI_DelayBuffer));
	InitDelayBuffers(pPart_dst->db, pPart_dst->size.idb, dst->model.partFunctions[pid].delayInfos, 0);

	pPart_dst->iDPbd = malloc(pPart_dst->size.iDPB * sizeof(ITI_DPBlockData));
	InitDPBlockData(pPart_dst->iDPbd, &pPart_dst->stateIncidence, dst->model.partFunctions[pid].DPBlockSizes, pPart_dst->size.iDPB, 0);

	pPart_dst->ibd = malloc(pPart_dst->size.numBlocks * sizeof(ITI_BlockData));
	InitBlockData(pPart_dst->ibd, pPart_dst->size.numBlocks, dst->model.partFunctions[pid].blockSizes, dst->model.partFunctions[pid].numJacColsData, dst->model.partFunctions[pid].DPBlockSizes, 0);
	dst->model.partFunctions[pid].InitBlockVars(pPart_dst->ibd);

	pPart_dst->smm = malloc(sizeof(ITI_StateMinMax));
	InitStateMinMax(pPart_dst->smm, pPart_dst->size.numStateAttr);

	pPart_dst->performanceData = pPart_src->performanceData;  
	pPart_dst->partitionData = NULL;
	pPart_dst->partitionIG = NULL;
	pPart_dst->size.iig = 0;
#ifdef ITI_COMP_SIM
	dst->modelData.traceFlags = src->modelData.traceFlags;
#endif
}

void InitParallelData(ITI_SolverData *cvd)
{
	ITI_int i;
	size_t pid = 0;  
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)cvd->sc[pid];
	ITI_ParallelData *parallelData;
	ITI_Partition *pPart = &cvd->partition[pid];

	cvc->parDat = malloc(sizeof(ITI_ParallelData));
	parallelData = (ITI_ParallelData*)cvc->parDat;

	parallelData->y_par = malloc(cvc->maxThreads * sizeof(N_Vector));
	parallelData->ftemp_par = malloc(cvc->maxThreads * sizeof(N_Vector));
	parallelData->jthCol_par = malloc(cvc->maxThreads * sizeof(N_Vector));
	parallelData->cvd_par = malloc(cvc->maxThreads * sizeof(ITI_SolverData));

#ifdef ITI_COMP_SIM
	parallelData->bx_tmp = malloc(pPart->curr->size.ibx * sizeof(ITI_real));
#endif

	for (i = 0; i < cvc->maxThreads; i++) {
		parallelData->y_par[i] = N_VNew_Serial(pPart->curr->size.ix);
		parallelData->ftemp_par[i] = N_VNew_Serial(pPart->curr->size.ix);
		parallelData->jthCol_par[i] = N_VNewEmpty_Serial(pPart->curr->size.ix);

		InitData(&parallelData->cvd_par[i], cvd);
	}
}

void FreeData(size_t pid, ITI_SolverData *cvd)
{
	ITI_int i;
	ITI_Partition* pPart = &cvd->partition[pid];

#ifdef ITI_COMP_SIM
	free(pPart->curr->bxd);

	if (pPart->curr->size.iv_real > 0)
		free(pPart->curr->v.realData[0]);
 
	if (pPart->curr->size.iz_real > 0) {
		free(pPart->curr->z.realData[0]);
		free(pPart->curr->pre_z.realData[0]);
	}
#else
		free(pPart->curr->bx_tmp);
#endif

	FreeCompositeData(&pPart->curr->y, 0);
	FreeCompositeData(&pPart->curr->u, 0);
	FreeCompositeData(&pPart->curr->p, 0);

	FreeCompositeData(&pPart->curr->v, 0);
 
	FreeCompositeData(&pPart->curr->z, 0);
	FreeCompositeData(&pPart->curr->pre_z, 0);

	free(pPart->curr->bx);
	 

	free(pPart->curr->clocksv.realData);
	free(pPart->curr->clocksv.intData);
	free(pPart->curr->clocksv.strData);
	free(pPart->curr->clocksv.strSize);

 

	FreeZFData(pPart->curr, 0, 0);

	if (pid == 0) {
		FreeIGData(pPart, &free);
		free(pPart->transient->partitionData);
	}





	free(pPart->curr->sv);













	cvd->model.FreeRecords(pPart, &cvd->modelData);

#ifndef ITI_COMP_SIM
	FreeCurveSetData(pPart->curr->cSet, pPart->curr->size.icset, NULL);
#endif
	free(pPart->curr->cSet);

#ifndef ITI_COMP_SIM
	FreeCurveDataND(pPart->curr->cNd, pPart->curr->size.icnd, NULL);
#endif
	free(pPart->curr->cNd);

	for (i = 0; i < pPart->curr->size.ics; i++)
		free(pPart->curr->cs[i].pSeqCs);

	free(pPart->curr->cs);

	free(pPart->curr->hcs);

	FreeDelayBuffers(pPart->curr->db, pPart->curr->size.idb, 0);
	free(pPart->curr->db);

	FreeDPBlockData(pPart->curr->iDPbd, &pPart->curr->stateIncidence, pPart->curr->size.iDPB, 0);
	free(pPart->curr->iDPbd);

	FreeBlockData(pPart->curr->ibd, pPart->curr->size.numBlocks, 0);
	free(pPart->curr->ibd);

	FreeStateMinMax(pPart->curr->smm);
	free(pPart->curr->smm);

	FreeDataArrays2(&cvd->modelData.currMem, pPart->curr->arrays, pPart->curr->size.iarr, 0);

	cvd->model.FreeAllMemory(&cvd->modelData.currMem);
	cvd->model.FreeAllMemory(&cvd->modelData.funcMem);
	cvd->model.FreeAllMemory(&cvd->modelData.strMem);

	free(cvd->partition->curr);
	free(cvd->partition);
}

void FreeParallelData(void* pData) {
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)pData;
	ITI_ParallelData *parallelData = (ITI_ParallelData *)cvc->parDat;
	ITI_int i;

	if (parallelData != NULL) {
		for (i = 0; i < cvc->maxThreads; i++) {
			N_VDestroy_Serial(parallelData->y_par[i]);
			N_VDestroy_Serial(parallelData->ftemp_par[i]);
			N_VDestroy_Serial(parallelData->jthCol_par[i]);
			FreeData(0, &parallelData->cvd_par[i]);	 
		}

	#ifdef ITI_COMP_SIM
		free(parallelData->bx_tmp);
	#endif

		free(parallelData->y_par);
		free(parallelData->ftemp_par);
		free(parallelData->jthCol_par);
		free(parallelData->cvd_par);

		free(cvc->parDat);
	}
}

void CopySimData(ITI_SolverData *dst, ITI_SolverData *src)
{
	 
	size_t pid = 0;  
	ITI_int i;
	unsigned j;

	ITI_PartitionVar *pPartCurr_dst = dst->partition[pid].curr;
	ITI_PartitionVar *pPartCurr_src = src->partition[pid].curr;

	 
	pPartCurr_dst->t = pPartCurr_src->t;

#ifdef ITI_COMP_SIM
	CopyVarsA(pPartCurr_src->bx_tmp, pPartCurr_dst->bxd, pPartCurr_src->size.bxind_cdfirst, pPartCurr_src->size.ibx);
	



	for (i = 0; i < pPartCurr_dst->size.iz_real; i++) {
		*pPartCurr_dst->pre_z.realData[i] = *pPartCurr_src->pre_z.realData[i];
		*pPartCurr_dst->z.realData[i] = *pPartCurr_src->z.realData[i];
	}
	for (i = 0; i < pPartCurr_dst->size.iv_real; i++)
		*pPartCurr_dst->v.realData[i] = *pPartCurr_src->v.realData[i];
#else
	memcpy(pPartCurr_dst->bx, pPartCurr_src->bx, pPartCurr_dst->size.ibx * sizeof(ITI_real));

	memcpy(pPartCurr_dst->p.realData, pPartCurr_src->p.realData, pPartCurr_dst->size.ip_real * sizeof(ITI_real));

	memcpy(pPartCurr_dst->pre_z.realData, pPartCurr_src->pre_z.realData, pPartCurr_dst->size.iz_real * sizeof(ITI_real));
	memcpy(pPartCurr_dst->z.realData, pPartCurr_src->z.realData, pPartCurr_dst->size.iz_real * sizeof(ITI_real));

	memcpy(pPartCurr_dst->v.realData, pPartCurr_src->v.realData, pPartCurr_src->size.iv_real * sizeof(ITI_real));
#endif

	memcpy(pPartCurr_dst->u.intData, pPartCurr_src->u.intData, pPartCurr_dst->size.iu_int * sizeof(ITI_int));

#ifdef ITI_COMP_SIM
	for (i = 0; i < pPartCurr_dst->size.iu_real; i++)
		*pPartCurr_dst->u.realData[i] = *pPartCurr_src->u.realData[i];
#else
	memcpy(pPartCurr_dst->u.realData, pPartCurr_src->u.realData, pPartCurr_dst->size.iu_real * sizeof(ITI_real));
#endif

	memcpy(pPartCurr_dst->p.intData, pPartCurr_src->p.intData, pPartCurr_dst->size.ip_int * sizeof(ITI_int));

	memcpy(pPartCurr_dst->pre_z.intData, pPartCurr_src->pre_z.intData, pPartCurr_dst->size.iz_int * sizeof(ITI_int));

	memcpy(pPartCurr_dst->z.intData, pPartCurr_src->z.intData, pPartCurr_dst->size.iz_int * sizeof(ITI_int));

	memcpy(pPartCurr_dst->v.intData, pPartCurr_src->v.intData, pPartCurr_src->size.iv_int * sizeof(ITI_int));

	pPartCurr_dst->szf = pPartCurr_src->oszf;

	for (i = 0; i < pPartCurr_dst->size.ics; i++)
		for (j = 0; j < dst->model.partFunctions[pid].seqCsSizes[i]; j++)
			pPartCurr_dst->cs[i].pSeqCs[j] = pPartCurr_src->cs[i].pSeqCs[j];

	for (i = 0; i < pPartCurr_dst->size.ihcs; i++)
		pPartCurr_dst->hcs[i] = pPartCurr_src->hcs[i];

	for (i = 0; i < pPartCurr_dst->size.idb; i++) {
		pPartCurr_dst->db[i].lastPosIn = pPartCurr_src->db[i].lastPosIn;
		pPartCurr_dst->db[i].lastPosOut = pPartCurr_src->db[i].lastPosOut;
		memcpy(pPartCurr_dst->db[i].times, pPartCurr_src->db[i].times, pPartCurr_src->db[i].size * sizeof(ITI_real));
		if (pPartCurr_src->db[i].valType == DelayValueType_Real)
			memcpy(pPartCurr_dst->db[i].realValues, pPartCurr_src->db[i].realValues, pPartCurr_src->db[i].size * sizeof(ITI_real));
		else
			memcpy(pPartCurr_dst->db[i].intValues, pPartCurr_src->db[i].intValues, pPartCurr_src->db[i].size * sizeof(ITI_int));
		pPartCurr_dst->db[i].iL = pPartCurr_src->db[i].iL;
		pPartCurr_dst->db[i].iR = pPartCurr_src->db[i].iR;
		pPartCurr_dst->db[i].iSearch = pPartCurr_src->db[i].iSearch;
		pPartCurr_dst->db[i].iNewVal = pPartCurr_src->db[i].iNewVal;
	}

	if (pPartCurr_src->size.i_inc > 0)
		memcpy(pPartCurr_dst->iDPbd->M, pPartCurr_src->iDPbd->M, pPartCurr_src->size.i_inc * sizeof(ITI_uint));
	





	pPartCurr_dst->tLastStep = pPartCurr_src->tLastStep;

	 
	pPartCurr_dst->sInfo = pPartCurr_src->sInfo;
}

void CopySimData1st(ITI_SolverData *src)
{
	 
	ITI_int i, j;
	size_t pid = 0;  
	ITI_CVodeContext *cvc = (ITI_CVodeContext *)src->sc[pid];
	ITI_ParallelData *pd = (ITI_ParallelData *)cvc->parDat;

	for (i = 0; i < cvc->maxThreads; i++) {
		ITI_PartitionVar *pPartCurr_dst, *pPartCurr_src;

		ITI_SolverData *dst = &pd->cvd_par[i];

		CopySimData(dst, src);

		pPartCurr_dst = dst->partition[pid].curr;
		pPartCurr_src = src->partition[pid].curr;

#ifdef ITI_COMP_SIM
		for (j = 0; j < pPartCurr_dst->size.ip_real; j++)
			pPartCurr_dst->p.realData[j] = pPartCurr_src->p.realData[j];  

		for (j = 0; j < pPartCurr_dst->size.ibx; j++)
			*pPartCurr_dst->bx[j] = *pPartCurr_src->bx[j];
		for (j = 0; j < pPartCurr_dst->size.bxind_cdfirst; j++)
			pPartCurr_dst->bxd[j] = *pPartCurr_src->bx[j];





		for (j = 0; j < pPartCurr_dst->size.iz_real; j++)
			*pPartCurr_dst->z.realData[j] = *pPartCurr_src->z.realData[j];

		for (j = 0; j < pPartCurr_dst->size.icnd; j++)
			pPartCurr_dst->cNd[j] = pPartCurr_src->cNd[j];

		for (j = 0; j < pPartCurr_dst->size.icset; j++)
			pPartCurr_dst->cSet[j] = pPartCurr_src->cSet[j];
#else
		memcpy(pPartCurr_dst->bx, pPartCurr_src->bx, pPartCurr_src->size.ibx * sizeof(ITI_real));
 
		memcpy(pPartCurr_dst->z.realData, pPartCurr_src->z.realData, pPartCurr_src->size.iz_real * sizeof(ITI_real));
#endif
 


		memcpy(pPartCurr_dst->y.intData, pPartCurr_src->y.intData, pPartCurr_src->size.iy_int * sizeof(ITI_int));
		memcpy(pPartCurr_dst->y.realData, pPartCurr_src->y.realData, pPartCurr_src->size.iy_real * sizeof(ITI_real));
 
 
		memcpy(pPartCurr_dst->zf, pPartCurr_src->zf, pPartCurr_src->size.izf * sizeof(ITI_real));
		memcpy(pPartCurr_dst->sv, pPartCurr_src->sv, pPartCurr_src->size.isv * sizeof(ITI_int));

		SetBlockSettings(pPartCurr_dst->size.numBlocks, pPartCurr_dst->ibd, dst->ss.gltol, dst->ss.linSolv, dst->ss.ignoreMinMax);

		pPartCurr_dst->_hyst_init_data = pPartCurr_src->_hyst_init_data;

		if (pPartCurr_dst->size.iRec > 0)
			memcpy(pPartCurr_dst->pRecord, pPartCurr_src->pRecord, src->model.GetRecordSize());

		for (j = 0; j < pPartCurr_dst->size.iarr; j++) {
			memcpy(pPartCurr_dst->arrays[j].dims, pPartCurr_src->arrays[j].dims, pPartCurr_src->arrays[j].nDims * sizeof(ITI_int));
			switch (pPartCurr_src->arrays[j].memType) {
			case REAL_TYPE:
				if (pPartCurr_src->arrays[j].realValues != NULL)
					memcpy(pPartCurr_dst->arrays[j].realValues, pPartCurr_src->arrays[j].realValues, src->model.partFunctions[pid].arrayData[j].nValues * sizeof(ITI_real));
				break;
			case INT_TYPE:
				if (pPartCurr_src->arrays[j].intValues != NULL)
					memcpy(pPartCurr_dst->arrays[j].intValues, pPartCurr_src->arrays[j].intValues, src->model.partFunctions[pid].arrayData[j].nValues * sizeof(ITI_int));
				break;
			case STRING_TYPE:  
			case STRING_PTR_TYPE:
				if (pPartCurr_src->arrays[j].charValues != NULL)
					memcpy(pPartCurr_dst->arrays[j].charValues, pPartCurr_src->arrays[j].charValues, src->model.partFunctions[pid].arrayData[j].nValues * sizeof(ITI_char*));
				break;
			default:
				break;
			}
		}
	}
}

#endif

static ITI_SolverState handleValidTimeStep(size_t pid, void* pData){
	ITI_SolverData* cvd = (ITI_SolverData*)pData;
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)cvd->sc[pid];
	ITI_Partition *pPart = &cvd->partition[pid];
	ITI_PartFunctions* pPartFunctions = &cvd->model.partFunctions[pid];
	ITI_SolverState iRet = SOLVER_SUCCESS_END;

	cvc->contextBase.action = SOLVER_UPDATE_DATA;
	if(cvd->ss.saveModeB & (SaveOutputsEquidistantBit | SaveOutputsEquidistantPostEventsBit | SaveOutputsEquidistantPrePostEventsBit | SaveOutputsEquidistantAllEventStepsBit)) {
		iRet = HandleEquidistantOutput(pid, cvd);
		if (iRet > SOLVER_SUCCESS_END)
		{
			HandleWarnings(&pPart->transient->sInfo);
			cvc->contextBase.state = SOLVER_ERROR;
			return cvc->contextBase.state;
		}
	}

	 
	 
	Update_pre_zf(pPart->curr->pre_zf, pPart->curr->zf, pPart->curr->size.izf);

	cvd->stat[pid].iRhsCalls++;
	pPart->curr->x = NV_DATA_S(cvc->x);  
	pPart->curr->sInfo.bDPRequired = ITI_false;
	pPart->curr->sInfo.bEventTriggered = ITI_false;
	pPart->curr->sInfo.tracingAllowed = ITI_true;
	pPart->curr->sInfo.isTerminate = ITI_false;

	if (cvc->contextBase.OnSetInputs)
	{
		if(cvc->contextBase.OnSetInputs(cvd, pPart->curr->t, &pPart->curr->u) > 0)
		{
			HandleWarnings(&pPart->transient->sInfo);
			cvc->contextBase.state = SOLVER_ERROR_IN_ON_SET_INPUTS;
			return cvc->contextBase.state;
		}
	}
	pPart->curr->sInfo.strAnalysisTypeDetail = "validStep";
	pPart->transient->sInfo.bAssertActive = ITI_false;
	 
		 
		if (ExceptWrapper2((ModelFunc2)pPartFunctions->CalcDerivatives, pPart, &cvd->modelData) > SOLVER_SUCCESS_END) {
			HandleWarnings(&pPart->transient->sInfo);
			cvc->contextBase.state = SOLVER_ERROR;
			return cvc->contextBase.state;
		}
		cvd->model.ReleaseAllMemory(&cvd->modelData.currMem);
	 
	pPart->curr->sInfo.strAnalysisTypeDetail = "validStep";
	if (ExceptWrapper2((ModelFunc2)pPartFunctions->ValidStep, pPart, &cvd->modelData) > SOLVER_SUCCESS_END) {
		HandleWarnings(&pPart->transient->sInfo);
		cvc->contextBase.state = SOLVER_ERROR;
		return cvc->contextBase.state;
	}
	cvd->model.ReleaseAllMemory(&cvd->modelData.currMem);

	pPart->transient->sInfo.bAssertActive = pPart->transient->sInfo.bAssertOn;

#ifdef TRACE_STATES
	TRACE_STATES
	traceStates(pid, pPart->curr, &cvd->modelData, IDS_CVODE_VALIDSTEP);
	END_TRACE
#endif
#ifdef TRACE_DER
	TRACE_DER
	traceDer(pid, pPart->curr, &cvd->modelData, IDS_CVODE_VALIDSTEP);
	END_TRACE
#endif

	pPart->curr->sInfo.strAnalysisTypeDetail = "residuals";

	UpdateEpsilonZF(pPart->curr);

	#ifdef _SAVE_VARS_VALID_STEP
	{
		int i;
		FILE* vars = fopen("VarsValid.txt", "w+");
		for(i = 0; i < pPart->curr->size.iv_real; i++)
		{
			fprintf(vars, "%f\n", *(pPart->curr->v.realData[i]));
		}
		fclose(vars);

		vars = fopen("DiscVarsValid.txt", "w+");
		for(i = 0; i <pPart->curr->size.iz_real; i++)
		{
			fprintf(vars, "%f\n", *(pPart->curr->z.realData[i]));
		}
		fclose(vars);

	}
	#endif

	 
	pPartFunctions->AssignLastVar(pPart, &cvd->modelData);
	if(cvd->ss.saveModeB & (SaveOutputsAtleastwithdtProtBit | SaveOutputsAtleastwithdtProtPostEventsBit | SaveOutputsAtleastwithdtProtPrePostEventsBit | SaveOutputsAtleastwithdtProtAllEventStepsBit))
	{
		if(cvc->contextBase.t >= cvc->contextBase.tProt + cvd->ss.dtProtMin)
		{
			cvc->contextBase.tProt = cvc->contextBase.t;
			if (HandleSaveOutputs(pid, cvd, (SaveOutputsAtleastwithdtProtBit | SaveOutputsAtleastwithdtProtPostEventsBit | SaveOutputsAtleastwithdtProtPrePostEventsBit | SaveOutputsAtleastwithdtProtAllEventStepsBit), ITI_true) > SOLVER_SUCCESS_END)
			{
				HandleWarnings(&pPart->transient->sInfo);
				cvc->contextBase.state = SOLVER_ERROR;
				return cvc->contextBase.state;
			}
		}
	}
	if (HandleSaveOutputs(pid, cvd, SaveOutputsAllBit, ITI_true) != SOLVER_SUCCESS_END)
	{
		HandleWarnings(&pPart->transient->sInfo);
		cvc->contextBase.state = SOLVER_ERROR;
		return cvc->contextBase.state;
	}

	if(cvc->OnValidTimeStep)
		cvc->OnValidTimeStep(pid, pData);

	pPart->curr->sInfo.tracingAllowed = ITI_false;
	cvd->stat[pid].iValidSteps ++;

	 
	UpdateDelayBuffers(pPart->curr->db, pPart->curr->size.idb);
	UpdateHystCurves(pPart->curr->hcs, pPart->curr->size.ihcs);
	HandleAssertWarnings(&pPart->transient->sInfo);

	 
	if(pPart->curr->sInfo.isTerminate)
	{
		cvc->contextBase.bTerminateRequired  = ITI_true;
		cvc->contextBase.bTimeEvent = ITI_true;
	}

	return cvc->contextBase.state;
}

static ITI_SolverState handleTimeEventEfficiently(size_t pid, void* pData){
	ITI_SolverData* cvd = (ITI_SolverData*)pData;
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)cvd->sc[pid];
	ITI_Partition *pPart = &cvd->partition[pid];
	ITI_PartFunctions* pPartFunctions = &cvd->model.partFunctions[pid];

	cvc->t1 = cvc->contextBase.t;

	 
	if(cvc->contextBase.tHit <= cvc->t1){
		ITI_int bRepeat = 0;
		ITI_int iReinitSolver = 0;
		do{
			ITI_int i;
			if(pPart->curr->size.izf == 0){
				 
				cvd->stat[pid].iRhsCalls++;
				pPart->curr->xdot = NV_DATA_S(cvc->xdot);
				ExceptWrapper2((ModelFunc2)pPartFunctions->CalcDerivatives, pPart, &cvd->modelData);
				cvd->model.ReleaseAllMemory(&cvd->modelData.currMem);
#ifdef TRACE_STATES
				TRACE_STATES
				traceStates(pid, pPart->curr, &cvd->modelData, IDS_EFFICIENT);
				END_TRACE
#endif
#ifdef TRACE_DER
				TRACE_DER
				traceDer(pid, pPart->curr, &cvd->modelData, IDS_EFFICIENT);
				END_TRACE
#endif
			}

			iReinitSolver = 0;
			cvd->stat[pid].iTimeEvents++;

			for (i = 0; i < pPart->curr->size.ix; i++)
				pPart->curr->xChanged[i] = 0;

			 
			pPart->curr->x = NV_DATA_S(cvc->x_tE);
			pPart->curr->xdot = NV_DATA_S(cvc->xdot_tE);

			 
			CVodeGetDky(cvc->cvodeMem, cvc->contextBase.tHit, 0, cvc->x_tE);

			 
			cvc->contextBase.t = pPart->curr->t = cvc->contextBase.tHit;
			if (cvc->contextBase.OnSetInputs){
				cvc->contextBase.OnSetInputs(cvd, pPart->curr->t, &pPart->curr->u);
			}

			pPart->transient->sInfo.dt = cvc->contextBase.t - pPart->curr->tLastStep;

			if(handleValidTimeStep(pid, pData) < SOLVER_SUCCESS_END){
				return cvc->contextBase.state;
			}

			if(cvc->OnCheckExternalEvent){
				ITI_SolverState iRet = cvc->OnCheckExternalEvent(pData);

				if(iRet > SOLVER_SUCCESS_END)
					pPart->curr->sInfo.bEventTriggered = ITI_true;
			}

			if(pPart->curr->sInfo.bEventTriggered)
				cvd->stat[pid].iOtherEvents++;

			 
			pPart->curr->xdot = NV_DATA_S(cvc->xdot_tEE);

			 
			if (cvc->contextBase.tHit = cvc->contextBase.tHitSample) {
				CheckSampleActive(pid, cvd);

				 
				 
				if (cvd->ss.bStopAtStop) {
					ITI_bui_minus(&cvc->contextBase.timeEventCounter[pPart->curr->size.isv], &cvc->contextBase.ui_dtHit);
					if (ITI_bui_is_zero(&cvc->contextBase.timeEventCounter[pPart->curr->size.isv])) {
						ITI_bui_reset(&cvc->contextBase.ui_dtHit);
						cvc->contextBase.bTerminateRequired = ITI_true;
						cvc->contextBase.bTimeEvent = ITI_true;
					}
				}
				else {
					cvc->contextBase.bTimeEvent = ITI_true;
				}
			}

			if(cvc->contextBase.bTimeEvent){
				cvc->contextBase.state = EventIterationPartition(pid, cvd);
				if(cvc->contextBase.state != SOLVER_SUCCESS_CONTINUE)
					return cvc->contextBase.state;

				if(!pPart->transient->sInfo.isTerminal) {
					 
					iReinitSolver = classifyEventNumerically(pid, pData);
				}
				else{
					iReinitSolver = 1;
				}

				 

				if(iReinitSolver){
					cvd->stat[pid].iTimeEventsReinit++;
					cvc->contextBase.t = pPart->curr->t = cvc->contextBase.tHit;
					 
					N_VScale(ONE, cvc->x_tE, cvc->x);
					pPart->curr->x = NV_DATA_S(cvc->x);
					reinitCVode(pid, pData);
					cvc->contextBase.bZeroFunc = ITI_false;
				}
				pPart->curr->tLastStep = cvc->contextBase.tHit;
				 
				calcNextHitTime(pid, pData, cvc->contextBase.t);
			}

			cvc->contextBase.bTimeEvent = ITI_false;

			bRepeat = (pPart->transient->sInfo.isTerminal==0) && (iReinitSolver==0) && (cvc->contextBase.tHit <= cvc->t1);
		}while(bRepeat);

		if(!iReinitSolver  ){
			CVodeUpdateGlo(cvc->cvodeMem, pPart->curr->zf);
			cvc->contextBase.t = pPart->curr->t = cvc->t1;
			pPart->transient->sInfo.dt = cvc->contextBase.t - pPart->curr->tLastStep;
			pPart->curr->tLastStep = pPart->curr->t = cvc->contextBase.t;
			pPart->curr->x = NV_DATA_S(cvc->x);
			pPart->curr->xdot = NV_DATA_S(cvc->xdot);

			if(handleValidTimeStep(pid, pData) < SOLVER_SUCCESS_END)
				return cvc->contextBase.state;
		}
	}
	else{
		pPart->curr->tLastStep = pPart->curr->t = cvc->contextBase.t;
		CVodeGetLastStep(cvc->cvodeMem, &pPart->transient->sInfo.dt);

		if(handleValidTimeStep(pid, pData) < SOLVER_SUCCESS_END){
			return cvc->contextBase.state;
		}
	}
	return cvc->contextBase.state;
}

static ITI_SolverState reinitCVode(size_t pid, void* pData){
	ITI_SolverData* cvd = (ITI_SolverData*)pData;
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)cvd->sc[pid];
	ITI_Partition *pPart = &cvd->partition[pid];
	ITI_real* v = N_VGetArrayPointer(cvc->x);
	N_VSetArrayPointer(pPart->curr->x, cvc->x);

	CVodeReInit(cvc->cvodeMem, CalcRHS, cvc->contextBase.t, cvc->x, CV_SV, cvc->contextBase.relTol, cvc->absTolVec);

	N_VSetArrayPointer(v, cvc->x);

	return SOLVER_SUCCESS_END;
}

static ITI_SolverState classifyEventNumerically(size_t pid, void* pData){
	ITI_SolverData* cvd = (ITI_SolverData*)pData;
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)cvd->sc[pid];
	ITI_Partition *pPart = &cvd->partition[pid];
	ITI_PartFunctions* pPartFunctions = &cvd->model.partFunctions[pid];
	ITI_SolverState iRet = SOLVER_SUCCESS_END;
	ITI_SolverState iDRet = SOLVER_SUCCESS_END;

	if(pPart->curr->sInfo.bSolverNeedsReset){
		 
		pPart->curr->sInfo.bSolverNeedsReset = ITI_false;
		iRet = SOLVER_SUCCESS_CONTINUE;
	}

	 
	if(checkInvalidateDerivatives(pid, pData, cvc->xdot_tE, cvc->xdot_tEE)){
		iRet = SOLVER_SUCCESS_CONTINUE;
	}

	 
	 
	cvc->contextBase.t = pPart->curr->t = cvc->t1;
	pPart->curr->x = NV_DATA_S(cvc->x);
	pPart->curr->xdot = NV_DATA_S(cvc->xdot_tE1);

	if (cvc->contextBase.OnSetInputs){
		cvc->contextBase.OnSetInputs(cvd, pPart->curr->t, &pPart->curr->u);
	}

	 
	cvd->stat[pid].iRhsCalls++;
	iDRet = ExceptWrapper2((ModelFunc2)pPartFunctions->CalcDerivatives, pPart, &cvd->modelData);
	cvd->model.ReleaseAllMemory(&cvd->modelData.currMem);

	if(iDRet > SOLVER_SUCCESS_END){
		ITI_int i;
		iRet = SOLVER_SUCCESS_CONTINUE;
		 
		for(i=0; i<pPart->curr->size.ix; i++)
			pPart->curr->xChanged[i] = 1;
	}
	else{
		if(checkInvalidateDerivatives(pid, pData, cvc->xdot, cvc->xdot_tE1)){
			iRet = SOLVER_SUCCESS_CONTINUE;
		}
	}

	 
	if(cvc->contextBase.bZeroFunc)
		iRet = SOLVER_SUCCESS_CONTINUE;

	 
	if(iRet == SOLVER_SUCCESS_END){
		if(CheckForZeroCrossing(pPart->curr)){
			iRet = SOLVER_SUCCESS_CONTINUE;
		}
	}

#ifdef __TRACE_INFLUENCED_STATES
	if (iRet != SOLVER_SUCCESS_END){
		ITI_int i;
		char strMsg[16384];
		char strState[1024];
		strcpy(strMsg, "");
		for(i=0; i<pPart->curr->size.ix; i++){
			if(cvc->xChanged[i]){
				sprintf(strState, "%lu ", (unsigned long)i);
				strcat(strMsg, strState);
			}
		}
		pPart->transient->sInfo.trace(0,0, "Influenced States:\n", strMsg, &pPart->transient->sInfo);
	}
#endif

	return iRet;
}

static ITI_SolverState calcNextHitTime(size_t pid, void* pData, ITI_real tCurr){
	ITI_SolverData* cvd = (ITI_SolverData*)pData;
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)cvd->sc[pid];
	ITI_Partition *pPart = &cvd->partition[pid];
	ITI_SolverState iRet = SOLVER_SUCCESS_END;
	ITI_int iHit;

	if (!pPart->transient->sInfo.isTerminal) {
		if (pid == 0) {
			ITI_int i;
			if (!cvc->contextBase.hitIsSample) {
				cvc->contextBase.tHitClock = 1E300;
			}
			for (i = 0; i < pPart->curr->size.ipart; i++) {
				if ((pPart->transient->sInfo.timeTriggeredClock[i].nextTickTime > tCurr) && (pPart->transient->sInfo.timeTriggeredClock[i].nextTickTime < cvc->contextBase.tHitClock)) {
					cvc->contextBase.tHitClock = pPart->transient->sInfo.timeTriggeredClock[i].nextTickTime;
				}
			}
		}
		iHit = cvc->contextBase.isvMax;
		if(cvc->contextBase.hitIsSample && (cvc->contextBase.isvMax > 0)){
			ITI_int i;
			 
			cvc->contextBase.ui_dtHit = cvc->contextBase.ui_dt_Max;
			for (i = 0; i < cvc->contextBase.isvMax; i++){
				if(ITI_bui_lt(&cvc->contextBase.timeEventCounter[i], &cvc->contextBase.ui_dtHit)){
					iHit = i;
					cvc->contextBase.ui_dtHit = cvc->contextBase.timeEventCounter[i];
				}
			}
			ITI_bi_plus(&cvc->contextBase.i_tHit, &cvc->contextBase.ui_dtHit);
			cvc->contextBase.tHitSample = ITI_bi_getreal(&cvc->contextBase.i_tHit, cvd->ss.dtMin);
			if(cvd->ss.bStopAtStop && iHit == (cvc->contextBase.isvMax-1))  
				cvc->nextTimeEventStops = 1;
			else
				cvc->nextTimeEventStops = 0;
			cvc->contextBase.hitIsSample = ITI_false;	 
		}
		else{
			cvc->contextBase.tHit = ITI_bui_getreal(&cvc->contextBase.ui_dt_Max, cvd->ss.dtMin);
		}
	}
	return iRet;
}

static ITI_SolverState checkInvalidateDerivatives(size_t pid, void* pData, const N_Vector nv1,  const N_Vector nv2){
	ITI_SolverData* cvd = (ITI_SolverData*)pData;
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)cvd->sc[pid];
	ITI_Partition *pPart = &cvd->partition[pid];
	
	ITI_SolverState iRet = SOLVER_SUCCESS_END;
	ITI_int i;

	ITI_real* v1 = NV_DATA_S(nv1);
	ITI_real* v2 = NV_DATA_S(nv2);
	for(i=0; i<pPart->curr->size.ix; i++){
		ITI_real dv = v1[i]-v2[i];
		if(fabs(dv) > cvd->ss.absTol){
			pPart->curr->xChanged[i] = 1;
			iRet = SOLVER_SUCCESS_CONTINUE;
		}
		else{
			if(v1[i]!=0){
				if(fabs(dv/v1[i]) > cvd->ss.relTol){
					pPart->curr->xChanged[i] = 1;
					iRet = SOLVER_SUCCESS_CONTINUE;
				}
			}
		}
	}
	return iRet;
}

#define CVODE_SERIALIZE_STRING(op, storageDataPtr, value, mem_size)\
	switch (op) {\
	case SUNDIALS_SERIALIZATION_OPERATION_SERIALIZE:\
		memcpy(storageDataPtr, value, (int)(strlen(value) + 1));\
		break;\
	case SUNDIALS_SERIALIZATION_OPERATION_DESERIALIZE:\
		memcpy(value, storageDataPtr, (int)(strlen(value) + 1)); \
		break;\
	case SUNDIALS_SERIALIZATION_OPERATION_SIZE:\
		mem_size += (int)(strlen(value) + 1);\
		break;\
	}

static long int SerializeModelPrivate(int op, void *data, void **storageDataPtr)
{
	long int i, memSize = 0;
	ITI_int intVal;
	ITI_uint k, size_big_uint;
	ITI_SolverData *cvd = (ITI_SolverData *)data;
	size_t pid = 0;
	ITI_Partition *pPart = &cvd->partition[pid];
	ITI_PartFunctions* pPartFunctions = &cvd->model.partFunctions[pid];
	ITI_CVodeContext *cvc = (ITI_CVodeContext*)(cvd->sc[pid]);

   
	CVODE_SERIALIZE_A(op, ITI_real, *storageDataPtr, pPart->curr->t, memSize)
	for (i = 0; i < pPart->curr->size.ix; i++)
		CVODE_SERIALIZE_A(op, ITI_real, *storageDataPtr, pPart->curr->x[i], memSize)


	for (i = 0; i < pPart->curr->size.ibx; i++)
#ifdef ITI_COMP_SIM
		CVODE_SERIALIZE_A(op, ITI_real, *storageDataPtr, *pPart->curr->bx[i], memSize)
#else
		CVODE_SERIALIZE_A(op, ITI_real, *storageDataPtr, pPart->curr->bx[i], memSize)
#endif




	for (i = 0; i < pPart->curr->size.iu_real; i++)
#ifdef ITI_COMP_SIM
		CVODE_SERIALIZE_A(op, ITI_real, *storageDataPtr, *(pPart->curr->u.realData[i]), memSize)
#else
		CVODE_SERIALIZE_A(op, ITI_real, *storageDataPtr, pPart->curr->u.realData[i], memSize)
#endif
	for (i = 0; i < pPart->curr->size.iu_int; i++)
		CVODE_SERIALIZE_A(op, ITI_int, *storageDataPtr, pPart->curr->u.intData[i], memSize)
	for (i = 0; i < pPart->curr->size.iu_str; i++)
		CVODE_SERIALIZE_STRING(op, *storageDataPtr, pPart->curr->u.strData[i], memSize)
	for (i = 0; i < pPart->curr->size.ip_real; i++)
#ifdef ITI_COMP_SIM
		CVODE_SERIALIZE_A(op, ITI_real, *storageDataPtr, *(pPart->curr->p.realData[i]), memSize)
#else
		CVODE_SERIALIZE_A(op, ITI_real, *storageDataPtr, pPart->curr->p.realData[i], memSize)
#endif
	for (i = 0; i < pPart->curr->size.ip_int; i++)
		CVODE_SERIALIZE_A(op, ITI_int, *storageDataPtr, pPart->curr->p.intData[i], memSize)
	for (i = 0; i < pPart->curr->size.ip_str; i++)
		CVODE_SERIALIZE_STRING(op, *storageDataPtr, pPart->curr->p.strData[i], memSize)
 
	for (i = 0; i < pPart->curr->size.iz_real; i++)
#ifdef ITI_COMP_SIM
		CVODE_SERIALIZE_A(op, ITI_real, *storageDataPtr, *pPart->curr->pre_z.realData[i], memSize)
#else
		CVODE_SERIALIZE_A(op, ITI_real, *storageDataPtr, pPart->curr->pre_z.realData[i], memSize)
#endif
	for (i = 0; i < pPart->curr->size.iz_int; i++)
		CVODE_SERIALIZE_A(op, ITI_int, *storageDataPtr, pPart->curr->pre_z.intData[i], memSize)
	for (i = 0; i < pPart->curr->size.iz_str; i++)
		CVODE_SERIALIZE_STRING(op, *storageDataPtr, pPart->curr->pre_z.strData[i], memSize)



	for (i = 0; i < pPart->curr->size.izf; i++)
		CVODE_SERIALIZE_A(op, ITI_real, *storageDataPtr, pPart->curr->pre_zf[i], memSize)
	for (i = 0; i < pPart->curr->size.izf; i++)  
		CVODE_SERIALIZE_A(op, ITI_uchar, *storageDataPtr, pPart->curr->czf[i], memSize)
	for (i = 0; i < pPart->curr->size.izf; i++)  
		CVODE_SERIALIZE_A(op, ITI_uchar, *storageDataPtr, pPart->curr->ezf[i], memSize)
	for (i = 0; i < pPart->curr->size.izf; i++)  
		CVODE_SERIALIZE_A(op, ITI_int, *storageDataPtr, pPart->curr->cszf[i], memSize)
	for (i = 0; i < pPart->curr->size.izf; i++)  
		CVODE_SERIALIZE_A(op, ITI_int, *storageDataPtr, pPart->curr->oszf[i], memSize)
	for (i = 0; i < pPart->curr->size.izf; i++)  
		CVODE_SERIALIZE_A(op, ITI_int, *storageDataPtr, pPart->curr->szf[i], memSize)
	for (i = 0; i < pPart->curr->size.izf; i++)  
		CVODE_SERIALIZE_A(op, ITI_int, *storageDataPtr, pPart->curr->relzf[i], memSize)
	for (i = 0; i < pPart->curr->size.izf; i++)  
		CVODE_SERIALIZE_A(op, ITI_real, *storageDataPtr, pPart->curr->epszf[i], memSize)
	for (i = 0; i < pPart->curr->size.izf; i++)  
		CVODE_SERIALIZE_A(op, ITI_real, *storageDataPtr, pPart->curr->e1zf[i], memSize)
	for (i = 0; i < pPart->curr->size.izf; i++)  
		CVODE_SERIALIZE_A(op, ITI_real, *storageDataPtr, pPart->curr->e2zf[i], memSize)
	for (i = 0; i < pPart->curr->size.izf; i++)  
		CVODE_SERIALIZE_A(op, ITI_uint, *storageDataPtr, pPart->curr->sczf[i], memSize)



	for (i = 0; i < pPart->curr->size.ics; i++) {
		ITI_uint j;
		for (j = 0; j < pPartFunctions->seqCsSizes[i]; j++)
			CVODE_SERIALIZE_A(op, ITI_int, *storageDataPtr, pPart->curr->cs[i].pSeqCs[j].iPos, memSize)
	}
	for (i = 0; i < pPart->curr->size.ihcs; i++) {
		ITI_uint j;
		for (j = 0; j < pPartFunctions->seqCsSizes[i]; j++) {
			CVODE_SERIALIZE_A(op, ITI_int, *storageDataPtr, pPart->curr->cs[i].pSeqCs[j].iPos, memSize)  
			CVODE_SERIALIZE_A(op, ITI_real, *storageDataPtr, pPart->curr->hcs[i].lastY, memSize)
			CVODE_SERIALIZE_A(op, ITI_int, *storageDataPtr, pPart->curr->hcs[i].direction, memSize)
		}
	}





	for (i = 0; i < pPart->curr->size.idb; i++) {
		ITI_int j;
		CVODE_SERIALIZE_A(op, ITI_int, *storageDataPtr, pPart->curr->db[i].size, memSize)
		CVODE_SERIALIZE_A(op, enum DelayValueType, *storageDataPtr, pPart->curr->db[i].valType, memSize)
		CVODE_SERIALIZE_A(op, ITI_int, *storageDataPtr, pPart->curr->db[i].lastPosIn, memSize)
		CVODE_SERIALIZE_A(op, ITI_int, *storageDataPtr, pPart->curr->db[i].lastPosOut, memSize)
		for (j = 0; j < pPart->curr->db[i].size; j++)
			CVODE_SERIALIZE_A(op, ITI_real, *storageDataPtr, pPart->curr->db[i].times[j], memSize)
		if (pPart->curr->db[i].valType == DelayValueType_Real) {
			for (j = 0; j < pPart->curr->db[i].size; j++)
				CVODE_SERIALIZE_A(op, ITI_real, *storageDataPtr, pPart->curr->db[i].realValues[j], memSize)
		} else {
			for (j = 0; j < pPart->curr->db[i].size; j++)
				CVODE_SERIALIZE_A(op, ITI_int, *storageDataPtr, pPart->curr->db[i].intValues[j], memSize)
		}
		CVODE_SERIALIZE_A(op, ITI_int, *storageDataPtr, pPart->curr->db[i].iL, memSize)
		CVODE_SERIALIZE_A(op, ITI_int, *storageDataPtr, pPart->curr->db[i].iR, memSize)
		CVODE_SERIALIZE_A(op, ITI_int, *storageDataPtr, pPart->curr->db[i].iSearch, memSize)
		CVODE_SERIALIZE_A(op, ITI_int, *storageDataPtr, pPart->curr->db[i].iNewVal, memSize)
	}



	CVODE_SERIALIZE_A(op, ITI_uint, *storageDataPtr, pPart->curr->incCount, memSize)
	for (k = 0; k < pPart->curr->incCount; k++)
		CVODE_SERIALIZE_A(op, ITI_uint, *storageDataPtr, pPart->curr->stateIncidence[k], memSize)









































	switch (op) {
	case SUNDIALS_SERIALIZATION_OPERATION_SERIALIZE:
		size_big_uint = ITI_big_uint_size;
		SERIALIZE(ITI_int, *storageDataPtr, pPart->curr->size.isv)
		SERIALIZE(ITI_uint, *storageDataPtr, size_big_uint)
		for (i = 0; i < pPart->curr->size.isv; i++)
			for (k = 0; k < size_big_uint; k++)
				SERIALIZE(ITI_uint, *storageDataPtr, cvc->contextBase.timeEventCounter[i].v[k]);
		break;
	case SUNDIALS_SERIALIZATION_OPERATION_DESERIALIZE:
		DESERIALIZE(ITI_int, *storageDataPtr, intVal)
		assert(intVal == pPart->curr->size.isv);
		DESERIALIZE(ITI_uint, *storageDataPtr, size_big_uint)
		assert(size_big_uint == ITI_big_uint_size);
		for (i = 0; i < pPart->curr->size.isv; i++)
			for (k = 0; k < size_big_uint; k++)
				DESERIALIZE(ITI_uint, *storageDataPtr, cvc->contextBase.timeEventCounter[i].v[k]);
		break;
	case SUNDIALS_SERIALIZATION_OPERATION_SIZE:
		memSize += sizeof(ITI_int) + (1 + pPart->curr->size.isv * ITI_big_uint_size) * sizeof(ITI_uint);
		break;
	}
	return memSize;
}

long int ModelSerializationSize(void *data)
{
  return SerializeModelPrivate(SUNDIALS_SERIALIZATION_OPERATION_SIZE, data, NULL);
}

long int ModelSerialize(void *data, void **storageDataPtr)
{
  return SerializeModelPrivate(SUNDIALS_SERIALIZATION_OPERATION_SERIALIZE, data, storageDataPtr);
}

long int ModelDeserialize(void *data, void **storageDataPtr)
{
  return SerializeModelPrivate(SUNDIALS_SERIALIZATION_OPERATION_DESERIALIZE, data, storageDataPtr);
}
