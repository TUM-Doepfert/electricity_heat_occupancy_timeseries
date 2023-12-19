/**
 * ITI_Functions.c
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#if defined(__gnu_linux__) || defined(__CYGWIN__)
#define _GNU_SOURCE 1
#endif

#if defined(_MSC_VER)
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <excpt.h>
#define STATUS_ASSERT			0xE0000001
#define STATUS_MODELICAERROR	0xE0000002
#endif

#include "ITI_crt.h"
#include "ITI_Functions.h"
#include "ITI_LinSolver.h"
#include "ITI_ArrayFunctions.h"
#if (defined(__gnu_linux__) || defined(__CYGWIN__)) && !defined(ITI_SFuncSolver) && !defined(ITI_DSPACE)
#include <fenv.h>
#endif
#ifdef ITI_COMP_SIM
#include "ITI_Interface_Types.h"
#endif

#if !defined(ITI_DSPACE)
#include <signal.h>
#endif

 
#if defined(STDC99)
#define HAVE_SNPRINTF 1
#elif defined(__MINGW32__) || defined(__CYGWIN__)
#if __STDC_VERSION__ >= 199901L
#define HAVE_SNPRINTF 1
#endif
#elif defined(__WATCOMC__)
#define HAVE_SNPRINTF 1
#elif defined(__TURBOC__) && __TURBOC__ >= 0x550
#define HAVE_SNPRINTF 1
#elif defined(MSDOS) && defined(__BORLANDC__) && (BORLANDC > 0x410)
#define HAVE_SNPRINTF 1
#elif defined(_MSC_VER) && _MSC_VER >= 1900
#define HAVE_SNPRINTF 1
#else
#undef HAVE_SNPRINTF
#endif

#if !HAVE_SNPRINTF
int rpl_snprintf(char *, size_t, const char *, ...);
#define snprintf rpl_snprintf
#endif  

 
#if defined(STDC99)
#define HAVE_VSNPRINTF 1
#elif defined(__MINGW32__) || defined(__CYGWIN__)
#if __STDC_VERSION__ >= 199901L
#define HAVE_VSNPRINTF 1
#endif
#elif defined(__WATCOMC__)
#define HAVE_VSNPRINTF 1
#elif defined(__TURBOC__) && __TURBOC__ >= 0x550
#define HAVE_VSNPRINTF 1
#elif defined(MSDOS) && defined(__BORLANDC__) && (BORLANDC > 0x410)
#define HAVE_VSNPRINTF 1
#elif defined(_MSC_VER) && _MSC_VER >= 1900
#define HAVE_VSNPRINTF 1
#else
#undef HAVE_VSNPRINTF
#endif

#if !HAVE_VSNPRINTF
int rpl_vsnprintf(char *, size_t, const char *, va_list);
#define vsnprintf rpl_vsnprintf
#endif  

ITI_SolverInfo* g_sInfo=0;
ITI_MemoryObject* g_currMem=0;
ITI_real g_tStart=0;

static ITI_real AdjustLookupValue(ITI_real x, ITI_CurveData_ND* pCurve, CalcInfo* pCi, enum Axis axis);
static void LookupValue(ITI_real x, enum Axis axis, ITI_CurveData_ND* pCurve, ITI_SeqCallState* pSeqCs, CalcInfo* pCi, ITI_ushort bUpdateIndex);
static void InitCalcInfo(ITI_CurveData_ND* pCurve, CalcInfo* pCi, enum Axis axis);
static void InitCurveData(ITI_CurveData_ND* pCurve, CurveData* pData, enum Axis axis, ITI_int yIndex, ITI_int zIndex, ITI_YScale* pYScale);
static void InitStructCurveData(CurveData* pCd, ITI_uint size, ITI_real* pX, ITI_real* pVal, ITI_real** pYCoeff, ITI_YScale* pYScale);
static ITI_ushort ApproxUsed(CalcInfo* pCi);
static ITI_real GetHystDelta(ITI_real x, ITI_ushort bUp, ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf);
static ITI_real GetHystDDelta(ITI_real x, ITI_ushort bUp, ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf);
static ITI_real GetHystD2Delta(ITI_real x, ITI_ushort bUp, ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf);
static ITI_real GetHystDLower(ITI_real x, ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo);
static ITI_real GetHystDUpper(ITI_real x, ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo);
static ITI_real GetHystD2Lower(ITI_real x, ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo);
static ITI_real GetHystD2Upper(ITI_real x, ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo);
static ITI_real GetHystDMw(ITI_real x, ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf);
static ITI_real GetAt(ITI_real* values, ITI_CurveSetData* pCurve, ITI_int index, ITI_ushort bHystYSeq);
static ITI_real GetValAt(ITI_CurveData_ND* pCurve, enum Axis axis, ITI_int index);
static ITI_real GetRealMax(ITI_CurveData_ND* pCurve, enum Axis axis);
static ITI_real GetRealMin(ITI_CurveData_ND* pCurve, enum Axis axis);
static ITI_int FindValue(ITI_real value, enum Axis axis, ITI_ushort bNotUsed, ITI_CurveData_ND* pCurve, ITI_SeqCallState* pSeqCs, ITI_ushort bStairs, ITI_ushort bUpdateIndex);
static ITI_int GetSize(ITI_CurveData_ND* pCurve, enum Axis axis);
static ITI_real GetCoeffVal(ITI_int size, ITI_int coeffIdx, ITI_int index, ITI_real** pCoeff);
static ITI_real GetYScale(CurveData* pData);
static ITI_real GetDYdbl(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_int seqIdx);
static ITI_real GetD2Ydbl(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_int seqIdx);
static void CalcHystScale(ITI_CurveSetData* pCurve);
static void CalcHystYScale(ITI_CurveSetData* pCurve, ITI_int seqIdx, ITI_ushort bHystSeq);
static ITI_real GetCoeffVal(ITI_int size, ITI_int coeffIdx, ITI_int index, ITI_real** pCoeff);
static ITI_real GetHyperbolicApproxValue(CurveData* pData, ITI_real x, ITI_int index, ITI_real xi);
static ITI_real GetDerHyperbolicApproxValue(CurveData* pData, ITI_real x, ITI_int index, ITI_real xi);
static ITI_real GetDer2HyperbolicApproxValue(CurveData* pData, ITI_real x, ITI_int index, ITI_real xi);
static ITI_real GetArcApproxValue(CurveData* pData, ITI_real x, ITI_int index, ITI_real xi);
static ITI_real GetDerArcApproxValue(CurveData* pData, ITI_real x, ITI_int index, ITI_real xi);
static ITI_real GetDer2ArcApproxValue(CurveData* pData, ITI_real x, ITI_int index, ITI_real xi);
static ITI_real GetQuadraticApproxValue(CurveData* pData, ITI_real x, ITI_int index, ITI_real xi);
static ITI_real GetDerQuadraticApproxValue(CurveData* pData, ITI_real x, ITI_int index, ITI_real xi);
static ITI_real GetDer2QuadraticApproxValue(CurveData* pData, ITI_real x, ITI_int index, ITI_real xi);
static void GetCurveIdx(ITI_CurveSetData* pCurve, ITI_real scharParam, ITI_int* low, ITI_int* high);
static ITI_real GetMaxParam(ITI_CurveSetData* pCurve);
static ITI_real GetMinParam(ITI_CurveSetData* pCurve);
static ITI_real GetLocalParam(ITI_CurveSetData* pCurve, ITI_int seqIdx);
static ITI_real CalcDValue(ITI_real x, ITI_real* Y, ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs, CalcInfo* pCi, ITI_int idx_offset, ITI_int yIndex, ITI_int zIndex, enum Axis axis);
static ITI_real CalcD2Value(ITI_real x, ITI_real* Y, ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs, CalcInfo* pCi, ITI_int idx_offset, ITI_int yIndex, ITI_int zIndex, enum Axis axis);
static ITI_real CalcInterpol(ITI_DelayBuffer* pBuffer, ITI_real t);
static ITI_real CalcUDerCurve3D(ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real y, ITI_real z, ITI_ushort bXdot, ITI_ushort bYdot, ITI_ushort bZdot);
static ITI_real CalcUDer2Curve3D(ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real y, ITI_real z, ITI_ushort bXdot, ITI_ushort bYdot, ITI_ushort bZdot);
static ITI_real CalcValue(ITI_real x, ITI_real* Y, ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs, CalcInfo* pCi, ITI_int idx_offset, ITI_int yIndex, ITI_int zIndex, enum Axis axis);
static ITI_real CalcZCurve2D(ITI_real x, ITI_real y, ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs, ITI_real* zf, ITI_SolverInfo* pSInfo);
static ITI_real CalcZDerCurve2D(ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real y, ITI_ushort bXdot, ITI_ushort bYdot);
static ITI_real CalcZDer2Curve2D(ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real y, ITI_ushort bXdot, ITI_ushort bYdot);
static ITI_real CalcZeroFunction(ITI_DelayBuffer* pBuffer, ITI_real t);
static ITI_real CalcY(ITI_CurveSetData* curve, ITI_CurveCallState* cs, ITI_SolverInfo* sInfo, ITI_real* zf, ITI_real x, ITI_int seqIdx, ITI_ushort bHystCurve);
static ITI_real CalcYdX(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_int seqIdx, ITI_ushort bHystCurve);
static ITI_real CalcYd2X(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_int seqIdx, ITI_ushort bHystCurve);
static ITI_real CalcYCurve1D(ITI_real x, ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs, ITI_real* zf, ITI_SolverInfo* pSInfo);
static void CalcZF(ITI_real x, ITI_real* zf, ITI_CurveData_ND* pCurve, CalcInfo* pCi, enum Axis axis);
static void FindDelayInterval(ITI_DelayBuffer* pBuffer, ITI_real time, ITI_uint isEvent);
static ITI_int GetNextDelayIndex(ITI_DelayBuffer* pBuffer, ITI_int lowIndex);
static ITI_int FindXValue(ITI_CurveSetData* curve, ITI_CurveCallState* cs, ITI_SolverInfo* sInfo, ITI_real val, ITI_ushort bStairs, ITI_uint update_index);
static ITI_real dbl_epsilon(ITI_real v1, ITI_real v2);
static void swap(ITI_real* a, ITI_real* b);
static ITI_ushort InHorizontalMode(ITI_HystCurveInitData* pHystInitData);
static ITI_ushort InContinousMode(ITI_HystCurveInitData* pHystInitData);
static void CalcBlockJac(ITI_BlockData* pBd, ITI_SolverInfo* pInfo);
static void CalcBlockJac_DP(ITI_BlockData* pBd, ITI_SolverInfo* pInfo);
static void CalcM(ITI_BlockData* pBd, ITI_DPBlockData* pDPbd, ITI_uint nODE, ITI_uint nDAE);
static void CheckM(ITI_BlockData* pBd, ITI_DPBlockData* pDPbd, ITI_uint nODE, ITI_uint nDAE);
static void CheckBounds(ITI_BlockData* pBd, ITI_uint n, ITI_SolverInfo* pInfo);
static void CheckBounds_DP(ITI_BlockData* pBd, ITI_DPBlockData* bdBD, ITI_uint nDAE, ITI_SolverInfo* pInfo);
static ITI_uint CheckBoundsRect(ITI_BlockData* pBd, ITI_uint n, ITI_SolverInfo* pInfo);
static void Check_Jac(ITI_BlockData* pBd, ITI_DPBlockData* bdBD, ITI_SolverInfo* pInfo, ITI_uint nODE, ITI_uint nDAE);
static ITI_uint globalNewton(ITI_BlockData* pBd, ITI_uint _n, ITI_SolverInfo* pInfo);
static ITI_uint globalNewton_rect(ITI_BlockData* pBd, ITI_uint _m, ITI_uint _n, ITI_SolverInfo* pInfo, ITI_WorkMemory* pWorkMem);
static ITI_uint globalNewton_DP(ITI_BlockData* pBd, ITI_DPBlockData* bdBD, ITI_uint _n, ITI_uint nDAE, ITI_SolverInfo* pInfo);
static ITI_real ScaledNorm2(ITI_real* a, ITI_real* b, ITI_uint n);
static void GetNamesStr(ITI_BlockData* pBd, ITI_char* names, ITI_uint n);
static void ErrorExceedsBorder(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i);
static void ErrorInitialBracketNotFound(ITI_BlockData* pBd, ITI_SolverInfo* pInfo);
static void ErrorLambdaMin(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint n);
static void ErrorMaxIter(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint n);
static void ErrorResidualImage(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint n);
static void WarningBelowMin(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i, ITI_uint j);
static void WarningBelowMinDamping(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i);
static void WarningBelowMinDamping2(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i, ITI_uint k);
static void WarningExceedsMax(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i, ITI_uint j);
static void WarningExceedsMaxDamping(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i);
static void WarningExceedsMaxDamping2(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i, ITI_uint k);
static void WarningReducingDampFac(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i);
static void WarningResidualImage(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint m, ITI_uint n, ITI_uint l);
static void SetAnalysisTypeDetail(ITI_SolverInfo* pInfo, char* typeDetail);
static void UpdateEventIndeces(ITI_DelayBuffer* pBuffer);
static void SwitchLinearSolver(ITI_BlockData *pBd, ITI_SolverInfo *pInfo);
static void UpdateEpsilonSingleZF(ITI_PartitionVar* pData, size_t i);
static ITI_int Check_z_real(ITI_real pre_z, ITI_real z, ITI_real relTol, ITI_real absTol);
static ITI_int CheckEpsilonRange(ITI_real* x, ITI_real xmin, ITI_real xmax);
static void Update_sign_zf(ITI_PartitionVar* pData,  size_t index);

#ifdef _OPENMP
#pragma omp threadprivate(g_currMem)
#pragma omp threadprivate(g_sInfo)
#pragma omp threadprivate(g_tStart)
#endif

#define SCALE

void* AllocM(size_t num, size_t size)
{
	if (num == 0)
		return NULL;
	return calloc(num, size);
}


#ifdef ITI_SCALERT
void* calloc_SCALERT(size_t nobj, size_t size)
{
	return memset(vmalloc(nobj*size), 0, nobj*size);
}
void free_SCALERT(void* p)
{
	vfree(p);
}
#define ITI_HandleAllocMemory {if(allocateMemory==0)allocateMemory = calloc_SCALERT;}
#define ITI_HandleFreeMemory {if(freeMemory==0) freeMemory = free_SCALERT;}
#else
#define ITI_HandleAllocMemory {if(allocateMemory==0)allocateMemory = calloc;}
#define ITI_HandleFreeMemory {if(freeMemory==0) freeMemory = free;}
#endif

#ifndef sign
ITI_real sign(ITI_real x)
{
	if(x>0.0)
		return 1.0;
	if(x<0.0)
		return -1.0;
	return 0.0;
}
#endif

ITI_real ITI_limited_exp(ITI_real x) {
	if(x<log(1e100))
		return exp(x);
	return 1e100;
}

#if defined ITI_TWINCAT || (!defined(_MSC_VER) && !defined(__MINGW32__))
ITI_real _copysign(ITI_real x, ITI_real y)
{
	if ((x < 0 && y >= 0) || (x > 0 && y < 0))
		return -x;
	return x;
}
#endif

#define _MEMCPY

ITI_int initialFunction(ITI_SolverInfo* pInfo)
{
	return pInfo->isInitial;
}
ITI_int terminalFunction(ITI_SolverInfo* pInfo)
{
	if(pInfo->isTerminal)
		pInfo->iTerminalCalled=1;
	return pInfo->isTerminal;
}
char* analysisTypeDetailFunction(ITI_SolverInfo* pInfo)
{
	return pInfo->strAnalysisTypeDetail;
}
char* analysisTypeFunction(ITI_SolverInfo* pInfo)
{
	return pInfo->strAnalysesType;
}
ITI_uint analysisTypeDependFunction(ITI_SolverInfo* pInfo) {
	return pInfo->isCalcDependencies;
}
ITI_uint inAnimationFunction(ITI_SolverInfo* pInfo) {
#ifdef ITI_ANIMATION
	return pInfo->isAnimation;
#else
	return 0;
#endif
}

ITI_real int_pow(ITI_real x, ITI_int y)
{
	ITI_real r = 1.0;
	if (y < 0){
		x = 1/x;
		y = -1*y;
	} 
	while (y-- > 0)
		r *= x;
	return r;
} 

#if defined(_MSC_VER)
#pragma optimize( "", off )
#endif

ITI_real real_pow(ITI_real x, ITI_real y)
{
	ITI_real res=0.0;
	res=((double)pow((double)x,(double)y));
	return res;
}

#if defined(_MSC_VER)
#pragma optimize( "", on )
#endif

ITI_FUNCTIONS_API ITI_real AbsRemainder(ITI_real x, ITI_real y)
{
	ITI_real r;
#if ((defined(_MSC_VER) && _MSC_VER >= 1800) || (defined(__GNUC__) && !defined(ITI_DSPACE))) && (!defined ITI_TWINCAT) 
	r = fabs(remainder(x, y));
#else
	ITI_real r1;
	r = fmod(x, y);
	r1 = fabs(r - y);
	if (r1 < r)
		r = r1;
#endif
	return r;
}

ITI_int __iti_int_min(ITI_int x, ITI_int y) {
	if (x <= y)
		return x;
	else
		return y;
}

ITI_real __iti_real_min(ITI_real x, ITI_real y) {
	if (x <= y)
		return x;
	else
		return y;
}

ITI_int __iti_int_max(ITI_int x, ITI_int y) {
	if (x >= y)
		return x;
	else
		return y;
}

ITI_real __iti_real_max(ITI_real x, ITI_real y) {
	if (x >= y)
		return x;
	else
		return y;
}
static ITI_real dbl_epsilon(ITI_real v1, ITI_real v2)
{
	ITI_real eps = V_EPSILON;
	return eps*__max(__max(fabs(v1), fabs(v2)), eps);
} 

void traceFunction(const ITI_char* msg, ITI_SolverInfo* sInfo)
{
	if(!sInfo)
		printf("%s", msg);
	else if(sInfo->tracingAllowed)
	{
#ifdef ITI_DSPACE
		msg_info_set(MSG_SM_USER, 0, msg);
#else
		if(sInfo->trace)
		{
			sInfo->trace(0,5, msg, "", (void*)sInfo);
		}
		else
		{
			const char newLine[] = "\n";
			if((strlen(sInfo->strTrace) + strlen(msg) + sizeof(newLine)) <= ITI_TRACE_STRING_SIZE)
			{
				strcat(sInfo->strTrace, msg);
				strcat(sInfo->strTrace, newLine);
			}
		}
#endif
	}
}

void traceError(const ITI_char* msg, ITI_SolverInfo* sInfo)
{
	if(!sInfo)
		printf("%s", msg);
	else
	{
#ifdef ITI_DSPACE
		msg_warning_set(MSG_SM_USER, ITI_MODEL_ERROR, msg);
#else
		if(sInfo->trace)
		{
			sInfo->trace(0,4, "ERROR", msg, (void*)sInfo);
		}
		else if((strlen(sInfo->strTrace) + strlen(msg)) < ITI_TRACE_STRING_SIZE)
		{
			strcat(sInfo->strTrace, msg);
			HandleTrace(sInfo);
		}
#endif
	}
}

void traceWarningImmediately(const ITI_char* shortMsg, const ITI_char* longMsg, ITI_SolverInfo* sInfo)
{
	if(!sInfo)
	{
		printf("%s: ", shortMsg);
		printf("%s\n", longMsg);
	}
	else
	{
#ifdef ITI_DSPACE
		msg_warning_set(MSG_SM_USER, ITI_SOLVER_WARNING, longMsg);
#else
		if(sInfo->trace)
		{
			sInfo->trace(0,1, shortMsg, longMsg, (void*)sInfo);
		}
		else
		{
			const char newLineEx[] = " :\n";
			if((strlen(sInfo->strTrace) + strlen(shortMsg) + strlen(longMsg) + sizeof(newLineEx)) <= ITI_TRACE_STRING_SIZE)
			{
				strcat(sInfo->strTrace, shortMsg);
				strcat(sInfo->strTrace, newLineEx);
				strcat(sInfo->strTrace, longMsg);
				HandleTrace(sInfo);
			}
		}
#endif
	}
}

void ResetWarningStack(ITI_SolverInfo* sInfo)
{
	sInfo->warningStack.size = 0;
	sInfo->warningStack.lastMsg = -1;
}

int containsDuplicateWarning(ITI_int idx, ITI_SolverInfo* sInfo) {
	ITI_WarningStack* warningStack = &sInfo->warningStack;
	ITI_int i;
	for (i = 0; i < warningStack->size; ++i) {
		if (i != idx &&
			strcmp(warningStack->msg[i].shortMsg, warningStack->msg[idx].shortMsg) == 0 &&
			strcmp(warningStack->msg[i].longMsg, warningStack->msg[idx].longMsg) == 0)
			return 1;
	}
	return 0;
}

void traceWarning(const ITI_char* msg, ITI_SolverInfo* sInfo)
{
	ITI_WarningStack* warningStack = &sInfo->warningStack;
	ITI_int pre_last = warningStack->lastMsg;
	ITI_int pre_size = warningStack->size;

	warningStack->lastMsg++;

	if(warningStack->lastMsg > ITI_WARNING_STACK_SIZE-1)
		warningStack->lastMsg = 0;

	warningStack->size++;
	if(warningStack->size > ITI_WARNING_STACK_SIZE)
		warningStack->size = ITI_WARNING_STACK_SIZE;

	warningStack->msg[warningStack->lastMsg].type = SimX_warning;
	strcpy(warningStack->msg[warningStack->lastMsg].shortMsg, "Warning");
	if (strlen(msg) > ITI_TRACE_STRING_SIZE)
		strncpy(warningStack->msg[warningStack->lastMsg].longMsg, msg, ITI_TRACE_STRING_SIZE);
	else
		strcpy(warningStack->msg[warningStack->lastMsg].longMsg, msg);

	if (containsDuplicateWarning(warningStack->lastMsg, sInfo)) {
		warningStack->lastMsg = pre_last;
		warningStack->size = pre_size;
	}
}

void traceErrorWarning(const ITI_char* msg, ITI_SolverInfo* sInfo)
{
	ITI_WarningStack* warningStack = &sInfo->warningStack;
	ITI_int pre_last = warningStack->lastMsg;
	ITI_int pre_size = warningStack->size;
	warningStack->lastMsg++;

	if(warningStack->lastMsg > ITI_WARNING_STACK_SIZE-1)
		warningStack->lastMsg = 0;

	warningStack->size++;
	if(warningStack->size > ITI_WARNING_STACK_SIZE)
		warningStack->size = ITI_WARNING_STACK_SIZE;

	warningStack->msg[warningStack->lastMsg].type = SimX_error;
	strcpy(warningStack->msg[warningStack->lastMsg].shortMsg, "Error");
	if (strlen(msg) > ITI_TRACE_STRING_SIZE)
		strncpy(warningStack->msg[warningStack->lastMsg].longMsg, msg, ITI_TRACE_STRING_SIZE);
	else
		strcpy(warningStack->msg[warningStack->lastMsg].longMsg, msg);
	if (containsDuplicateWarning(warningStack->lastMsg, sInfo)) {
		warningStack->lastMsg = pre_last;
		warningStack->size = pre_size;
	}
}

void TurnErrors2Warnings(ITI_SolverInfo* sInfo) {
	ITI_WarningStack* warningStack = &sInfo->warningStack;
	ITI_int i;
	for (i = 0; i < warningStack->size; i++) {
		warningStack->msg[i].type = SimX_warning;
	}
}

void HandleWarnings(ITI_SolverInfo* sInfo){
	ITI_WarningStack* warningStack = &sInfo->warningStack;

	if(warningStack->size > 0){
		ITI_int i;
		ITI_char bShowAsError=0;
		ITI_int iMsgBefore;
		ITI_int iMsg = warningStack->lastMsg - (warningStack->size-1);
		ITI_char strBuff[(ITI_WARNING_STACK_SIZE+1) * (ITI_TRACE_STRING_SIZE + 100)];

		if(iMsg < 0){
			iMsg=ITI_WARNING_STACK_SIZE+iMsg;
		}
		iMsgBefore = iMsg;

		if(warningStack->msg[warningStack->lastMsg].type == SimX_error){
			bShowAsError = 1;
			strcpy(strBuff, "Error: The solution failed! Please have a look at the warning or assertion messages which have possibly been printed above! These warnings might be the reason for the error!\n \n");
		}

		for(i=0;i<warningStack->size;i++){
			ITI_char bFilter;
			if(bShowAsError){
				warningStack->msg[iMsg].type = SimX_error;
			}
			bFilter=0;
			if(iMsgBefore != iMsg){
				if(strcmp(warningStack->msg[iMsg].longMsg, warningStack->msg[iMsgBefore].longMsg)==0){
					bFilter=1;
				}
			}
			if(!bFilter){
				if((warningStack->msg[iMsg].type == SimX_error) && (strcmp(warningStack->msg[iMsg].shortMsg, "Warning")==0)){
					strcpy(warningStack->msg[iMsg].shortMsg, "Error");
				}
#ifdef ITI_DSPACE
				msg_warning_set(MSG_SM_USER, ITI_SOLVER_WARNING, warningStack->msg[iMsg].longMsg);
#else
				if(bShowAsError){
					if((strlen(strBuff) + strlen(warningStack->msg[iMsg].shortMsg) + strlen(warningStack->msg[iMsg].longMsg + 6)) < ((ITI_WARNING_STACK_SIZE+1) * (ITI_TRACE_STRING_SIZE + 100))){
						strcat(strBuff, warningStack->msg[iMsg].shortMsg);
						strcat(strBuff, ": ");
						strcat(strBuff, warningStack->msg[iMsg].longMsg);
						strcat(strBuff, "\n \n");
					}
				}
				else if(sInfo->trace){
						sInfo->trace(0, warningStack->msg[iMsg].type, warningStack->msg[iMsg].shortMsg, warningStack->msg[iMsg].longMsg, (void*)sInfo);
				}
				else{
					const char newLine[] = "\n";
					if ((strlen(sInfo->strTrace) + strlen(warningStack->msg[iMsg].longMsg) + sizeof(newLine)) <= ITI_TRACE_STRING_SIZE){
						strcat(sInfo->strTrace, warningStack->msg[iMsg].longMsg);
						strcat(sInfo->strTrace, newLine);
					}
				}
#endif
			}
			iMsgBefore = iMsg;
			iMsg++;
			if(iMsg>ITI_WARNING_STACK_SIZE-1)
				iMsg = 0;
		}
		if(bShowAsError){
#ifdef ITI_DSPACE
			msg_warning_set(MSG_SM_USER, ITI_SOLVER_ERROR, warningStack->msg[iMsg].longMsg);
#else
			if(sInfo->trace){
				sInfo->trace(0, SimX_error, "Error", strBuff, (void*)sInfo);
			}
			else{
				const char newLine[] = "\n";
				if ((strlen(sInfo->strTrace) + strlen(strBuff) + sizeof(newLine)) <= ITI_TRACE_STRING_SIZE){
					strcat(sInfo->strTrace, strBuff);
					strcat(sInfo->strTrace, newLine);
				}
			}
#endif
		}
	}
	ResetWarningStack(sInfo);
}

void TransferWarnings(ITI_SolverInfo* srcInfo, ITI_SolverInfo* dstInfo)
{
	ITI_WarningStack* srcStack = &srcInfo->warningStack;

	if(srcStack->size > 0)
	{
		ITI_int i;
		for(i=0;i<srcStack->size;i++)
		{
			traceWarning(srcStack->msg[i].longMsg, dstInfo);
		}
		ResetWarningStack(srcInfo);
	}
}

int assertFunction(ITI_int v, const ITI_char* msg, ITI_SolverInfo* sInfo)
{
	return AssertFunction(v, 0, msg, sInfo, AL_Error, -1, 0, 0);
}

int AssertFunction(ITI_int v, const ITI_char* msgCond, const ITI_char* msgTxt, ITI_SolverInfo* sInfo, enum AssertionLevel level, ITI_int index, double t, const ITI_char* modelName)
{
	size_t msgCondlen=0;
	size_t msgTxtlen=0;

	if (sInfo && !sInfo->bAssertActive && !sInfo->bAssertTraceOn)
		return 0;

	if(v && (level == AL_Error))
		return 0;

	if (msgCond!=NULL)
		msgCondlen=strlen(msgCond);
	if (msgTxt!=NULL)
		msgTxtlen=strlen(msgTxt);

	if(level == AL_Error)
	{
		static char strMsg[ITI_TRACE_STRING_SIZE];
		char reasonStr[ITI_TRACE_STRING_SIZE];
		int cx;
		if (sInfo && sInfo->GetImpactBDF != NULL && sInfo->bInitializeConditions)
			return 0;

#ifdef ITI_COMP_SIM
		GetHyperlink(reasonStr, "Modelica.Assert");
#else
		strcpy(reasonStr, "Help: Modelica.Assert");
#endif
		cx = snprintf(strMsg, ITI_TRACE_STRING_SIZE, "In model %s\n%s\n%s", modelName, msgTxt, reasonStr);
		if (cx >= ITI_TRACE_STRING_SIZE)
			strcpy(&strMsg[ITI_TRACE_STRING_SIZE - 4], "...");

		if(!sInfo)
		{
			printf("%s", strMsg);
			exit(EXIT_FAILURE);
			return 0;
		}
		if (sInfo->bAssertOn || sInfo->bAssertTraceOn) {
			if (sInfo->bAssertActive)
				traceErrorWarning(strMsg, sInfo);
			else
				traceWarning(strMsg, sInfo);
		}

		if (!sInfo->bAssertActive)
			return 0;

#ifndef ITI_SCALERT
#if defined _MSC_VER && !defined ITI_TWINCAT
		if (!sInfo->allowJump) {
			RaiseException(STATUS_ASSERT, 0, 0, 0);
		}
		else
#endif
		{
			if (sInfo->allowBlockJump)
				longjmp(sInfo->blockEnv, 1);
			if (sInfo->allowJump)
				longjmp(sInfo->buf, 1);
		}
#endif
		sInfo->assertData.bAssertError = ITI_true;
		return 0;
	}
	else if (index < (ITI_int)sInfo->assertData.n)
	{
		sInfo->assertData.assertStateW[index] = (ITI_uchar)v;
		if(v != sInfo->assertData.assertStateR[index])
		{
			ITI_char str[ITI_TRACE_STRING_SIZE];
			int cx;

			strncpy(sInfo->assertData.condMsg[index], msgCond, ITI_TRACE_STRING_SIZE - 4);
			if (msgCondlen > ITI_TRACE_STRING_SIZE - 4)
				strcat(sInfo->assertData.condMsg[index], "...");

			cx = snprintf(str, ITI_TRACE_STRING_SIZE, "Time: %gs: Warning in model %s\n%s", t, modelName, msgTxt);
			if (cx >= ITI_TRACE_STRING_SIZE)
				strcpy(&str[ITI_TRACE_STRING_SIZE - 4], "...");
			strncpy(sInfo->assertData.warnMsg[index], str, ITI_TRACE_STRING_SIZE);

			sInfo->assertData.bAssertStateChanged = ITI_true;
			return 1;
		}
	}
	return 0;
}

int _errorFunction(ITI_int v, const ITI_char* msg, ITI_SolverInfo* sInfo)
{
	if (!v)
	{
		static char strMsg[ITI_TRACE_STRING_SIZE];
		int cx;

		cx = snprintf(strMsg, ITI_TRACE_STRING_SIZE, "Error: %s", msg);
		if (cx >= ITI_TRACE_STRING_SIZE)
			strcpy(&strMsg[ITI_TRACE_STRING_SIZE - 4], "...");

		if(!sInfo)
		{
			printf("%s", strMsg);
			exit(EXIT_FAILURE);
		}

		traceErrorWarning(strMsg, sInfo);
		sInfo->isTerminate = ITI_true;

#ifndef ITI_SCALERT
#if defined _MSC_VER && !defined ITI_TWINCAT
	if (!sInfo->allowJump) {
		RaiseException(STATUS_MODELICAERROR, 0, 0, 0);
	}
	else
#endif
	{
		if (sInfo->allowBlockJump)
			longjmp(sInfo->blockEnv, 1);
		if (sInfo->allowJump)
			longjmp(sInfo->buf, 1);
	}
#endif

	}
	return 1;
}

int terminateFunction(const ITI_char* msg, ITI_SolverInfo* sInfo)
{
	if(!sInfo)
	{
		printf("\nTerminating: ");
		printf("%s", msg);
		exit(EXIT_FAILURE);
		return 0;
	}

#ifdef ITI_DSPACE
	if (msg)
	{
		msg_info_set(MSG_SM_USER, ITI_TERMINATE, msg);
	}
#else
	if(sInfo->trace)
	{
		if(sInfo->tracingAllowed && !sInfo->isTerminate)
			sInfo->trace(0,0, "Terminating:", msg, (void*)sInfo);
	}
	else
	{
		const char termMsg[] = "\nTerminating:\n";
		if((strlen(sInfo->strTrace) + sizeof(termMsg)) <= ITI_TRACE_STRING_SIZE)
		{
			strcat(sInfo->strTrace, termMsg);
		}
		if (msg)
		{
			if((strlen(sInfo->strTrace) + strlen(msg)) < ITI_TRACE_STRING_SIZE)
				strcat(sInfo->strTrace, msg);
			else
			{
				const char termMsg2[] = "\nTerminating: ";
				if((sizeof(termMsg2) + strlen(msg)) <= ITI_TRACE_STRING_SIZE)
				{
					strcpy(sInfo->strTrace, termMsg2);
					strcat(sInfo->strTrace, msg);
				}
			}
		}
	}
#endif

	sInfo->isTerminate = ITI_true;

#ifdef ITI_COMP_SIM
	{
		ITI_SimXInterface* simx = ((ITI_SimXInterface*)((ITI_SolverData*)(sInfo->pSolverData))->modelData.simxInterface);
		simx->SetTerminateCalled(simx);
	}
#endif
	return 0;
} 

void HandleTrace(ITI_SolverInfo* sInfo)
{
	if (sInfo->strTrace[0] != '\0')
	{
#if !defined ITI_NI_LV_CDSIM && !defined ITI_SFuncSolver
#ifndef ITI_DSPACE
		printf("\n");
		printf("%s", sInfo->strTrace);
#else
		msg_warning_set(MSG_SM_USER, ITI_MODEL_ERROR, sInfo->strTrace);
#endif
		sInfo->strTrace[0] = '\0';
#endif
	}
}

#if !defined(ITI_DSPACE)
void HandleTerminate(ITI_SolverInfo* sInfo)
{
	if(sInfo->isTerminate)
		exit(EXIT_FAILURE);
}
#endif

ITI_char* GetRecordStr(ITI_TraceData* traceData, ITI_MemoryObject* pMemObj, ITI_char* string, ...)
{
	va_list argList;
	ITI_int len = (ITI_int)strlen(string) + 1024;
	ITI_char* recStr = GetStringMemory(pMemObj, len);

	va_start(argList, string);
	vsnprintf(recStr, len, string, argList);
	va_end(argList);
	return recStr;
}

ITI_char* __ITI_ResolveResourceFolder(ITI_PartitionVar* pData, ITI_ModelData* modelData, char* strFile) {
	const char strURIFMU[] = "fmu://resources/";
	const size_t len = strlen(strURIFMU);
	if (strncmp(strFile, strURIFMU, len) == 0) {
		ITI_char* str;
		str = GetStringMemory(&modelData->strMem, (int)strlen(strFile) - (int)len + (int)strlen(pData->sInfo.strResourceFolder));
		if (str != 0) {
			sprintf(str, "%s%s", pData->sInfo.strResourceFolder, strFile + len);
			return str;
		}
		 
	}
	return strFile;
}

void SetResourceFolder(ITI_PartitionVar* pData, char* strFolder){
	if(strlen(pData->sInfo.strResourceFolder) < strlen(strFolder)){
		strcpy(pData->sInfo.strResourceFolder, strFolder);
	}
	else{
		 
		pData->sInfo.strResourceFolder[0] = '\0';
	}
}




static void InitStructCurveData(CurveData* pCd, ITI_uint size, ITI_real* pX,
									ITI_real* pVal, ITI_real** pYCoeff,
									ITI_YScale* pYScale)
{
	pCd->size = size;
	pCd->pX = pX;
	pCd->pVal = pVal;
	pCd->pYCoeff = pYCoeff;
	pCd->pYScale = pYScale;
} 

static ITI_real GetAt(ITI_real* values, ITI_CurveSetData* pCurve,
							ITI_int index, ITI_ushort bHystYSeq){
	ITI_real res = 0.;

	if (values && pCurve){
		ITI_int size = (ITI_int) pCurve->size;
		if (index < size && index >= 0)
			res = values[index];

		if (bHystYSeq)
			res += pCurve->pY[MW_IDX][index];
	} 
	else if (values && index >= 0)
		res = values[index];

	return res;
} 





static ITI_int FindXValue(ITI_CurveSetData* pCurve, ITI_CurveCallState* cs,
				   ITI_SolverInfo* sInfo, ITI_real val, ITI_ushort bStairs, ITI_uint update_index)
{
	ITI_int pos = 0;

	if (pCurve && pCurve->size > 1 && cs && sInfo)
	{
		ITI_int size = (ITI_int) pCurve->size;
		if (size > 1)
		{
			pos = cs->pSeqCs->iPos;
			if (pos < -1)
				pos = -1;
			else if ((pos > size - 2) && !bStairs)
				pos = size - 2;
			else if (pos > size - 1)
				pos = size - 1;

			if (update_index || (pos < 0))
			{
				ITI_real prev, next;
				if(pos < 0)
					pos = 0;
				if (pos > size - 2)
					pos = size - 2;

				prev = GetAt(pCurve->pX, pCurve, pos, 0);
				next = GetAt(pCurve->pX, pCurve, pos + 1, 0);

				if (prev > val)
				{
					for (pos--; pos >= 0; pos--)
					{
						next = prev;
						prev = GetAt(pCurve->pX, pCurve, pos, 0);
						if (prev <= val && val < next)
							break;
					}
					if (pos < 0)
						pos = 0;
				}
				else if (val >= next)
				{
					for (pos++; pos <= size - 2; pos++)
					{
						prev = next;
						next = GetAt(pCurve->pX, pCurve, pos + 1, 0);
						if (prev <= val && val < next)
							break;
					}
					if (pos > size - 2)
						pos = size - 2;
					if (bStairs && val >= GetAt(pCurve->pX, pCurve, size - 1, 0))
						pos = size - 1;
				}
			}
			cs->pSeqCs->iPos = pos;
		}
	}

	return pos;
}

ITI_real GetSplineValue(ITI_real x, ITI_int i, ITI_real* pX, ITI_real* pY, ITI_real** pC, ITI_uint bPeriod,
										ITI_CurveSetData* pCurve, ITI_ushort bHystYSeq)
{
	ITI_real res = 0.;

	if (pX && pY && pC){
		ITI_real Ms = pX[i+1] - pX[i];
		ITI_real Mx = x - pX[i];
		ITI_real y = GetAt(pY, pCurve, i, bHystYSeq);
		 
		ITI_real My = (GetAt(pY, pCurve, i+1, bHystYSeq) - y)/Ms;

		if (!bPeriod){
			res = y + pC[0][i] * Mx + ((Mx*Mx)/Ms)*((My-pC[0][i]) + ((pC[0][i+1]-2.0 * My + pC[0][i])*(x-pX[i+1]))/Ms);
		} 
		else {
			ITI_real d = y - Ms * Ms * pC[0][i];
			ITI_real c = My - Ms*(pC[0][i+1] - pC[0][i]);
			ITI_real Mx1 = pX[i+1] - x;
			res = (Mx1*Mx1*Mx1*pC[0][i] + Mx*Mx*Mx*pC[0][i+1])/Ms + c*Mx+d;
		} 
	}

	return res;
} 

ITI_real GetDSplineValue(ITI_real x, ITI_int i, ITI_real* pX, ITI_real* pY, ITI_real** pC, ITI_uint bPeriod,
						 ITI_CurveSetData* pCurve, ITI_ushort bHystYSeq)
{
	ITI_real res = 0.;

	if (pX && pY && pC){
		ITI_real Ms = pX[i+1] - pX[i];
		ITI_real Mx = x - pX[i];
		 
		ITI_real My = (GetAt(pY, pCurve, i+1, bHystYSeq) - GetAt(pY, pCurve, i, bHystYSeq))/Ms;

		if (!bPeriod){
			res = pC[0][i] + (Mx/Ms)*(2.0*(My - pC[0][i]) + ((pC[0][i+1]-2.0 * My + pC[0][i])*(2.0*(x-pX[i+1])+Mx))/Ms);
		} 
		else {
			ITI_real Mx1 = pX[i+1] - x;
			ITI_real c = My - Ms*(pC[0][i+1] - pC[0][i]);
			res = (3.0 * (Mx*Mx*pC[0][i+1]-Mx1*Mx1*pC[0][i]))/Ms + c;
		} 
	} 

	return res;
} 

ITI_real GetD2SplineValue(ITI_real x, ITI_int i, ITI_real* pX, ITI_real* pY, ITI_real** pC, ITI_uint bPeriod)
{
	ITI_real res = 0.;

	if (pX && pY && pC){
		ITI_real Ms = pX[i+1] - pX[i];
		ITI_real Mx = x - pX[i];
		ITI_real My = (pY[i+1] - pY[i])/Ms;

		if (!bPeriod){
			res = (1/Ms)*(2.0*(My - pC[0][i]) + ((pC[0][i+1]-2.0 * My + pC[0][i])*(2.0*(x-pX[i+1])+4.0*Mx))/Ms);
		} 
		else {
			ITI_real Mx1 = pX[i+1] - x;
			res = (6.0*(Mx*pC[0][i+1]+Mx1*pC[0][i]))/Ms;
		} 
	} 

	return res;
} 

static ITI_real GetCoeffVal(ITI_int size, ITI_int coeffIdx, ITI_int index, ITI_real** pCoeff)
{
	ITI_real res = 0.;

	if (pCoeff){
		 
		res = pCoeff[coeffIdx-1][index];
	} 

	return res;
} 

static ITI_real GetYScale(CurveData* pData)
{
	ITI_real scale = 1.;

	if (pData && pData->pYScale){
		if (!pData->pYScale->bScaleInitialized){
			ITI_uint i = 0;
			ITI_real ymax = -DBL_MAX;
			ITI_real ymin = DBL_MAX;
			ITI_real xmax = -DBL_MAX;
			ITI_real xmin = DBL_MAX;
			for (i=0; i < pData->size; ++i){
				ymax = __max(ymax, pData->pVal[i]);
				ymin = __min(ymin, pData->pVal[i]);
				xmax = __max(xmax, pData->pX[i]);
				xmin = __min(xmin, pData->pX[i]);
			}

			scale = (ymax - ymin)/(xmax - xmin);
			if (scale == 0.0)
				scale = 1.0;
			pData->pYScale->scale = scale;
			pData->pYScale->bScaleInitialized = ITI_true;
		}
		else
			scale = pData->pYScale->scale;
	}

	return scale;
}

static void CalcHystScale(ITI_CurveSetData* pCurve)
{
	if (pCurve && pCurve->pYScale && pCurve->nYScale==3){
		CalcHystYScale(pCurve, 0, 0);
		CalcHystYScale(pCurve, 1, 1);
		CalcHystYScale(pCurve, 2, 1);
	}
}

static void CalcHystYScale(ITI_CurveSetData* pCurve, ITI_int seqIdx, ITI_ushort bHystSeq)
{
	if (!pCurve->pYScale[seqIdx].bScaleInitialized){
		ITI_int i = 0;
		ITI_real scale = 1.;
		ITI_real ymax = -DBL_MAX;
		ITI_real ymin = DBL_MAX;
		ITI_real xmax = -DBL_MAX;
		ITI_real xmin = DBL_MAX;
		ITI_int size = pCurve->size;
		for (i=0; i < size; ++i){
			ymax = __max(ymax, GetAt(pCurve->pY[seqIdx], pCurve, i, bHystSeq));
			ymin = __min(ymin, GetAt(pCurve->pY[seqIdx], pCurve, i, bHystSeq));
			xmax = __max(xmax, GetAt(pCurve->pX, pCurve, i, 0));
			xmin = __min(xmin, GetAt(pCurve->pX, pCurve, i, 0));
		}

		scale = (ymax - ymin)/(xmax - xmin);
		if (scale == 0.0)
			scale = 1.0;
		pCurve->pYScale[seqIdx].scale = scale;
		pCurve->pYScale[seqIdx].bScaleInitialized = ITI_true;
	}
}

static ITI_real GetHyperbolicApproxValue(CurveData* pData, ITI_real x, ITI_int index, ITI_real xi)
{
	ITI_real res = 0.;

	if (pData){
		ITI_int dermeanIdx   = 1;
		ITI_int bIdx = 2;
		ITI_int cIdx = 3;
		ITI_int dIdx = 4;
		ITI_int derdiffIdx   = 5;
		ITI_int size = pData->size;
		ITI_real** pCoeff = pData->pYCoeff;

		ITI_real dx = x-xi;
		ITI_real yscale = GetYScale(pData);
		ITI_real b = GetCoeffVal(size, bIdx, index, pCoeff);
		ITI_real dist = GetCoeffVal(size, dIdx, index, pCoeff);
		if(dx < -dist)
			res = yscale * (GetCoeffVal(size, dermeanIdx, index, pCoeff) - GetCoeffVal(size, derdiffIdx, index, pCoeff)) * dx;
		else if(dx > dist)
			res = yscale * (GetCoeffVal(size, dermeanIdx, index, pCoeff) + GetCoeffVal(size, derdiffIdx, index, pCoeff)) * dx;
		else
			res = yscale * (GetCoeffVal(size, derdiffIdx, index, pCoeff) *
				((1-b)*dist+sqrt(b*dx*dx+GetCoeffVal(size, cIdx, index, pCoeff))) +
				GetCoeffVal(size, dermeanIdx, index, pCoeff) * dx);













	} 

	return res;
} 

static ITI_real GetDerHyperbolicApproxValue(CurveData* pData, ITI_real x, ITI_int index,
																	ITI_real xi)
{
	ITI_real res = 0.0;

	if (pData){
		ITI_int dermeanIdx   = 1;
		ITI_int bIdx = 2;
		ITI_int cIdx = 3;
		ITI_int dIdx = 4;
		ITI_int derdiffIdx   = 5;
		ITI_int size = pData->size;
		ITI_real** pCoeff = pData->pYCoeff;

		ITI_real dx = x-xi;
		ITI_real yscale = GetYScale(pData);
		ITI_real b = GetCoeffVal(size, bIdx, index, pCoeff);
		ITI_real d=b*dx*dx+GetCoeffVal(size, cIdx, index, pCoeff);
		ITI_real dist = GetCoeffVal(size, dIdx, index, pCoeff);
		if(dx < -dist)
			res = yscale * (GetCoeffVal(size, dermeanIdx, index, pCoeff) - GetCoeffVal(size, derdiffIdx, index, pCoeff));
		else if(dx > dist)
			res = yscale * (GetCoeffVal(size, dermeanIdx, index, pCoeff) + GetCoeffVal(size, derdiffIdx, index, pCoeff));
		else if(d == 0)
			res = yscale * GetCoeffVal(size, dermeanIdx, index, pCoeff);
		else
			res = yscale * (GetCoeffVal(size, derdiffIdx, index, pCoeff) * b * dx / sqrt(d) + GetCoeffVal(size, dermeanIdx, index, pCoeff));









	}
	return res;
}

static ITI_real GetDer2HyperbolicApproxValue(CurveData* pData, ITI_real x, ITI_int index,
																	ITI_real xi)
{
	ITI_real res = 0.0;

	if (pData){
		 
		ITI_int bIdx = 2;
		ITI_int cIdx = 3;
		ITI_int dIdx = 4;
		ITI_int derdiffIdx   = 5;
		ITI_int size = pData->size;
		ITI_real** pCoeff = pData->pYCoeff;

		ITI_real dx = x-xi;
		ITI_real yscale = GetYScale(pData);
		ITI_real b = GetCoeffVal(size, bIdx, index, pCoeff);
		ITI_real d=b*dx*dx+GetCoeffVal(size, cIdx, index, pCoeff);
		ITI_real dist = GetCoeffVal(size, dIdx, index, pCoeff);
		if(dx < -dist)
			res = 0;
		else if(dx > dist)
			res = 0;
		else if(d == 0)
			res = 0;
		else
			res = yscale * GetCoeffVal(size, derdiffIdx, index, pCoeff) * b * (1-b*dx*dx/d) / sqrt(d);









	}
	return res;
}

static ITI_real GetArcApproxValue(CurveData* pData, ITI_real x, ITI_int index, ITI_real xi)
{
	ITI_real res = 0.;

	if (pData){
		ITI_int c1Idx = 1;
		ITI_int dx3Idx = 6;
		ITI_int size = pData->size;
		ITI_real** pCoeff = pData->pYCoeff;

		ITI_real yscale = GetYScale(pData);
		ITI_real c1 = GetCoeffVal(size, c1Idx, index, pCoeff);
		ITI_real x3 = xi + GetCoeffVal(size, dx3Idx, index, pCoeff);

		if (x <= x3){
			res = yscale*c1*(x - xi);
		} 
		else {
			ITI_int c2Idx = 2;
			ITI_int dx4Idx = 7;
			ITI_real c2 = GetCoeffVal(size, c2Idx, index, pCoeff);
			ITI_real x4 = xi + GetCoeffVal(size, dx4Idx, index, pCoeff);

			if (x >= x4){
				res = yscale*c2*(x - xi);
			} 
			else {
				ITI_int dxmIdx = 3;
				ITI_int dymIdx = 4;
				ITI_int r2Idx = 5;
				ITI_real xm = xi + GetCoeffVal(size, dxmIdx, index, pCoeff);
				ITI_real r2 = GetCoeffVal(size, r2Idx, index, pCoeff);

				if (fabs(c1-c2)<DBL_EPSILON*__max(fabs(c1), fabs(c2))*10)
					res = yscale*c1*(x-xi);
				else if (c2 > c1)
					res = yscale * (GetCoeffVal(size, dymIdx, index, pCoeff)-
						sqrt(r2-(x-xm)*(x-xm)));
				else
					res = yscale * (GetCoeffVal(size, dymIdx, index, pCoeff)+
						sqrt(r2-(x-xm)*(x-xm)));
			} 
		} 
	} 

	return res;
} 

static ITI_real GetDerArcApproxValue(CurveData* pData, ITI_real x, ITI_int index,
																ITI_real xi)
{
	ITI_real res = 0;

	if (pData){
		ITI_int c1Idx = 1;
		 
		ITI_int dx3Idx = 6;
		ITI_int size = pData->size;
		ITI_real** pCoeff = pData->pYCoeff;

		ITI_real yscale = GetYScale(pData);
		ITI_real c1 = GetCoeffVal(size, c1Idx, index, pCoeff);
		ITI_real x3 = xi + GetCoeffVal(size, dx3Idx, index, pCoeff);
		if (x <= x3)
			res = yscale*c1;
		else {
			ITI_int c2Idx = 2;
			ITI_int dx4Idx = 7;
			ITI_real c2 = GetCoeffVal(size, c2Idx, index, pCoeff);
			ITI_real x4 = xi + GetCoeffVal(size, dx4Idx, index, pCoeff);

			if (x >= x4)
				res = yscale*GetCoeffVal(size, c2Idx, index, pCoeff);
			else {
				ITI_int dxmIdx = 3;
				ITI_int r2Idx = 5;
				ITI_real xm = xi + GetCoeffVal(size, dxmIdx, index, pCoeff);
				ITI_real r2 = GetCoeffVal(size, r2Idx, index, pCoeff);

				if (c2 > c1)
					res = yscale * (x-xm)/sqrt(r2-(x-xm)*(x-xm));
				else if (GetCoeffVal(size, c2Idx, index, pCoeff) <
						GetCoeffVal(size, c1Idx, index, pCoeff))
					res = yscale * (-(x-xm)/sqrt(r2-(x-xm)*(x-xm)));
				else
					res = yscale * GetCoeffVal(size, c1Idx, index, pCoeff);
			}
		}
	}
	return res;
}

static ITI_real GetDer2ArcApproxValue(CurveData* pData, ITI_real x, ITI_int index, ITI_real xi)
{
	ITI_real res = 0.0;

	if (pData){
		 
		ITI_int dx3Idx = 6;
		ITI_int size = pData->size;
		ITI_real** pCoeff = pData->pYCoeff;

		ITI_real yscale = GetYScale(pData);
		ITI_real x3 = xi + GetCoeffVal(size, dx3Idx, index, pCoeff);
		if (x <= x3)
			res = 0;
		else {
			ITI_int dx4Idx = 7;
			ITI_real x4 = xi + GetCoeffVal(size, dx4Idx, index, pCoeff);
			if (x >= x4)
				res = 0.;
			else {
				ITI_int c1Idx = 1;
				ITI_int c2Idx = 2;
				ITI_int dxmIdx = 3;
				ITI_int r2Idx = 5;
				ITI_real c1 = GetCoeffVal(size, c1Idx, index, pCoeff);
				ITI_real c2 = GetCoeffVal(size, c2Idx, index, pCoeff);
				ITI_real xm = xi + GetCoeffVal(size, dxmIdx, index, pCoeff);
				ITI_real r2 = GetCoeffVal(size, r2Idx, index, pCoeff);

				if (c2 > c1){
					ITI_real xm2 = (x-xm)*(x-xm);
					ITI_real arg = r2 - xm2;
					res = yscale*(1+xm2/arg)/sqrt(arg);
				}
				else if (c2 < c1){
					ITI_real xm2 = (x-xm)*(x-xm);
					ITI_real arg = r2 - xm2;
					res = -yscale*(1+xm2/arg)/sqrt(arg);
				}
				else
					res = 0.;
			}
		}
	}
	return res;
}

static ITI_real GetQuadraticApproxValue(CurveData* pData, ITI_real x, ITI_int index, ITI_real xi)
{
	ITI_real res = 0.;

	if (pData){
		ITI_int c1Idx = 1;
		ITI_int c2Idx = 2;
		ITI_int distIdx = 3;
		ITI_int size = pData->size;
		ITI_real** pCoeff = pData->pYCoeff;

		ITI_real dx = x - xi;
		ITI_real yscale = GetYScale(pData);
		ITI_real c1 = GetCoeffVal(size, c1Idx, index, pCoeff);
		ITI_real c2 = GetCoeffVal(size, c2Idx, index, pCoeff);
		ITI_real dist = GetCoeffVal(size, distIdx, index, pCoeff);

		if (dx <= -dist)
			 
			res = yscale*c1*dx;
		else if (dx >= dist)
			 
			res = yscale*c2*dx;
		else if (c1 == c2)
			

			res = yscale*c1*dx;
		else
			res = yscale*(c2*(dx+dist)*(dx+dist)-c1*(dx-dist)*(dx-dist))/(4*dist);
	}

	return res;
} 

static ITI_real GetDerQuadraticApproxValue(CurveData* pData, ITI_real x, ITI_int index, ITI_real xi)
{
	ITI_real res = 0;

	if (pData){
		ITI_int c1Idx = 1;
		ITI_int c2Idx = 2;
		ITI_int distIdx = 3;
		ITI_int size = pData->size;
		ITI_real** pCoeff = pData->pYCoeff;

		ITI_real dx = x - xi;
		ITI_real yscale = GetYScale(pData);
		ITI_real c1 = GetCoeffVal(size, c1Idx, index, pCoeff);
		ITI_real c2 = GetCoeffVal(size, c2Idx, index, pCoeff);
		ITI_real dist = GetCoeffVal(size, distIdx, index, pCoeff);

		if (dx <= -dist)
			 
			res = yscale*c1;
		else if (dx >= dist)
			 
			res = yscale*c2;
		else if (c1 == c2)
			

			res = yscale*c1;
		else
			res = yscale*(c2*(dx+dist)-c1*(dx-dist))/(2*dist);
	} 

	return res;
} 

static ITI_real GetDer2QuadraticApproxValue(CurveData* pData, ITI_real x, ITI_int index, ITI_real xi)
{
	ITI_real res = 0;

	if (pData){
		ITI_int c1Idx = 1;
		ITI_int c2Idx = 2;
		ITI_int distIdx = 3;
		ITI_int size = pData->size;
		ITI_real** pCoeff = pData->pYCoeff;

		ITI_real dx = x - xi;
		ITI_real yscale = GetYScale(pData);
		ITI_real c1 = GetCoeffVal(size, c1Idx, index, pCoeff);
		ITI_real c2 = GetCoeffVal(size, c2Idx, index, pCoeff);
		ITI_real dist = GetCoeffVal(size, distIdx, index, pCoeff);

		if (dx <= -dist)
			 
			res = 0;
		else if (dx >= dist)
			 
			res = 0;
		else if (c1 == c2)
			

			res = 0;
		else
			res = yscale*(c2-c1)/(2*dist);
	} 

	return res;
} 

static ITI_real CalcY(ITI_CurveSetData* curve, ITI_CurveCallState* cs,
				ITI_SolverInfo* sInfo, ITI_real* zf, ITI_real x, ITI_int seqIdx,
				ITI_ushort bHystCurve)
{
	ITI_real y = 0.0;

	if (curve && cs && sInfo){
		ITI_int size = curve->size;

		if (size == 1){
			if (curve->nY > 0)
				y = curve->pY[seqIdx][0];
		}
		else if (size > 1){
			ITI_bool bExtra = curve->yInfo[seqIdx].bExtrapol;
			ITI_bool bMirror = curve->yInfo[seqIdx].bMirror;
			ITI_bool bCycle = curve->yInfo[seqIdx].bCycle;

			ITI_int idx = -1;
			ITI_real nCycle = 0;
			ITI_real xmin = curve->pX[0];
			ITI_real xmax = curve->pX[size-1];

			ITI_uint isEvent = ITI_false;
			enum Interpol interpol = curve->yInfo[seqIdx].iPol;

			if (bHystCurve)
				bMirror = curve->yInfo[MW_IDX].bMirror;

			if (interpol == InterpolSpline || interpol == InterpolHyperbolicApprox || interpol == InterpolCircualArcApprox || interpol == InterpolQuadraticApprox || !zf || sInfo->isEvent)
				isEvent = ITI_true;

			if (x > xmax || x < xmin){
				if (bCycle){
					ITI_real period = xmax-xmin;
					const ITI_real x_old = x;
					 
					x -= xmin;
					




					 
					x=fmod(x,period);
					if(x<0)
						x+=period;
					nCycle = floor((x_old-x)/period+0.5);
					 
					

					 
					x += xmin;
					if (x < xmin)
						x += period;
					else if (x > xmax)
						x -= period;

					bExtra = ITI_false;
					if (!isEvent){
						if (nCycle < cs->pSeqCs->nCycle){
							x -= period;
						} 
						else if (nCycle > cs->pSeqCs->nCycle){
							x += period;
						} 
					} 

					bMirror = ITI_false;
				} 
				else if (bMirror) {
					if (x < xmin) {
						 
						if (x >= (2*xmin - xmax)) {
							bExtra = ITI_false;
						}
						else if (!bExtra && !CheckEpsilonRange(&x, xmin, xmax)) {
							 
							char msg[500];
							snprintf(msg, 500, "%.400s: x-value %g is out of range (no extrapolation)", curve->name, x);
							assertFunction(0, msg, sInfo);
						}
					} 
					else if (!bExtra && !CheckEpsilonRange(&x, xmin, xmax)) {
						 
						char msg[500];
						snprintf(msg, 500, "%.400s: x-value %g is out of range (no extrapolation)", curve->name, x);
						assertFunction(0, msg, sInfo);
					}
					else
						bMirror = ITI_false;
				} 
				if (!bExtra && !bMirror && !bCycle && !CheckEpsilonRange(&x, xmin, xmax)){
					 
					char msg[500];
					snprintf(msg, 500, "%.400s: x-value %g is out of range (no extrapolation)", curve->name, x);
					assertFunction(0, msg, sInfo);
				} 
			} 
			else {
				

				bExtra = ITI_false;
				bMirror = ITI_false;
			} 

			if (sInfo->isEvent || !zf){
				cs->pSeqCs->nCycle = (ITI_int)nCycle;
				cs->pSeqCs->bExtra = bExtra;
				cs->pSeqCs->bMirror= bMirror;
			} 

			if (cs->pSeqCs->bMirror)
				x = xmin+(xmin-x);

			if (!bExtra){
				idx = FindXValue(curve, cs, sInfo, x, (ITI_ushort)(interpol == InterpolStairs), isEvent || cs->pSeqCs->bExtra != bExtra);

				if (idx > -1){
					if (GetAt(curve->pX, curve, idx, 0) != x || interpol == InterpolHyperbolicApprox ||
								interpol == InterpolCircualArcApprox ||
								interpol == InterpolQuadraticApprox){
						

						CurveData data;
						InitStructCurveData(&data, curve->size, curve->pX,
								curve->pY[seqIdx], curve->pYCoeff[seqIdx],
								curve->pYScale?(&curve->pYScale[seqIdx]):0);

						switch (interpol){
							case InterpolStairs :
								y = GetAt(curve->pY[seqIdx], curve, idx, bHystCurve);
								break;
							case InterpolSpline :
								y = GetSplineValue(x, idx, curve->pX, curve->pY[seqIdx],
									curve->pYCoeff[seqIdx], bCycle, curve, bHystCurve);
								break;
							case InterpolLinear :
								


    
								y = GetAt(curve->pY[seqIdx], curve, idx, bHystCurve) +
									(x- GetAt(curve->pX, curve, idx, 0))*
									(GetAt(curve->pY[seqIdx], curve, idx+1, bHystCurve) -
									GetAt(curve->pY[seqIdx], curve, idx, bHystCurve))/
									(GetAt(curve->pX, curve, idx+1, 0) -
									GetAt(curve->pX, curve, idx, 0));
								break;
							case InterpolHyperbolicApprox :
								{
									int i = idx;
									 
									ITI_real xi = GetAt(curve->pX, curve, idx, 0);
									ITI_real xi_1 = GetAt(curve->pX, curve, idx+1, 0);
									if (xi_1-x < x-xi){
										i++;
										xi = xi_1;
									} 
									 
									y = GetAt(curve->pY[seqIdx], curve, i, bHystCurve)+
										GetHyperbolicApproxValue(&data, x, i, xi);
								}
								break;
							case InterpolCircualArcApprox :
								{
									int i = idx;
									 
									ITI_real xi = GetAt(curve->pX, curve, idx, 0);
									ITI_real xi_1 = GetAt(curve->pX, curve, idx+1, 0);
									if (xi_1-x < x-xi){
										i++;
										xi = xi_1;
									} 
									y = GetAt(curve->pY[seqIdx], curve, i, bHystCurve)+
										GetArcApproxValue(&data, x, i, xi);
								}
								break;
							case InterpolQuadraticApprox :
								{
									int i = idx;
									 
									ITI_real xi = GetAt(curve->pX, curve, idx, 0);
									ITI_real xi_1 = GetAt(curve->pX, curve, idx+1, 0);
									if (xi_1-x < x-xi){
										i++;
										xi = xi_1;
									} 
									y = GetAt(curve->pY[seqIdx], curve, i, bHystCurve)+
										GetQuadraticApproxValue(&data, x, i, xi);
								}
								break;
							default:
								break;
						} 
					} 
					else {
						y = GetAt(curve->pY[seqIdx], curve, idx, bHystCurve);
					} 

					if (cs->pSeqCs->bMirror)
						y = GetAt(curve->pY[seqIdx], curve, 0, bHystCurve)-
						(y-GetAt(curve->pY[seqIdx], curve, 0, bHystCurve));
				} 
			} 
			else {
				 
				ITI_real x1 = 0.;
				ITI_real x2 = 0.;
				ITI_real y1 = 0.;
				ITI_real y2 = 0.;
				ITI_real anstieg = 0.;
				idx = 0;

				if (x > xmax){
					x1 = GetAt(curve->pX, curve , size-1, 0);
					x2 = GetAt(curve->pX, curve , size-2, 0);
					y1 = GetAt(curve->pY[seqIdx], curve, size-1, bHystCurve);
					y2 = GetAt(curve->pY[seqIdx], curve, size-2, bHystCurve);
					idx = size -2;
				} 
				else {
					x1 = GetAt(curve->pX, curve, 0, 0);
					x2 = GetAt(curve->pX, curve, 1, 0);
					y1 = GetAt(curve->pY[seqIdx], curve, 0, bHystCurve);
					y2 = GetAt(curve->pY[seqIdx], curve, 1, bHystCurve);
				} 

				switch (interpol){
					case InterpolStairs :
						anstieg = 0.;
						break;
					case InterpolSpline :
						 
						anstieg = GetDSplineValue(x1, idx, curve->pX, curve->pY[seqIdx],
									curve->pYCoeff[seqIdx], bCycle, curve, bHystCurve);
						break;
					default :
						{
							ITI_real dx = x2 - x1;
							if (fabs(dx) < dbl_epsilon(x1,x2))
								dx = _copysign(dbl_epsilon(x1,x2), dx);
							anstieg = (y2 - y1)/dx;
						}
				} 

				y = (x-x1) * anstieg;
				y += y1;

				if (cs->pSeqCs->bMirror)
					y = GetAt(curve->pY[seqIdx], curve, 0, bHystCurve)-
					(y-GetAt(curve->pY[seqIdx], curve, 0, bHystCurve));
			} 

			 
			if (zf){
				if (interpol == InterpolSpline || interpol == InterpolHyperbolicApprox ||
						interpol == InterpolCircualArcApprox ||
						interpol == InterpolQuadraticApprox){
					if (bMirror)
						*zf = x-xmin;
					else
						 
						*zf = 1.0;

				} 
				else {
					if (bExtra && idx == -1){
						if (x < GetAt(curve->pX, curve, 0, 0))
							idx = 0;
						else
							idx = size-2;
					} 
					if (bExtra && idx == 0 && !bMirror && !bCycle)
						*zf = x - GetAt(curve->pX, curve, idx, 0);
					else {
						ITI_real dx1 = GetAt(curve->pX, curve, idx+1, 0) - x;
						ITI_real dx2 = x - GetAt(curve->pX, curve, idx, 0);
						*zf = fabs(dx1)<fabs(dx2)?dx1:dx2;
					} 
					if (idx%2)
						*zf = -*zf;
				} 

				if (cs->pSeqCs->bMirror)
					*zf = -*zf;
			} 
		} 
	} 

	return y;
} 

ITI_real GetYFromCurve(ITI_CurveSetData* curve, ITI_CurveCallState* cs,
					   ITI_SolverInfo* sInfo, ITI_real* zf, ITI_real x)
{
	return CalcY(curve, cs, sInfo, zf, x, 0, 0);
} 

 

ITI_real GetYdbl(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
			ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_int seqIdx){
	ITI_real y = 0.0;

	if (seqIdx >= 0)
		y = CalcY(pCurve, pCs, pSInfo, zf, x, seqIdx, 0);

	return y;
} 

void GetYFromCurveSet(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
				ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real* y)
{
	if (pCurve && pCs && pSInfo){
		ITI_int seqs = pCurve->nY;
		 

		if (seqs == 1)
			*y = GetYdbl(pCurve, pCs, pSInfo, zf, x, 0);
		else {
			int i = 0;
			for (i=0; i < seqs; i++){
				y[i] = GetYdbl(pCurve, pCs, pSInfo, zf, x, i);
			}
		}
	}
}

ITI_real GetYFromCurveSet2(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
				ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_int seq)
{
	ITI_real y = 0;

	if (pCurve && pCs && pSInfo){
		ITI_int seqs = pCurve->nY;

		if(seq>=0 && seq<seqs)
			y=GetYdbl(pCurve, pCs, pSInfo, zf, x, seq);
	}
	return y;
}

 

static ITI_real CalcYdX(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
				ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_int seqIdx,
				ITI_ushort bHystCurve)
{
	ITI_real y = 0.0;

	if (pCurve && pCs && pSInfo){
		ITI_int size = pCurve->size;

		if (size >= 2){
			enum Interpol interpol = pCurve->yInfo[seqIdx].iPol;

			if (interpol != InterpolStairs){
				ITI_int idx = -1;
				ITI_uint isEvent = ITI_false;
				ITI_real nCycle = 0.0;
				ITI_real xmin = pCurve->pX[0];
				ITI_real xmax = pCurve->pX[size-1];

				ITI_bool bExtra = pCurve->yInfo[seqIdx].bExtrapol;
				ITI_bool bMirror = pCurve->yInfo[seqIdx].bMirror;
				ITI_bool bCycle = pCurve->yInfo[seqIdx].bCycle;

				if (interpol == InterpolSpline || interpol == InterpolHyperbolicApprox || interpol == InterpolCircualArcApprox || interpol == InterpolQuadraticApprox || !zf || pSInfo->isEvent)
					isEvent = ITI_true;

				if (x > xmax || x < xmin){
					if (bCycle){
						ITI_real period = xmax-xmin;
						const ITI_real x_old = x;
						 
						x -= xmin;
						




						 
						x=fmod(x,period);
						if(x<0)
							x+=period;
						nCycle = floor((x_old-x)/period+0.5);
						 
						

						 
						x += xmin;
						if (x < xmin)
							x += period;
						else if (x > xmax)
							x -= period;

						bExtra = ITI_false;
						if (!isEvent){
							if (nCycle < pCs->pSeqCs->nCycle){
								x -= period;
							} 
							else if (nCycle > pCs->pSeqCs->nCycle){
								x += period;
							} 
						} 

						bMirror = ITI_false;
					} 
					else if (bMirror){
						if (x < xmin){
							 
							if (x>=xmin-(xmax-xmin))
								bExtra = ITI_false;
						} 
						else {
							

							bMirror = ITI_false;
						} 
					} 
				} 
				else {
					

					bExtra = ITI_false;
					bMirror = ITI_false;
				} 

				if (pSInfo->isEvent || !zf){
					pCs->pSeqCs->nCycle = (ITI_int)nCycle;
					pCs->pSeqCs->bExtra = bExtra;
					pCs->pSeqCs->bMirror = bMirror;
				} 

				if (pCs->pSeqCs->bMirror)
					x = xmin+(xmin-x);

				if (!bExtra){
					idx = FindXValue(pCurve, pCs, pSInfo, x, (ITI_ushort)(interpol == InterpolStairs), isEvent || pCs->pSeqCs->bExtra != bExtra);

					if (idx > -1){
						

						CurveData data;
						InitStructCurveData(&data, pCurve->size, pCurve->pX,
								pCurve->pY[seqIdx], pCurve->pYCoeff[seqIdx],
								pCurve->pYScale?(&pCurve->pYScale[seqIdx]):0);

						switch (interpol){
							case InterpolSpline :
								y = GetDSplineValue(x, idx, pCurve->pX,
									pCurve->pY[seqIdx],
									pCurve->pYCoeff[seqIdx], bCycle, pCurve, bHystCurve);
								break;
							case InterpolHyperbolicApprox :
								{
									int i = idx;
									 
									ITI_real xi = GetAt(pCurve->pX, pCurve, idx, 0);
									ITI_real xi_1 = GetAt(pCurve->pX, pCurve, idx+1, 0);
									if (xi_1-x < x-xi){
										i++;
										xi = xi_1;
									} 
									y = GetDerHyperbolicApproxValue(&data, x, i, xi);
								}
								break;
							case InterpolCircualArcApprox :
								{
									int i = idx;
									 
									ITI_real xi = GetAt(pCurve->pX, pCurve, idx, 0);
									ITI_real xi_1 = GetAt(pCurve->pX, pCurve, idx+1, 0);
									if (xi_1-x < x-xi){
										i++;
										xi = xi_1;
									} 
									y = GetDerArcApproxValue(&data, x, i, xi);
								}
								break;
							case InterpolQuadraticApprox :
								{
									int i = idx;
									 
									ITI_real xi = GetAt(pCurve->pX, pCurve, idx, 0);
									ITI_real xi_1 = GetAt(pCurve->pX, pCurve, idx+1, 0);
									if (xi_1-x < x-xi){
										i++;
										xi = xi_1;
									} 
									y = GetDerQuadraticApproxValue(&data, x, i, xi);
								}
								break;
							default :  
								{
									ITI_real x1 = GetAt(pCurve->pX, pCurve, idx, 0);
									ITI_real x2 = GetAt(pCurve->pX, pCurve, idx+1, 0);
									ITI_real dx = x2-x1;
									if (fabs(dx) < dbl_epsilon(x1, x2))
										dx = _copysign(dbl_epsilon(x1,x2), dx);

									y = (GetAt(pCurve->pY[seqIdx], pCurve, idx+1, bHystCurve) -
										GetAt(pCurve->pY[seqIdx], pCurve, idx, bHystCurve)) / dx;
								}
								break;
						} 
					} 
				} 
				else {
					 
					if (interpol == InterpolSpline){
						ITI_real xp = GetAt(pCurve->pX, pCurve, 0, 0);
						idx = 0;

						if (x > xmax){
							idx = pCurve->size-2;
							xp = GetAt(pCurve->pX, pCurve, pCurve->size-1, 0);
						} 

						y = GetDSplineValue(xp, idx, pCurve->pX,
									pCurve->pY[seqIdx],
									pCurve->pYCoeff[seqIdx],
									bCycle, pCurve, bHystCurve);
					} 
					else {
						 
						ITI_real x1 = 0.0;
						ITI_real x2 = 0.0;
						ITI_real y1 = 0.0;
						ITI_real y2 = 0.0;
						ITI_real dx = 0.0;

						if (x > xmax){
							x1 = GetAt(pCurve->pX, pCurve, size-2, 0);
							x2 = GetAt(pCurve->pX, pCurve, size-1, 0);
							y1 = GetAt(pCurve->pY[seqIdx], pCurve, size-2, bHystCurve);
							y2 = GetAt(pCurve->pY[seqIdx], pCurve, size-1, bHystCurve);
						} 
						else {
							x1 = GetAt(pCurve->pX, pCurve, 0, 0);
							x2 = GetAt(pCurve->pX, pCurve, 1, 0);
							y1 = GetAt(pCurve->pY[seqIdx], pCurve, 0, bHystCurve);
							y2 = GetAt(pCurve->pY[seqIdx], pCurve, 1, bHystCurve);
						} 

						dx = x2 - x1;
						if (fabs(dx) < dbl_epsilon(x1, x2))
							dx = _copysign(dbl_epsilon(x1, x2), dx);

						y = (y2 - y1)/dx;
					} 
				} 

				 
				if (zf){
					if (interpol == InterpolHyperbolicApprox ||
							interpol == InterpolCircualArcApprox ||
							interpol == InterpolQuadraticApprox){
						if (bMirror)
							*zf = x-xmin;
						else
							 
							*zf = 1.0;
					} 
					else {
						if (interpol == InterpolSpline){
							if (bCycle)
								*zf = 1.0;
							else if (bExtra){
								if (x > xmax)
									*zf = xmax - x;
								else
									*zf = x - xmin;
							} 
							else {
								*zf = (x-xmax)*(x-xmin);
							} 
						} 
						else {
							if (bExtra && !bCycle){
								 
								if (x > xmax){
									*zf = xmax - x;
									if (size%2)
										*zf = -*zf;
								} 
								else
									*zf = x -xmin;
							} 
							else {
								ITI_real dx1 = GetAt(pCurve->pX, pCurve, idx+1, 0) - x;
								ITI_real dx2 = GetAt(pCurve->pX, pCurve, idx, 0);
								*zf = fabs(dx1) < fabs(dx2)?dx1:dx2;
							} 
						} 
					} 

					if (pCs->pSeqCs->bMirror)
						*zf = -*zf;
				} 
			} 
		} 
	} 

	return y;
} 

static ITI_real GetDYdbl(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
			ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_int seqIdx){
	ITI_real y = 0.0;

	if (seqIdx >= 0)
		y = CalcYdX(pCurve, pCs, pSInfo, zf, x, seqIdx, 0);

	return y;
}

ITI_real GetYFromDerCurve(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
				ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real der)
{
	ITI_real y = 0.0;

	if (pCurve && pCs && pSInfo && der != 0.0){
		ITI_int seqs = pCurve->nY;
		 

		if (seqs == 1)
			y = GetDYdbl(pCurve, pCs, pSInfo, zf, x, 0);

		y *= der;
	}
	return y;
}

void GetYFromDerCurveSet(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
			ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real der,
			ITI_real* y)
{
	if (pCurve && pCs && pSInfo){
		int i = 0;
		ITI_int nSeqs = pCurve->nY;

		for (i = 0; i < nSeqs; i++){
			if (der)
				y[i] = der * GetDYdbl(pCurve, pCs, pSInfo, zf, x, i);
		}
	}
}

ITI_real GetYFromDerCurveSet2(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
			ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_int seq, ITI_real der)
{
	ITI_real y = 0;
	if (pCurve && pCs && pSInfo){
		ITI_int nSeqs = pCurve->nY;

		if(0<=seq && seq<nSeqs)
			y = der * GetDYdbl(pCurve, pCs, pSInfo, zf, x, seq);
	}
	return y;
}

 

static ITI_real CalcYd2X(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
				ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_int seqIdx,
				ITI_ushort bHystCurve)
{
	ITI_real y = 0.0;

	if (pCurve && pCs && pSInfo){
		ITI_int size = pCurve->size;

		if (size >= 2){
			enum Interpol interpol = pCurve->yInfo[seqIdx].iPol;

			if (interpol != InterpolStairs && interpol != InterpolLinear){
				ITI_int idx = -1;
				ITI_uint isEvent = ITI_false;
				ITI_real nCycle = 0.0;
				ITI_real xmin = pCurve->pX[0];
				ITI_real xmax = pCurve->pX[size-1];

				ITI_bool bExtra = pCurve->yInfo[seqIdx].bExtrapol;
				ITI_bool bMirror = pCurve->yInfo[seqIdx].bMirror;
				ITI_bool bCycle = pCurve->yInfo[seqIdx].bCycle;

				if (interpol == InterpolSpline || interpol == InterpolHyperbolicApprox || interpol == InterpolCircualArcApprox || interpol == InterpolQuadraticApprox || !zf || pSInfo->isEvent)
					isEvent = ITI_true;

				if (x > xmax || x < xmin){
					if (bCycle){
						ITI_real period = xmax-xmin;
						const ITI_real x_old = x;
						 
						x -= xmin;
						




						 
						x=fmod(x,period);
						if(x<0)
							x+=period;
						nCycle = floor((x_old-x)/period+0.5);
						 
						

						 
						x += xmin;
						if (x < xmin)
							x += period;
						else if (x > xmax)
							x -= period;

						bExtra = ITI_false;
						if (!isEvent){
							if (nCycle < pCs->pSeqCs->nCycle){
								x -= period;
							} 
							else if (nCycle > pCs->pSeqCs->nCycle){
								x += period;
							} 
						} 

						bMirror = ITI_false;
					} 
					else if (bMirror){
						if (x < xmin){
							 
							if (x>=xmin-(xmax-xmin))
								bExtra = ITI_false;
						} 
						else {
							

							bMirror = ITI_false;
						} 
					} 
				} 
				else {
					

					bExtra = ITI_false;
					bMirror = ITI_false;
				} 

				if (pSInfo->isEvent || !zf){
					pCs->pSeqCs->nCycle = (ITI_int)nCycle;
					pCs->pSeqCs->bExtra = bExtra;
					pCs->pSeqCs->bMirror = bMirror;
				} 

				if (pCs->pSeqCs->bMirror)
					x = xmin+(xmin-x);

				if (!bExtra){
					idx = FindXValue(pCurve, pCs, pSInfo, x, (ITI_ushort)(interpol == InterpolStairs), isEvent || pCs->pSeqCs->bExtra != bExtra);

					if (idx > -1){
						CurveData data;
						InitStructCurveData(&data, pCurve->size, pCurve->pX,
								pCurve->pY[seqIdx], pCurve->pYCoeff[seqIdx],
								pCurve->pYScale?(&pCurve->pYScale[seqIdx]):0);

						switch (interpol){
							case InterpolSpline :
								y = GetD2SplineValue(x, idx, pCurve->pX,
									pCurve->pY[seqIdx],
									pCurve->pYCoeff[seqIdx], bCycle);
								break;
							case InterpolHyperbolicApprox :
								{
									int i = idx;
									 
									ITI_real xi = GetAt(pCurve->pX, pCurve, idx, 0);
									ITI_real xi_1 = GetAt(pCurve->pX, pCurve, idx+1, 0);
									if (xi_1-x < x-xi){
										i++;
										xi = xi_1;
									} 
									y = GetDer2HyperbolicApproxValue(&data, x, i, xi);
								}
								break;
							case InterpolCircualArcApprox :
								{
									int i = idx;
									 
									ITI_real xi = GetAt(pCurve->pX, pCurve, idx, 0);
									ITI_real xi_1 = GetAt(pCurve->pX, pCurve, idx+1, 0);
									if (xi_1-x < x-xi){
										i++;
										xi = xi_1;
									} 
									y = GetDer2ArcApproxValue(&data, x, i, xi);
								}
								break;
							case InterpolQuadraticApprox :
								{
									int i = idx;
									 
									ITI_real xi = GetAt(pCurve->pX, pCurve, idx, 0);
									ITI_real xi_1 = GetAt(pCurve->pX, pCurve, idx+1, 0);
									if (xi_1-x < x-xi){
										i++;
										xi = xi_1;
									} 
									y = GetDer2QuadraticApproxValue(&data, x, i, xi);
								}
								break;
							default :  
								y = 0.0;
								break;
						} 
					} 
				} 
				else {
					 
					y = 0.0;
				} 

				 
				if (zf){
					if (interpol == InterpolHyperbolicApprox ||
							interpol == InterpolCircualArcApprox ||
							interpol == InterpolQuadraticApprox){
						if (bMirror)
							*zf = x-xmin;
						else
							 
							*zf = 1.0;
					} 
					else {
						if (interpol == InterpolSpline){
							if (bCycle)
								*zf = 1.0;
							else if (bExtra){
								if (x > xmax)
									*zf = xmax - x;
								else
									*zf = x - xmin;
							} 
							else {
								*zf = (x-xmax)*(x-xmin);
							} 
						} 
						else {
							if (bExtra && !bCycle){
								 
								if (x > xmax){
									*zf = xmax - x;
									if (size%2)
										*zf = -*zf;
								} 
								else
									*zf = x -xmin;
							} 
							else {
								ITI_real dx1 = GetAt(pCurve->pX, pCurve, idx+1, 0) - x;
								ITI_real dx2 = GetAt(pCurve->pX, pCurve, idx, 0);
								*zf = fabs(dx1) < fabs(dx2)?dx1:dx2;
							} 
						} 
					} 

					if (pCs->pSeqCs->bMirror)
						*zf = -*zf;
				} 
			} 
		} 
	} 
	return y;
} 

static ITI_real GetD2Ydbl(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
			ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_int seqIdx){
	ITI_real y = 0.0;

	if (seqIdx >= 0)
		y = CalcYd2X(pCurve, pCs, pSInfo, zf, x, seqIdx, 0);

	return y;
} 

ITI_real GetYFromDer2Curve(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
			ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real der,
			ITI_real der2)
{
	ITI_real y = 0.0;

	if (pCurve && pCs && pSInfo){
		if (der2)
			y = der2 * GetDYdbl(pCurve, pCs, pSInfo, zf, x, 0);
		if (der)
			y = y + der * der* GetD2Ydbl(pCurve, pCs, pSInfo, zf, x, 0);
	} 

	return y;
} 

void GetYFromDer2CurveSet(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
			ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real der,
			ITI_real der2, ITI_real* y)
{
	if (pCurve && pCs && pSInfo){
		int i = 0;
		ITI_int nSeqs = pCurve->nY;

		for (i = 0; i < nSeqs; i++){
			if (der2)
				y[i] = der2 * GetDYdbl(pCurve, pCs, pSInfo, zf, x, i);
			else
				y[i] = 0.;
			if (der)
				y[i] = y[i] + der * der* GetD2Ydbl(pCurve, pCs, pSInfo, zf, x, i);
		} 
	} 
} 

ITI_real GetYFromDer2CurveSet2(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
			ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_int seq, ITI_real der,
			ITI_real der2)
{
	ITI_real y = 0;
	if (pCurve && pCs && pSInfo){
		ITI_int nSeqs = pCurve->nY;

		if(0<=seq && seq<nSeqs) {
			if (der2)
				y = der2 * GetDYdbl(pCurve, pCs, pSInfo, zf, x, seq);
			if (der)
				y = y + der * der* GetD2Ydbl(pCurve, pCs, pSInfo, zf, x, seq);
		}
	} 
	return y;
} 

 

static ITI_real GetMaxParam(ITI_CurveSetData* pCurve)
{
	ITI_real max = -1.0;
	if (pCurve){
		ITI_int size = pCurve->nY;
		if (size > 0){
			ITI_SeqInfoY sInfo = pCurve->yInfo[size-1];
			max = sInfo.param;
		} 
	} 
	return max;
} 

static ITI_real GetMinParam(ITI_CurveSetData* pCurve)
{
	ITI_real min = -1.0;
	if (pCurve){
		ITI_int size = pCurve->nY;
		if (size > 0){
			ITI_SeqInfoY sInfo = pCurve->yInfo[0];
			min = sInfo.param;
		} 
	} 
	return min;
} 

static ITI_real GetLocalParam(ITI_CurveSetData* pCurve, ITI_int seqIdx)
{
	ITI_real param = -1.0;
	if (pCurve){
		ITI_int size = pCurve->nY;
		if (seqIdx < size){
			ITI_SeqInfoY sInfo = pCurve->yInfo[seqIdx];
			param = sInfo.param;
		} 
	} 
	return param;
} 

static void GetCurveIdx(ITI_CurveSetData* pCurve, ITI_real scharParam, ITI_int* low,
																ITI_int* high)
{
	if (pCurve){
		if (scharParam > GetMaxParam(pCurve)){
			*high = pCurve->nY-1;
			*low = __max(0, *high-1);
		} 
		else if (scharParam < GetMinParam(pCurve)){
			*high = __min((unsigned int)1, pCurve->nY-1);
			*low = 0;
		} 
		else {
			ITI_int i = 1;
			ITI_int max = pCurve->nY;

			if (max == 1){
				*low = 0;
				*high = 0;
			} 

			for (; i < max; i++){
				ITI_real d = GetLocalParam(pCurve, i);
				if (d == scharParam){
					*low = i;
					*high = i;
					break;
				} 
				if (scharParam < d){
					*low = i-1;
					*high = i;
					break;
				} 
			} 
		} 
	} 
} 

ITI_real GetCurveFamYdbl(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
							ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x,
														ITI_real scharParam)
{
	ITI_real y = 0.0;

	if (pCurve){
		ITI_int low = -1;
		ITI_int high = -1;

		GetCurveIdx(pCurve, scharParam, &low, &high);

		if (low >= 0 && high >= 0){
			if (low == high){
				y = GetYdbl(pCurve, pCs, pSInfo, zf, x, low);
			} 
			else {
				ITI_real lowParam = GetLocalParam(pCurve, low);
				ITI_real highParam = GetLocalParam(pCurve, high);

				ITI_real prel = (scharParam-lowParam)/(highParam-lowParam);
				ITI_real y1 = GetYdbl(pCurve, pCs, pSInfo, zf, x, low);
				ITI_real y2 = GetYdbl(pCurve, pCs, pSInfo, zf, x, high);

				y = y1+prel*(y2-y1);
			} 
		} 
	} 

	return y;
} 

ITI_real GetYFromCurveFam(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
				ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real p)
{
	ITI_real y = 0.;

	if (pCurve && pCs && pSInfo){
		y = GetCurveFamYdbl(pCurve, pCs, pSInfo, zf, x, p);
	} 

	return y;
} 

 

ITI_real GetCurveFamDYdbl(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
							ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x,
									ITI_real scharParam, ITI_ushort bp_dot)
{
	ITI_real dy = 0.0;

	ITI_int low = -1;
	ITI_int high = -1;

	GetCurveIdx(pCurve, scharParam, &low, &high);

	if (low >= 0 && high >= 0){
		if (!bp_dot){
			if (low == high){
				dy = GetDYdbl(pCurve, pCs, pSInfo, zf, x, low);
			}
			else {
				ITI_real lowParam = GetLocalParam(pCurve, low);
				ITI_real highParam = GetLocalParam(pCurve, high);

				ITI_real prel = (scharParam-lowParam)/(highParam-lowParam);
				ITI_real y1 = GetDYdbl(pCurve, pCs, pSInfo, zf, x, low);
				ITI_real y2 = GetDYdbl(pCurve, pCs, pSInfo, zf, x, high);

				dy = y1+prel*(y2-y1);
			}
		}
		else if (!((low == high) || (low < 0 || high < 0))){
			ITI_real lowParam = GetLocalParam(pCurve, low);
			ITI_real highParam = GetLocalParam(pCurve, high);

			ITI_real y1 = GetYdbl(pCurve, pCs, pSInfo, zf, x, low);
			ITI_real y2 = GetYdbl(pCurve, pCs, pSInfo, zf, x, high);

			dy = (y2 - y1)/(highParam-lowParam);
		}
	}

	return dy;
} 

ITI_real GetYFromDerCurveFam(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
				ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real p,
				ITI_real x_dot, ITI_real p_dot)
{
	ITI_real y = 0.;

	if (pCurve && pCs && pSInfo){
		if (x_dot)
			y = x_dot*GetCurveFamDYdbl(pCurve, pCs, pSInfo, zf, x, p, 0);
		if (p_dot)
			y = y + p_dot* GetCurveFamDYdbl(pCurve, pCs, pSInfo, zf, x, p, 1);
	}
	return y;
}

 

ITI_real GetCurveFamD2Ydbl(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
							ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x,
									ITI_real scharParam, ITI_ushort bp_dot)
{
	ITI_real dy = 0.0;
	ITI_int low = -1;
	ITI_int high = -1;

	GetCurveIdx(pCurve, scharParam, &low, &high);

	if (low >= 0 && high >= 0){
		if (!bp_dot){
			if (low == high)
				dy = GetD2Ydbl(pCurve, pCs, pSInfo, zf, x, low);
			else {
				ITI_real lowParam = GetLocalParam(pCurve, low);
				ITI_real highParam = GetLocalParam(pCurve, high);

				ITI_real prel = (scharParam-lowParam)/(highParam-lowParam);
				ITI_real y1 = GetDYdbl(pCurve, pCs, pSInfo, zf, x, low);
				ITI_real y2 = GetDYdbl(pCurve, pCs, pSInfo, zf, x, high);

				dy = y1+prel*(y2-y1);
			}
		}
		else if (!((low == high) || (low < 0 || high < 0))){
			ITI_real lowParam = GetLocalParam(pCurve, low);
			ITI_real highParam = GetLocalParam(pCurve, high);

			ITI_real y1 = GetYdbl(pCurve, pCs, pSInfo, zf, x, low);
			ITI_real y2 = GetYdbl(pCurve, pCs, pSInfo, zf, x, high);

			dy = (y2 - y1)/(highParam-lowParam);
		}
	}
	return dy;
}

ITI_real GetYFromDer2CurveFam(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
				ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real p,
				ITI_real x_dot, ITI_real p_dot, ITI_real x_dot2, ITI_real p_dot2)
{
	ITI_real y = 0.;

	if (pCurve && pCs && pSInfo){
		if (x_dot2)
			y = x_dot2*GetCurveFamDYdbl(pCurve, pCs, pSInfo, zf, x, p, 0);
		if (x_dot)
			y = y + x_dot*x_dot*GetCurveFamD2Ydbl(pCurve, pCs, pSInfo, zf, x, p, 0);
		if (x_dot && p_dot)
			y = y + 2*x_dot*p_dot*GetCurveFamD2Ydbl(
											pCurve, pCs, pSInfo, zf, x, p, 1);
		if (p_dot2)
			y = y + p_dot2*GetCurveFamDYdbl(pCurve, pCs, pSInfo, zf, x, p, 1);
	}
	return y;
}

 

static void swap(ITI_real* a, ITI_real* b)
{
	ITI_real tmp = *a;
	*a = *b;
	*b = tmp;
}

static ITI_ushort InHorizontalMode(ITI_HystCurveInitData* pHystInitData)
{
	if (pHystInitData->hystMode == HystModeDiscontHorizontal)
		return 1;
	else
		return 0;
}

static ITI_ushort InContinousMode(ITI_HystCurveInitData* pHystInitData)
{
	if (pHystInitData->hystMode == HystModeContinous)
		return 1;
	else
		return 0;
}

static ITI_real GetHystDelta(ITI_real x, ITI_ushort bUp, ITI_CurveSetData* pCurve,
							ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo,
							ITI_real* zf)
{
	ITI_real y = 0.0;
	ITI_real f = 1.0;

	if (pCurve->yInfo[MW_IDX].bMirror){
		ITI_real xmin = GetAt(pCurve->pX, pCurve, 0, 0);

		if (x < xmin){
			x = xmin + (xmin-x);
			if (bUp)
				bUp = 0;
			else
				bUp = 1;
			 
			f = -1.0;
		}
	}

	if (bUp)
		y = CalcY(pCurve, pCs, pSInfo, zf, x, HI_IDX, 1);
	else
		y = CalcY(pCurve, pCs, pSInfo, zf, x, LO_IDX, 1);

	y *= f;

	return y;
}

static ITI_real GetHystDDelta(ITI_real x, ITI_ushort bUp, ITI_CurveSetData* pCurve,
							ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo,
							ITI_real* zf)
{
	ITI_real y = 0.0;
	ITI_real f = 1.0;

	if (pCurve->yInfo[MW_IDX].bMirror){
		ITI_real xmin = GetAt(pCurve->pX, pCurve, 0, 0);

		if (x < xmin){
			x = xmin + (xmin-x);
			if (bUp)
				bUp = 0;
			else
				bUp = 1;
			 
			f = -1.0;
		}
	}

	if (bUp)
		y = CalcYdX(pCurve, pCs, pSInfo, zf, x, HI_IDX, 1);
	else
		y = CalcYdX(pCurve, pCs, pSInfo, zf, x, LO_IDX, 1);

	y *= f;

	return y;
}

static ITI_real GetHystD2Delta(ITI_real x, ITI_ushort bUp, ITI_CurveSetData* pCurve,
	ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo,
	ITI_real* zf)
{
	ITI_real y = 0.0;
	ITI_real f = 1.0;

	if (pCurve->yInfo[MW_IDX].bMirror) {
		ITI_real xmin = GetAt(pCurve->pX, pCurve, 0, 0);

		if (x < xmin) {
			x = xmin + (xmin - x);
			if (bUp)
				bUp = 0;
			else
				bUp = 1;
			 
			f = -1.0;
		}
	}

	if (bUp)
		y = CalcYd2X(pCurve, pCs, pSInfo, zf, x, HI_IDX, 1);
	else
		y = CalcYd2X(pCurve, pCs, pSInfo, zf, x, LO_IDX, 1);

	y *= f;

	return y;
}

ITI_real GetHystLower(ITI_real x, ITI_CurveSetData* pCurve,
					  ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo)
{
	return GetHystDelta(x, 0, pCurve, pCs, pSInfo, 0);
}

ITI_real GetHystUpper(ITI_real x, ITI_CurveSetData* pCurve,
					  ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo)
{
	return GetHystDelta(x, 1, pCurve, pCs, pSInfo, 0);
}

static ITI_real GetHystDLower(ITI_real x, ITI_CurveSetData* pCurve,
					  ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo)
{
	return GetHystDDelta(x, 0, pCurve, pCs, pSInfo, 0);
}

static ITI_real GetHystDUpper(ITI_real x, ITI_CurveSetData* pCurve,
					  ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo)
{
	return GetHystDDelta(x, 1, pCurve, pCs, pSInfo, 0);
}

static ITI_real GetHystD2Lower(ITI_real x, ITI_CurveSetData* pCurve,
	ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo)
{
	return GetHystD2Delta(x, 0, pCurve, pCs, pSInfo, 0);
}

static ITI_real GetHystD2Upper(ITI_real x, ITI_CurveSetData* pCurve,
	ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo)
{
	return GetHystD2Delta(x, 1, pCurve, pCs, pSInfo, 0);
}

ITI_real GetHystMw(ITI_real x, ITI_CurveSetData* pCurve,
					ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo,
					ITI_real* zf)
{
	ITI_real y = 0.0;

	if (pCurve && pCs){
		y = CalcY(pCurve, pCs, pSInfo, zf, x, MW_IDX, 0);

		if (pCurve->yInfo[MW_IDX].bMirror){
			ITI_real xmin = GetAt(pCurve->pX, pCurve, 0, 0);

			if (x < xmin){
				ITI_real a = GetAt(pCurve->pY[HI_IDX], pCurve, 0, 1);
				ITI_real b = GetAt(pCurve->pY[LO_IDX], pCurve, 0, 1);
				y += a + b;
			}
		}
	}
	return y;
}

static ITI_real GetHystDMw(ITI_real x, ITI_CurveSetData* pCurve,
					ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo,
					ITI_real* zf)
{
	ITI_real dy = 0.0;
	if (pCurve && pCs){
		dy = CalcYdX(pCurve, pCs, pSInfo, zf, x, MW_IDX, 0);

		if (pCurve->yInfo[MW_IDX].bMirror){
			ITI_real xmin = GetAt(pCurve->pX, pCurve, 0, 0);

			if (x < xmin){
				ITI_real da = 0;
				ITI_real db = 0;
				x = xmin + (xmin-x);

				da = CalcYdX(pCurve, pCs, pSInfo, zf, x, HI_IDX, 1);
				db = CalcYdX(pCurve, pCs, pSInfo, zf, x, LO_IDX, 1);
				dy = -dy - da - db;
			}
		}
	}
	return dy;
}

ITI_real GetHystDerMw(ITI_real x, ITI_real der, ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf) {
	ITI_real y = 0.0;

	if (pCurve && pCs && pSInfo && der != 0.0)
		y = der * GetHystDMw(x, pCurve, pCs, pSInfo, zf);

	return y;
}

static ITI_real GetHystD2Mw(ITI_real x, ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf)
{
	ITI_real dy = 0.0;
	if (pCurve && pCs) {
		dy = CalcYd2X(pCurve, pCs, pSInfo, zf, x, MW_IDX, 0);

		if (pCurve->yInfo[MW_IDX].bMirror) {
			ITI_real xmin = GetAt(pCurve->pX, pCurve, 0, 0);

			if (x < xmin) {
				ITI_real da = 0;
				ITI_real db = 0;
				x = xmin + (xmin - x);

				da = CalcYd2X(pCurve, pCs, pSInfo, zf, x, HI_IDX, 1);
				db = CalcYd2X(pCurve, pCs, pSInfo, zf, x, LO_IDX, 1);
				dy = -dy - da - db;
			}
		}
	}
	return dy;
}

ITI_real GetHystDer2Mw(ITI_real x, ITI_real der, ITI_real der2, ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs, ITI_SolverInfo* pSInfo, ITI_real* zf) {
	ITI_real y = 0.0;

	if (pCurve && pCs && pSInfo) {
		if (der2)
			y = der2 * GetHystDMw(x, pCurve, pCs, pSInfo, zf);
		if (der)
			y = y + der * der* GetHystD2Mw(x, pCurve, pCs, pSInfo, zf);
	}

	return y;
}

#define NEW_FORMULA
ITI_real GetYFromHystCurve(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
	ITI_HystCurveCallState* pHcs, ITI_SolverInfo* pSInfo,
	ITI_real* zf, ITI_real* pre_zf, ITI_real x,
	ITI_real dx_dt, ITI_real gamma,
	ITI_HystCurveInitData* pHystInitData)
{
	ITI_real y = 0.0;

	if (pCurve && pCs && pHcs && pSInfo && pHystInitData) {
		ITI_real _zf[8] = {0, 0, 0, 0, 0, 0, 0, 0};
		ITI_real _pre_zf[8] = {0, 0, 0, 0, 0, 0, 0, 0};
		ITI_real* __zf = (zf == NULL) ? _zf : zf;
		const ITI_real* __pre_zf = (pre_zf == NULL) ? _pre_zf : pre_zf;
		ITI_real lower_i = 0.0;
		ITI_real upper_i = 0.0;
		ITI_real upper = 0.0;
		ITI_real lower = 0.0;
		ITI_real dupper = 0.0;
		ITI_real dlower = 0.0;
		ITI_real sign3 = 0.0;
		ITI_real delta = 0;
		ITI_real eps = pHystInitData->eps_xdot;

		if (pSInfo->isEvent)
			__pre_zf = __zf;  

		if (eps < 1e-10)
			eps = 1e-10;

		if (!pHcs->bInitialized) {
			ITI_int z = 0;
			for (z = 0; z < NHYSTZERO; z++) {
				__zf[z] = InHorizontalMode(pHystInitData) ? 0.0 : 1.0;
			}
			pHcs->direction = InHorizontalMode(pHystInitData) ? 0 : dx_dt>0 ? 1 : -1;  
			pHcs->bInitialized = ITI_true;
		}

		CalcHystScale(pCurve);

		 
		dx_dt = dx_dt + sign(__pre_zf[0])*eps;

		 

		upper_i = GetHystUpper(x, pCurve, pCs, pSInfo);
		lower_i = GetHystLower(x, pCurve, pCs, pSInfo);
		if (pSInfo->isInitial) {
			y = y + pHystInitData->startY;

			switch (pHystInitData->hystStartValue) {
			case HystStartValueUpper:
				y = upper_i;
				break;
			case HystStartValueLower:
				y = lower_i;
				break;
			case HystStartValueMeanValue:
				y = GetHystMw(x, pCurve, pCs, pSInfo, &(__zf[NHYSTZERO]));
				break;
			default:
				y = __max(y, __min(lower_i, upper_i));
				y = __min(y, __max(lower_i, upper_i));
			}
		}
		



		 
		delta += fabs(upper_i - lower_i);
		if (delta <= 1e-65) {
			ITI_real dupper_i = GetHystDUpper(x, pCurve, pCs, pSInfo);
			ITI_real dlower_i = GetHystDLower(x, pCurve, pCs, pSInfo);
			delta += fabs(dupper_i - dlower_i);
		}
		__zf[3] = upper_i - lower_i;
		sign3 = sign(__pre_zf[3]);
		if (pSInfo->isEvent)
			sign3 = __zf[3];

		if (sign3 < 0)
			swap(&upper_i, &lower_i);

		if (InContinousMode(pHystInitData))
			swap(&upper_i, &lower_i);

		if (pHystInitData->bClockwise)
			swap(&upper_i, &lower_i);

		upper = upper_i;
		lower = lower_i;

		if (InHorizontalMode(pHystInitData)) {
			dupper = GetHystDUpper(x, pCurve, pCs, pSInfo);
			dlower = GetHystDLower(x, pCurve, pCs, pSInfo);
			if (sign3 < 0)
				swap(&dupper, &dlower);
			if (pHystInitData->bClockwise)
				swap(&dupper, &dlower);
		}

		if (!pSInfo->isInitial) {
			if (InContinousMode(pHystInitData)) {
				ITI_real mw = GetHystMw(x, pCurve, pCs, pSInfo, &(__zf[NHYSTZERO]));
				ITI_real d_up = upper - mw;
				ITI_real d_low = lower - mw;
#if !defined NEW_FORMULA
				ITI_real abw = (d_up - d_low) / 2.0;
				ITI_real offset = d_up - abw;
				ITI_real y_tb = pHcs->yTurnBack;
#else
				ITI_real lambda_tb = pHcs->lambdaTurnBack;
#endif
				ITI_real x_tb = pHcs->xTurnBack;
#if !defined NEW_FORMULA
				y = mw + y_tb + (abw + (offset - y_tb)*pHcs->direction)*tanh(gamma*(x - x_tb));
				 
				if (d_up > d_low) {
					if (y>mw + d_up)
						y = mw + d_up;
					if (y<mw + d_low)
						y = mw + d_low;
				}
				else {
					if (y<mw + d_up)
						y = mw + d_up;
					if (y>mw + d_low)
						y = mw + d_low;
				}
#else
				y = mw + d_low + (d_up - d_low)*(lambda_tb + tanh(gamma*(x - x_tb))*(0.5 + pHcs->direction*(0.5 - lambda_tb)));
#endif
				 
				 
				














			}
			else {
				if (pHcs->direction >= 1)
					y = lower;
				else if (pHcs->direction <= -1)
					y = upper;
				else
					y = pHcs->lastY;
			}
		}

		pHcs->lastYCi = y;

		if (pHcs->direction == 0) {
			ITI_real tanhTerm = 0.5 * tanh(2 * dx_dt / eps);
			__zf[1] = y - lower;
			__zf[2] = upper - y;
			__zf[4] = dlower*(0.5 + tanhTerm) + dupper*(0.5 - tanhTerm);
		}
		else
		{
			 
			 
			__zf[0] = dx_dt;
		}
		if ((pHcs->direction == -2) || (pHcs->direction == 2)) {
			__zf[5] = dlower;
			__zf[6] = dupper;
		}

		if (delta <= 1e-65)
			__zf[0] = __pre_zf[0];

		 
		if (pSInfo->isEvent) {
			ITI_ushort turnback = 0;
			if (pHcs->direction == 0) {
				if (pHystInitData->bClockwise) {
					if (sign(__zf[4])>0) {
						if (dx_dt>0)  
							pHcs->direction = 1;
						else
							pHcs->direction = -1;
					}
					else if (sign(__zf[1])>0) {  
						if (dx_dt >= 0)	 
							pHcs->direction = 1;
						else
							pHcs->direction = 2;
					}
					else if (sign(__zf[2])>0) {  
						if (dx_dt <= 0)	 
							pHcs->direction = -1;
						else
							pHcs->direction = -2;
					}
				}
				else {
					if (sign(__zf[4])<0) {
						if (dx_dt>0)  
							pHcs->direction = 1;
						else
							pHcs->direction = -1;
					}
					else if (sign(__zf[1])<0) {  
						if (dx_dt >= 0)	 
							pHcs->direction = 1;
						else
							pHcs->direction = 2;
					}
					else if (sign(__zf[2])<0) {  
						if (dx_dt <= 0)	 
							pHcs->direction = -1;
						else
							pHcs->direction = -2;
					}
				}
			}
			else if (pHcs->direction == 1) {
				if (sign(__zf[0])<0) {  
					turnback = 1;
					if (InHorizontalMode(pHystInitData)) {
						ITI_real m_to = 0.0;
						if (pHystInitData->bClockwise)
							m_to = -dupper;
						else
							m_to = dupper;
						if (m_to < 0)
							pHcs->direction = -1;	 
						else {
							ITI_real m_from = 0.0;
							if (pHystInitData->bClockwise)
								m_from = -dlower;
							else
								m_from = dlower;
							if (m_from > 0)
								pHcs->direction = 0;	 
							else
								pHcs->direction = 2;
						}
					}
					else
						pHcs->direction = -1;
				}
			}
			else if (pHcs->direction == 2) {
				if (sign(__zf[0])>0)  
					pHcs->direction = 1;
				else if (((pHystInitData->bClockwise) && (sign(__zf[6])>0)) || ((!pHystInitData->bClockwise) && (sign(__zf[6])<0)))	 
					pHcs->direction = -1;
				else if (((pHystInitData->bClockwise) && (sign(__zf[5])<0)) || ((!pHystInitData->bClockwise) && (sign(__zf[5])>0)))	 
					pHcs->direction = 0;
			}
			else if (pHcs->direction == -1) {
				if (sign(__zf[0])>0) {  
					turnback = 1;
					if (InHorizontalMode(pHystInitData)) {
						ITI_real m_to = 0.0;
						if (pHystInitData->bClockwise)
							m_to = -dlower;
						else
							m_to = dlower;
						if (m_to < 0)
							pHcs->direction = 1;	 
						else {
							ITI_real m_from = 0.0;
							if (pHystInitData->bClockwise)
								m_from = -dupper;
							else
								m_from = dupper;
							if (m_from > 0)
								pHcs->direction = 0;	 
							else
								pHcs->direction = -2;
						}
					}
					else
						pHcs->direction = 1;
				}
			}
			else if (pHcs->direction == -2) {
				if (sign(__zf[0])<0)  
					pHcs->direction = -1;
				else if (((pHystInitData->bClockwise) && (sign(__zf[5])>0)) || ((!pHystInitData->bClockwise) && (sign(__zf[5])<0)))	 
					pHcs->direction = 1;
				else if (((pHystInitData->bClockwise) && (sign(__zf[6])<0)) || ((!pHystInitData->bClockwise) && (sign(__zf[6])>0)))	 
					pHcs->direction = 0;
			}

			if (InContinousMode(pHystInitData)) {
				if (turnback || pSInfo->isInitial) {
					pHcs->xTurnBack = x;
#if !defined NEW_FORMULA
					pHcs->yTurnBack = y - GetHystMw(x, pCurve, pCs, pSInfo, &dummy_zf);
#else
					if ((upper - lower == 0) || (fabs(upper - lower) < fabs(y - lower)) || ((y - lower) * (upper - lower) < 0)) {
						if (pHcs->direction == 1)
							pHcs->lambdaTurnBack = 1;
						else
							pHcs->lambdaTurnBack = 0;
					}
					else
						pHcs->lambdaTurnBack = (y - lower) / (upper - lower);
#endif
				}
			}
		}
	}
	return y;
}

void UpdateHystCurves(ITI_HystCurveCallState* pHcs, ITI_int nHyst)
{
	if (pHcs)
	{
		ITI_int i = 0;
		for (i = 0; i < nHyst; i++)
		{
			pHcs[i].lastY = pHcs[i].lastYCi;
			 
		}
	}
}

 

ITI_real GetYFromDerHystCurve(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
	ITI_HystCurveCallState* pHcs, ITI_SolverInfo* pSInfo,
	ITI_real* zf, ITI_real* pre_zf, ITI_real x,
	ITI_real dx_dt, ITI_real gamma,
	ITI_HystCurveInitData* pHystInitData)
{
	ITI_real dy = 0.0;

	if (pCurve && pCs && pHcs && pSInfo && pHystInitData) {
		ITI_real _zf[8] = {0, 0, 0, 0, 0, 0, 0, 0};
		ITI_real _pre_zf[8] = {0, 0, 0, 0, 0, 0, 0, 0};
		ITI_real* __zf = (zf == NULL) ? _zf : zf;
		const ITI_real* __pre_zf = (pre_zf == NULL) ? _pre_zf : pre_zf;
		ITI_real upper = 0.0;
		ITI_real lower = 0.0;
		ITI_real dupper = 0.0;
		ITI_real dlower = 0.0;
		ITI_real sign3 = 0.0;

		if (pSInfo->isEvent)
			__pre_zf = __zf;  

		if (!pHcs->bInitialized) {
			ITI_int z = 0;
			for (z = 0; z < NHYSTZERO; z++) {
				__zf[z] = InHorizontalMode(pHystInitData) ? 0.0 : 1.0;
			}
			pHcs->direction = InHorizontalMode(pHystInitData) ? 0 : dx_dt>0 ? 1 : -1;  
			pHcs->bInitialized = ITI_true;
		}

		CalcHystScale(pCurve);

		 

		upper = GetHystUpper(x, pCurve, pCs, pSInfo);
		lower = GetHystLower(x, pCurve, pCs, pSInfo);
		dupper = GetHystDUpper(x, pCurve, pCs, pSInfo);
		dlower = GetHystDLower(x, pCurve, pCs, pSInfo);
		if (pSInfo->isInitial) {
			switch (pHystInitData->hystStartValue) {
			case HystStartValueUpper:
				dy = dupper;
				break;
			case HystStartValueLower:
				dy = dlower;
				break;
			case HystStartValueMeanValue:
			{
				ITI_real dummy_zf = 0.0;
				dy = GetHystDMw(x, pCurve, pCs, pSInfo, &dummy_zf);
			}
			break;
			default:
			{
				ITI_real _small = lower;
				ITI_real big = upper;
				ITI_real dsmall = dlower;
				ITI_real dbig = dupper;
				if (lower > upper) {
					_small = upper;
					big = lower;
					dsmall = dupper;
					dbig = dlower;
				}
				if (pHystInitData->startY < _small)
					dy = dsmall;
				else if (pHystInitData->startY > big)
					dy = dbig;
				else
					dy = 0.0;
			}
			}
		}

		sign3 = sign(__pre_zf[3]);
		if (pSInfo->isEvent)
			sign3 = __zf[3];
		if (sign3 < 0) {
			swap(&upper, &lower);
			swap(&dupper, &dlower);
		}

		if (InContinousMode(pHystInitData)) {
			swap(&upper, &lower);
			swap(&dupper, &dlower);
		}

		if (pHystInitData->bClockwise) {
			swap(&upper, &lower);
			swap(&dupper, &dlower);
		}

		if (!pSInfo->isInitial) {
			if (InContinousMode(pHystInitData)) {
				ITI_real dummy_zf = 0.0;
				ITI_real mw = GetHystMw(x, pCurve, pCs, pSInfo, &dummy_zf);
				ITI_real d_up = upper - mw;
				ITI_real d_low = lower - mw;
				ITI_real dmw = GetHystDMw(x, pCurve, pCs, pSInfo, &dummy_zf);
				ITI_real d_upDx = dupper - dmw;
				ITI_real d_lowDx = dlower - dmw;
#if !defined NEW_FORMULA
				ITI_real abw = (d_up - d_low) / 2.0;
				ITI_real dabw = (d_upDx - d_lowDx) / 2.0;
				ITI_real offset = d_up - abw;
				ITI_real doffset = d_upDx - dabw;
				ITI_real y_tb = pHcs->yTurnBack;
#else
				ITI_real lambda_tb = pHcs->lambdaTurnBack;
#endif
				ITI_real x_tb = pHcs->xTurnBack;
				ITI_real tanhTerm = tanh(gamma*(x - x_tb));
#if !defined NEW_FORMULA
				 
				 
				if (abs(gamma*(x - x_tb)) <340) {
					dy = (abw + (offset - y_tb)*pHcs->direction) / pow(cosh(gamma*(x - x_tb)), 2)*gamma;
					dy += dmw + (dabw + doffset*pHcs->direction)*tanhTerm;
				}
				 
#else
				 
				 
				dy = dmw + d_lowDx + (d_upDx - d_lowDx) * (lambda_tb + tanhTerm*(0.5 + pHcs->direction*(0.5 - lambda_tb)));
				if (abs(gamma*(x - x_tb))<340)
					dy += (d_up - d_low) * (0.5 + pHcs->direction*(0.5 - lambda_tb)) * gamma / pow(cosh(gamma*(x - x_tb)), 2);
#endif
			}
			else {
				if (pHcs->direction >= 1)
					dy = dlower;
				else if (pHcs->direction <= -1)
					dy = dupper;
				else
					dy = 0;
			}
		}
	}
	return dy;
}

ITI_real GetYFromDer2HystCurve(ITI_CurveSetData* pCurve, ITI_CurveCallState* pCs,
	ITI_HystCurveCallState* pHcs, ITI_SolverInfo* pSInfo,
	ITI_real* zf, ITI_real* pre_zf, ITI_real x,
	ITI_real dx_dt, ITI_real gamma,
	ITI_HystCurveInitData* pHystInitData)
{
	ITI_real d2y = 0.0;

	if (pCurve && pCs && pHcs && pSInfo && pHystInitData) {
		ITI_real _zf[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
		ITI_real _pre_zf[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
		ITI_real* __zf = (zf == NULL) ? _zf : zf;
		const ITI_real* __pre_zf = (pre_zf == NULL) ? _pre_zf : pre_zf;
		ITI_real upper = 0.0;
		ITI_real lower = 0.0;
		ITI_real dupper = 0.0;
		ITI_real dlower = 0.0;
		ITI_real d2upper = 0.0;
		ITI_real d2lower = 0.0;
		ITI_real sign3 = 0.0;

		if (pSInfo->isEvent)
			__pre_zf = __zf;  

		if (!pHcs->bInitialized) {
			ITI_int z = 0;
			for (z = 0; z < NHYSTZERO; z++) {
				__zf[z] = InHorizontalMode(pHystInitData) ? 0.0 : 1.0;
			}
			pHcs->direction = InHorizontalMode(pHystInitData) ? 0 : dx_dt>0 ? 1 : -1;  
			pHcs->bInitialized = ITI_true;
		}

		CalcHystScale(pCurve);

		 

		upper = GetHystUpper(x, pCurve, pCs, pSInfo);
		lower = GetHystLower(x, pCurve, pCs, pSInfo);
		dupper = GetHystDUpper(x, pCurve, pCs, pSInfo);
		dlower = GetHystDLower(x, pCurve, pCs, pSInfo);
		dupper = GetHystD2Upper(x, pCurve, pCs, pSInfo);
		dlower = GetHystD2Lower(x, pCurve, pCs, pSInfo);
		if (pSInfo->isInitial) {
			switch (pHystInitData->hystStartValue) {
			case HystStartValueUpper:
				d2y = d2upper;
				break;
			case HystStartValueLower:
				d2y = d2lower;
				break;
			case HystStartValueMeanValue:
			{
				ITI_real dummy_zf = 0.0;
				d2y = GetHystD2Mw(x, pCurve, pCs, pSInfo, &dummy_zf);
			}
			break;
			default:
			{
				ITI_real _small = lower;
				ITI_real big = upper;
				ITI_real d2small = d2lower;
				ITI_real d2big = d2upper;
				if (lower > upper) {
					_small = upper;
					big = lower;
					d2small = d2upper;
					d2big = d2lower;
				}
				if (pHystInitData->startY < _small)
					d2y = d2small;
				else if (pHystInitData->startY > big)
					d2y = d2big;
				else
					d2y = 0.0;
			}
			}
		}

		sign3 = sign(__pre_zf[3]);
		if (pSInfo->isEvent)
			sign3 = __zf[3];
		if (sign3 < 0) {
			swap(&upper, &lower);
			swap(&dupper, &dlower);
			swap(&d2upper, &d2lower);
		}

		if (InContinousMode(pHystInitData)) {
			swap(&upper, &lower);
			swap(&dupper, &dlower);
			swap(&d2upper, &d2lower);
		}

		if (pHystInitData->bClockwise) {
			swap(&upper, &lower);
			swap(&dupper, &dlower);
			swap(&d2upper, &d2lower);
		}

		if (!pSInfo->isInitial) {
			if (InContinousMode(pHystInitData)) {
				ITI_real dummy_zf = 0.0;
				ITI_real mw = GetHystMw(x, pCurve, pCs, pSInfo, &dummy_zf);
				ITI_real d_up = upper - mw;
				ITI_real d_low = lower - mw;
				ITI_real dmw = GetHystDMw(x, pCurve, pCs, pSInfo, &dummy_zf);
				ITI_real d_upDx = dupper - dmw;
				ITI_real d_lowDx = dlower - dmw;
				ITI_real d2mw = GetHystD2Mw(x, pCurve, pCs, pSInfo, &dummy_zf);
				ITI_real d_upD2x = d2upper - d2mw;
				ITI_real d_lowD2x = d2lower - d2mw;
#if !defined NEW_FORMULA
				ITI_real abw = (d_up - d_low) / 2.0;
				ITI_real dabw = (d_upDx - d_lowDx) / 2.0;
				ITI_real d2abw = (d_upD2x - d_lowD2x) / 2.0;
				ITI_real offset = d_up - abw;
				ITI_real doffset = d_upDx - dabw;
				ITI_real d2offset = d_upD2x - d2abw;
				ITI_real y_tb = pHcs->yTurnBack;
#else
				ITI_real lambda_tb = pHcs->lambdaTurnBack;
#endif
				ITI_real x_tb = pHcs->xTurnBack;
				ITI_real tanhTerm = tanh(gamma*(x - x_tb));
#if !defined NEW_FORMULA
				 
				 
				if (abs(gamma*(x - x_tb))<230) {
					d2y = -2 * (abw + (offset - y_tb)*pHcs->direction) * sinh(gamma*(x - x_tb)) / pow(cosh(gamma*(x - x_tb)), 3)*pow(gamma, 2);
					d2y += 2 * (dabw + doffset*pHcs->direction) / pow(cosh(gamma*(x - x_tb)), 2)*gamma;
					d2y += d2mw + (d2abw + d2offset*pHcs->direction)*tanhTerm;
				}
#else
				 
				 
				d2y = d2mw + d_lowD2x + (d_upD2x - d_lowD2x) * (lambda_tb + tanhTerm*(0.5 + pHcs->direction*(0.5 - lambda_tb)));
				if (abs(gamma*(x - x_tb))<340) {
					d2y += 2 * (d_upDx - d_lowDx) * (0.5 + pHcs->direction*(0.5 - lambda_tb)) * gamma / pow(cosh(gamma*(x - x_tb)), 2);
				}
				if (abs(gamma*(x - x_tb))<230) {
					d2y += -2 * (d_up - d_low) * (0.5 + pHcs->direction*(0.5 - lambda_tb)) * pow(gamma, 2) * sinh(gamma*(x - x_tb)) / pow(cosh(gamma*(x - x_tb)), 3);
				}

#endif
			}
			else {
				if (pHcs->direction >= 1)
					d2y = d2lower;
				else if (pHcs->direction <= -1)
					d2y = d2upper;
				else
					d2y = 0;
			}
		}
	}
	return d2y;
}

 

static ITI_ushort ApproxUsed(CalcInfo* pCi)
{
	ITI_ushort res = 0;
	if (pCi){
		res = (pCi->interpol==InterpolHyperbolicApprox ||
			pCi->interpol==InterpolCircualArcApprox)?1:0;
	}
	return res;
}

static void InitCalcInfo(ITI_CurveData_ND* pCurve, CalcInfo* pCi, enum Axis axis)
{
	if (pCurve && pCi){
		ITI_AxisInfo* pAxisInfo = 0;

		switch (axis){
			case AxisX :
				pAxisInfo = &pCurve->axisInfo[0];
				break;
			case AxisY :
				pAxisInfo = &pCurve->axisInfo[1];
				break;
			case AxisZ :
				pAxisInfo = &pCurve->axisInfo[2];
				break;
		}

		pCi->index = -1;
		pCi->index1 = -1;
		pCi->interpol = pAxisInfo->iPol;
		pCi->bExtrapol = pAxisInfo->bExtrapol;
		pCi->bCycle = pAxisInfo->bCycle;
		pCi->bMirror = pAxisInfo->bMirror;
	}
}

static void InitCurveData(ITI_CurveData_ND* pCurve, CurveData* pData, enum Axis axis,
					ITI_int yIndex, ITI_int zIndex, ITI_YScale* pYScale)
{
	if (pCurve && pData){
		pData->size = GetSize(pCurve, axis);
		pData->pX = pCurve->pX;
		pData->pVal = pCurve->pVal + pCurve->sizeX*yIndex +
			pCurve->sizeX*pCurve->sizeY *zIndex;
		pData->pYCoeff = pCurve->pYCoeff[ pCurve->sizeY*zIndex + yIndex];
		if (pYScale)
			pData->pYScale = &pYScale[pCurve->sizeY*zIndex + yIndex];
		else
			pData->pYScale = 0;
	}
}

static ITI_real GetRealMax(ITI_CurveData_ND* pCurve, enum Axis axis)
{
	ITI_real realMax = -DBL_MAX;

	if (pCurve){
		switch (axis){
			case AxisX :
				if (pCurve->sizeX > 0)
					realMax = pCurve->pX[pCurve->sizeX-1];
				break;
			case AxisY :
				if (pCurve->sizeY > 0)
					realMax = pCurve->pY[pCurve->sizeY-1];
				break;
			case AxisZ :
				if (pCurve->sizeZ > 0)
					realMax = pCurve->pZ[pCurve->sizeZ-1];
				break;
		}
	}
	return realMax;
}

static ITI_real GetRealMin(ITI_CurveData_ND* pCurve, enum Axis axis)
{
	ITI_real realMin = DBL_MAX;

	if (pCurve){
		switch (axis){
			case AxisX :
				realMin = pCurve->pX[0];
				break;
			case AxisY :
				realMin = pCurve->pY[0];
				break;
			case AxisZ :
				realMin = pCurve->pZ[0];
				break;
		}
	}
	return realMin;
}

static ITI_int GetSize(ITI_CurveData_ND* pCurve, enum Axis axis)
{
	ITI_int size = 0;

	if (pCurve){
		switch (axis){
			case AxisX :
				size = pCurve->sizeX;
				break;
			case AxisY :
				size = pCurve->sizeY;
				break;
			case AxisZ :
				size = pCurve->sizeZ;
				break;
		}
	}
	return size;
}

static ITI_real GetValAt(ITI_CurveData_ND* pCurve, enum Axis axis, ITI_int index)
{
	ITI_real res = 0.;

	if (pCurve){
		ITI_real* values = 0;
		ITI_int size = 0;

		switch (axis){
			case AxisX :
				values = pCurve->pX;
				size = pCurve->sizeX;
				break;
			case AxisY :
				values = pCurve->pY;
				size = pCurve->sizeY;
				break;
			case AxisZ :
				values = pCurve->pZ;
				size = pCurve->sizeZ;
				break;
		}
		if (values && index < size){
			res = values[index];
		}
	}
	return res;
}

static ITI_real AdjustLookupValue(ITI_real x, ITI_CurveData_ND* pCurve, CalcInfo* pCi,
																enum Axis axis)
{
	if (pCurve && pCi){
		ITI_real realMin = GetRealMin(pCurve, axis);
		ITI_real realMax = GetRealMax(pCurve, axis);

		if (x > realMax || x < realMin){
			if (pCi->bCycle){
				ITI_real period = realMax - realMin;
				x -= realMin;
				x = fmod(x, period);
				x += realMax;
				if (x < realMin)
					x += period;
				else if (x > realMax)
					x -= period;
				pCi->bExtrapol = ITI_false;
				pCi->bMirror = ITI_false;
			}

			if (pCi->bExtrapol && pCi->bMirror){
				if (x < realMin){
					if (x >= realMin-(realMax-realMin)){
						pCi->bExtrapol = ITI_false;
					}
					x = realMin + (realMin - x);
				}
				else {
					pCi->bMirror = ITI_false;
				}
			}
		}
		else {
			pCi->bExtrapol = ITI_false;
			pCi->bMirror = ITI_false;
		}
	}
	return x;
}

static ITI_int FindValue(ITI_real val, enum Axis axis, ITI_ushort bNotUsed,
											ITI_CurveData_ND* pCurve,
											ITI_SeqCallState* pSeqCs,
											ITI_ushort bStairs,
											ITI_ushort bUpdateIndex)
{
	ITI_int pos = 0;

	if (pCurve && pSeqCs)
	{
		ITI_int size = GetSize(pCurve, axis);

		if (size > 1)
		{
			pos = pSeqCs->iPos;
			if (pos < -1)
				pos = -1;
			else if ((pos > size - 2) && !bStairs)
				pos = size-2;
			else if (pos > size - 1)
				pos = size - 1;

			if (bUpdateIndex || (pos < 0))
			{
				ITI_real prev, next;
				if(pos < 0)
					pos = 0;
				if (pos > size - 2)
					pos = size - 2;

				prev = GetValAt(pCurve, axis, pos);
				next = GetValAt(pCurve, axis, pos + 1);

				if (prev > val)
				{
					for (pos--; pos >= 0; pos--)
					{
						next = prev;
						prev = GetValAt(pCurve, axis, pos);
						if (prev <= val && val < next)
							break;
					}
					if (pos < 0)
						pos = 0;
				}
				else if (val >= next)
				{
					for (pos++; pos <= size - 2; pos++)
					{
						prev = next;
						next = GetValAt(pCurve, axis, pos+1);
						if (prev <= val && val < next)
							break;
					}
					if (pos > size - 2)
						pos = size - 2;
					if (bStairs && val >= GetValAt(pCurve, axis, size - 1))
						pos = size - 1;
				}
			}
			pSeqCs->iPos = pos;
		}
	}

	return pos;
}

static void LookupValue(ITI_real x, enum Axis axis, ITI_CurveData_ND* pCurve,
							ITI_SeqCallState* pSeqCs, CalcInfo* pCi,
											ITI_ushort bUpdateIndex)
{
	if (pCurve && pSeqCs && pCi){
		ITI_real realMax = GetRealMax(pCurve, axis);

		if (GetSize(pCurve, axis) == 1){
			pCi->index = 0;
			pCi->index1 = 0;
			pCi->bExtrapol = ITI_false;
		}
		else {
			if (!pCi->bExtrapol)
				pCi->index = FindValue(x, axis, 0, pCurve, pSeqCs, (ITI_ushort)(pCi->interpol == InterpolStairs), bUpdateIndex);
			else if (x > realMax) {
				if(pCi->interpol == InterpolStairs)
					pCi->index = GetSize(pCurve, axis)-1;
				else
					pCi->index = GetSize(pCurve, axis)-2;
			}
			else
				pCi->index = 0;

			if(pCi->index<=GetSize(pCurve, axis)-2)
				pCi->index1=pCi->index + 1;
			else
				pCi->index1=pCi->index;
		}
	}
}

static ITI_real CalcValue(ITI_real x, ITI_real* Y, ITI_CurveData_ND* pCurve,
				   ITI_CurveCallState* pCs, CalcInfo* pCi, ITI_int idx_offset,
				   ITI_int yIndex, ITI_int zIndex, enum Axis axis)
{
	ITI_real y = 0.0;

	if (Y && pCurve && pCi){
		if (!pCi->bExtrapol){
			ITI_int idx = pCi->index;

			if (idx > -1){
				y = Y[idx + idx_offset];
				if (idx != pCi->index1 || ApproxUsed(pCi)){
					if (GetValAt(pCurve, axis, idx) != x || ApproxUsed(pCi)){
						


						CurveData data;
						InitCurveData(pCurve, &data, axis, yIndex, zIndex,
														pCurve->pYScale);

						switch (pCi->interpol){
							case InterpolNone:
							case InterpolStairs :
								break;
							case InterpolSpline :
								y = GetSplineValue(x, idx, pCurve->pX,
									pCurve->pVal+pCurve->sizeX*(yIndex+pCurve->sizeY*zIndex),
									pCurve->pYCoeff[yIndex+pCurve->sizeY*zIndex], pCi->bCycle, 0, 0);
								break;
							case InterpolHyperbolicApprox :
								{
									ITI_int i = idx + idx_offset;
									ITI_real xi = GetValAt(pCurve,
												axis, i);
									ITI_real xi_1 = GetValAt(pCurve,
												axis, i+1);
									if (xi_1 - x < x - xi){
										i++;
										xi = xi_1;
										y = Y[i];
									}
									y += GetHyperbolicApproxValue(&data, x, i, xi);
									break;
								}
							case InterpolCircualArcApprox :
								{
									ITI_int i = idx + idx_offset;
									ITI_real xi = GetValAt(pCurve,
												axis, i);
									ITI_real xi_1 = GetValAt(pCurve,
												axis, i+1);
									if (xi_1 - x < x - xi){
										i++;
										xi = xi_1;
										y = Y[i];
									}
									y += GetArcApproxValue(&data, x, i, xi);
									break;
								}
							case InterpolQuadraticApprox :
								{
									ITI_int i = idx + idx_offset;
									ITI_real xi = GetValAt(pCurve,
												axis, i);
									ITI_real xi_1 = GetValAt(pCurve,
												axis, i+1);
									if (xi_1 - x < x - xi){
										i++;
										xi = xi_1;
										y = Y[i];
									}
									y += GetQuadraticApproxValue(&data, x, i, xi);
									break;
								}
							case InterpolLinear :
								y += (x - GetValAt(pCurve, axis, idx)) *
									(Y[idx+1+idx_offset] - Y[idx+idx_offset]) /
									(GetValAt(pCurve, axis, idx+1)-
									GetValAt(pCurve, axis, idx));
						}
					}
				}

				if (pCi->bMirror)
					y = Y[0] - (y - Y[0]);
			}
		}
		else {
			ITI_int idx = pCi->index;
			ITI_real x1 = 0.;
			ITI_real x2 = 0.;
			ITI_real y1 = Y[idx+idx_offset];
			ITI_real y2 = (idx == GetSize(pCurve, axis) - 1) ? y1 : Y[idx+1+idx_offset];
			ITI_ushort bUse_x2 = 0;
			ITI_real anstieg = 0.0;
			ITI_real realMax = GetRealMax(pCurve, axis);

			if (x > realMax){
				ITI_int size = GetSize(pCurve, axis);
				x1 = GetValAt(pCurve, axis, size-2);
				x2 = GetValAt(pCurve, axis, size-1);
				bUse_x2 = 1;
			}
			else {
				x1 = GetValAt(pCurve, axis, 0);
				x2 = GetValAt(pCurve, axis, 1);
			}

			switch (pCi->interpol){
				case InterpolStairs :
					anstieg = 0.0;
					break;
				case InterpolSpline :
					anstieg = GetDSplineValue(bUse_x2?x2:x1, idx, pCurve->pX,
									pCurve->pVal+pCurve->sizeX*(yIndex+pCurve->sizeY*zIndex),
									pCurve->pYCoeff[yIndex+pCurve->sizeY*zIndex], pCi->bCycle, 0, 0);
					break;
				default :
					{
						ITI_real dx = x2 - x1;
						if (fabs(dx) < dbl_epsilon(x1,x2))
								dx = _copysign(dbl_epsilon(x1,x2), dx);
						anstieg = (y2 - y1)/dx;
					}
			}

			y = (x-(bUse_x2?x2:x1)) * anstieg;
			y += (bUse_x2?y2:y1);

			if (pCi->bMirror)
				y = Y[0] - (y - Y[0]);
		}
	}

	return y;
}

static void CalcZF(ITI_real x, ITI_real* zf, ITI_CurveData_ND* pCurve,
										CalcInfo* pCi, enum Axis axis)
{
	if (pCurve && pCi){
		if (ApproxUsed(pCi)){
			*zf = 1.0;
		}
		else if (pCi->index == pCi->index1){
			*zf = 1.0;
		}
		else if (pCi->interpol == InterpolSpline){
			*zf = 1.0;
		}
		else {
			if (pCi->bExtrapol){
				ITI_real realMin = GetRealMin(pCurve, axis);
				ITI_real realMax = GetRealMax(pCurve, axis);

				if (x > realMax){
					*zf = x - realMax;
					if (GetSize(pCurve, axis)%2 == 1)
						*zf = -*zf;
				}
				else {
					*zf = x - realMin;
				}
			}
			else {
				*zf = (GetValAt(pCurve, AxisX, pCi->index+1)-x)*
						(x-GetValAt(pCurve, AxisX, pCi->index));
				if (pCi->index%2)
					*zf = -*zf;
			}
		}

		if (pCi->bMirror)
			*zf = -*zf;
	}
}

static ITI_real CalcYCurve1D(ITI_real x, ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs,
										ITI_real* zf, ITI_SolverInfo* pSInfo)
{
	ITI_real y = 0.;

	if (pCurve && pCurve->sizeX > 0){
		if (pCurve->sizeX == 1){
			y = pCurve->pVal[0];
		}
		else {
			CalcInfo ci;
			ITI_ushort bUpdateIndex;

			InitCalcInfo(pCurve, &ci, AxisX);
			x = AdjustLookupValue(x, pCurve, &ci, AxisX);
			bUpdateIndex = (ci.interpol!=InterpolStairs||!zf||pSInfo->isEvent)?1:0;
			LookupValue(x, AxisX, pCurve, pCs->pSeqCs, &ci, bUpdateIndex);
			y = CalcValue(x, pCurve->pVal, pCurve, pCs, &ci, 0, 0, 0, AxisX);

			if (zf)
				CalcZF(x, zf, pCurve, &ci, AxisX);
		}
	}

	return y;
} 

static ITI_real CalcZCurve2D(ITI_real x, ITI_real y, ITI_CurveData_ND* pCurve,
				ITI_CurveCallState* pCs, ITI_real* zf, ITI_SolverInfo* pSInfo)
{
	ITI_real z = 0.;

	if (pCurve && pCurve->sizeY > 0){
		if (pCurve->sizeY == 1){
			z = CalcYCurve1D(x, pCurve, pCs, zf, pSInfo);
		}
		else {
			CalcInfo ci_x;
			CalcInfo ci_y;
			ITI_real z_i[3];
			ITI_ushort bUpdateIndex;

			InitCalcInfo(pCurve, &ci_x, AxisX);
			x = AdjustLookupValue(x, pCurve, &ci_x, AxisX);
			bUpdateIndex = (ci_x.interpol!=InterpolStairs||!zf||pSInfo->isEvent)?1:0;
			LookupValue(x, AxisX, pCurve, pCs->pSeqCs, &ci_x,
												bUpdateIndex);
			if (zf)
				CalcZF(x, zf, pCurve, &ci_x, AxisX);

			InitCalcInfo(pCurve, &ci_y, AxisY);
			if (ci_y.interpol == InterpolSpline)
				ci_y.interpol = InterpolLinear;

			y = AdjustLookupValue(y, pCurve, &ci_y, AxisY);
			bUpdateIndex = (ci_y.interpol!=InterpolStairs||!zf||pSInfo->isEvent)?1:0;
			LookupValue(y, AxisY, pCurve, (pCs->pSeqCs+1), &ci_y,
													bUpdateIndex);

			if (zf)
				CalcZF(y, zf+1, pCurve, &ci_y, AxisY);

			z_i[0] = ci_y.bMirror?CalcValue(x, pCurve->pVal, pCurve,
										pCs, &ci_x, 0, 0, 0, AxisX):0.0;
			z_i[1] = CalcValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index,
								pCurve, pCs, &ci_x, 0, ci_y.index, 0, AxisX);
			z_i[2] = CalcValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index1,
								pCurve, pCs, &ci_x, 0, ci_y.index1, 0, AxisX);
			z = CalcValue(y, z_i, pCurve, pCs, &ci_y, -ci_y.index+1,
													ci_y.index, 0, AxisY);
		}
	}

	return z;
}

ITI_real GetZFromCurve2D(ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs,
				ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real y)
{
	return CalcZCurve2D(x, y, pCurve, pCs, zf, pSInfo);
}

 

static ITI_real CalcDValue(ITI_real x, ITI_real* Y, ITI_CurveData_ND* pCurve,
				   ITI_CurveCallState* pCs, CalcInfo* pCi, ITI_int idx_offset,
				   ITI_int yIndex, ITI_int zIndex, enum Axis axis)
{
	ITI_real dy = 0.0;

	if (Y && pCurve && pCs && pCi){
		ITI_int idx = pCi->index;
		ITI_int i = idx + idx_offset;

		if (!pCi->bExtrapol){
			if (idx >= 0){


						CurveData data;
						InitCurveData(pCurve, &data, axis, yIndex, zIndex,
														pCurve->pYScale);

						switch (pCi->interpol){
							case InterpolNone :
							case InterpolStairs :
							case InterpolQuadraticApprox :
								break;
							case InterpolLinear :
								{
									ITI_real x1 = GetValAt(pCurve, axis, idx);
									ITI_real x2 = GetValAt(pCurve, axis, idx+1);
									ITI_real dx = x2 - x1;
									if (fabs(dx) < dbl_epsilon(x1,x2))
										dx = _copysign(dbl_epsilon(x1,x2), dx);
									dy = (Y[i+1] - Y[i]) / dx;
								}
								break;
							case InterpolSpline :
								dy = GetDSplineValue(x, idx, pCurve->pX,
									pCurve->pVal+pCurve->sizeX*yIndex,
									pCurve->pYCoeff[yIndex], pCi->bCycle, 0, 0);
								break;
							case InterpolHyperbolicApprox :
								{
									ITI_real xi = GetValAt(pCurve, axis, i);
									ITI_real xi_1 = GetValAt(pCurve, axis, i+1);
									if (xi_1 - x < x -xi){
										i++;
										xi = xi_1;
									}
									dy = GetDerHyperbolicApproxValue(&data, x, i, xi);
								}
								break;
							case InterpolCircualArcApprox :
								{
									ITI_real xi = GetValAt(pCurve, axis, i);
									ITI_real xi_1 = GetValAt(pCurve, axis, i+1);
									if (xi_1 - x < x -xi){
										i++;
										xi = xi_1;
									}
									dy = GetDerArcApproxValue(&data, x, i, xi);
								}
								break;
						}
					 
				 

				if (pCi->bMirror)
					dy = -dy;
			}
		}
		else {
			ITI_real x1 = 0.0;
			ITI_real x2 = 0.0;
			ITI_real y1 = Y[i];
			ITI_real y2 = (idx == GetSize(pCurve, axis) - 1) ? y1 : Y[i+1];
			ITI_ushort bUse_x2 = 0;
			ITI_real realMax = GetRealMax(pCurve, axis);

			if (x > realMax){
				ITI_int size = GetSize(pCurve, axis);
				x1 = GetValAt(pCurve, axis, size-2);
				x2 = GetValAt(pCurve, axis, size-1);
				bUse_x2 = 1;
			}
			else {
				x1 = GetValAt(pCurve, axis, 0);
				x2 = GetValAt(pCurve, axis, 1);
			}

			switch (pCi->interpol){
				case InterpolStairs :
					dy = 0.0;
					break;
				case InterpolSpline :
					dy = GetDSplineValue(bUse_x2?x2:x1, idx, pCurve->pX,
									pCurve->pVal+pCurve->sizeX*yIndex,
									pCurve->pYCoeff[yIndex], pCi->bCycle, 0, 0);
					break;
				default :
					{
						ITI_real dx = x2 - x1;
						if (fabs(dx) < dbl_epsilon(x1,x2))
							dx = _copysign(dbl_epsilon(x1,x2), dx);
						dy = (y2 - y1)/dx;
					}
					break;
			}
			if (pCi->bMirror)
				dy = -dy;
		}
	}

	return dy;
}

static ITI_real CalcZDerCurve2D(ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs,
				ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real y,
				ITI_ushort bXdot, ITI_ushort bYdot)
{
	ITI_real z = 0.0;

	if (pCurve && pCs && pSInfo){
		 
			CalcInfo ci_x;
			CalcInfo ci_y;
			ITI_ushort bUpdateIndex;

			InitCalcInfo(pCurve, &ci_x, AxisX);
			x = AdjustLookupValue(x, pCurve, &ci_x, AxisX);
			bUpdateIndex = (ci_x.interpol!=InterpolStairs||!zf||pSInfo->isEvent)?1:0;
			LookupValue(x, AxisX, pCurve, pCs->pSeqCs, &ci_x,
												bUpdateIndex);

			if (zf)
				CalcZF(x, zf, pCurve, &ci_x, AxisX);

			InitCalcInfo(pCurve, &ci_y, AxisY);
			if (ci_y.interpol == InterpolSpline)
				ci_y.interpol = InterpolLinear;

			y = AdjustLookupValue(y, pCurve, &ci_y, AxisY);
			bUpdateIndex = (ci_y.interpol!=InterpolStairs||!zf||pSInfo->isEvent)?1:0;
			LookupValue(y, AxisY, pCurve, (pCs->pSeqCs+1), &ci_y,
												bUpdateIndex);

			if (zf)
				CalcZF(y, zf+1, pCurve, &ci_y, AxisY);

			if (bXdot){
				ITI_real z_i[3];

				z_i[0] = 0.0;
				z_i[1] = CalcDValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index,
								pCurve, pCs, &ci_x, 0, ci_y.index, 0, AxisX);
				z_i[2] = CalcDValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index1,
								pCurve, pCs, &ci_x, 0, ci_y.index1, 0, AxisX);
				z = CalcValue(y, z_i, pCurve, pCs, &ci_y, -ci_y.index+1,
													ci_y.index, 0, AxisY);
			}
			else if (bYdot){
				if (ci_y.interpol != InterpolStairs)
				{
					ITI_real z_i = 0.0;
					ITI_real z_i1 = 0.0;
					z_i = CalcValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index,
									pCurve, pCs, &ci_x, 0, ci_y.index, 0, AxisX);
					z_i1 = CalcValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index1,
									pCurve, pCs, &ci_x, 0, ci_y.index1, 0, AxisX);

					 
					z = (z_i1 - z_i) / (GetValAt(pCurve, AxisY, ci_y.index1) - GetValAt(pCurve, AxisY, ci_y.index));
				}
				else
				{
					z = 0.0;
				}
			}
		 
	}

	return z;
} 

ITI_real GetZFromDerCurve2D(ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs,
				ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real y,
				ITI_real xdot, ITI_real ydot)
{
	ITI_real z = 0.0;

	if (pCurve && pCs && pSInfo){
		if (xdot){
			z = xdot * CalcZDerCurve2D(pCurve, pCs, pSInfo, zf, x, y, 1, 0);
		}

		if (ydot){
			z = z + ydot * CalcZDerCurve2D(pCurve, pCs, pSInfo, zf, x, y, 0, 1);
		}
	}

	return z;
} 

 

static ITI_real CalcD2Value(ITI_real x, ITI_real* Y, ITI_CurveData_ND* pCurve,
				   ITI_CurveCallState* pCs, CalcInfo* pCi, ITI_int idx_offset,
				   ITI_int yIndex, ITI_int zIndex, enum Axis axis)
{
	ITI_real dy = 0.0;

	if (Y && pCurve && pCs && pCi){
		ITI_int idx = pCi->index;
		ITI_int i = idx + idx_offset;

		if (!pCi->bExtrapol){
			if (idx >= 0){
				CurveData data;
				InitCurveData(pCurve, &data, axis, yIndex, zIndex,
													pCurve->pYScale);

				switch (pCi->interpol){
					case InterpolNone :
					case InterpolStairs :
					case InterpolLinear :
					case InterpolQuadraticApprox :
						break;
					case InterpolSpline :
						dy = GetD2SplineValue(x, idx, pCurve->pX,
									pCurve->pVal+pCurve->sizeX*yIndex,
									pCurve->pYCoeff[yIndex], pCi->bCycle);
						break;
					case InterpolHyperbolicApprox :
						{
							ITI_real xi = GetValAt(pCurve, axis, i);
							ITI_real xi_1 = GetValAt(pCurve, axis, i+1);
							if (xi_1 - x < x -xi){
								i++;
								xi = xi_1;
							}
							dy = GetDer2HyperbolicApproxValue(&data, x, i, xi);
						}
						break;
					case InterpolCircualArcApprox :
						{
							ITI_real xi = GetValAt(pCurve, axis, i);
							ITI_real xi_1 = GetValAt(pCurve, axis, i+1);
							if (xi_1 - x < x -xi){
								i++;
								xi = xi_1;
							}
							dy = GetDer2ArcApproxValue(&data, x, i, xi);
						}
						break;
				}

				if (pCi->bMirror)
					dy = -dy;
			}
		}
		else {
			dy = 0.0;
		}
	}
	return dy;
}

static ITI_real CalcZDer2Curve2D(ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs,
				ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real y,
				ITI_ushort bXdot, ITI_ushort bYdot)
{
	ITI_real z = 0.0;

	if (pCurve && pCs && pSInfo){
		if (pCurve->sizeY > 1){
			CalcInfo ci_x;
			CalcInfo ci_y;

			InitCalcInfo(pCurve, &ci_x, AxisX);
			if (ci_x.interpol != InterpolStairs &&
								ci_x.interpol != InterpolLinear){
				ITI_ushort bUpdateIndex;
				x = AdjustLookupValue(x, pCurve, &ci_x, AxisX);
				LookupValue(x, AxisX, pCurve, pCs->pSeqCs, &ci_x, 1);

				if (zf)
					CalcZF(x, zf, pCurve, &ci_x, AxisX);

				InitCalcInfo(pCurve, &ci_y, AxisY);
				if (ci_y.interpol == InterpolSpline)
					ci_y.interpol = InterpolLinear;

				y = AdjustLookupValue(y, pCurve, &ci_y, AxisY);
				bUpdateIndex = (ci_y.interpol!=InterpolStairs||!zf||pSInfo->isEvent)?1:0;
				LookupValue(y, AxisY, pCurve, (pCs->pSeqCs+1), &ci_y,
												bUpdateIndex);

				if (zf)
					CalcZF(y, zf+1, pCurve, &ci_y, AxisY);

				if (bXdot && bYdot){
					ITI_real z_i = 0.0;
					ITI_real z_i1 = 0.0;

					z_i = CalcDValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index,
								pCurve, pCs, &ci_x, 0, ci_y.index, 0, AxisX);
					z_i1 = CalcDValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index1,
								pCurve, pCs, &ci_x, 0, ci_y.index1, 0, AxisX);
					 
					z = (z_i1 - z_i) / (GetValAt(pCurve, AxisY, ci_y.index1) -
										GetValAt(pCurve, AxisY, ci_y.index));
				}
				else if (bXdot){
					ITI_real z_i[3];

					z_i[0] = 0.0;
					z_i[1] = CalcD2Value(x, pCurve->pVal+pCurve->sizeX*ci_y.index,
									pCurve, pCs, &ci_x, 0, ci_y.index, 0, AxisX);
					z_i[2] = CalcD2Value(x, pCurve->pVal+pCurve->sizeX*ci_y.index1,
									pCurve, pCs, &ci_x, 0, ci_y.index1, 0, AxisX);
					z = CalcValue(y, z_i, pCurve, pCs, &ci_y, -ci_y.index+1,
														ci_y.index, 0, AxisY);
				}
				else  
					z = 0.0;
			}
		}
	}
	return z;
}

ITI_real GetZFromDer2Curve2D(ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs,
				 ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real y,
				 ITI_real xdot, ITI_real ydot, ITI_real xdot2, ITI_real ydot2)
{
	ITI_real z = 0.0;

	if (pCurve && pCs && pSInfo){
		if (xdot2)
			z = xdot2*CalcZDerCurve2D(pCurve, pCs, pSInfo, zf, x, y, 1, 0);
		if (xdot)
			z = z + xdot*CalcZDer2Curve2D(pCurve, pCs, pSInfo, zf, x, y, 1, 0);
		if (xdot && ydot)
			z = z + 2*xdot*ydot*CalcZDer2Curve2D(
										pCurve, pCs, pSInfo, zf, x, y, 1, 1);
		if (ydot2)
			z = z + ydot2*CalcZDerCurve2D(pCurve, pCs, pSInfo, zf, x, y, 1, 0);
	} 

	return z;
} 

 

ITI_real GetUFromCurve3D(ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs,
		ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real y, ITI_real z)
{
	ITI_real u = 0.0;

	if (pCurve && pCurve->sizeZ > 0){
		if (pCurve->sizeZ == 1){
			u = CalcZCurve2D(x, y, pCurve, pCs, zf, pSInfo);
		} 
		else {
			CalcInfo ci_x;
			CalcInfo ci_y;
			CalcInfo ci_z;
			ITI_real u_i[3];
			ITI_real z_i1[3];
			ITI_real z_i2[3];
			ITI_real u_mirror = 0.0;
			ITI_bool bUpdateIndex;

			InitCalcInfo(pCurve, &ci_x, AxisX);
			x = AdjustLookupValue(x, pCurve, &ci_x, AxisX);
			bUpdateIndex = (ci_x.interpol!=InterpolStairs||!zf||pSInfo->isEvent) ? ITI_true : ITI_false;
			LookupValue(x, AxisX, pCurve, pCs->pSeqCs, &ci_x, bUpdateIndex);

			if (zf)
				CalcZF(x, zf, pCurve, &ci_x, AxisX);

			InitCalcInfo(pCurve, &ci_y, AxisY);
			if (ci_y.interpol == InterpolSpline)
				ci_y.interpol = InterpolLinear;

			y = AdjustLookupValue(y, pCurve, &ci_y, AxisY);
			bUpdateIndex = (ci_y.interpol!=InterpolStairs||!zf||pSInfo->isEvent) ? ITI_true : ITI_false;
			LookupValue(y, AxisY, pCurve, (pCs->pSeqCs+1), &ci_y, bUpdateIndex);

			if (zf)
				CalcZF(y, zf+1, pCurve, &ci_y, AxisY);

			InitCalcInfo(pCurve, &ci_z, AxisZ);
			if (ci_z.interpol == InterpolSpline)
				ci_z.interpol = InterpolLinear;

			z = AdjustLookupValue(z, pCurve, &ci_z, AxisZ);
			bUpdateIndex = (ci_z.interpol!=InterpolStairs||!zf||pSInfo->isEvent) ? ITI_true : ITI_false;
			LookupValue(z, AxisZ, pCurve, (pCs->pSeqCs+2), &ci_z, bUpdateIndex);

			if (zf)
				CalcZF(z, zf+2, pCurve, &ci_z, AxisZ);

			z_i1[0] = (ci_y.bMirror||ci_z.bMirror)?CalcValue(
				x, pCurve->pVal+pCurve->sizeX*pCurve->sizeY*ci_z.index,
				pCurve, pCs, &ci_x, 0, 0, ci_z.index, AxisX):0.0;
			z_i1[1] = CalcValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index+
				pCurve->sizeX*pCurve->sizeY*ci_z.index, pCurve, pCs, &ci_x,
				0, ci_y.index, ci_z.index, AxisX);
			z_i1[2] = CalcValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index1+
				pCurve->sizeX*pCurve->sizeY*ci_z.index, pCurve, pCs, &ci_x,
				0, ci_y.index1, ci_z.index, AxisX);

			z_i2[0] = (ci_y.bMirror||ci_z.bMirror)?CalcValue(
				x, pCurve->pVal+pCurve->sizeX*pCurve->sizeY*ci_z.index1,
				pCurve, pCs, &ci_x, 0, 0, ci_z.index1, AxisX):0.0;
			z_i2[1] = CalcValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index+
				pCurve->sizeX*pCurve->sizeY*ci_z.index1, pCurve, pCs, &ci_x,

				0, ci_y.index, ci_z.index1, AxisX);
			z_i2[2] = CalcValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index1+
				pCurve->sizeX*pCurve->sizeY*ci_z.index1, pCurve, pCs, &ci_x,
				0, ci_y.index1, ci_z.index1, AxisX);

			if (ci_z.bMirror){
				CalcInfo ci_zm;
				ITI_real z_im[3];
				InitCalcInfo(pCurve, &ci_zm, AxisZ);
				ci_zm.bMirror = ITI_false;
				z_im[0] = 0.0;
				z_im[1] = z_i1[0];
				z_im[2] = z_i2[0];

				u_mirror = CalcValue(y, z_im, pCurve, pCs, &ci_zm,
									-ci_y.index+1, 0, 0, AxisY);
			} 

			u_i[0] = u_mirror;
			u_i[1] = CalcValue(y, z_i1, pCurve, pCs, &ci_y,
								-ci_y.index+1, 0, 0, AxisY);
			u_i[2] = CalcValue(y, z_i2, pCurve, pCs, &ci_y,
								-ci_y.index+1, 0, 0, AxisY);

			u = CalcValue(z, u_i, pCurve, pCs, &ci_z, -ci_z.index+1, 0, 0, AxisZ);
		} 
	} 

	return u;
} 

 

static ITI_real CalcUDerCurve3D(ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs,
		ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real y,
		ITI_real z, ITI_ushort bXdot, ITI_ushort bYdot, ITI_ushort bZdot)
{
	ITI_real u = 0.0;

	if (!(bXdot && bYdot) && !(bXdot && bZdot) && !(bYdot && bZdot)){
		if (pCurve && pCs && pSInfo){
			 
				CalcInfo ci_x;
				CalcInfo ci_y;
				CalcInfo ci_z;
				ITI_ushort bUpdateIndex;

				InitCalcInfo(pCurve, &ci_x, AxisX);
				x = AdjustLookupValue(x, pCurve, &ci_x, AxisX);
				bUpdateIndex = (ci_x.interpol!=InterpolStairs||!zf||pSInfo->isEvent)?1:0;
				LookupValue(x, AxisX, pCurve, pCs->pSeqCs, &ci_x,
													bUpdateIndex);

				if (zf)
					CalcZF(x, zf, pCurve, &ci_x, AxisX);

				InitCalcInfo(pCurve, &ci_y, AxisY);
				if (ci_y.interpol == InterpolSpline)
					ci_y.interpol = InterpolLinear;

				y = AdjustLookupValue(y, pCurve, &ci_y, AxisY);
				bUpdateIndex = (ci_y.interpol!=InterpolStairs||!zf||pSInfo->isEvent)?1:0;
				LookupValue(y, AxisY, pCurve, (pCs->pSeqCs+1), &ci_y,
													bUpdateIndex);

				if (zf)
					CalcZF(y, zf+1, pCurve, &ci_y, AxisY);

				InitCalcInfo(pCurve, &ci_z, AxisZ);
				if (ci_z.interpol == InterpolSpline)
					ci_z.interpol = InterpolLinear;

				z = AdjustLookupValue(z, pCurve, &ci_z, AxisZ);
				bUpdateIndex = (ci_z.interpol!=InterpolStairs||!zf||pSInfo->isEvent)?1:0;
				LookupValue(z, AxisZ, pCurve, (pCs->pSeqCs+2), &ci_z,
													bUpdateIndex);

				if (zf)
					CalcZF(z, zf+2, pCurve, &ci_z, AxisZ);

				if (bXdot){
					ITI_real z_i1[3];
					ITI_real z_i2[3];
					ITI_real u_i[3];

					z_i1[0] = 0.0;
					z_i1[1] = CalcDValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index+
							pCurve->sizeX*pCurve->sizeY*ci_z.index, pCurve, pCs, &ci_x,
							0, ci_y.index, ci_z.index, AxisX);
					z_i1[2] =  CalcDValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index1+
							pCurve->sizeX*pCurve->sizeY*ci_z.index, pCurve, pCs, &ci_x,
							0, ci_y.index1, ci_z.index, AxisX);

					z_i2[0] = 0.0;
					z_i2[1] = CalcDValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index+
							pCurve->sizeX*pCurve->sizeY*ci_z.index1, pCurve, pCs, &ci_x,
							0, ci_y.index, ci_z.index1, AxisX);
					z_i2[2] =  CalcDValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index1+
							pCurve->sizeX*pCurve->sizeY*ci_z.index1, pCurve, pCs, &ci_x,
							0, ci_y.index1, ci_z.index1, AxisX);

					u_i[0] = 0.0;
					u_i[1] = CalcValue(y, z_i1, pCurve, pCs, &ci_y,
									-ci_y.index+1, 0, 0, AxisY);
					u_i[2] = CalcValue(y, z_i2, pCurve, pCs, &ci_y,
									-ci_y.index+1, 0, 0, AxisY);

					u = CalcValue(z, u_i, pCurve, pCs, &ci_z,
									-ci_z.index+1, 0, 0, AxisZ);
				} 
				else if (bYdot){
					if (ci_y.interpol != InterpolStairs)
					{
						ITI_real z_i1[2];
						ITI_real z_i2[2];
						ITI_real u_i[3];

						z_i1[0] = CalcValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index+
								pCurve->sizeX*pCurve->sizeY*ci_z.index, pCurve, pCs, &ci_x,
								0, ci_y.index, ci_z.index, AxisX);
						z_i1[1] = CalcValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index1+
								pCurve->sizeX*pCurve->sizeY*ci_z.index, pCurve, pCs, &ci_x,
								0, ci_y.index1, ci_z.index, AxisX);

						z_i2[0] = CalcValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index+
								pCurve->sizeX*pCurve->sizeY*ci_z.index1, pCurve, pCs, &ci_x,
								0, ci_y.index, ci_z.index1, AxisX);
						z_i2[1] =  CalcValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index1+
								pCurve->sizeX*pCurve->sizeY*ci_z.index1, pCurve, pCs, &ci_x,
								0, ci_y.index1, ci_z.index1, AxisX);

						u_i[0] = 0.0;
						u_i[1] = (z_i1[1] - z_i1[0]) / (GetValAt(pCurve, AxisY, ci_y.index1)
													- GetValAt(pCurve, AxisY, ci_y.index));
						u_i[2] = (z_i2[1] - z_i2[0]) / (GetValAt(pCurve, AxisY, ci_y.index1)
													- GetValAt(pCurve, AxisY, ci_y.index));

						u = CalcValue(z, u_i, pCurve, pCs, &ci_z,
										-ci_z.index+1, 0, 0, AxisZ);
					}
					else
					{
						u = 0.0;
					}
				} 
				else {  
					if (ci_z.interpol != InterpolStairs)
					{
						ITI_real z_i1[3];
						ITI_real z_i2[3];
						ITI_real u_i = 0.0;
						ITI_real u_i1 = 0.0;

						z_i1[0] = (ci_y.bMirror||ci_z.bMirror)?CalcValue(
							x, pCurve->pVal+pCurve->sizeX*pCurve->sizeY*ci_z.index,
							pCurve, pCs, &ci_x, 0, 0, ci_z.index, AxisX):0.0;
						z_i1[1] = CalcValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index+
							pCurve->sizeX*pCurve->sizeY*ci_z.index, pCurve, pCs, &ci_x,
							0, ci_y.index, ci_z.index, AxisX);
						z_i1[2] = CalcValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index1+
							pCurve->sizeX*pCurve->sizeY*ci_z.index, pCurve, pCs, &ci_x,
							0, ci_y.index1, ci_z.index, AxisX);

						z_i2[0] = (ci_y.bMirror||ci_z.bMirror)?CalcValue(
							x, pCurve->pVal+pCurve->sizeX*pCurve->sizeY*ci_z.index1,
							pCurve, pCs, &ci_x, 0, 0, ci_z.index1, AxisX):0.0;
						z_i2[1] = CalcValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index+
							pCurve->sizeX*pCurve->sizeY*ci_z.index1, pCurve, pCs, &ci_x,
							0, ci_y.index, ci_z.index1, AxisX);
						z_i2[2] = CalcValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index1+
							pCurve->sizeX*pCurve->sizeY*ci_z.index1, pCurve, pCs, &ci_x,
							0, ci_y.index1, ci_z.index1, AxisX);

						u_i = CalcValue(y, z_i1, pCurve, pCs, &ci_y,
										-ci_y.index+1, 0, 0, AxisY);
						u_i1 = CalcValue(y, z_i2, pCurve, pCs, &ci_y,
										-ci_y.index+1, 0, 0, AxisY);

						u = (u_i1 - u_i) / (GetValAt(pCurve, AxisZ, ci_z.index1) -
											GetValAt(pCurve, AxisZ, ci_z.index));
					}
					else
					{
						u = 0.0;
					}
				} 
			 
		} 
	} 

	return u;
} 

ITI_real GetUFromDerCurve3D(ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs,
		ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real y, ITI_real z,
		ITI_real xdot, ITI_real ydot, ITI_real zdot)
{
	ITI_real u = 0.0;

	if (xdot)
		u = xdot * CalcUDerCurve3D(pCurve, pCs, pSInfo, zf, x, y, z, 1, 0, 0);
	if (ydot)
		u = u + ydot * CalcUDerCurve3D(pCurve, pCs, pSInfo, zf, x, y, z, 0, 1, 0);
	if (zdot)
		u = u + zdot * CalcUDerCurve3D(pCurve, pCs, pSInfo, zf, x, y, z, 0, 0, 1);

	return u;
} 

 

static ITI_real CalcUDer2Curve3D(ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs,
		ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real y,
		ITI_real z, ITI_ushort bXdot, ITI_ushort bYdot, ITI_ushort bZdot)
{
	ITI_real u = 0.0;

	if (pCurve && pCs && pSInfo){
		if (pCurve->sizeZ > 1 || (!bZdot && pCurve->sizeZ == 1)){
			CalcInfo ci_x;
			CalcInfo ci_y;
			CalcInfo ci_z;

			InitCalcInfo(pCurve, &ci_x, AxisX);

			if (ci_x.interpol != InterpolStairs &&
							ci_x.interpol != InterpolLinear){
				ITI_ushort bUpdateIndex;

				 
				x = AdjustLookupValue(x, pCurve, &ci_x, AxisX);
				LookupValue(x, AxisX, pCurve, pCs->pSeqCs, &ci_x, 1);

				if (zf)
					CalcZF(x, zf, pCurve, &ci_x, AxisX);

				 
				InitCalcInfo(pCurve, &ci_y, AxisY);
				if (ci_y.interpol == InterpolSpline)
					ci_y.interpol = InterpolLinear;

				y = AdjustLookupValue(y, pCurve, &ci_y, AxisY);
				bUpdateIndex = (ci_y.interpol!=InterpolStairs||!zf||pSInfo->isEvent)?1:0;
				LookupValue(y, AxisY, pCurve, (pCs->pSeqCs+1), &ci_y,
													bUpdateIndex);

				if (zf)
					CalcZF(y, zf+1, pCurve, &ci_y, AxisY);

				 
				InitCalcInfo(pCurve, &ci_z, AxisZ);
				if (ci_z.interpol == InterpolSpline)
					ci_z.interpol = InterpolLinear;

				z = AdjustLookupValue(z, pCurve, &ci_z, AxisZ);
				bUpdateIndex = (ci_z.interpol!=InterpolStairs||!zf||pSInfo->isEvent)?1:0;
				LookupValue(z, AxisZ, pCurve, (pCs->pSeqCs+2), &ci_z,
													bUpdateIndex);

				if (zf)
					CalcZF(z, zf+2, pCurve, &ci_z, AxisZ);

				if (bXdot && bYdot){
					ITI_real z_i1[2];
					ITI_real z_i2[2];
					ITI_real u_i[3];

					z_i1[0] = CalcDValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index+
							pCurve->sizeX*pCurve->sizeY*ci_z.index, pCurve, pCs, &ci_x,
							0, ci_y.index, ci_z.index, AxisX);
					z_i1[1] =  CalcDValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index1+
							pCurve->sizeX*pCurve->sizeX*ci_z.index, pCurve, pCs, &ci_x,
							0, ci_y.index1, ci_z.index, AxisX);

					z_i2[0] = CalcDValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index+
							pCurve->sizeX*pCurve->sizeY*ci_z.index1, pCurve, pCs, &ci_x,
							0, ci_y.index, ci_z.index1, AxisX);
					z_i2[1] =  CalcDValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index1+
							pCurve->sizeX*pCurve->sizeY*ci_z.index1, pCurve, pCs, &ci_x,
							0, ci_y.index1, ci_z.index1, AxisX);

					u_i[0] = 0.0;
					u_i[1] = (z_i1[1] - z_i1[0]) / (GetValAt(pCurve, AxisY, ci_y.index1)
												- GetValAt(pCurve, AxisY, ci_y.index));
					u_i[2] = (z_i2[1] - z_i2[0]) / (GetValAt(pCurve, AxisY, ci_y.index1)
												- GetValAt(pCurve, AxisY, ci_y.index));

					u = CalcValue(z, u_i, pCurve, pCs, &ci_z,
									-ci_z.index+1, 0, 0, AxisZ);
				} 
				else if (bXdot && bZdot){
					ITI_real z_i1[3];
					ITI_real z_i2[3];
					ITI_real u_i = 0.0;
					ITI_real u_i1 = 0.0;

					z_i1[0] = (ci_y.bMirror||ci_z.bMirror)?CalcDValue(
						x, pCurve->pVal+pCurve->sizeX*pCurve->sizeY*ci_z.index,
						pCurve, pCs, &ci_x, 0, 0, ci_z.index, AxisX):0.0;
					z_i1[1] = CalcDValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index+
						pCurve->sizeX*pCurve->sizeY*ci_z.index, pCurve, pCs, &ci_x,
						0, ci_y.index, ci_z.index, AxisX);
					z_i1[2] = CalcDValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index1+
						pCurve->sizeX*pCurve->sizeY*ci_z.index, pCurve, pCs, &ci_x,
						0, ci_y.index1, ci_z.index, AxisX);

					z_i2[0] = (ci_y.bMirror||ci_z.bMirror)?CalcDValue(
						x, pCurve->pVal+pCurve->sizeX*pCurve->sizeY*ci_z.index1,
						pCurve, pCs, &ci_x, 0, 0, ci_z.index1, AxisX):0.0;
					z_i2[1] = CalcDValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index+
						pCurve->sizeX*pCurve->sizeY*ci_z.index1, pCurve, pCs, &ci_x,
						0, ci_y.index, ci_z.index1, AxisX);
					z_i2[2] = CalcDValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index1+
						pCurve->sizeX*pCurve->sizeY*ci_z.index1, pCurve, pCs, &ci_x,
						0, ci_y.index1, ci_z.index1, AxisX);

					u_i = CalcValue(y, z_i1, pCurve, pCs, &ci_y,
									-ci_y.index+1, 0, 0, AxisY);
					u_i1 = CalcValue(y, z_i2, pCurve, pCs, &ci_y,
									-ci_y.index+1, 0, 0, AxisY);

					u = (u_i1 - u_i) / (GetValAt(pCurve, AxisZ, ci_z.index1) -
										GetValAt(pCurve, AxisZ, ci_z.index));
				} 
				else if (bYdot && bZdot){
					ITI_real z_i1[2];
					ITI_real z_i2[2];
					ITI_real u_i[3];

					z_i1[0] = CalcValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index+
							pCurve->sizeX*pCurve->sizeY*ci_z.index, pCurve, pCs, &ci_x,
							0, ci_y.index, ci_z.index, AxisX);
					z_i1[1] = CalcValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index1+
							pCurve->sizeX*pCurve->sizeY*ci_z.index, pCurve, pCs, &ci_x,
							0, ci_y.index1, ci_z.index, AxisX);

					z_i2[0] = CalcValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index+
							pCurve->sizeX*pCurve->sizeY*ci_z.index1, pCurve, pCs, &ci_x,
							0, ci_y.index, ci_z.index1, AxisX);
					z_i2[1] =  CalcValue(x, pCurve->pVal+pCurve->sizeX*ci_y.index1+
							pCurve->sizeX*pCurve->sizeY*ci_z.index1, pCurve, pCs, &ci_x,
							0, ci_y.index1, ci_z.index1, AxisX);

					u_i[0] = 0.0;
					u_i[1] = (z_i1[1] - z_i1[0]) / (GetValAt(pCurve, AxisY, ci_y.index1)
												- GetValAt(pCurve, AxisY, ci_y.index));
					u_i[2] = (z_i2[1] - z_i2[0]) / (GetValAt(pCurve, AxisY, ci_y.index1)
												- GetValAt(pCurve, AxisY, ci_y.index));

					u = (u_i[2] - u_i[1]) / (GetValAt(pCurve, AxisZ, ci_z.index1) -
										GetValAt(pCurve, AxisZ, ci_z.index));
				} 
				else if (bXdot){
					ITI_real z_i1[3];
					ITI_real z_i2[3];
					ITI_real u_i[3];

					z_i1[0] = 0.0;
					z_i1[1] = CalcD2Value(x, pCurve->pVal+pCurve->sizeX*ci_y.index+
							pCurve->sizeX*pCurve->sizeY*ci_z.index, pCurve, pCs, &ci_x,
							0, ci_y.index, ci_z.index, AxisX);
					z_i1[2] =  CalcD2Value(x, pCurve->pVal+pCurve->sizeX*ci_y.index1+
							pCurve->sizeX*pCurve->sizeY*ci_z.index, pCurve, pCs, &ci_x,
							0, ci_y.index1, ci_z.index, AxisX);

					z_i2[0] = 0.0;
					z_i2[1] = CalcD2Value(x, pCurve->pVal+pCurve->sizeX*ci_y.index+
							pCurve->sizeX*pCurve->sizeY*ci_z.index1, pCurve, pCs, &ci_x,
							0, ci_y.index, ci_z.index1, AxisX);
					z_i2[2] =  CalcD2Value(x, pCurve->pVal+pCurve->sizeX*ci_y.index1+
							pCurve->sizeX*pCurve->sizeY*ci_z.index1, pCurve, pCs, &ci_x,
							0, ci_y.index1, ci_z.index1, AxisX);

					u_i[0] = 0.0;
					u_i[1] = CalcValue(y, z_i1, pCurve, pCs, &ci_y,
									-ci_y.index+1, 0, 0, AxisY);
					u_i[2] = CalcValue(y, z_i2, pCurve, pCs, &ci_y,
									-ci_y.index+1, 0, 0, AxisY);

					u = CalcValue(z, u_i, pCurve, pCs, &ci_z,
									-ci_z.index+1, 0, 0, AxisZ);
				} 
				else {
					u = 0.0;
				} 
			} 
		} 
	} 

	return u;
} 

ITI_real GetUFromDer2Curve3D(ITI_CurveData_ND* pCurve, ITI_CurveCallState* pCs,
		ITI_SolverInfo* pSInfo, ITI_real* zf, ITI_real x, ITI_real y, ITI_real z,
		ITI_real xdot, ITI_real ydot, ITI_real zdot, ITI_real xdot2,
		ITI_real ydot2, ITI_real zdot2)
{
	ITI_real u = 0.0;

	if (xdot2)
		u = xdot2*CalcUDerCurve3D(pCurve, pCs, pSInfo, zf, x, y, z, 1, 0, 0);
	if (ydot2)
		u = u + ydot2*CalcUDerCurve3D(pCurve, pCs, pSInfo, zf, x, y, z, 0, 1, 0);
	if (zdot2)
		u = u + zdot2*CalcUDerCurve3D(pCurve, pCs, pSInfo, zf, x, y, z, 0, 0, 1);
	if (xdot)
		u = u + xdot*xdot*CalcUDer2Curve3D(
									pCurve, pCs, pSInfo, zf, x, y, z, 1, 0, 0);
	if (xdot && ydot)
		u = u + 2*xdot*ydot*CalcUDer2Curve3D(
									pCurve, pCs, pSInfo, zf, x, y, z, 1, 1, 0);
	if (xdot && zdot)
		u = u + 2*xdot*zdot*CalcUDer2Curve3D(
									pCurve, pCs, pSInfo, zf, x, y, z, 1, 0, 1);
	if (ydot && zdot)
		u = u + 2*ydot*zdot*CalcUDer2Curve3D(
									pCurve, pCs, pSInfo, zf, x, y, z, 0, 1, 1);

	return u;
} 

 

static ITI_int GetNextDelayIndex(ITI_DelayBuffer* pBuffer, ITI_int lowIndex)
{
	if((lowIndex+1) < pBuffer->size)
		return lowIndex+1;
	return 0;
}

static void UpdateEventIndeces(ITI_DelayBuffer* pBuffer)
{
	if(pBuffer->lastPosOut<0)
		return;

	if(pBuffer->valType==DelayValueType_Real)
	{
		ITI_int found = 0;
		ITI_int iStop;
		ITI_int i = 0;
		 
		if(pBuffer->lastPosIn > pBuffer->lastPosOut)
		{
			if((pBuffer->iR> 0) && ((pBuffer->iR > pBuffer->lastPosOut) && (pBuffer->iR < pBuffer->lastPosIn)))
				iStop = pBuffer->iR;
			else
				iStop = pBuffer->lastPosIn-1;
			if(iStop == pBuffer->size)
				iStop--;
			for (i=pBuffer->lastPosOut; i < iStop; i++)
			{
				if(pBuffer->times[i] == pBuffer->times[i+1])
				{
					pBuffer->iR = i;
					break;
				}
			}
		}
		else
		{
			if((pBuffer->iR> 0) && ((pBuffer->iR > pBuffer->lastPosOut)))
			{
				iStop = pBuffer->iR;
				found = 1;
			}
			else
				iStop = pBuffer->size;
			if(iStop == pBuffer->size)
				iStop--;
			for (i=pBuffer->lastPosOut; i < iStop; i++)
			{
				if(pBuffer->times[i] == pBuffer->times[i+1])
				{
					pBuffer->iR = i;
					found = 1;
					break;
				}
			}
			if(found == 0)
			{
				if((pBuffer->iR> 0) && ((pBuffer->iR < pBuffer->lastPosIn)))
				{
					iStop = pBuffer->iR;
					found = 1;
				}
				else
					iStop = pBuffer->lastPosIn-1;
				if(iStop == pBuffer->size)
					iStop--;
				for (i=0; i < iStop; i++)
				{
					if(pBuffer->times[i] == pBuffer->times[i+1])
					{
						pBuffer->iR = i;
						found = 1;
						break;
					}
				}
			}
		}
		 
		if(pBuffer->lastPosIn > pBuffer->lastPosOut)
		{
			if((pBuffer->iL> 0) && ((pBuffer->iL < pBuffer->lastPosOut) && (pBuffer->iL > pBuffer->lastPosIn)))
				iStop = pBuffer->iL;
			else
				iStop = 1;
			if(iStop == pBuffer->size)
				iStop--;
			for (i=pBuffer->lastPosOut; i >= iStop; i--)
			{
				if(pBuffer->times[i] == pBuffer->times[i-1])
				{
					pBuffer->iL = i;
					break;
				}
			}
		}
		else
		{
			if((pBuffer->iL> 0) && ((pBuffer->iL < pBuffer->lastPosOut)))
			{
				iStop = pBuffer->iL;
				found = 1;
			}
			else
				iStop = 1;
			for (i=pBuffer->lastPosOut; i >= iStop; i--)
			{
				if(pBuffer->times[i] == pBuffer->times[i-1])
				{
					pBuffer->iL = i;
					found = 1;
					break;
				}
			}
			if(found == 0)
			{
				if((pBuffer->iL> 0) && ((pBuffer->iL > pBuffer->lastPosIn)))
				{
					iStop = pBuffer->iL;
				}
				else
					iStop = pBuffer->lastPosIn;
				if(iStop == 0)
					iStop++;
				for (i=pBuffer->size-1; i >= iStop; i--)
				{
					if((pBuffer->times[i] == pBuffer->times[i-1]) && (pBuffer->realValues[i] != pBuffer->realValues[i-1]))
					{
						pBuffer->iL = i;
						break;
					}
				}
			}
		}
	}
	else
	{
		pBuffer->iL = pBuffer->lastPosOut;
		pBuffer->iR = GetNextDelayIndex(pBuffer, pBuffer->lastPosOut);

	}
	pBuffer->iSearch = 0;
}

static void FindDelayInterval(ITI_DelayBuffer* pBuffer, ITI_real time, ITI_uint keepInterval)
{
	ITI_int found = 0;
	ITI_int i = 0;
	if((keepInterval==0) || ((pBuffer->iL<0) && (pBuffer->iR<0)))
	{
		 
		if(pBuffer->lastPosOut < 0)
		{
			if((pBuffer->lastPosIn > 0) && (time > pBuffer->times[0]))
			{
				pBuffer->lastPosOut = 0;
				pBuffer->iSearch = 1;
			}
			else
				return;
		}

		if(pBuffer->times[pBuffer->lastPosOut] < time)
		{
			ITI_int pos = pBuffer->lastPosOut;
			 
			if(time > pBuffer->times[GetNextDelayIndex(pBuffer, pBuffer->lastPosOut)])
			{
				 
				for (i=pBuffer->lastPosOut; i < pBuffer->size; i++)
				{
					if (pBuffer->times[i] >= time)
					{
						pBuffer->lastPosOut = i-1;
						found = 1;
						break;
					}
				}
				if (found == 0)
				{
					for (i = 0; i < pBuffer->lastPosIn; i++)
					{
						if (pBuffer->times[i] > time)
						{
							if (i == 0)
								pBuffer->lastPosOut = pBuffer->size-1;
							else
								pBuffer->lastPosOut = i-1;
							break;
						}
					}
				}
				if((pBuffer->iR > -1) && (pos <= pBuffer->iR) && (pBuffer->lastPosOut >= pBuffer->iR))
					pBuffer->iSearch = 1;
			}
		}
		else
		{
			ITI_int pos = pBuffer->lastPosOut;
			 
			for (i=pBuffer->lastPosOut; i >= 0; i--)
			{
				if (pBuffer->times[i] < time)
				{
					pBuffer->lastPosOut = i;
					found = 1;
					break;
				}
			}

			if (found == 0)
			{
				for (i = pBuffer->size-1; i >= pBuffer->lastPosOut; i--)
				{
					if (pBuffer->times[i] <= time)
					{
						pBuffer->lastPosOut = i;
						break;
					}
				}
			}
			if((pBuffer->iL > -1) && (pos >= pBuffer->iL) && (pBuffer->lastPosOut <= pBuffer->iL))
				pBuffer->iSearch = 1;
		}
	}
	else
	{
		 
		ITI_int iStop;
		if(pBuffer->lastPosOut == -1)
			return;

		if(pBuffer->times[pBuffer->lastPosOut] < time)
		{
			 
			if(time > pBuffer->times[GetNextDelayIndex(pBuffer, pBuffer->lastPosOut)])
			{
				 
				if((pBuffer->iR>-1) && (pBuffer->iR > pBuffer->lastPosOut))
					iStop = pBuffer->iR;
				else
					iStop = pBuffer->size;
				for (i=pBuffer->lastPosOut; i < iStop; i++)
				{
					if (pBuffer->times[i] > time)
					{
						pBuffer->lastPosOut = i-1;
						found = 1;
						return;
					}
				}
				if(i==pBuffer->iR)
					return;

				if (found == 0)
				{
					if((pBuffer->iR>-1) && (pBuffer->iR < pBuffer->lastPosIn))
						iStop = pBuffer->iR;
					else
						iStop = pBuffer->lastPosIn;
					for (i = 0; i < pBuffer->lastPosIn; i++)
					{
						if (pBuffer->times[i] > time)
						{
							if (i == 0)
								pBuffer->lastPosOut = pBuffer->size-1;
							else
								pBuffer->lastPosOut = i-1;
							return;
						}
					}
				}
			}
		}
		else
		{
			 
			iStop = 0;
			if((pBuffer->iL>-1) && (pBuffer->iL < pBuffer->lastPosOut))
				iStop = pBuffer->iL;

			for (i=pBuffer->lastPosOut; i >= iStop; i--)
			{
				if (pBuffer->times[i] < time)
				{
					pBuffer->lastPosOut = i;
					found = 1;
					return;
				}
			}
			if(i==pBuffer->iL)
				return;

			if (found == 0)
			{
				if((pBuffer->iL>-1) && (pBuffer->iL > pBuffer->lastPosIn))
					iStop = pBuffer->iL;
				else
					iStop = pBuffer->lastPosIn;

				for (i = pBuffer->size-1; i >= iStop; i--)
				{
					if (pBuffer->times[i] < time)
					{
						pBuffer->lastPosOut = i;
						return;
					}
				}
			}
		}
	}
}

ITI_real GetDelayRealValue(ITI_DelayBuffer* pBuffer, ITI_real delayExpr, ITI_real delayTime, ITI_real t, ITI_SolverInfo* sInfo, ITI_real* zf)
{
	ITI_real retVal = delayExpr;
	#ifdef ITI_ANIMATION
	if(pBuffer && sInfo->isAnimation)
		return sInfo->aniData.realDelayData[pBuffer->aniIndex];
	#endif

	if (pBuffer){
		ITI_real time = t - delayTime;

		if(pBuffer->size > 0)
		{
			pBuffer->realValues[pBuffer->lastPosIn] = delayExpr;
			pBuffer->times[pBuffer->lastPosIn] = t;
			 
		}

		if (delayTime > 0.0)
		{
			if (time > 0.0)
			{
				if((zf) && (pBuffer->iSearch==1))
					UpdateEventIndeces(pBuffer);

				if((pBuffer->lastPosOut > -1) && (pBuffer->times[pBuffer->lastPosOut] == time))
				{
					retVal = pBuffer->realValues[pBuffer->lastPosOut];
				}
				else
				{
					FindDelayInterval(pBuffer, time,zf && sInfo->isEvent==0);

					if(pBuffer->lastPosOut == -1)
						retVal = pBuffer->realValues[0];
					else
						retVal = CalcInterpol(pBuffer, time);
				}
			}
			else
			{
				retVal = pBuffer->realValues[0];
			}
			if(zf)
			{
				*zf = CalcZeroFunction(pBuffer, time);
			}
		}
	}
	#ifdef ITI_ANIMATION
	if (pBuffer)
		sInfo->aniData.realDelayData[pBuffer->aniIndex] = retVal;
	#endif
	return retVal;
}

ITI_int GetDelayIntValue(ITI_DelayBuffer* pBuffer, ITI_real delayExpr, ITI_real delayTime, ITI_real t, ITI_SolverInfo* sInfo, ITI_real* zf)
{
	ITI_int retVal = (ITI_int)delayExpr;
	#ifdef ITI_ANIMATION
	if(pBuffer && sInfo->isAnimation)
		return sInfo->aniData.intDelayData[pBuffer->aniIndex];
	#endif
	if (pBuffer){
		ITI_real time = t - delayTime;

		if(pBuffer->size > 0){
			pBuffer->intValues[pBuffer->lastPosIn] = (ITI_int)delayExpr;
			pBuffer->times[pBuffer->lastPosIn] = t;
			if(sInfo->isEvent)
				pBuffer->iNewVal=1;
		}

		if (delayTime > 0.0)
		{
			if (time > 0.0)
			{
				if((zf) && (pBuffer->iSearch==1))
					UpdateEventIndeces(pBuffer);

				if((pBuffer->lastPosOut > -1) && (pBuffer->times[pBuffer->lastPosOut] == time))
				{
					retVal = pBuffer->intValues[pBuffer->lastPosOut];
				}
				else
				{
					FindDelayInterval(pBuffer, time,zf && sInfo->isEvent==0);

					if(pBuffer->lastPosOut == -1)
						retVal = pBuffer->intValues[0];
					else
						retVal = pBuffer->intValues[pBuffer->lastPosOut];
				}
			}
			else
			{
				retVal = pBuffer->intValues[0];
			}
			if(zf)
			{
				*zf = CalcZeroFunction(pBuffer, time);
			}
		}
	}
	#ifdef ITI_ANIMATION
	if (pBuffer)
		sInfo->aniData.intDelayData[pBuffer->aniIndex] = retVal;
	#endif

	return retVal;
}

static ITI_real CalcInterpol(ITI_DelayBuffer* pBuffer, ITI_real t)
{
	ITI_int nextIndex = GetNextDelayIndex(pBuffer, pBuffer->lastPosOut);
	if (pBuffer->times[pBuffer->lastPosOut] == pBuffer->times[nextIndex])
		return pBuffer->realValues[pBuffer->lastPosOut];
	else
		return (pBuffer->realValues[pBuffer->lastPosOut] + (t-pBuffer->times[pBuffer->lastPosOut])*
					(pBuffer->realValues[nextIndex]-pBuffer->realValues[pBuffer->lastPosOut]) /
					(pBuffer->times[nextIndex]-pBuffer->times[pBuffer->lastPosOut]));
}

static ITI_real CalcZeroFunction(ITI_DelayBuffer* pBuffer, ITI_real t)
{
	if((pBuffer->iR < 0) && (pBuffer->iL < 0))
		return 1.0;
	else
	{
		ITI_real dR = t;
		ITI_real dL = t;
		if(pBuffer->iR >= 0)
			dR = pBuffer->times[pBuffer->iR] - t;
		if(pBuffer->iL >= 0)
			dL = t - pBuffer->times[pBuffer->iL];
		else
			return dR;
		return fabs(dR)<fabs(dL)?dR:dL;
	}
}

ITI_int InitCurveDataND(ITI_CurveData_ND *dst, ITI_CurveData_ND *src, size_t icnd, ITI_AllocateMemory allocateMemory)
{
	size_t i;

	if (dst == NULL)
		return 0;

	ITI_HandleAllocMemory

	memcpy(dst, src, icnd * sizeof(ITI_CurveData_ND));
	for (i = 0; i < icnd; i++)
		if (dst[i].nYScale > 0) {
			ITI_uint j;
			dst[i].pYScale = (ITI_YScale *)allocateMemory(dst[i].nYScale, sizeof(ITI_YScale));
			if (dst[i].pYScale == NULL)
				return -1;
			for (j = 0; j < dst[i].nYScale; j++)
				dst[i].pYScale[j].bScaleInitialized = ITI_false;
		}
		else
			dst[i].pYScale = NULL;
	return 0;
}

void FreeCurveDataND(ITI_CurveData_ND *cData, size_t icnd, ITI_FreeMemory freeMemory)
{
	size_t i;

	ITI_HandleFreeMemory

	for (i = 0; i < icnd; i++)
		freeMemory(cData[i].pYScale);
}

ITI_int InitCurveSetData(ITI_CurveSetData *dst, ITI_CurveSetData *src, size_t icset, ITI_AllocateMemory allocateMemory)
{
	size_t i;
	
	if (dst == NULL)
		return 0;

	ITI_HandleAllocMemory

	memcpy(dst, src, icset * sizeof(ITI_CurveSetData));
	for (i = 0; i < icset; i++)
		if (dst[i].nYScale > 0) {
			ITI_uint j;
			dst[i].pYScale = (ITI_YScale *)allocateMemory(dst[i].nYScale, sizeof(ITI_YScale));
			if (dst[i].pYScale == NULL)
				return -1;
			for (j = 0; j < dst[i].nYScale; j++)
				dst[i].pYScale[j].bScaleInitialized = ITI_false;
		}
		else
			dst[i].pYScale = NULL;
	return 0;
}

void FreeCurveSetData(ITI_CurveSetData *csData, size_t icset, ITI_FreeMemory freeMemory)
{
	size_t i;

	ITI_HandleFreeMemory

	for (i = 0; i < icset; i++)
		freeMemory(csData[i].pYScale);
}

void UpdateDelayBuffers(ITI_DelayBuffer* pBuffers, ITI_int nBuffer)
{
	if (pBuffers)
	{
		ITI_int i = 0;
		for (i=0; i < nBuffer; i++)
		{
			if(pBuffers[i].size > 0)
			{
				ITI_int incr = 1;
				if(pBuffers[i].lastPosIn>0)
				{
					if(pBuffers[i].valType==DelayValueType_Int)
					{
						 
						if(pBuffers[i].iNewVal)
						{
							if(pBuffers[i].intValues[pBuffers[i].lastPosIn] == pBuffers[i].intValues[pBuffers[i].lastPosIn-1])
								incr = 0;
							else
								pBuffers[i].iSearch=1;
						}
						else
						{
							incr = 0;
						}
					}
					else
					{
						if(pBuffers[i].times[pBuffers[i].lastPosIn] == pBuffers[i].times[pBuffers[i].lastPosIn-1])
						{
							 
							if(pBuffers[i].realValues[pBuffers[i].lastPosIn] == pBuffers[i].realValues[pBuffers[i].lastPosIn-1])
								incr = 0;
							else
								pBuffers[i].iSearch=1;
						}
						else if(pBuffers[i].lastPosIn>1)
						{
							if((pBuffers[i].realValues[pBuffers[i].lastPosIn-1]== pBuffers[i].realValues[pBuffers[i].lastPosIn]) && (pBuffers[i].realValues[pBuffers[i].lastPosIn-2]== pBuffers[i].realValues[pBuffers[i].lastPosIn]))
							{
								pBuffers[i].times[pBuffers[i].lastPosIn-1] = pBuffers[i].times[pBuffers[i].lastPosIn];
								incr = 0;
							}
						}
					}
				}
				pBuffers[i].iNewVal = 0;
				if(incr==1)
				{
					if (pBuffers[i].lastPosIn+1 == pBuffers[i].size)
						pBuffers[i].lastPosIn = 0;
					else
						pBuffers[i].lastPosIn++;

					if(pBuffers[i].lastPosIn == pBuffers[i].iL)
						pBuffers[i].iL = -1;
					if(pBuffers[i].lastPosIn == pBuffers[i].iR)
						pBuffers[i].iR = -1;
				}
			}
		}
	}
}

void InitDelayBuffers(ITI_DelayBuffer* pBuffers, ITI_int nBuffer, ITI_DelayInfo* pDelayInfos, ITI_AllocateMemory allocateMemory)
{
	ITI_HandleAllocMemory

	if (pBuffers)
	{
		ITI_int i = 0;
		for (i = 0; i < nBuffer; i++)
		{
			pBuffers[i].valType = pDelayInfos[i].valType;
			 
			if ((2*pDelayInfos[i].bufSize >= MAX_DELAY_BUFFER_SIZE) || (pDelayInfos[i].bufSize == 0))
			{
				pBuffers[i].size = MAX_DELAY_BUFFER_SIZE;
			}
			else
			{
				pBuffers[i].size = 2*pDelayInfos[i].bufSize;
			}
			switch(pBuffers[i].valType)
			{
			case DelayValueType_Int:
				pBuffers[i].intValues = (ITI_int*) allocateMemory(pBuffers[i].size, sizeof(ITI_int));
				pBuffers[i].realValues = 0;
				break;
			case DelayValueType_Real:
				pBuffers[i].intValues = 0;
				pBuffers[i].realValues = (ITI_real*) allocateMemory(pBuffers[i].size, sizeof(ITI_real));
				break;
			}
			pBuffers[i].times = (ITI_real*) allocateMemory(pBuffers[i].size, sizeof(ITI_real));
		}
		SetDelayBufferData(pBuffers, nBuffer);
	}
}

#ifdef ITI_ANIMATION
void GetNumDelay(ITI_DelayBuffer* pBuffers, ITI_int nBuffer, ITI_int* iReal, ITI_int* iInt)
{
	ITI_int i;
	*iInt=0;
	*iReal=0;
	for (i = 0; i < nBuffer; i++)
	{
		switch(pBuffers[i].valType)
		{
		case DelayValueType_Int:
			(*iInt)++;
			break;
		case DelayValueType_Real:
			(*iReal)++;
			break;
		}
	}
}
#endif

void SetDelayBufferData(ITI_DelayBuffer* pBuffers, ITI_int nBuffer)
{
	if (pBuffers)
	{
		ITI_int i = 0;
		#ifdef ITI_ANIMATION
		ITI_int intIndex = 0;
		ITI_int realIndex=0;
		#endif
		for (i = 0; i < nBuffer; i++)
		{
			switch(pBuffers[i].valType)
			{
			case DelayValueType_Int:
				memset(pBuffers[i].intValues, 0, pBuffers[i].size*sizeof(ITI_int));
				#ifdef ITI_ANIMATION
				pBuffers[i].aniIndex=intIndex;
				intIndex++;
				#endif
				break;
			case DelayValueType_Real:
				memset(pBuffers[i].realValues, 0, pBuffers[i].size*sizeof(ITI_real));
				#ifdef ITI_ANIMATION
				pBuffers[i].aniIndex=realIndex;
				realIndex++;
				#endif
				break;
			}
			memset(pBuffers[i].times, 0, pBuffers[i].size*sizeof(ITI_real));

			pBuffers[i].lastPosIn = 0;
			pBuffers[i].lastPosOut = -1;
			pBuffers[i].iL = -1;
			pBuffers[i].iR = 0;
			pBuffers[i].iSearch = 0;
			pBuffers[i].iNewVal = 0;
		}
	}
}

void FreeDelayBuffers(ITI_DelayBuffer* pBuffers, ITI_int nBuffer, ITI_FreeMemory freeMemory)
{
	ITI_int i;
	ITI_HandleFreeMemory

	for (i = 0; i < nBuffer; i++)
	{
		switch(pBuffers[i].valType)
		{
		case DelayValueType_Int:
			freeMemory(pBuffers[i].intValues);
			break;
		case DelayValueType_Real:
			freeMemory(pBuffers[i].realValues);
			break;
		}
		freeMemory(pBuffers[i].times);
	}
}

void Update_pre_z_data(ITI_PartitionVar* pData, ITI_ModelData* modelData)
{
	ITI_int i=0;
	if (!modelData || !pData)
		return;
	 
	#ifdef _MEMCPY
	memcpy(pData->pre_z.intData, pData->z.intData, pData->size.iz_int * sizeof(ITI_int));
	memcpy(pData->pre_z.realData, pData->z.realData, pData->size.iz_real * sizeof(ITI_real));
	#else
	for(i=0; i<pData->size.iz_int; i++)
		pData->pre_z.intData[i] = pData->z.intData[i];
	for(i=0; i<pData->size.iz_real; i++)
		pData->pre_z.realData[i] = pData->z.realData[i];
	#endif
	for(i=0; i<pData->size.iz_str; i++)
		AssignString2(&modelData->strMem, (const ITI_char**)&pData->pre_z.strData[i], pData->z.strData[i], (const ITI_char**)pData->pre_z.strData, pData->pre_z.strSize, (int)i);
}

void Restore_z_data(ITI_PartitionVar* pData, ITI_ModelData* modelData, ITI_CompositeData* zOld){
	size_t i;

	#ifdef _MEMCPY
	memcpy(pData->z.intData, zOld->intData, pData->size.iz_int*sizeof(ITI_int));
	memcpy(pData->z.realData, zOld->realData, pData->size.iz_real*sizeof(ITI_real));
	#else
	for (i = 0; i < (size_t)pData->size.iz_int; i++)
		pData->z.intData[i] = zOld->intData[i];
	for (i = 0; i < (size_t)pData->size.iz_real; i++)
		pData->z.realData[i] = zOld->realData[i];
	#endif
	for (i=0; i<(size_t)pData->size.iz_str; i++)
		AssignString2(&modelData->strMem, (const ITI_char**)&pData->z.strData[i], zOld->strData[i], (const ITI_char**)pData->z.strData, pData->z.strSize, (int)i);
}

 
void Restore_z_data_ptr(ITI_PartitionVar* pData, ITI_ModelData* modelData, ITI_CompositeData* zOld) {
	size_t i;
#ifndef ITI_COMP_SIM
	 
	assert(0);
	return;
#endif
	for (i = 0; i < (size_t)pData->size.iz_real; i++) {
#ifdef ITI_COMP_SIM
		*pData->z.realData[i] = *zOld->realData[i];
#else
		pData->z.realData[i] = zOld->realData[i];
#endif
	}

	#ifdef _MEMCPY
	memcpy(pData->z.intData, zOld->intData, pData->size.iz_int*sizeof(ITI_int));
	#else
	for (i = 0; i < pData->size.iz_int; i++)
		pData->z.intData[i] = zOld->intData[i];
	#endif
	for (i=0; i<(size_t)pData->size.iz_str; i++)
		AssignString2(&modelData->strMem, (const ITI_char**)&pData->z.strData[i], zOld->strData[i], (const ITI_char**)pData->z.strData, pData->z.strSize, (int)i);
}

void Update_real_pre_z_data(ITI_PartitionVar* pData){
	size_t i=0;
#ifdef ITI_COMP_SIM
	for (i = 0; i < (size_t)pData->size.iz_real; i++)
		*pData->pre_z.realData[i] = *pData->z.realData[i];
#else
	#ifdef _MEMCPY
	memcpy(pData->pre_z.realData, pData->z.realData, pData->size.iz_real * sizeof(ITI_real));
	#else
	for(i=0; i<(size_t)pData->size.iz_real; i++)
		pData->pre_z.realData[i] = pData->z.realData[i];
	#endif
#endif
}

 
void Update_pre_z_data_ptr(ITI_PartitionVar* pData, ITI_ModelData* modelData)
{
	size_t i;
#ifndef ITI_COMP_SIM
	assert(0);
	return;
#endif
	if (!pData)
		return;

	for (i = 0; i < (size_t)pData->size.iz_real; i++) {
#ifdef ITI_COMP_SIM
		*pData->pre_z.realData[i] = *pData->z.realData[i];
#else
		pData->pre_z.realData[i] = pData->z.realData[i];
#endif
	}
	#ifdef _MEMCPY
	memcpy(pData->pre_z.intData, pData->z.intData, pData->size.iz_int*sizeof(ITI_int));
	#else
	for (i = 0; i < (size_t)pData->size.iz_int; i++){
		pData->pre_z.intData[i] = pData->z.intData[i];
	}
	#endif
	for(i=0; i<(size_t)pData->size.iz_str; i++)
		AssignString2(&modelData->strMem, (const ITI_char**)&pData->pre_z.strData[i], pData->z.strData[i], (const ITI_char**)pData->pre_z.strData, pData->pre_z.strSize, (int)i);
}

void Update_pre_zf(ITI_real* zf, ITI_real* pre_zf, ITI_int iSize)
{
	 
	#ifdef _MEMCPY
	memcpy(pre_zf, zf, iSize * sizeof(ITI_real));
	#else
	ITI_int i=0;
	for(i=0; i<iSize; i++)
		pre_zf[i] = zf[i];
	#endif
}

ITI_int Check_oldsign_zf(ITI_real* zf,ITI_real*  old_sign_zf, ITI_int iSize)
{
	ITI_int i;
	ITI_int iRet = SOLVER_SUCCESS_END;
	for(i=0; i<iSize; i++)
	{
		if(old_sign_zf[i] != sign(zf[i]))
		{
			iRet = SOLVER_SUCCESS_CONTINUE;
			break;
		}
	}
	return iRet;
}

void Update_oldsign_zf(ITI_real* zf,ITI_real*  old_sign_zf, ITI_int iSize)
{
	ITI_int i=0;
	for(i=0; i<iSize; i++)
		old_sign_zf[i] = sign(zf[i]);
}

ITI_int Check_Update_oldsign_zf(ITI_real* zf, ITI_real* old_sign_zf, ITI_int iSize)
{
	ITI_int i;
	ITI_int iRet = SOLVER_SUCCESS_END;
	for(i=0; i<iSize; i++)
	{
		if(old_sign_zf[i] != sign(zf[i]))
		{
			iRet = SOLVER_SUCCESS_CONTINUE;
			break;
		}
	}
	for(i=0; i<iSize; i++)
	{
		old_sign_zf[i] = sign(zf[i]);
	}
	return iRet;
}

static ITI_int CheckEpsilonRange(ITI_real* x, ITI_real xmin, ITI_real xmax) {
	double eps = DBL_EPSILON * 10.0 * fabs(*x);
	if (*x < xmin) {
		if (*x > xmin - eps) {
			*x = xmin;
			return 1;
		}
		return 0;
	}
	else if (*x > xmax) {
		if (*x < xmax + eps) {
			*x = xmax;
			return 1;
		}
		return 0;
	}
	return 1;

}



static ITI_int Check_z_real(ITI_real pre_z, ITI_real z, ITI_real relTol, ITI_real absTol){
	if (pre_z != z){
		ITI_real delta = fabs(pre_z - z);
		if(delta > (absTol + fabs(relTol * z))){
			return 1;
		}
	}
	return 0;
}

 
ITI_int Check_z_data_ptr(ITI_PartitionVar* pData, ITI_real relTol, ITI_real absTol)
{
	size_t i;
#ifndef ITI_COMP_SIM
	assert(0);
	return 0;
#endif
	if (!pData)
		return 0;

	for (i = 0; i < (size_t)pData->size.iz_real; i++){
#ifdef ITI_COMP_SIM
		if (Check_z_real(*pData->pre_z.realData[i], *pData->z.realData[i], relTol, absTol))
#else
		if (Check_z_real(pData->pre_z.realData[i], pData->z.realData[i], relTol, absTol))
#endif
			return 1;
	}
	for (i = 0; i < (size_t)pData->size.iz_int; i++){
		if (pData->pre_z.intData[i] != pData->z.intData[i])
			return 1;
	}
	for (i = 0; i < (size_t)pData->size.iz_str; i++){
		if(strcmp(pData->pre_z.strData[i], pData->z.strData[i]) != 0)
			return 1;
	}

	return 0;
}

ITI_int Check_z_data(ITI_PartitionVar* pData, ITI_real relTol, ITI_real absTol){
	size_t i;
	if (!pData)
		return 0;

	for (i = 0; i < (size_t)pData->size.iz_real; i++){
#ifdef ITI_COMP_SIM
		if (Check_z_real(*(pData->pre_z.realData[i]), *(pData->z.realData[i]), relTol, absTol))
#else
		if (Check_z_real(pData->pre_z.realData[i], pData->z.realData[i], relTol, absTol))
#endif
			return 1;
	}

	for (i = 0; i < (size_t)pData->size.iz_int; i++){
		if (pData->pre_z.intData[i] != pData->z.intData[i])
			return 1;
	}
	for (i = 0; i < (size_t)pData->size.iz_str; i++){
		if(strcmp(pData->pre_z.strData[i], pData->z.strData[i]) != 0)
			return 1;
	}
	return 0;
}

void CopyVars(ITI_real* src, ITI_real* dest, ITI_int start, ITI_int end)
{
#ifdef _MEMCPY
	memcpy(&dest[start], &src[start], (end - start) * sizeof(ITI_real));
#else
	ITI_int i;
	for (i = start; i < end; i++)
		dest[i] = src[i];
#endif
}

void CopyVarsCS(ITI_real** src, ITI_real** dest, ITI_int start, ITI_int end)
{
	ITI_int i;
	for (i = start; i < end; i++)
		*(dest[i]) = *(src[i]);
}

void CopyVarsA(ITI_real** src, ITI_real* dest, ITI_int start, ITI_int end)
{
	ITI_int i;
	for (i = start; i < end; i++)
		dest[i] = *(src[i]);
}

void CopyVarsB(ITI_real* src, ITI_real** dest, ITI_int start, ITI_int end)
{
	ITI_int i;
	for (i = start; i < end; i++)
		*(dest[i]) = src[i];
}

void InitParameter(ITI_PartitionVar* pData, ITI_parameterData* parameters, ITI_real* param, int nparam, ITI_int ip)
{
	int i;
	size_t intIndex = 0;
	size_t realIndex = 0;
	size_t strIndex = 0;

	for (i = 0; i < ip; i++){
		if (i < nparam){
			switch (parameters[i].valType){
				case SharedType_Real :
#ifdef ITI_COMP_SIM
					*(pData->p.realData[realIndex]) = param[i];
#else
					pData->p.realData[realIndex] = param[i];
#endif
					realIndex++;
					break;
				case SharedType_Int : pData->p.intData[intIndex] = (ITI_int)param[i];
					intIndex++;
					break;
				case SharedType_Str :
					AssignAdaptString_calloc(&pData->p, parameters[i].unit, strIndex, 0, 0);
					strIndex++;
				default:
					break;
			}
		}
		else {
			switch (parameters[i].valType){
				case SharedType_Real :
#ifdef ITI_COMP_SIM
					*(pData->p.realData[realIndex]) = parameters[i].defaultValue;
#else
					pData->p.realData[realIndex] = parameters[i].defaultValue;
#endif
					realIndex++;
					break;
				case SharedType_Int : pData->p.intData[intIndex] = (ITI_int)parameters[i].defaultValue;
					intIndex++;
					break;
				case SharedType_Str :
					AssignAdaptString_calloc(&pData->p, parameters[i].unit, strIndex, 0, 0);
					strIndex++;
				default:
					break;
			}
		}
	}
}

void AllocInitParameters(ITI_CompositeData* p, ITI_parameterData* pData, ITI_real* pValue, size_t nPreal, size_t nPint, size_t nPstr)
{
	size_t i;
	size_t intIndex = 0;
	size_t realIndex = 0;
	size_t strIndex = 0;

	if (nPreal == 0)
		p->realData = NULL;
	else {
#ifdef ITI_COMP_SIM
		p->realData = (ITI_real**)calloc(nPreal, sizeof(ITI_real*));
#else
		p->realData = (ITI_real*)calloc(nPreal, sizeof(ITI_real));
#endif
	}
	if (nPint == 0)
		p->intData = NULL;
	else
		p->intData = (ITI_int*)calloc(nPint, sizeof(ITI_int));
	if (nPstr == 0) {
		p->strData = NULL;
		p->strSize = NULL;
	}
	else {
		p->strData = (ITI_char**)calloc(nPstr, sizeof(ITI_char*));
		p->strSize = (size_t*)calloc(nPstr, sizeof(size_t));
	}

	for (i = 0; i < nPreal+nPint+nPstr; i++)
	{
		if(pValue != 0)
		{
			switch (pData[i].valType)
			{
					case SharedType_Real :
#ifdef ITI_COMP_SIM
						p->realData[realIndex] = &(pValue[i]);
#else
						p->realData[realIndex] = pValue[i];
#endif
						realIndex++;
						break;
					case SharedType_Int : p->intData[intIndex] = (ITI_int)pValue[i];
						intIndex++;
						break;
					case SharedType_Str:
						AssignAdaptString_calloc(p, pData[i].unit, strIndex, 0, 0);
						strIndex++;
						break;
					default:
						break;
			}
		}
		else
		{
			switch (pData[i].valType)
			{
				case SharedType_Real :
#ifdef ITI_COMP_SIM
					p->realData[realIndex] = &(pData[i].defaultValue);
#else
					p->realData[realIndex] = pData[i].defaultValue;
#endif
					realIndex++;
					break;
				case SharedType_Int :
					p->intData[intIndex] = (ITI_int)pData[i].defaultValue;
					intIndex++;
					break;
				case SharedType_Str:
					AssignAdaptString_calloc(p, pData[i].unit, strIndex, 0, 0);
					strIndex++;
					break;
				default:
					break;
			}
		}
	}
}

void AssignAdaptString_calloc(ITI_CompositeData* data, const char* str, size_t index, ITI_AllocateMemory allocateMemory, ITI_FreeMemory freeMemory){
	ITI_HandleAllocMemory
	ITI_HandleFreeMemory
	if((strlen(str)+1) > data->strSize[index]){
		data->strSize[index] = 2*strlen(str);
		freeMemory(data->strData[index]);
		data->strData[index] = (ITI_char*)allocateMemory(data->strSize[index], sizeof(char));
	}
	strcpy(data->strData[index], str);
}

void FreeParameters(ITI_CompositeData* p)
{
	if(p->realData != 0)
		free(p->realData);
	if(p->intData != 0)
		free(p->intData);
	if(p->strData != 0)
		free(p->strData);
	if (p->strSize != 0)
		free(p->strSize);
}

















































#define	FACTOR	1.6
#define	NTRY	50
#define	GLTOL	1e-16
#define SNTRY	10

void Solve(ITI_BlockData* pBd, ITI_SolverInfo* pInfo)
{
	ITI_uint _n = pBd->nRes;
	ITI_uint i;
	ITI_int info = 0;
	ITI_int n = _n;

	if (pBd->error) {
		if (_n == 1 && pBd->hybrid == 0) {
			pBd->hybrid = 1;
			if (pBd->nCol > 0 || pBd->useNumJac) {
				pBd->iCol = -1;
				pBd->mode = 0;
			} else
				pBd->mode = 1;
		} else {
			pBd->lambda /= 2.;
			if (pBd->lambda < pBd->lambda_min) {
				(*pBd->vTable->ErrorLambdaMin)(pBd, pInfo, _n);
				return;
			}
			pBd->error = 0;
			pBd->beta = -1.;
		}
		return;
	} else {
		pBd->beta = 1.;
		if (_n == 1)
			pBd->lambda = 1.;
	}

	if (pBd->mode == 0) {
		CalcBlockJac(pBd, pInfo);
		return;
	}

	if (pBd->mode == 11 || pBd->mode == 12) {
		pBd->repeat = 0;
		return;
	}

	if (_n == 1 && pBd->hybrid) {
		double sMin;

		if (pBd->mode == 1 && pBd->hybrid == 2)
			pBd->mode = 6;

		switch (pBd->mode) {
		case 1:
			sMin = pBd->gltol * (1.0 + fabs(pBd->x[0]));
			if (pBd->jac[0] == 0.)
				pBd->s[0] = sMin;
			else {
				pBd->s[0] = pBd->res[0] / pBd->jac[0];
				if (fabs(pBd->s[0]) < sMin)
					pBd->s[0] = sMin;
			}
			pBd->xl = pBd->xh = pBd->x[0];
			pBd->resSav = pBd->res[0];
			pBd->sSav = pBd->s[0];
			pBd->mode = 7;
			pBd->corrStep++;
			pBd->hybrid = 2;
			if (pBd->considerLimit)
				CheckBounds(pBd, _n, pInfo);
			break;
		case 7:
			pBd->corrStep++;
			if ((pBd->res[0] < 0. && pBd->resSav > 0.) || (pBd->res[0] > 0. && pBd->resSav < 0.)) {
				if (pBd->res[0] > 0.) {
					pBd->xl = pBd->xh;
					pBd->xh = pBd->x[0];
				} else {
					pBd->xh = pBd->xl;
					pBd->xl = pBd->x[0];
				}
				pBd->dxSav = fabs(pBd->xl - pBd->xh);
				pBd->mode = 6;
			} else if (pBd->corrStep == NTRY) {
				if (pBd->zfSwitch == -1) {
					pBd->zfSwitch = 1;
					pBd->hybrid = 1;
					pBd->mode = 8;
					return;
				} else {
					(*pBd->vTable->ErrorInitialBracketNotFound)(pBd, pInfo);
					pBd->hybrid = 1;
					return;
				}
			} else {
				if (fabs(pBd->resSav) > fabs(pBd->res[0])) {
					pBd->xh = pBd->x[0];
					pBd->s[0] *= (1 + FACTOR);
				} else {
					pBd->xl = pBd->x[0];
					pBd->s[0] *= -FACTOR;
				}
				pBd->resSav = pBd->res[0];
				if (pBd->considerLimit)
					CheckBounds(pBd, _n, pInfo);
				return;
			}
			pBd->sSav = pBd->s[0];
			 
		case 6:
			pBd->s[0] = pBd->sSav;
			if (fabs(pBd->s[0]) <=  GLTOL * (1.0 + fabs(pBd->x[0]))) {
				pBd->mode = 10;
				pBd->repeat = 0;
				return;
			}
			if (pBd->res[0] > 0.)
				pBd->xh = pBd->x[0];
			else
				pBd->xl = pBd->x[0];
			if ((((pBd->x[0] - pBd->xh) * pBd->jac[0] <= pBd->res[0]) && ((pBd->x[0] - pBd->xl) * pBd->jac[0] <= pBd->res[0]))
				|| (((pBd->x[0] - pBd->xh) * pBd->jac[0] >= pBd->res[0]) && ((pBd->x[0] - pBd->xl) * pBd->jac[0] >= pBd->res[0]))
				|| fabs(2. * pBd->res[0]) > fabs(pBd->dxSav * pBd->jac[0])) {
				pBd->dxSav = pBd->s[0];
				pBd->s[0] = 0.5 * (pBd->xl - pBd->xh);
				pBd->x[0] = 0.5 * (pBd->xl + pBd->xh) + pBd->s[0];
			} else {
				pBd->dxSav = pBd->s[0];
				pBd->s[0] = pBd->res[0] / pBd->jac[0];
			}
			if (pBd->x[0] - pBd->s[0] == pBd->x[0]) {
				pBd->mode = 10;
				pBd->repeat = 0;
				return;
			}
			pBd->sSav = pBd->s[0];
			if (pBd->considerLimit)
				CheckBounds(pBd, _n, pInfo);

			if (pBd->nCol > 0 || pBd->useNumJac) {
				pBd->mode = 13;
				pBd->iCol = -1;
			} else
				(*pBd->vTable->SetAnalysisTypeDetail)(pInfo, pBd->strAnalysisTypeDetail);

			break;
		}
		return;
	}

	if (_n == 1) {
		double eps, temp;

		switch (pBd->mode) {
		case 1:
			if (pBd->res[0] == 0.) {
				pBd->mode = 10;
				pBd->repeat = 0;
				return;
			}

			temp = fabs(pBd->x[0]);
			if (temp > 1.)
				pBd->colsc[0] = temp;
			else
				pBd->colsc[0] = 1.;
			temp = fabs(pBd->jac[0] * pBd->colsc[0]);
			if (temp > 0.)
				pBd->rowsc[0] = 1. / temp;
			else
				pBd->rowsc[0] = 1.;

			pBd->lambda = 1.;
			pBd->mode = 6;
			 
		case 6:
			eps = pBd->gltol * (1.0 + fabs(pBd->x[0]));

			if (pBd->jac[0] != 0.)
				pBd->s[0] = pBd->res[0] / pBd->jac[0];
			else if (pBd->res[0] == 0.) {
				pBd->mode = 10;
				pBd->repeat = 0;
				break;
			}
			else {
				pBd->hybrid = 1;
				pBd->mode = 8;
				return;
			}

			pBd->normdx = fabs(pBd->s[0]);

			if (pBd->normdx < eps) {
				if ((pBd->x[0] - pBd->s[0] != pBd->x[0]) && strcmp(pBd->strAnalysisTypeDetail, "validStep")  ) {
					pBd->mode = 3;
					if (pBd->considerLimit)
						CheckBounds(pBd, _n, pInfo);
					break;
				} else {
					pBd->mode = 10;
					pBd->repeat = 0;
					break;
				}
			}

			pBd->corrStep++;
			if (pBd->corrStep > SNTRY) {
				pBd->hybrid = 1;
				pBd->mode = 8;
				return;
			} else if (pBd->considerLimit)
				CheckBounds(pBd, _n, pInfo);

			if (pBd->nCol <= 0 && pBd->useNumJac == 0)
				(*pBd->vTable->SetAnalysisTypeDetail)(pInfo, pBd->strAnalysisTypeDetail);

			break;
		case 3:
			pBd->mode = 10;
			pBd->repeat = 0;
			break;
		case 9:
			if (fabs(pBd->res[0]) * pBd->rowsc[0] > pBd->gltol * 10.) {
				temp = fabs(pBd->x[0]);
				if (temp > 1.)
					pBd->colsc[0] = temp;
				else
					pBd->colsc[0] = 1.;
				temp = fabs(pBd->jac[0] * pBd->colsc[0]);
				if (temp > 0.)
					pBd->rowsc[0] = 1. / temp;
				else
					pBd->rowsc[0] = 1.;
				if (fabs(pBd->res[0]) * pBd->rowsc[0] > pBd->gltol * 10.) {
					if (pBd->isNonlinear)
						pBd->mode = 1;
					else {
						(*pBd->vTable->ErrorResidualImage)(pBd, pInfo, _n);
						pBd->mode = 15;
					}
				}
			}
			if (pBd->mode == 9) {
				pBd->mode = 10;
				pBd->repeat = 0;
			}
			break;
		}
		return;
	}

	switch(pBd->mode)
	{
		case 1:
			if (EuklNorm(pBd->res, _n) == 0.) {
				pBd->mode = 10;
				pBd->repeat = 0;
				return;
			}

			pInfo->iFailedEqu = 0;
			pBd->reduced = 0;
#ifdef SCALE
			scaleJacCols(pBd->jac, pBd->x, pBd->colsc, _n, _n);
			scaleJacRows(pBd->jac, pBd->res, pBd->rowsc, _n, _n);
#endif
			if (pBd->linSolv == 0) {  
				ITI_int one = 1;

				for (i = 0; i < _n; i++)
					pBd->s[i] = pBd->res[i];
				iti_dgetrf_(&n, &n, pBd->jac, &n, pBd->ipiv, pBd->colpiv, &info);
				if (info == 0)
					dgetrs_("N", &n, &one, pBd->jac, &n, pBd->ipiv, pBd->s, &n, &info);
				else {
					pInfo->iFailedEqu = -info;
					iti_dgetrs_("N", &n, &one, pBd->jac, &n, pBd->ipiv, pBd->colpiv, pBd->s, &n, &info);
					if (!pBd->useNumJac && info != 0)
						pBd->error = 1;
				}
			} else {  
				for (i = 0; i < _n; i++) {
					pBd->s[i] = pBd->res[i];

					pBd->llsData.jpvt[i] = 0;
				}
				pBd->llsData.m = _n;
				pBd->llsData.n = _n;
				pBd->llsData.b = pBd->s;

				lls_fact(&pBd->llsData);
				if (pBd->llsData.rank != 0)
					lls_solv(&pBd->llsData);
				else
					memset((void *)pBd->s, 0, _n*sizeof(ITI_real));
			}

			pBd->normdx = EuklNorm(pBd->s, _n);
#ifdef SCALE
			for (i = 0; i < _n; i++)
				pBd->s[i] *= pBd->colsc[i];
#endif

			if (info > 0) {
				pInfo->iFailedEqu = info;
				if (pBd->zfSwitch == 1 || pBd->undamped)
					(*pBd->vTable->ErrorResidualImage)(pBd, pInfo, _n);
				else {
					(*pBd->vTable->WarningResidualImage)(pBd, pInfo, _n, _n, _n);
					if (pBd->autoLinSolv == 1) {
						SwitchLinearSolver(pBd, pInfo);
						return;
					}
				}
			} else {
				if (pBd->normdx < pBd->gltol) {
					if (pBd->normdx > 0.0 && strcmp(pBd->strAnalysisTypeDetail, "validStep")  ) {
						pBd->mode = 3;
						if (pBd->considerLimit)
							CheckBounds(pBd, _n, pInfo);
						break;
					} else {
						pBd->mode = 10;
						pBd->repeat = 0;
						break;
					}
				}
				if (pBd->corrStep > 0 && pBd->zfSwitch != 1 && !pBd->undamped) {
					ITI_real s;
					for (i = 0; i < _n; i++)
						pBd->w[i] = pBd->dxbar[i] - pBd->s[i];
#ifdef SCALE
					s = ScaledNorm2(pBd->w, pBd->colsc, _n);
#else
					s = EuklNorm(pBd->w, _n);
#endif
					if (s==0.0) {
						




						pBd->lambda = 1.0;
					} else {
						ITI_real mue = pBd->normdxkm1 * pBd->normdxbar * pBd->lambda / (s * pBd->normdx);
						pBd->lambda = max(min(1.0, mue), pBd->lambda_min);
					}
				}
				if (pBd->zfSwitch == 1 || pBd->undamped)
					pBd->corrStep++;
				if (pBd->corrStep > pBd->maxiter) {
					if (pBd->zfSwitch != -1 && pBd->undamped) {
						if (pBd->autoLinSolv == 1) {
							SwitchLinearSolver(pBd, pInfo);
							return;
						} else
							(*pBd->vTable->ErrorMaxIter)(pBd, pInfo, _n);
						break;
					} else if (pBd->zfSwitch == -1) {
						pBd->zfSwitch = 1;
						if (pBd->nCol > 0 || pBd->useNumJac) {
							pBd->iCol = -1;
							pBd->mode = 0;
						} else
							pBd->mode = 1;
						pBd->corrStep = 0;
						pBd->lambda = 1.;
						return;
					} else {
						pBd->undamped = 1;
						pBd->corrStep = 0;
						pBd->lambda = 1.;
					}
				}
			}

			if(pBd->considerLimit)
				CheckBounds(pBd, _n, pInfo);
			pBd->mode = 2;
			break;
		case 3:
		case 4:
			pBd->mode = 10;
			pBd->repeat = 0;
			break;
		case 2:
		case 5:
			if (pBd->lambda < pBd->lambda_min) {
				if (pBd->zfSwitch == -1) {
					pBd->zfSwitch = 1;
					if (pBd->nCol > 0 || pBd->useNumJac) {
						pBd->iCol = -1;
						pBd->mode = 0;
					} else
						pBd->mode = 1;
					pBd->corrStep = 0;
					pBd->lambda = 1.;
					return;
				} else {
					if (pBd->autoLinSolv == 1) {
						SwitchLinearSolver(pBd, pInfo);
						return;
					} else if (!pBd->undamped) {
						pBd->undamped = 1;
						pBd->corrStep = 0;
						pBd->lambda = 1.0;
						pBd->mode = 8;
						pBd->error = 0;
						return;
					} else {
						(*pBd->vTable->ErrorLambdaMin)(pBd, pInfo, _n);
						if (EuklNorm(pBd->res, _n) <= pBd->gltol)
							pBd->error = 0;
					}
					break;
				}
			}
			else if (pInfo->iFailedEqu > 0) {
				if (pBd->zfSwitch == -1) {
					pBd->zfSwitch = 1;
					if (pBd->nCol > 0 || pBd->useNumJac) {
						pBd->iCol = -1;
						pBd->mode = 0;
					} else
						pBd->mode = 1;
					pBd->corrStep = 0;
					pBd->lambda = 1.;
					return;
				} else if (pBd->corrStep > 20) {
					if (pBd->autoLinSolv == 1) {
						SwitchLinearSolver(pBd, pInfo);
						return;
					} else
						(*pBd->vTable->ErrorResidualImage)(pBd, pInfo, _n);
					break;
				} else {
					pBd->repeat = 1;
					pBd->normdxkm1 = 1e35;
					pBd->normdxbar = 1e35;
				}
			}
			else
				pBd->repeat = globalNewton(pBd, _n, pInfo);
			if (pBd->repeat==1) {
				memset((void *) pBd->s, 0, _n*sizeof(ITI_real));
				pBd->corrStep++;

				if(pBd->nCol > 0 || pBd->useNumJac)
				{
					pBd->iCol = -1;
					pBd->mode = 0;
				}
				else
				{
					pBd->mode = 1;
					(*pBd->vTable->SetAnalysisTypeDetail)(pInfo, pBd->strAnalysisTypeDetail);
				}
			}
			break;
		case 9:
			{
				double wnorm2 = 0.;
				for (i = 0; i < _n; i++) {
					double f = pBd->res[i] * pBd->rowsc[i];
					wnorm2 += f * f;
				}
				wnorm2 = sqrt(wnorm2 / _n);
				if (wnorm2 > pBd->gltol * 100.) {
					if (pBd->isNonlinear)
						if (pBd->nCol > 0 || pBd->useNumJac) {
							pBd->iCol = -1;
							pBd->mode = 0;
						} else
							pBd->mode = 1;
					else {
						(*pBd->vTable->ErrorResidualImage)(pBd, pInfo, _n);
						pBd->mode = 15;
					}
				} else {
					pBd->mode = 10;
					pBd->repeat = 0;
				}
			}
			break;
	}
}

#undef	FACTOR
#undef	NTRY
#undef	GLTOL

void SolveRect(ITI_BlockData* pBd, ITI_SolverInfo* pInfo)
{
	ITI_uint _m = pBd->nRes;
	ITI_uint _n = pBd->nDAE;
	ITI_WorkMemory *pWorkMem = pBd->workMem;

	if (pBd->error) {
		pBd->lambda /= 2.;
		if (pBd->lambda < pBd->lambda_min) {
			(*pBd->vTable->ErrorLambdaMin)(pBd, pInfo, _n);
			return;
		}
		pBd->error = 0;
		pBd->beta = -1.;
	} else
		pBd->beta = 1.;

	switch(pBd->mode)
	{
		case 0:
			CalcBlockJac(pBd, pInfo);
			break;
		case 1:
			{
				ITI_uint i;
				pBd->reduced = 0;
				pInfo->iFailedEqu = 0;

































				{
					ITI_uint j;
					ITI_int m = _m;
					ITI_int n = _n;
					ITI_int info = 0;
					if (pBd->nViolLimit > 0) {
						for (i = 0; i < pBd->nViolLimit; i++) {
							ITI_char msg[500];
							for (j = 0; j < _m; j++)
								pBd->jac[pBd->iViolLimit[i]*_m + j] = 0.0;
							snprintf(msg, 500, "Problem during solving system of equations for %s.\nStep %i: The Newton update is set to zero.", pBd->name[pBd->iViolLimit[i]], pBd->corrStep+1);
							traceWarning(msg, pInfo);
						}
					}
					if (EuklNorm(pBd->res, _m) == 0.) {
						pBd->mode = 10;
						pBd->repeat = 0;
						break;
					}
					if (pBd->linSolv == 0) {
						pBd->rect_error = 4.44089209850063e-013;

						for (i = 0; i < _m; i++) {
							ITI_real rowvalue = fabs(pBd->res[i]);
							for (j = 0; j < _n; j++) {
								rowvalue += fabs(pBd->jac[_m*j + i] * pBd->xstart[j]);
							}
							rowvalue *= 1e-15;
							if (rowvalue > pBd->rect_error)
								pBd->rect_error = rowvalue;
						}
						iti_dgetrf_(&m, &n, pBd->jac, &m, pBd->ipiv, pBd->colpiv, &info);
						for (i = 0; i < _m; i++)
							pBd->s[i] = pBd->res[i];
						if (_n > _m) {
							for (i = _m; i < _n; i++)
								pBd->s[i] = 0.0;
						}
						iti_dgetrs_rect_normal_(&m, &n, pBd->jac, pBd->ipiv, pBd->colpiv, pBd->s, &info, pWorkMem->ker,
								pWorkMem->kerCopy, pWorkMem->vecCopy, pWorkMem->dWork, pWorkMem->lPermVecCol, pBd->rect_error);
					}
					else {
						for (i = 0; i < _m; i++)
							pBd->s[i] = pBd->res[i];
						if (_n > _m) {
							for (i = _m; i < _n; i++)
								pBd->s[i] = 0.0;
						}
						for (i = 0; i < _n; i++)
							pBd->llsData.jpvt[i] = 0;

						pBd->llsData.m = _m;
						pBd->llsData.n = _n;
						pBd->llsData.b = pBd->s;

						lls_fact(&pBd->llsData);
						if (pBd->llsData.rank != 0)
							lls_solv(&pBd->llsData);
						else
							memset((void *)pBd->s, 0, _n*sizeof(ITI_real));
					}
					if (info > 0) {
						pInfo->iFailedEqu = info;
						if (pBd->zfSwitch == 1 || pBd->undamped)
							(*pBd->vTable->ErrorResidualImage)(pBd, pInfo, _n);
						else
							(*pBd->vTable->WarningResidualImage)(pBd, pInfo, _m, _n, _n);
						if (pBd->autoLinSolv == 1) {
							SwitchLinearSolver(pBd, pInfo);
							return;
						}
					}
				}
				if (pInfo->iFailedEqu == 0) {
					pBd->normdx = EuklNorm(pBd->s, _n);
					if (pBd->normdx < pBd->gltol) {
						if (pBd->considerLimit) {
							if ((CheckBoundsRect(pBd, _n, pInfo) > 0) && (_n - pBd->nViolLimit >= _m)) {
								memset((void *) pBd->s, 0, _n*sizeof(ITI_real));
								if(pBd->nCol > 0 || pBd->useNumJac)
								{
									pBd->iCol = -1;
									pBd->mode = 0;
									break;
								}
								pBd->mode = 1;
								(*pBd->vTable->SetAnalysisTypeDetail)(pInfo, pBd->strAnalysisTypeDetail);
								break;
							}
						}
						pBd->mode = 19;
						break;
					}
					if (pBd->corrStep > 0 && pBd->zfSwitch != 1 && !pBd->undamped) {
						ITI_real s;
						for (i = 0; i < _n; i++)
							pBd->w[i] = pBd->dxbar[i] - pBd->s[i];
						s = EuklNorm(pBd->w, _n);
						if (s==0.0) {
							




							pBd->lambda = 1.0;
						}
						else {
							ITI_real mue = pBd->normdxkm1 * pBd->normdxbar * pBd->lambda / (s * pBd->normdx);
							pBd->lambda = max(min(1.0, mue), pBd->lambda_min);
						}
					}
					if (pBd->zfSwitch == 1 || pBd->undamped)
						pBd->corrStep++;
					if (pBd->corrStep > pBd->maxiter) {
						if (pBd->zfSwitch != -1 && pBd->undamped) {
							if (pBd->autoLinSolv == 1) {
								SwitchLinearSolver(pBd, pInfo);
								return;
							} else
								(*pBd->vTable->ErrorMaxIter)(pBd, pInfo, _n);
							break;
						} else if (pBd->zfSwitch == -1) {
							pBd->zfSwitch = 1;
							if (pBd->nCol > 0 || pBd->useNumJac) {
								pBd->iCol = -1;
								pBd->mode = 0;
							} else
								pBd->mode = 1;
							pBd->corrStep = 0;
							pBd->lambda = 1.;
							return;
						} else {
							pBd->undamped = 1;
							pBd->corrStep = 0;
							pBd->lambda = 1.;
						}
					}
				}
				pBd->mode = 2;
				if (pBd->considerLimit) {
					if ((CheckBoundsRect(pBd, _n, pInfo) > 0) && (_n - pBd->nViolLimit >= _m)) {
						memset((void *) pBd->s, 0, _n*sizeof(ITI_real));
						if(pBd->nCol > 0 || pBd->useNumJac)
						{
							pBd->iCol = -1;
							pBd->mode = 0;
						}
						else
						{
							pBd->mode = 1;
							(*pBd->vTable->SetAnalysisTypeDetail)(pInfo, pBd->strAnalysisTypeDetail);
						}
					}
					else
						pBd->nViolLimit = 0;
				}
			}
			break;
		case 3:
		case 4:
			pBd->mode = 10;
			pBd->repeat = 0;
			break;
		case 2:
		case 5:
			if (pBd->lambda < pBd->lambda_min) {
				if (pBd->zfSwitch == -1) {
					pBd->zfSwitch = 1;
					if (pBd->nCol > 0 || pBd->useNumJac) {
						pBd->iCol = -1;
						pBd->mode = 0;
					} else
						pBd->mode = 1;
					pBd->corrStep = 0;
					pBd->lambda = 1.;
					return;
				} else {
					if (pBd->autoLinSolv == 1) {
						SwitchLinearSolver(pBd, pInfo);
						return;
					} else if (!pBd->undamped) {
						pBd->undamped = 1;
						pBd->corrStep = 0;
						pBd->lambda = 1.0;
						pBd->mode = 8;
						pBd->error = 0;
						return;
					} else {
						(*pBd->vTable->ErrorLambdaMin)(pBd, pInfo, _n);
						if (EuklNorm(pBd->res, _m) <= pBd->gltol)
							pBd->error = 0;
					}
					break;
				}
			}
			else if (pInfo->iFailedEqu > 0) {
				if (pBd->zfSwitch == -1) {
					pBd->zfSwitch = 1;
					if (pBd->nCol > 0 || pBd->useNumJac) {
						pBd->iCol = -1;
						pBd->mode = 0;
					} else
						pBd->mode = 1;
					pBd->corrStep = 0;
					pBd->lambda = 1.;
					return;
				} else if (!pBd->isNonlinear || pBd->corrStep > 20) {
					if (EuklNorm(pBd->res, _m) < pBd->gltol) {
						ITI_char msg[500];
						snprintf(msg, 500, "Equation %d failed. However, residual norm is less than the block tolerance.", pInfo->iFailedEqu);
						traceWarning(msg, pInfo);
						pBd->repeat = 0;
						pBd->mode = 10;
					} else {
						if (pBd->autoLinSolv == 1) {
							SwitchLinearSolver(pBd, pInfo);
							return;
						} else
							(*pBd->vTable->ErrorResidualImage)(pBd, pInfo, _n);
					}
					break;
				} else {
					pBd->repeat = 1;
					pBd->normdxkm1 = 1e35;
					pBd->normdxbar = 1e35;
				}
			}
			else
				pBd->repeat = globalNewton_rect(pBd, _m, _n, pInfo, pWorkMem);
			if (pBd->repeat==1) {
				memset((void *) pBd->s, 0, _n*sizeof(ITI_real));
				pBd->corrStep++;

				if(pBd->nCol > 0 || pBd->useNumJac)
				{
					pBd->iCol = -1;
					pBd->mode = 0;
				}
				else
				{
					pBd->mode = 1;
					(*pBd->vTable->SetAnalysisTypeDetail)(pInfo, pBd->strAnalysisTypeDetail);
				}
			}
			break;
		case 9:
			pBd->mode = 19;
		case 19:
			scaleJacCols(pBd->jac, pBd->x, pBd->colsc, _m, _n);
			scaleJacRows(pBd->jac, pBd->res, pBd->rowsc, _m, _n);
			if (EuklNorm(pBd->res, _m) > pBd->gltol) {
				if (pBd->autoLinSolv == 1) {
					SwitchLinearSolver(pBd, pInfo);
					return;
				} else
					(*pBd->vTable->ErrorResidualImage)(pBd, pInfo, _n);
			} else {
				pBd->mode = 10;
				pBd->repeat = 0;
			}
			break;
		case 11:
		case 12:
			pBd->repeat = 0;
			break;
	}
}

void Solve_DP(ITI_BlockData* pBd, ITI_DPBlockData* bdBD, ITI_SolverInfo* pInfo)
{
	ITI_uint _n = pBd->nRes;
	ITI_uint nDAE = pBd->nDAE;

	if (pBd->error) {
		pBd->lambda /= 2.;
		if (pBd->lambda < pBd->lambda_min) {
			(*pBd->vTable->ErrorLambdaMin)(pBd, pInfo, _n);
			return;
		}
		pBd->error = 0;
		pBd->beta = -1.;
	} else
		pBd->beta = 1.;

	switch(pBd->mode)
	{
		case 0:
			CalcBlockJac_DP(pBd, pInfo);
			break;
		case 1:
			{
				ITI_uint i,k;
				ITI_int info = 0;
				Check_Jac(pBd, bdBD, pInfo, nDAE-_n, nDAE);

				pInfo->iFailedEqu = 0;
				pBd->reduced = 0;

				if (_n == 1) {
					if (pBd->jac[0] == 0.0) {
						pBd->s[0] = 0.0;
						pBd->normdx = 0.0;
						if (fabs(pBd->res[0]) > 4.44089209850063e-013)
							info = 1;
						else {
							pBd->mode = 10;
							pBd->repeat = 0;
							break;
						}
					} else {
#ifdef SCALE
						pBd->colsc[0] = 1.;
#endif
						pBd->s[0] = pBd->res[0] / pBd->jac[0];
						pBd->normdx = fabs(pBd->s[0]);
					}
				} else {
#ifdef SCALE
					scaleJacCols_DP(pBd, bdBD, _n, nDAE);
					scaleJacRows(pBd->jac, pBd->res, pBd->rowsc, _n, _n);
#endif
					if (pBd->linSolv == 0) {  
						ITI_int one = 1;
						ITI_int n = _n;

						for (i = 0; i < _n; i++)
							pBd->s[i] = pBd->res[i];
						iti_dgetrf_(&n, &n, pBd->jac, &n, pBd->ipiv, pBd->colpiv, &info);
						if(info == 0)
							dgetrs_("N", &n, &one, pBd->jac, &n, pBd->ipiv, pBd->s, &n, &info);
						else {
							pInfo->iFailedEqu = -info;
							iti_dgetrs_("N", &n, &one, pBd->jac, &n, pBd->ipiv, pBd->colpiv, pBd->s, &n, &info);
							if (!pBd->useNumJac && info != 0)
								pBd->error = 1;
						}
					} else {  
						for (i = 0; i < _n; i++) {
							pBd->s[i] = pBd->res[i];

							pBd->llsData.jpvt[i] = 0;
						}
						pBd->llsData.m = _n;
						pBd->llsData.n = _n;
						pBd->llsData.b = pBd->s;

						lls_fact(&pBd->llsData);
						if (pBd->llsData.rank != 0)
							lls_solv(&pBd->llsData);
						else
							memset((void *)pBd->s, 0, _n*sizeof(ITI_real));
					}
					pBd->normdx = EuklNorm(pBd->s, _n);
#ifdef SCALE
					for (i = 0; i < _n; i++)
						pBd->s[i] *= pBd->colsc[i];
#endif
				}
				if (info > 0) {
					pInfo->iFailedEqu = info;
					if (pBd->zfSwitch == 1 || pBd->undamped)
						(*pBd->vTable->ErrorResidualImage)(pBd, pInfo, _n);
					else
						(*pBd->vTable->WarningResidualImage)(pBd, pInfo, _n, _n, nDAE);
				} else {
					if (pBd->normdx < pBd->gltol) {
						if (pBd->normdx > 0.0 && strcmp(pBd->strAnalysisTypeDetail, "validStep")  ) {
							if (pBd->considerLimit)
								CheckBounds_DP(pBd, bdBD, nDAE, pInfo);
							for(i = 0, k = 0; i < nDAE; i++) {
								if(bdBD->M[i] < nDAE) {
									pBd->mv[i] -= pBd->lambda * pBd->alpha * pBd->s[k];
									k++;
								}
							}
							pBd->mode = 3;
							break;
						} else {
							pBd->mode = 10;
							pBd->repeat = 0;
							break;
						}
					}
					if (pBd->corrStep > 0 && pBd->zfSwitch != 1 && !pBd->undamped) {
						ITI_real s;
						for (i = 0; i < _n; i++)
							pBd->w[i] = pBd->dxbar[i] - pBd->s[i];
#ifdef SCALE
						s = ScaledNorm2(pBd->w, pBd->colsc, _n);
#else
						s = EuklNorm(pBd->w, _n);
#endif
						if (s==0.0) {
							










							pBd->lambda = 1.0;
						} else {
							ITI_real mue = pBd->normdxkm1 * pBd->normdxbar * pBd->lambda / (s * pBd->normdx);
							pBd->lambda = max(min(1.0, mue), pBd->lambda_min);
						}
					}
					if (pBd->zfSwitch == 1 || pBd->undamped)
						pBd->corrStep++;
					if (pBd->corrStep > pBd->maxiter) {
						if (pBd->zfSwitch != -1 && pBd->undamped) {
							if (pBd->autoLinSolv == 1) {
								SwitchLinearSolver(pBd, pInfo);
								if (pBd->nCol > 0 || pBd->useNumJac) {
									pBd->iCol = -1;
									pBd->mode = 0;
								} else
									pBd->mode = 1;
								return;
							} else
								(*pBd->vTable->ErrorMaxIter)(pBd, pInfo, nDAE);
							break;
						} else if (pBd->zfSwitch == -1) {
							pBd->zfSwitch = 1;
							if (pBd->nCol > 0 || pBd->useNumJac) {
								pBd->iCol = -1;
								pBd->mode = 0;
							} else
								pBd->mode = 1;
							pBd->corrStep = 0;
							pBd->lambda = 1.;
							return;
						} else {
							pBd->undamped = 1;
							pBd->corrStep = 0;
							pBd->lambda = 1.;
						}
					}
				}
				if (pBd->considerLimit)
					CheckBounds_DP(pBd, bdBD, nDAE, pInfo);
				pBd->mode = 2;
				for (i = 0, k = 0; i < nDAE; i++) {
					if (bdBD->M[i] < nDAE) {
						pBd->mv[i] -= pBd->lambda * pBd->alpha * pBd->s[k];
						k++;
					}
				}
			}
			break;
		case 3:
		case 4:
			pBd->mode = 10;
			pBd->repeat = 0;
			break;
		case 2:
		case 5:
			if (pBd->lambda < pBd->lambda_min) {
				if (pBd->zfSwitch == -1) {
					pBd->zfSwitch = 1;
					if (pBd->nCol > 0 || pBd->useNumJac) {
						pBd->iCol = -1;
						pBd->mode = 0;
					} else
						pBd->mode = 1;
					pBd->corrStep = 0;
					pBd->lambda = 1.;
					return;
				} else {
					if (pBd->autoLinSolv == 1) {
						SwitchLinearSolver(pBd, pInfo);
						if (pBd->nCol > 0 || pBd->useNumJac) {
							pBd->iCol = -1;
							pBd->mode = 0;
						} else
							pBd->mode = 1;
						return;
					} else if (!pBd->undamped) {
						pBd->undamped = 1;
						pBd->corrStep = 0;
						pBd->lambda = 1.0;
						pBd->error = 0;
						if (pBd->nCol > 0 || pBd->useNumJac) {
							pBd->iCol = -1;
							pBd->mode = 0;
						} else
							pBd->mode = 1;
						return;
					} else {
						(*pBd->vTable->ErrorLambdaMin)(pBd, pInfo, nDAE);
						if (EuklNorm(pBd->res, _n) <= pBd->gltol)
							pBd->error = 0;
					}
					break;
				}
			}
			else if (pInfo->iFailedEqu > 0) {
				if (pBd->zfSwitch == -1) {
					pBd->zfSwitch = 1;
					if (pBd->nCol > 0 || pBd->useNumJac) {
						pBd->iCol = -1;
						pBd->mode = 0;
					} else
						pBd->mode = 1;
					pBd->corrStep = 0;
					pBd->lambda = 1.;
					return;
				} else if (pBd->corrStep > 20) {
					if (pBd->autoLinSolv == 1) {
						SwitchLinearSolver(pBd, pInfo);
						if (pBd->nCol > 0 || pBd->useNumJac) {
							pBd->iCol = -1;
							pBd->mode = 0;
						} else
							pBd->mode = 1;
						return;
					} else
						(*pBd->vTable->ErrorResidualImage)(pBd, pInfo, nDAE);
					break;
				} else {
					pBd->repeat = 1;
					pBd->normdxkm1 = 1e35;
					pBd->normdxbar = 1e35;
				}
			}
			else
				pBd->repeat = globalNewton_DP(pBd, bdBD, _n, nDAE, pInfo);
			if (pBd->repeat==1) {
				memset((void *) pBd->s, 0, _n*sizeof(ITI_real));
				pBd->corrStep++;

				if(pBd->nCol > 0 || pBd->useNumJac)
				{
					pBd->iCol = -1;
					pBd->mode = 0;
				}
				else
				{
					pBd->mode = 1;
					(*pBd->vTable->SetAnalysisTypeDetail)(pInfo, pBd->strAnalysisTypeDetail);
				}
			}
			break;
		case 9:
		case 11:
		case 12:
			pBd->repeat = 0;
			break;
	}
}

static void SwitchLinearSolver(ITI_BlockData *pBd, ITI_SolverInfo *pInfo)
{
	if (pBd->linSolv == 0)
		pBd->linSolv = 1;
	else
		pBd->linSolv = 0;
	pBd->autoLinSolv = -1;
	pBd->undamped = 0;
	pBd->corrStep = 0;



		pBd->lambda = 1.0;
	pBd->mode = 8;
	pBd->error = 0;
}

static void CheckBounds(ITI_BlockData* pBd, ITI_uint n, ITI_SolverInfo* pInfo) {
	ITI_uint i;
	pBd->alpha = 1.0;
	for(i=0; i<n; ++i)
	{
		if((pBd->considerMin[i]) && (pBd->x[i]-pBd->s[i] <= pBd->minVal[i])) {
			if(pBd->s[i] != 0.0) {
				pBd->alpha = min(pBd->alpha, 0.5*((pBd->x[i] - pBd->minVal[i]) / pBd->s[i]));
				(*pBd->vTable->WarningBelowMinDamping)(pBd, pInfo, i);
			}
			while((pBd->x[i] - pBd->alpha * pBd->s[i] <= pBd->minVal[i]) && (pBd->alpha != 0.0)) {
				pBd->alpha /= 10.0;
				(*pBd->vTable->WarningReducingDampFac)(pBd, pInfo, i);
			}
		}
		if((pBd->considerMax[i]) && (pBd->x[i]-pBd->s[i] >= pBd->maxVal[i])) {
			if(pBd->s[i] != 0.0) {
				pBd->alpha = min(pBd->alpha, 0.5*((pBd->x[i] - pBd->maxVal[i]) / pBd->s[i]));
				(*pBd->vTable->WarningExceedsMaxDamping)(pBd, pInfo, i);
			}
			while((pBd->x[i] - pBd->alpha * pBd->s[i] >= pBd->maxVal[i]) && (pBd->alpha != 0.0)) {
				pBd->alpha /= 10.0;
				(*pBd->vTable->WarningReducingDampFac)(pBd, pInfo, i);
			}
		}
		if(pBd->alpha == 0.0) {
			(*pBd->vTable->ErrorExceedsBorder)(pBd, pInfo, i);
			break;
		}
	}
}

static ITI_uint CheckBoundsRect(ITI_BlockData* pBd, ITI_uint n, ITI_SolverInfo* pInfo) {
	ITI_uint i;
	pBd->alpha = 1.0;
	for (i = 0; i < n; i++) {
		if ((pBd->considerMin[i]) && (pBd->x[i]-pBd->s[i] <= pBd->minVal[i])) {
			if (pBd->s[i] != 0.0) {
				pBd->alpha = min(pBd->alpha, 0.5*((pBd->x[i] - pBd->minVal[i]) / pBd->s[i]));
				(*pBd->vTable->WarningBelowMinDamping)(pBd, pInfo, i);
				pBd->iViolLimit[pBd->nViolLimit] = i;
				pBd->nViolLimit++;
			}
			while ((pBd->x[i] - pBd->alpha * pBd->s[i] <= pBd->minVal[i]) && (pBd->alpha != 0.0)) {
				pBd->alpha /= 10.0;
				(*pBd->vTable->WarningReducingDampFac)(pBd, pInfo, i);
			}
		}
		if ((pBd->considerMax[i]) && (pBd->x[i]-pBd->s[i] >= pBd->maxVal[i])) {
			if (pBd->s[i] != 0.0) {
				pBd->alpha = min(pBd->alpha, 0.5*((pBd->x[i] - pBd->maxVal[i]) / pBd->s[i]));
				(*pBd->vTable->WarningExceedsMaxDamping)(pBd, pInfo, i);
				pBd->iViolLimit[pBd->nViolLimit] = i;
				pBd->nViolLimit++;
			}
			while ((pBd->x[i] - pBd->alpha * pBd->s[i] >= pBd->maxVal[i]) && (pBd->alpha != 0.0)) {
				pBd->alpha /= 10.0;
				(*pBd->vTable->WarningReducingDampFac)(pBd, pInfo, i);
			}
		}
		if (pBd->alpha == 0.0) {
			(*pBd->vTable->ErrorExceedsBorder)(pBd, pInfo, i);
			return 0;
		}
	}
	if (n > 1 && pInfo->iFailedEqu == 0 && pBd->alpha < 1.0)
		return pBd->nViolLimit;
	else
		return 0;
}

static void CheckBounds_DP(ITI_BlockData* pBd, ITI_DPBlockData* bdBD, ITI_uint nDAE, ITI_SolverInfo* pInfo) {
	ITI_uint i,k;
	pBd->alpha = 1.0;
	for(i=0,k=0;i<nDAE;i++) {
		if(bdBD->M[i] < nDAE) {
			if((pBd->considerMin[i]) && (pBd->mv[i]-pBd->s[k] <= pBd->minVal[i])) {
				if(pBd->s[k] != 0.0) {
					pBd->alpha = min(pBd->alpha, 0.5*((pBd->mv[i] - pBd->minVal[i]) / pBd->s[k]));
					(*pBd->vTable->WarningBelowMinDamping2)(pBd, pInfo, i, k);
				}
				while((pBd->mv[i] - pBd->alpha * pBd->s[k] <= pBd->minVal[i]) && (pBd->alpha != 0.0)) {
					pBd->alpha /= 10.0;
					(*pBd->vTable->WarningReducingDampFac)(pBd, pInfo, i);
				}
			}
			if((pBd->considerMax[i]) && (pBd->mv[i]-pBd->s[k] >= pBd->maxVal[i])) {
				if(pBd->s[k] != 0.0) {
					pBd->alpha = min(pBd->alpha, 0.5*((pBd->mv[i] - pBd->maxVal[i]) / pBd->s[k]));
					(*pBd->vTable->WarningExceedsMaxDamping2)(pBd, pInfo, i, k);
				}
				while((pBd->mv[i] - pBd->alpha * pBd->s[k] >= pBd->maxVal[i]) && (pBd->alpha != 0.0)) {
					pBd->alpha /= 10.0;
					(*pBd->vTable->WarningReducingDampFac)(pBd, pInfo, i);
				}
			}
			if(pBd->alpha == 0.0) {
				(*pBd->vTable->ErrorExceedsBorder)(pBd, pInfo, i);
				break;
			}
			k++;
		}
	}
}

void CheckLimits_DP(ITI_BlockData* pBd, ITI_DPBlockData* bdBD, ITI_uint nODE, ITI_uint nDAE, ITI_SolverInfo* pInfo)
{
	ITI_uint i;
	for(i = nDAE; i < nDAE + nODE; i++) {
		ITI_uint j = bdBD->M[i];
		if((pBd->considerMin[j]) && (pBd->v[i] <= pBd->minVal[j])) {
			(*pBd->vTable->WarningBelowMin)(pBd, pInfo, i, j);
			pBd->error = 1;
			break;
		}
		if((pBd->considerMax[j]) && (pBd->v[i] >= pBd->maxVal[j])) {
			(*pBd->vTable->WarningExceedsMax)(pBd, pInfo, i, j);
			pBd->error = 1;
			break;
		}
	}
}

static void Check_Jac(ITI_BlockData* pBd, ITI_DPBlockData* bdBD, ITI_SolverInfo* pInfo, ITI_uint nODE, ITI_uint nDAE)
{
	ITI_uint i,j,k;

	if ((pInfo->bDPAllowed != 1) || (bdBD->MCP != 1))
		CheckM(pBd, bdBD, nODE, nDAE);

	if (bdBD->MCP == 1) {
		if(pInfo->bDPAllowed == 1)
		{
			CalcM(pBd, bdBD, nODE, nDAE);
			for(i=nDAE;i<(nDAE+nODE);i++)
			{
				pBd->v[i] = pBd->mv[bdBD->M[i]];
			}
			pInfo->bDPHappened = ITI_true;
		}
		else
			pInfo->bDPRequired = ITI_true;
	}
	k=0;
	for(i=0;i<nDAE;i++)
	{
		if(bdBD->M[i] < nDAE)
		{
			for(j=0;j<nDAE-nODE;j++)
			{
				pBd->jac[(nDAE-nODE)*k+j] = pBd->sjac[nDAE*j+i];
			}
			k++;
		}
	}
}
























































































































































































static ITI_uint globalNewton(ITI_BlockData* pBd, ITI_uint _n, ITI_SolverInfo* pInfo)
{
	ITI_real lambda_new, wnorm, theta, mue;

	if (_n==1) {
		pBd->dxbar[0] = pBd->res[0] / pBd->jac[0];
		pBd->normdxbar = fabs(pBd->dxbar[0]);
#ifdef SCALE
		pBd->dxbar[0] *= pBd->colsc[0];
		wnorm = fabs(pBd->dxbar[0] + (pBd->lambda - 1.0) * pBd->s[0]) / pBd->colsc[0];
#else
		wnorm = fabs(pBd->dxbar[0] + (pBd->lambda - 1.0) * pBd->s[0]);
#endif
	}
	else {
		ITI_int n = _n;
		ITI_uint i;
		if (pBd->linSolv == 0) {  
			ITI_int info = -pInfo->iFailedEqu;
			ITI_int one = 1;
			for (i = 0; i < _n; i++)
#ifdef SCALE
				pBd->dxbar[i] = pBd->res[i] * pBd->rowsc[i];
#else
				pBd->dxbar[i] = pBd->res[i];
#endif
			if (info == 0)
				dgetrs_("N", &n, &one, pBd->jac, &n, pBd->ipiv, pBd->dxbar, &n, &info);
			else
				iti_dgetrs_("N", &n, &one, pBd->jac, &n, pBd->ipiv, pBd->colpiv, pBd->dxbar, &n, &info);
		}
		else {  
			for (i = 0; i < _n; i++)
#ifdef SCALE
				pBd->dxbar[i] = pBd->res[i] * pBd->rowsc[i];
#else
				pBd->dxbar[i] = pBd->res[i];
#endif
			pBd->llsData.b = pBd->dxbar;
			lls_solv(&pBd->llsData);
		}

		pBd->normdxbar = EuklNorm(pBd->dxbar, _n);
		for (i = 0; i < _n; i++) {
#ifdef SCALE
			pBd->dxbar[i] *= pBd->colsc[i];
#endif
			pBd->w[i] = pBd->dxbar[i] + (pBd->lambda - 1.0) * pBd->s[i];
		}
#ifdef SCALE
		wnorm = ScaledNorm2(pBd->w, pBd->colsc, _n);
#else
		wnorm = EuklNorm(pBd->w, _n);
#endif
	}

	{
		ITI_real _numerator = (0.5 * pBd->normdx * pBd->lambda * pBd->lambda);
		if ( _numerator < 1e+35*wnorm )
			mue = _numerator / wnorm;
		else
			mue = 1e+35;
	}

	switch (pInfo->isEvent) {
		case 0:
			theta = pBd->normdxbar / pBd->normdx;
			if (theta > 1.0 - pBd->lambda / 4.0) {
				lambda_new = min(mue, 0.5 * pBd->lambda);
				if (pBd->lambda <= pBd->lambda_min)
					pBd->lambda = lambda_new;
				else
					pBd->lambda = max(lambda_new, pBd->lambda_min);
				pBd->reduced = 1;
				pBd->mode = 5;
				return 5;
			}
			break;
		case 1:
			if (pBd->normdxbar >= pBd->normdx) {
				lambda_new = min(mue, 0.5 * pBd->lambda);
				if (pBd->lambda <= pBd->lambda_min)
					pBd->lambda = lambda_new;
				else
					pBd->lambda = max(lambda_new, pBd->lambda_min);
				pBd->reduced = 1;
				pBd->mode = 5;
				return 5;
			}
			break;
	}

	lambda_new = min(1.0, mue);
	if (pBd->lambda == 1.0 && lambda_new == 1.0) {
		if (pBd->mode == 2 && pBd->normdxbar <= pBd->gltol) {
			if (pBd->normdxbar > 0.0 && strcmp(pBd->strAnalysisTypeDetail, "validStep")  ) {
				pBd->mode = 4;
				return 4;
			}
			else {
				pBd->mode = 10;
				return 0;
			}
		}
	}
	else {
		if (lambda_new >= 4.0*pBd->lambda && pBd->reduced == 0) {
			pBd->lambda = lambda_new;
			pBd->mode = 5;
			return 5;
		}
	}

	pBd->normdxkm1 = pBd->normdx;
	return 1;
}

static ITI_uint globalNewton_rect(ITI_BlockData* pBd, ITI_uint _m, ITI_uint _n, ITI_SolverInfo* pInfo, ITI_WorkMemory* pWorkMem)
{
	ITI_uint i;
	ITI_real lambda_new, wnorm, mue;

	if (_n==1) {
		if (pBd->jac[pBd->iMax] != 0.0)
			pBd->dxbar[0] = pBd->res[pBd->iMax] / pBd->jac[pBd->iMax];
		else
			pBd->dxbar[0] = 0.0;
	}
	else {
		ITI_int m = _m;
		ITI_int n = _n;
		for (i = 0; i < _m; i++)
			pBd->dxbar[i] = pBd->res[i];
		if (_n > _m) {
			for (i = _m; i < _n; i++)
				pBd->dxbar[i] = 0.0;
		}
		if (pBd->linSolv == 0) {
			ITI_int info = 0;
			iti_dgetrs_rect_normal_(&m, &n, pBd->jac, pBd->ipiv, pBd->colpiv, pBd->dxbar, &info, pWorkMem->ker,
					pWorkMem->kerCopy, pWorkMem->vecCopy, pWorkMem->dWork, pWorkMem->lPermVecCol, pBd->rect_error);
		}
		else {
			pBd->llsData.b = pBd->dxbar;
			lls_solv(&pBd->llsData);
		}
	}

	pBd->normdxbar = EuklNorm(pBd->dxbar, _n);
	for (i = 0; i < _n; i++)
		pBd->w[i] = pBd->dxbar[i] + (pBd->lambda - 1.0) * pBd->s[i];
	wnorm = EuklNorm(pBd->w, _n);
	{
		ITI_real _numerator = (0.5 * pBd->normdx * pBd->lambda * pBd->lambda);
		if (_numerator < 1e35*wnorm)
			mue = _numerator / wnorm;
		else
			mue = 1e+35;
	}

	if (pBd->normdxbar >= pBd->normdx) {
		lambda_new = min(mue, 0.5 * pBd->lambda);
		if (pBd->lambda <= pBd->lambda_min)
			pBd->lambda = lambda_new;
		else
			pBd->lambda = max(lambda_new, pBd->lambda_min);
		pBd->reduced = 1;
		pBd->mode = 5;
		return 5;
	}

	lambda_new = min(1.0, mue);
	if (pBd->lambda == 1.0 && lambda_new == 1.0) {
		if (pBd->mode == 2 && pBd->normdxbar <= pBd->gltol) {
			pBd->mode = 10;
			return 0;
		}
	}
	else {
		if (lambda_new >= 4.0*pBd->lambda && pBd->reduced == 0) {
			pBd->lambda = lambda_new;
			pBd->mode = 5;
			return 5;
		}
	}
	pBd->normdxkm1 = pBd->normdx;
	return 1;
}

static ITI_uint globalNewton_DP(ITI_BlockData* pBd, ITI_DPBlockData* bdBD, ITI_uint _n, ITI_uint nDAE, ITI_SolverInfo* pInfo)
{
	ITI_uint i,k;
	ITI_real lambda_new, wnorm, theta, mue;

	if (_n==1) {
		pBd->dxbar[0] = pBd->res[0] / pBd->jac[0];
		pBd->normdxbar = fabs(pBd->dxbar[0]);
		wnorm = fabs(pBd->dxbar[0] + (pBd->lambda - 1.0) * pBd->s[0]);
	}
	else {
		ITI_int n = _n;
		if (pBd->linSolv == 0) {  
			ITI_int info = -pInfo->iFailedEqu;
			ITI_int one = 1;
			for (i = 0; i < _n; i++)
#ifdef SCALE
				pBd->dxbar[i] = pBd->res[i] * pBd->rowsc[i];
#else
				pBd->dxbar[i] = pBd->res[i];
#endif
			if (info == 0)
				dgetrs_("N", &n, &one, pBd->jac, &n, pBd->ipiv, pBd->dxbar, &n, &info);
			else
				iti_dgetrs_("N", &n, &one, pBd->jac, &n, pBd->ipiv, pBd->colpiv, pBd->dxbar, &n, &info);
		}
		else {  
			for (i = 0; i < _n; i++)
#ifdef SCALE
				pBd->dxbar[i] = pBd->res[i] * pBd->rowsc[i];
#else
				pBd->dxbar[i] = pBd->res[i];
#endif
			pBd->llsData.b = pBd->dxbar;
			lls_solv(&pBd->llsData);
		}
		pBd->normdxbar = EuklNorm(pBd->dxbar, _n);
		for (i = 0; i < _n; i++) {
#ifdef SCALE
			pBd->dxbar[i] *= pBd->colsc[i];
#endif
			pBd->w[i] = pBd->dxbar[i] + (pBd->lambda - 1.0) * pBd->s[i];
		}
#ifdef SCALE
		wnorm = ScaledNorm2(pBd->w, pBd->colsc, _n);
#else
		wnorm = EuklNorm(pBd->w, _n);
#endif
	}

	{
		ITI_real _numerator = (0.5 * pBd->normdx * pBd->lambda * pBd->lambda);
		if (_numerator < 1e35*wnorm)
			mue = _numerator / wnorm;
		else
			mue = 1e+35;
	}

	switch (pInfo->isEvent) {
		case 0:
			theta = pBd->normdxbar / pBd->normdx;
			if (theta > 1.0 - pBd->lambda / 4.0) {
				lambda_new = min(mue, 0.5 * pBd->lambda);
				if (pBd->lambda <= pBd->lambda_min)
					pBd->lambda = lambda_new;
				else
					pBd->lambda = max(lambda_new, pBd->lambda_min);
				pBd->reduced = 1;
				for (i = 0, k = 0; i < nDAE; i++) {
					if (bdBD->M[i] < nDAE) {
						pBd->mv[i] = pBd->xjac[i] - pBd->lambda * pBd->alpha * pBd->s[k];
						k++;
					}
				}
				pBd->mode = 5;
				return 5;
			}
			break;
		case 1:
			if (pBd->normdxbar >= pBd->normdx) {
				lambda_new = min(mue, 0.5 * pBd->lambda);
				if (pBd->lambda <= pBd->lambda_min)
					pBd->lambda = lambda_new;
				else
					pBd->lambda = max(lambda_new, pBd->lambda_min);
				pBd->reduced = 1;
				for (i = 0, k = 0; i < nDAE; i++) {
					if (bdBD->M[i] < nDAE) {
						pBd->mv[i] = pBd->xjac[i] - pBd->lambda * pBd->alpha * pBd->s[k];
						k++;
					}
				}
				pBd->mode = 5;
				return 5;
			}
			break;
	}

	lambda_new = min(1.0, mue);
	if (pBd->lambda == 1.0 && lambda_new == 1.0) {
		if (pBd->normdxbar <= pBd->gltol) {
			if (pBd->mode == 2 && pBd->normdxbar > 0.0 && strcmp(pBd->strAnalysisTypeDetail, "validStep")  ) {
				for (i = 0, k = 0; i < nDAE; i++) {
					if (bdBD->M[i] < nDAE) {
						pBd->mv[i] -= pBd->alpha * pBd->dxbar[k];
						k++;
					}
				}
				pBd->mode = 4;
				return 4;
			}
			else {
				pBd->mode = 10;
				return 0;
			}
		}
	}
	else {
		if (lambda_new >= 4.0*pBd->lambda && pBd->reduced == 0) {
			pBd->lambda = lambda_new;
			for (i = 0, k = 0; i < nDAE; i++) {
				if (bdBD->M[i] < nDAE) {
					pBd->mv[i] = pBd->xjac[i] - pBd->lambda * pBd->alpha * pBd->s[k];
					k++;
				}
			}
			pBd->mode = 5;
			return 5;
		}
	}
	pBd->normdxkm1 = pBd->normdx;
	return 1;
}

ITI_real EuklNorm(ITI_real* a, ITI_uint n)
{
	ITI_uint i;
	ITI_real dblNorm = 0.0;

	for (i = 0; i < n; i++)
		dblNorm = max(dblNorm, fabs(a[i]));
	if (dblNorm > 0.) {
		ITI_real sum = 0.0;
		for (i = 0; i < n; i++) {
			ITI_real tmp = a[i] / dblNorm;
			sum += tmp*tmp;
		}
		dblNorm *= sqrt(sum / (double)n);
	}

	return dblNorm;
}

static ITI_real ScaledNorm2(ITI_real* a, ITI_real* b, ITI_uint n)
{
	ITI_uint i;
	ITI_real dblNorm = 0.0;

	for (i = 0; i < n; i++)
		dblNorm = max(dblNorm, fabs(a[i] / b[i]));
	if (dblNorm > 0.) {
		ITI_real sum = 0.0;
		for (i = 0; i < n; i++) {
			ITI_real tmp = (a[i] / b[i]) / dblNorm;
			sum += tmp*tmp;
		}
		dblNorm *= sqrt(sum / (double)n);
	}

	return dblNorm;
}

ITI_real SProd(ITI_real* a, ITI_real* b, ITI_uint n)
{
	ITI_uint i;
	ITI_real sum = 0.0;

	for (i = 0; i < n; i++)
		sum += a[i]*b[i];

	return sum;
}

void scaleJacCols(ITI_real* jac, ITI_real* x, ITI_real* colsc, ITI_uint m, ITI_uint n)
{
	ITI_uint i,j;

	for (i = 0; i < n; i++) {
		ITI_real temp = fabs(x[i]);
		if (temp > 1.0) {
			colsc[i] = temp;
			for (j = 0; j < m; j++)
				jac[i*m + j] *= temp;
		}
		else
			colsc[i] = 1.0;
	}
}

void scaleJacColsCS(ITI_real* jac, ITI_real** x, ITI_real* colsc, ITI_uint m, ITI_uint n)
{
	ITI_uint i,j;

	for (i = 0; i < n; i++) {
		ITI_real temp = fabs(*x[i]);
		if (temp > 1.0) {
			colsc[i] = temp;
			for (j = 0; j < m; j++)
				jac[i*m + j] *= temp;
		}
		else
			colsc[i] = 1.0;
	}
}

void scaleJacCols_DP(ITI_BlockData* pBd, ITI_DPBlockData* bdBD, ITI_uint n, ITI_uint nDAE)
{
	ITI_uint i,j,k;
	ITI_real temp;

	for (i = 0, k = 0; i < nDAE; i++) {
		if (bdBD->M[i] < nDAE) {
			temp = fabs(pBd->mv[i]);
			if (temp > 1.0) {
				pBd->colsc[k] = temp;
				for (j = 0; j < n; j++)
					pBd->jac[k*n + j] *= temp;
			}
			else
				pBd->colsc[k] = 1.0;
			k++;
		}
	}
}

void scaleJacRows(ITI_real* jac, ITI_real* res, ITI_real* rowsc, ITI_uint m, ITI_uint n)
{
	ITI_uint i,j;
	ITI_real test;

	for (i = 0; i < m; i++) {
		ITI_real temp = fabs(jac[i]);
		for (j = 1; j < n; j++) {
			test = fabs(jac[j*m + i]);
			if (test > temp)
				temp = test;
		}
		if (temp > 0.) {
			if (temp < DBL_MIN)
				temp = DBL_MIN;
			rowsc[i] = 1.0/temp;
			res[i] *= rowsc[i];
			for (j = 0; j < n; j++)
				jac[j*m + i] *= rowsc[i];
		}
		else
			rowsc[i] = 1.0;
	}
}

static void CalcM(ITI_BlockData* pBd, ITI_DPBlockData* pDPbd, ITI_uint nODE, ITI_uint nDAE)
{
#define JAC(_i,_j)\
pBd->sjac[nDAE*_i+_j]

#define JACLOC(_i,_j)\
pBd->sjactemp[nDAE*_i+_j]

#define PERMVECCOL(_i)\
pBd->permVecCol[_i]

#define M(_i)\
pDPbd->M[_i]

	ITI_uint i,j, k;

	for(i=0; i<nDAE-nODE; ++i) {
		for(j=0; j<nDAE; ++j) {
			JACLOC(i,j) = JAC(i,j);
		}
	}

	for(i=0; i<nDAE; ++i)
		PERMVECCOL(i) = i;

	for(i=0; i<nDAE-nODE; ++i) {
		ITI_uint uMax = i;
		for(j=i+1; j<nDAE; ++j) {
			if(fabs(JACLOC(i,PERMVECCOL(j))) > fabs(JACLOC(i,PERMVECCOL(uMax))))
				uMax = j;
		}
		if(uMax != i) {
			j = PERMVECCOL(i);
			PERMVECCOL(i) = PERMVECCOL(uMax);
			PERMVECCOL(uMax) = j;
		}
		if(JACLOC(i,PERMVECCOL(i)) != 0.0) {
			for(k=i+1; k<nDAE; ++k) {
				for(j=i+1; j<nDAE-nODE; ++j)
					JACLOC(j,PERMVECCOL(k)) -= (JACLOC(i,PERMVECCOL(k)) * JACLOC(j,PERMVECCOL(i)) / JACLOC(i,PERMVECCOL(i)));
			}
		}
		M(PERMVECCOL(i)) = PERMVECCOL(i);
	}

	for(i=nDAE-nODE; i<nDAE; ++i) {
		M(PERMVECCOL(i)) = nODE + i;
		M(nODE + i) = PERMVECCOL(i);
	}

	pDPbd->MCP=0;
	pDPbd->MC=1;

#undef JAC
#undef JACLOC
#undef PERMVECCOL
#undef M
} 

static void CheckM(ITI_BlockData* pBd, ITI_DPBlockData* pDPbd, ITI_uint nODE, ITI_uint nDAE)
{
#define JAC(_i,_j)\
pBd->sjac[nDAE*_i+_j]

#define JACLOC(_i,_j)\
pBd->sjactemp[nDAE*_i+_j]

#define PERMVECCOL(_i)\
pBd->permVecCol[_i]

#define M(_i)\
pDPbd->M[_i]

	ITI_uint i,j, k;

	 
	pDPbd->MCP=0;

	for(i=0; i<nDAE-nODE; ++i) {
		for(j=0; j<nDAE; ++j) {
			JACLOC(i,j) = JAC(i,j);
		}
	}

	for(i=0; i<nDAE; ++i)
		PERMVECCOL(i) = i;

	for(i=0; i<nDAE-nODE; ++i) {
		ITI_real MaxColFac = 1;
		ITI_uint uMax = i;
		if(M(PERMVECCOL(uMax)) != PERMVECCOL(uMax))
			MaxColFac = 0.99;
		for(j=i+1; j<nDAE; ++j) {
			ITI_real ActColFac = 1;
			if(M(PERMVECCOL(j)) != PERMVECCOL(j))
				ActColFac = 0.99;
			if(ActColFac*fabs(JACLOC(i,PERMVECCOL(j))) > MaxColFac*fabs(JACLOC(i,PERMVECCOL(uMax)))) {
				uMax = j;
				MaxColFac = ActColFac;
			}
		}
		if(uMax != i) {
			j = PERMVECCOL(i);
			PERMVECCOL(i) = PERMVECCOL(uMax);
			PERMVECCOL(uMax) = j;
		}
		if(JACLOC(i,PERMVECCOL(i)) != 0.0) {
			for(k=i+1; k<nDAE; ++k) {
				for(j=i+1; j<nDAE-nODE; ++j)
					JACLOC(j,PERMVECCOL(k)) -= (JACLOC(i,PERMVECCOL(k)) * JACLOC(j,PERMVECCOL(i)) / JACLOC(i,PERMVECCOL(i)));
			}
		}
		if(M(PERMVECCOL(i)) != PERMVECCOL(i)) {
			pDPbd->MCP=1;
			break;
		}
	}

#undef JAC
#undef JACLOC
#undef PERMVECCOL
#undef M
} 

ITI_int Trace(ITI_ushort traceOn, ITI_SolverInfo* sInfo, ITI_char* timeStr,
					ITI_char* timeValStr, ITI_char* envStr, ITI_uint n,
					ITI_ushort arg1IsString, ...)
{
	if (traceOn){
		#define ARG_BUFFER_SIZE 100
		ITI_uint j = 0;
		ITI_uint i = 0;
		ITI_uint lenArg = 0;
		ITI_uint msgMarker = 0;
		static ITI_char msg[ITI_TRACE_STRING_SIZE];
		ITI_char time[100];
		ITI_char* arg1 = 0;
		ITI_char* arg = 0;

		const ITI_ushort normal = 0;
		const ITI_ushort startFmt = 1;
		ITI_ushort state = normal;

		va_list marker;
		va_start(marker, arg1IsString);

		strcpy(time, timeStr);
		strcat(time, " ");
		strcat(time, timeValStr);
		strcat(time, "s: ");
		strcpy(msg, time);

		strcat(msg, envStr);
		msgMarker = (ITI_uint)(strlen(time) + strlen(envStr));

		if (arg1IsString){
			ITI_uint len1 = 0;
			ITI_ushort assCond = 0;
			arg1 = va_arg(marker, ITI_char*);
			len1 = (ITI_uint)strlen(arg1);

			assCond = len1 < ITI_TRACE_STRING_SIZE?1:0;
			assertFunction(assCond,
						"Trace: Size of 1. argument is too big! ", sInfo);

			if (assCond){
				ITI_uint fmtNumber = 0;
				ITI_uint foundFmt = 0;
				for (i = 0; i < len1; i++){
					char c = arg1[i];
					switch (c){
						case '%' :
							if (state == startFmt){
								msg[msgMarker] = c;
								msgMarker++;
							}
							else
								state = startFmt;
							break;
						default :
							if (state == startFmt){
								int temp = atoi(&c);
								if (temp > 0){
									fmtNumber = temp;
									foundFmt = 1;
								}

								if (temp <= 0 || i+1 == len1){
									if (fmtNumber > 0){
										assCond = fmtNumber < n?1:0;
										assertFunction(assCond,
											"Trace: Argument number not valid! ", sInfo);
										if (assCond){
											va_start(marker, arg1IsString);
											va_arg(marker, ITI_char*);
											for (j = 0; j < fmtNumber; j++){
												arg = va_arg(marker, ITI_char*);
											}
											lenArg = (ITI_uint)strlen(arg);

											if (lenArg < ARG_BUFFER_SIZE){
												for (j = 0; j < lenArg; j++){
													msg[msgMarker] = arg[j];
													msgMarker++;
												}
											}
										}
									}

									if (temp == 0 && i+1 <= len1){
										msg[msgMarker] = c;
										msgMarker++;
									}

									state = normal;
									fmtNumber = 0;
								}
							}
							else {
								msg[msgMarker] = c;
								msgMarker++;
							}
							break;
					}
				}

				if (!foundFmt){
					va_start(marker, arg1IsString);
					va_arg(marker, ITI_char*);
					for (i = 1; i < n; i++){
						arg = va_arg(marker, ITI_char*);
						lenArg = (ITI_uint)strlen(arg);
						if (lenArg < ARG_BUFFER_SIZE){
							for (j = 0; j < lenArg; j++){
								msg[msgMarker] = arg[j];
								msgMarker++;
							}
						}
					}
				}
			}
		}
		else {
			for (i = 0; i < n; i++){
				arg = va_arg(marker, ITI_char*);
				lenArg = (ITI_uint)strlen(arg);
				if (lenArg+1 < ARG_BUFFER_SIZE){
					msg[msgMarker] = ' ';
					msgMarker++;
					for (j = 0; j < lenArg; j++){
						msg[msgMarker] = arg[j];
						msgMarker++;
					}
				}
			}
		}

		va_end(marker);

		msg[msgMarker] = '\0';
		traceFunction(msg, sInfo);
		#undef ARG_BUFFER_SIZE
	}
	return 1;
}

void InitWorkMemory(ITI_WorkMemory* pWorkMem, ITI_int inEq_n, ITI_int inEq_n_Min_m,
						ITI_int inEq_n_Mul_n_Min_m, ITI_int inEq_35_Mul_n_Min_m_Plus_32, ITI_AllocateMemory allocateMemory)
{
	if (!pWorkMem)
		return;

	ITI_HandleAllocMemory

	pWorkMem->dWork = 0;
	pWorkMem->ker = 0;
	pWorkMem->kerCopy = 0;
	pWorkMem->lPermVecCol = 0;
	pWorkMem->vecCopy = 0;

	if (inEq_n > 0)
		pWorkMem->vecCopy = (ITI_real*)allocateMemory(inEq_n, sizeof(ITI_real));
	if (inEq_n_Min_m > 0)
		pWorkMem->lPermVecCol = (ITI_int*)allocateMemory(inEq_n_Min_m, sizeof(ITI_int));
	if (inEq_n_Mul_n_Min_m > 0) {
		pWorkMem->ker = (ITI_real*)allocateMemory(inEq_n_Mul_n_Min_m, sizeof(ITI_real));
		pWorkMem->kerCopy = (ITI_real*)allocateMemory(inEq_n_Mul_n_Min_m, sizeof(ITI_real));
	}
	if (inEq_35_Mul_n_Min_m_Plus_32 > 0)
		pWorkMem->dWork = (ITI_real*)allocateMemory(inEq_35_Mul_n_Min_m_Plus_32, sizeof(ITI_real));
}

void FreeWorkMemory(ITI_WorkMemory* pWorkMem, ITI_FreeMemory freeMemory)
{
	if (!pWorkMem)
		return;

	ITI_HandleFreeMemory

	if (pWorkMem->dWork)
		freeMemory(pWorkMem->dWork);
	if (pWorkMem->ker)
		freeMemory(pWorkMem->ker);
	if (pWorkMem->kerCopy)
		freeMemory(pWorkMem->kerCopy);
	if (pWorkMem->lPermVecCol)
		freeMemory(pWorkMem->lPermVecCol);
	if (pWorkMem->vecCopy)
		freeMemory(pWorkMem->vecCopy);
}

void FreeCompositeData(ITI_CompositeData* data, ITI_FreeMemory freeMemory)
{
	if (!data)
		return;

	ITI_HandleFreeMemory

	freeMemory(data->intData); data->intData = NULL;
	freeMemory(data->realData); data->realData = NULL;
	freeMemory(data->strData); data->strData = NULL;
	freeMemory(data->strSize); data->strSize = NULL;
}

ITI_uint GetIncSize(ITI_uint* DPBlockSizes, ITI_uint iDPB)
{
	ITI_uint i, cnt=0;
	for (i = 0; i < iDPB; i++)
	{
		cnt += DPBlockSizes[2*i] + DPBlockSizes[2*i+1];
	}
	return cnt;
}

void InitDPBlockData(ITI_DPBlockData* iDPbd, ITI_uint** stateInc, ITI_uint* DPBlockSizes, ITI_uint iDPB, ITI_AllocateMemory allocateMemory)
{
	ITI_uint i;
	ITI_uint cnt = GetIncSize(DPBlockSizes, iDPB);

	ITI_HandleAllocMemory

	if (cnt > 0)
		*stateInc = (ITI_uint*)allocateMemory(cnt, sizeof(ITI_uint));
	else
		*stateInc = NULL;
	
	cnt=0;

	for (i = 0; i < iDPB; i++)
	{
		iDPbd[i].M=&((*stateInc)[cnt]);
		iDPbd[i].Vdot=(ITI_real*)allocateMemory(DPBlockSizes[2*i+1], sizeof(ITI_real));

		cnt+=DPBlockSizes[2*i] + DPBlockSizes[2*i+1];
	}

	SetDPBlockData(iDPbd, DPBlockSizes, iDPB);
}

void SetDPBlockData(ITI_DPBlockData* iDPbd, ITI_uint* DPBlockSizes, ITI_uint iDPB)
{
	ITI_uint i,j;

	for (i = 0; i < iDPB; i++)
	{
		iDPbd[i].MC = 0;
		iDPbd[i].MCP = 1;
		for(j=0;j<DPBlockSizes[2*i];j++)
		{
			iDPbd[i].M[j]=DPBlockSizes[2*i+1] + j;
			iDPbd[i].M[j+DPBlockSizes[2*i+1]] = j;
		}
		for(j=DPBlockSizes[2*i];j<DPBlockSizes[2*i+1];j++)
		{
			iDPbd[i].M[j] = j;
		}
	}
}

void InitDataArrays(ITI_PartitionVar* pData, ITI_uint size, ITI_ArrayData* arrData, ITI_AllocateMemory allocateMemory)
{
	if (!pData)
		return;

	ITI_HandleAllocMemory

		if (size > 0)
			pData->arrays = (ITI_Array*)allocateMemory(size, sizeof(ITI_Array));
		else {
			pData->arrays = NULL;
			return;
		}

	InitDataArrays2(pData->arrays, size, arrData, allocateMemory);
}

void InitDataArrays2(ITI_Array* arrays, ITI_uint size, ITI_ArrayData* arrData, ITI_AllocateMemory allocateMemory)
{
	ITI_uint i;
	if (!arrays)
		return;

	ITI_HandleAllocMemory

	for (i = 0; i < size; i++) {
		switch (arrData[i].memType) {
			case REAL_TYPE:
				if (arrData[i].nValues > 0)
					arrays[i].realValues = (ITI_real*)allocateMemory(arrData[i].nValues, sizeof(ITI_real));
				else
					arrays[i].realValues = NULL;
				break;
			case INT_TYPE:
				if (arrData[i].nValues > 0)
					arrays[i].intValues = (ITI_int*)allocateMemory(arrData[i].nValues, sizeof(ITI_int));
				else
					arrays[i].intValues = NULL;
				break;
			case STRING_TYPE:
			case STRING_PTR_TYPE:
				if (arrData[i].nValues > 0)
					arrays[i].charValues = (ITI_char**)allocateMemory(arrData[i].nValues, sizeof(ITI_char*));
				else
					arrays[i].charValues = NULL;
				break;
			default:
				break;
		}
		arrays[i].nDims = arrData[i].nDims;
		arrays[i].dims = (ITI_int*)allocateMemory(max(arrays[i].nDims, 1), sizeof(ITI_int));
		arrays[i].memType = arrData[i].memType;
	}
}

void ResetDataArrays(ITI_PartitionVar* pData, ITI_uint size, ITI_ArrayData* arrData)
{
	ITI_uint i;
	ITI_Array* arrays;

	if (!pData)
		return;
	arrays = pData->arrays;

	if (!arrays)
		return;

	for (i = 0; i < size; i++){
		switch (arrData[i].memType){
			case REAL_TYPE :
				memset((void*)arrays[i].realValues, 0, arrData[i].nValues*sizeof(ITI_real));
				break;
			case INT_TYPE :
				memset((void*)arrays[i].intValues, 0, arrData[i].nValues*sizeof(ITI_int));
				break;
			case STRING_TYPE :
			case STRING_PTR_TYPE:
				memset((void*)arrays[i].charValues, 0, arrData[i].nValues*sizeof(ITI_char*));
				break;
			default:
				break;
		}
	}
}

void FreeDataArrays(ITI_PartitionVar* pData, ITI_ModelData* modelData, ITI_uint size, ITI_FreeMemory freeMemory)
{
	if (!pData || !modelData)
		return;
	FreeDataArrays2(&modelData->currMem, pData->arrays, size, freeMemory);
	pData->arrays = NULL;
}

void FreeDataArrays2(ITI_MemoryObject* currMem, ITI_Array* arrays, ITI_uint size, ITI_FreeMemory freeMemory)
{
	ITI_uint i;
	if (!arrays)
		return;

	ITI_HandleFreeMemory

	for (i = 0; i < size; i++){
		ITI_uint isGlobalArray = 1;
		switch (arrays[i].memType){
			case REAL_TYPE :
				if (IsInMemoryBlock((ITI_char*)arrays[i].realValues, currMem, REAL_TYPE))
					isGlobalArray = 0;
				else
					freeMemory(arrays[i].realValues);
				break;
			case INT_TYPE :
				if (IsInMemoryBlock((ITI_char*)arrays[i].intValues, currMem, INT_TYPE))
					isGlobalArray = 0;
				else
					freeMemory(arrays[i].intValues);
				break;
			case STRING_TYPE :
			case STRING_PTR_TYPE:
				if (IsInMemoryBlock((ITI_char*)arrays[i].charValues, currMem, STRING_TYPE))
					isGlobalArray = 0;
				else
					freeMemory(arrays[i].charValues);
				break;
			default:
				break;
		}
		if (isGlobalArray)
			freeMemory(arrays[i].dims);
	}
	freeMemory(arrays);
}

void FreeDPBlockData(ITI_DPBlockData* iDPbd, ITI_uint** stateInc, ITI_uint iDPB, ITI_FreeMemory freeMemory)
{
	ITI_uint i;

	ITI_HandleFreeMemory

	freeMemory(*stateInc);
	for (i = 0; i < iDPB; i++)
	{
		freeMemory(iDPbd[i].Vdot);
	}
}

ITI_BlockDataVTable g_VTable = {
	&ErrorExceedsBorder,
	&ErrorInitialBracketNotFound,
	&ErrorLambdaMin,
	&ErrorMaxIter,
	&ErrorResidualImage,
	&WarningBelowMin,
	&WarningBelowMinDamping,
	&WarningBelowMinDamping2,
	&WarningExceedsMax,
	&WarningExceedsMaxDamping,
	&WarningExceedsMaxDamping2,
	&WarningReducingDampFac,
	&WarningResidualImage,
	&SetAnalysisTypeDetail
};

void InitBlockData(ITI_BlockData* ibd, ITI_int numBlocks, ITI_BlockSizes *blockSizes, ITI_int *numJacCols, ITI_uint* DPBlockSizes, ITI_AllocateMemory allocateMemory)
{
	ITI_int i, k;
	ITI_uint cnt = 0;

	ITI_HandleAllocMemory

	for (k = 0; k < numBlocks; k++) {
		ITI_uint max_ires_iDAE;
		ITI_int n_minus_m;

		ibd[k].vTable = &g_VTable;

		if (blockSizes[k].nrDPBlock < 0) {
			ibd[k].nRes = (ITI_uint)(blockSizes[k].ires);
			ibd[k].nDAE = (ITI_uint)(blockSizes[k].iDAE);
			ibd[k].sjac = NULL;
			ibd[k].sjactemp = NULL;
			ibd[k].permVecCol = NULL;
			ibd[k].v = NULL;
			ibd[k].mv = NULL;
		} else {
			ITI_uint nODE = DPBlockSizes[2 * blockSizes[k].nrDPBlock];
			ibd[k].nDAE = DPBlockSizes[2 * blockSizes[k].nrDPBlock + 1];
			ibd[k].nRes = ibd[k].nDAE - nODE;
			ibd[k].sjac = (ITI_real *)allocateMemory(ibd[k].nRes * ibd[k].nDAE, sizeof(ITI_real));
			ibd[k].sjactemp = (ITI_real *)allocateMemory(ibd[k].nRes * ibd[k].nDAE, sizeof(ITI_real));
			ibd[k].permVecCol = (ITI_uint *)allocateMemory(ibd[k].nDAE, sizeof(ITI_uint));
			ibd[k].v = (ITI_real *)allocateMemory(nODE + ibd[k].nDAE, sizeof(ITI_real));
			ibd[k].mv = (ITI_real *)allocateMemory(ibd[k].nDAE, sizeof(ITI_real));
		}
		max_ires_iDAE = max(ibd[k].nRes, ibd[k].nDAE);

		ibd[k].x = (ITI_real *)allocateMemory(ibd[k].nDAE, sizeof(ITI_real));
		ibd[k].xorg = (ITI_real *)allocateMemory(ibd[k].nDAE, sizeof(ITI_real));
		ibd[k].xstart = (ITI_real *)allocateMemory(ibd[k].nDAE, sizeof(ITI_real));
		ibd[k].xjac = (ITI_real *)allocateMemory(ibd[k].nDAE, sizeof(ITI_real));
		ibd[k].delta = (ITI_real *)allocateMemory(ibd[k].nDAE, sizeof(ITI_real));
		ibd[k].minVal = (ITI_real *)allocateMemory(ibd[k].nDAE, sizeof(ITI_real));
		ibd[k].maxVal = (ITI_real *)allocateMemory(ibd[k].nDAE, sizeof(ITI_real));
		ibd[k].nomVal = (ITI_real *)allocateMemory(ibd[k].nDAE, sizeof(ITI_real));
		ibd[k].considerMin = (ITI_ushort *)allocateMemory(ibd[k].nDAE, sizeof(ITI_ushort));
		ibd[k].considerMax = (ITI_ushort *)allocateMemory(ibd[k].nDAE, sizeof(ITI_ushort));
		ibd[k].name = (ITI_char **)allocateMemory(ibd[k].nDAE, sizeof(ITI_char *));
		ibd[k].iViolLimit = (ITI_uint *)allocateMemory(ibd[k].nDAE, sizeof(ITI_uint));

		ibd[k].jac = (ITI_real *)allocateMemory(ibd[k].nRes * ibd[k].nDAE, sizeof(ITI_real));
		ibd[k].res = (ITI_real *)allocateMemory(ibd[k].nRes, sizeof(ITI_real));
		ibd[k].tmpres = (ITI_real *)allocateMemory(ibd[k].nRes, sizeof(ITI_real));
		ibd[k].s = (ITI_real *)allocateMemory(max_ires_iDAE, sizeof(ITI_real));
		ibd[k].ipiv = (ITI_int *)allocateMemory(ibd[k].nRes, sizeof(ITI_int));
		ibd[k].colpiv = (ITI_int *)allocateMemory(ibd[k].nRes, sizeof(ITI_int));
		ibd[k].tol = (ITI_real *)allocateMemory(ibd[k].nDAE, sizeof(ITI_real));
		ibd[k].dxbar = (ITI_real *)allocateMemory(max_ires_iDAE, sizeof(ITI_real));
		ibd[k].w = (ITI_real *)allocateMemory(ibd[k].nDAE, sizeof(ITI_real));
		ibd[k].colsc = (ITI_real *)allocateMemory(ibd[k].nDAE, sizeof(ITI_real));
		ibd[k].rowsc = (ITI_real *)allocateMemory(ibd[k].nRes, sizeof(ITI_real));

		ibd[k].nCol = numJacCols[cnt++];
		if (ibd[k].nCol == 0) {
			ibd[k].numJacCols = (ITI_int *)allocateMemory(1, sizeof(ITI_int));
			ibd[k].numJacCols[0] = -1;
		} else {
			ibd[k].numJacCols = (ITI_int *)allocateMemory(ibd[k].nCol, sizeof(ITI_int));
			for (i = 0; i < ibd[k].nCol; i++, cnt++)
				ibd[k].numJacCols[i] = numJacCols[cnt];
		}

		ibd[k].firstTime = 1;
		ibd[k].justOnceMore = 0;
		ibd[k].corrStep = 0;
		ibd[k].nViolLimit = 0;
		ibd[k].lambda_min = 1e-008;
		ibd[k].zfSwitch = 0;
		ibd[k].undamped = 1;

		n_minus_m = ibd[k].nDAE - ibd[k].nRes;
		if (n_minus_m < 0)
			n_minus_m = 0;
		ibd[k].workMem = (ITI_WorkMemory *)allocateMemory(1, sizeof(ITI_WorkMemory));
		InitWorkMemory(ibd[k].workMem, ibd[k].nDAE, n_minus_m, ibd[k].nDAE * n_minus_m, 35 * n_minus_m + 32, allocateMemory);

		assert(sizeof(integer) == sizeof(ITI_int));
		assert(sizeof(doublereal) == sizeof(ITI_real));
		ibd[k].llsData.a = ibd[k].jac;
		ibd[k].llsData.m = ibd[k].nRes;
		ibd[k].llsData.n = ibd[k].nDAE;
		ibd[k].llsData.ldb = max_ires_iDAE;
		lls_init(&ibd[k].llsData);
		ibd[k].llsData.work = (ITI_real *)allocateMemory(ibd[k].llsData.lwork, sizeof(ITI_real));
		ibd[k].llsData.jpvt = (ITI_int *)allocateMemory(ibd[k].nDAE, sizeof(ITI_int));

		ibd[k].xsave = (ITI_real *)allocateMemory(ibd[k].nDAE, sizeof(ITI_real));
		ibd[k].zintsave = (ITI_int *)allocateMemory(blockSizes[k].iHybrid_Z_Int, sizeof(ITI_int));
		ibd[k].zrealsave = (ITI_real *)allocateMemory(blockSizes[k].iHybrid_Z_Real, sizeof(ITI_real));
		ibd[k].zstrsave = (ITI_char **)allocateMemory(blockSizes[k].iHybrid_Z_Str, sizeof(ITI_char *));
		ibd[k].zfsave = (ITI_real *)allocateMemory(blockSizes[k].iHybrid_Zf, sizeof(ITI_real));

		ibd[k].isNonlinear = blockSizes[k].isNonlinear;

		ibd[k].resCalls = 0;
		ibd[k].jacCalls = 0;
	}
}

void FreeBlockData(ITI_BlockData* ibd, ITI_int numBlocks, ITI_FreeMemory freeMemory)
{
	ITI_int k;

	ITI_HandleFreeMemory

	for (k = 0; k < numBlocks; k++) {
		freeMemory(ibd[k].x);
		freeMemory(ibd[k].minVal);
		freeMemory(ibd[k].maxVal);
		freeMemory(ibd[k].nomVal);
		freeMemory(ibd[k].considerMin);
		freeMemory(ibd[k].considerMax);
		freeMemory(ibd[k].iViolLimit);
		freeMemory(ibd[k].jac);
		freeMemory(ibd[k].res);
		freeMemory(ibd[k].tmpres);
		freeMemory(ibd[k].s);
		freeMemory(ibd[k].ipiv);
		freeMemory(ibd[k].colpiv);
		freeMemory(ibd[k].tol);
		freeMemory(ibd[k].delta);
		freeMemory(ibd[k].xorg);
		freeMemory(ibd[k].xstart);
		freeMemory(ibd[k].xsave);
		freeMemory(ibd[k].zfsave);
		freeMemory(ibd[k].zintsave);
		freeMemory(ibd[k].zrealsave);
		freeMemory(ibd[k].zstrsave);
		freeMemory(ibd[k].dxbar);
		freeMemory(ibd[k].w);
		freeMemory(ibd[k].xjac);
		freeMemory(ibd[k].colsc);
		freeMemory(ibd[k].rowsc);
		freeMemory(ibd[k].numJacCols);

		freeMemory(ibd[k].name);

		freeMemory(ibd[k].sjac);
		freeMemory(ibd[k].sjactemp);
		freeMemory(ibd[k].permVecCol);
		freeMemory(ibd[k].v);
		freeMemory(ibd[k].mv);

		if (ibd[k].workMem) {
			FreeWorkMemory(ibd[k].workMem, freeMemory);
			freeMemory(ibd[k].workMem);
		}

		freeMemory(ibd[k].llsData.work);
		freeMemory(ibd[k].llsData.jpvt);
	}
}

void SetBlockSettings(ITI_uint numBlocks, ITI_BlockData *ibd, ITI_real gltol, ITI_int linSolv, ITI_uint ignoreLimits)
{
	ITI_uint i, k;

	for (k = 0; k < numBlocks; k++) {
		ibd[k].gltol = gltol;
		if (linSolv == -1) {
			ibd[k].autoLinSolv = 1;
			ibd[k].linSolv = 0;
		} else {
			ibd[k].autoLinSolv = 0;
			ibd[k].linSolv = linSolv;
		}
		ibd[k].ignoreLimits = ignoreLimits;
		for (i = 0; i < ibd[k].nDAE; i++) {
			if (ibd[k].ignoreLimits == 0 && (ibd[k].considerMin[i] || ibd[k].considerMax[i]))
				ibd[k].considerLimit = 1;
			else
				ibd[k].considerLimit = 0;
		}
	}
}

void ResetBlockData(ITI_uint numBlocks, ITI_BlockData *ibd, ITI_BlockSizes *blockSizes)
{
	ITI_uint k;
	for (k = 0; k < numBlocks; k++) {
		ITI_int i;
		for (i = 0; i < blockSizes[k].iHybrid_Zf; i++)
			ibd[k].zfsave[i] = 0.;
		ibd[k].resCalls = 0;
		ibd[k].jacCalls = 0;
	}
}

void InitHomMinMax(ITI_HomMinMax* hmm, ITI_int ihomx)
{
	ITI_int i;

	hmm->minVal = (double*)calloc(ihomx, sizeof(ITI_real));
	hmm->maxVal = (double*)calloc(ihomx, sizeof(ITI_real));
	hmm->considerMin = (ITI_ushort*)calloc(ihomx, sizeof(ITI_ushort));
	hmm->considerMax = (ITI_ushort*)calloc(ihomx, sizeof(ITI_ushort));
	hmm->name = (ITI_char**)calloc(ihomx, sizeof(ITI_char*));
	hmm->nomVal = (double*)calloc(ihomx, sizeof(ITI_real));
	hmm->considerLimit = 0;

	for (i = 0; i < ihomx; i++)
		hmm->name[i] = NULL;
}

void FreeHomMinMax(ITI_HomMinMax* hmm, ITI_int ihomx)
{
	free(hmm->minVal);
	free(hmm->maxVal);
	free(hmm->considerMin);
	free(hmm->considerMax);
	free(hmm->nomVal);
	free(hmm->name);
}

void InitStateMinMax(ITI_StateMinMax* smm, ITI_int dim)
{
	smm->nMin = 0;
	smm->nMax = 0;
	smm->minInd = (ITI_int*)calloc(dim, sizeof(ITI_int));
	smm->maxInd = (ITI_int*)calloc(dim, sizeof(ITI_int));
	smm->minVal = (double*)calloc(dim, sizeof(ITI_real));
	smm->maxVal = (double*)calloc(dim, sizeof(ITI_real));
}

void FreeStateMinMax(ITI_StateMinMax* smm)
{
	free(smm->minInd);
	free(smm->maxInd);
	free(smm->minVal);
	free(smm->maxVal);
}

#ifdef ITI_COMP_SIM
#define ITI_realVar *pPart->transient->v.realData
#else
#define ITI_realVar pPart->transient->v.realData
#endif

void FillStateMinMax(void* pData, ITI_VarAttributes* stateAttributes, ITI_int dim, ITI_real absTol)
{
	ITI_Partition* pPart = (ITI_Partition*)pData;
	ITI_StateMinMax* smm = pPart->transient->smm;

	ITI_int i;
	 
	smm->nMin=0;
	smm->nMax=0;
	for (i=0; i < dim; i++)
	{
		 
		if (stateAttributes[i].minIdx > -1)
		{
			smm->minInd[smm->nMin] = stateAttributes[i].stateIdx;
			if (stateAttributes[i].minNotReachedIdx > -1)
			{
				if(pPart->transient->v.intData[stateAttributes[i].minNotReachedIdx] > 0)
					smm->minVal[smm->nMin] = ITI_realVar[stateAttributes[i].minIdx];
				else
					smm->minVal[smm->nMin] = ITI_realVar[stateAttributes[i].minIdx] - absTol;
			}
			else
				smm->minVal[smm->nMin] = ITI_realVar[stateAttributes[i].minIdx] - absTol;

			smm->nMin++;
		}
		 
		if (stateAttributes[i].maxIdx > -1)
		{
			smm->maxInd[smm->nMax] = stateAttributes[i].stateIdx;
			if (stateAttributes[i].maxNotReachedIdx > -1)
			{
				if (pPart->transient->v.intData[stateAttributes[i].maxNotReachedIdx] > 0)
					smm->maxVal[smm->nMax] = ITI_realVar[stateAttributes[i].maxIdx];
				else
					smm->maxVal[smm->nMax] = ITI_realVar[stateAttributes[i].maxIdx] + absTol;
			}
			else
				smm->maxVal[smm->nMax] = ITI_realVar[stateAttributes[i].maxIdx] + absTol;
			smm->nMax++;
		}
	}
}

ITI_real _BuiltIn_PackShape(char* shapename)
{
	if (strcmp(shapename, "box")==0)
		return 101.0;
	else if (strcmp(shapename, "sphere")==0)
		return 102.0;
	else if (strcmp(shapename, "cylinder")==0)
		return 103.0;
	else if (strcmp(shapename, "cone")==0)
		return 104.0;
	else if (strcmp(shapename, "pipe")==0)
		return 105.0;
	else if (strcmp(shapename, "beam")==0)
		return 106.0;
	else if (strcmp(shapename, "wirebox")==0)
		return 107.0;
	else if (strcmp(shapename, "gearwheel")==0)
		return 108.0;
	else if (strcmp(shapename, "vector")==0)
		return 109.0;
	else if (strcmp(shapename, "pipecylinder")==0)
		return 110.0;
	else if (strcmp(shapename, "spring")==0)
		return 111.0;
	else if (strcmp(shapename, "tire")==0 || strcmp(shapename, "tyre")==0)
		return 112.0;
	else
		return 200.0+atoi(shapename);
}

ITI_real _BuiltIn_PackMaterial(ITI_real d1, ITI_real d2, ITI_real d3, ITI_real d4)
{
	ITI_int a, b, c, d, ires;
	ITI_real res;
	 
	a = (int) (d1*100 - 0.5);
	if (a < 0) a = 0;
	if (a > 99) a = 99;

	b = (int) (d2*100 - 0.5);
	if (b < 0) b = 0;
	if (b > 99) b = 99;

	c = (int) (d3*100 - 0.5);
	if (c < 0) c = 0;
	if (c > 99) c = 99;

	d = (int) (d4*10 - 0.5);
	if (d < 0) d = 0;
	if (d > 9) d = 9;
	 
	ires = ((((a * 100) + b) * 100) + c) * 10 + d;
	res = ires;
	return res;
}

void PrintSwitchingEntities(ITI_CompositeData* z, ITI_CompositeData* pre_z, ITI_real* zf, ITI_real* old_sign_zf, ITI_SolverInfo* sInfo, ITI_int intSize, ITI_int realSize, ITI_int stringSize, ITI_int zfSize)
{
	int i;
	for (i = 0; i < intSize; i++)
	{
		if(z->intData[i] != pre_z->intData[i])
		{
			char msg[255];
			snprintf(msg, 255, "Event Iteration: z_int[%d] = %d\tpre(z_int) = %d\n", i, z->intData[i], pre_z->intData[i]);
			traceWarning(msg, sInfo);
		}
	}
	for (i = 0; i < realSize; i++)
	{
		if(z->realData[i] != pre_z->realData[i])
		{
			char msg[255];
#ifdef ITI_COMP_SIM
			snprintf(msg, 255, "Event Iteration: z_real[%d] = %.15f\tpre(z_real) = %.15f\n", i, *(z->realData[i]), *(pre_z->realData[i]));
#else
			snprintf(msg, 255, "Event Iteration: z_real[%d] = %.15f\tpre(z_real) = %.15f\n", i, z->realData[i], pre_z->realData[i]);
#endif
			traceWarning(msg, sInfo);
		}
	}
	 
	for (i = 0; i < zfSize; i++)
	{
		if(old_sign_zf[i] != sign(zf[i]))
		{
			ITI_char msg[255];
			snprintf(msg, 255, "Event Iteration: sign(zf[%d]) = %g\tsign(old_zf) = %g\n", i, sign(zf[i]), old_sign_zf[i]);
			traceWarning(msg, sInfo);
		}
	}
}

static void CalcBlockJac(ITI_BlockData* pBd, ITI_SolverInfo* pInfo)
{
	ITI_uint m = pBd->nRes;
	ITI_uint n = pBd->nDAE;
	ITI_uint i;

	(*pBd->vTable->SetAnalysisTypeDetail)(pInfo, "jacobian");
	memset((void *) pBd->s, 0, n*sizeof(ITI_real));
	if (pBd->iCol == -1)
	{
		for (i = 0; i < m; i++)
			pBd->tmpres[i] = pBd->res[i];
	}
	else if (pBd->useNumJac == 0)
	{
		for (i = 0; i < m; i++)
			pBd->jac[m * pBd->numJacCols[pBd->iCol] + i] = (pBd->res[i] - pBd->tmpres[i]) / pBd->d;
	}
	else
	{
		for (i = 0; i < m; i++)
			pBd->jac[m * pBd->iCol + i] = (pBd->res[i] - pBd->tmpres[i]) / pBd->d;
	}
	pBd->iCol++;
	if (pBd->useNumJac == 0 && pBd->iCol < pBd->nCol)
	{
		pBd->d = pBd->delta[pBd->numJacCols[pBd->iCol]];
		pBd->s[pBd->numJacCols[pBd->iCol]] = - pBd->d;
	}
	else if (pBd->useNumJac == 1 && (ITI_uint)pBd->iCol < pBd->nDAE)
	{
		pBd->d = pBd->delta[pBd->iCol];
		pBd->s[pBd->iCol] = - pBd->d;
	}
	else
	{
		pBd->mode = 1;
		(*pBd->vTable->SetAnalysisTypeDetail)(pInfo, pBd->strAnalysisTypeDetail);
	}
}

static void CalcBlockJac_DP(ITI_BlockData* pBd, ITI_SolverInfo* pInfo)
{
	ITI_uint n = pBd->nRes;
	ITI_uint nDAE = pBd->nDAE;
	ITI_uint i;

	(*pBd->vTable->SetAnalysisTypeDetail)(pInfo, "jacobian");
	if(pBd->iCol == -1)
	{
		for (i = 0; i < n; i++)
			pBd->tmpres[i] = pBd->res[i];
	}
	else
	{
		pBd->mv[pBd->numJacCols[pBd->iCol]] = pBd->d;
		for (i = 0; i < n; i++)
			pBd->sjac[nDAE * i + pBd->numJacCols[pBd->iCol]] = (pBd->res[i] - pBd->tmpres[i]) / pBd->delta[pBd->numJacCols[pBd->iCol]];
	}
	pBd->iCol++;
	if (pBd->iCol < pBd->nCol)
	{
		pBd->d = pBd->mv[pBd->numJacCols[pBd->iCol]];
		pBd->mv[pBd->numJacCols[pBd->iCol]] += pBd->delta[pBd->numJacCols[pBd->iCol]];
	}
	else
	{
		pBd->mode = 1;
		(*pBd->vTable->SetAnalysisTypeDetail)(pInfo, pBd->strAnalysisTypeDetail);
	}
}

static void GetNamesStr(ITI_BlockData* pBd, ITI_char* names, ITI_uint n)
{
	ITI_uint i;
	size_t shift = 0;
	for (i = 0; i < n; i++)
	{
		size_t len = strlen(pBd->name[i]);
		if (shift+len+3 >= 1000)
			break;
		strcat(names, pBd->name[i]);
		if (i < n-1){
			strcat(names, ", ");
			shift += 2;
		}
		shift += len;
	}
}

static void ErrorExceedsBorder(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i)
{
	char msg[400];
	snprintf(msg, 400, "Step %i: %s exceeds a border.", pBd->corrStep + 1, pBd->name[i]);
	traceWarning(msg, pInfo);
	pBd->error = 1;
	pBd->repeat = 0;
}

static void ErrorInitialBracketNotFound(ITI_BlockData* pBd, ITI_SolverInfo* pInfo)
{
	char msg[1200];
	snprintf(msg, 1200, "Problem during solving equation for %s.\nAn initial bracket for the root of equation could not be found.", pBd->name[0]);
	traceWarning(msg, pInfo);
	pBd->error = 1;
	pBd->repeat = 0;
}

static void ErrorLambdaMin(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint n)
{
	ITI_char msg[1200];
	if (n > 1) {
		ITI_char names[1000] = "";
		GetNamesStr(pBd, names, n);
		snprintf(msg, 1200, "Problem during solving system of equations for %s.\nAfter %i steps lambda is too small (||S|| = %.17g).", names, pBd->corrStep + 1, pBd->normdx);
	}
	else
		snprintf(msg, 1200, "Problem during solving equation for %s.\nAfter %i steps lambda is too small lambda (S = %.17g).", pBd->name[0], pBd->corrStep + 1, pBd->s[0]);
	traceWarning(msg, pInfo);
	pBd->error = 1;
	pBd->repeat = 0;
}

static void ErrorMaxIter(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint n)
{
	ITI_char msg[1200];
	if (n > 1) {
		ITI_char names[1000] = "";
		GetNamesStr(pBd, names, n);
		snprintf(msg, 1200, "Problem during solving system of equations for %s.\nMore than %i steps.", names, pBd->maxiter);
	}
	else
		snprintf(msg, 1200, "Problem during solving system of equations for %s.\nMore than %i steps.", pBd->name[0], pBd->maxiter);
	traceWarning(msg, pInfo);
	pBd->error = 1;
	pBd->repeat = 0;
}

static void ErrorResidualImage(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint n)
{
	ITI_char msg[1200];
	if (n > 1) {
		ITI_char names[1000] = "";
		GetNamesStr(pBd, names, n);
		snprintf(msg, 1200, "Problem during solving system of equations for %s.\nAfter %i steps residual is not in the image of the Jacobian.", names, pBd->corrStep + 1);
	}
	else
		snprintf(msg, 1200, "Problem during solving equation for %s.\nAfter %i steps residual is not in the image of the Jacobian.", pBd->name[0], pBd->corrStep + 1);
	traceWarning(msg, pInfo);
	pBd->error = 1;
	pBd->repeat = 0;
}

static void WarningBelowMin(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i, ITI_uint j)
{
	char msg[500];
	snprintf(msg, 500, "The value %-.17g is below the minimum (%-.17g) of %s.", pBd->v[i], pBd->minVal[j], pBd->name[j]);
	traceWarning(msg, pInfo);
}

static void WarningBelowMinDamping(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i)
{
	char msg[500];
	snprintf(msg, 500, "Step %i: The value %-.17g is below the minimum (%-.17g) of %s (Damping factor: %-.17g).", pBd->corrStep+1, pBd->x[i]-pBd->s[i], pBd->minVal[i], pBd->name[i], 0.5*((pBd->x[i] - pBd->minVal[i]) / pBd->s[i]));
	traceWarning(msg, pInfo);
}

static void WarningBelowMinDamping2(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i, ITI_uint k)
{
	char msg[500];
	snprintf(msg, 500, "Step %i: The value %-.17g is below the minimum (%-.17g) of %s (Damping factor: %-.17g).", pBd->corrStep + 1, pBd->mv[i] - pBd->s[k], pBd->minVal[i], pBd->name[i], 0.5*((pBd->mv[i] - pBd->minVal[i]) / pBd->s[k]));
	traceWarning(msg, pInfo);
}

static void WarningExceedsMax(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i, ITI_uint j)
{
	char msg[500];
	snprintf(msg, 500, "The value %-.17g exceeds the maximum (%-.17g) of %s.", pBd->v[i], pBd->maxVal[j], pBd->name[j]);
	traceWarning(msg, pInfo);
}

static void WarningExceedsMaxDamping(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i)
{
	char msg[500];
	snprintf(msg, 500, "Step %i: The value %-.17g exceeds the maximum (%-.17g) of %s (Damping factor: %-.17g).", pBd->corrStep+1, pBd->x[i]-pBd->s[i], pBd->maxVal[i], pBd->name[i], 0.5*((pBd->x[i] - pBd->maxVal[i]) / pBd->s[i]));
	traceWarning(msg, pInfo);
}

static void WarningExceedsMaxDamping2(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i, ITI_uint k)
{
	char msg[500];
	snprintf(msg, 500, "Step %i: The value %-.17g exceeds the maximum (%-.17g) of %s (Damping factor: %-.17g).", pBd->corrStep + 1, pBd->mv[i] - pBd->s[k], pBd->maxVal[i], pBd->name[i], 0.5*((pBd->mv[i] - pBd->maxVal[i]) / pBd->s[k]));
	traceWarning(msg, pInfo);
}

static void WarningReducingDampFac(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i)
{
	char msg[400];
	snprintf(msg, 400, "Step %i: Reducing the damping factor to %-.17g because of %s.", pBd->corrStep+1, pBd->alpha, pBd->name[i]);
	traceWarning(msg, pInfo);
}

static void WarningResidualImage(ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint m, ITI_uint n, ITI_uint l)
{
	ITI_char msg[1200];
	ITI_char names[1000] = "";
	GetNamesStr(pBd, names, l);
	snprintf(msg, 1200, "Problem during solving system of equations for %s.\nStep %i: Residual is not in the image of the %u*%u-Jacobian: Equation %i", names, pBd->corrStep + 1, m, n, pInfo->iFailedEqu);
	traceWarning(msg, pInfo);
}

static void SetAnalysisTypeDetail(ITI_SolverInfo* pInfo, char* typeDetail)
{
	pInfo->strAnalysisTypeDetail = typeDetail;
}

void AllocAssertData(ITI_AssertData * pAssertData, size_t n, ITI_AllocateMemory allocateMemory)
{
	size_t i;
	ITI_HandleAllocMemory

	pAssertData->assertState1 = (ITI_uchar*)allocateMemory(n, sizeof(ITI_uchar));
	pAssertData->assertState2 = (ITI_uchar*)allocateMemory(n, sizeof(ITI_uchar));
	pAssertData->warnMsg = (ITI_char**)allocateMemory(n, sizeof(ITI_char*));
	pAssertData->condMsg = (ITI_char**)allocateMemory(n, sizeof(ITI_char*));
	pAssertData->n = n;

	for(i=0; i<pAssertData->n; i++)
	{
		pAssertData->warnMsg[i] = (ITI_char*)allocateMemory(ITI_TRACE_STRING_SIZE, sizeof(ITI_char*));
		pAssertData->condMsg[i] = (ITI_char*)allocateMemory(ITI_TRACE_STRING_SIZE, sizeof(ITI_char*));
	}

	InitAssertData(pAssertData);
}

void InitAssertData(ITI_AssertData * pAssertData)
{
	size_t i;
	for(i=0; i<pAssertData->n; i++)
	{
		pAssertData->assertState1[i] = (ITI_uchar)1;
		pAssertData->assertState2[i] = (ITI_uchar)1;
		*pAssertData->warnMsg[i] = '\0';
		*pAssertData->condMsg[i] = '\0';
	}
	pAssertData->assertStateR = pAssertData->assertState1;
	pAssertData->assertStateW = pAssertData->assertState2;
	pAssertData->bAssertStateChanged = ITI_false;

	pAssertData->bAssertError = ITI_false;
}

void FreeAssertData(ITI_AssertData * pAssertData, ITI_FreeMemory freeMemory)
{
	size_t i;
	ITI_HandleFreeMemory

	freeMemory(pAssertData->assertState1);
	freeMemory(pAssertData->assertState2);

	pAssertData->assertStateR = 0;
	pAssertData->assertStateW = 0;
	pAssertData->assertState1 = 0;
	pAssertData->assertState2 = 0;

	for(i=0; i<pAssertData->n; i++)
	{
		freeMemory(pAssertData->warnMsg[i]);
		freeMemory(pAssertData->condMsg[i]);
	}
	freeMemory(pAssertData->warnMsg);
	freeMemory(pAssertData->condMsg);
	pAssertData->warnMsg = 0;
	pAssertData->condMsg = 0;

	pAssertData->n = 0;
}

int AllocEventCounters(ITI_SolverStatistic* stat, size_t izf, size_t iz, ITI_AllocateMemory allocateMemory){
	ITI_HandleAllocMemory
		if (izf > 0)
			stat->zeroCrossingCount = (ITI_uint*)allocateMemory(izf, sizeof(ITI_uint));
		else
			stat->zeroCrossingCount = NULL;
	if (iz > 0)
		stat->discreteCount = (ITI_uint*)allocateMemory(iz, sizeof(ITI_uint));
	else
		stat->discreteCount = NULL;

	if(stat->zeroCrossingCount && stat->discreteCount){
		InitEventCounters(stat, izf, iz);
		return 1;
	}
	return 0;
}

void FreeEventCounters(ITI_SolverStatistic* stat, ITI_FreeMemory freeMemory){
	ITI_HandleFreeMemory
	freeMemory(stat->zeroCrossingCount);
	freeMemory(stat->discreteCount);
	stat->zeroCrossingCount = 0;
	stat->discreteCount = 0;
}

void InitEventCounters(ITI_SolverStatistic* stat, size_t izf, size_t iz){
	memset((void*)stat->zeroCrossingCount, 0, izf * sizeof(ITI_uint));
	memset((void*)stat->discreteCount, 0, iz * sizeof(ITI_uint));
}

void InitModelSizes(ITI_ModelSize* pSize)
{
	pSize->ix = 0;
	pSize->ibx = 0;
	pSize->ix_i = 0;
	pSize->ires_i = 0;
	pSize->ihomres = 0;
	pSize->iy_int = 0;
	pSize->iy_real = 0;
	pSize->iy_str = 0;
	pSize->ip_int = 0;
	pSize->ip_real = 0;
	pSize->ip_str = 0;
	pSize->ip_arr = 0;
	pSize->iu_int = 0;
	pSize->iu_real = 0;
	pSize->iu_str = 0;
	pSize->iz_int = 0;
	pSize->iz_real = 0;
	pSize->iz_str = 0;
	pSize->iv_int = 0;
	pSize->iv_real = 0;
	pSize->iv_str = 0;
	pSize->iclocksv_int = 0;
	pSize->iclocksv_real = 0;
	pSize->iclocksv_str = 0;
	pSize->i_inc = 0;
	pSize->izf = 0;
	pSize->ics = 0;
	pSize->isv = 0;
	pSize->ihcs = 0;
	pSize->idb = 0;
	pSize->iExtObj = 0;
	pSize->iarr = 0;
	pSize->iRec = 0;
	pSize->icset = 0;
	pSize->ipcset = 0;
	pSize->icnd = 0;
	pSize->iass = 0;
	pSize->ieb = 0;
	pSize->ide = 0;
	pSize->ivn = 0;

	pSize->numBlocks = 0;
	pSize->numStateAttr = 0;
	pSize->numInitStateAttr = 0;
	pSize->numRESBlock = 0;
	pSize->numXBlock = 0;

	pSize->iSimX_X = 0;
	pSize->iSimX_V = 0;
	pSize->iSimX_Z = 0;
	pSize->iSimX_BX = 0;
	pSize->iSimX_ClockSV = 0;

	pSize->iDPB = 0;
	pSize->iInEq_n = 0;
	pSize->iInEq_n_Min_m = 0;
	pSize->iInEq_n_Mul_n_Min_m = 0;
	pSize->iInEq_35_Mul_n_Min_m_Plus_32 = 0;

	pSize->bxind_lambda = 0;
	pSize->bxind_cdfirst = 0;
	pSize->bxind_homlast = 0;

	pSize->ipart = 0;
	pSize->iig = 0;
	pSize->iig_nodes = NULL;
	pSize->iig_edges = NULL;
	pSize->iig_children = NULL;
	pSize->iig_roots = NULL;
	pSize->iig_baseclocks = NULL;
	pSize->iig_solverclocks = NULL;
	pSize->iig_solverneeded = NULL;
	pSize->iig_paths = NULL;
	pSize->iig_steps = NULL;
}

ITI_int* SetIntSizes(ITI_AllocateMemory allocateMemory, ITI_int n, ...)
{
	ITI_int i;
	ITI_int* pIntArray;
	va_list argList;
	va_start(argList, n);

	pIntArray = (ITI_int*)allocateMemory(n, sizeof(ITI_int));
	for (i = 0; i<n; i++)
		pIntArray[i] = va_arg(argList, ITI_int);
	va_end(argList);
	return pIntArray;
}

int AllocZFData(ITI_PartitionVar* pData, ITI_zerofunctionData* zfData, char bComplete, ITI_AllocateMemory allocateMemory){
	ITI_HandleAllocMemory

	if (pData->size.izf > 0)
	{
		pData->zf = (ITI_real*)allocateMemory(pData->size.izf, sizeof(ITI_real));
		pData->cszf = (ITI_int*)allocateMemory(pData->size.izf, sizeof(ITI_int));
		pData->e1zf = (ITI_real*)allocateMemory(pData->size.izf, sizeof(ITI_real));
		pData->e2zf = (ITI_real*)allocateMemory(pData->size.izf, sizeof(ITI_real));
	}
	else
	{
		pData->zf = NULL;
		pData->cszf = NULL;
		pData->e1zf = NULL;
		pData->e2zf = NULL;
		pData->pre_zf = NULL;
		pData->oszf = NULL;
		pData->czf = NULL;
		pData->ezf = NULL;
		pData->relzf = NULL;
		pData->epszf = NULL;
		pData->pszf = NULL;
		pData->sczf = NULL;
#ifdef ITI_COMP_SIM
		pData->curve_zf = NULL;
#endif
		return 1;
	}

	if(bComplete){
		size_t i;
		pData->pre_zf = (ITI_real*)allocateMemory(pData->size.izf, sizeof(ITI_real));

		pData->pszf = (ITI_real**)allocateMemory(pData->size.izf, sizeof(ITI_real*));
		pData->oszf = (ITI_int*)allocateMemory(pData->size.izf, sizeof(ITI_int));

		pData->czf = (ITI_uchar*)allocateMemory(pData->size.izf, sizeof(ITI_uchar));
		pData->ezf = (ITI_uchar*)allocateMemory(pData->size.izf, sizeof(ITI_uchar));

		pData->relzf = (ITI_int*)allocateMemory(pData->size.izf, sizeof(ITI_int));
		pData->epszf = (ITI_real*)allocateMemory(pData->size.izf, sizeof(ITI_real));
		pData->sczf = (ITI_uint*)allocateMemory(pData->size.izf, sizeof(ITI_uint));
#ifdef ITI_COMP_SIM
		pData->curve_zf = (ITI_uchar*)allocateMemory(pData->size.izf, sizeof(ITI_uchar));
#endif

		for(i=0; i<(size_t)pData->size.izf; i++){
#ifdef ITI_COMP_SIM
			pData->curve_zf[i] = 0;
#endif
			if (!zfData[i].needHysterese) {
				pData->relzf[i] = 3;
#ifdef ITI_COMP_SIM
				if ((zfData[i].rel == Rel_EQ) && strstr(zfData[i].parentIdent, "curve")) {
					pData->curve_zf[i] = 1;
				}
#endif
			}
			else{
				switch(zfData[i].rel){
					case Rel_LT:
						pData->relzf[i] = -2;
						break;
					case Rel_LE:
						pData->relzf[i] = -1;
						break;
					case Rel_GT:
						pData->relzf[i] = 2;
						break;
					case Rel_GE:
						pData->relzf[i] = 1;
						break;
					case Rel_EQ:
					case Rel_NE:
						pData->relzf[i] = 0;
						break;
				}
			}
		}
	}
	return 1;
}

int InitZFData(ITI_PartitionVar* pData){
	size_t i;

	for(i=0; i<(size_t)pData->size.izf; i++){
		pData->zf[i]=0.0;
		pData->pre_zf[i]=0.0;

		pData->epszf[i] = 0.0;
		pData->pszf[i] = 0;

		pData->cszf[i] = 0;
		pData->oszf[i] = 0;

		pData->czf[i] = 1;
		pData->ezf[i] = 0;

		pData->sczf[i] = 0;
	}

	return 1;
}

int FreeZFData(ITI_PartitionVar* pData, char bComplete, ITI_FreeMemory freeMemory){
	ITI_HandleFreeMemory

	freeMemory(pData->zf);   pData->zf=0;
	freeMemory(pData->cszf); pData->cszf = 0;
	freeMemory(pData->e1zf); pData->e1zf = 0;
	freeMemory(pData->e2zf); pData->e2zf = 0;

	if(bComplete){
		freeMemory(pData->pre_zf); pData->pre_zf=0;
		freeMemory(pData->oszf);   pData->oszf = 0;
		freeMemory(pData->pszf);   pData->pszf = 0;
		freeMemory(pData->czf);    pData->czf = 0;
		freeMemory(pData->ezf);	   pData->ezf = 0;
		freeMemory(pData->relzf);  pData->relzf = 0;
		freeMemory(pData->epszf);  pData->epszf = 0;
		freeMemory(pData->sczf);   pData->e1zf = 0;
#ifdef ITI_COMP_SIM
		freeMemory(pData->curve_zf);	pData->curve_zf = 0;
#endif
	}
	return 1;
}

void Update_oszf(ITI_PartitionVar* pData){
	size_t i;
	for(i=0; i<(size_t)pData->size.izf; i++){
		if(pData->czf[i]){
			Update_sign_zf(pData, i);	 
			pData->oszf[i] = pData->cszf[i];
		}
	}
}

void Reset_ezf(ITI_PartitionVar* pData){
	size_t i;
	for(i=0; i<(size_t)pData->size.izf; i++){
		pData->ezf[i]=0;
	}
}

void Update_czf(ITI_PartitionVar* pData){
	size_t i;
	for(i=0; i<(size_t)pData->size.izf; i++){
		if(pData->relzf[i]!=3)
			pData->czf[i] = pData->ezf[i];
		pData->ezf[i] = 0;
	}
}

ITI_int Check_Update_oszf(ITI_PartitionVar* pData){
	size_t i;

	for(i=0; i<(size_t)pData->size.izf; i++){
		if(pData->czf[i]){
			Update_sign_zf(pData, i);	 
			if(pData->relzf[i] != 3){
				if(pData->oszf[i] != pData->cszf[i]){
					pData->sczf[i]++;
					Update_oszf(pData);
					return SOLVER_SUCCESS_CONTINUE;
				}
			}
		}
	}
	Update_oszf(pData);
	return SOLVER_SUCCESS_END;
}

ITI_int CheckForZeroCrossing(ITI_PartitionVar* pData){
	size_t i;

	for(i=0; i<(size_t)pData->size.izf; i++){
		if(pData->czf[i]){
			Update_sign_zf(pData, i);	 
			if(pData->oszf[i] != pData->cszf[i]){
				return 1;
			}
		}
	}
	return 0;
}

void ResetSCCounter(ITI_PartitionVar* pData){
	size_t i;

	for(i=0; i<(size_t)pData->size.izf; i++){
		pData->sczf[i] = 0;
	}
	UpdateEpsilonZF(pData);
}

static void UpdateEpsilonSingleZF(ITI_PartitionVar* pData, size_t i){
	if(pData->sInfo.sSettings->hysteresis && pData->sInfo.applyHysteresis){
		ITI_real eps_sign=1.0;
		switch(pData->relzf[i]) {
			case 2:  
				if(pData->oszf[i]>0)
					eps_sign=1;
				else
					eps_sign=-1;
				break;
			case 1:  
				if(pData->oszf[i]>=0)
					eps_sign=1;
				else
					eps_sign=-1;
				break;
			case 0:  
				eps_sign=0;
				break;
			case -1:  
				if(pData->oszf[i]<=0)
					eps_sign=-1;
				else
					eps_sign=1;
				break;
			case -2:  
				if(pData->oszf[i]<0)
					eps_sign=-1;
				else
					eps_sign=1;
				break;
			default: {
				eps_sign=0.0;
			}
		}
		pData->epszf[i]=eps_sign * pData->sInfo.sSettings->epsilon;

		if(pData->sInfo.isEvent){
			ITI_int k;
			for(k=pData->sczf[i] - pData->sInfo.sSettings->adaptThreshold;k>0;--k)
				pData->epszf[i]*=pData->sInfo.sSettings->adaptFactor;
		}
		if(pData->sInfo.sSettings->scaleEpsilon) {
			double ref=max(max(fabs(pData->e1zf[i]),fabs(pData->e2zf[i])),1.0);
			pData->epszf[i] = pData->epszf[i]*ref;
		}
	}
	else
		pData->epszf[i]=0.0;
}

void __ITI_UpdateEpsilonOsZF(ITI_PartitionVar* pData, size_t i){
	pData->oszf[i] = pData->cszf[i];
	UpdateEpsilonSingleZF(pData, i);
}

void UpdateEpsilonZF(ITI_PartitionVar* pData){
	size_t i;

	if(pData->sInfo.sSettings->hysteresis && pData->sInfo.applyHysteresis){
		for(i=0; i<(size_t)pData->size.izf; i++){
			UpdateEpsilonSingleZF(pData, i);
		}
	}
	else{
		for(i=0; i<(size_t)pData->size.izf; i++){
			pData->epszf[i] = 0.0;
		}
	}
}

static void Update_sign_zf(ITI_PartitionVar* pData,  size_t index){
	if(pData->epszf[index]==0 && pData->zf[index]==0.0) {
		switch(pData->relzf[index]) {
		case 2:  
		case -1:  
			pData->cszf[index]=-1;
			break;
		case 1:  
		case -2:  
			pData->cszf[index]=1;
			break;
		default:
			pData->cszf[index]=0;
		}
	}
	else if(pData->zf[index]>0) {
		pData->cszf[index]=1;
	}
	else if(pData->zf[index]<0) {
		pData->cszf[index]=-1;
	}
	else
		pData->cszf[index]=pData->oszf[index];
}

void __ITI_AssignZF(ITI_real e1, ITI_real e2,size_t index, ITI_PartitionVar* pData){
	if(!pData->czf[index]){
		pData->oszf[index] = (ITI_int)sign(e1-e2);
		UpdateEpsilonSingleZF(pData, index);
	}
	pData->zf[index] = e1 - e2 + pData->epszf[index];
	Update_sign_zf(pData, index);

	pData->e1zf[index]=e1;
	pData->e2zf[index]=e2;
}

int HandleAssertWarnings(ITI_SolverInfo* pInfo)
{
	size_t i;
	int iRet = SOLVER_SUCCESS_END;
	ITI_uchar* tmp;
	ITI_char shortMsg[ITI_TRACE_STRING_SIZE];
	ITI_char longMsg[ITI_TRACE_STRING_SIZE];

	if(!pInfo->assertData.bAssertStateChanged)
		return SOLVER_SUCCESS_END;

	for(i=0; i<pInfo->assertData.n; i++)
	{
		if(pInfo->assertData.assertStateR[i] != pInfo->assertData.assertStateW[i])
		{
			if(pInfo->assertData.assertStateW[i])
				snprintf(shortMsg, ITI_TRACE_STRING_SIZE, "%s : Warning revoked", pInfo->assertData.warnMsg[i]);
			else
				snprintf(shortMsg, ITI_TRACE_STRING_SIZE, pInfo->assertData.warnMsg[i]);

#ifdef ITI_COMP_SIM
			GetHyperlink(longMsg,
						 pInfo->assertData.assertStateW[i]?"Modelica.AssertWarningRevoked":"Modelica.AssertWarning");
#else
			snprintf(longMsg, ITI_TRACE_STRING_SIZE,
					 pInfo->assertData.assertStateW[i]?"Modelica.AssertWarningRevoked":"Help: Modelica.AssertWarning");
#endif
			traceWarningImmediately(shortMsg, longMsg, pInfo);
			pInfo->assertData.assertStateR[i] = pInfo->assertData.assertStateW[i];
			iRet = SOLVER_SUCCESS_CONTINUE;
		}
	}
	tmp = pInfo->assertData.assertStateR;
	pInfo->assertData.assertStateR = pInfo->assertData.assertStateW;
	pInfo->assertData.assertStateW = tmp;

	pInfo->assertData.bAssertStateChanged = ITI_false;
	return iRet;
}

void WarningChangedDiscreteVars(ITI_PartitionVar* pData, int iEventStep, ITI_real relTol, ITI_real absTol){
	size_t i;
	for (i = 0; i < (size_t)pData->size.iz_int; i++){
		if(pData->z.intData[i] != pData->pre_z.intData[i])
		{
			ITI_char msg[255];
			 
			snprintf(msg, 255, "Event step %d: z_int[%lu] = %d\tpre(z_int) = %d\n", iEventStep, (unsigned long)i, pData->z.intData[i], pData->pre_z.intData[i]);
			traceWarning(msg, &pData->sInfo);
		}
	}
	for (i = 0; i < (size_t)pData->size.iz_real; i++){
		#ifdef ITI_COMP_SIM
		if(Check_z_real(*pData->pre_z.realData[i], *pData->z.realData[i], relTol, absTol))
		#else
		if(Check_z_real(pData->pre_z.realData[i], pData->z.realData[i], relTol, absTol))
		#endif
		{
			ITI_char msg[255];
			#ifdef ITI_COMP_SIM
			snprintf(msg, 255, "Event step %d: z_real[%lu] = %.15f\tpre_z_real = %.15f\n", iEventStep, (unsigned long)i, *pData->z.realData[i], *pData->pre_z.realData[i]);
			#else
			snprintf(msg, 255, "Event step %d: z_real[%lu] = %.15f\tpre(z_real) = %.15f\n", iEventStep, (unsigned long)i, pData->z.realData[i], pData->pre_z.realData[i]);
			#endif
			traceWarning(msg, &pData->sInfo);
		}
	}
	 
}

void set_g_sInfo(ITI_SolverInfo *sInfo)
{
	g_sInfo = sInfo;
}

#ifndef ITI_SCALERT

#ifndef ITI_DSPACE
void ITI_FPE_Handler1(int sig)
{
	if (sig == SIGFPE) {
		char strMsg[1024];
		snprintf(strMsg, 1024, "***Floating Point exception!***");
		if (g_sInfo) {
			if (g_sInfo->allowBlockJump) {
				traceWarning(strMsg, g_sInfo);
				ClearAllExceptions();
				longjmp(g_sInfo->blockEnv, 1);
			}
			if (g_sInfo->allowJump) {
				traceWarning(strMsg, g_sInfo);
				ClearAllExceptions();
				longjmp(g_sInfo->buf, 1);
			}
		}
		fprintf(stdout, "\n\n%s\nAborting program\n\n", strMsg);
		exit(EXIT_FAILURE);
	}
}
#endif

ITI_SolverState ExceptWrapper2(ModelFunc2 modelFunction, ITI_Partition* pPart, SimData* modelData)
{
#ifdef ITI_COMP_SIM
	__try {
#endif
		return modelFunction(pPart, modelData);
#ifdef ITI_COMP_SIM
	}
	__except (FPEfilter(GetExceptionCode(), &pPart->curr->sInfo)) {
		RestoreMask(modelData->oldCW, modelData->oldHandler);
		if (modelData->traceFlags.trBlockStatistics)
			EndPerformanceTiming(pPart->curr->performanceData, -1);
		return 1;
	}
#endif
}

ITI_SolverState ExceptWrapper3(ModelFunc3 modelFunction, ITI_Partition* pPart, SimData* modelData, ITI_real* __jac)
{
#ifdef ITI_COMP_SIM
	__try {
#endif
		return modelFunction(pPart, modelData, __jac);
#ifdef ITI_COMP_SIM
	}
	__except (FPEfilter(GetExceptionCode(), &pPart->curr->sInfo)) {
		RestoreMask(modelData->oldCW, modelData->oldHandler);
		if (modelData->traceFlags.trBlockStatistics)
			EndPerformanceTiming(pPart->curr->performanceData, -1);
		return 1;
	}
#endif
}

#ifdef _MSC_VER

void ITI_FPE_Handler2(int sig, ...)
{
	if (sig == SIGFPE)
	{
		int fpeCode;
		char strMsg[1024];
		char *fpeStr = "\n\n***Floating Point exception!***\n\n";

		va_list argptr;
		va_start(argptr, sig);

		fpeCode = va_arg(argptr, int);

		switch (fpeCode)
		{
		case 0:
		{
			va_end(argptr);
			return;
		}
		case(_FPE_STACKOVERFLOW):
		case(_FPE_STACKUNDERFLOW):
		{
			snprintf(strMsg, 1024, "%s***Floating Point Stack overflow!***\n\nThis problem is caused by a MSVC 6 Compiler problem!\nUse another Compiler or try to change Compiler Settings!\n", fpeStr);
			break;
		}
		case(_FPE_INVALID):
			snprintf(strMsg, 1024, "%s***Invalid Operation***", fpeStr);
			break;
		case(_FPE_ZERODIVIDE):
			snprintf(strMsg, 1024, "%s***Divide by zero***", fpeStr);
			break;
		case(_FPE_OVERFLOW):
			snprintf(strMsg, 1024, "%s***Floating Point overflow***", fpeStr);
			break;
		case(_FPE_SQRTNEG):
			snprintf(strMsg, 1024, "%s***Root of negative number***", fpeStr);
			break;
		}
		va_end(argptr);

		if (g_sInfo) {
			if (g_sInfo->allowBlockJump) {
				traceWarning(strMsg, g_sInfo);
				ClearAllExceptions();
				longjmp(g_sInfo->blockEnv, 1);
			}
			if (g_sInfo->allowJump) {
				traceWarning(strMsg, g_sInfo);
				ClearAllExceptions();
				longjmp(g_sInfo->buf, 1);
			}
		}

		fprintf(stdout, "\n\n%s\nAborting program\n\n", strMsg);
		exit(EXIT_FAILURE);
	}
}

void UnmaskExceptions(int *oldCW, void (**fPtr)(int))
{
	_clearfp();
	*oldCW = _controlfp(0, 0);
	_controlfp(~(_EM_INVALID | _EM_ZERODIVIDE | _EM_OVERFLOW), MCW_EM);
}

void DisableExceptions(int *oldCW, void (**fPtr)(int))
{
	*oldCW = _controlfp(0, 0);
#if !defined ITI_TWINCAT
	_fpreset();
#endif
}

void RestoreMask(int oldCW, void (*fPtr)(int))
{
#if !defined ITI_TWINCAT
	_fpreset();
#endif
	_controlfp(oldCW, MCW_EM);
}

void ClearAllExceptions(void)
{
	_clearfp();
}

int FPEfilter(unsigned long fpeCode, ITI_SolverInfo *pSInfo)
{
	char strMsg[1024] = "*** Floating Point exception! ***\n";
	char *strInvalidOperation = "*** Invalid Operation ***";
	char *strDivideByZero = "*** Divide by zero ***";
	char *strOverflow = "*** Overflow ***";

	switch (fpeCode) {
#if !defined ITI_TWINCAT
	case EXCEPTION_FLT_INVALID_OPERATION:
		strcat(strMsg, strInvalidOperation);
		break;
	case EXCEPTION_FLT_DIVIDE_BY_ZERO:
		strcat(strMsg, strDivideByZero);
		break;
	case EXCEPTION_FLT_OVERFLOW:
		strcat(strMsg, strOverflow);
		break;
	case EXCEPTION_FLT_STACK_CHECK:
		strcat(strMsg, "*** Floating Point Stack overflow or underflow ***");
		break;
	case EXCEPTION_INT_DIVIDE_BY_ZERO:
		strcat(strMsg, "*** Integer divide by zero ***");
		break;
	case STATUS_FLOAT_MULTIPLE_FAULTS:
	case STATUS_FLOAT_MULTIPLE_TRAPS:
#if _M_IX86_FP > 0
		{
			unsigned int mxcsr = _mm_getcsr();
			if (mxcsr & 0x1)
				strcat(strMsg, strInvalidOperation);
			if (mxcsr & 0x4)
				strcat(strMsg, strDivideByZero);
			if (mxcsr & 0x8)
				strcat(strMsg, strOverflow);
		}
#endif
		break;
#endif  
	case STATUS_ASSERT:
		return EXCEPTION_EXECUTE_HANDLER;
	case STATUS_MODELICAERROR:
		return EXCEPTION_EXECUTE_HANDLER;
	default:
		strcpy(strMsg, "*** Unknown exception! ***");
		break;
	}

	_clearfp();

	traceWarning(strMsg, pSInfo);

	return EXCEPTION_EXECUTE_HANDLER;
}

#elif (defined(__gnu_linux__) || defined(__CYGWIN__)) && !defined(ITI_SFuncSolver) && !defined(ITI_DSPACE)

void UnmaskExceptions(int *oldCW, void(**fPtr)(int))
{
	feclearexcept(FE_ALL_EXCEPT);
	*fPtr = signal(SIGFPE, ITI_FPE_Handler1);
	*oldCW = feenableexcept(FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW);
}

void DisableExceptions(int *oldCW, void (**fPtr)(int))
{
	*fPtr = signal(SIGFPE, ITI_FPE_Handler1);
	*oldCW = fedisableexcept(FE_ALL_EXCEPT);
}

void RestoreMask(int oldCW, void (*fPtr)(int))
{
	feclearexcept(FE_ALL_EXCEPT);
	feenableexcept(oldCW);
	signal(SIGFPE, fPtr);
}

void ClearAllExceptions(void)
{
	feclearexcept(FE_ALL_EXCEPT);
}

#else  

void UnmaskExceptions(int *oldCW, void (**fPtr)(int)) {}

void DisableExceptions(int *oldCW, void (**fPtr)(int)) {}

void RestoreMask(int oldCW, void (*fPtr)(int)) {}

void ClearAllExceptions(void) {}

#endif

#endif  

 
#if defined (_WIN32)
#if defined(__WATCOMC__) || (defined(_MSC_VER) && _MSC_VER >= 1300)
#define HAVE_LONG_LONG 1
#endif
#endif
#if defined(__GNUC__)
#if !defined(HAVE_LONG_LONG)
#define HAVE_LONG_LONG 1
#endif
#endif

int ITI_finite(double x)
{
#if !defined(__STDC__) && defined(HAVE_LONG_LONG)
	union {
		unsigned long long u;
		double f;
	} ieeeValue;

	ieeeValue.f = x;

	return !(((ieeeValue.u >> 32) & 0x7ff00000) == 0x7ff00000);
#elif !defined(__STDC__) && defined(_WIN32) && defined(_MSC_VER) && _MSC_VER < 1300
	union {
		unsigned __int64 u;
		double f;
	} ieeeValue;

	ieeeValue.f = x;

	return !(((ieeeValue.u >> 32) & 0x7ff00000) == 0x7ff00000);
#else
	union {
		unsigned long u[2];
		double f;
	} ieeeValue;

	ieeeValue.f = x;

	return !((ieeeValue.u[1] & 0x7ff00000) == 0x7ff00000);  
#endif
}

#undef SCALE









void CountDiscrete(ITI_uint* dC, ITI_PartitionVar* pData){
#ifndef ITI_COMP_SIM
	return;
#else
	if (pData)
	{
		ITI_int i;

		 
		for (i = 0; i < pData->size.iz_real; i++)
		{
			if (*pData->pre_z.realData[i] != *pData->z.realData[i])
				dC[i]++;
		}
		 
		for (i = 0; i < pData->size.iz_int; i++)
		{
			if (pData->pre_z.intData[i] != pData->z.intData[i])
				dC[i + pData->size.iz_real]++;
		}
		 
		for (i = 0; i < pData->size.iz_str; i++)
		{
			 
			if (strcmp(pData->pre_z.strData[i], pData->z.strData[i]) != 0)
				dC[i + pData->size.iz_int + pData->size.iz_real]++;
		}
	}
#endif
}


void CountZeroCrossing(ITI_uint* zCC, ITI_PartitionVar* pData) {
	size_t i;

	for (i = 0; i < (size_t)pData->size.izf; i++) {
		if (pData->czf[i]) {
#ifdef ITI_COMP_SIM
			if (pData->curve_zf) {
				if (pData->oszf[i] != sign(pData->zf[i])) {
					zCC[i]++;
				}
			}
			else
#endif
			{
				if (pData->oszf[i] != pData->cszf[i]) {
					zCC[i]++;
				}
			}
		}
	}
}
