/**
 * ITI_Cvode_base.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#ifndef _ITI_CVODE_BASE_H_
#define _ITI_CVODE_BASE_H_

#include "ITI_crt.h"
#include "ITI_Cvode_model_if.h"
#include "ITI_Cvode_helpers.h"
#include "ITI_Cvode_jac.h"
#include "ITI_FunctionsAlloc.h"
#include "ITI_PartitionInterface.h"

typedef int (*OnCheckStopFunc)(void* pData);
typedef void (*OnValidTimeStepFunc)(size_t pid, void* pData);
typedef void (*OnValidEventStepFunc)(size_t pid, void* pData);
typedef void (*OnBeforeEventStepFunc)(size_t pid, void* pData);
typedef int (*OnCheckExternalEventFunc)(void* pData);

typedef struct ITI_CVodeContext {
	ITI_SolverContextBase contextBase;  

	void* cvodeMem;
	N_Vector absTolVec;
	N_Vector x;
	N_Vector xdot;
	N_Vector xInter;

	N_Vector x_tE;
	N_Vector x_tEE;
	N_Vector x_tE1;

	N_Vector xdot_tE;
	N_Vector xdot_tEE;
	N_Vector xdot_tE1;

	ITI_real t1;
	 

	N_Vector eweight;
	N_Vector ele;
	N_Vector elesum;
	ITI_int nextTimeEventStops;

	FILE* sStates;
	FILE* sJournal;

	OnCheckStopFunc	OnCheckStop;
	OnValidTimeStepFunc OnValidTimeStep;
	OnCheckExternalEventFunc OnCheckExternalEvent;

	ITI_int flag;
	ITI_real* pxData;

	ITI_SortJac* pSortJac;

	int maxThreads;
	void *parDat;

	void* pContainer;
}ITI_CVodeContext;

typedef struct {
	N_Vector *y_par;
	N_Vector *ftemp_par;
	N_Vector *jthCol_par;
	ITI_real* bx_tmp;
	ITI_SolverData *cvd_par;
} ITI_ParallelData;

typedef struct ITI_CVodeContainer {
	ITI_SolverData* cvd;
	ITI_Partition* pPart;
} ITI_CVodeContainer;

 
ITI_SolverState CreateSolverInstance(void** pData, const char* modelName, int nParams, double* pValues, TRACE_FUNC* pTraceFunc);
ITI_SolverState CreateSolverInstanceExtParams(void** pData, const char* modelName, int nParams, double* pValues, TRACE_FUNC* pTraceFunc, ITI_parameterData* params);
void* CreateCVODE(size_t pid, ITI_SolverData* cvd, ITI_PartitionSolverMethod solverMethod);
ITI_SolverState InitializeSolver(void* pData);
void InitData(ITI_SolverData *dst, ITI_SolverData *src);
void InitParallelData(ITI_SolverData *cvd);
void CopySimData(ITI_SolverData *dst, ITI_SolverData *src);
void CopySimData1st(ITI_SolverData *src);

 
ITI_SolverState SetSolverSettings(void* pData, ITI_SolverSettings* settings);
void SetSetInputsFunction(void* pData, SolverInterfaceOnSetInputsFunc pOnSetInputs);
void SetValidTimeStepFunc(void* pData, OnValidTimeStepFunc pOnValidTimeStepFunc);
void SetCheckStopFunc(void* pData, OnCheckStopFunc pOnCheckStopFunc);
void SetCheckExternalEventFunc(void* pData, OnCheckExternalEventFunc pOnCheckExternalEventFunc);
#ifndef ITI_COMP_SIM
void SetResourceFolder_CVode(void* pData, ITI_char* strFolder);
#endif

 
ITI_SolverState InitializeModel(void* pData);
ITI_SolverState InitializeConditionsModelOnly(void* pData);
ITI_SolverState InitializeConditionsModelFinish(void* pData);

ITI_SolverState InitializePrepareCVODE(size_t pid, ITI_SolverData* sd);
ITI_SolverState InitializeFinishCVODE(size_t pid, ITI_SolverData* sd);

 
ITI_SolverState CalcOneStepCVODE(size_t pid, void* pData, double endTime);
ITI_SolverState CalcOneStep(size_t pid, void* pData, int considerEndTime, double endTime);
ITI_SolverState PrepareTimeEventHandlingCVODE(size_t pid, ITI_SolverData* sd);
ITI_SolverState TerminateModel(void* pData);

 
void UpdateSolverStatistics(void* pData);
void BuildSolverStatisticsString(void* pData, char** strStat);
void BuildDetailedSolverStatisticsString(void* pData, size_t pid, char* strStat);
void PrintSolverStatistics(void* pData);
void WriteRootCounterFile(void* pData);

 
void FreeCVode(void* ctx);
void FreeSolverInstance(void* pData);
void FreeData(size_t pid, ITI_SolverData *cvd);
void FreeParallelData(void*pData);

 
ITI_bool CheckBit(int var, int mask);
ITI_SolverState HandleEquidistantOutput(size_t pid, ITI_SolverData* sd);

 
long int ModelSerializationSize(void *mem);
long int ModelSerialize(void *mem, void **storageDataPtr);
long int ModelDeserialize(void *mem, void **storageDataPtr);

#endif
