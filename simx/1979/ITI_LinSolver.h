#ifndef __LINSOLV_H
#define __LINSOLV_H


/*     Copyright (c) 1992-2016 The University of Tennessee and The University
 *                             of Tennessee Research Foundation.  All rights
 *                             reserved.
 *      Copyright (c) 2000-2016 The University of California Berkeley. All
 *                              rights reserved.
 *      Copyright (c) 2006-2016 The University of Colorado Denver.  All rights
 *                              reserved.
 *      
 *      $COPYRIGHT$
 *      
 *      Additional copyrights may follow
 *      
 *      $HEADER$
 *      
 *      Redistribution and use in source and binary forms, with or without
 *      modification, are permitted provided that the following conditions are
 *      met:
 *      
 *      - Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *      
 *      - Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer listed
 *        in this license in the documentation and/or other materials
 *        provided with the distribution.
 *      
 *      - Neither the name of the copyright holders nor the names of its
 *        contributors may be used to endorse or promote products derived from
 *        this software without specific prior written permission.
 *      
 *      The copyright holders provide no reassurances that the source code
 *      provided does not infringe any patent, copyright, or any other
 *      intellectual property rights of third parties.  The copyright holders
 *      disclaim any liability to any recipient for claims brought against
 *      recipient by any third party for infringement of that parties
 *      intellectual property rights.
 *      
 *      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *      "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *      A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *      OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


/*
 * =============================================================================
 * f2c.h  --  Standard Fortran to C header file
 * =============================================================================
 */

typedef int integer;
typedef unsigned int uinteger;
typedef char *address;
typedef short int shortint;
typedef float real;
typedef double doublereal;
typedef struct { real r, i; } complex;
typedef struct { doublereal r, i; } doublecomplex;
typedef int logical;
typedef short int shortlogical;
typedef char logical1;
typedef char integer1;
#ifdef INTEGER_STAR_8	/* Adjust for integer*8. */
typedef long long longint;		/* system-dependent */
typedef unsigned long long ulongint;	/* system-dependent */
#define qbit_clear(a,b)	((a) & ~((ulongint)1 << (b)))
#define qbit_set(a,b)	((a) |  ((ulongint)1 << (b)))
#endif

#define TRUE_ (1)
#define FALSE_ (0)

/* Extern is for use with -E */
#ifndef Extern
#define Extern extern
#endif

/* I/O stuff */

#ifdef f2c_i2
/* for -i2 */
typedef short flag;
typedef short ftnlen;
typedef short ftnint;
#else
typedef int flag;
typedef int ftnlen;
typedef int ftnint;
#endif

/*external read, write*/
typedef struct
{	flag cierr;
	ftnint ciunit;
	flag ciend;
	char *cifmt;
	ftnint cirec;
} cilist;

/*internal read, write*/
typedef struct
{	flag icierr;
	char *iciunit;
	flag iciend;
	char *icifmt;
	ftnint icirlen;
	ftnint icirnum;
} icilist;

/*open*/
typedef struct
{	flag oerr;
	ftnint ounit;
	char *ofnm;
	ftnlen ofnmlen;
	char *osta;
	char *oacc;
	char *ofm;
	ftnint orl;
	char *oblnk;
} olist;

/*close*/
typedef struct
{	flag cerr;
	ftnint cunit;
	char *csta;
} cllist;

/*rewind, backspace, endfile*/
typedef struct
{	flag aerr;
	ftnint aunit;
} alist;

/* inquire */
typedef struct
{	flag inerr;
	ftnint inunit;
	char *infile;
	ftnlen infilen;
	ftnint	*inex;	/*parameters in standard's order*/
	ftnint	*inopen;
	ftnint	*innum;
	ftnint	*innamed;
	char	*inname;
	ftnlen	innamlen;
	char	*inacc;
	ftnlen	inacclen;
	char	*inseq;
	ftnlen	inseqlen;
	char 	*indir;
	ftnlen	indirlen;
	char	*infmt;
	ftnlen	infmtlen;
	char	*inform;
	ftnint	informlen;
	char	*inunf;
	ftnlen	inunflen;
	ftnint	*inrecl;
	ftnint	*innrec;
	char	*inblank;
	ftnlen	inblanklen;
} inlist;

