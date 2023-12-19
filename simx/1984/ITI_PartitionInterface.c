/**
 * ITI_PartitionInterface.c
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#include "ITI_PartitionInterface.h"
#ifndef ITI_SIMULINK_S_FUNC
#include "ITI_SolverHelpers.h"
#endif
ITI_SolverState CalcModelOutputs(size_t pid, void* pData) {
	ITI_SolverData* sd = (ITI_SolverData*)pData;
	ITI_Partition* pPart = &sd->partition[pid];
	ITI_PartFunctions* pPartFunctions = &sd->model.partFunctions[pid];
	ITI_SolverState iRet = SOLVER_SUCCESS_END;

	pPart->curr->sInfo.tracingAllowed = ITI_true;
	iRet = ExceptWrapper2((ModelFunc2)pPartFunctions->CalcOutputs, pPart, &sd->modelData);
	if (iRet == SOLVER_SUCCESS_END)
		iRet = ExceptWrapper2(pPartFunctions->SynchOutputs, pPart, &sd->modelData);

	if (iRet != SOLVER_SUCCESS_END) {
		HandleWarnings(&pPart->curr->sInfo);
		traceError("Error: While computing outputs.\n", &pPart->curr->sInfo);
		HandleTrace(&pPart->curr->sInfo);
		iRet = SOLVER_ERROR;
	}
	ReleaseAllMemory(&sd->modelData.currMem);
	pPart->curr->sInfo.tracingAllowed = ITI_false;
#ifdef ITI_COMP_SIM
	UpdateStates(pPartFunctions->dataX, pPart->curr->size.iSimX_X, pPart->curr->ws, pPart->curr->x);
#endif
	return iRet;
}

ITI_SolverState CalcDerivatives(size_t pid, void* pData) {
	ITI_SolverData* sd = (ITI_SolverData*)pData;
	ITI_Partition *pPart = &sd->partition[pid];
	ITI_PartFunctions* pPartFunctions = &sd->model.partFunctions[pid];
	ITI_SolverState iRet = SOLVER_SUCCESS_END;

	iRet = ExceptWrapper2((ModelFunc2)pPartFunctions->CalcDerivatives, pPart, &sd->modelData);
	






	sd->model.ReleaseAllMemory(&sd->modelData.currMem);

	return iRet;
}

ITI_SolverState CalcInitialDerivativesSafe(size_t pid, void* pData) {
	ITI_SolverData* sd = (ITI_SolverData*)pData;
	ITI_Partition *pPart = &sd->partition[pid];
	ITI_PartFunctions* pPartFunctions = &sd->model.partFunctions[pid];
	ITI_SolverState iRet = SOLVER_SUCCESS_END;

#ifndef ITI_COMP_SIM
	ITI_CompositeData z_tmp, pre_z_tmp, z, pre_z;
	ITI_int* v_int;
	ITI_int i;

	 
	char* strAnalysisTypeDetail = pPart->curr->sInfo.strAnalysisTypeDetail;
	ITI_bool isEvent = pPart->curr->sInfo.isEvent;
	ITI_bool isFirstEventStep = pPart->curr->sInfo.isFirstEventStep;
	ITI_bool tracingAllowed = pPart->curr->sInfo.tracingAllowed;

	pPart->curr->sInfo.strAnalysisTypeDetail = "residuals";
	pPart->curr->sInfo.isEvent = ITI_false;
	pPart->curr->sInfo.isFirstEventStep = ITI_false;
	pPart->curr->sInfo.tracingAllowed = ITI_false;

	z_tmp.realData = (ITI_real*)calloc(pPart->curr->size.iz_real, sizeof(ITI_real));
	z_tmp.intData = (ITI_int*)calloc(pPart->curr->size.iz_int, sizeof(ITI_int));
	z_tmp.strData = (ITI_char**)calloc(pPart->curr->size.iz_str, sizeof(ITI_char*));
	z_tmp.strSize = (size_t*)calloc(pPart->curr->size.iz_str, sizeof(size_t));

	pre_z_tmp.realData = (ITI_real*)calloc(pPart->curr->size.iz_real, sizeof(ITI_real));
	pre_z_tmp.intData = (ITI_int*)calloc(pPart->curr->size.iz_int, sizeof(ITI_int));
	pre_z_tmp.strData = (ITI_char**)calloc(pPart->curr->size.iz_str, sizeof(ITI_char*));
	pre_z_tmp.strSize = (size_t*)calloc(pPart->curr->size.iz_str, sizeof(size_t));

	 
	v_int = (ITI_int*)calloc(pPart->curr->size.iv_int, sizeof(ITI_int));

	for (i = 0; i < pPart->curr->size.iv_int; i++) {
		v_int[i] = pPart->curr->v.intData[i];
	}

	z.realData = pPart->curr->z.realData;
	z.intData = pPart->curr->z.intData;
	z.strData = pPart->curr->z.strData;
	z.strSize = pPart->curr->z.strSize;

	pre_z.realData = pPart->curr->pre_z.realData;
	pre_z.intData = pPart->curr->pre_z.intData;
	pre_z.strData = pPart->curr->pre_z.strData;
	pre_z.strSize = pPart->curr->pre_z.strSize;

	pPart->curr->z.realData = z_tmp.realData;
	pPart->curr->z.intData = z_tmp.intData;
	pPart->curr->z.strData = z_tmp.strData;
	pPart->curr->z.strSize = z_tmp.strSize;

	pPart->curr->pre_z.realData = pre_z_tmp.realData;
	pPart->curr->pre_z.intData = pre_z_tmp.intData;
	pPart->curr->pre_z.strData = pre_z_tmp.strData;
	pPart->curr->pre_z.strSize = pre_z_tmp.strSize;

	Restore_z_data(pPart->curr, &sd->modelData, &z);
	Update_pre_z_data(pPart->curr, &sd->modelData);

	pPart->curr->sInfo.isFirstRhsCall = ITI_true;
	iRet = pPartFunctions->CalcDerivatives(pPart, &sd->modelData);
	ReleaseAllMemory(&sd->modelData.currMem);
	pPart->curr->sInfo.isFirstRhsCall = ITI_false;

	pPart->curr->sInfo.strAnalysisTypeDetail = strAnalysisTypeDetail;
	pPart->curr->sInfo.isEvent = isEvent;
	pPart->curr->sInfo.isFirstEventStep = isFirstEventStep;
	pPart->curr->sInfo.tracingAllowed = tracingAllowed;

	 
	pPart->curr->z.realData = z.realData;
	pPart->curr->z.intData = z.intData;
	pPart->curr->z.strData = z.strData;
	pPart->curr->z.strSize = z.strSize;

	pPart->curr->pre_z.realData = pre_z.realData;
	pPart->curr->pre_z.intData = pre_z.intData;
	pPart->curr->pre_z.strData = pre_z.strData;
	pPart->curr->pre_z.strSize = pre_z.strSize;

	for (i = 0; i < pPart->curr->size.iv_int; i++) {
		pPart->curr->v.intData[i] = v_int[i];
	}
	free(v_int);

	FreeCompositeData(&z_tmp, 0);
	FreeCompositeData(&pre_z_tmp, 0);
#endif 
	return iRet;
}

ITI_SolverState HandleSaveOutputs(size_t pid, ITI_SolverData* sd, unsigned int iSaveMode, ITI_bool bUpdate_tProt) {
	ITI_SolverState iRet = SOLVER_SUCCESS_END;
	ITI_Partition *pPart = &sd->partition[pid];
	
	if (iSaveMode & sd->ss.saveModeB) {
		if (bUpdate_tProt)
			sd->sc[pid]->tProt = pPart->curr->t;
		iRet = CalcModelOutputs(pid, sd);
		if (iRet == SOLVER_SUCCESS_END && sd->sc[pid]->OnSaveOutputsSolver) {
			sd->sc[pid]->OnSaveOutputsSolver(pid, sd, ITI_true);
		}
	}
	return iRet;
}

ITI_SolverState HandleSyncOutputs(size_t pid, ITI_SolverData* sd, unsigned int iSaveMode, ITI_bool bUpdate_tProt) {
	ITI_Partition *pPart = &sd->partition[pid];
	ITI_SolverState iRet = SOLVER_SUCCESS_END;

	if (iSaveMode & sd->ss.saveModeB) {
		if(bUpdate_tProt)
			sd->sc[pid]->tProt = pPart->curr->t;
		iRet = ExceptWrapper2(sd->model.partFunctions[pid].SynchOutputs, pPart, &sd->modelData);
		if (iRet == SOLVER_SUCCESS_END && sd->sc[pid]->OnSaveOutputsSolver) {
			sd->sc[pid]->OnSaveOutputsSolver(pid, sd, ITI_true);
		}
	}
	return iRet;
}

void CheckSampleActive(size_t pid, ITI_SolverData* sd) {
	ITI_Partition *pPart = &sd->partition[pid];
	ITI_int i;
	for (i = 0; i < pPart->curr->size.isv; i++) {
		 
		ITI_bui_minus(&sd->sc[pid]->timeEventCounter[i], &sd->sc[pid]->ui_dtHit);
		if (ITI_bui_is_zero(&sd->sc[pid]->timeEventCounter[i])) {
			 
			sd->sc[pid]->timeEventCounter[i] = sd->sc[pid]->timeEventMax[i];
			pPart->curr->sv[i] = 1;
			sd->sc[pid]->bTimeEvent = ITI_true;
			sd->sc[pid]->hitIsSample = ITI_true;
		}
	}
}

void SetInterfaceFunctions(size_t pid, void* pData,
						   SolverInterfaceFunc pOnPrepareSaveOutputs,
	                       SolverInterfaceLogFunc pOnSaveOutputs,
						   SolverInterfaceGlobalFunc pOnFinishSaveOutputs,
						   SolverInterfaceFunc pOnValidEventStepFunc,
						   SolverInterfaceFunc pOnBeforeEventStepFunc) 
{
	ITI_SolverData* sd = (ITI_SolverData*)pData;
	sd->sc[pid]->OnPrepareSaveOutputs = pOnPrepareSaveOutputs;
	sd->sc[pid]->OnSaveOutputsSolver = pOnSaveOutputs;
	sd->sc[pid]->OnFinishSaveOutputs = pOnFinishSaveOutputs;
	sd->sc[pid]->OnValidEventStepSolver = pOnValidEventStepFunc;
	sd->sc[pid]->OnBeforeEventStepSolver = pOnBeforeEventStepFunc;
}


#ifdef ITI_COMP_SIM
ITI_SolverState ConstConditionsChanged(void* pData, int afterReset) {
	ITI_SolverData* sd = (ITI_SolverData*)pData;
	ITI_SolverState iRet = SOLVER_SUCCESS_END;
	ITI_Partition* pPart = &sd->partition[0];

	sd->partition[0].transient->sInfo.bAssertActive = ITI_false;
	if (sd->model.partFunctions[0].InitializeConstants(pPart, &sd->modelData) != SOLVER_SUCCESS_END) {
		HandleWarnings(&pPart->transient->sInfo);
		pPart->transient->sInfo.trace(0, 4, "Solver Error", "Initialization of constants failed during ConstConditionsChanged.", (void*)&pPart->transient->sInfo);
		sd->sc[0]->state = SOLVER_ERROR_IN_INITIALIZATION;
		return sd->sc[0]->state;
	}
	if (sd->model.partFunctions[0].InitializeParameterDependent(pPart, &sd->modelData) != SOLVER_SUCCESS_END) {
		HandleWarnings(&pPart->transient->sInfo);
		pPart->transient->sInfo.trace(0, 4, "Solver Error", "Initialization of dependent parameters failed during ConstConditionsChanged.", (void*)&pPart->transient->sInfo);
		sd->sc[0]->state = SOLVER_ERROR_IN_INITIALIZATION;
		return sd->sc[0]->state;
	}
	if (sd->model.partFunctions[0].InitializeTunableParameter(pPart, &sd->modelData) != SOLVER_SUCCESS_END) {
		HandleWarnings(&pPart->transient->sInfo);
		pPart->transient->sInfo.trace(0, 4, "Solver Error", "Initialization of tunable parameters failed during ConstConditionsChanged.", (void*)&pPart->transient->sInfo);
		sd->sc[0]->state = SOLVER_ERROR_IN_INITIALIZATION;
		return sd->sc[0]->state;
	}
	if (afterReset) {
		ITI_int pid;
		for (pid = 0; pid < sd->partition[0].curr->size.ipart; ++pid) {
			pPart = &sd->partition[pid];
			if (!IsBasePartition(pPart)) {
				pPart->curr->t = sd->ss.tStart; 
				if (sd->model.partFunctions[pid].Initialize(pPart, &sd->modelData) != SOLVER_SUCCESS_END) {
					HandleWarnings(&pPart->transient->sInfo);
					pPart->transient->sInfo.trace(0, 4, "Solver Error", "Initialization of model failed during ConstConditionsChanged.", (void*)&pPart->transient->sInfo);
					sd->sc[pid]->state = SOLVER_ERROR_IN_INITIALIZATION;
					return sd->sc[pid]->state;
				}
			}
		}
	}
	iRet = sd->model.ConstConditionsChanged(pPart, &sd->modelData);
	if (afterReset) {
		ITI_int pid;
		for (pid = 0; pid < sd->partition[0].curr->size.ipart; ++pid) {
			pPart = &sd->partition[pid];
			if (!IsBasePartition(pPart)) {
				if (ExceptWrapper2(sd->model.partFunctions[pid].Terminate, pPart, &sd->modelData) > SOLVER_SUCCESS_END) {
					HandleWarnings(&pPart->curr->sInfo);
					pPart->curr->sInfo.trace(0, 4, "Solver Error", "Error during termination.", (void*)&pPart->transient->sInfo);
					sd->sc[pid]->state = SOLVER_ERROR;
					return sd->sc[pid]->state;
				}
			}
		}
	}
	pPart->transient->sInfo.bAssertActive = pPart->transient->sInfo.bAssertOn;
	return iRet;
}
#endif 

#ifndef ITI_SIMULINK_S_FUNC
 
void Trace_to_Screen(int iTab, int iKind, const char* strCapt, const char* strTxt, const void* pVoid)
{
	char strKind[16];
	switch (iKind)
	{
	case Info:
		sprintf(strKind, "Information");
		break;
	case Warning:
		sprintf(strKind, "Warning");
		break;
	case Error:
		sprintf(strKind, "Error");
		break;
	case Debug:
		sprintf(strKind, "Debug");
		break;
	}
	printf("\n%s: %s\n%s\n", strKind, strCapt, strTxt);
}

void ExecModel_OnPrepareSaveOutputs(size_t pid, void* pData)
{
	ITI_ExecModel_Data* peData = (ITI_ExecModel_Data*)GetContainerData(pData);
	char fOutputs[FILENAME_MAX];

	GetOutputFileName(fOutputs, peData->outputFileName, peData->iVariant);

	 

	if (GetSolverSettings(pData)->saveModeB & SaveOutputsEquidistantBit)
	{
		if (GetSolverSettings(pData)->dtProtMin < GetSolverSettings(pData)->dtMin)
			peData->iPlaces = GetNumberOfDecimalPlaces(GetSolverSettings(pData)->dtMin);
		else
			peData->iPlaces = GetNumberOfDecimalPlaces(GetSolverSettings(pData)->dtProtMin);
	}
	else if (GetSolverSettings(pData)->saveModeB & (SaveOutputsEquidistantPostEventsBit | SaveOutputsEquidistantPrePostEventsBit | SaveOutputsEquidistantAllEventStepsBit)) {
		if (GetSolverSettings(pData)->dtProtMin < GetSolverSettings(pData)->dtMin)
			peData->iPlaces = min(GetNumberOfDecimalPlaces(GetSolverSettings(pData)->dtProtMin),17);
		else
			peData->iPlaces = min(GetNumberOfDecimalPlaces(GetSolverSettings(pData)->dtMin),17);

	}
	else
		peData->iPlaces = 17;

	peData->outputs = fopen(fOutputs, "w+");
	if (peData->outputs)
		WriteOutputStreamHeader(peData->outputs, GetOutputData(pData), GetSizeY(pid, pData));
}

void ExecModel_OnSaveOutputs(size_t pid, void* pData, ITI_bool force)
{
	ITI_ExecModel_Data* peData = (ITI_ExecModel_Data*)GetContainerData(pData);

	if (peData->outputs)
		WriteOutput2Stream(peData->outputs, GetOutputData(pData), GetSimVar(pid, pData), GetSizeY(pid, pData), peData->iPlaces, 15);
}

void ExecModel_OnFinishSaveOutputs(void* pData)
{
	ITI_ExecModel_Data* peData = (ITI_ExecModel_Data*)GetContainerData(pData);

	if (peData->outputs)
		fclose(peData->outputs);
	peData->outputs = 0;
}

int ExecModel_OnSetInputs(void* pData, double t, ITI_CompositeData* u)
{
	ITI_ExecModel_Data* peData = (ITI_ExecModel_Data*)GetContainerData(pData);

	if (peData->pSetInputFunc)
		peData->pSetInputFunc(u, t);

	return 0;
}

void ExecModel_OnValidStepFunc(size_t pid, void* pData)
{
	ITI_ExecModel_Data* peData = (ITI_ExecModel_Data*)GetContainerData(pData);

	ShowActTime(&peData->cLast, Get_t(pid, pData), GetSolverSettings(pData)->tStop, 0);
}
#endif