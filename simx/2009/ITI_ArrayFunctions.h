/**
 * ITI_ArrayFunctions.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#ifndef _ITI_ARRAYFUNCTIONS_H
#define _ITI_ARRAYFUNCTIONS_H

#include "ITI_Types.h"

enum Op {
	Add = 1,
	Sub = 2,
	Mul = 3,
	Div = 4,
	Pow = 5
};

enum RelOp {
	RelOp_Eq = 1,
	RelOp_NotEq = 2,
	RelOp_Greater = 3,
	RelOp_Less = 4,
	RelOp_GreaterEq = 5,
	RelOp_LessEq = 6,
	RelOp_Unknown = 7
};

enum ArgTag {
	AT_Index = 1,
	AT_Colon = 2,
	AT_Range = 3,
	AT_RangeEx = 4,
	AT_Vector = 5,
	AT_End = 6
};

enum FuncIdent {
	FI_fabs = 1,
	FI_abs = 2,
	FI_sign = 3,
	FI_sin = 4,
	FI_cos = 5,
	FI_tan = 6,
	FI_asin = 7,
	FI_acos = 8,
	FI_atan = 9,
	FI_sinh = 10,
	FI_cosh = 11,
	FI_tanh = 12,
	FI_exp = 13,
	FI_log = 14,
	FI_log10 = 15,
	FI_sqrt = 16,
	FI_floor = 17,
	FI_ceil = 18
};

typedef struct TaggedIndices {
	enum ArgTag tag;
	union {
		ITI_int index;
		ITI_int range[3];
		ITI_Array vector;
	}u_idx;
}TaggedIndices;

ITI_FUNCTIONS_API void InitArray(ITI_Array* pArray);
ITI_FUNCTIONS_API ITI_int GetNumArrayValues(const ITI_Array a);
ITI_FUNCTIONS_API ITI_Array CreateRealArray(ITI_MemoryObject* currMem, ITI_int nDims, ...);
ITI_FUNCTIONS_API ITI_Array CreateRealVector(ITI_MemoryObject* currMem, ITI_int nValues, ...);
ITI_FUNCTIONS_API ITI_Array CreateIntArray(ITI_MemoryObject* currMem, ITI_int nDims, ...);
ITI_FUNCTIONS_API ITI_Array CreateIntVector(ITI_MemoryObject* currMem, ITI_int nValues, ...);
ITI_FUNCTIONS_API void InitValuesMemory(ITI_MemoryObject* currMem, ITI_Array* a, enum MemoryType memType, ITI_int nValues);
ITI_FUNCTIONS_API ITI_Array Promote(ITI_MemoryObject* currMem, ITI_Array a, ITI_int n);
ITI_FUNCTIONS_API ITI_Array IntPromoteScalar(ITI_MemoryObject* currMem, ITI_int x, ITI_int n);
ITI_FUNCTIONS_API ITI_Array RealPromoteScalar(ITI_MemoryObject* currMem, ITI_real x, ITI_int n);
ITI_FUNCTIONS_API ITI_int ArrayMatching(const ITI_Array a1, const ITI_Array a2);
ITI_FUNCTIONS_API void ArrayMatchingOp(ITI_SolverInfo* sInfo, enum Op op, const ITI_Array a1, const ITI_Array a2);
ITI_FUNCTIONS_API ITI_Array CreateArray(ITI_MemoryObject* currMem, const ITI_Array a);
ITI_FUNCTIONS_API ITI_Array CastArray(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, const ITI_Array a, enum MemoryType memType);
ITI_FUNCTIONS_API ITI_Array ArrayOp(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, enum Op op, const ITI_Array a1, const ITI_Array a2);
ITI_FUNCTIONS_API ITI_Array ArrayAdd(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, const ITI_Array a1, const ITI_Array a2);
ITI_FUNCTIONS_API ITI_Array ArraySub(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, const ITI_Array a1, const ITI_Array a2);
ITI_FUNCTIONS_API ITI_real ArrayScalarProd(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, const ITI_Array a1, const ITI_Array a2);
ITI_FUNCTIONS_API ITI_Array ArrayArrayOp(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, const ITI_Array a1, const ITI_Array a2, enum Op op);
ITI_FUNCTIONS_API ITI_Array ArrayScaleOpReal(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, enum Op op, const ITI_Array a, ITI_real v, ITI_uint swap);
ITI_FUNCTIONS_API ITI_Array ArrayScaleOpInt(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, enum Op op, const ITI_Array a, ITI_int v, ITI_uint swap);
ITI_FUNCTIONS_API ITI_real ArrayRealValM(ITI_Array a, ITI_int n, ITI_int m);
ITI_FUNCTIONS_API ITI_int ArrayIntValM(ITI_Array a, ITI_int n, ITI_int m);
ITI_FUNCTIONS_API ITI_int ArrayIndex(ITI_Array a, ITI_char* fmt, ...);
ITI_FUNCTIONS_API ITI_real ArrayValReal(const ITI_Array a, int index);
ITI_FUNCTIONS_API ITI_int ArrayValInt(const ITI_Array a, int index);
ITI_FUNCTIONS_API ITI_char* ArrayValStr(const ITI_Array a, int index);
ITI_FUNCTIONS_API ITI_Array ArrayMulReal(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, const ITI_Array a, const ITI_real v);
ITI_FUNCTIONS_API ITI_Array ArrayDivReal(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, const ITI_Array a, const ITI_real v);
ITI_FUNCTIONS_API ITI_Array ArrayMulInt(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, const ITI_Array a, const ITI_int v);
ITI_FUNCTIONS_API ITI_Array ArrayDivInt(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, const ITI_Array a, const ITI_int v);
ITI_FUNCTIONS_API ITI_Array ArrayMulMM(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, const ITI_Array a1, const ITI_Array a2);
ITI_FUNCTIONS_API ITI_Array ArrayMulMV(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, const ITI_Array a1, const ITI_Array a2);
ITI_FUNCTIONS_API ITI_Array ArrayMulVM(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, const ITI_Array a1, const ITI_Array a2);
ITI_FUNCTIONS_API ITI_real ArrayRealMin(const ITI_Array a);
ITI_FUNCTIONS_API ITI_int ArrayIntMin(const ITI_Array a);
ITI_FUNCTIONS_API ITI_real ArrayRealMax(const ITI_Array a);
ITI_FUNCTIONS_API ITI_int ArrayIntMax(const ITI_Array a);
ITI_FUNCTIONS_API ITI_real ArrayRealSum(const ITI_Array a);
ITI_FUNCTIONS_API ITI_int ArrayIntSum(const ITI_Array a);
ITI_FUNCTIONS_API ITI_real ArrayRealProduct(const ITI_Array a);
ITI_FUNCTIONS_API ITI_int ArrayIntProduct(const ITI_Array a);
ITI_FUNCTIONS_API ITI_real ArrayRealScalar(ITI_SolverInfo* sInfo, const ITI_Array a);
ITI_FUNCTIONS_API ITI_int ArrayIntScalar(ITI_SolverInfo* sInfo, const ITI_Array a);
ITI_FUNCTIONS_API ITI_Array ArraySize(ITI_MemoryObject* currMem, const ITI_Array a);
ITI_FUNCTIONS_API void ArrayAssign(ITI_MemoryObject* currMem, ITI_SolverInfo* sInfo, ITI_Array* dest, ITI_Array src);
ITI_FUNCTIONS_API ITI_Array FillIntArray(ITI_MemoryObject* currMem, ITI_int val, ITI_int nDims, ...);
ITI_FUNCTIONS_API ITI_Array FillIntArrayWithArray(ITI_MemoryObject* currMem, ITI_Array valArr, ITI_int nDims, ...);
ITI_FUNCTIONS_API ITI_Array FillRealArray(ITI_MemoryObject* currMem, ITI_real val, ITI_int nDims, ...);
ITI_FUNCTIONS_API ITI_Array FillRealArrayWithArray(ITI_MemoryObject* currMem, ITI_Array valArr, ITI_int nDims, ...);
ITI_FUNCTIONS_API ITI_Array FillStringArray(ITI_MemoryObject* currMem, const ITI_char* val, ITI_int nDims, ...);
ITI_FUNCTIONS_API ITI_Array ArrayVector(ITI_MemoryObject* currMem, ITI_Array a);
ITI_FUNCTIONS_API ITI_Array ArrayVectorReal(ITI_MemoryObject* currMem, ITI_real v);
ITI_FUNCTIONS_API ITI_Array ArrayVectorInt(ITI_MemoryObject* currMem, ITI_int v);
ITI_FUNCTIONS_API ITI_Array ArrayRealDiagonal(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_Array a);
ITI_FUNCTIONS_API ITI_Array ArrayIntDiagonal(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_Array a);
ITI_FUNCTIONS_API ITI_Array ArrayIdentity(ITI_MemoryObject* currMem, ITI_int n);
ITI_FUNCTIONS_API ITI_Array ArrayMatrix(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_Array a);
ITI_FUNCTIONS_API ITI_Array ArrayTranspose(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_Array a);
ITI_FUNCTIONS_API ITI_Array* ArrayRefTranspose(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_Array* a);
ITI_FUNCTIONS_API ITI_Array ArrayOuterProduct(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_Array a, ITI_Array b);
ITI_FUNCTIONS_API ITI_Array ArrayCross(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_Array a, ITI_Array b);
ITI_FUNCTIONS_API ITI_Array ArraySkew(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_Array a);
ITI_FUNCTIONS_API ITI_Array ArrayLinspace(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_real x1, ITI_real x2, ITI_int n);
ITI_FUNCTIONS_API ITI_Array ArraySymmetric(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_Array a);
ITI_FUNCTIONS_API ITI_Array ArrayUnaryMinus(ITI_MemoryObject* currMem, const ITI_Array a);
ITI_FUNCTIONS_API void ArrayInSubArray(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, const ITI_Array inArr, ITI_Array outArr, ...);
ITI_FUNCTIONS_API void SetArrayInSubArray(TaggedIndices* taggedIndices, ITI_Array dest, ITI_int destOffset, ITI_int destDim, ITI_Array src, ITI_int srcOffset, ITI_int srcDim, ITI_int fillSize);
ITI_FUNCTIONS_API ITI_Array SubArrayFromArray(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_Array a, ...);
ITI_FUNCTIONS_API void GetSubArrayFromArray(TaggedIndices* taggedIndices, ITI_Array dest, ITI_int destOffset, ITI_int destDim, const ITI_Array src, ITI_int srcOffset, ITI_int srcDim, ITI_int fillSize);
ITI_FUNCTIONS_API ITI_Array ArrayCat(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_int alongDim, ITI_int nArgs, ITI_Array a1, ...);
ITI_FUNCTIONS_API ITI_Array RealRangeArray(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_real start, ITI_real step, ITI_real end);
ITI_FUNCTIONS_API ITI_Array IntRangeArray(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_int start, ITI_int step, ITI_int end);
ITI_FUNCTIONS_API void SetRealInArray(ITI_SolverInfo* sInfo, ITI_Array a, ITI_int index, ITI_real value);
ITI_FUNCTIONS_API void SetIntInArray(ITI_SolverInfo* sInfo, ITI_Array a, ITI_int index, ITI_int value);
ITI_FUNCTIONS_API void SetStrInArray(ITI_SolverInfo* sInfo, ITI_Array a, ITI_int index, ITI_char* value);
ITI_FUNCTIONS_API ITI_int ArrayCompare(ITI_SolverInfo* sInfo, ITI_Array a1, ITI_Array a2, enum RelOp relOp);
ITI_FUNCTIONS_API ITI_Array ArrayFromArrays(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_int nArgs, ITI_Array a1, ...);
ITI_FUNCTIONS_API ITI_Array ApplyFuncOnArray(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_Array a, enum FuncIdent fi);
ITI_FUNCTIONS_API ITI_Array CopyToRealArray(ITI_MemoryObject* currMem, ITI_real** values, ITI_int nDims, ...);
ITI_FUNCTIONS_API ITI_Array CopyToIntArray(ITI_MemoryObject* currMem, ITI_int** values, ITI_int nDims, ...);

ITI_FUNCTIONS_API ITI_char* AddString(ITI_MemoryObject* currMem, const ITI_char* str1, const ITI_char* str2);
ITI_FUNCTIONS_API ITI_char* RealToString(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_real val, ITI_int leftJustified,
													ITI_int minLen, ITI_int signifDig);
ITI_FUNCTIONS_API ITI_char* IntToString(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_int val, ITI_int leftJustified,
													ITI_int minLen, ITI_int signifDig);
ITI_FUNCTIONS_API ITI_char* BooleanToString(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_uint val, ITI_int leftJustified,
																		ITI_int minLen);
ITI_FUNCTIONS_API ITI_char* RealToStringFormat(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_real val, ITI_char* format);
ITI_FUNCTIONS_API void AssignString(ITI_MemoryObject* strMem, const ITI_char** dest, const ITI_char* src);
ITI_FUNCTIONS_API void AssignString2(ITI_MemoryObject* strMem, const ITI_char** dest, const ITI_char* src, const ITI_char** strData, size_t* strSize, ITI_int index);
ITI_FUNCTIONS_API void InitString(ITI_MemoryObject* strMem, const ITI_char** dest, ITI_uint size);
ITI_FUNCTIONS_API void InitString2(ITI_MemoryObject* strMem, const ITI_char** dest, ITI_uint size, size_t* strLengths, ITI_int index);

ITI_int GetMatrixStr(ITI_Array arr, ITI_int index, ITI_int nRows, ITI_int nCols, ITI_char* ret, const ITI_ushort MAX_MEM, ITI_int sum);
ITI_FUNCTIONS_API ITI_char* ArrayToString(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_Array arr);
ITI_FUNCTIONS_API ITI_char* GetArrayStr(ITI_Array arr, ITI_TraceData* traceData, ITI_MemoryObject* currMem);
ITI_FUNCTIONS_API ITI_char* GetIntArrayStr(ITI_int* arr, ITI_int dim, ITI_TraceData* traceData, ITI_MemoryObject* currMem);
ITI_FUNCTIONS_API ITI_char* GetRealArrayStr(ITI_real* arr, ITI_int dim, ITI_TraceData* traceData, ITI_MemoryObject* currMem);
ITI_FUNCTIONS_API ITI_int GetRealIndex(ITI_real* vars, ITI_int nVars, ITI_real* var);

#endif  