#define VOID void

union Multitype {	/* for multiple entry points */
	integer1 g;
	shortint h;
	integer i;
	/* longint j; */
	real r;
	doublereal d;
	complex c;
	doublecomplex z;
	};

typedef union Multitype Multitype;

/*typedef long int Long;*/	/* No longer used; formerly in Namelist */

struct Vardesc {	/* for Namelist */
	char *name;
	char *addr;
	ftnlen *dims;
	int  type;
	};
typedef struct Vardesc Vardesc;

struct Namelist {
	char *name;
	Vardesc **vars;
	int nvars;
	};
typedef struct Namelist Namelist;

#define abs(x) ((x) >= 0 ? (x) : -(x))
#define dabs(x) (doublereal)abs(x)
#ifndef min
#define min(a,b) ((a) <= (b) ? (a) : (b))
#endif
#ifndef max
#define max(a,b) ((a) >= (b) ? (a) : (b))
#endif
#define dmin(a,b) (doublereal)min(a,b)
#define dmax(a,b) (doublereal)max(a,b)
#define bit_test(a,b)	((a) >> (b) & 1)
#define bit_clear(a,b)	((a) & ~((uinteger)1 << (b)))
#define bit_set(a,b)	((a) |  ((uinteger)1 << (b)))

/* procedure parameter types for -A and -C++ */

#define F2C_proc_par_types 1
#ifdef __cplusplus
typedef int /* Unknown procedure type */ (*U_fp)(...);
typedef shortint (*J_fp)(...);
typedef integer (*I_fp)(...);
typedef real (*R_fp)(...);
typedef doublereal (*D_fp)(...), (*E_fp)(...);
typedef /* Complex */ VOID (*C_fp)(...);
typedef /* Double Complex */ VOID (*Z_fp)(...);
typedef logical (*L_fp)(...);
typedef shortlogical (*K_fp)(...);
typedef /* Character */ VOID (*H_fp)(...);
typedef /* Subroutine */ int (*S_fp)(...);
#else
typedef int /* Unknown procedure type */ (*U_fp)();
typedef shortint (*J_fp)();
typedef integer (*I_fp)();
typedef real (*R_fp)();
typedef doublereal (*D_fp)(), (*E_fp)();
typedef /* Complex */ VOID (*C_fp)();
typedef /* Double Complex */ VOID (*Z_fp)();
typedef logical (*L_fp)();
typedef shortlogical (*K_fp)();
typedef /* Character */ VOID (*H_fp)();
typedef /* Subroutine */ int (*S_fp)();
#endif
/* E_fp is for real functions when -R is not specified */
typedef VOID C_f;	/* complex function */
typedef VOID H_f;	/* character function */
typedef VOID Z_f;	/* double complex function */
typedef doublereal E_f;	/* real function with -R not specified */

/* undef any lower-case symbols that your C compiler predefines, e.g.: */

#ifndef Skip_f2c_Undefs
#undef cray
#undef gcos
#undef mc68010
#undef mc68020
#undef mips
#undef pdp11
#undef sgi
#undef sparc
#undef sun
#undef sun2
#undef sun3
#undef sun4
#undef u370
#undef u3b
#undef u3b2
#undef u3b5
#undef unix
#undef vax
#endif

/*
 * =============================================================================
 * Prototypes
 * =============================================================================
 */

double d_lg10(doublereal *x);
double d_sign(doublereal *a, doublereal *b);
integer i_dnnt(doublereal *x);
integer i_nint(real *x);
double pow_dd(doublereal *ap, doublereal *bp);
double pow_di(doublereal *ap, integer *bp);
void s_cat(char *lp, char *rpp[], ftnint rnp[], ftnint *np, ftnlen ll);
integer s_cmp(char *a0, char *b0, ftnlen la, ftnlen lb);
void s_copy(char *a, char *b, ftnlen la, ftnlen lb);

