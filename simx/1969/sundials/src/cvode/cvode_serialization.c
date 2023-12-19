/*
 * -----------------------------------------------------------------
 * This is the implementation file for the CVODE serialization
 * functions.
 *------------------------------------------------------------------
 */

/*=================================================================*/
/*             Import Header Files                                 */
/*=================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "cvode_impl.h"
#include "cvode_dense_impl.h"
#include <cvode/cvode_serialization.h>
#include <sundials/sundials_serialization.h>

/*=================================================================*/
/*             Defines                                             */
/*=================================================================*/

/*=================================================================*/
/*             Macros                                              */
/*=================================================================*/

/* If this define is enabled, all serialization code is done in
 * dedicated functions that avoid the macros to switch to code based
 * on operation flag (for performance increase). This requires the
 * code-generator to run over the generic macro code and fill in
 * the helper functions.
 */
/* #undef CVODE_SERIALIZATION_GENERATED_CODE */

#define CVODE_LINSOLV_SERIALIZATION(op, storageDataPtr, mem_size)\
	switch (op) {\
	case SUNDIALS_SERIALIZATION_OPERATION_SERIALIZE:\
		cv_mem->cv_LinSolvSerialization(cv_mem->cv_lmem, storageDataPtr);\
		break;\
	case SUNDIALS_SERIALIZATION_OPERATION_DESERIALIZE:\
		cv_mem->cv_LinSolvDeserialization(cv_mem->cv_lmem, storageDataPtr);\
		break;\
	case SUNDIALS_SERIALIZATION_OPERATION_SIZE:\
		mem_size += cv_mem->cv_LinSolvSerializationSize(cv_mem->cv_lmem);\
		break;\
	}

#define CVODE_USER_SERIALIZATION(op, storageDataPtr, mem_size)\
	switch (op) {\
	case SUNDIALS_SERIALIZATION_OPERATION_SERIALIZE:\
		cv_mem->cv_UserSerialization(cv_mem->cv_UserSerializationData, storageDataPtr);\
		break;\
	case SUNDIALS_SERIALIZATION_OPERATION_DESERIALIZE:\
		cv_mem->cv_UserDeserialization(cv_mem->cv_UserSerializationData, storageDataPtr);\
		break;\
	case SUNDIALS_SERIALIZATION_OPERATION_SIZE:\
		mem_size += cv_mem->cv_UserSerializationSize(cv_mem->cv_UserSerializationData);\
		break;\
	}

/*=================================================================*/
/*             Private Helper Functions Prototypes                 */
/*=================================================================*/

long int CVodeSerializationPrivate(int op, void *cvode_mem, void **storageDataPtr) {
  CVodeMem cv_mem = (CVodeMem)cvode_mem;
  /* Variable to count memory size if operation is SUNDIALS_SERIALIZATION_OPERATION_SIZE */
  long int memSize = 0;
  void * storageDataPtrStart;
  long int i, lmax;

  /* Store start address of memory block */
  if (op != SUNDIALS_SERIALIZATION_OPERATION_SIZE)
    storageDataPtrStart = *storageDataPtr;

  /* Read/write magic header and version number is no longer maintained here.
   * This information is now used at an upper level. */

  if (cv_mem == NULL) /* should not happen */
	return memSize;

  /* machine unit roundoff */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_uround, memSize)
  /* lmm = CV_ADAMS or CV_BDF */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_lmm, memSize)
  switch (cv_mem->cv_lmm) {
    case CV_ADAMS : lmax = ADAMS_Q_MAX + 1; break;
    case CV_BDF   : lmax = BDF_Q_MAX + 1; break;
  }
  /* iter = CV_FUNCTIONAL or CV_NEWTON */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_iter, memSize)
  /* itol = CV_SS, CV_SV, CV_WF, CV_NN */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_itol, memSize)
  /* relative tolerance */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_reltol, memSize)
  switch (cv_mem->cv_itol) {
    case CV_SS :
      /* scalar absolute tolerance */
      CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_Sabstol, memSize)
      break;
	case CV_SV :
	case CV_WF :
      /* vector absolute tolerance */
      CVODE_SERIALIZE_NVECTOR(op, storageDataPtr, cv_mem->cv_Vabstol, memSize)
      break;
  }

  /* Nordsieck array, of size N x (q+1). */
  for (i = 0; i < lmax; ++i)
    CVODE_SERIALIZE_NVECTOR(op, storageDataPtr, cv_mem->cv_zn[i], memSize)

  /* error weight vector */
  CVODE_SERIALIZE_NVECTOR(op, storageDataPtr, cv_mem->cv_ewt, memSize)
  /* y is used as temporary storage by the solver */
