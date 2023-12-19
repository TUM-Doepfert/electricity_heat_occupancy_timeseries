
#if !defined(_ITI_CVODE_Helpers)
#define _ITI_CVODE_Helpers
#include "ITI_crt.h"
#include "ITI_Cvode_sparse.h"
typedef struct ITI_SortJac{ITI_int zb36402356f;ITI_int z034e6ffe57;ITI_int*
z3e9c56f364;ITI_int*zc6a08ae4ce;ITI_int*zd8a87c601d;ITI_int*zcf3f0bddab;ITI_int*
z61e64063a9;ITI_real*z4604308cab;ITI_real*zfcb927fa80;}ITI_SortJac;typedef 
struct ITI_CVData{ITI_SortJac*pSortJac;ITI_void*pData;ITI_int iJac;}ITI_CVData;
#define ZERO		 RCONST(0.0)
#define MIN_INC_MULT RCONST(1000.0)
#define ONE			 RCONST(1.0)
#define TWO          RCONST(2.0)
void BuildEffJac(ITI_SparseData*z78d65c20d2,ITI_SortJac*z3cc0d439ea,ITI_char*
z89a5c64780,ITI_int z600a6fd606,ITI_uint*zb36402356f);void z47fab46d62(
ITI_SparseData*z78d65c20d2,ITI_SortJac*z3cc0d439ea,ITI_char*z89a5c64780,ITI_int 
z600a6fd606,ITI_int*zb3014479f7);void z5e418a6660(ITI_SparseData*z78d65c20d2,
ITI_SortJac*z3cc0d439ea,ITI_int*zb3014479f7,ITI_int*z0ba4bcbb4e,ITI_int*
z5fc72ba8be);void z86611319ac(ITI_int*z0ba4bcbb4e,ITI_int*z589c61258e,ITI_int 
z600a6fd606);void z78d1334933(ITI_SortJac*z3cc0d439ea,ITI_int*z589c61258e,
ITI_int*z5fc72ba8be,ITI_int z600a6fd606);void z423e955797(ITI_SortJac*
z3cc0d439ea,ITI_int z600a6fd606);void FreeEffJacData(ITI_SortJac*z3cc0d439ea);
#endif