int daxpy_(integer *n, doublereal *da, doublereal *dx, integer *incx, doublereal *dy, integer *incy);
int dcopy_(integer *n, doublereal *dx, integer *incx, doublereal *dy, integer *incy);
doublereal ddot_(integer *n, doublereal *dx, integer *incx, doublereal *dy, integer *incy);
int dgemm_(char *transa, char *transb, integer *m, integer *n, integer *k, doublereal *alpha, doublereal *a, integer *lda, doublereal *b, integer *ldb, doublereal *beta, doublereal *c__, integer *ldc);
int dgemv_(char *trans, integer *m, integer *n, doublereal *alpha, doublereal *a, integer *lda, doublereal *x, integer *incx, doublereal *beta, doublereal *y, integer *incy);
int dger_(integer *m, integer *n, doublereal *alpha, doublereal *x, integer *incx, doublereal *y, integer *incy, doublereal *a, integer *lda);
doublereal dnrm2_(integer *n, doublereal *x, integer *incx);
int drot_(integer *n, doublereal *dx, integer *incx, doublereal *dy, integer *incy, doublereal *c__, doublereal *s);
int dscal_(integer *n, doublereal *da, doublereal *dx, integer *incx);
int dswap_(integer *n, doublereal *dx, integer *incx, doublereal *dy, integer *incy);
int dtrmm_(char *side, char *uplo, char *transa, char *diag, integer *m, integer *n, doublereal *alpha, doublereal *a, integer *lda, doublereal *b, integer *ldb);
int dtrmv_(char *uplo, char *trans, char *diag, integer *n, doublereal *a, integer *lda, doublereal *x, integer *incx);
int dtrsm_(char *side, char *uplo, char *transa, char *diag, integer *m, integer *n, doublereal *alpha, doublereal *a, integer *lda, doublereal *b, integer *ldb);
integer idamax_(integer *n, doublereal *dx, integer *incx);