/*  CVODE_SERIALIZE_NVECTOR(op, storageDataPtr, &cv_mem->cv_y, memSize)*/
  /* In the context of the solution of the nonlinear equation, acor = y_n(m) - y_n(0).
     On return, this vector is scaled to give the est. local err. */
  CVODE_SERIALIZE_NVECTOR(op, storageDataPtr, cv_mem->cv_acor, memSize)
  /* temporary storage vector */
  CVODE_SERIALIZE_NVECTOR(op, storageDataPtr, cv_mem->cv_tempv, memSize)
  /* temporary storage vector */
  CVODE_SERIALIZE_NVECTOR(op, storageDataPtr, cv_mem->cv_ftemp, memSize)

  CVODE_SERIALIZE_A(op, booleantype, *storageDataPtr, cv_mem->cv_tstopset, memSize)
  CVODE_SERIALIZE_A(op, booleantype, *storageDataPtr, cv_mem->cv_istop, memSize)
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_tstop, memSize)

  /* current order */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_q, memSize)
  /* order to be used on the next step = q-1, q, or q+1 */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_qprime, memSize)
  /* order to be used on the next step */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_next_q, memSize)
  /* number of internal steps to wait before considering a change in q */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_qwait, memSize)
  /* L = q + 1 */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_L, memSize)
  /* initial step size */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_hin, memSize)
  /* current step size */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_h, memSize)
  /* step size to be used on the next step */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_hprime, memSize)
  /* step size to be used on the next step */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_next_h, memSize)
  /* eta = hprime / h */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_eta, memSize)
  /* value of h used in zn */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_hscale, memSize)
  /* current internal value of t */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_tn, memSize)
  /* value of tret last returned by CVode */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_tretlast, memSize)
  /* array of previous q+1 successful step sizes indexed from 1 to q+1 */
  for (i = 0; i < lmax+1; ++i)
    CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_tau[i], memSize)
  /* array of test quantities indexed from 1 to NUM_TESTS(=5) */
  for (i = 0; i < NUM_TESTS+1; ++i)
    CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_tq[i], memSize)
  /* coefficients of l(x) (degree q poly) */
  for (i = 0; i < lmax; ++i)
    CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_l[i], memSize)
  /* the scalar 1/l[1] */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_rl1, memSize)
  /* gamma = h * rl1 */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_gamma, memSize)
  /* gamma at the last setup call */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_gammap, memSize)
  /* gamma / gammap */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_gamrat, memSize)
  /* estimated corrector convergence rate */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_crate, memSize)
  /* | acor | wrms */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_acnrm, memSize)
  /* coeficient in nonlinear convergence test */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_nlscoef, memSize)
  /* Newton iteration counter */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_mnewt, memSize)

  /* q <= qmax */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_qmax, memSize)
  /* maximum number of internal steps for one user call */
  CVODE_SERIALIZE_A(op, long, *storageDataPtr, cv_mem->cv_mxstep, memSize)
  /* maximum number of corrector iterations for the solution of the nonlinear equation */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_maxcor, memSize)
  /* maximum number of warning messages issued to the user that t + h == t for the next internal step */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_mxhnil, memSize)
  /* maximum number of error test failures */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_maxnef, memSize)
  /* maximum number of nonlinear convergence failures */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_maxncf, memSize)
  /* maximum number of steps between Jacobian evaluations */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_maxStepNumberBetweenJacobianEvaluations, memSize)
  /* |h| >= hmin */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_hmin, memSize)
  /* |h| <= 1/hmax_inv */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_hmax_inv, memSize)
  /* eta <= etamax */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_etamax, memSize)

  /* number of internal steps taken */
  CVODE_SERIALIZE_A(op, long, *storageDataPtr, cv_mem->cv_nst, memSize)
  /* number of f calls */
  CVODE_SERIALIZE_A(op, long, *storageDataPtr, cv_mem->cv_nfe, memSize)
  /* number of corrector convergence failures */
  CVODE_SERIALIZE_A(op, long, *storageDataPtr, cv_mem->cv_ncfn, memSize)
  /* number of error test failures */
  CVODE_SERIALIZE_A(op, long, *storageDataPtr, cv_mem->cv_netf, memSize)
  /* number of Newton iterations performed */
  CVODE_SERIALIZE_A(op, long, *storageDataPtr, cv_mem->cv_nni, memSize)
  /* number of setup calls */
  CVODE_SERIALIZE_A(op, long, *storageDataPtr, cv_mem->cv_nsetups, memSize)
  /* number of messages issued to the user that t + h == t for the next iternal step */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_nhnil, memSize)
  /* ratio of new to old h for order q-1 */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_etaqm1, memSize)
  /* ratio of new to old h for order q */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_etaq, memSize)
  /* ratio of new to old h for order q+1 */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_etaqp1, memSize)

  /* no. of realtype words in 1 N_Vector */
  CVODE_SERIALIZE_A(op, long, *storageDataPtr, cv_mem->cv_lrw1, memSize)
  /* no. of integer words in 1 N_Vector */
  CVODE_SERIALIZE_A(op, long, *storageDataPtr, cv_mem->cv_liw1, memSize)
  /* no. of realtype words in CVODE work vectors */
  CVODE_SERIALIZE_A(op, long, *storageDataPtr, cv_mem->cv_lrw, memSize)
  /* no. of integer words in CVODE work vectors */
  CVODE_SERIALIZE_A(op, long, *storageDataPtr, cv_mem->cv_liw, memSize)

  /* last successful q value used */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_qu, memSize)
  /* step number of last setup call */
  CVODE_SERIALIZE_A(op, long, *storageDataPtr, cv_mem->cv_nstlp, memSize)
  /* actual initial stepsize */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_h0u, memSize)
  /* last successful h value used */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_hu, memSize)
  /* saved value of tq[5] */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_saved_tq5, memSize)
  /* is Jacobian info. for lin. solver current? */
  CVODE_SERIALIZE_A(op, booleantype, *storageDataPtr, cv_mem->cv_jcur, memSize)
  /* tolerance scale factor */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_tolsf, memSize)
  /* value of qmax used when allocating memory */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_qmax_alloc, memSize)
  /* index of the zn vector with saved acor */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_indx_acor, memSize)

  /* does setup do anything? */
  CVODE_SERIALIZE_A(op, booleantype, *storageDataPtr, cv_mem->cv_setupNonNull, memSize)
  CVODE_SERIALIZE_A(op, booleantype, *storageDataPtr, cv_mem->cv_damp, memSize)

  CVODE_SERIALIZE_A(op, booleantype, *storageDataPtr, cv_mem->cv_VabstolMallocDone, memSize)
  CVODE_SERIALIZE_A(op, booleantype, *storageDataPtr, cv_mem->cv_MallocDone, memSize)

  /* is Stability Limit Detection on? */
  CVODE_SERIALIZE_A(op, booleantype, *storageDataPtr, cv_mem->cv_sldeton, memSize)
  /* scaled data array for STALD */
  for (i = 0; i < 6; ++i) {
    long int j;
    for (j = 0; i < 4; ++i)
      CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_ssdat[i][j], memSize)
  }
  /* counter for STALD method */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_nscon, memSize)
  /* counter for number of order reductions */
  CVODE_SERIALIZE_A(op, long, *storageDataPtr, cv_mem->cv_nor, memSize)

  /* number of components of g */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_nrtfn, memSize)
  /* array for root information */
  for (i = 0; i < cv_mem->cv_nrtfn; ++i)
    CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_iroots[i], memSize)
  /* nearest endpoint of interval in root search */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_tlo, memSize)
  /* farthest endpoint of interval in root search */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_thi, memSize)
  /* t value returned by rootfinding routine */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_trout, memSize)
  /* saved array of g values at t = tlo */
  for (i = 0; i < cv_mem->cv_nrtfn; ++i)
    CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_glo[i], memSize)
  /* saved array of g values at t = thi */
  for (i = 0; i < cv_mem->cv_nrtfn; ++i)
    CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_ghi[i], memSize)
  /* array of g values at t = trout */
  for (i = 0; i < cv_mem->cv_nrtfn; ++i)
    CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_grout[i], memSize)
  /* copy of tout (if NORMAL mode) */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_toutc, memSize)
  /* tolerance on root location */
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_ttol, memSize)
  /* copy of parameter itask */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_taskc, memSize)
  /* flag showing whether last step had a root */
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_irfnd, memSize)
  /* counter for g evaluations */
  CVODE_SERIALIZE_A(op, long, *storageDataPtr, cv_mem->cv_nge, memSize)

  /* index array */
  for (i = 0; i < cv_mem->cv_nrtfn; ++i)
    CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_rootindex[i], memSize)
  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_maxindex, memSize)
  for (i = 0; i < cv_mem->cv_nrtfn; ++i)
    CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_signglo[i], memSize)
  for (i = 0; i < cv_mem->cv_nrtfn; ++i)
    CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_signghi[i], memSize)
  for (i = 0; i < cv_mem->cv_nrtfn; ++i)
    CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_irootctr[i], memSize)
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_savtlo, memSize)
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_savglo, memSize)
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_savthi, memSize)
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_savghi, memSize)
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_savtmid, memSize)
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_savgmid, memSize)

  CVODE_SERIALIZE_A(op, int, *storageDataPtr, cv_mem->cv_hysteresis, memSize)
  CVODE_SERIALIZE_A(op, realtype, *storageDataPtr, cv_mem->cv_epsilon, memSize)

  /* serialization of linear solver */
  CVODE_LINSOLV_SERIALIZATION(op, storageDataPtr, memSize)

  /* serialization of user data (model data) */
  CVODE_USER_SERIALIZATION(op, storageDataPtr, memSize)

  switch (op) {
    case SUNDIALS_SERIALIZATION_OPERATION_SERIALIZE :
    case SUNDIALS_SERIALIZATION_OPERATION_DESERIALIZE :
      memSize = (long int)((char *)*storageDataPtr - (char *)storageDataPtrStart); break;
  }

  return memSize;
}


