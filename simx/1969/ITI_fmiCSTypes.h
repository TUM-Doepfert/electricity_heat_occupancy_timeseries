/**
 * ITI_fmiCSTypes.h
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#if !defined(_fmi_CS_ITI_Types)
#define _fmi_CS_ITI_Types

#include "ITI_Types.h"
#include "fmiFunctions.h"
#include "sundials/include/nvector/nvector_serial.h"

#define ITI_MAX_REAL_INPUT_DER_ORDER 2

enum ITI_fmiVarKind {
	ITI_fmiContVariable=0,
	ITI_fmiDiscVariable=1,
	ITI_fmiInput=2,
	ITI_fmiOutput=3,
	ITI_fmiParameter=4,

	ITI_fmiDerivative=5,
	ITI_fmiEventIndicator=6,

	ITI_fmiDiscInput = 8
};

enum ITI_fmiCSMode {
	ITI_fmiCSInstantiated=0,
	ITI_fmiCSInitialized=1,
	ITI_fmiCSStepping=2,
	ITI_fmiCSTerminated=3,
	ITI_fmiCSError=4,
};


typedef struct ITI_fmiCSComponent {
	fmiCallbackFunctions functions;
	fmiBoolean loggingOn;
	char instanceName[255];

	ITI_SolverData* sd;

	fmiBoolean bError;
	fmiBoolean bEventPending;

	enum ITI_fmiCSMode mode;

	void* pData;

	fmiReal tc0;
	fmiReal tc1;
	fmiReal H;

	fmiReal tLastInputInterpolation;
	fmiBoolean uInterpolationValid;

	N_Vector ur[ITI_MAX_REAL_INPUT_DER_ORDER+1];
	N_Vector uModel;

} ITI_fmiCSComponent;

#endif
