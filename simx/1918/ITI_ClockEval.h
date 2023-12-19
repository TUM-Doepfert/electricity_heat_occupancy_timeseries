/**
 * ITI_ClockEval.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#if !defined(_ITI_ClockEval)
#define _ITI_ClockEval

#include "ITI_crt.h"
#include "ITI_FunctionsAlloc.h"

 
ITI_int GetNumClockedPartitions(ITI_Partition* pPart);
ITI_PartitionSolverMethod GetSolverMethod(ITI_Partition* pPart);
ITI_bool IsEventClock(ITI_Partition* pPart);
ITI_bool IsBasePartition(ITI_Partition* pPart);
ITI_bool IsContinuousPartition(ITI_Partition* pPart);

 
ITI_bool HasActiveSample(ITI_Partition* pPart);
ITI_bool HoldHasChanged(ITI_Partition* pPart);
ITI_bool HoldHasChangedBaseClocks(ITI_SolverData* sd);

 
ITI_FUNCTIONS_API void DoClockTick(size_t pid, ITI_SolverData* sd);
ITI_FUNCTIONS_API void NextClockTick(size_t pid, ITI_SolverData* sd, ITI_real nextActivationTime);
ITI_FUNCTIONS_API ITI_int SetTimeTriggeredClocks(ITI_SolverData* sd, ITI_real time);

 
ITI_FUNCTIONS_API ITI_SolverState HandleTimeTriggeredClocks(ITI_SolverData* sd, ITI_real time);
ITI_FUNCTIONS_API ITI_SolverState IntegratePartition(size_t pid, ITI_SolverData* sd, ITI_real nextActivationTime);

 
ITI_FUNCTIONS_API ITI_SolverState PerformInferenceGraph(ITI_Partition* pPart, ITI_ModelData* modelData);

#endif
