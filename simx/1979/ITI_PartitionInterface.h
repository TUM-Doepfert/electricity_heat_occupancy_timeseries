/**
 * ITI_PartitionInterface.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#if !defined(_ITI_PartitionInterface)
#define _ITI_PartitionInterface

#include "ITI_crt.h"

ITI_FUNCTIONS_API ITI_SolverState CalcModelOutputs(size_t pid, void* pData);
ITI_FUNCTIONS_API ITI_SolverState CalcDerivatives(size_t pid, void* pData);
ITI_FUNCTIONS_API ITI_SolverState CalcInitialDerivativesSafe(size_t pid, void* pData);
ITI_FUNCTIONS_API ITI_SolverState HandleSaveOutputs(size_t pid, ITI_SolverData* sd, unsigned int iSaveMode, ITI_bool bUpdate_tProt);
ITI_FUNCTIONS_API ITI_SolverState HandleSyncOutputs(size_t pid, ITI_SolverData* sd, unsigned int iSaveMode, ITI_bool bUpdate_tProt);
ITI_FUNCTIONS_API void CheckSampleActive(size_t pid, ITI_SolverData* sd);

ITI_FUNCTIONS_API void SetInterfaceFunctions(size_t pid, void* pData,
											 SolverInterfaceFunc pOnPrepareSaveOutputs, 
											 SolverInterfaceLogFunc pOnSaveOutputs,
											 SolverInterfaceGlobalFunc pOnFinishSaveOutputs,
											 SolverInterfaceFunc pOnValidEventStepFunc, 
											 SolverInterfaceFunc pOnBeforeEventStepFunc);

#ifdef ITI_COMP_SIM
ITI_FUNCTIONS_API ITI_SolverState ConstConditionsChanged(void* pData, int afterReset);
#endif

#ifndef ITI_SIMULINK_S_FUNC
 
ITI_FUNCTIONS_API void Trace_to_Screen(int iTab, int iKind, const char* strCapt, const char* strTxt, const void* pVoid);
ITI_FUNCTIONS_API void ExecModel_OnPrepareSaveOutputs(size_t pid, void* pData);
ITI_FUNCTIONS_API void ExecModel_OnSaveOutputs(size_t pid, void* pData, ITI_bool force);
ITI_FUNCTIONS_API void ExecModel_OnFinishSaveOutputs(void* pData);
ITI_FUNCTIONS_API int ExecModel_OnSetInputs(void* pData, double t, ITI_CompositeData* u);
ITI_FUNCTIONS_API void ExecModel_OnValidStepFunc(size_t pid, void* pData);
#endif

 
#define GetParameterData(pid,pData) 		(((ITI_SolverData*)pData)->model.partFunctions[pid].parameters)
#define GetParametersArrData(pid,pData)		(((ITI_SolverData*)pData)->model.partFunctions[pid].parametersArr)
#define GetInputData(pData) 				(((ITI_SolverData*)pData)->model.inputData)
#define GetOutputData(pData) 				(((ITI_SolverData*)pData)->model.outputData)

#define GetSizeY(pid, pData)				(((ITI_SolverData*)pData)->partition[pid].curr->size.iy_real) + \
											(((ITI_SolverData*)pData)->partition[pid].curr->size.iy_int) + \
											(((ITI_SolverData*)pData)->partition[pid].curr->size.iy_str)

#define GetSimVar(pid, pData) 				(((ITI_SolverData*)pData)->partition[pid].curr)
#define GetSimData(pData)					(&((ITI_SolverData*)pData)->modelData)
#define Get_size_x(pid, pData)				(((ITI_SolverData*)pData)->partition[pid].curr->size.ix)

#define GetSolverSettings(pData)            (&((ITI_SolverData*)pData)->ss)
#define Get_dtProtMin(pData)                (((ITI_SolverData*)pData)->ss.dtProtMin)
#define Get_dtMin(pData)                    (((ITI_SolverData*)pData)->ss.dtMin)

#define Get_t(pid, pData)                   (((ITI_SolverData*)pData)->partition[pid].curr->t)
#define Get_dt(pid, pData)                  (((ITI_SolverData*)pData)->partition[pid].curr->sInfo.dt)
#define Get_tProt(pData)                    ((((ITI_SolverData*)pData)->sc[0])->tProt)
#define Get_lastOrder(pid, pData)           (((ITI_SolverData*)pData)->stat[pid].iOrder)
#define IsTimeEvent(pid, pData)             ((((ITI_SolverData*)pData)->sc[pid])->bTimeEvent)

#define Get_u(pid, pData)					(((ITI_SolverData*)pData)->partition[pid].curr->u)
#define Get_uReal(pid, pData)				(((ITI_SolverData*)pData)->partition[pid].curr->u.realData)
#define Get_uInt(pid, pData)				(((ITI_SolverData*)pData)->partition[pid].curr->u.intData)
#define Get_uStr(pid, pData)				(((ITI_SolverData*)pData)->partition[pid].curr->u.strData)
#define Get_y(pid, pData)					(((ITI_SolverData*)pData)->partition[pid].curr->y)
#define Get_yReal(pid, pData)				(((ITI_SolverData*)pData)->partition[pid].curr->y.realData)
#define Get_yInt(pid, pData)				(((ITI_SolverData*)pData)->partition[pid].curr->y.intData)
#define Get_yStr(pid, pData)				(((ITI_SolverData*)pData)->partition[pid].curr->y.strData)
#define Get_p(pid, pData)					(((ITI_SolverData*)pData)->partition[pid].curr->p)
#define Get_pReal(pid, pData)				(((ITI_SolverData*)pData)->partition[pid].curr->p.realData)
#define Get_pInt(pid, pData)				(((ITI_SolverData*)pData)->partition[pid].curr->p.intData)
#define Get_pStr(pid, pData)				(((ITI_SolverData*)pData)->partition[pid].curr->p.strData)
#define Get_v(pid, pData)					(((ITI_SolverData*)pData)->partition[pid].curr->v)
#define Get_vReal(pid, pData)				(((ITI_SolverData*)pData)->partition[pid].curr->v.realData)
#define Get_vInt(pid, pData)				(((ITI_SolverData*)pData)->partition[pid].curr->v.intData)
#define Get_vStr(pid, pData)				(((ITI_SolverData*)pData)->partition[pid].curr->v.strData)
#define Get_z(pid, pData)					(((ITI_SolverData*)pData)->partition[pid].curr->z)
#define Get_zReal(pid, pData)				(((ITI_SolverData*)pData)->partition[pid].curr->z.realData)
#define Get_zInt(pid, pData)				(((ITI_SolverData*)pData)->partition[pid].curr->z.intData)
#define Get_zStr(pid, pData)				(((ITI_SolverData*)pData)->partition[pid].curr->z.strData)
#define Get_zStrsize(pid, pData)			(((ITI_SolverData*)pData)->partition[pid].curr->z.strSize)
#define Get_pre_z(pid, pData)				(((ITI_SolverData*)pData)->partition[pid].curr->pre_z)
#define Get_pre_zReal(pid, pData)			(((ITI_SolverData*)pData)->partition[pid].curr->pre_z.realData)
#define Get_pre_zInt(pid, pData)			(((ITI_SolverData*)pData)->partition[pid].curr->pre_z.intData)
#define Get_pre_zStr(pid, pData)			(((ITI_SolverData*)pData)->partition[pid].curr->pre_z.strData)
#define Get_pre_zStrsize(pid, pData)		(((ITI_SolverData*)pData)->partition[pid].curr->pre_z.strSize)

#define Get_x(pid, pData)					(((ITI_SolverData*)pData)->partition[pid].curr->x)
#define Get_dx(pid, pData)					(((ITI_SolverData*)pData)->partition[pid].curr->xdot )

#define Get_Comp_u(pid, pData)				(&((ITI_SolverData*)pData)->partition[pid].curr->u)

#define Get_TerminateState(pid, pData)		((((ITI_SolverData*)pData)->partition[pid].curr->sInfo.isTerminate) || (((ITI_SolverData*)pData)->sc[pid]->state < SOLVER_SUCCESS_END))

#define Get_TerminateStateOnly(pid, pData)	(((ITI_SolverData*)pData)->partition[pid].curr->sInfo.isTerminate)

#define Get_ErrorState(pid, pData)			(((ITI_SolverData*)pData)->sc[pid]->state)

#define Get_TraceString(pData)				(((ITI_SolverData*)pData)->partition[0].curr->sInfo.strTrace)

#define Get_size_u_allTypes(pid, pData)		((((ITI_SolverData*)pData)->partition[pid].curr->size.iu_real) + \
											(((ITI_SolverData*)pData)->partition[pid].curr->size.iu_int) + \
											(((ITI_SolverData*)pData)->partition[pid].curr->size.iu_str))

#define Get_size_u(pid, pData)				(((ITI_SolverData*)pData)->partition[pid].curr->size.iu_real)

#define Get_size_v_real(pid, pData)			(((ITI_SolverData*)pData)->partition[pid].curr->size.iv_real)
#define Get_size_v_int(pid, pData)			(((ITI_SolverData*)pData)->partition[pid].curr->size.iv_int)
#define Get_size_v_str(pid, pData)			(((ITI_SolverData*)pData)->partition[pid].curr->size.iv_str)

#define Get_size_z_real(pid, pData)	 		(((ITI_SolverData*)pData)->partition[pid].curr->size.iz_real)
#define Get_size_z_int(pid, pData)			(((ITI_SolverData*)pData)->partition[pid].curr->size.iz_int)
#define Get_size_z_str(pid, pData)			(((ITI_SolverData*)pData)->partition[pid].curr->size.iz_str)

#define Get_size_u_real(pid, pData) 		(((ITI_SolverData*)pData)->partition[pid].curr->size.iu_real)
#define Get_size_u_int(pid, pData)			(((ITI_SolverData*)pData)->partition[pid].curr->size.iu_int)
#define Get_size_u_str(pid, pData)			(((ITI_SolverData*)pData)->partition[pid].curr->size.iu_str)

#define Get_size_y_allTypes(pid, pData)		((((ITI_SolverData*)pData)->partition[pid].curr->size.iy_real) + \
											(((ITI_SolverData*)pData)->partition[pid].curr->size.iy_int) + \
											(((ITI_SolverData*)pData)->partition[pid].curr->size.iy_str))

#define Get_size_y(pid, pData)				(((ITI_SolverData*)pData)->partition[pid].curr->size.iy_real)
#define Get_size_y_real(pid, pData)			(((ITI_SolverData*)pData)->partition[pid].curr->size.iy_real)
#define Get_size_y_int(pid, pData)			(((ITI_SolverData*)pData)->partition[pid].curr->size.iy_int)
#define Get_size_y_str(pid, pData)			(((ITI_SolverData*)pData)->partition[pid].curr->size.iy_str)

#define Get_size_p(pid, pData)				(((ITI_SolverData*)pData)->partition[pid].curr->size.ip_real)
#define Get_size_p_real(pid, pData)			(((ITI_SolverData*)pData)->partition[pid].curr->size.ip_real)
#define Get_size_p_int(pid, pData)			(((ITI_SolverData*)pData)->partition[pid].curr->size.ip_int)
#define Get_size_p_str(pid, pData)			(((ITI_SolverData*)pData)->partition[pid].curr->size.ip_str)
#define GetSize_p_allTypes(pid, pData) 		((((ITI_SolverData*)pData)->partition[pid].curr->size.ip_real) + \
											(((ITI_SolverData*)pData)->partition[pid].curr->size.ip_int) + \
											(((ITI_SolverData*)pData)->partition[pid].curr->size.ip_str))
#define Get_size_p_allTypes(pid, pData) 	((((ITI_SolverData*)pData)->partition[pid].curr->size.ip_real) + \
											(((ITI_SolverData*)pData)->partition[pid].curr->size.ip_int) + \
											(((ITI_SolverData*)pData)->partition[pid].curr->size.ip_str))
#define Get_size_p_arr(pid, pData)			(((ITI_SolverData*)pData)->partition[pid].curr->size.ip_arr)

#define Is_TraceStringAvailable(pData) 	(strlen(Get_TraceString(pData)) > 0)
#define Clear_TraceString(pData)		strcpy(Get_TraceString(pData), "")

#endif  