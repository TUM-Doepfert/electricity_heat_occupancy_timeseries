/**
 * ITI_crt.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#ifndef ITI_CRT_INCLUDE
#define ITI_CRT_INCLUDE

 

#ifdef REAL_TIME
#define ITI_BLOCK_SIZE 1048576
#else
#define ITI_BLOCK_SIZE 8192
#endif

#ifndef MAX_DELAY_BUFFER_SIZE
#define MAX_DELAY_BUFFER_SIZE 655360
#endif

#define ITI_FUNCTIONS_API

#define _ITI_INLINE __inline

#ifdef _MSC_VER
#pragma warning(disable : 4996)
#endif

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <signal.h>
#include "ITI_Types.h"
#include "ITI_big_uint.h"
#include "ITI_Functions.h"
#include "ITI_Declarations.h"
#include "ITI_BlockDeclarations.h"
#include "ITI_Memory.h"
#include "ITI_ArrayFunctions.h"
#include "ITI_AllocClockInference.h"
#include "ITI_ClockInference.h"
#include "ITI_SolverHelpers.h"

#endif
