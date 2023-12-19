/**
 * ITI_Functions.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#if !defined(_ITI_Functions)
#define _ITI_Functions

#include "ITI_crt.h"

#ifndef _MSC_VER
#if defined ITI_DSPACE || defined ITI_SIMULINK_S_FUNC
#define __max(a,b)            (((a) > (b)) ? (a) : (b))
#else
#if !defined(__max)
#define __max max
#endif
#endif
#endif

#ifndef _MSC_VER
#if defined ITI_DSPACE || defined ITI_SIMULINK_S_FUNC
#define __min(a,b)            (((a) < (b)) ? (a) : (b))
#else
#if !defined(__min)
#define __min min
#endif
#endif
#endif

#ifndef __cplusplus
#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif
#endif

#define __LOOP_LIMIT_NOTREACHED(loopvar,limit,stepsize)	(((stepsize)>0) ? (loopvar<=limit) : (loopvar>=limit))

#ifndef sign
ITI_FUNCTIONS_API ITI_real sign(ITI_real x);
#endif

#ifndef ITI_exp
ITI_FUNCTIONS_API ITI_real ITI_limited_exp(ITI_real x);
#define ITI_exp(x) ITI_limited_exp(x)
#endif


#ifdef ITI_SCALERT
void* calloc_SCALERT(size_t nobj, size_t size);
void free_SCALERT(void* p);
#endif

ITI_FUNCTIONS_API void* AllocM(size_t num, size_t size);
ITI_FUNCTIONS_API ITI_int initialFunction(ITI_SolverInfo* pInfo);
ITI_FUNCTIONS_API ITI_int terminalFunction(ITI_SolverInfo* pInfo);
ITI_FUNCTIONS_API char* analysisTypeDetailFunction(ITI_SolverInfo* pInfo);
ITI_FUNCTIONS_API char* analysisTypeFunction(ITI_SolverInfo* pInfo);
ITI_FUNCTIONS_API ITI_uint analysisTypeDependFunction(ITI_SolverInfo* pInfo);
ITI_FUNCTIONS_API ITI_uint inAnimationFunction(ITI_SolverInfo* pInfo);
ITI_FUNCTIONS_API int assertFunction(ITI_int v, const ITI_char* msg, ITI_SolverInfo* sInfo);
ITI_FUNCTIONS_API int AssertFunction(ITI_int v, const ITI_char* msgCond, const ITI_char* msgTxt, ITI_SolverInfo* sInfo, enum AssertionLevel level, ITI_int index, double t, const ITI_char* modelName);
ITI_FUNCTIONS_API void AllocAssertData(ITI_AssertData * pAssertData, size_t n, ITI_AllocateMemory allocateMemory);
ITI_FUNCTIONS_API void InitAssertData(ITI_AssertData * pAssertData);
ITI_FUNCTIONS_API void FreeAssertData(ITI_AssertData * pAssertData, ITI_FreeMemory freeMemory);
ITI_FUNCTIONS_API void TurnErrors2Warnings(ITI_SolverInfo* sInfo);
ITI_FUNCTIONS_API int HandleAssertWarnings(ITI_SolverInfo* pInfo);
ITI_FUNCTIONS_API int _errorFunction(ITI_int v, const ITI_char* msg, ITI_SolverInfo* sInfo);
ITI_FUNCTIONS_API int terminateFunction(const ITI_char* msg, ITI_SolverInfo* sInfo);
ITI_FUNCTIONS_API void traceFunction(const ITI_char* msg, ITI_SolverInfo* sInfo);
ITI_FUNCTIONS_API void traceError(const ITI_char* msg, ITI_SolverInfo* sInfo);

ITI_FUNCTIONS_API void HandleWarnings(ITI_SolverInfo* sInfo);
ITI_FUNCTIONS_API void TransferWarnings(ITI_SolverInfo* srcInfo, ITI_SolverInfo* dstInfo);
ITI_FUNCTIONS_API void traceWarning(const ITI_char* msg, ITI_SolverInfo* sInfo);
ITI_FUNCTIONS_API void traceWarningImmediately(const ITI_char* shortMsg, const ITI_char* longMsg, ITI_SolverInfo* sInfo);
ITI_FUNCTIONS_API void traceErrorWarning(const ITI_char* msg, ITI_SolverInfo* sInfo);

ITI_FUNCTIONS_API void ResetWarningStack(ITI_SolverInfo* sInfo);

ITI_FUNCTIONS_API void InitModelSizes(ITI_ModelSize* pSize);
ITI_FUNCTIONS_API ITI_int* SetIntSizes(ITI_AllocateMemory allocateMemory, ITI_int, ...);

ITI_FUNCTIONS_API int AllocZFData(ITI_PartitionVar* pData, ITI_zerofunctionData* zfData, char bComplete, ITI_AllocateMemory allocateMemory);
ITI_FUNCTIONS_API int InitZFData(ITI_PartitionVar* pData);
ITI_FUNCTIONS_API int FreeZFData(ITI_PartitionVar* pData, char bComplete, ITI_FreeMemory freeMemory);
ITI_FUNCTIONS_API void UpdateEpsilonZF(ITI_PartitionVar* pData);

ITI_FUNCTIONS_API void __ITI_UpdateEpsilonOsZF(ITI_PartitionVar* pData, size_t i);
ITI_FUNCTIONS_API void __ITI_AssignZF(ITI_real e1, ITI_real e2,size_t index, ITI_PartitionVar* pData);

ITI_FUNCTIONS_API int AllocEventCounters(ITI_SolverStatistic* stat, size_t izf, size_t iz, ITI_AllocateMemory allocateMemory);
ITI_FUNCTIONS_API void InitEventCounters(ITI_SolverStatistic* stat, size_t izf, size_t iz);
ITI_FUNCTIONS_API void FreeEventCounters(ITI_SolverStatistic* stat, ITI_FreeMemory freeMemory);

ITI_FUNCTIONS_API void CountDiscrete(ITI_uint* dC, ITI_PartitionVar* pData);
ITI_FUNCTIONS_API void CountZeroCrossing(ITI_uint* zCC, ITI_PartitionVar* pData);


typedef struct CurveData {
	ITI_uint size;
	ITI_real* pX;
	ITI_real* pVal;
	ITI_real** pYCoeff;
	ITI_YScale* pYScale;
} CurveData;

typedef struct CalcInfo {
	ITI_int index;
	ITI_int index1;
	enum Interpol interpol;
	ITI_uint bExtrapol : 1;
	ITI_uint bCycle : 1;
	ITI_uint bMirror : 1;
} CalcInfo;

enum Axis {
	AxisX,
	AxisY,
	AxisZ
};

ITI_FUNCTIONS_API void HandleTrace(ITI_SolverInfo* sInfo);

#ifndef ITI_DSPACE
ITI_FUNCTIONS_API void HandleTerminate(ITI_SolverInfo* sInfo);
#endif

ITI_FUNCTIONS_API ITI_char* GetRecordStr(ITI_TraceData* traceData, ITI_MemoryObject* pMemObj, ITI_char* fmtStr, ...);

ITI_FUNCTIONS_API ITI_char* __ITI_ResolveResourceFolder(ITI_PartitionVar* pData, ITI_ModelData* modelData, char* strFile);
ITI_FUNCTIONS_API void SetResourceFolder(ITI_PartitionVar* data, char* strFolder);

ITI_FUNCTIONS_API void Update_pre_z_data(ITI_PartitionVar* pData, ITI_ModelData* modelData);
ITI_FUNCTIONS_API void Update_pre_z_data_ptr(ITI_PartitionVar* pData, ITI_ModelData* modelData);
ITI_FUNCTIONS_API void Update_real_pre_z_data(ITI_PartitionVar* data);
ITI_FUNCTIONS_API void Restore_z_data(ITI_PartitionVar* pData, ITI_ModelData* modelData, ITI_CompositeData* zOld);
ITI_FUNCTIONS_API void Restore_z_data_ptr(ITI_PartitionVar* pData, ITI_ModelData* modelData, ITI_CompositeData* zOld);
ITI_FUNCTIONS_API void Update_pre_zf(ITI_real* zf, ITI_real* pre_zf, ITI_int iSize);
ITI_FUNCTIONS_API ITI_int Check_z_data_ptr(ITI_PartitionVar* pData, ITI_real relTol, ITI_real absTol);
ITI_FUNCTIONS_API ITI_int Check_z_data(ITI_PartitionVar* pData, ITI_real relTol, ITI_real absTol);
ITI_FUNCTIONS_API void Update_oldsign_zf(ITI_real* zf,ITI_real*  old_sign_zf, ITI_int iSize);
ITI_FUNCTIONS_API ITI_int Check_oldsign_zf(ITI_real* zf,ITI_real*  old_sign_zf, ITI_int iSize);
ITI_FUNCTIONS_API ITI_int Check_Update_oldsign_zf(ITI_real* zf, ITI_real* old_sign_zf, ITI_int iSize);

ITI_FUNCTIONS_API void Update_oszf(ITI_PartitionVar* pData);
ITI_FUNCTIONS_API void Reset_ezf(ITI_PartitionVar* pData);
ITI_FUNCTIONS_API void Update_czf(ITI_PartitionVar* pData);
ITI_FUNCTIONS_API ITI_int Check_Update_oszf(ITI_PartitionVar* pData);
ITI_FUNCTIONS_API int CheckForZeroCrossing(ITI_PartitionVar* pData);
ITI_FUNCTIONS_API void ResetSCCounter(ITI_PartitionVar* pData);


ITI_FUNCTIONS_API void CopyVars(ITI_real* src, ITI_real* dest, ITI_int start, ITI_int end);
ITI_FUNCTIONS_API void CopyVarsCS(ITI_real** src, ITI_real** dest, ITI_int start, ITI_int end);
ITI_FUNCTIONS_API void CopyVarsA(ITI_real** src, ITI_real* dest, ITI_int start, ITI_int end);
ITI_FUNCTIONS_API void CopyVarsB(ITI_real* src, ITI_real** dest, ITI_int start, ITI_int end);

ITI_FUNCTIONS_API void InitParameter(ITI_PartitionVar* pData, ITI_parameterData* parameters, ITI_real* param, int nparam, ITI_int ip);
 
ITI_FUNCTIONS_API void AllocInitParameters(ITI_CompositeData* p, ITI_parameterData* pData, ITI_real* pValue, size_t nPreal, size_t nPint, size_t nPstr);
ITI_FUNCTIONS_API void AssignAdaptString_calloc(ITI_CompositeData* data, const char* str, size_t index, ITI_AllocateMemory allocateMemory, ITI_FreeMemory freeMemory);
ITI_FUNCTIONS_API void FreeParameters(ITI_CompositeData* p);

ITI_FUNCTIONS_API ITI_real int_pow(ITI_real x, ITI_int y);
ITI_FUNCTIONS_API ITI_real real_pow(ITI_real x, ITI_real y);

ITI_FUNCTIONS_API ITI_real AbsRemainder(ITI_real x, ITI_real y);

ITI_FUNCTIONS_API ITI_int __iti_int_min(ITI_int x, ITI_int y);
ITI_FUNCTIONS_API ITI_real __iti_real_min(ITI_real x, ITI_real y);
ITI_FUNCTIONS_API ITI_int __iti_int_max(ITI_int x, ITI_int y);
ITI_FUNCTIONS_API ITI_real __iti_real_max(ITI_real x, ITI_real y);

ITI_FUNCTIONS_API ITI_real GetYFromCurve(ITI_CurveSetData* curve, ITI_CurveCallState* cs, ITI_SolverInfo* sInfo, ITI_real* zf, ITI_real var);
ITI_FUNCTIONS_API ITI_real GetHystUpper(ITI_real x, ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo);
ITI_FUNCTIONS_API ITI_real GetHystLower(ITI_real x, ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo);
ITI_FUNCTIONS_API ITI_real GetHystMw(ITI_real x, ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf);
ITI_FUNCTIONS_API ITI_real GetHystDerMw(ITI_real x, ITI_real der, ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf);
ITI_FUNCTIONS_API ITI_real GetHystDer2Mw(ITI_real x, ITI_real der, ITI_real der2, ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf);
ITI_FUNCTIONS_API ITI_real GetYFromHystCurve(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_HystCurveCallState* pHcs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real* pre_zf, ITI_real x, ITI_real dx_dt, ITI_real gamma, ITI_HystCurveInitData* pHystInitData);
ITI_FUNCTIONS_API ITI_real GetYFromDerHystCurve(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_HystCurveCallState* pHcs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real* pre_zf, ITI_real x, ITI_real dx_dt, ITI_real gamma, ITI_HystCurveInitData* pHystInitData);
ITI_FUNCTIONS_API ITI_real GetYFromDer2HystCurve(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_HystCurveCallState* pHcs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real* pre_zf, ITI_real x, ITI_real dx_dt, ITI_real gamma, ITI_HystCurveInitData* pHystInitData);
ITI_FUNCTIONS_API void UpdateHystCurves(ITI_HystCurveCallState* pHcs, ITI_int nHyst);

ITI_FUNCTIONS_API ITI_real GetSplineValue(ITI_real x, ITI_int i, ITI_real* pX, ITI_real* pY, ITI_real** pC, ITI_uint bPeriod, ITI_CurveSetData* pCurve, ITI_ushort bHystYSeq);
ITI_FUNCTIONS_API ITI_real GetDSplineValue(ITI_real x, ITI_int i, ITI_real* pX, ITI_real* pY, ITI_real** pC, ITI_uint bPeriod, ITI_CurveSetData* pCurve, ITI_ushort bHystYSeq);
ITI_FUNCTIONS_API ITI_real GetD2SplineValue(ITI_real x, ITI_int i, ITI_real* pX, ITI_real* pY, ITI_real** pC, ITI_uint bPeriod);
ITI_FUNCTIONS_API ITI_real GetYdbl(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_int seqIdx);
ITI_FUNCTIONS_API void GetYFromCurveSet(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real* y);
ITI_FUNCTIONS_API ITI_real GetYFromCurveSet2(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_int seq);
ITI_FUNCTIONS_API ITI_real GetYFromDerCurve(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real der);
ITI_FUNCTIONS_API ITI_real GetYFromDer2Curve(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real der, ITI_real der2);
ITI_FUNCTIONS_API void GetYFromDerCurveSet(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real der, ITI_real* y);
ITI_FUNCTIONS_API ITI_real GetYFromDerCurveSet2(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_int seq, ITI_real der);
ITI_FUNCTIONS_API void GetYFromDer2CurveSet(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real der, ITI_real der2, ITI_real* y);
ITI_FUNCTIONS_API ITI_real GetYFromDer2CurveSet2(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_int seq, ITI_real der, ITI_real der2);

ITI_FUNCTIONS_API ITI_real GetCurveFamYdbl(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real scharParam);
ITI_FUNCTIONS_API ITI_real GetYFromCurveFam(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real p);

ITI_FUNCTIONS_API ITI_real GetCurveFamDYdbl(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real scharParam, ITI_ushort bp_dot);
ITI_FUNCTIONS_API ITI_real GetYFromDerCurveFam(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real p, ITI_real x_dot, ITI_real p_dot);
ITI_FUNCTIONS_API ITI_real GetCurveFamD2Ydbl(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real scharParam, ITI_ushort bp_dot);
ITI_FUNCTIONS_API ITI_real GetYFromDer2CurveFam(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real p, ITI_real x_dot, ITI_real p_dot, ITI_real x_dot2, ITI_real p_dot2);

ITI_FUNCTIONS_API ITI_real GetZFromCurve2D(ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real y);
ITI_FUNCTIONS_API ITI_real GetZFromDerCurve2D(ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real y, ITI_real xdot, ITI_real ydot);
ITI_FUNCTIONS_API ITI_real GetZFromDer2Curve2D(ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real y, ITI_real xdot, ITI_real ydot, ITI_real xdot2, ITI_real ydot2);
ITI_FUNCTIONS_API ITI_real GetUFromCurve3D(ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real y, ITI_real z);
ITI_FUNCTIONS_API ITI_real GetUFromDerCurve3D(ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real y, ITI_real z, ITI_real xdot, ITI_real ydot, ITI_real zdot);
ITI_FUNCTIONS_API ITI_real GetUFromDer2Curve3D(ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs,ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real y, ITI_real z,ITI_real xdot, ITI_real ydot, ITI_real zdot, ITI_real xdot2, ITI_real ydot2, ITI_real zdot2);

ITI_FUNCTIONS_API ITI_int InitCurveDataND(ITI_CurveData_ND *dst, ITI_CurveData_ND *src, size_t icnd, ITI_AllocateMemory allocateMemory);
ITI_FUNCTIONS_API void FreeCurveDataND(ITI_CurveData_ND *cData, size_t icnd, ITI_FreeMemory freeMemory);
ITI_FUNCTIONS_API ITI_int InitCurveSetData(ITI_CurveSetData *dst, ITI_CurveSetData *src, size_t icset, ITI_AllocateMemory allocateMemory);
ITI_FUNCTIONS_API void FreeCurveSetData(ITI_CurveSetData *csData, size_t icset, ITI_FreeMemory freeMemory);

ITI_FUNCTIONS_API ITI_real GetDelayRealValue(ITI_DelayBuffer* pBuffer, ITI_real delayExpr, ITI_real delayTime, ITI_real t, ITI_SolverInfo* sInfo, ITI_real* zf);
ITI_FUNCTIONS_API ITI_int GetDelayIntValue(ITI_DelayBuffer* pBuffer, ITI_real delayExpr, ITI_real delayTime, ITI_real t, ITI_SolverInfo* sInfo, ITI_real* zf);
ITI_FUNCTIONS_API void UpdateDelayBuffers(ITI_DelayBuffer* pBuffers, ITI_int nBuffer);
ITI_FUNCTIONS_API void InitDelayBuffers(ITI_DelayBuffer* pBuffers, ITI_int nBuffer, ITI_DelayInfo* pDelayInfos, ITI_AllocateMemory allocateMemory);
ITI_FUNCTIONS_API void FreeDelayBuffers(ITI_DelayBuffer* pBuffers, ITI_int nBuffer, ITI_FreeMemory freeMemory);
ITI_FUNCTIONS_API void SetDelayBufferData(ITI_DelayBuffer* pBuffers, ITI_int nBuffer);
#ifdef ITI_ANIMATION
ITI_FUNCTIONS_API void GetNumDelay(ITI_DelayBuffer* pBuffers, ITI_int nBuffer, ITI_int* iReal, ITI_int* iInt);
#endif

ITI_FUNCTIONS_API void Solve(ITI_BlockData* pBd, ITI_SolverInfo* pInfo);
ITI_FUNCTIONS_API void SolveRect(ITI_BlockData* pBd, ITI_SolverInfo* pInfo);
ITI_FUNCTIONS_API void Solve_DP(ITI_BlockData* pBd, ITI_DPBlockData* bdBD, ITI_SolverInfo* pInfo);
ITI_FUNCTIONS_API void CheckLimits_DP(ITI_BlockData* pBd, ITI_DPBlockData* bdBD, ITI_uint nODE, ITI_uint nDAE, ITI_SolverInfo* pInfo);


ITI_FUNCTIONS_API ITI_real EuklNorm(ITI_real* a, ITI_uint n);
ITI_FUNCTIONS_API ITI_real SProd(ITI_real* a, ITI_real* b, ITI_uint n);
ITI_FUNCTIONS_API void scaleJacCols(ITI_real* jac, ITI_real* x, ITI_real* colsc, ITI_uint m, ITI_uint n);
ITI_FUNCTIONS_API void scaleJacColsCS(ITI_real* jac, ITI_real** x, ITI_real* colsc, ITI_uint m, ITI_uint n);
ITI_FUNCTIONS_API void scaleJacCols_DP(ITI_BlockData* pBd, ITI_DPBlockData* bdBD, ITI_uint n, ITI_uint nDAE);
ITI_FUNCTIONS_API void scaleJacRows(ITI_real* jac, ITI_real* res, ITI_real* rowsc, ITI_uint m, ITI_uint n);

ITI_FUNCTIONS_API ITI_int Trace(ITI_ushort traceOn, ITI_SolverInfo* sInfo, ITI_char* timeStr, ITI_char* timeValStr, ITI_char* envStr, ITI_uint n, ITI_ushort arg1IsString, ...);

ITI_FUNCTIONS_API void InitWorkMemory(ITI_WorkMemory* pWorkMem, ITI_int inEq_n, ITI_int inEq_n_Min_m, ITI_int inEq_n_Mul_n_Min_m, ITI_int inEq_35_Mul_n_Min_m_Plus_32, ITI_AllocateMemory allocateMemory);
ITI_FUNCTIONS_API void FreeWorkMemory(ITI_WorkMemory* pWorkMem, ITI_FreeMemory freeMemory);

ITI_FUNCTIONS_API void FreeCompositeData(ITI_CompositeData* data, ITI_FreeMemory freeMemory);

ITI_FUNCTIONS_API ITI_uint GetIncSize(ITI_uint* DPBlockSizes, ITI_uint iDPB);
ITI_FUNCTIONS_API void InitDPBlockData(ITI_DPBlockData* iDPbd, ITI_uint** stateInc, ITI_uint* DPBlockSizes, ITI_uint iDPB, ITI_AllocateMemory allocateMemory);
ITI_FUNCTIONS_API void FreeDPBlockData(ITI_DPBlockData* iDPbd, ITI_uint** stateInc, ITI_uint iDPB, ITI_FreeMemory freeMemory);
ITI_FUNCTIONS_API void SetDPBlockData(ITI_DPBlockData* iDPbd, ITI_uint* DPBlockSizes, ITI_uint iDPB);

ITI_FUNCTIONS_API void InitDataArrays(ITI_PartitionVar* pData, ITI_uint size, ITI_ArrayData* arrData, ITI_AllocateMemory allocateMemory);
ITI_FUNCTIONS_API void InitDataArrays2(ITI_Array* arrays, ITI_uint size, ITI_ArrayData* arrData, ITI_AllocateMemory allocateMemory);
ITI_FUNCTIONS_API void ResetDataArrays(ITI_PartitionVar* pData, ITI_uint size, ITI_ArrayData* arrData);
ITI_FUNCTIONS_API void FreeDataArrays(ITI_PartitionVar* pData, ITI_ModelData* modelData, ITI_uint size, ITI_FreeMemory freeMemory);
ITI_FUNCTIONS_API void FreeDataArrays2(ITI_MemoryObject* currMem, ITI_Array* arrays, ITI_uint size, ITI_FreeMemory freeMemory);

ITI_FUNCTIONS_API void InitBlockData(ITI_BlockData* ibd, ITI_int numBlocks, ITI_BlockSizes *blockSizes, ITI_int *numJacCols, ITI_uint* DPBlockSizes, ITI_AllocateMemory allocateMemory);
ITI_FUNCTIONS_API void FreeBlockData(ITI_BlockData* ibd, ITI_int numBlocks, ITI_FreeMemory freeMemory);
ITI_FUNCTIONS_API void SetBlockSettings(ITI_uint numBlocks, ITI_BlockData *ibd, ITI_real gltol, ITI_int linSolv, ITI_uint ignoreLimits);
ITI_FUNCTIONS_API void ResetBlockData(ITI_uint numBlocks, ITI_BlockData *ibd, ITI_BlockSizes *blockSizes);

ITI_FUNCTIONS_API void InitHomMinMax(ITI_HomMinMax* hmm, ITI_int ihomx);
ITI_FUNCTIONS_API void FreeHomMinMax(ITI_HomMinMax* hmm, ITI_int ihomx);

ITI_FUNCTIONS_API void InitStateMinMax(ITI_StateMinMax* smm, ITI_int dim);
ITI_FUNCTIONS_API void FreeStateMinMax(ITI_StateMinMax* smm);
ITI_FUNCTIONS_API void FillStateMinMax(void* pData, ITI_VarAttributes* stateAttributes, ITI_int dim, ITI_real absTol);

ITI_FUNCTIONS_API ITI_real _BuiltIn_PackShape(char* shapename);
ITI_FUNCTIONS_API ITI_real _BuiltIn_PackMaterial(ITI_real d1, ITI_real d2, ITI_real d3, ITI_real d4);

ITI_FUNCTIONS_API void PrintSwitchingEntities(ITI_CompositeData* z, ITI_CompositeData* pre_z, ITI_real* zf, ITI_real* old_sign_zf, ITI_SolverInfo* sInfo, ITI_int intSize, ITI_int realSize, ITI_int stringSize, ITI_int zfSize);

ITI_FUNCTIONS_API void set_g_sInfo(ITI_SolverInfo *sInfo);

ITI_FUNCTIONS_API void ITI_FPE_Handler1(int sig);
ITI_FUNCTIONS_API void ITI_FPE_Handler2(int sig, ...);

ITI_FUNCTIONS_API void UnmaskExceptions(int *oldCW, void (**fPtr)(int));
ITI_FUNCTIONS_API void DisableExceptions(int *oldCW, void (**fPtr)(int));
ITI_FUNCTIONS_API void RestoreMask(int oldCW, void (*fPtr)(int));
ITI_FUNCTIONS_API void ClearAllExceptions(void);
#ifdef _MSC_VER
ITI_FUNCTIONS_API int FPEfilter(unsigned long fpeCode, ITI_SolverInfo *pSInfo);
#endif
ITI_FUNCTIONS_API int ITI_finite(double x);

ITI_FUNCTIONS_API void WarningChangedDiscreteVars(ITI_PartitionVar* pData, int iEventStep, ITI_real relTol, ITI_real absTol);

ITI_FUNCTIONS_API ITI_SolverState ExceptWrapper2(ModelFunc2 modelFunction, ITI_Partition* pPart, SimData* modelData);
ITI_FUNCTIONS_API ITI_SolverState ExceptWrapper3(ModelFunc3 modelFunction, ITI_Partition* pPart, SimData* modelData, ITI_real* __jac);

#endif
