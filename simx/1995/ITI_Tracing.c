/**
 * ITI_Tracing.c
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#include "ITI_crt.h"
#include "ITI_Tracing.h"

void traceStates(size_t pid, ITI_PartitionVar *sv, ITI_ModelData *sd, const char *strId)
{
	int i;
	char msg[256];
	ITI_char msh[ITI_TRACE_STRING_SIZE];
	ITI_char msl[ITI_TRACE_STRING_SIZE] = "";

	if (sd->traceData.pTraceOn && *(sd->traceData.pTraceOn) == 0)
		return;

	sprintf(msg, "%sstates at time t=%.17g s:\n", strId, sv->t);
	for (i = 0; i < sv->size.ix; i++) {
		sprintf(msh, "%*s\t%.17g\n", sv->trwidth, sv->stateNames[i], sv->x[i]);
		if (strlen(msl) + strlen(msh) >= ITI_TRACE_STRING_SIZE) {
			sv->sInfo.trace(0, Debug, msg, msl, (void*)&sv->sInfo);
			*msl = '\0';
		}
		strcat(msl, msh);
	}
	sv->sInfo.trace(0, Debug, msg, msl, (void*)&sv->sInfo);
}

void traceDer(size_t pid, ITI_PartitionVar *sv, ITI_ModelData *sd, const char *strId)
{
	int i;
	char msg[256];
	ITI_char msh[ITI_TRACE_STRING_SIZE];
	ITI_char msl[ITI_TRACE_STRING_SIZE] = "";

	if (sd->traceData.pTraceOn && *(sd->traceData.pTraceOn) == 0)
		return;

	sprintf(msg, "%sderivatives at time t=%.17g s:\n", strId, sv->t);
	for (i = 0; i < sv->size.ix; i++) {
		sprintf(msh, "%*s\t%.17g\n", sv->dtrwidth, sv->dstateNames[i], sv->xdot[i]);
		if (strlen(msl) + strlen(msh) >= ITI_TRACE_STRING_SIZE) {
			sv->sInfo.trace(0, Debug, msg, msl, (void*)&sv->sInfo);
			*msl = '\0';
		}
		strcat(msl, msh);
	}
	sv->sInfo.trace(0, Debug, msg, msl, (void*)&sv->sInfo);
}

void traceDiscrVarChanged(size_t pid, ITI_PartitionVar *sv, ITI_ModelData *sd, ITI_ModelFunctions *model, ITI_uint iter)
{
	ITI_int i;
	ITI_int trc = 0;
	ITI_char msg[256];
	ITI_char msh[ITI_TRACE_STRING_SIZE];
	ITI_char msl[ITI_TRACE_STRING_SIZE] = "";

	if (sd->traceData.pTraceOn && *(sd->traceData.pTraceOn) == 0)
		return;

	sprintf(msg, "Time: %.17g s: Event Iteration step %u: A discrete variable has changed its value.", sv->t, iter+1);

	for (i = 0; i < sv->size.iz_real; i++) {
#ifdef ITI_COMP_SIM
		if (*sv->pre_z.realData[i] != *sv->z.realData[i]) {
			sprintf(msh, "%s\t from %.17g to %.17g.\n", model->partFunctions[pid].dataZ[i].name, *sv->pre_z.realData[i], *sv->z.realData[i]);
#else
		if (sv->pre_z.realData[i] != sv->z.realData[i]) {
			sprintf(msh, "realData[%d]\t from %.17g to %.17g.\n", i, sv->pre_z.realData[i], sv->z.realData[i]);
#endif
			trc = 1;
			if (strlen(msh) + strlen(msl) >= ITI_TRACE_STRING_SIZE) {
				sv->sInfo.trace(0, Debug, msg, msl, (void*)&sv->sInfo);
				msl[0] = '\0';
			}
			strcat(msl, msh);
		}
	}
	for (i = 0; i < sv->size.iz_int; i++) {
		if (sv->pre_z.intData[i] != sv->z.intData[i]) {
#ifdef ITI_COMP_SIM
			sprintf(msh, "%s\t from %d to %d.\n", model->partFunctions[pid].dataZ[i+sv->size.iz_real].name, sv->pre_z.intData[i], sv->z.intData[i]);
#else
			sprintf(msh, "intData[%d]\t from %d to %d.\n", i, sv->pre_z.intData[i], sv->z.intData[i]);
#endif
			trc = 1;
			if (strlen(msh) + strlen(msl) >= ITI_TRACE_STRING_SIZE) {
				sv->sInfo.trace(0, Debug, msg, msl, (void*)&sv->sInfo);
				*msl = '\0';
			}
			strcat(msl, msh);
		}
	}
	for (i = 0; i < sv->size.iz_str; i++) {
		if (strcmp(sv->pre_z.strData[i], sv->z.strData[i]) != 0) {
#ifdef ITI_COMP_SIM
			sprintf(msh, "%s\t from \"%s\" to \"%s\".\n", model->partFunctions[pid].dataZ[i + sv->size.iz_real + sv->size.iz_int].name, sv->pre_z.strData[i], sv->z.strData[i]);
#else
			sprintf(msh, "strData[%d]\t from \"%s\" to \"%s\".\n", i, sv->pre_z.strData[i], sv->z.strData[i]);
#endif
			trc = 1;
			if (strlen(msh) + strlen(msl) >= ITI_TRACE_STRING_SIZE) {
				sv->sInfo.trace(0, Debug, msg, msl, (void*)&sv->sInfo);
				*msl = '\0';
			}
			strcat(msl, msh);
		}
	}
	if (trc)
		sv->sInfo.trace(0, Debug, msg, msl, (void*)&sv->sInfo);
}

void traceZeroFct(size_t pid, ITI_PartitionVar *sv, ITI_ModelData *sd, ITI_ModelFunctions *model, ITI_int *root)
{
	ITI_int i;
	ITI_char msg[256];
	ITI_char msh[ITI_TRACE_STRING_SIZE];
	ITI_char msl[ITI_TRACE_STRING_SIZE] = "";

	if (sd->traceData.pTraceOn && *(sd->traceData.pTraceOn) == 0)
		return;
	sprintf(msg, "Time: %.17g s: Sign change of zerofunctions.", sv->t);
	for (i = 0; i < sv->size.izf; i++) {
		if (root[i] == 1) {
			int sign_pre = sv->pre_zf[i] < 0 ? -1 :( sv->pre_zf[i] > 0 ? 1 : 0);
			int sign_act = sv->zf[i] < 0 ? -1 : (sv->zf[i] > 0 ? 1 : 0);
#ifdef ITI_COMP_SIM
			sprintf(msh, "%s: %s, value changed from %.17g to %.17g, sign: %d -> %d\n", model->partFunctions[pid].dataZF[i].parentIdent, model->partFunctions[pid].dataZF[i].name, sv->pre_zf[i], sv->zf[i], sign_pre, sign_act);
#else
			sprintf(msh, "zero(%d) = %.17g\tpre_zero = %.17g, sign: %d -> %d\n", i, sv->zf[i], sv->pre_zf[i], sign_pre, sign_act);
#endif
			if (strlen(msl) + strlen(msh) >= ITI_TRACE_STRING_SIZE) {
				sv->sInfo.trace(0, Debug, msg, msl, (void*)&sv->sInfo);
				*msl = '\0';
			}
			strcat(msl, msh);
		}
	}
	sv->sInfo.trace(0, Debug, msg, msl, (void*)&sv->sInfo);
}

void traceDummyPivoting(ITI_PartitionVar *sv, ITI_ModelData *sd)
{
	char strCapt[256];
	char msg[] = "";

	if (sd->traceData.pTraceOn && *(sd->traceData.pTraceOn) == 0)
		return;

	sprintf(strCapt, "Time: %.17g s: Dummy derivative pivoting.\n", sv->t);
	sv->sInfo.trace(0, Debug, strCapt, msg, (void*)&sv->sInfo);
}

void InitBlockStatistics(ITI_SolverStatistic *stat, ITI_int numBlocks)
{
	stat->numBlocks = numBlocks;
	if (numBlocks > 0)
	{
		stat->numBlockRes = (ITI_long *)calloc(numBlocks, sizeof(ITI_long));
		stat->numBlockJac = (ITI_long *)calloc(numBlocks, sizeof(ITI_long));
		stat->blockTimes = (ITI_real *)calloc(numBlocks, sizeof(ITI_real));
	}
	else
	{
		stat->numBlockRes = NULL;
		stat->numBlockJac = NULL;
		stat->blockTimes = NULL;
	}
}

void CollectBlockStatistics(ITI_SolverStatistic *stat, ITI_BlockData *ibd, void *performanceData)
{
	ITI_uint i;
	ITI_PerformanceTimer *pt = (ITI_PerformanceTimer *)performanceData;

	PerformanceTimeInSeconds(pt, &stat->calcDerivativesTime, stat->blockTimes);
	for (i = 0; i < stat->numBlocks; i++) {
		stat->numBlockRes[i] = ibd[i].resCalls;
		stat->numBlockJac[i] = ibd[i].jacCalls;
	}
}

void FreeBlockStatistics(ITI_SolverStatistic *stat)
{
	free(stat->numBlockRes); stat->numBlockRes = NULL;
	free(stat->numBlockJac); stat->numBlockJac = NULL;
	free(stat->blockTimes); stat->blockTimes = NULL;
}

#if defined _MSC_VER && !defined ITI_TWINCAT

void InitPerformanceTiming(void **perfData, ITI_uint numBlocks)
{
	ITI_PerformanceTimer *pt = calloc(1, sizeof(ITI_PerformanceTimer));  
	pt->nBlocks = numBlocks;
	if (numBlocks > 0)
		pt->blockTiming = calloc(numBlocks, sizeof(LARGE_INTEGER));  
	else
		pt->blockTiming = NULL;

	QueryPerformanceFrequency(&pt->frequency);

	*perfData = pt;
}

void SetPerformanceTimingOMP(void *perfData, ITI_ushort omp)
{
	ITI_PerformanceTimer *pt = (ITI_PerformanceTimer *)perfData;
	pt->omp = omp;
}

void StartPerformanceTiming(void *perfData, int index)
{
	ITI_PerformanceTimer *pt = (ITI_PerformanceTimer *)perfData;
	if (pt->omp != 0)
		return;

	QueryPerformanceCounter(index == -1 ? &pt->modelStart : &pt->blockStart);
}

void EndPerformanceTiming(void *perfData, int index)
{
	LARGE_INTEGER endingTime;
	ITI_PerformanceTimer *pt = (ITI_PerformanceTimer *)perfData;
	if (pt->omp != 0)
		return;

	QueryPerformanceCounter(&endingTime);
	if (index == -1)
		pt->modelTiming.QuadPart += endingTime.QuadPart - pt->modelStart.QuadPart;
	else
		pt->blockTiming[index].QuadPart += endingTime.QuadPart - pt->blockStart.QuadPart;
}

void FreePerformanceTiming(void *perfData)
{
	if (perfData) {
		ITI_PerformanceTimer *pt = (ITI_PerformanceTimer *)perfData;
		free(pt->blockTiming);
		free(pt);
	}
}

void PerformanceTimeInSeconds(ITI_PerformanceTimer *pt, double *tCD, double *tBlocks)
{
	ITI_uint i;
	*tCD = (double)pt->modelTiming.QuadPart / pt->frequency.QuadPart;
	for (i = 0; i < pt->nBlocks; i++)
		tBlocks[i] = (double)pt->blockTiming[i].QuadPart / pt->frequency.QuadPart;
}

#else

void InitPerformanceTiming(void **perfData, ITI_uint numBlocks) {}

void SetPerformanceTimingOMP(void *perfData, ITI_ushort omp) {}

void StartPerformanceTiming(void *perfData, int index) {}

void EndPerformanceTiming(void *perfData, int index) {}

void FreePerformanceTiming(void *perfData) {}

void PerformanceTimeInSeconds(ITI_PerformanceTimer *pt, double *tCD, double *tBlocks) {}

#endif
