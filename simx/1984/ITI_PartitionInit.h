/**
 * ITI_PartitionInit.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#if !defined(_ITI_PartitionInit)
#define _ITI_PartitionInit

#include "ITI_crt.h"

ITI_FUNCTIONS_API ITI_SolverState InitializePartitionComplete(size_t pid, ITI_SolverData* sd);
ITI_FUNCTIONS_API void InitializePartitionVars(size_t pid, ITI_SolverData* sd);
ITI_FUNCTIONS_API ITI_SolverState InitializePartition(size_t pid, ITI_SolverData* sd);
ITI_FUNCTIONS_API ITI_SolverState InitializeConditionsPartitionComplete(size_t pid, ITI_SolverData* sd);
ITI_FUNCTIONS_API ITI_SolverState InitializeConditionsPartition(size_t pid, ITI_SolverData* sd);
ITI_FUNCTIONS_API ITI_SolverState InitializeConditionsPartitionFinish(size_t pid, ITI_SolverData* sd);
ITI_FUNCTIONS_API ITI_SolverState PrepareTimeEventHandlingPartition(size_t pid, ITI_SolverData* sd);
ITI_FUNCTIONS_API void ResetSolverStatistics(ITI_SolverStatistic* pStat, ITI_int ix);

#endif  