int dbdsqr_(char *uplo, integer *n, integer *ncvt, integer *nru, integer *ncc, doublereal *d__, doublereal *e, doublereal *vt, integer *ldvt, doublereal *u, integer *ldu, doublereal *c__, integer *ldc, doublereal *work, integer *info);
int dgebd2_(integer *m, integer *n, doublereal *a, integer *lda, doublereal *d__, doublereal *e, doublereal *tauq, doublereal *taup, doublereal *work, integer *info);
int dgebrd_(integer *m, integer *n, doublereal *a, integer *lda, doublereal *d__, doublereal *e, doublereal *tauq, doublereal *taup, doublereal *work, integer *lwork, integer *info);
int dgelq2_(integer *m, integer *n, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *info);
int dgelqf_(integer *m, integer *n, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);
int dgelsy_(integer *m, integer *n, integer *nrhs, doublereal *a, integer *lda, doublereal *b, integer *ldb, integer *jpvt, doublereal *rcond, integer *rank, doublereal *work, integer *lwork, integer *info);
int dgeqp3_(integer *m, integer *n, doublereal *a, integer *lda, integer *jpvt, doublereal *tau, doublereal *work, integer *lwork, integer *info);
int dgeqr2_(integer *m, integer *n, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *info);
int dgeqrf_(integer *m, integer *n, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);
int dgesvd_(char *jobu, char *jobvt, integer *m, integer *n, doublereal *a, integer *lda, doublereal *s, doublereal *u, integer *ldu, doublereal *vt, integer *ldvt, doublereal *work, integer *lwork, integer *info);
int dgetf2_(integer *m, integer *n, doublereal *a, integer *lda, integer *ipiv, integer *info);
int dgetrf_(integer *m, integer *n, doublereal *a, integer *lda, integer *ipiv, integer *info);
int dgetrs_(char *trans, integer *n, integer *nrhs, doublereal *a, integer *lda, integer *ipiv, doublereal *b, integer *ldb, integer *info);
logical disnan_(doublereal *din);
int dlabad_(doublereal *small, doublereal *large);
int dlabrd_(integer *m, integer *n, integer *nb, doublereal *a, integer *lda, doublereal *d__, doublereal *e, doublereal *tauq, doublereal *taup, doublereal *x, integer *ldx, doublereal *y, integer *ldy);
int dlacpy_(char *uplo, integer *m, integer *n, doublereal *a, integer *lda, doublereal *b, integer *ldb);
int dlaic1_(integer *job, integer *j, doublereal *x, doublereal *sest, doublereal *w, doublereal *gamma, doublereal *sestpr, doublereal *s, doublereal *c__);
logical dlaisnan_(doublereal *din1, doublereal *din2);
doublereal dlamch_(char *cmach);
doublereal dlange_(char *norm, integer *m, integer *n, doublereal *a, integer *lda, doublereal *work);
doublereal dlapy2_(doublereal *x, doublereal *y);
int dlaqp2_(integer *m, integer *n, integer *offset, doublereal *a, integer *lda, integer *jpvt, doublereal *tau, doublereal *vn1, doublereal *vn2, doublereal *work);
int dlaqps_(integer *m, integer *n, integer *offset, integer *nb, integer *kb, doublereal *a, integer *lda, integer *jpvt, doublereal *tau, doublereal *vn1, doublereal *vn2, doublereal *auxv, doublereal *f, integer *ldf);
int dlarf_(char *side, integer *m, integer *n, doublereal *v, integer *incv, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work);
int dlarfb_(char *side, char *trans, char *direct, char *storev, integer *m, integer *n, integer *k, doublereal *v, integer *ldv, doublereal *t, integer *ldt, doublereal *c__, integer *ldc, doublereal *work, integer *ldwork);
int dlarfg_(integer *n, doublereal *alpha, doublereal *x, integer *incx, doublereal *tau);
int dlarfp_(integer *n, doublereal *alpha, doublereal *x, integer *incx, doublereal *tau);
int dlarft_(char *direct, char *storev, integer *n, integer *k, doublereal *v, integer *ldv, doublereal *tau, doublereal *t, integer *ldt);
int dlartg_(doublereal *f, doublereal *g, doublereal *cs, doublereal *sn, doublereal *r__);
int dlarz_(char *side, integer *m, integer *n, integer *l, doublereal *v, integer *incv, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work);
int dlarzb_(char *side, char *trans, char *direct, char *storev, integer *m, integer *n, integer *k, integer *l, doublereal *v, integer *ldv, doublereal *t, integer *ldt, doublereal *c__, integer *ldc, doublereal *work, integer *ldwork);
int dlarzt_(char *direct, char *storev, integer *n, integer *k, doublereal *v, integer *ldv, doublereal *tau, doublereal *t, integer *ldt);
int dlas2_(doublereal *f, doublereal *g, doublereal *h__, doublereal *ssmin, doublereal *ssmax);
int dlascl_(char *type__, integer *kl, integer *ku, doublereal *cfrom, doublereal *cto, integer *m, integer *n, doublereal *a, integer *lda, integer *info);
int dlaset_(char *uplo, integer *m, integer *n, doublereal *alpha, doublereal *beta, doublereal *a, integer *lda);
int dlasq1_(integer *n, doublereal *d__, doublereal *e, doublereal *work, integer *info);
int dlasq2_(integer *n, doublereal *z__, integer *info);
int dlasq3_(integer *i0, integer *n0, doublereal *z__, integer *pp, doublereal *dmin__, doublereal *sigma, doublereal *desig, doublereal *qmax, integer *nfail, integer *iter, integer *ndiv, logical *ieee, integer *ttype, doublereal *dmin1, doublereal *dmin2, doublereal *dn, doublereal *dn1, doublereal *dn2, doublereal *g, doublereal *tau);
int dlasq4_(integer *i0, integer *n0, doublereal *z__, integer *pp, integer *n0in, doublereal *dmin__, doublereal *dmin1, doublereal *dmin2, doublereal *dn, doublereal *dn1, doublereal *dn2, doublereal *tau, integer *ttype, doublereal *g);
int dlasq5_(integer *i0, integer *n0, doublereal *z__, integer *pp, doublereal *tau, doublereal *dmin__, doublereal *dmin1, doublereal *dmin2, doublereal *dn, doublereal *dnm1, doublereal *dnm2, logical *ieee);
int dlasq6_(integer *i0, integer *n0, doublereal *z__, integer *pp, doublereal *dmin__, doublereal *dmin1, doublereal *dmin2, doublereal *dn, doublereal *dnm1, doublereal *dnm2);
int dlasr_(char *side, char *pivot, char *direct, integer *m, integer *n, doublereal *c__, doublereal *s, doublereal *a, integer *lda);
int dlasrt_(char *id, integer *n, doublereal *d__, integer *info);
int dlassq_(integer *n, doublereal *x, integer *incx, doublereal *scale, doublereal *sumsq);
int dlasv2_(doublereal *f, doublereal *g, doublereal *h__, doublereal *ssmin, doublereal *ssmax, doublereal *snr, doublereal *csr, doublereal *snl, doublereal *csl);
int dlaswp_(integer *n, doublereal *a, integer *lda, integer *k1, integer *k2, integer *ipiv, integer *incx);
int dlatrz_(integer *m, integer *n, integer *l, doublereal *a, integer *lda, doublereal *tau, doublereal *work);
int dorg2r_(integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *info);
int dorgbr_(char *vect, integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);
int dorgl2_(integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *info);
int dorglq_(integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);
int dorgqr_(integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);
int dorm2r_(char *side, char *trans, integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, integer *info);
int dormbr_(char *vect, char *side, char *trans, integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, integer *lwork, integer *info);
int dorml2_(char *side, char *trans, integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, integer *info);
int dormlq_(char *side, char *trans, integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, integer *lwork, integer *info);
int dormqr_(char *side, char *trans, integer *m, integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, integer *lwork, integer *info);
int dormr3_(char *side, char *trans, integer *m, integer *n, integer *k, integer *l, doublereal *a, integer *lda, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, integer *info);
int dormrz_(char *side, char *trans, integer *m, integer *n, integer *k, integer *l, doublereal *a, integer *lda, doublereal *tau, doublereal *c__, integer *ldc, doublereal *work, integer *lwork, integer *info);
int dtzrzf_(integer *m, integer *n, doublereal *a, integer *lda, doublereal *tau, doublereal *work, integer *lwork, integer *info);
integer ieeeck_(integer *ispec, real *zero, real *one);
integer iladlc_(integer *m, integer *n, doublereal *a, integer *lda);
integer iladlr_(integer *m, integer *n, doublereal *a, integer *lda);
integer ilaenv_(integer *ispec, char *name__, char *opts, integer *n1, integer *n2, integer *n3, integer *n4);
integer iparmq_(integer *ispec, char *name__, char *opts, integer *n, integer *ilo, integer *ihi, integer *lwork);
logical lsame_(char *ca, char *cb);
int xerbla_(char *srname, integer *info);


