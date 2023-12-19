/**
 * ITI_FunctionsAlloc.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#if !defined(_ITI_FunctionsAlloc)
#define _ITI_FunctionsAlloc

#include "ITI_crt.h"

ITI_FUNCTIONS_API ITI_SolverData* CreateSolverData(const char* modelName, int nParams, double* pValues, TRACE_FUNC* pTraceFunc, CreateSolverContextFunc pCreateSolverContext);
ITI_FUNCTIONS_API ITI_SolverData* CreateSolverDataExtParams(const char* modelName, int nParams, double* pValues, TRACE_FUNC* pTraceFunc, CreateSolverContextFunc CreateSolverContext, ITI_parameterData* params);
ITI_FUNCTIONS_API ITI_SolverState CreatePartitionSolvers(ITI_SolverData* sd);
ITI_FUNCTIONS_API ITI_SolverState TerminateModelPartitions(ITI_SolverData* sd);
ITI_FUNCTIONS_API void FreeSolverData(ITI_SolverData* pSolverData);

#endif
