/**
 * ITI_Cvode_model_if.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#ifndef _ITI_CVODE_MODEL_IF_H_
#define _ITI_CVODE_MODEL_IF_H_

#include "ITI_crt.h"

#include "sundials/include/nvector/nvector_serial.h"
#include "sundials/src/cvode/cvode_impl.h"
#include "sundials/src/cvode/cvode_dense_impl.h"
#include "sundials/include/sundials/sundials_math.h"

void ErrHandler(int error_code, const char *module, const char *function,char *msg, void *eh_data);
int CalcRHS(realtype t, N_Vector x, N_Vector xdot, void* f_data);
int CalcZeros(realtype t, N_Vector y, realtype *gout, void *g_data, int type);
void TraceFunction(char *msg, char *msl, void *tf_data);

#endif
