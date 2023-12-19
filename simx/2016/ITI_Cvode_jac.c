/**
 * ITI_Cvode_jac.c
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/


#if defined(_WIN32)
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#endif
#include "ITI_crt.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <stdarg.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>
#include "ITI_Cvode_helpers.h"
#include "ITI_Cvode_base.h"
#include "ITI_Cvode_jac.h"
#ifdef _OPENMP
#include <omp.h>
#endif
#ifdef z792c571d03
char**zbd872a1da3;z9a88724fcf z97f07ce7f3;z9a88724fcf z20e42aaf2b;z9a88724fcf 
z5a5ffda126;double z108c4f8b41=(0xe49+4287-0x1f08);double zac37203452=
(0xc67+4453-0x1dcc);double zb274caa67f=(0x9c6+6218-0x2210);double zfbc16931b0=
(0x171f+723-0x19f2);
#endif
#define z5227064b5e         (z8f1755e318->cv_f)
#define z119f1bd5f7    (z8f1755e318->cv_f_data)
#define z864430a72f    (z8f1755e318->cv_uround)
#define z7edcc2416e        (z8f1755e318->cv_tn)
#define z02b1c4a3ea         (z8f1755e318->cv_h)
#define z8344334d43       (z8f1755e318->cv_ewt)
#define z078ac0b1a5      (z8f1755e318->cv_lmem)
#define z3960d6c10a       (z6ed11884bf->zd5e138db82)
#define z00a21f2f88      (z6ed11884bf->d_nfeD)
int CalcJac(long int z3278a41716,DenseMat zf4bfdcc441,realtype t,N_Vector y,
N_Vector z5912f211db,void*zdfc42fc222,N_Vector z4f637ff870,N_Vector z84df455267,
N_Vector z112f1e371d){realtype zdc91ee786b,z33126b9d36,zfcb927fa80,z4604308cab,
z350211736d;realtype*z6dda406080,*z312548ef45,*z37ae829af5;N_Vector z2de573310b,
z263158f19f;long int z26dbd73a5e;int retval;CVodeMem z8f1755e318=(CVodeMem)
zdfc42fc222;CVDenseMem z6ed11884bf=(CVDenseMem)z078ac0b1a5;ITI_CVodeContainer*
ze630766edd=(ITI_CVodeContainer*)z119f1bd5f7;ITI_SolverData*cvd=ze630766edd->cvd
;ITI_Partition*pPart=ze630766edd->pPart;pPart->curr->sInfo.
strAnalysisTypeDetail="\x6a\x61\x63\x6f\x62\x69\x61\x6e";pPart->curr->t=t;
z6dda406080=N_VGetArrayPointer(z84df455267);z2de573310b=z4f637ff870;z263158f19f=
z84df455267;z37ae829af5=N_VGetArrayPointer(z8344334d43);z312548ef45=
N_VGetArrayPointer(y);z350211736d=RSqrt(z864430a72f);zdc91ee786b=N_VWrmsNorm(
z5912f211db,z8344334d43);z33126b9d36=(zdc91ee786b!=ZERO)?(MIN_INC_MULT*ABS(
z02b1c4a3ea)*z864430a72f*z3278a41716*zdc91ee786b):ONE;
#ifdef _CALC_MESSAGES
fprintf(stdout,"\n" "\x4a\x61\x63\x3a" "\t" "\x25\x2e\x33\x32\x66",t);
#endif
for(z26dbd73a5e=(0xb47+4924-0x1e83);z26dbd73a5e<z3278a41716;z26dbd73a5e++){long 
int zce99d8264d;N_VSetArrayPointer(DENSE_COL(zf4bfdcc441,z26dbd73a5e),
z263158f19f);z4604308cab=z312548ef45[z26dbd73a5e];zfcb927fa80=MAX(z350211736d*
ABS(z4604308cab),z33126b9d36/z37ae829af5[z26dbd73a5e]);zfcb927fa80=MAX(
zfcb927fa80,z864430a72f);z312548ef45[z26dbd73a5e]+=zfcb927fa80;
#ifdef ITI_COMP_SIM
zfadc7b64e5(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#else
CopyVars(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#endif
retval=z5227064b5e(z7edcc2416e,y,z2de573310b,z119f1bd5f7);z00a21f2f88++;if(
retval!=(0x167+510-0x365)){z312548ef45[z26dbd73a5e]=z4604308cab;zfcb927fa80=-
zfcb927fa80;z312548ef45[z26dbd73a5e]+=zfcb927fa80;
#ifdef ITI_COMP_SIM
zfadc7b64e5(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#else
CopyVars(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#endif
retval=z5227064b5e(z7edcc2416e,y,z2de573310b,z119f1bd5f7);z00a21f2f88++;if(
retval!=(0xf4b+5628-0x2547)){N_VSetArrayPointer(z6dda406080,z84df455267);
#ifdef ITI_COMP_SIM
zfadc7b64e5(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#else
CopyVars(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#endif
pPart->curr->sInfo.strAnalysisTypeDetail=
"\x72\x65\x73\x69\x64\x75\x61\x6c\x73";return(retval);}}z312548ef45[z26dbd73a5e]
=z4604308cab;for(zce99d8264d=(0x629+3781-0x14ee);zce99d8264d<z3278a41716;
zce99d8264d++)NV_Ith_S(z263158f19f,zce99d8264d)=(NV_Ith_S(z2de573310b,
zce99d8264d)-NV_Ith_S(z5912f211db,zce99d8264d))/zfcb927fa80;DENSE_COL(
zf4bfdcc441,z26dbd73a5e)=N_VGetArrayPointer(z263158f19f);}N_VSetArrayPointer(
z6dda406080,z84df455267);
#ifdef ITI_COMP_SIM
zfadc7b64e5(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#else
CopyVars(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#endif
pPart->curr->sInfo.strAnalysisTypeDetail=
"\x72\x65\x73\x69\x64\x75\x61\x6c\x73";cvd->stat[pPart->pid].iJac++;return(
(0x595+1417-0xb1e));}int ITI_CalcEffJac(long int z3278a41716,DenseMat 
zf4bfdcc441,realtype t,N_Vector y,N_Vector z5912f211db,void*zdfc42fc222,N_Vector
 z4f637ff870,N_Vector z84df455267,N_Vector z112f1e371d){realtype zdc91ee786b,
z33126b9d36,z350211736d;realtype*z6dda406080,*z312548ef45,*z37ae829af5;N_Vector 
z2de573310b,z263158f19f;long int zce99d8264d,z26dbd73a5e,z812c65ff2f,z4bc2586276
;int retval;CVodeMem z8f1755e318=(CVodeMem)zdfc42fc222;CVDenseMem z6ed11884bf=(
CVDenseMem)z078ac0b1a5;ITI_CVodeContainer*ze630766edd=(ITI_CVodeContainer*)
z119f1bd5f7;ITI_SolverData*cvd=ze630766edd->cvd;ITI_Partition*pPart=ze630766edd
->pPart;ITI_CVodeContext*cvc=(ITI_CVodeContext*)cvd->sc[pPart->pid];ITI_SortJac*
z3cc0d439ea=cvc->pSortJac;pPart->curr->sInfo.strAnalysisTypeDetail=
"\x6a\x61\x63\x6f\x62\x69\x61\x6e";pPart->curr->t=t;z6dda406080=
N_VGetArrayPointer(z84df455267);z2de573310b=z4f637ff870;z263158f19f=z84df455267;
z37ae829af5=N_VGetArrayPointer(z8344334d43);z312548ef45=N_VGetArrayPointer(y);
z350211736d=RSqrt(z864430a72f);zdc91ee786b=N_VWrmsNorm(z5912f211db,z8344334d43);
z33126b9d36=(zdc91ee786b!=ZERO)?(MIN_INC_MULT*ABS(z02b1c4a3ea)*z864430a72f*
z3278a41716*zdc91ee786b):ONE;
#ifdef _CALC_MESSAGES
fprintf(stdout,"\n" "\x4a\x61\x63\x3a" "\t" "\x25\x2e\x33\x32\x66",t);
#endif
for(z812c65ff2f=(0x1621+3431-0x2388);z812c65ff2f<z3cc0d439ea->zb36402356f;
z812c65ff2f++){for(z26dbd73a5e=(0xf19+634-0x1193);z26dbd73a5e<z3cc0d439ea->
z3e9c56f364[z812c65ff2f];z26dbd73a5e++){z4bc2586276=z3cc0d439ea->zc6a08ae4ce[
z812c65ff2f*z3278a41716+z26dbd73a5e];z3cc0d439ea->z4604308cab[z4bc2586276]=
z312548ef45[z4bc2586276];z3cc0d439ea->zfcb927fa80[z4bc2586276]=MAX(z350211736d*
ABS(z3cc0d439ea->z4604308cab[z4bc2586276]),z33126b9d36/z37ae829af5[z4bc2586276])
;z3cc0d439ea->zfcb927fa80[z4bc2586276]=MAX(z3cc0d439ea->zfcb927fa80[z4bc2586276]
,z864430a72f);z312548ef45[z4bc2586276]+=z3cc0d439ea->zfcb927fa80[z4bc2586276];}
#ifdef ITI_COMP_SIM
zfadc7b64e5(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#else
CopyVars(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#endif
retval=z5227064b5e(z7edcc2416e,y,z2de573310b,z119f1bd5f7);z00a21f2f88++;if(
retval!=(0x315+7917-0x2202)){for(z26dbd73a5e=(0x1666+1025-0x1a67);z26dbd73a5e<
z3cc0d439ea->z3e9c56f364[z812c65ff2f];z26dbd73a5e++){z4bc2586276=z3cc0d439ea->
zc6a08ae4ce[z812c65ff2f*z3278a41716+z26dbd73a5e];z312548ef45[z4bc2586276]=
z3cc0d439ea->z4604308cab[z4bc2586276];z3cc0d439ea->zfcb927fa80[z4bc2586276]=MAX(
z350211736d*ABS(z3cc0d439ea->z4604308cab[z4bc2586276]),z33126b9d36/z37ae829af5[
z4bc2586276]);z3cc0d439ea->zfcb927fa80[z4bc2586276]=-MAX(z3cc0d439ea->
zfcb927fa80[z4bc2586276],z864430a72f);z312548ef45[z4bc2586276]+=z3cc0d439ea->
zfcb927fa80[z4bc2586276];}
#ifdef ITI_COMP_SIM
zfadc7b64e5(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#else
CopyVars(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#endif
retval=z5227064b5e(z7edcc2416e,y,z2de573310b,z119f1bd5f7);z00a21f2f88++;if(
retval!=(0x1a75+1987-0x2238)){N_VSetArrayPointer(z6dda406080,z84df455267);
#ifdef ITI_COMP_SIM
zfadc7b64e5(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#else
CopyVars(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#endif
pPart->curr->sInfo.strAnalysisTypeDetail=
"\x72\x65\x73\x69\x64\x75\x61\x6c\x73";return(retval);}}for(z26dbd73a5e=
(0xbc2+2600-0x15ea);z26dbd73a5e<z3cc0d439ea->z3e9c56f364[z812c65ff2f];
z26dbd73a5e++){z4bc2586276=z3cc0d439ea->zc6a08ae4ce[z812c65ff2f*z3278a41716+
z26dbd73a5e];N_VSetArrayPointer(DENSE_COL(zf4bfdcc441,z4bc2586276),z263158f19f);
N_VConst(ZERO,z263158f19f);for(zce99d8264d=(0x741+4626-0x1953);zce99d8264d<
z3cc0d439ea->z61e64063a9[z4bc2586276];zce99d8264d++)NV_Ith_S(z263158f19f,
z3cc0d439ea->zcf3f0bddab[z4bc2586276*z3278a41716+zce99d8264d])=(NV_Ith_S(
z2de573310b,z3cc0d439ea->zcf3f0bddab[z4bc2586276*z3278a41716+zce99d8264d])-
NV_Ith_S(z5912f211db,z3cc0d439ea->zcf3f0bddab[z4bc2586276*z3278a41716+
zce99d8264d]))/z3cc0d439ea->zfcb927fa80[z4bc2586276];DENSE_COL(zf4bfdcc441,
z4bc2586276)=N_VGetArrayPointer(z263158f19f);z312548ef45[z4bc2586276]=
z3cc0d439ea->z4604308cab[z4bc2586276];}}N_VSetArrayPointer(z6dda406080,
z84df455267);
#ifdef ITI_COMP_SIM
zfadc7b64e5(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#else
CopyVars(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#endif
pPart->curr->sInfo.strAnalysisTypeDetail=
"\x72\x65\x73\x69\x64\x75\x61\x6c\x73";cvd->stat[pPart->pid].iJac++;return(
(0xd34+1553-0x1345));}int ITI_CalcEffJacSparse(long int z3278a41716,realtype t,
N_Vector y,N_Vector z5912f211db,void*zdfc42fc222,N_Vector z4f637ff870,N_Vector 
z84df455267,N_Vector z112f1e371d){realtype zdc91ee786b,z33126b9d36,z350211736d;
realtype*z6dda406080,*z312548ef45,*z37ae829af5;N_Vector z2de573310b;long int 
zce99d8264d,z26dbd73a5e,z812c65ff2f,z4bc2586276;int retval;CVodeMem z8f1755e318=
(CVodeMem)zdfc42fc222;ITI_SparseData*z78d65c20d2=(ITI_SparseData*)z078ac0b1a5;
ITI_CVodeContainer*ze630766edd=(ITI_CVodeContainer*)z119f1bd5f7;ITI_SolverData*
cvd=ze630766edd->cvd;ITI_Partition*pPart=ze630766edd->pPart;ITI_CVodeContext*cvc
=(ITI_CVodeContext*)cvd->sc[pPart->pid];ITI_SortJac*z3cc0d439ea=cvc->pSortJac;
pPart->curr->sInfo.strAnalysisTypeDetail="\x6a\x61\x63\x6f\x62\x69\x61\x6e"
;pPart->curr->t=t;
#ifdef z792c571d03
zbd872a1da3=(char**)calloc(cvc->maxThreads,sizeof(char*));for(z812c65ff2f=
(0x28f+3548-0x106b);z812c65ff2f<cvc->maxThreads;z812c65ff2f++)zbd872a1da3[
z812c65ff2f]=(char*)calloc((0x1fcb+548-0x20f0),sizeof(char));zdd072bd41d(&
z97f07ce7f3);
#endif
z6dda406080=N_VGetArrayPointer(z84df455267);z2de573310b=z4f637ff870;z37ae829af5=
N_VGetArrayPointer(z8344334d43);z312548ef45=N_VGetArrayPointer(y);z350211736d=
RSqrt(z864430a72f);zdc91ee786b=N_VWrmsNorm(z5912f211db,z8344334d43);z33126b9d36=
(zdc91ee786b!=ZERO)?(MIN_INC_MULT*ABS(z02b1c4a3ea)*z864430a72f*z3278a41716*
zdc91ee786b):ONE;
#ifdef _CALC_MESSAGES
fprintf(stdout,"\n" "\x4a\x61\x63\x3a" "\t" "\x25\x2e\x33\x32\x66",t);
#endif
for(z812c65ff2f=(0x1dc+1959-0x983);z812c65ff2f<z3cc0d439ea->zb36402356f;
z812c65ff2f++){for(z26dbd73a5e=(0xfa+1870-0x848);z26dbd73a5e<z3cc0d439ea->
z3e9c56f364[z812c65ff2f];z26dbd73a5e++){z4bc2586276=z3cc0d439ea->zc6a08ae4ce[
z812c65ff2f*z3278a41716+z26dbd73a5e];z3cc0d439ea->z4604308cab[z4bc2586276]=
z312548ef45[z4bc2586276];z3cc0d439ea->zfcb927fa80[z4bc2586276]=MAX(z350211736d*
ABS(z3cc0d439ea->z4604308cab[z4bc2586276]),z33126b9d36/z37ae829af5[z4bc2586276])
;z3cc0d439ea->zfcb927fa80[z4bc2586276]=MAX(z3cc0d439ea->zfcb927fa80[z4bc2586276]
,z864430a72f);z312548ef45[z4bc2586276]+=z3cc0d439ea->zfcb927fa80[z4bc2586276];}
#ifdef ITI_COMP_SIM
zfadc7b64e5(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#else
CopyVars(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#endif
retval=z5227064b5e(z7edcc2416e,y,z2de573310b,z119f1bd5f7);z78d65c20d2->
z1b10328be9++;if(retval!=(0x156c+3790-0x243a)){for(z26dbd73a5e=
(0x399+5238-0x180f);z26dbd73a5e<z3cc0d439ea->z3e9c56f364[z812c65ff2f];
z26dbd73a5e++){z4bc2586276=z3cc0d439ea->zc6a08ae4ce[z812c65ff2f*z3278a41716+
z26dbd73a5e];z312548ef45[z4bc2586276]=z3cc0d439ea->z4604308cab[z4bc2586276];
z3cc0d439ea->zfcb927fa80[z4bc2586276]=MAX(z350211736d*ABS(z3cc0d439ea->
z4604308cab[z4bc2586276]),z33126b9d36/z37ae829af5[z4bc2586276]);z3cc0d439ea->
zfcb927fa80[z4bc2586276]=-MAX(z3cc0d439ea->zfcb927fa80[z4bc2586276],z864430a72f)
;z312548ef45[z4bc2586276]+=z3cc0d439ea->zfcb927fa80[z4bc2586276];}
#ifdef ITI_COMP_SIM
zfadc7b64e5(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#else
CopyVars(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#endif
retval=z5227064b5e(z7edcc2416e,y,z2de573310b,z119f1bd5f7);z78d65c20d2->
z1b10328be9++;if(retval!=(0x1636+3879-0x255d)){N_VSetArrayPointer(z6dda406080,
z84df455267);
#ifdef ITI_COMP_SIM
zfadc7b64e5(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#else
CopyVars(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#endif
pPart->curr->sInfo.strAnalysisTypeDetail=
"\x72\x65\x73\x69\x64\x75\x61\x6c\x73";return(retval);}}for(z26dbd73a5e=
(0x590+769-0x891);z26dbd73a5e<z3cc0d439ea->z3e9c56f364[z812c65ff2f];z26dbd73a5e
++){z4bc2586276=z3cc0d439ea->zc6a08ae4ce[z812c65ff2f*z3278a41716+z26dbd73a5e];
for(zce99d8264d=(0x96a+1189-0xe0f);zce99d8264d<z3cc0d439ea->z61e64063a9[
z4bc2586276];zce99d8264d++)z78d65c20d2->m_Sparse.z9e4098361d[z78d65c20d2->
z22a80c7c9a[zce99d8264d+z78d65c20d2->z6e19225a91[z4bc2586276]]]=(NV_Ith_S(
z2de573310b,z3cc0d439ea->zcf3f0bddab[z4bc2586276*z3278a41716+zce99d8264d])-
NV_Ith_S(z5912f211db,z3cc0d439ea->zcf3f0bddab[z4bc2586276*z3278a41716+
zce99d8264d]))/z3cc0d439ea->zfcb927fa80[z4bc2586276];z312548ef45[z4bc2586276]=
z3cc0d439ea->z4604308cab[z4bc2586276];}}
#ifdef z792c571d03
{double zc3072eb312;zdd072bd41d(&z20e42aaf2b);z97b9267d3a(&z5a5ffda126);
zc3072eb312=(double)(z20e42aaf2b.z0c40f5d56f-z97f07ce7f3.z0c40f5d56f)/(double)
z5a5ffda126.z0c40f5d56f;if(cvd->stat[pPart->pid].iJac==(0x7e3+496-0x9d3)){
#ifdef zdb0d3593aa
sprintf(zbd872a1da3[(0xe25+4324-0x1f09)],
"\x74\x53\x75\x6d\x3a\x20\x25\x66\x2c\x20\x74\x4d\x69\x6e\x20\x25\x66\x2c\x20\x74\x4d\x61\x78\x3a\x20\x25\x66\x2c\x20\x74\x41\x76\x72\x3a\x20\x25\x66"
,z108c4f8b41,zac37203452,zb274caa67f,zfbc16931b0);pPart->transient->sInfo.
z2b7d9e78b1((0x2ff+2979-0xea2),(0x23+8972-0x232e),zbd872a1da3[
(0xce5+5839-0x23b4)],"",(void*)&pPart->transient->sInfo);
#endif
z108c4f8b41=(0x1610+537-0x1829);zac37203452=zc3072eb312;zb274caa67f=zc3072eb312;
}else{z108c4f8b41+=zc3072eb312;if(zac37203452>zc3072eb312)zac37203452=
zc3072eb312;if(zb274caa67f<zc3072eb312)zb274caa67f=zc3072eb312;}zfbc16931b0=
z108c4f8b41/(cvd->stat[pPart->pid].iJac+(0xb97+3768-0x1a4e));
#ifndef zdb0d3593aa
sprintf(zbd872a1da3[(0xe0+8781-0x232d)],
"\x74\x4a\x61\x63\x3a\x20\x25\x66\x2c\x20\x74\x53\x75\x6d\x3a\x20\x25\x66\x2c\x20\x74\x4d\x69\x6e\x20\x25\x66\x2c\x20\x74\x4d\x61\x78\x3a\x20\x25\x66\x2c\x20\x74\x41\x76\x72\x3a\x20\x25\x66"
,zc3072eb312,z108c4f8b41,zac37203452,zb274caa67f,zfbc16931b0);pPart->transient->
sInfo.z2b7d9e78b1((0x9d1+6513-0x2342),(0x14c0+3139-0x2102),zbd872a1da3[
(0x1017+173-0x10c4)],"",(void*)&pPart->transient->sInfo);
#endif
for(z812c65ff2f=(0xdd1+1164-0x125d);z812c65ff2f<cvc->maxThreads;z812c65ff2f++)
free(zbd872a1da3[z812c65ff2f]);free(zbd872a1da3);}
#endif
N_VSetArrayPointer(z6dda406080,z84df455267);
#ifdef ITI_COMP_SIM
zfadc7b64e5(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#else
CopyVars(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#endif
pPart->curr->sInfo.strAnalysisTypeDetail=
"\x72\x65\x73\x69\x64\x75\x61\x6c\x73";cvd->stat[pPart->pid].iJac++;return(
(0x350+2446-0xcde));}
#ifdef _OPENMP
int CalcJacPar(long int z3278a41716,DenseMat zf4bfdcc441,realtype t,N_Vector y,
N_Vector z5912f211db,void*zdfc42fc222,N_Vector z4f637ff870,N_Vector z84df455267,
N_Vector z112f1e371d){realtype zdc91ee786b,z33126b9d36,z350211736d;realtype*
z312548ef45,*z37ae829af5;long int zcec140f672,zbc8cafba26;int retval=
(0x16dc+2573-0x20e9);size_t size=z3278a41716*sizeof(realtype);CVodeMem 
z8f1755e318=(CVodeMem)zdfc42fc222;CVDenseMem z6ed11884bf=(CVDenseMem)z078ac0b1a5
;ITI_CVodeContainer*ze630766edd=(ITI_CVodeContainer*)z119f1bd5f7;ITI_SolverData*
cvd=ze630766edd->cvd;ITI_Partition*pPart=ze630766edd->pPart;ITI_CVodeContext*cvc
=(ITI_CVodeContext*)cvd->sc[pPart->pid];ITI_ParallelData*zd6cbc80993=(
ITI_ParallelData*)cvc->parDat;
#ifdef z792c571d03
zbd872a1da3=(char**)calloc(cvc->maxThreads,sizeof(char*));for(zcec140f672=
(0x4b3+5414-0x19d9);zcec140f672<cvc->maxThreads;zcec140f672++)zbd872a1da3[
zcec140f672]=(char*)calloc((0x17af+2637-0x20fd),sizeof(char));zdd072bd41d(&
z97f07ce7f3);
#endif
#ifdef ITI_COMP_SIM
for(zcec140f672=pPart->curr->size.bxind_cdfirst;zcec140f672<pPart->curr->size.
ibx;zcec140f672++)zd6cbc80993->bx_tmp[zcec140f672]=*pPart->curr->bx[zcec140f672]
;
#endif
pPart->curr->sInfo.strAnalysisTypeDetail="\x6a\x61\x63\x6f\x62\x69\x61\x6e"
;pPart->curr->t=t;z37ae829af5=NV_DATA_S(z8344334d43);z312548ef45=NV_DATA_S(y);
z350211736d=RSqrt(z864430a72f);zdc91ee786b=N_VWrmsNorm(z5912f211db,z8344334d43);
z33126b9d36=(zdc91ee786b!=ZERO)?(MIN_INC_MULT*ABS(z02b1c4a3ea)*z864430a72f*
z3278a41716*zdc91ee786b):ONE;
#ifdef _CALC_MESSAGES
fprintf(stdout,"\n" "\x4a\x61\x63\x3a" "\t" "\x25\x2e\x33\x32\x66",t);
#endif
zbc8cafba26=z3278a41716/cvc->maxThreads+(0x1c69+1708-0x2314);
#pragma omp parallel for reduction (| : retval)
for(zcec140f672=(0xc80+2108-0x14bc);zcec140f672<cvc->maxThreads;zcec140f672++){
long int z6e6181a44d;realtype zfcb927fa80;realtype*zc6e4e964cb;ITI_SolverData*
z251953f24a;int z27c0327a06=omp_get_thread_num();
#ifdef _WIN32
SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_HIGHEST);
#endif
for(z6e6181a44d=(0x195d+923-0x1cf8);z6e6181a44d<zbc8cafba26;z6e6181a44d++){
ITI_CVodeContainer z5392b1d490;long zce99d8264d,z26dbd73a5e;z26dbd73a5e=
zcec140f672*zbc8cafba26+z6e6181a44d;if(z26dbd73a5e>=z3278a41716)break;
#if defined z792c571d03 && defined zc3a8ef1eb8
sprintf(zbd872a1da3[z27c0327a06],"\x53\x3a\x20\x25\x64\x20\x25\x64",z26dbd73a5e,
z27c0327a06);pPart->transient->sInfo.z2b7d9e78b1((0xeaa+2205-0x1747),
(0x1f02+1299-0x2414),zbd872a1da3[z27c0327a06],"",(void*)&pPart->transient->sInfo
);
#endif
z251953f24a=&zd6cbc80993->cvd_par[z27c0327a06];zc6e4e964cb=NV_DATA_S(zd6cbc80993
->y_par[z27c0327a06]);memcpy(zc6e4e964cb,z312548ef45,size);N_VSetArrayPointer(
DENSE_COL(zf4bfdcc441,z26dbd73a5e),zd6cbc80993->jthCol_par[z27c0327a06]);
zfcb927fa80=MAX(z350211736d*ABS(z312548ef45[z26dbd73a5e]),z33126b9d36/
z37ae829af5[z26dbd73a5e]);zfcb927fa80=MAX(zfcb927fa80,z864430a72f);zc6e4e964cb[
z26dbd73a5e]+=zfcb927fa80;CopySimData(z251953f24a,cvd);
#ifdef ITI_COMP_SIM
zfadc7b64e5(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#else
CopyVars(pPart->curr->bx_tmp,z251953f24a->partition->curr->bx,pPart->curr->size.
bxind_cdfirst,pPart->curr->size.ibx);
#endif
z5392b1d490.cvd=z251953f24a;z5392b1d490.pPart=z251953f24a->partition;retval=
z5227064b5e(t,zd6cbc80993->y_par[z27c0327a06],zd6cbc80993->ftemp_par[z27c0327a06
],&z5392b1d490);for(zce99d8264d=(0x1be5+1980-0x23a1);zce99d8264d<z3278a41716;
zce99d8264d++)NV_Ith_S(zd6cbc80993->jthCol_par[z27c0327a06],zce99d8264d)=(
NV_Ith_S(zd6cbc80993->ftemp_par[z27c0327a06],zce99d8264d)-NV_Ith_S(z5912f211db,
zce99d8264d))/zfcb927fa80;DENSE_COL(zf4bfdcc441,z26dbd73a5e)=N_VGetArrayPointer(
zd6cbc80993->jthCol_par[z27c0327a06]);
#if defined z792c571d03 && defined zc3a8ef1eb8
sprintf(zbd872a1da3[z27c0327a06],"\x45\x3a\x20\x25\x64\x20\x25\x64",z26dbd73a5e,
z27c0327a06);pPart->transient->sInfo.z2b7d9e78b1((0x723+6175-0x1f42),
(0xa42+1299-0xf54),zbd872a1da3[z27c0327a06],"",(void*)&pPart->transient->sInfo);
#endif
}}
#ifdef z792c571d03
{double zc3072eb312;zdd072bd41d(&z20e42aaf2b);z97b9267d3a(&z5a5ffda126);
zc3072eb312=(double)(z20e42aaf2b.z0c40f5d56f-z97f07ce7f3.z0c40f5d56f)/(double)
z5a5ffda126.z0c40f5d56f;if(cvd->stat[pPart->pid].iJac==(0x988+1735-0x104f)){
#ifdef zdb0d3593aa
sprintf(zbd872a1da3[(0x1154+2880-0x1c94)],
"\x74\x53\x75\x6d\x3a\x20\x25\x66\x2c\x20\x74\x4d\x69\x6e\x20\x25\x66\x2c\x20\x74\x4d\x61\x78\x3a\x20\x25\x66\x2c\x20\x74\x41\x76\x72\x3a\x20\x25\x66"
,z108c4f8b41,zac37203452,zb274caa67f,zfbc16931b0);pPart->transient->sInfo.
z2b7d9e78b1((0x23d+7765-0x2092),(0x591+6454-0x1ec6),zbd872a1da3[
(0x1b04+2594-0x2526)],"",(void*)&pPart->transient->sInfo);
#endif
z108c4f8b41=(0x13e3+2054-0x1be9);zac37203452=zc3072eb312;zb274caa67f=zc3072eb312
;}else{z108c4f8b41+=zc3072eb312;if(zac37203452>zc3072eb312)zac37203452=
zc3072eb312;if(zb274caa67f<zc3072eb312)zb274caa67f=zc3072eb312;}zfbc16931b0=
z108c4f8b41/(cvd->stat[pPart->pid].iJac+(0x401+1367-0x957));
#ifndef zdb0d3593aa
sprintf(zbd872a1da3[(0x182+6319-0x1a31)],
"\x74\x4a\x61\x63\x3a\x20\x25\x66\x2c\x20\x74\x53\x75\x6d\x3a\x20\x25\x66\x2c\x20\x74\x4d\x69\x6e\x20\x25\x66\x2c\x20\x74\x4d\x61\x78\x3a\x20\x25\x66\x2c\x20\x74\x41\x76\x72\x3a\x20\x25\x66"
,zc3072eb312,z108c4f8b41,zac37203452,zb274caa67f,zfbc16931b0);pPart->transient->
sInfo.z2b7d9e78b1((0x1694+3684-0x24f8),(0x12c3+1479-0x1889),zbd872a1da3[
(0x1c5c+2343-0x2583)],"",(void*)&pPart->transient->sInfo);
#endif
for(zcec140f672=(0x1904+3063-0x24fb);zcec140f672<cvc->maxThreads;zcec140f672++)
free(zbd872a1da3[zcec140f672]);free(zbd872a1da3);}
#endif
z00a21f2f88+=z3278a41716;cvd->stat[pPart->pid].iRhsCalls+=z3278a41716;
#ifdef ITI_COMP_SIM
zfadc7b64e5(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#else
CopyVars(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#endif
pPart->curr->sInfo.strAnalysisTypeDetail=
"\x72\x65\x73\x69\x64\x75\x61\x6c\x73";cvd->stat[pPart->pid].iJac++;if(retval!=
(0x538+1024-0x938)){for(zcec140f672=(0xec8+3923-0x1e1b);zcec140f672<cvc->
maxThreads;zcec140f672++)TransferWarnings(&zd6cbc80993->cvd_par[zcec140f672].
partition->curr->sInfo,&pPart->transient->sInfo);}return retval;}int 
ITI_CalcEffJacPar(long int z3278a41716,DenseMat zf4bfdcc441,realtype t,N_Vector 
y,N_Vector z5912f211db,void*zdfc42fc222,N_Vector z4f637ff870,N_Vector 
z84df455267,N_Vector z112f1e371d){realtype zdc91ee786b,z33126b9d36,z350211736d;
realtype*z312548ef45,*z37ae829af5;long int zcec140f672,zbc8cafba26;int retval=
(0x80f+2042-0x1009);size_t size=z3278a41716*sizeof(realtype);CVodeMem 
z8f1755e318=(CVodeMem)zdfc42fc222;CVDenseMem z6ed11884bf=(CVDenseMem)z078ac0b1a5
;ITI_CVodeContainer*ze630766edd=(ITI_CVodeContainer*)z119f1bd5f7;ITI_SolverData*
cvd=ze630766edd->cvd;ITI_Partition*pPart=ze630766edd->pPart;ITI_CVodeContext*cvc
=(ITI_CVodeContext*)cvd->sc[pPart->pid];ITI_SortJac*z3cc0d439ea=cvc->pSortJac;
ITI_ParallelData*zd6cbc80993=(ITI_ParallelData*)cvc->parDat;
#ifdef _WIN32
DWORD z24dc63527f=GetThreadPriority(GetCurrentThread());
#endif
#ifdef z792c571d03
zbd872a1da3=(char**)calloc(cvc->maxThreads,sizeof(char*));for(zcec140f672=
(0xc41+5038-0x1fef);zcec140f672<cvc->maxThreads;zcec140f672++)zbd872a1da3[
zcec140f672]=(char*)calloc((0x20b9+697-0x2273),sizeof(char));zdd072bd41d(&
z97f07ce7f3);
#endif
#ifdef ITI_COMP_SIM
for(zcec140f672=pPart->curr->size.bxind_cdfirst;zcec140f672<pPart->curr->size.
ibx;zcec140f672++)zd6cbc80993->bx_tmp[zcec140f672]=*pPart->curr->bx[zcec140f672]
;
#endif
pPart->curr->sInfo.strAnalysisTypeDetail="\x6a\x61\x63\x6f\x62\x69\x61\x6e"
;pPart->curr->t=t;z37ae829af5=N_VGetArrayPointer(z8344334d43);z312548ef45=
N_VGetArrayPointer(y);z350211736d=RSqrt(z864430a72f);zdc91ee786b=N_VWrmsNorm(
z5912f211db,z8344334d43);z33126b9d36=(zdc91ee786b!=ZERO)?(MIN_INC_MULT*ABS(
z02b1c4a3ea)*z864430a72f*z3278a41716*zdc91ee786b):ONE;
#ifdef _CALC_MESSAGES
fprintf(stdout,"\n" "\x4a\x61\x63\x3a" "\t" "\x25\x2e\x33\x32\x66",t);
#endif
zbc8cafba26=z3cc0d439ea->zb36402356f/cvc->maxThreads+(0x6b1+4266-0x175a);
#pragma omp parallel for reduction (| : retval)
for(zcec140f672=(0x717+7150-0x2305);zcec140f672<cvc->maxThreads;zcec140f672++){
long int z6e6181a44d;realtype*z2b31100a61;ITI_SolverData*z251953f24a;int 
z27c0327a06=omp_get_thread_num();
#ifdef _WIN32
SetThreadPriority(GetCurrentThread(),z24dc63527f);
#endif
for(z6e6181a44d=(0x7eb+1606-0xe31);z6e6181a44d<zbc8cafba26;z6e6181a44d++){
ITI_CVodeContainer z5392b1d490;long int zce99d8264d,z26dbd73a5e,z812c65ff2f,
z4bc2586276;z812c65ff2f=zcec140f672*zbc8cafba26+z6e6181a44d;if(z812c65ff2f>=
z3cc0d439ea->zb36402356f)break;
#if defined z792c571d03 && defined zc3a8ef1eb8
sprintf(zbd872a1da3[z27c0327a06],"\x53\x3a\x20\x25\x64\x20\x25\x64",z812c65ff2f,
z27c0327a06);pPart->transient->sInfo.z2b7d9e78b1((0xfd8+4397-0x2105),
(0x13ff+4014-0x23ac),zbd872a1da3[z27c0327a06],"",(void*)&pPart->transient->sInfo
);
#endif
z251953f24a=&zd6cbc80993->cvd_par[z27c0327a06];z2b31100a61=NV_DATA_S(zd6cbc80993
->y_par[z27c0327a06]);memcpy(z2b31100a61,z312548ef45,size);for(z26dbd73a5e=
(0x16bc+2217-0x1f65);z26dbd73a5e<z3cc0d439ea->z3e9c56f364[z812c65ff2f];
z26dbd73a5e++){z4bc2586276=z3cc0d439ea->zc6a08ae4ce[z812c65ff2f*z3278a41716+
z26dbd73a5e];z3cc0d439ea->zfcb927fa80[z4bc2586276]=MAX(z350211736d*ABS(
z312548ef45[z4bc2586276]),z33126b9d36/z37ae829af5[z4bc2586276]);z3cc0d439ea->
zfcb927fa80[z4bc2586276]=MAX(z3cc0d439ea->zfcb927fa80[z4bc2586276],z864430a72f);
z2b31100a61[z4bc2586276]+=z3cc0d439ea->zfcb927fa80[z4bc2586276];}CopySimData(
z251953f24a,cvd);
#ifdef ITI_COMP_SIM
zfadc7b64e5(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#else
CopyVars(pPart->curr->bx_tmp,z251953f24a->partition->curr->bx,pPart->curr->size.
bxind_cdfirst,pPart->curr->size.ibx);
#endif
z5392b1d490.cvd=z251953f24a;z5392b1d490.pPart=z251953f24a->partition;retval=
z5227064b5e(z7edcc2416e,zd6cbc80993->y_par[z27c0327a06],zd6cbc80993->ftemp_par[
z27c0327a06],&z5392b1d490);for(z26dbd73a5e=(0x461+841-0x7aa);z26dbd73a5e<
z3cc0d439ea->z3e9c56f364[z812c65ff2f];z26dbd73a5e++){z4bc2586276=z3cc0d439ea->
zc6a08ae4ce[z812c65ff2f*z3278a41716+z26dbd73a5e];N_VSetArrayPointer(DENSE_COL(
zf4bfdcc441,z4bc2586276),zd6cbc80993->jthCol_par[z27c0327a06]);N_VConst(ZERO,
zd6cbc80993->jthCol_par[z27c0327a06]);for(zce99d8264d=(0x18+7719-0x1e3f);
zce99d8264d<z3cc0d439ea->z61e64063a9[z4bc2586276];zce99d8264d++)NV_Ith_S(
zd6cbc80993->jthCol_par[z27c0327a06],z3cc0d439ea->zcf3f0bddab[z4bc2586276*
z3278a41716+zce99d8264d])=(NV_Ith_S(zd6cbc80993->ftemp_par[z27c0327a06],
z3cc0d439ea->zcf3f0bddab[z4bc2586276*z3278a41716+zce99d8264d])-NV_Ith_S(
z5912f211db,z3cc0d439ea->zcf3f0bddab[z4bc2586276*z3278a41716+zce99d8264d]))/
z3cc0d439ea->zfcb927fa80[z4bc2586276];DENSE_COL(zf4bfdcc441,z4bc2586276)=
N_VGetArrayPointer(zd6cbc80993->jthCol_par[z27c0327a06]);}
#if defined z792c571d03 && defined zc3a8ef1eb8
sprintf(zbd872a1da3[z27c0327a06],"\x45\x3a\x20\x25\x64\x20\x25\x64",z812c65ff2f,
z27c0327a06);pPart->transient->sInfo.z2b7d9e78b1((0x1e16+688-0x20c6),
(0x590+4181-0x15e4),zbd872a1da3[z27c0327a06],"",(void*)&pPart->transient->sInfo)
;
#endif
}}
#ifdef z792c571d03
{double zc3072eb312;zdd072bd41d(&z20e42aaf2b);z97b9267d3a(&z5a5ffda126);
zc3072eb312=(double)(z20e42aaf2b.z0c40f5d56f-z97f07ce7f3.z0c40f5d56f)/(double)
z5a5ffda126.z0c40f5d56f;if(cvd->stat[pPart->pid].iJac==(0x459+2085-0xc7e)){
#ifdef zdb0d3593aa
sprintf(zbd872a1da3[(0x18b4+1478-0x1e7a)],
"\x74\x53\x75\x6d\x3a\x20\x25\x66\x2c\x20\x74\x4d\x69\x6e\x20\x25\x66\x2c\x20\x74\x4d\x61\x78\x3a\x20\x25\x66\x2c\x20\x74\x41\x76\x72\x3a\x20\x25\x66"
,z108c4f8b41,zac37203452,zb274caa67f,zfbc16931b0);pPart->transient->sInfo.
z2b7d9e78b1((0xfa1+1501-0x157e),(0x2550+93-0x25ac),zbd872a1da3[
(0xbbb+4612-0x1dbf)],"",(void*)&pPart->transient->sInfo);
#endif
z108c4f8b41=(0x1a1+2065-0x9b2);zac37203452=zc3072eb312;zb274caa67f=zc3072eb312;}
else{z108c4f8b41+=zc3072eb312;if(zac37203452>zc3072eb312)zac37203452=zc3072eb312
;if(zb274caa67f<zc3072eb312)zb274caa67f=zc3072eb312;}zfbc16931b0=z108c4f8b41/(
cvd->stat[pPart->pid].iJac+(0x17f9+2592-0x2218));
#ifndef zdb0d3593aa
sprintf(zbd872a1da3[(0x38+1055-0x457)],
"\x74\x4a\x61\x63\x3a\x20\x25\x66\x2c\x20\x74\x53\x75\x6d\x3a\x20\x25\x66\x2c\x20\x74\x4d\x69\x6e\x20\x25\x66\x2c\x20\x74\x4d\x61\x78\x3a\x20\x25\x66\x2c\x20\x74\x41\x76\x72\x3a\x20\x25\x66"
,zc3072eb312,z108c4f8b41,zac37203452,zb274caa67f,zfbc16931b0);pPart->transient->
sInfo.z2b7d9e78b1((0x8eb+4083-0x18de),(0xafd+1269-0xff1),zbd872a1da3[
(0xe32+473-0x100b)],"",(void*)&pPart->transient->sInfo);
#endif
for(zcec140f672=(0x2d+2609-0xa5e);zcec140f672<cvc->maxThreads;zcec140f672++)free
(zbd872a1da3[zcec140f672]);free(zbd872a1da3);}
#endif
z00a21f2f88+=z3cc0d439ea->zb36402356f;cvd->stat[pPart->pid].iRhsCalls+=
z3cc0d439ea->zb36402356f;
#ifdef ITI_COMP_SIM
zfadc7b64e5(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#else
CopyVars(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#endif
pPart->curr->sInfo.strAnalysisTypeDetail=
"\x72\x65\x73\x69\x64\x75\x61\x6c\x73";cvd->stat[pPart->pid].iJac++;if(retval!=
(0x1389+68-0x13cd)){for(zcec140f672=(0x17c3+211-0x1896);zcec140f672<cvc->
maxThreads;zcec140f672++)TransferWarnings(&zd6cbc80993->cvd_par[zcec140f672].
partition->curr->sInfo,&pPart->transient->sInfo);}return retval;}int 
ITI_CalcEffJacSparsePar(long int z3278a41716,realtype t,N_Vector y,N_Vector 
z5912f211db,void*zdfc42fc222,N_Vector z4f637ff870,N_Vector z84df455267,N_Vector 
z112f1e371d){realtype zdc91ee786b,z33126b9d36,z350211736d;realtype*z312548ef45,*
z37ae829af5;long int zcec140f672,zbc8cafba26;int retval=(0xb2+6976-0x1bf2);
size_t size=z3278a41716*sizeof(realtype);CVodeMem z8f1755e318=(CVodeMem)
zdfc42fc222;ITI_SparseData*z78d65c20d2=(ITI_SparseData*)z078ac0b1a5;
ITI_CVodeContainer*ze630766edd=(ITI_CVodeContainer*)z119f1bd5f7;ITI_SolverData*
cvd=ze630766edd->cvd;ITI_Partition*pPart=ze630766edd->pPart;ITI_CVodeContext*cvc
=(ITI_CVodeContext*)cvd->sc[pPart->pid];ITI_SortJac*z3cc0d439ea=cvc->pSortJac;
ITI_ParallelData*zd6cbc80993=(ITI_ParallelData*)cvc->parDat;
#ifdef _WIN32
DWORD z24dc63527f=GetThreadPriority(GetCurrentThread());
#endif
#ifdef z792c571d03
zbd872a1da3=(char**)calloc(cvc->maxThreads,sizeof(char*));for(zcec140f672=
(0x16ad+2990-0x225b);zcec140f672<cvc->maxThreads;zcec140f672++)zbd872a1da3[
zcec140f672]=(char*)calloc((0xdc8+1779-0x13bc),sizeof(char));zdd072bd41d(&
z97f07ce7f3);
#endif
#ifdef ITI_COMP_SIM
for(zcec140f672=pPart->curr->size.bxind_cdfirst;zcec140f672<pPart->curr->size.
ibx;zcec140f672++)zd6cbc80993->bx_tmp[zcec140f672]=*pPart->curr->bx[zcec140f672]
;
#endif
pPart->curr->sInfo.strAnalysisTypeDetail="\x6a\x61\x63\x6f\x62\x69\x61\x6e"
;pPart->curr->t=t;z37ae829af5=N_VGetArrayPointer(z8344334d43);z312548ef45=
N_VGetArrayPointer(y);z350211736d=RSqrt(z864430a72f);zdc91ee786b=N_VWrmsNorm(
z5912f211db,z8344334d43);z33126b9d36=(zdc91ee786b!=ZERO)?(MIN_INC_MULT*ABS(
z02b1c4a3ea)*z864430a72f*z3278a41716*zdc91ee786b):ONE;
#ifdef _CALC_MESSAGES
fprintf(stdout,"\n" "\x4a\x61\x63\x3a" "\t" "\x25\x2e\x33\x32\x66",t);
#endif
zbc8cafba26=z3cc0d439ea->zb36402356f/cvc->maxThreads+(0x3d+5284-0x14e0);
#pragma omp parallel for reduction (| : retval)
for(zcec140f672=(0x10e6+422-0x128c);zcec140f672<cvc->maxThreads;zcec140f672++){
long int z6e6181a44d;realtype*z2b31100a61;ITI_SolverData*z251953f24a;int 
z27c0327a06=omp_get_thread_num();
#ifdef _WIN32
SetThreadPriority(GetCurrentThread(),z24dc63527f);
#endif
for(z6e6181a44d=(0x13f2+4095-0x23f1);z6e6181a44d<zbc8cafba26;z6e6181a44d++){
ITI_CVodeContainer z5392b1d490;long int zce99d8264d,z26dbd73a5e,z812c65ff2f,
z4bc2586276;z812c65ff2f=zcec140f672*zbc8cafba26+z6e6181a44d;if(z812c65ff2f>=
z3cc0d439ea->zb36402356f)break;
#if defined z792c571d03 && defined zc3a8ef1eb8
sprintf(zbd872a1da3[z27c0327a06],"\x53\x3a\x20\x25\x64\x20\x25\x64",z812c65ff2f,
z27c0327a06);pPart->transient->sInfo.z2b7d9e78b1((0x1840+502-0x1a36),
(0x810+3305-0x14f8),zbd872a1da3[z27c0327a06],"",(void*)&pPart->transient->sInfo)
;
#endif
z251953f24a=&zd6cbc80993->cvd_par[z27c0327a06];z2b31100a61=NV_DATA_S(zd6cbc80993
->y_par[z27c0327a06]);memcpy(z2b31100a61,z312548ef45,size);for(z26dbd73a5e=
(0xbd5+2029-0x13c2);z26dbd73a5e<z3cc0d439ea->z3e9c56f364[z812c65ff2f];
z26dbd73a5e++){z4bc2586276=z3cc0d439ea->zc6a08ae4ce[z812c65ff2f*z3278a41716+
z26dbd73a5e];z3cc0d439ea->zfcb927fa80[z4bc2586276]=MAX(z350211736d*ABS(
z312548ef45[z4bc2586276]),z33126b9d36/z37ae829af5[z4bc2586276]);z3cc0d439ea->
zfcb927fa80[z4bc2586276]=MAX(z3cc0d439ea->zfcb927fa80[z4bc2586276],z864430a72f);
z2b31100a61[z4bc2586276]+=z3cc0d439ea->zfcb927fa80[z4bc2586276];}CopySimData(
z251953f24a,cvd);
#ifdef ITI_COMP_SIM
zfadc7b64e5(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#else
CopyVars(pPart->curr->bx_tmp,z251953f24a->partition->curr->bx,pPart->curr->size.
bxind_cdfirst,pPart->curr->size.ibx);
#endif
z5392b1d490.cvd=z251953f24a;z5392b1d490.pPart=z251953f24a->partition;retval=
z5227064b5e(z7edcc2416e,zd6cbc80993->y_par[z27c0327a06],zd6cbc80993->ftemp_par[
z27c0327a06],&z5392b1d490);for(z26dbd73a5e=(0x6c+4834-0x134e);z26dbd73a5e<
z3cc0d439ea->z3e9c56f364[z812c65ff2f];z26dbd73a5e++){z4bc2586276=z3cc0d439ea->
zc6a08ae4ce[z812c65ff2f*z3278a41716+z26dbd73a5e];for(zce99d8264d=
(0xf29+3087-0x1b38);zce99d8264d<z3cc0d439ea->z61e64063a9[z4bc2586276];
zce99d8264d++)z78d65c20d2->m_Sparse.z9e4098361d[z78d65c20d2->z22a80c7c9a[
zce99d8264d+z78d65c20d2->z6e19225a91[z4bc2586276]]]=(NV_Ith_S(zd6cbc80993->
ftemp_par[z27c0327a06],z3cc0d439ea->zcf3f0bddab[z4bc2586276*z3278a41716+
zce99d8264d])-NV_Ith_S(z5912f211db,z3cc0d439ea->zcf3f0bddab[z4bc2586276*
z3278a41716+zce99d8264d]))/z3cc0d439ea->zfcb927fa80[z4bc2586276];}
#if defined z792c571d03 && defined zc3a8ef1eb8
sprintf(zbd872a1da3[z27c0327a06],"\x45\x3a\x20\x25\x64\x20\x25\x64",z812c65ff2f,
z27c0327a06);pPart->transient->sInfo.z2b7d9e78b1((0x7ad+373-0x922),
(0x13cc+4012-0x2377),zbd872a1da3[z27c0327a06],"",(void*)&pPart->transient->sInfo
);
#endif
}}
#ifdef z792c571d03
{double zc3072eb312;zdd072bd41d(&z20e42aaf2b);z97b9267d3a(&z5a5ffda126);
zc3072eb312=(double)(z20e42aaf2b.z0c40f5d56f-z97f07ce7f3.z0c40f5d56f)/(double)
z5a5ffda126.z0c40f5d56f;if(cvd->stat[pPart->pid].iJac==(0xfdc+355-0x113f)){
#ifdef zdb0d3593aa
sprintf(zbd872a1da3[(0x6da+6557-0x2077)],
"\x74\x53\x75\x6d\x3a\x20\x25\x66\x2c\x20\x74\x4d\x69\x6e\x20\x25\x66\x2c\x20\x74\x4d\x61\x78\x3a\x20\x25\x66\x2c\x20\x74\x41\x76\x72\x3a\x20\x25\x66"
,z108c4f8b41,zac37203452,zb274caa67f,zfbc16931b0);pPart->transient->sInfo.
z2b7d9e78b1((0x819+4494-0x19a7),(0x624+5995-0x1d8e),zbd872a1da3[
(0xdd9+777-0x10e2)],"",(void*)&pPart->transient->sInfo);
#endif
z108c4f8b41=(0x37a+1605-0x9bf);zac37203452=zc3072eb312;zb274caa67f=zc3072eb312;}
else{z108c4f8b41+=zc3072eb312;if(zac37203452>zc3072eb312)zac37203452=zc3072eb312
;if(zb274caa67f<zc3072eb312)zb274caa67f=zc3072eb312;}zfbc16931b0=z108c4f8b41/(
cvd->stat[pPart->pid].iJac+(0x128f+4051-0x2261));
#ifndef zdb0d3593aa
sprintf(zbd872a1da3[(0xc2a+5895-0x2331)],
"\x74\x4a\x61\x63\x3a\x20\x25\x66\x2c\x20\x74\x53\x75\x6d\x3a\x20\x25\x66\x2c\x20\x74\x4d\x69\x6e\x20\x25\x66\x2c\x20\x74\x4d\x61\x78\x3a\x20\x25\x66\x2c\x20\x74\x41\x76\x72\x3a\x20\x25\x66"
,zc3072eb312,z108c4f8b41,zac37203452,zb274caa67f,zfbc16931b0);pPart->transient->
sInfo.z2b7d9e78b1((0x13fc+4441-0x2555),(0x21f+1338-0x758),zbd872a1da3[
(0xa18+5745-0x2089)],"",(void*)&pPart->transient->sInfo);
#endif
for(zcec140f672=(0x1b8d+1971-0x2340);zcec140f672<cvc->maxThreads;zcec140f672++)
free(zbd872a1da3[zcec140f672]);free(zbd872a1da3);}
#endif
z78d65c20d2->z1b10328be9+=z3cc0d439ea->zb36402356f;cvd->stat[pPart->pid].
iRhsCalls+=z3cc0d439ea->zb36402356f;
#ifdef ITI_COMP_SIM
zfadc7b64e5(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#else
CopyVars(pPart->curr->bx_tmp,pPart->curr->bx,pPart->curr->size.bxind_cdfirst,
pPart->curr->size.ibx);
#endif
pPart->curr->sInfo.strAnalysisTypeDetail=
"\x72\x65\x73\x69\x64\x75\x61\x6c\x73";cvd->stat[pPart->pid].iJac++;if(retval!=
(0x417+8379-0x24d2)){for(zcec140f672=(0x25c+3792-0x112c);zcec140f672<cvc->
maxThreads;zcec140f672++)TransferWarnings(&zd6cbc80993->cvd_par[zcec140f672].
partition->curr->sInfo,&pPart->transient->sInfo);}return retval;}
#endif
#undef z5227064b5e
#undef z119f1bd5f7
#undef z864430a72f
#undef z7edcc2416e
#undef z02b1c4a3ea
#undef z8344334d43
#undef z078ac0b1a5
#undef z3960d6c10a
#undef z00a21f2f88

