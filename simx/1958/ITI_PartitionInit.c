/**
 * ITI_PartitionInit.c
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#include "ITI_PartitionInit.h"
#include "ITI_PartitionInterface.h"
#include "ITI_PartitionEval.h"

#ifdef ITI_COMP_SIM
#include "ITI_NonLinSolver.h"
#else
#include "ITI_NonLinSolver.h"
#endif

#include "ITI_ClockEval.h"

ITI_SolverState InitializePartitionComplete(size_t pid, ITI_SolverData* sd) {
	ITI_SolverState iRet;
	InitializePartitionVars(pid, sd);
	iRet = InitializePartition(pid, sd);
	if (iRet == SOLVER_SUCCESS_CONTINUE) {
		iRet = InitializeConditionsPartition(pid, sd);
	}
	if (iRet == SOLVER_SUCCESS_CONTINUE) {
		iRet = InitializeConditionsPartitionFinish(pid, sd);
	}
	 
	




	 

	return iRet;
}

ITI_SolverState InitializeConditionsPartitionComplete(size_t pid, ITI_SolverData* sd) {
	ITI_SolverState iRet = InitializeConditionsPartition(pid, sd);
	if (iRet == SOLVER_SUCCESS_CONTINUE) {
		iRet = InitializeConditionsPartitionFinish(pid, sd);
	}
	return iRet;
}

void InitializePartitionVars(size_t pid, ITI_SolverData* sd) {
	ITI_int i;
	ITI_uint j;
	ITI_Partition *pPart = &sd->partition[pid];
	ITI_PartFunctions* pPartFunctions = &sd->model.partFunctions[pid];

	if (pid == 0)
		pPart->curr->t = sd->ss.tStart;

	 
	for (i = 0; i < pPart->curr->size.iv_real; i++) {
#ifdef ITI_COMP_SIM
		*(pPart->curr->v.realData[i]) = 0.0;
#else
		pPart->curr->v.realData[i] = 0.0;
#endif
	}

	for (i = 0; i < pPart->curr->size.ibx; i++) {
#ifdef ITI_COMP_SIM
		*(pPart->curr->bx[i]) = 0.0;
#else
		pPart->curr->bx[i] = 0.0;
#endif
	}

	for (i = 0; i < pPart->curr->size.iv_int; i++) {
		pPart->curr->v.intData[i] = 0;
	}

	for (i = 0; i < pPart->curr->size.iv_str; i++) {
		if (&pPart->curr->v.strData[i])
		{
			if (pPart->curr->v.strSize[i] < 1)
			{
				pPart->curr->v.strData[i] = sd->model.GetStringMemory(&sd->modelData.strMem, 1);
				pPart->curr->v.strSize[i] = 1;
			}
			strcpy(pPart->curr->v.strData[i], "");
		}
	}

	for (i = 0; i < pPart->curr->size.iz_real; i++) {
#ifdef ITI_COMP_SIM
		*(pPart->curr->pre_z.realData[i]) = 0.0;
		*(pPart->curr->z.realData[i]) = 0.0;
#else
		pPart->curr->pre_z.realData[i] = 0.0;
		pPart->curr->z.realData[i] = 0.0;
#endif
	}

	for (i = 0; i < pPart->curr->size.iz_int; i++) {
		pPart->curr->pre_z.intData[i] = 0;
		pPart->curr->z.intData[i] = 0;
	}

	for (i = 0; i < pPart->curr->size.iz_str; i++) {
		if (&pPart->curr->z.strData[i]) {
			if (pPart->curr->z.strSize[i] < 1) {
				pPart->curr->z.strData[i] = sd->model.GetStringMemory(&sd->modelData.strMem, 1);
				pPart->curr->z.strSize[i] = 1;
			}
			strcpy(pPart->curr->z.strData[i], "");
		}
		if (&pPart->curr->pre_z.strData[i]) {
			if (pPart->curr->pre_z.strSize[i] < 1) {
				pPart->curr->pre_z.strData[i] = sd->model.GetStringMemory(&sd->modelData.strMem, 1);
				pPart->curr->pre_z.strSize[i] = 1;
			}
			strcpy(pPart->curr->pre_z.strData[i], "");
		}
	}

	for (i = 0; i < pPart->curr->size.iclocksv_real; i++) {
#ifdef ITI_COMP_SIM
		*(pPart->curr->clocksv.realData[i]) = 0.0;
#else
		pPart->curr->clocksv.realData[i] = 0.0;
#endif
	}

	for (i = 0; i < pPart->curr->size.iclocksv_int; i++) {
		pPart->curr->clocksv.intData[i] = 0;
	}

	for (i = 0; i < pPart->curr->size.iclocksv_str; i++) {
		if (&pPart->curr->clocksv.strData[i])
		{
			if (pPart->curr->clocksv.strSize[i] < 1)
			{
				pPart->curr->clocksv.strData[i] = sd->model.GetStringMemory(&sd->modelData.strMem, 1);
				pPart->curr->clocksv.strSize[i] = 1;
			}
			strcpy(pPart->curr->clocksv.strData[i], "");
		}
	}

	for (i = 0; i < pPart->curr->size.icset; i++) {
		for (j = 0; j < pPart->curr->cSet[i].nYScale; j++) {
			pPart->curr->cSet[i].pYScale[j].bScaleInitialized = 0;
		}
	}

	for (i = 0; i < pPart->curr->size.icnd; i++) {
		for (j = 0; j < pPart->curr->cNd[i].nYScale; j++) {
			pPart->curr->cNd[i].pYScale[j].bScaleInitialized = 0;
		}
	}

	for (i = 0; i < pPart->curr->size.ihcs; i++) {
		pPart->curr->hcs[i].bInitialized = 0;
	}

	for (i = 0; i < pPart->curr->size.ix; i++) {
		pPart->curr->xdot[i] = 0.0;
		pPart->curr->x[i] = 0.0;
	}

	 
	InitZFData(pPart->curr);

#ifdef ITI_COMP_SIM
	InitEventCounters(&sd->stat[pid], pPart->curr->size.izf, pPart->curr->size.iz_real + pPart->curr->size.iz_int + pPart->curr->size.iz_str);
#endif

	 
	SetDelayBufferData(pPart->curr->db, pPart->curr->size.idb);
	InitAssertData(&pPart->curr->sInfo.assertData);

	SetDPBlockData(pPart->curr->iDPbd, pPartFunctions->DPBlockSizes, pPart->curr->size.iDPB);

	 
	if (sd->ss.gltol == 0.0) {
		sd->ss.gltol = 1e-6;
	}
	else {
		if (sd->ss.gltol >= sd->ss.relTol || sd->ss.gltol >= sd->ss.absTol) {
			ITI_char strMsg[1024];
			double tol = min(sd->ss.relTol, sd->ss.absTol) / 10.;
			sprintf(strMsg, "The tolerance for solving implicit blocks (%g) must be smaller than absolute and relative tolerance. It is reduced to %g.", sd->ss.gltol, tol);
			pPart->transient->sInfo.trace(0, 1, "Warning", strMsg, (void*)&pPart->transient->sInfo);
			sd->ss.gltol = tol;
		}
	}

	pPart->curr->sInfo.allowJump = ITI_false;
	pPart->curr->sInfo.allowBlockJump = ITI_false;
	pPart->curr->sInfo.isInitial = ITI_true;
	pPart->curr->sInfo.isTerminal = ITI_false;
	pPart->curr->sInfo.isTerminate = ITI_false;
	pPart->curr->sInfo.strAnalysesType = "residuals";
	pPart->curr->sInfo.strAnalysisTypeDetail = "event";
	pPart->curr->sInfo.isEvent = ITI_true;
	pPart->curr->sInfo.isFirstEventStep = ITI_true;
	pPart->curr->sInfo.applyHysteresis = ITI_false;
	pPart->curr->sInfo.tracingAllowed = ITI_true;
	pPart->curr->sInfo.bDPAllowed = ITI_true;
	pPart->curr->sInfo.bDPRequired = ITI_false;
	pPart->curr->sInfo.bSolverNeedsReset = ITI_false;
	pPart->curr->sInfo.bDPHappened = ITI_false;
	pPart->curr->sInfo.dt = 0.0;
	pPart->curr->tLastStep = 0.0;
	pPart->curr->sInfo.isEventClock = ITI_false;
	pPart->curr->sInfo.strTrace[0] = '\0';

	SetBlockSettings(pPart->curr->size.numBlocks, pPart->curr->ibd, sd->ss.gltol, sd->ss.linSolv, sd->ss.ignoreMinMax);
	ResetBlockData(pPart->curr->size.numBlocks, pPart->curr->ibd, pPartFunctions->blockSizes);

	pPart->curr->sInfo.isEmbed = ITI_false;
	pPart->curr->sInfo.bAssertOn = sd->ss.bAssertOn;
	pPart->curr->sInfo.bAssertTraceOn = sd->ss.bAssertTraceOn;
	pPart->curr->sInfo.bAssertActive = sd->ss.bAssertOn;
	pPart->curr->sInfo.bEventTriggered = ITI_false;
	pPart->curr->sInfo.bUseSimpleHomotopy = ITI_false;

	 
	if (pid == 0) {
		if (pPart->curr->sInfo.timeTriggeredClock) {
			for (i = 0; i < GetNumClockedPartitions(pPart); i++) {
				pPart->curr->sInfo.timeTriggeredClock[i].bTick = 0;
			}
		}
	}
	ResetSolverStatistics(&sd->stat[pid], pPart->curr->size.ix);

	 
	 
	pPart->curr->szf = pPart->curr->cszf;

	 
	 
	if (sd->ss.bStopAtStop) {
		if (sd->ss.dtMin > sd->ss.tStop - sd->ss.tStart && sd->ss.tStop > sd->ss.tStart) {
			ITI_char strMsg[1024];
			sd->ss.dtMin = sd->ss.tStop - sd->ss.tStart;
			sprintf(strMsg, "dtMin is reduced to tStop - tStart = %g.", sd->ss.dtMin);
			pPart->transient->sInfo.trace(0, Warning, "dtMin must not be greater than tStop - tStart.", strMsg, &pPart->transient->sInfo);
		}
	}
	sd->stat[pid].dblhTmp = sd->ss.dtMin;  
#ifdef ITI_COMP_SIM
	UpdateStates(pPartFunctions->dataX, pPart->curr->size.iSimX_X, pPart->curr->ws, pPart->curr->x);
#endif
	ResetDataArrays(pPart->curr, pPart->curr->size.iarr, pPartFunctions->arrayData);
}

ITI_SolverState InitializePartition(size_t pid, ITI_SolverData* sd) {
	ITI_Partition *pPart = &sd->partition[pid];
	ITI_PartFunctions* pPartFunctions = &sd->model.partFunctions[pid];

	sd->sc[pid]->action = SOLVER_INITIALIZE;
	sd->sc[pid]->state = SOLVER_SUCCESS_CONTINUE;

	sd->sc[pid]->bTerminateRequired = ITI_false;
	sd->sc[pid]->bTimeEvent = ITI_false;
	sd->sc[pid]->hitIsSample = ITI_false;
	sd->sc[pid]->hitIsClock = ITI_false;
	sd->sc[pid]->bZeroFunc = ITI_false;
	sd->sc[pid]->bDPHappenedInEventiteration = ITI_false;

	if (pid == 0 && sd->sc[pid]->OnSetInputs) {
		if (sd->sc[pid]->OnSetInputs(sd, sd->ss.tStart, &pPart->curr->u) != 0) {
			HandleWarnings(&pPart->transient->sInfo);
			sd->sc[pid]->state = SOLVER_ERROR_IN_ON_SET_INPUTS;
			return sd->sc[pid]->state;
		}
	}

	 
	if (sd->sc[pid]->InitializePrepareSolver) {
		if (sd->sc[pid]->InitializePrepareSolver(pid, sd) != SOLVER_SUCCESS_CONTINUE) {
			HandleWarnings(&pPart->transient->sInfo);
			pPart->transient->sInfo.trace(0, 4, "Solver Error", "Initialization of solver failed.", (void*)&pPart->transient->sInfo);
			sd->sc[pid]->state = SOLVER_ERROR_IN_INITIALIZATION;
			return sd->sc[pid]->state;
		}
	}
	 
	if (pid == 0) {
		if (pPartFunctions->InitializeConstants(pPart, &sd->modelData) != SOLVER_SUCCESS_END) {
			HandleWarnings(&pPart->transient->sInfo);
			pPart->transient->sInfo.trace(0, 4, "Solver Error", "Initialization of constants failed.", (void*)&pPart->transient->sInfo);
			sd->sc[pid]->state = SOLVER_ERROR_IN_INITIALIZATION;
			return sd->sc[pid]->state;
		}
		if (pPartFunctions->InitializeParameterDependent(pPart, &sd->modelData) != SOLVER_SUCCESS_END) {
			HandleWarnings(&pPart->transient->sInfo);
			pPart->transient->sInfo.trace(0, 4, "Solver Error", "Initialization of dependent parameters failed.", (void*)&pPart->transient->sInfo);
			sd->sc[pid]->state = SOLVER_ERROR_IN_INITIALIZATION;
			return sd->sc[pid]->state;
		}
		if (pPartFunctions->InitializeTunableParameter(pPart, &sd->modelData) != SOLVER_SUCCESS_END) {
			HandleWarnings(&pPart->transient->sInfo);
			pPart->transient->sInfo.trace(0, 4, "Solver Error", "Initialization of tunable parameters failed.", (void*)&pPart->transient->sInfo);
			sd->sc[pid]->state = SOLVER_ERROR_IN_INITIALIZATION;
			return sd->sc[pid]->state;
		}
	}

	 
	if (pPartFunctions->Initialize(pPart, &sd->modelData) != SOLVER_SUCCESS_END) {
		HandleWarnings(&pPart->transient->sInfo);
		pPart->transient->sInfo.trace(0, 4, "Solver Error", "Initialization of model failed.", (void*)&pPart->transient->sInfo);
		sd->sc[pid]->state = SOLVER_ERROR_IN_INITIALIZATION;
		return sd->sc[pid]->state;
	}
	pPart->curr->sInfo.bInitializeFuncCalled = ITI_true;

	 
#ifdef ITI_COMP_SIM
	if (ExceptWrapper2(pPartFunctions->SynchOutputs, pPart, &sd->modelData) != SOLVER_SUCCESS_END) {
		HandleWarnings(&pPart->transient->sInfo);
		pPart->transient->sInfo.trace(0, 4, "Solver Error", "Initialization of model failed during synchronization.", (void*)&pPart->transient->sInfo);
		sd->sc[pid]->state = SOLVER_ERROR_IN_INITIALIZATION;
		return sd->sc[pid]->state;
	}
#endif

	sd->model.ReleaseAllMemory(&sd->modelData.currMem);
	pPart->curr->szf = pPart->curr->oszf;
	if (!sd->ss.ignoreMinMax) {
		FillStateMinMax(pPart, pPartFunctions->stateAttributes, pPart->curr->size.numStateAttr, sd->ss.absTol);
	}

	 
	if (pPart->curr->sInfo.isTerminate) {
		HandleWarnings(&pPart->transient->sInfo);
		sd->sc[pid]->bTerminateRequired = ITI_true;
		sd->sc[pid]->state = SOLVER_TERMINATED;
		return sd->sc[pid]->state;
	}

	 
	Update_pre_zf(pPart->curr->zf, pPart->curr->pre_zf, pPart->curr->size.izf);
	Update_oszf(pPart->curr);

#ifdef ITI_COMP_SIM
	 
	if (sd->ss.useInitFile) {
		ITI_int i;
		for (i = 0; i < pPart->curr->size.ix; i++) {
			*pPart->curr->ws.px[i] = pPart->curr->x[i];
		}
	}
#endif

	 
	sd->stat->iValidSteps = 0;
	sd->stat->iRhsCalls = 0;
	sd->stat->iRoots = 0;
	sd->stat->iTimeEvents = 0;

	return SOLVER_SUCCESS_CONTINUE;
}

ITI_SolverState InitializeConditionsPartition(size_t pid, ITI_SolverData* sd) {
	ITI_Partition *pPart = &sd->partition[pid];
	ITI_PartFunctions* pPartFunctions = &sd->model.partFunctions[pid];

	ITI_EmbeddingData hom;
	ITI_EmbeddingParams homp;
	ITI_SolverState iRet = SOLVER_SUCCESS_END;

	sd->sc[pid]->action = SOLVER_INITIALIZE_CONDITIONS;

#ifdef ITI_COMP_SIM
	 
	if (sd->ss.useInitFile) {
		ITI_int i;
		for (i = 0; i < pPart->curr->size.ix; i++) {
			pPart->curr->x[i] = *pPart->curr->ws.px[i];
		}
		Update_pre_z_data_ptr(pPart->curr, &sd->modelData);

		 
		if (!sd->ss.consistentInitialConditions) {
			Update_pre_zf(pPart->curr->zf, pPart->curr->pre_zf, pPart->curr->size.izf);
			Update_oszf(pPart->curr);
			pPartFunctions->AssignLastVar(pPart, &sd->modelData);
			UpdateDelayBuffers(pPart->curr->db, pPart->curr->size.idb);
			UpdateHystCurves(pPart->curr->hcs, pPart->curr->size.ihcs);
			HandleAssertWarnings(&pPart->curr->sInfo);
			UpdateStates(pPartFunctions->dataX, pPart->curr->size.iSimX_X, pPart->curr->ws, pPart->curr->x);
			return SOLVER_SUCCESS_CONTINUE;
		}
	}
#endif

	if (pPart->curr->size.bxind_lambda > -1) {
#ifdef ITI_COMP_SIM
		InitHomotopy(pPart->curr, &sd->modelData, &hom, &homp, pPart->curr->size.bxind_lambda, pPart->curr->size.bxind_homlast, pPart->curr->size.ihomres, sd->ss.absTol, sd->ss.relTol);
#else
		InitHomotopy(pPart->curr, &sd->modelData, &hom, &homp, pPart->curr->size.bxind_lambda, pPart->curr->size.bxind_homlast, pPart->curr->size.ihomres, sd->ss.absTol, sd->ss.relTol);
#endif
	}
	 
	pPart->curr->szf = pPart->curr->cszf;

	


	Update_oszf(pPart->curr);

	if (pid == 0 && sd->sc[pid]->OnSetInputs) {
		if (sd->sc[pid]->OnSetInputs(sd, sd->ss.tStart, &pPart->curr->u) != 0) {
			HandleWarnings(&pPart->transient->sInfo);
			sd->sc[pid]->state = SOLVER_ERROR_IN_ON_SET_INPUTS;
			return sd->sc[pid]->state;
		}
	}
#ifdef _BEGINEVENTSTEP
	TraceBeginEventStep(sd);
#endif
	if (pPart->curr->size.bxind_lambda > -1) {
#ifdef ITI_COMP_SIM
		CopyVarsA(pPart->curr->bx, hom.bx_tmp, 0, pPart->curr->size.bxind_homlast);
#else
		CopyVars(pPart->curr->bx, hom.bx_tmp, 0, pPart->curr->size.bxind_homlast);
#endif
	}

	pPart->transient->sInfo.bAssertActive = pPart->transient->sInfo.bAssertOn;
	pPart->transient->sInfo.bInitializeConditions = ITI_true;
	iRet = ExceptWrapper2((ModelFunc2)pPartFunctions->InitializeConditions, pPart, &sd->modelData);

#ifdef ITI_COMP_SIM
	if (ExceptWrapper2(pPartFunctions->SynchOutputs, pPart, &sd->modelData) > SOLVER_SUCCESS_END) {
		HandleWarnings(&pPart->transient->sInfo);
		pPart->transient->sInfo.trace(0, 4, "Solver Error", "Synchronization of initial values failed.", (void*)&pPart->transient->sInfo);
		sd->sc[pid]->state = SOLVER_ERROR_IN_INITIALIZATION;
		if (pPart->curr->size.bxind_lambda > -1) {
#ifdef ITI_COMP_SIM
			FreeHomotopy(&sd->modelData, &hom);
#else
			FreeHomotopy(&sd->modelData, &hom);
#endif
		}
		return sd->sc[pid]->state;
	}
#endif
	pPart->transient->sInfo.bInitializeConditions = ITI_false;
	sd->model.ReleaseAllMemory(&sd->modelData.currMem);
	pPart->curr->szf = pPart->curr->oszf;

	 
#ifdef TRACE_STATES
	TRACE_STATES
		traceStates(pid, pPart->curr, &sd->modelData, IDS_INIT_VALUE);
	END_TRACE
#endif
#ifdef TRACE_DER
		TRACE_DER
		traceDer(pid, pPart->curr, &sd->modelData, IDS_INIT_VALUE);
	END_TRACE
#endif

		if (pPart->curr->size.bxind_lambda > -1 && iRet > SOLVER_SUCCESS_END) {
			ResetWarningStack(&pPart->transient->sInfo);
			pPart->curr->sInfo.isTerminate = ITI_false;
#ifdef ITI_COMP_SIM
			Restore_z_data_ptr(pPart->curr, &sd->modelData, &pPart->curr->pre_z);
			iRet = CalcCurve(pPart->curr, &sd->modelData, &hom, &homp, &sd->model);
#else
			Restore_z_data(pPart->curr, &sd->modelData, &pPart->curr->pre_z);
			iRet = CalcCurve(pPart->curr, &sd->modelData, &hom, &homp, &sd->model);
#endif
		}

	if (iRet > SOLVER_SUCCESS_END) {
		HandleWarnings(&pPart->transient->sInfo);
		pPart->transient->sInfo.trace(0, 4, "Solver Error", "Computation of consistent initial values failed.", (void*)&pPart->transient->sInfo);
		sd->sc[pid]->state = SOLVER_ERROR_IN_INITIALIZATION;
		if (pPart->curr->size.bxind_lambda > -1) {
#ifdef ITI_COMP_SIM
			FreeHomotopy(&sd->modelData, &hom);
#else
			FreeHomotopy(&sd->modelData, &hom);
#endif
		}
		return sd->sc[pid]->state;
	}

	if (pPart->curr->size.bxind_lambda > -1) {
#ifdef ITI_COMP_SIM
		FreeHomotopy(&sd->modelData, &hom);
#else
		FreeHomotopy(&sd->modelData, &hom);
#endif
	}

	



	if (HandleSyncOutputs(pid, sd, SaveOutputsAllBit | SaveOutputsAtleastwithdtProtPrePostEventsBit | SaveOutputsAtleastwithdtProtAllEventStepsBit | SaveOutputsEquidistantPrePostEventsBit | SaveOutputsEquidistantAllEventStepsBit, (sd->ss.saveModeB != SaveOutputsEquidistantPrePostEventsBit) && (sd->ss.saveModeB != SaveOutputsEquidistantAllEventStepsBit)) != SOLVER_SUCCESS_END) {
		HandleWarnings(&pPart->transient->sInfo);
		pPart->transient->sInfo.trace(0, 4, "Solver Error", "Error during computation of outputs after computation of consistent initial values.", (void*)&pPart->transient->sInfo);
		sd->sc[pid]->state = SOLVER_ERROR_IN_INITIALIZATION_AFTERDISCONTINUITY;
		return sd->sc[pid]->state;
	}

#ifdef ITI_COMP_SIM
	 
	UpdateStates(pPartFunctions->dataX, pPart->curr->size.iSimX_X, pPart->curr->ws, pPart->curr->x);
#endif
	return SOLVER_SUCCESS_CONTINUE;
}

ITI_SolverState InitializeConditionsPartitionFinish(size_t pid, ITI_SolverData* sd) {
	ITI_Partition *pPart = &sd->partition[pid];
	ITI_PartFunctions* pPartFunctions = &sd->model.partFunctions[pid];
	ITI_SolverContextBase* sc = sd->sc[pid];
	size_t i = 0;
	ITI_int bDoEventiteration = ITI_false;
	ITI_SolverState iRet = SOLVER_SUCCESS_END;
	unsigned int iSaveMode;


#ifdef ITI_COMP_SIM
	 

	 
	bDoEventiteration |= Check_z_data_ptr(pPart->curr, sd->ss.relTol, sd->ss.absTol);
#else
	bDoEventiteration |= Check_z_data(pPart->curr, sd->ss.relTol, sd->ss.absTol);
#endif

	 
	if (pPart->curr->sInfo.isTerminate) {
		sd->sc[pid]->bTerminateRequired = ITI_true;
		sd->sc[pid]->state = SOLVER_TERMINATED;
		bDoEventiteration = ITI_true;
	}
	sd->model.ReleaseAllMemory(&sd->modelData.currMem);

	 
	if (pPart->curr->sInfo.bSolverNeedsReset) {
		pPart->curr->sInfo.bSolverNeedsReset = ITI_false;
		bDoEventiteration |= ITI_true;
	}

	 

	 
	if (pid == 0) {
		 
		if (GetNumClockedPartitions(pPart) > 1) {
			pPartFunctions->UpdateInferenceGraph(pPart, &sd->modelData);
			if (PerformInferenceGraph(pPart, &sd->modelData) == SOLVER_ERROR_IN_INITIALIZATION) {
				sd->sc[pid]->state = SOLVER_ERROR_IN_INITIALIZATION;
				return sd->sc[pid]->state;
			}
			pPartFunctions->LoadInferenceGraphResults(pPart, &sd->modelData);

#ifdef ITI_COMP_SIM
			 
			ExceptWrapper2(sd->model.partFunctions[pid].SynchOutputs, pPart, &sd->modelData);
#endif
			 
			if (CreatePartitionSolvers(sd) == SOLVER_ERROR) {
				HandleWarnings(&pPart->transient->sInfo);
				pPart->transient->sInfo.trace(0, 4, "Solver Error", "Error during initialization of partition solvers.", (void*)&pPart->transient->sInfo);
				sd->sc[pid]->state = SOLVER_ERROR_IN_INITIALIZATION;
				return sd->sc[pid]->state;
			}

			bDoEventiteration |= 1;
			
			 
			for (i = 1; i < (size_t)GetNumClockedPartitions(pPart); i++) {
				ITI_Partition *pClockedPart = &sd->partition[i];
				if (IsBasePartition(pClockedPart)) {
					continue;
				}
				
				InitializePartitionVars(i, sd);
				if (InitializePartition(i, sd) != SOLVER_SUCCESS_CONTINUE) {
					HandleWarnings(&pPart->transient->sInfo);
					pPart->transient->sInfo.trace(0, 4, "Solver Error", "Error during initialization of partition solvers.", (void*)&pPart->transient->sInfo);
					sd->sc[pid]->state = SOLVER_ERROR_IN_INITIALIZATION;
					return sd->sc[pid]->state;
				}
			}
		}

		 
		if (sd->sc[pid]->PrepareTimeEventHandlingSolver) {
			if (sd->sc[pid]->PrepareTimeEventHandlingSolver(pid, sd) < SOLVER_SUCCESS_END) {
				return sd->sc[pid]->state;
			}
		}

		 
		if (pPart->curr->sInfo.timeTriggeredClock) {
			pPart->curr->sInfo.timeTriggeredClock[0].nextTickTime = sd->ss.tStart - 1.0;
			for (i = 1; i < (size_t)GetNumClockedPartitions(pPart); i++) {
				ITI_Partition *pClockedPart = &sd->partition[i];
				if (IsBasePartition(pClockedPart) && !IsEventClock(pClockedPart)) {
					pPart->curr->sInfo.timeTriggeredClock[i].nextTickTime = sd->ss.tStart;
				}
				else {
					pPart->curr->sInfo.timeTriggeredClock[i].nextTickTime = sd->ss.tStart - 1.0;
				}
			}
		}

		if (SetTimeTriggeredClocks(sd, sd->ss.tStart) > 0) {
			sc->hitIsClock = ITI_true;
		}
	}

	Update_pre_zf(pPart->curr->zf, pPart->curr->pre_zf, pPart->curr->size.izf);
	Update_oszf(pPart->curr);
	 
	pPartFunctions->AssignDiscreteReal(pPart, &sd->modelData);
#ifdef ITI_COMP_SIM
	Update_pre_z_data_ptr(pPart->curr, &sd->modelData);
#else
	Update_pre_z_data(pPart->curr, &sd->modelData);
#endif
	pPartFunctions->AssignLastVar(pPart, &sd->modelData);
	UpdateHystCurves(pPart->curr->hcs, pPart->curr->size.ihcs);

	if (pid == 0 && sd->sc[pid]->OnSetInputs) {
		if (sd->sc[pid]->OnSetInputs(sd, sd->ss.tStart, &pPart->curr->u) != 0) {
			HandleWarnings(&pPart->transient->sInfo);
			sd->sc[pid]->state = SOLVER_ERROR_IN_ON_SET_INPUTS;
			return sd->sc[pid]->state;
		}
	}
	pPart->curr->sInfo.isInitial = ITI_false;
	pPart->curr->sInfo.isTerminal = ITI_false;
	pPart->curr->sInfo.strAnalysesType = "residuals";
	pPart->curr->sInfo.strAnalysisTypeDetail = "residuals";
	pPart->curr->sInfo.isEvent = ITI_true;
	pPart->curr->sInfo.isFirstEventStep = ITI_false;
	pPart->curr->sInfo.tracingAllowed = ITI_true;
	pPart->curr->sInfo.bDPAllowed = ITI_true;

	



	pPart->curr->sInfo.strAnalysisTypeDetail = "validInitialization";
	pPart->curr->sInfo.bEventTriggered = ITI_false;
	 
	pPart->curr->sInfo.isFirstRhsCall = ITI_true;
	sd->stat[pid].iRhsCalls++;
	 
	pPart->curr->szf = pPart->curr->cszf;
	if (ExceptWrapper2((ModelFunc2)pPartFunctions->CalcDerivatives, pPart, &sd->modelData) != SOLVER_SUCCESS_END) {
		pPart->curr->szf = pPart->curr->oszf;
		pPart->curr->sInfo.isFirstRhsCall = ITI_false;
		HandleWarnings(&pPart->transient->sInfo);
		 
		pPart->transient->sInfo.trace(0, 4, "Solver Error", "Error in first RHS call after initialization.", (void*)&pPart->transient->sInfo);
		sd->sc[pid]->state = SOLVER_ERROR_IN_INITIALIZATION;
		return sd->sc[pid]->state;
	}
	sd->model.ReleaseAllMemory(&sd->modelData.currMem);

	UpdateDelayBuffers(pPart->curr->db, pPart->curr->size.idb);

	 
	pPart->curr->szf = pPart->curr->oszf;
	Update_pre_zf(pPart->curr->zf, pPart->curr->pre_zf, pPart->curr->size.izf);
	Update_oszf(pPart->curr);

#ifdef ITI_COMP_SIM
	 
	Restore_z_data_ptr(pPart->curr, &sd->modelData, &pPart->curr->pre_z);
#else
	 
	Restore_z_data(pPart->curr, &sd->modelData, &pPart->curr->pre_z);
#endif
	pPart->curr->sInfo.isFirstRhsCall = ITI_false;
	pPart->curr->sInfo.isEvent = ITI_false;

	pPart->curr->sInfo.strAnalysisTypeDetail = "residuals";

	 
	if (!(bDoEventiteration || pPart->curr->sInfo.bEventTriggered || sd->sc[pid]->bTimeEvent)) {
		sd->stat[pid].iRhsCalls++;
		if (ExceptWrapper2((ModelFunc2)pPartFunctions->CalcDerivatives, pPart, &sd->modelData) != SOLVER_SUCCESS_END) {
			sd->sc[pid]->state = SOLVER_ERROR_IN_INITIALIZATION;
			HandleWarnings(&pPart->transient->sInfo);
			pPart->transient->sInfo.trace(0, 4, "Solver Error", "Error in first RHS call after initialization.", (void*)&pPart->transient->sInfo);
			return sd->sc[pid]->state;
		}
		sd->model.ReleaseAllMemory(&sd->modelData.currMem);
#ifdef ITI_COMP_SIM
		 
		bDoEventiteration |= Check_z_data_ptr(pPart->curr, pPart->transient->sInfo.sSettings->absTol, pPart->transient->sInfo.sSettings->relTol);
		 
		Restore_z_data_ptr(pPart->curr, &sd->modelData, &pPart->curr->pre_z);
#else
		 
		bDoEventiteration |= Check_z_data(pPart->curr, pPart->transient->sInfo.sSettings->absTol, pPart->transient->sInfo.sSettings->relTol);
		 
		Restore_z_data(pPart->curr, &sd->modelData, &pPart->curr->pre_z);
#endif
	}
	 
	sd->sc[pid]->bZeroFunc = Check_Update_oszf(pPart->curr);

	 
	 
	if (sd->sc[pid]->bPerformEventIterationInPartitionFinish &&
		(bDoEventiteration || pPart->curr->sInfo.bEventTriggered || sd->sc[pid]->bTimeEvent || sd->sc[pid]->bZeroFunc)) {
		if (sd->sc[pid]->bZeroFunc)
			sd->stat[pid].iZeros++;
		if (sd->sc[pid]->bTimeEvent)
			sd->stat[pid].iTimeEvents++;
		if (pPart->curr->sInfo.bEventTriggered)
			sd->stat[pid].iOtherEvents++;

		pPart->curr->sInfo.isInitial = ITI_true;
		sd->sc[pid]->state = EventIterationPartition(pid, sd);
		sd->sc[pid]->bZeroFunc = ITI_false;
		sd->sc[pid]->bTimeEvent = ITI_false;
		pPart->curr->sInfo.bEventTriggered = ITI_false;
	}

	if (sd->sc[pid]->bPerformEventIterationInPartitionFinish) {
		if (sd->sc[pid]->state < SOLVER_SUCCESS_END) {
			



			sd->sc[pid]->state = SOLVER_ERROR_IN_INITIALIZATION;
			return sd->sc[pid]->state;
		}

		pPart->curr->sInfo.strAnalysisTypeDetail = "validStep";
		if (ExceptWrapper2((ModelFunc2)pPartFunctions->ValidStep, pPart, &sd->modelData) > SOLVER_SUCCESS_END) {
			HandleWarnings(&pPart->transient->sInfo);
			sd->sc[pid]->state = SOLVER_ERROR;
			return sd->sc[pid]->state;
		}
		sd->model.ReleaseAllMemory(&sd->modelData.currMem);

		pPart->curr->sInfo.strAnalysisTypeDetail = "residuals";

		pPartFunctions->AssignLastVar(pPart, &sd->modelData);
		UpdateDelayBuffers(pPart->curr->db, pPart->curr->size.idb);
		UpdateHystCurves(pPart->curr->hcs, pPart->curr->size.ihcs);
		HandleAssertWarnings(&pPart->transient->sInfo);

		pPart->curr->sInfo.tracingAllowed = ITI_false;

#ifdef _SAVE_OUTPUTS
		Write2Stream(cvc->outputs, &cvc->t, (double*)pPart->curr->y.intData, pPart->curr->y.realData, 1, pPart->curr->size.iy_int, pPart->curr->size.iy_real, cvc->iPlaces, 15, 15);
#endif

#ifdef _SAVE_STATES
		{
			char fStates[MAX_PATH];
			sprintf(fStates, "states.txt");
			cvc->sStates = fopen(fStates, "w+");
			WriteStreamHeader(cvc->sStates, "t[s]", "x", "dx", 1, pPart->curr->size.ix, pPart->curr->size.ix);
			if (pPart->curr->t >= _TDEBUG)
			{
				Write2Stream(fsc->sStates, &pPart->curr->t, pPart->curr->x, pPart->curr->xdot, 1, pPart->curr->size.ix, pPart->curr->size.ix, 32, 32, 32);
				fflush(fsc->sStates);
			}
		}
#endif

#ifdef TRACE_STATES
		TRACE_STATES
			traceStates(pid, pPart->curr, &sd->modelData, IDS_INITIAL);
		END_TRACE
#endif
#ifdef TRACE_DER
			TRACE_DER
			traceDer(pid, pPart->curr, &sd->modelData, IDS_INITIAL);
		END_TRACE
#endif
	}

	if (sd->sc[pid]->InitializeFinishSolver) {
		sd->sc[pid]->InitializeFinishSolver(pid, sd);
	}

	if (pPart->curr->sInfo.isTerminate) {
		sd->sc[pid]->state = SOLVER_TERMINATED;
		iSaveMode = SaveOutputsLastValueBit;
	}
	else {
		iSaveMode = SaveOutputsAllBit | SaveOutputsEquidistantBit | SaveOutputsAtleastwithdtProtBit | SaveOutputsAtleastwithdtProtPostEventsBit | SaveOutputsAtleastwithdtProtPrePostEventsBit | SaveOutputsAtleastwithdtProtAllEventStepsBit | SaveOutputsEquidistantPostEventsBit | SaveOutputsEquidistantPrePostEventsBit | SaveOutputsEquidistantAllEventStepsBit | SaveOutputsAfterDoStepBit;
	}

	if (HandleSaveOutputs(pid, sd, iSaveMode, ITI_true) != SOLVER_SUCCESS_END) {
		HandleWarnings(&pPart->transient->sInfo);
		sd->sc[pid]->state = SOLVER_ERROR;
		return sd->sc[pid]->state;
	}
	pPart->transient->sInfo.isInitial = ITI_false;

	 
	if (sd->sc[pid]->OnValidEventStepSolver) {
		sd->sc[pid]->OnValidEventStepSolver(pid, sd);
	}
	return sd->sc[pid]->state;
}

ITI_SolverState PrepareTimeEventHandlingPartition(size_t pid, ITI_SolverData* sd) {
	ITI_Partition *pPart = &sd->partition[pid];
	ITI_PartFunctions* pPartFunctions = &sd->model.partFunctions[pid];

	ITI_int i = 0;
	ITI_bool iFound = ITI_false;
	ITI_real maxVal;
	ITI_char strMsg[1024];

	pPartFunctions->SampleFunction(pPart, &sd->modelData);

	iFound = 0;
	for (i = 0; i < pPart->curr->size.isv; i++) {
		if (pPart->curr->sampleTime[i].ts <= 0.0) {
			iFound = ITI_true;
			break;
		}
		if (pPart->curr->sampleTime[i].ts < sd->ss.dtMin) {
			sprintf(strMsg, "The model contains a sample time of %g s which is smaller than the minimum step size dtMin (%g s). The minimum step size is reduced to that value in order to represent the sample time precisely.", pPart->curr->sampleTime[i].ts, sd->ss.dtMin);
			pPart->transient->sInfo.trace(0, 1, "Warning", strMsg, (void*)&pPart->transient->sInfo);
			sd->ss.dtMin = pPart->curr->sampleTime[i].ts;
		}
		if ((pPart->curr->sampleTime[i].to > 0.0) && (pPart->curr->sampleTime[i].to < sd->ss.dtMin)) {
			sprintf(strMsg, "The model contains a sample offset time of %g s which is smaller than the minimum step size dtMin (%g s). The minimum step size is reduced to that value in order to represent the sample offset time precisely.", pPart->curr->sampleTime[i].to, sd->ss.dtMin);
			pPart->transient->sInfo.trace(0, 1, "Warning", strMsg, (void*)&pPart->transient->sInfo);
			sd->ss.dtMin = pPart->curr->sampleTime[i].to;
		}
	}
	if (iFound) {
		pPart->transient->sInfo.trace(0, 4, "Solver Error", "One of the sample times is zero or not constant. This is not allowed for this solver!", (void*)&pPart->transient->sInfo);
		sd->sc[pid]->state = SOLVER_ERROR_IN_INITIALIZATION;
		return sd->sc[pid]->state;
	}
	maxVal = ITI_bui_getrealMax(sd->ss.dtMin);
	for (i = 0; i < pPart->curr->size.isv; i++) {
		if (pPart->curr->sampleTime[i].ts > maxVal) {
			sprintf(strMsg, "The model contains a large sample time of %g s. This sample time cannot be expressed using the current setting for dtMin (%g s).\nThe biggest representable value is %g s. The sample time is reduced to that value.\nPlease consider an increasing of dtMin or a reduction of the sample time if this leads to wrong behavior.", pPart->curr->sampleTime[i].ts, sd->ss.dtMin, maxVal);
			pPart->transient->sInfo.trace(0, 1, "Warning", strMsg, (void*)&pPart->transient->sInfo);
			pPart->curr->sampleTime[i].ts = maxVal;
		}
		if (fabs(pPart->curr->sampleTime[i].to - sd->ss.tStart) > maxVal) {
			sprintf(strMsg, "The model contains a large sample offset time of %g s. This offset time value cannot be expressed using the current setting for dtMin (%g s).\nThe biggest representable value is %g s. The sample time is reduced to that value.\nPlease consider an increasing of dtMin or a reduction of the offset time if this leads to wrong behavior.", pPart->curr->sampleTime[i].to, sd->ss.dtMin, maxVal);
			pPart->transient->sInfo.trace(0, 1, "Warning", strMsg, (void*)&pPart->transient->sInfo);
			pPart->curr->sampleTime[i].to = maxVal + sd->ss.tStart;
		}
	}
	 
	for (i = 0; i < pPart->curr->size.isv; i++) {
		ITI_real tOffset = pPart->curr->sampleTime[i].to - sd->ss.tStart;
		if (tOffset < 0.0) {
			ITI_real tMod = fmod(fabs(tOffset) / pPart->curr->sampleTime[i].ts, 1.0);
			if (fabs(tMod) < 1e-12)
				tMod = 0.0;
			if (fabs(tMod - 1.0) < 1e-12)
				tMod = 1.0;
			if (tMod == 0.0 || tMod == 1.0)
				tOffset = 0.0;
			else
				tOffset = (1.0 - tMod) * pPart->curr->sampleTime[i].ts;
		}
		ITI_bui_setreal(&sd->sc[pid]->timeEventMax[i], fabs(tOffset), sd->ss.dtMin);
		sd->sc[pid]->timeEventCounter[i] = sd->sc[pid]->timeEventMax[i];
	}

	 
	if (sd->ss.bStopAtStop) {
		if ((sd->ss.tStop - sd->ss.tStart) > maxVal) {
			sprintf(strMsg, "The stop time (%g s) is larger than the maximum representable time value. Thus the stop time is reduced to the maximum value of %g s. To resolve the problem you can also try to sufficiently increase dtMin.", sd->ss.tStop, maxVal + sd->ss.tStart);
			pPart->transient->sInfo.trace(0, 1, "Solver Warning", strMsg, (void*)&pPart->transient->sInfo);
			sd->ss.tStop = maxVal + sd->ss.tStart;
		}

		if (sd->ss.tStop >= sd->ss.tStart)
			ITI_bui_setreal(&sd->sc[pid]->timeEventMax[pPart->curr->size.isv], fabs(sd->ss.tStop - sd->ss.tStart), sd->ss.dtMin);
		else {
			pPart->transient->sInfo.trace(0, 4, "Solver Error", "tStop must not be smaller than tStart.", (void*)&pPart->transient->sInfo);
			sd->sc[pid]->state = SOLVER_ERROR_IN_INITIALIZATION;
			return sd->sc[pid]->state;
		}
		sd->sc[pid]->timeEventCounter[pPart->curr->size.isv] = sd->sc[pid]->timeEventMax[pPart->curr->size.isv];
	}

	 
	for (i = 0; i < pPart->curr->size.isv; i++) {
		ITI_bui_setreal(&sd->sc[pid]->timeEventMax[i], pPart->curr->sampleTime[i].ts, sd->ss.dtMin);
		if (ITI_bui_is_zero(&sd->sc[pid]->timeEventCounter[i])) {
			sd->sc[pid]->bTimeEvent = ITI_true;
			sd->sc[pid]->hitIsSample = ITI_true;
			sd->sc[pid]->timeEventCounter[i] = sd->sc[pid]->timeEventMax[i];
			pPart->curr->sv[i] = 1;
		}
	}
	return SOLVER_SUCCESS_CONTINUE;
}

void ResetSolverStatistics(ITI_SolverStatistic* stat, ITI_int ix)
{
	stat->iOrder = 1;
	stat->iValidSteps = 0;
	stat->iZero = 0;
	stat->iZeros = 0;
	stat->iJac = 0;
	stat->iCodegen = 0;
	stat->iDecomp = 0;
	stat->iElim = 0;
	stat->dblChangeStepSize = 1;
	stat->iErrTestFailStep = 0;
	stat->iErrTestFails = 0;
	stat->iRhsCalls = 0;
	stat->ix = ix;
	stat->ngrp = 0;
	stat->iRoots = 0;
	stat->iTimeEvents = 0;
	stat->iTimeEventsReinit = 0;
	stat->iStateSelections = 0;
	stat->iOtherEvents = 0;
	stat->iRfcalls = 0;
	stat->calcDerivativesTime = 0;
}
