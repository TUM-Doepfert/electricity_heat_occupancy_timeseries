
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "sundials/include/nvector/nvector_serial.h"
#include "sundials/src/cvode/cvode_dense_impl.h"
#include "sundials/src/cvode/cvode_impl.h"
#include <sundials/sundials_math.h>
#include "ma_serialization.h"
#include <sundials/sundials_serialization.h>
#include "ITI_Cvode_helpers.h"
static int za1b2b653c2(CVodeMem z8f1755e318);static int zbe89c8ec29(CVodeMem 
z8f1755e318,int z31408bbb6e,N_Vector z1f3fe71cf8,N_Vector z5da45a44ad,
booleantype*z59367caf9f,N_Vector z8cb046920f,N_Vector ze7ad17045a,N_Vector 
ze1aab32d96);static int z80b8e79a14(CVodeMem z8f1755e318,N_Vector zc40e7ae7ae,
N_Vector zceec58c610,N_Vector z3be6d61a13,N_Vector z1f4ba8c4f3);static void 
z3a0827125e(CVodeMem z8f1755e318);
#define ze06934a82b       (z8f1755e318->cv_lmm)
#define z5227064b5e         (z8f1755e318->cv_f)
#define z119f1bd5f7    (z8f1755e318->cv_f_data)
#define z864430a72f    (z8f1755e318->cv_uround)
#define z32e3fe3ae7       (z8f1755e318->cv_nst)
#define z7edcc2416e        (z8f1755e318->cv_tn)
#define z02b1c4a3ea         (z8f1755e318->cv_h)
#define ze5b3573c3a     (z8f1755e318->cv_gamma)
#define zcb9dff0c31    (z8f1755e318->cv_gammap)
#define z923ac3b766    (z8f1755e318->cv_gamrat)
#define z8344334d43       (z8f1755e318->cv_ewt)
#define z39b5048ec7     (z8f1755e318->cv_linit)
#define zfa27ae39d9    (z8f1755e318->cv_lsetup)
#define zee1e63ef25    (z8f1755e318->cv_lsolve)
#define z7541f5c380     (z8f1755e318->cv_lfree)
#define z078ac0b1a5      (z8f1755e318->cv_lmem)
#define zd236d1e733     (z8f1755e318->cv_tempv)
#define z91080e6c96 (z8f1755e318->cv_setupNonNull)
#define z5bbc0e2d91           (z8f1755e318->cv_tfun)
#define z0fb4580104        (z8f1755e318->cv_tf_data)
int CVSparse(void*zfc39fd83d1,long int z3278a41716){CVodeMem z8f1755e318;
ITI_SparseData*z78d65c20d2=NULL;if(zfc39fd83d1==NULL){CVProcessError(NULL,
z5274b4c3dc,"\x43\x56\x53\x50\x41\x52\x53\x45",
"\x43\x56\x53\x70\x61\x72\x73\x65",MSGDS_CVMEM_NULL);return(z5274b4c3dc);}
z8f1755e318=(CVodeMem)zfc39fd83d1;if(zd236d1e733->ops->nvgetarraypointer==NULL||
zd236d1e733->ops->nvsetarraypointer==NULL){CVProcessError(z8f1755e318,
z1b941eefee,"\x43\x56\x53\x50\x41\x52\x53\x45",
"\x43\x56\x53\x70\x61\x72\x73\x65",MSGDS_BAD_NVECTOR);return(z1b941eefee);}if(
z7541f5c380!=NULL)z7541f5c380(z8f1755e318);z39b5048ec7=za1b2b653c2;zfa27ae39d9=
zbe89c8ec29;zee1e63ef25=z80b8e79a14;z7541f5c380=z3a0827125e;AllocSparseData(&
z78d65c20d2,z3278a41716);z78d65c20d2->z3960d6c10a=(0x1047+5142-0x245d);
z78d65c20d2->z353e857643=(0xad8+1305-0xff1);z78d65c20d2->zb9132752a5=z1cb858b9f6
;z91080e6c96=TRUE;z78d65c20d2->z500eaf1fbc=z3278a41716;z078ac0b1a5=(void*)
z78d65c20d2;z8f1755e318->cv_LinSolvSerialization=ze25ef2447e;z8f1755e318->
cv_LinSolvDeserialization=zef2b3bfa61;z8f1755e318->cv_LinSolvSerializationSize=
z74de6aad74;return(z1cb858b9f6);}int CVSparseSetJacFn(void*zfc39fd83d1,
CVSparseJacFn z4d08893320,void*zdfc42fc222){CVodeMem z8f1755e318;ITI_SparseData*
z78d65c20d2;if(zfc39fd83d1==NULL){CVProcessError(NULL,z5274b4c3dc,
"\x43\x56\x53\x50\x41\x52\x53\x45",
"\x43\x56\x53\x70\x61\x72\x73\x65\x53\x65\x74\x4a\x61\x63\x46\x6e",
MSGDS_CVMEM_NULL);return(z5274b4c3dc);}z8f1755e318=(CVodeMem)zfc39fd83d1;if(
z078ac0b1a5==NULL){CVProcessError(z8f1755e318,z1413761acc,
"\x43\x56\x53\x50\x41\x52\x53\x45",
"\x43\x56\x53\x70\x61\x72\x73\x65\x53\x65\x74\x4a\x61\x63\x46\x6e",za7195f91fc);
return(z1413761acc);}z78d65c20d2=(ITI_SparseData*)z078ac0b1a5;z78d65c20d2->
z3960d6c10a=z4d08893320;if(z4d08893320!=NULL)z78d65c20d2->z353e857643=
zdfc42fc222;return(z1cb858b9f6);}int zc875b86afb(void*zfc39fd83d1,long int*
zbb0cb88046,long int*z3b32a5d8c9){CVodeMem z8f1755e318;ITI_SparseData*
z78d65c20d2;if(zfc39fd83d1==NULL){CVProcessError(NULL,z5274b4c3dc,
"\x43\x56\x53\x50\x41\x52\x53\x45",
"\x43\x56\x53\x70\x61\x72\x73\x65\x47\x65\x74\x57\x6f\x72\x6b\x53\x70\x61\x63\x65"
,MSGDS_CVMEM_NULL);return(z5274b4c3dc);}z8f1755e318=(CVodeMem)zfc39fd83d1;if(
z078ac0b1a5==NULL){CVProcessError(z8f1755e318,z1413761acc,
"\x43\x56\x53\x50\x41\x52\x53\x45",
"\x43\x56\x53\x70\x61\x72\x73\x65\x47\x65\x74\x57\x6f\x72\x6b\x53\x70\x61\x63\x65"
,za7195f91fc);return(z1413761acc);}z78d65c20d2=(ITI_SparseData*)z078ac0b1a5;*
zbb0cb88046=(0xe9f+356-0x1003);*z3b32a5d8c9=(0xc14+6699-0x263f);return(
z1cb858b9f6);}int z9c3bba7f11(void*zfc39fd83d1,long int*zd94534fdae){CVodeMem 
z8f1755e318;ITI_SparseData*z78d65c20d2;if(zfc39fd83d1==NULL){CVProcessError(NULL
,z5274b4c3dc,"\x43\x56\x53\x50\x41\x52\x53\x45",
"\x43\x56\x53\x70\x61\x72\x73\x65\x47\x65\x74\x4e\x75\x6d\x4a\x61\x63\x45\x76\x61\x6c\x73"
,MSGDS_CVMEM_NULL);return(z5274b4c3dc);}z8f1755e318=(CVodeMem)zfc39fd83d1;if(
z078ac0b1a5==NULL){CVProcessError(z8f1755e318,z1413761acc,
"\x43\x56\x53\x50\x41\x52\x53\x45",
"\x43\x56\x53\x70\x61\x72\x73\x65\x47\x65\x74\x4e\x75\x6d\x4a\x61\x63\x45\x76\x61\x6c\x73"
,za7195f91fc);return(z1413761acc);}z78d65c20d2=(ITI_SparseData*)z078ac0b1a5;*
zd94534fdae=z78d65c20d2->z21dfaed2ff;return(z1cb858b9f6);}int z0ed6cebf3a(void*
zfc39fd83d1,long int*z845b0cfcd8){CVodeMem z8f1755e318;ITI_SparseData*
z78d65c20d2;if(zfc39fd83d1==NULL){CVProcessError(NULL,z5274b4c3dc,
"\x43\x56\x53\x50\x41\x52\x53\x45",
"\x43\x56\x53\x70\x61\x72\x73\x65\x47\x65\x74\x4e\x75\x6d\x52\x68\x73\x45\x76\x61\x6c\x73"
,MSGDS_CVMEM_NULL);return(z5274b4c3dc);}z8f1755e318=(CVodeMem)zfc39fd83d1;if(
z078ac0b1a5==NULL){CVProcessError(z8f1755e318,z1413761acc,
"\x43\x56\x53\x50\x41\x52\x53\x45",
"\x43\x56\x53\x70\x61\x72\x73\x65\x47\x65\x74\x4e\x75\x6d\x52\x68\x73\x45\x76\x61\x6c\x73"
,za7195f91fc);return(z1413761acc);}z78d65c20d2=(ITI_SparseData*)z078ac0b1a5;*
z845b0cfcd8=z78d65c20d2->z1b10328be9;return(z1cb858b9f6);}char*zcc60383671(int 
z9f1a7be944){char*z05fb73be78;z05fb73be78=(char*)malloc((0x13f1+4328-0x24bb)*
sizeof(char));switch(z9f1a7be944){case z1cb858b9f6:sprintf(z05fb73be78,
"\x43\x56\x53\x50\x41\x52\x53\x45\x5f\x53\x55\x43\x43\x45\x53\x53");break;case 
z5274b4c3dc:sprintf(z05fb73be78,
"\x43\x56\x53\x50\x41\x52\x53\x45\x5f\x4d\x45\x4d\x5f\x4e\x55\x4c\x4c");break;
case z1413761acc:sprintf(z05fb73be78,
"\x43\x56\x53\x50\x41\x52\x53\x45\x5f\x53\x4d\x45\x4d\x5f\x4e\x55\x4c\x4c");
break;case z1b941eefee:sprintf(z05fb73be78,
"\x43\x56\x53\x50\x41\x52\x53\x45\x5f\x49\x4c\x4c\x5f\x49\x4e\x50\x55\x54");
break;case z5f6198da16:sprintf(z05fb73be78,
"\x43\x56\x53\x50\x41\x52\x53\x45\x5f\x4d\x45\x4d\x5f\x46\x41\x49\x4c");break;
case za2883f7c51:sprintf(z05fb73be78,
"\x43\x56\x53\x50\x41\x52\x53\x45\x5f\x4a\x41\x43\x46\x55\x4e\x43\x5f\x55\x4e\x52\x45\x43\x56\x52"
);break;case zc1a9b6e483:sprintf(z05fb73be78,
"\x43\x56\x53\x50\x41\x52\x53\x45\x5f\x4a\x41\x43\x46\x55\x4e\x43\x5f\x52\x45\x43\x56\x52"
);break;default:sprintf(z05fb73be78,"\x4e\x4f\x4e\x45");}return(z05fb73be78);}
int z9284133f53(void*zfc39fd83d1,int*z9f1a7be944){CVodeMem z8f1755e318;
ITI_SparseData*z78d65c20d2;if(zfc39fd83d1==NULL){CVProcessError(NULL,z5274b4c3dc
,"\x43\x56\x53\x50\x41\x52\x53\x45",
"\x43\x56\x53\x70\x61\x72\x73\x65\x47\x65\x74\x4c\x61\x73\x74\x46\x6c\x61\x67",
MSGDS_CVMEM_NULL);return(z5274b4c3dc);}z8f1755e318=(CVodeMem)zfc39fd83d1;if(
z078ac0b1a5==NULL){CVProcessError(z8f1755e318,z1413761acc,
"\x43\x56\x53\x50\x41\x52\x53\x45",
"\x43\x56\x53\x70\x61\x72\x73\x65\x47\x65\x74\x4c\x61\x73\x74\x46\x6c\x61\x67",
za7195f91fc);return(z1413761acc);}z78d65c20d2=(ITI_SparseData*)z078ac0b1a5;*
z9f1a7be944=z78d65c20d2->zb9132752a5;return(z1cb858b9f6);}static int za1b2b653c2
(CVodeMem z8f1755e318){ITI_SparseData*z78d65c20d2=(ITI_SparseData*)z078ac0b1a5;
z78d65c20d2->z21dfaed2ff=(0xae6+4115-0x1af9);z78d65c20d2->z1b10328be9=
(0x866+4406-0x199c);z78d65c20d2->z2166c6aec0=(0x77a+3190-0x13f0);z78d65c20d2->
zb9132752a5=z1cb858b9f6;return((0x12e5+5077-0x26ba));}static int zbe89c8ec29(
CVodeMem z8f1755e318,int z31408bbb6e,N_Vector z1f3fe71cf8,N_Vector z5da45a44ad,
booleantype*z59367caf9f,N_Vector z8cb046920f,N_Vector ze7ad17045a,N_Vector 
ze1aab32d96){booleantype z56d43963a8,z6cf4530937;realtype z83ba132798;
z24c056d577 zce99d8264d;int retval,zcbd489f686;ITI_SparseData*z78d65c20d2=(
ITI_SparseData*)z078ac0b1a5;if(zcb9dff0c31!=ZERO)z83ba132798=ABS((ze5b3573c3a/
zcb9dff0c31)-ONE);else z83ba132798=ZERO;z56d43963a8=(z32e3fe3ae7==
(0x191f+317-0x1a5c))||(z32e3fe3ae7>z78d65c20d2->z2166c6aec0+z8f1755e318->
cv_maxStepNumberBetweenJacobianEvaluations)||((z31408bbb6e==CV_FAIL_BAD_J)&&(
z83ba132798<z87265f3e63))||(z31408bbb6e==CV_FAIL_OTHER);z6cf4530937=!z56d43963a8
;if(z6cf4530937){*z59367caf9f=FALSE;for(zce99d8264d=(0x755+6503-0x20bc);
zce99d8264d<z78d65c20d2->z54807acf9f.z034e6ffe57;zce99d8264d++)z78d65c20d2->
m_Sparse.z9e4098361d[zce99d8264d]=z78d65c20d2->z54807acf9f.z9e4098361d[
zce99d8264d];}else{z78d65c20d2->z21dfaed2ff++;z78d65c20d2->z2166c6aec0=
z32e3fe3ae7;*z59367caf9f=TRUE;for(zce99d8264d=(0x2+7330-0x1ca4);zce99d8264d<
z78d65c20d2->z972a0c3c3b;zce99d8264d++)z78d65c20d2->m_Sparse.z9e4098361d[
z78d65c20d2->zb776f37529[zce99d8264d]]=0.0;retval=z78d65c20d2->z3960d6c10a(
z78d65c20d2->z500eaf1fbc,z7edcc2416e,z1f3fe71cf8,z5da45a44ad,z78d65c20d2->
z353e857643,z8cb046920f,ze7ad17045a,ze1aab32d96);if(retval<(0xe72+663-0x1109)){
CVProcessError(z8f1755e318,za2883f7c51,"\x43\x56\x53\x50\x41\x52\x53\x45",
"\x43\x56\x53\x70\x61\x72\x73\x65\x53\x65\x74\x75\x70",MSGDS_JACFUNC_FAILED);
z78d65c20d2->zb9132752a5=za2883f7c51;return(-(0x182+6831-0x1c30));}if(retval>
(0x2624+48-0x2654)){z78d65c20d2->zb9132752a5=zc1a9b6e483;return(
(0xfcc+1547-0x15d6));}for(zce99d8264d=(0x6b8+3962-0x1632);zce99d8264d<
z78d65c20d2->z54807acf9f.z034e6ffe57;zce99d8264d++)z78d65c20d2->z54807acf9f.
z9e4098361d[zce99d8264d]=z78d65c20d2->m_Sparse.z9e4098361d[zce99d8264d];if(
z8f1755e318->trJac){char zea4cd01646[(0x102a+5856-0x26a6)],*za77fa12c48=NULL;
char zb30cbb84a3[]=
"\x54\x79\x70\x65\x3a\x20\x64\x65\x72\x28\x46\x2c\x78\x29" "\n";size_t 
za72522e016=sizeof(zb30cbb84a3);sprintf(zea4cd01646,
"\x43\x6f\x6d\x70\x75\x74\x61\x74\x69\x6f\x6e\x20\x6f\x66\x20\x4a\x61\x63\x6f\x62\x69\x61\x6e\x20\x61\x74\x20\x74\x20\x3d\x20\x25\x2e\x31\x37\x67\x3a"
,z7edcc2416e);z6f8ca8964f(z8f1755e318,&z78d65c20d2->m_Sparse,&za77fa12c48,
za72522e016);strncpy(za77fa12c48,zb30cbb84a3,za72522e016-(0x1295+3242-0x1f3e));
z5bbc0e2d91(zea4cd01646,za77fa12c48,z0fb4580104);free(za77fa12c48);}}for(
zce99d8264d=(0x8f+7136-0x1c6f);zce99d8264d<z78d65c20d2->z54807acf9f.z034e6ffe57;
zce99d8264d++)z78d65c20d2->m_Sparse.z9e4098361d[zce99d8264d]*=-ze5b3573c3a;for(
zce99d8264d=(0xac+826-0x3e6);zce99d8264d<z78d65c20d2->m_Sparse.ze05b33d1dc;
zce99d8264d++)z78d65c20d2->m_Sparse.z9e4098361d[z78d65c20d2->z5126954186[
zce99d8264d]]+=ONE;if(z8f1755e318->trJac){char zea4cd01646[(0x4f0+6847-0x1f4b)],
*za77fa12c48=NULL;char zb30cbb84a3[]=
"\x54\x79\x70\x65\x3a\x20\x49\x20\x2d\x20\x67\x61\x6d\x6d\x61\x20\x2a\x20\x64\x65\x72\x28\x46\x2c\x78\x29" "\n"
;size_t za72522e016=sizeof(zb30cbb84a3);sprintf(zea4cd01646,
"\x43\x6f\x6d\x70\x75\x74\x61\x74\x69\x6f\x6e\x20\x6f\x66\x20\x69\x74\x65\x72\x61\x74\x69\x6f\x6e\x20\x6d\x61\x74\x72\x69\x78\x20\x61\x74\x20\x74\x20\x3d\x20\x25\x2e\x31\x37\x67\x3a"
,z7edcc2416e);z6f8ca8964f(z8f1755e318,&z78d65c20d2->m_Sparse,&za77fa12c48,
za72522e016);strncpy(za77fa12c48,zb30cbb84a3,za72522e016-(0x487+3653-0x12cb));
z5bbc0e2d91(zea4cd01646,za77fa12c48,z0fb4580104);free(za77fa12c48);}if(
z78d65c20d2->z26760f5376==(0x7bd+1984-0xf7d)){zd6eb0a6292(&z78d65c20d2->m_Sparse
,&z78d65c20d2->zc71e9cd244,stdout);z78d65c20d2->z26760f5376++;}else{zcbd489f686=
z866326407a(&z78d65c20d2->m_Sparse,&z78d65c20d2->zc71e9cd244);z78d65c20d2->
z270e86c352++;if(zcbd489f686==(0x9d1+6365-0x22ad)){for(zce99d8264d=
(0x200d+375-0x2184);zce99d8264d<z78d65c20d2->z54807acf9f.z034e6ffe57;zce99d8264d
++){z78d65c20d2->m_Sparse.z9e4098361d[zce99d8264d]=z78d65c20d2->z54807acf9f.
z9e4098361d[zce99d8264d];z78d65c20d2->m_Sparse.zdd87164e4a[zce99d8264d]=
z78d65c20d2->z54807acf9f.zdd87164e4a[zce99d8264d];}for(zce99d8264d=z78d65c20d2->
z54807acf9f.z034e6ffe57;zce99d8264d<z78d65c20d2->m_Sparse.z034e6ffe57;
zce99d8264d++){z78d65c20d2->m_Sparse.z9e4098361d[zce99d8264d]=0.0;z78d65c20d2->
m_Sparse.zdd87164e4a[zce99d8264d]=(0x11f9+3709-0x2076);}for(zce99d8264d=
(0x1cd1+568-0x1f09);zce99d8264d<z78d65c20d2->m_Sparse.ze05b33d1dc+
(0xb32+558-0xd5f);zce99d8264d++)z78d65c20d2->m_Sparse.z5ccd45e7a8[zce99d8264d]=
z78d65c20d2->z54807acf9f.z5ccd45e7a8[zce99d8264d];z78d65c20d2->m_Sparse.
z034e6ffe57=z78d65c20d2->z54807acf9f.z034e6ffe57;for(zce99d8264d=
(0x1473+819-0x17a6);zce99d8264d<z78d65c20d2->m_Sparse.z034e6ffe57;zce99d8264d++)
z78d65c20d2->m_Sparse.z9e4098361d[zce99d8264d]*=-ze5b3573c3a;for(zce99d8264d=
(0x3c9+8713-0x25d2);zce99d8264d<z78d65c20d2->m_Sparse.ze05b33d1dc;zce99d8264d++)
z78d65c20d2->m_Sparse.z9e4098361d[z78d65c20d2->z5126954186[zce99d8264d]]+=ONE;
zd6eb0a6292(&z78d65c20d2->m_Sparse,&z78d65c20d2->zc71e9cd244,stdout);z78d65c20d2
->z26760f5376++;}}return((0x10e3+2118-0x1929));}static int z80b8e79a14(CVodeMem 
z8f1755e318,N_Vector zc40e7ae7ae,N_Vector zceec58c610,N_Vector z3be6d61a13,
N_Vector z1f4ba8c4f3){long int zce99d8264d;ITI_SparseData*z78d65c20d2=(
ITI_SparseData*)z078ac0b1a5;for(zce99d8264d=(0x1ba5+1534-0x21a3);zce99d8264d<
z78d65c20d2->m_Sparse.ze05b33d1dc;zce99d8264d++)z78d65c20d2->z625199ef9a[
zce99d8264d]=NV_Ith_S(zc40e7ae7ae,zce99d8264d);z4249190bfd(&z78d65c20d2->
m_Sparse,&z78d65c20d2->zc71e9cd244,z78d65c20d2->z625199ef9a,z78d65c20d2->
zb248acdbc7);z78d65c20d2->zd262c6ec37++;for(zce99d8264d=(0x12b+5150-0x1549);
zce99d8264d<z78d65c20d2->m_Sparse.ze05b33d1dc;zce99d8264d++)NV_Ith_S(zc40e7ae7ae
,zce99d8264d)=z78d65c20d2->zb248acdbc7[zce99d8264d];if((ze06934a82b==CV_BDF)&&(
z923ac3b766!=ONE))N_VScale(TWO/(ONE+z923ac3b766),zc40e7ae7ae,zc40e7ae7ae);
z78d65c20d2->zb9132752a5=z1cb858b9f6;return((0x15ec+1615-0x1c3b));}static void 
z3a0827125e(CVodeMem z8f1755e318){ITI_SparseData*z78d65c20d2=(ITI_SparseData*)
z078ac0b1a5;FreeSparseData(&z78d65c20d2);}void FreeSparseData(ITI_SparseData**
z78d65c20d2){z161699ae8b(&(*z78d65c20d2)->m_Sparse);z161699ae8b(&(*z78d65c20d2)
->z54807acf9f);zad882a33d8(&(*z78d65c20d2)->zc71e9cd244);if((*z78d65c20d2)->
z22a80c7c9a!=NULL){free((*z78d65c20d2)->z22a80c7c9a);(*z78d65c20d2)->z22a80c7c9a
=NULL;}if((*z78d65c20d2)->z6e19225a91!=NULL){free((*z78d65c20d2)->z6e19225a91);(
*z78d65c20d2)->z6e19225a91=NULL;}if((*z78d65c20d2)->zb248acdbc7!=NULL){free((*
z78d65c20d2)->zb248acdbc7);(*z78d65c20d2)->zb248acdbc7=NULL;}if((*z78d65c20d2)->
z625199ef9a!=NULL){free((*z78d65c20d2)->z625199ef9a);(*z78d65c20d2)->z625199ef9a
=NULL;}if((*z78d65c20d2)->z5126954186!=NULL){free((*z78d65c20d2)->z5126954186);(
*z78d65c20d2)->z5126954186=NULL;}if((*z78d65c20d2)->zb776f37529!=NULL){free((*
z78d65c20d2)->zb776f37529);(*z78d65c20d2)->zb776f37529=NULL;}free(*z78d65c20d2);
*z78d65c20d2=NULL;}void AllocSparseData(ITI_SparseData**z78d65c20d2,long int 
z3278a41716){int z540ca407d7=z3278a41716*z3278a41716;int zb5f9d830bc=z3278a41716
+(0xcdb+3376-0x1a0a);*z78d65c20d2=NULL;*z78d65c20d2=(ITI_SparseData*)calloc(
(0xf7c+4465-0x20ec),sizeof(ITI_SparseData));z717baa419d(&(*z78d65c20d2)->
m_Sparse);z717baa419d(&(*z78d65c20d2)->z54807acf9f);memset(&(*z78d65c20d2)->
zc71e9cd244,(0xa31+2475-0x13dc),sizeof((*z78d65c20d2)->zc71e9cd244));z6349c6a912
(&(*z78d65c20d2)->zc71e9cd244);(*z78d65c20d2)->m_Sparse.z9e4098361d=(value*)
calloc((unsigned)z540ca407d7,sizeof(value));(*z78d65c20d2)->m_Sparse.zdd87164e4a
=(z24c056d577*)calloc((unsigned)z540ca407d7,sizeof(z24c056d577));(*z78d65c20d2)
->m_Sparse.z5ccd45e7a8=(z24c056d577*)calloc((unsigned)zb5f9d830bc,sizeof(
z24c056d577));(*z78d65c20d2)->z54807acf9f.z9e4098361d=(value*)calloc((unsigned)
z540ca407d7,sizeof(value));(*z78d65c20d2)->z54807acf9f.zdd87164e4a=(z24c056d577*
)calloc((unsigned)z540ca407d7,sizeof(z24c056d577));(*z78d65c20d2)->z54807acf9f.
z5ccd45e7a8=(z24c056d577*)calloc((unsigned)zb5f9d830bc,sizeof(z24c056d577));(*
z78d65c20d2)->z22a80c7c9a=(z24c056d577*)calloc((unsigned)z540ca407d7,sizeof(
z24c056d577));(*z78d65c20d2)->z6e19225a91=(z24c056d577*)calloc((unsigned)
zb5f9d830bc,sizeof(z24c056d577));(*z78d65c20d2)->zb248acdbc7=(value*)calloc((
unsigned)z3278a41716,sizeof(value));(*z78d65c20d2)->z625199ef9a=(value*)calloc((
unsigned)z3278a41716,sizeof(value));(*z78d65c20d2)->z5126954186=(int*)calloc((
unsigned)z3278a41716,sizeof(int));(*z78d65c20d2)->zb776f37529=(int*)calloc((
unsigned)z3278a41716,sizeof(int));(*z78d65c20d2)->zb776f37529[
(0x222a+863-0x2589)]=-(0xd15+5983-0x2473);(*z78d65c20d2)->z972a0c3c3b=
(0xcd0+6421-0x25e5);}void SetIntoSparse(ITI_SparseData*z78d65c20d2){z24c056d577 
z6e6181a44d;z24c056d577 z812c65ff2f=(0x17c9+1557-0x1dde);z24c056d577*z394658dec5
=(z24c056d577*)calloc(z78d65c20d2->z500eaf1fbc+(0x1811+478-0x19ee),sizeof(
z24c056d577));for(z6e6181a44d=(0x1519+3352-0x2231);z6e6181a44d<z78d65c20d2->
m_Sparse.z034e6ffe57;z6e6181a44d++)z394658dec5[z78d65c20d2->m_Sparse.zdd87164e4a
[z6e6181a44d]+(0xf8a+110-0xff7)]++;for(z6e6181a44d=(0x1543+792-0x185a);
z6e6181a44d<z78d65c20d2->z500eaf1fbc+(0x1d67+2414-0x26d4);z6e6181a44d++){
z394658dec5[z6e6181a44d]+=z394658dec5[z6e6181a44d-(0x680+6676-0x2093)];
z78d65c20d2->z6e19225a91[z6e6181a44d]=z394658dec5[z6e6181a44d];}for(z6e6181a44d=
(0x158+5157-0x157d);z6e6181a44d<z78d65c20d2->m_Sparse.z034e6ffe57;z6e6181a44d++)
if(z78d65c20d2->zb776f37529[z812c65ff2f]==z6e6181a44d)z812c65ff2f++;else{
z78d65c20d2->z22a80c7c9a[z394658dec5[z78d65c20d2->m_Sparse.zdd87164e4a[
z6e6181a44d]]]=z6e6181a44d;z394658dec5[z78d65c20d2->m_Sparse.zdd87164e4a[
z6e6181a44d]]++;}free(z394658dec5);}int CVSparseGetNumDecomp(void*zfc39fd83d1,
long int*z1c95cc38d4){CVodeMem z8f1755e318;ITI_SparseData*z78d65c20d2;if(
zfc39fd83d1==NULL){CVProcessError(NULL,z5274b4c3dc,
"\x43\x56\x53\x50\x41\x52\x53\x45",
"\x43\x56\x53\x70\x61\x72\x73\x65\x47\x65\x74\x4e\x75\x6d\x44\x65\x63\x6f\x6d\x70"
,MSGDS_CVMEM_NULL);return(z5274b4c3dc);}z8f1755e318=(CVodeMem)zfc39fd83d1;if(
z078ac0b1a5==NULL){CVProcessError(z8f1755e318,z1413761acc,
"\x43\x56\x53\x50\x41\x52\x53\x45",
"\x43\x56\x53\x70\x61\x72\x73\x65\x47\x65\x74\x4e\x75\x6d\x44\x65\x63\x6f\x6d\x70"
,za7195f91fc);return(z1413761acc);}z78d65c20d2=(ITI_SparseData*)z078ac0b1a5;*
z1c95cc38d4=z78d65c20d2->z270e86c352;return(z1cb858b9f6);}int CVSparseGetNumElim
(void*zfc39fd83d1,long int*zcd73a567da){CVodeMem z8f1755e318;ITI_SparseData*
z78d65c20d2;if(zfc39fd83d1==NULL){CVProcessError(NULL,z5274b4c3dc,
"\x43\x56\x53\x50\x41\x52\x53\x45",
"\x43\x56\x53\x70\x61\x72\x73\x65\x47\x65\x74\x4e\x75\x6d\x45\x6c\x69\x6d",
MSGDS_CVMEM_NULL);return(z5274b4c3dc);}z8f1755e318=(CVodeMem)zfc39fd83d1;if(
z078ac0b1a5==NULL){CVProcessError(z8f1755e318,z1413761acc,
"\x43\x56\x53\x50\x41\x52\x53\x45",
"\x43\x56\x53\x70\x61\x72\x73\x65\x47\x65\x74\x4e\x75\x6d\x45\x6c\x69\x6d",
za7195f91fc);return(z1413761acc);}z78d65c20d2=(ITI_SparseData*)z078ac0b1a5;*
zcd73a567da=z78d65c20d2->zd262c6ec37;return(z1cb858b9f6);}int 
CVSparseGetNumCodeGen(void*zfc39fd83d1,long int*z35bf3f87aa){CVodeMem 
z8f1755e318;ITI_SparseData*z78d65c20d2;if(zfc39fd83d1==NULL){CVProcessError(NULL
,z5274b4c3dc,"\x43\x56\x53\x50\x41\x52\x53\x45",
"\x43\x56\x53\x70\x61\x72\x73\x65\x47\x65\x74\x4e\x75\x6d\x43\x6f\x64\x65\x47\x65\x6e"
,MSGDS_CVMEM_NULL);return(z5274b4c3dc);}z8f1755e318=(CVodeMem)zfc39fd83d1;if(
z078ac0b1a5==NULL){CVProcessError(z8f1755e318,z1413761acc,
"\x43\x56\x53\x50\x41\x52\x53\x45",
"\x43\x56\x53\x70\x61\x72\x73\x65\x47\x65\x74\x4e\x75\x6d\x43\x6f\x64\x65\x47\x65\x6e"
,za7195f91fc);return(z1413761acc);}z78d65c20d2=(ITI_SparseData*)z078ac0b1a5;*
z35bf3f87aa=z78d65c20d2->z26760f5376;return(z1cb858b9f6);}void SetSparsePrev(
ITI_SparseData*z78d65c20d2){int z6e6181a44d;z78d65c20d2->z54807acf9f.z034e6ffe57
=z78d65c20d2->m_Sparse.z034e6ffe57;z78d65c20d2->z54807acf9f.ze05b33d1dc=
z78d65c20d2->m_Sparse.ze05b33d1dc;z78d65c20d2->z54807acf9f.zf2247982ab=
z78d65c20d2->m_Sparse.zf2247982ab;z78d65c20d2->z54807acf9f.zc54f041a7d=
z78d65c20d2->m_Sparse.zc54f041a7d;z78d65c20d2->z54807acf9f.zec3e4fdb5e=
z78d65c20d2->m_Sparse.zec3e4fdb5e;for(z6e6181a44d=(0x197c+1099-0x1dc7);
z6e6181a44d<z78d65c20d2->m_Sparse.z034e6ffe57;z6e6181a44d++)z78d65c20d2->
z54807acf9f.zdd87164e4a[z6e6181a44d]=z78d65c20d2->m_Sparse.zdd87164e4a[
z6e6181a44d];for(z6e6181a44d=(0x36b+3807-0x124a);z6e6181a44d<z78d65c20d2->
m_Sparse.ze05b33d1dc+(0xc5f+1251-0x1141);z6e6181a44d++)z78d65c20d2->z54807acf9f.
z5ccd45e7a8[z6e6181a44d]=z78d65c20d2->m_Sparse.z5ccd45e7a8[z6e6181a44d];}void 
z2526dc3a0a(struct z5baae04982*z9a26be94d7,char*zb30cbb84a3){z24c056d577 
zce99d8264d,z26dbd73a5e;int zfc2f2d1ec5;zfc2f2d1ec5=sprintf(zb30cbb84a3,
"\x72\x6f\x77" "\t" "\x63\x6f\x6c\x75\x6d\x6e" "\t" "\x76\x61\x6c\x75\x65" "\n")
;for(zce99d8264d=(0x19b1+2427-0x232c);zce99d8264d<z9a26be94d7->zf2247982ab;
zce99d8264d++)for(z26dbd73a5e=z9a26be94d7->z5ccd45e7a8[zce99d8264d];z26dbd73a5e<
z9a26be94d7->z5ccd45e7a8[zce99d8264d+(0xef9+3906-0x1e3a)];z26dbd73a5e++)
zfc2f2d1ec5+=sprintf(&zb30cbb84a3[zfc2f2d1ec5],
"\x25\x6c\x64" "\t" "\x25\x6c\x64" "\t" "\x25\x2e\x31\x37\x67" "\n",zce99d8264d,
z9a26be94d7->zdd87164e4a[z26dbd73a5e],z9a26be94d7->z9e4098361d[z26dbd73a5e]);}
void z6f8ca8964f(CVodeMem z8f1755e318,struct z5baae04982*z9a26be94d7,char**
zb30cbb84a3,size_t za72522e016){z24c056d577 zce99d8264d,z26dbd73a5e;size_t 
zfc2f2d1ec5=za72522e016-(0x698+3652-0x14db);int z962b2881df;z962b2881df=
z8f1755e318->cv_trwidth>(0x1200+824-0x151f)?z8f1755e318->cv_trwidth:
(0x10c5+2281-0x1995);*zb30cbb84a3=malloc((z9a26be94d7->zf2247982ab+
(0x174+8571-0x22ee))*(z9a26be94d7->zc54f041a7d*(z962b2881df+(0x103+7657-0x1eeb))
+z8f1755e318->cv_dtrwidth+(0x775+3194-0x13ee))+za72522e016);if(*zb30cbb84a3!=
NULL){size_t size=z9a26be94d7->zf2247982ab*sizeof(double);double*zcb41917595=
malloc(size);if(zcb41917595!=NULL){zfc2f2d1ec5+=sprintf(*zb30cbb84a3+zfc2f2d1ec5
,"\x25\x2a\x73" "\t",z8f1755e318->cv_dtrwidth,"");for(z26dbd73a5e=
(0x2268+480-0x2448);z26dbd73a5e<z9a26be94d7->zc54f041a7d-(0xd67+24-0xd7e);
z26dbd73a5e++)zfc2f2d1ec5+=sprintf(*zb30cbb84a3+zfc2f2d1ec5,"\x25\x2a\x73" "\t",
z962b2881df,z8f1755e318->cv_stateNames[z26dbd73a5e]);zfc2f2d1ec5+=sprintf(*
zb30cbb84a3+zfc2f2d1ec5,"\x25\x2a\x73" "\n",z962b2881df,z8f1755e318->
cv_stateNames[z9a26be94d7->zc54f041a7d-(0x1917+2866-0x2448)]);for(zce99d8264d=
(0x1e0f+1803-0x251a);zce99d8264d<z9a26be94d7->zf2247982ab;zce99d8264d++){memset(
zcb41917595,(0xe67+204-0xf33),size);for(z26dbd73a5e=z9a26be94d7->z5ccd45e7a8[
zce99d8264d];z26dbd73a5e<z9a26be94d7->z5ccd45e7a8[zce99d8264d+
(0xcab+5904-0x23ba)];z26dbd73a5e++){z24c056d577 z8d416ef9b0=z9a26be94d7->
zdd87164e4a[z26dbd73a5e];if(z8d416ef9b0<(0x6d1+6776-0x2149))z8d416ef9b0=-(
z8d416ef9b0+(0x144b+3809-0x232b));zcb41917595[z8d416ef9b0]=z9a26be94d7->
z9e4098361d[z26dbd73a5e];}zfc2f2d1ec5+=sprintf(*zb30cbb84a3+zfc2f2d1ec5,
"\x25\x2a\x73" "\t",z8f1755e318->cv_dtrwidth,z8f1755e318->cv_dstateNames[
zce99d8264d]);for(z26dbd73a5e=(0xdb3+6057-0x255c);z26dbd73a5e<z9a26be94d7->
zc54f041a7d-(0x12fd+154-0x1396);z26dbd73a5e++)zfc2f2d1ec5+=sprintf(*zb30cbb84a3+
zfc2f2d1ec5,"\x25\x2a\x2e\x31\x37\x67" "\t",z962b2881df,zcb41917595[z26dbd73a5e]
);zfc2f2d1ec5+=sprintf(*zb30cbb84a3+zfc2f2d1ec5,"\x25\x2a\x2e\x31\x37\x67" "\n",
z962b2881df,zcb41917595[z9a26be94d7->zc54f041a7d-(0x100f+5223-0x2475)]);}free(
zcb41917595);}}}
#define zc5f29fa84a(z723855ccf9, type, storageDataPtr, value, z5c847f59f1)\
	switch (z723855ccf9) {\
	case SUNDIALS_SERIALIZATION_OPERATION_SERIALIZE:\
		z6eb08ccc90(type, storageDataPtr, value)\
		break;\
	case SUNDIALS_SERIALIZATION_OPERATION_DESERIALIZE:\
		zdceda3f4bf(type, storageDataPtr, value)\
		break;\
	case SUNDIALS_SERIALIZATION_OPERATION_SIZE:\
		z5c847f59f1 += sizeof(type);\
		break;\
	}
