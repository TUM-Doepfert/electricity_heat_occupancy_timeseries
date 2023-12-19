/**
 * ITI_NonLinSolver.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/


#if !defined(z7171ec76ab)
#define z7171ec76ab
#include "ITI_crt.h"
#ifdef _FMIMODEL_HOMOTOPY
#include "ITI_fmiModelTypes.h"
#endif
#ifdef ITI_COMP_SIM
#include "ITI_CSHelpers.h"
#define __CAT(a,b) a
#elif defined (ITI_CE_ETAS_LABCAR) || defined (ITI_SIMULINK_S_FUNC) || defined (\
ITI_SFuncSolver) || defined (ITI_FMI_CS2)
#include "ITI_Declarations.h"
#include "ITI_ModelInclude.h"
#define __CAT(a,b) a##b
#else
#include "ITI_ModelInclude.h"
#define __CAT(a,b) a
#endif
#ifdef ITI_COMP_SIM
#define _bstate(zce99d8264d)		*pPart->transient->bx[zce99d8264d]
#define _sInfo			pPart->transient->sInfo
#define __hmm			modelData->hmm
#define z15f3b3f7db ITI_ModelData* modelData = (ITI_ModelData*)zfb02fbb98b;
#define z7529d16d33 ITI_Partition z270f871881 = { (0x144c+2778-0x1f26), (\
ITI_PartitionVar*)zb425515a78, NULL, NULL, (ITI_PartitionVar*)zb425515a78};
#define z1d6d302708 ITI_Partition* pPart = &z270f871881;
#define z6ccc5f5e83 CopyVarsA(pPart->transient->bx, zdcec0d15c5->bx_tmp, \
(0x4df+1095-0x926), pPart->transient->size.bxind_homlast);
#define z5e407f1d0d CopyVarsB(zdcec0d15c5->bx_tmp, pPart->transient->bx, \
(0x1ca3+860-0x1fff), pPart->transient->size.bxind_homlast);
#define zb1f36b2499 ExceptWrapper2((ModelFunc2)model->partFunctions[\
(0x851+7525-0x25b6)].InitializeConditions, pPart, modelData); model->\
ReleaseAllMemory(&modelData->currMem);
#define z29851826b5 model->partFunctions[(0x266+3642-0x10a0)].\
UpdateInferenceGraph(pPart, modelData)
#define z73130e01de model->partFunctions[(0x1ce3+2505-0x26ac)].\
LoadInferenceGraphResults(pPart, modelData)
#elif defined _FMIMODEL_HOMOTOPY
#define z15f3b3f7db ITI_fmiComponent* z279035f318 = (ITI_fmiComponent*)\
zfb02fbb98b;
#define z7529d16d33 ITI_Partition z270f871881 = { (0x1d97+1690-0x2431), (\
ITI_PartitionVar*)zb425515a78, NULL, NULL, (ITI_PartitionVar*)zb425515a78};
#define z1d6d302708 ITI_Partition* pPart = &z270f871881;
#define z6ccc5f5e83 CopyVars(pPart->transient->bx, zdcec0d15c5->bx_tmp, \
(0x1c7b+328-0x1dc3), pPart->transient->size.bxind_homlast);
#define z5e407f1d0d CopyVars(zdcec0d15c5->bx_tmp, pPart->transient->bx, \
(0xb97+5676-0x21c3), pPart->transient->size.bxind_homlast);
#define zb1f36b2499 InitializeConditions(pPart, modelData); ReleaseAllMemory(&\
modelData->currMem);
#define z29851826b5 UpdateInferenceGraph(pPart, modelData)
#define z73130e01de LoadInferenceGraphResults(pPart, modelData)
#elif defined _EMI_HOMOTOPY
#define z15f3b3f7db emc* __C = (emc*)zfb02fbb98b;
#define z6ccc5f5e83 CopyVars(((ITI_real*)emcGetPWork(__C)[(0x2d1+8597-0x2458)]),\
 zdcec0d15c5->bx_tmp, (0x7b2+7945-0x26bb), pPart->transient->size.bxind_homlast)\
;
#define z5e407f1d0d CopyVars(zdcec0d15c5->bx_tmp, ((ITI_real*)emcGetPWork(__C)[\
(0x5b7+2545-0xf9a)]), (0x9a+9446-0x2580), pPart->transient->size.bxind_homlast);
#define zb1f36b2499 InitializeConditions(__C, z3f082f8bdc, zf, zf); \
ReleaseAllMemory((struct ITI_MemoryObject*)ssGetPWork(__C)[(0xe46+895-0x11c2)]);
#else
#define z15f3b3f7db ITI_ModelData* modelData = (ITI_ModelData*)zfb02fbb98b;
#define z7529d16d33 ITI_Partition z270f871881 = { (0xe63+4420-0x1fa7), (\
ITI_PartitionVar*)zb425515a78, NULL, NULL, (ITI_PartitionVar*)zb425515a78};
#define z1d6d302708 ITI_Partition* pPart = &z270f871881;
#define z6ccc5f5e83 CopyVars(pPart->transient->bx, zdcec0d15c5->bx_tmp, \
(0x97d+5407-0x1e9c), pPart->transient->size.bxind_homlast);
#define z5e407f1d0d CopyVars(zdcec0d15c5->bx_tmp, pPart->transient->bx, \
(0x110c+3015-0x1cd3), pPart->transient->size.bxind_homlast);
#if defined ITI_SFuncSolver || defined ITI_CE_ETAS_LABCAR || defined ITI_FMI_CS2\
 || defined ITI_SIMULINK_S_FUNC
#define zb1f36b2499 model->partFunctions[(0xb26+2342-0x144c)].\
InitializeConditions(pPart, modelData); ReleaseAllMemory(&modelData->currMem);
#else
#define zb1f36b2499 model->partFunctions[(0x508+7704-0x2320)].\
InitializeConditions(pPart, modelData); ReleaseAllMemory(&modelData->currMem);
#endif
#define z29851826b5 model->partFunctions[(0x1b31+786-0x1e43)].\
UpdateInferenceGraph(pPart, modelData)
#define z73130e01de model->partFunctions[(0x9a7+6078-0x2165)].\
LoadInferenceGraphResults(pPart, modelData)
#endif
typedef struct ITI_EmbeddingData{ITI_uint z4eeebcd909;ITI_uint z90bbed6de0;
ITI_uint z25f5c17222;ITI_real z3f01d343c0;ITI_uint ze8fdbc6343;ITI_real*
z9e92215ca6;ITI_real*z4bc2586276;ITI_real*bx_tmp;ITI_real*z8a41d0006a;ITI_real*
z44a72f7bfb;ITI_real*z434f62ee93;ITI_real*z411b5a9678;ITI_real*z3960d6c10a;
ITI_uint ze4482e84dd;ITI_uint z7450bac220;ITI_real*z03e5515547;ITI_real*
zf08be7baa7;ITI_real*z6473e0bce5;ITI_real*z8ba7bd6cb6;ITI_real*work;ITI_int 
lwork;ITI_uint z7663004f47;ITI_real*z8ccfbd4931;ITI_real*ze7514d6a7f;ITI_real*
z8d4186ad41;ITI_real*z8a73e5ac9c;ITI_real*z34b6b98586;ITI_uint*zf7377f07fe;
ITI_real*zf4ae93b057;ITI_real*ze94ec32586;ITI_real*z4c54a1eefd;ITI_uint 
z264c1cd328;ITI_uint*zc81779069f;ITI_real z72506057c6;ITI_real z18c08b309a;
ITI_real*z51391e3ef1;ITI_real*zf667805127;ITI_real z2d76deb4a2;ITI_real 
zfaa7d86a2c;ITI_real z22d4438c10;ITI_uint ze4a8849194;ITI_LLSData z9e95b22d7f;
ITI_real*ze957e2faee;ITI_real*zed744e2941;ITI_real*z09e05a7a6d;ITI_real*
z417a4f498b;}ITI_EmbeddingData;typedef struct ITI_EmbeddingParams{ITI_real 
z95f376aec4;ITI_real z26b200c34d;ITI_real z5c954d713f;ITI_real z4bfea9a90b;
ITI_real zfdee43babc;ITI_real z432f21aa64;ITI_real z81339bb7b3;ITI_uint 
z717ffc7f4b;ITI_real z0920b53d5c;ITI_real zc9298ae764;ITI_real z8021017b9a;
ITI_real z1e52fe5184;ITI_uint z8e8b5dbf80;ITI_uint zc72a658dd9;ITI_uint 
z1a8d55b886;ITI_real ze954f3cce4;ITI_uint zcb80911ce0;ITI_real z0466e2bdbb;
ITI_real za494561071;ITI_real zc55b8fab64;ITI_real zbe0284b765;ITI_real 
z881e726654;ITI_real ze59e1c0f65;ITI_real zb389952bf4;ITI_real z298a09d9bc;
ITI_uint z1ae0008de8;ITI_real za49a3a96d0;ITI_real z6dbe734b84;ITI_real 
z7930998139;ITI_uint za8dced7e59;ITI_uint z98306416c2;ITI_uint zd4f0975869;
ITI_uint z1903a1d1d0;}ITI_EmbeddingParams;ITI_FUNCTIONS_API void __CAT(
InitEmbeddingData,)(void*zb425515a78,void*zfb02fbb98b,
ITI_EmbeddingData*zdcec0d15c5,ITI_uint za4489f0b51,ITI_uint bxind_homlast,
ITI_uint z77c4719614);ITI_FUNCTIONS_API void __CAT(zb3611fe3f7,)(
ITI_EmbeddingData*zdcec0d15c5);ITI_FUNCTIONS_API void __CAT(z39328dfd8f,
)(ITI_EmbeddingParams*z6952f3187e,ITI_real za5d9603097,ITI_real 
z62eb1a3615);ITI_FUNCTIONS_API void __CAT(z74e5623a8b,)(
ITI_EmbeddingData*zdcec0d15c5,ITI_uint z9e4f0600bc,ITI_uint z77c4719614);
ITI_FUNCTIONS_API void __CAT(InitHomotopy,)(void*zb425515a78,void*
zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*z6952f3187e,
ITI_uint za4489f0b51,ITI_uint bxind_homlast,ITI_uint z77c4719614,ITI_real 
za5d9603097,ITI_real z62eb1a3615);ITI_FUNCTIONS_API void __CAT(FreeHomotopy,
)(void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5);ITI_FUNCTIONS_API 
ITI_uint __CAT(CalcCurve,)(void*zb425515a78,void*zfb02fbb98b,
ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*z6952f3187e,void*zf48d7e43ff);
ITI_FUNCTIONS_API ITI_uint __CAT(z85035d0bf5,)(void*zb425515a78,void*
zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*z6952f3187e,void*
zf48d7e43ff);ITI_FUNCTIONS_API ITI_uint __CAT(z8b17e620d6,)(void*
zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*
z6952f3187e,void*zf48d7e43ff);ITI_FUNCTIONS_API ITI_uint __CAT(z82aef60b72,
)(void*zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,
ITI_EmbeddingParams*z6952f3187e,void*zf48d7e43ff,ITI_uint z6fcd5db760);
ITI_FUNCTIONS_API ITI_uint __CAT(z97f5bd8a23,)(void*zb425515a78,void*
zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*z6952f3187e,void*
zf48d7e43ff);ITI_FUNCTIONS_API ITI_uint __CAT(zfcc32624f6,)(void*
zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*
z6952f3187e,void*zf48d7e43ff);ITI_FUNCTIONS_API void __CAT(zbb1a877b64,
)(void*zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,
ITI_EmbeddingParams*z6952f3187e);ITI_FUNCTIONS_API ITI_uint __CAT(z6e964533e7,
)(void*zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,
ITI_EmbeddingParams*z6952f3187e,void*zf48d7e43ff);ITI_FUNCTIONS_API ITI_uint 
__CAT(z8401db3b7b,)(void*zb425515a78,void*zfb02fbb98b,
ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*z6952f3187e,void*zf48d7e43ff);
ITI_FUNCTIONS_API ITI_real __CAT(z62f48093a2,)(void*zb425515a78,void*
zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*z6952f3187e,void*
zf48d7e43ff);ITI_FUNCTIONS_API void __CAT(z4320d07649,)(void*
zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*
z6952f3187e,void*zf48d7e43ff);ITI_FUNCTIONS_API void __CAT(zf29e330b26,
)(void*zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,
ITI_EmbeddingParams*z6952f3187e,void*zf48d7e43ff);ITI_FUNCTIONS_API ITI_int 
__CAT(z6d34c7efdb,)(void*zb425515a78,void*zfb02fbb98b,
ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*z6952f3187e,void*zf48d7e43ff);
ITI_FUNCTIONS_API ITI_uint __CAT(z5669ea4bf3,)(void*zb425515a78,void*
zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*z6952f3187e,void*
zf48d7e43ff,ITI_uint z00f6ed1d9c);ITI_FUNCTIONS_API ITI_uint __CAT(z5650878f4b,
)(void*zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5);
ITI_FUNCTIONS_API void __CAT(z1fe51ea564,)(void*zb425515a78,void*
zfb02fbb98b,ITI_real*z09e05a7a6d);ITI_FUNCTIONS_API void __CAT(z1faac1090f,
)(void*zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,
ITI_EmbeddingParams*z6952f3187e);ITI_FUNCTIONS_API void __CAT(z4bc25bef61,
)(ITI_real*a,ITI_real*b,ITI_uint z1581844784);ITI_FUNCTIONS_API void 
__CAT(z11cd768e30,)(ITI_real*a,ITI_real z1437e7d647,ITI_uint 
z1581844784);ITI_FUNCTIONS_API ITI_uint __CAT(z6474127c41,)(void*
zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5);ITI_FUNCTIONS_API 
void __CAT(z54d9b09da9,)(ITI_EmbeddingData*zdcec0d15c5,ITI_real*
z9e92215ca6,ITI_real*zbd05723d83);ITI_FUNCTIONS_API ITI_uint __CAT(z5551e92655,
)(ITI_EmbeddingData*zdcec0d15c5);ITI_FUNCTIONS_API ITI_real __CAT(
zb82f30584a,)(ITI_real*z7b058c25be,ITI_real*z6e0310fb34,ITI_real*
zf667805127,ITI_uint z1581844784);ITI_FUNCTIONS_API ITI_real __CAT(z9383ee8374,
)(ITI_real*z7b058c25be,ITI_real*z6e0310fb34,ITI_real*zf667805127,
ITI_uint z1581844784);ITI_FUNCTIONS_API ITI_real __CAT(z224a93e97c,)(
void*zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5);
ITI_FUNCTIONS_API ITI_real __CAT(zab7ffcf1ba,)(ITI_real*za04057655a,
ITI_real*z82425fa37c,ITI_uint z1581844784);ITI_FUNCTIONS_API ITI_real __CAT(
z48766ede72,)(ITI_real*za04057655a,ITI_real*z82425fa37c,ITI_uint 
z1581844784,ITI_uint zf1cdc30602);ITI_FUNCTIONS_API ITI_real __CAT(zc1c3f4c2b5,
)(ITI_real**za04057655a,ITI_real*z82425fa37c,ITI_uint z1581844784,
ITI_uint zf1cdc30602);ITI_FUNCTIONS_API ITI_real __CAT(z66842ef5f7,)(
ITI_EmbeddingParams*z6952f3187e,ITI_real*z3f082f8bdc,ITI_real*za04057655a,
ITI_uint z1581844784,ITI_uint zf1cdc30602);ITI_FUNCTIONS_API ITI_real __CAT(
ze7161a9726,)(ITI_EmbeddingParams*z6952f3187e,ITI_real*z3f082f8bdc,
ITI_real**za04057655a,ITI_uint z1581844784,ITI_uint zf1cdc30602);
ITI_FUNCTIONS_API ITI_real __CAT(z8315707fda,)(void*zb425515a78,void*
zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*z6952f3187e);
ITI_FUNCTIONS_API ITI_uint __CAT(z5d747ed95f,)(void*zb425515a78,void*
zfb02fbb98b,ITI_EmbeddingParams*z6952f3187e,ITI_real*zbd05723d83,ITI_real*
z82425fa37c,ITI_uint z1581844784,ITI_uint zf1cdc30602,ITI_real*z9439e49293);
ITI_FUNCTIONS_API void __CAT(zf901b7d7e1,)(void*zb425515a78,void*
zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_real*z9e92215ca6,ITI_real*
zbd05723d83,ITI_uint z7ec2813c96);ITI_FUNCTIONS_API void __CAT(zfa5fa8855f,
)(void*zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,
ITI_EmbeddingParams*z6952f3187e,ITI_int zaa5147cc6a,ITI_real zbd762e14d2);
ITI_FUNCTIONS_API void __CAT(zf162d5c8f1,)(void*zb425515a78,void*
zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_int zaa5147cc6a,ITI_real 
z82803ff4d1);ITI_FUNCTIONS_API void __CAT(z828752be51,)(void*
zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_EmbeddingParams*
z6952f3187e);ITI_FUNCTIONS_API void __CAT(zb3da54817e,)(void*
zb425515a78,void*zfb02fbb98b,ITI_EmbeddingData*zdcec0d15c5,ITI_real*zbd05723d83)
;ITI_FUNCTIONS_API void __CAT(z097b6f9bf5,)(ITI_EmbeddingData*
zdcec0d15c5,ITI_EmbeddingParams*z6952f3187e);
#endif

