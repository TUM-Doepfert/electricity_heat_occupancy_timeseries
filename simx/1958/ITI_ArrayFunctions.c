/**
 * ITI_ArrayFunctions.c
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#include "ITI_crt.h"
#include "ITI_ArrayFunctions.h"
#include <stdarg.h>

static ITI_Array CreateRealArrayWithDims(ITI_MemoryObject* currMem, ITI_int nDims, va_list ap);
static ITI_Array CreateIntArrayWithDims(ITI_MemoryObject* currMem, ITI_int nDims, va_list ap);
static ITI_Array CreateStringArrayWithDims(ITI_MemoryObject* currMem, ITI_int nDims, va_list ap);
static ITI_Array CreateRealArrayWithDimsExt(ITI_MemoryObject* currMem, ITI_int nDims, ITI_int extDim, va_list ap);
static ITI_Array CreateIntArrayWithDimsExt(ITI_MemoryObject* currMem, ITI_int nDims, ITI_int extDim, va_list ap);

void InitArray(ITI_Array* pArray)
{
	if (pArray){
		pArray->charValues = 0;
		pArray->intValues = 0;
		pArray->realValues = 0;
	}
}

ITI_int GetNumArrayValues(const ITI_Array a)
{
	ITI_int nValues = 1;
	if (a.dims){
		ITI_int i;
		for (i = 0; i < a.nDims; i++){
			nValues *= a.dims[i];
		}
	}
	return nValues;
}

static ITI_Array CreateRealArrayWithDims(ITI_MemoryObject* currMem, ITI_int nDims, va_list ap)
{
	ITI_int i;
	ITI_Array res;

	InitArray(&res);
	res.nDims = nDims;
	res.dims = GetIntMemory(currMem, nDims);

	for (i = 0; i < nDims; i++){
		res.dims[i] = va_arg(ap, ITI_int);
	}
	res.memType = REAL_TYPE;
	return res;
}

static ITI_Array CreateIntArrayWithDims(ITI_MemoryObject* currMem, ITI_int nDims, va_list ap)
{
	ITI_int i;
	ITI_Array res;

	InitArray(&res);
	res.nDims = nDims;
	res.dims = GetIntMemory(currMem, nDims);

	for (i = 0; i < nDims; i++){
		res.dims[i] = va_arg(ap, ITI_int);
	}
	res.memType = INT_TYPE;
	return res;
}

static ITI_Array CreateStringArrayWithDims(ITI_MemoryObject* currMem, ITI_int nDims, va_list ap)
{
	ITI_int i;
	ITI_Array res;

	InitArray(&res);
	res.nDims = nDims;
	res.dims = GetIntMemory(currMem, nDims);

	for (i = 0; i < nDims; i++){
		res.dims[i] = va_arg(ap, ITI_int);
	}
	res.memType = STRING_TYPE;
	return res;
}

static ITI_Array CreateRealArrayWithDimsExt(ITI_MemoryObject* currMem, ITI_int nDims, ITI_int extDim, va_list ap)
{
	ITI_int i;
	ITI_Array res;

	InitArray(&res);
	res.nDims = nDims+1;
	res.dims = GetIntMemory(currMem, nDims+1);

	for (i = 0; i < nDims; i++){
		res.dims[i] = va_arg(ap, ITI_int);
	}

	res.dims[nDims] = extDim;

	res.memType = REAL_TYPE;
	return res;
}

static ITI_Array CreateIntArrayWithDimsExt(ITI_MemoryObject* currMem, ITI_int nDims, ITI_int extDim, va_list ap)
{
	ITI_int i;
	ITI_Array res;

	InitArray(&res);
	res.nDims = nDims+1;
	res.dims = GetIntMemory(currMem, nDims+1);

	for (i = 0; i < nDims; i++){
		res.dims[i] = va_arg(ap, ITI_int);
	}

	res.dims[nDims] = extDim;

	res.memType = INT_TYPE;
	return res;
}

ITI_Array CreateRealArray(ITI_MemoryObject* currMem, ITI_int nDims, ...)
{
	va_list ap;
	ITI_Array res;
	ITI_int nValues;

	InitArray(&res);
	va_start(ap, nDims);
	res = CreateRealArrayWithDims(currMem, nDims, ap);

	nValues = GetNumArrayValues(res);
	res.realValues = GetRealMemory(currMem, nValues);
	va_end(ap);
	return res;
}

ITI_Array CreateRealVector(ITI_MemoryObject* currMem, ITI_int nValues, ...)
{
	va_list ap;
	ITI_int i;
	ITI_Array res;

	InitArray(&res);
	res.nDims = 1;
	res.dims = GetIntMemory(currMem, 1);
	res.dims[0] = nValues;
	res.memType = REAL_TYPE;
	res.realValues = GetRealMemory(currMem, nValues);

	va_start(ap, nValues);
	for (i = 0; i < nValues; i++){
		res.realValues[i] = va_arg(ap, ITI_real);
	}
	va_end(ap);
	return res;
}

ITI_Array CreateIntArray(ITI_MemoryObject* currMem, ITI_int nDims, ...)
{
	va_list ap;
	ITI_Array res;
	ITI_int nValues;

	InitArray(&res);
	va_start(ap, nDims);
	res = CreateIntArrayWithDims(currMem, nDims, ap);

	nValues = GetNumArrayValues(res);
	res.intValues = GetIntMemory(currMem, nValues);
	va_end(ap);
	return res;
}

ITI_Array CreateIntVector(ITI_MemoryObject* currMem, ITI_int nValues, ...)
{
	va_list ap;
	ITI_int i;
	ITI_Array res;

	InitArray(&res);
	res.nDims = 1;
	res.dims = GetIntMemory(currMem, 1);
	res.dims[0] = nValues;
	res.memType = INT_TYPE;
	res.intValues = GetIntMemory(currMem, nValues);

	va_start(ap, nValues);
	for (i = 0; i < nValues; i++){
		res.intValues[i] = va_arg(ap, ITI_int);
	}
	va_end(ap);
	return res;
}

void InitValuesMemory(ITI_MemoryObject* currMem, ITI_Array* a,
					enum MemoryType memType, ITI_int nValues)
{
	if (a){
		switch (memType){
			case REAL_TYPE :
				a->realValues = GetRealMemory(currMem, nValues);
				break;
			case INT_TYPE :
				a->intValues = GetIntMemory(currMem, nValues);
				break;
			case STRING_TYPE:
			case STRING_PTR_TYPE:
				a->charValues = GetStringPtrMemory(currMem, nValues);
				break;
			default:
				break;
		}
	}
}

ITI_Array Promote(ITI_MemoryObject* currMem, ITI_Array a, ITI_int n)
{
	ITI_int i;
	ITI_Array res;

	assertFunction(a.nDims<=n, "Promote operation can not decrease the dimension number.", 0);
	InitArray(&res);

	res.nDims = n;
	res.dims = GetIntMemory(currMem, n);
	for (i = 0; i < a.nDims; i++){
		res.dims[i] = a.dims[i];
	}
	for (i = a.nDims; i < n; i++){
		res.dims[i] = 1;
	}
	switch (a.memType){
		case REAL_TYPE : res.realValues = a.realValues;
			break;
		case INT_TYPE : res.intValues = a.intValues;
			break;
		default:
			break;
	}
	res.memType = a.memType;
	return res;
}

ITI_Array IntPromoteScalar(ITI_MemoryObject* currMem, ITI_int x, ITI_int n)
{
	ITI_Array res;
	ITI_int i;

	InitArray(&res);
	res.memType = INT_TYPE;
	res.nDims = n;
	res.dims = GetIntMemory(currMem, n);
	for (i = 0; i < n; i++){
		res.dims[i] = 1;
	}
	res.intValues = GetIntMemory(currMem, 1);
	res.intValues[0] = x;
	return res;
}

ITI_Array RealPromoteScalar(ITI_MemoryObject* currMem, ITI_real x, ITI_int n)
{
	ITI_Array res;
	ITI_int i;

	InitArray(&res);
	res.memType = REAL_TYPE;
	res.nDims = n;
	res.dims = GetIntMemory(currMem, n);
	for (i = 0; i < n; i++){
		res.dims[i] = 1;
	}
	res.realValues = GetRealMemory(currMem, 1);
	res.realValues[0] = x;
	return res;
}

ITI_int ArrayMatching(const ITI_Array a1, const ITI_Array a2)
{
	ITI_int res = 0;
	if (a1.nDims == a2.nDims){
		if (a1.dims && a2.dims){
			ITI_int i;
			res = 1;
			for (i = 0; i < a1.nDims; i++){
				if (a1.dims[i] != a2.dims[i]){
					res = 0;
					break;
				}
			}
		}
	}
	return res;
}

void ArrayMatchingOp(ITI_SolverInfo* sInfo, enum Op op, const ITI_Array a1, const ITI_Array a2)
{
	switch (op){
		case Add : assertFunction(ArrayMatching(a1, a2),
				"Add of arrays needs matching arguments (size, type)", sInfo);
			break;
		case Sub : assertFunction(ArrayMatching(a1, a2),
				"Subtract of arrays needs matching arguments (size, type)", sInfo);
			break;
		default : break;
	}
}

ITI_Array CreateArray(ITI_MemoryObject* currMem, const ITI_Array a)
{
	ITI_int i;
	ITI_int nValues = 1;
	ITI_Array res;
	InitArray(&res);
	res.nDims = a.nDims;
	res.dims = GetIntMemory(currMem, a.nDims);
	for (i = 0; i < a.nDims; i++){
		res.dims[i] = a.dims[i];
		nValues *= a.dims[i];
	}
	switch (a.memType){
		case INT_TYPE : res.intValues = GetIntMemory(currMem, nValues);
			break;
		case REAL_TYPE : res.realValues = GetRealMemory(currMem, nValues);
			break;
		case STRING_TYPE :
			break;
		default:
			break;
	}
	res.memType = a.memType;
	return res;
}

ITI_Array CastArray(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem,
							const ITI_Array a, enum MemoryType memType)
{
	enum CastType {NoCast=0, RealToInt=1, IntToReal=2, StringCast=3};
	ITI_Array res;
	ITI_Array temp;
	enum CastType castType = NoCast;

	InitArray(&res);

	switch (memType){
		case INT_TYPE :
			switch (a.memType){
				case INT_TYPE		: castType = NoCast; break;
				case REAL_TYPE		: castType = RealToInt; break;
				case STRING_TYPE	: castType = StringCast; break;
				default:
					break;
			}
			break;
		case REAL_TYPE :
			switch (a.memType){
				case INT_TYPE		: castType = IntToReal; break;
				case REAL_TYPE		: castType = NoCast; break;
				case STRING_TYPE	: castType = StringCast; break;
				default:
					break;
			}
			break;
		case STRING_TYPE :
			castType = StringCast;
			break;
		default:
			break;
	}

	if (castType == StringCast){
		assertFunction(0,
				"CastArray():Cast string is not supported.", sInfo);
		castType = NoCast;
	}

	if (castType != NoCast) {
		ITI_int i;
		ITI_int nValues;
		temp = a;
		temp.memType = memType;
		nValues = GetNumArrayValues(a);
		res = CreateArray(currMem, temp);

		for (i = 0; i < nValues; i++){
			switch (castType){
				case RealToInt :
					res.intValues[i] = (ITI_int)a.realValues[i];
					break;
				case IntToReal :
					res.realValues[i] = (ITI_real)a.intValues[i];
					break;
				default:
					break;
			}
		}
		return res;
	}
	return a;
}

ITI_Array ArrayOp(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, enum Op op,
										const ITI_Array a1, const ITI_Array a2)
{
	ITI_int i;
	ITI_Array res;
	ITI_int nValues = GetNumArrayValues(a1);

	InitArray(&res);

	if (a1.memType == REAL_TYPE)
		res = CreateArray(currMem, a1);
	else
		res = CreateArray(currMem, a2);

	ArrayMatchingOp(sInfo, op, a1, a2);
	for (i = 0; i < nValues; i++){
		switch (op){
			case Add :
				switch (res.memType){
					case INT_TYPE :
						res.intValues[i] = a1.intValues[i] + a2.intValues[i];
						break;
					case REAL_TYPE :
						res.realValues[i] = (a1.memType==REAL_TYPE?
								a1.realValues[i]:a1.intValues[i]) +
								(a2.memType==REAL_TYPE?a2.realValues[i]:a2.intValues[i]);
						break;
					case STRING_TYPE : break;
					default:
						break;
				}
				break;
			case Sub :
				switch (res.memType){
					case INT_TYPE :
						res.intValues[i] = a1.intValues[i] - a2.intValues[i];
						break;
					case REAL_TYPE :
						res.realValues[i] = (a1.memType==REAL_TYPE?
								a1.realValues[i]:a1.intValues[i]) -
								(a2.memType==REAL_TYPE?a2.realValues[i]:a2.intValues[i]);
						break;
					case STRING_TYPE : break;
					default:
						break;
				}
				break;
			case Mul :
				switch (res.memType){
					case INT_TYPE :
						res.intValues[i] = a1.intValues[i] * a2.intValues[i];
						break;
					case REAL_TYPE :
						res.realValues[i] = (a1.memType==REAL_TYPE?
								a1.realValues[i]:a1.intValues[i]) *
								(a2.memType==REAL_TYPE?a2.realValues[i]:a2.intValues[i]);
						break;
					case STRING_TYPE : break;
					default:
						break;
				}
				break;
			case Div :
				switch (res.memType){
					case INT_TYPE :
						res.intValues[i] = a1.intValues[i] / a2.intValues[i];
						break;
					case REAL_TYPE :
						res.realValues[i] = (a1.memType==REAL_TYPE?
								a1.realValues[i]:a1.intValues[i]) /
								(a2.memType==REAL_TYPE?a2.realValues[i]:a2.intValues[i]);
						break;
					case STRING_TYPE : break;
					default:
						break;
				}
				break;
			case Pow :
				switch (res.memType){
					case INT_TYPE :
						res.intValues[i] = (ITI_int)int_pow(a1.intValues[i], a2.intValues[i]);
						break;
					case REAL_TYPE :
						if (a2.memType == INT_TYPE)
							res.realValues[i] = int_pow((a1.memType==REAL_TYPE?
								a1.realValues[i]:a1.intValues[i]),a2.intValues[i]);
						else if (a1.memType == INT_TYPE)
							res.realValues[i] = pow(a1.intValues[i],
								(a2.memType==REAL_TYPE?a2.realValues[i]:a2.intValues[i]));
						else
							res.realValues[i] = pow(a1.realValues[i], a2.realValues[i]);
						break;
					case STRING_TYPE : break;
					default:
						break;
				}
				break;
			default : break;
		}
	}
	return res;
}

ITI_Array ArrayScaleOpReal(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, enum Op op,
										const ITI_Array a, ITI_real v, ITI_uint swapArgs)
{
	ITI_int i;
	ITI_Array res;
	ITI_ushort incompatible = 0;
	ITI_int nValues = GetNumArrayValues(a);

	InitArray(&res);

	if (a.memType == INT_TYPE){
		ITI_Array b = a;
		b.memType = REAL_TYPE;
		res = CreateArray(currMem, b);
	}
	else
		res = CreateArray(currMem, a);

	for (i = 0; i < nValues; i++){
		switch (op){
			case Add :
				switch (a.memType){
					case REAL_TYPE :
						res.realValues[i] = a.realValues[i] + v;
						break;
					case INT_TYPE :
						res.realValues[i] = a.intValues[i] + v;
						break;
					default :
						incompatible = 1;
						break;
				}
				break;
			case Sub :
				switch (a.memType){
					case REAL_TYPE :
						if (swapArgs)
							res.realValues[i] = v - a.realValues[i];
						else
							res.realValues[i] = a.realValues[i] - v;
						break;
					case INT_TYPE :
						if (swapArgs)
							res.realValues[i] = v - a.intValues[i];
						else
							res.realValues[i] = a.intValues[i] - v;
						break;
					default :
						incompatible = 1;
						break;
				}
				break;
			case Mul :
				switch (a.memType){
					case REAL_TYPE :
						res.realValues[i] = a.realValues[i] * v;
						break;
					case INT_TYPE :
						res.realValues[i] = a.intValues[i] * v;
						break;
					default :
						incompatible = 1;
						break;
				}
				break;
			case Div :
				switch (a.memType){
					case REAL_TYPE :
						if (swapArgs)
							res.realValues[i] = v / a.realValues[i];
						else
							res.realValues[i] = a.realValues[i] / v;
						break;
					case INT_TYPE :
						if (swapArgs)
							res.realValues[i] = v / a.intValues[i];
						else
							res.realValues[i] = a.intValues[i] / v;
						break;
					default :
						incompatible = 1;
						break;
				}
				break;
			case Pow :
				switch (a.memType){
					case REAL_TYPE :
						if (swapArgs)
							res.realValues[i] = pow(v, a.realValues[i]);
						else
							res.realValues[i] = pow(a.realValues[i], v);
						break;
					case INT_TYPE :
						if (swapArgs)
							res.realValues[i] = int_pow(v, a.intValues[i]);
						else
							res.realValues[i] = pow(a.intValues[i], v);
						break;
					default :
						incompatible = 1;
						break;
				}
				break;
			default : break;
		}
	}
	if (incompatible)
		assertFunction(0, "Scale operation needs a compatible array type", sInfo);
	return res;
}

ITI_Array ArrayScaleOpInt(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, enum Op op,
										const ITI_Array a, ITI_int v, ITI_uint swapArgs)
{
	ITI_int i;
	ITI_Array res;
	ITI_ushort incompatible = 0;
	ITI_int nValues = GetNumArrayValues(a);

	InitArray(&res);

	if (op == Div && a.memType == INT_TYPE){
		ITI_Array b = a;
		b.memType = REAL_TYPE;
		res = CreateArray(currMem, b);
	}
	else
		res = CreateArray(currMem, a);

	for (i = 0; i < nValues; i++){
		switch (op){
			case Add :
				switch (a.memType){
					case REAL_TYPE :
						res.realValues[i] = a.realValues[i] + v;
						break;
					case INT_TYPE :
						res.intValues[i] = a.intValues[i] + v;
						break;
					default :
						incompatible = 1;
						break;
				}
				break;
			case Sub :
				switch (a.memType){
					case REAL_TYPE :
						if (swapArgs)
							res.realValues[i] = v - a.realValues[i];
						else
							res.realValues[i] = a.realValues[i] - v;
						break;
					case INT_TYPE :
						if (swapArgs)
							res.intValues[i] = v - a.intValues[i];
						else
							res.intValues[i] = a.intValues[i] - v;
						break;
					default :
						incompatible = 1;
						break;
				}
				break;
			case Mul :
				switch (a.memType){
					case REAL_TYPE :
						res.realValues[i] = a.realValues[i] * v;
						break;
					case INT_TYPE :
						res.intValues[i] = a.intValues[i] * v;
						break;
					default :
						incompatible = 1;
						break;
				}
				break;
			case Div :
				switch (a.memType){
					case REAL_TYPE :
						if (swapArgs)
							res.realValues[i] = v / a.realValues[i];
						else
							res.realValues[i] = a.realValues[i] / v;
						break;
					case INT_TYPE :
						

						if (swapArgs)
							res.realValues[i] = v / (ITI_real)a.intValues[i];
						else
							res.realValues[i] = (ITI_real)a.intValues[i] / v;
						break;
					default :
						incompatible = 1;
						break;
				}
				break;
			case Pow :
				switch (a.memType){
					case REAL_TYPE :
						if (swapArgs)
							res.realValues[i] = pow(v, a.realValues[i]);
						else
							res.realValues[i] = int_pow(a.realValues[i], v);
						break;
					case INT_TYPE :
						if (swapArgs)
							res.intValues[i] = (ITI_int)int_pow(v, a.intValues[i]);
						else
							res.intValues[i] = (ITI_int)int_pow(a.intValues[i], v);
						break;
					default :
						incompatible = 1;
						break;
				}
				break;
			default : break;
		}
	}
	if (incompatible)
		assertFunction(0, "Scale operation needs a compatible array type", sInfo);
	return res;
}

ITI_real ArrayRealValM(ITI_Array a, ITI_int n, ITI_int m)
{
	ITI_real res = 0;
	ITI_int index = ArrayIndex(a, "dd", n, m);
	if (index >= 0){
		switch (a.memType){
			case REAL_TYPE :
				res = a.realValues[index]; break;
			case INT_TYPE :
				res = (ITI_real)a.intValues[index]; break;
			default:
				break;
		}
	}
	return res;
}

ITI_int ArrayIntValM(ITI_Array a, ITI_int n, ITI_int m)
{
	ITI_int res = 0;
	ITI_int index = ArrayIndex(a, "dd", n, m);
	if (index >= 0){
		switch (a.memType){
			case REAL_TYPE :
				res = (ITI_int)a.realValues[index]; break;
			case INT_TYPE :
				res = a.intValues[index]; break;
			default:
				break;
		}
	}
	return res;
}

 

ITI_int ArrayIndex(ITI_Array a, ITI_char* fmt, ...)
{
	va_list ap;
	ITI_int i = 0;
	ITI_int index = 0;
	va_start(ap, fmt);
	while (*fmt){
		switch (*fmt++){
			case 'd' : {
				ITI_int d = 0;
				ITI_int temp = 1;
				ITI_int v = va_arg(ap, ITI_int);
				for (d = i + 1; d < a.nDims; d++){
					temp *= a.dims[d];
				}

				if (i + 1 == a.nDims)
					index += v;
				else
					index += temp * v;

				i++;
				break;
			}
			default :
				assertFunction(0, "Index type is not valid", 0);
				break;
		}
	}
	va_end(ap);
	return index;
}

ITI_real ArrayValReal(const ITI_Array a, int index)
{
	ITI_real res = 0.0;
	switch (a.memType){
		case REAL_TYPE :
			if (a.realValues)
				res = a.realValues[index];
			break;
		case INT_TYPE :
			if (a.intValues)
				res = a.intValues[index];
			break;
		case STRING_TYPE :
			assertFunction(0, "Can not convert ITI_char to ITI_real", 0);
			break;
		default:
			break;
	}
	return res;
}

ITI_int ArrayValInt(const ITI_Array a, int index)
{
	ITI_int res = 0;
	switch (a.memType){
		case REAL_TYPE :
			if (a.realValues)
				res = (int)a.realValues[index];
			break;
		case INT_TYPE :
			if (a.intValues)
				res = a.intValues[index];
			break;
		case STRING_TYPE :
			assertFunction(0, "Can not convert ITI_char to ITI_int", 0);
			break;
		default:
			break;
	}
	return res;
}

ITI_char* ArrayValStr(const ITI_Array a, int index)
{
	ITI_char* res = 0;
	switch (a.memType){
		case REAL_TYPE :
			assertFunction(0, "Can not convert ITI_real ITI_char*", 0);
			break;
		case INT_TYPE :
			assertFunction(0, "Can not convert ITI_int to ITI_char*", 0);
			break;
		case STRING_TYPE :
			if (a.charValues)
				res = a.charValues[index];
			break;
		default:
			break;
	}
	return res;
}

ITI_Array ArrayAdd(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, const ITI_Array a1, const ITI_Array a2)
{
	return ArrayOp(sInfo, currMem, Add, a1, a2);
}

ITI_Array ArraySub(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, const ITI_Array a1, const ITI_Array a2)
{
	return ArrayOp(sInfo, currMem, Sub, a1, a2);
}

ITI_Array ArrayMulReal(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, const ITI_Array a,
																const ITI_real v)
{
	return ArrayScaleOpReal(sInfo, currMem, Mul, a, v, 0);
}

ITI_Array ArrayMulInt(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, const ITI_Array a,
																const ITI_int v)
{
	return ArrayScaleOpInt(sInfo, currMem, Mul, a, v, 0);
}

ITI_Array ArrayDivReal(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, const ITI_Array a,
																const ITI_real v)
{
	return ArrayScaleOpReal(sInfo, currMem, Div, a, v, 0);
}

ITI_Array ArrayDivInt(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, const ITI_Array a,
																const ITI_int v)
{
	return ArrayScaleOpInt(sInfo, currMem, Div, a, v, 0);
}

ITI_real ArrayScalarProd(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem,
								const ITI_Array a1, const ITI_Array a2)
{
	ITI_int i;
	ITI_real res = 0.0;
	ITI_int dim = a1.dims[0];
	assertFunction(a1.nDims == 1,
		"A scalar product needs a vector as first operand", sInfo);
	assertFunction(a2.nDims == 1,
		"A scalar product needs a vector as second operand", sInfo);
	assertFunction(ArrayMatching(a1, a2),
		"A scalar product requires a matching vector size", sInfo);
	switch (a1.memType){
		case INT_TYPE :
			for (i = 0; i < dim; i++){
				res += a1.intValues[i]*
					(a2.memType==REAL_TYPE?a2.realValues[i]:a2.intValues[i]);
			}
			break;
		case REAL_TYPE :
			for (i = 0; i < dim; i++){
				res += a1.realValues[i]*
					(a2.memType==REAL_TYPE?a2.realValues[i]:a2.intValues[i]);
			}
			break;
		case STRING_TYPE : break;
		default:
			break;
	}
	return res;
}

ITI_Array ArrayArrayOp(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem,
					const ITI_Array a1, const ITI_Array a2, enum Op op)
{
	return ArrayOp(sInfo, currMem, op, a1, a2);
}

ITI_Array ArrayMulMM(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem,
							const ITI_Array a1, const ITI_Array a2)
{
	ITI_Array res;
	ITI_int i = 0;
	ITI_int j = 0;
	ITI_int k = 0;
	ITI_int index = 0;
	ITI_int sumInt = 0;
	ITI_real sumReal = 0;
	InitArray(&res);
	

	assertFunction(a1.nDims==2&&a2.nDims==2,
		"Matrix multiply requires that both operands are a matrix", sInfo);
	assertFunction(a1.dims[1]==a2.dims[0],
		"Matrix multiply requires that inner dimensions of operands match", sInfo);
	res.nDims = 2;
	if (a1.memType == REAL_TYPE)
		res.memType = a1.memType;
	else
		res.memType = a2.memType;
	res.dims = GetIntMemory(currMem, 2);
	res.dims[0] = a1.dims[0];
	res.dims[1] = a2.dims[1];
	switch (res.memType){
		case REAL_TYPE :
			res.realValues = GetRealMemory(currMem, res.dims[0]*res.dims[1]);
			break;
		case INT_TYPE :
			res.intValues = GetIntMemory(currMem, res.dims[0]*res.dims[1]);
			break;
		case STRING_TYPE : break;
		default:
			break;
	}
	for (i = 0; i < a1.dims[0]; i++){
		for (j = 0; j < a2.dims[1]; j++){
			sumInt = 0;
			sumReal = 0;
			for (k = 0; k < a1.dims[1]; k++){
				switch (res.memType){
					case REAL_TYPE :
						sumReal += (a1.memType==REAL_TYPE?ArrayRealValM(a1, i, k):
									ArrayIntValM(a1, i, k))*
									(a2.memType==REAL_TYPE?ArrayRealValM(a2, k, j):
									ArrayIntValM(a2, k, j));
						break;
					case INT_TYPE :
						sumInt += ArrayIntValM(a1, i, k)*
									ArrayIntValM(a2, k, j);
						break;
					case STRING_TYPE : break;
					default:
						break;
				}
			}
			index = ArrayIndex(res, "dd", i, j);
			switch (res.memType){
				case REAL_TYPE :
					res.realValues[index] = sumReal;
					break;
				case INT_TYPE :
					res.intValues[index] = sumInt;
					break;
				case STRING_TYPE : break;
				default:
					break;
			}
		}
	}
	return res;
}

ITI_Array ArrayMulMV(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem,
								const ITI_Array a1, const ITI_Array a2)
{
	ITI_Array res;
	ITI_int j = 0;
	ITI_int k = 0;
	InitArray(&res);
	

	assertFunction(a1.nDims==2,
		"Matrix times vector requires that the first operand is a matrix", sInfo);
	assertFunction(a2.nDims==1,
		"Matrix times vector requires that the second operand is a vector", sInfo);
	assertFunction(a1.dims[1]==a2.dims[0],
		"Matrix times vector requires: a1[j,k] a2[k]", sInfo);
	res.nDims = 1;
	if (a1.memType == REAL_TYPE)
		res.memType = REAL_TYPE;
	else
		res.memType =  a2.memType;
	res.dims = GetIntMemory(currMem, 1);
	res.dims[0] = a1.dims[0];
	switch (res.memType){
		case REAL_TYPE :
			res.realValues = GetRealMemory(currMem, res.dims[0]);
			break;
		case INT_TYPE :
			res.intValues = GetIntMemory(currMem, res.dims[0]);
			break;
		case STRING_TYPE : break;
		default:
			break;
	}
	for (j = 0; j < a1.dims[0]; j++){
		ITI_int sumInt = 0;
		ITI_real sumReal = 0;
		for (k = 0; k < a2.dims[0]; k++){
			switch (res.memType){
				case REAL_TYPE :
					sumReal += (a1.memType==REAL_TYPE?ArrayRealValM(a1, j, k):
								ArrayIntValM(a1, j, k))*
								(a2.memType==REAL_TYPE?a2.realValues[k]:
								a2.intValues[k]);
					break;
				case INT_TYPE :
					sumInt += ArrayIntValM(a1, j, k)*a2.intValues[k];
					break;
				case STRING_TYPE : break;
				default:
					break;
			}
		}
		switch (res.memType){
			case REAL_TYPE :
				res.realValues[j] = sumReal;
				break;
			case INT_TYPE :
				res.intValues[j] = sumInt;
				break;
			case STRING_TYPE : break;
			default:
				break;
		}
	}
	return res;
}

ITI_Array ArrayMulVM(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem,
								const ITI_Array a1, const ITI_Array a2)
{
	ITI_Array res;
	ITI_int j = 0;
	ITI_int k = 0;
	InitArray(&res);
	

	assertFunction(a1.nDims==1,
		"Vector times matrix requires that the first operand is a vector", sInfo);
	assertFunction(a2.nDims==2,
		"Vector times matrix requires that the second operand is a matrix", sInfo);
	assertFunction(a1.dims[0]==a2.dims[0],
		"Vector times matrix requires: a1[k] a2[k, j]", sInfo);
	res.nDims = 1;
	if (a1.memType == REAL_TYPE)
		res.memType = REAL_TYPE;
	else
		res.memType =  a2.memType;
	res.dims = GetIntMemory(currMem, 1);
	res.dims[0] = a2.dims[1];
	switch (res.memType){
		case REAL_TYPE :
			res.realValues = GetRealMemory(currMem, res.dims[0]);
			break;
		case INT_TYPE :
			res.intValues = GetIntMemory(currMem, res.dims[0]);
			break;
		case STRING_TYPE : break;
		default:
			break;
	}
	for (j = 0; j < a2.dims[1]; j++){
		ITI_int sumInt = 0;
		ITI_real sumReal = 0;
		for (k = 0; k < a1.dims[0]; k++){
			switch (res.memType){
				case REAL_TYPE :
					sumReal += (a1.memType==REAL_TYPE?a1.realValues[k]:a1.intValues[k])*(a2.memType==REAL_TYPE?ArrayRealValM(a2, k, j):ArrayIntValM(a2, k, j));
					break;
				case INT_TYPE :
					sumInt += a1.intValues[k]*ArrayIntValM(a2, k, j);
					break;
				case STRING_TYPE : break;
				default:
					break;
			}
		}
		switch (res.memType){
			case REAL_TYPE :
				res.realValues[j] = sumReal;
				break;
			case INT_TYPE :
				res.intValues[j] = sumInt;
				break;
			case STRING_TYPE : break;
			default:
				break;
		}
	}
	return res;
}

ITI_char* AddString(ITI_MemoryObject* currMem, const ITI_char* str1, const ITI_char* str2)
{
	ITI_char* ret = GetStringMemory(currMem, (int)strlen(str1) + (int)strlen(str2));
	strcpy(ret, str1);
	strcat(ret, str2);
	return ret;
}

#define MAX_PRECISION 50	 
#define MAX_WIDTH 50		 

ITI_char* RealToString(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem,
									ITI_real val, ITI_int leftJustified,
									ITI_int minLen, ITI_int signifDig)
{
	ITI_char* ret;
	ITI_char buf[100];
	assertFunction(minLen < MAX_WIDTH && signifDig < MAX_PRECISION,
										"Error in RealToString()", sInfo);
	sprintf(buf, leftJustified?"%-*.*g":"%*.*g", minLen, signifDig, val);
	ret = GetStringMemory(currMem, (int)strlen(buf));
	strcpy(ret, buf);
	return ret;
}

ITI_char* IntToString(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem,
									ITI_int val, ITI_int leftJustified,
									ITI_int minLen, ITI_int signifDig)
{
	ITI_char* ret;
	ITI_char buf[100];
	assertFunction(minLen < MAX_WIDTH && signifDig < MAX_PRECISION,
										"Error in IntToString()", sInfo);
	sprintf(buf, leftJustified?"%-*.*d":"%*.*d", minLen, signifDig, val);
	ret = GetStringMemory(currMem, (int)strlen(buf));
	strcpy(ret, buf);
	return ret;
}

ITI_char* BooleanToString(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem,
						ITI_uint val, ITI_int leftJustified, ITI_int minLen)
{
	ITI_char* ret;
	ITI_char buf[100];
	assertFunction(minLen < MAX_WIDTH, "Error in BooleanToString()", sInfo);
	sprintf(buf, leftJustified?"%-*s":"%*s", minLen, val?"true":"false");
	ret = GetStringMemory(currMem, (int)strlen(buf));
	strcpy(ret, buf);
	return ret;
}

ITI_char* RealToStringFormat(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem,
											ITI_real val, ITI_char* format)
{
	char buf[100];
	char* ret;
	buf[99] = '\0';
	sprintf(buf, AddString(currMem, "%", format), val);
	assertFunction(buf[99]=='\0', "Error in RealToStringFormat", sInfo);
	ret = GetStringMemory(currMem, (int)strlen(buf));
	strcpy(ret, buf);
	return ret;
}

void AssignString(ITI_MemoryObject* strMem, const ITI_char** dest, const ITI_char* src)
{
	if (src && dest){
		ITI_char* strTemp;
		if(*dest != NULL && strcmp(*dest, src) == 0)
			return;
		strTemp = GetStringMemory(strMem, (int)strlen(src));
		strcpy(strTemp, src);
		*dest = strTemp;
	}
}
void AssignString2(ITI_MemoryObject* strMem, const ITI_char** dest, const ITI_char* src, const ITI_char** strData, size_t* strSize, ITI_int index) {
	ITI_uint isfromData = 0;
	if (!(*dest)) {
		*dest = strData[index];
		isfromData = 1;
	}

	if (src && dest){
		ITI_uint len = (ITI_uint)strlen(src);
		if(len>0){
			if (strSize && index >= 0){
				if (len <= strSize[index]) {
					 
					strcpy((ITI_char*)(*dest), src);
				}
				else {
					AssignString(strMem, dest, src);
					if (isfromData == 1)
						strData[index] = *dest;
					strSize[index] = len;
				}
			}
			else{
				if (len <= strlen(*dest)) {
					 
					strcpy((ITI_char*)(*dest), src);
				}
				else
					AssignString(strMem, dest, src);
			}
		}
	}
}

void InitString(ITI_MemoryObject* strMem, const ITI_char** dest, ITI_uint size)
{
	ITI_char* strTemp = GetStringMemory(strMem, size);
	strcpy(strTemp, "");
	*dest = strTemp;
}

void InitString2(ITI_MemoryObject* strMem, const ITI_char** dest, ITI_uint size, size_t* strLengths, ITI_int index)
{
	if (dest){
		if (strLengths && index >= 0){
			if (size > strLengths[index]){
				InitString(strMem, dest, size);
				strLengths[index] = size;
			}
			else {
				 
				strcpy((ITI_char*)(*dest), "");
			}
		}
		else {
			InitString(strMem, dest, size);
		}
	}
}

ITI_real ArrayRealMin(const ITI_Array a)
{
	ITI_int i;
	ITI_real res = a.realValues[0];
	ITI_int size = GetNumArrayValues(a);
	for (i = 0; i < size; i++){
		if (a.realValues[i] < res)
			res = a.realValues[i];
	}
	return res;
}

ITI_int ArrayIntMin(const ITI_Array a)
{
	ITI_int i;
	ITI_int res = a.intValues[0];
	ITI_int size = GetNumArrayValues(a);
	for (i = 0; i < size; i++){
		if (a.intValues[i] < res)
			res = a.intValues[i];
	}
	return res;
}

ITI_real ArrayRealMax(const ITI_Array a)
{
	ITI_int i;
	ITI_real res = a.realValues[0];
	ITI_int size = GetNumArrayValues(a);
	for (i = 0; i < size; i++){
		if (a.realValues[i] > res)
			res = a.realValues[i];
	}
	return res;
}

ITI_int ArrayIntMax(const ITI_Array a)
{
	ITI_int i;
	ITI_int res = a.intValues[0];
	ITI_int size = GetNumArrayValues(a);
	for (i = 0; i < size; i++){
		if (a.intValues[i] > res)
			res = a.intValues[i];
	}
	return res;
}

ITI_real ArrayRealSum(const ITI_Array a)
{
	ITI_int i;
	ITI_real res = 0;
	ITI_int size = GetNumArrayValues(a);
	for (i = 0; i < size; i++){
		res += a.realValues[i];
	}
	return res;
}

ITI_int ArrayIntSum(const ITI_Array a)
{
	ITI_int i;
	ITI_int res = 0;
	ITI_int size = GetNumArrayValues(a);
	for (i = 0; i < size; i++){
		res += a.intValues[i];
	}
	return res;
}

ITI_real ArrayRealProduct(const ITI_Array a)
{
	ITI_int i;
	ITI_real res = 1;
	ITI_int size = GetNumArrayValues(a);
	for (i = 0; i < size; i++){
		res *= a.realValues[i];
	}
	return res;
}

ITI_int ArrayIntProduct(const ITI_Array a)
{
	ITI_int i;
	ITI_int res = 1;
	ITI_int size = GetNumArrayValues(a);
	for (i = 0; i < size; i++){
		res *= a.intValues[i];
	}
	return res;
}

ITI_real ArrayRealScalar(ITI_SolverInfo* sInfo, const ITI_Array a)
{
	assertFunction(GetNumArrayValues(a)==1,
			"The argument 1 of function \"scalar\" has to be a simple value.", sInfo);
	return a.realValues[0];
}

ITI_int ArrayIntScalar(ITI_SolverInfo* sInfo, const ITI_Array a)
{
	assertFunction(GetNumArrayValues(a)==1,
			"The argument 1 of function \"scalar\" has to be a simple value.", sInfo);
	return a.intValues[0];
}

ITI_Array ArraySize(ITI_MemoryObject* currMem, const ITI_Array a)
{
	int i;
	ITI_Array sizeArray;
	InitArray(&sizeArray);
	sizeArray.nDims = 1;
	sizeArray.dims = GetIntMemory(currMem, sizeArray.nDims);
	sizeArray.dims[0] = a.nDims;
	sizeArray.memType = INT_TYPE;
	sizeArray.intValues = GetIntMemory(currMem, a.nDims);
	for (i = 0; i < a.nDims; i++){
		sizeArray.intValues[i] = a.dims[i];
	}
	return sizeArray;
}

void ArrayAssign(ITI_MemoryObject* currMem, ITI_SolverInfo* sInfo,
									ITI_Array* dest, ITI_Array src)
{
	int i;
	int nValues = 1;

	assertFunction(dest->nDims==src.nDims || (src.nDims>0 && !dest->dims),
		"ArrayAssign: Dimensions must have the same sizes.", sInfo);
	assertFunction(dest->memType==UNKNOWN_TYPE || dest->memType==src.memType,
		"ArrayAssign: The value type must be the same.", sInfo);

	dest->nDims = src.nDims;
	dest->memType = src.memType;
	if (!dest->dims) {
		dest->dims = GetIntMemory(currMem, dest->nDims);
	}
	for (i = 0; i < src.nDims; i++){
		dest->dims[i] = src.dims[i];
		nValues *= src.dims[i];
	}
	switch (src.memType){
		case REAL_TYPE :
			if (!dest->realValues){
				dest->realValues = GetRealMemory(currMem, nValues);
			}
			for  (i = 0; i < nValues; i++){
				dest->realValues[i] = src.realValues[i];
			}
			break;
		case INT_TYPE :
			if (!dest->intValues){
				dest->intValues = GetIntMemory(currMem, nValues);
			}
			for  (i = 0; i < nValues; i++){
				dest->intValues[i] = src.intValues[i];
			}
			break;
		case STRING_TYPE :
			if (!dest->charValues){
				dest->charValues = GetStringPtrMemory(currMem, nValues);
			}
			for  (i = 0; i < nValues; i++){
				AssignString(currMem, (const ITI_char**)&dest->charValues[i], src.charValues[i]);
			}
			break;
		default:
			break;
	}
}

ITI_Array FillIntArray(ITI_MemoryObject* currMem, ITI_int val, ITI_int nDims, ...)
{
	ITI_int i;
	va_list ap;
	ITI_Array res;
	ITI_int nValues;

	va_start(ap, nDims);
	res = CreateIntArrayWithDims(currMem, nDims, ap);
	InitArray(&res);

	nValues = GetNumArrayValues(res);
	res.intValues = GetIntMemory(currMem, nValues);
	for (i = 0; i < nValues; i++){
		res.intValues[i] = val;
	}
	va_end(ap);
	return res;
}

ITI_Array FillIntArrayWithArray(ITI_MemoryObject* currMem, ITI_Array valArr, ITI_int nDims, ...)
{
	ITI_int i,j;
	va_list ap;
	ITI_Array res;
	ITI_int nValues;
	ITI_int nArrValues;
	ITI_int size;

	nArrValues = GetNumArrayValues(valArr);

	va_start(ap, nDims);
	res = CreateIntArrayWithDimsExt(currMem, nDims, nArrValues, ap);
	InitArray(&res);

	nValues = GetNumArrayValues(res);
	res.intValues = GetIntMemory(currMem, nValues);

	size = nValues/nArrValues;

	for (i = 0; i < size; i++){
		for (j = 0; j < nArrValues; j++){
			res.intValues[i*nArrValues+j] = valArr.intValues[j];
		}
	}
	va_end(ap);
	return res;
}

ITI_Array FillRealArray(ITI_MemoryObject* currMem, ITI_real val, ITI_int nDims, ...)
{
	ITI_int i;
	va_list ap;
	ITI_Array res;
	ITI_int nValues;

	va_start(ap, nDims);
	res = CreateRealArrayWithDims(currMem, nDims, ap);
	InitArray(&res);

	nValues = GetNumArrayValues(res);
	res.realValues = GetRealMemory(currMem, nValues);
	for (i = 0; i < nValues; i++){
		res.realValues[i] = val;
	}
	va_end(ap);
	return res;
}

ITI_Array FillRealArrayWithArray(ITI_MemoryObject* currMem, ITI_Array valArr, ITI_int nDims, ...)
{
	ITI_int i,j;
	va_list ap;
	ITI_Array res;
	ITI_int nValues;
	ITI_int nArrValues;
	ITI_int size;

	nArrValues = GetNumArrayValues(valArr);

	va_start(ap, nDims);
	res = CreateRealArrayWithDimsExt(currMem, nDims, nArrValues, ap);
	InitArray(&res);

	nValues = GetNumArrayValues(res);
	res.realValues = GetRealMemory(currMem, nValues);

	size = nValues/nArrValues;

	for (i = 0; i < size; i++){
		for (j = 0; j < nArrValues; j++){
			res.realValues[i*nArrValues+j] = valArr.realValues[j];
		}
	}
	va_end(ap);
	return res;
}

ITI_Array FillStringArray(ITI_MemoryObject* currMem, const ITI_char* val, ITI_int nDims, ...)
{
	ITI_int i;
	va_list ap;
	ITI_Array res;
	ITI_int nValues;

	va_start(ap, nDims);
	res = CreateStringArrayWithDims(currMem, nDims, ap);
	InitArray(&res);

	nValues = GetNumArrayValues(res);
	res.charValues = GetStringPtrMemory(currMem, nValues);
	for (i = 0; i < nValues; i++){
		AssignString(currMem, (const ITI_char**)&res.charValues[i], val);
	}
	va_end(ap);
	return res;
}

ITI_Array ArrayVector(ITI_MemoryObject* currMem, ITI_Array a)
{
	ITI_int i;
	ITI_Array res;
	ITI_int nValues;

	InitArray(&res);

	res.nDims = 1;
	res.dims = GetIntMemory(currMem, res.nDims);
	nValues = GetNumArrayValues(a);
	res.dims[0] = nValues;

	res.memType = a.memType;
	switch (a.memType){
		case REAL_TYPE :
			res.realValues = GetRealMemory(currMem, nValues);
			for  (i = 0; i < nValues; i++){
				res.realValues[i] = a.realValues[i];
			}
			break;
		case INT_TYPE :
			res.intValues = GetIntMemory(currMem, nValues);
			for  (i = 0; i < nValues; i++){
				res.intValues[i] = a.intValues[i];
			}
			break;
		case STRING_TYPE : break;
		default:
			break;
	}
	return res;
}

ITI_Array ArrayVectorReal(ITI_MemoryObject* currMem, ITI_real v)
{
	ITI_Array res;

	InitArray(&res);
	res.nDims = 1;
	res.dims = GetIntMemory(currMem, res.nDims);
	res.dims[0] = 1;
	res.realValues = GetRealMemory(currMem, 1);
	res.realValues[0] = v;
	res.memType = REAL_TYPE;
	return res;
}

ITI_Array ArrayVectorInt(ITI_MemoryObject* currMem, ITI_int v)
{
	ITI_Array res;

	InitArray(&res);
	res.nDims = 1;
	res.dims = GetIntMemory(currMem, res.nDims);
	res.dims[0] = 1;
	res.intValues = GetIntMemory(currMem, 1);
	res.intValues[0] = v;
	res.memType = INT_TYPE;
	return res;
}

ITI_Array ArrayRealDiagonal(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_Array a)
{
	ITI_int i, j;
	ITI_Array res;
	ITI_int nValues;

	InitArray(&res);

	assertFunction(a.nDims==1, "Diagonal operation needs a vector as input.", sInfo);
	nValues = GetNumArrayValues(a);
	res = CreateRealArray(currMem, 2, nValues, nValues);

	for (i = 0; i < nValues; i++){
		for (j = 0; j < nValues; j++){
			if (i == j)
				res.realValues[i*nValues+j] = a.realValues[i];
			else
				res.realValues[i*nValues+j] = 0;
		}
	}
	return res;
}

ITI_Array ArrayIntDiagonal(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_Array a)
{
	ITI_int i, j;
	ITI_Array res;
	ITI_int nValues;

	InitArray(&res);

	assertFunction(a.nDims==1, "Diagonal operation needs a vector as input.", sInfo);
	nValues = GetNumArrayValues(a);
	res = CreateIntArray(currMem, 2, nValues, nValues);

	for (i = 0; i < nValues; i++){
		for (j = 0; j < nValues; j++){
			if (i == j)
				res.intValues[i*nValues+j] = a.intValues[i];
			else
				res.intValues[i*nValues+j] = 0;
		}
	}
	return res;
}

ITI_Array ArrayIdentity(ITI_MemoryObject* currMem, ITI_int n)
{
	ITI_int i, j;
	ITI_Array res;

	InitArray(&res);

	res = CreateIntArray(currMem, 2, n, n);

	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			res.intValues[i*n+j] = i==j?1:0;
		}
	}
	return res;
}

ITI_Array ArrayMatrix(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_Array a)
{
	ITI_Array res;

	if (a.nDims == 1){
		res = Promote(currMem, a, 2);
	}
	else {
		InitArray(&res);
		res.nDims = 2;
		res.dims = GetIntMemory(currMem, 2);
		res.dims[0] = a.dims[0];
		res.dims[1] = a.dims[1];
		res.memType = a.memType;

		switch (a.memType){
			case REAL_TYPE :
				res.realValues = a.realValues;
				break;
			case INT_TYPE :
				res.intValues = a.intValues;
				break;
			default:
				break;
		}
		assertFunction(GetNumArrayValues(res)==GetNumArrayValues(a),
					"The higher dimensions (>2) of the argument of the matrix function must be of size 1.",
					sInfo);
	}
	return res;
}

ITI_Array ArrayTranspose(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_Array a)
{
	ITI_int i,j,k,i1,i2,size1,size2,nValues;
	ITI_int size3 = 1;
	ITI_Array res;

	assertFunction(a.nDims>=2,
					"The argument of the transpose function must be at least a matrix.", sInfo);
	InitArray(&res);

	if (!a.dims){
		res.nDims = 0;
		res.dims = 0;
		res.memType = a.memType;
		return res;
	}

	res.nDims = a.nDims;
	res.dims = GetIntMemory(currMem, a.nDims);
	size1 = a.dims[0];
	size2 = a.dims[1];
	res.dims[0] = size2;
	res.dims[1] = size1;
	for (i = 2; i < a.nDims; i++){
		size3 *= a.dims[i];
		res.dims[i] = a.dims[i];
	}
	res.memType = a.memType;
	nValues = GetNumArrayValues(a);

	switch (a.memType){
		case REAL_TYPE :
			res.realValues = GetRealMemory(currMem, nValues);
			break;
		case INT_TYPE :
			res.intValues = GetIntMemory(currMem, nValues);
			break;
		default:
			break;
	}

	for (i = 0; i < size1; i++){
		for (j = 0; j < size2; j++){
			for (k = 0; k < size3; k++){
				i1 = i*size2*size3 + j*size3 + k;
				i2 = j*size1*size3 + i*size3 + k;

				switch (a.memType){
					case REAL_TYPE :
						res.realValues[i2] = a.realValues[i1];
						break;
					case INT_TYPE :
						res.intValues[i2] = a.intValues[i1];
						break;
					default:
						break;
				}
			}
		}
	}
	return res;
}

ITI_Array* ArrayRefTranspose(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_Array* a)
{
	if (a){
		ITI_int i;
		ITI_int nValues = GetNumArrayValues(*a);
		ITI_Array transArray = ArrayTranspose(sInfo, currMem, *a);

		a->dims[0] = transArray.dims[0];
		a->dims[1] = transArray.dims[1];

		for (i = 0; i < nValues; i++){
			switch (a->memType){
				case REAL_TYPE :
					a->realValues[i] = transArray.realValues[i];
					break;
				case INT_TYPE :
					a->intValues[i] = transArray.intValues[i];
					break;
				default:
					break;
			}
		}
	}
	return a;
}

ITI_Array ArrayOuterProduct(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem,
													ITI_Array a, ITI_Array b)
{
	ITI_Array res;
	ITI_real v1, v2;
	ITI_int aDims, bDims, i, j;

	assertFunction(a.nDims==1&&b.nDims==1,
					"The arguments of the function outerProduct must be vectors.", sInfo);
	aDims = a.dims[0];
	bDims = b.dims[0];

	InitArray(&res);

	if (a.memType == REAL_TYPE || b.memType == REAL_TYPE)
		res = CreateRealArray(currMem, 2, aDims, bDims);
	else
		res = CreateIntArray(currMem, 2, aDims, bDims);

	for (i = 0; i < aDims; i++){
		for (j = 0; j < bDims; j++){
			switch (res.memType){
				case REAL_TYPE : {
					v1 = (a.memType==INT_TYPE?(ITI_real)a.intValues[i]:a.realValues[i]);
					v2 = (b.memType==INT_TYPE?(ITI_real)b.intValues[j]:b.realValues[j]);
					res.realValues[i*bDims+j] = v1*v2;
					break;
				}
				case INT_TYPE :
					res.intValues[i*bDims+j] = a.intValues[i]*b.intValues[j];
					break;
				default:
					break;
			}
		}
	}
	return res;
}

ITI_Array ArrayCross(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem,
												ITI_Array a, ITI_Array b)
{
	ITI_Array res;
	ITI_real av1,av2,av3,bv1,bv2,bv3;

	assertFunction(a.nDims==1&&b.nDims==1,
					"The arguments of the function cross must be vectors.", sInfo);
	assertFunction(a.dims[0]==3,
			"The first argument of the function cross must be a 3-vector.", sInfo);
	assertFunction(b.dims[0]==3,
			"The second argument of the function cross must be a 3-vector.", sInfo);

	InitArray(&res);

	if (a.memType == REAL_TYPE || b.memType == REAL_TYPE)
		res = CreateRealArray(currMem, 1, 3);
	else
		res = CreateIntArray(currMem, 1, 3);

	switch (res.memType){
		case REAL_TYPE :
			av1 = (a.memType==INT_TYPE?(ITI_real)a.intValues[0]:a.realValues[0]);
			av2 = (a.memType==INT_TYPE?(ITI_real)a.intValues[1]:a.realValues[1]);
			av3 = (a.memType==INT_TYPE?(ITI_real)a.intValues[2]:a.realValues[2]);
			bv1 = (b.memType==INT_TYPE?(ITI_real)b.intValues[0]:b.realValues[0]);
			bv2 = (b.memType==INT_TYPE?(ITI_real)b.intValues[1]:b.realValues[1]);
			bv3 = (b.memType==INT_TYPE?(ITI_real)b.intValues[2]:b.realValues[2]);
			res.realValues[0] = av2*bv3 - av3*bv2;
			res.realValues[1] = av3*bv1 - av1*bv3;
			res.realValues[2] = av1*bv2 - av2*bv1;
			break;
		case INT_TYPE :
			res.intValues[0] = a.intValues[1]*b.intValues[2] - a.intValues[2]*b.intValues[1];
			res.intValues[1] = a.intValues[2]*b.intValues[0] - a.intValues[0]*b.intValues[2];
			res.intValues[2] = a.intValues[0]*b.intValues[1] - a.intValues[1]*b.intValues[0];
			break;
		default:
			break;
	}
	return res;
}

ITI_Array ArraySkew(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_Array a)
{
	ITI_Array res;

	assertFunction(a.nDims==1&&a.dims[0]==3,
			"The argument of the function skew must be a 3-vector.", sInfo);

	InitArray(&res);

	if (a.memType == REAL_TYPE)
		res = CreateRealArray(currMem, 2, 3, 3);
	else
		res = CreateIntArray(currMem, 2, 3, 3);

	switch (a.memType){
		case REAL_TYPE :
			res.realValues[0] = 0;
			res.realValues[1] = -a.realValues[2];
			res.realValues[2] = a.realValues[1];
			res.realValues[3] = a.realValues[2];
			res.realValues[4] = 0;
			res.realValues[5] = -a.realValues[0];
			res.realValues[6] = -a.realValues[1];
			res.realValues[7] = a.realValues[0];
			res.realValues[8] = 0;
			break;
		case INT_TYPE :
			res.intValues[0] = 0;
			res.intValues[1] = -a.intValues[2];
			res.intValues[2] = a.intValues[1];
			res.intValues[3] = a.intValues[2];
			res.intValues[4] = 0;
			res.intValues[5] = -a.intValues[0];
			res.intValues[6] = -a.intValues[1];
			res.intValues[7] = a.intValues[0];
			res.intValues[8] = 0;
		default:
			break;
	}
	return res;
}

ITI_Array ArrayLinspace(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem,
									ITI_real x1, ITI_real x2, ITI_int n)
{
	ITI_Array res;
	ITI_int i, nv;
	ITI_real dx;

	InitArray(&res);

	assertFunction(n>=2, "Linspace number of elements have to be greater than 1.", sInfo);
	res = CreateRealArray(currMem, 1, n);

	nv = n-1;
	dx = (x2-x1);
	for (i = 0; i < n; i++){
		res.realValues[i] = x1 + dx*i/nv;
	}
	return res;
}

ITI_Array ArraySymmetric(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem, ITI_Array a)
{
	ITI_Array res;
	ITI_int i,j,nValues;

	assertFunction(a.nDims==2 && a.dims[0]==a.dims[1],
			"Symmetric function needs square matrix.", sInfo);

	InitArray(&res);

	nValues = a.dims[0];

	if (a.memType == REAL_TYPE)
		res = CreateRealArray(currMem, 2, nValues, nValues);
	else
		res = CreateIntArray(currMem, 2, nValues, nValues);

	for (i = 0; i < nValues; i++){
		for (j = 0; j <= i; j++){
			if (a.memType == REAL_TYPE)
				res.realValues[i*nValues+j] = a.realValues[j*nValues+i];
			else
				res.intValues[i*nValues+j] = a.intValues[j*nValues+i];
		}
		for (; j < nValues; j++){
			if (a.memType == REAL_TYPE)
				res.realValues[i*nValues+j] = a.realValues[i*nValues+j];
			else
				res.intValues[i*nValues+j] = a.intValues[i*nValues+j];
		}
	}
	return res;
}

ITI_Array ArrayUnaryMinus(ITI_MemoryObject* currMem, const ITI_Array a)
{
	ITI_int i = 0;
	ITI_Array res;
	ITI_int nValues = GetNumArrayValues(a);

	InitArray(&res);

	res = CreateArray(currMem, a);

	for (i = 0; i < nValues; i++){
		if (a.memType == REAL_TYPE)
			res.realValues[i] = -a.realValues[i];
		else if (a.memType == INT_TYPE)
			res.intValues[i] = -a.intValues[i];
	}
	return res;
}

void ArrayInSubArray(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem,
							const ITI_Array inArr, ITI_Array outArr, ...)
{
	va_list ap;
	ITI_int i = 0;
	ITI_uint end = 0;
	ITI_int inDim = 0;
	ITI_int outDim = 0;
	ITI_int fillSize = 1;
	ITI_int nArgs = 0;
	enum ArgTag tag;
	TaggedIndices* taggedIndices;

	va_start(ap, outArr);
	while (!end){
		tag = va_arg(ap, enum ArgTag);
		switch (tag){
			case AT_Index : va_arg(ap, ITI_int); nArgs++; break;
			case AT_Colon : nArgs++; break;
			case AT_RangeEx : va_arg(ap, ITI_int);
			case AT_Range : va_arg(ap, ITI_int); va_arg(ap, ITI_int); nArgs++;break;
			case AT_Vector : va_arg(ap, ITI_Array); nArgs++;break;
			case AT_End : end = 1; break;
		}
	}
	va_end(ap);

	taggedIndices = (TaggedIndices*)GetStringMemory(currMem,
							(nArgs+1)*sizeof(TaggedIndices));

	end = 0;
	va_start(ap, outArr);
	while (!end){
		tag = va_arg(ap, enum ArgTag);
		taggedIndices[outDim].tag = tag;
		switch (tag){
			case AT_Index : {
					ITI_int i = va_arg(ap, ITI_int);
					assertFunction(outDim<outArr.nDims,
						"SetArrayInSubArray(): Error (Index)", sInfo);
					assertFunction((i>=1&&i<=outArr.dims[outDim]),
						"SetArrayInSubArray(): scalar index out of range", sInfo);
					taggedIndices[outDim].u_idx.index = i;
					outDim++;
					break;
				}
			case AT_Colon :
				assertFunction(outDim<outArr.nDims,
						"SetArrayInSubArray(): Error (:)", sInfo);
				assertFunction(inDim<inArr.nDims,
						"SetArrayInSubArray(): Error (:)", sInfo);
				assertFunction(inArr.dims[inDim]==outArr.dims[outDim],
						"SetArrayInSubArray(): Error (:) sizes don't match", sInfo);
				outDim++;
				inDim++;
				break;
			case AT_Range :
			case AT_RangeEx : {
					ITI_int start=0, stop=0, step=1, n = 0;
					start = va_arg(ap, ITI_int);
					if (tag == AT_RangeEx)
						step = va_arg(ap, ITI_int);
					stop = va_arg(ap, ITI_int);
					taggedIndices[outDim].u_idx.range[0] = start;
					taggedIndices[outDim].u_idx.range[1] = step;
					taggedIndices[outDim].u_idx.range[2] = stop;
					n = (stop-start+step)/step;
					if (n <= 0)
						n = 0;
					else {
						assertFunction((start>0&&start<=outArr.dims[outDim]),
								"SetArrayInSubArray(): start index out of range", sInfo);
						assertFunction((stop>0&&stop<=outArr.dims[outDim]),
								"SetArrayInSubArray(): stop index out of range", sInfo);
					}
					assertFunction(outDim<outArr.nDims,
						"SetArrayInSubArray(): Error (range)", sInfo);
					assertFunction(inDim<inArr.nDims,
						"SetArrayInSubArray(): Error (range)", sInfo);
					assertFunction(inArr.dims[inDim]==n,
						"SetArrayInSubArray(): Error (range) sizes don't match", sInfo);
					outDim++;
					inDim++;
					break;
				}
			case AT_Vector :
				{
					ITI_int i = 0;
					ITI_Array vec = va_arg(ap, ITI_Array);
					assertFunction(outDim<outArr.nDims,
						"SetArrayInSubArray(): Error (Vector)", sInfo);
					assertFunction(inDim<inArr.nDims,
						"SetArrayInSubArray(): Error (Vector)", sInfo);
					assertFunction(vec.nDims==1,
						"SetArrayInSubArray(): indices have to be a vector", sInfo);
					for (i = 0; i < vec.dims[0]; i++){
						 assertFunction((vec.intValues[i]>=1)&&
						 (vec.intValues[i]<=outArr.dims[outDim]),
						 "SetArrayInSubArray(): vector index out of bounds", sInfo);
					}
					taggedIndices[outDim].u_idx.vector = vec;
					outDim++;
					inDim++;
					break;
				}
			case AT_End : end = 1;
				break;
		}
	}
	va_end(ap);
	assertFunction(inArr.nDims-inDim == outArr.nDims-outDim,
			"SetArrayInSubArray(): unequal number of dimensions", sInfo);

	

	for (i = inDim; i < inArr.nDims; i++){
		fillSize *= inArr.dims[i];
		assertFunction(inArr.dims[i]==outArr.dims[(i-inDim)+outDim],
				"SetArrayInSubArray(): subscripting error", sInfo);
	}

	SetArrayInSubArray(taggedIndices, outArr, 0, 0, inArr, 0 , 0, fillSize);
}

void SetArrayInSubArray(TaggedIndices* taggedIndices, ITI_Array dest,
						ITI_int destOffset, ITI_int destDim, ITI_Array src,
						ITI_int srcOffset, ITI_int srcDim, ITI_int fillSize)
{
	ITI_int tag = taggedIndices->tag;

	switch (tag){
		case AT_Index : {
			ITI_int i = taggedIndices->u_idx.index;
			SetArrayInSubArray(taggedIndices+1, dest, destOffset*dest.dims[destDim]+
								(i-1), destDim+1, src, srcOffset, srcDim, fillSize);
			break;
		}
		case AT_Colon : {
			ITI_int newDim = src.dims[srcDim];
			ITI_int i;
			for (i = 0; i < newDim; i++){
				SetArrayInSubArray(taggedIndices+1, dest, destOffset*newDim+i,
					destDim+1, src, srcOffset*newDim+i, srcDim+1, fillSize);
			}
			break;
		}
		case AT_Range :
		case AT_RangeEx : {
			ITI_int start, step=1, srcNewDim, destNewDim, i;
			start = taggedIndices->u_idx.range[0];
			if (tag == AT_RangeEx)
				step = taggedIndices->u_idx.range[1];
			srcNewDim = src.dims[srcDim];
			destNewDim = dest.dims[destDim];
			for (i = 0; i < srcNewDim; i++){
				SetArrayInSubArray(taggedIndices+1, dest, destOffset*destNewDim+
						(start+step*i-1), destDim+1, src, srcOffset*srcNewDim+i,
						srcDim+1, fillSize);
			}
			break;
		}
		case AT_Vector : {
			ITI_int srcNewDim, destNewDim, i;
			ITI_Array vec = taggedIndices->u_idx.vector;
			srcNewDim = src.dims[srcDim];
			destNewDim = dest.dims[destDim];
			for (i = 0; i < vec.dims[0]; i++){
				SetArrayInSubArray(taggedIndices+1, dest, destOffset*destNewDim+
						vec.intValues[i]-1, destDim+1, src, srcOffset*srcNewDim+i,
						srcDim+1, fillSize);
			}
			break;
		}
		case AT_End : {
			 
			ITI_int i = 0;
			switch (src.memType){
				case REAL_TYPE : {
					ITI_real* p_dest = dest.realValues+destOffset;
					ITI_real* p_src = src.realValues+srcOffset;
					for (i = 0; i < fillSize; i++){
						*p_dest = *p_src;
						p_dest++;p_src++;
					}
					break;
				}
				case INT_TYPE : {
					ITI_int* p_dest = dest.intValues+destOffset;
					ITI_int* p_src = src.intValues+srcOffset;
					for (i = 0; i < fillSize; i++){
						*p_dest = *p_src;
						p_dest++;p_src++;
					}
					break;
				}
				case STRING_TYPE : {
					ITI_char** p_dest = dest.charValues + destOffset;
					ITI_char** p_src = src.charValues + srcOffset;
					for (i = 0; i < fillSize; i++) {
						*p_dest = *p_src;
						p_dest++; p_src++;
					}
					break;
				}
				default:
					break;
			}
		}
	}
}

ITI_Array SubArrayFromArray(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem,
														ITI_Array arr, ...)
{
	ITI_Array res;
	va_list ap;
	ITI_int i = 0;
	ITI_uint end = 0;
	ITI_int nArgs = 0;
	ITI_int arrDim = 0;
	ITI_int resDim = 0;
	ITI_int fillSize = 1;
	ITI_int nValueSize = 0;
	ITI_int nDims = arr.nDims;
	enum ArgTag tag;
	TaggedIndices* taggedIndices;

	InitArray(&res);
	res.memType = arr.memType;

	 
	va_start(ap, arr);
	while (!end){
		tag = va_arg(ap, enum ArgTag);
		switch (tag){
			case AT_Index : va_arg(ap, ITI_int); nArgs++; nDims--;break;
			case AT_Colon : nArgs++; break;
			case AT_RangeEx : va_arg(ap, ITI_int);
			case AT_Range : va_arg(ap, ITI_int); va_arg(ap, ITI_int); nArgs++;break;
			case AT_Vector : va_arg(ap, ITI_Array); nArgs++;break;
			case AT_End : end = 1; break;
		}
	}
	va_end(ap);
	res.nDims = nDims;
	res.dims = GetIntMemory(currMem, nDims);

	taggedIndices = (TaggedIndices*)GetStringMemory(currMem,
							(nArgs+1)*sizeof(TaggedIndices));

	 
	end = 0;
	va_start(ap, arr);
	while (!end){
		tag = va_arg(ap, enum ArgTag);
		taggedIndices[arrDim].tag = tag;
		switch (tag){
			case AT_Index : {
				ITI_int i = va_arg(ap, ITI_int);
				assertFunction((i>=1&&i<=arr.dims[arrDim]),
					"SubArrayFromArray(): scalar index out of range", sInfo);
				taggedIndices[arrDim].u_idx.index = i;
				break;
			}
			case AT_Colon :
				res.dims[resDim] = arr.dims[arrDim]; resDim++;
				break;
			case AT_Range :
			case AT_RangeEx : {
				ITI_int start=0, stop=0, step=1, n = 0;
				start = va_arg(ap, ITI_int);
				if (tag == AT_RangeEx)
					step = va_arg(ap, ITI_int);
				stop = va_arg(ap, ITI_int);
				taggedIndices[arrDim].u_idx.range[0] = start;
				taggedIndices[arrDim].u_idx.range[1] = step;
				taggedIndices[arrDim].u_idx.range[2] = stop;
				n = (stop-start)/step +1;
				assertFunction(n >= 0, "SubArrayFromArray(): range is not valid", sInfo);
				assertFunction((start>0&&start<=arr.dims[arrDim]),
								"SubArrayFromArray(): start index out of range", sInfo);
				assertFunction((stop>0&&stop<=arr.dims[arrDim]),
								"SubArrayFromArray(): stop index out of range", sInfo);
				res.dims[resDim] = n;
				resDim++;
				break;
			}
			case AT_Vector : {
				ITI_int dim;
				ITI_Array vec = va_arg(ap, ITI_Array);
				taggedIndices[arrDim].u_idx.vector = vec;
				assertFunction(vec.nDims==1,
						"SubArrayFromArray(): indices have to be a vector", sInfo);
				dim = vec.dims[0];
				res.dims[resDim] = dim;
				resDim++;
				for (i = 0; i < dim; i++){
					assertFunction((vec.intValues[i]>0&&vec.intValues[i]<=arr.dims[arrDim]),
						"SubArrayFromArray(): vector index out of range", sInfo);
				}
				break;
			}
			case AT_End : end = 1;
				break;
		}
		arrDim++;
	}
	va_end(ap);

	

	for (i = nArgs; i < arr.nDims; i++){
		res.dims[resDim] = arr.dims[i];
		fillSize *= arr.dims[i];
		resDim++;
	}

	 
	nValueSize = GetNumArrayValues(res);
	InitValuesMemory(currMem, &res, res.memType, nValueSize);

	GetSubArrayFromArray(taggedIndices, res, 0, 0, arr, 0, 0, fillSize);
	return res;
}

void GetSubArrayFromArray(TaggedIndices* taggedIndices, ITI_Array dest,
						ITI_int destOffset, ITI_int destDim, const ITI_Array src,
						ITI_int srcOffset, ITI_int srcDim, ITI_int fillSize)
{
	ITI_int tag = taggedIndices->tag;

	switch (tag){
		case AT_Index : {
			ITI_int i = taggedIndices->u_idx.index;
			GetSubArrayFromArray(taggedIndices+1, dest, destOffset, destDim,
						src, srcOffset*src.dims[srcDim]+i-1, srcDim+1, fillSize);
			break;
		}
		case AT_Colon : {
			ITI_int newDim = src.dims[srcDim];
			ITI_int i;
			for (i = 0; i < newDim; i++){
				GetSubArrayFromArray(taggedIndices+1, dest, destOffset*newDim+i,
						destDim+1, src, srcOffset*newDim+i, srcDim+1, fillSize);
			}
			break;
		}
		case AT_Range :
		case AT_RangeEx : {
			ITI_int start, step=1, srcNewDim, destNewDim, i;
			start = taggedIndices->u_idx.range[0];
			if (tag == AT_RangeEx)
				step = taggedIndices->u_idx.range[1];
			srcNewDim = src.dims[srcDim];
			destNewDim = dest.dims[destDim];
			for (i = 0; i < destNewDim; i++){
				GetSubArrayFromArray(taggedIndices+1, dest, destOffset*destNewDim+i,
						destDim+1, src, srcOffset*srcNewDim+(start+step*i-1),
						srcDim+1, fillSize);
			}
			break;
		}
		case AT_Vector : {
			ITI_int srcNewDim, destNewDim, i;
			ITI_Array vec = taggedIndices->u_idx.vector;
			srcNewDim = src.dims[srcDim];
			destNewDim = dest.dims[destDim];
			for (i = 0; i < vec.dims[0]; i++){
				GetSubArrayFromArray(taggedIndices+1, dest, destOffset*destNewDim+i,
						destDim+1, src, srcOffset*srcNewDim+vec.intValues[i]-1,
						srcDim+1, fillSize);
			}
			break;
		}
		case AT_End : {
			 
			ITI_int i = 0;
			switch (src.memType){
				case REAL_TYPE : {
					ITI_real* p_dest = dest.realValues+destOffset;
					ITI_real* p_src = src.realValues+srcOffset;
					for (i = 0; i < fillSize; i++){
						*p_dest = *p_src;
						p_dest++;p_src++;
					}
					break;
				}
				case INT_TYPE : {
					ITI_int* p_dest = dest.intValues+destOffset;
					ITI_int* p_src = src.intValues+srcOffset;
					for (i = 0; i < fillSize; i++){
						*p_dest = *p_src;
						p_dest++;p_src++;
					}
					break;
				}
				case STRING_TYPE : {
					ITI_char** p_dest = dest.charValues + destOffset;
					ITI_char** p_src = src.charValues + srcOffset;
					for (i = 0; i < fillSize; i++) {
						*p_dest = *p_src;
						p_dest++; p_src++;
					}
					break;
				}
				default:
					break;
			}
			break;
		}
	}
}

ITI_Array ArrayCat(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem,
			ITI_int alongDim, ITI_int nArgs, ITI_Array arr1, ...)
{
	ITI_Array res;
	ITI_Array arr;
	ITI_int i,j;
	va_list ap;
	ITI_int nValues;
	ITI_int mark = 0;
	ITI_int preAlongSize = 1;
	ITI_int postAlongSize = 1;

	InitArray(&res);

	res.memType = arr1.memType;
	 
	va_start(ap, arr1);
	if (arr1.memType != REAL_TYPE){
		for (j = 1; j < nArgs; j++){
			arr = va_arg(ap, ITI_Array);
			res.memType = arr.memType;
			if (arr.memType == REAL_TYPE){
				break;
			}
		}
	}
	va_end(ap);

	res.nDims = arr1.nDims;
	res.dims = GetIntMemory(currMem, arr1.nDims);
	alongDim--;  


	 
	for (i = 0; i < arr1.nDims; i++){
		res.dims[i] = arr1.dims[i];
	}

	va_start(ap, arr1);
	for (j = 1; j < nArgs; j++){
		arr = va_arg(ap, ITI_Array);
		assertFunction((arr.nDims==arr1.nDims),
					"ArrayCat : Number of dimensions does not match.", sInfo);
		res.dims[alongDim] += arr.dims[alongDim];
	}
	va_end(ap);

	 
	nValues = GetNumArrayValues(res);
	InitValuesMemory(currMem, &res, res.memType, nValues);

	for (i = 0; i < alongDim; i++){
		preAlongSize *= res.dims[i];
	}
	for (i = alongDim+1; i < res.nDims; i++){
		postAlongSize *= res.dims[i];
	}
	va_start(ap, arr1);
	for (i = 0; i < nArgs; i++){
		ITI_int pre, post, curr;
		if (i == 0)
			arr = arr1;
		else
			arr = va_arg(ap, ITI_Array);

		for (pre = 0; pre < preAlongSize; pre++){
			for (curr = 0; curr < arr.dims[alongDim]; curr++){
				for (post = 0; post < postAlongSize; post++){
					ITI_int arrIndex = (pre*arr.dims[alongDim]+curr)*
													postAlongSize+post;
					ITI_int resIndex = (pre*res.dims[alongDim]+(curr+mark))*
													postAlongSize+post;
					if (arr.memType == INT_TYPE){
						ITI_int val = arr.intValues[arrIndex];
						if (res.memType == INT_TYPE)
							res.intValues[resIndex] = val;
						else
							res.realValues[resIndex] = val;
					}
					else {
						ITI_real val = arr.realValues[arrIndex];
						if (res.memType == INT_TYPE)
							res.intValues[resIndex] = (ITI_int)val;
						else
							res.realValues[resIndex] = val;
					}
				}
			}
		}
		mark += arr.dims[alongDim];
	}
	va_end(ap);
	return res;
}

ITI_Array RealRangeArray(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem,
							ITI_real start, ITI_real step, ITI_real end)
{
	ITI_Array res;
	ITI_int size;
	ITI_int i;

	if (step==0  )
		assertFunction(0, "RealRangeArray : range is not valid.", sInfo);

	InitArray(&res);
	res.memType = REAL_TYPE;
	res.nDims = 1;
	res.dims = GetIntMemory(currMem, 1);

	if ((step>0 && start>end) || (step<0 && start<end))
		size = 0;
	else {
		const double eps=(step<0?-1:1)*(fabs(start)+fabs(end))*DBL_EPSILON;
		size = (int)floor((end-start+eps)/step)+1;
	}
	res.dims[0] = size;

	if (size > 0) {
		res.realValues = GetRealMemory(currMem, size);

		for (i = 0; i < size; i++) {
			res.realValues[i]=start+i*step;
		}
	}
	return res;
}

ITI_Array IntRangeArray(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem,
							ITI_int start, ITI_int step, ITI_int end)
{
	ITI_Array res;
	ITI_int size;
	ITI_int i;

	if (step==0  )
		assertFunction(0, "IntRangeArray : range is not valid.", sInfo);

	InitArray(&res);
	res.memType = INT_TYPE;
	res.nDims = 1;
	res.dims = GetIntMemory(currMem, 1);

	if ((step>0 && start>end) || (step<0 && start<end))
		size = 0;
	else
		size = (int)floor((end-start)/step)+1;
	res.dims[0] = size;

	if (size > 0) {
		res.intValues = GetIntMemory(currMem, size);

		for (i = 0; i < size; i++) {
			res.intValues[i]=start+i*step;
		}
	}
	return res;
}

void SetRealInArray(ITI_SolverInfo* sInfo, ITI_Array a, ITI_int index, ITI_real value) {
	ITI_int size = GetNumArrayValues(a);
	if (index < size){
		if (a.memType == REAL_TYPE)
			a.realValues[index] = value;
		else
			assertFunction(0,
				"SetRealInArray : value needs compatible array type", sInfo);
	}
	else
		assertFunction(0, "SetRealInArray : index is not valid", sInfo);
}

void SetIntInArray(ITI_SolverInfo* sInfo, ITI_Array a, ITI_int index, ITI_int value) {
	ITI_int size = GetNumArrayValues(a);
	if (index < size){
		if (a.memType == INT_TYPE)
			a.intValues[index] = value;
		else if (a.memType == REAL_TYPE)
			a.realValues[index] = (ITI_real)value;
		else
			assertFunction(0,
				"SetIntInArray : value needs compatible array type", sInfo);
	}
	else
		assertFunction(0, "SetIntInArray : index is not valid", sInfo);
}

void SetStrInArray(ITI_SolverInfo* sInfo, ITI_Array a, ITI_int index, ITI_char* value) {
	ITI_int size = GetNumArrayValues(a);
	if (index < size) {
		if (a.memType == STRING_TYPE)
			a.charValues[index] = value;
		else
			assertFunction(0,
				"SetStrInArray : value needs compatible array type", sInfo);
	}
	else
		assertFunction(0, "SetStrInArray : index is not valid", sInfo);
}


ITI_int ArrayCompare(ITI_SolverInfo* sInfo, ITI_Array a1, ITI_Array a2,
														enum  RelOp relOp)
{
	ITI_int res = 0;

	if (relOp!=RelOp_Eq && relOp!=RelOp_NotEq){
		assertFunction(!(relOp==RelOp_Greater),
			"ArrayCompare: Operator \">\" is not supported for arrays.", sInfo);
		assertFunction(!(relOp==RelOp_Less),
			"ArrayCompare: Operator \"<\" is not supported for arrays.", sInfo);
		assertFunction(!(relOp==RelOp_GreaterEq),
			"ArrayCompare: Operator \">=\" is not supported for arrays.", sInfo);
		assertFunction(!(relOp==RelOp_LessEq),
			"ArrayCompare: Operator \"<=\" is not supported for arrays.", sInfo);
		assertFunction(!(relOp==RelOp_Unknown),
			"ArrayCompare: Operator \"Unknown\" is not supported for arrays.", sInfo);
	}
	else {
		if (ArrayMatching(a1, a2)){
			ITI_int n = 0;
			ITI_int size = GetNumArrayValues(a1);
			res = 1;

			if (a1.memType == INT_TYPE && a2.memType == INT_TYPE){
				for (n = 0; n < size; n++){
					if (a1.intValues[n] != a2.intValues[n]){
						res = 0;
						break;
					}
				}
			}
			else if (a1.memType == STRING_TYPE || a2.memType == STRING_TYPE){
				 
			}
			else {
				if (a1.memType == INT_TYPE){
					for (n = 0; n < size; n++){
						if ((ITI_real)a1.intValues[n] != a2.realValues[n]){
							res = 0;
							break;
						}
					}
				}
				else if (a2.memType == INT_TYPE){
					for (n = 0; n < size; n++){
						if ((ITI_real)a2.intValues[n] != a1.realValues[n]){
							res = 0;
							break;
						}
					}
				}
				else {
					for (n = 0; n < size; n++){
						if (a2.realValues[n] != a1.realValues[n]){
							res = 0;
							break;
						}
					}
				}
			}
		}
	}
	if (relOp == RelOp_NotEq)
		res = !res;
	return res;
}

ITI_Array ArrayFromArrays(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem,
											ITI_int nArgs, ITI_Array a1, ...)
{
	va_list ap;
	ITI_Array res;
	ITI_Array arr;
	ITI_int i, j, a1Size;
	ITI_uint matching = 1;

	InitArray(&res);

	res.memType = a1.memType;
	res.nDims = a1.nDims+1;
	res.dims = GetIntMemory(currMem, res.nDims);
	res.dims[0] = nArgs;
	for (i = 1; i < res.nDims; i++){
		res.dims[i] = a1.dims[i-1];
	}
	a1Size = GetNumArrayValues(a1);
	switch (res.memType){
		case INT_TYPE :
			res.intValues = GetIntMemory(currMem, a1Size*nArgs);
			break;
		default :
			res.realValues = GetRealMemory(currMem, a1Size*nArgs);
			break;
	}
	va_start(ap, a1);
	arr = a1;
	for (i = 0; i < nArgs; i++){
		if (i > 0){
			arr = va_arg(ap, ITI_Array);
			matching = (ArrayMatching(a1, arr)&&a1.memType==arr.memType);
			assertFunction(matching,
				"ArrayFromArrays: Arrays needs matching arguments (size, type)", sInfo);
		}
		if (matching){
			switch (res.memType){
				case INT_TYPE :
					for (j = 0; j < a1Size; j++){
						res.intValues[i*a1Size+j] = arr.intValues[j];
					}
					break;
				default :
					for (j = 0; j < a1Size; j++){
						res.realValues[i*a1Size+j] = arr.realValues[j];
					}
					break;
			}
		}
	}
	va_end(ap);
	return res;
}

ITI_Array ApplyFuncOnArray(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem,
											ITI_Array a, enum FuncIdent fi)
{
	ITI_Array res;
	ITI_Array temp_a;
	ITI_int size;
	ITI_int i;

	temp_a = a;

	InitArray(&res);

	switch (fi){
		case FI_sin :
		case FI_cos :
		case FI_tan :
		case FI_asin :
		case FI_acos :
		case FI_atan :
		case FI_sinh :
		case FI_cosh :
		case FI_tanh :
		case FI_exp :
		case FI_log :
		case FI_log10 :
		case FI_sqrt :
		case FI_ceil :
			if (a.memType == INT_TYPE)
				temp_a.memType = REAL_TYPE;
			break;
		case FI_floor :
			temp_a.memType = INT_TYPE;
			break;
		default:
			break;
	}

	res = CreateArray(currMem, temp_a);
	size = GetNumArrayValues(a);

	switch (fi){
		case FI_fabs :
			if (a.memType == REAL_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = fabs(a.realValues[i]);
				}
			}
			else
				assertFunction(0,
					"ApplyScalarFuncOnArray: fabs() needs real values.", sInfo);
			break;
		case FI_abs :
			if (a.memType == INT_TYPE){
				for (i = 0; i < size; i++){
					res.intValues[i] = abs(a.intValues[i]);
				}
			}
			else
				assertFunction(0,
					"ApplyScalarFuncOnArray: abs() needs int values.", sInfo);
			break;
		case FI_sign :
			if (a.memType == REAL_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = sign(a.realValues[i]);
				}
			}
			else if (a.memType == INT_TYPE){
				for (i = 0; i < size; i++){
					res.intValues[i] = abs(a.intValues[i]);
				}
			}
			break;
		case FI_sin :
			if (a.memType == REAL_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = sin(a.realValues[i]);
				}
			}
			else if (a.memType == INT_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = sin(a.intValues[i]);
				}
			}
			break;
		case FI_cos :
			if (a.memType == REAL_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = cos(a.realValues[i]);
				}
			}
			else if (a.memType == INT_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = cos(a.intValues[i]);
				}
			}
			break;
		case FI_tan :
			if (a.memType == REAL_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = tan(a.realValues[i]);
				}
			}
			else if (a.memType == INT_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = tan(a.intValues[i]);
				}
			}
			break;
		case FI_asin :
			if (a.memType == REAL_TYPE){
				for (i = 0; i < size; i++){
					ITI_real v = a.realValues[i];
					if (v >= -1 && v <= 1)
						res.realValues[i] = asin(v);
					else
						assertFunction(0,
							"ApplyScalarFuncOnArray: asin(x) x is not valid (-1<=x<=1).", sInfo);
				}
			}
			else if (a.memType == INT_TYPE){
				for (i = 0; i < size; i++){
					ITI_int v = a.intValues[i];
					if (v >= -1 && v <= 1)
						res.realValues[i] = asin(v);
					else
						assertFunction(0,
							"ApplyScalarFuncOnArray: asin(x) x is not valid (-1<=x<=1).", sInfo);
				}
			}
			break;
		case FI_acos :
			if (a.memType == REAL_TYPE){
				for (i = 0; i < size; i++){
					ITI_real v = a.realValues[i];
					if (v >= -1 && v <= 1)
						res.realValues[i] = acos(v);
					else
						assertFunction(0,
							"ApplyScalarFuncOnArray: acos(x) x is not valid (-1<=x<=1).", sInfo);
				}
			}
			else if (a.memType == INT_TYPE){
				for (i = 0; i < size; i++){
					ITI_int v = a.intValues[i];
					if (v >= -1 && v <= 1)
						res.realValues[i] = acos(v);
					else
						assertFunction(0,
							"ApplyScalarFuncOnArray: acos(x) x is not valid (-1<=x<=1).", sInfo);
				}
			}
			break;
		case FI_atan :
			if (a.memType == REAL_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = atan(a.realValues[i]);
				}
			}
			else if (a.memType == INT_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = atan(a.intValues[i]);
				}
			}
			break;
		case FI_sinh :
			if (a.memType == REAL_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = sinh(a.realValues[i]);
				}
			}
			else if (a.memType == INT_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = sinh(a.intValues[i]);
				}
			}
			break;
		case FI_cosh :
			if (a.memType == REAL_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = cosh(a.realValues[i]);
				}
			}
			else if (a.memType == INT_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = cosh(a.intValues[i]);
				}
			}
			break;
		case FI_tanh :
			if (a.memType == REAL_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = tanh(a.realValues[i]);
				}
			}
			else if (a.memType == INT_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = tanh(a.intValues[i]);
				}
			}
			break;
		case FI_exp :
			if (a.memType == REAL_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = ITI_exp(a.realValues[i]);
				}
			}
			else if (a.memType == INT_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] =ITI_exp(a.intValues[i]);
				}
			}
			break;
		case FI_log :
			if (a.memType == REAL_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = log(a.realValues[i]);
				}
			}
			else if (a.memType == INT_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = log(a.intValues[i]);
				}
			}
			break;
		case FI_log10 :
			if (a.memType == REAL_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = log10(a.realValues[i]);
				}
			}
			else if (a.memType == INT_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = log10(a.intValues[i]);
				}
			}
			break;
		case FI_sqrt :
			if (a.memType == REAL_TYPE){
				for (i = 0; i < size; i++){
					ITI_real v = a.realValues[i];
					if (v >= 0)
						res.realValues[i] = sqrt(v);
					else
						assertFunction(0,
							"ApplyScalarFuncOnArray: sqrt(x) x is not valid (x>=0).", sInfo);
				}
			}
			else if (a.memType == INT_TYPE){
				for (i = 0; i < size; i++){
					ITI_int v = a.intValues[i];
					if (v >= 0)
						res.realValues[i] = sqrt(v);
					else
						assertFunction(0,
							"ApplyScalarFuncOnArray: sqrt(x) x is not valid (x>=0).", sInfo);
				}
			}
			break;
		case FI_floor :
			if (a.memType == REAL_TYPE){
				for (i = 0; i < size; i++){
					res.intValues[i] = (ITI_int)floor(a.realValues[i]);
				}
			}
			else if (a.memType == INT_TYPE){
				for (i = 0; i < size; i++){
					res.intValues[i] = (ITI_int)floor(a.intValues[i]);
				}
			}
			break;
		case FI_ceil :
			if (a.memType == REAL_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = ceil(a.realValues[i]);
				}
			}
			else if (a.memType == INT_TYPE){
				for (i = 0; i < size; i++){
					res.realValues[i] = ceil(a.intValues[i]);
				}
			}
			break;
	}
	return res;
}

ITI_Array CopyToRealArray(ITI_MemoryObject* currMem, ITI_real** values,
													ITI_int nDims, ...)
{
	va_list ap;
	ITI_Array res;
	ITI_int i = 0;
	ITI_int nValues = 0;

	InitArray(&res);

	va_start(ap, nDims);
	res = CreateRealArrayWithDims(currMem, nDims, ap);

	nValues = GetNumArrayValues(res);
	res.realValues = GetRealMemory(currMem, nValues);
	for (i = 0; i < nValues; i++){
		res.realValues[i] = *(values[i]);
	}
	va_end(ap);
	return res;
}

ITI_Array CopyToIntArray(ITI_MemoryObject* currMem, ITI_int** values,
													ITI_int nDims, ...)
{
	va_list ap;
	ITI_Array res;
	ITI_int i = 0;
	ITI_int nValues = 0;

	InitArray(&res);

	va_start(ap, nDims);
	res = CreateIntArrayWithDims(currMem, nDims, ap);

	nValues = GetNumArrayValues(res);
	res.intValues = GetIntMemory(currMem, nValues);
	for (i = 0; i < nValues; i++){
		res.intValues[i] = *(values[i]);
	}
	va_end(ap);
	return res;
}

ITI_int GetMatrixStr(ITI_Array arr, ITI_int index, ITI_int nRows, ITI_int nCols,
						ITI_char* ret, const ITI_ushort MAX_MEM, ITI_int sum)
{
	ITI_int row, col;
	ITI_char str[100];

	if (strlen(ret)==0)
		strcpy(ret, "\n[");
	else
		strcat(ret, "[");

	for (row = 0; row < nRows; row++){
		for (col = 0; col < nCols; col++){
			if (arr.memType == INT_TYPE)
				sprintf(str, "%i", arr.intValues[index]);
			else
				sprintf(str, "%.17g", arr.realValues[index]);
			if (col+1 == nCols && row+1 < nRows)
				strcat(str, ";\n");
			else if (col+1 < nCols)
				strcat(str, ",");

			sum += (ITI_int)strlen(str);
			if (sum >= MAX_MEM)
				return sum;

			strcat(ret, str);
			index++;
		}
	}
	strcat(ret, "]\n");
	return sum;
}

ITI_char* ArrayToString(ITI_SolverInfo* sInfo, ITI_MemoryObject* currMem,
															ITI_Array arr)
{
	ITI_char* ret;
	ITI_int sum = 0;
	ITI_int nRows = 1;
	ITI_int nCols = 0;
	ITI_int nDims = arr.nDims;
	int extraDims = nDims - 2;
	const ITI_ushort MAX_MEM = 1024;

	if (nDims == 1){
		nCols = arr.dims[0];
	}
	else if (nDims > 1){
		nRows = arr.dims[nDims-2];
		nCols = arr.dims[nDims-1];
	}

	ret = GetStringMemory(currMem, MAX_MEM);

	if (arr.memType == INT_TYPE){
		if (arr.intValues==0){
			strcpy(ret, "Error: arr.intValues is NULL");
			return ret;
		}
	}
	else if (arr.memType == REAL_TYPE){
		if (arr.realValues==0){
			strcpy(ret, "Error: arr.realValues is NULL");
			return ret;
		}
	}

	if (extraDims <= 0){
		sum += GetMatrixStr(arr, 0, nRows, nCols, ret, MAX_MEM, sum);
	}
	else {
		ITI_int n, d, i;
		ITI_int index = 0;
		ITI_int extraDimSize = 1;
		ITI_int* dimIndizes = (ITI_int*)calloc(extraDims, sizeof(ITI_int));
		for (n = 0; n < extraDims; n++){
			dimIndizes[n] = 0;
		}
		for (d = 0; d < extraDims; d++){
			extraDimSize *= arr.dims[d];
		}
		for (i = 0; i < extraDimSize; i++){
			sum += GetMatrixStr(arr, index, nRows, nCols, ret, MAX_MEM, sum);
			index = index  + (nRows*nCols);
		}
		free(dimIndizes);
	}
	return ret;
}

ITI_char* GetArrayStr(ITI_Array arr, ITI_TraceData* traceData, ITI_MemoryObject* currMem)
{
	ITI_int i = 0;
	ITI_char str[100];
	ITI_ushort sum = 0;
	const ITI_ushort MAX_MEM = 1024;
	ITI_int nValues = GetNumArrayValues(arr);

	traceData->temp = GetStringMemory(currMem, MAX_MEM);

	if (arr.memType == INT_TYPE){
		if (arr.intValues==0){
			strcpy(traceData->temp, "NULL");
		}
		else {
			for (i = 0; i < nValues; i++){
				if (i+1 < nValues)
					sprintf(str, "%i,", arr.intValues[i]);
				else
					sprintf(str, "%i", arr.intValues[i]);

				sum += (ITI_ushort)strlen(str);
				if (sum >= MAX_MEM)
					return traceData->temp;

				if (i == 0)
					strcpy(traceData->temp, str);
				else
					strcat(traceData->temp, str);
			}
		}
	}
	else if (arr.memType == REAL_TYPE){
		if (arr.realValues==0){
			strcpy(traceData->temp, "NULL");
		}
		else {
			for (i = 0; i < nValues; i++){
				if (i+1 < nValues)
					sprintf(str, "%.17g,", arr.realValues[i]);
				else
					sprintf(str, "%.17g", arr.realValues[i]);

				sum += (ITI_ushort)strlen(str);
				if (sum >= MAX_MEM)
					return traceData->temp;

				if (i == 0)
					strcpy(traceData->temp, str);
				else
					strcat(traceData->temp, str);
			}
		}
	}
	return traceData->temp;
}

ITI_char* GetIntArrayStr(ITI_int* arr, ITI_int dim, ITI_TraceData* traceData, ITI_MemoryObject* currMem)
{
	ITI_int i = 0;
	ITI_char str[100];
	ITI_ushort sum = 0;
	const ITI_ushort MAX_MEM = 1024;

	traceData->temp = GetStringMemory(currMem, MAX_MEM);

	for (i = 0; i < dim; i++){
		if (i+1 < dim)
			sprintf(str, "%i,", arr[i]);
		else
			sprintf(str, "%i", arr[i]);

		sum += (ITI_ushort)strlen(str);
		if (sum >= MAX_MEM)
			return traceData->temp;

		if (i == 0)
			strcpy(traceData->temp, str);
		else
			strcat(traceData->temp, str);
	}
	return traceData->temp;
}

ITI_char* GetRealArrayStr(ITI_real* arr, ITI_int dim, ITI_TraceData* traceData, ITI_MemoryObject* currMem)
{
	ITI_int i = 0;
	ITI_char str[100];
	ITI_ushort sum = 0;
	const ITI_ushort MAX_MEM = 1024;

	traceData->temp = GetStringMemory(currMem, MAX_MEM);

	for (i = 0; i < dim; i++){
		if (i+1 < dim)
			sprintf(str, "%.17g,", arr[i]);
		else
			sprintf(str, "%.17g", arr[i]);

		sum += (ITI_ushort)strlen(str);
		if (sum >= MAX_MEM)
			return traceData->temp;

		if (i == 0)
			strcpy(traceData->temp, str);
		else
			strcat(traceData->temp, str);
	}
	return traceData->temp;
}

ITI_int GetRealIndex(ITI_real* vars, ITI_int nVars, ITI_real* var)
{
	ITI_int i = 0;
	for (i = 0; i < nVars; i++){
		if (&vars[i] == var)
			return i;
	}
	return -1;
}