#define z6827ad272a(z723855ccf9, storageDataPtr, z499f9db273, z5c847f59f1)\
	switch (z723855ccf9) {\
	case SUNDIALS_SERIALIZATION_OPERATION_SERIALIZE:\
		z34d6de563c(storageDataPtr, z499f9db273);\
		break;\
	case SUNDIALS_SERIALIZATION_OPERATION_DESERIALIZE:\
		zd08ab6e0d1(storageDataPtr, z499f9db273);\
		break;\
	case SUNDIALS_SERIALIZATION_OPERATION_SIZE:\
		z5c847f59f1 += (0x6dc+2446-0x1068) * sizeof(unsigned) + ((0x324+4186-0x137c) +\
 (0x11f0+3410-0x1f40) * (z499f9db273)->zec3e4fdb5e + (z499f9db273)->zc54f041a7d \
+ (0x1726+3731-0x25b8)) * sizeof(z24c056d577) + (z499f9db273)->zec3e4fdb5e * \
sizeof(value);\
		break;\
	}
#define za42d8de736(z723855ccf9, storageDataPtr, z7e959727c4, z499f9db273, \
z5c847f59f1)\
	switch (z723855ccf9) {\
	case SUNDIALS_SERIALIZATION_OPERATION_SERIALIZE:\
		zbaac5bbd3a(storageDataPtr, z7e959727c4, z499f9db273);\
		break;\
	case SUNDIALS_SERIALIZATION_OPERATION_DESERIALIZE:\
		z69391c23cc(storageDataPtr, z7e959727c4, z499f9db273);\
		break;\
	case SUNDIALS_SERIALIZATION_OPERATION_SIZE:\
		z5c847f59f1 += ((0x393+8767-0x25c7) + (z7e959727c4)->z29f7835664 + (\
z7e959727c4)->zf59d98a745 + (z499f9db273)->zf2247982ab + (z499f9db273)->\
zc54f041a7d + (z7e959727c4)->ze90daf6de2 + ((z499f9db273)->zf2247982ab > (\
z499f9db273)->zc54f041a7d ? (z499f9db273)->zc54f041a7d : (z499f9db273)->\
zf2247982ab) - (z7e959727c4)->z88f450ae47) * sizeof(z24c056d577) + \
(0x14ba+480-0x1696) * sizeof(value) + sizeof(z991d65e01a);\
		break;\
	}