/*
 * =================================================================
 * EXPORTED FUNCTIONS IMPLEMENTATION
 * =================================================================
 */

/*
 * Function : CVodeSerializationSize
 */
long int CVodeSerializationSize(void *cvode_mem) {
  return CVodeSerializationPrivate(SUNDIALS_SERIALIZATION_OPERATION_SIZE, cvode_mem, NULL);
}

/*
 * Function : CVodeSerialize
 */
long int CVodeSerialize(void *cvode_mem, void ** storageDataPtr) {
  return CVodeSerializationPrivate(SUNDIALS_SERIALIZATION_OPERATION_SERIALIZE, cvode_mem, storageDataPtr);
}

/*
 * Function : CVodeDeserialize
 */
long int CVodeDeserialize(void *cvode_mem, void ** storageDataPtr) {
  return CVodeSerializationPrivate(SUNDIALS_SERIALIZATION_OPERATION_DESERIALIZE, cvode_mem, storageDataPtr);
}

/*
* Function : UserSerializationSize
*/
long int UserSerializationSize(void *cvode_mem) {
	return 0;
}

/*
* Function : UserSerialize
*/
long int UserSerialize(void *cvode_mem, void ** storageDataPtr) {
	return 0;
}

/*
* Function : UserDeserialize
*/
long int UserDeserialize(void *cvode_mem, void ** storageDataPtr) {
	return 0;
}
