/**
 * ITI_Declarations.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#ifndef _ITI_DECLARATIONS_H_
#define _ITI_DECLARATIONS_H_

#include "ITI_DeclarationsBase.h"

#define __azf(index,b,cond,e1,e2) \
if(cond){ \
	if(b) __ITI_UpdateEpsilonOsZF(pPart->curr, index); \
	__ITI_AssignZF((e1),(e2),index,pPart->curr); \
	pPart->curr->ezf[index]=1; \
	pPart->curr->czf[index]=1;} \
else \
	pPart->curr->czf[index]=0;

#define __szf(index) pPart->curr->szf[index]

#define Ith(v,i) NV_Ith_S(v,i)

#define __IF_IS_EVENT if (_sInfo.isEvent)

#define ResolveResource(strFile) \
__ITI_ResolveResourceFolder(pPart->curr, Param_Passing_SimData, strFile)

#define GetRecordSize_Head size_t GetRecordSize()
#define GetRecordSize_Declare GetRecordSize_Head;

#if (defined(ITI_COMP_SIM) || defined(ITI_CE_EXEC_MODEL)) && !defined(_OPENMP)
#define S_PERF_T StartPerformanceTiming(pPart->curr->performanceData, -1);
#define E_PERF_T EndPerformanceTiming(pPart->curr->performanceData, -1);
#else
#define S_PERF_T
#define E_PERF_T
#endif

#ifdef _MSC_VER

#ifdef FD_BEGIN
#undef FD_BEGIN
#endif
#define FD_BEGIN \
	UnmaskExceptions(&modelData->oldCW, &modelData->oldHandler);\
	S_PERF_T\
	CHECK_REAL_INPUTS\
	__try {

#else

#ifdef FD_BEGIN
#undef FD_BEGIN
#endif
#define FD_BEGIN \
	UnmaskExceptions(&modelData->oldCW, &modelData->oldHandler);\
	_sInfo.allowJump = ITI_true;\
	_sInfo.allowBlockJump = ITI_false;\
	S_PERF_T\
	CHECK_REAL_INPUTS\
	if (setjmp(_sInfo.buf) == 0) {

#endif

#ifndef isfinite
#ifdef _MSC_VER
#define isfinite _finite
#elif defined(__gnu_linux__)
#define isfinite finite
#else
#define isfinite ITI_finite
#endif
#endif

#ifdef InitializeConditions_Begin
#undef InitializeConditions_Begin
#endif
#define InitializeConditions_Begin InitializeConditions_Head {\
	FIC_BEGIN

#ifdef CalcDerivatives_End
#undef CalcDerivatives_End
#endif
#define CalcDerivatives_End FD_END

#define GetModelSizes_Head void GetModelSizes(ITI_AllocateMemory allocateMemory, ITI_ModelSize* pSize)
#define GetModelSizes_Declare GetModelSizes_Head ;
#define Declare_ModelSizes_Begin GetModelSizes_Head \
{pSize->numBlocks = GetNumberOfBlocks(); pSize->numStateAttr = GetSizeOfStateAttr();
#define Declare_ModelSizes_End }
#define GetPartitionSizes_Head static void GetPartitionSizes(ITI_AllocateMemory allocateMemory, ITI_ModelSize* pSize)
#define GetPartitionSizes_Declare GetPartitionSizes_Head ;
#define Declare_PartitionSizes_Begin GetPartitionSizes_Head \
{pSize->numBlocks = GetNumberOfBlocks(); pSize->numStateAttr = GetSizeOfStateAttr();
#define Declare_PartitionSizes_End }
#define ValidStep_End F_END

#define Declare_Jacobian_A_Pattern_Head static void GetJacobianAPattern(ITI_Partition* pPart, ITI_ModelData* modelData, ITI_char* pat)
#define Declare_Jacobian_A_Pattern_Declare Declare_Jacobian_A_Pattern_Head ;
#define Declare_Jacobian_A_Pattern_Begin Declare_Jacobian_A_Pattern_Head {
#define Declare_Jacobian_A_Pattern_End }

#define _JAP(m, n, k) pat[m*pPart->curr->size.ix+n]=k;

#define Declare_StateNames_Head static void GetStateNames(ITI_Partition* pPart)
#define Declare_StateNames_None Declare_StateNames_Head {}
#define Declare_StateNames_Begin Declare_StateNames_Head {
#define Declare_StateNames_End }

#define Declare_StateName(n,name,synonyms)	pPart->curr->stateNames[n] = name;
#define Declare_DStateName(n,name)	pPart->curr->dstateNames[n] = name;

#define CLOCKED_INIT(clockid) InitializeConditionsPartitionComplete(clockid, _sInfo.pSolverData);

#define Factory_Partition_Access_Decl_Begin(pidx) Factory_Partition_Access_Decl_Head(pidx) { \
_partition->parameters = parameters; \
_partition->parametersArr = parametersArr; \
_partition->arrayData = arrayData; \
_partition->dataZF = dataZF; \
_partition->curveSets = curveSets; \
_partition->curveNDs = curveNDs; \
_partition->blockSizes = blockSizes; \
_partition->stateAttributes = stateAttributes; \
_partition->seqCsSizes = seqCsSizes; \
_partition->delayInfos = delayInfos; \
_partition->_hyst_init_data = _hyst_init_data; \
_partition->numJacColsData = numJacColsData; \
_partition->DPBlockSizes = DPBlockSizes;

#define __reinit(state, index, val) \
if(state!=val) \
{ \
	state = val;\
	__SOLVER_NEEDS_RESET\
} \

GetModelSizes_Declare
InferenceGraph_Declare
GetPartitionData_Declare
GetPartitionAccess_Declare
AllocateRecords_Declare
FreeRecords_Declare
GetRecordSize_Declare

#define DECLARE_STATICS_DECL(pidx) \
Factory_Partition_Access_Decl_Begin(pidx) \
Factory(SampleFunction) \
	Factory(InitBlockVars) \
	Factory(GetJacobianAPattern)\
	Factory(GetStateNames)\
	Factory(GetModelInfo) \
Factory_Partition_Access_Decl_End

#define DECLARE_BPARTITION_STATICS_DECL(pidx) \
Factory_Partition_Access_Decl_Begin(pidx) \
	Factory(GetPartitionSizes) \
	Factory(GetModelInfo) \
Factory_Partition_Access_Decl_End

#define DECLARE_PARTITION_STATICS_DECL(pidx) \
Factory_Partition_Access_Decl_Begin(pidx) \
	Factory(GetPartitionSizes) \
	Factory(SampleFunction) \
	Factory(InitBlockVars) \
	Factory(GetJacobianAPattern)\
	Factory(GetStateNames)\
	Factory(GetModelInfo) \
Factory_Partition_Access_Decl_End

#define DECLARE_STATICS(pidx) \
Factory_Partition_Access_Main_Begin(pidx) \
	Factory(CalcDerivatives) \
	Factory(CalcOutputs) \
	Factory(SynchOutputs) \
	Factory(ValidStep) \
	Factory(AssignLastVar) \
	Factory(AssignDiscreteReal) \
	Factory(Terminate) \
	Factory(PreActivation) \
	Factory(PostActivation) \
Factory_Partition_Access_Main_End

#define DECLARE_BPARTITION_STATICS(pidx) \
Factory_Partition_Access_Main_Begin(pidx) \
	Factory(PreActivation) \
	Factory(PostActivation) \
	Factory(PerformIntervalUpdate) \
Factory_Partition_Access_Main_End

#define DECLARE_PARTITION_STATICS(pidx) \
Factory_Partition_Access_Main_Begin(pidx) \
	Factory(CalcDerivatives) \
	Factory(CalcOutputs) \
	Factory(SynchOutputs) \
	Factory(ValidStep) \
	Factory(AssignLastVar) \
	Factory(AssignDiscreteReal) \
	Factory(Terminate) \
	Factory(PreActivation) \
	Factory(PostActivation) \
Factory_Partition_Access_Main_End

#define DECLARE_STATICS_INIT(pidx) \
Factory_Partition_Access_Init_Begin(pidx) \
	Factory(InitializeConstants) \
	Factory(InitializeParameterDependent) \
	Factory(InitializeTunableParameter) \
	Factory(Initialize) \
	Factory(InitializeConditions) \
	Factory(UpdateInferenceGraph) \
	Factory(LoadInferenceGraphResults) \
Factory_Partition_Access_Init_End \
AllocateRecords_Head\
{if (pPart->curr->size.iRec > 0)pPart->curr->pRecord = (ITI_void*)calloc(1, sizeof(ITI_Records)); } \
GetRecordSize_Head \
{return sizeof(ITI_Records);}

#define DECLARE_PARTITION_STATICS_INIT(pidx) \
Factory_Partition_Access_Init_Begin(pidx) \
	Factory(InitializeTunableParameter) \
	Factory(Initialize) \
	Factory(InitializeConditions) \
Factory_Partition_Access_Init_End


#endif
