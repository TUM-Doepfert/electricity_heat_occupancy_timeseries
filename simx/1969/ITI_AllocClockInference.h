/**
 * ITI_AllocClockInference.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#if !defined(_ITI_ALLOC_CLOCKINFERENCE)
#define _ITI_ALLOC_CLOCKINFERENCE

#include "ITI_crt.h"

ITI_FUNCTIONS_API int AllocIGData(ITI_Partition* pPart, ITI_AllocateMemory allocateMemory);
ITI_FUNCTIONS_API int FreeIGData(ITI_Partition* pPart, ITI_FreeMemory freeMemory);

#endif
