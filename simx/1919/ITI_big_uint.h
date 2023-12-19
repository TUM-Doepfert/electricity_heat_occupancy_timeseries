/**
 * ITI_big_uint.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#if !defined(ITI_BIG_UINT_H)
#define ITI_BIG_UINT_H

#include "ITI_crt.h"

ITI_FUNCTIONS_API void ITI_bi_setMax(ITI_bi* v1);
ITI_FUNCTIONS_API void ITI_bi_reset(ITI_bi* v1);
ITI_FUNCTIONS_API void ITI_bi_setreal(ITI_bi* v1, ITI_real v2, ITI_real res);
ITI_FUNCTIONS_API ITI_real ITI_bi_getreal(ITI_bi* v1, ITI_real res);
ITI_FUNCTIONS_API void ITI_bi_plus(ITI_bi* v1, ITI_bui* v2);
ITI_FUNCTIONS_API void ITI_bi_minus(ITI_bi* v1, ITI_bui* v2);
ITI_FUNCTIONS_API void ITI_bi_overflow(ITI_bi* v1, ITI_uint iPlace);
ITI_FUNCTIONS_API void ITI_bi_underflow(ITI_bi* v1, ITI_uint iPlace);
ITI_FUNCTIONS_API ITI_int ITI_bi_gt(ITI_bi* v1, ITI_bi* v2);

ITI_FUNCTIONS_API void ITI_bi_setui(ITI_bi* v1, ITI_bui* v2);
ITI_FUNCTIONS_API void ITI_bui_seti(ITI_bui* v1, ITI_bi* v2);

ITI_FUNCTIONS_API void ITI_bui_reset(ITI_bui* v1);
ITI_FUNCTIONS_API void ITI_bui_setMax(ITI_bui* v1);
ITI_FUNCTIONS_API ITI_real ITI_bui_getrealMax(ITI_real res);
ITI_FUNCTIONS_API void ITI_bui_plus(ITI_bui* v1, ITI_bui* v2);
ITI_FUNCTIONS_API void ITI_bui_plus_max(ITI_bui* v1, ITI_bui* v2);
ITI_FUNCTIONS_API void ITI_bui_minus(ITI_bui* v1, ITI_bui* v2);
ITI_FUNCTIONS_API void ITI_bui_div(ITI_bui* v1, ITI_real v2);
ITI_FUNCTIONS_API void ITI_bui_dec(ITI_bui* v1);
ITI_FUNCTIONS_API void ITI_bui_inc(ITI_bui* v1);

ITI_FUNCTIONS_API ITI_int ITI_bui_eq(ITI_bui* v1, ITI_bui* v2);
ITI_FUNCTIONS_API ITI_int ITI_bui_gt(ITI_bui* v1, ITI_bui* v2);
ITI_FUNCTIONS_API ITI_int ITI_bui_lt(ITI_bui* v1, ITI_bui* v2);

ITI_FUNCTIONS_API ITI_int ITI_bui_gt1(ITI_bui* v1);
ITI_FUNCTIONS_API ITI_int ITI_bui_is_zero(ITI_bui* v1);

ITI_FUNCTIONS_API void ITI_bui_setreal(ITI_bui* v1, ITI_real v2, ITI_real res);
ITI_FUNCTIONS_API ITI_real ITI_bui_getreal(ITI_bui* v1, ITI_real res);

ITI_FUNCTIONS_API void ITI_bui_overflow(ITI_bui* v1, ITI_uint iPlace);
ITI_FUNCTIONS_API void ITI_bui_underflow(ITI_bui* v1, ITI_uint iPlace);

#endif
