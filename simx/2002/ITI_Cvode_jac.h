/**
 * ITI_Cvode_jac.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/


#if !defined(z4a197bf4ab)
#define z4a197bf4ab
int CalcJac(long int z3278a41716,DenseMat zf4bfdcc441,realtype t,N_Vector y,
N_Vector z5912f211db,void*zdfc42fc222,N_Vector z4f637ff870,N_Vector z84df455267,
N_Vector z112f1e371d);int ITI_CalcEffJac(long int z3278a41716,DenseMat 
zf4bfdcc441,realtype t,N_Vector y,N_Vector z5912f211db,void*zdfc42fc222,N_Vector
 z4f637ff870,N_Vector z84df455267,N_Vector z112f1e371d);int ITI_CalcEffJacSparse
(long int z3278a41716,realtype t,N_Vector y,N_Vector z5912f211db,void*
zdfc42fc222,N_Vector z4f637ff870,N_Vector z84df455267,N_Vector z112f1e371d);int 
CalcJacPar(long int z3278a41716,DenseMat zf4bfdcc441,realtype t,N_Vector y,
N_Vector z5912f211db,void*zdfc42fc222,N_Vector z4f637ff870,N_Vector z84df455267,
N_Vector z112f1e371d);int ITI_CalcEffJacPar(long int z3278a41716,DenseMat 
zf4bfdcc441,realtype t,N_Vector y,N_Vector z5912f211db,void*zdfc42fc222,N_Vector
 z4f637ff870,N_Vector z84df455267,N_Vector z112f1e371d);int 
ITI_CalcEffJacSparsePar(long int z3278a41716,realtype t,N_Vector y,N_Vector 
z5912f211db,void*zdfc42fc222,N_Vector z4f637ff870,N_Vector z84df455267,N_Vector 
z112f1e371d);
#endif

