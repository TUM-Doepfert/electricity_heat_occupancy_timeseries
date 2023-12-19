/**
 * ITI_NonLinSolver.c
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/


#include "ITI_crt.h"
#include "ITI_LinSolver.h"
#include "ITI_ClockEval.h"
#if defined (ITI_SIMULINK_S_FUNC) || defined (ITI_SFuncSolver)
#include "simstruc.h"
#endif
#if defined (ITI_CE_ETAS_LABCAR) || defined (ITI_SIMULINK_S_FUNC) || defined (\
ITI_SFuncSolver) || defined (ITI_FMI_CS2)
#include "ITI_NonLinSolver.h"
#else
#include "ITI_NonLinSolver.h"
#endif
#ifdef ITI_DSPACE
#undef _x
#undef _y
#endif
#if defined(zcbe7dd4099) && (zcbe7dd4099 < (0x1339+5695-0x220c))
#  define z614527e6ed zaa5129c2d9
#endif
void __CAT(InitEmbeddingData,)(void*zb425515a78,void*zfb02fbb98b,
ITI_EmbeddingData*zdcec0d15c5,ITI_uint za4489f0b51,ITI_uint bxind_homlast,
ITI_uint z77c4719614){z7529d16d33 z1d6d302708 ITI_uint zce99d8264d;ITI_uint 
z9e4f0600bc=bxind_homlast-za4489f0b51;ITI_int zb9c72bfb92=max(z77c4719614,
z9e4f0600bc);zdcec0d15c5->z4eeebcd909=z9e4f0600bc;zdcec0d15c5->z90bbed6de0=
za4489f0b51;zdcec0d15c5->z25f5c17222=z77c4719614;zdcec0d15c5->ze8fdbc6343=(
z77c4719614>=z9e4f0600bc);zdcec0d15c5->z9e92215ca6=(ITI_real*)calloc(z77c4719614
,sizeof(ITI_real));zdcec0d15c5->z4bc2586276=(ITI_real*)calloc(z9e4f0600bc,sizeof
(ITI_real));zdcec0d15c5->bx_tmp=(ITI_real*)calloc(bxind_homlast,sizeof(ITI_real)
);zdcec0d15c5->z8a41d0006a=(ITI_real*)calloc(z9e4f0600bc,sizeof(ITI_real));
zdcec0d15c5->z44a72f7bfb=(ITI_real*)calloc(z9e4f0600bc,sizeof(ITI_real));
zdcec0d15c5->z434f62ee93=(ITI_real*)calloc(z9e4f0600bc,sizeof(ITI_real));
zdcec0d15c5->z411b5a9678=(ITI_real*)calloc(z9e4f0600bc,sizeof(ITI_real));
zdcec0d15c5->z3960d6c10a=(ITI_real*)calloc(z9e4f0600bc*z77c4719614,sizeof(
ITI_real));zdcec0d15c5->z8ccfbd4931=(ITI_real*)calloc(z9e4f0600bc,sizeof(
ITI_real));zdcec0d15c5->ze7514d6a7f=(ITI_real*)calloc(z9e4f0600bc,sizeof(
ITI_real));zdcec0d15c5->z8d4186ad41=(ITI_real*)calloc(z9e4f0600bc,sizeof(
ITI_real));zdcec0d15c5->z8a73e5ac9c=(ITI_real*)calloc(z77c4719614,sizeof(
ITI_real));zdcec0d15c5->z34b6b98586=(ITI_real*)calloc(z9e4f0600bc,sizeof(
ITI_real));zdcec0d15c5->zf7377f07fe=(ITI_uint*)calloc(z9e4f0600bc,sizeof(
ITI_uint));zdcec0d15c5->zf4ae93b057=(ITI_real*)calloc(z9e4f0600bc,sizeof(
ITI_real));zdcec0d15c5->ze94ec32586=(ITI_real*)calloc(z9e4f0600bc,sizeof(
ITI_real));zdcec0d15c5->z4c54a1eefd=(ITI_real*)calloc(z9e4f0600bc,sizeof(
ITI_real));zdcec0d15c5->z51391e3ef1=(ITI_real*)calloc(zb9c72bfb92,sizeof(
ITI_real));zdcec0d15c5->zf667805127=(ITI_real*)calloc(zb9c72bfb92,sizeof(
ITI_real));for(zce99d8264d=(0x624+7254-0x227a);zce99d8264d<z9e4f0600bc;
zce99d8264d++){zdcec0d15c5->z34b6b98586[zce99d8264d]=1.0;zdcec0d15c5->
zf4ae93b057[zce99d8264d]=DBL_EPSILON;zdcec0d15c5->z4c54a1eefd[zce99d8264d]=1.0;
zdcec0d15c5->ze94ec32586[zce99d8264d]=-1.0;}zdcec0d15c5->zc81779069f=(ITI_uint*)
calloc(z9e4f0600bc,sizeof(ITI_uint));zdcec0d15c5->z264c1cd328=
(0x445+4027-0x1400);zdcec0d15c5->z72506057c6=1.0;__CAT(z74e5623a8b,)(
zdcec0d15c5,z9e4f0600bc,z77c4719614);assert(sizeof(integer)==sizeof(ITI_int));
assert(sizeof(doublereal)==sizeof(ITI_real));zdcec0d15c5->z9e95b22d7f.a=
zdcec0d15c5->z3960d6c10a;zdcec0d15c5->z9e95b22d7f.m=z77c4719614;zdcec0d15c5->
z9e95b22d7f.n=z9e4f0600bc;zdcec0d15c5->z9e95b22d7f.ldb=z9e4f0600bc;lls_init(&
zdcec0d15c5->z9e95b22d7f);zdcec0d15c5->z9e95b22d7f.work=calloc(zdcec0d15c5->
z9e95b22d7f.lwork,sizeof(ITI_real));zdcec0d15c5->z9e95b22d7f.jpvt=calloc(
z9e4f0600bc,sizeof(ITI_int));zdcec0d15c5->ze957e2faee=(ITI_real*)calloc(pPart->
transient->size.izf,sizeof(ITI_real));zdcec0d15c5->zed744e2941=(ITI_real*)calloc
(pPart->transient->size.izf,sizeof(ITI_real));zdcec0d15c5->z09e05a7a6d=(ITI_real
*)calloc(pPart->transient->size.izf,sizeof(ITI_real));zdcec0d15c5->z417a4f498b=(
ITI_real*)calloc(zdcec0d15c5->z4eeebcd909,sizeof(ITI_real));}void __CAT(
zb3611fe3f7,)(ITI_EmbeddingData*zdcec0d15c5){free(zdcec0d15c5->
z9e92215ca6);free(zdcec0d15c5->z4bc2586276);free(zdcec0d15c5->bx_tmp);free(
zdcec0d15c5->z8a41d0006a);free(zdcec0d15c5->z44a72f7bfb);free(zdcec0d15c5->
z434f62ee93);free(zdcec0d15c5->z411b5a9678);free(zdcec0d15c5->z3960d6c10a);free(
zdcec0d15c5->z03e5515547);free(zdcec0d15c5->zf08be7baa7);free(zdcec0d15c5->
z6473e0bce5);free(zdcec0d15c5->z8ba7bd6cb6);free(zdcec0d15c5->work);free(
zdcec0d15c5->z8ccfbd4931);free(zdcec0d15c5->ze7514d6a7f);free(zdcec0d15c5->
z8d4186ad41);free(zdcec0d15c5->z8a73e5ac9c);free(zdcec0d15c5->z34b6b98586);free(
zdcec0d15c5->zf7377f07fe);free(zdcec0d15c5->zf4ae93b057);free(zdcec0d15c5->
ze94ec32586);free(zdcec0d15c5->z4c54a1eefd);free(zdcec0d15c5->zc81779069f);free(
zdcec0d15c5->z51391e3ef1);free(zdcec0d15c5->zf667805127);free(zdcec0d15c5->
z9e95b22d7f.work);free(zdcec0d15c5->z9e95b22d7f.jpvt);free(zdcec0d15c5->
ze957e2faee);free(zdcec0d15c5->zed744e2941);free(zdcec0d15c5->z09e05a7a6d);free(
zdcec0d15c5->z417a4f498b);}void __CAT(z39328dfd8f,)(
ITI_EmbeddingParams*z6952f3187e,ITI_real za5d9603097,ITI_real z62eb1a3615){
z6952f3187e->z95f376aec4=1e-8;z6952f3187e->z26b200c34d=(0x97d+5995-0x20de);
z6952f3187e->z5c954d713f=0.2;z6952f3187e->z4bfea9a90b=0.5;z6952f3187e->
zfdee43babc=0.3;z6952f3187e->z432f21aa64=0.5*z6952f3187e->zfdee43babc;
z6952f3187e->z81339bb7b3=2.0;z6952f3187e->z717ffc7f4b=(0xd33+1637-0xfb0);
z6952f3187e->z0920b53d5c=1.0e-8;z6952f3187e->zc9298ae764=0.1;z6952f3187e->
z8021017b9a=-0.5;z6952f3187e->z1e52fe5184=1.01;z6952f3187e->z8e8b5dbf80=
(0x14eb+1797-0x1be6);z6952f3187e->zc72a658dd9=(0x1ae0+1963-0x1ea3);z6952f3187e->
z0466e2bdbb=0.0;z6952f3187e->zc55b8fab64=z6952f3187e->z95f376aec4;z6952f3187e->
zbe0284b765=z6952f3187e->z26b200c34d;z6952f3187e->z881e726654=0.1;z6952f3187e->
ze59e1c0f65=0.9;z6952f3187e->zb389952bf4=za5d9603097;z6952f3187e->z298a09d9bc=
z62eb1a3615;z6952f3187e->z1ae0008de8=(0x2f7+8-0x2eb);z6952f3187e->za49a3a96d0=
0.1;z6952f3187e->z6dbe734b84=0.5;z6952f3187e->z7930998139=1e-5;z6952f3187e->
z1903a1d1d0=(0x1182+3001-0x1d3b);}void __CAT(z74e5623a8b,)(
ITI_EmbeddingData*zdcec0d15c5,ITI_uint z9e4f0600bc,ITI_uint z77c4719614){ITI_int
 zbcd06d4a67;ITI_real z2cead138df;ITI_int m=z77c4719614;ITI_int n=zdcec0d15c5->
z4eeebcd909;ITI_int zed7121633b=min(m,n);ITI_int z0544068583=max(
(0x1138+802-0x1459),m);ITI_char zf325a54eb5=((char)(0xc12+2008-0x13a9));ITI_char
 z68981c957f=((char)(0x1e3f+1510-0x23e4));zdcec0d15c5->z03e5515547=(ITI_real*)
calloc(z77c4719614*z77c4719614,sizeof(ITI_real));zdcec0d15c5->zf08be7baa7=(
ITI_real*)calloc(zed7121633b,sizeof(ITI_real));zdcec0d15c5->z6473e0bce5=(
ITI_real*)calloc(z9e4f0600bc*z9e4f0600bc,sizeof(ITI_real));zdcec0d15c5->
z8ba7bd6cb6=(ITI_real*)calloc(z9e4f0600bc*z9e4f0600bc,sizeof(ITI_real));
zdcec0d15c5->lwork=-(0xfec+1786-0x16e5);dgesvd_(&zf325a54eb5,&z68981c957f,&m,&n,
NULL,&z0544068583,NULL,NULL,&z0544068583,NULL,&n,&z2cead138df,&zdcec0d15c5->
lwork,&zbcd06d4a67);zdcec0d15c5->lwork=(ITI_int)z2cead138df;zdcec0d15c5->work=(
ITI_real*)calloc(zdcec0d15c5->lwork,sizeof(ITI_real));}void __CAT(InitHomotopy,
)(void*zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,
ITI_EmbeddingParams*z6952f3187e,ITI_uint za4489f0b51,ITI_uint bxind_homlast,
ITI_uint z77c4719614,ITI_real za5d9603097,ITI_real z62eb1a3615){z15f3b3f7db 
z7529d16d33 z1d6d302708
#if defined _EMI_HOMOTOPY
ITI_HomMinMax*hmm;
#endif
__CAT(InitEmbeddingData,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,
za4489f0b51,bxind_homlast,z77c4719614);__CAT(z39328dfd8f,)(
z6952f3187e,za5d9603097,z62eb1a3615);
#ifdef _FMIMODEL_HOMOTOPY
modelData->hmm=(ITI_HomMinMax*)z279035f318->functions.allocateMemory(
(0xb20+1203-0xfd2),sizeof(ITI_HomMinMax));
#elif defined _EMI_HOMOTOPY
hmm=(ITI_HomMinMax*)calloc((0x55f+7979-0x2489),sizeof(ITI_HomMinMax));
#else
modelData->hmm=(ITI_HomMinMax*)calloc((0x908+5180-0x1d43),sizeof(ITI_HomMinMax))
;
#endif
#ifdef _EMI_HOMOTOPY
InitHomMinMax(hmm,zdcec0d15c5->z4eeebcd909);emcGetPWork(__C)[(0x250+7547-0x1fba)
]=hmm;
#else
InitHomMinMax(modelData->hmm,zdcec0d15c5->z4eeebcd909);
#endif
_bstate(zdcec0d15c5->z90bbed6de0)=1.0;}void __CAT(FreeHomotopy,)(void
*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5){z15f3b3f7db
#ifdef _EMI_HOMOTOPY
ITI_HomMinMax*hmm=(struct ITI_HomMinMax*)emcGetPWork(__C)[(0x827+2426-0x1190)];
#endif
#ifdef _EMI_HOMOTOPY
FreeHomMinMax(hmm,zdcec0d15c5->z4eeebcd909);
#else
FreeHomMinMax(modelData->hmm,zdcec0d15c5->z4eeebcd909);
#endif
#ifdef _FMIMODEL_HOMOTOPY
z279035f318->functions.freeMemory(modelData->hmm);
#elif defined _EMI_HOMOTOPY
free(hmm);
#else
free(modelData->hmm);
#endif
__CAT(zb3611fe3f7,)(zdcec0d15c5);}ITI_uint __CAT(CalcCurve,
)(void*zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,
ITI_EmbeddingParams*z6952f3187e,void*zf48d7e43ff){z15f3b3f7db z7529d16d33 
z1d6d302708 ITI_ModelFunctions*model=(ITI_ModelFunctions*)zf48d7e43ff;
#ifdef _EMI_HOMOTOPY
ITI_real z3f082f8bdc[pPart->transient->size.z600a6fd606+(0x1386+2300-0x1c81)];
ITI_real*zf=&(emcGetRWork(__C)[pPart->transient->size.zbf83df116e]);
#endif
ITI_int z01a44ab058=SOLVER_SUCCESS_END;ITI_uint zce99d8264d,z09d05839f2=
(0x12+9532-0x254e);ITI_uint zd74042d590=(0x25fc+264-0x2704);ITI_real zcfb665793f
,zb87c4bff82,z5e3656c9b1;ITI_real*z8c8519dc9d=(ITI_real*)calloc(zdcec0d15c5->
z4eeebcd909,sizeof(ITI_real));ITI_real*z97eabe881c=(ITI_real*)calloc(zdcec0d15c5
->z4eeebcd909,sizeof(ITI_real));
#ifdef zf26266bf1d
z7006c31b6f*zf0f8ffbaae=z9c1d462f32("\x70\x61\x74\x68\x2e\x74\x78\x74",
"\x77\x2b");fprintf(zf0f8ffbaae,
"\x53\x74\x65\x70" "\t" "\x6c\x61\x6d\x62\x64\x61\x48\x6f\x6d\x6f\x74\x6f\x70\x79" "\t" "\x53\x74\x65\x70\x20\x73\x69\x7a\x65" "\n"
);fprintf(zf0f8ffbaae,
"\x30" "\t" "\x20\x30" "\t" "\x25\x2d\x2e\x31\x37\x67" "\n",z6952f3187e->
z5c954d713f);
#endif
z5e407f1d0d z6952f3187e->ze954f3cce4=z6952f3187e->z5c954d713f;z6952f3187e->
zc55b8fab64=z6952f3187e->z95f376aec4;z6952f3187e->zbe0284b765=z6952f3187e->
z26b200c34d;_bstate(zdcec0d15c5->z90bbed6de0)=0.0;zdcec0d15c5->z8a41d0006a[
(0x1497+2974-0x2035)]=1.0;_sInfo.isEmbed=ITI_true;z6952f3187e->z1a8d55b886=
(0xefd+4620-0x2109);_sInfo.bUseSimpleHomotopy=(0x250+10-0x259);z01a44ab058=
zb1f36b2499 if(z01a44ab058>SOLVER_SUCCESS_END){ITI_char zea4cd01646[
(0xd01+5046-0x1fb8)];sprintf(zea4cd01646,
"\x45\x72\x72\x6f\x72\x3a\x20\x43\x61\x6e\x6e\x6f\x74\x20\x63\x6f\x6d\x70\x75\x74\x65\x20\x63\x6f\x6e\x73\x69\x73\x74\x65\x6e\x74\x20\x69\x6e\x69\x74\x69\x61\x6c\x20\x76\x61\x6c\x75\x65\x73\x20\x6f\x66\x20\x74\x68\x65\x20\x73\x74\x61\x72\x74\x20\x70\x6f\x69\x6e\x74\x20\x6f\x66\x20\x74\x68\x65\x20\x63\x75\x72\x76\x65\x20\x66\x6f\x72\x20\x6c\x61\x6d\x62\x64\x61\x48\x6f\x6d\x6f\x74\x6f\x70\x79\x3d\x30\x2e\x30\x2e" "\n"
);traceWarning(zea4cd01646,&_sInfo);free(z8c8519dc9d);free(z97eabe881c);
#ifdef zf26266bf1d
zaef96f649a(zf0f8ffbaae);
#endif
return(0x397+6521-0x1d0f);}
#if !defined _EMI_HOMOTOPY && !defined ITI_NI_LV_CDSIM
if(GetNumClockedPartitions(pPart)>(0x7a4+2743-0x125a)){z29851826b5;if(
PerformInferenceGraph(pPart,modelData)==SOLVER_ERROR_IN_INITIALIZATION){return
(0x1478+1767-0x1b5e);}z73130e01de;}
#endif
_sInfo.isEvent=ITI_false;__CAT(z1fe51ea564,)(zb425515a78,zfb02fbb98b,
zdcec0d15c5->zed744e2941);z01a44ab058=__CAT(z6d34c7efdb,)(zb425515a78
,zfb02fbb98b,zdcec0d15c5,z6952f3187e,zf48d7e43ff);if(z01a44ab058<
SOLVER_SUCCESS_END){ITI_char zea4cd01646[(0x2626+244-0x261b)];sprintf(
zea4cd01646,
"\x45\x72\x72\x6f\x72\x3a\x20\x43\x61\x6e\x6e\x6f\x74\x20\x63\x6f\x6d\x70\x75\x74\x65\x20\x63\x6f\x6e\x73\x69\x73\x74\x65\x6e\x74\x20\x69\x6e\x69\x74\x69\x61\x6c\x20\x76\x61\x6c\x75\x65\x73\x20\x6f\x66\x20\x74\x68\x65\x20\x73\x74\x61\x72\x74\x20\x70\x6f\x69\x6e\x74\x20\x6f\x66\x20\x74\x68\x65\x20\x63\x75\x72\x76\x65\x20\x66\x6f\x72\x20\x6c\x61\x6d\x62\x64\x61\x48\x6f\x6d\x6f\x74\x6f\x70\x79\x3d\x30\x2e\x30\x2e" "\n"
);traceWarning(zea4cd01646,&_sInfo);free(z8c8519dc9d);free(z97eabe881c);
#ifdef zf26266bf1d
zaef96f649a(zf0f8ffbaae);
#endif
return(0x9a9+3007-0x1567);}_bstate(zdcec0d15c5->z90bbed6de0)=0.0;_sInfo.
bUseSimpleHomotopy=(0x4f+2459-0x9ea);_sInfo.isEmbed=(0x13+7113-0x1bda);__CAT(
z1faac1090f,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e);if(
__CAT(z97f5bd8a23,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e,
zf48d7e43ff)>(0x1acb+2930-0x263d)){ITI_char zea4cd01646[(0x1210+4728-0x2389)];
sprintf(zea4cd01646,
"\x45\x72\x72\x6f\x72\x3a\x20\x54\x61\x6e\x67\x65\x6e\x74\x20\x63\x6f\x6d\x70\x75\x74\x61\x74\x69\x6f\x6e\x20\x66\x61\x69\x6c\x73\x20\x66\x6f\x72\x20\x6c\x61\x6d\x62\x64\x61\x48\x6f\x6d\x6f\x74\x6f\x70\x79\x3d\x30\x2e\x30\x2e" "\n"
);traceWarning(zea4cd01646,&_sInfo);free(z8c8519dc9d);free(z97eabe881c);
#ifdef zf26266bf1d
zaef96f649a(zf0f8ffbaae);
#endif
return(0xcc9+4622-0x1ed6);}for(zce99d8264d=(0x10ab+419-0x124e);zce99d8264d<
zdcec0d15c5->z4eeebcd909;zce99d8264d++){z8c8519dc9d[zce99d8264d]=_bstate(
zce99d8264d+zdcec0d15c5->z90bbed6de0);z97eabe881c[zce99d8264d]=zdcec0d15c5->
z8a41d0006a[zce99d8264d];}zcfb665793f=_bstate(zdcec0d15c5->z90bbed6de0);
z6952f3187e->ze954f3cce4=min(z6952f3187e->ze954f3cce4,z6952f3187e->zbe0284b765);
while(zd74042d590<z6952f3187e->z717ffc7f4b){__CAT(z828752be51,)(
zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e);zd74042d590++;z6952f3187e->
zbe0284b765=z6952f3187e->z26b200c34d;if(__CAT(zfcc32624f6,)(
zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e,zf48d7e43ff)>(0x23b6+532-0x25ca)
){free(z8c8519dc9d);free(z97eabe881c);
#ifdef zf26266bf1d
zaef96f649a(zf0f8ffbaae);
#endif
return(0x691+2564-0x1094);}zb87c4bff82=zcfb665793f;zcfb665793f=_bstate(
zdcec0d15c5->z90bbed6de0);z5e3656c9b1=z6952f3187e->zc9298ae764*fabs(zcfb665793f-
zb87c4bff82)+z6952f3187e->z0920b53d5c;if(zcfb665793f>=1.0-z5e3656c9b1){if(
zdcec0d15c5->z44a72f7bfb[(0x232+5819-0x18ed)]!=0.0)__CAT(zfa5fa8855f,
)(zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e,(0xe0+8207-0x20ef),(1.0-
zdcec0d15c5->z8ccfbd4931[(0x749+3953-0x16ba)])/zdcec0d15c5->z44a72f7bfb[
(0x580+6422-0x1e96)]);else{ITI_char zea4cd01646[(0x720+2535-0x1008)];sprintf(
zea4cd01646,
"\x54\x68\x65\x20\x63\x6f\x6d\x70\x75\x74\x65\x64\x20\x74\x61\x6e\x67\x65\x6e\x74\x20\x76\x65\x63\x74\x6f\x72\x20\x6f\x66\x20\x74\x68\x65\x20\x65\x6d\x62\x65\x64\x64\x69\x6e\x67\x20\x70\x61\x74\x68\x20\x68\x61\x73\x20\x7a\x65\x72\x6f\x20\x6c\x65\x6e\x67\x74\x68\x20\x61\x74\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x20\x76\x61\x6c\x75\x65\x20\x25\x65\x2e"
,zdcec0d15c5->z8ccfbd4931[(0x1509+1214-0x19c7)]);traceWarning(zea4cd01646,&
_sInfo);}break;}if(zcfb665793f<z6952f3187e->z8021017b9a){if(z09d05839f2>
(0xf6f+4859-0x226a)){ITI_char zea4cd01646[(0x726+7622-0x23ed)];sprintf(
zea4cd01646,
"\x45\x72\x72\x6f\x72\x3a\x20\x54\x68\x65\x20\x65\x6d\x62\x65\x64\x64\x69\x6e\x67\x20\x70\x61\x74\x68\x20\x67\x6f\x65\x73\x20\x69\x6e\x20\x74\x68\x65\x20\x77\x72\x6f\x6e\x67\x20\x65\x6d\x62\x65\x64\x64\x69\x6e\x67\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x20\x64\x69\x72\x65\x63\x74\x69\x6f\x6e\x2e"
);traceWarning(zea4cd01646,&_sInfo);free(z8c8519dc9d);free(z97eabe881c);
#ifdef zf26266bf1d
zaef96f649a(zf0f8ffbaae);
#endif
return(0x2471+421-0x2615);}++z09d05839f2;for(zce99d8264d=(0x18a2+1083-0x1cdd);
zce99d8264d<zdcec0d15c5->z4eeebcd909;zce99d8264d++){_bstate(zce99d8264d+
zdcec0d15c5->z90bbed6de0)=z8c8519dc9d[zce99d8264d];zdcec0d15c5->z8a41d0006a[
zce99d8264d]=-z97eabe881c[zce99d8264d];}zcfb665793f=_bstate(zdcec0d15c5->
z90bbed6de0);}
#ifdef zf26266bf1d
fprintf(zf0f8ffbaae,
"\x25\x75" "\t" "\x25\x2d\x2e\x31\x37\x67" "\t" "\x25\x2d\x2e\x31\x37\x67" "\n",
zd74042d590,_bstate(zdcec0d15c5->z90bbed6de0),z6952f3187e->ze954f3cce4);
#endif
if(z6952f3187e->ze954f3cce4<z6952f3187e->z95f376aec4){ITI_char zea4cd01646[
(0x13b5+267-0x13c1)];sprintf(zea4cd01646,
"\x45\x72\x72\x6f\x72\x3a\x20\x54\x68\x65\x20\x73\x74\x65\x70\x20\x73\x69\x7a\x65\x20\x25\x67\x20\x69\x73\x20\x73\x6d\x61\x6c\x6c\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x68\x65\x20\x6d\x69\x6e\x69\x6d\x61\x6c\x20\x73\x74\x65\x70\x20\x73\x69\x7a\x65\x20\x25\x67\x2e"
,z6952f3187e->ze954f3cce4,z6952f3187e->z95f376aec4);traceWarning(zea4cd01646,&
_sInfo);free(z8c8519dc9d);free(z97eabe881c);
#ifdef zf26266bf1d
zaef96f649a(zf0f8ffbaae);
#endif
return(0x609+6292-0x1e9c);}__CAT(z1faac1090f,)(zb425515a78,
zfb02fbb98b,zdcec0d15c5,z6952f3187e);}if(zd74042d590>=z6952f3187e->z717ffc7f4b){
ITI_char zea4cd01646[(0x495+5478-0x18fc)];sprintf(zea4cd01646,
"\x45\x72\x72\x6f\x72\x3a\x20\x48\x6f\x6d\x6f\x74\x6f\x70\x79\x20\x66\x61\x69\x6c\x73\x20\x61\x66\x74\x65\x72\x20\x25\x75\x20\x73\x74\x65\x70\x73\x20\x28\x6c\x61\x6d\x62\x64\x61\x48\x6f\x6d\x6f\x74\x6f\x70\x79\x3d\x25\x2d\x2e\x31\x37\x67\x29\x2e" "\n"
,z6952f3187e->z717ffc7f4b,_bstate(zdcec0d15c5->z90bbed6de0));traceWarning(
zea4cd01646,&_sInfo);free(z8c8519dc9d);free(z97eabe881c);
#ifdef zf26266bf1d
zaef96f649a(zf0f8ffbaae);
#endif
return(0x1ed+8391-0x22b3);}
#ifdef zf26266bf1d
fprintf(zf0f8ffbaae,
"\x25\x75" "\t" "\x25\x2d\x2e\x31\x37\x67" "\t" "\x25\x2d\x2e\x31\x37\x67" "\n",
zd74042d590,_bstate(zdcec0d15c5->z90bbed6de0),z6952f3187e->ze954f3cce4);
#endif
__CAT(z828752be51,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e);
zd74042d590++;zdcec0d15c5->z8a41d0006a[(0x4cb+4725-0x1740)]=(zdcec0d15c5->
z44a72f7bfb[(0xbf7+4828-0x1ed3)]<0.0)?-1.0:1.0;_bstate(zdcec0d15c5->z90bbed6de0)
=1.0;zdcec0d15c5->ze8fdbc6343=(0x23c8+558-0x25f6);for(zce99d8264d=
(0x153a+3868-0x2455);zce99d8264d<zdcec0d15c5->z4eeebcd909;zce99d8264d++)
zdcec0d15c5->z8a41d0006a[zce99d8264d]=0.0;_sInfo.isEmbed=ITI_false;_sInfo.
isEvent=ITI_true;z01a44ab058=zb1f36b2499 if(z01a44ab058>SOLVER_SUCCESS_END){
ITI_char zea4cd01646[(0x178+8880-0x2329)];sprintf(zea4cd01646,
"\x45\x72\x72\x6f\x72\x3a\x20\x48\x6f\x6d\x6f\x74\x6f\x70\x79\x20\x66\x61\x69\x6c\x73\x20\x61\x74\x20\x74\x68\x65\x20\x73\x74\x6f\x70\x20\x70\x6f\x69\x6e\x74\x20\x6f\x66\x20\x74\x68\x65\x20\x63\x75\x72\x76\x65\x20\x66\x6f\x72\x20\x6c\x61\x6d\x62\x64\x61\x48\x6f\x6d\x6f\x74\x6f\x70\x79\x3d\x31\x2e\x30\x2e" "\n"
);traceWarning(zea4cd01646,&_sInfo);free(z8c8519dc9d);free(z97eabe881c);
#ifdef zf26266bf1d
zaef96f649a(zf0f8ffbaae);
#endif
return(0xf70+3570-0x1d61);}
#if !defined _EMI_HOMOTOPY && !defined ITI_NI_LV_CDSIM
if(GetNumClockedPartitions(pPart)>(0x4f6+5502-0x1a73)){z29851826b5;if(
PerformInferenceGraph(pPart,modelData)==SOLVER_ERROR_IN_INITIALIZATION){return
(0x421+295-0x547);}z73130e01de;}
#endif
z01a44ab058=__CAT(z6d34c7efdb,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,
z6952f3187e,zf48d7e43ff);_sInfo.isEvent=ITI_true;if(z01a44ab058<
SOLVER_SUCCESS_END){ITI_char zea4cd01646[(0x1fc0+1582-0x24ef)];sprintf(
zea4cd01646,
"\x45\x72\x72\x6f\x72\x3a\x20\x48\x6f\x6d\x6f\x74\x6f\x70\x79\x20\x66\x61\x69\x6c\x73\x20\x61\x74\x20\x74\x68\x65\x20\x73\x74\x6f\x70\x20\x70\x6f\x69\x6e\x74\x20\x6f\x66\x20\x74\x68\x65\x20\x63\x75\x72\x76\x65\x20\x66\x6f\x72\x20\x6c\x61\x6d\x62\x64\x61\x48\x6f\x6d\x6f\x74\x6f\x70\x79\x3d\x31\x2e\x30\x2e" "\n"
);traceWarning(zea4cd01646,&_sInfo);free(z8c8519dc9d);free(z97eabe881c);
#ifdef zf26266bf1d
zaef96f649a(zf0f8ffbaae);
#endif
return(0x13b+6915-0x1c3d);}
#ifdef zf26266bf1d
fprintf(zf0f8ffbaae,
"\x25\x75" "\t" "\x25\x2d\x2e\x31\x37\x67" "\t" "\x25\x2d\x2e\x31\x37\x67" "\n",
zd74042d590,_bstate(zdcec0d15c5->z90bbed6de0),z6952f3187e->ze954f3cce4);
zaef96f649a(zf0f8ffbaae);
#endif
if(__CAT(z97f5bd8a23,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,
z6952f3187e,zf48d7e43ff)>(0xb7f+3871-0x1a9e)){ITI_char zea4cd01646[
(0x1d70+1675-0x22fc)];sprintf(zea4cd01646,
"\x45\x72\x72\x6f\x72\x3a\x20\x54\x61\x6e\x67\x65\x6e\x74\x20\x63\x6f\x6d\x70\x75\x74\x61\x74\x69\x6f\x6e\x20\x66\x61\x69\x6c\x73\x20\x66\x6f\x72\x20\x6c\x61\x6d\x62\x64\x61\x48\x6f\x6d\x6f\x74\x6f\x70\x79\x3d\x31\x2e\x30\x2e" "\n"
);traceWarning(zea4cd01646,&_sInfo);free(z8c8519dc9d);free(z97eabe881c);return
(0xc57+3103-0x1875);}_sInfo.isEmbed=ITI_false;free(z8c8519dc9d);free(z97eabe881c
);return(0x32b+2835-0xe3e);}ITI_uint __CAT(z85035d0bf5,)(void*
zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*
z6952f3187e,void*zf48d7e43ff){z15f3b3f7db z7529d16d33 z1d6d302708 ITI_uint 
zce99d8264d;ITI_char zea4cd01646[(0x1a4+1772-0x791)];ITI_uint z7ec2813c96=
(0x16cb+1427-0x1c5d);ITI_real zf38d6c2ce4=0.0;ITI_real zf2146ea2b9=0.0;ITI_real 
z812893a007=1.0;ITI_real zf14d711e90=0.0;ITI_real zcf8e59cd26=1.0;ITI_uint 
z812c65ff2f=(0x1481+4648-0x26a9);__CAT(zf29e330b26,)(zb425515a78,
zfb02fbb98b,zdcec0d15c5,z6952f3187e,zf48d7e43ff);for(z812c65ff2f=
(0x33a+78-0x388);z812c65ff2f<z6952f3187e->z1ae0008de8;z812c65ff2f++){__CAT(
z4320d07649,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e,
zf48d7e43ff);if(__CAT(z6474127c41,)(zb425515a78,zfb02fbb98b,
zdcec0d15c5)>(0x1a8d+2586-0x24a7))return(0x83+9818-0x26dc);__CAT(zf901b7d7e1,
)(zb425515a78,zfb02fbb98b,zdcec0d15c5,zdcec0d15c5->z9e92215ca6,
zdcec0d15c5->z4bc2586276,z7ec2813c96);zf2146ea2b9=__CAT(z62f48093a2,)
(zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e,zf48d7e43ff);zf14d711e90=
zf2146ea2b9/z812893a007;for(zce99d8264d=(0x182a+3775-0x26e9);zce99d8264d<
zdcec0d15c5->z4eeebcd909;zce99d8264d++)_bstate(zce99d8264d+zdcec0d15c5->
z90bbed6de0)+=zdcec0d15c5->z4bc2586276[zce99d8264d]*zdcec0d15c5->z3f01d343c0;if(
(zf2146ea2b9<=z6952f3187e->z7930998139)||((zdcec0d15c5->z3f01d343c0==1.0)&&(
zf38d6c2ce4==1.0)&&(zcf8e59cd26<1.0)&&(zf2146ea2b9<=1.0)&&((zcf8e59cd26<=
DBL_EPSILON)||(zf14d711e90<zcf8e59cd26))))return(0x12bf+3958-0x2235);zf38d6c2ce4
=zdcec0d15c5->z3f01d343c0;z812893a007=zf2146ea2b9;zcf8e59cd26=zf14d711e90;}
sprintf(zea4cd01646,
"\x45\x72\x72\x6f\x72\x3a\x20\x4e\x6f\x20\x63\x6f\x6e\x76\x65\x72\x67\x65\x6e\x63\x65\x20\x61\x66\x74\x65\x72\x20\x25\x75\x20\x73\x74\x65\x70\x73\x20\x66\x6f\x72\x20\x6c\x61\x6d\x62\x64\x61\x48\x6f\x6d\x6f\x74\x6f\x70\x79\x3d\x25\x2d\x2e\x31\x37\x67\x2e" "\n"
,z6952f3187e->z1ae0008de8,_bstate(zdcec0d15c5->z90bbed6de0));traceWarning(
zea4cd01646,&_sInfo);return(0x1058+3343-0x1d66);}ITI_uint __CAT(z8b17e620d6,
)(void*zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,
ITI_EmbeddingParams*z6952f3187e,void*zf48d7e43ff){ITI_uint z6fcd5db760=
(0x466+4502-0x15fb);__CAT(zf29e330b26,)(zb425515a78,zfb02fbb98b,
zdcec0d15c5,z6952f3187e,zf48d7e43ff);return __CAT(z82aef60b72,)(
zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e,zf48d7e43ff,z6fcd5db760);}
ITI_uint __CAT(z82aef60b72,)(void*zb425515a78,void*zfb02fbb98b,
ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*z6952f3187e,void*zf48d7e43ff,
ITI_uint z6fcd5db760){z7529d16d33 z1d6d302708 ITI_char zea4cd01646[
(0x1238+3502-0x1ee7)];ITI_uint zce99d8264d;ITI_real z720ca9f240,z8475703e80,
za4112c943e;ITI_int m=zdcec0d15c5->z25f5c17222;ITI_int n=zdcec0d15c5->
z4eeebcd909;ITI_real z3f01d343c0=0.1;ITI_uint z6fd7c833c1=(0x774+7354-0x242e);
ITI_uint z3bbc4e81f2=(0x19d4+220-0x1aaf);do{switch(z3bbc4e81f2){case
(0x7f4+6653-0x21f0):switch(z6fcd5db760){case(0x1635+2397-0x1f91):__CAT(
z4320d07649,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e,
zf48d7e43ff);for(zce99d8264d=(0x1480+3755-0x232b);zce99d8264d<zdcec0d15c5->
z25f5c17222;zce99d8264d++){zdcec0d15c5->z4bc2586276[zce99d8264d]=zdcec0d15c5->
z9e92215ca6[zce99d8264d];zdcec0d15c5->z9e95b22d7f.jpvt[zce99d8264d]=
(0x317+8360-0x23bf);}zdcec0d15c5->z9e95b22d7f.m=m;zdcec0d15c5->z9e95b22d7f.n=n;
zdcec0d15c5->z9e95b22d7f.ldb=n;zdcec0d15c5->z9e95b22d7f.b=zdcec0d15c5->
z4bc2586276;lls_fact(&zdcec0d15c5->z9e95b22d7f);lls_solv(&zdcec0d15c5->
z9e95b22d7f);break;case(0x1845+821-0x1b78):__CAT(z54d9b09da9,)(
zdcec0d15c5,zdcec0d15c5->z9e92215ca6,zdcec0d15c5->z4bc2586276);break;}
zdcec0d15c5->z18c08b309a=EuklNorm(zdcec0d15c5->z4bc2586276,zdcec0d15c5->
z4eeebcd909);if(zdcec0d15c5->z18c08b309a<1e-007)return(0x1844+3105-0x2465);if(
z6fd7c833c1>(0x16c6+329-0x180f)){ITI_real z4bc2586276;for(zce99d8264d=
(0x1e33+767-0x2132);zce99d8264d<zdcec0d15c5->z4eeebcd909;zce99d8264d++)
zdcec0d15c5->zf667805127[zce99d8264d]=zdcec0d15c5->z51391e3ef1[zce99d8264d]-
zdcec0d15c5->z4bc2586276[zce99d8264d];z4bc2586276=EuklNorm(zdcec0d15c5->
zf667805127,zdcec0d15c5->z4eeebcd909);if(z4bc2586276==0.0)z3f01d343c0=1.0;else{
za4112c943e=zdcec0d15c5->z22d4438c10*zdcec0d15c5->zfaa7d86a2c*z3f01d343c0/(
z4bc2586276*zdcec0d15c5->z18c08b309a);z3f01d343c0=max(min(1.0,za4112c943e),
1e-008);}}z6ccc5f5e83 case(0xabd+4480-0x1c38):z6fd7c833c1++;if(z3f01d343c0<
1e-008){sprintf(zea4cd01646,
"\x45\x72\x72\x6f\x72\x3a\x20\x4e\x6f\x20\x63\x6f\x6e\x76\x65\x72\x67\x65\x6e\x63\x65\x20\x28\x64\x61\x6d\x70\x69\x6e\x67\x29\x20\x66\x6f\x72\x20\x6c\x61\x6d\x62\x64\x61\x48\x6f\x6d\x6f\x74\x6f\x70\x79\x3d\x25\x2d\x2e\x31\x37\x67\x2e" "\n"
,_bstate(zdcec0d15c5->z90bbed6de0));traceWarning(zea4cd01646,&_sInfo);return 
z6fcd5db760;}for(zce99d8264d=(0xce9+5082-0x20c3);zce99d8264d<zdcec0d15c5->
z4eeebcd909;zce99d8264d++)_bstate(zce99d8264d+zdcec0d15c5->z90bbed6de0)-=
z3f01d343c0*zdcec0d15c5->z4bc2586276[zce99d8264d];__CAT(zf29e330b26,)
(zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e,zf48d7e43ff);for(zce99d8264d=
(0xa5a+5737-0x20c3);zce99d8264d<zdcec0d15c5->z4eeebcd909;zce99d8264d++)
zdcec0d15c5->z51391e3ef1[zce99d8264d]=0.0;switch(z6fcd5db760){case
(0x40+6587-0x19fa):for(zce99d8264d=(0x18d4+3138-0x2516);zce99d8264d<zdcec0d15c5
->z25f5c17222;zce99d8264d++)zdcec0d15c5->z51391e3ef1[zce99d8264d]=zdcec0d15c5->
z9e92215ca6[zce99d8264d];zdcec0d15c5->z9e95b22d7f.b=zdcec0d15c5->z51391e3ef1;
lls_solv(&zdcec0d15c5->z9e95b22d7f);break;case(0x960+1776-0x104e):__CAT(
z54d9b09da9,)(zdcec0d15c5,zdcec0d15c5->z9e92215ca6,zdcec0d15c5->
z51391e3ef1);break;}zdcec0d15c5->zfaa7d86a2c=EuklNorm(zdcec0d15c5->z51391e3ef1,
zdcec0d15c5->z4eeebcd909);for(zce99d8264d=(0x5db+5853-0x1cb8);zce99d8264d<
zdcec0d15c5->z4eeebcd909;zce99d8264d++)zdcec0d15c5->zf667805127[zce99d8264d]=
zdcec0d15c5->z51391e3ef1[zce99d8264d]+(z3f01d343c0-1.0)*zdcec0d15c5->z4bc2586276
[zce99d8264d];z8475703e80=EuklNorm(zdcec0d15c5->zf667805127,zdcec0d15c5->
z4eeebcd909);{ITI_real zc9ad6c3dc6=(0.5*zdcec0d15c5->z18c08b309a*z3f01d343c0*
z3f01d343c0);if(zc9ad6c3dc6<1e35*z8475703e80)za4112c943e=zc9ad6c3dc6/z8475703e80
;else za4112c943e=1e+35;}if(zdcec0d15c5->zfaa7d86a2c>=zdcec0d15c5->z18c08b309a){
z720ca9f240=min(za4112c943e,0.5*z3f01d343c0);if(z3f01d343c0<=1e-008)z3f01d343c0=
z720ca9f240;else z3f01d343c0=max(z720ca9f240,1e-008);zdcec0d15c5->ze4a8849194=
(0x1e44+166-0x1ee9);z5e407f1d0d z3bbc4e81f2=(0x12a8+4039-0x226a);continue;}
z720ca9f240=min(1.0,za4112c943e);if(z3f01d343c0==1.0&&z720ca9f240==1.0){if(
zdcec0d15c5->zfaa7d86a2c<=1e-007)return(0xe9b+3851-0x1da6);}else{if(z720ca9f240
>=4.0*z3f01d343c0&&zdcec0d15c5->ze4a8849194==(0x12fc+3453-0x2079)){z3f01d343c0=
z720ca9f240;zdcec0d15c5->ze4a8849194=(0x7ab+2632-0x11f2);z5e407f1d0d z3bbc4e81f2
=(0xd75+727-0x1047);continue;}}zdcec0d15c5->ze4a8849194=(0xe78+1722-0x1532);
zdcec0d15c5->z22d4438c10=zdcec0d15c5->z18c08b309a;z3bbc4e81f2=(0xdb+9246-0x24f8)
;}}while(z6fd7c833c1<z6952f3187e->z1ae0008de8);sprintf(zea4cd01646,
"\x45\x72\x72\x6f\x72\x3a\x20\x4e\x6f\x20\x63\x6f\x6e\x76\x65\x72\x67\x65\x6e\x63\x65\x20\x61\x66\x74\x65\x72\x20\x25\x75\x20\x73\x74\x65\x70\x73\x20\x66\x6f\x72\x20\x6c\x61\x6d\x62\x64\x61\x48\x6f\x6d\x6f\x74\x6f\x70\x79\x3d\x25\x2d\x2e\x31\x37\x67\x2e" "\n"
,z6952f3187e->z1ae0008de8,_bstate(zdcec0d15c5->z90bbed6de0));traceWarning(
zea4cd01646,&_sInfo);return z6fcd5db760;}ITI_uint __CAT(z97f5bd8a23,)
(void*zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,
ITI_EmbeddingParams*z6952f3187e,void*zf48d7e43ff){z15f3b3f7db z7529d16d33 
z1d6d302708 ITI_uint zce99d8264d,z26dbd73a5e;ITI_real zd8bb6b5553;ITI_real 
zf7f2900287;__CAT(z4320d07649,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,
z6952f3187e,zf48d7e43ff);if(__CAT(z6474127c41,)(zb425515a78,
zfb02fbb98b,zdcec0d15c5)>(0x755+7748-0x2599))return(0x5b+6471-0x19a1);
zdcec0d15c5->ze4482e84dd=zdcec0d15c5->z4eeebcd909-zdcec0d15c5->z7663004f47;for(
zce99d8264d=(0x617+2762-0x10e1);zce99d8264d<zdcec0d15c5->ze4482e84dd;zce99d8264d
++)zdcec0d15c5->z434f62ee93[zce99d8264d]=zdcec0d15c5->z6473e0bce5[zdcec0d15c5->
z7663004f47+zce99d8264d];zf7f2900287=EuklNorm(zdcec0d15c5->z434f62ee93,
zdcec0d15c5->ze4482e84dd);if(zf7f2900287==0.0){for(zce99d8264d=
(0x12c0+1183-0x175f);zce99d8264d<zdcec0d15c5->z4eeebcd909;zce99d8264d++){
zdcec0d15c5->z411b5a9678[zce99d8264d]=zdcec0d15c5->z6473e0bce5[(int)floor(
z6952f3187e->z1903a1d1d0/2.0)+zdcec0d15c5->z7663004f47+zdcec0d15c5->z4eeebcd909*
zce99d8264d];}z6952f3187e->z1903a1d1d0++;if(floor(z6952f3187e->z1903a1d1d0/2.0)
>=zdcec0d15c5->ze4482e84dd)z6952f3187e->z1903a1d1d0=(0x5d6+1315-0xaf9);}else{for
(zce99d8264d=(0x827+871-0xb8e);zce99d8264d<zdcec0d15c5->z4eeebcd909;zce99d8264d
++){zdcec0d15c5->z411b5a9678[zce99d8264d]=0.0;for(z26dbd73a5e=
(0x142c+4452-0x2590);z26dbd73a5e<zdcec0d15c5->ze4482e84dd;z26dbd73a5e++)
zdcec0d15c5->z411b5a9678[zce99d8264d]+=zdcec0d15c5->z6473e0bce5[zdcec0d15c5->
z7663004f47+z26dbd73a5e+zdcec0d15c5->z4eeebcd909*zce99d8264d]*zdcec0d15c5->
z434f62ee93[z26dbd73a5e];zdcec0d15c5->z411b5a9678[zce99d8264d]/=zf7f2900287;}}
__CAT(z11cd768e30,)(zdcec0d15c5->z411b5a9678,z6952f3187e->z26b200c34d
,zdcec0d15c5->z4eeebcd909);if(SProd(zdcec0d15c5->z8a41d0006a,zdcec0d15c5->
z411b5a9678,zdcec0d15c5->z4eeebcd909)<(0x18b5+623-0x1b24))__CAT(z11cd768e30,
)(zdcec0d15c5->z411b5a9678,-1.0,zdcec0d15c5->z4eeebcd909);if(__hmm->
considerLimit)__CAT(zb3da54817e,)(zb425515a78,zfb02fbb98b,zdcec0d15c5
,zdcec0d15c5->z411b5a9678);zd8bb6b5553=__CAT(zab7ffcf1ba,)(
zdcec0d15c5->z411b5a9678,zdcec0d15c5->z34b6b98586,zdcec0d15c5->z4eeebcd909);for(
zce99d8264d=(0x22b0+82-0x2302);zce99d8264d<zdcec0d15c5->z4eeebcd909;zce99d8264d
++)zdcec0d15c5->z8a41d0006a[zce99d8264d]=zdcec0d15c5->z411b5a9678[zce99d8264d]/
zd8bb6b5553;z6952f3187e->zbe0284b765=max(z6952f3187e->z95f376aec4,min(
z6952f3187e->z26b200c34d*zdcec0d15c5->z72506057c6,z6952f3187e->zbe0284b765));if(
z6952f3187e->z26b200c34d*zdcec0d15c5->z72506057c6<z6952f3187e->z95f376aec4){
ITI_char zea4cd01646[(0x1f6+3725-0xf84)];sprintf(zea4cd01646,
"\x54\x68\x65\x20\x69\x6e\x20\x6f\x72\x64\x65\x72\x20\x74\x6f\x20\x61\x76\x6f\x69\x64\x20\x65\x78\x63\x65\x65\x64\x69\x6e\x67\x20\x74\x68\x65\x20\x6c\x69\x6d\x69\x74\x73\x20\x73\x75\x67\x67\x65\x73\x74\x65\x64\x20\x73\x74\x65\x70\x20\x73\x69\x7a\x65\x20\x25\x67\x20\x69\x73\x20\x73\x6d\x61\x6c\x6c\x65\x72\x20\x74\x68\x61\x6e\x20\x74\x68\x65\x20\x6d\x69\x6e\x69\x6d\x61\x6c\x20\x73\x74\x65\x70\x20\x73\x69\x7a\x65\x20\x25\x67\x2e\x20" "\n"
,z6952f3187e->z26b200c34d*zdcec0d15c5->z72506057c6,z6952f3187e->z95f376aec4);
traceWarning(zea4cd01646,&_sInfo);return(0x301+6375-0x1be7);}return
(0x2b4+7436-0x1fc0);}ITI_uint __CAT(zfcc32624f6,)(void*zb425515a78,
void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*z6952f3187e,
void*zf48d7e43ff){z15f3b3f7db z7529d16d33 z1d6d302708 ITI_uint z01a44ab058=
SOLVER_SUCCESS_END;ITI_uint z0d48c638e3=(0x15db+2649-0x2034);ITI_int zbc03e9b268
=-(0x208+9079-0x257e);z6952f3187e->za494561071=z6952f3187e->z4bfea9a90b;do{for(
z6952f3187e->zcb80911ce0=(0xa5+4802-0x1367);z6952f3187e->ze954f3cce4>=
z6952f3187e->zc55b8fab64;z6952f3187e->ze954f3cce4*=z6952f3187e->z4bfea9a90b,
z6952f3187e->zcb80911ce0=(0x576+602-0x7d0)){__CAT(zfa5fa8855f,)(
zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e,-(0x8d7+3608-0x16ee),z6952f3187e
->ze954f3cce4);z01a44ab058=__CAT(z6e964533e7,)(zb425515a78,
zfb02fbb98b,zdcec0d15c5,z6952f3187e,zf48d7e43ff);if(z01a44ab058==
SOLVER_SUCCESS_CONTINUE)return(0x52b+5177-0x1963);else if(z01a44ab058==
SOLVER_TERMINATED)continue;else z6952f3187e->z1a8d55b886=(0x10c+4097-0x110c);
__CAT(zf29e330b26,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e,
zf48d7e43ff);if(__CAT(z97f5bd8a23,)(zb425515a78,zfb02fbb98b,
zdcec0d15c5,z6952f3187e,zf48d7e43ff)>(0x3d6+3082-0xfe0)){ITI_char zea4cd01646[
(0x8e7+1464-0xda0)];sprintf(zea4cd01646,
"\x45\x72\x72\x6f\x72\x3a\x20\x54\x61\x6e\x67\x65\x6e\x74\x20\x63\x6f\x6d\x70\x75\x74\x61\x74\x69\x6f\x6e\x20\x66\x61\x69\x6c\x73\x20\x66\x6f\x72\x20\x6c\x61\x6d\x62\x64\x61\x48\x6f\x6d\x6f\x74\x6f\x70\x79\x3d\x25\x2d\x2e\x31\x37\x67\x2e" "\n"
,_bstate(zdcec0d15c5->z90bbed6de0));traceWarning(zea4cd01646,&_sInfo);return
(0xe00+3463-0x1b86);}__CAT(z097b6f9bf5,)(zdcec0d15c5,z6952f3187e);if(
z6952f3187e->z0466e2bdbb<=z6952f3187e->zfdee43babc)break;}if(z6952f3187e->
ze954f3cce4<z6952f3187e->zc55b8fab64){if(__CAT(z85035d0bf5,)(
zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e,zf48d7e43ff)>(0xa99+4868-0x1d9d)
)return(0xe06+4117-0x1e1a);z6952f3187e->z1a8d55b886=(0x818+1362-0xd69);}
z6952f3187e->zcb80911ce0=(0xdd7+3908-0x1d1b);zbc03e9b268=__CAT(z6d34c7efdb,
)(zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e,zf48d7e43ff);if(
zbc03e9b268<(0x941+1933-0x10ce)){z6952f3187e->zcb80911ce0=(0x10a6+5202-0x24f7);
z6952f3187e->ze954f3cce4=max(z6952f3187e->z95f376aec4,0.99*z6952f3187e->
ze954f3cce4);}if(z6952f3187e->zcb80911ce0){if(++z0d48c638e3>z6952f3187e->
z8e8b5dbf80){ITI_char zea4cd01646[(0x227d+182-0x2234)];sprintf(zea4cd01646,
"\x45\x72\x72\x6f\x72\x3a\x20\x54\x68\x65\x20\x6d\x61\x78\x69\x6d\x61\x6c\x20\x6e\x75\x6d\x62\x65\x72\x20\x6f\x66\x20\x25\x75\x20\x72\x65\x74\x72\x69\x65\x73\x20\x28\x77\x69\x74\x68\x20\x72\x65\x64\x75\x63\x65\x64\x20\x73\x74\x65\x70\x20\x73\x69\x7a\x65\x29\x20\x61\x66\x74\x65\x72\x20\x61\x20\x72\x65\x70\x65\x61\x74\x65\x64\x20\x63\x61\x6c\x63\x75\x6c\x61\x74\x69\x6f\x6e\x20\x6f\x66\x20\x74\x68\x65\x20\x63\x75\x72\x72\x65\x6e\x74\x20\x70\x6f\x69\x6e\x74\x20\x68\x61\x73\x20\x62\x65\x65\x6e\x20\x65\x78\x63\x65\x65\x64\x65\x64\x20\x69\x6e\x20\x61\x20\x68\x6f\x6d\x6f\x74\x6f\x70\x79\x20\x73\x74\x65\x70\x20\x66\x6f\x72\x20\x6c\x61\x6d\x62\x64\x61\x48\x6f\x6d\x6f\x74\x6f\x70\x79\x3d\x25\x2d\x2e\x31\x37\x67\x2e" "\n"
,z6952f3187e->z8e8b5dbf80,_bstate(zdcec0d15c5->z90bbed6de0));traceWarning(
zea4cd01646,&_sInfo);return(0xefc+1654-0x1571);}}else break;}while(
(0x212a+1299-0x263c));if(zbc03e9b268>(0x1ced+359-0x1e54))z6952f3187e->
ze954f3cce4=z6952f3187e->z5c954d713f;else if(z6952f3187e->ze954f3cce4<
z6952f3187e->zc55b8fab64)z6952f3187e->ze954f3cce4=z6952f3187e->z95f376aec4;else{
__CAT(zbb1a877b64,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e);
}return(0x226d+215-0x2344);}void __CAT(zbb1a877b64,)(void*zb425515a78
,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*z6952f3187e)
{z7529d16d33 z1d6d302708 ITI_real z26505f5082=__CAT(zab7ffcf1ba,)(
zdcec0d15c5->z8a41d0006a,zdcec0d15c5->z34b6b98586,zdcec0d15c5->z4eeebcd909);
ITI_real z31b80bfa3d=zdcec0d15c5->z8a41d0006a[(0xfe8+5472-0x2548)]/z26505f5082;
ITI_real z4675d8a028;z6952f3187e->za494561071=max(z6952f3187e->za494561071,
z6952f3187e->z0466e2bdbb/z6952f3187e->z432f21aa64);if(z6952f3187e->za494561071*
z6952f3187e->zbe0284b765>z6952f3187e->ze954f3cce4)z6952f3187e->ze954f3cce4=max(
z6952f3187e->z95f376aec4,z6952f3187e->ze954f3cce4/z6952f3187e->za494561071);else
 z6952f3187e->ze954f3cce4=min(z6952f3187e->zbe0284b765,z6952f3187e->ze954f3cce4/
z6952f3187e->z4bfea9a90b);z4675d8a028=_bstate(zdcec0d15c5->z90bbed6de0)+
z31b80bfa3d*z6952f3187e->ze954f3cce4;if(z4675d8a028>1.0)z6952f3187e->ze954f3cce4
=max(z6952f3187e->z95f376aec4,z6952f3187e->z1e52fe5184*(1.0-_bstate(zdcec0d15c5
->z90bbed6de0))/z31b80bfa3d);}ITI_uint __CAT(z6e964533e7,)(void*
zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*
z6952f3187e,void*zf48d7e43ff){z7529d16d33 z1d6d302708 ITI_uint zce99d8264d;
ITI_real z9439e49293,zdc8d9bb183;ITI_uint z7ec2813c96=(0x211+2777-0xce9);
ITI_uint z6fd7c833c1=(0x4d5+2079-0xcf4);__CAT(zf29e330b26,)(
zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e,zf48d7e43ff);if(__CAT(
z97f5bd8a23,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e,
zf48d7e43ff)>(0x1536+689-0x17e7)){ITI_char zea4cd01646[(0x3e5+965-0x6ab)];
sprintf(zea4cd01646,
"\x45\x72\x72\x6f\x72\x3a\x20\x54\x61\x6e\x67\x65\x6e\x74\x20\x63\x6f\x6d\x70\x75\x74\x61\x74\x69\x6f\x6e\x20\x66\x61\x69\x6c\x73\x20\x66\x6f\x72\x20\x6c\x61\x6d\x62\x64\x61\x48\x6f\x6d\x6f\x74\x6f\x70\x79\x3d\x25\x2d\x2e\x31\x37\x67\x2e" "\n"
,_bstate(zdcec0d15c5->z90bbed6de0));traceWarning(zea4cd01646,&_sInfo);return
(0x1358+2312-0x1c5f);}__CAT(z097b6f9bf5,)(zdcec0d15c5,z6952f3187e);if
(z6952f3187e->z0466e2bdbb>z6952f3187e->zfdee43babc)return(0xd53+451-0xf14);__CAT
(zf901b7d7e1,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,zdcec0d15c5->
z9e92215ca6,zdcec0d15c5->z4bc2586276,z7ec2813c96);for(zce99d8264d=
(0x78d+2348-0x10b9);zce99d8264d<zdcec0d15c5->z4eeebcd909;zce99d8264d++)_bstate(
zce99d8264d+zdcec0d15c5->z90bbed6de0)+=zdcec0d15c5->z4bc2586276[zce99d8264d];
z6fd7c833c1++;if(__CAT(z5d747ed95f,)(zb425515a78,zfb02fbb98b,
z6952f3187e,zdcec0d15c5->z4bc2586276,zdcec0d15c5->z34b6b98586,zdcec0d15c5->
z4eeebcd909,zdcec0d15c5->z90bbed6de0,&z9439e49293))return(0xc1+8250-0x20fb);if(
z9439e49293>z6952f3187e->z881e726654)return(0x180b+3207-0x2490);__CAT(
zf29e330b26,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e,
zf48d7e43ff);__CAT(zf901b7d7e1,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,
zdcec0d15c5->z9e92215ca6,zdcec0d15c5->z4bc2586276,z7ec2813c96);for(zce99d8264d=
(0x11cc+3491-0x1f6f);zce99d8264d<zdcec0d15c5->z4eeebcd909;zce99d8264d++)_bstate(
zce99d8264d+zdcec0d15c5->z90bbed6de0)+=zdcec0d15c5->z4bc2586276[zce99d8264d];
z6fd7c833c1++;if(__CAT(z5d747ed95f,)(zb425515a78,zfb02fbb98b,
z6952f3187e,zdcec0d15c5->z4bc2586276,zdcec0d15c5->z34b6b98586,zdcec0d15c5->
z4eeebcd909,zdcec0d15c5->z90bbed6de0,&zdc8d9bb183))return(0x128d+144-0x131d);if(
z9439e49293*z6952f3187e->ze59e1c0f65<zdc8d9bb183)return(0xd49+3620-0x1b6b);if(
__CAT(z8b17e620d6,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e,
zf48d7e43ff)>(0xe73+2182-0x16f9))return(0x52f+6011-0x1ca8);return
(0xf02+2435-0x1885);}ITI_uint __CAT(z8401db3b7b,)(void*zb425515a78,
void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*z6952f3187e,
void*zf48d7e43ff){z7529d16d33 z1d6d302708 ITI_uint z6fcd5db760=
(0x14d3+1408-0x1a51);__CAT(zf29e330b26,)(zb425515a78,zfb02fbb98b,
zdcec0d15c5,z6952f3187e,zf48d7e43ff);if(__CAT(z97f5bd8a23,)(
zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e,zf48d7e43ff)>(0x71+4558-0x123f))
{ITI_char zea4cd01646[(0xf2b+279-0xf43)];sprintf(zea4cd01646,
"\x45\x72\x72\x6f\x72\x3a\x20\x54\x61\x6e\x67\x65\x6e\x74\x20\x63\x6f\x6d\x70\x75\x74\x61\x74\x69\x6f\x6e\x20\x66\x61\x69\x6c\x73\x20\x66\x6f\x72\x20\x6c\x61\x6d\x62\x64\x61\x48\x6f\x6d\x6f\x74\x6f\x70\x79\x3d\x25\x2d\x2e\x31\x37\x67\x2e" "\n"
,_bstate(zdcec0d15c5->z90bbed6de0));traceWarning(zea4cd01646,&_sInfo);return
(0x6ec+6785-0x216c);}__CAT(z097b6f9bf5,)(zdcec0d15c5,z6952f3187e);if(
z6952f3187e->z0466e2bdbb>z6952f3187e->zfdee43babc)return(0x8d+7697-0x1e9c);
return __CAT(z82aef60b72,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,
z6952f3187e,zf48d7e43ff,z6fcd5db760);}ITI_real __CAT(z62f48093a2,)(
void*zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,
ITI_EmbeddingParams*z6952f3187e,void*zf48d7e43ff){z7529d16d33 z1d6d302708 
ITI_real z988292fecc;ITI_real zd3919aa600,z73789d311b;ITI_real z52754d10b7,
z84df455267;ITI_uint zce99d8264d;zdcec0d15c5->z3f01d343c0=1.0;z6ccc5f5e83 for(
zce99d8264d=(0xef2+3818-0x1ddc);zce99d8264d<zdcec0d15c5->z4eeebcd909;zce99d8264d
++)_bstate(zce99d8264d+zdcec0d15c5->z90bbed6de0)+=zdcec0d15c5->z4bc2586276[
zce99d8264d];__CAT(zf29e330b26,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,
z6952f3187e,zf48d7e43ff);z5e407f1d0d zd3919aa600=__CAT(z8315707fda,)(
zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e);
#ifdef ITI_COMP_SIM
z988292fecc=__CAT(ze7161a9726,)(z6952f3187e,zdcec0d15c5->z4bc2586276,
pPart->transient->bx,zdcec0d15c5->z4eeebcd909,zdcec0d15c5->z90bbed6de0);
#elif defined _EMI_HOMOTOPY
z988292fecc=__CAT(z66842ef5f7,)(z6952f3187e,zdcec0d15c5->z4bc2586276,
((ITI_real*)emcGetPWork(__C)[(0x21d+2965-0xda4)]),zdcec0d15c5->z4eeebcd909,
zdcec0d15c5->z90bbed6de0);
#else
z988292fecc=__CAT(z66842ef5f7,)(z6952f3187e,zdcec0d15c5->z4bc2586276,
pPart->transient->bx,zdcec0d15c5->z4eeebcd909,zdcec0d15c5->z90bbed6de0);
#endif
if(zd3919aa600<=z6952f3187e->ze59e1c0f65*z988292fecc)return zd3919aa600;
zdcec0d15c5->z3f01d343c0=min(max(z6952f3187e->za49a3a96d0,0.5*z988292fecc/
zd3919aa600),0.7*zdcec0d15c5->z3f01d343c0);z6ccc5f5e83 for(zce99d8264d=
(0xdfb+405-0xf90);zce99d8264d<zdcec0d15c5->z4eeebcd909;zce99d8264d++)_bstate(
zce99d8264d+zdcec0d15c5->z90bbed6de0)+=zdcec0d15c5->z3f01d343c0*zdcec0d15c5->
z4bc2586276[zce99d8264d];__CAT(zf29e330b26,)(zb425515a78,zfb02fbb98b,
zdcec0d15c5,z6952f3187e,zf48d7e43ff);z5e407f1d0d z73789d311b=__CAT(z8315707fda,
)(zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e);if(z73789d311b<=
z6952f3187e->ze59e1c0f65*z988292fecc)return z73789d311b;z52754d10b7=(z73789d311b
-z988292fecc*(1.0-zdcec0d15c5->z3f01d343c0)-zd3919aa600*int_pow(zdcec0d15c5->
z3f01d343c0,(0xef7+5050-0x22ae)))/(int_pow(zdcec0d15c5->z3f01d343c0,
(0x854+3545-0x162b))*(1.0-zdcec0d15c5->z3f01d343c0));z84df455267=-z52754d10b7/(
3.0*(zd3919aa600-z52754d10b7));zdcec0d15c5->z3f01d343c0=min(max(min(z84df455267+
sqrt(int_pow(z84df455267,(0x3d0+7450-0x20e8))+z988292fecc),z6952f3187e->
z6dbe734b84*zdcec0d15c5->z3f01d343c0),z6952f3187e->za49a3a96d0*zdcec0d15c5->
z3f01d343c0),0.7*zdcec0d15c5->z3f01d343c0);z6ccc5f5e83 for(zce99d8264d=
(0x16e3+1732-0x1da7);zce99d8264d<zdcec0d15c5->z4eeebcd909;zce99d8264d++)_bstate(
zce99d8264d+zdcec0d15c5->z90bbed6de0)+=zdcec0d15c5->z3f01d343c0*zdcec0d15c5->
z4bc2586276[zce99d8264d];__CAT(zf29e330b26,)(zb425515a78,zfb02fbb98b,
zdcec0d15c5,z6952f3187e,zf48d7e43ff);z5e407f1d0d return __CAT(z8315707fda,
)(zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e);}void __CAT(
z4320d07649,)(void*zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*
zdcec0d15c5,ITI_EmbeddingParams*z6952f3187e,void*zf48d7e43ff){z7529d16d33 
z1d6d302708 ITI_uint zce99d8264d,z26dbd73a5e,z812c65ff2f;ITI_real z7493f886db;
z6ccc5f5e83 CopyVars(zdcec0d15c5->z9e92215ca6,zdcec0d15c5->z8a73e5ac9c,
(0x12e7+2931-0x1e5a),zdcec0d15c5->z25f5c17222);for(zce99d8264d=
(0x56a+3602-0x137c);zce99d8264d<zdcec0d15c5->z4eeebcd909;zce99d8264d++){
z812c65ff2f=zce99d8264d+zdcec0d15c5->z90bbed6de0;z7493f886db=min(max(fabs(
_bstate(z812c65ff2f))*sqrt(DBL_EPSILON),z6952f3187e->zb389952bf4),__MAX_PERT);
_bstate(z812c65ff2f)+=z7493f886db;__CAT(zf29e330b26,)(zb425515a78,
zfb02fbb98b,zdcec0d15c5,z6952f3187e,zf48d7e43ff);for(z26dbd73a5e=
(0x1840+3749-0x26e5);z26dbd73a5e<zdcec0d15c5->z25f5c17222;z26dbd73a5e++)
zdcec0d15c5->z3960d6c10a[zce99d8264d*zdcec0d15c5->z25f5c17222+z26dbd73a5e]=(
zdcec0d15c5->z9e92215ca6[z26dbd73a5e]-zdcec0d15c5->z8a73e5ac9c[z26dbd73a5e])/
z7493f886db;_bstate(z812c65ff2f)=zdcec0d15c5->bx_tmp[z812c65ff2f];}z5e407f1d0d 
_sInfo.isEmbed=(0xdb5+6380-0x269e);__CAT(zf29e330b26,)(zb425515a78,
zfb02fbb98b,zdcec0d15c5,z6952f3187e,zf48d7e43ff);_sInfo.isEmbed=
(0x54f+309-0x682);}void __CAT(zf29e330b26,)(void*zb425515a78,void*
zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*z6952f3187e,void*
zf48d7e43ff){z15f3b3f7db z7529d16d33 z1d6d302708 ITI_ModelFunctions*model=(
ITI_ModelFunctions*)zf48d7e43ff;
#ifdef _EMI_HOMOTOPY
ITI_real z3f082f8bdc[pPart->transient->size.z600a6fd606+(0x1ac9+1975-0x227f)];
ITI_real*zf=&(emcGetRWork(__C)[pPart->transient->size.zbf83df116e]);emcGetPWork(
__C)[(0x1819+2841-0x2320)]=(ITI_void*)zdcec0d15c5->z9e92215ca6;emcGetPWork(__C)[
(0x329+1159-0x79d)]=(ITI_void*)zdcec0d15c5->z3960d6c10a;
#else
modelData->hom_res=zdcec0d15c5->z9e92215ca6;modelData->hom_jac=zdcec0d15c5->
z3960d6c10a;
#endif
zb1f36b2499}ITI_int __CAT(z6d34c7efdb,)(void*zb425515a78,void*
zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*z6952f3187e,void*
zf48d7e43ff){z7529d16d33 z1d6d302708 ITI_uint z43bff7bac5=(0x4f6+1280-0x9f6);if(
!__CAT(z5669ea4bf3,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e,
zf48d7e43ff,(0xc11+3927-0x1b68))){ITI_uint zce99d8264d;for(zce99d8264d=
(0x1c43+303-0x1d72);zce99d8264d<zdcec0d15c5->z4eeebcd909;zce99d8264d++)
zdcec0d15c5->z417a4f498b[zce99d8264d]=_bstate(zce99d8264d+zdcec0d15c5->
z90bbed6de0);for(z43bff7bac5++;z43bff7bac5!=z6952f3187e->zc72a658dd9;z43bff7bac5
++){z6952f3187e->zcb80911ce0=(0x12d5+820-0x1609);if(__CAT(z85035d0bf5,
)(zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e,zf48d7e43ff)>
(0x16d3+777-0x19dc)){z6952f3187e->zcb80911ce0=(0x1f31+1286-0x2436);break;}else 
if(__CAT(z5669ea4bf3,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,
z6952f3187e,zf48d7e43ff,(0xbcc+1886-0x1329))){z6952f3187e->zcb80911ce0=
(0x6ab+6914-0x21ad);z6952f3187e->ze954f3cce4=z6952f3187e->z5c954d713f;break;}}if
(z43bff7bac5==z6952f3187e->zc72a658dd9){--z43bff7bac5;z6952f3187e->zcb80911ce0=
(0x1aa1+918-0x1e36);}if(z6952f3187e->zcb80911ce0){for(zce99d8264d=
(0x1924+80-0x1974);zce99d8264d<zdcec0d15c5->z4eeebcd909;zce99d8264d++)_bstate(
zce99d8264d+zdcec0d15c5->z90bbed6de0)=zdcec0d15c5->z8ccfbd4931[zce99d8264d];
__CAT(z5669ea4bf3,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,z6952f3187e,
zf48d7e43ff,(0x103+5665-0x1722));for(zce99d8264d=(0x26a+8326-0x22f0);zce99d8264d
<zdcec0d15c5->z4eeebcd909;zce99d8264d++)_bstate(zce99d8264d+zdcec0d15c5->
z90bbed6de0)=zdcec0d15c5->z417a4f498b[zce99d8264d];return-(0x16e8+126-0x1765);}}
return z43bff7bac5;}ITI_uint __CAT(z5669ea4bf3,)(void*zb425515a78,
void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*z6952f3187e,
void*zf48d7e43ff,ITI_uint z00f6ed1d9c){z7529d16d33 z1d6d302708 ITI_uint 
zb12cd23f9f=(0x6fc+55-0x733);switch(z00f6ed1d9c){case(0x73c+7932-0x2638):
zb12cd23f9f=__CAT(z5650878f4b,)(zb425515a78,zfb02fbb98b,zdcec0d15c5);
if(zb12cd23f9f){ITI_real z1e07cd0a35=1.0;ITI_real zb2913d8fa6=0.99;ITI_int 
z4c0d9ada56;for(z4c0d9ada56=(0x925+348-0xa81);z4c0d9ada56<pPart->transient->size
.izf;++z4c0d9ada56){if((zdcec0d15c5->z09e05a7a6d[z4c0d9ada56]<0.0&&zdcec0d15c5->
ze957e2faee[z4c0d9ada56]>0.0)||(zdcec0d15c5->z09e05a7a6d[z4c0d9ada56]>0.0&&
zdcec0d15c5->ze957e2faee[z4c0d9ada56]<0.0)){ITI_real z7ada113a3a=zdcec0d15c5->
ze957e2faee[z4c0d9ada56]/(zdcec0d15c5->ze957e2faee[z4c0d9ada56]-zdcec0d15c5->
z09e05a7a6d[z4c0d9ada56]);if(fabs(z7ada113a3a)<z1e07cd0a35)z1e07cd0a35=fabs(
z7ada113a3a);}}if(z1e07cd0a35<1.0)zb2913d8fa6=0.9*z1e07cd0a35;if(zb2913d8fa6>0.0
){z6952f3187e->zcb80911ce0=(0x91f+3200-0x159e);z6952f3187e->ze954f3cce4=max(
z6952f3187e->z95f376aec4,min(0.99*z6952f3187e->ze954f3cce4,zb2913d8fa6*__CAT(
z224a93e97c,)(zb425515a78,zfb02fbb98b,zdcec0d15c5)));}}break;case
(0x18d1+3550-0x26ae):zb12cd23f9f=__CAT(z5650878f4b,)(zb425515a78,
zfb02fbb98b,zdcec0d15c5);break;case(0x35a+4497-0x14e9):{ITI_int z4c0d9ada56;for(
z4c0d9ada56=(0x1e32+1442-0x23d4);z4c0d9ada56<pPart->transient->size.izf;++
z4c0d9ada56)zdcec0d15c5->zed744e2941[z4c0d9ada56]=zdcec0d15c5->ze957e2faee[
z4c0d9ada56];zb12cd23f9f=(0xa1a+5703-0x2060);break;}}if(zb12cd23f9f){_sInfo.
isEvent=ITI_true;__CAT(zf29e330b26,)(zb425515a78,zfb02fbb98b,
zdcec0d15c5,z6952f3187e,zf48d7e43ff);Update_pre_z_data(zb425515a78,zfb02fbb98b);
_sInfo.isEvent=ITI_false;}else __CAT(z1fe51ea564,)(zb425515a78,
zfb02fbb98b,zdcec0d15c5->ze957e2faee);return zb12cd23f9f==(0x1724+3901-0x2661)?
(0x218+7347-0x1eca):(0x8ba+5368-0x1db2);}ITI_uint __CAT(z5650878f4b,)
(void*zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5){z7529d16d33 
z1d6d302708 ITI_int z4c0d9ada56;ITI_uint zb12cd23f9f=(0x1283+4980-0x25f7);__CAT(
z1fe51ea564,)(zb425515a78,zfb02fbb98b,zdcec0d15c5->z09e05a7a6d);for(
z4c0d9ada56=(0xa92+4500-0x1c26);z4c0d9ada56<pPart->transient->size.izf;++
z4c0d9ada56){if((zdcec0d15c5->z09e05a7a6d[z4c0d9ada56]<0.0&&zdcec0d15c5->
zed744e2941[z4c0d9ada56]>=0.0)||(zdcec0d15c5->z09e05a7a6d[z4c0d9ada56]>0.0&&
zdcec0d15c5->zed744e2941[z4c0d9ada56]<=0.0))zb12cd23f9f=(0x627+4540-0x17e2);
zdcec0d15c5->zed744e2941[z4c0d9ada56]=zdcec0d15c5->z09e05a7a6d[z4c0d9ada56];}
return zb12cd23f9f;}void __CAT(z1fe51ea564,)(void*zb425515a78,void*
zfb02fbb98b,ITI_real*z09e05a7a6d){z7529d16d33 z1d6d302708 ITI_int z4c0d9ada56;
for(z4c0d9ada56=(0x925+6950-0x244b);z4c0d9ada56<pPart->transient->size.izf;++
z4c0d9ada56){
#ifdef _EMI_HOMOTOPY
#else
z09e05a7a6d[z4c0d9ada56]=pPart->transient->zf[z4c0d9ada56];
#endif
}}void __CAT(z1faac1090f,)(void*zb425515a78,void*zfb02fbb98b,
ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*z6952f3187e){z7529d16d33 
z1d6d302708 ITI_uint zce99d8264d,ze8cf17c11e,z760cb77366=(0x40d+3509-0x11c2);
ITI_real*zbd05723d83=(ITI_real*)calloc(zdcec0d15c5->z4eeebcd909,sizeof(ITI_real)
);for(zce99d8264d=(0xc64+5505-0x21e4);zce99d8264d<zdcec0d15c5->z4eeebcd909;
zce99d8264d++){if(_bstate(zce99d8264d+zdcec0d15c5->z90bbed6de0)>zdcec0d15c5->
z4c54a1eefd[zce99d8264d])zdcec0d15c5->z4c54a1eefd[zce99d8264d]=zdcec0d15c5->
ze94ec32586[zce99d8264d]+z6952f3187e->z81339bb7b3*(_bstate(zce99d8264d+
zdcec0d15c5->z90bbed6de0)-zdcec0d15c5->ze94ec32586[zce99d8264d]);else if(_bstate
(zce99d8264d+zdcec0d15c5->z90bbed6de0)<zdcec0d15c5->ze94ec32586[zce99d8264d])
zdcec0d15c5->ze94ec32586[zce99d8264d]=zdcec0d15c5->z4c54a1eefd[zce99d8264d]+
z6952f3187e->z81339bb7b3*(_bstate(zce99d8264d+zdcec0d15c5->z90bbed6de0)-
zdcec0d15c5->z4c54a1eefd[zce99d8264d]);else continue;if(zdcec0d15c5->z34b6b98586
[zce99d8264d]*(zdcec0d15c5->z4c54a1eefd[zce99d8264d]-zdcec0d15c5->ze94ec32586[
zce99d8264d])>1.0){if(!z760cb77366){ITI_real z26505f5082=__CAT(zab7ffcf1ba,
)(zdcec0d15c5->z8a41d0006a,zdcec0d15c5->z34b6b98586,zdcec0d15c5->
z4eeebcd909);if(z26505f5082<DBL_EPSILON){ITI_char zea4cd01646[
(0x1a56+3174-0x25bd)];sprintf(zea4cd01646,
"\x54\x68\x65\x20\x63\x6f\x6d\x70\x75\x74\x65\x64\x20\x74\x61\x6e\x67\x65\x6e\x74\x20\x76\x65\x63\x74\x6f\x72\x20\x6f\x66\x20\x74\x68\x65\x20\x65\x6d\x62\x65\x64\x64\x69\x6e\x67\x20\x70\x61\x74\x68\x20\x68\x61\x73\x20\x7a\x65\x72\x6f\x20\x6c\x65\x6e\x67\x74\x68\x20\x61\x74\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x20\x76\x61\x6c\x75\x65\x20\x25\x65\x2e"
,_bstate(zdcec0d15c5->z90bbed6de0));traceWarning(zea4cd01646,&_sInfo);for(
ze8cf17c11e=(0xb2a+3703-0x19a1);ze8cf17c11e<zdcec0d15c5->z4eeebcd909;ze8cf17c11e
++)zbd05723d83[ze8cf17c11e]=z6952f3187e->ze954f3cce4*zdcec0d15c5->z8a41d0006a[
ze8cf17c11e]/DBL_EPSILON;}else{for(ze8cf17c11e=(0x3a5+8252-0x23e1);ze8cf17c11e<
zdcec0d15c5->z4eeebcd909;ze8cf17c11e++)zbd05723d83[ze8cf17c11e]=z6952f3187e->
ze954f3cce4*zdcec0d15c5->z8a41d0006a[ze8cf17c11e]/z26505f5082;}}zdcec0d15c5->
z34b6b98586[zce99d8264d]=max((0x207+8840-0x248e)/(zdcec0d15c5->z4c54a1eefd[
zce99d8264d]-zdcec0d15c5->ze94ec32586[zce99d8264d]),zdcec0d15c5->zf4ae93b057[
zce99d8264d]);z760cb77366=(0x1a3+7092-0x1d56);}}if(z760cb77366){z6952f3187e->
ze954f3cce4=__CAT(zab7ffcf1ba,)(zbd05723d83,zdcec0d15c5->z34b6b98586,
zdcec0d15c5->z4eeebcd909);z6952f3187e->zc55b8fab64=min(z6952f3187e->z95f376aec4,
z6952f3187e->ze954f3cce4);}free(zbd05723d83);}void __CAT(z4bc25bef61,
)(ITI_real*a,ITI_real*b,ITI_uint z1581844784){ITI_uint zce99d8264d;for(
zce99d8264d=(0x43+3189-0xcb8);zce99d8264d<z1581844784;zce99d8264d++)a[
zce99d8264d]/=b[zce99d8264d];}void __CAT(z11cd768e30,)(ITI_real*a,
ITI_real z1437e7d647,ITI_uint z1581844784){ITI_uint zce99d8264d;for(zce99d8264d=
(0x1acb+2180-0x234f);zce99d8264d<z1581844784;zce99d8264d++)a[zce99d8264d]*=
z1437e7d647;}ITI_uint __CAT(z6474127c41,)(void*zb425515a78,void*
zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5){z7529d16d33 z1d6d302708 if(__CAT(
z5551e92655,)(zdcec0d15c5)>(0x167c+3454-0x23fa)){ITI_char zea4cd01646
[(0x1d43+1480-0x220c)];sprintf(zea4cd01646,
"\x45\x72\x72\x6f\x72\x3a\x20\x53\x56\x44\x20\x64\x65\x63\x6f\x6d\x70\x6f\x73\x69\x74\x69\x6f\x6e\x20\x66\x61\x69\x6c\x73\x20\x66\x6f\x72\x20\x6c\x61\x6d\x62\x64\x61\x48\x6f\x6d\x6f\x74\x6f\x70\x79\x20\x3d\x20\x25\x2d\x2e\x31\x37\x67\x2e" "\n"
,_bstate(zdcec0d15c5->z90bbed6de0));traceWarning(zea4cd01646,&_sInfo);return
(0xe74+235-0xf5e);}if(zdcec0d15c5->zf08be7baa7[(0x3b0+1379-0x913)]==0.0)
zdcec0d15c5->z7663004f47=(0x8d+5370-0x1587);else{ITI_uint zce99d8264d=min(
zdcec0d15c5->z25f5c17222,zdcec0d15c5->z4eeebcd909);while((zce99d8264d>
(0x1cdd+1459-0x2290))&&(zdcec0d15c5->zf08be7baa7[zce99d8264d-(0x7+9468-0x2502)]<
10.0*DBL_EPSILON*zdcec0d15c5->zf08be7baa7[(0x119b+4099-0x219e)]))zce99d8264d--;
zdcec0d15c5->z7663004f47=zce99d8264d;}if(zdcec0d15c5->z7663004f47>=zdcec0d15c5->
z4eeebcd909){ITI_char zea4cd01646[(0x114f+2100-0x1884)];sprintf(zea4cd01646,
"\x45\x72\x72\x6f\x72\x3a\x20\x4b\x65\x72\x6e\x65\x6c\x20\x6f\x66\x20\x74\x68\x65\x20\x4a\x61\x63\x6f\x62\x69\x61\x6e\x20\x64\x6f\x65\x73\x20\x6e\x6f\x74\x20\x65\x78\x69\x73\x74\x20\x66\x6f\x72\x20\x6c\x61\x6d\x62\x64\x61\x48\x6f\x6d\x6f\x74\x6f\x70\x79\x20\x3d\x20\x25\x2d\x2e\x31\x37\x67\x2e" "\n"
,_bstate(zdcec0d15c5->z90bbed6de0));traceWarning(zea4cd01646,&_sInfo);return
(0x7d7+5681-0x1e07);}return(0x9b+4697-0x12f4);}void __CAT(z54d9b09da9,
)(ITI_EmbeddingData*zdcec0d15c5,ITI_real*z9e92215ca6,ITI_real*
zbd05723d83){ITI_uint zce99d8264d,z26dbd73a5e;ITI_uint z1581844784=zdcec0d15c5->
z4eeebcd909;ITI_uint z77c4719614=zdcec0d15c5->z25f5c17222;memset((void*)
zdcec0d15c5->z8d4186ad41,(0x1323+2639-0x1d72),zdcec0d15c5->z7663004f47*sizeof(
ITI_real));memset((void*)zbd05723d83,(0xdb5+781-0x10c2),z1581844784*sizeof(
ITI_real));for(zce99d8264d=(0xcac+4924-0x1fe8);zce99d8264d<z77c4719614;
zce99d8264d++)for(z26dbd73a5e=(0x1736+1154-0x1bb8);z26dbd73a5e<z77c4719614;
z26dbd73a5e++)zdcec0d15c5->z8d4186ad41[zce99d8264d]+=zdcec0d15c5->z03e5515547[
zce99d8264d*z77c4719614+z26dbd73a5e]*z9e92215ca6[z26dbd73a5e];for(zce99d8264d=
(0x42+7249-0x1c93);zce99d8264d<zdcec0d15c5->z7663004f47;zce99d8264d++)
zdcec0d15c5->z8d4186ad41[zce99d8264d]/=zdcec0d15c5->zf08be7baa7[zce99d8264d];for
(zce99d8264d=zdcec0d15c5->z7663004f47;zce99d8264d<z1581844784;zce99d8264d++)
zdcec0d15c5->z8d4186ad41[zce99d8264d]=0.0;for(zce99d8264d=(0x382+5680-0x19b2);
zce99d8264d<z1581844784;zce99d8264d++)for(z26dbd73a5e=(0x4fa+3705-0x1373);
z26dbd73a5e<z1581844784;z26dbd73a5e++)zbd05723d83[zce99d8264d]+=zdcec0d15c5->
z6473e0bce5[zce99d8264d*z1581844784+z26dbd73a5e]*zdcec0d15c5->z8d4186ad41[
z26dbd73a5e];}ITI_uint __CAT(z5551e92655,)(ITI_EmbeddingData*
zdcec0d15c5){ITI_int zbcd06d4a67;ITI_int m=zdcec0d15c5->z25f5c17222;ITI_int n=
zdcec0d15c5->z4eeebcd909;ITI_char zf325a54eb5=((char)(0x1152+5044-0x24c5));
ITI_char z68981c957f=((char)(0x1c8+4653-0x13b4));memset((void*)zdcec0d15c5->work
,(0xfa0+1243-0x147b),zdcec0d15c5->lwork*sizeof(ITI_real));dgesvd_(&zf325a54eb5,&
z68981c957f,&m,&n,zdcec0d15c5->z3960d6c10a,&m,zdcec0d15c5->zf08be7baa7,
zdcec0d15c5->z03e5515547,&m,zdcec0d15c5->z6473e0bce5,&n,zdcec0d15c5->work,&
zdcec0d15c5->lwork,&zbcd06d4a67);return zbcd06d4a67;}ITI_real __CAT(zb82f30584a,
)(ITI_real*z7b058c25be,ITI_real*z6e0310fb34,ITI_real*zf667805127,
ITI_uint z1581844784){ITI_real z3c32d4e665=__CAT(z9383ee8374,)(
z7b058c25be,z6e0310fb34,zf667805127,z1581844784);ITI_real zb0d9bb9d1a=__CAT(
zab7ffcf1ba,)(z7b058c25be,zf667805127,z1581844784)*__CAT(zab7ffcf1ba,
)(z6e0310fb34,zf667805127,z1581844784);if((zb0d9bb9d1a>=DBL_MIN)&&(
fabs(z3c32d4e665)<zb0d9bb9d1a))return acos(z3c32d4e665/zb0d9bb9d1a);else if(
z3c32d4e665<=-zb0d9bb9d1a)return 2.0*acos(0.);else return 0.0;}ITI_real __CAT(
z9383ee8374,)(ITI_real*z7b058c25be,ITI_real*z6e0310fb34,ITI_real*
zf667805127,ITI_uint z1581844784){ITI_uint zce99d8264d;ITI_real z7be9105675;
ITI_real zdb5468ea8f=0.0;for(zce99d8264d=(0x12cd+233-0x13b6);zce99d8264d<
z1581844784;zce99d8264d++){z7be9105675=zf667805127[zce99d8264d]*zf667805127[
zce99d8264d];zdb5468ea8f+=z7b058c25be[zce99d8264d]*z6e0310fb34[zce99d8264d]*
z7be9105675;}return zdb5468ea8f;}ITI_real __CAT(z224a93e97c,)(void*
zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5){z7529d16d33 
z1d6d302708 ITI_uint zce99d8264d;ITI_real z5e26adef18=0.;for(zce99d8264d=
(0x1d85+1316-0x22a9);zce99d8264d<zdcec0d15c5->z4eeebcd909;zce99d8264d++)
z5e26adef18=max(z5e26adef18,fabs(zdcec0d15c5->z34b6b98586[zce99d8264d]*(_bstate(
zdcec0d15c5->z90bbed6de0+zce99d8264d)-zdcec0d15c5->z8ccfbd4931[zce99d8264d])));
if(z5e26adef18!=0.){ITI_real z6fcd2c121f=0.;for(zce99d8264d=(0x1801+2861-0x232e)
;zce99d8264d<zdcec0d15c5->z4eeebcd909;zce99d8264d++){ITI_real z7be9105675=((
zdcec0d15c5->z34b6b98586[zce99d8264d]*(_bstate(zdcec0d15c5->z90bbed6de0+
zce99d8264d)-zdcec0d15c5->z8ccfbd4931[zce99d8264d]))/z5e26adef18);z6fcd2c121f+=
z7be9105675*z7be9105675;}z5e26adef18*=sqrt(z6fcd2c121f);}return z5e26adef18;}
ITI_real __CAT(zab7ffcf1ba,)(ITI_real*za04057655a,ITI_real*
z82425fa37c,ITI_uint z1581844784){ITI_uint zce99d8264d;ITI_real z5e26adef18=0.;
for(zce99d8264d=(0x563+5005-0x18f0);zce99d8264d<z1581844784;zce99d8264d++)
z5e26adef18=max(z5e26adef18,fabs(za04057655a[zce99d8264d]*z82425fa37c[
zce99d8264d]));if(z5e26adef18!=0.){ITI_real z6fcd2c121f=0.;for(zce99d8264d=
(0xe12+1368-0x136a);zce99d8264d<z1581844784;zce99d8264d++){ITI_real z7be9105675=
((za04057655a[zce99d8264d]*z82425fa37c[zce99d8264d])/z5e26adef18);z6fcd2c121f+=
z7be9105675*z7be9105675;}z5e26adef18*=sqrt(z6fcd2c121f);}return z5e26adef18;}
ITI_real __CAT(z48766ede72,)(ITI_real*za04057655a,ITI_real*
z82425fa37c,ITI_uint z1581844784,ITI_uint zf1cdc30602){ITI_uint zce99d8264d;
ITI_real z5e26adef18=0.0;for(zce99d8264d=(0x121b+4459-0x2386);zce99d8264d<
z1581844784;zce99d8264d++)z5e26adef18=max(z5e26adef18,fabs(za04057655a[
zce99d8264d+zf1cdc30602]*z82425fa37c[zce99d8264d]));if(z5e26adef18!=0.){ITI_real
 z6fcd2c121f=0.;for(zce99d8264d=(0x64b+6792-0x20d3);zce99d8264d<z1581844784;
zce99d8264d++){ITI_real z7be9105675=((za04057655a[zce99d8264d+zf1cdc30602]*
z82425fa37c[zce99d8264d])/z5e26adef18);z6fcd2c121f+=z7be9105675*z7be9105675;}
z5e26adef18*=sqrt(z6fcd2c121f);}return z5e26adef18;}ITI_real __CAT(zc1c3f4c2b5,
)(ITI_real**za04057655a,ITI_real*z82425fa37c,ITI_uint z1581844784,
ITI_uint zf1cdc30602){ITI_uint zce99d8264d;ITI_real z5e26adef18=0.0;for(
zce99d8264d=(0x1910+3406-0x265e);zce99d8264d<z1581844784;zce99d8264d++)
z5e26adef18=max(z5e26adef18,fabs(*za04057655a[zce99d8264d+zf1cdc30602]*
z82425fa37c[zce99d8264d]));if(z5e26adef18!=0.){ITI_real z6fcd2c121f=0.;for(
zce99d8264d=(0x1e7d+1421-0x240a);zce99d8264d<z1581844784;zce99d8264d++){ITI_real
 z7be9105675=((*za04057655a[zce99d8264d+zf1cdc30602]*z82425fa37c[zce99d8264d])/
z5e26adef18);z6fcd2c121f+=z7be9105675*z7be9105675;}z5e26adef18*=sqrt(z6fcd2c121f
);}return z5e26adef18;}ITI_real __CAT(z66842ef5f7,)(
ITI_EmbeddingParams*z6952f3187e,ITI_real*z3f082f8bdc,ITI_real*za04057655a,
ITI_uint z1581844784,ITI_uint zf1cdc30602){ITI_uint zce99d8264d;ITI_real 
z5e26adef18=0.0;for(zce99d8264d=(0xa97+1217-0xf58);zce99d8264d<z1581844784;
zce99d8264d++)z5e26adef18=max(z5e26adef18,fabs(z3f082f8bdc[zce99d8264d]/(
z6952f3187e->zb389952bf4+z6952f3187e->z298a09d9bc*fabs(za04057655a[zce99d8264d+
zf1cdc30602]))));if(z5e26adef18!=0.){ITI_real z6fcd2c121f=0.;for(zce99d8264d=
(0x846+872-0xbae);zce99d8264d<z1581844784;zce99d8264d++){ITI_real z7be9105675=(
z3f082f8bdc[zce99d8264d]/(z6952f3187e->zb389952bf4+z6952f3187e->z298a09d9bc*fabs
(za04057655a[zce99d8264d+zf1cdc30602])))/z5e26adef18;z6fcd2c121f+=z7be9105675*
z7be9105675;}z5e26adef18*=sqrt(z6fcd2c121f);}return z5e26adef18;}ITI_real __CAT(
ze7161a9726,)(ITI_EmbeddingParams*z6952f3187e,ITI_real*z3f082f8bdc,
ITI_real**za04057655a,ITI_uint z1581844784,ITI_uint zf1cdc30602){ITI_uint 
zce99d8264d;ITI_real z5e26adef18=0.;for(zce99d8264d=(0x1338+850-0x168a);
zce99d8264d<z1581844784;zce99d8264d++)z5e26adef18=max(z5e26adef18,fabs(
z3f082f8bdc[zce99d8264d]/(z6952f3187e->zb389952bf4+z6952f3187e->z298a09d9bc*fabs
(*za04057655a[zce99d8264d+zf1cdc30602]))));if(z5e26adef18!=0.){ITI_real 
z6fcd2c121f=0.;for(zce99d8264d=(0x1a7+562-0x3d9);zce99d8264d<z1581844784;
zce99d8264d++){ITI_real z7be9105675=(z3f082f8bdc[zce99d8264d]/(z6952f3187e->
zb389952bf4+z6952f3187e->z298a09d9bc*fabs(*za04057655a[zce99d8264d+zf1cdc30602])
))/z5e26adef18;z6fcd2c121f+=z7be9105675*z7be9105675;}z5e26adef18*=sqrt(
z6fcd2c121f);}return z5e26adef18;}ITI_real __CAT(z8315707fda,)(void*
zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*
z6952f3187e){z7529d16d33 z1d6d302708 ITI_uint zce99d8264d;ITI_uint z7ec2813c96=
(0x1a55+2515-0x2428);for(zce99d8264d=(0xc7+6001-0x1838);zce99d8264d<zdcec0d15c5
->z4eeebcd909;zce99d8264d++)zdcec0d15c5->ze7514d6a7f[zce99d8264d]=0.0;__CAT(
zf901b7d7e1,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,zdcec0d15c5->
z9e92215ca6,zdcec0d15c5->ze7514d6a7f,z7ec2813c96);
#ifdef ITI_COMP_SIM
return __CAT(ze7161a9726,)(z6952f3187e,zdcec0d15c5->ze7514d6a7f,pPart
->transient->bx,zdcec0d15c5->z4eeebcd909,zdcec0d15c5->z90bbed6de0);
#elif defined _EMI_HOMOTOPY
return __CAT(z66842ef5f7,)(z6952f3187e,zdcec0d15c5->ze7514d6a7f,((
ITI_real*)emcGetPWork(__C)[(0x2f0+3088-0xef2)]),zdcec0d15c5->z4eeebcd909,
zdcec0d15c5->z90bbed6de0);
#else
return __CAT(z66842ef5f7,)(z6952f3187e,zdcec0d15c5->ze7514d6a7f,pPart
->transient->bx,zdcec0d15c5->z4eeebcd909,zdcec0d15c5->z90bbed6de0);
#endif
}ITI_uint __CAT(z5d747ed95f,)(void*zb425515a78,void*zfb02fbb98b,
ITI_EmbeddingParams*z6952f3187e,ITI_real*zbd05723d83,ITI_real*z82425fa37c,
ITI_uint z1581844784,ITI_uint zf1cdc30602,ITI_real*z9439e49293){z7529d16d33 
z1d6d302708 ITI_real za26b66afdf;
#ifdef ITI_COMP_SIM
za26b66afdf=__CAT(zc1c3f4c2b5,)(pPart->transient->bx,z82425fa37c,
z1581844784,zf1cdc30602);
#elif defined _EMI_HOMOTOPY
za26b66afdf=__CAT(z48766ede72,)(((ITI_real*)emcGetPWork(__C)[
(0x1789+1624-0x1dd3)]),z82425fa37c,z1581844784,zf1cdc30602);
#else
za26b66afdf=__CAT(z48766ede72,)(pPart->transient->bx,z82425fa37c,
z1581844784,zf1cdc30602);
#endif
*z9439e49293=__CAT(zab7ffcf1ba,)(zbd05723d83,z82425fa37c,z1581844784)
;return(*z9439e49293<z6952f3187e->z298a09d9bc*za26b66afdf+z6952f3187e->
zb389952bf4);}void __CAT(zf901b7d7e1,)(void*zb425515a78,void*
zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_real*z9e92215ca6,ITI_real*
zbd05723d83,ITI_uint z7ec2813c96){z15f3b3f7db z7529d16d33 z1d6d302708 __CAT(
z54d9b09da9,)(zdcec0d15c5,z9e92215ca6,zbd05723d83);__CAT(z11cd768e30,
)(zbd05723d83,-1.0,zdcec0d15c5->z4eeebcd909);if(z7ec2813c96){if(__hmm
->considerLimit){__CAT(zb3da54817e,)(zb425515a78,zfb02fbb98b,
zdcec0d15c5,zbd05723d83);__CAT(z11cd768e30,)(zbd05723d83,zdcec0d15c5
->z72506057c6,zdcec0d15c5->z4eeebcd909);}}}void __CAT(zfa5fa8855f,)(
void*zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,
ITI_EmbeddingParams*z6952f3187e,ITI_int zaa5147cc6a,ITI_real zbd762e14d2){
z7529d16d33 z1d6d302708 ITI_uint zce99d8264d;if(z6952f3187e->z1a8d55b886){if(
zaa5147cc6a>=(0xad9+1735-0x11a0)){ITI_real z00a6472bbe=_bstate(zaa5147cc6a+
zdcec0d15c5->z90bbed6de0)-zdcec0d15c5->z8ccfbd4931[zaa5147cc6a];if(z00a6472bbe<
DBL_EPSILON){ITI_char zea4cd01646[(0x14d4+381-0x1552)];sprintf(zea4cd01646,
"\x54\x68\x65\x20\x63\x6f\x6d\x70\x75\x74\x65\x64\x20\x74\x61\x6e\x67\x65\x6e\x74\x20\x76\x65\x63\x74\x6f\x72\x20\x6f\x66\x20\x74\x68\x65\x20\x65\x6d\x62\x65\x64\x64\x69\x6e\x67\x20\x70\x61\x74\x68\x20\x68\x61\x73\x20\x7a\x65\x72\x6f\x20\x6c\x65\x6e\x67\x74\x68\x20\x61\x74\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x20\x76\x61\x6c\x75\x65\x20\x25\x65\x2e"
,zdcec0d15c5->z8ccfbd4931[zaa5147cc6a]);traceWarning(zea4cd01646,&_sInfo);__CAT(
zf162d5c8f1,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,zaa5147cc6a,
zbd762e14d2*zdcec0d15c5->z44a72f7bfb[zaa5147cc6a]/DBL_EPSILON);}else __CAT(
zf162d5c8f1,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,zaa5147cc6a,
zbd762e14d2*zdcec0d15c5->z44a72f7bfb[zaa5147cc6a]/z00a6472bbe);}else{ITI_real 
ze005fc796d=__CAT(z224a93e97c,)(zb425515a78,zfb02fbb98b,zdcec0d15c5);
__CAT(zf162d5c8f1,)(zb425515a78,zfb02fbb98b,zdcec0d15c5,zaa5147cc6a,
zbd762e14d2/ze005fc796d);}}else{ITI_real z26505f5082=__CAT(zab7ffcf1ba,
)(zdcec0d15c5->z44a72f7bfb,zdcec0d15c5->z34b6b98586,zdcec0d15c5->
z4eeebcd909);if(z26505f5082<DBL_EPSILON){ITI_char zea4cd01646[
(0x1437+4301-0x2405)];sprintf(zea4cd01646,
"\x54\x68\x65\x20\x63\x6f\x6d\x70\x75\x74\x65\x64\x20\x74\x61\x6e\x67\x65\x6e\x74\x20\x76\x65\x63\x74\x6f\x72\x20\x6f\x66\x20\x74\x68\x65\x20\x65\x6d\x62\x65\x64\x64\x69\x6e\x67\x20\x70\x61\x74\x68\x20\x68\x61\x73\x20\x7a\x65\x72\x6f\x20\x6c\x65\x6e\x67\x74\x68\x20\x61\x74\x20\x70\x61\x72\x61\x6d\x65\x74\x65\x72\x20\x76\x61\x6c\x75\x65\x20\x25\x65\x2e"
,zdcec0d15c5->z8ccfbd4931[(0x2145+1214-0x2603)]);traceWarning(zea4cd01646,&
_sInfo);}for(zce99d8264d=(0x1150+99-0x11b3);zce99d8264d<zdcec0d15c5->z4eeebcd909
;zce99d8264d++){if((z26505f5082<DBL_EPSILON)||(zaa5147cc6a>=(0x2e8+8503-0x241f))
)_bstate(zce99d8264d+zdcec0d15c5->z90bbed6de0)=zdcec0d15c5->z8ccfbd4931[
zce99d8264d]+zbd762e14d2*zdcec0d15c5->z44a72f7bfb[zce99d8264d];else _bstate(
zce99d8264d+zdcec0d15c5->z90bbed6de0)=zdcec0d15c5->z8ccfbd4931[zce99d8264d]+
zbd762e14d2*zdcec0d15c5->z44a72f7bfb[zce99d8264d]/z26505f5082;zdcec0d15c5->
z8a41d0006a[zce99d8264d]=zdcec0d15c5->z44a72f7bfb[zce99d8264d];}}z6952f3187e->
z1a8d55b886=(0x211c+1489-0x26ed);}void __CAT(zf162d5c8f1,)(void*
zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_int zaa5147cc6a,
ITI_real z82803ff4d1){z7529d16d33 z1d6d302708 ITI_uint zce99d8264d;ITI_real 
z705a029a29=__CAT(zab7ffcf1ba,)(zdcec0d15c5->z44a72f7bfb,zdcec0d15c5
->z34b6b98586,zdcec0d15c5->z4eeebcd909);ITI_real z17727c7045,zf81159d307,
z89f5814a4b,z1100b66e46,z8cf49f35be,zbb236df42a,z528e38ee4f,zc25b82582e,
z8b03b8bfd8,z72506057c6,z6fcd2c121f;for(zce99d8264d=(0x1edb+1021-0x22d8);
zce99d8264d<zdcec0d15c5->z4eeebcd909;zce99d8264d++){_bstate(zce99d8264d+
zdcec0d15c5->z90bbed6de0)-=zdcec0d15c5->z8ccfbd4931[zce99d8264d];}z17727c7045=
0.0;for(zce99d8264d=(0x207+8620-0x23b3);zce99d8264d<zdcec0d15c5->z4eeebcd909;
zce99d8264d++)z17727c7045=max(z17727c7045,fabs(_bstate(zdcec0d15c5->z90bbed6de0+
zce99d8264d)*zdcec0d15c5->z34b6b98586[zce99d8264d]));if(z17727c7045!=0.){
z6fcd2c121f=0.0;for(zce99d8264d=(0x1220+1197-0x16cd);zce99d8264d<zdcec0d15c5->
z4eeebcd909;zce99d8264d++){ITI_real z7be9105675=((_bstate(zdcec0d15c5->
z90bbed6de0+zce99d8264d)*zdcec0d15c5->z34b6b98586[zce99d8264d])/z17727c7045);
z6fcd2c121f+=z7be9105675*z7be9105675;}z17727c7045*=sqrt(z6fcd2c121f);}
zf81159d307=z17727c7045*z17727c7045;z6fcd2c121f=0.0;for(zce99d8264d=
(0xe94+3082-0x1a9e);zce99d8264d<zdcec0d15c5->z4eeebcd909;zce99d8264d++)
z6fcd2c121f+=_bstate(zdcec0d15c5->z90bbed6de0+zce99d8264d)*zdcec0d15c5->
z44a72f7bfb[zce99d8264d]*zdcec0d15c5->z34b6b98586[zce99d8264d]*zdcec0d15c5->
z34b6b98586[zce99d8264d];z89f5814a4b=z6fcd2c121f/z705a029a29;if(zaa5147cc6a>=
(0x4a+2440-0x9d2)){ITI_real z83faf7e699=zdcec0d15c5->z34b6b98586[zaa5147cc6a];
z83faf7e699*=z83faf7e699;z1100b66e46=z83faf7e699*zdcec0d15c5->z44a72f7bfb[
zaa5147cc6a]/z705a029a29;z8cf49f35be=z83faf7e699*_bstate(zaa5147cc6a+zdcec0d15c5
->z90bbed6de0);}else{z1100b66e46=z89f5814a4b;z8cf49f35be=zf81159d307;}
zbb236df42a=2.0*(zf81159d307-z89f5814a4b*z89f5814a4b);z528e38ee4f=sqrt(fabs(
zbb236df42a));zc25b82582e=0.5*z89f5814a4b;z8b03b8bfd8=zc25b82582e+z528e38ee4f;if
(fabs(0.5*z8cf49f35be)>fabs(z8b03b8bfd8*z1100b66e46))z72506057c6=z8b03b8bfd8;
else z72506057c6=0.5*z8cf49f35be/z1100b66e46;for(zce99d8264d=(0x77+7429-0x1d7c);
zce99d8264d<zdcec0d15c5->z4eeebcd909;zce99d8264d++){zdcec0d15c5->z8a41d0006a[
zce99d8264d]=_bstate(zce99d8264d+zdcec0d15c5->z90bbed6de0)*2.0*z82803ff4d1+
zdcec0d15c5->z44a72f7bfb[zce99d8264d]*2.0*z72506057c6*(1.0-2.0*z82803ff4d1)/
z705a029a29;_bstate(zce99d8264d+zdcec0d15c5->z90bbed6de0)=zdcec0d15c5->
z8ccfbd4931[zce99d8264d]+_bstate(zce99d8264d+zdcec0d15c5->z90bbed6de0)*
z82803ff4d1*z82803ff4d1+zdcec0d15c5->z44a72f7bfb[zce99d8264d]*2.0*z72506057c6*
z82803ff4d1*(1.0-z82803ff4d1)/z705a029a29;}}void __CAT(z828752be51,)(
void*zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,
ITI_EmbeddingParams*z6952f3187e){z7529d16d33 z1d6d302708 ITI_uint zce99d8264d;
for(zce99d8264d=(0xa4+9272-0x24dc);zce99d8264d<zdcec0d15c5->z4eeebcd909;
zce99d8264d++){zdcec0d15c5->z8ccfbd4931[zce99d8264d]=_bstate(zce99d8264d+
zdcec0d15c5->z90bbed6de0);zdcec0d15c5->z44a72f7bfb[zce99d8264d]=zdcec0d15c5->
z8a41d0006a[zce99d8264d];}zdcec0d15c5->z7450bac220=zdcec0d15c5->ze4482e84dd;
z6952f3187e->z1a8d55b886=(0x182+4887-0x1499);}void __CAT(zb3da54817e,
)(void*zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_real*
zbd05723d83){z15f3b3f7db z7529d16d33 z1d6d302708 ITI_uint zce99d8264d,
z26dbd73a5e;zdcec0d15c5->z72506057c6=1.0;for(zce99d8264d=(0x124+2254-0x9f1);
zce99d8264d<zdcec0d15c5->z4eeebcd909;++zce99d8264d){z26dbd73a5e=zce99d8264d+
zdcec0d15c5->z90bbed6de0;if((__hmm->considerMin[zce99d8264d])&&(_bstate(
z26dbd73a5e)+zbd05723d83[zce99d8264d]<=__hmm->minVal[zce99d8264d])){if(
zbd05723d83[zce99d8264d]!=0.0){ITI_char zea4cd01646[(0xd4f+6924-0x2667)];
zdcec0d15c5->z72506057c6=min(zdcec0d15c5->z72506057c6,0.5*((__hmm->minVal[
zce99d8264d]-_bstate(z26dbd73a5e))/zbd05723d83[zce99d8264d]));sprintf(
zea4cd01646,
"\x54\x68\x65\x20\x76\x61\x6c\x75\x65\x20\x25\x2d\x2e\x31\x37\x67\x20\x69\x73\x20\x62\x65\x6c\x6f\x77\x20\x74\x68\x65\x20\x6d\x69\x6e\x69\x6d\x75\x6d\x20\x28\x25\x2d\x2e\x31\x37\x67\x29\x20\x6f\x66\x20\x74\x68\x65\x20\x45\x6d\x62\x65\x64\x64\x69\x6e\x67\x20\x73\x74\x61\x74\x65\x20\x25\x73\x20\x28\x44\x61\x6d\x70\x69\x6e\x67\x20\x66\x61\x63\x74\x6f\x72\x3a\x20\x25\x2d\x2e\x31\x37\x67\x29\x2e"
,_bstate(z26dbd73a5e)+zbd05723d83[zce99d8264d],__hmm->minVal[zce99d8264d],__hmm
->name[zce99d8264d],0.5*((__hmm->minVal[zce99d8264d]-_bstate(z26dbd73a5e))/
zbd05723d83[zce99d8264d]));traceWarning(zea4cd01646,&_sInfo);}while((_bstate(
z26dbd73a5e)+zdcec0d15c5->z72506057c6*zbd05723d83[zce99d8264d]<=__hmm->minVal[
zce99d8264d])&&(zdcec0d15c5->z72506057c6!=0.0)){ITI_char zea4cd01646[
(0x336+2199-0xa3d)];zdcec0d15c5->z72506057c6/=10.0;sprintf(zea4cd01646,
"\x52\x65\x64\x75\x63\x69\x6e\x67\x20\x74\x68\x65\x20\x64\x61\x6d\x70\x69\x6e\x67\x20\x66\x61\x63\x74\x6f\x72\x20\x74\x6f\x20\x25\x2d\x2e\x31\x37\x67\x20\x62\x65\x63\x61\x75\x73\x65\x20\x6f\x66\x20\x74\x68\x65\x20\x44\x41\x45\x20\x73\x74\x61\x74\x65\x20\x25\x73\x2e"
,zdcec0d15c5->z72506057c6,__hmm->name[zce99d8264d]);traceWarning(zea4cd01646,&
_sInfo);}}if((__hmm->considerMax[zce99d8264d])&&(_bstate(z26dbd73a5e)+
zbd05723d83[zce99d8264d]>=__hmm->maxVal[zce99d8264d])){if(zbd05723d83[
zce99d8264d]!=0.0){ITI_char zea4cd01646[(0x1c53+3140-0x26a3)];zdcec0d15c5->
z72506057c6=min(zdcec0d15c5->z72506057c6,0.5*((__hmm->maxVal[zce99d8264d]-
_bstate(z26dbd73a5e))/zbd05723d83[zce99d8264d]));sprintf(zea4cd01646,
"\x54\x68\x65\x20\x76\x61\x6c\x75\x65\x20\x25\x2d\x2e\x31\x37\x67\x20\x65\x78\x63\x65\x65\x64\x73\x20\x74\x68\x65\x20\x6d\x61\x78\x69\x6d\x75\x6d\x20\x28\x25\x2d\x2e\x31\x37\x67\x29\x20\x6f\x66\x20\x74\x68\x65\x20\x44\x41\x45\x20\x73\x74\x61\x74\x65\x20\x25\x73\x20\x28\x44\x61\x6d\x70\x69\x6e\x67\x20\x66\x61\x63\x74\x6f\x72\x3a\x20\x25\x2d\x2e\x31\x37\x67\x29\x2e"
,_bstate(z26dbd73a5e)+zbd05723d83[zce99d8264d],__hmm->maxVal[zce99d8264d],__hmm
->name[zce99d8264d],0.5*((__hmm->maxVal[zce99d8264d]-_bstate(z26dbd73a5e))/
zbd05723d83[zce99d8264d]));traceWarning(zea4cd01646,&_sInfo);}while((_bstate(
z26dbd73a5e)+zdcec0d15c5->z72506057c6*zbd05723d83[zce99d8264d]>=__hmm->maxVal[
zce99d8264d])&&(zdcec0d15c5->z72506057c6!=0.0)){ITI_char zea4cd01646[
(0x101b+1367-0x13e2)];zdcec0d15c5->z72506057c6/=10.0;sprintf(zea4cd01646,
"\x52\x65\x64\x75\x63\x69\x6e\x67\x20\x74\x68\x65\x20\x64\x61\x6d\x70\x69\x6e\x67\x20\x66\x61\x63\x74\x6f\x72\x20\x74\x6f\x20\x25\x2d\x2e\x31\x37\x67\x20\x62\x65\x63\x61\x75\x73\x65\x20\x6f\x66\x20\x74\x68\x65\x20\x44\x41\x45\x20\x73\x74\x61\x74\x65\x20\x25\x73\x2e"
,zdcec0d15c5->z72506057c6,__hmm->name[zce99d8264d]);traceWarning(zea4cd01646,&
_sInfo);}}if(zdcec0d15c5->z72506057c6==0.0){ITI_char zea4cd01646[
(0x59f+3286-0x10e5)];sprintf(zea4cd01646,
"\x44\x41\x45\x20\x73\x74\x61\x74\x65\x20\x25\x73\x20\x65\x78\x63\x65\x65\x64\x73\x20\x61\x20\x62\x6f\x72\x64\x65\x72\x2e"
,__hmm->name[zce99d8264d]);traceWarning(zea4cd01646,&_sInfo);break;}}}void __CAT
(z097b6f9bf5,)(ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*
z6952f3187e){if((zdcec0d15c5->ze4482e84dd==(0x22ad+482-0x248e))&&(zdcec0d15c5->
z7450bac220==(0x90a+2447-0x1298)))z6952f3187e->z0466e2bdbb=__CAT(zb82f30584a,
)(zdcec0d15c5->z8a41d0006a,zdcec0d15c5->z44a72f7bfb,zdcec0d15c5->
z34b6b98586,zdcec0d15c5->z4eeebcd909);else{fprintf(stdout,
"\x64\x69\x6d\x5f\x66\x61\x63\x74\x6f\x72\x20\x3e\x20\x31\x2e\x20\x45\x78\x74\x65\x6e\x64\x20\x43\x61\x6c\x63\x41\x6e\x67\x6c\x65\x54\x61\x6e\x67\x65\x6e\x74\x73\x2e" "\n"
);}}
