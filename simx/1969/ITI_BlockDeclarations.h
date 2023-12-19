/**
 * ITI_BlockDeclarations.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#ifndef ITI_BLOCKDECLARATIONS_H
#define ITI_BLOCKDECLARATIONS_H

#ifndef ITI_QUOTE1
#define ITI_QUOTE1(arg) #arg
#endif
#ifndef ITI_QUOTE
#define ITI_QUOTE(arg) ITI_QUOTE1(arg)
#endif

#if (defined(ITI_COMP_SIM) || defined(ITI_CE_EXEC_MODEL)) && !defined(_OPENMP)
#define START_PERF_T	StartPerformanceTiming(pPart->curr->performanceData, blockNr);
#define END_PERF_T		EndPerformanceTiming(pPart->curr->performanceData, blockNr);
#define INC_RES_CALLS	__ibd->resCalls++;
#define INC_JAC_CALLS	__ibd->jacCalls++;
#else
#define START_PERF_T
#define END_PERF_T
#define INC_RES_CALLS
#define INC_JAC_CALLS
#endif


#define __iti_assert(i, string, al, index)\
if((!(al) && !(i)) || (al)) AssertFunction(i, #i, string, &_sInfo, (enum AssertionLevel)(al), index, _t, ITI_QUOTE(ITI_projectName))


#define __RES(i) __ibd->res[i]
#define __S(i) __ibd->s[i]
#define __JAC(n,i,j) __ibd->jac[(n)*j+i]
#define __SJAC(n,i,j) __ibd->sjac[(n)*i+j]
#define __V(i) __ibd->v[i]
#define __MV(i) __ibd->mv[i]
#define __MVM(kDP, i) __ibd->mv[__iDPbd(kDP).M[i]]

#ifndef __ERROR_TRACE_FLUSH
#define __ERROR_TRACE_FLUSH
#endif

#define __BLOCKVAR(_blockNr, _varNr, _name, _considerMin, _minVal, _considerMax, _maxVal, _nomVal) \
	bd[_blockNr].name[_varNr] = _name;\
	bd[_blockNr].considerMin[_varNr] = _considerMin;\
	bd[_blockNr].minVal[_varNr] = _minVal;\
	bd[_blockNr].considerMax[_varNr] = _considerMax;\
	bd[_blockNr].maxVal[_varNr] = _maxVal;\
	bd[_blockNr].nomVal[_varNr] = _nomVal;

#define __VAR_MAPPING(kDP, nODE, nDAE)\
memset((void *) __ibd->sjac, 0, (nDAE-nODE)*nDAE*sizeof(ITI_real));\
{\
	ITI_uint i;\
	if(_sInfo.isFirstRhsCall)\
		for(i=nDAE;i<(nDAE+nODE);i++)\
		{\
			__ibd->v[i] = __ibd->v[__iDPbd(kDP).M[i]];\
		}\
	for(i=0; i<nDAE;i++)\
		__ibd->mv[i]=__ibd->v[__iDPbd(kDP).M[i]];\
}\

#define __DP_HAPPENED(kDP)\
if((__iDPbd(kDP).MC==1) || _sInfo.isFirstRhsCall)\
{\
	if(__iDPbd(kDP).MC==1)\
		__SOLVER_NEEDS_RESET\

#define __DP_END_HAPPENED(kDP)\
__iDPbd(kDP).MC=0;\
}\

#define __SET_V_DOT(kDP, iDAEState, VarName)\
__iDPbd(kDP).Vdot[iDAEState] = VarName;\

#define __SET_DUMMY_DOT(kDP, iODEState, nDAE, VarName)\
VarName = __iDPbd(kDP).Vdot[__iDPbd(kDP).M[nDAE+iODEState]];\

#define __BLOCK(number) \
{\
	ITI_uint blockNr = number;\
	START_PERF_T \
	__ibd->firstTime = 1;\
	__ibd->useNumJac = 0;

#define __END_BLOCK \
	END_PERF_T \
}

#define __NUM_JAC \
{\
	ITI_uint k = 0;\
	__ibd->iCol = -1;\
	__ibd->mode = 0;


#define __NO_NUM_JAC \
{\
	ITI_uint k = 0;\
	__ibd->iCol = -1;\
	__ibd->mode = 1;

#define __BLOCK_INITS \
memset((void *) __ibd->jac, 0, __ibd->nRes*__ibd->nDAE*sizeof(ITI_real));\
__ibd->repeat = 1;\
__ibd->strAnalysisTypeDetail = _sInfo.strAnalysisTypeDetail;\
__ibd->saveStartValues = 1; \
__ibd->error = 0; \
__ibd->corrStep = 0; \
__ibd->hybrid = 0;\
__ibd->alpha = 1.0;\
__ibd->zfSwitch = 0;\
if (__ibd->autoLinSolv < 0)\
	__ibd->autoLinSolv = 1;

#define __BEGIN_LINEAR_BLOCK \
__BLOCK_INITS \
__ibd->lambda = 1.0;\
__ibd->maxiter = 1;\
do\
{\
	if ((__ibd->mode == 2 || __ibd->mode == 3 || __ibd->mode == 6) && (_sInfo.iFailedEqu <= 0) && (__ibd->alpha == 1.0)) {\
		if (__ibd->zfSwitch != 1) {\
			__ibd->mode = 9;\
			__ibd->repeat = 0;\
		} else {\
			__ibd->mode = 1;\
			__ibd->zfSwitch = 0;\
		}\
	}

#define __BEGIN_NONLINEAR_BLOCK \
__BLOCK_INITS \
if (_sInfo.isInitial)\
	__ibd->lambda = 0.01;\
else\
	__ibd->lambda = 1.;\
__ibd->maxiter = 100;\
__ibd->undamped = 0;\
do\
{

#ifndef isfinite
#ifdef _MSC_VER
#define isfinite _finite
#elif defined(__gnu_linux__)
#define isfinite finite
#else
#define isfinite ITI_finite
#endif
#endif

#define __CALC_BLOCKDATA(i, VarName, __minVal, __maxVal) \
if (__ibd->firstTime == 1) {\
	if (_sInfo.isInitial)\
		if (!isfinite(VarName))\
			VarName = __ibd->nomVal[i];\
	if (__ibd->ignoreLimits == 0) {\
		if (__ibd->considerMin[i])\
			__ibd->minVal[i]=__minVal;\
		if (__ibd->considerMax[i])\
			__ibd->maxVal[i]=__maxVal;\
		}\
	__ibd->xsave[i] = VarName;\
}\
if(((__ibd->iCol == -1) && (__ibd->mode==0)) || (__ibd->mode==2) || (__ibd->mode==5))\
	__ibd->xorg[i] = VarName;\
if(__ibd->saveStartValues == 1)\
	__ibd->xstart[i] = VarName;\
if(__ibd->mode == 1) \
	__ibd->xjac[i] = VarName;\
__ibd->x[i] = VarName;\
__ibd->delta[i]=min(max(fabs(VarName) * sqrt(DBL_EPSILON), ITI_absTol), __MAX_PERT);\

#define __CHECK_LIMITS_DP(kDP, nODE, nDAE) \
if(__ibd->saveStartValues == 1) \
{\
	CheckLimits_DP(__ibd, &(__iDPbd(kDP)), nODE, nDAE, &_sInfo); \
	if(__ibd->error == 1) \
		return(1); \
}\

#if !defined(TRY)
#if !defined(ITI_SCALERT) && !defined(ITI_DSPACE) && !defined(ITI_NI_LV_CDSIM) && !defined(ITI_CE_ETAS_LABCAR)

#ifdef _MSC_VER

#define TRY __try {


#ifdef ITI_COMP_SIM

#define EXCEPT \
} __except (FPEfilter(GetExceptionCode(), &_sInfo)) {\
	if (__ibd->firstTime) {\
		RestoreMask(modelData->oldCW, modelData->oldHandler);\
		__ERROR_TRACE_FLUSH \
		return 1;\
	}\
	__ibd->error = 1;\
}

#else

#define EXCEPT \
} __except (FPEfilter(GetExceptionCode(), &_sInfo)) {\
	if (__ibd->firstTime) {\
		RestoreMask(modelData->oldCW, modelData->oldHandler);\
		__ERROR_TRACE_FLUSH \
		return 1;\
	}\
	__ibd->error = 1;\
}

#endif  

#elif !defined ITI_COMP_SIM  

#define TRY \
_sInfo.allowBlockJump = ITI_true;\
if (setjmp(_sInfo.blockEnv) == 0) {

#define EXCEPT \
} else {\
	if (__ibd->firstTime) {\
		RestoreMask(modelData->oldCW, modelData->oldHandler);\
		_sInfo.allowBlockJump = ITI_false;\
		_sInfo.allowJump = ITI_false;\
		return 1;\
	}\
	__ibd->error = 1;\
}

#else

#define TRY
#define EXCEPT

#endif  

#else

#define TRY
#define EXCEPT

#endif  
#endif  

#define __BEGIN_RES \
TRY \
__ibd->saveStartValues = 0;\
__ibd->error = 0;\
if((__ibd->mode != 1 && __ibd->mode != 6 && __ibd->mode != 19) || __ibd->useNumJac)\
{\
	INC_RES_CALLS

#define __BEGIN_JAC \
}\
if((__ibd->mode == 1 || __ibd->mode == 6 || __ibd->mode == 19) && !__ibd->useNumJac)\
{\
	INC_JAC_CALLS

#define __END_JAC \
}\
EXCEPT

#define __ON_FIRST_PASS_IN_EVENT \
if (__ibd->mode == 20) {\
	if (__ibd->nCol > 0)\
		__ibd->mode = 0;\
	else\
		__ibd->mode = 1;\
	__ibd->firstTime = 0;\
	continue;\
}

#define __SOLVE_EQUATION \
__END_JAC \
__ON_FIRST_PASS_IN_EVENT \
Solve(__ibd, &_sInfo);\
__ibd->firstTime = 0;

#define __SOLVE_EQUATION_DP(kDP) \
__END_JAC \
__ON_FIRST_PASS_IN_EVENT \
Solve_DP(__ibd, &(__iDPbd(kDP)), &_sInfo);\
__ibd->firstTime = 0;

#define __SOLVE_EQUATION_RECT \
__END_JAC \
__ON_FIRST_PASS_IN_EVENT \
SolveRect(__ibd, &_sInfo);\
__ibd->firstTime = 0;

#define __UPDATE_VAR(i, VarName) \
if (__ibd->error == 0) {\
	if ((__ibd->nCol > 0 || __ibd->useNumJac) && (__ibd->mode < 10))\
		VarName = __ibd->xorg[i];\
	switch (__ibd->mode) {\
	case 0:\
		VarName -= __S(i);\
		break;\
	case 13:\
		if(__ibd->nCol > 0 || __ibd->useNumJac) {\
			__ibd->iCol = -1;\
			__ibd->mode = 0;\
		} else \
			__ibd->mode = 1;\
	case 6:\
		if (__ibd->nCol > 0 || __ibd->useNumJac) {\
			__ibd->mode = 0;\
			__ibd->iCol = -1;\
		}\
		 \
	case 7:\
		VarName = __ibd->x[i] - __ibd->lambda * __ibd->alpha * __ibd->beta * __S(i);\
		break;\
	case 2:\
	case 3:\
		VarName -= __ibd->lambda * __ibd->alpha * __ibd->beta * __S(i);\
		break;\
	case 4:\
		VarName -= __ibd->alpha * __ibd->dxbar[i];\
		break;\
	case 5:\
		VarName = __ibd->xjac[i] - __ibd->lambda * __ibd->alpha * __S(i);\
		break;\
	case 8:\
		VarName = __ibd->xstart[i];\
		break;\
	}\
} else\
	VarName = __ibd->xstart[i];\

#define __END_NONLINEAR_BLOCK \
	if (__ibd->mode == 8) {\
		if (__ibd->nCol > 0 || __ibd->useNumJac) {\
			__ibd->iCol = -1;\
			__ibd->mode = 0;\
		} else \
			__ibd->mode = 1;\
	}\
	if (__ibd->zfSwitch == -1 && __ibd->mode == 15) {\
		__ibd->error = 0;\
		__ibd->repeat = 1;\
		if (__ibd->nCol > 0 || __ibd->useNumJac) {\
			__ibd->iCol = -1;\
			__ibd->mode = 0;\
		} else\
			__ibd->mode = 1;\
		__ibd->zfSwitch = 1;\
	}\
	if ((__ibd->zfSwitch == 1 || __ibd->undamped) && __ibd->mode == 2) {\
		if(__ibd->nCol > 0 || __ibd->useNumJac) {\
			__ibd->iCol = -1;\
			__ibd->mode = 0;\
		} else \
			__ibd->mode = 1;\
	}\
	if (__ibd->error == 1 && !__ibd->useNumJac) {\
		__ibd->useNumJac = 1;\
		__ibd->iCol = -1;\
		__ibd->mode = 0;\
		__ibd->lambda = 1.;\
		__ibd->repeat = 1;\
		__ibd->error = 0;\
	}\
}\
while(__ibd->repeat > 0);\
_sInfo.allowBlockJump = ITI_false;\
if(__ibd->error == 1){ \
	__ERROR_TRACE_FLUSH \
	return(1); \
} \
}

#define __END_LINEAR_BLOCK \
	if (__ibd->mode == 8) {\
		if (__ibd->nCol > 0 || __ibd->useNumJac) {\
			__ibd->iCol = -1;\
			__ibd->mode = 0;\
		} else \
			__ibd->mode = 1;\
	}\
	if (__ibd->zfSwitch == -1 && __ibd->mode == 15) {\
		__ibd->error = 0;\
		__ibd->repeat = 1;\
		if (__ibd->nCol > 0 || __ibd->useNumJac) {\
			__ibd->iCol = -1;\
			__ibd->mode = 0;\
		} else\
			__ibd->mode = 1;\
		__ibd->zfSwitch = 1;\
	}\
	if (__ibd->error == 1 && !__ibd->useNumJac) {\
		__ibd->useNumJac = 1;\
		__ibd->iCol = -1;\
		__ibd->mode = 0;\
		__ibd->lambda = 1.;\
		__ibd->repeat = 1;\
		__ibd->error = 0;\
	}\
}\
while(__ibd->repeat > 0);\
if(__ibd->error == 1){ \
	__ERROR_TRACE_FLUSH \
	return(1); \
}\
}

#define __IS_BLOCK_EVENT (_sInfo.isEvent) && (__ibd->zfSwitch == 1 || (__ibd->mode == 11) || (__ibd->mode == 12) || (__ibd->mode == 20))
#define __IF_IS_BLOCK_EVENT if(__IS_BLOCK_EVENT)

#define lambda_diff 0.001
#define lambda_eps 1e-12
#define k_max 13

#define __SAVE_DISCRETE_REAL(i, VarName) \
__ibd->zrealsave[i] = VarName;

#define __SAVE_DISCRETE_INT(i, VarName) \
__ibd->zintsave[i] = VarName;

#define __SAVE_DISCRETE_STR(i, VarName) \
__ibd->zstrsave[i] = VarName;

#define __BEGIN_HYBRID_NONLINEAR_BLOCK \
for(k=0; k<3*k_max; k++) {\
	ITI_real lambda1 = 1.0;\
	ITI_real lambda2 = 1.0;\
	ITI_ushort changed = 0;\
	if (_sInfo.isEvent && __ibd->firstTime) __ibd->mode = 20;\
	{

#define __BEGIN_HYBRID_LINEAR_BLOCK \
for(k=0; k<2*k_max; k++) {\
	ITI_real lambda1 = 1.0;\
	ITI_real lambda2 = 1.0;\
	ITI_ushort changed = 0;\
	if (_sInfo.isEvent && __ibd->firstTime) __ibd->mode = 20;\
	if(__ibd->mode == 10) {\
		k--;\
		__ibd->mode = 11;\
	}\
	{

#define __END_HYBRID_LINEAR_BLOCK \
if(__ibd->mode==12) {\
	if(__ibd->nCol > 0 || __ibd->useNumJac) {\
		__ibd->iCol = -1;\
		__ibd->mode = 0;\
	}\
	else {\
		__ibd->mode = 1;\
		(&_sInfo)->strAnalysisTypeDetail = __ibd->strAnalysisTypeDetail;\
	}\
}\
if(__ibd->mode == 11) {\
	if((lambda1 < 1 - lambda_diff) && (lambda2 < 1.0))\
		__ibd->mode = 12;\
	else {\
		if(changed == 0) break;\
		k++;\
		if(__ibd->nCol > 0 || __ibd->useNumJac) {\
			__ibd->iCol = -1;\
			__ibd->mode = 0;\
		}\
		else {\
			__ibd->mode = 1;\
			(&_sInfo)->strAnalysisTypeDetail = __ibd->strAnalysisTypeDetail;\
		}\
	}\
}\
}\
}

#define __USE_ZERO_FUNCTION(i, VarName) \
if((__ibd->mode==11) && (k>1)) {\
	ITI_real dblLam;\
	if(((__ibd->zfsave[i] < 0) && (VarName > 0)) || ((__ibd->zfsave[i] > 0) && (VarName < 0))) {\
		dblLam = __ibd->zfsave[i] / (__ibd->zfsave[i] - VarName);\
		if(dblLam < lambda1) {\
			if(dblLam < lambda1 - lambda_eps)\
				lambda2 = lambda1;\
			lambda1 = dblLam;\
		}\
		else if((dblLam < lambda2) && (dblLam > lambda1 + lambda_eps))\
			lambda2 = dblLam;\
	}\
}\
if (((__ibd->mode == 11) || (__ibd->mode == 12)) && (((__ibd->zfsave[i] <= 0) && (VarName > 0)) || ((__ibd->zfsave[i] >= 0) && (VarName < 0))))\
	changed = 1;\
if (__ibd->zfSwitch == 0 && __ibd->firstTime != 1) {\
	int signOld = __ibd->zfsave[i] < 0 ? -1 : (__ibd->zfsave[i] > 0 ? 1 : 0);\
	int signNew = VarName < 0 ? -1 : (VarName > 0 ? 1 : 0);\
	if (signOld != signNew)\
		__ibd->zfSwitch = -1;\
}\
if ((__ibd->mode == 11) || (__ibd->mode == 12) || __ibd->zfSwitch == 0)\
	__ibd->zfsave[i] = VarName;

#define __COMPARE_DISCRETE_REAL(i, VarName) \
if(((__ibd->mode == 11) || (__ibd->mode == 12)) && (__ibd->zrealsave[i] != VarName)) {\
	changed = 1;\
	__ibd->zrealsave[i] = VarName;\
}

#define __COMPARE_DISCRETE_INT(i, VarName) \
if(((__ibd->mode == 11) || (__ibd->mode == 12)) && (__ibd->zintsave[i] != VarName)) {\
	changed = 1;\
	__ibd->zintsave[i] = VarName;\
}

#define __COMPARE_DISCRETE_STR(i, VarName) \
if(((__ibd->mode == 11) || (__ibd->mode == 12)) && (strcmp(__ibd->zstrsave[i], VarName)==0)) {\
	changed = 1;\
	__ibd->zstrsave[i] = VarName;\
}

#define __UPDATE_HYBRID_VAR(i, VarName) \
__UPDATE_VAR(i, VarName)\
if (__ibd->error == 0)\
{\
	if (__ibd->mode == 11) {\
		if((lambda1 < 1 - lambda_diff) && (lambda2 < 1.0)) {\
			ITI_real lambda=min(lambda1+lambda_diff,(lambda1+lambda2)/2);\
			VarName = lambda * VarName + (1 - lambda) * __ibd->xsave[i];\
		}\
		else\
			__ibd->xsave[i] = VarName;\
	} else if (__ibd->mode == 12)\
		__ibd->xsave[i] = VarName;\
}

#define __END_HYBRID_NONLINEAR_BLOCK \
if(!_sInfo.isEvent) break;\
if(__ibd->mode==12) {\
	if(__ibd->nCol > 0 || __ibd->useNumJac) {\
		__ibd->iCol = -1;\
		__ibd->mode = 0;\
	}\
	else {\
		__ibd->mode = 1;\
		(&_sInfo)->strAnalysisTypeDetail = __ibd->strAnalysisTypeDetail;\
	}\
}\
if(__ibd->mode == 11) {\
	if((lambda1 < 1 - lambda_diff) && (lambda2 < 1.0))\
		__ibd->mode = 12;\
	else {\
		if(changed == 0) break;\
		k++;\
		if(__ibd->nCol > 0 || __ibd->useNumJac) {\
			__ibd->iCol = -1;\
			__ibd->mode = 0;\
		}\
		else {\
			__ibd->mode = 1;\
			(&_sInfo)->strAnalysisTypeDetail = __ibd->strAnalysisTypeDetail;\
		}\
	}\
}\
if(__ibd->mode == 10)\
	__ibd->mode = 11;\
}\
}

#define __RES_HOM(i,p)  (*((_sInfo.isEmbed < 2) ? (__ibd->res + (i)) : (__hom_res + (p))))
#define __JAC_HOM(n,i,j,q)  (*((_sInfo.isEmbed < 2) ? (__ibd->jac + ((n)*j+i)) : (__hom_jac + (q))))

#define __NUM_JAC_HOM \
{\
	ITI_uint k = 0;\
	if (_sInfo.isEmbed < 2) \
	{\
		__ibd->iCol = -1;\
		__ibd->mode = 0;\
	}\

#define __NO_NUM_JAC_HOM \
{\
	ITI_uint k = 0;\
	if (_sInfo.isEmbed < 2) \
	{\
		__ibd->iCol = -1;\
		__ibd->mode = 1;\
	}\

#define __BEGIN_LINEAR_BLOCK_HOM \
if(_sInfo.isEmbed < 2)\
{\
	__BLOCK_INITS \
	__ibd->lambda = 1.0;\
	__ibd->maxiter = 1;\
}\
else\
{\
	__ibd->repeat = 0;\
	__ibd->error = 0;\
	if (_sInfo.isEmbed==3)\
		__ibd->mode = 1;\
	else\
		__ibd->mode = 0;\
}\
do\
{\
	if ((__ibd->mode == 2 || __ibd->mode == 3 || __ibd->mode == 6) && (_sInfo.iFailedEqu <= 0) && (__ibd->alpha == 1.0)) {\
		__ibd->mode = 9;\
		__ibd->repeat = 0;\
	}

#define __BEGIN_NONLINEAR_BLOCK_HOM \
if(_sInfo.isEmbed < 2)\
{\
	__BLOCK_INITS \
	__ibd->lambda = 1.;\
	__ibd->maxiter = 100;\
	__ibd->undamped = 0;\
}\
else\
{\
	__ibd->repeat = 0;\
	__ibd->error = 0;\
	if (_sInfo.isEmbed==3)\
		__ibd->mode = 1;\
	else\
		__ibd->mode = 0;\
}\
do\
{\
	if ((__ibd->mode == 3 || __ibd->mode == 4) && (_sInfo.iFailedEqu <= 0) && (__ibd->alpha == 1.0)) {\
		__ibd->mode = 9;\
		__ibd->repeat = 0;\
	}

#define __CALC_BLOCKDATA_HOM(i, ind, VarName, __minVal, __maxVal) \
if(_sInfo.isEmbed==0)\
{\
	__CALC_BLOCKDATA(i, VarName, __minVal, __maxVal) \
}\
else if(_sInfo.isEmbed==1)\
{\
	__CALC_BLOCKDATA(i, VarName, __minVal, __maxVal) \
	__hmm->considerMin[ind]=__ibd->considerMin[i];\
	if (__hmm->considerMin[ind]) {\
		__hmm->minVal[ind]=__minVal;\
		__hmm->considerLimit=1;\
	}\
	__hmm->considerMax[ind]=__ibd->considerMax[i];\
	if (__hmm->considerMax[ind]) {\
		__hmm->maxVal[ind]=__maxVal;\
		__hmm->considerLimit=1;\
	}\
	__hmm->nomVal[ind]=__ibd->nomVal[i];\
	__hmm->name[ind]=__ibd->name[i];\
}\

#define __SOLVE_EQUATION_HOM \
__END_JAC \
if(_sInfo.isEmbed < 2)\
{\
	__ON_FIRST_PASS_IN_EVENT \
	Solve(__ibd, &_sInfo);\
	__ibd->firstTime = 0;

#define __SOLVE_EQUATION_RECT_HOM \
__END_JAC \
if(_sInfo.isEmbed < 2)\
{\
	__ON_FIRST_PASS_IN_EVENT \
	SolveRect(__ibd, &_sInfo);\
	__ibd->firstTime = 0;

#define __END_NONLINEAR_BLOCK_HOM \
}\
__END_NONLINEAR_BLOCK \

#define __END_LINEAR_BLOCK_HOM \
}\
__END_LINEAR_BLOCK \


#define __BEGIN_HYBRID_NONLINEAR_BLOCK_HOM \
__BEGIN_HYBRID_NONLINEAR_BLOCK \

#define __END_HYBRID_NONLINEAR_BLOCK_HOM \
if (_sInfo.isEmbed > 1) break;\
__END_HYBRID_NONLINEAR_BLOCK\


#define __BEGIN_HYBRID_LINEAR_BLOCK_HOM \
__BEGIN_HYBRID_LINEAR_BLOCK \

#define __END_HYBRID_LINEAR_BLOCK_HOM \
if (_sInfo.isEmbed > 1) break;\
__END_HYBRID_LINEAR_BLOCK\

#endif
