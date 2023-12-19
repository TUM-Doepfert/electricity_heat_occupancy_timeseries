
#ifndef z114d0912d7
#define z114d0912d7
#ifdef __cplusplus  
extern"\x43"{
#endif
#include <sundials/sundials_dense.h>
#include <sundials/sundials_nvector.h>
#include <../src/cvode/cvode_impl.h>
#include "ma_sparse.h"
#define zd30a145af1  (0xcad+3451-0x19f6)
#define z87265f3e63 RCONST(0.2)
typedef int(*CVSparseJacFn)(long int z3278a41716,realtype t,N_Vector y,N_Vector 
z5912f211db,void*zdfc42fc222,N_Vector z4f637ff870,N_Vector z84df455267,N_Vector 
z112f1e371d);int CVSparse(void*zfc39fd83d1,long int z3278a41716);int 
CVSparseSetJacFn(void*zfc39fd83d1,CVSparseJacFn z4d08893320,void*zdfc42fc222);
int zc875b86afb(void*zfc39fd83d1,long int*zbb0cb88046,long int*z3b32a5d8c9);int 
z9c3bba7f11(void*zfc39fd83d1,long int*zd94534fdae);int z0ed6cebf3a(void*
zfc39fd83d1,long int*z845b0cfcd8);int CVSparseGetNumDecomp(void*zfc39fd83d1,long
 int*z1c95cc38d4);int CVSparseGetNumElim(void*zfc39fd83d1,long int*zcd73a567da);
int CVSparseGetNumCodeGen(void*zfc39fd83d1,long int*z35bf3f87aa);int z9284133f53
(void*zfc39fd83d1,int*z9f1a7be944);char*zcc60383671(int z9f1a7be944);
#define z1cb858b9f6           (0x1568+2421-0x1edd)
#define z5274b4c3dc         -(0xa1f+5741-0x208b)
#define z1413761acc        -(0x49b+3308-0x1185)
#define z1b941eefee        -(0x1b0f+834-0x1e4e)
#define z5f6198da16         -(0x781+7483-0x24b8)
#define za2883f7c51  -(0x2f3+6651-0x1ce9)
#define zc1a9b6e483    -(0x1965+3100-0x257b)
typedef struct ITI_SparseData{struct z5baae04982 m_Sparse;struct z5baae04982 
z54807acf9f;struct z307b03c7b0 zc71e9cd244;double*zb248acdbc7;double*z625199ef9a
;long int*z22a80c7c9a;long int*z6e19225a91;int*z5126954186;int*zb776f37529;long 
int z972a0c3c3b;long int z270e86c352;long int zd262c6ec37;long int z26760f5376;
long int z21dfaed2ff;long int z1b10328be9;long int z2166c6aec0;void*z353e857643;
long int z500eaf1fbc;CVSparseJacFn z3960d6c10a;int zb9132752a5;}ITI_SparseData;
void AllocSparseData(ITI_SparseData**z78d65c20d2,long int z3278a41716);void 
FreeSparseData(ITI_SparseData**z78d65c20d2);void SetIntoSparse(ITI_SparseData*
z78d65c20d2);void SetSparsePrev(ITI_SparseData*z78d65c20d2);void z2526dc3a0a(
struct z5baae04982*z9a26be94d7,char*zb30cbb84a3);void z6f8ca8964f(CVodeMem 
z8f1755e318,struct z5baae04982*z9a26be94d7,char**zb30cbb84a3,size_t za72522e016)
;long int z74de6aad74(void*z11a0670315);long int ze25ef2447e(void*z11a0670315,
void**storageDataPtr);long int zef2b3bfa61(void*z11a0670315,void**storageDataPtr
);
#define za7195f91fc \
"\x43\x56\x53\x50\x41\x52\x53\x45\x20\x6d\x65\x6d\x6f\x72\x79\x20\x69\x73\x20\x4e\x55\x4c\x4c\x2e"
#ifdef __cplusplus
}
#endif
#endif

