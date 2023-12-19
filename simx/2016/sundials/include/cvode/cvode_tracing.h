/*
 * -----------------------------------------------------------------
 * This is the header file for the CVODE tracing functions.
 *------------------------------------------------------------------
 */

#ifndef _CVODE_TRACING_H
#define _CVODE_TRACING_H

#ifdef __cplusplus  /* wrapper to enable C++ usage */
extern "C" {
#endif

#include <sundials/sundials_dense.h>
#include <nvector/nvector_serial.h>
#include <../src/cvode/cvode_impl.h>

enum trKind {tr_states, tr_der, tr_corr, tr_res};

/*
 * -----------------------------------------------------------------
 * Function : DensePrintStr
 * -----------------------------------------------------------------
 * Usage : DensePrintStr(A, str);
 * -----------------------------------------------------------------
 * This routine prints the M by N dense matrix A to string str with
 * an offset as it would normally appear on paper. It is intended as
 * a debugging tool with small values of M and N. The elements are
 * printed using the %g option.
 * -----------------------------------------------------------------
 */

void DensePrintStr(CVodeMem cv_mem, DenseMat A, char **str, size_t offset);

void InitializeTracing(CVodeMem cv_mem);

void InitializeCorrectorTracing(CVodeMem cv_mem);
void FreeCorrectorTracing(CVodeMem cv_mem);

void StrPrintHistory(CVodeMem cv_mem, double *history, int kind, char **str);
void StrPrintHistoryLast(CVodeMem cv_mem, double *history, int kind, char **str);

#ifdef __cplusplus
}
#endif

#endif