/*
 * =============================================================================
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
 * =============================================================================
 */

int iti_dtrsm_(char *side, char *uplo, char *transa, char *diag, integer *m, integer *n, doublereal *alpha, doublereal *a, integer *lda, doublereal *b, integer *ldb, integer *info);
int iti_dgetf2_(integer *m, integer *n, doublereal *a, integer *lda, integer *ipiv, integer *colpiv, integer *info);
int iti_dgetrf_(integer *m, integer *n, doublereal *a, integer *lda, integer *ipiv, integer *colpiv, integer *info);
int iti_dgetrs_(char *trans, integer *n, integer *nrhs, doublereal *a, integer *lda, integer *ipiv, integer *colpiv, doublereal *b, integer *ldb, integer *info);
int iti_dgetrs_rect_normal_(integer *m, integer *n, doublereal *a, integer *ipiv, integer *colpiv, doublereal *b, integer *info, doublereal *ker, doublereal *kercopy, doublereal *veccopy, doublereal *dWork, integer *lPermVecCol, doublereal error);
int iti_dlaswp_(integer *n, doublereal *a, integer *lda, integer *k1, integer *k2, integer *colpiv);
void lls_init(ITI_LLSData *data);
void lls_fact(ITI_LLSData *data);
void lls_solv(ITI_LLSData *data);

#endif /* __LINSOLV_H */
