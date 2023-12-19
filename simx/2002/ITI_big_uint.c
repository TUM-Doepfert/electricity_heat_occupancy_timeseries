/**
 * ITI_big_uint.c
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#include "ITI_big_uint.h"
#include <math.h>

void ITI_bi_setMax(ITI_bi* v1)
{
	int i;
	ITI_bi_reset(v1);
	for(i=0; i<ITI_big_uint_size;i++)
		v1->v[i]--;
	v1->s=1;
}

void ITI_bi_reset(ITI_bi* v1)
{
	memset(v1->v, 0, sizeof v1->v);
	v1->s=1;
}

void ITI_bi_setreal(ITI_bi* v1, ITI_real v2, ITI_real res){
	ITI_real v;
	assert(res > 0.0);	 
	assert(DBL_EPSILON * ((ITI_real)(ITI_big_uint_max)+1.0) < 1.0);	 

	ITI_bi_reset(v1);
	if(v2>=0.0){
		v=v2;
	}
	else{
		v=-v2;
		v1->s=-1;
	}
	if((v == 0.0) || (v < res))
		return;
	else if(v == res)
	{
		v1->v[0] = 1u;
		return;
	}
	else
	{
		ITI_real q, quo, base, quo_round;
		ITI_uint imax = 0;
		ITI_int i, i1;
		assert((res >= 1.0) || ((res < 1.0) && (v <= res * DBL_MAX)));	 
		q = v/res;
		quo = q;
		while(quo >= ((ITI_real)(ITI_big_uint_max)+1.0)) {
			quo /= ((ITI_real)(ITI_big_uint_max)+1.0);
			++imax;
			assert(imax < ITI_big_uint_size);	 
		}
		quo = q;
		for(i=imax; i>=0; i--) {
			if(i==0) {
				quo_round = ceil(quo-0.5);
				if(quo_round <= (ITI_real)(ITI_big_uint_max))
					v1->v[0] = (ITI_big_uint)quo_round;
				else {
					ITI_bui one;
					ITI_bui_reset(& one);
					one.v[0] = 1;
					v1->v[0] = (ITI_big_uint)ITI_big_uint_max;
					ITI_bi_plus(v1, &one);
				}
			}
			else {
				base = 1.0;
				for(i1=0; i1<i; i1++)
					base *= ((ITI_real)(ITI_big_uint_max)+1.0);
				assert(quo / base < (ITI_real)(ITI_big_uint_max)+1.0);	 
				v1->v[i] = (ITI_big_uint)floor(quo / base);
				quo -= v1->v[i] * base;
			}
		}
	}
}

ITI_real ITI_bi_getreal(ITI_bi* v1, ITI_real res){
	ITI_uint i;
	ITI_real val =0.0;
	ITI_real base = res;
	ITI_ushort big = 0;

	assert(res >= 0.0);	 
	for(i=0; i<ITI_big_uint_size;i++)
	{
		 
		assert((big == 0) || (v1->v[i] == 0));
		assert(((base >= 1.0) && ((ITI_real)v1->v[i] <= (DBL_MAX - val) / base)) || ((base < 1.0) && (val + (ITI_real)v1->v[i] * base <= DBL_MAX)));
		val+=v1->v[i] * base;
		if(base <= DBL_MAX / ((ITI_real)(ITI_big_uint_max)+1.0))
			base *= ((ITI_real)(ITI_big_uint_max)+1.0);
		else
			big = 1;
	}
	if (v1->s>0)
		return val;
	else
		return -val;
}

void ITI_bi_plus(ITI_bi* v1, ITI_bui* v2)
{
	ITI_uint i;
	ITI_big_uint v;
	if(v1->s>0){  
		for(i=0; i<ITI_big_uint_size;i++){
			v = v1->v[i] + v2->v[i];
			if(v < v1->v[i]){
				assert(i+1 < ITI_big_uint_size);
				ITI_bi_overflow(v1, i+1);
			}
			v1->v[i] = v;
		}
	}
	else{
		ITI_bui v1ui;
		ITI_bui_seti(&v1ui, v1);
		if(ITI_bui_gt(&v1ui, v2)){  
			for(i=0; i<ITI_big_uint_size;i++){
				v = v1->v[i] - v2->v[i];
				if(v > v1->v[i]){
					assert(i+1 < ITI_big_uint_size);
					ITI_bi_underflow(v1, i+1);
				}
				v1->v[i] = v;
			}
		}
		else{  
			ITI_bui v2ui = *v2;
			for(i=0; i<ITI_big_uint_size;i++){
				v = v2ui.v[i] - v1ui.v[i];
				if(v > v2ui.v[i]){
					assert(i+1 < ITI_big_uint_size);
					ITI_bui_underflow(&v2ui, i+1);
				}
				v2ui.v[i] = v;
			}
			ITI_bi_setui(v1, &v2ui);
		}
	}
}

void ITI_bi_minus(ITI_bi* v1, ITI_bui* v2)
{
	ITI_uint i;
	ITI_big_uint v;
	ITI_bui v2ui = *v2;
	ITI_bui v1ui;
	ITI_bui_seti(&v1ui, v1);

	if(v1->s>0){
		if(ITI_bui_gt(&v1ui, v2)){  
			for(i=0; i<ITI_big_uint_size;i++){
				v = v1->v[i] - v2->v[i];
				if(v > v1->v[i]){
					assert(i+1 < ITI_big_uint_size);
					ITI_bi_underflow(v1, i+1);
				}
				v1->v[i] = v;
			}
		}
		else{  
			for(i=0; i<ITI_big_uint_size;i++){
				v = v2ui.v[i] - v1ui.v[i];
				if(v > v2ui.v[i]){
					assert(i+1 < ITI_big_uint_size);
					ITI_bui_underflow(&v2ui, i+1);
				}
				v2ui.v[i] = v;
			}
			ITI_bi_setui(v1, &v2ui);
			if(!ITI_bui_is_zero(&v2ui))
				v1->s=-1;
		}
	}
	else{  
		for(i=0; i<ITI_big_uint_size;i++){
			v = v1->v[i] + v2->v[i];
			if(v < v1->v[i]){
				assert(i+1 < ITI_big_uint_size);
				ITI_bi_overflow(v1, i+1);
			}
			v1->v[i] = v;
		}
	}
}


void ITI_bi_setui(ITI_bi* v1, ITI_bui* v2){
	ITI_uint i;
	for(i=0; i<ITI_big_uint_size;i++){
		v1->v[i] = v2->v[i];
	}
	v1->s=1;
}

void ITI_bui_seti(ITI_bui* v1, ITI_bi* v2){
	ITI_uint i;
	for(i=0; i<ITI_big_uint_size;i++){
		v1->v[i] = v2->v[i];
	}
}

void ITI_bi_overflow(ITI_bi* v1, ITI_uint iPlace)
{
	ITI_big_uint v=v1->v[iPlace];
	v1->v[iPlace]++;
	if(v1->v[iPlace]<v)
	{
		iPlace++;
		if(iPlace<ITI_big_uint_size)
		{
			ITI_bi_overflow(v1, iPlace);
		}
		else
		{
			 
			assert(0);
		}
	}
}

void ITI_bi_underflow(ITI_bi* v1, ITI_uint iPlace)
{
	ITI_big_uint v=v1->v[iPlace];
	v1->v[iPlace]--;
	if(v1->v[iPlace]>v)
	{
		iPlace++;
		if(iPlace<ITI_big_uint_size)
		{
			ITI_bi_underflow(v1, iPlace);
		}
		else
		{
			 
			assert(0);
		}
	}
}

ITI_FUNCTIONS_API ITI_int ITI_bi_gt(ITI_bi * v1, ITI_bi * v2)
{
	ITI_int i;
	if (v1->s > 0) {
		if (v2->s > 0) {
			for (i = ITI_big_uint_size - 1; i >= 0; i--)
			{
				if (v1->v[i] == v2->v[i])
					continue;
				if (v1->v[i] > v2->v[i])
					return 1;
				else
					return 0;
			}
			return 0;
		}
		else
			return 1;
	}
	else {
		if (v2->s > 0)
			return 0;
		else {
			for (i = ITI_big_uint_size - 1; i >= 0; i--)
			{
				if (v1->v[i] == v2->v[i])
					continue;
				if (v1->v[i] > v2->v[i])
					return 0;
				else
					return 1;
			}
			return 0;
		}
	}
}

void ITI_bui_setMax(ITI_bui* v1)
{
	int i;
	ITI_bui_reset(v1);
	for(i=0; i<ITI_big_uint_size;i++)
		v1->v[i]--;
}

void ITI_bui_reset(ITI_bui* v1)
{
	memset(v1->v, 0, sizeof v1->v);
}

ITI_real ITI_bui_getrealMax(ITI_real res)
{
	ITI_bui v;
	ITI_bui_setMax(&v);
	v.v[ITI_big_uint_size-1]--;
	return ITI_bui_getreal(&v, res);
}

void ITI_bui_plus(ITI_bui* v1, ITI_bui* v2)
{
	ITI_uint i;
	for(i=0; i<ITI_big_uint_size;i++)
	{
		ITI_big_uint v = v1->v[i] + v2->v[i];
		if(v < v1->v[i])
		{
			assert(i+1 < ITI_big_uint_size);	 
			ITI_bui_overflow(v1, i+1);
		}
		v1->v[i] = v;
	}
}

void ITI_bui_minus(ITI_bui* v1, ITI_bui* v2)
{
	ITI_uint i;
	for(i=0; i<ITI_big_uint_size;i++)
	{
		ITI_big_uint v = v1->v[i] - v2->v[i];
		if(v > v1->v[i])
		{
			assert(i+1 < ITI_big_uint_size);	 
			ITI_bui_underflow(v1, i+1);
		}
		v1->v[i] = v;
	}
}

void ITI_bui_plus_max(ITI_bui* v1, ITI_bui* v2)
{
	ITI_uint i;
	for(i=0; i<ITI_big_uint_size;i++)
	{
		ITI_big_uint v = v1->v[i] + v2->v[i];
		if(v < v1->v[i])
		{
			if(i+1 >= ITI_big_uint_size)
			{
				ITI_bui_setMax(v1);
				return;
			}
			else
				ITI_bui_overflow(v1, i+1);
		}
		v1->v[i] = v;
	}
}

void ITI_bui_div(ITI_bui* v1, ITI_real v2)
{
	ITI_real quo;

	assert(v2 > 0.0);	 
	quo = ITI_bui_getreal(v1, 1.0/v2);
	ITI_bui_setreal(v1, quo, 1.0);
}

void ITI_bui_dec(ITI_bui* v1)
{
	ITI_big_uint v = v1->v[0];

	v1->v[0]--;

	if(v < v1->v[0])
	{
		ITI_bui_underflow(v1, 1);
	}
}

void ITI_bui_inc(ITI_bui* v1)
{
	ITI_big_uint v = v1->v[0];

	v1->v[0]++;

	if(v > v1->v[0])
	{
		ITI_bui_overflow(v1, 1);
	}
}


ITI_int ITI_bui_gt(ITI_bui* v1, ITI_bui* v2)
{
	ITI_int i;
	for(i=ITI_big_uint_size-1; i>=0; i--)
	{
		if(v1->v[i] == v2->v[i])
			continue;
		if(v1->v[i] > v2->v[i])
			return 1;
		else
			return 0;
	}
	return 0;
}

ITI_int ITI_bui_lt(ITI_bui* v1, ITI_bui* v2)
{
	ITI_int i;
	for(i=ITI_big_uint_size-1; i>=0; i--)
	{
		if(v1->v[i] == v2->v[i])
			continue;
		if(v1->v[i] < v2->v[i])
			return 1;
		else
			return 0;
	}
	return 0;
}

ITI_int ITI_bui_eq(ITI_bui* v1, ITI_bui* v2)
{
	if(memcmp(v1->v, v2->v, sizeof(v1->v))== 0)
		return 1;
	else
		return 0;
}

ITI_int ITI_bui_is_zero(ITI_bui* v1)
{
	int i;
	for(i=0; i<ITI_big_uint_size;i++)
	{
		if(v1->v[i] != 0)
			return 0;
	}
	return 1;
}

ITI_int ITI_bui_gt1(ITI_bui* v1)
{
	if(v1->v[0] > 1)
	{
		return 1;
	}
	else
	{
		int i;
		for(i=1; i<ITI_big_uint_size;i++)
		{
			if(v1->v[i] > 0)
				return 1;
		}
		return 0;
	}
}

void ITI_bui_setreal(ITI_bui* v1, ITI_real v2, ITI_real res)
{
	assert(v2 >= 0.0);	 
	assert(res > 0.0);	 
	assert(DBL_EPSILON * ((ITI_real)(ITI_big_uint_max)+1.0) < 1.0);	 
	ITI_bui_reset(v1);
	if((v2 == 0.0) || (v2 < res))
		return;
	else if(v2 == res)
	{
		v1->v[0] = 1u;
		return;
	}
	else
	{
		ITI_real q, quo, base, quo_round;
		ITI_uint imax = 0;
		ITI_int i, i1;
		assert((res >= 1.0) || ((res < 1.0) && (v2 <= res * DBL_MAX)));	 
		q = v2/res;
		quo = q;
		while(quo >= ((ITI_real)(ITI_big_uint_max)+1.0)) {
			quo /= ((ITI_real)(ITI_big_uint_max)+1.0);
			++imax;
			assert(imax < ITI_big_uint_size);	 
		}
		quo = q;
		for(i=imax; i>=0; i--) {
			if(i==0) {
				quo_round = ceil(quo-0.5);
				if(quo_round <= (ITI_real)(ITI_big_uint_max))
					v1->v[0] = (ITI_big_uint)quo_round;
				else {
					ITI_bui one;
					ITI_bui_reset(& one);
					one.v[0] = 1;
					v1->v[0] = (ITI_big_uint)ITI_big_uint_max;
					ITI_bui_plus(v1, &one);
				}
			}
			else {
				base = 1.0;
				for(i1=0; i1<i; i1++)
					base *= ((ITI_real)(ITI_big_uint_max)+1.0);
				assert(quo / base < (ITI_real)(ITI_big_uint_max)+1.0);	 
				v1->v[i] = (ITI_big_uint)floor(quo / base);
				quo -= v1->v[i] * base;
			}
		}
	}
}

ITI_real ITI_bui_getreal(ITI_bui* v1, ITI_real res)
{
	ITI_uint i;
	ITI_real val =0.0;
	ITI_real base = res;
	ITI_ushort big = 0;

	assert(res >= 0.0);	 
	for(i=0; i<ITI_big_uint_size;i++)
	{
		 
		assert((big == 0) || (v1->v[i] == 0));
		assert(((base >= 1.0) && ((ITI_real)v1->v[i] <= (DBL_MAX - val) / base)) || ((base < 1.0) && (val + (ITI_real)v1->v[i] * base <= DBL_MAX)));
		val+=v1->v[i] * base;
		if(base <= DBL_MAX / ((ITI_real)(ITI_big_uint_max)+1.0))
			base *= ((ITI_real)(ITI_big_uint_max)+1.0);
		else
			big = 1;
	}
	return val;
}

void ITI_bui_overflow(ITI_bui* v1, ITI_uint iPlace)
{
	ITI_big_uint v=v1->v[iPlace];
	v1->v[iPlace]++;
	if(v1->v[iPlace]<v)
	{
		iPlace++;
		if(iPlace<ITI_big_uint_size)
		{
			ITI_bui_overflow(v1, iPlace);
		}
		else
		{
			 
			assert(0);
		}
	}
}

void ITI_bui_underflow(ITI_bui* v1, ITI_uint iPlace)
{
	ITI_big_uint v=v1->v[iPlace];
	v1->v[iPlace]--;
	if(v1->v[iPlace]>v)
	{
		iPlace++;
		if(iPlace<ITI_big_uint_size)
		{
			ITI_bui_underflow(v1, iPlace);
		}
		else
		{
			 
			assert(0);
		}
	}
}
