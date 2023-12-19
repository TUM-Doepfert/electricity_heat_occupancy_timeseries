/**
 * ITI_PartitionEval.c
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#include "ITI_PartitionEval.h"
#ifdef ITI_COMP_SIM
#include "ITI_Interface_Types.h"
#include "ITI_NonLinSolver.h"
#else
#include "ITI_NonLinSolver.h"
#endif
#include "ITI_ClockEval.h"
#include "ITI_PartitionInterface.h"

#ifdef ITI_COMP_SIM
#define TRACEFLAGS	(&sd->modelData.traceFlags)
#endif

ITI_SolverState EventIterationPartition(size_t pid, ITI_SolverData* sd) {
	ITI_SolverContextBase* sc = sd->sc[pid];
	ITI_Partition *pPart = &sd->partition[pid];
	ITI_PartFunctions* pPartFunctions = &sd->model.partFunctions[pid];

	ITI_int i;
	ITI_int iIter = 0;
	ITI_bool bRepeat = ITI_false;

	ITI_SolverState iRet = SOLVER_SUCCESS_END;
	ITI_bool bSolverNeedsReset = ITI_false;
	ITI_bool bCallValidStep = ITI_false;
	ITI_bool hitIsClock = (ITI_bool)sc->hitIsClock;

	sc->action = SOLVER_EVENT_ITERATION_PREPARE;
	if (sd->sc[pid]->OnBeforeEventStepSolver) {
		sd->sc[pid]->OnBeforeEventStepSolver(pid, sd);
	}

	 
	if (!pPart->curr->sInfo.isInitial) {
		bCallValidStep = ITI_true;
		if (HandleSaveOutputs(pid, sd, SaveOutputsAtleastwithdtProtPrePostEventsBit | SaveOutputsAtleastwithdtProtAllEventStepsBit | SaveOutputsEquidistantPrePostEventsBit | SaveOutputsEquidistantAllEventStepsBit, (sd->ss.saveModeB != SaveOutputsEquidistantPrePostEventsBit) && (sd->ss.saveModeB != SaveOutputsEquidistantAllEventStepsBit)) != SOLVER_SUCCESS_END)
		{
			HandleWarnings(&pPart->transient->sInfo);
			pPart->transient->sInfo.trace(0, 4, "Solver Error", "Error in computation of outputs during reinitialization after an Event", (void*)&pPart->transient->sInfo);
			sc->state = SOLVER_ERROR_IN_INITIALIZATION_AFTERDISCONTINUITY;
			return sc->state;
		}
	}

	pPart->curr->sInfo.bDPHappened = ITI_false;
	sc->bDPHappenedInEventiteration = ITI_false;
	pPart->curr->sInfo.bDPAllowed = ITI_true;
	pPart->curr->sInfo.bDPRequired = ITI_false;
	pPart->curr->sInfo.tracingAllowed = ITI_true;
	pPart->curr->sInfo.isEvent = ITI_true;
	pPart->curr->sInfo.isFirstEventStep = ITI_true;
	pPart->curr->sInfo.strAnalysisTypeDetail = "event";

	 
#ifdef ITI_COMP_SIM
	if (sc->bZeroFunc) {
		CountZeroCrossing(sd->stat[pid].zeroCrossingCount, pPart->curr);
	}
#endif

	if (!pPart->curr->sInfo.isInitial) {
		 
		pPartFunctions->AssignDiscreteReal(pPart, &sd->modelData);
		Update_real_pre_z_data(pPart->curr);
		pPart->curr->sInfo.applyHysteresis = ITI_true;
	}
	else {
		pPart->curr->sInfo.applyHysteresis = ITI_false;
		if (sc->hitIsSample) {
			 
			for (i = 0; i < pPart->curr->size.isv; i++) {
				pPart->curr->svInit[i] = pPart->curr->sv[i];
				pPart->curr->sv[i] = 0;
			}
		}
	}

	 
	Update_oszf(pPart->curr);

	 
	pPart->curr->szf = pPart->curr->cszf;
	Reset_ezf(pPart->curr);

	pPart->curr->sInfo.dt = 0.0;

	sc->action = SOLVER_EVENT_ITERATION;

	do {
		sd->stat[pid].iRhsCalls++;
		sd->stat[pid].iZero++;
		pPart->curr->sInfo.bSolverNeedsReset = ITI_false;
		bRepeat = ITI_false;
		









		if (pid == 0) {
			if (hitIsClock || pPart->curr->sInfo.isEventClock) {
				 
				if (hitIsClock && !pPart->curr->sInfo.isInitial) {
					SetTimeTriggeredClocks(sd, pPart->curr->t);
					hitIsClock = ITI_false;
				}

				 
				ExceptWrapper2(pPartFunctions->PostActivation, pPart, &sd->modelData);  

				if (HandleTimeTriggeredClocks(sd, pPart->curr->t) > SOLVER_SUCCESS_END) {
					HandleWarnings(&pPart->curr->sInfo);
					pPart->curr->sInfo.trace(0, 4, "Solver Error", "Error during evaluation of clock partitions.", (void*)&pPart->curr->sInfo);
					sc->state = SOLVER_ERROR_IN_INITIALIZATION_AFTERDISCONTINUITY;
					return sc->state;
				}

				ExceptWrapper2(pPartFunctions->PreActivation, pPart, &sd->modelData);  

				pPart->curr->sInfo.isEventClock = ITI_false;

				





				 
				if (HoldHasChangedBaseClocks(sd)) {
					bRepeat = ITI_true;
				}

				 
				if (pPart->curr->sInfo.isTerminate && !pPart->curr->sInfo.isTerminal) {
					hitIsClock = ITI_true;
				}
			}
		}
		 
		iRet = ExceptWrapper2((ModelFunc2)pPartFunctions->CalcDerivatives, pPart, &sd->modelData);
		sd->model.ReleaseAllMemory(&sd->modelData.currMem);

#ifdef TRACE_STATES
		TRACE_STATES
			traceStates(pid, pPart->curr, &sd->modelData, IDS_EVENTITERATION);
		END_TRACE
#endif
#ifdef TRACE_DER
			TRACE_DER
			traceDer(pid, pPart->curr, &sd->modelData, IDS_EVENTITERATION);
		END_TRACE
#endif

			pPart->curr->sInfo.isFirstEventStep = ITI_false;

		



		if (pPart->curr->sInfo.isInitial) {
			pPart->curr->sInfo.isInitial = ITI_false;
			if (sc->hitIsSample) {
				 
				for (i = 0; i < pPart->curr->size.isv; i++) {
					pPart->curr->sv[i] = pPart->curr->svInit[i];

					






				}
			}
		}
		else {
			if (sc->hitIsSample || sc->bTimeEvent) {
				sc->bTimeEvent = ITI_false;
				sc->hitIsSample = ITI_false;
				 
				for (i = 0; i < pPart->curr->size.isv; i++)
					pPart->curr->sv[i] = 0;
			}
		}
		if (iRet > SOLVER_SUCCESS_END) {
			HandleWarnings(&pPart->curr->sInfo);
			pPart->curr->sInfo.trace(0, 4, "Solver Error", "Error during Reinitialization after an Event", (void*)&pPart->curr->sInfo);
			sc->state = SOLVER_ERROR_IN_INITIALIZATION_AFTERDISCONTINUITY;
			return sc->state;
		}
		if (pPart->curr->sInfo.bDPHappened)
			sc->bDPHappenedInEventiteration = ITI_true;

		 
		if (pPart->curr->sInfo.bSolverNeedsReset) {
			bSolverNeedsReset = 1;
			pPart->curr->sInfo.bSolverNeedsReset = ITI_false;

			for (i = 0; i < pPart->curr->size.ix; i++) {
				if (pPart->curr->iReinit[i]) {
					pPart->curr->xChanged[i] = 1;
					pPart->curr->iReinit[i] = 0;
				}
			}
		}
		bRepeat |= sc->hitIsSample;

		pPartFunctions->AssignDiscreteReal(pPart, &sd->modelData);
		 
#ifdef ITI_COMP_SIM
		bRepeat |= Check_z_data_ptr(pPart->curr, pPart->curr->sInfo.sSettings->absTol, pPart->curr->sInfo.sSettings->relTol);
		 
		if (bRepeat)
			CountDiscrete(sd->stat[pid].discreteCount, pPart->curr);
#else
		bRepeat |= Check_z_data(pPart->curr, pPart->curr->sInfo.sSettings->absTol, pPart->curr->sInfo.sSettings->relTol);
#endif

#ifdef TRACE_DISCRETE
		TRACE_DISCRETE
			if (bRepeat)
				traceDiscrVarChanged(pid, pPart->curr, &sd->modelData, &sd->model, iIter);
		END_TRACE
#endif
			Update_czf(pPart->curr);
		bRepeat |= Check_Update_oszf(pPart->curr);

		if (bRepeat && iIter > 10)
			pPart->curr->sInfo.applyHysteresis = ITI_true;

		if (pPart->curr->sInfo.applyHysteresis) {
			UpdateEpsilonZF(pPart->curr);
		}

		if (iIter > 995) {
			WarningChangedDiscreteVars(pPart->curr, iIter, pPart->curr->sInfo.sSettings->absTol, pPart->curr->sInfo.sSettings->relTol);
		}
#ifdef _ENDEVENTSTEP
		TraceEndEventStep(sd);
#endif

		 
#ifdef ITI_COMP_SIM
		Update_pre_z_data_ptr(pPart->curr, &sd->modelData);
#else
		Update_pre_z_data(pPart->curr, &sd->modelData);
#endif
		iIter++;

		 
		 
		if (sc->bTerminateRequired) {
			pPart->curr->sInfo.isTerminal = ITI_true;
			sc->bTerminateRequired = ITI_false;
		}
		else if (pPart->curr->sInfo.isTerminal) {
			bRepeat = ITI_false;
		}
		else if (pPart->curr->sInfo.isTerminate) {  
			pPart->curr->sInfo.isTerminal = ITI_true;
			bRepeat = ITI_true;
		}

#ifdef _EVENT_STEP
		 
		if (((cvc->t >= _ROOT_PROT_BEGIN[0]) && (pPart->curr->t <= _ROOT_PROT_END[0])) || ((pPart->curr->t >= _ROOT_PROT_BEGIN[1]) && (pPart->curr->t <= _ROOT_PROT_END[1])) || ((pPart->curr->t >= _ROOT_PROT_BEGIN[2]) && (pPart->curr->t <= _ROOT_PROT_END[2])))
		{
			FILE* roots = fopen("roots.txt", "a");
			fprintf(roots, "Event Step:\t%u\n", iIter);
			fclose(roots);
		}
#endif
		 
		if (iIter > 999) {
			HandleWarnings(&pPart->curr->sInfo);
			pPart->curr->sInfo.trace(0, 4, "Solver Error", "Cycle in Event Iteration", (void*)&pPart->curr->sInfo);
			sc->state = SOLVER_CYCLE_IN_EVENT_ITERATION;
			return sc->state;
		}
		if (bRepeat) {
			if (HandleSaveOutputs(pid, sd, SaveOutputsAtleastwithdtProtAllEventStepsBit | SaveOutputsEquidistantAllEventStepsBit, (sd->ss.saveModeB != SaveOutputsEquidistantAllEventStepsBit)) != SOLVER_SUCCESS_END)
			{
				HandleWarnings(&pPart->curr->sInfo);
				pPart->curr->sInfo.trace(0, 4, "Solver ERROR", "Error in computation of outputs during reinitialization after an Event", (void*)&pPart->curr->sInfo);
				sc->state = SOLVER_ERROR_IN_INITIALIZATION_AFTERDISCONTINUITY;
				return sc->state;
			}
		}
	} while (iIter < 1000 && bRepeat);

#ifdef _ENDEVENTITER
	TraceEndEventIter(sd, iIter);
#endif
	sc->action = SOLVER_EVENT_ITERATION_EXIT;

	if (bCallValidStep) {
		pPart->curr->sInfo.strAnalysisTypeDetail = "validStep";
		if (ExceptWrapper2((ModelFunc2)pPartFunctions->ValidStep, pPart, &sd->modelData) > SOLVER_SUCCESS_END) {
			HandleWarnings(&pPart->curr->sInfo);
			sc->state = SOLVER_ERROR;
			return sc->state;
		}
		sd->model.ReleaseAllMemory(&sd->modelData.currMem);
		pPart->curr->sInfo.strAnalysisTypeDetail = "residuals";
	}

	 
	pPartFunctions->AssignLastVar(pPart, &sd->modelData);

	if (HandleSaveOutputs(pid, sd, SaveOutputsAtleastwithdtProtPostEventsBit | SaveOutputsAtleastwithdtProtPrePostEventsBit | SaveOutputsAtleastwithdtProtAllEventStepsBit | SaveOutputsEquidistantPostEventsBit | SaveOutputsEquidistantPrePostEventsBit | SaveOutputsEquidistantAllEventStepsBit, (sd->ss.saveModeB != SaveOutputsEquidistantPostEventsBit) && (sd->ss.saveModeB != SaveOutputsEquidistantPrePostEventsBit) && (sd->ss.saveModeB != SaveOutputsEquidistantAllEventStepsBit)) != SOLVER_SUCCESS_END) {
		HandleWarnings(&pPart->curr->sInfo);
		pPart->curr->sInfo.trace(0, 4, "Solver ERROR", "Error in computation of outputs during reinitialization after an Event", (void*)&pPart->curr->sInfo);
		sc->state = SOLVER_ERROR_IN_INITIALIZATION_AFTERDISCONTINUITY;
		return sc->state;
	}
	if (sd->sc[pid]->OnValidEventStepSolver) {
		sd->sc[pid]->OnValidEventStepSolver(pid, sd);
	}

	pPart->curr->sInfo.tracingAllowed = ITI_false;
	pPart->curr->szf = pPart->curr->oszf;

	Update_pre_zf(pPart->curr->zf, pPart->curr->pre_zf, pPart->curr->size.izf);
	ResetSCCounter(pPart->curr);

	UpdateDelayBuffers(pPart->curr->db, pPart->curr->size.idb);
	UpdateHystCurves(pPart->curr->hcs, pPart->curr->size.ihcs);
	HandleAssertWarnings(&pPart->curr->sInfo);

	if (!pPart->curr->sInfo.applyHysteresis) {
		pPart->curr->sInfo.applyHysteresis = ITI_true;
		UpdateEpsilonZF(pPart->curr);
	}

	pPart->curr->sInfo.bDPAllowed = ITI_false;
	pPart->curr->sInfo.bDPHappened = ITI_false;
	sc->bDPHappenedInEventiteration = ITI_false;

	pPart->curr->sInfo.bSolverNeedsReset = bSolverNeedsReset;

	sc->action = SOLVER_CHECK_END_TIME;

	if (pPart->curr->sInfo.isTerminate)
		return SOLVER_TERMINATED;
	else
		return SOLVER_SUCCESS_CONTINUE;
}

ITI_SolverState TerminatePartition(size_t pid, ITI_SolverData* sd) {
	ITI_Partition *pPart = &sd->partition[pid];
	ITI_PartFunctions* pPartFunctions = &sd->model.partFunctions[pid];
	ITI_SolverContextBase* sc = sd->sc[pid];
	size_t i = 0;

	if (pPart->curr->sInfo.MEcalled)  
		return sc->state;

	 
	pPart->curr->sInfo.isInitial = ITI_false;
	pPart->curr->sInfo.isTerminate = ITI_false;
	pPart->curr->sInfo.strAnalysesType = "residuals";
	pPart->curr->sInfo.strAnalysisTypeDetail = "event";
	pPart->curr->sInfo.isEvent = ITI_true;
	pPart->curr->sInfo.isFirstEventStep = ITI_true;
	pPart->curr->sInfo.bDPAllowed = ITI_true;
	pPart->curr->sInfo.bDPRequired = ITI_false;
	pPart->curr->sInfo.bSolverNeedsReset = ITI_false;
	pPart->curr->sInfo.tracingAllowed = ITI_true;

	 
	if (!pPart->curr->sInfo.isTerminal && sc->state >= 0 && pPart->transient->sInfo.bInitializeFuncCalled) {
		pPart->curr->sInfo.isTerminal = ITI_true;
		sd->stat[pid].iRhsCalls++;

		











		if (ExceptWrapper2((ModelFunc2)pPartFunctions->CalcDerivatives, pPart, &sd->modelData) != SOLVER_SUCCESS_END) {
			HandleWarnings(&pPart->transient->sInfo);
			pPart->transient->sInfo.trace(0, 4, "Solver Error", "Error in computation of derivatives during termination of model", (void*)&pPart->transient->sInfo);
			sc->state = SOLVER_ERROR;
			return sc->state;
		}

		if (HandleSaveOutputs(pid, sd, SaveOutputsLastValueBit, ITI_true) != SOLVER_SUCCESS_END)
		{
			HandleWarnings(&pPart->transient->sInfo);
			pPart->transient->sInfo.trace(0, 4, "Solver Error", "Error in computation of outputs during termination of model", (void*)&pPart->transient->sInfo);
			sc->state = SOLVER_ERROR;
			return sc->state;
		}

#ifdef TRACE_STATES
		TRACE_STATES
			traceStates(pid, pPart->curr, &sd->modelData, IDS_TERMINATION);
		END_TRACE
#endif
#ifdef TRACE_DER
			TRACE_DER
			traceDer(pid, pPart->curr, &sd->modelData, IDS_TERMINATION);
		END_TRACE
#endif

	}

	if (pPart->curr->sInfo.bInitializeFuncCalled) {
		pPart->curr->sInfo.isTerminal = ITI_true;
		if (ExceptWrapper2(pPartFunctions->Terminate, pPart, &sd->modelData) > SOLVER_SUCCESS_END) {
			HandleWarnings(&pPart->curr->sInfo);
			pPart->curr->sInfo.trace(0, 4, "Solver Error", "Error during termination.", (void*)&pPart->transient->sInfo);
			sc->state = SOLVER_ERROR;
			return sc->state;
		}
		pPart->curr->sInfo.bInitializeFuncCalled = ITI_false;
		if (sd->sc[pid]->OnValidEventStepSolver) {
			sd->sc[pid]->OnValidEventStepSolver(pid, sd);
		}
	}
	ReleaseAllMemory(&sd->modelData.currMem);
	ReleaseAllMemory(&sd->modelData.strMem);

	for (i = 0; i < (size_t)pPart->curr->size.iv_str; i++)
		pPart->curr->v.strSize[i] = 0;
	for (i = 0; i < (size_t)pPart->curr->size.iz_str; i++) {
		pPart->curr->z.strSize[i] = 0;
		pPart->curr->pre_z.strSize[i] = 0;
	}

	return SOLVER_SUCCESS_END;
}
