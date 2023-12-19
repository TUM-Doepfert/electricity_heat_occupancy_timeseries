/*
 * -----------------------------------------------------------------
 * This is the implementation file for the CVODE tracing functions.
 *------------------------------------------------------------------
 */

/*=================================================================*/
/*             Import Header Files                                 */
/*=================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <sundials/sundials_nvector.h>
#include <sundials/sundials_dense.h>

#include <cvode/cvode_tracing.h>

/*=================================================================*/
/*             Defines                                             */
/*=================================================================*/

/*=================================================================*/
/*             Macros                                              */
/*=================================================================*/

#ifndef max
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#endif

/*=================================================================*/
/*             Private Helper Functions Prototypes                 */
/*=================================================================*/

/*
 * =================================================================
 * EXPORTED FUNCTIONS IMPLEMENTATION
 * =================================================================
 */

void DensePrintStr(CVodeMem cv_mem, DenseMat A, char **str, size_t offset)
{
	long int i, j;
	size_t ctr = offset - 1;
	int width;

	width = cv_mem->cv_trwidth > 25 ? cv_mem->cv_trwidth : 25;
	*str = malloc((A->M + 1) * (A->N * (width + 1) + cv_mem->cv_dtrwidth + 1) + offset);
	if (*str != NULL) {
		ctr += sprintf(*str + ctr, "%*s\t", cv_mem->cv_dtrwidth, "");
		for (j = 0; j < A->N - 1; j++)
			ctr += sprintf(*str + ctr, "%*s\t", width, cv_mem->cv_stateNames[j]);
		ctr += sprintf(*str + ctr, "%*s\n", width, cv_mem->cv_stateNames[A->N - 1]);
		for (i = 0; i < A->M; i++) {
			ctr += sprintf(*str + ctr, "%*s\t", cv_mem->cv_dtrwidth, cv_mem->cv_dstateNames[i]);
			for (j = 0; j < A->N - 1; j++)
				ctr += sprintf(*str + ctr, "%*.17g\t", width, A->data[j][i]);
			ctr += sprintf(*str + ctr, "%*.17g\n", width, A->data[A->N - 1][i]);
		}
	}
}

void InitializeTracing(CVodeMem cv_mem)
{
	cv_mem->cv_tfun = NULL;
	cv_mem->cv_tf_data = NULL;
	cv_mem->trRes = 0;
	cv_mem->trStates = 0;
	cv_mem->trDer = 0;
	cv_mem->trNewtonUpdate = 0;
	cv_mem->trJac = 0;
	cv_mem->trStepTrue = 0;
	cv_mem->trResTrue = 0;
	cv_mem->trStatesTrue = 0;
	cv_mem->trDerTrue = 0;
	cv_mem->trStepFalse = 0;
	cv_mem->trResFalse = 0;
	cv_mem->trStatesFalse = 0;
	cv_mem->trDerFalse = 0;
	cv_mem->trNewtonUpdateFalse = 0;
	cv_mem->cv_trMallocDone = FALSE;
	cv_mem->cv_states = NULL;
	cv_mem->cv_derivatives = NULL;
	cv_mem->cv_residuals = NULL;
	cv_mem->cv_corrections = NULL;
	cv_mem->cv_stateNames = NULL;
	cv_mem->cv_dstateNames = NULL;
}

void InitializeCorrectorTracing(CVodeMem cv_mem)
{
	int maxiter = max(5, cv_mem->cv_maxcor);
	long nr, ni;

	N_VSpace(cv_mem->cv_tempv, &nr, &ni);
	cv_mem->cv_dim = nr;
	cv_mem->cv_states = malloc((maxiter + 1)* nr * sizeof(realtype));
	cv_mem->cv_derivatives = malloc(maxiter * nr * sizeof(realtype));
	cv_mem->cv_residuals = malloc(maxiter * nr * sizeof(realtype));
	cv_mem->cv_corrections = malloc(maxiter * nr * sizeof(realtype));

	cv_mem->cv_trMallocDone = TRUE;
}

void FreeCorrectorTracing(CVodeMem cv_mem)
{
	free(cv_mem->cv_states);
	free(cv_mem->cv_derivatives);
	free(cv_mem->cv_residuals);
	free(cv_mem->cv_corrections);
}

void StrPrintHistory(CVodeMem cv_mem, double *history, int kind, char **str)
{
	int nCol, width;
	char **names;

	if (kind == tr_states)
		nCol = cv_mem->cv_mnewt + 1;
	else
		nCol = cv_mem->cv_mnewt;

	if (kind == tr_states || kind == tr_corr) {
		width = cv_mem->cv_trwidth;
		names = cv_mem->cv_stateNames;
	} else {
		width = cv_mem->cv_dtrwidth;
		names = cv_mem->cv_dstateNames;
	}

	*str = malloc((cv_mem->cv_dim + 1) * ((nCol + 1) * 26 + width + 1) + 1);
	if (*str != NULL) {
		long int i;
		int j, ctr = 0;
		ctr += sprintf(*str, "%*s\t", width, "");
		if (kind != tr_corr) {
			ctr += sprintf(*str + ctr, "%25s", "predictor, iteration 0");
			for (j = 0; j < nCol; j++)
				ctr += sprintf(*str + ctr, "\t%23s %1d", " corrector, iteration", j + 1);
			ctr += sprintf(*str + ctr, "\n");
		} else {
			for (j = 0; j < nCol; j++)
				ctr += sprintf(*str + ctr, "%23s %1d\t", " corrector, iteration", j + 1);
			ctr += sprintf(*str + ctr, "%23s %1d\n", " corrector, iteration", nCol + 1);
		}
		for (i = 0; i < cv_mem->cv_dim; i++) {
			ctr += sprintf(*str + ctr, "%*s\t", width, names[i]);
			for (j = 0; j < nCol; j++)
				ctr += sprintf(*str + ctr, "%25.17g\t", history[j * cv_mem->cv_dim + i]);
			ctr += sprintf(*str + ctr, "%25.17g\n", history[nCol * cv_mem->cv_dim + i]);
		}
	}
}

void StrPrintHistoryLast(CVodeMem cv_mem, double *history, int kind, char **str)
{
	int iCol, width;
	char **names;

	if (kind == tr_states)
		iCol = cv_mem->cv_mnewt + 1;
	else
		iCol = cv_mem->cv_mnewt;

	if (kind == tr_states || kind == tr_corr) {
		width = cv_mem->cv_trwidth;
		names = cv_mem->cv_stateNames;
	} else {
		width = cv_mem->cv_dtrwidth;
		names = cv_mem->cv_dstateNames;
	}

	*str = malloc(cv_mem->cv_dim * (25 + width + 2) + 1);
	if (*str != NULL) {
		long int i;
		int ctr = 0;
		for (i = 0; i < cv_mem->cv_dim; i++)
			ctr += sprintf(*str + ctr, "%*s\t%25.17g\n", width, names[i], history[iCol * cv_mem->cv_dim + i]);
	}
}
