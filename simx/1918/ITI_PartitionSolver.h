/**
 * ITI_PartitionSolver.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#if !defined(_ITI_PartitionSolver)
#define _ITI_PartitionSolver
#include "ITI_crt.h"
#include "ITI_FunctionsAlloc.h"

typedef struct SolverCoefficients {
	ITI_int	numSteps;
	ITI_int	s;
	ITI_real a[4];				 
	ITI_int  b[4];				 
	ITI_real c[4];				 
} SolverCoefficients;

typedef struct ITI_PartitionSolverContext {
	ITI_SolverContextBase	contextBase;		 

	ITI_real*				temp;				 
	ITI_real*				previousStates;		 

	ITI_real*				currentSamples;		 
	ITI_real*				previousSamples;	 

	ITI_real				h;					 

	SolverCoefficients		coeffs;				 
} ITI_PartitionSolverContext;

 
void* CreatePartitionSolver(size_t pid, ITI_SolverData* sd, ITI_PartitionSolverMethod solverMethod);
ITI_SolverState InitializeSolver(void* pData);

 

 
ITI_SolverState InitializePreparePartitionSolver(size_t pid, ITI_SolverData* sd);
ITI_SolverState InitializeFinishPartitionSolver(size_t pid, ITI_SolverData* sd);

 
ITI_SolverState CalcOneStepPartitionSolver(size_t pid, void* pData, double endTime);
ITI_SolverState PrepareTimeEventHandlingPartitionSolver(size_t pid, ITI_SolverData* sd);

 

 
void FreePartitionSolver(void* ctx);

#endif
