/**
 * ITI_FunctionsAlloc.c
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#include "ITI_FunctionsAlloc.h"
#include "ITI_ClockEval.h"
#include "ITI_PartitionEval.h"
#include "ITI_PartitionSolver.h"
#include "ITI_Tracing.h"
#ifndef ITI_COMP_SIM
#include "ITI_Declarations.h"
#else
#include "ITI_SolverHelpers.h"
#endif

#ifdef _OPENMP
#include <omp.h>
#endif

#ifndef ITI_COMP_SIM

#if (defined(_OPENMP) )
 
#if (defined(_MSC_VER) )
extern _declspec(thread) ITI_MemoryObject* g_currMem;
extern _declspec(thread) ITI_SolverInfo* g_sInfo;
#else  
extern ITI_MemoryObject* g_currMem;
extern ITI_SolverInfo* g_sInfo;
#pragma omp threadprivate(g_currMem)
#pragma omp threadprivate(g_sInfo)
#endif  
#else  
extern ITI_MemoryObject* g_currMem;
extern ITI_SolverInfo* g_sInfo;
#endif  

extern ITI_outputData outputData[];
extern ITI_inputData inputs[];
#endif

ITI_int NotifyAllocErrorAndUnloadDll(ITI_SolverInfo* sInfo, ITI_ModelFunctions* model)
{
	sInfo->trace(0, 4, "Error: Memory allocation", "\nError: Allocation of needed memory failed.\n\n", (void*)sInfo);
#ifdef ITI_COMP_SIM
	FreeLibrary((HMODULE)model->hModel);
	model->hModel = NULL;
#endif
	return SOLVER_ERROR_CREATE_INSTANCE;
}


#ifdef ITI_COMP_SIM

void InitWorkSpace(ITI_WorkSpace* ws, ITI_ModelSize *currSize) {
	ITI_int i;

	ws->vtmp.strSize = NULL;
	if (currSize->iv_real == 0)
	{
		ws->vtmp_mem_real = NULL;
		ws->vtmp.realData = NULL;
		ws->v_mem_real = NULL;
		ws->v.realData = NULL;
	}
	else
	{
		ws->vtmp_mem_real = (ITI_real*)calloc(currSize->iv_real, sizeof(ITI_real));
		ws->vtmp.realData = (ITI_real**)calloc(currSize->iv_real, sizeof(ITI_real*));
		ws->v_mem_real = (ITI_real*)calloc(currSize->iv_real, sizeof(ITI_real));
		ws->v.realData = (ITI_real**)calloc(currSize->iv_real, sizeof(ITI_real*));

		for (i = 0; i < currSize->iv_real; i++) {
			ws->vtmp.realData[i] = &(ws->vtmp_mem_real[i]);
			ws->v.realData[i] = &(ws->v_mem_real[i]);
		}
	}
	
	if (currSize->iv_int == 0)
	{
		ws->vtmp.intData = NULL;
		ws->v.intData = NULL;
	}
	else
	{
		ws->vtmp.intData = (ITI_int*)calloc(currSize->iv_int, sizeof(ITI_int));
		ws->v.intData = (ITI_int*)calloc(currSize->iv_int, sizeof(ITI_int));
	}

	if (currSize->iv_str == 0)
	{
		ws->vtmp.strData = NULL;
		ws->v.strData = NULL;
		ws->v.strSize = NULL;
	}
	else
	{
		ws->vtmp.strData = (ITI_char**)calloc(currSize->iv_str, sizeof(ITI_char*));
		ws->v.strData = (ITI_char**)calloc(currSize->iv_str, sizeof(ITI_char*));
		ws->v.strSize = (size_t*)calloc(currSize->iv_str, sizeof(size_t));
	}

	if (currSize->ip_real == 0)
	{
		ws->p_mem_real = NULL;
		ws->p.realData = NULL;
	}
	else
	{
		ws->p_mem_real = (ITI_real*)calloc(currSize->ip_real, sizeof(ITI_real));
		ws->p.realData = (ITI_real**)calloc(currSize->ip_real, sizeof(ITI_real*));

		for (i = 0; i < currSize->ip_real; i++) {
			ws->p.realData[i] = &(ws->p_mem_real[i]);
		}
	}

	if (currSize->ip_int == 0)
		ws->p.intData = NULL;
	else
		ws->p.intData = (ITI_int*)calloc(currSize->ip_int, sizeof(ITI_int));

	if (currSize->ip_str == 0)
		ws->p.strData = NULL;
	else
		ws->p.strData = (ITI_char**)calloc(currSize->ip_str, sizeof(ITI_char*));

	ws->p.strSize = NULL;

	   
											 
											 
	 
	if (currSize->iz_real == 0)
	{
		ws->z_mem_real = NULL;
		ws->z.realData = NULL;
		ws->pre_z_mem_real = NULL;
		ws->pre_z.realData = NULL;
	}
	else
	{
		ws->z_mem_real = (ITI_real*)calloc(currSize->iz_real, sizeof(ITI_real));
		ws->z.realData = (ITI_real**)calloc(currSize->iz_real, sizeof(ITI_real*));
		ws->pre_z_mem_real = (ITI_real*)calloc(currSize->iz_real, sizeof(ITI_real));
		ws->pre_z.realData = (ITI_real**)calloc(currSize->iz_real, sizeof(ITI_real*));

		for (i = 0; i < currSize->iz_real; i++)
		{
			ws->z.realData[i] = &(ws->z_mem_real[i]);
			ws->pre_z.realData[i] = &(ws->pre_z_mem_real[i]);
		}
	}

	if (currSize->iz_int == 0)
	{
		ws->z.intData = NULL;
		ws->pre_z.intData = NULL;
	}
	else
	{
		ws->z.intData = (ITI_int*)calloc(currSize->iz_int, sizeof(ITI_int));
		ws->pre_z.intData = (ITI_int*)calloc(currSize->iz_int, sizeof(ITI_int));
	}

	if (currSize->iz_str == 0)
	{
		ws->z.strData = NULL;
		ws->z.strSize = NULL;
		ws->pre_z.strData = NULL;
		ws->pre_z.strSize = NULL;
	}
	else
	{
		ws->z.strData = (ITI_char**)calloc(currSize->iz_str, sizeof(ITI_char*));
		ws->z.strSize = (size_t*)calloc(currSize->iz_str, sizeof(size_t));
		ws->pre_z.strData = (ITI_char**)calloc(currSize->iz_str, sizeof(ITI_char*));
		ws->pre_z.strSize = (size_t*)calloc(currSize->iz_str, sizeof(size_t));
	}

	if (currSize->ix == 0)
	{
		ws->x = NULL;
		ws->px = NULL;
	}
	else
	{
		ws->x = (ITI_real*)calloc(currSize->ix, sizeof(ITI_real));
		ws->px = (ITI_real**)calloc(currSize->ix, sizeof(ITI_real*));
		for (i = 0; i < currSize->ix; i++)
			ws->px[i] = &(ws->x[i]);
	}

	if (currSize->ibx == 0)
	{
		ws->bx = NULL;
		ws->bx_tmp = NULL;
	}
	else
	{
		ws->bx = (ITI_real*)calloc(currSize->ibx, sizeof(ITI_real));
		ws->bx_tmp = (ITI_real*)calloc(currSize->ibx, sizeof(ITI_real));
	}
	if (currSize->iclocksv_real == 0)
	{
		ws->clocksv_mem_real = NULL;
		ws->clocksv.realData = NULL;
	}
	else
	{
		ws->clocksv_mem_real = (ITI_real*)calloc(currSize->iclocksv_real, sizeof(ITI_real));
		ws->clocksv.realData = (ITI_real**)calloc(currSize->iclocksv_real, sizeof(ITI_real*));

		for (i = 0; i < currSize->iclocksv_real; i++) {
			ws->clocksv.realData[i] = &(ws->clocksv_mem_real[i]);
		}
	}

	if (currSize->iclocksv_int == 0)
		ws->clocksv.intData = NULL;
	else
		ws->clocksv.intData = (ITI_int*)calloc(currSize->iclocksv_int, sizeof(ITI_int));

	if (currSize->iclocksv_str == 0)
		ws->clocksv.strData = NULL;
	else
		ws->clocksv.strData = (ITI_char**)calloc(currSize->ip_str, sizeof(ITI_char*));
		ws->clocksv.strData = (ITI_char**)calloc(currSize->iclocksv_str, sizeof(ITI_char*));

	ws->clocksv.strSize = NULL;
}

#endif

ITI_SolverState InitModelInterface(ITI_ModelFunctions* model, const char* modelName, TRACE_FUNC* pTraceFunc, ITI_ModelSize* modelSize) {
#ifdef ITI_COMP_SIM
	 
	SetLastError(0);
	model->hModel = (void*)LoadLibraryA(modelName);
	if (!model->hModel)
	{
#ifdef _WIN64
		DWORD error = GetLastError();
		 
		if (error == ERROR_BAD_EXE_FORMAT) {  
			ITI_char msg[MAX_PATH + 150];
			sprintf(msg, "\"%s\" is not a valid 64 bit DLL.\n Probably the used compiler does not support 64 bit targets. Try to use another compiler.", modelName);
			pTraceFunc(0, 4, "Solver Error", msg, NULL );
		}
#endif  
		return SOLVER_ERROR_CREATE_INSTANCE;
	}
	 
	model->GetInterfaceVersion = (GetInterfaceVersionFunc)GetProcAddress((HINSTANCE)model->hModel, "GetInterfaceVersion");
	model->GetPartitionAccess = (GetPartitionAccessFunc)GetProcAddress((HINSTANCE)model->hModel, "GetPartitionAccess");
	if (!model->GetInterfaceVersion || !model->GetPartitionAccess || model->GetInterfaceVersion() != ITI_INTERFACE_VERSION) {
		if (model->hModel) {
			FreeLibrary((HMODULE)model->hModel);
		}
		 
		return SOLVER_ERROR_CREATE_INSTANCE;
	}
	 
	model->GetModelSizes = (GetModelSizesFunc)GetProcAddress((HINSTANCE)model->hModel, "GetModelSizes");
	model->InitInferenceGraph = (InitInferenceGraphFunc)GetProcAddress((HINSTANCE)model->hModel, "InitInferenceGraph");
	model->GetPartitionData = (GetPartitionDataFunc)GetProcAddress((HINSTANCE)model->hModel, "GetPartitionData");
	model->GetCheckSum = (GetCheckSumFunc)GetProcAddress((HINSTANCE)model->hModel, "GetCheckSum");
	model->ConstConditionsChanged = (ConstConditionsChangedFunc)GetProcAddress((HINSTANCE)model->hModel, "ConstConditionsChanged");
	model->SynchronizeParameters = (SynchronizeParametersFunc)GetProcAddress((HINSTANCE)model->hModel, "SynchronizeParameters");

	 
	model->InitMemory = (InitMemoryFunc)GetProcAddress((HINSTANCE)model->hModel, "InitMemory");
	model->FreeAllMemory = (FreeAllMemoryFunc)GetProcAddress((HINSTANCE)model->hModel, "FreeAllMemory");
	model->ReleaseAllMemory = (ReleaseAllMemoryFunc)GetProcAddress((HINSTANCE)model->hModel, "ReleaseAllMemory");
	model->GetStringMemory = (GetStringMemoryFunc)GetProcAddress((HINSTANCE)model->hModel, "GetStringMemory");
	model->AllocateRecords = (AllocateRecordsFunc)GetProcAddress((HINSTANCE)model->hModel, "AllocateRecords");
	model->FreeRecords = (FreeRecordsFunc)GetProcAddress((HINSTANCE)model->hModel, "FreeRecords");

	 
	model->outputData = (ITI_outputData*)GetProcAddress((HINSTANCE)model->hModel, "outputData");
	model->inputData = (ITI_inputData*)GetProcAddress((HINSTANCE)model->hModel, "inputs");

#else
	 
	model->GetModelSizes = (GetModelSizesFunc)&GetModelSizes;
	model->InitInferenceGraph = (InitInferenceGraphFunc)&InitInferenceGraph;
	model->GetPartitionData = (GetPartitionDataFunc)&GetPartitionData;
	model->GetPartitionAccess = (GetPartitionAccessFunc)&GetPartitionAccess;
	 
	model->InitMemory = (InitMemoryFunc)&InitMemory;
	model->FreeAllMemory = (FreeAllMemoryFunc)&FreeAllMemory;
	model->ReleaseAllMemory = (ReleaseAllMemoryFunc)&ReleaseAllMemory;
	model->GetStringMemory = (GetStringMemoryFunc)&GetStringMemory;
	model->AllocateRecords = (AllocateRecordsFunc)&AllocateRecords;
	model->FreeRecords = (FreeRecordsFunc)&FreeRecords;

	 
	model->outputData = outputData;
	model->inputData = inputs;
#endif  

	model->GetModelSizes(calloc, modelSize);

	model->partFunctions = (ITI_PartFunctions*)calloc(modelSize->ipart, sizeof(ITI_PartFunctions));
	model->GetPartitionAccess(model->partFunctions);

	return SOLVER_SUCCESS_END;
}

ITI_SolverState CreatePartition(ITI_SolverData* pSolverData, size_t pid, double* pValues, TRACE_FUNC* pTraceFunc, ITI_parameterData* params) {
	ITI_Partition* pPart=&pSolverData->partition[pid];
	ITI_ModelFunctions* model=&pSolverData->model;
	ITI_ModelSize *currSize;
#ifdef ITI_COMP_SIM
	ITI_WorkSpace* ws;
#endif
	ITI_int i;
	ITI_SolverState iRet;

	currSize = &pPart->curr->size;
	
	currSize->i_inc = GetIncSize(model->partFunctions[0].DPBlockSizes, currSize->iDPB);  

	pPart->curr->sInfo.trace = pTraceFunc;
	if (pid == 0) {
		pPart->curr->sInfo.bInitializeFuncCalled = ITI_false;
		pPart->curr->sInfo.isFirstRhsCall = ITI_false;
		pPart->curr->sInfo.bDPHappened = ITI_false;
		pPart->curr->sInfo.pContainer = 0;
		pPart->curr->sInfo.sSettings = &pSolverData->ss;
		pPart->curr->sInfo.applyHysteresis = ITI_false;
		pPart->curr->sInfo.bUseSimpleHomotopy = ITI_false;
		pPart->curr->sInfo.timeTriggeredClock = (ITI_TimeTriggeredClock*)calloc(pPart->curr->size.ipart, sizeof(ITI_TimeTriggeredClock));
	}
	else {
		 
		pPart->curr->sInfo.sSettings = &pSolverData->ss;
		pPart->curr->sInfo.timeTriggeredClock = NULL;
	}

	 
	 
	if (currSize->ix == 0) {
		pPart->curr->x = NULL;
		pPart->curr->xdot = NULL;
		pPart->curr->res = NULL;
		pPart->curr->xImpact = NULL;
	}
	else {
		pPart->curr->x = (ITI_real*)calloc(currSize->ix, sizeof(ITI_real));
		pPart->curr->xdot = (ITI_real*)calloc(currSize->ix, sizeof(ITI_real));
		pPart->curr->res = (ITI_real**)calloc(currSize->ix, sizeof(ITI_real*));
		pPart->curr->xImpact = (ITI_ushort*)calloc(currSize->ix, sizeof(ITI_ushort));
	}
	




	pPart->curr->x_bak = pPart->curr->x;
	pPart->curr->xdot_bak = pPart->curr->xdot;

	if (currSize->ires_i == 0)
		pPart->curr->res_i = NULL;
	else
		pPart->curr->res_i = (ITI_real**)calloc(currSize->ires_i, sizeof(ITI_real*));

	if (currSize->ibx == 0)
	{
		pPart->curr->bx = NULL;
		pPart->curr->bx_tmp = NULL;
		pPart->curr->bxd = NULL;
	}
	else
	{
#ifdef ITI_COMP_SIM
		pPart->curr->bx = (ITI_real**)calloc(currSize->ibx, sizeof(ITI_real*));
		pPart->curr->bx_tmp = (ITI_real**)calloc(currSize->ibx, sizeof(ITI_real*));
		pPart->curr->bxd = (ITI_real*)calloc(currSize->ibx, sizeof(ITI_real));
#else
		pPart->curr->bx = (ITI_real*)calloc(currSize->ibx, sizeof(ITI_real));
		pPart->curr->bx_tmp = (ITI_real*)calloc(currSize->ibx, sizeof(ITI_real));
		pPart->curr->bxd = NULL;  
#endif
	}

#ifdef ITI_COMP_SIM
	if (currSize->iy_real == 0)
	{
		pPart->curr->y_mem_real = NULL;
		pPart->curr->y.realData = NULL;
	}
	else
	{
		pPart->curr->y_mem_real = (ITI_real*)calloc(currSize->iy_real, sizeof(ITI_real));
		pPart->curr->y.realData = (ITI_real**)calloc(currSize->iy_real, sizeof(ITI_real*));
	}
	for (i = 0; i < currSize->iy_real; i++)
		pPart->curr->y.realData[i] = &(pPart->curr->y_mem_real[i]);

#else
	if (currSize->iy_real == 0)
		pPart->curr->y.realData = NULL;
	else
		pPart->curr->y.realData = (ITI_real*)calloc(currSize->iy_real, sizeof(ITI_real));
#endif
	if (currSize->iy_int == 0)
		pPart->curr->y.intData = NULL;
	else
		pPart->curr->y.intData = (ITI_int*)calloc(currSize->iy_int, sizeof(ITI_int));
	if (currSize->iy_str == 0)
	{
		pPart->curr->y.strData = NULL;
		pPart->curr->y.strSize = NULL;
	}
	else
	{
		pPart->curr->y.strData = (ITI_char**)calloc(currSize->iy_str, sizeof(ITI_char*));
		pPart->curr->y.strSize = (size_t*)calloc(currSize->iy_str, sizeof(size_t));
	}

#ifdef ITI_COMP_SIM
	if (currSize->iu_real == 0)
	{
		pPart->curr->u_mem_real = NULL;
		pPart->curr->u.realData = NULL;
	}
	else
	{
		pPart->curr->u_mem_real = (ITI_real*)calloc(currSize->iu_real, sizeof(ITI_real));
		pPart->curr->u.realData = (ITI_real**)calloc(currSize->iu_real, sizeof(ITI_real*));
	}
	for (i = 0; i < currSize->iu_real; i++)
		pPart->curr->u.realData[i] = &(pPart->curr->u_mem_real[i]);
#else
	if (currSize->iu_real == 0)
		pPart->curr->u.realData = NULL;
	else
		pPart->curr->u.realData = (ITI_real*)calloc(currSize->iu_real, sizeof(ITI_real));
#endif
	if (currSize->iu_int == 0)
		pPart->curr->u.intData = NULL;
	else
		pPart->curr->u.intData = (ITI_int*)calloc(currSize->iu_int, sizeof(ITI_int));
	if (currSize->iu_str == 0)
	{
		pPart->curr->u.strData = NULL;
		pPart->curr->u.strSize = NULL;
	}
	else
	{
		pPart->curr->u.strData = (ITI_char**)calloc(currSize->iu_str, sizeof(ITI_char*));
		pPart->curr->u.strSize = (size_t*)calloc(currSize->iu_str, sizeof(size_t));
	}

	if (params)
		AllocInitParameters(&pPart->curr->p, params, pValues, currSize->ip_real, currSize->ip_int, currSize->ip_str);
	else
		AllocInitParameters(&pPart->curr->p, model->partFunctions[pid].parameters, pValues, currSize->ip_real, currSize->ip_int, currSize->ip_str);

	if (currSize->ip_arr == 0) {
		pPart->curr->arr_p = NULL;
	}
	else {
		pPart->curr->arr_p = (ITI_Array*)calloc(currSize->ip_arr, sizeof(ITI_Array));

		for (i = 0; i < currSize->ip_arr; i++) {
			pPart->curr->arr_p[i].dims = NULL;
			pPart->curr->arr_p[i].realValues = NULL;
			pPart->curr->arr_p[i].intValues = NULL;
			pPart->curr->arr_p[i].charValues = NULL;
		}
	}


#ifdef ITI_COMP_SIM
	if (currSize->iv_real == 0)
	{
		pPart->curr->v.realData = NULL;
		pPart->curr->vtmp.realData = NULL;
	}
	else
	{
		pPart->curr->v.realData = (ITI_real**)calloc(currSize->iv_real, sizeof(ITI_real*));
		pPart->curr->vtmp.realData = (ITI_real**)calloc(currSize->iv_real, sizeof(ITI_real*));
	}
#else
	if (currSize->iv_real == 0)
	{
		pPart->curr->v.realData = NULL;
		pPart->curr->vtmp.realData = NULL;
	}
	else
	{
		pPart->curr->v.realData = (ITI_real*)calloc(currSize->iv_real, sizeof(ITI_real));
		pPart->curr->vtmp.realData = (ITI_real*)calloc(currSize->iv_real, sizeof(ITI_real));
	}
#endif
	if (currSize->iv_int == 0)
	{
		pPart->curr->v.intData = NULL;
		pPart->curr->vtmp.intData = NULL;
	}
	else
	{
		pPart->curr->v.intData = (ITI_int*)calloc(currSize->iv_int, sizeof(ITI_int));
		 
		pPart->curr->vtmp.intData = (ITI_int*)calloc(currSize->iv_int, sizeof(ITI_int));
	}
	if (currSize->iv_str == 0)
	{
		pPart->curr->v.strData = NULL;
		pPart->curr->v.strSize = NULL;
		pPart->curr->vtmp.strData = NULL;
		pPart->curr->vtmp.strSize = NULL;
	}
	else
	{
		pPart->curr->v.strData = (ITI_char**)calloc(currSize->iv_str, sizeof(ITI_char*));
		pPart->curr->v.strSize = (size_t*)calloc(currSize->iv_str, sizeof(size_t));
		 
		pPart->curr->vtmp.strData = (ITI_char**)calloc(currSize->iv_str, sizeof(ITI_char*));
		pPart->curr->vtmp.strSize = (size_t*)calloc(currSize->iv_str, sizeof(size_t));
		 
	}

#ifdef ITI_COMP_SIM
	if (currSize->iclocksv_real == 0)
		pPart->curr->clocksv.realData = NULL;
	else
		pPart->curr->clocksv.realData = (ITI_real**)calloc(currSize->iclocksv_real + currSize->iclocksv_int, sizeof(ITI_real*));
#else
	if (currSize->iclocksv_real == 0)
		pPart->curr->clocksv.realData = NULL;
	else
		pPart->curr->clocksv.realData = (ITI_real*)calloc(currSize->iclocksv_real, sizeof(ITI_real));
#endif
	if (currSize->iclocksv_int == 0)
		pPart->curr->clocksv.intData = NULL;
	else
		pPart->curr->clocksv.intData = (ITI_int*)calloc(currSize->iclocksv_int, sizeof(ITI_int));
	if (currSize->iclocksv_str == 0)
	{
		pPart->curr->clocksv.strData = NULL;
		pPart->curr->clocksv.strSize = NULL;
	}
	else
	{
		pPart->curr->clocksv.strData = (ITI_char**)calloc(currSize->iclocksv_str, sizeof(ITI_char*));
		pPart->curr->clocksv.strSize = (size_t*)calloc(currSize->iclocksv_str, sizeof(size_t));
	}

#ifdef ITI_COMP_SIM
	if (currSize->iz_real == 0)
		pPart->curr->z.realData = NULL;
	else
		pPart->curr->z.realData = (ITI_real**)calloc(currSize->iz_real + currSize->iz_int, sizeof(ITI_real*));
#else
	if (currSize->iz_real == 0)
		pPart->curr->z.realData = NULL;
	else
		pPart->curr->z.realData = (ITI_real*)calloc(currSize->iz_real + currSize->iz_int, sizeof(ITI_real));
#endif
	if (currSize->iz_int == 0)
		pPart->curr->z.intData = NULL;
	else
		pPart->curr->z.intData = (ITI_int*)calloc(currSize->iz_int, sizeof(ITI_int));
	if (currSize->iz_str == 0)
	{
		pPart->curr->z.strData = NULL;
		pPart->curr->z.strSize = NULL;
	}
	else
	{
		pPart->curr->z.strData = (ITI_char**)calloc(currSize->iz_str, sizeof(ITI_char*));
		pPart->curr->z.strSize = (size_t*)calloc(currSize->iz_str, sizeof(size_t));
	}

#ifdef ITI_COMP_SIM
	if (currSize->iz_real == 0)
		pPart->curr->pre_z.realData = NULL;
	else
		pPart->curr->pre_z.realData = (ITI_real**)calloc(currSize->iz_real, sizeof(ITI_real*));
#else
	if (currSize->iz_real == 0)
		pPart->curr->pre_z.realData = NULL;
	else
		pPart->curr->pre_z.realData = (ITI_real*)calloc(currSize->iz_real, sizeof(ITI_real));
#endif
	if (currSize->iz_int == 0)
		pPart->curr->pre_z.intData = NULL;
	else
		pPart->curr->pre_z.intData = (ITI_int*)calloc(currSize->iz_int, sizeof(ITI_int));
	if (currSize->iz_str == 0)
	{
		pPart->curr->pre_z.strData = NULL;
		pPart->curr->pre_z.strSize = NULL;
	}
	else
	{
		pPart->curr->pre_z.strData = (ITI_char**)calloc(currSize->iz_str, sizeof(ITI_char*));
		pPart->curr->pre_z.strSize = (size_t*)calloc(currSize->iz_str, sizeof(size_t));
	}

#ifdef ITI_COMP_SIM
	InitSynchStrsData(&pPart->curr->synchStrsData.pStrData, currSize->ip_str, 1);
	InitSynchStrsData(&pPart->curr->synchStrsData.zStrData, currSize->iz_str, 0);
	InitSynchStrsData(&pPart->curr->synchStrsData.pre_zStrData, currSize->iz_str, 0);
	InitSynchStrsData(&pPart->curr->synchStrsData.vStrData, currSize->iv_str, 0);
	InitSynchStrsData(&pPart->curr->synchStrsData.clocksvStrData, currSize->iz_str, 0);
#endif

	if (currSize->ix == 0)
	{
		pPart->curr->iReinit = NULL;
		pPart->curr->xReinit = NULL;
		pPart->curr->xChanged = NULL;
	}
	else
	{
		pPart->curr->iReinit = (ITI_uint*)calloc(currSize->ix, sizeof(ITI_uint));
		pPart->curr->xReinit = (ITI_real*)calloc(currSize->ix, sizeof(ITI_real));
		pPart->curr->xChanged = (ITI_uint*)calloc(currSize->ix, sizeof(ITI_uint));
	}

#ifdef ITI_COMP_SIM
	ws = &pPart->curr->ws;
	InitWorkSpace(ws,currSize);

	for (i = 0; i < currSize->iv_real; i++) {
		pPart->curr->v.realData[i] = ws->v.realData[i];
	}

	for (i = 0; i < currSize->ip_real; i++) {
		pPart->curr->p.realData[i] = ws->p.realData[i];
	}

	for (i = 0; i < currSize->iz_real; i++)
	{
		pPart->curr->z.realData[i] = ws->z.realData[i];
		pPart->curr->pre_z.realData[i] = ws->pre_z.realData[i];
	}

	for (i = 0; i < currSize->ibx; i++) {
		pPart->curr->bx[i] = &(ws->bx[i]);
		pPart->curr->bx_tmp[i] = &(ws->bx_tmp[i]);
	}

	for (i = 0; i < currSize->iclocksv_real; i++) {
		pPart->curr->clocksv.realData[i] = ws->clocksv.realData[i];
	}
#endif

	AllocZFData(pPart->curr, model->partFunctions[0].dataZF, 1, 0);

	if (currSize->isv == 0)
	{
		pPart->curr->sv = NULL;
		pPart->curr->svInit = NULL;
		pPart->curr->sampleTime = NULL;
	}
	else
	{
		pPart->curr->sv = (ITI_int*)calloc(currSize->isv, sizeof(ITI_int));
		pPart->curr->svInit = (ITI_int*)calloc(currSize->isv, sizeof(ITI_int));
		pPart->curr->sampleTime = (ITI_SampleTime*)calloc(currSize->isv, sizeof(ITI_SampleTime));
	}

	if (currSize->icnd == 0)
		pPart->curr->cNd = NULL;
	else
	{
		pPart->curr->cNd = (ITI_CurveData_ND *)calloc(currSize->icnd, sizeof(ITI_CurveData_ND));
#ifdef ITI_COMP_SIM
		if (pPart->curr->cNd == NULL) {
			return NotifyAllocErrorAndUnloadDll(&pPart->curr->sInfo, model);
		}
#endif
	}
	iRet = InitCurveDataND(pPart->curr->cNd, model->partFunctions[pid].curveNDs, currSize->icnd, NULL);
#ifdef ITI_COMP_SIM
	if (iRet != SOLVER_SUCCESS_END) {
		return NotifyAllocErrorAndUnloadDll(&pPart->curr->sInfo, model);
	}
#endif
	if (currSize->icset == 0)
		pPart->curr->cSet = NULL;
	else
	{
		pPart->curr->cSet = (ITI_CurveSetData *)calloc(currSize->icset, sizeof(ITI_CurveSetData));
#ifdef ITI_COMP_SIM
		if (pPart->curr->cSet == NULL) {
			return NotifyAllocErrorAndUnloadDll(&pPart->curr->sInfo, model);
		}
#endif
	}
	iRet = InitCurveSetData(pPart->curr->cSet, model->partFunctions[pid].curveSets, currSize->icset, NULL);
#ifdef ITI_COMP_SIM
	if (iRet != SOLVER_SUCCESS_END) {
		return NotifyAllocErrorAndUnloadDll(&pPart->curr->sInfo, model);
	}
#endif

	InitDataArrays(pPart->curr, currSize->iarr, model->partFunctions[0].arrayData, 0);

	if (currSize->ics == 0)
		pPart->curr->cs = NULL;
	else
		pPart->curr->cs = (ITI_CurveCallState*)calloc(currSize->ics, sizeof(ITI_CurveCallState));
	for (i = 0; i < currSize->ics; i++) {
		ITI_uint j;
		if (model->partFunctions[pid].seqCsSizes[i] == 0)
		{
			pPart->curr->cs[i].pSeqCs = NULL;
			continue;
		}
		pPart->curr->cs[i].pSeqCs = (ITI_SeqCallState*)calloc(model->partFunctions[pid].seqCsSizes[i], sizeof(ITI_SeqCallState));
		for (j = 0; j < model->partFunctions[pid].seqCsSizes[i]; j++)
			pPart->curr->cs[i].pSeqCs[j].iPos = -1;
	}

	if (currSize->ihcs == 0)
		pPart->curr->hcs = NULL;
	else
		pPart->curr->hcs = (ITI_HystCurveCallState*)calloc(currSize->ihcs, sizeof(ITI_HystCurveCallState));
	for (i = 0; i < currSize->ihcs; i++)
	{
		 
		 
		pPart->curr->hcs[i].pSeqCs = (ITI_SeqCallState*)calloc(3, sizeof(ITI_SeqCallState));
		pPart->curr->hcs[i].pSeqCs->iPos = -1;
	}

	if (currSize->idb > 0)
		pPart->curr->db = (ITI_DelayBuffer*)calloc(currSize->idb, sizeof(ITI_DelayBuffer));
	else
		pPart->curr->db = NULL;
	InitDelayBuffers(pPart->curr->db, currSize->idb, model->partFunctions[0].delayInfos, 0);

#if defined(ITI_COMP_SIM)
	{
		int i_realDelay, i_intDelay;
		GetNumDelay(pPart->curr->db, currSize->idb, &i_realDelay, &i_intDelay);
		if (i_realDelay > 0)
			pPart->curr->sInfo.aniData.realDelayData = (ITI_real*)calloc(i_realDelay, sizeof(ITI_real));
		else
			pPart->curr->sInfo.aniData.realDelayData = NULL;
		if (i_intDelay > 0)
			pPart->curr->sInfo.aniData.intDelayData = (ITI_int*)calloc(i_intDelay, sizeof(ITI_int));
		else
			pPart->curr->sInfo.aniData.intDelayData = NULL;
	}
#endif

	if (currSize->iDPB == 0)
		pPart->curr->iDPbd = NULL;
	else
		pPart->curr->iDPbd = (ITI_DPBlockData*)calloc(currSize->iDPB, sizeof(ITI_DPBlockData));

	InitDPBlockData(pPart->curr->iDPbd, &pPart->curr->stateIncidence, model->partFunctions[0].DPBlockSizes, currSize->iDPB, 0);

	if (currSize->numBlocks == 0)
		pPart->curr->ibd = NULL;
	else {
		pPart->curr->ibd = (ITI_BlockData*)calloc(currSize->numBlocks, sizeof(ITI_BlockData));
		InitBlockData(pPart->curr->ibd, currSize->numBlocks, model->partFunctions[pPart->pid].blockSizes, model->partFunctions[pPart->pid].numJacColsData, model->partFunctions[pPart->pid].DPBlockSizes, 0);
		model->partFunctions[pPart->pid].InitBlockVars(pPart->curr->ibd);
	}

	AllocAssertData(&pPart->curr->sInfo.assertData, currSize->iass, 0);

	pPart->curr->smm = (ITI_StateMinMax*)calloc(1, sizeof(ITI_StateMinMax));
	InitStateMinMax(pPart->curr->smm, currSize->numStateAttr);
#ifdef ITI_COMP_SIM
	ResetWarningStack(&pPart->curr->sInfo);
#endif

	pPart->curr->stateNames = (char**)calloc(pPart->curr->size.ix, sizeof(char *));
	pPart->curr->dstateNames = (char**)calloc(pPart->curr->size.ix, sizeof(char *));
	pPart->curr->stateSynonyms = (char**)calloc(pPart->curr->size.ix, sizeof(char *));

	if (model->partFunctions[pPart->pid].GetStateNames) {
		model->partFunctions[pPart->pid].GetStateNames(pPart);
	}

	return SOLVER_SUCCESS_END;
}

ITI_SolverData* CreateSolverData(const char* modelName, int nParams, double* pValues, TRACE_FUNC* pTraceFunc, CreateSolverContextFunc CreateSolverContext) {
	return CreateSolverDataExtParams(modelName, nParams, pValues, pTraceFunc, CreateSolverContext, NULL);
}

ITI_SolverData* CreateSolverDataExtParams(const char* modelName, int nParams, double* pValues, TRACE_FUNC* pTraceFunc, CreateSolverContextFunc CreateSolverContext, ITI_parameterData* params) {
	ITI_ModelData* pModelData;
	ITI_ModelFunctions* pModelFunc;
	ITI_ModelSize modelSize;
	size_t pid;
	ITI_Partition* pPart;

	ITI_SolverData* pSolverData = (ITI_SolverData*)calloc(1, sizeof(ITI_SolverData));

	if (pSolverData == NULL)
		return NULL;

	pModelData = &pSolverData->modelData;
	pModelFunc = &pSolverData->model;
	
	 
	InitMemory(&pModelData->currMem, 0, 0);
	InitMemory(&pModelData->funcMem, 0, 0);
	InitMemory(&pModelData->strMem, 0, 0);

	pSolverData->ss.tStop = 0.0;
	pSolverData->ss.dtMin = 0.0;

	InitModelSizes(&modelSize);
	if (InitModelInterface(&pSolverData->model, modelName, pTraceFunc, &modelSize) != SOLVER_SUCCESS_END) {
		FreeSolverData(pSolverData);
		return NULL;
	}
#ifndef ITI_COMP_SIM
	if ((pValues != NULL) && (nParams != (modelSize.ip_int + modelSize.ip_real + modelSize.ip_str))){
		printf("\nERROR: The number of parameters from parameter file (%d) is not equal to the number of model parameters (%d).\nPlease check the parameter file.\n\n", nParams, (modelSize.ip_int + modelSize.ip_real + modelSize.ip_str));
		FreeSolverData(pSolverData);
		return NULL;
	}
#endif

	 
	pSolverData->partition = (ITI_Partition*)calloc(modelSize.ipart, sizeof(ITI_Partition));

	for (pid = 0; pid < (size_t)modelSize.ipart; ++pid) {
		pSolverData->partition[pid].curr = (ITI_PartitionVar*)calloc(1, sizeof(ITI_PartitionVar));
		pSolverData->partition[pid].curr->solverData = pSolverData;
		pSolverData->partition[pid].pid = pid;
	}
	pPart = &pSolverData->partition[0];  
	pPart->transient = pPart->curr;
	pPart->curr->size = modelSize;

	 
	AllocIGData(pPart, calloc);
	if (pPart->curr->size.iig > 0)
		pModelFunc->InitInferenceGraph(pPart, &pSolverData->modelData);

	 
	pPart->curr->partitionData = (ITI_PartitionData*)calloc(pPart->curr->size.ipart, sizeof(ITI_PartitionData));
	pModelFunc->GetPartitionData(pPart, &pSolverData->modelData);

	for (pid = 0; pid < (size_t)modelSize.ipart; ++pid) {	 
		if (pid == 0) {
			pSolverData->partition[pid].base = NULL;
			pSolverData->partition[pid].sub = NULL;
			pSolverData->partition[pid].transient = pSolverData->partition[pid].curr;
		}
		else {
			pSolverData->partition[pid].transient = pPart->transient;
			if (pSolverData->partition[0].curr->partitionData[pid].type == CPT_BaseClock) {
				pSolverData->partition[pid].base = pSolverData->partition[pid].curr;
				pSolverData->partition[pid].sub = NULL;
			}
			else {
				pSolverData->partition[pid].base = pSolverData->partition[pSolverData->partition[0].curr->partitionData[pid].baseid].curr;
				pSolverData->partition[pid].sub = pSolverData->partition[pid].curr;
			}
		}
	}

	pModelFunc->partFunctions[0].GetModelInfo(&pSolverData->partition[0].curr->modelInfo);

	pSolverData->sc = (ITI_SolverContextBase**)calloc(modelSize.ipart, sizeof(ITI_SolverContextBase**));

	pSolverData->stat = (ITI_SolverStatistic*)calloc(modelSize.ipart, sizeof(ITI_SolverStatistic));

	for (pid = 0; pid < (size_t)modelSize.ipart; ++pid) {
		ITI_ModelSize *currSize;

		if (pid > 0) {
			InitModelSizes(&(pSolverData->partition[pid].curr->size));
			pModelFunc->partFunctions[pid].GetPartitionSizes(calloc, &(pSolverData->partition[pid].curr->size));
			 
			pSolverData->partition[pid].curr->size.ipart = 0;
		}

		if (CreatePartition(pSolverData, pid, pValues, pTraceFunc, params) != SOLVER_SUCCESS_END){
			FreeSolverData(pSolverData);
			return NULL;
		}

		if (pid == 0) {
			pSolverData->sc[pid] = (ITI_SolverContextBase*)CreateSolverContext(pid, pSolverData, External);
		}
		else {
			




			pSolverData->sc[pid] = NULL;
		}

		pPart = &pSolverData->partition[pid];
		pPart->curr->sInfo.pSolverData = pSolverData;
		currSize = &pPart->curr->size;

#ifndef ITI_COMP_SIM
		if (pid == 0) {
			g_currMem = &pSolverData->modelData.currMem;
			g_sInfo = &pPart->curr->sInfo;
		}
#endif

		pModelFunc->AllocateRecords(pPart);

		pSolverData->stat[pid].iValidSteps = 0;
		pSolverData->stat[pid].iRhsCalls = 0;
		pSolverData->stat[pid].iRoots = 0;
		pSolverData->stat[pid].iTimeEvents = 0;

		InitBlockStatistics(&pSolverData->stat[pid], currSize->numBlocks);

		pPart->curr->_hyst_init_data = pSolverData->model.partFunctions[pid]._hyst_init_data;

#ifdef ITI_COMP_SIM
		AllocEventCounters(&pSolverData->stat[pid], currSize->izf, currSize->iz_real + currSize->iz_int + currSize->iz_str, 0);
#endif
		InitPerformanceTiming(&pPart->curr->performanceData, currSize->numBlocks);
	}

#ifdef ITI_COMP_SIM
 
	pModelData->traceData.len = 0;
	pModelData->traceData.line = 0;
	pModelData->traceData.line_ext = 0;
	pModelData->traceData.buffer = 0;
	pModelData->traceData.temp = 0;
	pModelData->traceData.temp2 = 0;
	pModelData->traceData.start = 0;
	pModelData->traceData.memObj.allocateMemory = 0;
	pModelData->traceData.memObj.freeMemory = 0;
	pModelData->traceData.memObj2.allocateMemory = 0;
	pModelData->traceData.memObj2.freeMemory = 0;
	pModelData->traceData.memObj3.allocateMemory = 0;
	pModelData->traceData.memObj3.freeMemory = 0;
	 

	pSolverData->UpdateStrDataInSimxFunc = (ITI_UpdateStrDataInSimxFunc*)calloc(1, sizeof(ITI_UpdateStrDataInSimxFunc));

#endif
	
	if (modelSize.iExtObj == 0)
		pModelData->extObj = NULL;
	else
		pModelData->extObj = (ITI_void**)calloc(modelSize.iExtObj, sizeof(ITI_void*));

#ifdef ITI_COMP_SIM
	 
	pSolverData->tmpData.allocated = 0;

#if (defined(_ROOT_MESSAGE_FILE) || defined(_EVENT_STEP))
	{
		 
		FILE* roots = fopen("roots.txt", "w+");
		fclose(roots);
	}
#endif
#endif  

	return pSolverData;
}

ITI_SolverState CreatePartitionSolvers(ITI_SolverData* sd) {
	ITI_PartitionData* pd = sd->partition[0].curr->partitionData;
	size_t pid;
	ITI_Partition* pPart;

	for (pid = 1; pid < (size_t)sd->partition[0].curr->size.ipart; ++pid) {
		ITI_PartitionSolverMethod psm;
		



		pPart = &sd->partition[pid];

		 
		if (IsBasePartition(pPart)) {
			continue;
		}

		 
		if (!IsContinuousPartition(pPart)) {
			 
			if (sd->sc[pid] == NULL) {
				 
				sd->sc[pid] = (ITI_SolverContextBase*)CreatePartitionSolver(pid, sd, UnknownSolver);
			}
			continue;
		}

		 
		psm = GetSolverMethod(pPart);
		if (sd->sc[pid] != NULL && psm != sd->sc[pid]->solverMethod) {
			if (sd->sc[pid]->FreeSolver) {
				sd->sc[pid]->FreeSolver(sd->sc[pid]);
			}
			sd->sc[pid] = NULL;
		}

		if (sd->sc[pid] == NULL) {
			switch (psm) {
			case External:
			case ExplicitEulerInline:
			case ImplicitEulerInline:
			case ImplicitTrapezoidInline:
				 
				sd->sc[pid] = (ITI_SolverContextBase*)sd->sc[0]->CreateSolver(pid, sd, psm);
				break;
			case ExplicitEuler:
			case ExplicitMidPoint2:
			case ExplicitRungeKutta4:
			case ImplicitEuler:
			case ImplicitTrapezoid:
				sd->sc[pid] = (ITI_SolverContextBase*)CreatePartitionSolver(pid, sd, psm);
				break;
			default:
				 
				return SOLVER_ERROR;
			}
		}
	}
	return SOLVER_SUCCESS_END;
}

ITI_SolverState TerminateModelPartitions(ITI_SolverData* sd) {
	ITI_PartitionData* pd = sd->partition[0].curr->partitionData;
	size_t pid;
	ITI_SolverState iRet = SOLVER_SUCCESS_END;
	ITI_SolverState iRetPart;

	for (pid = 0; pid < (size_t)sd->partition[0].curr->size.ipart; ++pid) {
		if (sd->partition[0].curr->partitionData[pid].type == CPT_BaseClock)
			continue;
		iRetPart = TerminatePartition(pid, sd);
		if (iRetPart < SOLVER_SUCCESS_END) {
			iRet = iRetPart;
		}
	}
	sd->model.ReleaseAllMemory(&sd->modelData.currMem);
	sd->model.ReleaseAllMemory(&sd->modelData.strMem);

	return iRet;
}

#ifdef ITI_COMP_SIM
void FreeWorkSpace(ITI_WorkSpace* ws) {
	FreeCompositeData(&ws->vtmp, 0);
	FreeCompositeData(&ws->v, 0);
	FreeCompositeData(&ws->p, 0);
	FreeCompositeData(&ws->z, 0);
	FreeCompositeData(&ws->pre_z, 0);
	FreeCompositeData(&ws->clocksv, 0);
	free(ws->vtmp_mem_real); ws->vtmp_mem_real = NULL;
	free(ws->v_mem_real); ws->v_mem_real = NULL;
	free(ws->p_mem_real); ws->p_mem_real = NULL;
	free(ws->z_mem_real); ws->z_mem_real = NULL;
	free(ws->pre_z_mem_real); ws->pre_z_mem_real = NULL;
	free(ws->x); ws->x = NULL;
	free(ws->px); ws->px = NULL;
	free(ws->bx); ws->bx = NULL;
	free(ws->bx_tmp); ws->bx_tmp = NULL;
	free(ws->clocksv_mem_real); ws->clocksv_mem_real = NULL;
}

#endif

void FreePartition(ITI_Partition* pPart) {
	ITI_int i;
	ITI_SolverData* pSolverData;
	if (pPart == NULL)
		return;
	pSolverData = pPart->curr->solverData;

	if (pPart->pid == 0) {
#ifdef ITI_COMP_SIM
		FreeWorkSpace(&pPart->curr->ws);
#endif
		FreeIGData(pPart, &free);
		free(pPart->curr->partitionData);
		pPart->curr->partitionData = NULL;
	}

	FreeDataArrays2(&pSolverData->modelData.currMem, pPart->curr->arrays, pPart->curr->size.iarr, 0);
	pPart->curr->arrays = NULL;
	pSolverData->model.FreeRecords(pPart, &pSolverData->modelData);

#ifdef ITI_COMP_SIM
	free(pPart->curr->y_mem_real); pPart->curr->y_mem_real = NULL;
	free(pPart->curr->u_mem_real); pPart->curr->u_mem_real = NULL;
#endif
	FreeCompositeData(&pPart->curr->p, 0);
	for (i = 0; i < pPart->curr->size.ip_arr; i++) {
		free(pPart->curr->arr_p[i].dims); pPart->curr->arr_p[i].dims = NULL;
		free(pPart->curr->arr_p[i].realValues); pPart->curr->arr_p[i].realValues = NULL;
		free(pPart->curr->arr_p[i].intValues); pPart->curr->arr_p[i].intValues = NULL;
		free(pPart->curr->arr_p[i].charValues); pPart->curr->arr_p[i].charValues = NULL;
	}
	pPart->curr->size.ip_arr = 0;
	free(pPart->curr->arr_p); pPart->curr->arr_p = NULL;

	free(pPart->curr->x_bak);
	pPart->curr->x_bak = NULL; pPart->curr->x = NULL;
	free(pPart->curr->xdot_bak);
	pPart->curr->xdot_bak = NULL; pPart->curr->xdot = NULL;
	free(pPart->curr->res_i); pPart->curr->res_i = NULL;
	free(pPart->curr->res); pPart->curr->res = NULL;
	free(pPart->curr->bx); pPart->curr->bx = NULL;
	 
	free(pPart->curr->bx_tmp); pPart->curr->bx_tmp = NULL;

	free(pPart->curr->xImpact); pPart->curr->xImpact = NULL;

	FreeCompositeData(&pPart->curr->v, 0);
	 
	FreeCompositeData(&pPart->curr->vtmp, 0);
	FreeCompositeData(&pPart->curr->z, 0);
	FreeCompositeData(&pPart->curr->pre_z, 0);

	free(pPart->curr->iReinit); pPart->curr->iReinit = NULL;
	free(pPart->curr->xReinit); pPart->curr->xReinit = NULL;
	free(pPart->curr->xChanged); pPart->curr->xChanged = NULL;

	FreeZFData(pPart->curr, 1, 0);

	free(pPart->curr->sv); pPart->curr->sv = NULL;
	free(pPart->curr->svInit); pPart->curr->svInit = NULL;
	free(pPart->curr->sampleTime); pPart->curr->sampleTime = NULL;

	if (pPart->curr->sInfo.timeTriggeredClock)
		free(pPart->curr->sInfo.timeTriggeredClock);

#ifdef ITI_COMP_SIM
	free(pPart->curr->bxd); pPart->curr->bxd = NULL;

	FreeSynchStrsData(&pPart->curr->synchStrsData.pStrData);
	FreeSynchStrsData(&pPart->curr->synchStrsData.vStrData);
	FreeSynchStrsData(&pPart->curr->synchStrsData.pre_zStrData);
	FreeSynchStrsData(&pPart->curr->synchStrsData.zStrData);
	FreeSynchStrsData(&pPart->curr->synchStrsData.clocksvStrData);
#endif
	FreeCurveSetData(pPart->curr->cSet, pPart->curr->size.icset, NULL);
	free(pPart->curr->cSet); pPart->curr->cSet = NULL;

	FreeCurveDataND(pPart->curr->cNd, pPart->curr->size.icnd, NULL);
	free(pPart->curr->cNd); pPart->curr->cNd = NULL;

	for (i = 0; i < pPart->curr->size.ics; i++)
		free(pPart->curr->cs[i].pSeqCs);
	pPart->curr->size.ics = 0;
	free(pPart->curr->cs); pPart->curr->cs = NULL;
	
	for (i = 0; i < pPart->curr->size.ihcs; i++)
		free(pPart->curr->hcs[i].pSeqCs);
	pPart->curr->size.ihcs = 0;
	free(pPart->curr->hcs); pPart->curr->hcs = NULL;

#ifdef ITI_COMP_SIM
	free(pPart->curr->sInfo.aniData.realDelayData); pPart->curr->sInfo.aniData.realDelayData = NULL;
	free(pPart->curr->sInfo.aniData.intDelayData); pPart->curr->sInfo.aniData.intDelayData = NULL;
#endif

	FreeDelayBuffers(pPart->curr->db, pPart->curr->size.idb, 0);
	 
	free(pPart->curr->db); pPart->curr->db = NULL;

	FreeDPBlockData(pPart->curr->iDPbd, &pPart->curr->stateIncidence, pPart->curr->size.iDPB, 0);
	free(pPart->curr->iDPbd); pPart->curr->iDPbd = NULL;

	FreeBlockData(pPart->curr->ibd, pPart->curr->size.numBlocks, 0);
	free(pPart->curr->ibd); pPart->curr->ibd = NULL;

	FreeStateMinMax(pPart->curr->smm);
	free(pPart->curr->smm); pPart->curr->smm = NULL;

	FreeAssertData(&pPart->curr->sInfo.assertData, 0);

	FreeCompositeData(&pPart->curr->y, 0);
	FreeCompositeData(&pPart->curr->u, 0);

	free(pPart->curr->stateNames);
	free(pPart->curr->dstateNames);
	free(pPart->curr->stateSynonyms);

	free(pPart->curr->clocksv.realData);
	free(pPart->curr->clocksv.intData);
	free(pPart->curr->clocksv.strData);
	free(pPart->curr->clocksv.strSize);
}


void FreeSolverData(ITI_SolverData* pSolverData)
{
	ITI_int iParts;
	ITI_int pid;
	if (!pSolverData)
		return;

	if (pSolverData->partition) {
		iParts = pSolverData->partition[0].curr->size.ipart;
		for (pid = iParts - 1; pid != -1; --pid) {
			if (pSolverData->sc[pid]) {
				pSolverData->sc[pid]->FreeSolver(pSolverData->sc[pid]);
				pSolverData->sc[pid] = NULL;
			}
		}
		for (pid = iParts - 1; pid != -1; --pid) {
			ITI_Partition *pPart = &pSolverData->partition[pid];
			FreePerformanceTiming(pPart->curr->performanceData);
			FreePartition(pPart);
			free(pPart->curr);

			FreeBlockStatistics(&pSolverData->stat[pid]);
#ifdef ITI_COMP_SIM
			FreeEventCounters(&pSolverData->stat[pid], 0);
#endif
		}
	}

	free(pSolverData->modelData.extObj); pSolverData->modelData.extObj = NULL;
	free(pSolverData->model.partFunctions); pSolverData->model.partFunctions = NULL;

	if (pSolverData->model.FreeAllMemory) {
		pSolverData->model.FreeAllMemory(&pSolverData->modelData.currMem);
		pSolverData->model.FreeAllMemory(&pSolverData->modelData.funcMem);
		pSolverData->model.FreeAllMemory(&pSolverData->modelData.strMem);
	}
#ifdef ITI_COMP_SIM

	free(pSolverData->UpdateStrDataInSimxFunc);

	if (pSolverData->model.hModel)
	{
		FreeLibrary((HMODULE)pSolverData->model.hModel);
		pSolverData->model.hModel = NULL;
	}
#endif
	free(pSolverData->partition);
	free(pSolverData->stat);
	free(pSolverData->sc);
	free(pSolverData); 
}






