
#include "ITI_crt.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <float.h>
#include <stdarg.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>
#include "ITI_Cvode_helpers.h"
#include "sundials/include/nvector/nvector_serial.h"
#include "sundials/src/cvode/cvode_impl.h"
#include "sundials/src/cvode/cvode_dense_impl.h"
#include "sundials/include/sundials/sundials_math.h"
void BuildEffJac(ITI_SparseData*z78d65c20d2,ITI_SortJac*z3cc0d439ea,ITI_char*
z89a5c64780,ITI_int z600a6fd606,ITI_uint*zb36402356f){ITI_int*zb3014479f7=(
ITI_int*)calloc(z600a6fd606*z600a6fd606,sizeof(ITI_int));ITI_int*z0ba4bcbb4e=(
ITI_int*)calloc(z600a6fd606,sizeof(ITI_int));ITI_int*z5fc72ba8be=(ITI_int*)
calloc(z600a6fd606*z600a6fd606,sizeof(ITI_int));ITI_int*z589c61258e=(ITI_int*)
calloc(z600a6fd606,sizeof(ITI_int));z423e955797(z3cc0d439ea,z600a6fd606);
z47fab46d62(z78d65c20d2,z3cc0d439ea,z89a5c64780,z600a6fd606,zb3014479f7);
z5e418a6660(z78d65c20d2,z3cc0d439ea,zb3014479f7,z0ba4bcbb4e,z5fc72ba8be);
z86611319ac(z0ba4bcbb4e,z589c61258e,z600a6fd606);z78d1334933(z3cc0d439ea,
z589c61258e,z5fc72ba8be,z600a6fd606);*zb36402356f=z3cc0d439ea->zb36402356f;free(
zb3014479f7);free(z0ba4bcbb4e);free(z5fc72ba8be);free(z589c61258e);}void 
z47fab46d62(ITI_SparseData*z78d65c20d2,ITI_SortJac*z3cc0d439ea,ITI_char*
z89a5c64780,ITI_int z600a6fd606,ITI_int*zb3014479f7){ITI_int zcec140f672=
(0x10cf+5211-0x252a);ITI_int z500eaf1fbc=(0x17b1+1024-0x1bb1);ITI_int 
z812c65ff2f=(0x87d+2895-0x13cc);ITI_int z6e6181a44d,zea939115e0;z78d65c20d2->
m_Sparse.ze05b33d1dc=z600a6fd606;z78d65c20d2->m_Sparse.zc54f041a7d=z600a6fd606;
z78d65c20d2->m_Sparse.zf2247982ab=z600a6fd606;z78d65c20d2->m_Sparse.zec3e4fdb5e=
z600a6fd606*z600a6fd606;for(z6e6181a44d=(0x1cb8+433-0x1e69);z6e6181a44d<
z600a6fd606*z600a6fd606;z6e6181a44d++){if((z6e6181a44d==zcec140f672*z600a6fd606+
zcec140f672)&&(!z89a5c64780[z6e6181a44d])){z78d65c20d2->m_Sparse.zdd87164e4a[
z500eaf1fbc]=z6e6181a44d%z600a6fd606;zb3014479f7[z500eaf1fbc]=
(0xb4a+5324-0x2015);z78d65c20d2->z5126954186[zcec140f672]=z500eaf1fbc;
z78d65c20d2->zb776f37529[z812c65ff2f++]=z500eaf1fbc++;}if(z89a5c64780[
z6e6181a44d]){zea939115e0=z6e6181a44d%z600a6fd606;z3cc0d439ea->zcf3f0bddab[
zea939115e0*z600a6fd606+z3cc0d439ea->z61e64063a9[zea939115e0]]=zcec140f672;
z3cc0d439ea->z61e64063a9[zea939115e0]++;z78d65c20d2->m_Sparse.zdd87164e4a[
z500eaf1fbc++]=zea939115e0;if(z6e6181a44d==zcec140f672*z600a6fd606+zcec140f672)
z78d65c20d2->z5126954186[zcec140f672]=z500eaf1fbc-(0x160c+1859-0x1d4e);}if(
z6e6181a44d%z600a6fd606==(z600a6fd606-(0xa35+209-0xb05))){zcec140f672++;
z78d65c20d2->m_Sparse.z5ccd45e7a8[zcec140f672]=z500eaf1fbc;}}z78d65c20d2->
z972a0c3c3b=z812c65ff2f;z78d65c20d2->m_Sparse.z034e6ffe57=z500eaf1fbc;
z3cc0d439ea->z034e6ffe57=z500eaf1fbc;}void z5e418a6660(ITI_SparseData*
z78d65c20d2,ITI_SortJac*z3cc0d439ea,ITI_int*zb3014479f7,ITI_int*z0ba4bcbb4e,
ITI_int*z5fc72ba8be){ITI_int zce99d8264d,z28b7e30d3d,z26dbd73a5e,z6fbc885494,
z8a0c00cf66;ITI_int*z5c0f40451f=(ITI_int*)calloc(z78d65c20d2->m_Sparse.
ze05b33d1dc,sizeof(ITI_int));for(z26dbd73a5e=(0x106b+4871-0x2372);z26dbd73a5e<
z78d65c20d2->m_Sparse.ze05b33d1dc-(0x4aa+5833-0x1b72);z26dbd73a5e++){z5c0f40451f
[z26dbd73a5e]=z78d65c20d2->m_Sparse.ze05b33d1dc;for(z6fbc885494=
(0xfa7+960-0x1367);z6fbc885494<z3cc0d439ea->z61e64063a9[z26dbd73a5e];z6fbc885494
++){zce99d8264d=z3cc0d439ea->zcf3f0bddab[z26dbd73a5e*z78d65c20d2->m_Sparse.
ze05b33d1dc+z6fbc885494];for(z28b7e30d3d=z78d65c20d2->m_Sparse.z5ccd45e7a8[
zce99d8264d];z28b7e30d3d<z78d65c20d2->m_Sparse.z5ccd45e7a8[zce99d8264d+
(0xb17+2258-0x13e8)];z28b7e30d3d++)if(!zb3014479f7[z28b7e30d3d]){z8a0c00cf66=
z78d65c20d2->m_Sparse.zdd87164e4a[z28b7e30d3d];if(z5c0f40451f[z8a0c00cf66]<
z26dbd73a5e+(0x547+5234-0x19b8)){z5c0f40451f[z8a0c00cf66]=z26dbd73a5e+
(0x122b+2225-0x1adb);z0ba4bcbb4e[z8a0c00cf66]++;z5fc72ba8be[z8a0c00cf66*
z78d65c20d2->m_Sparse.ze05b33d1dc+z26dbd73a5e]=(0xab3+4363-0x1bbd);z0ba4bcbb4e[
z26dbd73a5e]++;z5fc72ba8be[z26dbd73a5e*z78d65c20d2->m_Sparse.ze05b33d1dc+
z8a0c00cf66]=(0x116c+2674-0x1bdd);}}}}free(z5c0f40451f);}void z86611319ac(
ITI_int*z0ba4bcbb4e,ITI_int*z589c61258e,ITI_int z600a6fd606){ITI_int zce99d8264d
;ITI_int*z20ba582b43=(ITI_int*)calloc(z600a6fd606,sizeof(ITI_int));ITI_int*
z394658dec5=(ITI_int*)calloc(z600a6fd606,sizeof(ITI_int));for(zce99d8264d=
(0x645+3900-0x1581);zce99d8264d<z600a6fd606;zce99d8264d++)z20ba582b43[
z0ba4bcbb4e[zce99d8264d]]++;for(zce99d8264d=(0x99f+6352-0x226e);zce99d8264d<
z600a6fd606;zce99d8264d++)z394658dec5[zce99d8264d]=z20ba582b43[zce99d8264d-
(0xdaa+3514-0x1b63)]+z394658dec5[zce99d8264d-(0x1ae7+10-0x1af0)];for(zce99d8264d
=(0x5b8+6167-0x1dcf);zce99d8264d<z600a6fd606;zce99d8264d++){z589c61258e[
z394658dec5[z0ba4bcbb4e[zce99d8264d]]]=zce99d8264d;z394658dec5[z0ba4bcbb4e[
zce99d8264d]]++;}free(z20ba582b43);free(z394658dec5);}void z78d1334933(
ITI_SortJac*z3cc0d439ea,ITI_int*z589c61258e,ITI_int*z5fc72ba8be,ITI_int 
z600a6fd606){ITI_int zce99d8264d,z26dbd73a5e,z812c65ff2f,za04057655a;ITI_int*
z5c0f40451f=(ITI_int*)calloc(z600a6fd606,sizeof(ITI_int));for(z26dbd73a5e=
(0xdc2+2154-0x162c);z26dbd73a5e<z600a6fd606;z26dbd73a5e++){za04057655a=
(0xc0f+2635-0x165a);for(zce99d8264d=z600a6fd606-(0x968+1033-0xd70);zce99d8264d>=
(0x1c41+1415-0x21c8);zce99d8264d--)if((z5fc72ba8be[z26dbd73a5e*z600a6fd606+
z589c61258e[zce99d8264d]]==(0x1813+276-0x1927))&&(z5c0f40451f[z589c61258e[
zce99d8264d]]==(0xb8a+348-0xce6))){z5c0f40451f[z589c61258e[zce99d8264d]]=
(0x708+4003-0x16aa);z3cc0d439ea->z3e9c56f364[z3cc0d439ea->zb36402356f]++;
z3cc0d439ea->zc6a08ae4ce[z3cc0d439ea->zb36402356f*z600a6fd606+za04057655a++]=
z589c61258e[zce99d8264d];z3cc0d439ea->zd8a87c601d[z589c61258e[zce99d8264d]]=
z3cc0d439ea->zb36402356f;if(z589c61258e[zce99d8264d]!=z26dbd73a5e)for(
z812c65ff2f=(0x14c3+4541-0x2680);z812c65ff2f<z600a6fd606;z812c65ff2f++){
z5fc72ba8be[z589c61258e[zce99d8264d]*z600a6fd606+z812c65ff2f]+=z5fc72ba8be[
z26dbd73a5e*z600a6fd606+z812c65ff2f];z5fc72ba8be[z26dbd73a5e*z600a6fd606+
z812c65ff2f]=z5fc72ba8be[z589c61258e[zce99d8264d]*z600a6fd606+z812c65ff2f];}}if(
za04057655a>(0x1beb+1827-0x230e))z3cc0d439ea->zb36402356f++;}free(z5c0f40451f);}
void z423e955797(ITI_SortJac*z3cc0d439ea,ITI_int z600a6fd606){FreeEffJacData(
z3cc0d439ea);z3cc0d439ea->zcf3f0bddab=(ITI_int*)calloc(z600a6fd606*z600a6fd606,
sizeof(ITI_int));z3cc0d439ea->z61e64063a9=(ITI_int*)calloc(z600a6fd606,sizeof(
ITI_int));z3cc0d439ea->z3e9c56f364=(ITI_int*)calloc(z600a6fd606,sizeof(ITI_int))
;z3cc0d439ea->zc6a08ae4ce=(ITI_int*)calloc(z600a6fd606*z600a6fd606,sizeof(
ITI_int));z3cc0d439ea->zd8a87c601d=(ITI_int*)calloc(z600a6fd606,sizeof(ITI_int))
;z3cc0d439ea->zfcb927fa80=(ITI_real*)calloc(z600a6fd606,sizeof(ITI_real));
z3cc0d439ea->z4604308cab=(ITI_real*)calloc(z600a6fd606,sizeof(ITI_real));
z3cc0d439ea->zb36402356f=(0xa51+3452-0x17cd);z3cc0d439ea->z034e6ffe57=
(0x19f1+709-0x1cb6);}void FreeEffJacData(ITI_SortJac*z3cc0d439ea){if(z3cc0d439ea
->zcf3f0bddab!=NULL){free(z3cc0d439ea->zcf3f0bddab);z3cc0d439ea->zcf3f0bddab=
NULL;}if(z3cc0d439ea->z61e64063a9!=NULL){free(z3cc0d439ea->z61e64063a9);
z3cc0d439ea->z61e64063a9=NULL;}if(z3cc0d439ea->z3e9c56f364!=NULL){free(
z3cc0d439ea->z3e9c56f364);z3cc0d439ea->z3e9c56f364=NULL;}if(z3cc0d439ea->
zc6a08ae4ce!=NULL){free(z3cc0d439ea->zc6a08ae4ce);z3cc0d439ea->zc6a08ae4ce=NULL;
}if(z3cc0d439ea->zd8a87c601d!=NULL){free(z3cc0d439ea->zd8a87c601d);z3cc0d439ea->
zd8a87c601d=NULL;}if(z3cc0d439ea->zfcb927fa80!=NULL){free(z3cc0d439ea->
zfcb927fa80);z3cc0d439ea->zfcb927fa80=NULL;}if(z3cc0d439ea->z4604308cab!=NULL){
free(z3cc0d439ea->z4604308cab);z3cc0d439ea->z4604308cab=NULL;}}
