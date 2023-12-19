/**
 * ITI_Tracing.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#ifndef ITI_TRACING_H
#define ITI_TRACING_H

#include "ITI_crt.h"

#ifdef ITI_COMP_SIM

#define TRACE_DISCRETE				if (TRACEFLAGS->trDiscrete) {
#define	TRACE_ROOTCOUNTER			if (TRACEFLAGS->trRootCounter) {
#define	TRACE_DUMMYPIVOTING			if (TRACEFLAGS->trDummyPivoting) {
#define	TRACE_ZEROFCT				if (TRACEFLAGS->trZeroFct) {
#define	TRACE_ZEROFCTTIME			if (TRACEFLAGS->trZeroFctTime) {
#define	TRACE_ZEROFCTTIME2			if (TRACEFLAGS->trZeroFctTime2) {
#define	TRACE_FINDDISCONT			if (TRACEFLAGS->trFindDiscont) {
#define	TRACE_STARTEVENTSTEP		if (TRACEFLAGS->trStartEventStep) {
#define	TRACE_ENDEVENTSTEP			if (TRACEFLAGS->trEndEventStep) {
#define	TRACE_ENDEVENTITER			if (TRACEFLAGS->trEndEventIter) {
#define	TRACE_TIMERSET				if (TRACEFLAGS->trTimerSet) {
#define	TRACE_TIMEREXPIRED			if (TRACEFLAGS->trTimerExpired) {

#define	TRACE_RESULT				if (TRACEFLAGS->trResult) {
#define	TRACE_IDO					if (TRACEFLAGS->trIdo) {
#define	TRACE_RES					if (TRACEFLAGS->trRes) {
#define	TRACE_STATES				if (TRACEFLAGS->trStates) {
#define	TRACE_DER					if (TRACEFLAGS->trDer) {
#define	TRACE_NEWTONUPDATE			if (TRACEFLAGS->trNewtonUpdate) {
#define	TRACE_JAC					if (TRACEFLAGS->trJac) {
#define	TRACE_INDEX					if (TRACEFLAGS->trIndex) {
#define	TRACE_STATEBOUNDS			if (TRACEFLAGS->trStateBounds) {
#define	TRACE_ERRORLINSYS			if (TRACEFLAGS->trErrorsLinSystem) {
#define	TRACE_STEPTRUE				if (TRACEFLAGS->trStepTrue) {
#define	TRACE_RESTRUE				if (TRACEFLAGS->trResTrue) {
#define	TRACE_STATESTRUE			if (TRACEFLAGS->trStatesTrue) {
#define	TRACE_DERTRUE				if (TRACEFLAGS->trDerTrue) {
#define	TRACE_STEPFALSE				if (TRACEFLAGS->trStepFalse) {
#define	TRACE_RESFALSE				if (TRACEFLAGS->trResFalse) {
#define	TRACE_STATESFALSE			if (TRACEFLAGS->trStatesFalse) {
#define	TRACE_DERFALSE				if (TRACEFLAGS->trDerFalse) {
#define	TRACE_NEWTONUPDATEFALSE		if (TRACEFLAGS->trNewtonUpdateFalse) {
#define TRACE_BLOCKSTATISTICS		if (TRACEFLAGS->trBlockStatistics) {
#define	TRACE_HOMOTOPYSTEPSIZE		if (TRACEFLAGS->trHomotopyStepSize) {
#define	TRACE_HOMOTOPYTANGENTSPACE	if (TRACEFLAGS->trHomotopyTangentSpace) {

#else  

 
 
 
 
 
 
 
 
 
 
 
 

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

#endif

#define END_TRACE }

#define IDS_CALCJAC			"Jacobian evaluation, "
#define IDS_EVENTITERATION	"During event iteration, "
#define IDS_INITIAL			"After initial value calculation, "
#define IDS_INIT_VALUE		"During initial value calculation, "
#define IDS_CVODE_RHS		"CVODE rhs calculation, "
#define IDS_CVODE_ZERO		"CVODE root calculation, "
#define IDS_CVODE_VALIDSTEP	"Valid step, "
#define IDS_CLASSIFY_EVENT	"During numerical classification of an event, "
#define IDS_TERMINATION		"During termination, "
#define IDS_OUTPUT			"During handling of equidistant output, "
#define IDS_EFFICIENT		"During efficient handling of a time event, "
#define IDS_END_SIM			"At the end of the transient simulation, "

ITI_FUNCTIONS_API void traceStates(size_t pid, ITI_PartitionVar *sv, ITI_ModelData *sd, const char *strId);
ITI_FUNCTIONS_API void traceDer(size_t pid, ITI_PartitionVar *sv, ITI_ModelData *sd, const char *strId);
ITI_FUNCTIONS_API void traceDiscrVarChanged(size_t pid, ITI_PartitionVar *sv, ITI_ModelData* sd, ITI_ModelFunctions *model, ITI_uint iter);
ITI_FUNCTIONS_API void traceZeroFct(size_t pid, ITI_PartitionVar *sv, ITI_ModelData* sd, ITI_ModelFunctions *model, ITI_int *root);
ITI_FUNCTIONS_API void traceDummyPivoting(ITI_PartitionVar *sv, ITI_ModelData* sd);

#ifdef _MSC_VER

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

typedef struct {
	LARGE_INTEGER frequency;
	LARGE_INTEGER modelTiming;
	ITI_uint nBlocks;
	LARGE_INTEGER *blockTiming;
	LARGE_INTEGER modelStart;
	LARGE_INTEGER blockStart;
	ITI_ushort omp;
} ITI_PerformanceTimer;

#else

typedef void ITI_PerformanceTimer;

#endif

ITI_FUNCTIONS_API void InitBlockStatistics(ITI_SolverStatistic *stat, ITI_int numBlocks);
ITI_FUNCTIONS_API void FreeBlockStatistics(ITI_SolverStatistic *stat);
ITI_FUNCTIONS_API void CollectBlockStatistics(ITI_SolverStatistic *stat, ITI_BlockData *ibd, void *performanceData);

ITI_FUNCTIONS_API void InitPerformanceTiming(void **perfData, ITI_uint numBlocks);
ITI_FUNCTIONS_API void SetPerformanceTimingOMP(void *perfData, ITI_ushort omp);
ITI_FUNCTIONS_API void StartPerformanceTiming(void *perfData, int index);
ITI_FUNCTIONS_API void EndPerformanceTiming(void *perfData, int index);
ITI_FUNCTIONS_API void FreePerformanceTiming(void *perfData);
ITI_FUNCTIONS_API void PerformanceTimeInSeconds(ITI_PerformanceTimer *pt, double *tCD, double *tBlocks);

#endif  
