/**
 * ITI_DeclarationsBase.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#ifndef ITI_DECLARATIONSBASE_H
#define ITI_DECLARATIONSBASE_H

#ifdef _MSC_VER
#include <excpt.h>
#endif

#ifdef ITI_COMP_SIM
#ifdef __GNUC__




#define _snprintf snprintf
#endif  
#ifndef ERROR
#define ERROR 0
#endif
#endif  


#define _ext_object(i) modelData->extObj[i]

#define __RECORD(name) ((ITI_Records*)pPart->transient->pRecord)->name
#define __DUMMY_RECORD typedef struct ITI_Records {char* dummy;}ITI_Records;

#define _sInfo pPart->transient->sInfo	 
#define __ibd (&pPart->curr->ibd[blockNr])
#define __iDPbd(k) pPart->curr->iDPbd[k]
#define __hmm modelData->hmm
#define __hom_res modelData->hom_res
#define __hom_jac modelData->hom_jac
#define _hcs pPart->transient->hcs
#define _db pPart->transient->db

#ifdef ITI_COMP_SIM

#define __INIT_TRACE_DATA InitMemory(&modelData->traceData.memObj, modelData->traceData.memObj.allocateMemory, modelData->traceData.memObj.freeMemory); \
modelData->traceData.memObj.allocStrategy = DontUseSpaceInOtherBlocks; \
InitMemory(&modelData->traceData.memObj2, modelData->traceData.memObj2.allocateMemory, modelData->traceData.memObj2.freeMemory); \
InitMemory(&modelData->traceData.memObj3, modelData->traceData.memObj3.allocateMemory, modelData->traceData.memObj3.freeMemory);

#define __TRACE_FLUSH(title) if (_traceOn > 0){ \
CopyToFlatMemory(&modelData->traceData.memObj, modelData->traceData.memObj.firstStringBlock); \
{\
ITI_char titleStr[100]; \
ITI_char formatStr[100]; \
strcpy(formatStr, title); \
if(pPart->pid>0){ \
	strcat(formatStr, " Clock Partition: %Iu"); \
	_snprintf(titleStr, 100, formatStr, _t, pPart->pid); \
} else _snprintf(titleStr, 100, formatStr, _t); \
_sInfo.trace(0,5, titleStr, modelData->traceData.memObj.flatMemory, (void*)&_sInfo); \
}\
FreeFlatMemory(&modelData->traceData.memObj); \
ReleaseAllMemory(&modelData->traceData.memObj);\
ReleaseAllMemory(&modelData->traceData.memObj2);\
ReleaseAllMemory(&modelData->traceData.memObj3); \
}

#define __ERROR_TRACE_FLUSH if (_traceOn > 0 && modelData->traceData.memObj.allocateMemory){\
	modelData->traceData.buffer = GetStringMemory(&modelData->traceData.memObj, strlen(modelData->traceData.line)-1);\
	strcat(modelData->traceData.buffer, modelData->traceData.line);\
	__TRACE_FLUSH("Time: %.16gs: Error")\
}\

#if (defined(_MSC_VER) && (_MSC_VER >= 1400)) || defined (__GNUC__)
#define __TRACE_RECORD(fLine, ...) __TRACE_RECORD_(&modelData->traceData.memObj2, fLine, ##__VA_ARGS__)
#define __TRACE_RECORD_EXT(fLine, ...) __TRACE_RECORD_(&modelData->traceData.memObj3, fLine, ##__VA_ARGS__)
#define __TRACE_RECORD_(pMemObj, fLine, ...) GetRecordStr(&modelData->traceData, pMemObj, fLine, ##__VA_ARGS__)

#define __TRACE_ARRAY(arr) __TRACE_ARRAY_(arr, &modelData->traceData.memObj2)
#define __TRACE_ARRAY_EXT(arr) __TRACE_ARRAY_(arr, &modelData->traceData.memObj3)
#define __TRACE_ARRAY_(arr, pMemObj) GetArrayStr(arr, &modelData->traceData, pMemObj)

#define __TRACE_TYPED_ARRAY(type, arr) __TRACE_TYPED_ARRAY_(type, arr, &modelData->traceData.memObj2)
#define __TRACE_TYPED_ARRAY_EXT(type, arr) __TRACE_TYPED_ARRAY_(type, arr, &modelData->traceData.memObj3)
#define __TRACE_TYPED_ARRAY_(type, arr, pMemObj) type==INT_TYPE?GetIntArrayStr((ITI_int*)arr, sizeof(arr)/sizeof(arr[0]), &modelData->traceData, pMemObj):GetRealArrayStr((ITI_real*)arr, sizeof(arr)/sizeof(arr[0]), &modelData->traceData, pMemObj)

#define __TRACE_STR(fline, ...) __TRACE_STMT("", fline, ##__VA_ARGS__)

#define __TRACE_STMT(oLine, fLine, ...) oLine; \
if (_traceOn > 0){ \
modelData->traceData.len = strlen(fLine)+1024; \
modelData->traceData.temp2 = GetStringMemory(&modelData->traceData.memObj2, modelData->traceData.len); \
_snprintf(modelData->traceData.temp2, modelData->traceData.len, fLine, ##__VA_ARGS__); \
modelData->traceData.len = strlen(modelData->traceData.temp2); \
modelData->traceData.buffer = GetStringMemory(&modelData->traceData.memObj, modelData->traceData.len-1); \
_snprintf(modelData->traceData.buffer, modelData->traceData.len, modelData->traceData.temp2); \
}

#define __TRACE_ASSIGN(oLine, fLine, lVar, lVarFmt, ...) __TRACE_ASSIGN_(&modelData->traceData.memObj2, modelData->traceData.line, oLine, fLine, lVar, lVarFmt, ##__VA_ARGS__)

#define __TRACE_ASSIGN_EXT(oLine, fLine, lVar, lVarFmt, ...) __TRACE_ASSIGN_(&modelData->traceData.memObj3, modelData->traceData.line_ext, oLine, fLine, lVar, lVarFmt, ##__VA_ARGS__)

#define __TRACE_ASSIGN_(pMemObj, line, oLine, fLine, lVar, lVarFmt, ...) line = 0;\
if (_traceOn > 0){ \
modelData->traceData.len = strlen(fLine)+1024; \
line = GetStringMemory(pMemObj, modelData->traceData.len); \
if (strlen(lVarFmt) == 2) \
	_snprintf(line, modelData->traceData.len, fLine, "??", ##__VA_ARGS__); \
else \
	_snprintf(line, modelData->traceData.len, fLine, "??   ", ##__VA_ARGS__); \
} \
oLine \
if (_traceOn > 0 && line){ \
modelData->traceData.start = strstr(line, "??"); \
if (modelData->traceData.start){ \
	ITI_uint first = 0; \
	strncpy(modelData->traceData.start, lVarFmt, strlen(lVarFmt)); \
	modelData->traceData.len = strlen(line)+256; \
	modelData->traceData.temp2 = GetStringMemory(pMemObj, modelData->traceData.len); \
	_snprintf(modelData->traceData.temp2, modelData->traceData.len, line, lVar); \
	modelData->traceData.len = strlen(modelData->traceData.temp2); \
	modelData->traceData.buffer = GetStringMemory(&modelData->traceData.memObj, modelData->traceData.len-1);\
	_snprintf(modelData->traceData.buffer, modelData->traceData.len, modelData->traceData.temp2); \
}\
ReleaseAllMemory(pMemObj); \
}
#endif

#define __TRACE_DPB_ODE_STATES(kDP, nODE, nDAE) \
{\
	ITI_uint i;\
	__TRACE_STR("    \"The following block states are ode states:\"")\
	for (i=nDAE; i<(nDAE+nODE); i++){\
		__TRACE_STR(" %d", __iDPbd(kDP).M[i])\
	}\
	__TRACE_STR(" .\n")\
}

#ifdef _MSC_VER
	#define DLL_Export __declspec(dllexport)
#elif __MINGW32__
	#define DLL_Export __declspec(dllexport)
#else
	#define DLL_Export
#endif

#else  
#define DLL_Export 
#endif  

#define _t pPart->curr->t
#define _time _t

#define _bcstate(i) pPart->base->x[i]
#define _scstate(i) pPart->sub->x[i]
#define _state(i) pPart->transient->x[i]
#define _bcder_state(i) pPart->base->xdot[i]
#define _scder_state(i) pPart->sub->xdot[i]
#define _der_state(i) pPart->transient->xdot[i]

#ifdef ITI_COMP_SIM
#define _parameter_real(i) (*pPart->transient->p.realData[i])
#define _parameter_int(i) pPart->transient->p.intData[i]
#define _parameter_str(i) pPart->transient->p.strData[i]
#else
#define _parameter_real(i, gi) pPart->transient->p.realData[i]
#define _parameter_int(i, gi) pPart->transient->p.intData[i]
#define _parameter_str(i, gi) pPart->transient->p.strData[i]
#endif

#ifdef ITI_COMP_SIM
#define _bcinput_real(i) (*pPart->base->u.realData[i])
#define _scinput_real(i) (*pPart->sub->u.realData[i])
#define _input_real(i) (*pPart->transient->u.realData[i])
#define _bcinput_int(i) pPart->base->u.intData[i]
#define _scinput_int(i) pPart->sub->u.intData[i]
#define _input_int(i) pPart->transient->u.intData[i]
#define _bcinput_str(i) pPart->base->u.strData[i]
#define _scinput_str(i) pPart->sub->u.strData[i]
#define _input_str(i) pPart->transient->u.strData[i]
#else
#define _bcinput_real(i, gi) pPart->base->u.realData[i]
#define _scinput_real(i, gi) pPart->sub->u.realData[i]
#define _input_real(i, gi) pPart->transient->u.realData[i]
#define _bcinput_int(i, gi) pPart->base->u.intData[i]
#define _scinput_int(i, gi) pPart->sub->u.intData[i]
#define _input_int(i, gi) pPart->transient->u.intData[i]
#define _bcinput_str(i, gi) pPart->base->u.strData[i]
#define _scinput_str(i, gi) pPart->sub->u.strData[i]
#define _input_str(i, gi) pPart->transient->u.strData[i]
#endif

#define __array(i) pPart->transient->arrays[i]
#define _dt _sInfo.dt

#ifdef ITI_COMP_SIM
#define _bcbstate(i) (*pPart->base->bx[i])
#define _scbstate(i) (*pPart->sub->bx[i])
#define _bstate(i) (*pPart->transient->bx[i])
#else
#define _bcbstate(i) pPart->base->bx[i]
#define _scbstate(i) pPart->sub->bx[i]
#define _bstate(i) pPart->transient->bx[i]
#endif

#ifndef ITI_COMP_SIM
#define __OUT_INT(i, gi, var) pPart->transient->y.intData[i] = var;
#define __OUT_REAL(i, gi, var) pPart->transient->y.realData[i] = var;
#define __OUT_STR(i, gi, var) pPart->transient->y.strData[i] = var;

#define _parameter_real_arr(i,j) pPart->transient->arr_p[i].realValues[j]
#define _parameter_int_arr(i,j) pPart->transient->arr_p[i].intValues[j]
#define _parameter_str_arr(i,j) pPart->transient->arr_p[i].strValues[j]
#define _parameter_arr(i) pPart->transient->arr_p[i]
#endif


#define Param_Declare_SimData ITI_ModelData* modelData
#define Param_Declare_SimVar ITI_Partition* pPart
#define Param_Passing_SimData modelData
#define Param_Passing_SimVar pPart
#define Param_SInfo_Mem &pPart->transient->sInfo, &modelData->currMem
#define Param_Mem &modelData->currMem
#define Param_Str_Mem &modelData->strMem

#define _bczero(i) pPart->base->zf[i]
#define _sczero(i) pPart->sub->zf[i]
#define _zero(i) pPart->transient->zf[i]
#define _bcbpre_zero(i) pPart->base->pre_zf[i]
#define _scbpre_zero(i) pPart->sub->pre_zf[i]
#define _pre_zero(i) pPart->transient->pre_zf[i]
#ifdef ITI_COMP_SIM
#define _bcclocksample_real(i) (*pPart->base->clocksv.realData[i])
#define _scclocksample_real(i) (*pPart->sub->clocksv.realData[i])
#define _clocksample_real(i) (*pPart->transient->clocksv.realData[i])
#else
#define _clocksample_real(i) pPart->transient->clocksv.realData[i]
#define _bcclocksample_real(i) pPart->base->clocksv.realData[i]
#define _scclocksample_real(i) pPart->sub->clocksv.realData[i]
#endif
#define _bcclocksample_int(i) pPart->base->clocksv.intData[i]
#define _scclocksample_int(i) pPart->sub->clocksv.intData[i]
#define _clocksample_int(i) pPart->transient->clocksv.intData[i]
#define _bcclocksample_str(i) pPart->base->clocksv.strData[i]
#define _scclocksample_str(i) pPart->sub->clocksv.strData[i]
#define _clocksample_str(i) pPart->transient->clocksv.strData[i]

#define _bccurve_sets(i) pPart->base->cSet[i]
#define _sccurve_sets(i) pPart->sub->cSet[i]
#define _curve_sets(i) pPart->transient->cSet[i]
#define _bccurve_nds(i) pPart->base->cNd[i]
#define _sccurve_nds(i) pPart->sub->cNd[i]
#define _curve_nds(i) pPart->transient->cNd[i]
#define _bccall_state(i) pPart->base->cs[i]
#define _sccall_state(i) pPart->sub->cs[i]
#define _call_state(i) pPart->transient->cs[i]
#define _bchyst_call_state(i) pPart->base->hcs[i]
#define _schyst_call_state(i) pPart->sub->hcs[i]
#define _hyst_call_state(i) pPart->transient->hcs[i]
#define _bcsample_variable(i) pPart->base->sv[i]
#define _scsample_variable(i) pPart->sub->sv[i]
#define _sample_variable(i) pPart->transient->sv[i]

#ifdef ITI_COMP_SIM
#define _bcdiscrete_real(i) (*pPart->base->z.realData[i])
#define _scdiscrete_real(i) (*pPart->sub->z.realData[i])
#define _discrete_real(i) (*pPart->transient->z.realData[i])
#else
#define _bcdiscrete_real(i) pPart->base->z.realData[i]
#define _scdiscrete_real(i) pPart->sub->z.realData[i]
#define _discrete_real(i) pPart->transient->z.realData[i]
#endif
#define _bcdiscrete_int(i) pPart->base->z.intData[i]
#define _scdiscrete_int(i) pPart->sub->z.intData[i]
#define _discrete_int(i) pPart->transient->z.intData[i]
#define _bcdiscrete_str(i) pPart->base->z.strData[i]
#define _scdiscrete_str(i) pPart->sub->z.strData[i]
#define _discrete_str(i) pPart->transient->z.strData[i]

#ifdef ITI_COMP_SIM
#define _bcpre_discrete_real(i) (*pPart->base->pre_z.realData[i])
#define _scpre_discrete_real(i) (*pPart->sub->pre_z.realData[i])
#define _pre_discrete_real(i) (*pPart->transient->pre_z.realData[i])
#else
#define _bcpre_discrete_real(i) pPart->base->pre_z.realData[i]
#define _scpre_discrete_real(i) pPart->sub->pre_z.realData[i]
#define _pre_discrete_real(i) pPart->transient->pre_z.realData[i]
#endif
#define _bcpre_discrete_int(i) pPart->base->pre_z.intData[i]
#define _scpre_discrete_int(i) pPart->sub->pre_z.intData[i]
#define _pre_discrete_int(i) pPart->transient->pre_z.intData[i]

#define _bcpre_discrete_str(i) pPart->base->pre_z.strData[i]
#define _scpre_discrete_str(i) pPart->sub->pre_z.strData[i]
#define _pre_discrete_str(i) pPart->transient->pre_z.strData[i]

#ifdef ITI_COMP_SIM
#define _bcoutput_real(i) (*pPart->base->y.realData[i])
#define _scoutput_real(i) (*pPart->sub->y.realData[i])
#define _output_real(i) (*pPart->transient->y.realData[i])
#define _bcoutput_int(i) pPart->base->y.intData[i]
#define _scoutput_int(i) pPart->sub->y.intData[i]
#define _output_int(i) pPart->transient->y.intData[i]
#define _bcoutput_str(i) pPart->base->y.strData[i]
#define _scoutput_str(i) pPart->sub->y.strData[i]
#define _output_str(i) pPart->transient->y.strData[i]
#endif

#ifdef ITI_COMP_SIM
#define _bcvariable_real(i) (*pPart->base->v.realData[i])
#define _scvariable_real(i) (*pPart->sub->v.realData[i])
#define _variable_real(i) (*pPart->transient->v.realData[i])
#else
#define _bcvariable_real(i) pPart->base->v.realData[i]
#define _scvariable_real(i) pPart->sub->v.realData[i]
#define _variable_real(i) pPart->transient->v.realData[i]
#endif
#define _bcvariable_int(i) pPart->base->v.intData[i]
#define _scvariable_int(i) pPart->sub->v.intData[i]
#define _variable_int(i) pPart->transient->v.intData[i]
#define _bcvariable_str(i) pPart->base->v.strData[i]
#define _scvariable_str(i) pPart->sub->v.strData[i]
#define _variable_str(i) pPart->transient->v.strData[i]

#define CHECK_REAL_INPUTS {\
	ITI_int i;\
	for (i = 0; i < pPart->curr->size.iu_real; i++)\
		if (!isfinite(pPart->curr->u.realData[i])) {\
			char msg[100];\
			sprintf(msg, "Input u[%d] to the model is not valid (Inf or NaN).\n", i);\
			_errorFunction(0, msg, &_sInfo);\
		}\
}

#ifdef _MSC_VER

#define F_BEGIN \
	UnmaskExceptions(&modelData->oldCW, &modelData->oldHandler);\
	__try {

#define FM_BEGIN \
	DisableExceptions(&modelData->oldCW, &modelData->oldHandler);\
	__try {

#define FIC_BEGIN \
	UnmaskExceptions(&modelData->oldCW, &modelData->oldHandler);\
	CHECK_REAL_INPUTS\
	__try {

#define FD_BEGIN \
	UnmaskExceptions(&modelData->oldCW, &modelData->oldHandler);\
	CHECK_REAL_INPUTS\
	__try {

#define F_END \
		RestoreMask(modelData->oldCW, modelData->oldHandler);\
		return 0;\
	}\
	__except (FPEfilter(GetExceptionCode(), &_sInfo)) {\
		RestoreMask(modelData->oldCW, modelData->oldHandler);\
		return 1;\
	}\
}

#define FD_END \
		E_PERF_T\
		RestoreMask(modelData->oldCW, modelData->oldHandler);\
		return 0;\
	}\
	__except (FPEfilter(GetExceptionCode(), &_sInfo)) {\
		E_PERF_T\
		RestoreMask(modelData->oldCW, modelData->oldHandler);\
		return 1;\
	}\
}

#else  

#define F_BEGIN \
	UnmaskExceptions(&modelData->oldCW, &modelData->oldHandler);\
	_sInfo.allowJump = ITI_true;\
	_sInfo.allowBlockJump = ITI_false;\
	if (setjmp(_sInfo.buf) == 0) {

#define FM_BEGIN \
	DisableExceptions(&modelData->oldCW, &modelData->oldHandler);\
	_sInfo.allowJump = ITI_true;\
	_sInfo.allowBlockJump = ITI_false;\
	if (setjmp(_sInfo.buf) == 0) {

#define FIC_BEGIN \
	UnmaskExceptions(&modelData->oldCW, &modelData->oldHandler);\
	_sInfo.allowJump = ITI_true;\
	_sInfo.allowBlockJump = ITI_false;\
	CHECK_REAL_INPUTS\
	if (setjmp(_sInfo.buf) == 0) {

#define FD_BEGIN \
	UnmaskExceptions(&modelData->oldCW, &modelData->oldHandler);\
	_sInfo.allowJump = ITI_true;\
	_sInfo.allowBlockJump = ITI_false;\
	CHECK_REAL_INPUTS\
	if (setjmp(_sInfo.buf) == 0) {

#define F_END\
		RestoreMask(modelData->oldCW, modelData->oldHandler);\
		_sInfo.allowJump = ITI_false;\
		return 0;\
	} else {\
		RestoreMask(modelData->oldCW, modelData->oldHandler);\
		_sInfo.allowJump = ITI_false;\
		return 1;\
	}\
}

#define FD_END \
		E_PERF_T\
		RestoreMask(modelData->oldCW, modelData->oldHandler);\
		_sInfo.allowJump = ITI_false;\
		return 0;\
	} else {\
		E_PERF_T\
		RestoreMask(modelData->oldCW, modelData->oldHandler);\
		_sInfo.allowJump = ITI_false;\
		return 1;\
	}\
}

#endif


#define AllocateRecords_Head DLL_Export void AllocateRecords(ITI_Partition* pPart)
#define AllocateRecords_Declare AllocateRecords_Head ;

#define InitializeConstants_Head static ITI_SolverState InitializeConstants(ITI_Partition* pPart, ITI_ModelData* modelData)
#define InitializeConstants_Declare InitializeConstants_Head ;
#define InitializeConstants_Begin InitializeConstants_Head {\
	FM_BEGIN
#define InitializeConstants_End F_END

#define InitializeParameterDependent_Head static ITI_SolverState InitializeParameterDependent(ITI_Partition* pPart, ITI_ModelData* modelData)
#define InitializeParameterDependent_Declare InitializeParameterDependent_Head ;
#define InitializeParameterDependent_Begin InitializeParameterDependent_Head {\
	FM_BEGIN
#define InitializeParameterDependent_End F_END

#define InitializeTunableParameter_Head static ITI_SolverState InitializeTunableParameter(ITI_Partition* pPart, ITI_ModelData* modelData)
#define InitializeTunableParameter_Declare InitializeTunableParameter_Head ;
#define InitializeTunableParameter_Begin InitializeTunableParameter_Head {\
	FM_BEGIN
#define InitializeTunableParameter_End F_END

#define Initialize_Head static ITI_SolverState Initialize(ITI_Partition* pPart, ITI_ModelData* modelData)
#define Initialize_Declare Initialize_Head ;
#define Initialize_Begin Initialize_Head {\
	FM_BEGIN
#define Initialize_End F_END 

#define InitializeConditions_Head static ITI_SolverState InitializeConditions(ITI_Partition* pPart, ITI_ModelData* modelData)
#define InitializeConditions_Declare InitializeConditions_Head ;

#ifdef ITI_COMP_SIM
#define InitializeConditions_Begin InitializeConditions_Head {\
	F_BEGIN
#else
#define InitializeConditions_Begin InitializeConditions_Head {\
	FD_BEGIN
#endif

#define InitializeConditions_End F_END

#define CalcOutputs_Head static ITI_SolverState CalcOutputs(ITI_Partition* pPart, ITI_ModelData* modelData)
#define CalcOutputs_Declare CalcOutputs_Head ;
#define CalcOutputs_Begin CalcOutputs_Head {\
	F_BEGIN
#define CalcOutputs_End F_END

#define SynchOutputs_Head static ITI_SolverState SynchOutputs(ITI_Partition* pPart, ITI_ModelData* modelData)
#define SynchOutputs_Declare SynchOutputs_Head ;
#define SynchOutputs_Begin SynchOutputs_Head {\
	F_BEGIN
#define SynchOutputs_End F_END

#define ValidStep_Head static ITI_SolverState ValidStep(ITI_Partition* pPart, ITI_ModelData* modelData)
#define ValidStep_Declare ValidStep_Head ;
#define ValidStep_Begin ValidStep_Head {\
	F_BEGIN
#define ValidStep_End F_END

#define CalcDerivatives_Head static ITI_SolverState CalcDerivatives(ITI_Partition* pPart, ITI_ModelData* modelData)
#define CalcDerivatives_Declare CalcDerivatives_Head ;
#define CalcDerivatives_Begin CalcDerivatives_Head {\
	FD_BEGIN
#define CalcDerivatives_End	F_END

#define Declare_ModelInfo_Head static void GetModelInfo(ITI_ModelInfo* pInfo)
#define Declare_ModelInfo_None Declare_ModelInfo_Head {}
#define Declare_ModelInfo_Begin Declare_ModelInfo_Head {
#define Declare_ModelInfo_End }

#define Declare_bNeedExtendedOnValidStep(b) pInfo->bNeedExtendedOnValidStep=b;
#define Declare_bHasDummyVariables(b) pInfo->bHasDummyVariables=b;

#define SampleFunction_Head static void SampleFunction(ITI_Partition* pPart, ITI_ModelData* modelData)
#define SampleFunction_Declare SampleFunction_Head ;
#define SampleFunction_Begin  SampleFunction_Head {
#define SampleFunction_WorkVar ITI_int __i=0;
#define SampleFunction_End }
#define Declare_SampleFunction(_to, _ts) \
	pPart->transient->sampleTime[__i].to = _to;\
	pPart->transient->sampleTime[__i++].ts = _ts;\


#define AssignLastVar_Head static void AssignLastVar(ITI_Partition* pPart, ITI_ModelData* modelData)
#define AssignLastVar_Declare AssignLastVar_Head ;
#define AssignLastVar_Begin AssignLastVar_Head {
#define AssignLastVar_End }

#define AssignDiscreteReal_Head static void AssignDiscreteReal(ITI_Partition* pPart, ITI_ModelData* modelData)
#define AssignDiscreteReal_Declare AssignDiscreteReal_Head ;
#define AssignDiscreteReal_Begin AssignDiscreteReal_Head {
#define AssignDiscreteReal_End }

#define FreeRecords_Head DLL_Export void FreeRecords(ITI_Partition* pPart, ITI_ModelData* modelData)
#define FreeRecords_Declare FreeRecords_Head ;
#ifdef ITI_COMP_SIM
#define FreeRecords_Begin FreeRecords_Head { \
  if (pPart->curr->size.iRec > 0){ \
	free(pPart->curr->pRecord); \
	pPart->curr->pRecord = NULL; \
  }
#else
#define FreeRecords_Begin FreeRecords_Head { \
  if (pPart->transient->size.iRec > 0){ \
	free(pPart->transient->pRecord); \
	pPart->transient->pRecord = NULL; \
  }
#endif

#define Terminate_Head static ITI_SolverState Terminate(ITI_Partition* pPart, ITI_ModelData* modelData)
#define Terminate_Declare Terminate_Head ;
#define Terminate_Begin Terminate_Head {\
	F_BEGIN
#define Terminate_End F_END
#define FreeRecords_End }

#ifdef ITI_COMP_SIM
#define ConstConditionsChanged_Head DLL_Export ITI_SolverState ConstConditionsChanged(ITI_Partition* pPart, ITI_ModelData* modelData)
#define ConstConditionsChanged_Declare ConstConditionsChanged_Head ;
#define ConstConditionsChanged_Begin ConstConditionsChanged_Head {
#define ConstConditionsChanged_End }

#define SynchronizeParameters_Head DLL_Export void SynchronizeParameters(ITI_Partition* pPart, ITI_ModelData* modelData)
#define SynchronizeParameters_Declare SynchronizeParameters_Head ;
#define SynchronizeParameters_Begin SynchronizeParameters_Head {
#define SynchronizeParameters_End }
#endif  

#define PreActivation_Head static ITI_SolverState PreActivation(ITI_Partition* pPart, ITI_ModelData* modelData)
#define PreActivation_Declare PreActivation_Head ;
#define PreActivation_Begin PreActivation_Head {\
	F_BEGIN
#define PreActivation_End F_END

#define PostActivation_Head static ITI_SolverState PostActivation(ITI_Partition* pPart, ITI_ModelData* modelData)
#define PostActivation_Declare PostActivation_Head ;
#define PostActivation_Begin PostActivation_Head {\
	F_BEGIN
#define PostActivation_End F_END

#define INTEGRATE_PARTITION(clockid, nexttick) IntegratePartition(clockid, _sInfo.pSolverData, nexttick);

#define CLOCK_TICK(clockid) DoClockTick(clockid, _sInfo.pSolverData);
#define NEXT_CLOCK_TICK(clockid, nexttick) NextClockTick(clockid, _sInfo.pSolverData, nexttick);
#define BASE_INTERVAL_UPDATE(graphid) PerformIntervalUpdate(pPart, graphid);

#define GetCheckSum_Decl DLL_Export unsigned long GetCheckSum();
#define GetCheckSum_Impl(check_sum) \
	unsigned long GetCheckSum(){return check_sum;}

#define GetInterfaceVersion_Decl DLL_Export ITI_real GetInterfaceVersion();
#define GetInterfaceVersion_Impl \
	ITI_real GetInterfaceVersion(){return ITI_INTERFACE_VERSION;}

#define Declare_Parameter_None static ITI_parameterData parameters[1];
#define Declare_Parameter_Begin static ITI_parameterData parameters[] = {
#define Declare_Parameter_End };
#define Declare_Parameter(name,comment,default_value,unit, signalName, paramType, valType) \
	{name, comment, default_value, unit, signalName, paramType, valType},

#ifndef ITI_COMP_SIM
#define Declare_Parameter_Arr_None static ITI_Data_Array parametersArr[1];
#define Declare_Parameter_Arr_Begin static ITI_Data_Array parametersArr[] = {
#define Declare_Parameter_Arr_End };
#define Declare_Data_Arr(name, comment, altName, unit, dims, nDims, valType) \
	{name, comment, altName, unit, dims, nDims, valType},
#endif

#define Declare_Input_None DLL_Export ITI_inputData inputs[1];
#define Declare_Input_Begin DLL_Export ITI_inputData inputs[] = {
#define Declare_Input_End };
#define Declare_Input(name,comment,default_value, bInterpol, bDirectThrough, signalName, paramType, typeStr, typeIndex) \
	{name, comment, default_value, bInterpol, bDirectThrough, signalName, paramType, typeStr, typeIndex},

#define Declare_Output_None DLL_Export ITI_outputData outputData[1];
#define Declare_Output_Begin DLL_Export ITI_outputData outputData[] = {
#define Declare_Output_End };
#define Declare_Output(name,comment,unit, signalName, type, typeIndex) \
	{name, comment, unit, signalName, type, typeIndex},

#ifdef ITI_COMP_SIM
#define Declare_V_None static ITI_varData dataPartitionV[1];
#define Declare_V_Begin static ITI_varData dataPartitionV[] = {
#define Declare_V_End };
#define Declare_V(name,index, indexSimX, dim, type, kind, recArrayIndex) \
	{name, index, indexSimX, dim, type, kind, recArrayIndex},

#define Declare_Z_None static ITI_varData dataPartitionZ[1];
#define Declare_Z_Begin static ITI_varData dataPartitionZ[] = {
#define Declare_Z_End };
#define Declare_Z(name,index, indexSimX, dim, type, kind, recArrayIndex) \
	{name, index, indexSimX, dim, type, kind, recArrayIndex},

#define Declare_BX_None static ITI_varData dataPartitionBX[1];
#define Declare_BX_Begin static ITI_varData dataPartitionBX[] = {
#define Declare_BX_End };
#define Declare_BX(name,index, indexSimX, dim, type, kind, recArrayIndex) \
	{name, index, indexSimX, dim, type, kind, recArrayIndex},
#endif  

#define Declare_ZF_None static ITI_zerofunctionData dataZF[1];
#define Declare_ZF_Begin static ITI_zerofunctionData dataZF[] = {
#define Declare_ZF_End };
#define Declare_ZF(name, index, parent, rel, needHysterese, expr) \
	{name, index, parent, rel, needHysterese, expr},

#define Declare_CurveSetData_None static ITI_CurveSetData curveSets[1];
#define Declare_CurveSetData_Begin static ITI_CurveSetData curveSets[] = {
#define Declare_CurveSetData_End };
#ifdef ITI_COMP_SIM
#define Declare_CurveSetData(name) \
	{sizeof(name##_X)/sizeof(ITI_real), sizeof(name##_pY)/sizeof(ITI_real*),\
	name##_YInfo, name##_X, name##_pY, name##_pYCoeff, 0, -1},
#else
#define Declare_CurveSetData(name, orig_name, nYScale, param_idx) \
	{sizeof(name##_X)/sizeof(ITI_real), sizeof(name##_pY)/sizeof(ITI_real*),\
	name##_YInfo, name##_X, name##_pY, name##_pYCoeff, #orig_name, nYScale, 0, param_idx},
#endif

#define Declare_CurveNDData_None static ITI_CurveData_ND curveNDs[1];
#define Declare_CurveNDData_Begin static ITI_CurveData_ND curveNDs[] = {
#define Declare_CurveNDData_End };
#ifdef ITI_COMP_SIM
#define Declare_CurveNDData(name) \
	{sizeof(name##_X)/sizeof(ITI_real), sizeof(name##_Y)/sizeof(ITI_real),\
	sizeof(name##_Z)/sizeof(ITI_real), name##_AxisInfo, name##_X, name##_Y,\
	name##_Z, name##_Val, name##_pYCoeff, 0},
#else
#define Declare_CurveNDData(name, orig_name, nYScale) \
	{sizeof(name##_X)/sizeof(ITI_real), sizeof(name##_Y)/sizeof(ITI_real),\
	sizeof(name##_Z)/sizeof(ITI_real), name##_AxisInfo, name##_X, name##_Y,\
	name##_Z, name##_Val, name##_pYCoeff, #orig_name, nYScale, 0},
#endif

#define Declare_SeqCsSize_None static ITI_uint seqCsSizes[1];
#define Declare_SeqCsSize_Begin static ITI_uint seqCsSizes[] = {
#define Declare_SeqCsSize_End };
#define Declare_SeqCsSize(size) size,

#define Declare_DelayInfo_None static ITI_DelayInfo delayInfos[1];
#define Declare_DelayInfo_Begin static ITI_DelayInfo delayInfos[] = {
#define Declare_DelayInfo_End };
#define Declare_DelayInfo(bufSize, valType, name) \
	{bufSize, valType, name},

#define Declare_HystInitFunction_None static ITI_HystCurveInitData _hyst_init_data[1];
#define Declare_HystInitFunction_Begin static ITI_HystCurveInitData _hyst_init_data[] = {
#define Declare_HystInitFunction_End };
#define Declare_HystInitFunction(name, enabled, hystMode, clockwise, startPoint, startValue, eps_xdot) \
	{name, enabled, hystMode, clockwise, startPoint, startValue, eps_xdot},

#define HYST_INIT_DATA(idx) pPart->curr->_hyst_init_data[idx]

#define Declare_StateAttributes_None static ITI_VarAttributes stateAttributes[1]; \
GetSizeOfStateAttr_Head \
{ \
	return 0; \
}

#define Declare_StateAttributes_Begin static ITI_VarAttributes stateAttributes[] = {
#define Declare_StateAttributes_End }; \
GetSizeOfStateAttr_Head \
{ \
	return sizeof(stateAttributes) / sizeof(stateAttributes[0]); \
}

#define Declare_StateAttributes(stateIdx, startIdx, minIdx, maxIdx, fixedIdx, notFixedIdx, nominalIdx, minNotReachedIdx, maxNotReachedIdx, absTolIdx, relTolIdx, discontChangeIdx) \
	{stateIdx, startIdx, minIdx, maxIdx, fixedIdx, notFixedIdx, nominalIdx, minNotReachedIdx, maxNotReachedIdx, absTolIdx, relTolIdx, discontChangeIdx},

#define GetSizeOfStateAttr_Head static int GetSizeOfStateAttr(void)
#define GetSizeOfStateAttr_Declare GetSizeOfStateAttr_Head ;

#define GetNumberOfBlocks_Head static int GetNumberOfBlocks()
#define GetNumberOfBlocks_Declare GetNumberOfBlocks_Head;

#define Declare_BlockSizes_None static ITI_BlockSizes blockSizes[1]; \
GetNumberOfBlocks_Head \
{ \
	return 0; \
} \
InitBlockVars_Begin \
InitBlockVars_End

#define Declare_BlockSizes_Begin static ITI_BlockSizes blockSizes[] = {
#define Declare_BlockSizes_End }; \
GetNumberOfBlocks_Head \
{ \
	return sizeof(blockSizes) / sizeof(blockSizes[0]); \
}

#define Declare_BlockSizes(ires, iDAE, iHybrid_Z_Real, iHybrid_Z_Int, iHybrid_Z_Str, iHybrid_Zf, nrDPBlock, isNonlinear) \
	{ires, iDAE, iHybrid_Z_Real, iHybrid_Z_Int, iHybrid_Z_Str, iHybrid_Zf, nrDPBlock, isNonlinear},

#define InitBlockVars_Head static void InitBlockVars(ITI_BlockData *bd)
#define InitBlockVars_Declare InitBlockVars_Head;
#define InitBlockVars_Begin InitBlockVars_Head {
#define InitBlockVars_End }

#define Declare_NumJacCols_None static ITI_int numJacColsData[1];
#define Declare_NumJacCols_Begin static ITI_int numJacColsData[] = {
#define Declare_NumJacCols_End };

#define Declare_DPBlock_None static ITI_uint DPBlockSizes[1];
#define Declare_DPBlock_Begin static ITI_uint DPBlockSizes[] = {
#define Declare_DPBlock_End };

#define Declare_Array_None static ITI_ArrayData arrayData[1];
#define Declare_Array_Begin static ITI_ArrayData arrayData[] = {
#define Declare_Array_End };
#define Declare_Array(nDims, nValues, memType) \
	{nDims, nValues, memType},

#define Declare_SeqInfo(name, n) \
		ITI_SeqInfoY name##_YInfo[n];

#define Declare_AxisInfo(name, n) \
		ITI_AxisInfo name##_AxisInfo[n];

#ifdef ITI_COMP_SIM
#define Declare_SimXCurveSetData(name, orig_name, nYScale , param_idx) \
		{0, 0, name##_YInfo, 0, 0, 0, #orig_name, nYScale, 0, param_idx},
#else
#define Declare_SimXCurveSetData(name, orig_name, nYScale) \
		{0, 0, name##_YInfo, 0, 0, 0, #orig_name, nYScale, 0},
#endif

#define Declare_SimXCurveNDData(name, orig_name, nYScale) \
		{0, 0, 0, name##_AxisInfo, 0, 0, 0, 0, 0, #orig_name, nYScale, 0},

#define Declare_IntSize(var, size) \
	pSize->var = size;

#define initial() initialFunction(&pPart->curr->sInfo)
#define terminal() terminalFunction(&pPart->curr->sInfo)
#define analysisTypeDetail() analysisTypeDetailFunction(&pPart->curr->sInfo)
#define analysisType() analysisTypeFunction(&pPart->curr->sInfo)
#define terminate(string) terminateFunction(string, &pPart->curr->sInfo)
#ifdef ITI_COMP_SIM
#define inAnimation() inAnimationFunction(&pPart->curr->sInfo)
#else
#define inAnimation() 0
#endif
#define GetIntMemory_M(size) GetIntMemory(&modelData->currMem, size)
#define GetRealMemory_M(size) GetRealMemory(&modelData->currMem, size)
#define GetStringPtrMemory_M(size) GetStringPtrMemory(&modelData->currMem, size)

#define ArrayAdd_M(a1, a2) ArrayAdd(&pPart->transient->sInfo, &modelData->currMem, a1, a2)
#define ArraySub_M(a1, a2) ArraySub(&pPart->transient->sInfo, &modelData->currMem, a1, a2)
#define ArrayMulReal_M(a, v) ArrayMulReal(&pPart->transient->sInfo, &modelData->currMem, a, v)
#define ArrayMulInt_M(a, v) ArrayMulInt(&pPart->transient->sInfo, &modelData->currMem, a, v)
#define ArrayDivReal_M(a, v) ArrayDivReal(&pPart->transient->sInfo, &modelData->currMem, a, v)
#define ArrayDivInt_M(a, v) ArrayDivInt(&pPart->transient->sInfo, &modelData->currMem, a, v)
#define ArrayMulMM_M(a1, a2) ArrayMulMM(&pPart->transient->sInfo, &modelData->currMem, a1, a2)
#define ArrayMulMV_M(a1, a2) ArrayMulMV(&pPart->transient->sInfo, &modelData->currMem, a1, a2)
#define ArrayMulVM_M(a1, a2) ArrayMulVM(&pPart->transient->sInfo, &modelData->currMem, a1, a2)
#define AddString_M(s1, s2) AddString(&modelData->currMem, s1, s2)
#define ArrayToString_M(arr) ArrayToString(&pPart->transient->sInfo, &modelData->currMem, arr)
#define RealToString_M(r, o1, o2, o3) RealToString(&pPart->transient->sInfo, &modelData->currMem, r, o1, o2, o3)
#define IntToString_M(i, o1, o2, o3) IntToString(&pPart->transient->sInfo, &modelData->currMem, i, o1, o2, o3)
#define BooleanToString_M(b, o1, o2) BooleanToString(&pPart->transient->sInfo, &modelData->currMem, b, o1, o2)
#define RealToStringFormat_M(r, f) RealToStringFormat(&pPart->transient->sInfo, &modelData->currMem, r, f)

#define GetIntMemory_F(size) GetIntMemory(&modelData->funcMem, size)
#define GetRealMemory_F(size) GetRealMemory(&modelData->funcMem, size)
#define GetStringPtrMemory_F(size) GetStringPtrMemory(&modelData->funcMem, size)
#define ReleaseFuncMemory() ReleaseAllMemory(&modelData->funcMem)

 
#define __STRING_ASSIGN(dest, src) AssignString(&modelData->strMem, (const ITI_char**)&dest, src)
#define __STRING_ASSIGN2(dest, src, index) AssignString2(&modelData->strMem, (const ITI_char**)&dest, src, (const ITI_char**)pPart->transient->v.strData, pPart->transient->v.strSize, index)
#define __Z_STRING_ASSIGN2(dest, src, index) AssignString2(&modelData->strMem, (const ITI_char**)&dest, src, (const ITI_char**)pPart->transient->z.strData, pPart->transient->z.strSize, index)
#define __V_STRING_ASSIGN2(dest, src, index) AssignString2(&modelData->strMem, (const ITI_char**)&dest, src, (const ITI_char**)pPart->transient->v.strData, pPart->transient->v.strSize, index)
#define __PRE_STRING_ASSIGN2(dest, src, index) AssignString2(&modelData->strMem, (const ITI_char**)&dest, src, (const ITI_char**)pPart->transient->pre_z.strData, pPart->transient->pre_z.strSize, index)
#define __SAVE_LOCAL_STR_MEM SaveCurrentBuffer(&modelData->strMem, STRING_TYPE);
#define __RESTORE_LOCAL_STR_MEM RestoreSavedBuffer(&modelData->strMem, STRING_TYPE);
#define __STRING_INIT(dest, size) InitString(&modelData->strMem, (const ITI_char**)&dest, size)
#define __STRING_INIT2(dest, size, index) InitString2(&modelData->strMem, (const ITI_char**)&dest, size, data->strLengths, index)
#define __STRING_CAT(dest, src) strcat(dest, src)

#define __ARRAY_NDIMS(arr) arr.nDims
#define __ARRAY_SIZE(arr, index) arr.dims[index-1]
#define __ARRAY_SIZE_V(arr) ArraySize(&modelData->currMem, arr)
#define __ARRAY_VECTOR(arr) ArrayVector(&modelData->currMem, arr)
#define __ARRAY_VECTOR_REAL(v) ArrayVectorReal(&modelData->currMem, v)
#define __ARRAY_VECTOR_INT(v) ArrayVectorInt(&modelData->currMem, v)
#define __ARRAY_MATRIX(arr) ArrayMatrix(&pPart->transient->sInfo, &modelData->currMem, arr)
#define __ARRAY_TRANSPOSE(arr) ArrayTranspose(&pPart->transient->sInfo, &modelData->currMem, arr)
#define __ARRAY_REF_TRANSPOSE(arr) ArrayRefTranspose(&pPart->transient->sInfo, &modelData->currMem, arr)
#define __ARRAY_OUTERPRODUCT(arr1, arr2) ArrayOuterProduct(&pPart->transient->sInfo, &modelData->currMem, arr1, arr2)
#define __ARRAY_CROSS(arr1, arr2) ArrayCross(&pPart->transient->sInfo, &modelData->currMem, arr1, arr2)
#define __ARRAY_SKEW(arr) ArraySkew(&pPart->transient->sInfo, &modelData->currMem, arr)
#define __ARRAY_SYMMETRIC(arr) ArraySymmetric(&pPart->transient->sInfo, &modelData->currMem, arr)
#define __ARRAY_LINSPACE(x1, x2, n) ArrayLinspace(&pPart->transient->sInfo, &modelData->currMem, x1, x2, n)
#define __ARRAY_MIN(arr) (arr.memType==REAL_TYPE?ArrayRealMin(arr):ArrayIntMin(arr))
#define __ARRAY_MAX(arr) (arr.memType==REAL_TYPE?ArrayRealMax(arr):ArrayIntMax(arr))
#define __ARRAY_SUM(arr) (arr.memType==REAL_TYPE?ArrayRealSum(arr):ArrayIntSum(arr))
#define __ARRAY_PRODUCT(arr) (arr.memType==REAL_TYPE?ArrayRealProduct(arr):ArrayIntProduct(arr))
#define __ARRAY_SCALAR(arr) (arr.memType==REAL_TYPE?ArrayRealScalar(&pPart->transient->sInfo, arr):ArrayIntScalar(&pPart->transient->sInfo, arr))
#define __ARRAY_DIAGONAL(arr) (arr.memType==REAL_TYPE?ArrayRealDiagonal(&pPart->transient->sInfo, &modelData->currMem, arr):ArrayIntDiagonal(&pPart->transient->sInfo, &modelData->currMem, arr))
#define __ARRAY_IDENTITY(n) ArrayIdentity(&modelData->currMem, n)
#define __ARRAY_ASSIGN(a1, a2) ArrayAssign(&modelData->currMem, &pPart->transient->sInfo, a1, a2)
#define __ARRAY_STRING_ASSIGN(a1, a2) ArrayAssign(&modelData->strMem, &pPart->transient->sInfo, a1, a2)
#define __ARRAY_UNARY_MINUS(arr) ArrayUnaryMinus(&modelData->currMem, arr)
#define __ARRAY_PROMOTE(arr, n) Promote(&modelData->currMem, arr, n)
#define __ARRAY_PROMOTE_REAL(x, n) RealPromoteScalar(&modelData->currMem, x, n)
#define __ARRAY_PROMOTE_INT(x, n) IntPromoteScalar(&modelData->currMem, x, n)
#define __ARRAY_COMPARE(a1,rel_op,a2) ArrayCompare(&pPart->transient->sInfo, a1, a2, rel_op)
#define __ARRAY_ARRAY_OP(a1, a2, op) ArrayArrayOp(&pPart->transient->sInfo, &modelData->currMem, a1, a2, op)
#define __ARRAY_SCALAR_OP_REAL(a, v, op, swap) ArrayScaleOpReal(&pPart->transient->sInfo, &modelData->currMem, op, a, v, swap)
#define __ARRAY_SCALAR_OP_REAL_SWAP(v, a, op) ArrayScaleOpReal(&pPart->transient->sInfo, &modelData->currMem, op, a, v, 0)
#define __ARRAY_SCALAR_OP_INT_SWAP(v, a, op) ArrayScaleOpInt(&pPart->transient->sInfo, &modelData->currMem, op, a, v, 0)
#define __SCALAR_ADD(v1, v2) (v1 + v2)
#define __ARRAY_SCALAR_OP_INT(a, v, op, swap) ArrayScaleOpInt(&pPart->transient->sInfo, &modelData->currMem, op, a, v, swap)
#define __ARRAY_CAST_TO_INT(a) CastArray(&pPart->transient->sInfo, &modelData->currMem, a, INT_TYPE)
#define __ARRAY_CAST_TO_REAL(a) CastArray(&pPart->transient->sInfo, &modelData->currMem, a, REAL_TYPE)
#define __ARRAY_CAST_TO_STR(a) CastArray(&pPart->transient->sInfo, &modelData->currMem, a, STRING_TYPE)
#define __ARRAY_APPLY_FUNC(func_ident, a) ApplyFuncOnArray(&pPart->transient->sInfo, &modelData->currMem, a, func_ident)
#define __ARRAY_SET_REAL(a, index, val) SetRealInArray(&pPart->transient->sInfo, a, index, val)
#define __ARRAY_SET_INT(a, index, val) SetIntInArray(&pPart->transient->sInfo, a, index, val)
#define __ARRAY_SET_STR(a, index, val) SetStrInArray(&pPart->transient->sInfo, a, index, val)

#define __GET_STATE_INDEX(stateVar) GetRealIndex(pPart->transient->x, &pPart->transient->size.ix, stateVar)

#define __triggerEvent() \
pPart->curr->sInfo.bEventTriggered = ITI_true;

#define __SOLVER_NEEDS_RESET \
pPart->curr->sInfo.bSolverNeedsReset = ITI_true;

#define Declare_InferenceGraph_Head DLL_Export void InitInferenceGraph(ITI_Partition* pPart, ITI_ModelData* data)
#define InferenceGraph_Declare Declare_InferenceGraph_Head ;
#define Declare_InferenceGraph_None Declare_InferenceGraph_Head {}
#define Declare_InferenceGraph_Begin Declare_InferenceGraph_Head {
#define Declare_InferenceGraph_End }

#define Declare_GraphInfo(idx, clockType) initInferenceGraph(&(pPart->transient->partitionIG[idx]), clockType, 0.0);
#define Declare_RootClock(idx,i,val) pPart->transient->partitionIG[idx].m_Roots[i]=val;
#define Declare_BaseClock(idx,i,val) pPart->transient->partitionIG[idx].m_BaseClocks[i]=val;

#define Declare_Node(id, nodeId, firstChld, numChldrn, ival, resolut, baseClk, constr) \
initNode(&(pPart->transient->partitionIG[id]), nodeId, firstChld, numChldrn, ival, resolut, baseClk, constr, data->currMem.allocateMemory);
#define Declare_Edge(id, nodeFrom, nodeTo, edgeId, neighbFrom, neighbTo, edgeT, factor, shift, alias, aliasFrom, path, constr) \
initEdge(&(pPart->transient->partitionIG[id]), nodeFrom, nodeTo, edgeId, neighbFrom, neighbTo, edgeT, factor, shift, alias, aliasFrom, path, constr, data->currMem.allocateMemory);

#define Declare_Path(id, pathIndex, firstStep, numSteps, firstNode, lastNode, isCycle) \
initPath(&(pPart->transient->partitionIG[id]), pathIndex, firstStep, numSteps, firstNode, lastNode, isCycle);

#define Declare_Step(id, stepIndex, stepInPath, nodeFrom, nodeTo, pathIndex, otherStep, edgeIndex, actsOnNominator) \
initStep(&(pPart->transient->partitionIG[id]), stepIndex, stepInPath, nodeFrom, nodeTo, pathIndex, otherStep, edgeIndex, actsOnNominator);

#define Declare_PartitionData_Head DLL_Export void GetPartitionData(ITI_Partition* pPart, ITI_ModelData* modelData)
#define GetPartitionData_Declare Declare_PartitionData_Head ;
#define Declare_PartitionData_Begin Declare_PartitionData_Head {
#define Declare_PartitionData_End }

#define Declare_Partition(cpt, pid, bcid, scid, sa, hc, activ, p, c, sm, iv, ec) \
	pPart->transient->partitionData[pid].type=cpt; \
	pPart->transient->partitionData[pid].id=pid; \
	pPart->transient->partitionData[pid].baseid=bcid; \
	pPart->transient->partitionData[pid].subid=scid; \
	pPart->transient->partitionData[pid].sampleActive=sa; \
	pPart->transient->partitionData[pid].holdChanged=hc; \
	pPart->transient->partitionData[pid].activated=activ; \
	pPart->transient->partitionData[pid].periodic=p; \
	pPart->transient->partitionData[pid].continous=c; \
	pPart->transient->partitionData[pid].solvermethod=sm; \
	pPart->transient->partitionData[pid].interval=iv; \
	pPart->transient->partitionData[pid].eventClock=ec; 

#define UpdateInferenceGraph_Head static ITI_SolverState UpdateInferenceGraph(ITI_Partition* pPart, ITI_ModelData* modelData)
#define UpdateInferenceGraph_None UpdateInferenceGraph_Head {return SOLVER_SUCCESS_END;}
#define UpdateInferenceGraph_Begin UpdateInferenceGraph_Head {
#define UpdateInferenceGraph_End return SOLVER_SUCCESS_END;}

#define update_ignode(idx,nidx,interval,resolution,ticks,maxticks) \
	updateIGNode(&(pPart->transient->partitionIG[idx]),nidx,interval,resolution,ticks,maxticks)

#define update_igedge(idx,eidx,factor,shift) \
	updateIGEdge(&(pPart->transient->partitionIG[idx]),eidx,factor,shift)

#define LoadInferenceGraphResults_Head static ITI_SolverState LoadInferenceGraphResults(ITI_Partition* pPart, ITI_ModelData* modelData)
#define LoadInferenceGraphResults_None LoadInferenceGraphResults_Head {return SOLVER_SUCCESS_END;}
#define LoadInferenceGraphResults_Begin LoadInferenceGraphResults_Head {
#define LoadInferenceGraphResults_End return SOLVER_SUCCESS_END;}

#define PerformBaseIntervalUpdate_Head static void PerformIntervalUpdate(ITI_Partition* pPart, ITI_int graphIndex)
#define PerformBaseIntervalUpdate_None PerformBaseIntervalUpdate_Head { }
#define PerformBaseIntervalUpdate_Begin PerformBaseIntervalUpdate_Head {
#define PerformBaseIntervalUpdate_End }

#define update_BaseInterval(idx,nidx,binterval) \
	updateNodeInterval(&(pPart->transient->partitionIG[idx]),nidx,binterval)

#define loadres_BaseInterval(idx,binterval) \
	loadResult_BaseInterval(&(pPart->transient->partitionIG[idx]),binterval)

#define loadres_ignode(idx,nidx,interval,maxTicks,ticks,activated) \
	loadResult_ClockInference(&(pPart->transient->partitionIG[idx]),nidx,interval,maxTicks,ticks,activated)

#define GetPartitionAccess_Head DLL_Export void GetPartitionAccess(ITI_PartFunctions* _partitions)
#define GetPartitionAccess_Declare GetPartitionAccess_Head ;
#define GetPartitionAccess_Begin GetPartitionAccess_Head {
#define GetPartitionAccess_End }

#define Factory_Partition_Access_Init_Name(pidx) FactoryPartitionAccessInit_##pidx
#define Factory_Partition_Access_Init_Head(pidx) void Factory_Partition_Access_Init_Name(pidx)(ITI_PartFunctions* _partition)
#define Factory_Partition_Access_Init_Begin(pidx) Factory_Partition_Access_Init_Head(pidx) {
#define Factory_Partition_Access_Init_End }

#define Factory_Partition_Access_Main_Name(pidx) FactoryPartitionAccessMain_##pidx
#define Factory_Partition_Access_Main_Head(pidx) void Factory_Partition_Access_Main_Name(pidx)(ITI_PartFunctions* _partition)
#define Factory_Partition_Access_Main_Begin(pidx) Factory_Partition_Access_Main_Head(pidx) {
#define Factory_Partition_Access_Main_End }

#define DeclareFactoryPartitionAccessDecl(pidx) Factory_Partition_Access_Decl_Name(pidx)(&(_partitions[pidx]));
#define Factory_Partition_Access_Decl_Name(pidx) FactoryPartitionAccessDecl_##pidx
#define Factory_Partition_Access_Decl_Head(pidx) void Factory_Partition_Access_Decl_Name(pidx)(ITI_PartFunctions* _partition)
#define Factory_Partition_Access_Decl_End }

#define DeclareFactoryPartitionAccessInit(pidx) {\
extern Factory_Partition_Access_Init_Head(pidx);\
Factory_Partition_Access_Init_Name(pidx)(&(_partitions[pidx]));}

#define DeclareFactoryPartitionAccessMain(pidx) {\
extern Factory_Partition_Access_Main_Head(pidx);\
Factory_Partition_Access_Main_Name(pidx)(&(_partitions[pidx]));}

#define Factory(function) _partition->function = function;

 
 
 
 

#define DECLARE_BPARTITION_STATICS_INIT(pidx) \
Factory_Partition_Access_Init_Begin(pidx) \
Factory_Partition_Access_Init_End



#endif  
