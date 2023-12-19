/**
 * ITI_ClockEval.c
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#include "ITI_ClockEval.h"
#include "ITI_ClockInference.h"
#ifdef ITI_COMP_SIM
#include "ITI_Interface_Types.h"
#endif

#ifdef ITI_COMP_SIM
#define TRACEFLAGS	(&sd->modelData.traceFlags)
#endif

 
#if !defined(_MSC_VER) && !defined(__BORLANDC__)
#include <math.h>
#define _nextafter nextafter
#endif




ITI_int GetNumClockedPartitions(ITI_Partition* pPart) {
	return pPart->transient->size.ipart;
}

ITI_PartitionSolverMethod GetSolverMethod(ITI_Partition* pPart) {
	return (ITI_PartitionSolverMethod)pPart->transient->partitionData[pPart->pid].solvermethod;
}

static
ITI_bool IsActivated(ITI_Partition* pPart) {
	return pPart->transient->v.intData[pPart->transient->partitionData[pPart->pid].activated];
}

ITI_bool IsBasePartition(ITI_Partition* pPart) {
	return pPart->transient->partitionData[pPart->pid].type == CPT_BaseClock;
}

ITI_bool IsContinuousPartition(ITI_Partition* pPart) {
	return pPart->transient->partitionData[pPart->pid].continous;
}

ITI_bool IsEventClock(ITI_Partition* pPart) {
	return pPart->transient->partitionData[pPart->pid].eventClock;
}

static
ITI_bool IsSubPartition(ITI_Partition* pPart) {
	return pPart->transient->partitionData[pPart->pid].type == CPT_SubClock;
}




ITI_bool HasActiveSample(ITI_Partition* pPart) {
	return (pPart->transient->v.intData[pPart->transient->partitionData[pPart->pid].sampleActive] == 1);
}

 
ITI_bool HoldHasChanged(ITI_Partition* pPart) {
	if (pPart->transient->v.intData[pPart->transient->partitionData[pPart->pid].holdChanged] == 1) {
		pPart->transient->v.intData[pPart->transient->partitionData[pPart->pid].holdChanged] = 0;
		return ITI_true;
	}
	return ITI_false;
}

 
ITI_bool HoldHasChangedBaseClocks(ITI_SolverData* sd) {
	ITI_int subPartitionId;
	ITI_int holdChanged = 0;
	ITI_Partition* pTransient = &sd->partition[0];
	for (subPartitionId = 1; subPartitionId < GetNumClockedPartitions(pTransient); ++subPartitionId) {
		ITI_Partition* pPart = &sd->partition[subPartitionId];
		if (IsBasePartition(pPart) && HoldHasChanged(pPart)) {
			holdChanged = ITI_true;
		}
	}
	return holdChanged;
}




void DoClockTick(size_t pid, ITI_SolverData* sd) {
	ITI_Partition* pPart = &sd->partition[pid];

	pPart->transient->sInfo.isEventClock = ITI_true;
	pPart->transient->sInfo.timeTriggeredClock[pid].bTick = ITI_true;
}

void NextClockTick(size_t pid, ITI_SolverData* sd, ITI_real nextActivationTime) {
	ITI_Partition* pPart = &sd->partition[pid];

	pPart->transient->sInfo.timeTriggeredClock[pid].nextTickTime = nextActivationTime;
}

ITI_int SetTimeTriggeredClocks(ITI_SolverData* sd, ITI_real time) {
	int subPartitionId;
	int iClockTicks = 0;
	ITI_Partition* pTransient = &sd->partition[0];
	if (pTransient->curr->sInfo.isFixedStep)
		time = _nextafter(time, DBL_MAX);
	for (subPartitionId = 1; subPartitionId < GetNumClockedPartitions(pTransient); ++subPartitionId) {
		ITI_Partition* pPart = &sd->partition[subPartitionId];
		if (IsBasePartition(pPart) && !IsEventClock(pPart)
			&& (pTransient->curr->sInfo.timeTriggeredClock[subPartitionId].nextTickTime <= time)) {
			iClockTicks++;
			pTransient->curr->sInfo.timeTriggeredClock[subPartitionId].bTick = ITI_true;
		}
	}
	return iClockTicks;
}




ITI_SolverState CalcSubClockTick(size_t pid, ITI_SolverData* sd, ITI_real time) {
	ITI_SolverState iRet = SOLVER_SUCCESS_END;
	ITI_Partition* pPart = &sd->partition[pid];
	ITI_PartFunctions* pPartFunctions = &sd->model.partFunctions[pid];
	char* strAnalysisTypeDetail_old;
	
	if (!IsSubPartition(pPart) || !IsActivated(pPart)) {
		return iRet;
	}
	strAnalysisTypeDetail_old = pPart->base->sInfo.strAnalysisTypeDetail;
	pPart->curr->sInfo.strAnalysisTypeDetail = "clockTick";
	
	pPart->curr->t = pPart->base->t;
	iRet = ExceptWrapper2(pPartFunctions->PreActivation, pPart, &sd->modelData);
	if (iRet != SOLVER_SUCCESS_END) {
		HandleWarnings(&pPart->transient->sInfo);
		ResetWarningStack(&pPart->transient->sInfo);
		return iRet;
	}

	


	iRet = ExceptWrapper2((ModelFunc2)pPartFunctions->CalcDerivatives, pPart, &sd->modelData);
	if (iRet != SOLVER_SUCCESS_END) {
		HandleWarnings(&pPart->transient->sInfo);
		ResetWarningStack(&pPart->transient->sInfo);
		return iRet;
	}

	 
	iRet = ExceptWrapper2((ModelFunc2)pPartFunctions->ValidStep, pPart, &sd->modelData);
	if (iRet != SOLVER_SUCCESS_END) {
		HandleWarnings(&pPart->transient->sInfo);
		ResetWarningStack(&pPart->transient->sInfo);
		return iRet;
	}

	 
	iRet = ExceptWrapper2((ModelFunc2)pPartFunctions->CalcOutputs, pPart, &sd->modelData);
	if (iRet != SOLVER_SUCCESS_END) {
		HandleWarnings(&pPart->transient->sInfo);
		ResetWarningStack(&pPart->transient->sInfo);
		return iRet;
	}

	 
	if (pPartFunctions->SynchOutputs) {
		iRet = ExceptWrapper2(pPartFunctions->SynchOutputs, pPart, &sd->modelData);
		if (iRet != SOLVER_SUCCESS_END) {
			HandleWarnings(&pPart->transient->sInfo);
			ResetWarningStack(&pPart->transient->sInfo);
			return iRet;
		}
	}

	 
	iRet = ExceptWrapper2(pPartFunctions->PostActivation, pPart, &sd->modelData);
	if (iRet != SOLVER_SUCCESS_END) {
		HandleWarnings(&pPart->transient->sInfo);
		ResetWarningStack(&pPart->transient->sInfo);
		return iRet;
	}

	 
#ifdef ITI_COMP_SIM
	Update_pre_z_data_ptr(pPart->curr, &sd->modelData);
#else
	Update_pre_z_data(pPart->curr, &sd->modelData);
#endif
	 
	if (pPart->curr->sInfo.isTerminate) {
		pPart->transient->sInfo.isTerminate = ITI_true;
	}

	 
	pPart->curr->sInfo.strAnalysisTypeDetail = strAnalysisTypeDetail_old;
	return iRet;
}

ITI_SolverState CalcClockTick(size_t pid, ITI_SolverData* sd, ITI_real time) {
	ITI_SolverState iRet = SOLVER_SUCCESS_END;
	ITI_Partition* pPart = &sd->partition[pid];    
	ITI_PartFunctions* pPartFunctions = &sd->model.partFunctions[pid];
	char* strAnalysisTypeDetail_old;
	int subPartitionId;

	if (!IsBasePartition(pPart)) {
		return iRet;
	}
	strAnalysisTypeDetail_old = pPart->base->sInfo.strAnalysisTypeDetail;
	pPart->curr->sInfo.strAnalysisTypeDetail = "clockTick";

	


	pPart->curr->t = time;

	 
	iRet = ExceptWrapper2(pPartFunctions->PreActivation, pPart, &sd->modelData);
	if (iRet != SOLVER_SUCCESS_END) {
		HandleWarnings(&pPart->transient->sInfo);
		ResetWarningStack(&pPart->transient->sInfo);
		return iRet;
	}

	 
	for (subPartitionId = 1; subPartitionId < GetNumClockedPartitions(pPart); ++subPartitionId) {
		ITI_Partition* pSubPart = &sd->partition[subPartitionId];
		if (IsSubPartition(pSubPart) &&
			pPart->transient->partitionData[subPartitionId].baseid == pPart->pid) {
			iRet = CalcSubClockTick(subPartitionId, sd, time);
			if (iRet != SOLVER_SUCCESS_END) {
				HandleWarnings(&pPart->transient->sInfo);
				ResetWarningStack(&pPart->transient->sInfo);
				return iRet;
			}
		}
	}

	 
	 

	 
	iRet = ExceptWrapper2(pPartFunctions->PostActivation, pPart, &sd->modelData);
	if (iRet != SOLVER_SUCCESS_END) {
		HandleWarnings(&pPart->transient->sInfo);
		ResetWarningStack(&pPart->transient->sInfo);
		return iRet;
	}

#ifdef ITI_COMP_SIM
	if (sd->modelData.simxInterface) {
		if (pPartFunctions->SynchOutputs) {
			iRet = ExceptWrapper2(pPartFunctions->SynchOutputs, pPart, &sd->modelData);
			if (iRet != SOLVER_SUCCESS_END) {
				HandleWarnings(&pPart->transient->sInfo);
				ResetWarningStack(&pPart->transient->sInfo);
				return iRet;
			}
		}
	}
#endif

	 
	pPart->curr->sInfo.strAnalysisTypeDetail = strAnalysisTypeDetail_old;
	return iRet;
}

ITI_SolverState IntegratePartition(size_t pid, ITI_SolverData* sd, ITI_real nextActivationTime) {
	ITI_SolverState iRet = SOLVER_SUCCESS_END;
	ITI_Partition* pPart = &sd->partition[pid];

	switch (GetSolverMethod(pPart)) {
	default:
		return sd->sc[pid]->CalcOneStepSolver(pid, sd, nextActivationTime);
	











	}
	return iRet;
}

ITI_SolverState HandleTimeTriggeredClocks(ITI_SolverData* sd, ITI_real time) {
	int subPartitionId;
	int last_partitionId = 0;
	ITI_Partition* pTransient = &sd->partition[0];
	for (subPartitionId = 1; subPartitionId < GetNumClockedPartitions(pTransient); ++subPartitionId) {
		ITI_Partition* pPart = &sd->partition[subPartitionId];
		if (IsBasePartition(pPart) && (pTransient->curr->sInfo.timeTriggeredClock[subPartitionId].bTick == ITI_true)) {
			ITI_SolverState iRet;
			last_partitionId = subPartitionId;
			iRet = CalcClockTick(subPartitionId, sd, time);
			if (iRet != SOLVER_SUCCESS_END) {
				return iRet;
			}
		}
	}

#ifdef ITI_COMP_SIM
	for (subPartitionId = 1; subPartitionId < GetNumClockedPartitions(pTransient); ++subPartitionId) {
		ITI_Partition* pPart = &sd->partition[subPartitionId];
		if (IsBasePartition(pPart) && (pTransient->curr->sInfo.timeTriggeredClock[subPartitionId].bTick == ITI_true)) {
			((ITI_SimXInterface*)sd->modelData.simxInterface)->LogResults(sd->modelData.simxInterface, subPartitionId,subPartitionId==last_partitionId);
		}
	}
#endif
	 
	if (!pTransient->curr->sInfo.isTerminate) {
		for (subPartitionId = 1; subPartitionId < GetNumClockedPartitions(pTransient); ++subPartitionId) {
			pTransient->curr->sInfo.timeTriggeredClock[subPartitionId].bTick = ITI_false;
		}
	}
	return SOLVER_SUCCESS_END;
}

ITI_SolverState PerformInferenceGraph(ITI_Partition* pPart, ITI_ModelData* modelData) {
	ITI_char errorMsg[MAX_ERROR_LENGTH + 1];
	ITI_SolverState iRet = SOLVER_SUCCESS_END;
	int i;
	for (i = 0; i < pPart->transient->size.iig; ++i) {
		ITI_ClockInferenceState status = performClockInference(&(pPart->transient->partitionIG[i]));
		if (status > noError) {
			HandleWarnings(&pPart->transient->sInfo);
			strcpy(errorMsg, getError(&(pPart->transient->partitionIG[i])));
			if (status < errorSolverInference) {
				pPart->transient->sInfo.trace(0, 1, "Solver Warning", errorMsg, (void*)&pPart->transient->sInfo);
				iRet = SOLVER_SUCCESS_CONTINUE;
			}
			else {
				pPart->transient->sInfo.trace(0, 4, "Solver Error", errorMsg, (void*)&pPart->transient->sInfo);
				iRet = SOLVER_ERROR_IN_INITIALIZATION;
			}
		}
	}
	return iRet;
}