/**
 * ITI_PartitionEval.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#if !defined(_ITI_PartitionEval)
#define _ITI_PartitionEval

#include "ITI_crt.h"

 
ITI_FUNCTIONS_API ITI_SolverState EventIterationPartition(size_t pid, ITI_SolverData* sd);
ITI_FUNCTIONS_API ITI_SolverState TerminatePartition(size_t pid, ITI_SolverData* sd);

#endif  