/**
 * ITI_Types.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#if !defined(_ITI_Types)
#define _ITI_Types

#ifdef __cplusplus
extern "C" {
#endif

#include <limits.h>
#include <float.h>
#include <setjmp.h>
#include <stdlib.h>

#define SimData ITI_ModelData


#ifdef ITI_SIMULINK_S_FUNC
#include "simstruc.h"
#define ITI_void	void
#define ITI_real	real_T
#define ITI_int		int_T
#define ITI_uint	uint_T
#define ITI_char	char_T
#define ITI_bool	char_T
#define ITI_ushort	unsigned short
#define ITI_uchar	unsigned char
#define ITI_long	long int
#define ITI_big_uint uint_T
#define ITI_big_uint_max UINT_MAX
#define ITI_shared	real_T
#else
#define ITI_void	void
#define ITI_real	double
#define ITI_int		int
#define ITI_bool	char
#define ITI_uint	unsigned int
#define ITI_ushort	unsigned short
#define ITI_uchar	unsigned char
#define ITI_char	char
#define ITI_long	long int
#define ITI_big_uint unsigned int
#define ITI_big_uint_max UINT_MAX
#define ITI_shared	double
#endif

#define ITI_big_uint_size 3

typedef struct {
	ITI_big_uint v[ITI_big_uint_size];
} ITI_bui;

typedef struct {
	ITI_big_uint v[ITI_big_uint_size];
	int s;
} ITI_bi;

#define ITI_true	1
#define ITI_false	0

#define ITI_TRACE_STRING_SIZE 10000
#define ITI_WARNING_STACK_SIZE 5

#define ITI_INTERFACE_VERSION 4.208

typedef enum ITI_SolverAction {
	SOLVER_INITIALIZE = 0,
	SOLVER_INITIALIZE_CONDITIONS = 1,
	SOLVER_INITIALIZE_SOLVER = 2,
	SOLVER_OVERTIME = 3,
	SOLVER_EVENTITER = 4,
	SOLVER_INTERPOLATE_PREPARE = 5,
	SOLVER_INTERPOLATE = 6,
	SOLVER_INTERPOLATE_EXIT = 7,
	SOLVER_UPDATE_DATA = 8,
	SOLVER_CHECK_EVENT = 9,
	SOLVER_EVENT_ITERATION_PREPARE = 10,
	SOLVER_EVENT_ITERATION = 11,
	SOLVER_EVENT_ITERATION_EXIT = 12,
	SOLVER_CHECK_END_TIME = 13,
} ITI_SolverAction;

typedef enum ITI_SolverState {
	SOLVER_TERMINATED = 2,
	SOLVER_SUCCESS_CONTINUE = 1,
	SOLVER_SUCCESS_END = 0,
	SOLVER_ERROR = -1,
	SOLVER_CYCLE_IN_EVENT_ITERATION = -2,
	SOLVER_ERROR_IN_INITIALIZATION  = -3,
	SOLVER_ERROR_IN_INITIALIZATION_AFTERDISCONTINUITY = -4,
	SOLVER_CYCLE_IN_EVENT_ITERATION_AT_START = -5,
	SOLVER_ERROR_CREATE_INSTANCE = -6,
	SOLVER_ERROR_IN_ON_SET_INPUTS = -7,
} ITI_SolverState;

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#define DBL_EPSILON_SQR (DBL_EPSILON*DBL_EPSILON)
#define V_EPSILON (DBL_EPSILON*10.0)
#define NHYSTZERO 7  
#define MW_IDX 0
#define LO_IDX 2
#define HI_IDX 1
#define __MAX_PERT 0.001

typedef void TRACE_FUNC(int, int, const char*, const char*, const void*);

 
#ifndef MAX_ERROR_LENGTH
#define MAX_ERROR_LENGTH 1000
#endif

 
typedef enum ITI_PartitionSolverMethod {
	UnknownSolver = -1,
	External,
	ExplicitEuler,
	ExplicitEulerInline,
	ExplicitMidPoint2,
	ExplicitRungeKutta4,
	ImplicitEuler,
	ImplicitEulerInline,
	ImplicitTrapezoid,
	ImplicitTrapezoidInline,
	InvalidSolver
} ITI_PartitionSolverMethod;

 
typedef enum ITI_ClockInferenceState {
	noError = 0,
	warningUnsupportedSolver,
	warningSolverInference,
	warningBaseClock,
	errorSolverInference,
	errorMissmatchFactors,
	errorWrongDirection,
	errorNotDivisible,
	errorUnknownFactor,
	errorMissmatchBaseClocks,
	errorCycleInconsistent,
	errorNegativeShift,
	errorNoMemory
} ITI_ClockInferenceState;

enum {
	SimulationTab = 0,
	FileTab = 1
};

enum {
	Info = 0,
	Warning = 1,
	Error = 4,
	Debug = 5
};

typedef ITI_real ITI_real2[2];

enum MemoryType {
	UNKNOWN_TYPE,
	INT_TYPE,
	REAL_TYPE,
	STRING_TYPE,
	STRING_PTR_TYPE
};

 
enum ITI_SimX_TraceMsgType {
	SimX_info = 0,
	SimX_warning = 1,
	SimX_stop = 2,
	SimX_question = 3,
	SimX_error = 4,
	SimX_debug = 5,
	SimX_none = 6,
	SimX_msgtype_size = 7
};

typedef struct ITI_SimX_TraceMsg {
	enum ITI_SimX_TraceMsgType type;
	ITI_char shortMsg[100];
	ITI_char longMsg[ITI_TRACE_STRING_SIZE];
	ITI_ushort isNewMSg;
} ITI_SimX_TraceMsg;

typedef struct ITI_WarningStack {
	ITI_int size;
	ITI_int lastMsg;
	ITI_SimX_TraceMsg msg[ITI_WARNING_STACK_SIZE];
} ITI_WarningStack;

 
enum SaveOutputsBits {
	SaveOutputsNoneBit =                           0,
	SaveOutputsAllBit =                            2,
	SaveOutputsEquidistantBit =                    4,
	SaveOutputsAtleastwithdtProtBit =              8,
	SaveOutputsAtleastwithdtProtPostEventsBit =    16,
	SaveOutputsAtleastwithdtProtPrePostEventsBit = 32,
	SaveOutputsAtleastwithdtProtAllEventStepsBit = 64,
	SaveOutputsLastValueBit =                      128,
	SaveOutputsEquidistantPostEventsBit =          256,
	SaveOutputsEquidistantPrePostEventsBit =       512,
	SaveOutputsEquidistantAllEventStepsBit =       1024,
	SaveOutputsAfterDoStepBit =                    2048
};

enum SimX_ProtKind {
	SimX_PK_All,
	SimX_PK_EquidistantTimeSteps,
	SimX_PK_MinTimeStepsNoEvents,
	SimX_PK_MinTimeStepsPostEvents,
	SimX_PK_MinTimeStepsPrePostEvents,
	SimX_PK_MinTimeStepsAllEventSteps,
	SimX_PK_LastValue,
	SimX_PK_EquidistantTimeStepsPostEvents,
	SimX_PK_EquidistantTimeStepsPrePostEvents,
	SimX_PK_EquidistantTimeStepsAllEventSteps,
	SimX_PK_AfterDoStep
};

enum SaveOutputsApproach {
	SaveOutputsAll = 0,
	SaveOutputsEquidistant = 1,
	SaveOutputsAtleastwithdtProt = 2,
	SaveOutputsAtleastwithdtProtPostEvents = 3,
	SaveOutputsAtleastwithdtProtPrePostEvents = 4,
	SaveOutputsAtleastwithdtProtAllEventSteps = 5,
	SaveOutputsLastValue = 6,
	SaveOutputsEquidistantPostEvents = 7,
	SaveOutputsEquidistantPrePostEvents = 8,
	SaveOutputsEquidistantAllEventSteps = 9,
	SaveOutputsAfterDoStep = 10
};

enum SharedType {
	SharedType_Int = 0,
	SharedType_Real = 1,
	SharedType_Str = 2,
	SharedType_Synch = 3
};

enum DelayValueType {
	DelayValueType_Int = 0,
	DelayValueType_Real = 1
};

enum VarDataKind {
	VDK_Default = 0,
	VDK_OdeStateSimX = 1,
	VDK_OdeStateVirtual = 2,
	VDK_OdeStateDp = 3,
	VDK_DiscreteSimX = 4,
	VDK_DiscreteVirtual = 5,
	VDK_DiscreteAttr = 6,
	VDK_StartAttr = 7,
	VDK_FormerAttr = 8,
	VDK_IV = 9,
	VDK_IZ = 10,
	VDK_IP = 11,
	VDK_BlockStateVar = 12,
	VDK_ClockActivated = 13
};

enum AssertionLevel {
	AL_Error = 0,
	AL_Warning = 1
};

enum BlockMemoryAllocStrategy {
	UseFreeSpaceInOtherBlocks = 0,
	DontUseSpaceInOtherBlocks = 99
};

enum ITI_Relation {
	Rel_LT = 0,
	Rel_LE = 1,
	Rel_GT = 2,
	Rel_GE = 3,
	Rel_EQ = 4,
	Rel_NE = 5
};

enum ClockPartitionType {
	CPT_BaseClock = 0,
	CPT_SubClock = 1
};

typedef struct ITI_CompositeData {
#ifdef ITI_COMP_SIM
	ITI_real** realData;
#else
	ITI_real* realData;
#endif
	ITI_int* intData;
	ITI_char** strData;
	size_t* strSize;
} ITI_CompositeData;

typedef void (*SetInputsFunc)(ITI_CompositeData* pu, ITI_real t);

typedef struct ITI_varData {
	ITI_char* name;
	ITI_int index;
	ITI_int arrayIndex;
	ITI_char* dim;
	enum SharedType type;
	enum VarDataKind kind;
	ITI_char* recArrayIndex;
} ITI_varData;

typedef struct ITI_xData {
	ITI_char* name;
	enum VarDataKind kind;
	ITI_int it;		 
	ITI_int ii;		 
	ITI_int nd;		 
	ITI_int nod;	 
	ITI_int id;		 
	ITI_bool ift;	 
	ITI_bool ia;	 
	ITI_bool ida;	 
	ITI_bool idn;	 
	ITI_int inds;	 
	ITI_int iids;	 
	ITI_bool iif;	 
	ITI_bool il;     

	ITI_char* dim;	 
	ITI_int arrayIndex;	 
	ITI_char* recArrayIndex;
} ITI_xData;

typedef struct ITI_resData {
	ITI_int i;				 
	ITI_bool init;			 
	ITI_bool ia;			 
	ITI_int ie;				 
	ITI_bool fi;			 
	ITI_bool iorig; 		 
} ITI_resData;


typedef struct ITI_zerofunctionData {
	ITI_char* name;
	ITI_int index;
	ITI_char* parentIdent;
	enum ITI_Relation rel;
	ITI_uint needHysterese;
	ITI_char* expression;
} ITI_zerofunctionData;

typedef struct ITI_SynchStrsDataItem {
	ITI_char*** modelStrs;
	ITI_void** simxStrs;
	ITI_void** simxStrVars;
	ITI_int* simxStrSizes;
	ITI_uint size;
	ITI_uint* indices;
} ITI_SynchStrsDataItem;

typedef struct ITI_SynchStrsData {
	ITI_SynchStrsDataItem pStrData;
	ITI_SynchStrsDataItem zStrData;
	ITI_SynchStrsDataItem pre_zStrData;
	ITI_SynchStrsDataItem vStrData;
	ITI_SynchStrsDataItem clocksvStrData;
} ITI_SynchStrsData;

typedef struct ITI_MemoryBlock {
	struct ITI_MemoryBlock* nextBlock;
	ITI_char* currBuffer;
	ITI_char* startBuffer;
	ITI_char* endBuffer;
	ITI_char* saveBuffer;
	enum MemoryType memType;
} ITI_MemoryBlock;

typedef void* (*ITI_AllocateMemory)(size_t nobj, size_t size);
typedef void  (*ITI_FreeMemory)(void* obj);

typedef struct ITI_MemoryObject {
	ITI_AllocateMemory allocateMemory;
	ITI_FreeMemory freeMemory;
	ITI_MemoryBlock* currentIntBlock;
	ITI_MemoryBlock* firstIntBlock;
	ITI_MemoryBlock* currentRealBlock;
	ITI_MemoryBlock* firstRealBlock;
	ITI_MemoryBlock* currentStringBlock;
	ITI_MemoryBlock* firstStringBlock;
	ITI_char* flatMemory;
	enum BlockMemoryAllocStrategy allocStrategy;
} ITI_MemoryObject;

typedef struct ITI_TraceData {
	ITI_uint len;
	ITI_char* line;
	ITI_char* line_ext;
	ITI_char* buffer;
	ITI_char* temp;
	ITI_char* temp2;
	ITI_char* start;
	ITI_MemoryObject memObj;
	ITI_MemoryObject memObj2;
	ITI_MemoryObject memObj3;
	ITI_int* pTraceOn;
} ITI_TraceData;

typedef void (*ITI_UpdateStrDataInSimxFunc)(ITI_SynchStrsData* sStrData);

typedef struct ITI_InputData {
	ITI_char* name;
	ITI_char* comment;
	ITI_real defaultValue;
	ITI_bool bInterpol;
	ITI_bool bDirectThrough;
	ITI_char* signalName;
	ITI_int paramType;
	enum SharedType type;
	ITI_int typeIndex;
} ITI_inputData;

typedef struct ITI_OutputData {
	ITI_char* name;
	ITI_char* comment;
	ITI_char* unit;
	ITI_char* signalName;
	enum SharedType type;
	ITI_int typeIndex;
} ITI_outputData;

typedef struct ITI_ParameterData {
	ITI_char* name;
	ITI_char* comment;
	ITI_shared defaultValue;
	ITI_char* unit;
	ITI_char* signalName;
	ITI_int paramType;
	enum SharedType valType;
} ITI_parameterData;

typedef struct ITI_ArrayData {
	ITI_uint nDims;
	ITI_uint nValues;
	enum MemoryType memType;
} ITI_ArrayData;

typedef struct ITI_Data_Array {
	ITI_char* name;
	ITI_char* comment;
	ITI_char* altName;
	ITI_char* unit;
	ITI_char* dims;
	ITI_uint nDims;
	enum SharedType valType;
} ITI_Data_Array;

enum Interpol {
	InterpolNone,
	InterpolLinear,
	InterpolSpline,
	InterpolStairs,
	InterpolHyperbolicApprox,
	InterpolCircualArcApprox,
	InterpolQuadraticApprox
};

enum Extrapol {
	ExtrapolNull,
	ExtrapolLinear,
	ExtrapolConstant,	 
	ExtrapolMirror,
	ExtrapolMirrorLinear,
	ExtrapolCycle
};

enum HystMode {
	HystModeDiscontHorizontal,
	HystModeDiscontVertical,
	HystModeContinous
};

enum HystStartValue {
	HystStartValueUpper,
	HystStartValueLower,
	HystStartValueMeanValue,
	HystStartValueStartValue
};

typedef struct ITI_SeqInfoY {
	enum Interpol iPol : 5;
	ITI_real param;
	ITI_bool bExtrapol : 1;
	ITI_bool bCycle : 1;
	ITI_bool bMirror : 1;
} ITI_SeqInfoY;

typedef struct ITI_AxisInfo {
	enum Interpol iPol : 5;
	ITI_bool bExtrapol : 1;
	ITI_bool bCycle : 1;
	ITI_bool bMirror : 1;
} ITI_AxisInfo;

typedef struct ITI_YScale {
	ITI_real scale;
	ITI_bool bScaleInitialized;
} ITI_YScale;

typedef struct ITI_CurveSetData {
	ITI_uint size;
	ITI_uint nY;
	ITI_SeqInfoY* yInfo;
	ITI_real* pX;
	ITI_real** pY;
	ITI_real*** pYCoeff;
	ITI_char* name;
	ITI_uint nYScale;
	ITI_YScale* pYScale;
	ITI_int curveParamIndex;
} ITI_CurveSetData;

typedef struct ITI_CurveData_ND {
	ITI_uint sizeX;
	ITI_uint sizeY;
	ITI_uint sizeZ;
	ITI_AxisInfo* axisInfo;
	ITI_real* pX;
	ITI_real* pY;
	ITI_real* pZ;
	ITI_real* pVal;
	ITI_real*** pYCoeff;
	ITI_char* name;
	ITI_uint nYScale;
	ITI_YScale* pYScale;
} ITI_CurveData_ND;

typedef struct ITI_SeqCallState {
	ITI_int iPos;
	ITI_int nCycle;
	ITI_bool bExtra;
	ITI_bool bMirror;
} ITI_SeqCallState;

typedef struct ITI_CurveCallState {
	ITI_SeqCallState* pSeqCs;
} ITI_CurveCallState;

typedef struct ITI_HystCurveCallState {
	ITI_SeqCallState* pSeqCs;
	ITI_real lastY;
	 
	ITI_real lastYCi;
	 
	ITI_int direction;
	ITI_real yTurnBack;
	ITI_real xTurnBack;
	ITI_real lambdaTurnBack;
	ITI_bool bInitialized;
} ITI_HystCurveCallState;

typedef struct ITI_AnimationData {
	ITI_real* realDelayData;
	ITI_int* intDelayData;
} ITI_AnimationData;

typedef struct ITI_AssertData {
	ITI_uchar* assertState1;
	ITI_uchar* assertState2;
	ITI_uchar* assertStateR;
	ITI_uchar* assertStateW;
	ITI_char** warnMsg;
	ITI_char** condMsg;
	ITI_bool bAssertStateChanged;
	ITI_bool bAssertError;
	size_t n;
} ITI_AssertData;

typedef struct {
	ITI_bool trDiscrete;
	ITI_bool trDummyPivoting;
	ITI_bool trZeroFct;
	ITI_bool trZeroFctTime;
	ITI_bool trZeroFctTime2;
	ITI_bool trFindDiscont;
	ITI_bool trStartEventStep;
	ITI_bool trEndEventStep;
	ITI_bool trEndEventIter;
	ITI_bool trTimerSet;
	ITI_bool trTimerExpired;
	 
	ITI_bool trResult;
	ITI_bool trIdo;
	ITI_bool trRes;
	ITI_bool trStates;
	ITI_bool trDer;
	ITI_bool trNewtonUpdate;
	ITI_bool trJac;
	ITI_bool trIndex;
	ITI_bool trStateBounds;
	ITI_bool trErrorsLinSystem;
	 
	ITI_bool trStepTrue;
	ITI_bool trResTrue;
	ITI_bool trStatesTrue;
	ITI_bool trDerTrue;
	 
	ITI_bool trStepFalse;
	ITI_bool trResFalse;
	ITI_bool trStatesFalse;
	ITI_bool trDerFalse;
	ITI_bool trNewtonUpdateFalse;
	ITI_bool trBlockStatistics;
	 
	ITI_bool trHomotopyStepSize;
	ITI_bool trHomotopyTangentSpace;
} ITI_TraceFlags;

typedef struct ITI_SolverSettings {
	ITI_real fromFile;
	ITI_real tStart;
	ITI_real tStop;
	ITI_real dtMin;
	ITI_real dtMax;
	ITI_real dtDetect;
	ITI_real absTol;
	ITI_real relTol;
	ITI_real dtProtMin;
	ITI_int mode;
	ITI_bool bStopAtStop;
	ITI_int influence;
	ITI_int zeros;
	ITI_int eventHandlingMode;
	ITI_int saveMode;
	enum SaveOutputsBits saveModeB;
	ITI_real trace;
	ITI_bool limitdtMin;
	ITI_int effJac;
	ITI_bool parJac;
	ITI_int maxOrder;
	ITI_real gltol;
	ITI_int linSolv;
	ITI_int threadLimit;
	ITI_bool ignoreMinMax;
	ITI_bool minmax;
	ITI_int maxStepNumberBetweenJacobianEvaluations;
	ITI_bool hysteresis;
	ITI_bool scaleEpsilon;
	ITI_bool adaptEpsilon;
	ITI_real epsilon;
	ITI_real maxEpsilon;
	ITI_bool adaptThreshold;
	ITI_bool adaptFactor;
	ITI_bool useInitFile;
	ITI_bool consistentInitialConditions;
	ITI_bool bAssertOn;
	ITI_bool bAssertTraceOn;
	ITI_bool bStopOnError;
}ITI_SolverSettings;

typedef void(*ITI_SetZeroFunctionBDFfunc)(void* pVoid, size_t index, double v1, double v2);
typedef double(*ITI_GetDelayValueBDFfunc)(void* pVoid, size_t index, double v, double tDelay, double t);
typedef double(*ITI_GetImpactBDF)(void* pVoid, size_t index);
typedef void(*DoClockTickFunc)(size_t pid, void* solverData);
typedef void(*DoClockedInitFunc)(size_t pid, void* solverData);
typedef void(*NextClockTickFunc)(size_t pid, void* solverData, const double nextActivationTime);
typedef void(*IntegratePartitionFunc)(size_t pid, void* solverData, const double nextActivationTime);

typedef struct ITI_TimeTriggeredClock {
	ITI_real nextTickTime;
	ITI_ushort bTick;
} ITI_TimeTriggeredClock;

typedef struct ITI_SolverInfo {
	ITI_bool bSolverNeedsReset;
	ITI_bool bEventTriggered;
	ITI_bool bDPAllowed;
	ITI_bool bDPRequired;
	ITI_bool bDPHappened;
	ITI_bool bSetImpactCalled;
	ITI_bool bInitializeConditions;
	ITI_bool isFirstRhsCall;
	ITI_bool isInitial;
	ITI_bool isEvent;
	ITI_bool isFirstEventStep;
	ITI_bool isTerminal;
	ITI_bool isCalcDependencies;
	ITI_bool iTerminalCalled;
	ITI_bool isTerminate;
	ITI_int iFailedEqu;
	ITI_char* strAnalysesType;
	ITI_char* strAnalysisTypeDetail;
	ITI_char strTrace[ITI_WARNING_STACK_SIZE*ITI_TRACE_STRING_SIZE];
	ITI_WarningStack warningStack;
	ITI_bool tracingAllowed;
	ITI_bool bInitializeFuncCalled;
	ITI_real dt;
	ITI_real lambdaHomotopy;
	ITI_AnimationData aniData;
	ITI_bool isAnimation;
	ITI_bool allowJump;
	jmp_buf buf;
	TRACE_FUNC* trace;
	ITI_bool isEmbed;
	ITI_bool allowBlockJump;
	jmp_buf blockEnv;
	ITI_bool bAssertOn;
	ITI_bool bAssertTraceOn;
	ITI_bool bAssertActive;
	void* pContainer;
	void* pSolverData;
	ITI_AssertData assertData;
	ITI_bool MEcalled;
	ITI_SolverSettings* sSettings;
	ITI_bool applyHysteresis;
	ITI_bool bUseSimpleHomotopy;
	ITI_bool bUseSimpleHomotopyForSteadyState;
	ITI_char strResourceFolder[1024];
	ITI_SetZeroFunctionBDFfunc SetZeroFunctionBDF;
	ITI_GetDelayValueBDFfunc GetDelayValueBDF;
	ITI_GetImpactBDF GetImpactBDF;
	DoClockTickFunc DoClockTick;
	DoClockedInitFunc DoClockedInit;
	NextClockTickFunc NextClockTick;
	IntegratePartitionFunc IntegratePartition;
	ITI_TimeTriggeredClock* timeTriggeredClock;
	ITI_bool isEventClock;
	ITI_bool isFixedStep;
} ITI_SolverInfo;

typedef struct ITI_ModelInfo {
	ITI_bool bNeedExtendedOnValidStep;
	ITI_bool bHasDummyVariables;
} ITI_ModelInfo;

typedef struct ITI_SolverStatistic {
	ITI_uint iOrder;
	ITI_uint iValidSteps;
	ITI_uint iZero;
	ITI_uint iZeros;
	ITI_uint iJac;
	ITI_uint iCodegen;
	ITI_uint iDecomp;
	ITI_uint iElim;
	ITI_real dblChangeStepSize;
	ITI_real dblhTmp;
	ITI_real* dblInfluence;
	ITI_uint* discreteCount;
	ITI_uint* zeroCrossingCount;
	ITI_uint iErrTestFailStep;
	ITI_uint iErrTestFails;
	ITI_uint iRhsCalls;
	ITI_uint ix;
	ITI_uint ngrp;
	ITI_uint iRoots;
	ITI_uint iTimeEvents;
	ITI_uint iTimeEventsReinit;
	ITI_uint iStateSelections;
	ITI_uint iOtherEvents;
	ITI_uint iRfcalls;
	ITI_uint numBlocks;
	ITI_long *numBlockRes;
	ITI_long *numBlockJac;
	ITI_real *blockTimes;
	ITI_real calcDerivativesTime;
} ITI_SolverStatistic;

typedef struct ITI_SampleTime {
	ITI_real to;
	ITI_real ts;
} ITI_SampleTime;

typedef struct ITI_HystCurveInitData {
	ITI_char* curveIdent;
	ITI_bool bEnabled;
	enum HystMode hystMode;
	ITI_bool bClockwise;
	ITI_real startY;
	enum HystStartValue hystStartValue;
	ITI_real eps_xdot;
} ITI_HystCurveInitData;

typedef struct ITI_EqBlock {
	ITI_int stateStartIdx;
	ITI_int stateSize;
	ITI_int eqStartIdx;
	ITI_int eqSize;
	ITI_int derEqSize;
} ITI_EqBlock;

typedef struct ITI_DerEquation {
	ITI_int idx_State;
	ITI_int idx_BaseState;
} ITI_DerEquation;

typedef struct ITI_VarNext {
	ITI_int state_i;
	ITI_int state_i_orig;
	ITI_bool iState_dc;
	ITI_bool iState_dd;
	ITI_bool iState_fcsp;
	ITI_bool iState_ibs;
	ITI_bool ider;
	ITI_int der_si;
	ITI_bool ider_dc;
	ITI_bool ider_dd;
} ITI_VarNext;

typedef struct ITI_VarAttributes {
	ITI_int stateIdx;
	ITI_int startIdx;
	ITI_int minIdx;
	ITI_int maxIdx;
	ITI_int fixedIdx;
	ITI_int notFixedIdx;
	ITI_int nominalIdx;
	ITI_int minNotReachedIdx;
	ITI_int maxNotReachedIdx;
	ITI_int absTolIdx;
	ITI_int relTolIdx;
	ITI_int discontChangeIdx;
} ITI_VarAttributes;

typedef struct ITI_BlockSizes {
	ITI_int ires;
	ITI_int iDAE;
	ITI_int iHybrid_Z_Real;
	ITI_int iHybrid_Z_Int;
	ITI_int iHybrid_Z_Str;
	ITI_int iHybrid_Zf;
	ITI_int nrDPBlock;
	ITI_int isNonlinear;
} ITI_BlockSizes;

typedef struct ITI_DelayInfo {
	ITI_uint bufSize;
	enum DelayValueType valType;
	ITI_char* name;
} ITI_DelayInfo;

typedef struct ITI_DelayBuffer {
	ITI_int size;
	ITI_int lastPosIn;
	ITI_int lastPosOut;
	ITI_real* times;
	ITI_real* realValues;
	ITI_int* intValues;
	ITI_int iL;
	ITI_int iR;
	ITI_int iSearch;
	ITI_int iNewVal;
	enum DelayValueType valType;
#ifdef ITI_ANIMATION
	ITI_int aniIndex;
#endif
} ITI_DelayBuffer;

typedef struct ITI_Array {
	ITI_int nDims;
	ITI_int* dims;
	ITI_char** charValues;
	ITI_int* intValues;
	ITI_real* realValues;
	enum MemoryType memType;
} ITI_Array;

typedef struct ITI_WorkMemory {
	ITI_real* ker;
	ITI_real* kerCopy;
	ITI_real* vecCopy;
	ITI_real* dWork;
	ITI_int*  lPermVecCol;
} ITI_WorkMemory;

typedef struct {
	ITI_real *a;
	ITI_real *b;
	ITI_real *work;
	ITI_real *wp1;
	ITI_real *wp2;
	ITI_int  *jpvt;
	ITI_real bignum;
	ITI_real smlnum;
	ITI_real anrm;
	ITI_int  m;
	ITI_int  n;
	ITI_int  ldb;
	ITI_int  lwork;
	ITI_int  rank;
	ITI_int  mn;
	ITI_real rcond;
	ITI_int  iascl;
} ITI_LLSData;


struct ITI_BlockData;
typedef struct ITI_BlockDataVTable {
	void(*ErrorExceedsBorder) (struct ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i);
	void(*ErrorInitialBracketNotFound) (struct ITI_BlockData* pBd, ITI_SolverInfo* pInfo);
	void(*ErrorLambdaMin)(struct ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint n);
	void(*ErrorMaxIter)(struct ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint n);
	void(*ErrorResidualImage) (struct ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint n);
	void(*WarningBelowMin) (struct ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i, ITI_uint j);
	void(*WarningBelowMinDamping) (struct ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i);
	void(*WarningBelowMinDamping2) (struct ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i, ITI_uint k);
	void(*WarningExceedsMax) (struct ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i, ITI_uint j);
	void(*WarningExceedsMaxDamping) (struct ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i);
	void(*WarningExceedsMaxDamping2) (struct ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i, ITI_uint k);
	void(*WarningReducingDampFac) (struct ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint i);
	void(*WarningResidualImage) (struct ITI_BlockData* pBd, ITI_SolverInfo* pInfo, ITI_uint m, ITI_uint n, ITI_uint l);
	void(*SetAnalysisTypeDetail) (struct ITI_SolverInfo* pInfo, char* typeDetail);
} ITI_BlockDataVTable;

typedef struct ITI_BlockData {
	ITI_BlockDataVTable* vTable;
	ITI_uint nRes;
	ITI_uint nDAE;
	ITI_real* x;
	ITI_real* minVal;
	ITI_real* maxVal;
	ITI_real* nomVal;
	ITI_uint ignoreLimits;
	ITI_ushort* considerMin;
	ITI_ushort* considerMax;
	ITI_ushort considerLimit;
	ITI_uint nViolLimit;
	ITI_uint* iViolLimit;
	ITI_real alpha;
	ITI_real beta;
	ITI_char** name;
	ITI_real* sjac;
	ITI_real* v;
	ITI_real* mv;
	ITI_real* jac;
	ITI_real* res;
	ITI_real* tmpres;
	ITI_real* s;
	ITI_int*  ipiv;
	ITI_int*  colpiv;
	ITI_real* tol;
	ITI_real* delta;
	ITI_real* xorg;
	ITI_WorkMemory *workMem;
	ITI_ushort mode;
	ITI_real* xstart;
	ITI_ushort saveStartValues;
	ITI_ushort error;
	ITI_int *numJacCols;
	ITI_int nCol;
	ITI_int iCol;
	ITI_uint repeat;
	ITI_real d;
	ITI_real preNorm;
	ITI_real firstNorm;
	ITI_int corrStep;
	ITI_ushort firstTime;
	ITI_ushort justOnceMore;
	ITI_real* sjactemp;
	ITI_uint* permVecCol;
	ITI_char* strAnalysisTypeDetail;
	ITI_real* xsave;
	ITI_int* zintsave;
	ITI_real* zrealsave;
	ITI_char** zstrsave;
	ITI_real* zfsave;
	ITI_real normdx;
	ITI_real* dxbar;
	ITI_real* w;
	ITI_real lambda;
	ITI_real normdxbar;
	ITI_real normdxkm1;
	ITI_real* xjac;
	ITI_uint reduced;
	ITI_int maxiter;
	ITI_real gltol;
	ITI_int linSolv;
	ITI_real lambda_min;
	ITI_uint iMax;
	ITI_real rect_error;
	ITI_real* colsc;
	ITI_real* rowsc;
	ITI_real xh;
	ITI_real xl;
	ITI_real resSav;
	ITI_real dxSav;
	ITI_real sSav;
	ITI_uint hybrid;
	ITI_LLSData llsData;
	ITI_int zfSwitch;
	ITI_uint undamped;
	ITI_uint isNonlinear;
	ITI_int autoLinSolv;
	ITI_uint useNumJac;
	ITI_long resCalls;
	ITI_long jacCalls;
} ITI_BlockData;

typedef struct ITI_DPBlockData {
	ITI_uint* M;
	ITI_real* Vdot;
	ITI_ushort MC;
	ITI_ushort MCP;
} ITI_DPBlockData;

typedef struct ITI_HomMinMax {
	ITI_ushort considerLimit;
	ITI_ushort* considerMin;
	ITI_real* minVal;
	ITI_ushort* considerMax;
	ITI_real* maxVal;
	ITI_real* nomVal;
	ITI_char** name;
}ITI_HomMinMax;

typedef struct ITI_StateMinMax {
	ITI_int nMin;
	ITI_int nMax;
	ITI_int* minInd;
	ITI_int* maxInd;
	ITI_real* minVal;
	ITI_real* maxVal;
}ITI_StateMinMax;

typedef struct ITI_ModelSize {
	ITI_int ix;
	ITI_int ibx;
	ITI_int ix_i;
	ITI_int ires_i;
	ITI_int ihomres;
	ITI_int iy_int;
	ITI_int iy_real;
	ITI_int iy_str;
	ITI_int ip_int;
	ITI_int ip_real;
	ITI_int ip_str;
	ITI_int ip_arr;
	ITI_int iu_int;
	ITI_int iu_real;
	ITI_int iu_str;
	ITI_int iz_int;
	ITI_int iz_real;
	ITI_int iz_str;
	ITI_int iv_int;
	ITI_int iv_real;
	ITI_int iv_str;
	ITI_int iclocksv_int;
	ITI_int iclocksv_real;
	ITI_int iclocksv_str;
	ITI_int i_inc;
	ITI_int izf;
	ITI_int ics;
	ITI_int isv;
	ITI_int ihcs;
	ITI_int idb;
	ITI_int iExtObj;
	ITI_int iarr;
	ITI_int iRec;
	ITI_int icset;
	ITI_int ipcset;
	ITI_int icnd;
	ITI_int iass;
	ITI_int ieb;
	ITI_int ide;
	ITI_int ivn;

	ITI_int numBlocks;
	ITI_int numStateAttr;
	ITI_int numInitStateAttr;
	ITI_int numRESBlock;
	ITI_int numXBlock;

	ITI_int iSimX_X;
	ITI_int iSimX_V;
	ITI_int iSimX_Z;
	ITI_int iSimX_BX;
	ITI_int iSimX_ClockSV;

	ITI_int iDPB;
	ITI_int iInEq_n;
	ITI_int iInEq_n_Min_m;
	ITI_int iInEq_n_Mul_n_Min_m;
	ITI_int iInEq_35_Mul_n_Min_m_Plus_32;

	ITI_int bxind_lambda;
	ITI_int bxind_cdfirst;
	ITI_int bxind_homlast;

	ITI_int ipart;
	ITI_int iig;
	ITI_int* iig_nodes;
	ITI_int* iig_edges;
	ITI_int* iig_children;
	ITI_int* iig_roots;
	ITI_int* iig_baseclocks;
	ITI_int* iig_solverclocks;
	ITI_int* iig_solverneeded;
	ITI_int* iig_paths;
	ITI_int* iig_steps;
} ITI_ModelSize;

typedef struct ITI_PartitionData {
	enum ClockPartitionType type;
	ITI_int id;
	ITI_int baseid;
	ITI_int subid;
	ITI_int sampleActive;
	ITI_int holdChanged;
	ITI_int activated;
	ITI_bool periodic;
	ITI_bool continous;
	ITI_int solvermethod;
	ITI_int interval;
	ITI_bool eventClock;
} ITI_PartitionData;

typedef struct ITI_WorkSpace {
	ITI_real* xdot_tmp;
	 
	ITI_CompositeData vtmp;
	ITI_CompositeData v;
	ITI_CompositeData p;
	ITI_CompositeData z;
	ITI_CompositeData pre_z;
	ITI_CompositeData clocksv;
	ITI_real* x;
	ITI_real* bx;
	ITI_real* bx_tmp;
	ITI_real** px;
#ifdef ITI_COMP_SIM
	ITI_real* vtmp_mem_real;
	ITI_real* v_mem_real;
	ITI_real* p_mem_real;
	ITI_real* z_mem_real;
	ITI_real* pre_z_mem_real;
	ITI_real* clocksv_mem_real;
#endif
}ITI_WorkSpace;

struct inferenceGraph;

typedef struct ITI_ModelData {
	ITI_MemoryObject currMem;
	ITI_MemoryObject funcMem;
	ITI_MemoryObject strMem;
	ITI_void** extObj;
	ITI_HomMinMax* hmm;	
	ITI_real* hom_res;	
	ITI_real* hom_jac;	
	
	
	ITI_TraceData traceData;
	ITI_TraceFlags traceFlags;
	void(*oldHandler)(int);
	int oldCW;
#ifdef ITI_COMP_SIM
	void* simxInterface;
#endif
} ITI_ModelData;


typedef struct ITI_PartitionVar {
	ITI_real* x;
	ITI_real* x_bak;
	ITI_real* xdot;
	ITI_real* xdot_bak;
	ITI_real* xdot_tmp;
	ITI_real* bxd;
	ITI_real** res;
	ITI_real** res_i;
	ITI_real* x_i;
#ifdef ITI_COMP_SIM
	ITI_real** bx;
	ITI_real** bx_tmp;
	ITI_real* y_mem_real;
	ITI_real* u_mem_real;
#else
	ITI_real* bx;
	ITI_real* bx_tmp;
#endif
	ITI_CompositeData v;
	ITI_CompositeData vtmp;
	ITI_CompositeData y;
	ITI_CompositeData u;
	ITI_CompositeData p;
	ITI_CompositeData z;
	ITI_CompositeData pre_z;
	ITI_CompositeData clocksv;
	ITI_Array* arr_p;
	ITI_Array* arrays;
	ITI_real* zf;
	ITI_real* pre_zf;
	ITI_uchar* czf;
	ITI_uchar* ezf;
	ITI_int* cszf;
	ITI_int* oszf;
	ITI_int* szf;
	ITI_int* relzf;
	ITI_real* epszf;
	ITI_real* e1zf;
	ITI_real* e2zf;
	ITI_uint* sczf;
#ifdef ITI_COMP_SIM
	ITI_uchar *curve_zf;
#endif
	ITI_real** pszf;
	ITI_void** extObj;
	ITI_CurveSetData* cSet;
	ITI_CurveData_ND* cNd;
	ITI_CurveCallState* cs;
	ITI_HystCurveCallState* hcs;
	ITI_real t;
	ITI_real tLastStep;
	ITI_SolverInfo sInfo;
	ITI_uint* iReinit;
	ITI_real* xReinit;
	ITI_uint* xChanged;
	ITI_ushort* xImpact;
	ITI_int* sv;
	ITI_int* svInit;  
	ITI_DelayBuffer* db;
	ITI_BlockData* ibd;
	ITI_DPBlockData* iDPbd;
	ITI_uint incCount;
	ITI_uint* stateIncidence;
	ITI_MemoryObject currMem;
	ITI_MemoryObject funcMem;
	ITI_ModelSize size;
	ITI_SampleTime* sampleTime;
	ITI_MemoryObject strMem;
	ITI_void* pRecord;
	ITI_HomMinMax* hmm;
	ITI_real* hom_res;
	ITI_real* hom_jac;
	ITI_StateMinMax* smm;
	ITI_ModelInfo modelInfo;
	ITI_HystCurveInitData* _hyst_init_data;
	struct inferenceGraph *partitionIG;
	ITI_PartitionData *partitionData;
	void *performanceData;
	struct ITI_SolverData* solverData;
	char **stateNames;
	char **dstateNames;
	char **stateSynonyms;
	int trwidth;
	int dtrwidth;
#ifdef ITI_COMP_SIM
	ITI_WorkSpace ws;
	ITI_SynchStrsData synchStrsData;
#endif
} ITI_PartitionVar;

typedef struct ITI_Partion {
	size_t pid;
	ITI_PartitionVar* transient;
	ITI_PartitionVar* base;
	ITI_PartitionVar* sub;
	ITI_PartitionVar* curr;
} ITI_Partition;

typedef ITI_SolverState(*ModelFunc2)(ITI_Partition* pPart, SimData* modelData);
typedef ITI_SolverState(*ModelFunc3)(ITI_Partition* pPart, SimData* modelData, ITI_real* __jac);
typedef ITI_SolverState(*CalcDerivativesFunc)(ITI_Partition* pPart, SimData* modelData);
typedef ITI_SolverState(*CalcResidualsFunc)(ITI_Partition* pPart, SimData* modelData);
typedef ITI_SolverState(*CalcOutputsFunc)(ITI_Partition* pPart, SimData* modelData);
typedef ITI_SolverState(*SynchOutputsFunc)(ITI_Partition* pPart, SimData* modelData);
typedef ITI_SolverState(*ValidStepFunc)(ITI_Partition* pPart, SimData* modelData);
typedef ITI_SolverState(*DoAcceptStatesFunc)(ITI_Partition* pPart, SimData* modelData);
typedef void(*AssignLastVarFunc)(ITI_Partition* pPart, SimData* modelData);
typedef void(*AssignDiscreteRealFunc)(ITI_Partition* pPart, SimData* modelData);
typedef void(*SampleFunctionFunc)(ITI_Partition* pPart, SimData* modelData);
typedef ITI_SolverState(*InitializeFunc)(ITI_Partition* pPart, SimData* modelData);
typedef ITI_SolverState(*InitializeConstantsFunc)(ITI_Partition* pPart, SimData* modelData);
typedef ITI_SolverState(*InitializeParameterDependentFunc)(ITI_Partition* pPart, SimData* modelData);
typedef ITI_SolverState(*InitializeTunableParameterFunc)(ITI_Partition* pPart, SimData* modelData);
typedef ITI_SolverState(*InitializeConditionsFunc)(ITI_Partition* pPart, SimData* modelData);
typedef ITI_SolverState(*UpdateInferenceGraphFunc)(ITI_Partition* pPart, SimData* modelData);
typedef ITI_SolverState(*PerformInferenceGraphFunc)(ITI_Partition* pPart, SimData* modelData);
typedef ITI_SolverState(*LoadInferenceGraphResultsFunc)(ITI_Partition* pPart, SimData* modelData);
typedef void(*PerformIntervalUpdateFunc)(ITI_Partition* pPart, ITI_int graphIndex);
typedef ITI_SolverState(*TerminateFunc)(ITI_Partition* pPart, SimData* modelData);
typedef ITI_SolverState(*CalcResidualsInitFunc)(ITI_Partition* pPart, SimData* modelData);
typedef void(*GetJacobianAPatternFunc)(ITI_Partition* pPart, SimData* modelData, ITI_char*);
typedef void(*GetJacobianEPatternFunc)(ITI_Partition* pPart, SimData* modelData, ITI_char*);
typedef void(*GetJacobianInitPatternFunc)(ITI_Partition* pPart, SimData* modelData, ITI_char*);
typedef ITI_SolverState(*CalcJacPrefixInitFunc)(ITI_Partition* pPart, SimData* modelData);
typedef ITI_SolverState(*CalcJacInitFunc)(ITI_Partition* pPart, SimData* modelData, ITI_real* __jac);
typedef ITI_SolverState(*CalcJacPrefixFunc)(ITI_Partition* pPart, SimData* modelData);
typedef ITI_SolverState(*CalcJacAFunc)(ITI_Partition* pPart, SimData* modelData, ITI_real* __jac);
typedef ITI_SolverState(*CalcJacEFunc)(ITI_Partition* pPart, SimData* modelData, ITI_real* __jac);
typedef ITI_SolverState(*PreActivationFunc)(ITI_Partition* pPart, SimData* modelData);
typedef ITI_SolverState(*PostActivationFunc)(ITI_Partition* pPart, SimData* modelData);
typedef void(*InitBlockVarsFunc)(ITI_BlockData *bd);
typedef void(*GetModelSizesFunc)(ITI_AllocateMemory allocateMemory, ITI_ModelSize* pSize);
typedef void(*GetPartitionSizesFunc)(ITI_AllocateMemory allocateMemory, ITI_ModelSize* pSize);
typedef void(*GetStateNamesFunc)(ITI_Partition* pPart);
typedef void(*GetModelInfoFunc)(ITI_ModelInfo* pInfo);

typedef struct ITI_PartFunctions {
	 
	InitializeFunc Initialize;
	InitializeConstantsFunc InitializeConstants;
	InitializeParameterDependentFunc InitializeParameterDependent;
	InitializeTunableParameterFunc InitializeTunableParameter;
	InitializeConditionsFunc InitializeConditions;
	InitBlockVarsFunc InitBlockVars;

	 
	CalcDerivativesFunc CalcDerivatives;
	CalcResidualsFunc CalcResiduals;
	CalcResidualsInitFunc CalcResidualsInit;
	CalcOutputsFunc CalcOutputs;
	SynchOutputsFunc SynchOutputs;
	ValidStepFunc ValidStep;
	CalcJacPrefixInitFunc CalcJacPrefixInit;
	CalcJacInitFunc CalcJacInit;
	CalcJacPrefixFunc CalcJacPrefix;
	CalcJacAFunc CalcJacA;
	CalcJacEFunc CalcJacE;
	DoAcceptStatesFunc DoAcceptStates;
	AssignLastVarFunc AssignLastVar;
	AssignDiscreteRealFunc AssignDiscreteReal;
	SampleFunctionFunc SampleFunction;
	TerminateFunc Terminate;

	 
	UpdateInferenceGraphFunc UpdateInferenceGraph;
	LoadInferenceGraphResultsFunc LoadInferenceGraphResults;
	PreActivationFunc PreActivation;
	PostActivationFunc PostActivation;
	PerformIntervalUpdateFunc PerformIntervalUpdate;

	 
	GetJacobianAPatternFunc GetJacobianAPattern;
	GetJacobianEPatternFunc GetJacobianEPattern;
	GetJacobianInitPatternFunc GetJacobianInitPattern;
	GetPartitionSizesFunc GetPartitionSizes;
	GetStateNamesFunc GetStateNames;
	GetModelInfoFunc GetModelInfo;

	 
	ITI_ArrayData* arrayData;
	ITI_parameterData* parameters;
	ITI_Data_Array* parametersArr;
	ITI_varData* dataV;
	ITI_varData* dataZ;
	ITI_xData* dataX;
	ITI_varData* dataBX;
	ITI_resData* dataRES;
	ITI_zerofunctionData* dataZF;
	ITI_varData* dataClockSV;
	ITI_CurveSetData* curveSets;
	ITI_CurveData_ND* curveNDs;
	ITI_BlockSizes *blockSizes;
	ITI_VarAttributes* stateAttributes;
	ITI_VarAttributes* initialStateAttributes;
	ITI_uint* seqCsSizes;
	ITI_DelayInfo* delayInfos;
	ITI_HystCurveInitData* _hyst_init_data;
	ITI_int *numJacColsData;
	ITI_uint* DPBlockSizes;
	ITI_EqBlock* eqblocks;
	ITI_DerEquation* der_equations;
	ITI_VarNext* varnext;
}ITI_PartFunctions;

 
typedef int (*GetSizeOfStateAttrFunc)();
typedef int(*GetSizeOfInitialStateAttrFunc)();
typedef size_t(*GetSizeOfRESBlockFunc)();
typedef size_t(*GetSizeOfXBlockFunc)();
typedef void (*InitInferenceGraphFunc)(ITI_Partition* pPart, SimData* modelData);
typedef void(*GetPartitionDataFunc)(ITI_Partition* pPart, SimData* modelData);
typedef void(*GetPartitionAccessFunc)(ITI_PartFunctions* _partitions);
typedef unsigned long (*GetCheckSumFunc)();
typedef void (*InitMemoryFunc)(ITI_MemoryObject* _currMem, ITI_AllocateMemory allocateMemory, ITI_FreeMemory freeMemory);
typedef void (*FreeAllMemoryFunc)(ITI_MemoryObject* _currMem);
typedef void (*ReleaseAllMemoryFunc)(ITI_MemoryObject* _currMem);
typedef ITI_real (*GetInterfaceVersionFunc)();
typedef ITI_SolverState (*ConstConditionsChangedFunc)(ITI_Partition* pPart, SimData* modelData);
typedef void (*SynchronizeParametersFunc)(ITI_Partition* pPart, SimData* modelData);
typedef ITI_char* (*GetStringMemoryFunc)(ITI_MemoryObject* currMem, ITI_int nChar);
typedef void (*AllocateRecordsFunc)(ITI_Partition* pPart);
typedef void (*FreeRecordsFunc)(ITI_Partition* pPart, SimData* modelData);
typedef size_t(*GetRecordSizeFunc)();

typedef struct ITI_ModelFunctions {
	ITI_PartFunctions* partFunctions;

	GetModelSizesFunc GetModelSizes;
	InitInferenceGraphFunc InitInferenceGraph;
	GetPartitionDataFunc GetPartitionData;
	GetPartitionAccessFunc GetPartitionAccess;

	InitMemoryFunc InitMemory;
	FreeAllMemoryFunc FreeAllMemory;
	ReleaseAllMemoryFunc ReleaseAllMemory;
	GetStringMemoryFunc GetStringMemory;
	AllocateRecordsFunc AllocateRecords;
	FreeRecordsFunc FreeRecords;
	GetRecordSizeFunc GetRecordSize;
#ifdef ITI_COMP_SIM
	GetCheckSumFunc GetCheckSum;
	GetInterfaceVersionFunc GetInterfaceVersion;
	ConstConditionsChangedFunc ConstConditionsChanged;
	SynchronizeParametersFunc SynchronizeParameters;
	void* hModel;
#endif
	ITI_outputData* outputData;
	ITI_inputData* inputData;
}ITI_ModelFunctions;

typedef struct ITI_CSTmpData {
	ITI_int allocated;
	ITI_SolverInfo sInfo;
	ITI_real* bx;
	ITI_CompositeData z;
	ITI_CompositeData pre_z;
	ITI_real* z_mem_real;
	ITI_real* pre_z_mem_real;
	ITI_real* zf;
	ITI_real* pre_zf;
	ITI_int* cszf;
	ITI_int* oszf;
	ITI_uint* stateIncidence;
}ITI_CSTmpData;

typedef void(*SolverInterfaceFunc)(size_t pid, struct ITI_SolverData* pData);
typedef void(*SolverInterfaceLogFunc)(size_t pid, struct ITI_SolverData* pData, ITI_bool force);
typedef void(*SolverInterfaceGlobalFunc)(struct ITI_SolverData* pData);
typedef int(*SolverInterfaceOnSetInputsFunc)(void* pData, double t, ITI_CompositeData* u);


typedef struct ITI_SolverContextBase {
	void*(*CreateSolver)(size_t, struct ITI_SolverData*, ITI_PartitionSolverMethod);	
	ITI_SolverState(*InitializePrepareSolver)(size_t, struct ITI_SolverData*);				
	ITI_SolverState(*InitializeFinishSolver)(size_t, struct ITI_SolverData*);				
	ITI_SolverState(*PrepareTimeEventHandlingSolver)(size_t, struct ITI_SolverData*);
	ITI_SolverState(*CalcOneStepSolver)(size_t, void*, double);

	SolverInterfaceFunc OnPrepareSaveOutputs;
	SolverInterfaceLogFunc OnSaveOutputsSolver;
	SolverInterfaceGlobalFunc OnFinishSaveOutputs;
	SolverInterfaceFunc OnBeforeEventStepSolver;
	SolverInterfaceFunc OnValidEventStepSolver;
	SolverInterfaceOnSetInputsFunc OnSetInputs;

	void(*FreeSolver)(void*);

	ITI_SolverAction action;
	ITI_SolverState state;
	ITI_bool bDPHappenedInEventiteration;
	ITI_bool bFinishSaveOutputsNecessary;
	ITI_bool bPerformEventIterationInPartitionFinish;
	ITI_bool bTerminateRequired;
	ITI_bool bTimeEvent;
	ITI_bool bZeroFunc;
	ITI_bool hitIsSample;
	ITI_bool hitIsClock;
	ITI_real t;
	ITI_bi i_t;

	ITI_real relTol;
	ITI_real absTol;
	ITI_real tHit;
	ITI_real tHitSample;
	ITI_real tHitClock;
	ITI_real tProt;
	ITI_real tTemp;
	ITI_bi i_tProtNext;
	ITI_bui ui_dtProt;
	ITI_bui ui_ProtCounter;
	ITI_bi i_tHit;
	ITI_bui ui_dtHit;
	ITI_bui ui_dt_Max;
	ITI_bool lastCalcWasAnimation;

	ITI_int isvMax;
	ITI_bui* timeEventMax;
	ITI_bui* timeEventCounter;

	ITI_PartitionSolverMethod solverMethod;
	 
}ITI_SolverContextBase;

typedef struct ITI_SolverData {
	ITI_SolverContextBase** sc;		
	ITI_ModelFunctions model;
	ITI_ModelData modelData;
	ITI_Partition* partition;						

	ITI_SolverSettings ss;			
	ITI_SolverStatistic* stat;		
#ifdef ITI_COMP_SIM
	ITI_CSTmpData tmpData;
	ITI_UpdateStrDataInSimxFunc* UpdateStrDataInSimxFunc;	
#endif
} ITI_SolverData;

typedef void*(*CreateSolverContextFunc)(size_t, ITI_SolverData*, ITI_PartitionSolverMethod);

#ifdef __cplusplus
}   
#endif

#endif
