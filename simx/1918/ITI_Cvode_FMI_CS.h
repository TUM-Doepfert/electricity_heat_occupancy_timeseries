/**
 * ITI_Cvode_FMI_CS.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#ifndef _ITI_CVODE_FMI_CS_H_
#define _ITI_CVODE_FMI_CS_H_

#include "ITI_crt.h"

void FMI_CS_OnPrepareSaveOutputs(size_t pid, void* pData);
void FMI_CS_OnSaveOutputs(size_t pid, void* pData, ITI_bool force);
void FMI_CS_OnFinishSaveOutputs(void* pData);
int FMI_CS_OnSetInputs(void* pData, double t, ITI_CompositeData* u);

#endif