long int z0bc74fe1cb(int z723855ccf9,void*z11a0670315,void**storageDataPtr){long
 int zddd0dd90ea=(0x34a+5237-0x17bf);long int zce99d8264d;ITI_SparseData*
zc41237d2a7=(ITI_SparseData*)z11a0670315;zc5f29fa84a(z723855ccf9,long,*
storageDataPtr,zc41237d2a7->z500eaf1fbc,zddd0dd90ea)z6827ad272a(z723855ccf9,
storageDataPtr,&zc41237d2a7->m_Sparse,zddd0dd90ea)z6827ad272a(z723855ccf9,
storageDataPtr,&zc41237d2a7->z54807acf9f,zddd0dd90ea)za42d8de736(z723855ccf9,
storageDataPtr,&zc41237d2a7->zc71e9cd244,&zc41237d2a7->m_Sparse,zddd0dd90ea)for(
zce99d8264d=(0x110d+2404-0x1a71);zce99d8264d<zc41237d2a7->z500eaf1fbc;++
zce99d8264d)zc5f29fa84a(z723855ccf9,double,*storageDataPtr,zc41237d2a7->
zb248acdbc7[zce99d8264d],zddd0dd90ea)for(zce99d8264d=(0x1398+2157-0x1c05);
zce99d8264d<zc41237d2a7->z500eaf1fbc;++zce99d8264d)zc5f29fa84a(z723855ccf9,
double,*storageDataPtr,zc41237d2a7->z625199ef9a[zce99d8264d],zddd0dd90ea)for(
zce99d8264d=(0x143a+2040-0x1c32);zce99d8264d<zc41237d2a7->z500eaf1fbc*
zc41237d2a7->z500eaf1fbc;++zce99d8264d)zc5f29fa84a(z723855ccf9,int,*
storageDataPtr,zc41237d2a7->z22a80c7c9a[zce99d8264d],zddd0dd90ea)for(zce99d8264d
=(0xba1+6495-0x2500);zce99d8264d<zc41237d2a7->z500eaf1fbc+(0x1fa+1763-0x8dc);++
zce99d8264d)zc5f29fa84a(z723855ccf9,long,*storageDataPtr,zc41237d2a7->
z6e19225a91[zce99d8264d],zddd0dd90ea)for(zce99d8264d=(0xdc7+2821-0x18cc);
zce99d8264d<zc41237d2a7->z500eaf1fbc;++zce99d8264d)zc5f29fa84a(z723855ccf9,int,*
storageDataPtr,zc41237d2a7->z5126954186[zce99d8264d],zddd0dd90ea)for(zce99d8264d
=(0x1100+2789-0x1be5);zce99d8264d<zc41237d2a7->z500eaf1fbc;++zce99d8264d)
zc5f29fa84a(z723855ccf9,int,*storageDataPtr,zc41237d2a7->zb776f37529[zce99d8264d
],zddd0dd90ea)zc5f29fa84a(z723855ccf9,long,*storageDataPtr,zc41237d2a7->
z972a0c3c3b,zddd0dd90ea)zc5f29fa84a(z723855ccf9,long,*storageDataPtr,zc41237d2a7
->z270e86c352,zddd0dd90ea)zc5f29fa84a(z723855ccf9,long,*storageDataPtr,
zc41237d2a7->zd262c6ec37,zddd0dd90ea)zc5f29fa84a(z723855ccf9,long,*
storageDataPtr,zc41237d2a7->z26760f5376,zddd0dd90ea)zc5f29fa84a(z723855ccf9,long
,*storageDataPtr,zc41237d2a7->z21dfaed2ff,zddd0dd90ea)zc5f29fa84a(z723855ccf9,
long,*storageDataPtr,zc41237d2a7->z1b10328be9,zddd0dd90ea)zc5f29fa84a(
z723855ccf9,long,*storageDataPtr,zc41237d2a7->z2166c6aec0,zddd0dd90ea)return 
zddd0dd90ea;}long int z74de6aad74(void*z11a0670315){return z0bc74fe1cb(
SUNDIALS_SERIALIZATION_OPERATION_SIZE,z11a0670315,NULL);}long int ze25ef2447e(
void*z11a0670315,void**storageDataPtr){return z0bc74fe1cb(
SUNDIALS_SERIALIZATION_OPERATION_SERIALIZE,z11a0670315,storageDataPtr);}long int
 zef2b3bfa61(void*z11a0670315,void**storageDataPtr){return z0bc74fe1cb(
SUNDIALS_SERIALIZATION_OPERATION_DESERIALIZE,z11a0670315,storageDataPtr);}
