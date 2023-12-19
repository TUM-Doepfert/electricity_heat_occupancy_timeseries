/**
 * ITI_PartitionSolver.c
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#include "ITI_PartitionSolver.h"
#include "ITI_PartitionInit.h"

SolverCoefficients CoeffInvalid = { -1, -1, { -1., -1., -1., -1. }, { -1, -1, -1, -1 }, { -1., -1., -1., -1. } };
SolverCoefficients CoeffExplicitEuler = { 1, 1, { 1. }, { 1 }, { 1. } };
SolverCoefficients CoeffExplicitMidPoint2 = { 2, 1, { 0., 0.5 }, { 0, 1 }, { 0.5, 1. } };
SolverCoefficients CoeffExplicitRungeKutta4 = { 4, 6, { 0., 0.5, 0.5, 1. }, { 1, 2, 2, 1 }, { 0., 0.5, 0.5, 1. } };

void* CreatePartitionSolver(size_t pid, ITI_SolverData* sd, ITI_PartitionSolverMethod solverMethod) {
	ITI_Partition* pPart = &sd->partition[pid];
	ITI_PartitionSolverContext* ctx = calloc(1, sizeof(ITI_PartitionSolverContext));

	ctx->contextBase.CreateSolver= CreatePartitionSolver;
	ctx->contextBase.InitializePrepareSolver= InitializePreparePartitionSolver;
	ctx->contextBase.InitializeFinishSolver = InitializeFinishPartitionSolver;
	ctx->contextBase.PrepareTimeEventHandlingSolver = PrepareTimeEventHandlingPartitionSolver;
	ctx->contextBase.OnPrepareSaveOutputs = NULL;
	ctx->contextBase.OnSaveOutputsSolver = NULL;
	ctx->contextBase.OnFinishSaveOutputs = NULL;
	ctx->contextBase.OnBeforeEventStepSolver = NULL;
	ctx->contextBase.OnValidEventStepSolver = NULL;
	ctx->contextBase.CalcOneStepSolver = CalcOneStepPartitionSolver;
	ctx->contextBase.FreeSolver= FreePartitionSolver;

	ctx->contextBase.bTerminateRequired = ITI_false;
	ctx->contextBase.bTimeEvent = ITI_false;
	ctx->contextBase.hitIsSample = ITI_false;
	ctx->contextBase.hitIsClock = ITI_false;
	ctx->contextBase.bZeroFunc = ITI_false;
	ctx->contextBase.bDPHappenedInEventiteration = ITI_false;
	ctx->contextBase.bFinishSaveOutputsNecessary = ITI_false;
	ctx->contextBase.bPerformEventIterationInPartitionFinish = ITI_true;
	ctx->contextBase.t = 0.0;

	ctx->contextBase.solverMethod = solverMethod;
	switch (solverMethod) {
	case ExplicitEuler:
		ctx->coeffs = CoeffExplicitEuler;
		break;
	case ExplicitMidPoint2:
		ctx->coeffs = CoeffExplicitMidPoint2;
		break;
	case ExplicitRungeKutta4:
		ctx->coeffs = CoeffExplicitRungeKutta4;
		break;
	default:
		ctx->coeffs = CoeffInvalid;
		break;
	}

	if (pPart->curr->size.ix == 0) {
		ctx->temp = NULL;
		ctx->previousStates = NULL;
	}
	else {
		ctx->temp = (ITI_real*)calloc(pPart->curr->size.ix, sizeof(ITI_real));
		ctx->previousStates = (ITI_real*)calloc(pPart->curr->size.ix, sizeof(ITI_real));
	}

	if (pPart->curr->size.iclocksv_real == 0) {
		ctx->currentSamples = NULL;
		ctx->previousSamples = NULL;
	}
	else {
		ctx->currentSamples = (ITI_real*)calloc(pPart->curr->size.iclocksv_real, sizeof(ITI_real));
		ctx->previousSamples = (ITI_real*)calloc(pPart->curr->size.iclocksv_real, sizeof(ITI_real));
	}

	return ctx;
}

ITI_SolverState InitializePreparePartitionSolver(size_t pid, ITI_SolverData* sd) {
	return SOLVER_SUCCESS_CONTINUE;
}

ITI_SolverState InitializeFinishPartitionSolver(size_t pid, ITI_SolverData* sd) {
	ITI_Partition *pPart = &sd->partition[pid];
	ITI_PartitionSolverContext* ctx = (ITI_PartitionSolverContext*)sd->sc[pid];
	
	ctx->contextBase.state = SOLVER_SUCCESS_END;
	memcpy(ctx->previousStates, pPart->curr->x, pPart->curr->size.ix * sizeof(double));
	return SOLVER_SUCCESS_END;
}

void FreePartitionSolver(void* pData) {
	ITI_PartitionSolverContext* ctx = (ITI_PartitionSolverContext*)pData;
	free(ctx->temp);
	free(ctx->previousStates);
	free(ctx->currentSamples);
	free(ctx->previousSamples);
	free(ctx);
}

ITI_SolverState PrepareTimeEventHandlingPartitionSolver(size_t pid, ITI_SolverData* sd) {
	return PrepareTimeEventHandlingPartition(pid, sd);
}

static
ITI_SolverState SolverCalculateDerivatives(size_t pid, ITI_SolverData* sd, ITI_int step) {
	ITI_PartitionSolverContext* ctx = (ITI_PartitionSolverContext*)sd->sc[pid];
	ITI_Partition* pPart = &sd->partition[pid];
	 
	return ExceptWrapper2((ModelFunc2)sd->model.partFunctions[pid].CalcDerivatives, pPart, &sd->modelData);
}

static
void SolverCalculateTemporaries(size_t pid, ITI_SolverData* sd, ITI_int step) {
	ITI_PartitionSolverContext* ctx = (ITI_PartitionSolverContext*)sd->sc[pid];
	ITI_Partition* pPart = &sd->partition[pid];
	ITI_int index = 0;
	for (; index < pPart->curr->size.ix; ++index) {
		if (step == 1 || ctx->coeffs.numSteps == 2) {
			



			ctx->temp[index] = ctx->h * pPart->curr->xdot[index];
		}
		else {
			 
			ctx->temp[index] += ctx->h * ctx->coeffs.b[step - 1] * pPart->curr->xdot[index];
		}
	}
}

static
void SolverInterpolateSamples(size_t pid, ITI_SolverData* sd, ITI_int step) {
	ITI_PartitionSolverContext* ctx = (ITI_PartitionSolverContext*)sd->sc[pid];
	ITI_Partition* pPart = &sd->partition[pid];
	ITI_int index = 0;
	for (; index < pPart->curr->size.iclocksv_real; ++index) {
		 
#ifdef ITI_COMP_SIM
		ctx->currentSamples[index] = (1 - ctx->coeffs.c[step - 1]) * ctx->previousSamples[index] + ctx->coeffs.c[step - 1] * (*pPart->curr->clocksv.realData[index]);
#else
		ctx->currentSamples[index] = (1 - ctx->coeffs.c[step - 1]) * ctx->previousSamples[index] + ctx->coeffs.c[step - 1] * pPart->curr->clocksv.realData[index];
#endif
	}
}

static
void SolverInterpolateStates(size_t pid, ITI_SolverData* sd, ITI_int step) {
	ITI_PartitionSolverContext* ctx = (ITI_PartitionSolverContext*)sd->sc[pid];
	ITI_Partition* pPart = &sd->partition[pid];
	ITI_int index = 0;
	for (; index < pPart->curr->size.ix; ++index) {
		if (step < ctx->coeffs.numSteps) {
			 
			pPart->curr->x[index] = ctx->previousStates[index] + ctx->h * ctx->coeffs.a[step] * pPart->curr->xdot[index];
		}
		else {
			 
			 
			pPart->curr->x[index] = ctx->previousStates[index] + ctx->temp[index] / ctx->coeffs.s;
		}
	}
}

static
void SolverInterpolateTime(size_t pid, ITI_SolverData* sd, ITI_int step) {
	ITI_PartitionSolverContext* ctx = (ITI_PartitionSolverContext*)sd->sc[pid];
	ITI_Partition* pPart = &sd->partition[pid];
	if (step < ctx->coeffs.numSteps) {
		 
		 
		pPart->curr->t = pPart->curr->t + (ctx->coeffs.c[step] - ctx->coeffs.c[step - 1]) * ctx->h;
	}
	else if (step == ctx->coeffs.numSteps) {
		 
		pPart->curr->t = pPart->transient->t;
	}
}

static
void SolverUpdatePreviousVars(size_t pid, ITI_SolverData* sd) {
	ITI_PartitionSolverContext* ctx = (ITI_PartitionSolverContext*)sd->sc[pid];
	ITI_Partition* pPart = &sd->partition[pid];
#ifdef ITI_COMP_SIM
	ITI_int index = 0;
	for (; index < pPart->curr->size.iclocksv_real; ++index) {
		ctx->previousSamples[index] = (*pPart->curr->clocksv.realData[index]);
	}
#else
	memcpy(ctx->previousSamples, pPart->curr->clocksv.realData, pPart->curr->size.iclocksv_real * sizeof(double));
#endif
	memcpy(ctx->previousStates, pPart->curr->x, pPart->curr->size.ix * sizeof(double));
}

static
void SolverUpdateSamples(size_t pid, ITI_SolverData* sd) {
	ITI_PartitionSolverContext* ctx = (ITI_PartitionSolverContext*)sd->sc[pid];
	ITI_Partition* pPart = &sd->partition[pid];
#ifdef ITI_COMP_SIM
	ITI_int index = 0;
	ctx->h = *pPart->transient->v.realData[pPart->transient->partitionData[pid].interval];
	for (; index < pPart->curr->size.iclocksv_real; ++index) {
		ctx->currentSamples[index] = *pPart->curr->clocksv.realData[index];
	}
#else
	ctx->h = pPart->transient->v.realData[pPart->transient->partitionData[pid].interval];
	memcpy(ctx->currentSamples, pPart->curr->clocksv.realData, pPart->curr->size.iclocksv_real * sizeof(double));
#endif
}

static
void SolverUpdateSimXStates(size_t pid, ITI_SolverData* sd) {
#ifdef ITI_COMP_SIM
	ITI_PartitionSolverContext* ctx = (ITI_PartitionSolverContext*)sd->sc[pid];
	ITI_Partition* pPart = &sd->partition[pid];
	UpdateStates(sd->model.partFunctions[pid].dataX, pPart->curr->size.iSimX_X, pPart->curr->ws, pPart->curr->x);
#endif
}

ITI_SolverState CalcOneStepPartitionSolver(size_t pid, void* pData, double endTime) {
	ITI_SolverData* sd = (ITI_SolverData*)pData;
	ITI_PartitionSolverContext* ctx = (ITI_PartitionSolverContext*)sd->sc[pid];
	ITI_int step = 1;
	SolverUpdateSamples(pid, sd);
	for (; step <= ctx->coeffs.numSteps; ++step) {
		SolverInterpolateTime(pid, sd, step);
		SolverCalculateTemporaries(pid, sd, step);
		SolverInterpolateStates(pid, sd, step);
		SolverInterpolateSamples(pid, sd, step);
		if (SolverCalculateDerivatives(pid, sd, step) != SOLVER_SUCCESS_END) {
			return SOLVER_ERROR;
		}
	}
	SolverUpdatePreviousVars(pid, sd);
	SolverUpdateSimXStates(pid, sd);
	return SOLVER_SUCCESS_END;
}
