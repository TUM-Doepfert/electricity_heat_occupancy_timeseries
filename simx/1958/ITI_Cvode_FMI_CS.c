/**
 * ITI_Cvode_FMI_CS.c
 * SimulationX 4.2.1.68046 (12/15/20)
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
**/

#include "ITI_crt.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <stdarg.h>
#include <stdlib.h>
#include <signal.h>
#include <ctype.h>

#include "ITI_fmiCSTypes.h"
#include "ITI_Cvode_FMI_CS.h"
#include "ITI_Cvode_base.h"
#include "ITI_SolverHelpers.h"

void FMI_CS_OnPrepareSaveOutputs(size_t pid, void* pData) {}
void FMI_CS_OnSaveOutputs(size_t pid, void* pData, ITI_bool force) {}
void FMI_CS_OnFinishSaveOutputs(void* pData) {}

int FMI_CS_OnSetInputs(void* pData, double t, ITI_CompositeData* u)
{
	size_t pid = 0;
	ITI_SolverData* cvd = (ITI_SolverData*)pData;
	ITI_CVodeContext* cvc = (ITI_CVodeContext*)cvd->sc[pid];
	ITI_Partition* pPart = &cvd->partition[pid];
	ITI_fmiCSComponent* _c = (ITI_fmiCSComponent*)pPart->curr->sInfo.pContainer;

	 
	if((pPart->curr->size.iu_real>0) &&((t!=_c->tLastInputInterpolation) || (_c->uInterpolationValid==fmiFalse)))
	{
		size_t j;
		fmiReal val;
		fmiReal H = t-_c->tc0;
		fmiReal Hpj = 1;
		size_t jFac = 1;
		fmiReal f;

		 
		NV_DATA_S(_c->uModel)=pPart->curr->u.realData;

		N_VConst(0.0, _c->uModel);

		for(j=0; j<ITI_MAX_REAL_INPUT_DER_ORDER+1; j++)
		{
			f=1.0/((fmiReal)jFac)*Hpj;
			N_VLinearSum(f, _c->ur[j], 1, _c->uModel, _c->uModel);
			val=NV_Ith_S(_c->ur[j],0);
			jFac*=j+1;
			Hpj*=H;
		}
		_c->tLastInputInterpolation=t;
		_c->uInterpolationValid=fmiTrue;
	}
	return 0;
}
