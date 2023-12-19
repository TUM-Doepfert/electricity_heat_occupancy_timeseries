#include "ITI_crt.h"
#include "ITI_LinSolver.h"

#ifdef _WIN32
#pragma warning( disable: 4100 4244 4554 4701 4723)
#endif

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
 * LIBF2C
 * =============================================================================
 */

#define NO_OVERWRITE

#define log10e 0.43429448190325182765

#ifdef KR_headers
double log();
double d_lg10(x) doublereal *x;
#else
#ifdef __cplusplus
extern "C" {
#endif
double d_lg10(doublereal *x)
#endif
{
return( log10e * log(*x) );
}
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef KR_headers
double d_sign(a,b) doublereal *a, *b;
#else
double d_sign(doublereal *a, doublereal *b)
#endif
{
double x;
x = (*a >= 0 ? *a : - *a);
return( *b >= 0 ? x : -x);
}
#ifdef __cplusplus
}
#endif

#ifdef KR_headers
double floor();
integer i_dnnt(x) doublereal *x;
#else
#ifdef __cplusplus
extern "C" {
#endif
integer i_dnnt(doublereal *x)
#endif
{
return (integer)(*x >= 0. ? floor(*x + .5) : -floor(.5 - *x));
}
#ifdef __cplusplus
}
#endif

#ifdef KR_headers
double floor();
integer i_nint(x) real *x;
#else
#ifdef __cplusplus
extern "C" {
#endif
integer i_nint(real *x)
#endif
{
return (integer)(*x >= 0 ? floor(*x + .5) : -floor(.5 - *x));
}
#ifdef __cplusplus
}
#endif

#ifdef KR_headers
double pow();
double pow_dd(ap, bp) doublereal *ap, *bp;
#else
#ifdef __cplusplus
extern "C" {
#endif
double pow_dd(doublereal *ap, doublereal *bp)
#endif
{
return(pow(*ap, *bp) );
}
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef KR_headers
double pow_di(ap, bp) doublereal *ap; integer *bp;
#else
double pow_di(doublereal *ap, integer *bp)
#endif
{
double pow, x;
integer n;
unsigned long u;

pow = 1;
x = *ap;
n = *bp;

if(n != 0)
	{
	if(n < 0)
		{
		n = -n;
		x = 1/x;
		}
	for(u = n; ; )
		{
		if(u & 01)
			pow *= x;
		if(u >>= 1)
			x *= x;
		else
			break;
		}
	}
return(pow);
}
#ifdef __cplusplus
}
#endif

#ifndef NO_OVERWRITE
#include "stdio.h"
#undef abs
#ifdef KR_headers
 extern char *F77_aloc();
 extern void free();
 extern void exit_();
#else
#undef min
#undef max
#include "stdlib.h"
extern
#ifdef __cplusplus
	"C"
#endif
	char *F77_aloc(ftnlen, const char*);
#endif
#include "string.h"
#endif /* NO_OVERWRITE */

#ifdef __cplusplus
extern "C" {
#endif

 VOID
#ifdef KR_headers
s_cat(lp, rpp, rnp, np, ll) char *lp, *rpp[]; ftnint rnp[], *np; ftnlen ll;
#else
s_cat(char *lp, char *rpp[], ftnint rnp[], ftnint *np, ftnlen ll)
#endif
{
	ftnlen i, nc;
	char *rp;
	ftnlen n = *np;
#ifndef NO_OVERWRITE
	ftnlen L, m;
	char *lp0, *lp1;

	lp0 = 0;
	lp1 = lp;
	L = ll;
	i = 0;
	while(i < n) {
		rp = rpp[i];
		m = rnp[i++];
		if (rp >= lp1 || rp + m <= lp) {
			if ((L -= m) <= 0) {
				n = i;
				break;
				}
			lp1 += m;
			continue;
			}
		lp0 = lp;
		lp = lp1 = F77_aloc(L = ll, "s_cat");
		break;
		}
	lp1 = lp;
#endif /* NO_OVERWRITE */
	for(i = 0 ; i < n ; ++i) {
		nc = ll;
		if(rnp[i] < nc)
			nc = rnp[i];
		ll -= nc;
		rp = rpp[i];
		while(--nc >= 0)
			*lp++ = *rp++;
		}
	while(--ll >= 0)
		*lp++ = ' ';
#ifndef NO_OVERWRITE
	if (lp0) {
		memcpy(lp0, lp1, L);
		free(lp1);
		}
#endif
	}
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* compare two strings */

#ifdef KR_headers
integer s_cmp(a0, b0, la, lb) char *a0, *b0; ftnlen la, lb;
#else
integer s_cmp(char *a0, char *b0, ftnlen la, ftnlen lb)
#endif
{
unsigned char *a, *aend, *b, *bend;
a = (unsigned char *)a0;
b = (unsigned char *)b0;
aend = a + la;
bend = b + lb;

if(la <= lb)
	{
	while(a < aend)
		if(*a != *b)
			return( *a - *b );
		else
			{ ++a; ++b; }

	while(b < bend)
		if(*b != ' ')
			return( ' ' - *b );
		else	++b;
	}

else
	{
	while(b < bend)
		if(*a == *b)
			{ ++a; ++b; }
		else
			return( *a - *b );
	while(a < aend)
		if(*a != ' ')
			return(*a - ' ');
		else	++a;
	}
return(0);
}
#ifdef __cplusplus
}
#endif

/* Unless compiled with -DNO_OVERWRITE, this variant of s_copy allows the
 * target of an assignment to appear on its right-hand side (contrary
 * to the Fortran 77 Standard, but in accordance with Fortran 90),
 * as in  a(2:5) = a(4:7) .
 */

#ifdef __cplusplus
extern "C" {
#endif

/* assign strings:  a = b */

#ifdef KR_headers
VOID s_copy(a, b, la, lb) char *a, *b; ftnlen la, lb;
#else
void s_copy(char *a, char *b, ftnlen la, ftnlen lb)
#endif
{
	char *aend, *bend;

	aend = a + la;

	if(la <= lb)
#ifndef NO_OVERWRITE
		if (a <= b || a >= b + la)
#endif
			while(a < aend)
				*a++ = *b++;
#ifndef NO_OVERWRITE
		else
			for(b += la; a < aend; )
				*--aend = *--b;
#endif

	else {
		bend = b + lb;
#ifndef NO_OVERWRITE
		if (a <= b || a >= bend)
#endif
			while(b < bend)
				*a++ = *b++;
#ifndef NO_OVERWRITE
		else {
			a += lb;
			while(b < bend)
				*--a = *--bend;
			a += lb;
			}
#endif
		while(a < aend)
			*a++ = ' ';
		}
	}
#ifdef __cplusplus
}
#endif

#undef NO_OVERWRITE

/*
 * =============================================================================
 * BLAS
 * =============================================================================
 */

/* Subroutine */ int daxpy_(integer *n, doublereal *da, doublereal *dx,
	integer *incx, doublereal *dy, integer *incy)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    integer i__, m, ix, iy, mp1;

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*     constant times a vector plus a vector. */
/*     uses unrolled loops for increments equal to one. */
/*     jack dongarra, linpack, 3/11/78. */
/*     modified 12/3/93, array(1) declarations changed to array(*) */


/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
    /* Parameter adjustments */
    --dy;
    --dx;

    /* Function Body */
    if (*n <= 0) {
	return 0;
    }
    if (*da == 0.) {
	return 0;
    }
    if (*incx == 1 && *incy == 1) {
	goto L20;
    }

/*        code for unequal increments or equal increments */
/*          not equal to 1 */

    ix = 1;
    iy = 1;
    if (*incx < 0) {
	ix = (-(*n) + 1) * *incx + 1;
    }
    if (*incy < 0) {
	iy = (-(*n) + 1) * *incy + 1;
    }
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	dy[iy] += *da * dx[ix];
	ix += *incx;
	iy += *incy;
/* L10: */
    }
    return 0;

/*        code for both increments equal to 1 */


/*        clean-up loop */

L20:
    m = *n % 4;
    if (m == 0) {
	goto L40;
    }
    i__1 = m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	dy[i__] += *da * dx[i__];
/* L30: */
    }
    if (*n < 4) {
	return 0;
    }
L40:
    mp1 = m + 1;
    i__1 = *n;
    for (i__ = mp1; i__ <= i__1; i__ += 4) {
	dy[i__] += *da * dx[i__];
	dy[i__ + 1] += *da * dx[i__ + 1];
	dy[i__ + 2] += *da * dx[i__ + 2];
	dy[i__ + 3] += *da * dx[i__ + 3];
/* L50: */
    }
    return 0;
} /* daxpy_ */

/* Subroutine */ int dcopy_(integer *n, doublereal *dx, integer *incx,
	doublereal *dy, integer *incy)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    integer i__, m, ix, iy, mp1;

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*     copies a vector, x, to a vector, y. */
/*     uses unrolled loops for increments equal to one. */
/*     jack dongarra, linpack, 3/11/78. */
/*     modified 12/3/93, array(1) declarations changed to array(*) */


/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
    /* Parameter adjustments */
    --dy;
    --dx;

    /* Function Body */
    if (*n <= 0) {
	return 0;
    }
    if (*incx == 1 && *incy == 1) {
	goto L20;
    }

/*        code for unequal increments or equal increments */
/*          not equal to 1 */

    ix = 1;
    iy = 1;
    if (*incx < 0) {
	ix = (-(*n) + 1) * *incx + 1;
    }
    if (*incy < 0) {
	iy = (-(*n) + 1) * *incy + 1;
    }
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	dy[iy] = dx[ix];
	ix += *incx;
	iy += *incy;
/* L10: */
    }
    return 0;

/*        code for both increments equal to 1 */


/*        clean-up loop */

L20:
    m = *n % 7;
    if (m == 0) {
	goto L40;
    }
    i__1 = m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	dy[i__] = dx[i__];
/* L30: */
    }
    if (*n < 7) {
	return 0;
    }
L40:
    mp1 = m + 1;
    i__1 = *n;
    for (i__ = mp1; i__ <= i__1; i__ += 7) {
	dy[i__] = dx[i__];
	dy[i__ + 1] = dx[i__ + 1];
	dy[i__ + 2] = dx[i__ + 2];
	dy[i__ + 3] = dx[i__ + 3];
	dy[i__ + 4] = dx[i__ + 4];
	dy[i__ + 5] = dx[i__ + 5];
	dy[i__ + 6] = dx[i__ + 6];
/* L50: */
    }
    return 0;
} /* dcopy_ */

doublereal ddot_(integer *n, doublereal *dx, integer *incx, doublereal *dy,
	integer *incy)
{
    /* System generated locals */
    integer i__1;
    doublereal ret_val;

    /* Local variables */
    integer i__, m, ix, iy, mp1;
    doublereal dtemp;

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*     forms the dot product of two vectors. */
/*     uses unrolled loops for increments equal to one. */
/*     jack dongarra, linpack, 3/11/78. */
/*     modified 12/3/93, array(1) declarations changed to array(*) */


/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
    /* Parameter adjustments */
    --dy;
    --dx;

    /* Function Body */
    ret_val = 0.;
    dtemp = 0.;
    if (*n <= 0) {
	return ret_val;
    }
    if (*incx == 1 && *incy == 1) {
	goto L20;
    }

/*        code for unequal increments or equal increments */
/*          not equal to 1 */

    ix = 1;
    iy = 1;
    if (*incx < 0) {
	ix = (-(*n) + 1) * *incx + 1;
    }
    if (*incy < 0) {
	iy = (-(*n) + 1) * *incy + 1;
    }
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	dtemp += dx[ix] * dy[iy];
	ix += *incx;
	iy += *incy;
/* L10: */
    }
    ret_val = dtemp;
    return ret_val;

/*        code for both increments equal to 1 */


/*        clean-up loop */

L20:
    m = *n % 5;
    if (m == 0) {
	goto L40;
    }
    i__1 = m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	dtemp += dx[i__] * dy[i__];
/* L30: */
    }
    if (*n < 5) {
	goto L60;
    }
L40:
    mp1 = m + 1;
    i__1 = *n;
    for (i__ = mp1; i__ <= i__1; i__ += 5) {
	dtemp = dtemp + dx[i__] * dy[i__] + dx[i__ + 1] * dy[i__ + 1] + dx[
		i__ + 2] * dy[i__ + 2] + dx[i__ + 3] * dy[i__ + 3] + dx[i__ +
		4] * dy[i__ + 4];
/* L50: */
    }
L60:
    ret_val = dtemp;
    return ret_val;
} /* ddot_ */

/* Subroutine */ int dgemm_(char *transa, char *transb, integer *m, integer *
	n, integer *k, doublereal *alpha, doublereal *a, integer *lda,
	doublereal *b, integer *ldb, doublereal *beta, doublereal *c__,
	integer *ldc)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, c_dim1, c_offset, i__1, i__2,
	    i__3;

    /* Local variables */
    integer i__, j, l, info;
    logical nota, notb;
    doublereal temp;
    integer ncola;
    extern logical lsame_(char *, char *);
    integer nrowa, nrowb;
    extern /* Subroutine */ int xerbla_(char *, integer *);

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGEMM  performs one of the matrix-matrix operations */

/*     C := alpha*op( A )*op( B ) + beta*C, */

/*  where  op( X ) is one of */

/*     op( X ) = X   or   op( X ) = X', */

/*  alpha and beta are scalars, and A, B and C are matrices, with op( A ) */
/*  an m by k matrix,  op( B )  a  k by n matrix and  C an m by n matrix. */

/*  Arguments */
/*  ========== */

/*  TRANSA - CHARACTER*1. */
/*           On entry, TRANSA specifies the form of op( A ) to be used in */
/*           the matrix multiplication as follows: */

/*              TRANSA = 'N' or 'n',  op( A ) = A. */

/*              TRANSA = 'T' or 't',  op( A ) = A'. */

/*              TRANSA = 'C' or 'c',  op( A ) = A'. */

/*           Unchanged on exit. */

/*  TRANSB - CHARACTER*1. */
/*           On entry, TRANSB specifies the form of op( B ) to be used in */
/*           the matrix multiplication as follows: */

/*              TRANSB = 'N' or 'n',  op( B ) = B. */

/*              TRANSB = 'T' or 't',  op( B ) = B'. */

/*              TRANSB = 'C' or 'c',  op( B ) = B'. */

/*           Unchanged on exit. */

/*  M      - INTEGER. */
/*           On entry,  M  specifies  the number  of rows  of the  matrix */
/*           op( A )  and of the  matrix  C.  M  must  be at least  zero. */
/*           Unchanged on exit. */

/*  N      - INTEGER. */
/*           On entry,  N  specifies the number  of columns of the matrix */
/*           op( B ) and the number of columns of the matrix C. N must be */
/*           at least zero. */
/*           Unchanged on exit. */

/*  K      - INTEGER. */
/*           On entry,  K  specifies  the number of columns of the matrix */
/*           op( A ) and the number of rows of the matrix op( B ). K must */
/*           be at least  zero. */
/*           Unchanged on exit. */

/*  ALPHA  - DOUBLE PRECISION. */
/*           On entry, ALPHA specifies the scalar alpha. */
/*           Unchanged on exit. */

/*  A      - DOUBLE PRECISION array of DIMENSION ( LDA, ka ), where ka is */
/*           k  when  TRANSA = 'N' or 'n',  and is  m  otherwise. */
/*           Before entry with  TRANSA = 'N' or 'n',  the leading  m by k */
/*           part of the array  A  must contain the matrix  A,  otherwise */
/*           the leading  k by m  part of the array  A  must contain  the */
/*           matrix A. */
/*           Unchanged on exit. */

/*  LDA    - INTEGER. */
/*           On entry, LDA specifies the first dimension of A as declared */
/*           in the calling (sub) program. When  TRANSA = 'N' or 'n' then */
/*           LDA must be at least  max( 1, m ), otherwise  LDA must be at */
/*           least  max( 1, k ). */
/*           Unchanged on exit. */

/*  B      - DOUBLE PRECISION array of DIMENSION ( LDB, kb ), where kb is */
/*           n  when  TRANSB = 'N' or 'n',  and is  k  otherwise. */
/*           Before entry with  TRANSB = 'N' or 'n',  the leading  k by n */
/*           part of the array  B  must contain the matrix  B,  otherwise */
/*           the leading  n by k  part of the array  B  must contain  the */
/*           matrix B. */
/*           Unchanged on exit. */

/*  LDB    - INTEGER. */
/*           On entry, LDB specifies the first dimension of B as declared */
/*           in the calling (sub) program. When  TRANSB = 'N' or 'n' then */
/*           LDB must be at least  max( 1, k ), otherwise  LDB must be at */
/*           least  max( 1, n ). */
/*           Unchanged on exit. */

/*  BETA   - DOUBLE PRECISION. */
/*           On entry,  BETA  specifies the scalar  beta.  When  BETA  is */
/*           supplied as zero then C need not be set on input. */
/*           Unchanged on exit. */

/*  C      - DOUBLE PRECISION array of DIMENSION ( LDC, n ). */
/*           Before entry, the leading  m by n  part of the array  C must */
/*           contain the matrix  C,  except when  beta  is zero, in which */
/*           case C need not be set on entry. */
/*           On exit, the array  C  is overwritten by the  m by n  matrix */
/*           ( alpha*op( A )*op( B ) + beta*C ). */

/*  LDC    - INTEGER. */
/*           On entry, LDC specifies the first dimension of C as declared */
/*           in  the  calling  (sub)  program.   LDC  must  be  at  least */
/*           max( 1, m ). */
/*           Unchanged on exit. */


/*  Level 3 Blas routine. */

/*  -- Written on 8-February-1989. */
/*     Jack Dongarra, Argonne National Laboratory. */
/*     Iain Duff, AERE Harwell. */
/*     Jeremy Du Croz, Numerical Algorithms Group Ltd. */
/*     Sven Hammarling, Numerical Algorithms Group Ltd. */


/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Parameters .. */
/*     .. */

/*     Set  NOTA  and  NOTB  as  true if  A  and  B  respectively are not */
/*     transposed and set  NROWA, NCOLA and  NROWB  as the number of rows */
/*     and  columns of  A  and the  number of  rows  of  B  respectively. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;

    /* Function Body */
    nota = lsame_(transa, "N");
    notb = lsame_(transb, "N");
    if (nota) {
	nrowa = *m;
	ncola = *k;
    } else {
	nrowa = *k;
	ncola = *m;
    }
    if (notb) {
	nrowb = *k;
    } else {
	nrowb = *n;
    }

/*     Test the input parameters. */

    info = 0;
    if (! nota && ! lsame_(transa, "C") && ! lsame_(
	    transa, "T")) {
	info = 1;
    } else if (! notb && ! lsame_(transb, "C") && !
	    lsame_(transb, "T")) {
	info = 2;
    } else if (*m < 0) {
	info = 3;
    } else if (*n < 0) {
	info = 4;
    } else if (*k < 0) {
	info = 5;
    } else if (*lda < max(1,nrowa)) {
	info = 8;
    } else if (*ldb < max(1,nrowb)) {
	info = 10;
    } else if (*ldc < max(1,*m)) {
	info = 13;
    }
    if (info != 0) {
	xerbla_("DGEMM ", &info);
	return 0;
    }

/*     Quick return if possible. */

    if (*m == 0 || *n == 0 || ((*alpha == 0. || *k == 0) && *beta == 1.)) {
	return 0;
    }

/*     And if  alpha.eq.zero. */

    if (*alpha == 0.) {
	if (*beta == 0.) {
	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = *m;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    c__[i__ + j * c_dim1] = 0.;
/* L10: */
		}
/* L20: */
	    }
	} else {
	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = *m;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    c__[i__ + j * c_dim1] = *beta * c__[i__ + j * c_dim1];
/* L30: */
		}
/* L40: */
	    }
	}
	return 0;
    }

/*     Start the operations. */

    if (notb) {
	if (nota) {

/*           Form  C := alpha*A*B + beta*C. */

	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		if (*beta == 0.) {
		    i__2 = *m;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			c__[i__ + j * c_dim1] = 0.;
/* L50: */
		    }
		} else if (*beta != 1.) {
		    i__2 = *m;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			c__[i__ + j * c_dim1] = *beta * c__[i__ + j * c_dim1];
/* L60: */
		    }
		}
		i__2 = *k;
		for (l = 1; l <= i__2; ++l) {
		    if (b[l + j * b_dim1] != 0.) {
			temp = *alpha * b[l + j * b_dim1];
			i__3 = *m;
			for (i__ = 1; i__ <= i__3; ++i__) {
			    c__[i__ + j * c_dim1] += temp * a[i__ + l *
				    a_dim1];
/* L70: */
			}
		    }
/* L80: */
		}
/* L90: */
	    }
	} else {

/*           Form  C := alpha*A'*B + beta*C */

	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = *m;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    temp = 0.;
		    i__3 = *k;
		    for (l = 1; l <= i__3; ++l) {
			temp += a[l + i__ * a_dim1] * b[l + j * b_dim1];
/* L100: */
		    }
		    if (*beta == 0.) {
			c__[i__ + j * c_dim1] = *alpha * temp;
		    } else {
			c__[i__ + j * c_dim1] = *alpha * temp + *beta * c__[
				i__ + j * c_dim1];
		    }
/* L110: */
		}
/* L120: */
	    }
	}
    } else {
	if (nota) {

/*           Form  C := alpha*A*B' + beta*C */

	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		if (*beta == 0.) {
		    i__2 = *m;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			c__[i__ + j * c_dim1] = 0.;
/* L130: */
		    }
		} else if (*beta != 1.) {
		    i__2 = *m;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			c__[i__ + j * c_dim1] = *beta * c__[i__ + j * c_dim1];
/* L140: */
		    }
		}
		i__2 = *k;
		for (l = 1; l <= i__2; ++l) {
		    if (b[j + l * b_dim1] != 0.) {
			temp = *alpha * b[j + l * b_dim1];
			i__3 = *m;
			for (i__ = 1; i__ <= i__3; ++i__) {
			    c__[i__ + j * c_dim1] += temp * a[i__ + l *
				    a_dim1];
/* L150: */
			}
		    }
/* L160: */
		}
/* L170: */
	    }
	} else {

/*           Form  C := alpha*A'*B' + beta*C */

	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = *m;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    temp = 0.;
		    i__3 = *k;
		    for (l = 1; l <= i__3; ++l) {
			temp += a[l + i__ * a_dim1] * b[j + l * b_dim1];
/* L180: */
		    }
		    if (*beta == 0.) {
			c__[i__ + j * c_dim1] = *alpha * temp;
		    } else {
			c__[i__ + j * c_dim1] = *alpha * temp + *beta * c__[
				i__ + j * c_dim1];
		    }
/* L190: */
		}
/* L200: */
	    }
	}
    }

    return 0;

/*     End of DGEMM . */

} /* dgemm_ */

/* Subroutine */ int dgemv_(char *trans, integer *m, integer *n, doublereal *
	alpha, doublereal *a, integer *lda, doublereal *x, integer *incx,
	doublereal *beta, doublereal *y, integer *incy)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;

    /* Local variables */
    integer i__, j, ix, iy, jx, jy, kx, ky, info;
    doublereal temp;
    integer lenx, leny;
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int xerbla_(char *, integer *);

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGEMV  performs one of the matrix-vector operations */

/*     y := alpha*A*x + beta*y,   or   y := alpha*A'*x + beta*y, */

/*  where alpha and beta are scalars, x and y are vectors and A is an */
/*  m by n matrix. */

/*  Arguments */
/*  ========== */

/*  TRANS  - CHARACTER*1. */
/*           On entry, TRANS specifies the operation to be performed as */
/*           follows: */

/*              TRANS = 'N' or 'n'   y := alpha*A*x + beta*y. */

/*              TRANS = 'T' or 't'   y := alpha*A'*x + beta*y. */

/*              TRANS = 'C' or 'c'   y := alpha*A'*x + beta*y. */

/*           Unchanged on exit. */

/*  M      - INTEGER. */
/*           On entry, M specifies the number of rows of the matrix A. */
/*           M must be at least zero. */
/*           Unchanged on exit. */

/*  N      - INTEGER. */
/*           On entry, N specifies the number of columns of the matrix A. */
/*           N must be at least zero. */
/*           Unchanged on exit. */

/*  ALPHA  - DOUBLE PRECISION. */
/*           On entry, ALPHA specifies the scalar alpha. */
/*           Unchanged on exit. */

/*  A      - DOUBLE PRECISION array of DIMENSION ( LDA, n ). */
/*           Before entry, the leading m by n part of the array A must */
/*           contain the matrix of coefficients. */
/*           Unchanged on exit. */

/*  LDA    - INTEGER. */
/*           On entry, LDA specifies the first dimension of A as declared */
/*           in the calling (sub) program. LDA must be at least */
/*           max( 1, m ). */
/*           Unchanged on exit. */

/*  X      - DOUBLE PRECISION array of DIMENSION at least */
/*           ( 1 + ( n - 1 )*abs( INCX ) ) when TRANS = 'N' or 'n' */
/*           and at least */
/*           ( 1 + ( m - 1 )*abs( INCX ) ) otherwise. */
/*           Before entry, the incremented array X must contain the */
/*           vector x. */
/*           Unchanged on exit. */

/*  INCX   - INTEGER. */
/*           On entry, INCX specifies the increment for the elements of */
/*           X. INCX must not be zero. */
/*           Unchanged on exit. */

/*  BETA   - DOUBLE PRECISION. */
/*           On entry, BETA specifies the scalar beta. When BETA is */
/*           supplied as zero then Y need not be set on input. */
/*           Unchanged on exit. */

/*  Y      - DOUBLE PRECISION array of DIMENSION at least */
/*           ( 1 + ( m - 1 )*abs( INCY ) ) when TRANS = 'N' or 'n' */
/*           and at least */
/*           ( 1 + ( n - 1 )*abs( INCY ) ) otherwise. */
/*           Before entry with BETA non-zero, the incremented array Y */
/*           must contain the vector y. On exit, Y is overwritten by the */
/*           updated vector y. */

/*  INCY   - INTEGER. */
/*           On entry, INCY specifies the increment for the elements of */
/*           Y. INCY must not be zero. */
/*           Unchanged on exit. */


/*  Level 2 Blas routine. */

/*  -- Written on 22-October-1986. */
/*     Jack Dongarra, Argonne National Lab. */
/*     Jeremy Du Croz, Nag Central Office. */
/*     Sven Hammarling, Nag Central Office. */
/*     Richard Hanson, Sandia National Labs. */


/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --x;
    --y;

    /* Function Body */
    info = 0;
    if (! lsame_(trans, "N") && ! lsame_(trans, "T") && ! lsame_(trans, "C")
	    ) {
	info = 1;
    } else if (*m < 0) {
	info = 2;
    } else if (*n < 0) {
	info = 3;
    } else if (*lda < max(1,*m)) {
	info = 6;
    } else if (*incx == 0) {
	info = 8;
    } else if (*incy == 0) {
	info = 11;
    }
    if (info != 0) {
	xerbla_("DGEMV ", &info);
	return 0;
    }

/*     Quick return if possible. */

    if (*m == 0 || *n == 0 || (*alpha == 0. && *beta == 1.)) {
	return 0;
    }

/*     Set  LENX  and  LENY, the lengths of the vectors x and y, and set */
/*     up the start points in  X  and  Y. */

    if (lsame_(trans, "N")) {
	lenx = *n;
	leny = *m;
    } else {
	lenx = *m;
	leny = *n;
    }
    if (*incx > 0) {
	kx = 1;
    } else {
	kx = 1 - (lenx - 1) * *incx;
    }
    if (*incy > 0) {
	ky = 1;
    } else {
	ky = 1 - (leny - 1) * *incy;
    }

/*     Start the operations. In this version the elements of A are */
/*     accessed sequentially with one pass through A. */

/*     First form  y := beta*y. */

    if (*beta != 1.) {
	if (*incy == 1) {
	    if (*beta == 0.) {
		i__1 = leny;
		for (i__ = 1; i__ <= i__1; ++i__) {
		    y[i__] = 0.;
/* L10: */
		}
	    } else {
		i__1 = leny;
		for (i__ = 1; i__ <= i__1; ++i__) {
		    y[i__] = *beta * y[i__];
/* L20: */
		}
	    }
	} else {
	    iy = ky;
	    if (*beta == 0.) {
		i__1 = leny;
		for (i__ = 1; i__ <= i__1; ++i__) {
		    y[iy] = 0.;
		    iy += *incy;
/* L30: */
		}
	    } else {
		i__1 = leny;
		for (i__ = 1; i__ <= i__1; ++i__) {
		    y[iy] = *beta * y[iy];
		    iy += *incy;
/* L40: */
		}
	    }
	}
    }
    if (*alpha == 0.) {
	return 0;
    }
    if (lsame_(trans, "N")) {

/*        Form  y := alpha*A*x + y. */

	jx = kx;
	if (*incy == 1) {
	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		if (x[jx] != 0.) {
		    temp = *alpha * x[jx];
		    i__2 = *m;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			y[i__] += temp * a[i__ + j * a_dim1];
/* L50: */
		    }
		}
		jx += *incx;
/* L60: */
	    }
	} else {
	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		if (x[jx] != 0.) {
		    temp = *alpha * x[jx];
		    iy = ky;
		    i__2 = *m;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			y[iy] += temp * a[i__ + j * a_dim1];
			iy += *incy;
/* L70: */
		    }
		}
		jx += *incx;
/* L80: */
	    }
	}
    } else {

/*        Form  y := alpha*A'*x + y. */

	jy = ky;
	if (*incx == 1) {
	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		temp = 0.;
		i__2 = *m;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    temp += a[i__ + j * a_dim1] * x[i__];
/* L90: */
		}
		y[jy] += *alpha * temp;
		jy += *incy;
/* L100: */
	    }
	} else {
	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		temp = 0.;
		ix = kx;
		i__2 = *m;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    temp += a[i__ + j * a_dim1] * x[ix];
		    ix += *incx;
/* L110: */
		}
		y[jy] += *alpha * temp;
		jy += *incy;
/* L120: */
	    }
	}
    }

    return 0;

/*     End of DGEMV . */

} /* dgemv_ */

/* Subroutine */ int dger_(integer *m, integer *n, doublereal *alpha,
	doublereal *x, integer *incx, doublereal *y, integer *incy,
	doublereal *a, integer *lda)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;

    /* Local variables */
    integer i__, j, ix, jy, kx, info;
    doublereal temp;
    extern /* Subroutine */ int xerbla_(char *, integer *);

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGER   performs the rank 1 operation */

/*     A := alpha*x*y' + A, */

/*  where alpha is a scalar, x is an m element vector, y is an n element */
/*  vector and A is an m by n matrix. */

/*  Arguments */
/*  ========== */

/*  M      - INTEGER. */
/*           On entry, M specifies the number of rows of the matrix A. */
/*           M must be at least zero. */
/*           Unchanged on exit. */

/*  N      - INTEGER. */
/*           On entry, N specifies the number of columns of the matrix A. */
/*           N must be at least zero. */
/*           Unchanged on exit. */

/*  ALPHA  - DOUBLE PRECISION. */
/*           On entry, ALPHA specifies the scalar alpha. */
/*           Unchanged on exit. */

/*  X      - DOUBLE PRECISION array of dimension at least */
/*           ( 1 + ( m - 1 )*abs( INCX ) ). */
/*           Before entry, the incremented array X must contain the m */
/*           element vector x. */
/*           Unchanged on exit. */

/*  INCX   - INTEGER. */
/*           On entry, INCX specifies the increment for the elements of */
/*           X. INCX must not be zero. */
/*           Unchanged on exit. */

/*  Y      - DOUBLE PRECISION array of dimension at least */
/*           ( 1 + ( n - 1 )*abs( INCY ) ). */
/*           Before entry, the incremented array Y must contain the n */
/*           element vector y. */
/*           Unchanged on exit. */

/*  INCY   - INTEGER. */
/*           On entry, INCY specifies the increment for the elements of */
/*           Y. INCY must not be zero. */
/*           Unchanged on exit. */

/*  A      - DOUBLE PRECISION array of DIMENSION ( LDA, n ). */
/*           Before entry, the leading m by n part of the array A must */
/*           contain the matrix of coefficients. On exit, A is */
/*           overwritten by the updated matrix. */

/*  LDA    - INTEGER. */
/*           On entry, LDA specifies the first dimension of A as declared */
/*           in the calling (sub) program. LDA must be at least */
/*           max( 1, m ). */
/*           Unchanged on exit. */


/*  Level 2 Blas routine. */

/*  -- Written on 22-October-1986. */
/*     Jack Dongarra, Argonne National Lab. */
/*     Jeremy Du Croz, Nag Central Office. */
/*     Sven Hammarling, Nag Central Office. */
/*     Richard Hanson, Sandia National Labs. */


/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    --x;
    --y;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    info = 0;
    if (*m < 0) {
	info = 1;
    } else if (*n < 0) {
	info = 2;
    } else if (*incx == 0) {
	info = 5;
    } else if (*incy == 0) {
	info = 7;
    } else if (*lda < max(1,*m)) {
	info = 9;
    }
    if (info != 0) {
	xerbla_("DGER  ", &info);
	return 0;
    }

/*     Quick return if possible. */

    if (*m == 0 || *n == 0 || *alpha == 0.) {
	return 0;
    }

/*     Start the operations. In this version the elements of A are */
/*     accessed sequentially with one pass through A. */

    if (*incy > 0) {
	jy = 1;
    } else {
	jy = 1 - (*n - 1) * *incy;
    }
    if (*incx == 1) {
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    if (y[jy] != 0.) {
		temp = *alpha * y[jy];
		i__2 = *m;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    a[i__ + j * a_dim1] += x[i__] * temp;
/* L10: */
		}
	    }
	    jy += *incy;
/* L20: */
	}
    } else {
	if (*incx > 0) {
	    kx = 1;
	} else {
	    kx = 1 - (*m - 1) * *incx;
	}
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    if (y[jy] != 0.) {
		temp = *alpha * y[jy];
		ix = kx;
		i__2 = *m;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    a[i__ + j * a_dim1] += x[ix] * temp;
		    ix += *incx;
/* L30: */
		}
	    }
	    jy += *incy;
/* L40: */
	}
    }

    return 0;

/*     End of DGER  . */

} /* dger_ */

doublereal dnrm2_(integer *n, doublereal *x, integer *incx)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal ret_val, d__1;

    /* Local variables */
    integer ix;
    doublereal ssq, norm, scale, absxi;

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DNRM2 returns the euclidean norm of a vector via the function */
/*  name, so that */

/*     DNRM2 := sqrt( x'*x ) */


/*  -- This version written on 25-October-1982. */
/*     Modified on 14-October-1993 to inline the call to DLASSQ. */
/*     Sven Hammarling, Nag Ltd. */


/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
    /* Parameter adjustments */
    --x;

    /* Function Body */
    if (*n < 1 || *incx < 1) {
	norm = 0.;
    } else if (*n == 1) {
	norm = abs(x[1]);
    } else {
	scale = 0.;
	ssq = 1.;
/*        The following loop is equivalent to this call to the LAPACK */
/*        auxiliary routine: */
/*        CALL DLASSQ( N, X, INCX, SCALE, SSQ ) */

	i__1 = (*n - 1) * *incx + 1;
	i__2 = *incx;
	for (ix = 1; i__2 < 0 ? ix >= i__1 : ix <= i__1; ix += i__2) {
	    if (x[ix] != 0.) {
		absxi = (d__1 = x[ix], abs(d__1));
		if (scale < absxi) {
/* Computing 2nd power */
		    d__1 = scale / absxi;
		    ssq = ssq * (d__1 * d__1) + 1.;
		    scale = absxi;
		} else {
/* Computing 2nd power */
		    d__1 = absxi / scale;
		    ssq += d__1 * d__1;
		}
	    }
/* L10: */
	}
	norm = scale * sqrt(ssq);
    }

    ret_val = norm;
    return ret_val;

/*     End of DNRM2. */

} /* dnrm2_ */

/* Subroutine */ int drot_(integer *n, doublereal *dx, integer *incx,
	doublereal *dy, integer *incy, doublereal *c__, doublereal *s)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    integer i__, ix, iy;
    doublereal dtemp;

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*     applies a plane rotation. */
/*     jack dongarra, linpack, 3/11/78. */
/*     modified 12/3/93, array(1) declarations changed to array(*) */


/*     .. Local Scalars .. */
/*     .. */
    /* Parameter adjustments */
    --dy;
    --dx;

    /* Function Body */
    if (*n <= 0) {
	return 0;
    }
    if (*incx == 1 && *incy == 1) {
	goto L20;
    }

/*       code for unequal increments or equal increments not equal */
/*         to 1 */

    ix = 1;
    iy = 1;
    if (*incx < 0) {
	ix = (-(*n) + 1) * *incx + 1;
    }
    if (*incy < 0) {
	iy = (-(*n) + 1) * *incy + 1;
    }
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	dtemp = *c__ * dx[ix] + *s * dy[iy];
	dy[iy] = *c__ * dy[iy] - *s * dx[ix];
	dx[ix] = dtemp;
	ix += *incx;
	iy += *incy;
/* L10: */
    }
    return 0;

/*       code for both increments equal to 1 */

L20:
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	dtemp = *c__ * dx[i__] + *s * dy[i__];
	dy[i__] = *c__ * dy[i__] - *s * dx[i__];
	dx[i__] = dtemp;
/* L30: */
    }
    return 0;
} /* drot_ */

/* Subroutine */ int dscal_(integer *n, doublereal *da, doublereal *dx,
	integer *incx)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Local variables */
    integer i__, m, mp1, nincx;

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */
/* * */
/*     scales a vector by a constant. */
/*     uses unrolled loops for increment equal to one. */
/*     jack dongarra, linpack, 3/11/78. */
/*     modified 3/93 to return if incx .le. 0. */
/*     modified 12/3/93, array(1) declarations changed to array(*) */


/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
    /* Parameter adjustments */
    --dx;

    /* Function Body */
    if (*n <= 0 || *incx <= 0) {
	return 0;
    }
    if (*incx == 1) {
	goto L20;
    }

/*        code for increment not equal to 1 */

    nincx = *n * *incx;
    i__1 = nincx;
    i__2 = *incx;
    for (i__ = 1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {
	dx[i__] = *da * dx[i__];
/* L10: */
    }
    return 0;

/*        code for increment equal to 1 */


/*        clean-up loop */

L20:
    m = *n % 5;
    if (m == 0) {
	goto L40;
    }
    i__2 = m;
    for (i__ = 1; i__ <= i__2; ++i__) {
	dx[i__] = *da * dx[i__];
/* L30: */
    }
    if (*n < 5) {
	return 0;
    }
L40:
    mp1 = m + 1;
    i__2 = *n;
    for (i__ = mp1; i__ <= i__2; i__ += 5) {
	dx[i__] = *da * dx[i__];
	dx[i__ + 1] = *da * dx[i__ + 1];
	dx[i__ + 2] = *da * dx[i__ + 2];
	dx[i__ + 3] = *da * dx[i__ + 3];
	dx[i__ + 4] = *da * dx[i__ + 4];
/* L50: */
    }
    return 0;
} /* dscal_ */

/* Subroutine */ int dswap_(integer *n, doublereal *dx, integer *incx,
	doublereal *dy, integer *incy)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    integer i__, m, ix, iy, mp1;
    doublereal dtemp;

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*     interchanges two vectors. */
/*     uses unrolled loops for increments equal one. */
/*     jack dongarra, linpack, 3/11/78. */
/*     modified 12/3/93, array(1) declarations changed to array(*) */


/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
    /* Parameter adjustments */
    --dy;
    --dx;

    /* Function Body */
    if (*n <= 0) {
	return 0;
    }
    if (*incx == 1 && *incy == 1) {
	goto L20;
    }

/*       code for unequal increments or equal increments not equal */
/*         to 1 */

    ix = 1;
    iy = 1;
    if (*incx < 0) {
	ix = (-(*n) + 1) * *incx + 1;
    }
    if (*incy < 0) {
	iy = (-(*n) + 1) * *incy + 1;
    }
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	dtemp = dx[ix];
	dx[ix] = dy[iy];
	dy[iy] = dtemp;
	ix += *incx;
	iy += *incy;
/* L10: */
    }
    return 0;

/*       code for both increments equal to 1 */


/*       clean-up loop */

L20:
    m = *n % 3;
    if (m == 0) {
	goto L40;
    }
    i__1 = m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	dtemp = dx[i__];
	dx[i__] = dy[i__];
	dy[i__] = dtemp;
/* L30: */
    }
    if (*n < 3) {
	return 0;
    }
L40:
    mp1 = m + 1;
    i__1 = *n;
    for (i__ = mp1; i__ <= i__1; i__ += 3) {
	dtemp = dx[i__];
	dx[i__] = dy[i__];
	dy[i__] = dtemp;
	dtemp = dx[i__ + 1];
	dx[i__ + 1] = dy[i__ + 1];
	dy[i__ + 1] = dtemp;
	dtemp = dx[i__ + 2];
	dx[i__ + 2] = dy[i__ + 2];
	dy[i__ + 2] = dtemp;
/* L50: */
    }
    return 0;
} /* dswap_ */

/* Subroutine */ int dtrmm_(char *side, char *uplo, char *transa, char *diag,
	integer *m, integer *n, doublereal *alpha, doublereal *a, integer *
	lda, doublereal *b, integer *ldb)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, i__1, i__2, i__3;

    /* Local variables */
    integer i__, j, k, info;
    doublereal temp;
    logical lside;
    extern logical lsame_(char *, char *);
    integer nrowa;
    logical upper;
    extern /* Subroutine */ int xerbla_(char *, integer *);
    logical nounit;

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DTRMM  performs one of the matrix-matrix operations */

/*     B := alpha*op( A )*B,   or   B := alpha*B*op( A ), */

/*  where  alpha  is a scalar,  B  is an m by n matrix,  A  is a unit, or */
/*  non-unit,  upper or lower triangular matrix  and  op( A )  is one  of */

/*     op( A ) = A   or   op( A ) = A'. */

/*  Arguments */
/*  ========== */

/*  SIDE   - CHARACTER*1. */
/*           On entry,  SIDE specifies whether  op( A ) multiplies B from */
/*           the left or right as follows: */

/*              SIDE = 'L' or 'l'   B := alpha*op( A )*B. */

/*              SIDE = 'R' or 'r'   B := alpha*B*op( A ). */

/*           Unchanged on exit. */

/*  UPLO   - CHARACTER*1. */
/*           On entry, UPLO specifies whether the matrix A is an upper or */
/*           lower triangular matrix as follows: */

/*              UPLO = 'U' or 'u'   A is an upper triangular matrix. */

/*              UPLO = 'L' or 'l'   A is a lower triangular matrix. */

/*           Unchanged on exit. */

/*  TRANSA - CHARACTER*1. */
/*           On entry, TRANSA specifies the form of op( A ) to be used in */
/*           the matrix multiplication as follows: */

/*              TRANSA = 'N' or 'n'   op( A ) = A. */

/*              TRANSA = 'T' or 't'   op( A ) = A'. */

/*              TRANSA = 'C' or 'c'   op( A ) = A'. */

/*           Unchanged on exit. */

/*  DIAG   - CHARACTER*1. */
/*           On entry, DIAG specifies whether or not A is unit triangular */
/*           as follows: */

/*              DIAG = 'U' or 'u'   A is assumed to be unit triangular. */

/*              DIAG = 'N' or 'n'   A is not assumed to be unit */
/*                                  triangular. */

/*           Unchanged on exit. */

/*  M      - INTEGER. */
/*           On entry, M specifies the number of rows of B. M must be at */
/*           least zero. */
/*           Unchanged on exit. */

/*  N      - INTEGER. */
/*           On entry, N specifies the number of columns of B.  N must be */
/*           at least zero. */
/*           Unchanged on exit. */

/*  ALPHA  - DOUBLE PRECISION. */
/*           On entry,  ALPHA specifies the scalar  alpha. When  alpha is */
/*           zero then  A is not referenced and  B need not be set before */
/*           entry. */
/*           Unchanged on exit. */

/*  A      - DOUBLE PRECISION array of DIMENSION ( LDA, k ), where k is m */
/*           when  SIDE = 'L' or 'l'  and is  n  when  SIDE = 'R' or 'r'. */
/*           Before entry  with  UPLO = 'U' or 'u',  the  leading  k by k */
/*           upper triangular part of the array  A must contain the upper */
/*           triangular matrix  and the strictly lower triangular part of */
/*           A is not referenced. */
/*           Before entry  with  UPLO = 'L' or 'l',  the  leading  k by k */
/*           lower triangular part of the array  A must contain the lower */
/*           triangular matrix  and the strictly upper triangular part of */
/*           A is not referenced. */
/*           Note that when  DIAG = 'U' or 'u',  the diagonal elements of */
/*           A  are not referenced either,  but are assumed to be  unity. */
/*           Unchanged on exit. */

/*  LDA    - INTEGER. */
/*           On entry, LDA specifies the first dimension of A as declared */
/*           in the calling (sub) program.  When  SIDE = 'L' or 'l'  then */
/*           LDA  must be at least  max( 1, m ),  when  SIDE = 'R' or 'r' */
/*           then LDA must be at least max( 1, n ). */
/*           Unchanged on exit. */

/*  B      - DOUBLE PRECISION array of DIMENSION ( LDB, n ). */
/*           Before entry,  the leading  m by n part of the array  B must */
/*           contain the matrix  B,  and  on exit  is overwritten  by the */
/*           transformed matrix. */

/*  LDB    - INTEGER. */
/*           On entry, LDB specifies the first dimension of B as declared */
/*           in  the  calling  (sub)  program.   LDB  must  be  at  least */
/*           max( 1, m ). */
/*           Unchanged on exit. */


/*  Level 3 Blas routine. */

/*  -- Written on 8-February-1989. */
/*     Jack Dongarra, Argonne National Laboratory. */
/*     Iain Duff, AERE Harwell. */
/*     Jeremy Du Croz, Numerical Algorithms Group Ltd. */
/*     Sven Hammarling, Numerical Algorithms Group Ltd. */


/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Parameters .. */
/*     .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;

    /* Function Body */
    lside = lsame_(side, "L");
    if (lside) {
	nrowa = *m;
    } else {
	nrowa = *n;
    }
    nounit = lsame_(diag, "N");
    upper = lsame_(uplo, "U");

    info = 0;
    if (! lside && ! lsame_(side, "R")) {
	info = 1;
    } else if (! upper && ! lsame_(uplo, "L")) {
	info = 2;
    } else if (! lsame_(transa, "N") && ! lsame_(transa,
	     "T") && ! lsame_(transa, "C")) {
	info = 3;
    } else if (! lsame_(diag, "U") && ! lsame_(diag,
	    "N")) {
	info = 4;
    } else if (*m < 0) {
	info = 5;
    } else if (*n < 0) {
	info = 6;
    } else if (*lda < max(1,nrowa)) {
	info = 9;
    } else if (*ldb < max(1,*m)) {
	info = 11;
    }
    if (info != 0) {
	xerbla_("DTRMM ", &info);
	return 0;
    }

/*     Quick return if possible. */

    if (*m == 0 || *n == 0) {
	return 0;
    }

/*     And when  alpha.eq.zero. */

    if (*alpha == 0.) {
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		b[i__ + j * b_dim1] = 0.;
/* L10: */
	    }
/* L20: */
	}
	return 0;
    }

/*     Start the operations. */

    if (lside) {
	if (lsame_(transa, "N")) {

/*           Form  B := alpha*A*B. */

	    if (upper) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = *m;
		    for (k = 1; k <= i__2; ++k) {
			if (b[k + j * b_dim1] != 0.) {
			    temp = *alpha * b[k + j * b_dim1];
			    i__3 = k - 1;
			    for (i__ = 1; i__ <= i__3; ++i__) {
				b[i__ + j * b_dim1] += temp * a[i__ + k *
					a_dim1];
/* L30: */
			    }
			    if (nounit) {
				temp *= a[k + k * a_dim1];
			    }
			    b[k + j * b_dim1] = temp;
			}
/* L40: */
		    }
/* L50: */
		}
	    } else {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    for (k = *m; k >= 1; --k) {
			if (b[k + j * b_dim1] != 0.) {
			    temp = *alpha * b[k + j * b_dim1];
			    b[k + j * b_dim1] = temp;
			    if (nounit) {
				b[k + j * b_dim1] *= a[k + k * a_dim1];
			    }
			    i__2 = *m;
			    for (i__ = k + 1; i__ <= i__2; ++i__) {
				b[i__ + j * b_dim1] += temp * a[i__ + k *
					a_dim1];
/* L60: */
			    }
			}
/* L70: */
		    }
/* L80: */
		}
	    }
	} else {

/*           Form  B := alpha*A'*B. */

	    if (upper) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    for (i__ = *m; i__ >= 1; --i__) {
			temp = b[i__ + j * b_dim1];
			if (nounit) {
			    temp *= a[i__ + i__ * a_dim1];
			}
			i__2 = i__ - 1;
			for (k = 1; k <= i__2; ++k) {
			    temp += a[k + i__ * a_dim1] * b[k + j * b_dim1];
/* L90: */
			}
			b[i__ + j * b_dim1] = *alpha * temp;
/* L100: */
		    }
/* L110: */
		}
	    } else {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = *m;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			temp = b[i__ + j * b_dim1];
			if (nounit) {
			    temp *= a[i__ + i__ * a_dim1];
			}
			i__3 = *m;
			for (k = i__ + 1; k <= i__3; ++k) {
			    temp += a[k + i__ * a_dim1] * b[k + j * b_dim1];
/* L120: */
			}
			b[i__ + j * b_dim1] = *alpha * temp;
/* L130: */
		    }
/* L140: */
		}
	    }
	}
    } else {
	if (lsame_(transa, "N")) {

/*           Form  B := alpha*B*A. */

	    if (upper) {
		for (j = *n; j >= 1; --j) {
		    temp = *alpha;
		    if (nounit) {
			temp *= a[j + j * a_dim1];
		    }
		    i__1 = *m;
		    for (i__ = 1; i__ <= i__1; ++i__) {
			b[i__ + j * b_dim1] = temp * b[i__ + j * b_dim1];
/* L150: */
		    }
		    i__1 = j - 1;
		    for (k = 1; k <= i__1; ++k) {
			if (a[k + j * a_dim1] != 0.) {
			    temp = *alpha * a[k + j * a_dim1];
			    i__2 = *m;
			    for (i__ = 1; i__ <= i__2; ++i__) {
				b[i__ + j * b_dim1] += temp * b[i__ + k *
					b_dim1];
/* L160: */
			    }
			}
/* L170: */
		    }
/* L180: */
		}
	    } else {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    temp = *alpha;
		    if (nounit) {
			temp *= a[j + j * a_dim1];
		    }
		    i__2 = *m;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			b[i__ + j * b_dim1] = temp * b[i__ + j * b_dim1];
/* L190: */
		    }
		    i__2 = *n;
		    for (k = j + 1; k <= i__2; ++k) {
			if (a[k + j * a_dim1] != 0.) {
			    temp = *alpha * a[k + j * a_dim1];
			    i__3 = *m;
			    for (i__ = 1; i__ <= i__3; ++i__) {
				b[i__ + j * b_dim1] += temp * b[i__ + k *
					b_dim1];
/* L200: */
			    }
			}
/* L210: */
		    }
/* L220: */
		}
	    }
	} else {

/*           Form  B := alpha*B*A'. */

	    if (upper) {
		i__1 = *n;
		for (k = 1; k <= i__1; ++k) {
		    i__2 = k - 1;
		    for (j = 1; j <= i__2; ++j) {
			if (a[j + k * a_dim1] != 0.) {
			    temp = *alpha * a[j + k * a_dim1];
			    i__3 = *m;
			    for (i__ = 1; i__ <= i__3; ++i__) {
				b[i__ + j * b_dim1] += temp * b[i__ + k *
					b_dim1];
/* L230: */
			    }
			}
/* L240: */
		    }
		    temp = *alpha;
		    if (nounit) {
			temp *= a[k + k * a_dim1];
		    }
		    if (temp != 1.) {
			i__2 = *m;
			for (i__ = 1; i__ <= i__2; ++i__) {
			    b[i__ + k * b_dim1] = temp * b[i__ + k * b_dim1];
/* L250: */
			}
		    }
/* L260: */
		}
	    } else {
		for (k = *n; k >= 1; --k) {
		    i__1 = *n;
		    for (j = k + 1; j <= i__1; ++j) {
			if (a[j + k * a_dim1] != 0.) {
			    temp = *alpha * a[j + k * a_dim1];
			    i__2 = *m;
			    for (i__ = 1; i__ <= i__2; ++i__) {
				b[i__ + j * b_dim1] += temp * b[i__ + k *
					b_dim1];
/* L270: */
			    }
			}
/* L280: */
		    }
		    temp = *alpha;
		    if (nounit) {
			temp *= a[k + k * a_dim1];
		    }
		    if (temp != 1.) {
			i__1 = *m;
			for (i__ = 1; i__ <= i__1; ++i__) {
			    b[i__ + k * b_dim1] = temp * b[i__ + k * b_dim1];
/* L290: */
			}
		    }
/* L300: */
		}
	    }
	}
    }

    return 0;

/*     End of DTRMM . */

} /* dtrmm_ */

/* Subroutine */ int dtrmv_(char *uplo, char *trans, char *diag, integer *n,
	doublereal *a, integer *lda, doublereal *x, integer *incx)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;

    /* Local variables */
    integer i__, j, ix, jx, kx, info;
    doublereal temp;
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int xerbla_(char *, integer *);
    logical nounit;

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DTRMV  performs one of the matrix-vector operations */

/*     x := A*x,   or   x := A'*x, */

/*  where x is an n element vector and  A is an n by n unit, or non-unit, */
/*  upper or lower triangular matrix. */

/*  Arguments */
/*  ========== */

/*  UPLO   - CHARACTER*1. */
/*           On entry, UPLO specifies whether the matrix is an upper or */
/*           lower triangular matrix as follows: */

/*              UPLO = 'U' or 'u'   A is an upper triangular matrix. */

/*              UPLO = 'L' or 'l'   A is a lower triangular matrix. */

/*           Unchanged on exit. */

/*  TRANS  - CHARACTER*1. */
/*           On entry, TRANS specifies the operation to be performed as */
/*           follows: */

/*              TRANS = 'N' or 'n'   x := A*x. */

/*              TRANS = 'T' or 't'   x := A'*x. */

/*              TRANS = 'C' or 'c'   x := A'*x. */

/*           Unchanged on exit. */

/*  DIAG   - CHARACTER*1. */
/*           On entry, DIAG specifies whether or not A is unit */
/*           triangular as follows: */

/*              DIAG = 'U' or 'u'   A is assumed to be unit triangular. */

/*              DIAG = 'N' or 'n'   A is not assumed to be unit */
/*                                  triangular. */

/*           Unchanged on exit. */

/*  N      - INTEGER. */
/*           On entry, N specifies the order of the matrix A. */
/*           N must be at least zero. */
/*           Unchanged on exit. */

/*  A      - DOUBLE PRECISION array of DIMENSION ( LDA, n ). */
/*           Before entry with  UPLO = 'U' or 'u', the leading n by n */
/*           upper triangular part of the array A must contain the upper */
/*           triangular matrix and the strictly lower triangular part of */
/*           A is not referenced. */
/*           Before entry with UPLO = 'L' or 'l', the leading n by n */
/*           lower triangular part of the array A must contain the lower */
/*           triangular matrix and the strictly upper triangular part of */
/*           A is not referenced. */
/*           Note that when  DIAG = 'U' or 'u', the diagonal elements of */
/*           A are not referenced either, but are assumed to be unity. */
/*           Unchanged on exit. */

/*  LDA    - INTEGER. */
/*           On entry, LDA specifies the first dimension of A as declared */
/*           in the calling (sub) program. LDA must be at least */
/*           max( 1, n ). */
/*           Unchanged on exit. */

/*  X      - DOUBLE PRECISION array of dimension at least */
/*           ( 1 + ( n - 1 )*abs( INCX ) ). */
/*           Before entry, the incremented array X must contain the n */
/*           element vector x. On exit, X is overwritten with the */
/*           tranformed vector x. */

/*  INCX   - INTEGER. */
/*           On entry, INCX specifies the increment for the elements of */
/*           X. INCX must not be zero. */
/*           Unchanged on exit. */


/*  Level 2 Blas routine. */

/*  -- Written on 22-October-1986. */
/*     Jack Dongarra, Argonne National Lab. */
/*     Jeremy Du Croz, Nag Central Office. */
/*     Sven Hammarling, Nag Central Office. */
/*     Richard Hanson, Sandia National Labs. */


/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --x;

    /* Function Body */
    info = 0;
    if (! lsame_(uplo, "U") && ! lsame_(uplo, "L")) {
	info = 1;
    } else if (! lsame_(trans, "N") && ! lsame_(trans,
	    "T") && ! lsame_(trans, "C")) {
	info = 2;
    } else if (! lsame_(diag, "U") && ! lsame_(diag,
	    "N")) {
	info = 3;
    } else if (*n < 0) {
	info = 4;
    } else if (*lda < max(1,*n)) {
	info = 6;
    } else if (*incx == 0) {
	info = 8;
    }
    if (info != 0) {
	xerbla_("DTRMV ", &info);
	return 0;
    }

/*     Quick return if possible. */

    if (*n == 0) {
	return 0;
    }

    nounit = lsame_(diag, "N");

/*     Set up the start point in X if the increment is not unity. This */
/*     will be  ( N - 1 )*INCX  too small for descending loops. */

    if (*incx <= 0) {
	kx = 1 - (*n - 1) * *incx;
    } else if (*incx != 1) {
	kx = 1;
    }

/*     Start the operations. In this version the elements of A are */
/*     accessed sequentially with one pass through A. */

    if (lsame_(trans, "N")) {

/*        Form  x := A*x. */

	if (lsame_(uplo, "U")) {
	    if (*incx == 1) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    if (x[j] != 0.) {
			temp = x[j];
			i__2 = j - 1;
			for (i__ = 1; i__ <= i__2; ++i__) {
			    x[i__] += temp * a[i__ + j * a_dim1];
/* L10: */
			}
			if (nounit) {
			    x[j] *= a[j + j * a_dim1];
			}
		    }
/* L20: */
		}
	    } else {
		jx = kx;
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    if (x[jx] != 0.) {
			temp = x[jx];
			ix = kx;
			i__2 = j - 1;
			for (i__ = 1; i__ <= i__2; ++i__) {
			    x[ix] += temp * a[i__ + j * a_dim1];
			    ix += *incx;
/* L30: */
			}
			if (nounit) {
			    x[jx] *= a[j + j * a_dim1];
			}
		    }
		    jx += *incx;
/* L40: */
		}
	    }
	} else {
	    if (*incx == 1) {
		for (j = *n; j >= 1; --j) {
		    if (x[j] != 0.) {
			temp = x[j];
			i__1 = j + 1;
			for (i__ = *n; i__ >= i__1; --i__) {
			    x[i__] += temp * a[i__ + j * a_dim1];
/* L50: */
			}
			if (nounit) {
			    x[j] *= a[j + j * a_dim1];
			}
		    }
/* L60: */
		}
	    } else {
		kx += (*n - 1) * *incx;
		jx = kx;
		for (j = *n; j >= 1; --j) {
		    if (x[jx] != 0.) {
			temp = x[jx];
			ix = kx;
			i__1 = j + 1;
			for (i__ = *n; i__ >= i__1; --i__) {
			    x[ix] += temp * a[i__ + j * a_dim1];
			    ix -= *incx;
/* L70: */
			}
			if (nounit) {
			    x[jx] *= a[j + j * a_dim1];
			}
		    }
		    jx -= *incx;
/* L80: */
		}
	    }
	}
    } else {

/*        Form  x := A'*x. */

	if (lsame_(uplo, "U")) {
	    if (*incx == 1) {
		for (j = *n; j >= 1; --j) {
		    temp = x[j];
		    if (nounit) {
			temp *= a[j + j * a_dim1];
		    }
		    for (i__ = j - 1; i__ >= 1; --i__) {
			temp += a[i__ + j * a_dim1] * x[i__];
/* L90: */
		    }
		    x[j] = temp;
/* L100: */
		}
	    } else {
		jx = kx + (*n - 1) * *incx;
		for (j = *n; j >= 1; --j) {
		    temp = x[jx];
		    ix = jx;
		    if (nounit) {
			temp *= a[j + j * a_dim1];
		    }
		    for (i__ = j - 1; i__ >= 1; --i__) {
			ix -= *incx;
			temp += a[i__ + j * a_dim1] * x[ix];
/* L110: */
		    }
		    x[jx] = temp;
		    jx -= *incx;
/* L120: */
		}
	    }
	} else {
	    if (*incx == 1) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    temp = x[j];
		    if (nounit) {
			temp *= a[j + j * a_dim1];
		    }
		    i__2 = *n;
		    for (i__ = j + 1; i__ <= i__2; ++i__) {
			temp += a[i__ + j * a_dim1] * x[i__];
/* L130: */
		    }
		    x[j] = temp;
/* L140: */
		}
	    } else {
		jx = kx;
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    temp = x[jx];
		    ix = jx;
		    if (nounit) {
			temp *= a[j + j * a_dim1];
		    }
		    i__2 = *n;
		    for (i__ = j + 1; i__ <= i__2; ++i__) {
			ix += *incx;
			temp += a[i__ + j * a_dim1] * x[ix];
/* L150: */
		    }
		    x[jx] = temp;
		    jx += *incx;
/* L160: */
		}
	    }
	}
    }

    return 0;

/*     End of DTRMV . */

} /* dtrmv_ */

/* Subroutine */ int dtrsm_(char *side, char *uplo, char *transa, char *diag,
	integer *m, integer *n, doublereal *alpha, doublereal *a, integer *
	lda, doublereal *b, integer *ldb)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, i__1, i__2, i__3;

    /* Local variables */
    integer i__, j, k, info;
    doublereal temp;
    logical lside;
    extern logical lsame_(char *, char *);
    integer nrowa;
    logical upper;
    extern /* Subroutine */ int xerbla_(char *, integer *);
    logical nounit;

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DTRSM  solves one of the matrix equations */

/*     op( A )*X = alpha*B,   or   X*op( A ) = alpha*B, */

/*  where alpha is a scalar, X and B are m by n matrices, A is a unit, or */
/*  non-unit,  upper or lower triangular matrix  and  op( A )  is one  of */

/*     op( A ) = A   or   op( A ) = A'. */

/*  The matrix X is overwritten on B. */

/*  Arguments */
/*  ========== */

/*  SIDE   - CHARACTER*1. */
/*           On entry, SIDE specifies whether op( A ) appears on the left */
/*           or right of X as follows: */

/*              SIDE = 'L' or 'l'   op( A )*X = alpha*B. */

/*              SIDE = 'R' or 'r'   X*op( A ) = alpha*B. */

/*           Unchanged on exit. */

/*  UPLO   - CHARACTER*1. */
/*           On entry, UPLO specifies whether the matrix A is an upper or */
/*           lower triangular matrix as follows: */

/*              UPLO = 'U' or 'u'   A is an upper triangular matrix. */

/*              UPLO = 'L' or 'l'   A is a lower triangular matrix. */

/*           Unchanged on exit. */

/*  TRANSA - CHARACTER*1. */
/*           On entry, TRANSA specifies the form of op( A ) to be used in */
/*           the matrix multiplication as follows: */

/*              TRANSA = 'N' or 'n'   op( A ) = A. */

/*              TRANSA = 'T' or 't'   op( A ) = A'. */

/*              TRANSA = 'C' or 'c'   op( A ) = A'. */

/*           Unchanged on exit. */

/*  DIAG   - CHARACTER*1. */
/*           On entry, DIAG specifies whether or not A is unit triangular */
/*           as follows: */

/*              DIAG = 'U' or 'u'   A is assumed to be unit triangular. */

/*              DIAG = 'N' or 'n'   A is not assumed to be unit */
/*                                  triangular. */

/*           Unchanged on exit. */

/*  M      - INTEGER. */
/*           On entry, M specifies the number of rows of B. M must be at */
/*           least zero. */
/*           Unchanged on exit. */

/*  N      - INTEGER. */
/*           On entry, N specifies the number of columns of B.  N must be */
/*           at least zero. */
/*           Unchanged on exit. */

/*  ALPHA  - DOUBLE PRECISION. */
/*           On entry,  ALPHA specifies the scalar  alpha. When  alpha is */
/*           zero then  A is not referenced and  B need not be set before */
/*           entry. */
/*           Unchanged on exit. */

/*  A      - DOUBLE PRECISION array of DIMENSION ( LDA, k ), where k is m */
/*           when  SIDE = 'L' or 'l'  and is  n  when  SIDE = 'R' or 'r'. */
/*           Before entry  with  UPLO = 'U' or 'u',  the  leading  k by k */
/*           upper triangular part of the array  A must contain the upper */
/*           triangular matrix  and the strictly lower triangular part of */
/*           A is not referenced. */
/*           Before entry  with  UPLO = 'L' or 'l',  the  leading  k by k */
/*           lower triangular part of the array  A must contain the lower */
/*           triangular matrix  and the strictly upper triangular part of */
/*           A is not referenced. */
/*           Note that when  DIAG = 'U' or 'u',  the diagonal elements of */
/*           A  are not referenced either,  but are assumed to be  unity. */
/*           Unchanged on exit. */

/*  LDA    - INTEGER. */
/*           On entry, LDA specifies the first dimension of A as declared */
/*           in the calling (sub) program.  When  SIDE = 'L' or 'l'  then */
/*           LDA  must be at least  max( 1, m ),  when  SIDE = 'R' or 'r' */
/*           then LDA must be at least max( 1, n ). */
/*           Unchanged on exit. */

/*  B      - DOUBLE PRECISION array of DIMENSION ( LDB, n ). */
/*           Before entry,  the leading  m by n part of the array  B must */
/*           contain  the  right-hand  side  matrix  B,  and  on exit  is */
/*           overwritten by the solution matrix  X. */

/*  LDB    - INTEGER. */
/*           On entry, LDB specifies the first dimension of B as declared */
/*           in  the  calling  (sub)  program.   LDB  must  be  at  least */
/*           max( 1, m ). */
/*           Unchanged on exit. */


/*  Level 3 Blas routine. */


/*  -- Written on 8-February-1989. */
/*     Jack Dongarra, Argonne National Laboratory. */
/*     Iain Duff, AERE Harwell. */
/*     Jeremy Du Croz, Numerical Algorithms Group Ltd. */
/*     Sven Hammarling, Numerical Algorithms Group Ltd. */


/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Parameters .. */
/*     .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;

    /* Function Body */
    lside = lsame_(side, "L");
    if (lside) {
	nrowa = *m;
    } else {
	nrowa = *n;
    }
    nounit = lsame_(diag, "N");
    upper = lsame_(uplo, "U");

    info = 0;
    if (! lside && ! lsame_(side, "R")) {
	info = 1;
    } else if (! upper && ! lsame_(uplo, "L")) {
	info = 2;
    } else if (! lsame_(transa, "N") && ! lsame_(transa,
	     "T") && ! lsame_(transa, "C")) {
	info = 3;
    } else if (! lsame_(diag, "U") && ! lsame_(diag,
	    "N")) {
	info = 4;
    } else if (*m < 0) {
	info = 5;
    } else if (*n < 0) {
	info = 6;
    } else if (*lda < max(1,nrowa)) {
	info = 9;
    } else if (*ldb < max(1,*m)) {
	info = 11;
    }
    if (info != 0) {
	xerbla_("DTRSM ", &info);
	return 0;
    }

/*     Quick return if possible. */

    if (*m == 0 || *n == 0) {
	return 0;
    }

/*     And when  alpha.eq.zero. */

    if (*alpha == 0.) {
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		b[i__ + j * b_dim1] = 0.;
/* L10: */
	    }
/* L20: */
	}
	return 0;
    }

/*     Start the operations. */

    if (lside) {
	if (lsame_(transa, "N")) {

/*           Form  B := alpha*inv( A )*B. */

	    if (upper) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    if (*alpha != 1.) {
			i__2 = *m;
			for (i__ = 1; i__ <= i__2; ++i__) {
			    b[i__ + j * b_dim1] = *alpha * b[i__ + j * b_dim1]
				    ;
/* L30: */
			}
		    }
		    for (k = *m; k >= 1; --k) {
			if (b[k + j * b_dim1] != 0.) {
			    if (nounit) {
				b[k + j * b_dim1] /= a[k + k * a_dim1];
			    }
			    i__2 = k - 1;
			    for (i__ = 1; i__ <= i__2; ++i__) {
				b[i__ + j * b_dim1] -= b[k + j * b_dim1] * a[
					i__ + k * a_dim1];
/* L40: */
			    }
			}
/* L50: */
		    }
/* L60: */
		}
	    } else {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    if (*alpha != 1.) {
			i__2 = *m;
			for (i__ = 1; i__ <= i__2; ++i__) {
			    b[i__ + j * b_dim1] = *alpha * b[i__ + j * b_dim1]
				    ;
/* L70: */
			}
		    }
		    i__2 = *m;
		    for (k = 1; k <= i__2; ++k) {
			if (b[k + j * b_dim1] != 0.) {
			    if (nounit) {
				b[k + j * b_dim1] /= a[k + k * a_dim1];
			    }
			    i__3 = *m;
			    for (i__ = k + 1; i__ <= i__3; ++i__) {
				b[i__ + j * b_dim1] -= b[k + j * b_dim1] * a[
					i__ + k * a_dim1];
/* L80: */
			    }
			}
/* L90: */
		    }
/* L100: */
		}
	    }
	} else {

/*           Form  B := alpha*inv( A' )*B. */

	    if (upper) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = *m;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			temp = *alpha * b[i__ + j * b_dim1];
			i__3 = i__ - 1;
			for (k = 1; k <= i__3; ++k) {
			    temp -= a[k + i__ * a_dim1] * b[k + j * b_dim1];
/* L110: */
			}
			if (nounit) {
			    temp /= a[i__ + i__ * a_dim1];
			}
			b[i__ + j * b_dim1] = temp;
/* L120: */
		    }
/* L130: */
		}
	    } else {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    for (i__ = *m; i__ >= 1; --i__) {
			temp = *alpha * b[i__ + j * b_dim1];
			i__2 = *m;
			for (k = i__ + 1; k <= i__2; ++k) {
			    temp -= a[k + i__ * a_dim1] * b[k + j * b_dim1];
/* L140: */
			}
			if (nounit) {
			    temp /= a[i__ + i__ * a_dim1];
			}
			b[i__ + j * b_dim1] = temp;
/* L150: */
		    }
/* L160: */
		}
	    }
	}
    } else {
	if (lsame_(transa, "N")) {

/*           Form  B := alpha*B*inv( A ). */

	    if (upper) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    if (*alpha != 1.) {
			i__2 = *m;
			for (i__ = 1; i__ <= i__2; ++i__) {
			    b[i__ + j * b_dim1] = *alpha * b[i__ + j * b_dim1]
				    ;
/* L170: */
			}
		    }
		    i__2 = j - 1;
		    for (k = 1; k <= i__2; ++k) {
			if (a[k + j * a_dim1] != 0.) {
			    i__3 = *m;
			    for (i__ = 1; i__ <= i__3; ++i__) {
				b[i__ + j * b_dim1] -= a[k + j * a_dim1] * b[
					i__ + k * b_dim1];
/* L180: */
			    }
			}
/* L190: */
		    }
		    if (nounit) {
			temp = 1. / a[j + j * a_dim1];
			i__2 = *m;
			for (i__ = 1; i__ <= i__2; ++i__) {
			    b[i__ + j * b_dim1] = temp * b[i__ + j * b_dim1];
/* L200: */
			}
		    }
/* L210: */
		}
	    } else {
		for (j = *n; j >= 1; --j) {
		    if (*alpha != 1.) {
			i__1 = *m;
			for (i__ = 1; i__ <= i__1; ++i__) {
			    b[i__ + j * b_dim1] = *alpha * b[i__ + j * b_dim1]
				    ;
/* L220: */
			}
		    }
		    i__1 = *n;
		    for (k = j + 1; k <= i__1; ++k) {
			if (a[k + j * a_dim1] != 0.) {
			    i__2 = *m;
			    for (i__ = 1; i__ <= i__2; ++i__) {
				b[i__ + j * b_dim1] -= a[k + j * a_dim1] * b[
					i__ + k * b_dim1];
/* L230: */
			    }
			}
/* L240: */
		    }
		    if (nounit) {
			temp = 1. / a[j + j * a_dim1];
			i__1 = *m;
			for (i__ = 1; i__ <= i__1; ++i__) {
			    b[i__ + j * b_dim1] = temp * b[i__ + j * b_dim1];
/* L250: */
			}
		    }
/* L260: */
		}
	    }
	} else {

/*           Form  B := alpha*B*inv( A' ). */

	    if (upper) {
		for (k = *n; k >= 1; --k) {
		    if (nounit) {
			temp = 1. / a[k + k * a_dim1];
			i__1 = *m;
			for (i__ = 1; i__ <= i__1; ++i__) {
			    b[i__ + k * b_dim1] = temp * b[i__ + k * b_dim1];
/* L270: */
			}
		    }
		    i__1 = k - 1;
		    for (j = 1; j <= i__1; ++j) {
			if (a[j + k * a_dim1] != 0.) {
			    temp = a[j + k * a_dim1];
			    i__2 = *m;
			    for (i__ = 1; i__ <= i__2; ++i__) {
				b[i__ + j * b_dim1] -= temp * b[i__ + k *
					b_dim1];
/* L280: */
			    }
			}
/* L290: */
		    }
		    if (*alpha != 1.) {
			i__1 = *m;
			for (i__ = 1; i__ <= i__1; ++i__) {
			    b[i__ + k * b_dim1] = *alpha * b[i__ + k * b_dim1]
				    ;
/* L300: */
			}
		    }
/* L310: */
		}
	    } else {
		i__1 = *n;
		for (k = 1; k <= i__1; ++k) {
		    if (nounit) {
			temp = 1. / a[k + k * a_dim1];
			i__2 = *m;
			for (i__ = 1; i__ <= i__2; ++i__) {
			    b[i__ + k * b_dim1] = temp * b[i__ + k * b_dim1];
/* L320: */
			}
		    }
		    i__2 = *n;
		    for (j = k + 1; j <= i__2; ++j) {
			if (a[j + k * a_dim1] != 0.) {
			    temp = a[j + k * a_dim1];
			    i__3 = *m;
			    for (i__ = 1; i__ <= i__3; ++i__) {
				b[i__ + j * b_dim1] -= temp * b[i__ + k *
					b_dim1];
/* L330: */
			    }
			}
/* L340: */
		    }
		    if (*alpha != 1.) {
			i__2 = *m;
			for (i__ = 1; i__ <= i__2; ++i__) {
			    b[i__ + k * b_dim1] = *alpha * b[i__ + k * b_dim1]
				    ;
/* L350: */
			}
		    }
/* L360: */
		}
	    }
	}
    }

    return 0;

/*     End of DTRSM . */

} /* dtrsm_ */

integer idamax_(integer *n, doublereal *dx, integer *incx)
{
    /* System generated locals */
    integer ret_val, i__1;
    doublereal d__1;

    /* Local variables */
    integer i__, ix;
    doublereal dmax__;

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*     finds the index of element having max. absolute value. */
/*     jack dongarra, linpack, 3/11/78. */
/*     modified 3/93 to return if incx .le. 0. */
/*     modified 12/3/93, array(1) declarations changed to array(*) */


/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
    /* Parameter adjustments */
    --dx;

    /* Function Body */
    ret_val = 0;
    if (*n < 1 || *incx <= 0) {
	return ret_val;
    }
    ret_val = 1;
    if (*n == 1) {
	return ret_val;
    }
    if (*incx == 1) {
	goto L20;
    }

/*        code for increment not equal to 1 */

    ix = 1;
    dmax__ = abs(dx[1]);
    ix += *incx;
    i__1 = *n;
    for (i__ = 2; i__ <= i__1; ++i__) {
	if ((d__1 = dx[ix], abs(d__1)) <= dmax__) {
	    goto L5;
	}
	ret_val = i__;
	dmax__ = (d__1 = dx[ix], abs(d__1));
L5:
	ix += *incx;
/* L10: */
    }
    return ret_val;

/*        code for increment equal to 1 */

L20:
    dmax__ = abs(dx[1]);
    i__1 = *n;
    for (i__ = 2; i__ <= i__1; ++i__) {
	if ((d__1 = dx[i__], abs(d__1)) <= dmax__) {
	    goto L30;
	}
	ret_val = i__;
	dmax__ = (d__1 = dx[i__], abs(d__1));
L30:
	;
    }
    return ret_val;
} /* idamax_ */

/*
 * =============================================================================
 * LAPACK
 * =============================================================================
 */

/* Subroutine */ int dbdsqr_(char *uplo, integer *n, integer *ncvt, integer *
	nru, integer *ncc, doublereal *d__, doublereal *e, doublereal *vt,
	integer *ldvt, doublereal *u, integer *ldu, doublereal *c__, integer *
	ldc, doublereal *work, integer *info)
{
    /* Table of constant values */

    doublereal c_b15 = -.125;
    integer c__1 = 1;
    doublereal c_b49 = 1.;
    doublereal c_b72 = -1.;

    /* System generated locals */
    integer c_dim1, c_offset, u_dim1, u_offset, vt_dim1, vt_offset, i__1,
	    i__2;
    doublereal d__1, d__2, d__3, d__4;

    /* Local variables */
    doublereal f, g, h__;
    integer i__, j, m;
    doublereal r__, cs;
    integer ll;
    doublereal sn, mu;
    integer nm1, nm12, nm13, lll;
    doublereal eps, sll, tol, abse;
    integer idir;
    doublereal abss;
    integer oldm;
    doublereal cosl;
    integer isub, iter;
    doublereal unfl, sinl, cosr, smin, smax, sinr;
    extern /* Subroutine */ int drot_(integer *, doublereal *, integer *,
	    doublereal *, integer *, doublereal *, doublereal *), dlas2_(
	    doublereal *, doublereal *, doublereal *, doublereal *,
	    doublereal *), dscal_(integer *, doublereal *, doublereal *,
	    integer *);
    extern logical lsame_(char *, char *);
    doublereal oldcs;
    extern /* Subroutine */ int dlasr_(char *, char *, char *, integer *,
	    integer *, doublereal *, doublereal *, doublereal *, integer *);
    integer oldll;
    doublereal shift, sigmn, oldsn;
    extern /* Subroutine */ int dswap_(integer *, doublereal *, integer *,
	    doublereal *, integer *);
    integer maxit;
    doublereal sminl, sigmx;
    logical lower;
    extern /* Subroutine */ int dlasq1_(integer *, doublereal *, doublereal *,
	     doublereal *, integer *), dlasv2_(doublereal *, doublereal *,
	    doublereal *, doublereal *, doublereal *, doublereal *,
	    doublereal *, doublereal *, doublereal *);
    extern doublereal dlamch_(char *);
    extern /* Subroutine */ int dlartg_(doublereal *, doublereal *,
	    doublereal *, doublereal *, doublereal *), xerbla_(char *,
	    integer *);
    doublereal sminoa, thresh;
    logical rotate;
    doublereal tolmul;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     January 2007 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DBDSQR computes the singular values and, optionally, the right and/or */
/*  left singular vectors from the singular value decomposition (SVD) of */
/*  a real N-by-N (upper or lower) bidiagonal matrix B using the implicit */
/*  zero-shift QR algorithm.  The SVD of B has the form */

/*     B = Q * S * P**T */

/*  where S is the diagonal matrix of singular values, Q is an orthogonal */
/*  matrix of left singular vectors, and P is an orthogonal matrix of */
/*  right singular vectors.  If left singular vectors are requested, this */
/*  subroutine actually returns U*Q instead of Q, and, if right singular */
/*  vectors are requested, this subroutine returns P**T*VT instead of */
/*  P**T, for given real input matrices U and VT.  When U and VT are the */
/*  orthogonal matrices that reduce a general matrix A to bidiagonal */
/*  form:  A = U*B*VT, as computed by DGEBRD, then */

/*     A = (U*Q) * S * (P**T*VT) */

/*  is the SVD of A.  Optionally, the subroutine may also compute Q**T*C */
/*  for a given real input matrix C. */

/*  See "Computing  Small Singular Values of Bidiagonal Matrices With */
/*  Guaranteed High Relative Accuracy," by J. Demmel and W. Kahan, */
/*  LAPACK Working Note #3 (or SIAM J. Sci. Statist. Comput. vol. 11, */
/*  no. 5, pp. 873-912, Sept 1990) and */
/*  "Accurate singular values and differential qd algorithms," by */
/*  B. Parlett and V. Fernando, Technical Report CPAM-554, Mathematics */
/*  Department, University of California at Berkeley, July 1992 */
/*  for a detailed description of the algorithm. */

/*  Arguments */
/*  ========= */

/*  UPLO    (input) CHARACTER*1 */
/*          = 'U':  B is upper bidiagonal; */
/*          = 'L':  B is lower bidiagonal. */

/*  N       (input) INTEGER */
/*          The order of the matrix B.  N >= 0. */

/*  NCVT    (input) INTEGER */
/*          The number of columns of the matrix VT. NCVT >= 0. */

/*  NRU     (input) INTEGER */
/*          The number of rows of the matrix U. NRU >= 0. */

/*  NCC     (input) INTEGER */
/*          The number of columns of the matrix C. NCC >= 0. */

/*  D       (input/output) DOUBLE PRECISION array, dimension (N) */
/*          On entry, the n diagonal elements of the bidiagonal matrix B. */
/*          On exit, if INFO=0, the singular values of B in decreasing */
/*          order. */

/*  E       (input/output) DOUBLE PRECISION array, dimension (N-1) */
/*          On entry, the N-1 offdiagonal elements of the bidiagonal */
/*          matrix B. */
/*          On exit, if INFO = 0, E is destroyed; if INFO > 0, D and E */
/*          will contain the diagonal and superdiagonal elements of a */
/*          bidiagonal matrix orthogonally equivalent to the one given */
/*          as input. */

/*  VT      (input/output) DOUBLE PRECISION array, dimension (LDVT, NCVT) */
/*          On entry, an N-by-NCVT matrix VT. */
/*          On exit, VT is overwritten by P**T * VT. */
/*          Not referenced if NCVT = 0. */

/*  LDVT    (input) INTEGER */
/*          The leading dimension of the array VT. */
/*          LDVT >= max(1,N) if NCVT > 0; LDVT >= 1 if NCVT = 0. */

/*  U       (input/output) DOUBLE PRECISION array, dimension (LDU, N) */
/*          On entry, an NRU-by-N matrix U. */
/*          On exit, U is overwritten by U * Q. */
/*          Not referenced if NRU = 0. */

/*  LDU     (input) INTEGER */
/*          The leading dimension of the array U.  LDU >= max(1,NRU). */

/*  C       (input/output) DOUBLE PRECISION array, dimension (LDC, NCC) */
/*          On entry, an N-by-NCC matrix C. */
/*          On exit, C is overwritten by Q**T * C. */
/*          Not referenced if NCC = 0. */

/*  LDC     (input) INTEGER */
/*          The leading dimension of the array C. */
/*          LDC >= max(1,N) if NCC > 0; LDC >=1 if NCC = 0. */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (4*N) */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  If INFO = -i, the i-th argument had an illegal value */
/*          > 0: */
/*             if NCVT = NRU = NCC = 0, */
/*                = 1, a split was marked by a positive value in E */
/*                = 2, current block of Z not diagonalized after 30*N */
/*                     iterations (in inner while loop) */
/*                = 3, termination criterion of outer while loop not met */
/*                     (program created more than N unreduced blocks) */
/*             else NCVT = NRU = NCC = 0, */
/*                   the algorithm did not converge; D and E contain the */
/*                   elements of a bidiagonal matrix which is orthogonally */
/*                   similar to the input matrix B;  if INFO = i, i */
/*                   elements of E have not converged to zero. */

/*  Internal Parameters */
/*  =================== */

/*  TOLMUL  DOUBLE PRECISION, default = max(10,min(100,EPS**(-1/8))) */
/*          TOLMUL controls the convergence criterion of the QR loop. */
/*          If it is positive, TOLMUL*EPS is the desired relative */
/*             precision in the computed singular values. */
/*          If it is negative, abs(TOLMUL*EPS*sigma_max) is the */
/*             desired absolute accuracy in the computed singular */
/*             values (corresponds to relative accuracy */
/*             abs(TOLMUL*EPS) in the largest singular value. */
/*          abs(TOLMUL) should be between 1 and 1/EPS, and preferably */
/*             between 10 (for fast convergence) and .1/EPS */
/*             (for there to be some accuracy in the results). */
/*          Default is to lose at either one eighth or 2 of the */
/*             available decimal digits in each computed singular value */
/*             (whichever is smaller). */

/*  MAXITR  INTEGER, default = 6 */
/*          MAXITR controls the maximum number of passes of the */
/*          algorithm through its inner loop. The algorithms stops */
/*          (and so fails to converge) if the number of passes */
/*          through the inner loop exceeds MAXITR*N**2. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    --d__;
    --e;
    vt_dim1 = *ldvt;
    vt_offset = 1 + vt_dim1;
    vt -= vt_offset;
    u_dim1 = *ldu;
    u_offset = 1 + u_dim1;
    u -= u_offset;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    --work;

    /* Function Body */
    *info = 0;
    lower = lsame_(uplo, "L");
    if (! lsame_(uplo, "U") && ! lower) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*ncvt < 0) {
	*info = -3;
    } else if (*nru < 0) {
	*info = -4;
    } else if (*ncc < 0) {
	*info = -5;
    } else if ((*ncvt == 0 && *ldvt < 1) || (*ncvt > 0 && *ldvt < max(1,*n))) {
	*info = -9;
    } else if (*ldu < max(1,*nru)) {
	*info = -11;
    } else if ((*ncc == 0 && *ldc < 1) || (*ncc > 0 && *ldc < max(1,*n))) {
	*info = -13;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DBDSQR", &i__1);
	return 0;
    }
    if (*n == 0) {
	return 0;
    }
    if (*n == 1) {
	goto L160;
    }

/*     ROTATE is true if any singular vectors desired, false otherwise */

    rotate = *ncvt > 0 || *nru > 0 || *ncc > 0;

/*     If no singular vectors desired, use qd algorithm */

    if (! rotate) {
	dlasq1_(n, &d__[1], &e[1], &work[1], info);
	return 0;
    }

    nm1 = *n - 1;
    nm12 = nm1 + nm1;
    nm13 = nm12 + nm1;
    idir = 0;

/*     Get machine constants */

    eps = dlamch_("Epsilon");
    unfl = dlamch_("Safe minimum");

/*     If matrix lower bidiagonal, rotate to be upper bidiagonal */
/*     by applying Givens rotations on the left */

    if (lower) {
	i__1 = *n - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    dlartg_(&d__[i__], &e[i__], &cs, &sn, &r__);
	    d__[i__] = r__;
	    e[i__] = sn * d__[i__ + 1];
	    d__[i__ + 1] = cs * d__[i__ + 1];
	    work[i__] = cs;
	    work[nm1 + i__] = sn;
/* L10: */
	}

/*        Update singular vectors if desired */

	if (*nru > 0) {
	    dlasr_("R", "V", "F", nru, n, &work[1], &work[*n], &u[u_offset],
		    ldu);
	}
	if (*ncc > 0) {
	    dlasr_("L", "V", "F", n, ncc, &work[1], &work[*n], &c__[c_offset],
		     ldc);
	}
    }

/*     Compute singular values to relative accuracy TOL */
/*     (By setting TOL to be negative, algorithm will compute */
/*     singular values to absolute accuracy ABS(TOL)*norm(input matrix)) */

/* Computing MAX */
/* Computing MIN */
    d__3 = 100., d__4 = pow_dd(&eps, &c_b15);
    d__1 = 10., d__2 = min(d__3,d__4);
    tolmul = max(d__1,d__2);
    tol = tolmul * eps;

/*     Compute approximate maximum, minimum singular values */

    smax = 0.;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MAX */
	d__2 = smax, d__3 = (d__1 = d__[i__], abs(d__1));
	smax = max(d__2,d__3);
/* L20: */
    }
    i__1 = *n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MAX */
	d__2 = smax, d__3 = (d__1 = e[i__], abs(d__1));
	smax = max(d__2,d__3);
/* L30: */
    }
    sminl = 0.;
    if (tol >= 0.) {

/*        Relative accuracy desired */

	sminoa = abs(d__[1]);
	if (sminoa == 0.) {
	    goto L50;
	}
	mu = sminoa;
	i__1 = *n;
	for (i__ = 2; i__ <= i__1; ++i__) {
	    mu = (d__2 = d__[i__], abs(d__2)) * (mu / (mu + (d__1 = e[i__ - 1]
		    , abs(d__1))));
	    sminoa = min(sminoa,mu);
	    if (sminoa == 0.) {
		goto L50;
	    }
/* L40: */
	}
L50:
	sminoa /= sqrt((doublereal) (*n));
/* Computing MAX */
	d__1 = tol * sminoa, d__2 = *n * 6 * *n * unfl;
	thresh = max(d__1,d__2);
    } else {

/*        Absolute accuracy desired */

/* Computing MAX */
	d__1 = abs(tol) * smax, d__2 = *n * 6 * *n * unfl;
	thresh = max(d__1,d__2);
    }

/*     Prepare for main iteration loop for the singular values */
/*     (MAXIT is the maximum number of passes through the inner */
/*     loop permitted before nonconvergence signalled.) */

    maxit = *n * 6 * *n;
    iter = 0;
    oldll = -1;
    oldm = -1;

/*     M points to last element of unconverged part of matrix */

    m = *n;

/*     Begin main iteration loop */

L60:

/*     Check for convergence or exceeding iteration count */

    if (m <= 1) {
	goto L160;
    }
    if (iter > maxit) {
	goto L200;
    }

/*     Find diagonal block of matrix to work on */

    if (tol < 0. && (d__1 = d__[m], abs(d__1)) <= thresh) {
	d__[m] = 0.;
    }
    smax = (d__1 = d__[m], abs(d__1));
    smin = smax;
    i__1 = m - 1;
    for (lll = 1; lll <= i__1; ++lll) {
	ll = m - lll;
	abss = (d__1 = d__[ll], abs(d__1));
	abse = (d__1 = e[ll], abs(d__1));
	if (tol < 0. && abss <= thresh) {
	    d__[ll] = 0.;
	}
	if (abse <= thresh) {
	    goto L80;
	}
	smin = min(smin,abss);
/* Computing MAX */
	d__1 = max(smax,abss);
	smax = max(d__1,abse);
/* L70: */
    }
    ll = 0;
    goto L90;
L80:
    e[ll] = 0.;

/*     Matrix splits since E(LL) = 0 */

    if (ll == m - 1) {

/*        Convergence of bottom singular value, return to top of loop */

	--m;
	goto L60;
    }
L90:
    ++ll;

/*     E(LL) through E(M-1) are nonzero, E(LL-1) is zero */

    if (ll == m - 1) {

/*        2 by 2 block, handle separately */

	dlasv2_(&d__[m - 1], &e[m - 1], &d__[m], &sigmn, &sigmx, &sinr, &cosr,
		 &sinl, &cosl);
	d__[m - 1] = sigmx;
	e[m - 1] = 0.;
	d__[m] = sigmn;

/*        Compute singular vectors, if desired */

	if (*ncvt > 0) {
	    drot_(ncvt, &vt[m - 1 + vt_dim1], ldvt, &vt[m + vt_dim1], ldvt, &
		    cosr, &sinr);
	}
	if (*nru > 0) {
	    drot_(nru, &u[(m - 1) * u_dim1 + 1], &c__1, &u[m * u_dim1 + 1], &
		    c__1, &cosl, &sinl);
	}
	if (*ncc > 0) {
	    drot_(ncc, &c__[m - 1 + c_dim1], ldc, &c__[m + c_dim1], ldc, &
		    cosl, &sinl);
	}
	m += -2;
	goto L60;
    }

/*     If working on new submatrix, choose shift direction */
/*     (from larger end diagonal element towards smaller) */

    if (ll > oldm || m < oldll) {
	if ((d__1 = d__[ll], abs(d__1)) >= (d__2 = d__[m], abs(d__2))) {

/*           Chase bulge from top (big end) to bottom (small end) */

	    idir = 1;
	} else {

/*           Chase bulge from bottom (big end) to top (small end) */

	    idir = 2;
	}
    }

/*     Apply convergence tests */

    if (idir == 1) {

/*        Run convergence test in forward direction */
/*        First apply standard test to bottom of matrix */

	if ((d__2 = e[m - 1], abs(d__2)) <= abs(tol) * (d__1 = d__[m], abs(
		d__1)) || (tol < 0. && (d__3 = e[m - 1], abs(d__3)) <= thresh))
		{
	    e[m - 1] = 0.;
	    goto L60;
	}

	if (tol >= 0.) {

/*           If relative accuracy desired, */
/*           apply convergence criterion forward */

	    mu = (d__1 = d__[ll], abs(d__1));
	    sminl = mu;
	    i__1 = m - 1;
	    for (lll = ll; lll <= i__1; ++lll) {
		if ((d__1 = e[lll], abs(d__1)) <= tol * mu) {
		    e[lll] = 0.;
		    goto L60;
		}
		mu = (d__2 = d__[lll + 1], abs(d__2)) * (mu / (mu + (d__1 = e[
			lll], abs(d__1))));
		sminl = min(sminl,mu);
/* L100: */
	    }
	}

    } else {

/*        Run convergence test in backward direction */
/*        First apply standard test to top of matrix */

	if ((d__2 = e[ll], abs(d__2)) <= abs(tol) * (d__1 = d__[ll], abs(d__1)
		) || (tol < 0. && (d__3 = e[ll], abs(d__3)) <= thresh)) {
	    e[ll] = 0.;
	    goto L60;
	}

	if (tol >= 0.) {

/*           If relative accuracy desired, */
/*           apply convergence criterion backward */

	    mu = (d__1 = d__[m], abs(d__1));
	    sminl = mu;
	    i__1 = ll;
	    for (lll = m - 1; lll >= i__1; --lll) {
		if ((d__1 = e[lll], abs(d__1)) <= tol * mu) {
		    e[lll] = 0.;
		    goto L60;
		}
		mu = (d__2 = d__[lll], abs(d__2)) * (mu / (mu + (d__1 = e[lll]
			, abs(d__1))));
		sminl = min(sminl,mu);
/* L110: */
	    }
	}
    }
    oldll = ll;
    oldm = m;

/*     Compute shift.  First, test if shifting would ruin relative */
/*     accuracy, and if so set the shift to zero. */

/* Computing MAX */
    d__1 = eps, d__2 = tol * .01;
    if (tol >= 0. && *n * tol * (sminl / smax) <= max(d__1,d__2)) {

/*        Use a zero shift to avoid loss of relative accuracy */

	shift = 0.;
    } else {

/*        Compute the shift from 2-by-2 block at end of matrix */

	if (idir == 1) {
	    sll = (d__1 = d__[ll], abs(d__1));
	    dlas2_(&d__[m - 1], &e[m - 1], &d__[m], &shift, &r__);
	} else {
	    sll = (d__1 = d__[m], abs(d__1));
	    dlas2_(&d__[ll], &e[ll], &d__[ll + 1], &shift, &r__);
	}

/*        Test if shift negligible, and if so set to zero */

	if (sll > 0.) {
/* Computing 2nd power */
	    d__1 = shift / sll;
	    if (d__1 * d__1 < eps) {
		shift = 0.;
	    }
	}
    }

/*     Increment iteration count */

    iter = iter + m - ll;

/*     If SHIFT = 0, do simplified QR iteration */

    if (shift == 0.) {
	if (idir == 1) {

/*           Chase bulge from top to bottom */
/*           Save cosines and sines for later singular vector updates */

	    cs = 1.;
	    oldcs = 1.;
	    i__1 = m - 1;
	    for (i__ = ll; i__ <= i__1; ++i__) {
		d__1 = d__[i__] * cs;
		dlartg_(&d__1, &e[i__], &cs, &sn, &r__);
		if (i__ > ll) {
		    e[i__ - 1] = oldsn * r__;
		}
		d__1 = oldcs * r__;
		d__2 = d__[i__ + 1] * sn;
		dlartg_(&d__1, &d__2, &oldcs, &oldsn, &d__[i__]);
		work[i__ - ll + 1] = cs;
		work[i__ - ll + 1 + nm1] = sn;
		work[i__ - ll + 1 + nm12] = oldcs;
		work[i__ - ll + 1 + nm13] = oldsn;
/* L120: */
	    }
	    h__ = d__[m] * cs;
	    d__[m] = h__ * oldcs;
	    e[m - 1] = h__ * oldsn;

/*           Update singular vectors */

	    if (*ncvt > 0) {
		i__1 = m - ll + 1;
		dlasr_("L", "V", "F", &i__1, ncvt, &work[1], &work[*n], &vt[
			ll + vt_dim1], ldvt);
	    }
	    if (*nru > 0) {
		i__1 = m - ll + 1;
		dlasr_("R", "V", "F", nru, &i__1, &work[nm12 + 1], &work[nm13
			+ 1], &u[ll * u_dim1 + 1], ldu);
	    }
	    if (*ncc > 0) {
		i__1 = m - ll + 1;
		dlasr_("L", "V", "F", &i__1, ncc, &work[nm12 + 1], &work[nm13
			+ 1], &c__[ll + c_dim1], ldc);
	    }

/*           Test convergence */

	    if ((d__1 = e[m - 1], abs(d__1)) <= thresh) {
		e[m - 1] = 0.;
	    }

	} else {

/*           Chase bulge from bottom to top */
/*           Save cosines and sines for later singular vector updates */

	    cs = 1.;
	    oldcs = 1.;
	    i__1 = ll + 1;
	    for (i__ = m; i__ >= i__1; --i__) {
		d__1 = d__[i__] * cs;
		dlartg_(&d__1, &e[i__ - 1], &cs, &sn, &r__);
		if (i__ < m) {
		    e[i__] = oldsn * r__;
		}
		d__1 = oldcs * r__;
		d__2 = d__[i__ - 1] * sn;
		dlartg_(&d__1, &d__2, &oldcs, &oldsn, &d__[i__]);
		work[i__ - ll] = cs;
		work[i__ - ll + nm1] = -sn;
		work[i__ - ll + nm12] = oldcs;
		work[i__ - ll + nm13] = -oldsn;
/* L130: */
	    }
	    h__ = d__[ll] * cs;
	    d__[ll] = h__ * oldcs;
	    e[ll] = h__ * oldsn;

/*           Update singular vectors */

	    if (*ncvt > 0) {
		i__1 = m - ll + 1;
		dlasr_("L", "V", "B", &i__1, ncvt, &work[nm12 + 1], &work[
			nm13 + 1], &vt[ll + vt_dim1], ldvt);
	    }
	    if (*nru > 0) {
		i__1 = m - ll + 1;
		dlasr_("R", "V", "B", nru, &i__1, &work[1], &work[*n], &u[ll *
			 u_dim1 + 1], ldu);
	    }
	    if (*ncc > 0) {
		i__1 = m - ll + 1;
		dlasr_("L", "V", "B", &i__1, ncc, &work[1], &work[*n], &c__[
			ll + c_dim1], ldc);
	    }

/*           Test convergence */

	    if ((d__1 = e[ll], abs(d__1)) <= thresh) {
		e[ll] = 0.;
	    }
	}
    } else {

/*        Use nonzero shift */

	if (idir == 1) {

/*           Chase bulge from top to bottom */
/*           Save cosines and sines for later singular vector updates */

	    f = ((d__1 = d__[ll], abs(d__1)) - shift) * (d_sign(&c_b49, &d__[
		    ll]) + shift / d__[ll]);
	    g = e[ll];
	    i__1 = m - 1;
	    for (i__ = ll; i__ <= i__1; ++i__) {
		dlartg_(&f, &g, &cosr, &sinr, &r__);
		if (i__ > ll) {
		    e[i__ - 1] = r__;
		}
		f = cosr * d__[i__] + sinr * e[i__];
		e[i__] = cosr * e[i__] - sinr * d__[i__];
		g = sinr * d__[i__ + 1];
		d__[i__ + 1] = cosr * d__[i__ + 1];
		dlartg_(&f, &g, &cosl, &sinl, &r__);
		d__[i__] = r__;
		f = cosl * e[i__] + sinl * d__[i__ + 1];
		d__[i__ + 1] = cosl * d__[i__ + 1] - sinl * e[i__];
		if (i__ < m - 1) {
		    g = sinl * e[i__ + 1];
		    e[i__ + 1] = cosl * e[i__ + 1];
		}
		work[i__ - ll + 1] = cosr;
		work[i__ - ll + 1 + nm1] = sinr;
		work[i__ - ll + 1 + nm12] = cosl;
		work[i__ - ll + 1 + nm13] = sinl;
/* L140: */
	    }
	    e[m - 1] = f;

/*           Update singular vectors */

	    if (*ncvt > 0) {
		i__1 = m - ll + 1;
		dlasr_("L", "V", "F", &i__1, ncvt, &work[1], &work[*n], &vt[
			ll + vt_dim1], ldvt);
	    }
	    if (*nru > 0) {
		i__1 = m - ll + 1;
		dlasr_("R", "V", "F", nru, &i__1, &work[nm12 + 1], &work[nm13
			+ 1], &u[ll * u_dim1 + 1], ldu);
	    }
	    if (*ncc > 0) {
		i__1 = m - ll + 1;
		dlasr_("L", "V", "F", &i__1, ncc, &work[nm12 + 1], &work[nm13
			+ 1], &c__[ll + c_dim1], ldc);
	    }

/*           Test convergence */

	    if ((d__1 = e[m - 1], abs(d__1)) <= thresh) {
		e[m - 1] = 0.;
	    }

	} else {

/*           Chase bulge from bottom to top */
/*           Save cosines and sines for later singular vector updates */

	    f = ((d__1 = d__[m], abs(d__1)) - shift) * (d_sign(&c_b49, &d__[m]
		    ) + shift / d__[m]);
	    g = e[m - 1];
	    i__1 = ll + 1;
	    for (i__ = m; i__ >= i__1; --i__) {
		dlartg_(&f, &g, &cosr, &sinr, &r__);
		if (i__ < m) {
		    e[i__] = r__;
		}
		f = cosr * d__[i__] + sinr * e[i__ - 1];
		e[i__ - 1] = cosr * e[i__ - 1] - sinr * d__[i__];
		g = sinr * d__[i__ - 1];
		d__[i__ - 1] = cosr * d__[i__ - 1];
		dlartg_(&f, &g, &cosl, &sinl, &r__);
		d__[i__] = r__;
		f = cosl * e[i__ - 1] + sinl * d__[i__ - 1];
		d__[i__ - 1] = cosl * d__[i__ - 1] - sinl * e[i__ - 1];
		if (i__ > ll + 1) {
		    g = sinl * e[i__ - 2];
		    e[i__ - 2] = cosl * e[i__ - 2];
		}
		work[i__ - ll] = cosr;
		work[i__ - ll + nm1] = -sinr;
		work[i__ - ll + nm12] = cosl;
		work[i__ - ll + nm13] = -sinl;
/* L150: */
	    }
	    e[ll] = f;

/*           Test convergence */

	    if ((d__1 = e[ll], abs(d__1)) <= thresh) {
		e[ll] = 0.;
	    }

/*           Update singular vectors if desired */

	    if (*ncvt > 0) {
		i__1 = m - ll + 1;
		dlasr_("L", "V", "B", &i__1, ncvt, &work[nm12 + 1], &work[
			nm13 + 1], &vt[ll + vt_dim1], ldvt);
	    }
	    if (*nru > 0) {
		i__1 = m - ll + 1;
		dlasr_("R", "V", "B", nru, &i__1, &work[1], &work[*n], &u[ll *
			 u_dim1 + 1], ldu);
	    }
	    if (*ncc > 0) {
		i__1 = m - ll + 1;
		dlasr_("L", "V", "B", &i__1, ncc, &work[1], &work[*n], &c__[
			ll + c_dim1], ldc);
	    }
	}
    }

/*     QR iteration finished, go back and check convergence */

    goto L60;

/*     All singular values converged, so make them positive */

L160:
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (d__[i__] < 0.) {
	    d__[i__] = -d__[i__];

/*           Change sign of singular vectors, if desired */

	    if (*ncvt > 0) {
		dscal_(ncvt, &c_b72, &vt[i__ + vt_dim1], ldvt);
	    }
	}
/* L170: */
    }

/*     Sort the singular values into decreasing order (insertion sort on */
/*     singular values, but only one transposition per singular vector) */

    i__1 = *n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {

/*        Scan for smallest D(I) */

	isub = 1;
	smin = d__[1];
	i__2 = *n + 1 - i__;
	for (j = 2; j <= i__2; ++j) {
	    if (d__[j] <= smin) {
		isub = j;
		smin = d__[j];
	    }
/* L180: */
	}
	if (isub != *n + 1 - i__) {

/*           Swap singular values and vectors */

	    d__[isub] = d__[*n + 1 - i__];
	    d__[*n + 1 - i__] = smin;
	    if (*ncvt > 0) {
		dswap_(ncvt, &vt[isub + vt_dim1], ldvt, &vt[*n + 1 - i__ +
			vt_dim1], ldvt);
	    }
	    if (*nru > 0) {
		dswap_(nru, &u[isub * u_dim1 + 1], &c__1, &u[(*n + 1 - i__) *
			u_dim1 + 1], &c__1);
	    }
	    if (*ncc > 0) {
		dswap_(ncc, &c__[isub + c_dim1], ldc, &c__[*n + 1 - i__ +
			c_dim1], ldc);
	    }
	}
/* L190: */
    }
    goto L220;

/*     Maximum number of iterations exceeded, failure to converge */

L200:
    *info = 0;
    i__1 = *n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (e[i__] != 0.) {
	    ++(*info);
	}
/* L210: */
    }
L220:
    return 0;

/*     End of DBDSQR */

} /* dbdsqr_ */

/* Subroutine */ int dgebd2_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *d__, doublereal *e, doublereal *tauq, doublereal *
	taup, doublereal *work, integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;

    /* Local variables */
    integer i__;
    extern /* Subroutine */ int dlarf_(char *, integer *, integer *,
	    doublereal *, integer *, doublereal *, doublereal *, integer *,
	    doublereal *), dlarfg_(integer *, doublereal *,
	    doublereal *, integer *, doublereal *), xerbla_(char *, integer *);


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGEBD2 reduces a real general m by n matrix A to upper or lower */
/*  bidiagonal form B by an orthogonal transformation: Q' * A * P = B. */

/*  If m >= n, B is upper bidiagonal; if m < n, B is lower bidiagonal. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows in the matrix A.  M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns in the matrix A.  N >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the m by n general matrix to be reduced. */
/*          On exit, */
/*          if m >= n, the diagonal and the first superdiagonal are */
/*            overwritten with the upper bidiagonal matrix B; the */
/*            elements below the diagonal, with the array TAUQ, represent */
/*            the orthogonal matrix Q as a product of elementary */
/*            reflectors, and the elements above the first superdiagonal, */
/*            with the array TAUP, represent the orthogonal matrix P as */
/*            a product of elementary reflectors; */
/*          if m < n, the diagonal and the first subdiagonal are */
/*            overwritten with the lower bidiagonal matrix B; the */
/*            elements below the first subdiagonal, with the array TAUQ, */
/*            represent the orthogonal matrix Q as a product of */
/*            elementary reflectors, and the elements above the diagonal, */
/*            with the array TAUP, represent the orthogonal matrix P as */
/*            a product of elementary reflectors. */
/*          See Further Details. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,M). */

/*  D       (output) DOUBLE PRECISION array, dimension (min(M,N)) */
/*          The diagonal elements of the bidiagonal matrix B: */
/*          D(i) = A(i,i). */

/*  E       (output) DOUBLE PRECISION array, dimension (min(M,N)-1) */
/*          The off-diagonal elements of the bidiagonal matrix B: */
/*          if m >= n, E(i) = A(i,i+1) for i = 1,2,...,n-1; */
/*          if m < n, E(i) = A(i+1,i) for i = 1,2,...,m-1. */

/*  TAUQ    (output) DOUBLE PRECISION array dimension (min(M,N)) */
/*          The scalar factors of the elementary reflectors which */
/*          represent the orthogonal matrix Q. See Further Details. */

/*  TAUP    (output) DOUBLE PRECISION array, dimension (min(M,N)) */
/*          The scalar factors of the elementary reflectors which */
/*          represent the orthogonal matrix P. See Further Details. */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (max(M,N)) */

/*  INFO    (output) INTEGER */
/*          = 0: successful exit. */
/*          < 0: if INFO = -i, the i-th argument had an illegal value. */

/*  Further Details */
/*  =============== */

/*  The matrices Q and P are represented as products of elementary */
/*  reflectors: */

/*  If m >= n, */

/*     Q = H(1) H(2) . . . H(n)  and  P = G(1) G(2) . . . G(n-1) */

/*  Each H(i) and G(i) has the form: */

/*     H(i) = I - tauq * v * v'  and G(i) = I - taup * u * u' */

/*  where tauq and taup are real scalars, and v and u are real vectors; */
/*  v(1:i-1) = 0, v(i) = 1, and v(i+1:m) is stored on exit in A(i+1:m,i); */
/*  u(1:i) = 0, u(i+1) = 1, and u(i+2:n) is stored on exit in A(i,i+2:n); */
/*  tauq is stored in TAUQ(i) and taup in TAUP(i). */

/*  If m < n, */

/*     Q = H(1) H(2) . . . H(m-1)  and  P = G(1) G(2) . . . G(m) */

/*  Each H(i) and G(i) has the form: */

/*     H(i) = I - tauq * v * v'  and G(i) = I - taup * u * u' */

/*  where tauq and taup are real scalars, and v and u are real vectors; */
/*  v(1:i) = 0, v(i+1) = 1, and v(i+2:m) is stored on exit in A(i+2:m,i); */
/*  u(1:i-1) = 0, u(i) = 1, and u(i+1:n) is stored on exit in A(i,i+1:n); */
/*  tauq is stored in TAUQ(i) and taup in TAUP(i). */

/*  The contents of A on exit are illustrated by the following examples: */

/*  m = 6 and n = 5 (m > n):          m = 5 and n = 6 (m < n): */

/*    (  d   e   u1  u1  u1 )           (  d   u1  u1  u1  u1  u1 ) */
/*    (  v1  d   e   u2  u2 )           (  e   d   u2  u2  u2  u2 ) */
/*    (  v1  v2  d   e   u3 )           (  v1  e   d   u3  u3  u3 ) */
/*    (  v1  v2  v3  d   e  )           (  v1  v2  e   d   u4  u4 ) */
/*    (  v1  v2  v3  v4  d  )           (  v1  v2  v3  e   d   u5 ) */
/*    (  v1  v2  v3  v4  v5 ) */

/*  where d and e denote diagonal and off-diagonal elements of B, vi */
/*  denotes an element of the vector defining H(i), and ui an element of */
/*  the vector defining G(i). */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input parameters */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --d__;
    --e;
    --tauq;
    --taup;
    --work;

    /* Function Body */
    *info = 0;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*m)) {
	*info = -4;
    }
    if (*info < 0) {
	i__1 = -(*info);
	xerbla_("DGEBD2", &i__1);
	return 0;
    }

    if (*m >= *n) {

/*        Reduce to upper bidiagonal form */

	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {

/*           Generate elementary reflector H(i) to annihilate A(i+1:m,i) */

	    i__2 = *m - i__ + 1;
/* Computing MIN */
	    i__3 = i__ + 1;
	    dlarfg_(&i__2, &a[i__ + i__ * a_dim1], &a[min(i__3, *m)+ i__ *
		    a_dim1], &c__1, &tauq[i__]);
	    d__[i__] = a[i__ + i__ * a_dim1];
	    a[i__ + i__ * a_dim1] = 1.;

/*           Apply H(i) to A(i:m,i+1:n) from the left */

	    if (i__ < *n) {
		i__2 = *m - i__ + 1;
		i__3 = *n - i__;
		dlarf_("Left", &i__2, &i__3, &a[i__ + i__ * a_dim1], &c__1, &
			tauq[i__], &a[i__ + (i__ + 1) * a_dim1], lda, &work[1]
);
	    }
	    a[i__ + i__ * a_dim1] = d__[i__];

	    if (i__ < *n) {

/*              Generate elementary reflector G(i) to annihilate */
/*              A(i,i+2:n) */

		i__2 = *n - i__;
/* Computing MIN */
		i__3 = i__ + 2;
		dlarfg_(&i__2, &a[i__ + (i__ + 1) * a_dim1], &a[i__ + min(
			i__3, *n)* a_dim1], lda, &taup[i__]);
		e[i__] = a[i__ + (i__ + 1) * a_dim1];
		a[i__ + (i__ + 1) * a_dim1] = 1.;

/*              Apply G(i) to A(i+1:m,i+1:n) from the right */

		i__2 = *m - i__;
		i__3 = *n - i__;
		dlarf_("Right", &i__2, &i__3, &a[i__ + (i__ + 1) * a_dim1],
			lda, &taup[i__], &a[i__ + 1 + (i__ + 1) * a_dim1],
			lda, &work[1]);
		a[i__ + (i__ + 1) * a_dim1] = e[i__];
	    } else {
		taup[i__] = 0.;
	    }
/* L10: */
	}
    } else {

/*        Reduce to lower bidiagonal form */

	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {

/*           Generate elementary reflector G(i) to annihilate A(i,i+1:n) */

	    i__2 = *n - i__ + 1;
/* Computing MIN */
	    i__3 = i__ + 1;
	    dlarfg_(&i__2, &a[i__ + i__ * a_dim1], &a[i__ + min(i__3, *n)*
		    a_dim1], lda, &taup[i__]);
	    d__[i__] = a[i__ + i__ * a_dim1];
	    a[i__ + i__ * a_dim1] = 1.;

/*           Apply G(i) to A(i+1:m,i:n) from the right */

	    if (i__ < *m) {
		i__2 = *m - i__;
		i__3 = *n - i__ + 1;
		dlarf_("Right", &i__2, &i__3, &a[i__ + i__ * a_dim1], lda, &
			taup[i__], &a[i__ + 1 + i__ * a_dim1], lda, &work[1]);
	    }
	    a[i__ + i__ * a_dim1] = d__[i__];

	    if (i__ < *m) {

/*              Generate elementary reflector H(i) to annihilate */
/*              A(i+2:m,i) */

		i__2 = *m - i__;
/* Computing MIN */
		i__3 = i__ + 2;
		dlarfg_(&i__2, &a[i__ + 1 + i__ * a_dim1], &a[min(i__3, *m)+
			i__ * a_dim1], &c__1, &tauq[i__]);
		e[i__] = a[i__ + 1 + i__ * a_dim1];
		a[i__ + 1 + i__ * a_dim1] = 1.;

/*              Apply H(i) to A(i+1:m,i+1:n) from the left */

		i__2 = *m - i__;
		i__3 = *n - i__;
		dlarf_("Left", &i__2, &i__3, &a[i__ + 1 + i__ * a_dim1], &
			c__1, &tauq[i__], &a[i__ + 1 + (i__ + 1) * a_dim1],
			lda, &work[1]);
		a[i__ + 1 + i__ * a_dim1] = e[i__];
	    } else {
		tauq[i__] = 0.;
	    }
/* L20: */
	}
    }
    return 0;

/*     End of DGEBD2 */

} /* dgebd2_ */

/* Subroutine */ int dgebrd_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *d__, doublereal *e, doublereal *tauq, doublereal *
	taup, doublereal *work, integer *lwork, integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;
    integer c_n1 = -1;
    integer c__3 = 3;
    integer c__2 = 2;
    doublereal c_b21 = -1.;
    doublereal c_b22 = 1.;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4;

    /* Local variables */
    integer i__, j, nb, nx;
    doublereal ws;
    extern /* Subroutine */ int dgemm_(char *, char *, integer *, integer *,
	    integer *, doublereal *, doublereal *, integer *, doublereal *,
	    integer *, doublereal *, doublereal *, integer *);
    integer nbmin, iinfo, minmn;
    extern /* Subroutine */ int dgebd2_(integer *, integer *, doublereal *,
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, integer *), dlabrd_(integer *, integer *, integer *
, doublereal *, integer *, doublereal *, doublereal *, doublereal
	    *, doublereal *, doublereal *, integer *, doublereal *, integer *)
	    , xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *,
	    integer *, integer *);
    integer ldwrkx, ldwrky, lwkopt;
    logical lquery;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGEBRD reduces a general real M-by-N matrix A to upper or lower */
/*  bidiagonal form B by an orthogonal transformation: Q**T * A * P = B. */

/*  If m >= n, B is upper bidiagonal; if m < n, B is lower bidiagonal. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows in the matrix A.  M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns in the matrix A.  N >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the M-by-N general matrix to be reduced. */
/*          On exit, */
/*          if m >= n, the diagonal and the first superdiagonal are */
/*            overwritten with the upper bidiagonal matrix B; the */
/*            elements below the diagonal, with the array TAUQ, represent */
/*            the orthogonal matrix Q as a product of elementary */
/*            reflectors, and the elements above the first superdiagonal, */
/*            with the array TAUP, represent the orthogonal matrix P as */
/*            a product of elementary reflectors; */
/*          if m < n, the diagonal and the first subdiagonal are */
/*            overwritten with the lower bidiagonal matrix B; the */
/*            elements below the first subdiagonal, with the array TAUQ, */
/*            represent the orthogonal matrix Q as a product of */
/*            elementary reflectors, and the elements above the diagonal, */
/*            with the array TAUP, represent the orthogonal matrix P as */
/*            a product of elementary reflectors. */
/*          See Further Details. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,M). */

/*  D       (output) DOUBLE PRECISION array, dimension (min(M,N)) */
/*          The diagonal elements of the bidiagonal matrix B: */
/*          D(i) = A(i,i). */

/*  E       (output) DOUBLE PRECISION array, dimension (min(M,N)-1) */
/*          The off-diagonal elements of the bidiagonal matrix B: */
/*          if m >= n, E(i) = A(i,i+1) for i = 1,2,...,n-1; */
/*          if m < n, E(i) = A(i+1,i) for i = 1,2,...,m-1. */

/*  TAUQ    (output) DOUBLE PRECISION array dimension (min(M,N)) */
/*          The scalar factors of the elementary reflectors which */
/*          represent the orthogonal matrix Q. See Further Details. */

/*  TAUP    (output) DOUBLE PRECISION array, dimension (min(M,N)) */
/*          The scalar factors of the elementary reflectors which */
/*          represent the orthogonal matrix P. See Further Details. */

/*  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK)) */
/*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK. */

/*  LWORK   (input) INTEGER */
/*          The length of the array WORK.  LWORK >= max(1,M,N). */
/*          For optimum performance LWORK >= (M+N)*NB, where NB */
/*          is the optimal blocksize. */

/*          If LWORK = -1, then a workspace query is assumed; the routine */
/*          only calculates the optimal size of the WORK array, returns */
/*          this value as the first entry of the WORK array, and no error */
/*          message related to LWORK is issued by XERBLA. */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value. */

/*  Further Details */
/*  =============== */

/*  The matrices Q and P are represented as products of elementary */
/*  reflectors: */

/*  If m >= n, */

/*     Q = H(1) H(2) . . . H(n)  and  P = G(1) G(2) . . . G(n-1) */

/*  Each H(i) and G(i) has the form: */

/*     H(i) = I - tauq * v * v'  and G(i) = I - taup * u * u' */

/*  where tauq and taup are real scalars, and v and u are real vectors; */
/*  v(1:i-1) = 0, v(i) = 1, and v(i+1:m) is stored on exit in A(i+1:m,i); */
/*  u(1:i) = 0, u(i+1) = 1, and u(i+2:n) is stored on exit in A(i,i+2:n); */
/*  tauq is stored in TAUQ(i) and taup in TAUP(i). */

/*  If m < n, */

/*     Q = H(1) H(2) . . . H(m-1)  and  P = G(1) G(2) . . . G(m) */

/*  Each H(i) and G(i) has the form: */

/*     H(i) = I - tauq * v * v'  and G(i) = I - taup * u * u' */

/*  where tauq and taup are real scalars, and v and u are real vectors; */
/*  v(1:i) = 0, v(i+1) = 1, and v(i+2:m) is stored on exit in A(i+2:m,i); */
/*  u(1:i-1) = 0, u(i) = 1, and u(i+1:n) is stored on exit in A(i,i+1:n); */
/*  tauq is stored in TAUQ(i) and taup in TAUP(i). */

/*  The contents of A on exit are illustrated by the following examples: */

/*  m = 6 and n = 5 (m > n):          m = 5 and n = 6 (m < n): */

/*    (  d   e   u1  u1  u1 )           (  d   u1  u1  u1  u1  u1 ) */
/*    (  v1  d   e   u2  u2 )           (  e   d   u2  u2  u2  u2 ) */
/*    (  v1  v2  d   e   u3 )           (  v1  e   d   u3  u3  u3 ) */
/*    (  v1  v2  v3  d   e  )           (  v1  v2  e   d   u4  u4 ) */
/*    (  v1  v2  v3  v4  d  )           (  v1  v2  v3  e   d   u5 ) */
/*    (  v1  v2  v3  v4  v5 ) */

/*  where d and e denote diagonal and off-diagonal elements of B, vi */
/*  denotes an element of the vector defining H(i), and ui an element of */
/*  the vector defining G(i). */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input parameters */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --d__;
    --e;
    --tauq;
    --taup;
    --work;

    /* Function Body */
    *info = 0;
/* Computing MAX */
    i__1 = 1, i__2 = ilaenv_(&c__1, "DGEBRD", " ", m, n, &c_n1, &c_n1);
    nb = max(i__1,i__2);
    lwkopt = (*m + *n) * nb;
    work[1] = (doublereal) lwkopt;
    lquery = *lwork == -1;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*m)) {
	*info = -4;
    } else /* if(complicated condition) */ {
/* Computing MAX */
	i__1 = max(1,*m);
	if (*lwork < max(i__1,*n) && ! lquery) {
	    *info = -10;
	}
    }
    if (*info < 0) {
	i__1 = -(*info);
	xerbla_("DGEBRD", &i__1);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible */

    minmn = min(*m,*n);
    if (minmn == 0) {
	work[1] = 1.;
	return 0;
    }

    ws = (doublereal) max(*m,*n);
    ldwrkx = *m;
    ldwrky = *n;

    if (nb > 1 && nb < minmn) {

/*        Set the crossover point NX. */

/* Computing MAX */
	i__1 = nb, i__2 = ilaenv_(&c__3, "DGEBRD", " ", m, n, &c_n1, &c_n1);
	nx = max(i__1,i__2);

/*        Determine when to switch from blocked to unblocked code. */

	if (nx < minmn) {
	    ws = (doublereal) ((*m + *n) * nb);
	    if ((doublereal) (*lwork) < ws) {

/*              Not enough work space for the optimal NB, consider using */
/*              a smaller block size. */

		nbmin = ilaenv_(&c__2, "DGEBRD", " ", m, n, &c_n1, &c_n1);
		if (*lwork >= (*m + *n) * nbmin) {
		    nb = *lwork / (*m + *n);
		} else {
		    nb = 1;
		    nx = minmn;
		}
	    }
	}
    } else {
	nx = minmn;
    }

    i__1 = minmn - nx;
    i__2 = nb;
    for (i__ = 1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {

/*        Reduce rows and columns i:i+nb-1 to bidiagonal form and return */
/*        the matrices X and Y which are needed to update the unreduced */
/*        part of the matrix */

	i__3 = *m - i__ + 1;
	i__4 = *n - i__ + 1;
	dlabrd_(&i__3, &i__4, &nb, &a[i__ + i__ * a_dim1], lda, &d__[i__], &e[
		i__], &tauq[i__], &taup[i__], &work[1], &ldwrkx, &work[ldwrkx
		* nb + 1], &ldwrky);

/*        Update the trailing submatrix A(i+nb:m,i+nb:n), using an update */
/*        of the form  A := A - V*Y' - X*U' */

	i__3 = *m - i__ - nb + 1;
	i__4 = *n - i__ - nb + 1;
	dgemm_("No transpose", "Transpose", &i__3, &i__4, &nb, &c_b21, &a[i__
		+ nb + i__ * a_dim1], lda, &work[ldwrkx * nb + nb + 1], &
		ldwrky, &c_b22, &a[i__ + nb + (i__ + nb) * a_dim1], lda);
	i__3 = *m - i__ - nb + 1;
	i__4 = *n - i__ - nb + 1;
	dgemm_("No transpose", "No transpose", &i__3, &i__4, &nb, &c_b21, &
		work[nb + 1], &ldwrkx, &a[i__ + (i__ + nb) * a_dim1], lda, &
		c_b22, &a[i__ + nb + (i__ + nb) * a_dim1], lda);

/*        Copy diagonal and off-diagonal elements of B back into A */

	if (*m >= *n) {
	    i__3 = i__ + nb - 1;
	    for (j = i__; j <= i__3; ++j) {
		a[j + j * a_dim1] = d__[j];
		a[j + (j + 1) * a_dim1] = e[j];
/* L10: */
	    }
	} else {
	    i__3 = i__ + nb - 1;
	    for (j = i__; j <= i__3; ++j) {
		a[j + j * a_dim1] = d__[j];
		a[j + 1 + j * a_dim1] = e[j];
/* L20: */
	    }
	}
/* L30: */
    }

/*     Use unblocked code to reduce the remainder of the matrix */

    i__2 = *m - i__ + 1;
    i__1 = *n - i__ + 1;
    dgebd2_(&i__2, &i__1, &a[i__ + i__ * a_dim1], lda, &d__[i__], &e[i__], &
	    tauq[i__], &taup[i__], &work[1], &iinfo);
    work[1] = ws;
    return 0;

/*     End of DGEBRD */

} /* dgebrd_ */

/* Subroutine */ int dgelq2_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *tau, doublereal *work, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;

    /* Local variables */
    integer i__, k;
    doublereal aii;
    extern /* Subroutine */ int dlarf_(char *, integer *, integer *,
	    doublereal *, integer *, doublereal *, doublereal *, integer *,
	    doublereal *), dlarfp_(integer *, doublereal *,
	    doublereal *, integer *, doublereal *), xerbla_(char *, integer *);


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGELQ2 computes an LQ factorization of a real m by n matrix A: */
/*  A = L * Q. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A.  M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A.  N >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the m by n matrix A. */
/*          On exit, the elements on and below the diagonal of the array */
/*          contain the m by min(m,n) lower trapezoidal matrix L (L is */
/*          lower triangular if m <= n); the elements above the diagonal, */
/*          with the array TAU, represent the orthogonal matrix Q as a */
/*          product of elementary reflectors (see Further Details). */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,M). */

/*  TAU     (output) DOUBLE PRECISION array, dimension (min(M,N)) */
/*          The scalar factors of the elementary reflectors (see Further */
/*          Details). */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (M) */

/*  INFO    (output) INTEGER */
/*          = 0: successful exit */
/*          < 0: if INFO = -i, the i-th argument had an illegal value */

/*  Further Details */
/*  =============== */

/*  The matrix Q is represented as a product of elementary reflectors */

/*     Q = H(k) . . . H(2) H(1), where k = min(m,n). */

/*  Each H(i) has the form */

/*     H(i) = I - tau * v * v' */

/*  where tau is a real scalar, and v is a real vector with */
/*  v(1:i-1) = 0 and v(i) = 1; v(i+1:n) is stored on exit in A(i,i+1:n), */
/*  and tau in TAU(i). */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    --work;

    /* Function Body */
    *info = 0;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*m)) {
	*info = -4;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGELQ2", &i__1);
	return 0;
    }

    k = min(*m,*n);

    i__1 = k;
    for (i__ = 1; i__ <= i__1; ++i__) {

/*        Generate elementary reflector H(i) to annihilate A(i,i+1:n) */

	i__2 = *n - i__ + 1;
/* Computing MIN */
	i__3 = i__ + 1;
	dlarfp_(&i__2, &a[i__ + i__ * a_dim1], &a[i__ + min(i__3, *n)* a_dim1]
, lda, &tau[i__]);
	if (i__ < *m) {

/*           Apply H(i) to A(i+1:m,i:n) from the right */

	    aii = a[i__ + i__ * a_dim1];
	    a[i__ + i__ * a_dim1] = 1.;
	    i__2 = *m - i__;
	    i__3 = *n - i__ + 1;
	    dlarf_("Right", &i__2, &i__3, &a[i__ + i__ * a_dim1], lda, &tau[
		    i__], &a[i__ + 1 + i__ * a_dim1], lda, &work[1]);
	    a[i__ + i__ * a_dim1] = aii;
	}
/* L10: */
    }
    return 0;

/*     End of DGELQ2 */

} /* dgelq2_ */

/* Subroutine */ int dgelqf_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *tau, doublereal *work, integer *lwork, integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;
    integer c_n1 = -1;
    integer c__3 = 3;
    integer c__2 = 2;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4;

    /* Local variables */
    integer i__, k, ib, nb, nx, iws, nbmin, iinfo;
    extern /* Subroutine */ int dgelq2_(integer *, integer *, doublereal *,
	    integer *, doublereal *, doublereal *, integer *), dlarfb_(char *,
	     char *, char *, char *, integer *, integer *, integer *,
	    doublereal *, integer *, doublereal *, integer *, doublereal *,
	    integer *, doublereal *, integer *), dlarft_(char *, char *, integer *, integer *, doublereal
	    *, integer *, doublereal *, doublereal *, integer *), xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *,
	    integer *, integer *);
    integer ldwork, lwkopt;
    logical lquery;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGELQF computes an LQ factorization of a real M-by-N matrix A: */
/*  A = L * Q. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A.  M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A.  N >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the M-by-N matrix A. */
/*          On exit, the elements on and below the diagonal of the array */
/*          contain the m-by-min(m,n) lower trapezoidal matrix L (L is */
/*          lower triangular if m <= n); the elements above the diagonal, */
/*          with the array TAU, represent the orthogonal matrix Q as a */
/*          product of elementary reflectors (see Further Details). */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,M). */

/*  TAU     (output) DOUBLE PRECISION array, dimension (min(M,N)) */
/*          The scalar factors of the elementary reflectors (see Further */
/*          Details). */

/*  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK)) */
/*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK. */

/*  LWORK   (input) INTEGER */
/*          The dimension of the array WORK.  LWORK >= max(1,M). */
/*          For optimum performance LWORK >= M*NB, where NB is the */
/*          optimal blocksize. */

/*          If LWORK = -1, then a workspace query is assumed; the routine */
/*          only calculates the optimal size of the WORK array, returns */
/*          this value as the first entry of the WORK array, and no error */
/*          message related to LWORK is issued by XERBLA. */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */

/*  Further Details */
/*  =============== */

/*  The matrix Q is represented as a product of elementary reflectors */

/*     Q = H(k) . . . H(2) H(1), where k = min(m,n). */

/*  Each H(i) has the form */

/*     H(i) = I - tau * v * v' */

/*  where tau is a real scalar, and v is a real vector with */
/*  v(1:i-1) = 0 and v(i) = 1; v(i+1:n) is stored on exit in A(i,i+1:n), */
/*  and tau in TAU(i). */

/*  ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    --work;

    /* Function Body */
    *info = 0;
    nb = ilaenv_(&c__1, "DGELQF", " ", m, n, &c_n1, &c_n1);
    lwkopt = *m * nb;
    work[1] = (doublereal) lwkopt;
    lquery = *lwork == -1;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*m)) {
	*info = -4;
    } else if (*lwork < max(1,*m) && ! lquery) {
	*info = -7;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGELQF", &i__1);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible */

    k = min(*m,*n);
    if (k == 0) {
	work[1] = 1.;
	return 0;
    }

    nbmin = 2;
    nx = 0;
    iws = *m;
    if (nb > 1 && nb < k) {

/*        Determine when to cross over from blocked to unblocked code. */

/* Computing MAX */
	i__1 = 0, i__2 = ilaenv_(&c__3, "DGELQF", " ", m, n, &c_n1, &c_n1);
	nx = max(i__1,i__2);
	if (nx < k) {

/*           Determine if workspace is large enough for blocked code. */

	    ldwork = *m;
	    iws = ldwork * nb;
	    if (*lwork < iws) {

/*              Not enough workspace to use optimal NB:  reduce NB and */
/*              determine the minimum value of NB. */

		nb = *lwork / ldwork;
/* Computing MAX */
		i__1 = 2, i__2 = ilaenv_(&c__2, "DGELQF", " ", m, n, &c_n1, &
			c_n1);
		nbmin = max(i__1,i__2);
	    }
	}
    }

    if (nb >= nbmin && nb < k && nx < k) {

/*        Use blocked code initially */

	i__1 = k - nx;
	i__2 = nb;
	for (i__ = 1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {
/* Computing MIN */
	    i__3 = k - i__ + 1;
	    ib = min(i__3,nb);

/*           Compute the LQ factorization of the current block */
/*           A(i:i+ib-1,i:n) */

	    i__3 = *n - i__ + 1;
	    dgelq2_(&ib, &i__3, &a[i__ + i__ * a_dim1], lda, &tau[i__], &work[
		    1], &iinfo);
	    if (i__ + ib <= *m) {

/*              Form the triangular factor of the block reflector */
/*              H = H(i) H(i+1) . . . H(i+ib-1) */

		i__3 = *n - i__ + 1;
		dlarft_("Forward", "Rowwise", &i__3, &ib, &a[i__ + i__ *
			a_dim1], lda, &tau[i__], &work[1], &ldwork);

/*              Apply H to A(i+ib:m,i:n) from the right */

		i__3 = *m - i__ - ib + 1;
		i__4 = *n - i__ + 1;
		dlarfb_("Right", "No transpose", "Forward", "Rowwise", &i__3,
			&i__4, &ib, &a[i__ + i__ * a_dim1], lda, &work[1], &
			ldwork, &a[i__ + ib + i__ * a_dim1], lda, &work[ib +
			1], &ldwork);
	    }
/* L10: */
	}
    } else {
	i__ = 1;
    }

/*     Use unblocked code to factor the last or only block. */

    if (i__ <= k) {
	i__2 = *m - i__ + 1;
	i__1 = *n - i__ + 1;
	dgelq2_(&i__2, &i__1, &a[i__ + i__ * a_dim1], lda, &tau[i__], &work[1]
, &iinfo);
    }

    work[1] = (doublereal) iws;
    return 0;

/*     End of DGELQF */

} /* dgelqf_ */

/* Subroutine */ int dgelsy_(integer *m, integer *n, integer *nrhs,
	doublereal *a, integer *lda, doublereal *b, integer *ldb, integer *
	jpvt, doublereal *rcond, integer *rank, doublereal *work, integer *
	lwork, integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;
    integer c_n1 = -1;
    integer c__0 = 0;
    doublereal c_b31 = 0.;
    integer c__2 = 2;
    doublereal c_b54 = 1.;

    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, i__1, i__2;
    doublereal d__1, d__2;

    /* Local variables */
    integer i__, j;
    doublereal c1, c2, s1, s2;
    integer nb, mn, nb1, nb2, nb3, nb4;
    doublereal anrm, bnrm, smin, smax;
    integer iascl, ibscl;
    extern /* Subroutine */ int dcopy_(integer *, doublereal *, integer *,
	    doublereal *, integer *);
    integer ismin, ismax;
    extern /* Subroutine */ int dtrsm_(char *, char *, char *, char *,
	    integer *, integer *, doublereal *, doublereal *, integer *,
	    doublereal *, integer *), dlaic1_(
	    integer *, integer *, doublereal *, doublereal *, doublereal *,
	    doublereal *, doublereal *, doublereal *, doublereal *);
    doublereal wsize;
    extern /* Subroutine */ int dgeqp3_(integer *, integer *, doublereal *,
	    integer *, integer *, doublereal *, doublereal *, integer *,
	    integer *), dlabad_(doublereal *, doublereal *);
    extern doublereal dlamch_(char *), dlange_(char *, integer *,
	    integer *, doublereal *, integer *, doublereal *);
    extern /* Subroutine */ int dlascl_(char *, integer *, integer *,
	    doublereal *, doublereal *, integer *, integer *, doublereal *,
	    integer *, integer *), dlaset_(char *, integer *, integer
	    *, doublereal *, doublereal *, doublereal *, integer *),
	    xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *,
	    integer *, integer *);
    doublereal bignum;
    integer lwkmin;
    extern /* Subroutine */ int dormqr_(char *, char *, integer *, integer *,
	    integer *, doublereal *, integer *, doublereal *, doublereal *,
	    integer *, doublereal *, integer *, integer *);
    doublereal sminpr, smaxpr, smlnum;
    extern /* Subroutine */ int dormrz_(char *, char *, integer *, integer *,
	    integer *, integer *, doublereal *, integer *, doublereal *,
	    doublereal *, integer *, doublereal *, integer *, integer *);
    integer lwkopt;
    logical lquery;
    extern /* Subroutine */ int dtzrzf_(integer *, integer *, doublereal *,
	    integer *, doublereal *, doublereal *, integer *, integer *);


/*  -- LAPACK driver routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGELSY computes the minimum-norm solution to a real linear least */
/*  squares problem: */
/*      minimize || A * X - B || */
/*  using a complete orthogonal factorization of A.  A is an M-by-N */
/*  matrix which may be rank-deficient. */

/*  Several right hand side vectors b and solution vectors x can be */
/*  handled in a single call; they are stored as the columns of the */
/*  M-by-NRHS right hand side matrix B and the N-by-NRHS solution */
/*  matrix X. */

/*  The routine first computes a QR factorization with column pivoting: */
/*      A * P = Q * [ R11 R12 ] */
/*                  [  0  R22 ] */
/*  with R11 defined as the largest leading submatrix whose estimated */
/*  condition number is less than 1/RCOND.  The order of R11, RANK, */
/*  is the effective rank of A. */

/*  Then, R22 is considered to be negligible, and R12 is annihilated */
/*  by orthogonal transformations from the right, arriving at the */
/*  complete orthogonal factorization: */
/*     A * P = Q * [ T11 0 ] * Z */
/*                 [  0  0 ] */
/*  The minimum-norm solution is then */
/*     X = P * Z' [ inv(T11)*Q1'*B ] */
/*                [        0       ] */
/*  where Q1 consists of the first RANK columns of Q. */

/*  This routine is basically identical to the original xGELSX except */
/*  three differences: */
/*    o The call to the subroutine xGEQPF has been substituted by the */
/*      the call to the subroutine xGEQP3. This subroutine is a Blas-3 */
/*      version of the QR factorization with column pivoting. */
/*    o Matrix B (the right hand side) is updated with Blas-3. */
/*    o The permutation of matrix B (the right hand side) is faster and */
/*      more simple. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A.  M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A.  N >= 0. */

/*  NRHS    (input) INTEGER */
/*          The number of right hand sides, i.e., the number of */
/*          columns of matrices B and X. NRHS >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the M-by-N matrix A. */
/*          On exit, A has been overwritten by details of its */
/*          complete orthogonal factorization. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,M). */

/*  B       (input/output) DOUBLE PRECISION array, dimension (LDB,NRHS) */
/*          On entry, the M-by-NRHS right hand side matrix B. */
/*          On exit, the N-by-NRHS solution matrix X. */

/*  LDB     (input) INTEGER */
/*          The leading dimension of the array B. LDB >= max(1,M,N). */

/*  JPVT    (input/output) INTEGER array, dimension (N) */
/*          On entry, if JPVT(i) .ne. 0, the i-th column of A is permuted */
/*          to the front of AP, otherwise column i is a free column. */
/*          On exit, if JPVT(i) = k, then the i-th column of AP */
/*          was the k-th column of A. */

/*  RCOND   (input) DOUBLE PRECISION */
/*          RCOND is used to determine the effective rank of A, which */
/*          is defined as the order of the largest leading triangular */
/*          submatrix R11 in the QR factorization with pivoting of A, */
/*          whose estimated condition number < 1/RCOND. */

/*  RANK    (output) INTEGER */
/*          The effective rank of A, i.e., the order of the submatrix */
/*          R11.  This is the same as the order of the submatrix T11 */
/*          in the complete orthogonal factorization of A. */

/*  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK)) */
/*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK. */

/*  LWORK   (input) INTEGER */
/*          The dimension of the array WORK. */
/*          The unblocked strategy requires that: */
/*             LWORK >= MAX( MN+3*N+1, 2*MN+NRHS ), */
/*          where MN = min( M, N ). */
/*          The block algorithm requires that: */
/*             LWORK >= MAX( MN+2*N+NB*(N+1), 2*MN+NB*NRHS ), */
/*          where NB is an upper bound on the blocksize returned */
/*          by ILAENV for the routines DGEQP3, DTZRZF, STZRQF, DORMQR, */
/*          and DORMRZ. */

/*          If LWORK = -1, then a workspace query is assumed; the routine */
/*          only calculates the optimal size of the WORK array, returns */
/*          this value as the first entry of the WORK array, and no error */
/*          message related to LWORK is issued by XERBLA. */

/*  INFO    (output) INTEGER */
/*          = 0: successful exit */
/*          < 0: If INFO = -i, the i-th argument had an illegal value. */

/*  Further Details */
/*  =============== */

/*  Based on contributions by */
/*    A. Petitet, Computer Science Dept., Univ. of Tenn., Knoxville, USA */
/*    E. Quintana-Orti, Depto. de Informatica, Universidad Jaime I, Spain */
/*    G. Quintana-Orti, Depto. de Informatica, Universidad Jaime I, Spain */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;
    --jpvt;
    --work;

    /* Function Body */
    mn = min(*m,*n);
    ismin = mn + 1;
    ismax = (mn << 1) + 1;

/*     Test the input arguments. */

    *info = 0;
    lquery = *lwork == -1;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*nrhs < 0) {
	*info = -3;
    } else if (*lda < max(1,*m)) {
	*info = -5;
    } else /* if(complicated condition) */ {
/* Computing MAX */
	i__1 = max(1,*m);
	if (*ldb < max(i__1,*n)) {
	    *info = -7;
	}
    }

/*     Figure out optimal block size */

    if (*info == 0) {
	if (mn == 0 || *nrhs == 0) {
	    lwkmin = 1;
	    lwkopt = 1;
	} else {
	    nb1 = ilaenv_(&c__1, "DGEQRF", " ", m, n, &c_n1, &c_n1);
	    nb2 = ilaenv_(&c__1, "DGERQF", " ", m, n, &c_n1, &c_n1);
	    nb3 = ilaenv_(&c__1, "DORMQR", " ", m, n, nrhs, &c_n1);
	    nb4 = ilaenv_(&c__1, "DORMRQ", " ", m, n, nrhs, &c_n1);
/* Computing MAX */
	    i__1 = max(nb1,nb2), i__1 = max(i__1,nb3);
	    nb = max(i__1,nb4);
/* Computing MAX */
	    i__1 = mn << 1, i__2 = *n + 1, i__1 = max(i__1,i__2), i__2 = mn +
		    *nrhs;
	    lwkmin = mn + max(i__1,i__2);
/* Computing MAX */
	    i__1 = lwkmin, i__2 = mn + (*n << 1) + nb * (*n + 1), i__1 = max(
		    i__1,i__2), i__2 = (mn << 1) + nb * *nrhs;
	    lwkopt = max(i__1,i__2);
	}
	work[1] = (doublereal) lwkopt;

	if (*lwork < lwkmin && ! lquery) {
	    *info = -12;
	}
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGELSY", &i__1);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible */

    if (mn == 0 || *nrhs == 0) {
	*rank = 0;
	return 0;
    }

/*     Get machine parameters */

    smlnum = dlamch_("S") / dlamch_("P");
    bignum = 1. / smlnum;
    dlabad_(&smlnum, &bignum);

/*     Scale A, B if max entries outside range [SMLNUM,BIGNUM] */

    anrm = dlange_("M", m, n, &a[a_offset], lda, &work[1]);
    iascl = 0;
    if (anrm > 0. && anrm < smlnum) {

/*        Scale matrix norm up to SMLNUM */

	dlascl_("G", &c__0, &c__0, &anrm, &smlnum, m, n, &a[a_offset], lda,
		info);
	iascl = 1;
    } else if (anrm > bignum) {

/*        Scale matrix norm down to BIGNUM */

	dlascl_("G", &c__0, &c__0, &anrm, &bignum, m, n, &a[a_offset], lda,
		info);
	iascl = 2;
    } else if (anrm == 0.) {

/*        Matrix all zero. Return zero solution. */

	i__1 = max(*m,*n);
	dlaset_("F", &i__1, nrhs, &c_b31, &c_b31, &b[b_offset], ldb);
	*rank = 0;
	goto L70;
    }

    bnrm = dlange_("M", m, nrhs, &b[b_offset], ldb, &work[1]);
    ibscl = 0;
    if (bnrm > 0. && bnrm < smlnum) {

/*        Scale matrix norm up to SMLNUM */

	dlascl_("G", &c__0, &c__0, &bnrm, &smlnum, m, nrhs, &b[b_offset], ldb,
		 info);
	ibscl = 1;
    } else if (bnrm > bignum) {

/*        Scale matrix norm down to BIGNUM */

	dlascl_("G", &c__0, &c__0, &bnrm, &bignum, m, nrhs, &b[b_offset], ldb,
		 info);
	ibscl = 2;
    }

/*     Compute QR factorization with column pivoting of A: */
/*        A * P = Q * R */

    i__1 = *lwork - mn;
    dgeqp3_(m, n, &a[a_offset], lda, &jpvt[1], &work[1], &work[mn + 1], &i__1,
	     info);
    wsize = mn + work[mn + 1];

/*     workspace: MN+2*N+NB*(N+1). */
/*     Details of Householder rotations stored in WORK(1:MN). */

/*     Determine RANK using incremental condition estimation */

    work[ismin] = 1.;
    work[ismax] = 1.;
    smax = (d__1 = a[a_dim1 + 1], abs(d__1));
    smin = smax;
    if ((d__1 = a[a_dim1 + 1], abs(d__1)) == 0.) {
	*rank = 0;
	i__1 = max(*m,*n);
	dlaset_("F", &i__1, nrhs, &c_b31, &c_b31, &b[b_offset], ldb);
	goto L70;
    } else {
	*rank = 1;
    }

L10:
    if (*rank < mn) {
	i__ = *rank + 1;
	dlaic1_(&c__2, rank, &work[ismin], &smin, &a[i__ * a_dim1 + 1], &a[
		i__ + i__ * a_dim1], &sminpr, &s1, &c1);
	dlaic1_(&c__1, rank, &work[ismax], &smax, &a[i__ * a_dim1 + 1], &a[
		i__ + i__ * a_dim1], &smaxpr, &s2, &c2);

	if (smaxpr * *rcond <= sminpr) {
	    i__1 = *rank;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		work[ismin + i__ - 1] = s1 * work[ismin + i__ - 1];
		work[ismax + i__ - 1] = s2 * work[ismax + i__ - 1];
/* L20: */
	    }
	    work[ismin + *rank] = c1;
	    work[ismax + *rank] = c2;
	    smin = sminpr;
	    smax = smaxpr;
	    ++(*rank);
	    goto L10;
	}
    }

/*     workspace: 3*MN. */

/*     Logically partition R = [ R11 R12 ] */
/*                             [  0  R22 ] */
/*     where R11 = R(1:RANK,1:RANK) */

/*     [R11,R12] = [ T11, 0 ] * Y */

    if (*rank < *n) {
	i__1 = *lwork - (mn << 1);
	dtzrzf_(rank, n, &a[a_offset], lda, &work[mn + 1], &work[(mn << 1) +
		1], &i__1, info);
    }

/*     workspace: 2*MN. */
/*     Details of Householder rotations stored in WORK(MN+1:2*MN) */

/*     B(1:M,1:NRHS) := Q' * B(1:M,1:NRHS) */

    i__1 = *lwork - (mn << 1);
    dormqr_("Left", "Transpose", m, nrhs, &mn, &a[a_offset], lda, &work[1], &
	    b[b_offset], ldb, &work[(mn << 1) + 1], &i__1, info);
/* Computing MAX */
    d__1 = wsize, d__2 = (mn << 1) + work[(mn << 1) + 1];
    wsize = max(d__1,d__2);

/*     workspace: 2*MN+NB*NRHS. */

/*     B(1:RANK,1:NRHS) := inv(T11) * B(1:RANK,1:NRHS) */

    dtrsm_("Left", "Upper", "No transpose", "Non-unit", rank, nrhs, &c_b54, &
	    a[a_offset], lda, &b[b_offset], ldb);

    i__1 = *nrhs;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *n;
	for (i__ = *rank + 1; i__ <= i__2; ++i__) {
	    b[i__ + j * b_dim1] = 0.;
/* L30: */
	}
/* L40: */
    }

/*     B(1:N,1:NRHS) := Y' * B(1:N,1:NRHS) */

    if (*rank < *n) {
	i__1 = *n - *rank;
	i__2 = *lwork - (mn << 1);
	dormrz_("Left", "Transpose", n, nrhs, rank, &i__1, &a[a_offset], lda,
		&work[mn + 1], &b[b_offset], ldb, &work[(mn << 1) + 1], &i__2,
		 info);
    }

/*     workspace: 2*MN+NRHS. */

/*     B(1:N,1:NRHS) := P * B(1:N,1:NRHS) */

    i__1 = *nrhs;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *n;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    work[jpvt[i__]] = b[i__ + j * b_dim1];
/* L50: */
	}
	dcopy_(n, &work[1], &c__1, &b[j * b_dim1 + 1], &c__1);
/* L60: */
    }

/*     workspace: N. */

/*     Undo scaling */

    if (iascl == 1) {
	dlascl_("G", &c__0, &c__0, &anrm, &smlnum, n, nrhs, &b[b_offset], ldb,
		 info);
	dlascl_("U", &c__0, &c__0, &smlnum, &anrm, rank, rank, &a[a_offset],
		lda, info);
    } else if (iascl == 2) {
	dlascl_("G", &c__0, &c__0, &anrm, &bignum, n, nrhs, &b[b_offset], ldb,
		 info);
	dlascl_("U", &c__0, &c__0, &bignum, &anrm, rank, rank, &a[a_offset],
		lda, info);
    }
    if (ibscl == 1) {
	dlascl_("G", &c__0, &c__0, &smlnum, &bnrm, n, nrhs, &b[b_offset], ldb,
		 info);
    } else if (ibscl == 2) {
	dlascl_("G", &c__0, &c__0, &bignum, &bnrm, n, nrhs, &b[b_offset], ldb,
		 info);
    }

L70:
    work[1] = (doublereal) lwkopt;

    return 0;

/*     End of DGELSY */

} /* dgelsy_ */

/* Subroutine */ int dgeqp3_(integer *m, integer *n, doublereal *a, integer *
	lda, integer *jpvt, doublereal *tau, doublereal *work, integer *lwork,
	 integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;
    integer c_n1 = -1;
    integer c__3 = 3;
    integer c__2 = 2;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;

    /* Local variables */
    integer j, jb, na, nb, sm, sn, nx, fjb, iws, nfxd;
    extern doublereal dnrm2_(integer *, doublereal *, integer *);
    integer nbmin, minmn;
    extern /* Subroutine */ int dswap_(integer *, doublereal *, integer *,
	    doublereal *, integer *);
    integer minws;
    extern /* Subroutine */ int dlaqp2_(integer *, integer *, integer *,
	    doublereal *, integer *, integer *, doublereal *, doublereal *,
	    doublereal *, doublereal *), dgeqrf_(integer *, integer *,
	    doublereal *, integer *, doublereal *, doublereal *, integer *,
	    integer *), xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *,
	    integer *, integer *);
    extern /* Subroutine */ int dlaqps_(integer *, integer *, integer *,
	    integer *, integer *, doublereal *, integer *, integer *,
	    doublereal *, doublereal *, doublereal *, doublereal *,
	    doublereal *, integer *);
    integer topbmn, sminmn;
    extern /* Subroutine */ int dormqr_(char *, char *, integer *, integer *,
	    integer *, doublereal *, integer *, doublereal *, doublereal *,
	    integer *, doublereal *, integer *, integer *);
    integer lwkopt;
    logical lquery;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGEQP3 computes a QR factorization with column pivoting of a */
/*  matrix A:  A*P = Q*R  using Level 3 BLAS. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A. M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A.  N >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the M-by-N matrix A. */
/*          On exit, the upper triangle of the array contains the */
/*          min(M,N)-by-N upper trapezoidal matrix R; the elements below */
/*          the diagonal, together with the array TAU, represent the */
/*          orthogonal matrix Q as a product of min(M,N) elementary */
/*          reflectors. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A. LDA >= max(1,M). */

/*  JPVT    (input/output) INTEGER array, dimension (N) */
/*          On entry, if JPVT(J).ne.0, the J-th column of A is permuted */
/*          to the front of A*P (a leading column); if JPVT(J)=0, */
/*          the J-th column of A is a free column. */
/*          On exit, if JPVT(J)=K, then the J-th column of A*P was the */
/*          the K-th column of A. */

/*  TAU     (output) DOUBLE PRECISION array, dimension (min(M,N)) */
/*          The scalar factors of the elementary reflectors. */

/*  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK)) */
/*          On exit, if INFO=0, WORK(1) returns the optimal LWORK. */

/*  LWORK   (input) INTEGER */
/*          The dimension of the array WORK. LWORK >= 3*N+1. */
/*          For optimal performance LWORK >= 2*N+( N+1 )*NB, where NB */
/*          is the optimal blocksize. */

/*          If LWORK = -1, then a workspace query is assumed; the routine */
/*          only calculates the optimal size of the WORK array, returns */
/*          this value as the first entry of the WORK array, and no error */
/*          message related to LWORK is issued by XERBLA. */

/*  INFO    (output) INTEGER */
/*          = 0: successful exit. */
/*          < 0: if INFO = -i, the i-th argument had an illegal value. */

/*  Further Details */
/*  =============== */

/*  The matrix Q is represented as a product of elementary reflectors */

/*     Q = H(1) H(2) . . . H(k), where k = min(m,n). */

/*  Each H(i) has the form */

/*     H(i) = I - tau * v * v' */

/*  where tau is a real/complex scalar, and v is a real/complex vector */
/*  with v(1:i-1) = 0 and v(i) = 1; v(i+1:m) is stored on exit in */
/*  A(i+1:m,i), and tau in TAU(i). */

/*  Based on contributions by */
/*    G. Quintana-Orti, Depto. de Informatica, Universidad Jaime I, Spain */
/*    X. Sun, Computer Science Dept., Duke University, USA */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test input arguments */
/*     ==================== */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --jpvt;
    --tau;
    --work;

    /* Function Body */
    *info = 0;
    lquery = *lwork == -1;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*m)) {
	*info = -4;
    }

    if (*info == 0) {
	minmn = min(*m,*n);
	if (minmn == 0) {
	    iws = 1;
	    lwkopt = 1;
	} else {
	    iws = *n * 3 + 1;
	    nb = ilaenv_(&c__1, "DGEQRF", " ", m, n, &c_n1, &c_n1);
	    lwkopt = (*n << 1) + (*n + 1) * nb;
	}
	work[1] = (doublereal) lwkopt;

	if (*lwork < iws && ! lquery) {
	    *info = -8;
	}
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGEQP3", &i__1);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible. */

    if (minmn == 0) {
	return 0;
    }

/*     Move initial columns up front. */

    nfxd = 1;
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	if (jpvt[j] != 0) {
	    if (j != nfxd) {
		dswap_(m, &a[j * a_dim1 + 1], &c__1, &a[nfxd * a_dim1 + 1], &
			c__1);
		jpvt[j] = jpvt[nfxd];
		jpvt[nfxd] = j;
	    } else {
		jpvt[j] = j;
	    }
	    ++nfxd;
	} else {
	    jpvt[j] = j;
	}
/* L10: */
    }
    --nfxd;

/*     Factorize fixed columns */
/*     ======================= */

/*     Compute the QR factorization of fixed columns and update */
/*     remaining columns. */

    if (nfxd > 0) {
	na = min(*m,nfxd);
/* CC      CALL DGEQR2( M, NA, A, LDA, TAU, WORK, INFO ) */
	dgeqrf_(m, &na, &a[a_offset], lda, &tau[1], &work[1], lwork, info);
/* Computing MAX */
	i__1 = iws, i__2 = (integer) work[1];
	iws = max(i__1,i__2);
	if (na < *n) {
/* CC         CALL DORM2R( 'Left', 'Transpose', M, N-NA, NA, A, LDA, */
/* CC  $                   TAU, A( 1, NA+1 ), LDA, WORK, INFO ) */
	    i__1 = *n - na;
	    dormqr_("Left", "Transpose", m, &i__1, &na, &a[a_offset], lda, &
		    tau[1], &a[(na + 1) * a_dim1 + 1], lda, &work[1], lwork,
		    info);
/* Computing MAX */
	    i__1 = iws, i__2 = (integer) work[1];
	    iws = max(i__1,i__2);
	}
    }

/*     Factorize free columns */
/*     ====================== */

    if (nfxd < minmn) {

	sm = *m - nfxd;
	sn = *n - nfxd;
	sminmn = minmn - nfxd;

/*        Determine the block size. */

	nb = ilaenv_(&c__1, "DGEQRF", " ", &sm, &sn, &c_n1, &c_n1);
	nbmin = 2;
	nx = 0;

	if (nb > 1 && nb < sminmn) {

/*           Determine when to cross over from blocked to unblocked code. */

/* Computing MAX */
	    i__1 = 0, i__2 = ilaenv_(&c__3, "DGEQRF", " ", &sm, &sn, &c_n1, &
		    c_n1);
	    nx = max(i__1,i__2);


	    if (nx < sminmn) {

/*              Determine if workspace is large enough for blocked code. */

		minws = (sn << 1) + (sn + 1) * nb;
		iws = max(iws,minws);
		if (*lwork < minws) {

/*                 Not enough workspace to use optimal NB: Reduce NB and */
/*                 determine the minimum value of NB. */

		    nb = (*lwork - (sn << 1)) / (sn + 1);
/* Computing MAX */
		    i__1 = 2, i__2 = ilaenv_(&c__2, "DGEQRF", " ", &sm, &sn, &
			    c_n1, &c_n1);
		    nbmin = max(i__1,i__2);


		}
	    }
	}

/*        Initialize partial column norms. The first N elements of work */
/*        store the exact column norms. */

	i__1 = *n;
	for (j = nfxd + 1; j <= i__1; ++j) {
	    work[j] = dnrm2_(&sm, &a[nfxd + 1 + j * a_dim1], &c__1);
	    work[*n + j] = work[j];
/* L20: */
	}

	if (nb >= nbmin && nb < sminmn && nx < sminmn) {

/*           Use blocked code initially. */

	    j = nfxd + 1;

/*           Compute factorization: while loop. */


	    topbmn = minmn - nx;
L30:
	    if (j <= topbmn) {
/* Computing MIN */
		i__1 = nb, i__2 = topbmn - j + 1;
		jb = min(i__1,i__2);

/*              Factorize JB columns among columns J:N. */

		i__1 = *n - j + 1;
		i__2 = j - 1;
		i__3 = *n - j + 1;
		dlaqps_(m, &i__1, &i__2, &jb, &fjb, &a[j * a_dim1 + 1], lda, &
			jpvt[j], &tau[j], &work[j], &work[*n + j], &work[(*n
			<< 1) + 1], &work[(*n << 1) + jb + 1], &i__3);

		j += fjb;
		goto L30;
	    }
	} else {
	    j = nfxd + 1;
	}

/*        Use unblocked code to factor the last or only block. */


	if (j <= minmn) {
	    i__1 = *n - j + 1;
	    i__2 = j - 1;
	    dlaqp2_(m, &i__1, &i__2, &a[j * a_dim1 + 1], lda, &jpvt[j], &tau[
		    j], &work[j], &work[*n + j], &work[(*n << 1) + 1]);
	}

    }

    work[1] = (doublereal) iws;
    return 0;

/*     End of DGEQP3 */

} /* dgeqp3_ */

/* Subroutine */ int dgeqr2_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *tau, doublereal *work, integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;

    /* Local variables */
    integer i__, k;
    doublereal aii;
    extern /* Subroutine */ int dlarf_(char *, integer *, integer *,
	    doublereal *, integer *, doublereal *, doublereal *, integer *,
	    doublereal *), dlarfp_(integer *, doublereal *,
	    doublereal *, integer *, doublereal *), xerbla_(char *, integer *);


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGEQR2 computes a QR factorization of a real m by n matrix A: */
/*  A = Q * R. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A.  M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A.  N >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the m by n matrix A. */
/*          On exit, the elements on and above the diagonal of the array */
/*          contain the min(m,n) by n upper trapezoidal matrix R (R is */
/*          upper triangular if m >= n); the elements below the diagonal, */
/*          with the array TAU, represent the orthogonal matrix Q as a */
/*          product of elementary reflectors (see Further Details). */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,M). */

/*  TAU     (output) DOUBLE PRECISION array, dimension (min(M,N)) */
/*          The scalar factors of the elementary reflectors (see Further */
/*          Details). */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (N) */

/*  INFO    (output) INTEGER */
/*          = 0: successful exit */
/*          < 0: if INFO = -i, the i-th argument had an illegal value */

/*  Further Details */
/*  =============== */

/*  The matrix Q is represented as a product of elementary reflectors */

/*     Q = H(1) H(2) . . . H(k), where k = min(m,n). */

/*  Each H(i) has the form */

/*     H(i) = I - tau * v * v' */

/*  where tau is a real scalar, and v is a real vector with */
/*  v(1:i-1) = 0 and v(i) = 1; v(i+1:m) is stored on exit in A(i+1:m,i), */
/*  and tau in TAU(i). */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    --work;

    /* Function Body */
    *info = 0;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*m)) {
	*info = -4;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGEQR2", &i__1);
	return 0;
    }

    k = min(*m,*n);

    i__1 = k;
    for (i__ = 1; i__ <= i__1; ++i__) {

/*        Generate elementary reflector H(i) to annihilate A(i+1:m,i) */

	i__2 = *m - i__ + 1;
/* Computing MIN */
	i__3 = i__ + 1;
	dlarfp_(&i__2, &a[i__ + i__ * a_dim1], &a[min(i__3, *m)+ i__ * a_dim1]
, &c__1, &tau[i__]);
	if (i__ < *n) {

/*           Apply H(i) to A(i:m,i+1:n) from the left */

	    aii = a[i__ + i__ * a_dim1];
	    a[i__ + i__ * a_dim1] = 1.;
	    i__2 = *m - i__ + 1;
	    i__3 = *n - i__;
	    dlarf_("Left", &i__2, &i__3, &a[i__ + i__ * a_dim1], &c__1, &tau[
		    i__], &a[i__ + (i__ + 1) * a_dim1], lda, &work[1]);
	    a[i__ + i__ * a_dim1] = aii;
	}
/* L10: */
    }
    return 0;

/*     End of DGEQR2 */

} /* dgeqr2_ */

/* Subroutine */ int dgeqrf_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *tau, doublereal *work, integer *lwork, integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;
    integer c_n1 = -1;
    integer c__3 = 3;
    integer c__2 = 2;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4;

    /* Local variables */
    integer i__, k, ib, nb, nx, iws, nbmin, iinfo;
    extern /* Subroutine */ int dgeqr2_(integer *, integer *, doublereal *,
	    integer *, doublereal *, doublereal *, integer *), dlarfb_(char *,
	     char *, char *, char *, integer *, integer *, integer *,
	    doublereal *, integer *, doublereal *, integer *, doublereal *,
	    integer *, doublereal *, integer *), dlarft_(char *, char *, integer *, integer *, doublereal
	    *, integer *, doublereal *, doublereal *, integer *), xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *,
	    integer *, integer *);
    integer ldwork, lwkopt;
    logical lquery;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGEQRF computes a QR factorization of a real M-by-N matrix A: */
/*  A = Q * R. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A.  M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A.  N >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the M-by-N matrix A. */
/*          On exit, the elements on and above the diagonal of the array */
/*          contain the min(M,N)-by-N upper trapezoidal matrix R (R is */
/*          upper triangular if m >= n); the elements below the diagonal, */
/*          with the array TAU, represent the orthogonal matrix Q as a */
/*          product of min(m,n) elementary reflectors (see Further */
/*          Details). */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,M). */

/*  TAU     (output) DOUBLE PRECISION array, dimension (min(M,N)) */
/*          The scalar factors of the elementary reflectors (see Further */
/*          Details). */

/*  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK)) */
/*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK. */

/*  LWORK   (input) INTEGER */
/*          The dimension of the array WORK.  LWORK >= max(1,N). */
/*          For optimum performance LWORK >= N*NB, where NB is */
/*          the optimal blocksize. */

/*          If LWORK = -1, then a workspace query is assumed; the routine */
/*          only calculates the optimal size of the WORK array, returns */
/*          this value as the first entry of the WORK array, and no error */
/*          message related to LWORK is issued by XERBLA. */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */

/*  Further Details */
/*  =============== */

/*  The matrix Q is represented as a product of elementary reflectors */

/*     Q = H(1) H(2) . . . H(k), where k = min(m,n). */

/*  Each H(i) has the form */

/*     H(i) = I - tau * v * v' */

/*  where tau is a real scalar, and v is a real vector with */
/*  v(1:i-1) = 0 and v(i) = 1; v(i+1:m) is stored on exit in A(i+1:m,i), */
/*  and tau in TAU(i). */

/*  ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    --work;

    /* Function Body */
    *info = 0;
    nb = ilaenv_(&c__1, "DGEQRF", " ", m, n, &c_n1, &c_n1);
    lwkopt = *n * nb;
    work[1] = (doublereal) lwkopt;
    lquery = *lwork == -1;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*m)) {
	*info = -4;
    } else if (*lwork < max(1,*n) && ! lquery) {
	*info = -7;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGEQRF", &i__1);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible */

    k = min(*m,*n);
    if (k == 0) {
	work[1] = 1.;
	return 0;
    }

    nbmin = 2;
    nx = 0;
    iws = *n;
    if (nb > 1 && nb < k) {

/*        Determine when to cross over from blocked to unblocked code. */

/* Computing MAX */
	i__1 = 0, i__2 = ilaenv_(&c__3, "DGEQRF", " ", m, n, &c_n1, &c_n1);
	nx = max(i__1,i__2);
	if (nx < k) {

/*           Determine if workspace is large enough for blocked code. */

	    ldwork = *n;
	    iws = ldwork * nb;
	    if (*lwork < iws) {

/*              Not enough workspace to use optimal NB:  reduce NB and */
/*              determine the minimum value of NB. */

		nb = *lwork / ldwork;
/* Computing MAX */
		i__1 = 2, i__2 = ilaenv_(&c__2, "DGEQRF", " ", m, n, &c_n1, &
			c_n1);
		nbmin = max(i__1,i__2);
	    }
	}
    }

    if (nb >= nbmin && nb < k && nx < k) {

/*        Use blocked code initially */

	i__1 = k - nx;
	i__2 = nb;
	for (i__ = 1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {
/* Computing MIN */
	    i__3 = k - i__ + 1;
	    ib = min(i__3,nb);

/*           Compute the QR factorization of the current block */
/*           A(i:m,i:i+ib-1) */

	    i__3 = *m - i__ + 1;
	    dgeqr2_(&i__3, &ib, &a[i__ + i__ * a_dim1], lda, &tau[i__], &work[
		    1], &iinfo);
	    if (i__ + ib <= *n) {

/*              Form the triangular factor of the block reflector */
/*              H = H(i) H(i+1) . . . H(i+ib-1) */

		i__3 = *m - i__ + 1;
		dlarft_("Forward", "Columnwise", &i__3, &ib, &a[i__ + i__ *
			a_dim1], lda, &tau[i__], &work[1], &ldwork);

/*              Apply H' to A(i:m,i+ib:n) from the left */

		i__3 = *m - i__ + 1;
		i__4 = *n - i__ - ib + 1;
		dlarfb_("Left", "Transpose", "Forward", "Columnwise", &i__3, &
			i__4, &ib, &a[i__ + i__ * a_dim1], lda, &work[1], &
			ldwork, &a[i__ + (i__ + ib) * a_dim1], lda, &work[ib
			+ 1], &ldwork);
	    }
/* L10: */
	}
    } else {
	i__ = 1;
    }

/*     Use unblocked code to factor the last or only block. */

    if (i__ <= k) {
	i__2 = *m - i__ + 1;
	i__1 = *n - i__ + 1;
	dgeqr2_(&i__2, &i__1, &a[i__ + i__ * a_dim1], lda, &tau[i__], &work[1]
, &iinfo);
    }

    work[1] = (doublereal) iws;
    return 0;

/*     End of DGEQRF */

} /* dgeqrf_ */

/* Subroutine */ int dgesvd_(char *jobu, char *jobvt, integer *m, integer *n,
	doublereal *a, integer *lda, doublereal *s, doublereal *u, integer *
	ldu, doublereal *vt, integer *ldvt, doublereal *work, integer *lwork,
	integer *info)
{
    /* Table of constant values */

    integer c__6 = 6;
    integer c__0 = 0;
    integer c__2 = 2;
    integer c__1 = 1;
    integer c_n1 = -1;
    doublereal c_b421 = 0.;
    doublereal c_b443 = 1.;

    /* System generated locals */
    address a__1[2];
    integer a_dim1, a_offset, u_dim1, u_offset, vt_dim1, vt_offset, i__1[2],
	    i__2, i__3, i__4;
    char ch__1[2];

    /* Local variables */
    integer i__, ie, ir, iu, blk, ncu;
    doublereal dum[1], eps;
    integer nru, iscl;
    doublereal anrm;
    integer ierr, itau, ncvt, nrvt;
    extern /* Subroutine */ int dgemm_(char *, char *, integer *, integer *,
	    integer *, doublereal *, doublereal *, integer *, doublereal *,
	    integer *, doublereal *, doublereal *, integer *);
    extern logical lsame_(char *, char *);
    integer chunk, minmn, wrkbl, itaup, itauq, mnthr, iwork;
    logical wntua, wntva, wntun, wntuo, wntvn, wntvo, wntus, wntvs;
    extern /* Subroutine */ int dgebrd_(integer *, integer *, doublereal *,
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, integer *, integer *);
    extern doublereal dlamch_(char *), dlange_(char *, integer *,
	    integer *, doublereal *, integer *, doublereal *);
    integer bdspac;
    extern /* Subroutine */ int dgelqf_(integer *, integer *, doublereal *,
	    integer *, doublereal *, doublereal *, integer *, integer *),
	    dlascl_(char *, integer *, integer *, doublereal *, doublereal *,
	    integer *, integer *, doublereal *, integer *, integer *),
	     dgeqrf_(integer *, integer *, doublereal *, integer *,
	    doublereal *, doublereal *, integer *, integer *), dlacpy_(char *,
	     integer *, integer *, doublereal *, integer *, doublereal *,
	    integer *), dlaset_(char *, integer *, integer *,
	    doublereal *, doublereal *, doublereal *, integer *),
	    dbdsqr_(char *, integer *, integer *, integer *, integer *,
	    doublereal *, doublereal *, doublereal *, integer *, doublereal *,
	     integer *, doublereal *, integer *, doublereal *, integer *), dorgbr_(char *, integer *, integer *, integer *,
	    doublereal *, integer *, doublereal *, doublereal *, integer *,
	    integer *);
    doublereal bignum;
    extern /* Subroutine */ int xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *,
	    integer *, integer *);
    extern /* Subroutine */ int dormbr_(char *, char *, char *, integer *,
	    integer *, integer *, doublereal *, integer *, doublereal *,
	    doublereal *, integer *, doublereal *, integer *, integer *), dorglq_(integer *, integer *, integer *,
	    doublereal *, integer *, doublereal *, doublereal *, integer *,
	    integer *), dorgqr_(integer *, integer *, integer *, doublereal *,
	     integer *, doublereal *, doublereal *, integer *, integer *);
    integer ldwrkr, minwrk, ldwrku, maxwrk;
    doublereal smlnum;
    logical lquery, wntuas, wntvas;


/*  -- LAPACK driver routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGESVD computes the singular value decomposition (SVD) of a real */
/*  M-by-N matrix A, optionally computing the left and/or right singular */
/*  vectors. The SVD is written */

/*       A = U * SIGMA * transpose(V) */

/*  where SIGMA is an M-by-N matrix which is zero except for its */
/*  min(m,n) diagonal elements, U is an M-by-M orthogonal matrix, and */
/*  V is an N-by-N orthogonal matrix.  The diagonal elements of SIGMA */
/*  are the singular values of A; they are real and non-negative, and */
/*  are returned in descending order.  The first min(m,n) columns of */
/*  U and V are the left and right singular vectors of A. */

/*  Note that the routine returns V**T, not V. */

/*  Arguments */
/*  ========= */

/*  JOBU    (input) CHARACTER*1 */
/*          Specifies options for computing all or part of the matrix U: */
/*          = 'A':  all M columns of U are returned in array U: */
/*          = 'S':  the first min(m,n) columns of U (the left singular */
/*                  vectors) are returned in the array U; */
/*          = 'O':  the first min(m,n) columns of U (the left singular */
/*                  vectors) are overwritten on the array A; */
/*          = 'N':  no columns of U (no left singular vectors) are */
/*                  computed. */

/*  JOBVT   (input) CHARACTER*1 */
/*          Specifies options for computing all or part of the matrix */
/*          V**T: */
/*          = 'A':  all N rows of V**T are returned in the array VT; */
/*          = 'S':  the first min(m,n) rows of V**T (the right singular */
/*                  vectors) are returned in the array VT; */
/*          = 'O':  the first min(m,n) rows of V**T (the right singular */
/*                  vectors) are overwritten on the array A; */
/*          = 'N':  no rows of V**T (no right singular vectors) are */
/*                  computed. */

/*          JOBVT and JOBU cannot both be 'O'. */

/*  M       (input) INTEGER */
/*          The number of rows of the input matrix A.  M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the input matrix A.  N >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the M-by-N matrix A. */
/*          On exit, */
/*          if JOBU = 'O',  A is overwritten with the first min(m,n) */
/*                          columns of U (the left singular vectors, */
/*                          stored columnwise); */
/*          if JOBVT = 'O', A is overwritten with the first min(m,n) */
/*                          rows of V**T (the right singular vectors, */
/*                          stored rowwise); */
/*          if JOBU .ne. 'O' and JOBVT .ne. 'O', the contents of A */
/*                          are destroyed. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,M). */

/*  S       (output) DOUBLE PRECISION array, dimension (min(M,N)) */
/*          The singular values of A, sorted so that S(i) >= S(i+1). */

/*  U       (output) DOUBLE PRECISION array, dimension (LDU,UCOL) */
/*          (LDU,M) if JOBU = 'A' or (LDU,min(M,N)) if JOBU = 'S'. */
/*          If JOBU = 'A', U contains the M-by-M orthogonal matrix U; */
/*          if JOBU = 'S', U contains the first min(m,n) columns of U */
/*          (the left singular vectors, stored columnwise); */
/*          if JOBU = 'N' or 'O', U is not referenced. */

/*  LDU     (input) INTEGER */
/*          The leading dimension of the array U.  LDU >= 1; if */
/*          JOBU = 'S' or 'A', LDU >= M. */

/*  VT      (output) DOUBLE PRECISION array, dimension (LDVT,N) */
/*          If JOBVT = 'A', VT contains the N-by-N orthogonal matrix */
/*          V**T; */
/*          if JOBVT = 'S', VT contains the first min(m,n) rows of */
/*          V**T (the right singular vectors, stored rowwise); */
/*          if JOBVT = 'N' or 'O', VT is not referenced. */

/*  LDVT    (input) INTEGER */
/*          The leading dimension of the array VT.  LDVT >= 1; if */
/*          JOBVT = 'A', LDVT >= N; if JOBVT = 'S', LDVT >= min(M,N). */

/*  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK)) */
/*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK; */
/*          if INFO > 0, WORK(2:MIN(M,N)) contains the unconverged */
/*          superdiagonal elements of an upper bidiagonal matrix B */
/*          whose diagonal is in S (not necessarily sorted). B */
/*          satisfies A = U * B * VT, so it has the same singular values */
/*          as A, and singular vectors related by U and VT. */

/*  LWORK   (input) INTEGER */
/*          The dimension of the array WORK. */
/*          LWORK >= MAX(1,3*MIN(M,N)+MAX(M,N),5*MIN(M,N)). */
/*          For good performance, LWORK should generally be larger. */

/*          If LWORK = -1, then a workspace query is assumed; the routine */
/*          only calculates the optimal size of the WORK array, returns */
/*          this value as the first entry of the WORK array, and no error */
/*          message related to LWORK is issued by XERBLA. */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit. */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value. */
/*          > 0:  if DBDSQR did not converge, INFO specifies how many */
/*                superdiagonals of an intermediate bidiagonal form B */
/*                did not converge to zero. See the description of WORK */
/*                above for details. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Local Arrays .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --s;
    u_dim1 = *ldu;
    u_offset = 1 + u_dim1;
    u -= u_offset;
    vt_dim1 = *ldvt;
    vt_offset = 1 + vt_dim1;
    vt -= vt_offset;
    --work;

    /* Function Body */
    *info = 0;
    minmn = min(*m,*n);
    wntua = lsame_(jobu, "A");
    wntus = lsame_(jobu, "S");
    wntuas = wntua || wntus;
    wntuo = lsame_(jobu, "O");
    wntun = lsame_(jobu, "N");
    wntva = lsame_(jobvt, "A");
    wntvs = lsame_(jobvt, "S");
    wntvas = wntva || wntvs;
    wntvo = lsame_(jobvt, "O");
    wntvn = lsame_(jobvt, "N");
    lquery = *lwork == -1;

    if (! (wntua || wntus || wntuo || wntun)) {
	*info = -1;
    } else if (! (wntva || wntvs || wntvo || wntvn) || (wntvo && wntuo)) {
	*info = -2;
    } else if (*m < 0) {
	*info = -3;
    } else if (*n < 0) {
	*info = -4;
    } else if (*lda < max(1,*m)) {
	*info = -6;
    } else if (*ldu < 1 || (wntuas && *ldu < *m)) {
	*info = -9;
    } else if (*ldvt < 1 || (wntva && *ldvt < *n) || (wntvs && *ldvt < minmn)) {
	*info = -11;
    }

/*     Compute workspace */
/*      (Note: Comments in the code beginning "Workspace:" describe the */
/*       minimal amount of workspace needed at that point in the code, */
/*       as well as the preferred amount for good performance. */
/*       NB refers to the optimal block size for the immediately */
/*       following subroutine, as returned by ILAENV.) */

    if (*info == 0) {
	minwrk = 1;
	maxwrk = 1;
	if (*m >= *n && minmn > 0) {

/*           Compute space needed for DBDSQR */

/* Writing concatenation */
	    i__1[0] = 1, a__1[0] = jobu;
	    i__1[1] = 1, a__1[1] = jobvt;
	    s_cat(ch__1, a__1, i__1, &c__2, (ftnlen)2);
	    mnthr = ilaenv_(&c__6, "DGESVD", ch__1, m, n, &c__0, &c__0);
	    bdspac = *n * 5;
	    if (*m >= mnthr) {
		if (wntun) {

/*                 Path 1 (M much larger than N, JOBU='N') */

		    maxwrk = *n + *n * ilaenv_(&c__1, "DGEQRF", " ", m, n, &
			    c_n1, &c_n1);
/* Computing MAX */
		    i__2 = maxwrk, i__3 = *n * 3 + (*n << 1) * ilaenv_(&c__1,
			    "DGEBRD", " ", n, n, &c_n1, &c_n1);
		    maxwrk = max(i__2,i__3);
		    if (wntvo || wntvas) {
/* Computing MAX */
			i__2 = maxwrk, i__3 = *n * 3 + (*n - 1) * ilaenv_(&
				c__1, "DORGBR", "P", n, n, n, &c_n1);
			maxwrk = max(i__2,i__3);
		    }
		    maxwrk = max(maxwrk,bdspac);
/* Computing MAX */
		    i__2 = *n << 2;
		    minwrk = max(i__2,bdspac);
		} else if (wntuo && wntvn) {

/*                 Path 2 (M much larger than N, JOBU='O', JOBVT='N') */

		    wrkbl = *n + *n * ilaenv_(&c__1, "DGEQRF", " ", m, n, &
			    c_n1, &c_n1);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n + *n * ilaenv_(&c__1, "DORGQR",
			    " ", m, n, n, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n * 3 + (*n << 1) * ilaenv_(&c__1,
			    "DGEBRD", " ", n, n, &c_n1, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n * 3 + *n * ilaenv_(&c__1, "DORGBR"
, "Q", n, n, n, &c_n1);
		    wrkbl = max(i__2,i__3);
		    wrkbl = max(wrkbl,bdspac);
/* Computing MAX */
		    i__2 = *n * *n + wrkbl, i__3 = *n * *n + *m * *n + *n;
		    maxwrk = max(i__2,i__3);
/* Computing MAX */
		    i__2 = *n * 3 + *m;
		    minwrk = max(i__2,bdspac);
		} else if (wntuo && wntvas) {

/*                 Path 3 (M much larger than N, JOBU='O', JOBVT='S' or */
/*                 'A') */

		    wrkbl = *n + *n * ilaenv_(&c__1, "DGEQRF", " ", m, n, &
			    c_n1, &c_n1);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n + *n * ilaenv_(&c__1, "DORGQR",
			    " ", m, n, n, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n * 3 + (*n << 1) * ilaenv_(&c__1,
			    "DGEBRD", " ", n, n, &c_n1, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n * 3 + *n * ilaenv_(&c__1, "DORGBR"
, "Q", n, n, n, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n * 3 + (*n - 1) * ilaenv_(&c__1,
			    "DORGBR", "P", n, n, n, &c_n1);
		    wrkbl = max(i__2,i__3);
		    wrkbl = max(wrkbl,bdspac);
/* Computing MAX */
		    i__2 = *n * *n + wrkbl, i__3 = *n * *n + *m * *n + *n;
		    maxwrk = max(i__2,i__3);
/* Computing MAX */
		    i__2 = *n * 3 + *m;
		    minwrk = max(i__2,bdspac);
		} else if (wntus && wntvn) {

/*                 Path 4 (M much larger than N, JOBU='S', JOBVT='N') */

		    wrkbl = *n + *n * ilaenv_(&c__1, "DGEQRF", " ", m, n, &
			    c_n1, &c_n1);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n + *n * ilaenv_(&c__1, "DORGQR",
			    " ", m, n, n, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n * 3 + (*n << 1) * ilaenv_(&c__1,
			    "DGEBRD", " ", n, n, &c_n1, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n * 3 + *n * ilaenv_(&c__1, "DORGBR"
, "Q", n, n, n, &c_n1);
		    wrkbl = max(i__2,i__3);
		    wrkbl = max(wrkbl,bdspac);
		    maxwrk = *n * *n + wrkbl;
/* Computing MAX */
		    i__2 = *n * 3 + *m;
		    minwrk = max(i__2,bdspac);
		} else if (wntus && wntvo) {

/*                 Path 5 (M much larger than N, JOBU='S', JOBVT='O') */

		    wrkbl = *n + *n * ilaenv_(&c__1, "DGEQRF", " ", m, n, &
			    c_n1, &c_n1);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n + *n * ilaenv_(&c__1, "DORGQR",
			    " ", m, n, n, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n * 3 + (*n << 1) * ilaenv_(&c__1,
			    "DGEBRD", " ", n, n, &c_n1, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n * 3 + *n * ilaenv_(&c__1, "DORGBR"
, "Q", n, n, n, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n * 3 + (*n - 1) * ilaenv_(&c__1,
			    "DORGBR", "P", n, n, n, &c_n1);
		    wrkbl = max(i__2,i__3);
		    wrkbl = max(wrkbl,bdspac);
		    maxwrk = (*n << 1) * *n + wrkbl;
/* Computing MAX */
		    i__2 = *n * 3 + *m;
		    minwrk = max(i__2,bdspac);
		} else if (wntus && wntvas) {

/*                 Path 6 (M much larger than N, JOBU='S', JOBVT='S' or */
/*                 'A') */

		    wrkbl = *n + *n * ilaenv_(&c__1, "DGEQRF", " ", m, n, &
			    c_n1, &c_n1);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n + *n * ilaenv_(&c__1, "DORGQR",
			    " ", m, n, n, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n * 3 + (*n << 1) * ilaenv_(&c__1,
			    "DGEBRD", " ", n, n, &c_n1, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n * 3 + *n * ilaenv_(&c__1, "DORGBR"
, "Q", n, n, n, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n * 3 + (*n - 1) * ilaenv_(&c__1,
			    "DORGBR", "P", n, n, n, &c_n1);
		    wrkbl = max(i__2,i__3);
		    wrkbl = max(wrkbl,bdspac);
		    maxwrk = *n * *n + wrkbl;
/* Computing MAX */
		    i__2 = *n * 3 + *m;
		    minwrk = max(i__2,bdspac);
		} else if (wntua && wntvn) {

/*                 Path 7 (M much larger than N, JOBU='A', JOBVT='N') */

		    wrkbl = *n + *n * ilaenv_(&c__1, "DGEQRF", " ", m, n, &
			    c_n1, &c_n1);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n + *m * ilaenv_(&c__1, "DORGQR",
			    " ", m, m, n, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n * 3 + (*n << 1) * ilaenv_(&c__1,
			    "DGEBRD", " ", n, n, &c_n1, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n * 3 + *n * ilaenv_(&c__1, "DORGBR"
, "Q", n, n, n, &c_n1);
		    wrkbl = max(i__2,i__3);
		    wrkbl = max(wrkbl,bdspac);
		    maxwrk = *n * *n + wrkbl;
/* Computing MAX */
		    i__2 = *n * 3 + *m;
		    minwrk = max(i__2,bdspac);
		} else if (wntua && wntvo) {

/*                 Path 8 (M much larger than N, JOBU='A', JOBVT='O') */

		    wrkbl = *n + *n * ilaenv_(&c__1, "DGEQRF", " ", m, n, &
			    c_n1, &c_n1);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n + *m * ilaenv_(&c__1, "DORGQR",
			    " ", m, m, n, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n * 3 + (*n << 1) * ilaenv_(&c__1,
			    "DGEBRD", " ", n, n, &c_n1, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n * 3 + *n * ilaenv_(&c__1, "DORGBR"
, "Q", n, n, n, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n * 3 + (*n - 1) * ilaenv_(&c__1,
			    "DORGBR", "P", n, n, n, &c_n1);
		    wrkbl = max(i__2,i__3);
		    wrkbl = max(wrkbl,bdspac);
		    maxwrk = (*n << 1) * *n + wrkbl;
/* Computing MAX */
		    i__2 = *n * 3 + *m;
		    minwrk = max(i__2,bdspac);
		} else if (wntua && wntvas) {

/*                 Path 9 (M much larger than N, JOBU='A', JOBVT='S' or */
/*                 'A') */

		    wrkbl = *n + *n * ilaenv_(&c__1, "DGEQRF", " ", m, n, &
			    c_n1, &c_n1);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n + *m * ilaenv_(&c__1, "DORGQR",
			    " ", m, m, n, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n * 3 + (*n << 1) * ilaenv_(&c__1,
			    "DGEBRD", " ", n, n, &c_n1, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n * 3 + *n * ilaenv_(&c__1, "DORGBR"
, "Q", n, n, n, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *n * 3 + (*n - 1) * ilaenv_(&c__1,
			    "DORGBR", "P", n, n, n, &c_n1);
		    wrkbl = max(i__2,i__3);
		    wrkbl = max(wrkbl,bdspac);
		    maxwrk = *n * *n + wrkbl;
/* Computing MAX */
		    i__2 = *n * 3 + *m;
		    minwrk = max(i__2,bdspac);
		}
	    } else {

/*              Path 10 (M at least N, but not much larger) */

		maxwrk = *n * 3 + (*m + *n) * ilaenv_(&c__1, "DGEBRD", " ", m,
			 n, &c_n1, &c_n1);
		if (wntus || wntuo) {
/* Computing MAX */
		    i__2 = maxwrk, i__3 = *n * 3 + *n * ilaenv_(&c__1, "DORG"
			    "BR", "Q", m, n, n, &c_n1);
		    maxwrk = max(i__2,i__3);
		}
		if (wntua) {
/* Computing MAX */
		    i__2 = maxwrk, i__3 = *n * 3 + *m * ilaenv_(&c__1, "DORG"
			    "BR", "Q", m, m, n, &c_n1);
		    maxwrk = max(i__2,i__3);
		}
		if (! wntvn) {
/* Computing MAX */
		    i__2 = maxwrk, i__3 = *n * 3 + (*n - 1) * ilaenv_(&c__1,
			    "DORGBR", "P", n, n, n, &c_n1);
		    maxwrk = max(i__2,i__3);
		}
		maxwrk = max(maxwrk,bdspac);
/* Computing MAX */
		i__2 = *n * 3 + *m;
		minwrk = max(i__2,bdspac);
	    }
	} else if (minmn > 0) {

/*           Compute space needed for DBDSQR */

/* Writing concatenation */
	    i__1[0] = 1, a__1[0] = jobu;
	    i__1[1] = 1, a__1[1] = jobvt;
	    s_cat(ch__1, a__1, i__1, &c__2, (ftnlen)2);
	    mnthr = ilaenv_(&c__6, "DGESVD", ch__1, m, n, &c__0, &c__0);
	    bdspac = *m * 5;
	    if (*n >= mnthr) {
		if (wntvn) {

/*                 Path 1t(N much larger than M, JOBVT='N') */

		    maxwrk = *m + *m * ilaenv_(&c__1, "DGELQF", " ", m, n, &
			    c_n1, &c_n1);
/* Computing MAX */
		    i__2 = maxwrk, i__3 = *m * 3 + (*m << 1) * ilaenv_(&c__1,
			    "DGEBRD", " ", m, m, &c_n1, &c_n1);
		    maxwrk = max(i__2,i__3);
		    if (wntuo || wntuas) {
/* Computing MAX */
			i__2 = maxwrk, i__3 = *m * 3 + *m * ilaenv_(&c__1,
				"DORGBR", "Q", m, m, m, &c_n1);
			maxwrk = max(i__2,i__3);
		    }
		    maxwrk = max(maxwrk,bdspac);
/* Computing MAX */
		    i__2 = *m << 2;
		    minwrk = max(i__2,bdspac);
		} else if (wntvo && wntun) {

/*                 Path 2t(N much larger than M, JOBU='N', JOBVT='O') */

		    wrkbl = *m + *m * ilaenv_(&c__1, "DGELQF", " ", m, n, &
			    c_n1, &c_n1);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m + *m * ilaenv_(&c__1, "DORGLQ",
			    " ", m, n, m, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m * 3 + (*m << 1) * ilaenv_(&c__1,
			    "DGEBRD", " ", m, m, &c_n1, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m * 3 + (*m - 1) * ilaenv_(&c__1,
			    "DORGBR", "P", m, m, m, &c_n1);
		    wrkbl = max(i__2,i__3);
		    wrkbl = max(wrkbl,bdspac);
/* Computing MAX */
		    i__2 = *m * *m + wrkbl, i__3 = *m * *m + *m * *n + *m;
		    maxwrk = max(i__2,i__3);
/* Computing MAX */
		    i__2 = *m * 3 + *n;
		    minwrk = max(i__2,bdspac);
		} else if (wntvo && wntuas) {

/*                 Path 3t(N much larger than M, JOBU='S' or 'A', */
/*                 JOBVT='O') */

		    wrkbl = *m + *m * ilaenv_(&c__1, "DGELQF", " ", m, n, &
			    c_n1, &c_n1);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m + *m * ilaenv_(&c__1, "DORGLQ",
			    " ", m, n, m, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m * 3 + (*m << 1) * ilaenv_(&c__1,
			    "DGEBRD", " ", m, m, &c_n1, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m * 3 + (*m - 1) * ilaenv_(&c__1,
			    "DORGBR", "P", m, m, m, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m * 3 + *m * ilaenv_(&c__1, "DORGBR"
, "Q", m, m, m, &c_n1);
		    wrkbl = max(i__2,i__3);
		    wrkbl = max(wrkbl,bdspac);
/* Computing MAX */
		    i__2 = *m * *m + wrkbl, i__3 = *m * *m + *m * *n + *m;
		    maxwrk = max(i__2,i__3);
/* Computing MAX */
		    i__2 = *m * 3 + *n;
		    minwrk = max(i__2,bdspac);
		} else if (wntvs && wntun) {

/*                 Path 4t(N much larger than M, JOBU='N', JOBVT='S') */

		    wrkbl = *m + *m * ilaenv_(&c__1, "DGELQF", " ", m, n, &
			    c_n1, &c_n1);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m + *m * ilaenv_(&c__1, "DORGLQ",
			    " ", m, n, m, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m * 3 + (*m << 1) * ilaenv_(&c__1,
			    "DGEBRD", " ", m, m, &c_n1, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m * 3 + (*m - 1) * ilaenv_(&c__1,
			    "DORGBR", "P", m, m, m, &c_n1);
		    wrkbl = max(i__2,i__3);
		    wrkbl = max(wrkbl,bdspac);
		    maxwrk = *m * *m + wrkbl;
/* Computing MAX */
		    i__2 = *m * 3 + *n;
		    minwrk = max(i__2,bdspac);
		} else if (wntvs && wntuo) {

/*                 Path 5t(N much larger than M, JOBU='O', JOBVT='S') */

		    wrkbl = *m + *m * ilaenv_(&c__1, "DGELQF", " ", m, n, &
			    c_n1, &c_n1);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m + *m * ilaenv_(&c__1, "DORGLQ",
			    " ", m, n, m, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m * 3 + (*m << 1) * ilaenv_(&c__1,
			    "DGEBRD", " ", m, m, &c_n1, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m * 3 + (*m - 1) * ilaenv_(&c__1,
			    "DORGBR", "P", m, m, m, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m * 3 + *m * ilaenv_(&c__1, "DORGBR"
, "Q", m, m, m, &c_n1);
		    wrkbl = max(i__2,i__3);
		    wrkbl = max(wrkbl,bdspac);
		    maxwrk = (*m << 1) * *m + wrkbl;
/* Computing MAX */
		    i__2 = *m * 3 + *n;
		    minwrk = max(i__2,bdspac);
		} else if (wntvs && wntuas) {

/*                 Path 6t(N much larger than M, JOBU='S' or 'A', */
/*                 JOBVT='S') */

		    wrkbl = *m + *m * ilaenv_(&c__1, "DGELQF", " ", m, n, &
			    c_n1, &c_n1);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m + *m * ilaenv_(&c__1, "DORGLQ",
			    " ", m, n, m, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m * 3 + (*m << 1) * ilaenv_(&c__1,
			    "DGEBRD", " ", m, m, &c_n1, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m * 3 + (*m - 1) * ilaenv_(&c__1,
			    "DORGBR", "P", m, m, m, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m * 3 + *m * ilaenv_(&c__1, "DORGBR"
, "Q", m, m, m, &c_n1);
		    wrkbl = max(i__2,i__3);
		    wrkbl = max(wrkbl,bdspac);
		    maxwrk = *m * *m + wrkbl;
/* Computing MAX */
		    i__2 = *m * 3 + *n;
		    minwrk = max(i__2,bdspac);
		} else if (wntva && wntun) {

/*                 Path 7t(N much larger than M, JOBU='N', JOBVT='A') */

		    wrkbl = *m + *m * ilaenv_(&c__1, "DGELQF", " ", m, n, &
			    c_n1, &c_n1);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m + *n * ilaenv_(&c__1, "DORGLQ",
			    " ", n, n, m, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m * 3 + (*m << 1) * ilaenv_(&c__1,
			    "DGEBRD", " ", m, m, &c_n1, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m * 3 + (*m - 1) * ilaenv_(&c__1,
			    "DORGBR", "P", m, m, m, &c_n1);
		    wrkbl = max(i__2,i__3);
		    wrkbl = max(wrkbl,bdspac);
		    maxwrk = *m * *m + wrkbl;
/* Computing MAX */
		    i__2 = *m * 3 + *n;
		    minwrk = max(i__2,bdspac);
		} else if (wntva && wntuo) {

/*                 Path 8t(N much larger than M, JOBU='O', JOBVT='A') */

		    wrkbl = *m + *m * ilaenv_(&c__1, "DGELQF", " ", m, n, &
			    c_n1, &c_n1);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m + *n * ilaenv_(&c__1, "DORGLQ",
			    " ", n, n, m, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m * 3 + (*m << 1) * ilaenv_(&c__1,
			    "DGEBRD", " ", m, m, &c_n1, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m * 3 + (*m - 1) * ilaenv_(&c__1,
			    "DORGBR", "P", m, m, m, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m * 3 + *m * ilaenv_(&c__1, "DORGBR"
, "Q", m, m, m, &c_n1);
		    wrkbl = max(i__2,i__3);
		    wrkbl = max(wrkbl,bdspac);
		    maxwrk = (*m << 1) * *m + wrkbl;
/* Computing MAX */
		    i__2 = *m * 3 + *n;
		    minwrk = max(i__2,bdspac);
		} else if (wntva && wntuas) {

/*                 Path 9t(N much larger than M, JOBU='S' or 'A', */
/*                 JOBVT='A') */

		    wrkbl = *m + *m * ilaenv_(&c__1, "DGELQF", " ", m, n, &
			    c_n1, &c_n1);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m + *n * ilaenv_(&c__1, "DORGLQ",
			    " ", n, n, m, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m * 3 + (*m << 1) * ilaenv_(&c__1,
			    "DGEBRD", " ", m, m, &c_n1, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m * 3 + (*m - 1) * ilaenv_(&c__1,
			    "DORGBR", "P", m, m, m, &c_n1);
		    wrkbl = max(i__2,i__3);
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *m * 3 + *m * ilaenv_(&c__1, "DORGBR"
, "Q", m, m, m, &c_n1);
		    wrkbl = max(i__2,i__3);
		    wrkbl = max(wrkbl,bdspac);
		    maxwrk = *m * *m + wrkbl;
/* Computing MAX */
		    i__2 = *m * 3 + *n;
		    minwrk = max(i__2,bdspac);
		}
	    } else {

/*              Path 10t(N greater than M, but not much larger) */

		maxwrk = *m * 3 + (*m + *n) * ilaenv_(&c__1, "DGEBRD", " ", m,
			 n, &c_n1, &c_n1);
		if (wntvs || wntvo) {
/* Computing MAX */
		    i__2 = maxwrk, i__3 = *m * 3 + *m * ilaenv_(&c__1, "DORG"
			    "BR", "P", m, n, m, &c_n1);
		    maxwrk = max(i__2,i__3);
		}
		if (wntva) {
/* Computing MAX */
		    i__2 = maxwrk, i__3 = *m * 3 + *n * ilaenv_(&c__1, "DORG"
			    "BR", "P", n, n, m, &c_n1);
		    maxwrk = max(i__2,i__3);
		}
		if (! wntun) {
/* Computing MAX */
		    i__2 = maxwrk, i__3 = *m * 3 + (*m - 1) * ilaenv_(&c__1,
			    "DORGBR", "Q", m, m, m, &c_n1);
		    maxwrk = max(i__2,i__3);
		}
		maxwrk = max(maxwrk,bdspac);
/* Computing MAX */
		i__2 = *m * 3 + *n;
		minwrk = max(i__2,bdspac);
	    }
	}
	maxwrk = max(maxwrk,minwrk);
	work[1] = (doublereal) maxwrk;

	if (*lwork < minwrk && ! lquery) {
	    *info = -13;
	}
    }

    if (*info != 0) {
	i__2 = -(*info);
	xerbla_("DGESVD", &i__2);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0) {
	return 0;
    }

/*     Get machine constants */

    eps = dlamch_("P");
    smlnum = sqrt(dlamch_("S")) / eps;
    bignum = 1. / smlnum;

/*     Scale A if max element outside range [SMLNUM,BIGNUM] */

    anrm = dlange_("M", m, n, &a[a_offset], lda, dum);
    iscl = 0;
    if (anrm > 0. && anrm < smlnum) {
	iscl = 1;
	dlascl_("G", &c__0, &c__0, &anrm, &smlnum, m, n, &a[a_offset], lda, &
		ierr);
    } else if (anrm > bignum) {
	iscl = 1;
	dlascl_("G", &c__0, &c__0, &anrm, &bignum, m, n, &a[a_offset], lda, &
		ierr);
    }

    if (*m >= *n) {

/*        A has at least as many rows as columns. If A has sufficiently */
/*        more rows than columns, first reduce using the QR */
/*        decomposition (if sufficient workspace available) */

	if (*m >= mnthr) {

	    if (wntun) {

/*              Path 1 (M much larger than N, JOBU='N') */
/*              No left singular vectors to be computed */

		itau = 1;
		iwork = itau + *n;

/*              Compute A=Q*R */
/*              (Workspace: need 2*N, prefer N+N*NB) */

		i__2 = *lwork - iwork + 1;
		dgeqrf_(m, n, &a[a_offset], lda, &work[itau], &work[iwork], &
			i__2, &ierr);

/*              Zero out below R */

		i__2 = *n - 1;
		i__3 = *n - 1;
		dlaset_("L", &i__2, &i__3, &c_b421, &c_b421, &a[a_dim1 + 2],
			lda);
		ie = 1;
		itauq = ie + *n;
		itaup = itauq + *n;
		iwork = itaup + *n;

/*              Bidiagonalize R in A */
/*              (Workspace: need 4*N, prefer 3*N+2*N*NB) */

		i__2 = *lwork - iwork + 1;
		dgebrd_(n, n, &a[a_offset], lda, &s[1], &work[ie], &work[
			itauq], &work[itaup], &work[iwork], &i__2, &ierr);
		ncvt = 0;
		if (wntvo || wntvas) {

/*                 If right singular vectors desired, generate P'. */
/*                 (Workspace: need 4*N-1, prefer 3*N+(N-1)*NB) */

		    i__2 = *lwork - iwork + 1;
		    dorgbr_("P", n, n, n, &a[a_offset], lda, &work[itaup], &
			    work[iwork], &i__2, &ierr);
		    ncvt = *n;
		}
		iwork = ie + *n;

/*              Perform bidiagonal QR iteration, computing right */
/*              singular vectors of A in A if desired */
/*              (Workspace: need BDSPAC) */

		dbdsqr_("U", n, &ncvt, &c__0, &c__0, &s[1], &work[ie], &a[
			a_offset], lda, dum, &c__1, dum, &c__1, &work[iwork],
			info);

/*              If right singular vectors desired in VT, copy them there */

		if (wntvas) {
		    dlacpy_("F", n, n, &a[a_offset], lda, &vt[vt_offset],
			    ldvt);
		}

	    } else if (wntuo && wntvn) {

/*              Path 2 (M much larger than N, JOBU='O', JOBVT='N') */
/*              N left singular vectors to be overwritten on A and */
/*              no right singular vectors to be computed */

/* Computing MAX */
		i__2 = *n << 2;
		if (*lwork >= *n * *n + max(i__2,bdspac)) {

/*                 Sufficient workspace for a fast algorithm */

		    ir = 1;
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *lda * *n + *n;
		    if (*lwork >= max(i__2,i__3) + *lda * *n) {

/*                    WORK(IU) is LDA by N, WORK(IR) is LDA by N */

			ldwrku = *lda;
			ldwrkr = *lda;
		    } else /* if(complicated condition) */ {
/* Computing MAX */
			i__2 = wrkbl, i__3 = *lda * *n + *n;
			if (*lwork >= max(i__2,i__3) + *n * *n) {

/*                    WORK(IU) is LDA by N, WORK(IR) is N by N */

			    ldwrku = *lda;
			    ldwrkr = *n;
			} else {

/*                    WORK(IU) is LDWRKU by N, WORK(IR) is N by N */

			    ldwrku = (*lwork - *n * *n - *n) / *n;
			    ldwrkr = *n;
			}
		    }
		    itau = ir + ldwrkr * *n;
		    iwork = itau + *n;

/*                 Compute A=Q*R */
/*                 (Workspace: need N*N+2*N, prefer N*N+N+N*NB) */

		    i__2 = *lwork - iwork + 1;
		    dgeqrf_(m, n, &a[a_offset], lda, &work[itau], &work[iwork]
, &i__2, &ierr);

/*                 Copy R to WORK(IR) and zero out below it */

		    dlacpy_("U", n, n, &a[a_offset], lda, &work[ir], &ldwrkr);
		    i__2 = *n - 1;
		    i__3 = *n - 1;
		    dlaset_("L", &i__2, &i__3, &c_b421, &c_b421, &work[ir + 1]
, &ldwrkr);

/*                 Generate Q in A */
/*                 (Workspace: need N*N+2*N, prefer N*N+N+N*NB) */

		    i__2 = *lwork - iwork + 1;
		    dorgqr_(m, n, n, &a[a_offset], lda, &work[itau], &work[
			    iwork], &i__2, &ierr);
		    ie = itau;
		    itauq = ie + *n;
		    itaup = itauq + *n;
		    iwork = itaup + *n;

/*                 Bidiagonalize R in WORK(IR) */
/*                 (Workspace: need N*N+4*N, prefer N*N+3*N+2*N*NB) */

		    i__2 = *lwork - iwork + 1;
		    dgebrd_(n, n, &work[ir], &ldwrkr, &s[1], &work[ie], &work[
			    itauq], &work[itaup], &work[iwork], &i__2, &ierr);

/*                 Generate left vectors bidiagonalizing R */
/*                 (Workspace: need N*N+4*N, prefer N*N+3*N+N*NB) */

		    i__2 = *lwork - iwork + 1;
		    dorgbr_("Q", n, n, n, &work[ir], &ldwrkr, &work[itauq], &
			    work[iwork], &i__2, &ierr);
		    iwork = ie + *n;

/*                 Perform bidiagonal QR iteration, computing left */
/*                 singular vectors of R in WORK(IR) */
/*                 (Workspace: need N*N+BDSPAC) */

		    dbdsqr_("U", n, &c__0, n, &c__0, &s[1], &work[ie], dum, &
			    c__1, &work[ir], &ldwrkr, dum, &c__1, &work[iwork]
, info);
		    iu = ie + *n;

/*                 Multiply Q in A by left singular vectors of R in */
/*                 WORK(IR), storing result in WORK(IU) and copying to A */
/*                 (Workspace: need N*N+2*N, prefer N*N+M*N+N) */

		    i__2 = *m;
		    i__3 = ldwrku;
		    for (i__ = 1; i__3 < 0 ? i__ >= i__2 : i__ <= i__2; i__ +=
			     i__3) {
/* Computing MIN */
			i__4 = *m - i__ + 1;
			chunk = min(i__4,ldwrku);
			dgemm_("N", "N", &chunk, n, n, &c_b443, &a[i__ +
				a_dim1], lda, &work[ir], &ldwrkr, &c_b421, &
				work[iu], &ldwrku);
			dlacpy_("F", &chunk, n, &work[iu], &ldwrku, &a[i__ +
				a_dim1], lda);
/* L10: */
		    }

		} else {

/*                 Insufficient workspace for a fast algorithm */

		    ie = 1;
		    itauq = ie + *n;
		    itaup = itauq + *n;
		    iwork = itaup + *n;

/*                 Bidiagonalize A */
/*                 (Workspace: need 3*N+M, prefer 3*N+(M+N)*NB) */

		    i__3 = *lwork - iwork + 1;
		    dgebrd_(m, n, &a[a_offset], lda, &s[1], &work[ie], &work[
			    itauq], &work[itaup], &work[iwork], &i__3, &ierr);

/*                 Generate left vectors bidiagonalizing A */
/*                 (Workspace: need 4*N, prefer 3*N+N*NB) */

		    i__3 = *lwork - iwork + 1;
		    dorgbr_("Q", m, n, n, &a[a_offset], lda, &work[itauq], &
			    work[iwork], &i__3, &ierr);
		    iwork = ie + *n;

/*                 Perform bidiagonal QR iteration, computing left */
/*                 singular vectors of A in A */
/*                 (Workspace: need BDSPAC) */

		    dbdsqr_("U", n, &c__0, m, &c__0, &s[1], &work[ie], dum, &
			    c__1, &a[a_offset], lda, dum, &c__1, &work[iwork],
			     info);

		}

	    } else if (wntuo && wntvas) {

/*              Path 3 (M much larger than N, JOBU='O', JOBVT='S' or 'A') */
/*              N left singular vectors to be overwritten on A and */
/*              N right singular vectors to be computed in VT */

/* Computing MAX */
		i__3 = *n << 2;
		if (*lwork >= *n * *n + max(i__3,bdspac)) {

/*                 Sufficient workspace for a fast algorithm */

		    ir = 1;
/* Computing MAX */
		    i__3 = wrkbl, i__2 = *lda * *n + *n;
		    if (*lwork >= max(i__3,i__2) + *lda * *n) {

/*                    WORK(IU) is LDA by N and WORK(IR) is LDA by N */

			ldwrku = *lda;
			ldwrkr = *lda;
		    } else /* if(complicated condition) */ {
/* Computing MAX */
			i__3 = wrkbl, i__2 = *lda * *n + *n;
			if (*lwork >= max(i__3,i__2) + *n * *n) {

/*                    WORK(IU) is LDA by N and WORK(IR) is N by N */

			    ldwrku = *lda;
			    ldwrkr = *n;
			} else {

/*                    WORK(IU) is LDWRKU by N and WORK(IR) is N by N */

			    ldwrku = (*lwork - *n * *n - *n) / *n;
			    ldwrkr = *n;
			}
		    }
		    itau = ir + ldwrkr * *n;
		    iwork = itau + *n;

/*                 Compute A=Q*R */
/*                 (Workspace: need N*N+2*N, prefer N*N+N+N*NB) */

		    i__3 = *lwork - iwork + 1;
		    dgeqrf_(m, n, &a[a_offset], lda, &work[itau], &work[iwork]
, &i__3, &ierr);

/*                 Copy R to VT, zeroing out below it */

		    dlacpy_("U", n, n, &a[a_offset], lda, &vt[vt_offset],
			    ldvt);
		    if (*n > 1) {
			i__3 = *n - 1;
			i__2 = *n - 1;
			dlaset_("L", &i__3, &i__2, &c_b421, &c_b421, &vt[
				vt_dim1 + 2], ldvt);
		    }

/*                 Generate Q in A */
/*                 (Workspace: need N*N+2*N, prefer N*N+N+N*NB) */

		    i__3 = *lwork - iwork + 1;
		    dorgqr_(m, n, n, &a[a_offset], lda, &work[itau], &work[
			    iwork], &i__3, &ierr);
		    ie = itau;
		    itauq = ie + *n;
		    itaup = itauq + *n;
		    iwork = itaup + *n;

/*                 Bidiagonalize R in VT, copying result to WORK(IR) */
/*                 (Workspace: need N*N+4*N, prefer N*N+3*N+2*N*NB) */

		    i__3 = *lwork - iwork + 1;
		    dgebrd_(n, n, &vt[vt_offset], ldvt, &s[1], &work[ie], &
			    work[itauq], &work[itaup], &work[iwork], &i__3, &
			    ierr);
		    dlacpy_("L", n, n, &vt[vt_offset], ldvt, &work[ir], &
			    ldwrkr);

/*                 Generate left vectors bidiagonalizing R in WORK(IR) */
/*                 (Workspace: need N*N+4*N, prefer N*N+3*N+N*NB) */

		    i__3 = *lwork - iwork + 1;
		    dorgbr_("Q", n, n, n, &work[ir], &ldwrkr, &work[itauq], &
			    work[iwork], &i__3, &ierr);

/*                 Generate right vectors bidiagonalizing R in VT */
/*                 (Workspace: need N*N+4*N-1, prefer N*N+3*N+(N-1)*NB) */

		    i__3 = *lwork - iwork + 1;
		    dorgbr_("P", n, n, n, &vt[vt_offset], ldvt, &work[itaup],
			    &work[iwork], &i__3, &ierr);
		    iwork = ie + *n;

/*                 Perform bidiagonal QR iteration, computing left */
/*                 singular vectors of R in WORK(IR) and computing right */
/*                 singular vectors of R in VT */
/*                 (Workspace: need N*N+BDSPAC) */

		    dbdsqr_("U", n, n, n, &c__0, &s[1], &work[ie], &vt[
			    vt_offset], ldvt, &work[ir], &ldwrkr, dum, &c__1,
			    &work[iwork], info);
		    iu = ie + *n;

/*                 Multiply Q in A by left singular vectors of R in */
/*                 WORK(IR), storing result in WORK(IU) and copying to A */
/*                 (Workspace: need N*N+2*N, prefer N*N+M*N+N) */

		    i__3 = *m;
		    i__2 = ldwrku;
		    for (i__ = 1; i__2 < 0 ? i__ >= i__3 : i__ <= i__3; i__ +=
			     i__2) {
/* Computing MIN */
			i__4 = *m - i__ + 1;
			chunk = min(i__4,ldwrku);
			dgemm_("N", "N", &chunk, n, n, &c_b443, &a[i__ +
				a_dim1], lda, &work[ir], &ldwrkr, &c_b421, &
				work[iu], &ldwrku);
			dlacpy_("F", &chunk, n, &work[iu], &ldwrku, &a[i__ +
				a_dim1], lda);
/* L20: */
		    }

		} else {

/*                 Insufficient workspace for a fast algorithm */

		    itau = 1;
		    iwork = itau + *n;

/*                 Compute A=Q*R */
/*                 (Workspace: need 2*N, prefer N+N*NB) */

		    i__2 = *lwork - iwork + 1;
		    dgeqrf_(m, n, &a[a_offset], lda, &work[itau], &work[iwork]
, &i__2, &ierr);

/*                 Copy R to VT, zeroing out below it */

		    dlacpy_("U", n, n, &a[a_offset], lda, &vt[vt_offset],
			    ldvt);
		    if (*n > 1) {
			i__2 = *n - 1;
			i__3 = *n - 1;
			dlaset_("L", &i__2, &i__3, &c_b421, &c_b421, &vt[
				vt_dim1 + 2], ldvt);
		    }

/*                 Generate Q in A */
/*                 (Workspace: need 2*N, prefer N+N*NB) */

		    i__2 = *lwork - iwork + 1;
		    dorgqr_(m, n, n, &a[a_offset], lda, &work[itau], &work[
			    iwork], &i__2, &ierr);
		    ie = itau;
		    itauq = ie + *n;
		    itaup = itauq + *n;
		    iwork = itaup + *n;

/*                 Bidiagonalize R in VT */
/*                 (Workspace: need 4*N, prefer 3*N+2*N*NB) */

		    i__2 = *lwork - iwork + 1;
		    dgebrd_(n, n, &vt[vt_offset], ldvt, &s[1], &work[ie], &
			    work[itauq], &work[itaup], &work[iwork], &i__2, &
			    ierr);

/*                 Multiply Q in A by left vectors bidiagonalizing R */
/*                 (Workspace: need 3*N+M, prefer 3*N+M*NB) */

		    i__2 = *lwork - iwork + 1;
		    dormbr_("Q", "R", "N", m, n, n, &vt[vt_offset], ldvt, &
			    work[itauq], &a[a_offset], lda, &work[iwork], &
			    i__2, &ierr);

/*                 Generate right vectors bidiagonalizing R in VT */
/*                 (Workspace: need 4*N-1, prefer 3*N+(N-1)*NB) */

		    i__2 = *lwork - iwork + 1;
		    dorgbr_("P", n, n, n, &vt[vt_offset], ldvt, &work[itaup],
			    &work[iwork], &i__2, &ierr);
		    iwork = ie + *n;

/*                 Perform bidiagonal QR iteration, computing left */
/*                 singular vectors of A in A and computing right */
/*                 singular vectors of A in VT */
/*                 (Workspace: need BDSPAC) */

		    dbdsqr_("U", n, n, m, &c__0, &s[1], &work[ie], &vt[
			    vt_offset], ldvt, &a[a_offset], lda, dum, &c__1, &
			    work[iwork], info);

		}

	    } else if (wntus) {

		if (wntvn) {

/*                 Path 4 (M much larger than N, JOBU='S', JOBVT='N') */
/*                 N left singular vectors to be computed in U and */
/*                 no right singular vectors to be computed */

/* Computing MAX */
		    i__2 = *n << 2;
		    if (*lwork >= *n * *n + max(i__2,bdspac)) {

/*                    Sufficient workspace for a fast algorithm */

			ir = 1;
			if (*lwork >= wrkbl + *lda * *n) {

/*                       WORK(IR) is LDA by N */

			    ldwrkr = *lda;
			} else {

/*                       WORK(IR) is N by N */

			    ldwrkr = *n;
			}
			itau = ir + ldwrkr * *n;
			iwork = itau + *n;

/*                    Compute A=Q*R */
/*                    (Workspace: need N*N+2*N, prefer N*N+N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dgeqrf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);

/*                    Copy R to WORK(IR), zeroing out below it */

			dlacpy_("U", n, n, &a[a_offset], lda, &work[ir], &
				ldwrkr);
			i__2 = *n - 1;
			i__3 = *n - 1;
			dlaset_("L", &i__2, &i__3, &c_b421, &c_b421, &work[ir
				+ 1], &ldwrkr);

/*                    Generate Q in A */
/*                    (Workspace: need N*N+2*N, prefer N*N+N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dorgqr_(m, n, n, &a[a_offset], lda, &work[itau], &
				work[iwork], &i__2, &ierr);
			ie = itau;
			itauq = ie + *n;
			itaup = itauq + *n;
			iwork = itaup + *n;

/*                    Bidiagonalize R in WORK(IR) */
/*                    (Workspace: need N*N+4*N, prefer N*N+3*N+2*N*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(n, n, &work[ir], &ldwrkr, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);

/*                    Generate left vectors bidiagonalizing R in WORK(IR) */
/*                    (Workspace: need N*N+4*N, prefer N*N+3*N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("Q", n, n, n, &work[ir], &ldwrkr, &work[itauq]
, &work[iwork], &i__2, &ierr);
			iwork = ie + *n;

/*                    Perform bidiagonal QR iteration, computing left */
/*                    singular vectors of R in WORK(IR) */
/*                    (Workspace: need N*N+BDSPAC) */

			dbdsqr_("U", n, &c__0, n, &c__0, &s[1], &work[ie],
				dum, &c__1, &work[ir], &ldwrkr, dum, &c__1, &
				work[iwork], info);

/*                    Multiply Q in A by left singular vectors of R in */
/*                    WORK(IR), storing result in U */
/*                    (Workspace: need N*N) */

			dgemm_("N", "N", m, n, n, &c_b443, &a[a_offset], lda,
				&work[ir], &ldwrkr, &c_b421, &u[u_offset],
				ldu);

		    } else {

/*                    Insufficient workspace for a fast algorithm */

			itau = 1;
			iwork = itau + *n;

/*                    Compute A=Q*R, copying result to U */
/*                    (Workspace: need 2*N, prefer N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dgeqrf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);
			dlacpy_("L", m, n, &a[a_offset], lda, &u[u_offset],
				ldu);

/*                    Generate Q in U */
/*                    (Workspace: need 2*N, prefer N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dorgqr_(m, n, n, &u[u_offset], ldu, &work[itau], &
				work[iwork], &i__2, &ierr);
			ie = itau;
			itauq = ie + *n;
			itaup = itauq + *n;
			iwork = itaup + *n;

/*                    Zero out below R in A */

			i__2 = *n - 1;
			i__3 = *n - 1;
			dlaset_("L", &i__2, &i__3, &c_b421, &c_b421, &a[
				a_dim1 + 2], lda);

/*                    Bidiagonalize R in A */
/*                    (Workspace: need 4*N, prefer 3*N+2*N*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(n, n, &a[a_offset], lda, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);

/*                    Multiply Q in U by left vectors bidiagonalizing R */
/*                    (Workspace: need 3*N+M, prefer 3*N+M*NB) */

			i__2 = *lwork - iwork + 1;
			dormbr_("Q", "R", "N", m, n, n, &a[a_offset], lda, &
				work[itauq], &u[u_offset], ldu, &work[iwork],
				&i__2, &ierr)
				;
			iwork = ie + *n;

/*                    Perform bidiagonal QR iteration, computing left */
/*                    singular vectors of A in U */
/*                    (Workspace: need BDSPAC) */

			dbdsqr_("U", n, &c__0, m, &c__0, &s[1], &work[ie],
				dum, &c__1, &u[u_offset], ldu, dum, &c__1, &
				work[iwork], info);

		    }

		} else if (wntvo) {

/*                 Path 5 (M much larger than N, JOBU='S', JOBVT='O') */
/*                 N left singular vectors to be computed in U and */
/*                 N right singular vectors to be overwritten on A */

/* Computing MAX */
		    i__2 = *n << 2;
		    if (*lwork >= (*n << 1) * *n + max(i__2,bdspac)) {

/*                    Sufficient workspace for a fast algorithm */

			iu = 1;
			if (*lwork >= wrkbl + (*lda << 1) * *n) {

/*                       WORK(IU) is LDA by N and WORK(IR) is LDA by N */

			    ldwrku = *lda;
			    ir = iu + ldwrku * *n;
			    ldwrkr = *lda;
			} else if (*lwork >= wrkbl + (*lda + *n) * *n) {

/*                       WORK(IU) is LDA by N and WORK(IR) is N by N */

			    ldwrku = *lda;
			    ir = iu + ldwrku * *n;
			    ldwrkr = *n;
			} else {

/*                       WORK(IU) is N by N and WORK(IR) is N by N */

			    ldwrku = *n;
			    ir = iu + ldwrku * *n;
			    ldwrkr = *n;
			}
			itau = ir + ldwrkr * *n;
			iwork = itau + *n;

/*                    Compute A=Q*R */
/*                    (Workspace: need 2*N*N+2*N, prefer 2*N*N+N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dgeqrf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);

/*                    Copy R to WORK(IU), zeroing out below it */

			dlacpy_("U", n, n, &a[a_offset], lda, &work[iu], &
				ldwrku);
			i__2 = *n - 1;
			i__3 = *n - 1;
			dlaset_("L", &i__2, &i__3, &c_b421, &c_b421, &work[iu
				+ 1], &ldwrku);

/*                    Generate Q in A */
/*                    (Workspace: need 2*N*N+2*N, prefer 2*N*N+N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dorgqr_(m, n, n, &a[a_offset], lda, &work[itau], &
				work[iwork], &i__2, &ierr);
			ie = itau;
			itauq = ie + *n;
			itaup = itauq + *n;
			iwork = itaup + *n;

/*                    Bidiagonalize R in WORK(IU), copying result to */
/*                    WORK(IR) */
/*                    (Workspace: need 2*N*N+4*N, */
/*                                prefer 2*N*N+3*N+2*N*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(n, n, &work[iu], &ldwrku, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);
			dlacpy_("U", n, n, &work[iu], &ldwrku, &work[ir], &
				ldwrkr);

/*                    Generate left bidiagonalizing vectors in WORK(IU) */
/*                    (Workspace: need 2*N*N+4*N, prefer 2*N*N+3*N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("Q", n, n, n, &work[iu], &ldwrku, &work[itauq]
, &work[iwork], &i__2, &ierr);

/*                    Generate right bidiagonalizing vectors in WORK(IR) */
/*                    (Workspace: need 2*N*N+4*N-1, */
/*                                prefer 2*N*N+3*N+(N-1)*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("P", n, n, n, &work[ir], &ldwrkr, &work[itaup]
, &work[iwork], &i__2, &ierr);
			iwork = ie + *n;

/*                    Perform bidiagonal QR iteration, computing left */
/*                    singular vectors of R in WORK(IU) and computing */
/*                    right singular vectors of R in WORK(IR) */
/*                    (Workspace: need 2*N*N+BDSPAC) */

			dbdsqr_("U", n, n, n, &c__0, &s[1], &work[ie], &work[
				ir], &ldwrkr, &work[iu], &ldwrku, dum, &c__1,
				&work[iwork], info);

/*                    Multiply Q in A by left singular vectors of R in */
/*                    WORK(IU), storing result in U */
/*                    (Workspace: need N*N) */

			dgemm_("N", "N", m, n, n, &c_b443, &a[a_offset], lda,
				&work[iu], &ldwrku, &c_b421, &u[u_offset],
				ldu);

/*                    Copy right singular vectors of R to A */
/*                    (Workspace: need N*N) */

			dlacpy_("F", n, n, &work[ir], &ldwrkr, &a[a_offset],
				lda);

		    } else {

/*                    Insufficient workspace for a fast algorithm */

			itau = 1;
			iwork = itau + *n;

/*                    Compute A=Q*R, copying result to U */
/*                    (Workspace: need 2*N, prefer N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dgeqrf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);
			dlacpy_("L", m, n, &a[a_offset], lda, &u[u_offset],
				ldu);

/*                    Generate Q in U */
/*                    (Workspace: need 2*N, prefer N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dorgqr_(m, n, n, &u[u_offset], ldu, &work[itau], &
				work[iwork], &i__2, &ierr);
			ie = itau;
			itauq = ie + *n;
			itaup = itauq + *n;
			iwork = itaup + *n;

/*                    Zero out below R in A */

			i__2 = *n - 1;
			i__3 = *n - 1;
			dlaset_("L", &i__2, &i__3, &c_b421, &c_b421, &a[
				a_dim1 + 2], lda);

/*                    Bidiagonalize R in A */
/*                    (Workspace: need 4*N, prefer 3*N+2*N*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(n, n, &a[a_offset], lda, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);

/*                    Multiply Q in U by left vectors bidiagonalizing R */
/*                    (Workspace: need 3*N+M, prefer 3*N+M*NB) */

			i__2 = *lwork - iwork + 1;
			dormbr_("Q", "R", "N", m, n, n, &a[a_offset], lda, &
				work[itauq], &u[u_offset], ldu, &work[iwork],
				&i__2, &ierr)
				;

/*                    Generate right vectors bidiagonalizing R in A */
/*                    (Workspace: need 4*N-1, prefer 3*N+(N-1)*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("P", n, n, n, &a[a_offset], lda, &work[itaup],
				 &work[iwork], &i__2, &ierr);
			iwork = ie + *n;

/*                    Perform bidiagonal QR iteration, computing left */
/*                    singular vectors of A in U and computing right */
/*                    singular vectors of A in A */
/*                    (Workspace: need BDSPAC) */

			dbdsqr_("U", n, n, m, &c__0, &s[1], &work[ie], &a[
				a_offset], lda, &u[u_offset], ldu, dum, &c__1,
				 &work[iwork], info);

		    }

		} else if (wntvas) {

/*                 Path 6 (M much larger than N, JOBU='S', JOBVT='S' */
/*                         or 'A') */
/*                 N left singular vectors to be computed in U and */
/*                 N right singular vectors to be computed in VT */

/* Computing MAX */
		    i__2 = *n << 2;
		    if (*lwork >= *n * *n + max(i__2,bdspac)) {

/*                    Sufficient workspace for a fast algorithm */

			iu = 1;
			if (*lwork >= wrkbl + *lda * *n) {

/*                       WORK(IU) is LDA by N */

			    ldwrku = *lda;
			} else {

/*                       WORK(IU) is N by N */

			    ldwrku = *n;
			}
			itau = iu + ldwrku * *n;
			iwork = itau + *n;

/*                    Compute A=Q*R */
/*                    (Workspace: need N*N+2*N, prefer N*N+N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dgeqrf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);

/*                    Copy R to WORK(IU), zeroing out below it */

			dlacpy_("U", n, n, &a[a_offset], lda, &work[iu], &
				ldwrku);
			i__2 = *n - 1;
			i__3 = *n - 1;
			dlaset_("L", &i__2, &i__3, &c_b421, &c_b421, &work[iu
				+ 1], &ldwrku);

/*                    Generate Q in A */
/*                    (Workspace: need N*N+2*N, prefer N*N+N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dorgqr_(m, n, n, &a[a_offset], lda, &work[itau], &
				work[iwork], &i__2, &ierr);
			ie = itau;
			itauq = ie + *n;
			itaup = itauq + *n;
			iwork = itaup + *n;

/*                    Bidiagonalize R in WORK(IU), copying result to VT */
/*                    (Workspace: need N*N+4*N, prefer N*N+3*N+2*N*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(n, n, &work[iu], &ldwrku, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);
			dlacpy_("U", n, n, &work[iu], &ldwrku, &vt[vt_offset],
				 ldvt);

/*                    Generate left bidiagonalizing vectors in WORK(IU) */
/*                    (Workspace: need N*N+4*N, prefer N*N+3*N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("Q", n, n, n, &work[iu], &ldwrku, &work[itauq]
, &work[iwork], &i__2, &ierr);

/*                    Generate right bidiagonalizing vectors in VT */
/*                    (Workspace: need N*N+4*N-1, */
/*                                prefer N*N+3*N+(N-1)*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("P", n, n, n, &vt[vt_offset], ldvt, &work[
				itaup], &work[iwork], &i__2, &ierr)
				;
			iwork = ie + *n;

/*                    Perform bidiagonal QR iteration, computing left */
/*                    singular vectors of R in WORK(IU) and computing */
/*                    right singular vectors of R in VT */
/*                    (Workspace: need N*N+BDSPAC) */

			dbdsqr_("U", n, n, n, &c__0, &s[1], &work[ie], &vt[
				vt_offset], ldvt, &work[iu], &ldwrku, dum, &
				c__1, &work[iwork], info);

/*                    Multiply Q in A by left singular vectors of R in */
/*                    WORK(IU), storing result in U */
/*                    (Workspace: need N*N) */

			dgemm_("N", "N", m, n, n, &c_b443, &a[a_offset], lda,
				&work[iu], &ldwrku, &c_b421, &u[u_offset],
				ldu);

		    } else {

/*                    Insufficient workspace for a fast algorithm */

			itau = 1;
			iwork = itau + *n;

/*                    Compute A=Q*R, copying result to U */
/*                    (Workspace: need 2*N, prefer N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dgeqrf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);
			dlacpy_("L", m, n, &a[a_offset], lda, &u[u_offset],
				ldu);

/*                    Generate Q in U */
/*                    (Workspace: need 2*N, prefer N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dorgqr_(m, n, n, &u[u_offset], ldu, &work[itau], &
				work[iwork], &i__2, &ierr);

/*                    Copy R to VT, zeroing out below it */

			dlacpy_("U", n, n, &a[a_offset], lda, &vt[vt_offset],
				ldvt);
			if (*n > 1) {
			    i__2 = *n - 1;
			    i__3 = *n - 1;
			    dlaset_("L", &i__2, &i__3, &c_b421, &c_b421, &vt[
				    vt_dim1 + 2], ldvt);
			}
			ie = itau;
			itauq = ie + *n;
			itaup = itauq + *n;
			iwork = itaup + *n;

/*                    Bidiagonalize R in VT */
/*                    (Workspace: need 4*N, prefer 3*N+2*N*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(n, n, &vt[vt_offset], ldvt, &s[1], &work[ie],
				&work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);

/*                    Multiply Q in U by left bidiagonalizing vectors */
/*                    in VT */
/*                    (Workspace: need 3*N+M, prefer 3*N+M*NB) */

			i__2 = *lwork - iwork + 1;
			dormbr_("Q", "R", "N", m, n, n, &vt[vt_offset], ldvt,
				&work[itauq], &u[u_offset], ldu, &work[iwork],
				 &i__2, &ierr);

/*                    Generate right bidiagonalizing vectors in VT */
/*                    (Workspace: need 4*N-1, prefer 3*N+(N-1)*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("P", n, n, n, &vt[vt_offset], ldvt, &work[
				itaup], &work[iwork], &i__2, &ierr)
				;
			iwork = ie + *n;

/*                    Perform bidiagonal QR iteration, computing left */
/*                    singular vectors of A in U and computing right */
/*                    singular vectors of A in VT */
/*                    (Workspace: need BDSPAC) */

			dbdsqr_("U", n, n, m, &c__0, &s[1], &work[ie], &vt[
				vt_offset], ldvt, &u[u_offset], ldu, dum, &
				c__1, &work[iwork], info);

		    }

		}

	    } else if (wntua) {

		if (wntvn) {

/*                 Path 7 (M much larger than N, JOBU='A', JOBVT='N') */
/*                 M left singular vectors to be computed in U and */
/*                 no right singular vectors to be computed */

/* Computing MAX */
		    i__2 = *n + *m, i__3 = *n << 2, i__2 = max(i__2,i__3);
		    if (*lwork >= *n * *n + max(i__2,bdspac)) {

/*                    Sufficient workspace for a fast algorithm */

			ir = 1;
			if (*lwork >= wrkbl + *lda * *n) {

/*                       WORK(IR) is LDA by N */

			    ldwrkr = *lda;
			} else {

/*                       WORK(IR) is N by N */

			    ldwrkr = *n;
			}
			itau = ir + ldwrkr * *n;
			iwork = itau + *n;

/*                    Compute A=Q*R, copying result to U */
/*                    (Workspace: need N*N+2*N, prefer N*N+N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dgeqrf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);
			dlacpy_("L", m, n, &a[a_offset], lda, &u[u_offset],
				ldu);

/*                    Copy R to WORK(IR), zeroing out below it */

			dlacpy_("U", n, n, &a[a_offset], lda, &work[ir], &
				ldwrkr);
			i__2 = *n - 1;
			i__3 = *n - 1;
			dlaset_("L", &i__2, &i__3, &c_b421, &c_b421, &work[ir
				+ 1], &ldwrkr);

/*                    Generate Q in U */
/*                    (Workspace: need N*N+N+M, prefer N*N+N+M*NB) */

			i__2 = *lwork - iwork + 1;
			dorgqr_(m, m, n, &u[u_offset], ldu, &work[itau], &
				work[iwork], &i__2, &ierr);
			ie = itau;
			itauq = ie + *n;
			itaup = itauq + *n;
			iwork = itaup + *n;

/*                    Bidiagonalize R in WORK(IR) */
/*                    (Workspace: need N*N+4*N, prefer N*N+3*N+2*N*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(n, n, &work[ir], &ldwrkr, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);

/*                    Generate left bidiagonalizing vectors in WORK(IR) */
/*                    (Workspace: need N*N+4*N, prefer N*N+3*N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("Q", n, n, n, &work[ir], &ldwrkr, &work[itauq]
, &work[iwork], &i__2, &ierr);
			iwork = ie + *n;

/*                    Perform bidiagonal QR iteration, computing left */
/*                    singular vectors of R in WORK(IR) */
/*                    (Workspace: need N*N+BDSPAC) */

			dbdsqr_("U", n, &c__0, n, &c__0, &s[1], &work[ie],
				dum, &c__1, &work[ir], &ldwrkr, dum, &c__1, &
				work[iwork], info);

/*                    Multiply Q in U by left singular vectors of R in */
/*                    WORK(IR), storing result in A */
/*                    (Workspace: need N*N) */

			dgemm_("N", "N", m, n, n, &c_b443, &u[u_offset], ldu,
				&work[ir], &ldwrkr, &c_b421, &a[a_offset],
				lda);

/*                    Copy left singular vectors of A from A to U */

			dlacpy_("F", m, n, &a[a_offset], lda, &u[u_offset],
				ldu);

		    } else {

/*                    Insufficient workspace for a fast algorithm */

			itau = 1;
			iwork = itau + *n;

/*                    Compute A=Q*R, copying result to U */
/*                    (Workspace: need 2*N, prefer N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dgeqrf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);
			dlacpy_("L", m, n, &a[a_offset], lda, &u[u_offset],
				ldu);

/*                    Generate Q in U */
/*                    (Workspace: need N+M, prefer N+M*NB) */

			i__2 = *lwork - iwork + 1;
			dorgqr_(m, m, n, &u[u_offset], ldu, &work[itau], &
				work[iwork], &i__2, &ierr);
			ie = itau;
			itauq = ie + *n;
			itaup = itauq + *n;
			iwork = itaup + *n;

/*                    Zero out below R in A */

			i__2 = *n - 1;
			i__3 = *n - 1;
			dlaset_("L", &i__2, &i__3, &c_b421, &c_b421, &a[
				a_dim1 + 2], lda);

/*                    Bidiagonalize R in A */
/*                    (Workspace: need 4*N, prefer 3*N+2*N*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(n, n, &a[a_offset], lda, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);

/*                    Multiply Q in U by left bidiagonalizing vectors */
/*                    in A */
/*                    (Workspace: need 3*N+M, prefer 3*N+M*NB) */

			i__2 = *lwork - iwork + 1;
			dormbr_("Q", "R", "N", m, n, n, &a[a_offset], lda, &
				work[itauq], &u[u_offset], ldu, &work[iwork],
				&i__2, &ierr)
				;
			iwork = ie + *n;

/*                    Perform bidiagonal QR iteration, computing left */
/*                    singular vectors of A in U */
/*                    (Workspace: need BDSPAC) */

			dbdsqr_("U", n, &c__0, m, &c__0, &s[1], &work[ie],
				dum, &c__1, &u[u_offset], ldu, dum, &c__1, &
				work[iwork], info);

		    }

		} else if (wntvo) {

/*                 Path 8 (M much larger than N, JOBU='A', JOBVT='O') */
/*                 M left singular vectors to be computed in U and */
/*                 N right singular vectors to be overwritten on A */

/* Computing MAX */
		    i__2 = *n + *m, i__3 = *n << 2, i__2 = max(i__2,i__3);
		    if (*lwork >= (*n << 1) * *n + max(i__2,bdspac)) {

/*                    Sufficient workspace for a fast algorithm */

			iu = 1;
			if (*lwork >= wrkbl + (*lda << 1) * *n) {

/*                       WORK(IU) is LDA by N and WORK(IR) is LDA by N */

			    ldwrku = *lda;
			    ir = iu + ldwrku * *n;
			    ldwrkr = *lda;
			} else if (*lwork >= wrkbl + (*lda + *n) * *n) {

/*                       WORK(IU) is LDA by N and WORK(IR) is N by N */

			    ldwrku = *lda;
			    ir = iu + ldwrku * *n;
			    ldwrkr = *n;
			} else {

/*                       WORK(IU) is N by N and WORK(IR) is N by N */

			    ldwrku = *n;
			    ir = iu + ldwrku * *n;
			    ldwrkr = *n;
			}
			itau = ir + ldwrkr * *n;
			iwork = itau + *n;

/*                    Compute A=Q*R, copying result to U */
/*                    (Workspace: need 2*N*N+2*N, prefer 2*N*N+N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dgeqrf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);
			dlacpy_("L", m, n, &a[a_offset], lda, &u[u_offset],
				ldu);

/*                    Generate Q in U */
/*                    (Workspace: need 2*N*N+N+M, prefer 2*N*N+N+M*NB) */

			i__2 = *lwork - iwork + 1;
			dorgqr_(m, m, n, &u[u_offset], ldu, &work[itau], &
				work[iwork], &i__2, &ierr);

/*                    Copy R to WORK(IU), zeroing out below it */

			dlacpy_("U", n, n, &a[a_offset], lda, &work[iu], &
				ldwrku);
			i__2 = *n - 1;
			i__3 = *n - 1;
			dlaset_("L", &i__2, &i__3, &c_b421, &c_b421, &work[iu
				+ 1], &ldwrku);
			ie = itau;
			itauq = ie + *n;
			itaup = itauq + *n;
			iwork = itaup + *n;

/*                    Bidiagonalize R in WORK(IU), copying result to */
/*                    WORK(IR) */
/*                    (Workspace: need 2*N*N+4*N, */
/*                                prefer 2*N*N+3*N+2*N*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(n, n, &work[iu], &ldwrku, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);
			dlacpy_("U", n, n, &work[iu], &ldwrku, &work[ir], &
				ldwrkr);

/*                    Generate left bidiagonalizing vectors in WORK(IU) */
/*                    (Workspace: need 2*N*N+4*N, prefer 2*N*N+3*N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("Q", n, n, n, &work[iu], &ldwrku, &work[itauq]
, &work[iwork], &i__2, &ierr);

/*                    Generate right bidiagonalizing vectors in WORK(IR) */
/*                    (Workspace: need 2*N*N+4*N-1, */
/*                                prefer 2*N*N+3*N+(N-1)*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("P", n, n, n, &work[ir], &ldwrkr, &work[itaup]
, &work[iwork], &i__2, &ierr);
			iwork = ie + *n;

/*                    Perform bidiagonal QR iteration, computing left */
/*                    singular vectors of R in WORK(IU) and computing */
/*                    right singular vectors of R in WORK(IR) */
/*                    (Workspace: need 2*N*N+BDSPAC) */

			dbdsqr_("U", n, n, n, &c__0, &s[1], &work[ie], &work[
				ir], &ldwrkr, &work[iu], &ldwrku, dum, &c__1,
				&work[iwork], info);

/*                    Multiply Q in U by left singular vectors of R in */
/*                    WORK(IU), storing result in A */
/*                    (Workspace: need N*N) */

			dgemm_("N", "N", m, n, n, &c_b443, &u[u_offset], ldu,
				&work[iu], &ldwrku, &c_b421, &a[a_offset],
				lda);

/*                    Copy left singular vectors of A from A to U */

			dlacpy_("F", m, n, &a[a_offset], lda, &u[u_offset],
				ldu);

/*                    Copy right singular vectors of R from WORK(IR) to A */

			dlacpy_("F", n, n, &work[ir], &ldwrkr, &a[a_offset],
				lda);

		    } else {

/*                    Insufficient workspace for a fast algorithm */

			itau = 1;
			iwork = itau + *n;

/*                    Compute A=Q*R, copying result to U */
/*                    (Workspace: need 2*N, prefer N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dgeqrf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);
			dlacpy_("L", m, n, &a[a_offset], lda, &u[u_offset],
				ldu);

/*                    Generate Q in U */
/*                    (Workspace: need N+M, prefer N+M*NB) */

			i__2 = *lwork - iwork + 1;
			dorgqr_(m, m, n, &u[u_offset], ldu, &work[itau], &
				work[iwork], &i__2, &ierr);
			ie = itau;
			itauq = ie + *n;
			itaup = itauq + *n;
			iwork = itaup + *n;

/*                    Zero out below R in A */

			i__2 = *n - 1;
			i__3 = *n - 1;
			dlaset_("L", &i__2, &i__3, &c_b421, &c_b421, &a[
				a_dim1 + 2], lda);

/*                    Bidiagonalize R in A */
/*                    (Workspace: need 4*N, prefer 3*N+2*N*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(n, n, &a[a_offset], lda, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);

/*                    Multiply Q in U by left bidiagonalizing vectors */
/*                    in A */
/*                    (Workspace: need 3*N+M, prefer 3*N+M*NB) */

			i__2 = *lwork - iwork + 1;
			dormbr_("Q", "R", "N", m, n, n, &a[a_offset], lda, &
				work[itauq], &u[u_offset], ldu, &work[iwork],
				&i__2, &ierr)
				;

/*                    Generate right bidiagonalizing vectors in A */
/*                    (Workspace: need 4*N-1, prefer 3*N+(N-1)*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("P", n, n, n, &a[a_offset], lda, &work[itaup],
				 &work[iwork], &i__2, &ierr);
			iwork = ie + *n;

/*                    Perform bidiagonal QR iteration, computing left */
/*                    singular vectors of A in U and computing right */
/*                    singular vectors of A in A */
/*                    (Workspace: need BDSPAC) */

			dbdsqr_("U", n, n, m, &c__0, &s[1], &work[ie], &a[
				a_offset], lda, &u[u_offset], ldu, dum, &c__1,
				 &work[iwork], info);

		    }

		} else if (wntvas) {

/*                 Path 9 (M much larger than N, JOBU='A', JOBVT='S' */
/*                         or 'A') */
/*                 M left singular vectors to be computed in U and */
/*                 N right singular vectors to be computed in VT */

/* Computing MAX */
		    i__2 = *n + *m, i__3 = *n << 2, i__2 = max(i__2,i__3);
		    if (*lwork >= *n * *n + max(i__2,bdspac)) {

/*                    Sufficient workspace for a fast algorithm */

			iu = 1;
			if (*lwork >= wrkbl + *lda * *n) {

/*                       WORK(IU) is LDA by N */

			    ldwrku = *lda;
			} else {

/*                       WORK(IU) is N by N */

			    ldwrku = *n;
			}
			itau = iu + ldwrku * *n;
			iwork = itau + *n;

/*                    Compute A=Q*R, copying result to U */
/*                    (Workspace: need N*N+2*N, prefer N*N+N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dgeqrf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);
			dlacpy_("L", m, n, &a[a_offset], lda, &u[u_offset],
				ldu);

/*                    Generate Q in U */
/*                    (Workspace: need N*N+N+M, prefer N*N+N+M*NB) */

			i__2 = *lwork - iwork + 1;
			dorgqr_(m, m, n, &u[u_offset], ldu, &work[itau], &
				work[iwork], &i__2, &ierr);

/*                    Copy R to WORK(IU), zeroing out below it */

			dlacpy_("U", n, n, &a[a_offset], lda, &work[iu], &
				ldwrku);
			i__2 = *n - 1;
			i__3 = *n - 1;
			dlaset_("L", &i__2, &i__3, &c_b421, &c_b421, &work[iu
				+ 1], &ldwrku);
			ie = itau;
			itauq = ie + *n;
			itaup = itauq + *n;
			iwork = itaup + *n;

/*                    Bidiagonalize R in WORK(IU), copying result to VT */
/*                    (Workspace: need N*N+4*N, prefer N*N+3*N+2*N*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(n, n, &work[iu], &ldwrku, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);
			dlacpy_("U", n, n, &work[iu], &ldwrku, &vt[vt_offset],
				 ldvt);

/*                    Generate left bidiagonalizing vectors in WORK(IU) */
/*                    (Workspace: need N*N+4*N, prefer N*N+3*N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("Q", n, n, n, &work[iu], &ldwrku, &work[itauq]
, &work[iwork], &i__2, &ierr);

/*                    Generate right bidiagonalizing vectors in VT */
/*                    (Workspace: need N*N+4*N-1, */
/*                                prefer N*N+3*N+(N-1)*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("P", n, n, n, &vt[vt_offset], ldvt, &work[
				itaup], &work[iwork], &i__2, &ierr)
				;
			iwork = ie + *n;

/*                    Perform bidiagonal QR iteration, computing left */
/*                    singular vectors of R in WORK(IU) and computing */
/*                    right singular vectors of R in VT */
/*                    (Workspace: need N*N+BDSPAC) */

			dbdsqr_("U", n, n, n, &c__0, &s[1], &work[ie], &vt[
				vt_offset], ldvt, &work[iu], &ldwrku, dum, &
				c__1, &work[iwork], info);

/*                    Multiply Q in U by left singular vectors of R in */
/*                    WORK(IU), storing result in A */
/*                    (Workspace: need N*N) */

			dgemm_("N", "N", m, n, n, &c_b443, &u[u_offset], ldu,
				&work[iu], &ldwrku, &c_b421, &a[a_offset],
				lda);

/*                    Copy left singular vectors of A from A to U */

			dlacpy_("F", m, n, &a[a_offset], lda, &u[u_offset],
				ldu);

		    } else {

/*                    Insufficient workspace for a fast algorithm */

			itau = 1;
			iwork = itau + *n;

/*                    Compute A=Q*R, copying result to U */
/*                    (Workspace: need 2*N, prefer N+N*NB) */

			i__2 = *lwork - iwork + 1;
			dgeqrf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);
			dlacpy_("L", m, n, &a[a_offset], lda, &u[u_offset],
				ldu);

/*                    Generate Q in U */
/*                    (Workspace: need N+M, prefer N+M*NB) */

			i__2 = *lwork - iwork + 1;
			dorgqr_(m, m, n, &u[u_offset], ldu, &work[itau], &
				work[iwork], &i__2, &ierr);

/*                    Copy R from A to VT, zeroing out below it */

			dlacpy_("U", n, n, &a[a_offset], lda, &vt[vt_offset],
				ldvt);
			if (*n > 1) {
			    i__2 = *n - 1;
			    i__3 = *n - 1;
			    dlaset_("L", &i__2, &i__3, &c_b421, &c_b421, &vt[
				    vt_dim1 + 2], ldvt);
			}
			ie = itau;
			itauq = ie + *n;
			itaup = itauq + *n;
			iwork = itaup + *n;

/*                    Bidiagonalize R in VT */
/*                    (Workspace: need 4*N, prefer 3*N+2*N*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(n, n, &vt[vt_offset], ldvt, &s[1], &work[ie],
				&work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);

/*                    Multiply Q in U by left bidiagonalizing vectors */
/*                    in VT */
/*                    (Workspace: need 3*N+M, prefer 3*N+M*NB) */

			i__2 = *lwork - iwork + 1;
			dormbr_("Q", "R", "N", m, n, n, &vt[vt_offset], ldvt,
				&work[itauq], &u[u_offset], ldu, &work[iwork],
				 &i__2, &ierr);

/*                    Generate right bidiagonalizing vectors in VT */
/*                    (Workspace: need 4*N-1, prefer 3*N+(N-1)*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("P", n, n, n, &vt[vt_offset], ldvt, &work[
				itaup], &work[iwork], &i__2, &ierr)
				;
			iwork = ie + *n;

/*                    Perform bidiagonal QR iteration, computing left */
/*                    singular vectors of A in U and computing right */
/*                    singular vectors of A in VT */
/*                    (Workspace: need BDSPAC) */

			dbdsqr_("U", n, n, m, &c__0, &s[1], &work[ie], &vt[
				vt_offset], ldvt, &u[u_offset], ldu, dum, &
				c__1, &work[iwork], info);

		    }

		}

	    }

	} else {

/*           M .LT. MNTHR */

/*           Path 10 (M at least N, but not much larger) */
/*           Reduce to bidiagonal form without QR decomposition */

	    ie = 1;
	    itauq = ie + *n;
	    itaup = itauq + *n;
	    iwork = itaup + *n;

/*           Bidiagonalize A */
/*           (Workspace: need 3*N+M, prefer 3*N+(M+N)*NB) */

	    i__2 = *lwork - iwork + 1;
	    dgebrd_(m, n, &a[a_offset], lda, &s[1], &work[ie], &work[itauq], &
		    work[itaup], &work[iwork], &i__2, &ierr);
	    if (wntuas) {

/*              If left singular vectors desired in U, copy result to U */
/*              and generate left bidiagonalizing vectors in U */
/*              (Workspace: need 3*N+NCU, prefer 3*N+NCU*NB) */

		dlacpy_("L", m, n, &a[a_offset], lda, &u[u_offset], ldu);
		if (wntus) {
		    ncu = *n;
		}
		if (wntua) {
		    ncu = *m;
		}
		i__2 = *lwork - iwork + 1;
		dorgbr_("Q", m, &ncu, n, &u[u_offset], ldu, &work[itauq], &
			work[iwork], &i__2, &ierr);
	    }
	    if (wntvas) {

/*              If right singular vectors desired in VT, copy result to */
/*              VT and generate right bidiagonalizing vectors in VT */
/*              (Workspace: need 4*N-1, prefer 3*N+(N-1)*NB) */

		dlacpy_("U", n, n, &a[a_offset], lda, &vt[vt_offset], ldvt);
		i__2 = *lwork - iwork + 1;
		dorgbr_("P", n, n, n, &vt[vt_offset], ldvt, &work[itaup], &
			work[iwork], &i__2, &ierr);
	    }
	    if (wntuo) {

/*              If left singular vectors desired in A, generate left */
/*              bidiagonalizing vectors in A */
/*              (Workspace: need 4*N, prefer 3*N+N*NB) */

		i__2 = *lwork - iwork + 1;
		dorgbr_("Q", m, n, n, &a[a_offset], lda, &work[itauq], &work[
			iwork], &i__2, &ierr);
	    }
	    if (wntvo) {

/*              If right singular vectors desired in A, generate right */
/*              bidiagonalizing vectors in A */
/*              (Workspace: need 4*N-1, prefer 3*N+(N-1)*NB) */

		i__2 = *lwork - iwork + 1;
		dorgbr_("P", n, n, n, &a[a_offset], lda, &work[itaup], &work[
			iwork], &i__2, &ierr);
	    }
	    iwork = ie + *n;
	    if (wntuas || wntuo) {
		nru = *m;
	    }
	    if (wntun) {
		nru = 0;
	    }
	    if (wntvas || wntvo) {
		ncvt = *n;
	    }
	    if (wntvn) {
		ncvt = 0;
	    }
	    if (! wntuo && ! wntvo) {

/*              Perform bidiagonal QR iteration, if desired, computing */
/*              left singular vectors in U and computing right singular */
/*              vectors in VT */
/*              (Workspace: need BDSPAC) */

		dbdsqr_("U", n, &ncvt, &nru, &c__0, &s[1], &work[ie], &vt[
			vt_offset], ldvt, &u[u_offset], ldu, dum, &c__1, &
			work[iwork], info);
	    } else if (! wntuo && wntvo) {

/*              Perform bidiagonal QR iteration, if desired, computing */
/*              left singular vectors in U and computing right singular */
/*              vectors in A */
/*              (Workspace: need BDSPAC) */

		dbdsqr_("U", n, &ncvt, &nru, &c__0, &s[1], &work[ie], &a[
			a_offset], lda, &u[u_offset], ldu, dum, &c__1, &work[
			iwork], info);
	    } else {

/*              Perform bidiagonal QR iteration, if desired, computing */
/*              left singular vectors in A and computing right singular */
/*              vectors in VT */
/*              (Workspace: need BDSPAC) */

		dbdsqr_("U", n, &ncvt, &nru, &c__0, &s[1], &work[ie], &vt[
			vt_offset], ldvt, &a[a_offset], lda, dum, &c__1, &
			work[iwork], info);
	    }

	}

    } else {

/*        A has more columns than rows. If A has sufficiently more */
/*        columns than rows, first reduce using the LQ decomposition (if */
/*        sufficient workspace available) */

	if (*n >= mnthr) {

	    if (wntvn) {

/*              Path 1t(N much larger than M, JOBVT='N') */
/*              No right singular vectors to be computed */

		itau = 1;
		iwork = itau + *m;

/*              Compute A=L*Q */
/*              (Workspace: need 2*M, prefer M+M*NB) */

		i__2 = *lwork - iwork + 1;
		dgelqf_(m, n, &a[a_offset], lda, &work[itau], &work[iwork], &
			i__2, &ierr);

/*              Zero out above L */

		i__2 = *m - 1;
		i__3 = *m - 1;
		dlaset_("U", &i__2, &i__3, &c_b421, &c_b421, &a[(a_dim1 << 1)
			+ 1], lda);
		ie = 1;
		itauq = ie + *m;
		itaup = itauq + *m;
		iwork = itaup + *m;

/*              Bidiagonalize L in A */
/*              (Workspace: need 4*M, prefer 3*M+2*M*NB) */

		i__2 = *lwork - iwork + 1;
		dgebrd_(m, m, &a[a_offset], lda, &s[1], &work[ie], &work[
			itauq], &work[itaup], &work[iwork], &i__2, &ierr);
		if (wntuo || wntuas) {

/*                 If left singular vectors desired, generate Q */
/*                 (Workspace: need 4*M, prefer 3*M+M*NB) */

		    i__2 = *lwork - iwork + 1;
		    dorgbr_("Q", m, m, m, &a[a_offset], lda, &work[itauq], &
			    work[iwork], &i__2, &ierr);
		}
		iwork = ie + *m;
		nru = 0;
		if (wntuo || wntuas) {
		    nru = *m;
		}

/*              Perform bidiagonal QR iteration, computing left singular */
/*              vectors of A in A if desired */
/*              (Workspace: need BDSPAC) */

		dbdsqr_("U", m, &c__0, &nru, &c__0, &s[1], &work[ie], dum, &
			c__1, &a[a_offset], lda, dum, &c__1, &work[iwork],
			info);

/*              If left singular vectors desired in U, copy them there */

		if (wntuas) {
		    dlacpy_("F", m, m, &a[a_offset], lda, &u[u_offset], ldu);
		}

	    } else if (wntvo && wntun) {

/*              Path 2t(N much larger than M, JOBU='N', JOBVT='O') */
/*              M right singular vectors to be overwritten on A and */
/*              no left singular vectors to be computed */

/* Computing MAX */
		i__2 = *m << 2;
		if (*lwork >= *m * *m + max(i__2,bdspac)) {

/*                 Sufficient workspace for a fast algorithm */

		    ir = 1;
/* Computing MAX */
		    i__2 = wrkbl, i__3 = *lda * *n + *m;
		    if (*lwork >= max(i__2,i__3) + *lda * *m) {

/*                    WORK(IU) is LDA by N and WORK(IR) is LDA by M */

			ldwrku = *lda;
			chunk = *n;
			ldwrkr = *lda;
		    } else /* if(complicated condition) */ {
/* Computing MAX */
			i__2 = wrkbl, i__3 = *lda * *n + *m;
			if (*lwork >= max(i__2,i__3) + *m * *m) {

/*                    WORK(IU) is LDA by N and WORK(IR) is M by M */

			    ldwrku = *lda;
			    chunk = *n;
			    ldwrkr = *m;
			} else {

/*                    WORK(IU) is M by CHUNK and WORK(IR) is M by M */

			    ldwrku = *m;
			    chunk = (*lwork - *m * *m - *m) / *m;
			    ldwrkr = *m;
			}
		    }
		    itau = ir + ldwrkr * *m;
		    iwork = itau + *m;

/*                 Compute A=L*Q */
/*                 (Workspace: need M*M+2*M, prefer M*M+M+M*NB) */

		    i__2 = *lwork - iwork + 1;
		    dgelqf_(m, n, &a[a_offset], lda, &work[itau], &work[iwork]
, &i__2, &ierr);

/*                 Copy L to WORK(IR) and zero out above it */

		    dlacpy_("L", m, m, &a[a_offset], lda, &work[ir], &ldwrkr);
		    i__2 = *m - 1;
		    i__3 = *m - 1;
		    dlaset_("U", &i__2, &i__3, &c_b421, &c_b421, &work[ir +
			    ldwrkr], &ldwrkr);

/*                 Generate Q in A */
/*                 (Workspace: need M*M+2*M, prefer M*M+M+M*NB) */

		    i__2 = *lwork - iwork + 1;
		    dorglq_(m, n, m, &a[a_offset], lda, &work[itau], &work[
			    iwork], &i__2, &ierr);
		    ie = itau;
		    itauq = ie + *m;
		    itaup = itauq + *m;
		    iwork = itaup + *m;

/*                 Bidiagonalize L in WORK(IR) */
/*                 (Workspace: need M*M+4*M, prefer M*M+3*M+2*M*NB) */

		    i__2 = *lwork - iwork + 1;
		    dgebrd_(m, m, &work[ir], &ldwrkr, &s[1], &work[ie], &work[
			    itauq], &work[itaup], &work[iwork], &i__2, &ierr);

/*                 Generate right vectors bidiagonalizing L */
/*                 (Workspace: need M*M+4*M-1, prefer M*M+3*M+(M-1)*NB) */

		    i__2 = *lwork - iwork + 1;
		    dorgbr_("P", m, m, m, &work[ir], &ldwrkr, &work[itaup], &
			    work[iwork], &i__2, &ierr);
		    iwork = ie + *m;

/*                 Perform bidiagonal QR iteration, computing right */
/*                 singular vectors of L in WORK(IR) */
/*                 (Workspace: need M*M+BDSPAC) */

		    dbdsqr_("U", m, m, &c__0, &c__0, &s[1], &work[ie], &work[
			    ir], &ldwrkr, dum, &c__1, dum, &c__1, &work[iwork]
, info);
		    iu = ie + *m;

/*                 Multiply right singular vectors of L in WORK(IR) by Q */
/*                 in A, storing result in WORK(IU) and copying to A */
/*                 (Workspace: need M*M+2*M, prefer M*M+M*N+M) */

		    i__2 = *n;
		    i__3 = chunk;
		    for (i__ = 1; i__3 < 0 ? i__ >= i__2 : i__ <= i__2; i__ +=
			     i__3) {
/* Computing MIN */
			i__4 = *n - i__ + 1;
			blk = min(i__4,chunk);
			dgemm_("N", "N", m, &blk, m, &c_b443, &work[ir], &
				ldwrkr, &a[i__ * a_dim1 + 1], lda, &c_b421, &
				work[iu], &ldwrku);
			dlacpy_("F", m, &blk, &work[iu], &ldwrku, &a[i__ *
				a_dim1 + 1], lda);
/* L30: */
		    }

		} else {

/*                 Insufficient workspace for a fast algorithm */

		    ie = 1;
		    itauq = ie + *m;
		    itaup = itauq + *m;
		    iwork = itaup + *m;

/*                 Bidiagonalize A */
/*                 (Workspace: need 3*M+N, prefer 3*M+(M+N)*NB) */

		    i__3 = *lwork - iwork + 1;
		    dgebrd_(m, n, &a[a_offset], lda, &s[1], &work[ie], &work[
			    itauq], &work[itaup], &work[iwork], &i__3, &ierr);

/*                 Generate right vectors bidiagonalizing A */
/*                 (Workspace: need 4*M, prefer 3*M+M*NB) */

		    i__3 = *lwork - iwork + 1;
		    dorgbr_("P", m, n, m, &a[a_offset], lda, &work[itaup], &
			    work[iwork], &i__3, &ierr);
		    iwork = ie + *m;

/*                 Perform bidiagonal QR iteration, computing right */
/*                 singular vectors of A in A */
/*                 (Workspace: need BDSPAC) */

		    dbdsqr_("L", m, n, &c__0, &c__0, &s[1], &work[ie], &a[
			    a_offset], lda, dum, &c__1, dum, &c__1, &work[
			    iwork], info);

		}

	    } else if (wntvo && wntuas) {

/*              Path 3t(N much larger than M, JOBU='S' or 'A', JOBVT='O') */
/*              M right singular vectors to be overwritten on A and */
/*              M left singular vectors to be computed in U */

/* Computing MAX */
		i__3 = *m << 2;
		if (*lwork >= *m * *m + max(i__3,bdspac)) {

/*                 Sufficient workspace for a fast algorithm */

		    ir = 1;
/* Computing MAX */
		    i__3 = wrkbl, i__2 = *lda * *n + *m;
		    if (*lwork >= max(i__3,i__2) + *lda * *m) {

/*                    WORK(IU) is LDA by N and WORK(IR) is LDA by M */

			ldwrku = *lda;
			chunk = *n;
			ldwrkr = *lda;
		    } else /* if(complicated condition) */ {
/* Computing MAX */
			i__3 = wrkbl, i__2 = *lda * *n + *m;
			if (*lwork >= max(i__3,i__2) + *m * *m) {

/*                    WORK(IU) is LDA by N and WORK(IR) is M by M */

			    ldwrku = *lda;
			    chunk = *n;
			    ldwrkr = *m;
			} else {

/*                    WORK(IU) is M by CHUNK and WORK(IR) is M by M */

			    ldwrku = *m;
			    chunk = (*lwork - *m * *m - *m) / *m;
			    ldwrkr = *m;
			}
		    }
		    itau = ir + ldwrkr * *m;
		    iwork = itau + *m;

/*                 Compute A=L*Q */
/*                 (Workspace: need M*M+2*M, prefer M*M+M+M*NB) */

		    i__3 = *lwork - iwork + 1;
		    dgelqf_(m, n, &a[a_offset], lda, &work[itau], &work[iwork]
, &i__3, &ierr);

/*                 Copy L to U, zeroing about above it */

		    dlacpy_("L", m, m, &a[a_offset], lda, &u[u_offset], ldu);
		    i__3 = *m - 1;
		    i__2 = *m - 1;
		    dlaset_("U", &i__3, &i__2, &c_b421, &c_b421, &u[(u_dim1 <<
			     1) + 1], ldu);

/*                 Generate Q in A */
/*                 (Workspace: need M*M+2*M, prefer M*M+M+M*NB) */

		    i__3 = *lwork - iwork + 1;
		    dorglq_(m, n, m, &a[a_offset], lda, &work[itau], &work[
			    iwork], &i__3, &ierr);
		    ie = itau;
		    itauq = ie + *m;
		    itaup = itauq + *m;
		    iwork = itaup + *m;

/*                 Bidiagonalize L in U, copying result to WORK(IR) */
/*                 (Workspace: need M*M+4*M, prefer M*M+3*M+2*M*NB) */

		    i__3 = *lwork - iwork + 1;
		    dgebrd_(m, m, &u[u_offset], ldu, &s[1], &work[ie], &work[
			    itauq], &work[itaup], &work[iwork], &i__3, &ierr);
		    dlacpy_("U", m, m, &u[u_offset], ldu, &work[ir], &ldwrkr);

/*                 Generate right vectors bidiagonalizing L in WORK(IR) */
/*                 (Workspace: need M*M+4*M-1, prefer M*M+3*M+(M-1)*NB) */

		    i__3 = *lwork - iwork + 1;
		    dorgbr_("P", m, m, m, &work[ir], &ldwrkr, &work[itaup], &
			    work[iwork], &i__3, &ierr);

/*                 Generate left vectors bidiagonalizing L in U */
/*                 (Workspace: need M*M+4*M, prefer M*M+3*M+M*NB) */

		    i__3 = *lwork - iwork + 1;
		    dorgbr_("Q", m, m, m, &u[u_offset], ldu, &work[itauq], &
			    work[iwork], &i__3, &ierr);
		    iwork = ie + *m;

/*                 Perform bidiagonal QR iteration, computing left */
/*                 singular vectors of L in U, and computing right */
/*                 singular vectors of L in WORK(IR) */
/*                 (Workspace: need M*M+BDSPAC) */

		    dbdsqr_("U", m, m, m, &c__0, &s[1], &work[ie], &work[ir],
			    &ldwrkr, &u[u_offset], ldu, dum, &c__1, &work[
			    iwork], info);
		    iu = ie + *m;

/*                 Multiply right singular vectors of L in WORK(IR) by Q */
/*                 in A, storing result in WORK(IU) and copying to A */
/*                 (Workspace: need M*M+2*M, prefer M*M+M*N+M)) */

		    i__3 = *n;
		    i__2 = chunk;
		    for (i__ = 1; i__2 < 0 ? i__ >= i__3 : i__ <= i__3; i__ +=
			     i__2) {
/* Computing MIN */
			i__4 = *n - i__ + 1;
			blk = min(i__4,chunk);
			dgemm_("N", "N", m, &blk, m, &c_b443, &work[ir], &
				ldwrkr, &a[i__ * a_dim1 + 1], lda, &c_b421, &
				work[iu], &ldwrku);
			dlacpy_("F", m, &blk, &work[iu], &ldwrku, &a[i__ *
				a_dim1 + 1], lda);
/* L40: */
		    }

		} else {

/*                 Insufficient workspace for a fast algorithm */

		    itau = 1;
		    iwork = itau + *m;

/*                 Compute A=L*Q */
/*                 (Workspace: need 2*M, prefer M+M*NB) */

		    i__2 = *lwork - iwork + 1;
		    dgelqf_(m, n, &a[a_offset], lda, &work[itau], &work[iwork]
, &i__2, &ierr);

/*                 Copy L to U, zeroing out above it */

		    dlacpy_("L", m, m, &a[a_offset], lda, &u[u_offset], ldu);
		    i__2 = *m - 1;
		    i__3 = *m - 1;
		    dlaset_("U", &i__2, &i__3, &c_b421, &c_b421, &u[(u_dim1 <<
			     1) + 1], ldu);

/*                 Generate Q in A */
/*                 (Workspace: need 2*M, prefer M+M*NB) */

		    i__2 = *lwork - iwork + 1;
		    dorglq_(m, n, m, &a[a_offset], lda, &work[itau], &work[
			    iwork], &i__2, &ierr);
		    ie = itau;
		    itauq = ie + *m;
		    itaup = itauq + *m;
		    iwork = itaup + *m;

/*                 Bidiagonalize L in U */
/*                 (Workspace: need 4*M, prefer 3*M+2*M*NB) */

		    i__2 = *lwork - iwork + 1;
		    dgebrd_(m, m, &u[u_offset], ldu, &s[1], &work[ie], &work[
			    itauq], &work[itaup], &work[iwork], &i__2, &ierr);

/*                 Multiply right vectors bidiagonalizing L by Q in A */
/*                 (Workspace: need 3*M+N, prefer 3*M+N*NB) */

		    i__2 = *lwork - iwork + 1;
		    dormbr_("P", "L", "T", m, n, m, &u[u_offset], ldu, &work[
			    itaup], &a[a_offset], lda, &work[iwork], &i__2, &
			    ierr);

/*                 Generate left vectors bidiagonalizing L in U */
/*                 (Workspace: need 4*M, prefer 3*M+M*NB) */

		    i__2 = *lwork - iwork + 1;
		    dorgbr_("Q", m, m, m, &u[u_offset], ldu, &work[itauq], &
			    work[iwork], &i__2, &ierr);
		    iwork = ie + *m;

/*                 Perform bidiagonal QR iteration, computing left */
/*                 singular vectors of A in U and computing right */
/*                 singular vectors of A in A */
/*                 (Workspace: need BDSPAC) */

		    dbdsqr_("U", m, n, m, &c__0, &s[1], &work[ie], &a[
			    a_offset], lda, &u[u_offset], ldu, dum, &c__1, &
			    work[iwork], info);

		}

	    } else if (wntvs) {

		if (wntun) {

/*                 Path 4t(N much larger than M, JOBU='N', JOBVT='S') */
/*                 M right singular vectors to be computed in VT and */
/*                 no left singular vectors to be computed */

/* Computing MAX */
		    i__2 = *m << 2;
		    if (*lwork >= *m * *m + max(i__2,bdspac)) {

/*                    Sufficient workspace for a fast algorithm */

			ir = 1;
			if (*lwork >= wrkbl + *lda * *m) {

/*                       WORK(IR) is LDA by M */

			    ldwrkr = *lda;
			} else {

/*                       WORK(IR) is M by M */

			    ldwrkr = *m;
			}
			itau = ir + ldwrkr * *m;
			iwork = itau + *m;

/*                    Compute A=L*Q */
/*                    (Workspace: need M*M+2*M, prefer M*M+M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dgelqf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);

/*                    Copy L to WORK(IR), zeroing out above it */

			dlacpy_("L", m, m, &a[a_offset], lda, &work[ir], &
				ldwrkr);
			i__2 = *m - 1;
			i__3 = *m - 1;
			dlaset_("U", &i__2, &i__3, &c_b421, &c_b421, &work[ir
				+ ldwrkr], &ldwrkr);

/*                    Generate Q in A */
/*                    (Workspace: need M*M+2*M, prefer M*M+M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dorglq_(m, n, m, &a[a_offset], lda, &work[itau], &
				work[iwork], &i__2, &ierr);
			ie = itau;
			itauq = ie + *m;
			itaup = itauq + *m;
			iwork = itaup + *m;

/*                    Bidiagonalize L in WORK(IR) */
/*                    (Workspace: need M*M+4*M, prefer M*M+3*M+2*M*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(m, m, &work[ir], &ldwrkr, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);

/*                    Generate right vectors bidiagonalizing L in */
/*                    WORK(IR) */
/*                    (Workspace: need M*M+4*M, prefer M*M+3*M+(M-1)*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("P", m, m, m, &work[ir], &ldwrkr, &work[itaup]
, &work[iwork], &i__2, &ierr);
			iwork = ie + *m;

/*                    Perform bidiagonal QR iteration, computing right */
/*                    singular vectors of L in WORK(IR) */
/*                    (Workspace: need M*M+BDSPAC) */

			dbdsqr_("U", m, m, &c__0, &c__0, &s[1], &work[ie], &
				work[ir], &ldwrkr, dum, &c__1, dum, &c__1, &
				work[iwork], info);

/*                    Multiply right singular vectors of L in WORK(IR) by */
/*                    Q in A, storing result in VT */
/*                    (Workspace: need M*M) */

			dgemm_("N", "N", m, n, m, &c_b443, &work[ir], &ldwrkr,
				 &a[a_offset], lda, &c_b421, &vt[vt_offset],
				ldvt);

		    } else {

/*                    Insufficient workspace for a fast algorithm */

			itau = 1;
			iwork = itau + *m;

/*                    Compute A=L*Q */
/*                    (Workspace: need 2*M, prefer M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dgelqf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);

/*                    Copy result to VT */

			dlacpy_("U", m, n, &a[a_offset], lda, &vt[vt_offset],
				ldvt);

/*                    Generate Q in VT */
/*                    (Workspace: need 2*M, prefer M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dorglq_(m, n, m, &vt[vt_offset], ldvt, &work[itau], &
				work[iwork], &i__2, &ierr);
			ie = itau;
			itauq = ie + *m;
			itaup = itauq + *m;
			iwork = itaup + *m;

/*                    Zero out above L in A */

			i__2 = *m - 1;
			i__3 = *m - 1;
			dlaset_("U", &i__2, &i__3, &c_b421, &c_b421, &a[(
				a_dim1 << 1) + 1], lda);

/*                    Bidiagonalize L in A */
/*                    (Workspace: need 4*M, prefer 3*M+2*M*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(m, m, &a[a_offset], lda, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);

/*                    Multiply right vectors bidiagonalizing L by Q in VT */
/*                    (Workspace: need 3*M+N, prefer 3*M+N*NB) */

			i__2 = *lwork - iwork + 1;
			dormbr_("P", "L", "T", m, n, m, &a[a_offset], lda, &
				work[itaup], &vt[vt_offset], ldvt, &work[
				iwork], &i__2, &ierr);
			iwork = ie + *m;

/*                    Perform bidiagonal QR iteration, computing right */
/*                    singular vectors of A in VT */
/*                    (Workspace: need BDSPAC) */

			dbdsqr_("U", m, n, &c__0, &c__0, &s[1], &work[ie], &
				vt[vt_offset], ldvt, dum, &c__1, dum, &c__1, &
				work[iwork], info);

		    }

		} else if (wntuo) {

/*                 Path 5t(N much larger than M, JOBU='O', JOBVT='S') */
/*                 M right singular vectors to be computed in VT and */
/*                 M left singular vectors to be overwritten on A */

/* Computing MAX */
		    i__2 = *m << 2;
		    if (*lwork >= (*m << 1) * *m + max(i__2,bdspac)) {

/*                    Sufficient workspace for a fast algorithm */

			iu = 1;
			if (*lwork >= wrkbl + (*lda << 1) * *m) {

/*                       WORK(IU) is LDA by M and WORK(IR) is LDA by M */

			    ldwrku = *lda;
			    ir = iu + ldwrku * *m;
			    ldwrkr = *lda;
			} else if (*lwork >= wrkbl + (*lda + *m) * *m) {

/*                       WORK(IU) is LDA by M and WORK(IR) is M by M */

			    ldwrku = *lda;
			    ir = iu + ldwrku * *m;
			    ldwrkr = *m;
			} else {

/*                       WORK(IU) is M by M and WORK(IR) is M by M */

			    ldwrku = *m;
			    ir = iu + ldwrku * *m;
			    ldwrkr = *m;
			}
			itau = ir + ldwrkr * *m;
			iwork = itau + *m;

/*                    Compute A=L*Q */
/*                    (Workspace: need 2*M*M+2*M, prefer 2*M*M+M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dgelqf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);

/*                    Copy L to WORK(IU), zeroing out below it */

			dlacpy_("L", m, m, &a[a_offset], lda, &work[iu], &
				ldwrku);
			i__2 = *m - 1;
			i__3 = *m - 1;
			dlaset_("U", &i__2, &i__3, &c_b421, &c_b421, &work[iu
				+ ldwrku], &ldwrku);

/*                    Generate Q in A */
/*                    (Workspace: need 2*M*M+2*M, prefer 2*M*M+M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dorglq_(m, n, m, &a[a_offset], lda, &work[itau], &
				work[iwork], &i__2, &ierr);
			ie = itau;
			itauq = ie + *m;
			itaup = itauq + *m;
			iwork = itaup + *m;

/*                    Bidiagonalize L in WORK(IU), copying result to */
/*                    WORK(IR) */
/*                    (Workspace: need 2*M*M+4*M, */
/*                                prefer 2*M*M+3*M+2*M*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(m, m, &work[iu], &ldwrku, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);
			dlacpy_("L", m, m, &work[iu], &ldwrku, &work[ir], &
				ldwrkr);

/*                    Generate right bidiagonalizing vectors in WORK(IU) */
/*                    (Workspace: need 2*M*M+4*M-1, */
/*                                prefer 2*M*M+3*M+(M-1)*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("P", m, m, m, &work[iu], &ldwrku, &work[itaup]
, &work[iwork], &i__2, &ierr);

/*                    Generate left bidiagonalizing vectors in WORK(IR) */
/*                    (Workspace: need 2*M*M+4*M, prefer 2*M*M+3*M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("Q", m, m, m, &work[ir], &ldwrkr, &work[itauq]
, &work[iwork], &i__2, &ierr);
			iwork = ie + *m;

/*                    Perform bidiagonal QR iteration, computing left */
/*                    singular vectors of L in WORK(IR) and computing */
/*                    right singular vectors of L in WORK(IU) */
/*                    (Workspace: need 2*M*M+BDSPAC) */

			dbdsqr_("U", m, m, m, &c__0, &s[1], &work[ie], &work[
				iu], &ldwrku, &work[ir], &ldwrkr, dum, &c__1,
				&work[iwork], info);

/*                    Multiply right singular vectors of L in WORK(IU) by */
/*                    Q in A, storing result in VT */
/*                    (Workspace: need M*M) */

			dgemm_("N", "N", m, n, m, &c_b443, &work[iu], &ldwrku,
				 &a[a_offset], lda, &c_b421, &vt[vt_offset],
				ldvt);

/*                    Copy left singular vectors of L to A */
/*                    (Workspace: need M*M) */

			dlacpy_("F", m, m, &work[ir], &ldwrkr, &a[a_offset],
				lda);

		    } else {

/*                    Insufficient workspace for a fast algorithm */

			itau = 1;
			iwork = itau + *m;

/*                    Compute A=L*Q, copying result to VT */
/*                    (Workspace: need 2*M, prefer M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dgelqf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);
			dlacpy_("U", m, n, &a[a_offset], lda, &vt[vt_offset],
				ldvt);

/*                    Generate Q in VT */
/*                    (Workspace: need 2*M, prefer M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dorglq_(m, n, m, &vt[vt_offset], ldvt, &work[itau], &
				work[iwork], &i__2, &ierr);
			ie = itau;
			itauq = ie + *m;
			itaup = itauq + *m;
			iwork = itaup + *m;

/*                    Zero out above L in A */

			i__2 = *m - 1;
			i__3 = *m - 1;
			dlaset_("U", &i__2, &i__3, &c_b421, &c_b421, &a[(
				a_dim1 << 1) + 1], lda);

/*                    Bidiagonalize L in A */
/*                    (Workspace: need 4*M, prefer 3*M+2*M*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(m, m, &a[a_offset], lda, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);

/*                    Multiply right vectors bidiagonalizing L by Q in VT */
/*                    (Workspace: need 3*M+N, prefer 3*M+N*NB) */

			i__2 = *lwork - iwork + 1;
			dormbr_("P", "L", "T", m, n, m, &a[a_offset], lda, &
				work[itaup], &vt[vt_offset], ldvt, &work[
				iwork], &i__2, &ierr);

/*                    Generate left bidiagonalizing vectors of L in A */
/*                    (Workspace: need 4*M, prefer 3*M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("Q", m, m, m, &a[a_offset], lda, &work[itauq],
				 &work[iwork], &i__2, &ierr);
			iwork = ie + *m;

/*                    Perform bidiagonal QR iteration, compute left */
/*                    singular vectors of A in A and compute right */
/*                    singular vectors of A in VT */
/*                    (Workspace: need BDSPAC) */

			dbdsqr_("U", m, n, m, &c__0, &s[1], &work[ie], &vt[
				vt_offset], ldvt, &a[a_offset], lda, dum, &
				c__1, &work[iwork], info);

		    }

		} else if (wntuas) {

/*                 Path 6t(N much larger than M, JOBU='S' or 'A', */
/*                         JOBVT='S') */
/*                 M right singular vectors to be computed in VT and */
/*                 M left singular vectors to be computed in U */

/* Computing MAX */
		    i__2 = *m << 2;
		    if (*lwork >= *m * *m + max(i__2,bdspac)) {

/*                    Sufficient workspace for a fast algorithm */

			iu = 1;
			if (*lwork >= wrkbl + *lda * *m) {

/*                       WORK(IU) is LDA by N */

			    ldwrku = *lda;
			} else {

/*                       WORK(IU) is LDA by M */

			    ldwrku = *m;
			}
			itau = iu + ldwrku * *m;
			iwork = itau + *m;

/*                    Compute A=L*Q */
/*                    (Workspace: need M*M+2*M, prefer M*M+M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dgelqf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);

/*                    Copy L to WORK(IU), zeroing out above it */

			dlacpy_("L", m, m, &a[a_offset], lda, &work[iu], &
				ldwrku);
			i__2 = *m - 1;
			i__3 = *m - 1;
			dlaset_("U", &i__2, &i__3, &c_b421, &c_b421, &work[iu
				+ ldwrku], &ldwrku);

/*                    Generate Q in A */
/*                    (Workspace: need M*M+2*M, prefer M*M+M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dorglq_(m, n, m, &a[a_offset], lda, &work[itau], &
				work[iwork], &i__2, &ierr);
			ie = itau;
			itauq = ie + *m;
			itaup = itauq + *m;
			iwork = itaup + *m;

/*                    Bidiagonalize L in WORK(IU), copying result to U */
/*                    (Workspace: need M*M+4*M, prefer M*M+3*M+2*M*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(m, m, &work[iu], &ldwrku, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);
			dlacpy_("L", m, m, &work[iu], &ldwrku, &u[u_offset],
				ldu);

/*                    Generate right bidiagonalizing vectors in WORK(IU) */
/*                    (Workspace: need M*M+4*M-1, */
/*                                prefer M*M+3*M+(M-1)*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("P", m, m, m, &work[iu], &ldwrku, &work[itaup]
, &work[iwork], &i__2, &ierr);

/*                    Generate left bidiagonalizing vectors in U */
/*                    (Workspace: need M*M+4*M, prefer M*M+3*M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("Q", m, m, m, &u[u_offset], ldu, &work[itauq],
				 &work[iwork], &i__2, &ierr);
			iwork = ie + *m;

/*                    Perform bidiagonal QR iteration, computing left */
/*                    singular vectors of L in U and computing right */
/*                    singular vectors of L in WORK(IU) */
/*                    (Workspace: need M*M+BDSPAC) */

			dbdsqr_("U", m, m, m, &c__0, &s[1], &work[ie], &work[
				iu], &ldwrku, &u[u_offset], ldu, dum, &c__1, &
				work[iwork], info);

/*                    Multiply right singular vectors of L in WORK(IU) by */
/*                    Q in A, storing result in VT */
/*                    (Workspace: need M*M) */

			dgemm_("N", "N", m, n, m, &c_b443, &work[iu], &ldwrku,
				 &a[a_offset], lda, &c_b421, &vt[vt_offset],
				ldvt);

		    } else {

/*                    Insufficient workspace for a fast algorithm */

			itau = 1;
			iwork = itau + *m;

/*                    Compute A=L*Q, copying result to VT */
/*                    (Workspace: need 2*M, prefer M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dgelqf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);
			dlacpy_("U", m, n, &a[a_offset], lda, &vt[vt_offset],
				ldvt);

/*                    Generate Q in VT */
/*                    (Workspace: need 2*M, prefer M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dorglq_(m, n, m, &vt[vt_offset], ldvt, &work[itau], &
				work[iwork], &i__2, &ierr);

/*                    Copy L to U, zeroing out above it */

			dlacpy_("L", m, m, &a[a_offset], lda, &u[u_offset],
				ldu);
			i__2 = *m - 1;
			i__3 = *m - 1;
			dlaset_("U", &i__2, &i__3, &c_b421, &c_b421, &u[(
				u_dim1 << 1) + 1], ldu);
			ie = itau;
			itauq = ie + *m;
			itaup = itauq + *m;
			iwork = itaup + *m;

/*                    Bidiagonalize L in U */
/*                    (Workspace: need 4*M, prefer 3*M+2*M*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(m, m, &u[u_offset], ldu, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);

/*                    Multiply right bidiagonalizing vectors in U by Q */
/*                    in VT */
/*                    (Workspace: need 3*M+N, prefer 3*M+N*NB) */

			i__2 = *lwork - iwork + 1;
			dormbr_("P", "L", "T", m, n, m, &u[u_offset], ldu, &
				work[itaup], &vt[vt_offset], ldvt, &work[
				iwork], &i__2, &ierr);

/*                    Generate left bidiagonalizing vectors in U */
/*                    (Workspace: need 4*M, prefer 3*M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("Q", m, m, m, &u[u_offset], ldu, &work[itauq],
				 &work[iwork], &i__2, &ierr);
			iwork = ie + *m;

/*                    Perform bidiagonal QR iteration, computing left */
/*                    singular vectors of A in U and computing right */
/*                    singular vectors of A in VT */
/*                    (Workspace: need BDSPAC) */

			dbdsqr_("U", m, n, m, &c__0, &s[1], &work[ie], &vt[
				vt_offset], ldvt, &u[u_offset], ldu, dum, &
				c__1, &work[iwork], info);

		    }

		}

	    } else if (wntva) {

		if (wntun) {

/*                 Path 7t(N much larger than M, JOBU='N', JOBVT='A') */
/*                 N right singular vectors to be computed in VT and */
/*                 no left singular vectors to be computed */

/* Computing MAX */
		    i__2 = *n + *m, i__3 = *m << 2, i__2 = max(i__2,i__3);
		    if (*lwork >= *m * *m + max(i__2,bdspac)) {

/*                    Sufficient workspace for a fast algorithm */

			ir = 1;
			if (*lwork >= wrkbl + *lda * *m) {

/*                       WORK(IR) is LDA by M */

			    ldwrkr = *lda;
			} else {

/*                       WORK(IR) is M by M */

			    ldwrkr = *m;
			}
			itau = ir + ldwrkr * *m;
			iwork = itau + *m;

/*                    Compute A=L*Q, copying result to VT */
/*                    (Workspace: need M*M+2*M, prefer M*M+M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dgelqf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);
			dlacpy_("U", m, n, &a[a_offset], lda, &vt[vt_offset],
				ldvt);

/*                    Copy L to WORK(IR), zeroing out above it */

			dlacpy_("L", m, m, &a[a_offset], lda, &work[ir], &
				ldwrkr);
			i__2 = *m - 1;
			i__3 = *m - 1;
			dlaset_("U", &i__2, &i__3, &c_b421, &c_b421, &work[ir
				+ ldwrkr], &ldwrkr);

/*                    Generate Q in VT */
/*                    (Workspace: need M*M+M+N, prefer M*M+M+N*NB) */

			i__2 = *lwork - iwork + 1;
			dorglq_(n, n, m, &vt[vt_offset], ldvt, &work[itau], &
				work[iwork], &i__2, &ierr);
			ie = itau;
			itauq = ie + *m;
			itaup = itauq + *m;
			iwork = itaup + *m;

/*                    Bidiagonalize L in WORK(IR) */
/*                    (Workspace: need M*M+4*M, prefer M*M+3*M+2*M*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(m, m, &work[ir], &ldwrkr, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);

/*                    Generate right bidiagonalizing vectors in WORK(IR) */
/*                    (Workspace: need M*M+4*M-1, */
/*                                prefer M*M+3*M+(M-1)*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("P", m, m, m, &work[ir], &ldwrkr, &work[itaup]
, &work[iwork], &i__2, &ierr);
			iwork = ie + *m;

/*                    Perform bidiagonal QR iteration, computing right */
/*                    singular vectors of L in WORK(IR) */
/*                    (Workspace: need M*M+BDSPAC) */

			dbdsqr_("U", m, m, &c__0, &c__0, &s[1], &work[ie], &
				work[ir], &ldwrkr, dum, &c__1, dum, &c__1, &
				work[iwork], info);

/*                    Multiply right singular vectors of L in WORK(IR) by */
/*                    Q in VT, storing result in A */
/*                    (Workspace: need M*M) */

			dgemm_("N", "N", m, n, m, &c_b443, &work[ir], &ldwrkr,
				 &vt[vt_offset], ldvt, &c_b421, &a[a_offset],
				lda);

/*                    Copy right singular vectors of A from A to VT */

			dlacpy_("F", m, n, &a[a_offset], lda, &vt[vt_offset],
				ldvt);

		    } else {

/*                    Insufficient workspace for a fast algorithm */

			itau = 1;
			iwork = itau + *m;

/*                    Compute A=L*Q, copying result to VT */
/*                    (Workspace: need 2*M, prefer M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dgelqf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);
			dlacpy_("U", m, n, &a[a_offset], lda, &vt[vt_offset],
				ldvt);

/*                    Generate Q in VT */
/*                    (Workspace: need M+N, prefer M+N*NB) */

			i__2 = *lwork - iwork + 1;
			dorglq_(n, n, m, &vt[vt_offset], ldvt, &work[itau], &
				work[iwork], &i__2, &ierr);
			ie = itau;
			itauq = ie + *m;
			itaup = itauq + *m;
			iwork = itaup + *m;

/*                    Zero out above L in A */

			i__2 = *m - 1;
			i__3 = *m - 1;
			dlaset_("U", &i__2, &i__3, &c_b421, &c_b421, &a[(
				a_dim1 << 1) + 1], lda);

/*                    Bidiagonalize L in A */
/*                    (Workspace: need 4*M, prefer 3*M+2*M*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(m, m, &a[a_offset], lda, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);

/*                    Multiply right bidiagonalizing vectors in A by Q */
/*                    in VT */
/*                    (Workspace: need 3*M+N, prefer 3*M+N*NB) */

			i__2 = *lwork - iwork + 1;
			dormbr_("P", "L", "T", m, n, m, &a[a_offset], lda, &
				work[itaup], &vt[vt_offset], ldvt, &work[
				iwork], &i__2, &ierr);
			iwork = ie + *m;

/*                    Perform bidiagonal QR iteration, computing right */
/*                    singular vectors of A in VT */
/*                    (Workspace: need BDSPAC) */

			dbdsqr_("U", m, n, &c__0, &c__0, &s[1], &work[ie], &
				vt[vt_offset], ldvt, dum, &c__1, dum, &c__1, &
				work[iwork], info);

		    }

		} else if (wntuo) {

/*                 Path 8t(N much larger than M, JOBU='O', JOBVT='A') */
/*                 N right singular vectors to be computed in VT and */
/*                 M left singular vectors to be overwritten on A */

/* Computing MAX */
		    i__2 = *n + *m, i__3 = *m << 2, i__2 = max(i__2,i__3);
		    if (*lwork >= (*m << 1) * *m + max(i__2,bdspac)) {

/*                    Sufficient workspace for a fast algorithm */

			iu = 1;
			if (*lwork >= wrkbl + (*lda << 1) * *m) {

/*                       WORK(IU) is LDA by M and WORK(IR) is LDA by M */

			    ldwrku = *lda;
			    ir = iu + ldwrku * *m;
			    ldwrkr = *lda;
			} else if (*lwork >= wrkbl + (*lda + *m) * *m) {

/*                       WORK(IU) is LDA by M and WORK(IR) is M by M */

			    ldwrku = *lda;
			    ir = iu + ldwrku * *m;
			    ldwrkr = *m;
			} else {

/*                       WORK(IU) is M by M and WORK(IR) is M by M */

			    ldwrku = *m;
			    ir = iu + ldwrku * *m;
			    ldwrkr = *m;
			}
			itau = ir + ldwrkr * *m;
			iwork = itau + *m;

/*                    Compute A=L*Q, copying result to VT */
/*                    (Workspace: need 2*M*M+2*M, prefer 2*M*M+M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dgelqf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);
			dlacpy_("U", m, n, &a[a_offset], lda, &vt[vt_offset],
				ldvt);

/*                    Generate Q in VT */
/*                    (Workspace: need 2*M*M+M+N, prefer 2*M*M+M+N*NB) */

			i__2 = *lwork - iwork + 1;
			dorglq_(n, n, m, &vt[vt_offset], ldvt, &work[itau], &
				work[iwork], &i__2, &ierr);

/*                    Copy L to WORK(IU), zeroing out above it */

			dlacpy_("L", m, m, &a[a_offset], lda, &work[iu], &
				ldwrku);
			i__2 = *m - 1;
			i__3 = *m - 1;
			dlaset_("U", &i__2, &i__3, &c_b421, &c_b421, &work[iu
				+ ldwrku], &ldwrku);
			ie = itau;
			itauq = ie + *m;
			itaup = itauq + *m;
			iwork = itaup + *m;

/*                    Bidiagonalize L in WORK(IU), copying result to */
/*                    WORK(IR) */
/*                    (Workspace: need 2*M*M+4*M, */
/*                                prefer 2*M*M+3*M+2*M*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(m, m, &work[iu], &ldwrku, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);
			dlacpy_("L", m, m, &work[iu], &ldwrku, &work[ir], &
				ldwrkr);

/*                    Generate right bidiagonalizing vectors in WORK(IU) */
/*                    (Workspace: need 2*M*M+4*M-1, */
/*                                prefer 2*M*M+3*M+(M-1)*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("P", m, m, m, &work[iu], &ldwrku, &work[itaup]
, &work[iwork], &i__2, &ierr);

/*                    Generate left bidiagonalizing vectors in WORK(IR) */
/*                    (Workspace: need 2*M*M+4*M, prefer 2*M*M+3*M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("Q", m, m, m, &work[ir], &ldwrkr, &work[itauq]
, &work[iwork], &i__2, &ierr);
			iwork = ie + *m;

/*                    Perform bidiagonal QR iteration, computing left */
/*                    singular vectors of L in WORK(IR) and computing */
/*                    right singular vectors of L in WORK(IU) */
/*                    (Workspace: need 2*M*M+BDSPAC) */

			dbdsqr_("U", m, m, m, &c__0, &s[1], &work[ie], &work[
				iu], &ldwrku, &work[ir], &ldwrkr, dum, &c__1,
				&work[iwork], info);

/*                    Multiply right singular vectors of L in WORK(IU) by */
/*                    Q in VT, storing result in A */
/*                    (Workspace: need M*M) */

			dgemm_("N", "N", m, n, m, &c_b443, &work[iu], &ldwrku,
				 &vt[vt_offset], ldvt, &c_b421, &a[a_offset],
				lda);

/*                    Copy right singular vectors of A from A to VT */

			dlacpy_("F", m, n, &a[a_offset], lda, &vt[vt_offset],
				ldvt);

/*                    Copy left singular vectors of A from WORK(IR) to A */

			dlacpy_("F", m, m, &work[ir], &ldwrkr, &a[a_offset],
				lda);

		    } else {

/*                    Insufficient workspace for a fast algorithm */

			itau = 1;
			iwork = itau + *m;

/*                    Compute A=L*Q, copying result to VT */
/*                    (Workspace: need 2*M, prefer M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dgelqf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);
			dlacpy_("U", m, n, &a[a_offset], lda, &vt[vt_offset],
				ldvt);

/*                    Generate Q in VT */
/*                    (Workspace: need M+N, prefer M+N*NB) */

			i__2 = *lwork - iwork + 1;
			dorglq_(n, n, m, &vt[vt_offset], ldvt, &work[itau], &
				work[iwork], &i__2, &ierr);
			ie = itau;
			itauq = ie + *m;
			itaup = itauq + *m;
			iwork = itaup + *m;

/*                    Zero out above L in A */

			i__2 = *m - 1;
			i__3 = *m - 1;
			dlaset_("U", &i__2, &i__3, &c_b421, &c_b421, &a[(
				a_dim1 << 1) + 1], lda);

/*                    Bidiagonalize L in A */
/*                    (Workspace: need 4*M, prefer 3*M+2*M*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(m, m, &a[a_offset], lda, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);

/*                    Multiply right bidiagonalizing vectors in A by Q */
/*                    in VT */
/*                    (Workspace: need 3*M+N, prefer 3*M+N*NB) */

			i__2 = *lwork - iwork + 1;
			dormbr_("P", "L", "T", m, n, m, &a[a_offset], lda, &
				work[itaup], &vt[vt_offset], ldvt, &work[
				iwork], &i__2, &ierr);

/*                    Generate left bidiagonalizing vectors in A */
/*                    (Workspace: need 4*M, prefer 3*M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("Q", m, m, m, &a[a_offset], lda, &work[itauq],
				 &work[iwork], &i__2, &ierr);
			iwork = ie + *m;

/*                    Perform bidiagonal QR iteration, computing left */
/*                    singular vectors of A in A and computing right */
/*                    singular vectors of A in VT */
/*                    (Workspace: need BDSPAC) */

			dbdsqr_("U", m, n, m, &c__0, &s[1], &work[ie], &vt[
				vt_offset], ldvt, &a[a_offset], lda, dum, &
				c__1, &work[iwork], info);

		    }

		} else if (wntuas) {

/*                 Path 9t(N much larger than M, JOBU='S' or 'A', */
/*                         JOBVT='A') */
/*                 N right singular vectors to be computed in VT and */
/*                 M left singular vectors to be computed in U */

/* Computing MAX */
		    i__2 = *n + *m, i__3 = *m << 2, i__2 = max(i__2,i__3);
		    if (*lwork >= *m * *m + max(i__2,bdspac)) {

/*                    Sufficient workspace for a fast algorithm */

			iu = 1;
			if (*lwork >= wrkbl + *lda * *m) {

/*                       WORK(IU) is LDA by M */

			    ldwrku = *lda;
			} else {

/*                       WORK(IU) is M by M */

			    ldwrku = *m;
			}
			itau = iu + ldwrku * *m;
			iwork = itau + *m;

/*                    Compute A=L*Q, copying result to VT */
/*                    (Workspace: need M*M+2*M, prefer M*M+M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dgelqf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);
			dlacpy_("U", m, n, &a[a_offset], lda, &vt[vt_offset],
				ldvt);

/*                    Generate Q in VT */
/*                    (Workspace: need M*M+M+N, prefer M*M+M+N*NB) */

			i__2 = *lwork - iwork + 1;
			dorglq_(n, n, m, &vt[vt_offset], ldvt, &work[itau], &
				work[iwork], &i__2, &ierr);

/*                    Copy L to WORK(IU), zeroing out above it */

			dlacpy_("L", m, m, &a[a_offset], lda, &work[iu], &
				ldwrku);
			i__2 = *m - 1;
			i__3 = *m - 1;
			dlaset_("U", &i__2, &i__3, &c_b421, &c_b421, &work[iu
				+ ldwrku], &ldwrku);
			ie = itau;
			itauq = ie + *m;
			itaup = itauq + *m;
			iwork = itaup + *m;

/*                    Bidiagonalize L in WORK(IU), copying result to U */
/*                    (Workspace: need M*M+4*M, prefer M*M+3*M+2*M*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(m, m, &work[iu], &ldwrku, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);
			dlacpy_("L", m, m, &work[iu], &ldwrku, &u[u_offset],
				ldu);

/*                    Generate right bidiagonalizing vectors in WORK(IU) */
/*                    (Workspace: need M*M+4*M, prefer M*M+3*M+(M-1)*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("P", m, m, m, &work[iu], &ldwrku, &work[itaup]
, &work[iwork], &i__2, &ierr);

/*                    Generate left bidiagonalizing vectors in U */
/*                    (Workspace: need M*M+4*M, prefer M*M+3*M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("Q", m, m, m, &u[u_offset], ldu, &work[itauq],
				 &work[iwork], &i__2, &ierr);
			iwork = ie + *m;

/*                    Perform bidiagonal QR iteration, computing left */
/*                    singular vectors of L in U and computing right */
/*                    singular vectors of L in WORK(IU) */
/*                    (Workspace: need M*M+BDSPAC) */

			dbdsqr_("U", m, m, m, &c__0, &s[1], &work[ie], &work[
				iu], &ldwrku, &u[u_offset], ldu, dum, &c__1, &
				work[iwork], info);

/*                    Multiply right singular vectors of L in WORK(IU) by */
/*                    Q in VT, storing result in A */
/*                    (Workspace: need M*M) */

			dgemm_("N", "N", m, n, m, &c_b443, &work[iu], &ldwrku,
				 &vt[vt_offset], ldvt, &c_b421, &a[a_offset],
				lda);

/*                    Copy right singular vectors of A from A to VT */

			dlacpy_("F", m, n, &a[a_offset], lda, &vt[vt_offset],
				ldvt);

		    } else {

/*                    Insufficient workspace for a fast algorithm */

			itau = 1;
			iwork = itau + *m;

/*                    Compute A=L*Q, copying result to VT */
/*                    (Workspace: need 2*M, prefer M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dgelqf_(m, n, &a[a_offset], lda, &work[itau], &work[
				iwork], &i__2, &ierr);
			dlacpy_("U", m, n, &a[a_offset], lda, &vt[vt_offset],
				ldvt);

/*                    Generate Q in VT */
/*                    (Workspace: need M+N, prefer M+N*NB) */

			i__2 = *lwork - iwork + 1;
			dorglq_(n, n, m, &vt[vt_offset], ldvt, &work[itau], &
				work[iwork], &i__2, &ierr);

/*                    Copy L to U, zeroing out above it */

			dlacpy_("L", m, m, &a[a_offset], lda, &u[u_offset],
				ldu);
			i__2 = *m - 1;
			i__3 = *m - 1;
			dlaset_("U", &i__2, &i__3, &c_b421, &c_b421, &u[(
				u_dim1 << 1) + 1], ldu);
			ie = itau;
			itauq = ie + *m;
			itaup = itauq + *m;
			iwork = itaup + *m;

/*                    Bidiagonalize L in U */
/*                    (Workspace: need 4*M, prefer 3*M+2*M*NB) */

			i__2 = *lwork - iwork + 1;
			dgebrd_(m, m, &u[u_offset], ldu, &s[1], &work[ie], &
				work[itauq], &work[itaup], &work[iwork], &
				i__2, &ierr);

/*                    Multiply right bidiagonalizing vectors in U by Q */
/*                    in VT */
/*                    (Workspace: need 3*M+N, prefer 3*M+N*NB) */

			i__2 = *lwork - iwork + 1;
			dormbr_("P", "L", "T", m, n, m, &u[u_offset], ldu, &
				work[itaup], &vt[vt_offset], ldvt, &work[
				iwork], &i__2, &ierr);

/*                    Generate left bidiagonalizing vectors in U */
/*                    (Workspace: need 4*M, prefer 3*M+M*NB) */

			i__2 = *lwork - iwork + 1;
			dorgbr_("Q", m, m, m, &u[u_offset], ldu, &work[itauq],
				 &work[iwork], &i__2, &ierr);
			iwork = ie + *m;

/*                    Perform bidiagonal QR iteration, computing left */
/*                    singular vectors of A in U and computing right */
/*                    singular vectors of A in VT */
/*                    (Workspace: need BDSPAC) */

			dbdsqr_("U", m, n, m, &c__0, &s[1], &work[ie], &vt[
				vt_offset], ldvt, &u[u_offset], ldu, dum, &
				c__1, &work[iwork], info);

		    }

		}

	    }

	} else {

/*           N .LT. MNTHR */

/*           Path 10t(N greater than M, but not much larger) */
/*           Reduce to bidiagonal form without LQ decomposition */

	    ie = 1;
	    itauq = ie + *m;
	    itaup = itauq + *m;
	    iwork = itaup + *m;

/*           Bidiagonalize A */
/*           (Workspace: need 3*M+N, prefer 3*M+(M+N)*NB) */

	    i__2 = *lwork - iwork + 1;
	    dgebrd_(m, n, &a[a_offset], lda, &s[1], &work[ie], &work[itauq], &
		    work[itaup], &work[iwork], &i__2, &ierr);
	    if (wntuas) {

/*              If left singular vectors desired in U, copy result to U */
/*              and generate left bidiagonalizing vectors in U */
/*              (Workspace: need 4*M-1, prefer 3*M+(M-1)*NB) */

		dlacpy_("L", m, m, &a[a_offset], lda, &u[u_offset], ldu);
		i__2 = *lwork - iwork + 1;
		dorgbr_("Q", m, m, n, &u[u_offset], ldu, &work[itauq], &work[
			iwork], &i__2, &ierr);
	    }
	    if (wntvas) {

/*              If right singular vectors desired in VT, copy result to */
/*              VT and generate right bidiagonalizing vectors in VT */
/*              (Workspace: need 3*M+NRVT, prefer 3*M+NRVT*NB) */

		dlacpy_("U", m, n, &a[a_offset], lda, &vt[vt_offset], ldvt);
		if (wntva) {
		    nrvt = *n;
		}
		if (wntvs) {
		    nrvt = *m;
		}
		i__2 = *lwork - iwork + 1;
		dorgbr_("P", &nrvt, n, m, &vt[vt_offset], ldvt, &work[itaup],
			&work[iwork], &i__2, &ierr);
	    }
	    if (wntuo) {

/*              If left singular vectors desired in A, generate left */
/*              bidiagonalizing vectors in A */
/*              (Workspace: need 4*M-1, prefer 3*M+(M-1)*NB) */

		i__2 = *lwork - iwork + 1;
		dorgbr_("Q", m, m, n, &a[a_offset], lda, &work[itauq], &work[
			iwork], &i__2, &ierr);
	    }
	    if (wntvo) {

/*              If right singular vectors desired in A, generate right */
/*              bidiagonalizing vectors in A */
/*              (Workspace: need 4*M, prefer 3*M+M*NB) */

		i__2 = *lwork - iwork + 1;
		dorgbr_("P", m, n, m, &a[a_offset], lda, &work[itaup], &work[
			iwork], &i__2, &ierr);
	    }
	    iwork = ie + *m;
	    if (wntuas || wntuo) {
		nru = *m;
	    }
	    if (wntun) {
		nru = 0;
	    }
	    if (wntvas || wntvo) {
		ncvt = *n;
	    }
	    if (wntvn) {
		ncvt = 0;
	    }
	    if (! wntuo && ! wntvo) {

/*              Perform bidiagonal QR iteration, if desired, computing */
/*              left singular vectors in U and computing right singular */
/*              vectors in VT */
/*              (Workspace: need BDSPAC) */

		dbdsqr_("L", m, &ncvt, &nru, &c__0, &s[1], &work[ie], &vt[
			vt_offset], ldvt, &u[u_offset], ldu, dum, &c__1, &
			work[iwork], info);
	    } else if (! wntuo && wntvo) {

/*              Perform bidiagonal QR iteration, if desired, computing */
/*              left singular vectors in U and computing right singular */
/*              vectors in A */
/*              (Workspace: need BDSPAC) */

		dbdsqr_("L", m, &ncvt, &nru, &c__0, &s[1], &work[ie], &a[
			a_offset], lda, &u[u_offset], ldu, dum, &c__1, &work[
			iwork], info);
	    } else {

/*              Perform bidiagonal QR iteration, if desired, computing */
/*              left singular vectors in A and computing right singular */
/*              vectors in VT */
/*              (Workspace: need BDSPAC) */

		dbdsqr_("L", m, &ncvt, &nru, &c__0, &s[1], &work[ie], &vt[
			vt_offset], ldvt, &a[a_offset], lda, dum, &c__1, &
			work[iwork], info);
	    }

	}

    }

/*     If DBDSQR failed to converge, copy unconverged superdiagonals */
/*     to WORK( 2:MINMN ) */

    if (*info != 0) {
	if (ie > 2) {
	    i__2 = minmn - 1;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		work[i__ + 1] = work[i__ + ie - 1];
/* L50: */
	    }
	}
	if (ie < 2) {
	    for (i__ = minmn - 1; i__ >= 1; --i__) {
		work[i__ + 1] = work[i__ + ie - 1];
/* L60: */
	    }
	}
    }

/*     Undo scaling if necessary */

    if (iscl == 1) {
	if (anrm > bignum) {
	    dlascl_("G", &c__0, &c__0, &bignum, &anrm, &minmn, &c__1, &s[1], &
		    minmn, &ierr);
	}
	if (*info != 0 && anrm > bignum) {
	    i__2 = minmn - 1;
	    dlascl_("G", &c__0, &c__0, &bignum, &anrm, &i__2, &c__1, &work[2],
		     &minmn, &ierr);
	}
	if (anrm < smlnum) {
	    dlascl_("G", &c__0, &c__0, &smlnum, &anrm, &minmn, &c__1, &s[1], &
		    minmn, &ierr);
	}
	if (*info != 0 && anrm < smlnum) {
	    i__2 = minmn - 1;
	    dlascl_("G", &c__0, &c__0, &smlnum, &anrm, &i__2, &c__1, &work[2],
		     &minmn, &ierr);
	}
    }

/*     Return optimal workspace in WORK(1) */

    work[1] = (doublereal) maxwrk;

    return 0;

/*     End of DGESVD */

} /* dgesvd_ */

/* Subroutine */ int dgetf2_(integer *m, integer *n, doublereal *a, integer *
	lda, integer *ipiv, integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;
    doublereal c_b8 = -1.;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    doublereal d__1;

    /* Local variables */
    integer i__, j, jp;
    extern /* Subroutine */ int dger_(integer *, integer *, doublereal *,
	    doublereal *, integer *, doublereal *, integer *, doublereal *,
	    integer *), dscal_(integer *, doublereal *, doublereal *, integer
	    *);
    doublereal sfmin;
    extern /* Subroutine */ int dswap_(integer *, doublereal *, integer *,
	    doublereal *, integer *);
    extern doublereal dlamch_(char *);
    extern integer idamax_(integer *, doublereal *, integer *);
    extern /* Subroutine */ int xerbla_(char *, integer *);


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGETF2 computes an LU factorization of a general m-by-n matrix A */
/*  using partial pivoting with row interchanges. */

/*  The factorization has the form */
/*     A = P * L * U */
/*  where P is a permutation matrix, L is lower triangular with unit */
/*  diagonal elements (lower trapezoidal if m > n), and U is upper */
/*  triangular (upper trapezoidal if m < n). */

/*  This is the right-looking Level 2 BLAS version of the algorithm. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A.  M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A.  N >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the m by n matrix to be factored. */
/*          On exit, the factors L and U from the factorization */
/*          A = P*L*U; the unit diagonal elements of L are not stored. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,M). */

/*  IPIV    (output) INTEGER array, dimension (min(M,N)) */
/*          The pivot indices; for 1 <= i <= min(M,N), row i of the */
/*          matrix was interchanged with row IPIV(i). */

/*  INFO    (output) INTEGER */
/*          = 0: successful exit */
/*          < 0: if INFO = -k, the k-th argument had an illegal value */
/*          > 0: if INFO = k, U(k,k) is exactly zero. The factorization */
/*               has been completed, but the factor U is exactly */
/*               singular, and division by zero will occur if it is used */
/*               to solve a system of equations. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --ipiv;

    /* Function Body */
    *info = 0;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*m)) {
	*info = -4;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGETF2", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0) {
	return 0;
    }

/*     Compute machine safe minimum */

    sfmin = dlamch_("S");

    i__1 = min(*m,*n);
    for (j = 1; j <= i__1; ++j) {

/*        Find pivot and test for singularity. */

	i__2 = *m - j + 1;
	jp = j - 1 + idamax_(&i__2, &a[j + j * a_dim1], &c__1);
	ipiv[j] = jp;
	if (a[jp + j * a_dim1] != 0.) {

/*           Apply the interchange to columns 1:N. */

	    if (jp != j) {
		dswap_(n, &a[j + a_dim1], lda, &a[jp + a_dim1], lda);
	    }

/*           Compute elements J+1:M of J-th column. */

	    if (j < *m) {
		if ((d__1 = a[j + j * a_dim1], abs(d__1)) >= sfmin) {
		    i__2 = *m - j;
		    d__1 = 1. / a[j + j * a_dim1];
		    dscal_(&i__2, &d__1, &a[j + 1 + j * a_dim1], &c__1);
		} else {
		    i__2 = *m - j;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			a[j + i__ + j * a_dim1] /= a[j + j * a_dim1];
/* L20: */
		    }
		}
	    }

	} else if (*info == 0) {

	    *info = j;
	}

	if (j < min(*m,*n)) {

/*           Update trailing submatrix. */

	    i__2 = *m - j;
	    i__3 = *n - j;
	    dger_(&i__2, &i__3, &c_b8, &a[j + 1 + j * a_dim1], &c__1, &a[j + (
		    j + 1) * a_dim1], lda, &a[j + 1 + (j + 1) * a_dim1], lda);
	}
/* L10: */
    }
    return 0;

/*     End of DGETF2 */

} /* dgetf2_ */

/* Subroutine */ int dgetrf_(integer *m, integer *n, doublereal *a, integer *
	lda, integer *ipiv, integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;
    integer c_n1 = -1;
    doublereal c_b16 = 1.;
    doublereal c_b19 = -1.;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4, i__5;

    /* Local variables */
    integer i__, j, jb, nb;
    extern /* Subroutine */ int dgemm_(char *, char *, integer *, integer *,
	    integer *, doublereal *, doublereal *, integer *, doublereal *,
	    integer *, doublereal *, doublereal *, integer *);
    integer iinfo;
    extern /* Subroutine */ int dtrsm_(char *, char *, char *, char *,
	    integer *, integer *, doublereal *, doublereal *, integer *,
	    doublereal *, integer *), dgetf2_(
	    integer *, integer *, doublereal *, integer *, integer *, integer
	    *), xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *,
	    integer *, integer *);
    extern /* Subroutine */ int dlaswp_(integer *, doublereal *, integer *,
	    integer *, integer *, integer *, integer *);


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGETRF computes an LU factorization of a general M-by-N matrix A */
/*  using partial pivoting with row interchanges. */

/*  The factorization has the form */
/*     A = P * L * U */
/*  where P is a permutation matrix, L is lower triangular with unit */
/*  diagonal elements (lower trapezoidal if m > n), and U is upper */
/*  triangular (upper trapezoidal if m < n). */

/*  This is the right-looking Level 3 BLAS version of the algorithm. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A.  M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A.  N >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the M-by-N matrix to be factored. */
/*          On exit, the factors L and U from the factorization */
/*          A = P*L*U; the unit diagonal elements of L are not stored. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,M). */

/*  IPIV    (output) INTEGER array, dimension (min(M,N)) */
/*          The pivot indices; for 1 <= i <= min(M,N), row i of the */
/*          matrix was interchanged with row IPIV(i). */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */
/*          > 0:  if INFO = i, U(i,i) is exactly zero. The factorization */
/*                has been completed, but the factor U is exactly */
/*                singular, and division by zero will occur if it is used */
/*                to solve a system of equations. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --ipiv;

    /* Function Body */
    *info = 0;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*m)) {
	*info = -4;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGETRF", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0) {
	return 0;
    }

/*     Determine the block size for this environment. */

    nb = ilaenv_(&c__1, "DGETRF", " ", m, n, &c_n1, &c_n1);
    if (nb <= 1 || nb >= min(*m,*n)) {

/*        Use unblocked code. */

	dgetf2_(m, n, &a[a_offset], lda, &ipiv[1], info);
    } else {

/*        Use blocked code. */

	i__1 = min(*m,*n);
	i__2 = nb;
	for (j = 1; i__2 < 0 ? j >= i__1 : j <= i__1; j += i__2) {
/* Computing MIN */
	    i__3 = min(*m,*n) - j + 1;
	    jb = min(i__3,nb);

/*           Factor diagonal and subdiagonal blocks and test for exact */
/*           singularity. */

	    i__3 = *m - j + 1;
	    dgetf2_(&i__3, &jb, &a[j + j * a_dim1], lda, &ipiv[j], &iinfo);

/*           Adjust INFO and the pivot indices. */

	    if (*info == 0 && iinfo > 0) {
		*info = iinfo + j - 1;
	    }
/* Computing MIN */
	    i__4 = *m, i__5 = j + jb - 1;
	    i__3 = min(i__4,i__5);
	    for (i__ = j; i__ <= i__3; ++i__) {
		ipiv[i__] = j - 1 + ipiv[i__];
/* L10: */
	    }

/*           Apply interchanges to columns 1:J-1. */

	    i__3 = j - 1;
	    i__4 = j + jb - 1;
	    dlaswp_(&i__3, &a[a_offset], lda, &j, &i__4, &ipiv[1], &c__1);

	    if (j + jb <= *n) {

/*              Apply interchanges to columns J+JB:N. */

		i__3 = *n - j - jb + 1;
		i__4 = j + jb - 1;
		dlaswp_(&i__3, &a[(j + jb) * a_dim1 + 1], lda, &j, &i__4, &
			ipiv[1], &c__1);

/*              Compute block row of U. */

		i__3 = *n - j - jb + 1;
		dtrsm_("Left", "Lower", "No transpose", "Unit", &jb, &i__3, &
			c_b16, &a[j + j * a_dim1], lda, &a[j + (j + jb) *
			a_dim1], lda);
		if (j + jb <= *m) {

/*                 Update trailing submatrix. */

		    i__3 = *m - j - jb + 1;
		    i__4 = *n - j - jb + 1;
		    dgemm_("No transpose", "No transpose", &i__3, &i__4, &jb,
			    &c_b19, &a[j + jb + j * a_dim1], lda, &a[j + (j +
			    jb) * a_dim1], lda, &c_b16, &a[j + jb + (j + jb) *
			     a_dim1], lda);
		}
	    }
/* L20: */
	}
    }
    return 0;

/*     End of DGETRF */

} /* dgetrf_ */

/* Subroutine */ int dgetrs_(char *trans, integer *n, integer *nrhs,
	doublereal *a, integer *lda, integer *ipiv, doublereal *b, integer *
	ldb, integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;
    doublereal c_b12 = 1.;
    integer c_n1 = -1;

    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, i__1;

    /* Local variables */
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int dtrsm_(char *, char *, char *, char *,
	    integer *, integer *, doublereal *, doublereal *, integer *,
	    doublereal *, integer *), xerbla_(
	    char *, integer *), dlaswp_(integer *, doublereal *,
	    integer *, integer *, integer *, integer *, integer *);
    logical notran;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGETRS solves a system of linear equations */
/*     A * X = B  or  A' * X = B */
/*  with a general N-by-N matrix A using the LU factorization computed */
/*  by DGETRF. */

/*  Arguments */
/*  ========= */

/*  TRANS   (input) CHARACTER*1 */
/*          Specifies the form of the system of equations: */
/*          = 'N':  A * X = B  (No transpose) */
/*          = 'T':  A'* X = B  (Transpose) */
/*          = 'C':  A'* X = B  (Conjugate transpose = Transpose) */

/*  N       (input) INTEGER */
/*          The order of the matrix A.  N >= 0. */

/*  NRHS    (input) INTEGER */
/*          The number of right hand sides, i.e., the number of columns */
/*          of the matrix B.  NRHS >= 0. */

/*  A       (input) DOUBLE PRECISION array, dimension (LDA,N) */
/*          The factors L and U from the factorization A = P*L*U */
/*          as computed by DGETRF. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,N). */

/*  IPIV    (input) INTEGER array, dimension (N) */
/*          The pivot indices from DGETRF; for 1<=i<=N, row i of the */
/*          matrix was interchanged with row IPIV(i). */

/*  B       (input/output) DOUBLE PRECISION array, dimension (LDB,NRHS) */
/*          On entry, the right hand side matrix B. */
/*          On exit, the solution matrix X. */

/*  LDB     (input) INTEGER */
/*          The leading dimension of the array B.  LDB >= max(1,N). */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --ipiv;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;

    /* Function Body */
    *info = 0;
    notran = lsame_(trans, "N");
    if (! notran && ! lsame_(trans, "T") && ! lsame_(
	    trans, "C")) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*nrhs < 0) {
	*info = -3;
    } else if (*lda < max(1,*n)) {
	*info = -5;
    } else if (*ldb < max(1,*n)) {
	*info = -8;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGETRS", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0 || *nrhs == 0) {
	return 0;
    }

    if (notran) {

/*        Solve A * X = B. */

/*        Apply row interchanges to the right hand sides. */

	dlaswp_(nrhs, &b[b_offset], ldb, &c__1, n, &ipiv[1], &c__1);

/*        Solve L*X = B, overwriting B with X. */

	dtrsm_("Left", "Lower", "No transpose", "Unit", n, nrhs, &c_b12, &a[
		a_offset], lda, &b[b_offset], ldb);

/*        Solve U*X = B, overwriting B with X. */

	dtrsm_("Left", "Upper", "No transpose", "Non-unit", n, nrhs, &c_b12, &
		a[a_offset], lda, &b[b_offset], ldb);
    } else {

/*        Solve A' * X = B. */

/*        Solve U'*X = B, overwriting B with X. */

	dtrsm_("Left", "Upper", "Transpose", "Non-unit", n, nrhs, &c_b12, &a[
		a_offset], lda, &b[b_offset], ldb);

/*        Solve L'*X = B, overwriting B with X. */

	dtrsm_("Left", "Lower", "Transpose", "Unit", n, nrhs, &c_b12, &a[
		a_offset], lda, &b[b_offset], ldb);

/*        Apply row interchanges to the solution vectors. */

	dlaswp_(nrhs, &b[b_offset], ldb, &c__1, n, &ipiv[1], &c_n1);
    }

    return 0;

/*     End of DGETRS */

} /* dgetrs_ */

logical disnan_(doublereal *din)
{
    /* System generated locals */
    logical ret_val;

    /* Local variables */
    extern logical dlaisnan_(doublereal *, doublereal *);


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DISNAN returns .TRUE. if its argument is NaN, and .FALSE. */
/*  otherwise.  To be replaced by the Fortran 2003 intrinsic in the */
/*  future. */

/*  Arguments */
/*  ========= */

/*  DIN      (input) DOUBLE PRECISION */
/*          Input to test for NaN. */

/*  ===================================================================== */

/*  .. External Functions .. */
/*  .. */
/*  .. Executable Statements .. */
    ret_val = dlaisnan_(din, din);
    return ret_val;
} /* disnan_ */

/* Subroutine */ int dlabad_(doublereal *small, doublereal *large)
{

/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLABAD takes as input the values computed by DLAMCH for underflow and */
/*  overflow, and returns the square root of each of these values if the */
/*  log of LARGE is sufficiently large.  This subroutine is intended to */
/*  identify machines with a large exponent range, such as the Crays, and */
/*  redefine the underflow and overflow limits to be the square roots of */
/*  the values computed by DLAMCH.  This subroutine is needed because */
/*  DLAMCH does not compensate for poor arithmetic in the upper half of */
/*  the exponent range, as is found on a Cray. */

/*  Arguments */
/*  ========= */

/*  SMALL   (input/output) DOUBLE PRECISION */
/*          On entry, the underflow threshold as computed by DLAMCH. */
/*          On exit, if LOG10(LARGE) is sufficiently large, the square */
/*          root of SMALL, otherwise unchanged. */

/*  LARGE   (input/output) DOUBLE PRECISION */
/*          On entry, the overflow threshold as computed by DLAMCH. */
/*          On exit, if LOG10(LARGE) is sufficiently large, the square */
/*          root of LARGE, otherwise unchanged. */

/*  ===================================================================== */

/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     If it looks like we're on a Cray, take the square root of */
/*     SMALL and LARGE to avoid overflow and underflow problems. */

    if (d_lg10(large) > 2e3) {
	*small = sqrt(*small);
	*large = sqrt(*large);
    }

    return 0;

/*     End of DLABAD */

} /* dlabad_ */

/* Subroutine */ int dlabrd_(integer *m, integer *n, integer *nb, doublereal *
	a, integer *lda, doublereal *d__, doublereal *e, doublereal *tauq,
	doublereal *taup, doublereal *x, integer *ldx, doublereal *y, integer
	*ldy)
{
    /* Table of constant values */

    doublereal c_b4 = -1.;
    doublereal c_b5 = 1.;
    integer c__1 = 1;
    doublereal c_b16 = 0.;

    /* System generated locals */
    integer a_dim1, a_offset, x_dim1, x_offset, y_dim1, y_offset, i__1, i__2,
	    i__3;

    /* Local variables */
    integer i__;
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *,
	    integer *), dgemv_(char *, integer *, integer *, doublereal *,
	    doublereal *, integer *, doublereal *, integer *, doublereal *,
	    doublereal *, integer *), dlarfg_(integer *, doublereal *,
	     doublereal *, integer *, doublereal *);


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLABRD reduces the first NB rows and columns of a real general */
/*  m by n matrix A to upper or lower bidiagonal form by an orthogonal */
/*  transformation Q' * A * P, and returns the matrices X and Y which */
/*  are needed to apply the transformation to the unreduced part of A. */

/*  If m >= n, A is reduced to upper bidiagonal form; if m < n, to lower */
/*  bidiagonal form. */

/*  This is an auxiliary routine called by DGEBRD */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows in the matrix A. */

/*  N       (input) INTEGER */
/*          The number of columns in the matrix A. */

/*  NB      (input) INTEGER */
/*          The number of leading rows and columns of A to be reduced. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the m by n general matrix to be reduced. */
/*          On exit, the first NB rows and columns of the matrix are */
/*          overwritten; the rest of the array is unchanged. */
/*          If m >= n, elements on and below the diagonal in the first NB */
/*            columns, with the array TAUQ, represent the orthogonal */
/*            matrix Q as a product of elementary reflectors; and */
/*            elements above the diagonal in the first NB rows, with the */
/*            array TAUP, represent the orthogonal matrix P as a product */
/*            of elementary reflectors. */
/*          If m < n, elements below the diagonal in the first NB */
/*            columns, with the array TAUQ, represent the orthogonal */
/*            matrix Q as a product of elementary reflectors, and */
/*            elements on and above the diagonal in the first NB rows, */
/*            with the array TAUP, represent the orthogonal matrix P as */
/*            a product of elementary reflectors. */
/*          See Further Details. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,M). */

/*  D       (output) DOUBLE PRECISION array, dimension (NB) */
/*          The diagonal elements of the first NB rows and columns of */
/*          the reduced matrix.  D(i) = A(i,i). */

/*  E       (output) DOUBLE PRECISION array, dimension (NB) */
/*          The off-diagonal elements of the first NB rows and columns of */
/*          the reduced matrix. */

/*  TAUQ    (output) DOUBLE PRECISION array dimension (NB) */
/*          The scalar factors of the elementary reflectors which */
/*          represent the orthogonal matrix Q. See Further Details. */

/*  TAUP    (output) DOUBLE PRECISION array, dimension (NB) */
/*          The scalar factors of the elementary reflectors which */
/*          represent the orthogonal matrix P. See Further Details. */

/*  X       (output) DOUBLE PRECISION array, dimension (LDX,NB) */
/*          The m-by-nb matrix X required to update the unreduced part */
/*          of A. */

/*  LDX     (input) INTEGER */
/*          The leading dimension of the array X. LDX >= M. */

/*  Y       (output) DOUBLE PRECISION array, dimension (LDY,NB) */
/*          The n-by-nb matrix Y required to update the unreduced part */
/*          of A. */

/*  LDY     (input) INTEGER */
/*          The leading dimension of the array Y. LDY >= N. */

/*  Further Details */
/*  =============== */

/*  The matrices Q and P are represented as products of elementary */
/*  reflectors: */

/*     Q = H(1) H(2) . . . H(nb)  and  P = G(1) G(2) . . . G(nb) */

/*  Each H(i) and G(i) has the form: */

/*     H(i) = I - tauq * v * v'  and G(i) = I - taup * u * u' */

/*  where tauq and taup are real scalars, and v and u are real vectors. */

/*  If m >= n, v(1:i-1) = 0, v(i) = 1, and v(i:m) is stored on exit in */
/*  A(i:m,i); u(1:i) = 0, u(i+1) = 1, and u(i+1:n) is stored on exit in */
/*  A(i,i+1:n); tauq is stored in TAUQ(i) and taup in TAUP(i). */

/*  If m < n, v(1:i) = 0, v(i+1) = 1, and v(i+1:m) is stored on exit in */
/*  A(i+2:m,i); u(1:i-1) = 0, u(i) = 1, and u(i:n) is stored on exit in */
/*  A(i,i+1:n); tauq is stored in TAUQ(i) and taup in TAUP(i). */

/*  The elements of the vectors v and u together form the m-by-nb matrix */
/*  V and the nb-by-n matrix U' which are needed, with X and Y, to apply */
/*  the transformation to the unreduced part of the matrix, using a block */
/*  update of the form:  A := A - V*Y' - X*U'. */

/*  The contents of A on exit are illustrated by the following examples */
/*  with nb = 2: */

/*  m = 6 and n = 5 (m > n):          m = 5 and n = 6 (m < n): */

/*    (  1   1   u1  u1  u1 )           (  1   u1  u1  u1  u1  u1 ) */
/*    (  v1  1   1   u2  u2 )           (  1   1   u2  u2  u2  u2 ) */
/*    (  v1  v2  a   a   a  )           (  v1  1   a   a   a   a  ) */
/*    (  v1  v2  a   a   a  )           (  v1  v2  a   a   a   a  ) */
/*    (  v1  v2  a   a   a  )           (  v1  v2  a   a   a   a  ) */
/*    (  v1  v2  a   a   a  ) */

/*  where a denotes an element of the original matrix which is unchanged, */
/*  vi denotes an element of the vector defining H(i), and ui an element */
/*  of the vector defining G(i). */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Quick return if possible */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --d__;
    --e;
    --tauq;
    --taup;
    x_dim1 = *ldx;
    x_offset = 1 + x_dim1;
    x -= x_offset;
    y_dim1 = *ldy;
    y_offset = 1 + y_dim1;
    y -= y_offset;

    /* Function Body */
    if (*m <= 0 || *n <= 0) {
	return 0;
    }

    if (*m >= *n) {

/*        Reduce to upper bidiagonal form */

	i__1 = *nb;
	for (i__ = 1; i__ <= i__1; ++i__) {

/*           Update A(i:m,i) */

	    i__2 = *m - i__ + 1;
	    i__3 = i__ - 1;
	    dgemv_("No transpose", &i__2, &i__3, &c_b4, &a[i__ + a_dim1], lda,
		     &y[i__ + y_dim1], ldy, &c_b5, &a[i__ + i__ * a_dim1], &
		    c__1);
	    i__2 = *m - i__ + 1;
	    i__3 = i__ - 1;
	    dgemv_("No transpose", &i__2, &i__3, &c_b4, &x[i__ + x_dim1], ldx,
		     &a[i__ * a_dim1 + 1], &c__1, &c_b5, &a[i__ + i__ *
		    a_dim1], &c__1);

/*           Generate reflection Q(i) to annihilate A(i+1:m,i) */

	    i__2 = *m - i__ + 1;
/* Computing MIN */
	    i__3 = i__ + 1;
	    dlarfg_(&i__2, &a[i__ + i__ * a_dim1], &a[min(i__3, *m)+ i__ *
		    a_dim1], &c__1, &tauq[i__]);
	    d__[i__] = a[i__ + i__ * a_dim1];
	    if (i__ < *n) {
		a[i__ + i__ * a_dim1] = 1.;

/*              Compute Y(i+1:n,i) */

		i__2 = *m - i__ + 1;
		i__3 = *n - i__;
		dgemv_("Transpose", &i__2, &i__3, &c_b5, &a[i__ + (i__ + 1) *
			a_dim1], lda, &a[i__ + i__ * a_dim1], &c__1, &c_b16, &
			y[i__ + 1 + i__ * y_dim1], &c__1);
		i__2 = *m - i__ + 1;
		i__3 = i__ - 1;
		dgemv_("Transpose", &i__2, &i__3, &c_b5, &a[i__ + a_dim1],
			lda, &a[i__ + i__ * a_dim1], &c__1, &c_b16, &y[i__ *
			y_dim1 + 1], &c__1);
		i__2 = *n - i__;
		i__3 = i__ - 1;
		dgemv_("No transpose", &i__2, &i__3, &c_b4, &y[i__ + 1 +
			y_dim1], ldy, &y[i__ * y_dim1 + 1], &c__1, &c_b5, &y[
			i__ + 1 + i__ * y_dim1], &c__1);
		i__2 = *m - i__ + 1;
		i__3 = i__ - 1;
		dgemv_("Transpose", &i__2, &i__3, &c_b5, &x[i__ + x_dim1],
			ldx, &a[i__ + i__ * a_dim1], &c__1, &c_b16, &y[i__ *
			y_dim1 + 1], &c__1);
		i__2 = i__ - 1;
		i__3 = *n - i__;
		dgemv_("Transpose", &i__2, &i__3, &c_b4, &a[(i__ + 1) *
			a_dim1 + 1], lda, &y[i__ * y_dim1 + 1], &c__1, &c_b5,
			&y[i__ + 1 + i__ * y_dim1], &c__1);
		i__2 = *n - i__;
		dscal_(&i__2, &tauq[i__], &y[i__ + 1 + i__ * y_dim1], &c__1);

/*              Update A(i,i+1:n) */

		i__2 = *n - i__;
		dgemv_("No transpose", &i__2, &i__, &c_b4, &y[i__ + 1 +
			y_dim1], ldy, &a[i__ + a_dim1], lda, &c_b5, &a[i__ + (
			i__ + 1) * a_dim1], lda);
		i__2 = i__ - 1;
		i__3 = *n - i__;
		dgemv_("Transpose", &i__2, &i__3, &c_b4, &a[(i__ + 1) *
			a_dim1 + 1], lda, &x[i__ + x_dim1], ldx, &c_b5, &a[
			i__ + (i__ + 1) * a_dim1], lda);

/*              Generate reflection P(i) to annihilate A(i,i+2:n) */

		i__2 = *n - i__;
/* Computing MIN */
		i__3 = i__ + 2;
		dlarfg_(&i__2, &a[i__ + (i__ + 1) * a_dim1], &a[i__ + min(
			i__3, *n)* a_dim1], lda, &taup[i__]);
		e[i__] = a[i__ + (i__ + 1) * a_dim1];
		a[i__ + (i__ + 1) * a_dim1] = 1.;

/*              Compute X(i+1:m,i) */

		i__2 = *m - i__;
		i__3 = *n - i__;
		dgemv_("No transpose", &i__2, &i__3, &c_b5, &a[i__ + 1 + (i__
			+ 1) * a_dim1], lda, &a[i__ + (i__ + 1) * a_dim1],
			lda, &c_b16, &x[i__ + 1 + i__ * x_dim1], &c__1);
		i__2 = *n - i__;
		dgemv_("Transpose", &i__2, &i__, &c_b5, &y[i__ + 1 + y_dim1],
			ldy, &a[i__ + (i__ + 1) * a_dim1], lda, &c_b16, &x[
			i__ * x_dim1 + 1], &c__1);
		i__2 = *m - i__;
		dgemv_("No transpose", &i__2, &i__, &c_b4, &a[i__ + 1 +
			a_dim1], lda, &x[i__ * x_dim1 + 1], &c__1, &c_b5, &x[
			i__ + 1 + i__ * x_dim1], &c__1);
		i__2 = i__ - 1;
		i__3 = *n - i__;
		dgemv_("No transpose", &i__2, &i__3, &c_b5, &a[(i__ + 1) *
			a_dim1 + 1], lda, &a[i__ + (i__ + 1) * a_dim1], lda, &
			c_b16, &x[i__ * x_dim1 + 1], &c__1);
		i__2 = *m - i__;
		i__3 = i__ - 1;
		dgemv_("No transpose", &i__2, &i__3, &c_b4, &x[i__ + 1 +
			x_dim1], ldx, &x[i__ * x_dim1 + 1], &c__1, &c_b5, &x[
			i__ + 1 + i__ * x_dim1], &c__1);
		i__2 = *m - i__;
		dscal_(&i__2, &taup[i__], &x[i__ + 1 + i__ * x_dim1], &c__1);
	    }
/* L10: */
	}
    } else {

/*        Reduce to lower bidiagonal form */

	i__1 = *nb;
	for (i__ = 1; i__ <= i__1; ++i__) {

/*           Update A(i,i:n) */

	    i__2 = *n - i__ + 1;
	    i__3 = i__ - 1;
	    dgemv_("No transpose", &i__2, &i__3, &c_b4, &y[i__ + y_dim1], ldy,
		     &a[i__ + a_dim1], lda, &c_b5, &a[i__ + i__ * a_dim1],
		    lda);
	    i__2 = i__ - 1;
	    i__3 = *n - i__ + 1;
	    dgemv_("Transpose", &i__2, &i__3, &c_b4, &a[i__ * a_dim1 + 1],
		    lda, &x[i__ + x_dim1], ldx, &c_b5, &a[i__ + i__ * a_dim1],
		     lda);

/*           Generate reflection P(i) to annihilate A(i,i+1:n) */

	    i__2 = *n - i__ + 1;
/* Computing MIN */
	    i__3 = i__ + 1;
	    dlarfg_(&i__2, &a[i__ + i__ * a_dim1], &a[i__ + min(i__3, *n)*
		    a_dim1], lda, &taup[i__]);
	    d__[i__] = a[i__ + i__ * a_dim1];
	    if (i__ < *m) {
		a[i__ + i__ * a_dim1] = 1.;

/*              Compute X(i+1:m,i) */

		i__2 = *m - i__;
		i__3 = *n - i__ + 1;
		dgemv_("No transpose", &i__2, &i__3, &c_b5, &a[i__ + 1 + i__ *
			 a_dim1], lda, &a[i__ + i__ * a_dim1], lda, &c_b16, &
			x[i__ + 1 + i__ * x_dim1], &c__1);
		i__2 = *n - i__ + 1;
		i__3 = i__ - 1;
		dgemv_("Transpose", &i__2, &i__3, &c_b5, &y[i__ + y_dim1],
			ldy, &a[i__ + i__ * a_dim1], lda, &c_b16, &x[i__ *
			x_dim1 + 1], &c__1);
		i__2 = *m - i__;
		i__3 = i__ - 1;
		dgemv_("No transpose", &i__2, &i__3, &c_b4, &a[i__ + 1 +
			a_dim1], lda, &x[i__ * x_dim1 + 1], &c__1, &c_b5, &x[
			i__ + 1 + i__ * x_dim1], &c__1);
		i__2 = i__ - 1;
		i__3 = *n - i__ + 1;
		dgemv_("No transpose", &i__2, &i__3, &c_b5, &a[i__ * a_dim1 +
			1], lda, &a[i__ + i__ * a_dim1], lda, &c_b16, &x[i__ *
			 x_dim1 + 1], &c__1);
		i__2 = *m - i__;
		i__3 = i__ - 1;
		dgemv_("No transpose", &i__2, &i__3, &c_b4, &x[i__ + 1 +
			x_dim1], ldx, &x[i__ * x_dim1 + 1], &c__1, &c_b5, &x[
			i__ + 1 + i__ * x_dim1], &c__1);
		i__2 = *m - i__;
		dscal_(&i__2, &taup[i__], &x[i__ + 1 + i__ * x_dim1], &c__1);

/*              Update A(i+1:m,i) */

		i__2 = *m - i__;
		i__3 = i__ - 1;
		dgemv_("No transpose", &i__2, &i__3, &c_b4, &a[i__ + 1 +
			a_dim1], lda, &y[i__ + y_dim1], ldy, &c_b5, &a[i__ +
			1 + i__ * a_dim1], &c__1);
		i__2 = *m - i__;
		dgemv_("No transpose", &i__2, &i__, &c_b4, &x[i__ + 1 +
			x_dim1], ldx, &a[i__ * a_dim1 + 1], &c__1, &c_b5, &a[
			i__ + 1 + i__ * a_dim1], &c__1);

/*              Generate reflection Q(i) to annihilate A(i+2:m,i) */

		i__2 = *m - i__;
/* Computing MIN */
		i__3 = i__ + 2;
		dlarfg_(&i__2, &a[i__ + 1 + i__ * a_dim1], &a[min(i__3, *m)+
			i__ * a_dim1], &c__1, &tauq[i__]);
		e[i__] = a[i__ + 1 + i__ * a_dim1];
		a[i__ + 1 + i__ * a_dim1] = 1.;

/*              Compute Y(i+1:n,i) */

		i__2 = *m - i__;
		i__3 = *n - i__;
		dgemv_("Transpose", &i__2, &i__3, &c_b5, &a[i__ + 1 + (i__ +
			1) * a_dim1], lda, &a[i__ + 1 + i__ * a_dim1], &c__1,
			&c_b16, &y[i__ + 1 + i__ * y_dim1], &c__1);
		i__2 = *m - i__;
		i__3 = i__ - 1;
		dgemv_("Transpose", &i__2, &i__3, &c_b5, &a[i__ + 1 + a_dim1],
			 lda, &a[i__ + 1 + i__ * a_dim1], &c__1, &c_b16, &y[
			i__ * y_dim1 + 1], &c__1);
		i__2 = *n - i__;
		i__3 = i__ - 1;
		dgemv_("No transpose", &i__2, &i__3, &c_b4, &y[i__ + 1 +
			y_dim1], ldy, &y[i__ * y_dim1 + 1], &c__1, &c_b5, &y[
			i__ + 1 + i__ * y_dim1], &c__1);
		i__2 = *m - i__;
		dgemv_("Transpose", &i__2, &i__, &c_b5, &x[i__ + 1 + x_dim1],
			ldx, &a[i__ + 1 + i__ * a_dim1], &c__1, &c_b16, &y[
			i__ * y_dim1 + 1], &c__1);
		i__2 = *n - i__;
		dgemv_("Transpose", &i__, &i__2, &c_b4, &a[(i__ + 1) * a_dim1
			+ 1], lda, &y[i__ * y_dim1 + 1], &c__1, &c_b5, &y[i__
			+ 1 + i__ * y_dim1], &c__1);
		i__2 = *n - i__;
		dscal_(&i__2, &tauq[i__], &y[i__ + 1 + i__ * y_dim1], &c__1);
	    }
/* L20: */
	}
    }
    return 0;

/*     End of DLABRD */

} /* dlabrd_ */

/* Subroutine */ int dlacpy_(char *uplo, integer *m, integer *n, doublereal *
	a, integer *lda, doublereal *b, integer *ldb)
{
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, i__1, i__2;

    /* Local variables */
    integer i__, j;
    extern logical lsame_(char *, char *);


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLACPY copies all or part of a two-dimensional matrix A to another */
/*  matrix B. */

/*  Arguments */
/*  ========= */

/*  UPLO    (input) CHARACTER*1 */
/*          Specifies the part of the matrix A to be copied to B. */
/*          = 'U':      Upper triangular part */
/*          = 'L':      Lower triangular part */
/*          Otherwise:  All of the matrix A */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A.  M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A.  N >= 0. */

/*  A       (input) DOUBLE PRECISION array, dimension (LDA,N) */
/*          The m by n matrix A.  If UPLO = 'U', only the upper triangle */
/*          or trapezoid is accessed; if UPLO = 'L', only the lower */
/*          triangle or trapezoid is accessed. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,M). */

/*  B       (output) DOUBLE PRECISION array, dimension (LDB,N) */
/*          On exit, B = A in the locations specified by UPLO. */

/*  LDB     (input) INTEGER */
/*          The leading dimension of the array B.  LDB >= max(1,M). */

/*  ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;

    /* Function Body */
    if (lsame_(uplo, "U")) {
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = min(j,*m);
	    for (i__ = 1; i__ <= i__2; ++i__) {
		b[i__ + j * b_dim1] = a[i__ + j * a_dim1];
/* L10: */
	    }
/* L20: */
	}
    } else if (lsame_(uplo, "L")) {
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (i__ = j; i__ <= i__2; ++i__) {
		b[i__ + j * b_dim1] = a[i__ + j * a_dim1];
/* L30: */
	    }
/* L40: */
	}
    } else {
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		b[i__ + j * b_dim1] = a[i__ + j * a_dim1];
/* L50: */
	    }
/* L60: */
	}
    }
    return 0;

/*     End of DLACPY */

} /* dlacpy_ */

/* Subroutine */ int dlaic1_(integer *job, integer *j, doublereal *x,
	doublereal *sest, doublereal *w, doublereal *gamma, doublereal *
	sestpr, doublereal *s, doublereal *c__)
{
    /* Table of constant values */

    integer c__1 = 1;
    doublereal c_b5 = 1.;

    /* System generated locals */
    doublereal d__1, d__2, d__3, d__4;

    /* Local variables */
    doublereal b, t, s1, s2, eps, tmp;
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *,
	    integer *);
    doublereal sine, test, zeta1, zeta2, alpha, norma;
    extern doublereal dlamch_(char *);
    doublereal absgam, absalp, cosine, absest;


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLAIC1 applies one step of incremental condition estimation in */
/*  its simplest version: */

/*  Let x, twonorm(x) = 1, be an approximate singular vector of an j-by-j */
/*  lower triangular matrix L, such that */
/*           twonorm(L*x) = sest */
/*  Then DLAIC1 computes sestpr, s, c such that */
/*  the vector */
/*                  [ s*x ] */
/*           xhat = [  c  ] */
/*  is an approximate singular vector of */
/*                  [ L     0  ] */
/*           Lhat = [ w' gamma ] */
/*  in the sense that */
/*           twonorm(Lhat*xhat) = sestpr. */

/*  Depending on JOB, an estimate for the largest or smallest singular */
/*  value is computed. */

/*  Note that [s c]' and sestpr**2 is an eigenpair of the system */

/*      diag(sest*sest, 0) + [alpha  gamma] * [ alpha ] */
/*                                            [ gamma ] */

/*  where  alpha =  x'*w. */

/*  Arguments */
/*  ========= */

/*  JOB     (input) INTEGER */
/*          = 1: an estimate for the largest singular value is computed. */
/*          = 2: an estimate for the smallest singular value is computed. */

/*  J       (input) INTEGER */
/*          Length of X and W */

/*  X       (input) DOUBLE PRECISION array, dimension (J) */
/*          The j-vector x. */

/*  SEST    (input) DOUBLE PRECISION */
/*          Estimated singular value of j by j matrix L */

/*  W       (input) DOUBLE PRECISION array, dimension (J) */
/*          The j-vector w. */

/*  GAMMA   (input) DOUBLE PRECISION */
/*          The diagonal element gamma. */

/*  SESTPR  (output) DOUBLE PRECISION */
/*          Estimated singular value of (j+1) by (j+1) matrix Lhat. */

/*  S       (output) DOUBLE PRECISION */
/*          Sine needed in forming xhat. */

/*  C       (output) DOUBLE PRECISION */
/*          Cosine needed in forming xhat. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    --w;
    --x;

    /* Function Body */
    eps = dlamch_("Epsilon");
    alpha = ddot_(j, &x[1], &c__1, &w[1], &c__1);

    absalp = abs(alpha);
    absgam = abs(*gamma);
    absest = abs(*sest);

    if (*job == 1) {

/*        Estimating largest singular value */

/*        special cases */

	if (*sest == 0.) {
	    s1 = max(absgam,absalp);
	    if (s1 == 0.) {
		*s = 0.;
		*c__ = 1.;
		*sestpr = 0.;
	    } else {
		*s = alpha / s1;
		*c__ = *gamma / s1;
		tmp = sqrt(*s * *s + *c__ * *c__);
		*s /= tmp;
		*c__ /= tmp;
		*sestpr = s1 * tmp;
	    }
	    return 0;
	} else if (absgam <= eps * absest) {
	    *s = 1.;
	    *c__ = 0.;
	    tmp = max(absest,absalp);
	    s1 = absest / tmp;
	    s2 = absalp / tmp;
	    *sestpr = tmp * sqrt(s1 * s1 + s2 * s2);
	    return 0;
	} else if (absalp <= eps * absest) {
	    s1 = absgam;
	    s2 = absest;
	    if (s1 <= s2) {
		*s = 1.;
		*c__ = 0.;
		*sestpr = s2;
	    } else {
		*s = 0.;
		*c__ = 1.;
		*sestpr = s1;
	    }
	    return 0;
	} else if (absest <= eps * absalp || absest <= eps * absgam) {
	    s1 = absgam;
	    s2 = absalp;
	    if (s1 <= s2) {
		tmp = s1 / s2;
		*s = sqrt(tmp * tmp + 1.);
		*sestpr = s2 * *s;
		*c__ = *gamma / s2 / *s;
		*s = d_sign(&c_b5, &alpha) / *s;
	    } else {
		tmp = s2 / s1;
		*c__ = sqrt(tmp * tmp + 1.);
		*sestpr = s1 * *c__;
		*s = alpha / s1 / *c__;
		*c__ = d_sign(&c_b5, gamma) / *c__;
	    }
	    return 0;
	} else {

/*           normal case */

	    zeta1 = alpha / absest;
	    zeta2 = *gamma / absest;

	    b = (1. - zeta1 * zeta1 - zeta2 * zeta2) * .5;
	    *c__ = zeta1 * zeta1;
	    if (b > 0.) {
		t = *c__ / (b + sqrt(b * b + *c__));
	    } else {
		t = sqrt(b * b + *c__) - b;
	    }

	    sine = -zeta1 / t;
	    cosine = -zeta2 / (t + 1.);
	    tmp = sqrt(sine * sine + cosine * cosine);
	    *s = sine / tmp;
	    *c__ = cosine / tmp;
	    *sestpr = sqrt(t + 1.) * absest;
	    return 0;
	}

    } else if (*job == 2) {

/*        Estimating smallest singular value */

/*        special cases */

	if (*sest == 0.) {
	    *sestpr = 0.;
	    if (max(absgam,absalp) == 0.) {
		sine = 1.;
		cosine = 0.;
	    } else {
		sine = -(*gamma);
		cosine = alpha;
	    }
/* Computing MAX */
	    d__1 = abs(sine), d__2 = abs(cosine);
	    s1 = max(d__1,d__2);
	    *s = sine / s1;
	    *c__ = cosine / s1;
	    tmp = sqrt(*s * *s + *c__ * *c__);
	    *s /= tmp;
	    *c__ /= tmp;
	    return 0;
	} else if (absgam <= eps * absest) {
	    *s = 0.;
	    *c__ = 1.;
	    *sestpr = absgam;
	    return 0;
	} else if (absalp <= eps * absest) {
	    s1 = absgam;
	    s2 = absest;
	    if (s1 <= s2) {
		*s = 0.;
		*c__ = 1.;
		*sestpr = s1;
	    } else {
		*s = 1.;
		*c__ = 0.;
		*sestpr = s2;
	    }
	    return 0;
	} else if (absest <= eps * absalp || absest <= eps * absgam) {
	    s1 = absgam;
	    s2 = absalp;
	    if (s1 <= s2) {
		tmp = s1 / s2;
		*c__ = sqrt(tmp * tmp + 1.);
		*sestpr = absest * (tmp / *c__);
		*s = -(*gamma / s2) / *c__;
		*c__ = d_sign(&c_b5, &alpha) / *c__;
	    } else {
		tmp = s2 / s1;
		*s = sqrt(tmp * tmp + 1.);
		*sestpr = absest / *s;
		*c__ = alpha / s1 / *s;
		*s = -d_sign(&c_b5, gamma) / *s;
	    }
	    return 0;
	} else {

/*           normal case */

	    zeta1 = alpha / absest;
	    zeta2 = *gamma / absest;

/* Computing MAX */
	    d__3 = zeta1 * zeta1 + 1. + (d__1 = zeta1 * zeta2, abs(d__1)),
		    d__4 = (d__2 = zeta1 * zeta2, abs(d__2)) + zeta2 * zeta2;
	    norma = max(d__3,d__4);

/*           See if root is closer to zero or to ONE */

	    test = (zeta1 - zeta2) * 2. * (zeta1 + zeta2) + 1.;
	    if (test >= 0.) {

/*              root is close to zero, compute directly */

		b = (zeta1 * zeta1 + zeta2 * zeta2 + 1.) * .5;
		*c__ = zeta2 * zeta2;
		t = *c__ / (b + sqrt((d__1 = b * b - *c__, abs(d__1))));
		sine = zeta1 / (1. - t);
		cosine = -zeta2 / t;
		*sestpr = sqrt(t + eps * 4. * eps * norma) * absest;
	    } else {

/*              root is closer to ONE, shift by that amount */

		b = (zeta2 * zeta2 + zeta1 * zeta1 - 1.) * .5;
		*c__ = zeta1 * zeta1;
		if (b >= 0.) {
		    t = -(*c__) / (b + sqrt(b * b + *c__));
		} else {
		    t = b - sqrt(b * b + *c__);
		}
		sine = -zeta1 / t;
		cosine = -zeta2 / (t + 1.);
		*sestpr = sqrt(t + 1. + eps * 4. * eps * norma) * absest;
	    }
	    tmp = sqrt(sine * sine + cosine * cosine);
	    *s = sine / tmp;
	    *c__ = cosine / tmp;
	    return 0;

	}
    }
    return 0;

/*     End of DLAIC1 */

} /* dlaic1_ */

logical dlaisnan_(doublereal *din1, doublereal *din2)
{
    /* System generated locals */
    logical ret_val;


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  This routine is not for general use.  It exists solely to avoid */
/*  over-optimization in DISNAN. */

/*  DLAISNAN checks for NaNs by comparing its two arguments for */
/*  inequality.  NaN is the only floating-point value where NaN != NaN */
/*  returns .TRUE.  To check for NaNs, pass the same variable as both */
/*  arguments. */

/*  A compiler must assume that the two arguments are */
/*  not the same variable, and the test will not be optimized away. */
/*  Interprocedural or whole-program optimization may delete this */
/*  test.  The ISNAN functions will be replaced by the correct */
/*  Fortran 03 intrinsic once the intrinsic is widely available. */

/*  Arguments */
/*  ========= */

/*  DIN1     (input) DOUBLE PRECISION */
/*  DIN2     (input) DOUBLE PRECISION */
/*          Two numbers to compare for inequality. */

/*  ===================================================================== */

/*  .. Executable Statements .. */
    ret_val = *din1 != *din2;
    return ret_val;
} /* dlaisnan_ */

doublereal dlamch_(char *cmach)
{
/*  -- LAPACK auxiliary routine --

    changed to circumvent problems of the original version (thread safety),
    ANSI C macros defined in <float.h> are used

    Purpose
    =======

    DLAMCH determines double precision machine parameters.

    Arguments
    =========

    CMACH   (input) CHARACTER*1
            Specifies the value to be returned by DLAMCH:
            = 'E' or 'e',   DLAMCH := eps
            = 'S' or 's ,   DLAMCH := sfmin
            = 'B' or 'b',   DLAMCH := base
            = 'P' or 'p',   DLAMCH := eps*base
            = 'N' or 'n',   DLAMCH := t
            = 'R' or 'r',   DLAMCH := rnd
            = 'M' or 'm',   DLAMCH := emin
            = 'U' or 'u',   DLAMCH := rmin
            = 'L' or 'l',   DLAMCH := emax
            = 'O' or 'o',   DLAMCH := rmax

            where

            eps   = relative machine precision
            sfmin = safe minimum, such that 1/sfmin does not overflow
            base  = base of the machine
            prec  = eps*base
            t     = number of (base) digits in the mantissa
            rnd   = 1.0 when rounding occurs in addition, 0.0 otherwise
            emin  = minimum exponent before (gradual) underflow
            rmin  = underflow threshold - base**(emin-1)
            emax  = largest exponent before overflow
            rmax  = overflow threshold  - (base**emax)*(1-eps)

   =====================================================================
*/

    doublereal rmach;

    /* only 'B', 'E', 'O', 'P', 'S', 'U' are used by LAPACK, cf. LAWN81 */

    if (lsame_(cmach, "E"))
        rmach = DBL_EPSILON / FLT_RADIX;
    else if (lsame_(cmach, "S")) {
        doublereal small = 1. / DBL_MAX;
        doublereal eps = DBL_EPSILON / FLT_RADIX;
        rmach = DBL_MIN;
        /* Use SMALL plus a bit, to avoid the possibility of rounding
           causing overflow when computing  1/sfmin. */
        if (small >= rmach)
            rmach = small * (eps + 1.);
    } else if (lsame_(cmach, "B"))
        rmach = FLT_RADIX;
    else if (lsame_(cmach, "P"))
        rmach = DBL_EPSILON;
    else if (lsame_(cmach, "U"))
        rmach = DBL_MIN;
    else if (lsame_(cmach, "O"))
        rmach = DBL_MAX;
    else
        rmach = 0;

    return rmach;
} /* dlamch_ */

doublereal dlange_(char *norm, integer *m, integer *n, doublereal *a, integer
	*lda, doublereal *work)
{
    /* Table of constant values */

    integer c__1 = 1;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;
    doublereal ret_val, d__1, d__2, d__3;

    /* Local variables */
    integer i__, j;
    doublereal sum, scale;
    extern logical lsame_(char *, char *);
    doublereal value;
    extern /* Subroutine */ int dlassq_(integer *, doublereal *, integer *,
	    doublereal *, doublereal *);


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLANGE  returns the value of the one norm,  or the Frobenius norm, or */
/*  the  infinity norm,  or the  element of  largest absolute value  of a */
/*  real matrix A. */

/*  Description */
/*  =========== */

/*  DLANGE returns the value */

/*     DLANGE = ( max(abs(A(i,j))), NORM = 'M' or 'm' */
/*              ( */
/*              ( norm1(A),         NORM = '1', 'O' or 'o' */
/*              ( */
/*              ( normI(A),         NORM = 'I' or 'i' */
/*              ( */
/*              ( normF(A),         NORM = 'F', 'f', 'E' or 'e' */

/*  where  norm1  denotes the  one norm of a matrix (maximum column sum), */
/*  normI  denotes the  infinity norm  of a matrix  (maximum row sum) and */
/*  normF  denotes the  Frobenius norm of a matrix (square root of sum of */
/*  squares).  Note that  max(abs(A(i,j)))  is not a consistent matrix norm. */

/*  Arguments */
/*  ========= */

/*  NORM    (input) CHARACTER*1 */
/*          Specifies the value to be returned in DLANGE as described */
/*          above. */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A.  M >= 0.  When M = 0, */
/*          DLANGE is set to zero. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A.  N >= 0.  When N = 0, */
/*          DLANGE is set to zero. */

/*  A       (input) DOUBLE PRECISION array, dimension (LDA,N) */
/*          The m by n matrix A. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(M,1). */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (MAX(1,LWORK)), */
/*          where LWORK >= M when NORM = 'I'; otherwise, WORK is not */
/*          referenced. */

/* ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --work;

    /* Function Body */
    if (min(*m,*n) == 0) {
	value = 0.;
    } else if (lsame_(norm, "M")) {

/*        Find max(abs(A(i,j))). */

	value = 0.;
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
/* Computing MAX */
		d__2 = value, d__3 = (d__1 = a[i__ + j * a_dim1], abs(d__1));
		value = max(d__2,d__3);
/* L10: */
	    }
/* L20: */
	}
    } else if (lsame_(norm, "O") || *(unsigned char *)
	    norm == '1') {

/*        Find norm1(A). */

	value = 0.;
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    sum = 0.;
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		sum += (d__1 = a[i__ + j * a_dim1], abs(d__1));
/* L30: */
	    }
	    value = max(value,sum);
/* L40: */
	}
    } else if (lsame_(norm, "I")) {

/*        Find normI(A). */

	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    work[i__] = 0.;
/* L50: */
	}
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		work[i__] += (d__1 = a[i__ + j * a_dim1], abs(d__1));
/* L60: */
	    }
/* L70: */
	}
	value = 0.;
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MAX */
	    d__1 = value, d__2 = work[i__];
	    value = max(d__1,d__2);
/* L80: */
	}
    } else if (lsame_(norm, "F") || lsame_(norm, "E")) {

/*        Find normF(A). */

	scale = 0.;
	sum = 1.;
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    dlassq_(m, &a[j * a_dim1 + 1], &c__1, &scale, &sum);
/* L90: */
	}
	value = scale * sqrt(sum);
    }

    ret_val = value;
    return ret_val;

/*     End of DLANGE */

} /* dlange_ */

doublereal dlapy2_(doublereal *x, doublereal *y)
{
    /* System generated locals */
    doublereal ret_val, d__1;

    /* Local variables */
    doublereal w, z__, xabs, yabs;


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLAPY2 returns sqrt(x**2+y**2), taking care not to cause unnecessary */
/*  overflow. */

/*  Arguments */
/*  ========= */

/*  X       (input) DOUBLE PRECISION */
/*  Y       (input) DOUBLE PRECISION */
/*          X and Y specify the values x and y. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    xabs = abs(*x);
    yabs = abs(*y);
    w = max(xabs,yabs);
    z__ = min(xabs,yabs);
    if (z__ == 0.) {
	ret_val = w;
    } else {
/* Computing 2nd power */
	d__1 = z__ / w;
	ret_val = w * sqrt(d__1 * d__1 + 1.);
    }
    return ret_val;

/*     End of DLAPY2 */

} /* dlapy2_ */

/* Subroutine */ int dlaqp2_(integer *m, integer *n, integer *offset,
	doublereal *a, integer *lda, integer *jpvt, doublereal *tau,
	doublereal *vn1, doublereal *vn2, doublereal *work)
{
    /* Table of constant values */

    integer c__1 = 1;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    doublereal d__1, d__2;

    /* Local variables */
    integer i__, j, mn;
    doublereal aii;
    integer pvt;
    doublereal temp;
    extern doublereal dnrm2_(integer *, doublereal *, integer *);
    doublereal temp2, tol3z;
    extern /* Subroutine */ int dlarf_(char *, integer *, integer *,
	    doublereal *, integer *, doublereal *, doublereal *, integer *,
	    doublereal *);
    integer offpi, itemp;
    extern /* Subroutine */ int dswap_(integer *, doublereal *, integer *,
	    doublereal *, integer *);
    extern doublereal dlamch_(char *);
    extern integer idamax_(integer *, doublereal *, integer *);
    extern /* Subroutine */ int dlarfp_(integer *, doublereal *, doublereal *,
	     integer *, doublereal *);


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLAQP2 computes a QR factorization with column pivoting of */
/*  the block A(OFFSET+1:M,1:N). */
/*  The block A(1:OFFSET,1:N) is accordingly pivoted, but not factorized. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A. M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A. N >= 0. */

/*  OFFSET  (input) INTEGER */
/*          The number of rows of the matrix A that must be pivoted */
/*          but no factorized. OFFSET >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the M-by-N matrix A. */
/*          On exit, the upper triangle of block A(OFFSET+1:M,1:N) is */
/*          the triangular factor obtained; the elements in block */
/*          A(OFFSET+1:M,1:N) below the diagonal, together with the */
/*          array TAU, represent the orthogonal matrix Q as a product of */
/*          elementary reflectors. Block A(1:OFFSET,1:N) has been */
/*          accordingly pivoted, but no factorized. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A. LDA >= max(1,M). */

/*  JPVT    (input/output) INTEGER array, dimension (N) */
/*          On entry, if JPVT(i) .ne. 0, the i-th column of A is permuted */
/*          to the front of A*P (a leading column); if JPVT(i) = 0, */
/*          the i-th column of A is a free column. */
/*          On exit, if JPVT(i) = k, then the i-th column of A*P */
/*          was the k-th column of A. */

/*  TAU     (output) DOUBLE PRECISION array, dimension (min(M,N)) */
/*          The scalar factors of the elementary reflectors. */

/*  VN1     (input/output) DOUBLE PRECISION array, dimension (N) */
/*          The vector with the partial column norms. */

/*  VN2     (input/output) DOUBLE PRECISION array, dimension (N) */
/*          The vector with the exact column norms. */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (N) */

/*  Further Details */
/*  =============== */

/*  Based on contributions by */
/*    G. Quintana-Orti, Depto. de Informatica, Universidad Jaime I, Spain */
/*    X. Sun, Computer Science Dept., Duke University, USA */

/*  Partial column norm updating strategy modified by */
/*    Z. Drmac and Z. Bujanovic, Dept. of Mathematics, */
/*    University of Zagreb, Croatia. */
/*    June 2006. */
/*  For more details see LAPACK Working Note 176. */
/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --jpvt;
    --tau;
    --vn1;
    --vn2;
    --work;

    /* Function Body */
/* Computing MIN */
    i__1 = *m - *offset;
    mn = min(i__1,*n);
    tol3z = sqrt(dlamch_("Epsilon"));

/*     Compute factorization. */

    i__1 = mn;
    for (i__ = 1; i__ <= i__1; ++i__) {

	offpi = *offset + i__;

/*        Determine ith pivot column and swap if necessary. */

	i__2 = *n - i__ + 1;
	pvt = i__ - 1 + idamax_(&i__2, &vn1[i__], &c__1);

	if (pvt != i__) {
	    dswap_(m, &a[pvt * a_dim1 + 1], &c__1, &a[i__ * a_dim1 + 1], &
		    c__1);
	    itemp = jpvt[pvt];
	    jpvt[pvt] = jpvt[i__];
	    jpvt[i__] = itemp;
	    vn1[pvt] = vn1[i__];
	    vn2[pvt] = vn2[i__];
	}

/*        Generate elementary reflector H(i). */

	if (offpi < *m) {
	    i__2 = *m - offpi + 1;
	    dlarfp_(&i__2, &a[offpi + i__ * a_dim1], &a[offpi + 1 + i__ *
		    a_dim1], &c__1, &tau[i__]);
	} else {
	    dlarfp_(&c__1, &a[*m + i__ * a_dim1], &a[*m + i__ * a_dim1], &
		    c__1, &tau[i__]);
	}

	if (i__ <= *n) {

/*           Apply H(i)' to A(offset+i:m,i+1:n) from the left. */

	    aii = a[offpi + i__ * a_dim1];
	    a[offpi + i__ * a_dim1] = 1.;
	    i__2 = *m - offpi + 1;
	    i__3 = *n - i__;
	    dlarf_("Left", &i__2, &i__3, &a[offpi + i__ * a_dim1], &c__1, &
		    tau[i__], &a[offpi + (i__ + 1) * a_dim1], lda, &work[1]);
	    a[offpi + i__ * a_dim1] = aii;
	}

/*        Update partial column norms. */

	i__2 = *n;
	for (j = i__ + 1; j <= i__2; ++j) {
	    if (vn1[j] != 0.) {

/*              NOTE: The following 4 lines follow from the analysis in */
/*              Lapack Working Note 176. */

/* Computing 2nd power */
		d__2 = (d__1 = a[offpi + j * a_dim1], abs(d__1)) / vn1[j];
		temp = 1. - d__2 * d__2;
		temp = max(temp,0.);
/* Computing 2nd power */
		d__1 = vn1[j] / vn2[j];
		temp2 = temp * (d__1 * d__1);
		if (temp2 <= tol3z) {
		    if (offpi < *m) {
			i__3 = *m - offpi;
			vn1[j] = dnrm2_(&i__3, &a[offpi + 1 + j * a_dim1], &
				c__1);
			vn2[j] = vn1[j];
		    } else {
			vn1[j] = 0.;
			vn2[j] = 0.;
		    }
		} else {
		    vn1[j] *= sqrt(temp);
		}
	    }
/* L10: */
	}

/* L20: */
    }

    return 0;

/*     End of DLAQP2 */

} /* dlaqp2_ */

/* Subroutine */ int dlaqps_(integer *m, integer *n, integer *offset, integer
	*nb, integer *kb, doublereal *a, integer *lda, integer *jpvt,
	doublereal *tau, doublereal *vn1, doublereal *vn2, doublereal *auxv,
	doublereal *f, integer *ldf)
{
    /* Table of constant values */

    integer c__1 = 1;
    doublereal c_b8 = -1.;
    doublereal c_b9 = 1.;
    doublereal c_b16 = 0.;

    /* System generated locals */
    integer a_dim1, a_offset, f_dim1, f_offset, i__1, i__2;
    doublereal d__1, d__2;

    /* Local variables */
    integer j, k, rk;
    doublereal akk;
    integer pvt;
    doublereal temp;
    extern doublereal dnrm2_(integer *, doublereal *, integer *);
    doublereal temp2, tol3z;
    extern /* Subroutine */ int dgemm_(char *, char *, integer *, integer *,
	    integer *, doublereal *, doublereal *, integer *, doublereal *,
	    integer *, doublereal *, doublereal *, integer *),
	     dgemv_(char *, integer *, integer *, doublereal *, doublereal *,
	    integer *, doublereal *, integer *, doublereal *, doublereal *,
	    integer *);
    integer itemp;
    extern /* Subroutine */ int dswap_(integer *, doublereal *, integer *,
	    doublereal *, integer *);
    extern doublereal dlamch_(char *);
    extern integer idamax_(integer *, doublereal *, integer *);
    extern /* Subroutine */ int dlarfp_(integer *, doublereal *, doublereal *,
	     integer *, doublereal *);
    integer lsticc, lastrk;


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLAQPS computes a step of QR factorization with column pivoting */
/*  of a real M-by-N matrix A by using Blas-3.  It tries to factorize */
/*  NB columns from A starting from the row OFFSET+1, and updates all */
/*  of the matrix with Blas-3 xGEMM. */

/*  In some cases, due to catastrophic cancellations, it cannot */
/*  factorize NB columns.  Hence, the actual number of factorized */
/*  columns is returned in KB. */

/*  Block A(1:OFFSET,1:N) is accordingly pivoted, but not factorized. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A. M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A. N >= 0 */

/*  OFFSET  (input) INTEGER */
/*          The number of rows of A that have been factorized in */
/*          previous steps. */

/*  NB      (input) INTEGER */
/*          The number of columns to factorize. */

/*  KB      (output) INTEGER */
/*          The number of columns actually factorized. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the M-by-N matrix A. */
/*          On exit, block A(OFFSET+1:M,1:KB) is the triangular */
/*          factor obtained and block A(1:OFFSET,1:N) has been */
/*          accordingly pivoted, but no factorized. */
/*          The rest of the matrix, block A(OFFSET+1:M,KB+1:N) has */
/*          been updated. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A. LDA >= max(1,M). */

/*  JPVT    (input/output) INTEGER array, dimension (N) */
/*          JPVT(I) = K <==> Column K of the full matrix A has been */
/*          permuted into position I in AP. */

/*  TAU     (output) DOUBLE PRECISION array, dimension (KB) */
/*          The scalar factors of the elementary reflectors. */

/*  VN1     (input/output) DOUBLE PRECISION array, dimension (N) */
/*          The vector with the partial column norms. */

/*  VN2     (input/output) DOUBLE PRECISION array, dimension (N) */
/*          The vector with the exact column norms. */

/*  AUXV    (input/output) DOUBLE PRECISION array, dimension (NB) */
/*          Auxiliar vector. */

/*  F       (input/output) DOUBLE PRECISION array, dimension (LDF,NB) */
/*          Matrix F' = L*Y'*A. */

/*  LDF     (input) INTEGER */
/*          The leading dimension of the array F. LDF >= max(1,N). */

/*  Further Details */
/*  =============== */

/*  Based on contributions by */
/*    G. Quintana-Orti, Depto. de Informatica, Universidad Jaime I, Spain */
/*    X. Sun, Computer Science Dept., Duke University, USA */

/*  Partial column norm updating strategy modified by */
/*    Z. Drmac and Z. Bujanovic, Dept. of Mathematics, */
/*    University of Zagreb, Croatia. */
/*    June 2006. */
/*  For more details see LAPACK Working Note 176. */
/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --jpvt;
    --tau;
    --vn1;
    --vn2;
    --auxv;
    f_dim1 = *ldf;
    f_offset = 1 + f_dim1;
    f -= f_offset;

    /* Function Body */
/* Computing MIN */
    i__1 = *m, i__2 = *n + *offset;
    lastrk = min(i__1,i__2);
    lsticc = 0;
    k = 0;
    tol3z = sqrt(dlamch_("Epsilon"));

/*     Beginning of while loop. */

L10:
    if (k < *nb && lsticc == 0) {
	++k;
	rk = *offset + k;

/*        Determine ith pivot column and swap if necessary */

	i__1 = *n - k + 1;
	pvt = k - 1 + idamax_(&i__1, &vn1[k], &c__1);
	if (pvt != k) {
	    dswap_(m, &a[pvt * a_dim1 + 1], &c__1, &a[k * a_dim1 + 1], &c__1);
	    i__1 = k - 1;
	    dswap_(&i__1, &f[pvt + f_dim1], ldf, &f[k + f_dim1], ldf);
	    itemp = jpvt[pvt];
	    jpvt[pvt] = jpvt[k];
	    jpvt[k] = itemp;
	    vn1[pvt] = vn1[k];
	    vn2[pvt] = vn2[k];
	}

/*        Apply previous Householder reflectors to column K: */
/*        A(RK:M,K) := A(RK:M,K) - A(RK:M,1:K-1)*F(K,1:K-1)'. */

	if (k > 1) {
	    i__1 = *m - rk + 1;
	    i__2 = k - 1;
	    dgemv_("No transpose", &i__1, &i__2, &c_b8, &a[rk + a_dim1], lda,
		    &f[k + f_dim1], ldf, &c_b9, &a[rk + k * a_dim1], &c__1);
	}

/*        Generate elementary reflector H(k). */

	if (rk < *m) {
	    i__1 = *m - rk + 1;
	    dlarfp_(&i__1, &a[rk + k * a_dim1], &a[rk + 1 + k * a_dim1], &
		    c__1, &tau[k]);
	} else {
	    dlarfp_(&c__1, &a[rk + k * a_dim1], &a[rk + k * a_dim1], &c__1, &
		    tau[k]);
	}

	akk = a[rk + k * a_dim1];
	a[rk + k * a_dim1] = 1.;

/*        Compute Kth column of F: */

/*        Compute  F(K+1:N,K) := tau(K)*A(RK:M,K+1:N)'*A(RK:M,K). */

	if (k < *n) {
	    i__1 = *m - rk + 1;
	    i__2 = *n - k;
	    dgemv_("Transpose", &i__1, &i__2, &tau[k], &a[rk + (k + 1) *
		    a_dim1], lda, &a[rk + k * a_dim1], &c__1, &c_b16, &f[k +
		    1 + k * f_dim1], &c__1);
	}

/*        Padding F(1:K,K) with zeros. */

	i__1 = k;
	for (j = 1; j <= i__1; ++j) {
	    f[j + k * f_dim1] = 0.;
/* L20: */
	}

/*        Incremental updating of F: */
/*        F(1:N,K) := F(1:N,K) - tau(K)*F(1:N,1:K-1)*A(RK:M,1:K-1)' */
/*                    *A(RK:M,K). */

	if (k > 1) {
	    i__1 = *m - rk + 1;
	    i__2 = k - 1;
	    d__1 = -tau[k];
	    dgemv_("Transpose", &i__1, &i__2, &d__1, &a[rk + a_dim1], lda, &a[
		    rk + k * a_dim1], &c__1, &c_b16, &auxv[1], &c__1);

	    i__1 = k - 1;
	    dgemv_("No transpose", n, &i__1, &c_b9, &f[f_dim1 + 1], ldf, &
		    auxv[1], &c__1, &c_b9, &f[k * f_dim1 + 1], &c__1);
	}

/*        Update the current row of A: */
/*        A(RK,K+1:N) := A(RK,K+1:N) - A(RK,1:K)*F(K+1:N,1:K)'. */

	if (k < *n) {
	    i__1 = *n - k;
	    dgemv_("No transpose", &i__1, &k, &c_b8, &f[k + 1 + f_dim1], ldf,
		    &a[rk + a_dim1], lda, &c_b9, &a[rk + (k + 1) * a_dim1],
		    lda);
	}

/*        Update partial column norms. */

	if (rk < lastrk) {
	    i__1 = *n;
	    for (j = k + 1; j <= i__1; ++j) {
		if (vn1[j] != 0.) {

/*                 NOTE: The following 4 lines follow from the analysis in */
/*                 Lapack Working Note 176. */

		    temp = (d__1 = a[rk + j * a_dim1], abs(d__1)) / vn1[j];
/* Computing MAX */
		    d__1 = 0., d__2 = (temp + 1.) * (1. - temp);
		    temp = max(d__1,d__2);
/* Computing 2nd power */
		    d__1 = vn1[j] / vn2[j];
		    temp2 = temp * (d__1 * d__1);
		    if (temp2 <= tol3z) {
			vn2[j] = (doublereal) lsticc;
			lsticc = j;
		    } else {
			vn1[j] *= sqrt(temp);
		    }
		}
/* L30: */
	    }
	}

	a[rk + k * a_dim1] = akk;

/*        End of while loop. */

	goto L10;
    }
    *kb = k;
    rk = *offset + *kb;

/*     Apply the block reflector to the rest of the matrix: */
/*     A(OFFSET+KB+1:M,KB+1:N) := A(OFFSET+KB+1:M,KB+1:N) - */
/*                         A(OFFSET+KB+1:M,1:KB)*F(KB+1:N,1:KB)'. */

/* Computing MIN */
    i__1 = *n, i__2 = *m - *offset;
    if (*kb < min(i__1,i__2)) {
	i__1 = *m - rk;
	i__2 = *n - *kb;
	dgemm_("No transpose", "Transpose", &i__1, &i__2, kb, &c_b8, &a[rk +
		1 + a_dim1], lda, &f[*kb + 1 + f_dim1], ldf, &c_b9, &a[rk + 1
		+ (*kb + 1) * a_dim1], lda);
    }

/*     Recomputation of difficult columns. */

L40:
    if (lsticc > 0) {
	itemp = i_dnnt(&vn2[lsticc]);
	i__1 = *m - rk;
	vn1[lsticc] = dnrm2_(&i__1, &a[rk + 1 + lsticc * a_dim1], &c__1);

/*        NOTE: The computation of VN1( LSTICC ) relies on the fact that */
/*        SNRM2 does not fail on vectors with norm below the value of */
/*        SQRT(DLAMCH('S')) */

	vn2[lsticc] = vn1[lsticc];
	lsticc = itemp;
	goto L40;
    }

    return 0;

/*     End of DLAQPS */

} /* dlaqps_ */

/* Subroutine */ int dlarf_(char *side, integer *m, integer *n, doublereal *v,
	 integer *incv, doublereal *tau, doublereal *c__, integer *ldc,
	doublereal *work)
{
    /* Table of constant values */

    doublereal c_b4 = 1.;
    doublereal c_b5 = 0.;
    integer c__1 = 1;

    /* System generated locals */
    integer c_dim1, c_offset;
    doublereal d__1;

    /* Local variables */
    integer i__;
    logical applyleft;
    extern /* Subroutine */ int dger_(integer *, integer *, doublereal *,
	    doublereal *, integer *, doublereal *, integer *, doublereal *,
	    integer *);
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int dgemv_(char *, integer *, integer *,
	    doublereal *, doublereal *, integer *, doublereal *, integer *,
	    doublereal *, doublereal *, integer *);
    integer lastc, lastv;
    extern integer iladlc_(integer *, integer *, doublereal *, integer *),
	    iladlr_(integer *, integer *, doublereal *, integer *);


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLARF applies a real elementary reflector H to a real m by n matrix */
/*  C, from either the left or the right. H is represented in the form */

/*        H = I - tau * v * v' */

/*  where tau is a real scalar and v is a real vector. */

/*  If tau = 0, then H is taken to be the unit matrix. */

/*  Arguments */
/*  ========= */

/*  SIDE    (input) CHARACTER*1 */
/*          = 'L': form  H * C */
/*          = 'R': form  C * H */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix C. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix C. */

/*  V       (input) DOUBLE PRECISION array, dimension */
/*                     (1 + (M-1)*abs(INCV)) if SIDE = 'L' */
/*                  or (1 + (N-1)*abs(INCV)) if SIDE = 'R' */
/*          The vector v in the representation of H. V is not used if */
/*          TAU = 0. */

/*  INCV    (input) INTEGER */
/*          The increment between elements of v. INCV <> 0. */

/*  TAU     (input) DOUBLE PRECISION */
/*          The value tau in the representation of H. */

/*  C       (input/output) DOUBLE PRECISION array, dimension (LDC,N) */
/*          On entry, the m by n matrix C. */
/*          On exit, C is overwritten by the matrix H * C if SIDE = 'L', */
/*          or C * H if SIDE = 'R'. */

/*  LDC     (input) INTEGER */
/*          The leading dimension of the array C. LDC >= max(1,M). */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension */
/*                         (N) if SIDE = 'L' */
/*                      or (M) if SIDE = 'R' */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    --v;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    --work;

    /* Function Body */
    applyleft = lsame_(side, "L");
    lastv = 0;
    lastc = 0;
    if (*tau != 0.) {
/*     Set up variables for scanning V.  LASTV begins pointing to the end */
/*     of V. */
	if (applyleft) {
	    lastv = *m;
	} else {
	    lastv = *n;
	}
	if (*incv > 0) {
	    i__ = (lastv - 1) * *incv + 1;
	} else {
	    i__ = 1;
	}
/*     Look for the last non-zero row in V. */
	while(lastv > 0 && v[i__] == 0.) {
	    --lastv;
	    i__ -= *incv;
	}
	if (applyleft) {
/*     Scan for the last non-zero column in C(1:lastv,:). */
	    lastc = iladlc_(&lastv, n, &c__[c_offset], ldc);
	} else {
/*     Scan for the last non-zero row in C(:,1:lastv). */
	    lastc = iladlr_(m, &lastv, &c__[c_offset], ldc);
	}
    }
/*     Note that lastc.eq.0 renders the BLAS operations null; no special */
/*     case is needed at this level. */
    if (applyleft) {

/*        Form  H * C */

	if (lastv > 0) {

/*           w(1:lastc,1) := C(1:lastv,1:lastc)' * v(1:lastv,1) */

	    dgemv_("Transpose", &lastv, &lastc, &c_b4, &c__[c_offset], ldc, &
		    v[1], incv, &c_b5, &work[1], &c__1);

/*           C(1:lastv,1:lastc) := C(...) - v(1:lastv,1) * w(1:lastc,1)' */

	    d__1 = -(*tau);
	    dger_(&lastv, &lastc, &d__1, &v[1], incv, &work[1], &c__1, &c__[
		    c_offset], ldc);
	}
    } else {

/*        Form  C * H */

	if (lastv > 0) {

/*           w(1:lastc,1) := C(1:lastc,1:lastv) * v(1:lastv,1) */

	    dgemv_("No transpose", &lastc, &lastv, &c_b4, &c__[c_offset], ldc,
		     &v[1], incv, &c_b5, &work[1], &c__1);

/*           C(1:lastc,1:lastv) := C(...) - w(1:lastc,1) * v(1:lastv,1)' */

	    d__1 = -(*tau);
	    dger_(&lastc, &lastv, &d__1, &work[1], &c__1, &v[1], incv, &c__[
		    c_offset], ldc);
	}
    }
    return 0;

/*     End of DLARF */

} /* dlarf_ */

/* Subroutine */ int dlarfb_(char *side, char *trans, char *direct, char *
	storev, integer *m, integer *n, integer *k, doublereal *v, integer *
	ldv, doublereal *t, integer *ldt, doublereal *c__, integer *ldc,
	doublereal *work, integer *ldwork)
{
    /* Table of constant values */

    integer c__1 = 1;
    doublereal c_b14 = 1.;
    doublereal c_b25 = -1.;

    /* System generated locals */
    integer c_dim1, c_offset, t_dim1, t_offset, v_dim1, v_offset, work_dim1,
	    work_offset, i__1, i__2;

    /* Local variables */
    integer i__, j;
    extern /* Subroutine */ int dgemm_(char *, char *, integer *, integer *,
	    integer *, doublereal *, doublereal *, integer *, doublereal *,
	    integer *, doublereal *, doublereal *, integer *);
    extern logical lsame_(char *, char *);
    integer lastc;
    extern /* Subroutine */ int dcopy_(integer *, doublereal *, integer *,
	    doublereal *, integer *), dtrmm_(char *, char *, char *, char *,
	    integer *, integer *, doublereal *, doublereal *, integer *,
	    doublereal *, integer *);
    integer lastv;
    extern integer iladlc_(integer *, integer *, doublereal *, integer *),
	    iladlr_(integer *, integer *, doublereal *, integer *);
    char transt[1];


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLARFB applies a real block reflector H or its transpose H' to a */
/*  real m by n matrix C, from either the left or the right. */

/*  Arguments */
/*  ========= */

/*  SIDE    (input) CHARACTER*1 */
/*          = 'L': apply H or H' from the Left */
/*          = 'R': apply H or H' from the Right */

/*  TRANS   (input) CHARACTER*1 */
/*          = 'N': apply H (No transpose) */
/*          = 'T': apply H' (Transpose) */

/*  DIRECT  (input) CHARACTER*1 */
/*          Indicates how H is formed from a product of elementary */
/*          reflectors */
/*          = 'F': H = H(1) H(2) . . . H(k) (Forward) */
/*          = 'B': H = H(k) . . . H(2) H(1) (Backward) */

/*  STOREV  (input) CHARACTER*1 */
/*          Indicates how the vectors which define the elementary */
/*          reflectors are stored: */
/*          = 'C': Columnwise */
/*          = 'R': Rowwise */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix C. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix C. */

/*  K       (input) INTEGER */
/*          The order of the matrix T (= the number of elementary */
/*          reflectors whose product defines the block reflector). */

/*  V       (input) DOUBLE PRECISION array, dimension */
/*                                (LDV,K) if STOREV = 'C' */
/*                                (LDV,M) if STOREV = 'R' and SIDE = 'L' */
/*                                (LDV,N) if STOREV = 'R' and SIDE = 'R' */
/*          The matrix V. See further details. */

/*  LDV     (input) INTEGER */
/*          The leading dimension of the array V. */
/*          If STOREV = 'C' and SIDE = 'L', LDV >= max(1,M); */
/*          if STOREV = 'C' and SIDE = 'R', LDV >= max(1,N); */
/*          if STOREV = 'R', LDV >= K. */

/*  T       (input) DOUBLE PRECISION array, dimension (LDT,K) */
/*          The triangular k by k matrix T in the representation of the */
/*          block reflector. */

/*  LDT     (input) INTEGER */
/*          The leading dimension of the array T. LDT >= K. */

/*  C       (input/output) DOUBLE PRECISION array, dimension (LDC,N) */
/*          On entry, the m by n matrix C. */
/*          On exit, C is overwritten by H*C or H'*C or C*H or C*H'. */

/*  LDC     (input) INTEGER */
/*          The leading dimension of the array C. LDA >= max(1,M). */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (LDWORK,K) */

/*  LDWORK  (input) INTEGER */
/*          The leading dimension of the array WORK. */
/*          If SIDE = 'L', LDWORK >= max(1,N); */
/*          if SIDE = 'R', LDWORK >= max(1,M). */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Quick return if possible */

    /* Parameter adjustments */
    v_dim1 = *ldv;
    v_offset = 1 + v_dim1;
    v -= v_offset;
    t_dim1 = *ldt;
    t_offset = 1 + t_dim1;
    t -= t_offset;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    work_dim1 = *ldwork;
    work_offset = 1 + work_dim1;
    work -= work_offset;

    /* Function Body */
    if (*m <= 0 || *n <= 0) {
	return 0;
    }

    if (lsame_(trans, "N")) {
	*(unsigned char *)transt = 'T';
    } else {
	*(unsigned char *)transt = 'N';
    }

    if (lsame_(storev, "C")) {

	if (lsame_(direct, "F")) {

/*           Let  V =  ( V1 )    (first K rows) */
/*                     ( V2 ) */
/*           where  V1  is unit lower triangular. */

	    if (lsame_(side, "L")) {

/*              Form  H * C  or  H' * C  where  C = ( C1 ) */
/*                                                  ( C2 ) */

/* Computing MAX */
		i__1 = *k, i__2 = iladlr_(m, k, &v[v_offset], ldv);
		lastv = max(i__1,i__2);
		lastc = iladlc_(&lastv, n, &c__[c_offset], ldc);

/*              W := C' * V  =  (C1'*V1 + C2'*V2)  (stored in WORK) */

/*              W := C1' */

		i__1 = *k;
		for (j = 1; j <= i__1; ++j) {
		    dcopy_(&lastc, &c__[j + c_dim1], ldc, &work[j * work_dim1
			    + 1], &c__1);
/* L10: */
		}

/*              W := W * V1 */

		dtrmm_("Right", "Lower", "No transpose", "Unit", &lastc, k, &
			c_b14, &v[v_offset], ldv, &work[work_offset], ldwork);
		if (lastv > *k) {

/*                 W := W + C2'*V2 */

		    i__1 = lastv - *k;
		    dgemm_("Transpose", "No transpose", &lastc, k, &i__1, &
			    c_b14, &c__[*k + 1 + c_dim1], ldc, &v[*k + 1 +
			    v_dim1], ldv, &c_b14, &work[work_offset], ldwork);
		}

/*              W := W * T'  or  W * T */

		dtrmm_("Right", "Upper", transt, "Non-unit", &lastc, k, &
			c_b14, &t[t_offset], ldt, &work[work_offset], ldwork);

/*              C := C - V * W' */

		if (lastv > *k) {

/*                 C2 := C2 - V2 * W' */

		    i__1 = lastv - *k;
		    dgemm_("No transpose", "Transpose", &i__1, &lastc, k, &
			    c_b25, &v[*k + 1 + v_dim1], ldv, &work[
			    work_offset], ldwork, &c_b14, &c__[*k + 1 +
			    c_dim1], ldc);
		}

/*              W := W * V1' */

		dtrmm_("Right", "Lower", "Transpose", "Unit", &lastc, k, &
			c_b14, &v[v_offset], ldv, &work[work_offset], ldwork);

/*              C1 := C1 - W' */

		i__1 = *k;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = lastc;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			c__[j + i__ * c_dim1] -= work[i__ + j * work_dim1];
/* L20: */
		    }
/* L30: */
		}

	    } else if (lsame_(side, "R")) {

/*              Form  C * H  or  C * H'  where  C = ( C1  C2 ) */

/* Computing MAX */
		i__1 = *k, i__2 = iladlr_(n, k, &v[v_offset], ldv);
		lastv = max(i__1,i__2);
		lastc = iladlr_(m, &lastv, &c__[c_offset], ldc);

/*              W := C * V  =  (C1*V1 + C2*V2)  (stored in WORK) */

/*              W := C1 */

		i__1 = *k;
		for (j = 1; j <= i__1; ++j) {
		    dcopy_(&lastc, &c__[j * c_dim1 + 1], &c__1, &work[j *
			    work_dim1 + 1], &c__1);
/* L40: */
		}

/*              W := W * V1 */

		dtrmm_("Right", "Lower", "No transpose", "Unit", &lastc, k, &
			c_b14, &v[v_offset], ldv, &work[work_offset], ldwork);
		if (lastv > *k) {

/*                 W := W + C2 * V2 */

		    i__1 = lastv - *k;
		    dgemm_("No transpose", "No transpose", &lastc, k, &i__1, &
			    c_b14, &c__[(*k + 1) * c_dim1 + 1], ldc, &v[*k +
			    1 + v_dim1], ldv, &c_b14, &work[work_offset],
			    ldwork);
		}

/*              W := W * T  or  W * T' */

		dtrmm_("Right", "Upper", trans, "Non-unit", &lastc, k, &c_b14,
			 &t[t_offset], ldt, &work[work_offset], ldwork);

/*              C := C - W * V' */

		if (lastv > *k) {

/*                 C2 := C2 - W * V2' */

		    i__1 = lastv - *k;
		    dgemm_("No transpose", "Transpose", &lastc, &i__1, k, &
			    c_b25, &work[work_offset], ldwork, &v[*k + 1 +
			    v_dim1], ldv, &c_b14, &c__[(*k + 1) * c_dim1 + 1],
			     ldc);
		}

/*              W := W * V1' */

		dtrmm_("Right", "Lower", "Transpose", "Unit", &lastc, k, &
			c_b14, &v[v_offset], ldv, &work[work_offset], ldwork);

/*              C1 := C1 - W */

		i__1 = *k;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = lastc;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			c__[i__ + j * c_dim1] -= work[i__ + j * work_dim1];
/* L50: */
		    }
/* L60: */
		}
	    }

	} else {

/*           Let  V =  ( V1 ) */
/*                     ( V2 )    (last K rows) */
/*           where  V2  is unit upper triangular. */

	    if (lsame_(side, "L")) {

/*              Form  H * C  or  H' * C  where  C = ( C1 ) */
/*                                                  ( C2 ) */

/* Computing MAX */
		i__1 = *k, i__2 = iladlr_(m, k, &v[v_offset], ldv);
		lastv = max(i__1,i__2);
		lastc = iladlc_(&lastv, n, &c__[c_offset], ldc);

/*              W := C' * V  =  (C1'*V1 + C2'*V2)  (stored in WORK) */

/*              W := C2' */

		i__1 = *k;
		for (j = 1; j <= i__1; ++j) {
		    dcopy_(&lastc, &c__[lastv - *k + j + c_dim1], ldc, &work[
			    j * work_dim1 + 1], &c__1);
/* L70: */
		}

/*              W := W * V2 */

		dtrmm_("Right", "Upper", "No transpose", "Unit", &lastc, k, &
			c_b14, &v[lastv - *k + 1 + v_dim1], ldv, &work[
			work_offset], ldwork);
		if (lastv > *k) {

/*                 W := W + C1'*V1 */

		    i__1 = lastv - *k;
		    dgemm_("Transpose", "No transpose", &lastc, k, &i__1, &
			    c_b14, &c__[c_offset], ldc, &v[v_offset], ldv, &
			    c_b14, &work[work_offset], ldwork);
		}

/*              W := W * T'  or  W * T */

		dtrmm_("Right", "Lower", transt, "Non-unit", &lastc, k, &
			c_b14, &t[t_offset], ldt, &work[work_offset], ldwork);

/*              C := C - V * W' */

		if (lastv > *k) {

/*                 C1 := C1 - V1 * W' */

		    i__1 = lastv - *k;
		    dgemm_("No transpose", "Transpose", &i__1, &lastc, k, &
			    c_b25, &v[v_offset], ldv, &work[work_offset],
			    ldwork, &c_b14, &c__[c_offset], ldc);
		}

/*              W := W * V2' */

		dtrmm_("Right", "Upper", "Transpose", "Unit", &lastc, k, &
			c_b14, &v[lastv - *k + 1 + v_dim1], ldv, &work[
			work_offset], ldwork);

/*              C2 := C2 - W' */

		i__1 = *k;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = lastc;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			c__[lastv - *k + j + i__ * c_dim1] -= work[i__ + j *
				work_dim1];
/* L80: */
		    }
/* L90: */
		}

	    } else if (lsame_(side, "R")) {

/*              Form  C * H  or  C * H'  where  C = ( C1  C2 ) */

/* Computing MAX */
		i__1 = *k, i__2 = iladlr_(n, k, &v[v_offset], ldv);
		lastv = max(i__1,i__2);
		lastc = iladlr_(m, &lastv, &c__[c_offset], ldc);

/*              W := C * V  =  (C1*V1 + C2*V2)  (stored in WORK) */

/*              W := C2 */

		i__1 = *k;
		for (j = 1; j <= i__1; ++j) {
		    dcopy_(&lastc, &c__[(*n - *k + j) * c_dim1 + 1], &c__1, &
			    work[j * work_dim1 + 1], &c__1);
/* L100: */
		}

/*              W := W * V2 */

		dtrmm_("Right", "Upper", "No transpose", "Unit", &lastc, k, &
			c_b14, &v[lastv - *k + 1 + v_dim1], ldv, &work[
			work_offset], ldwork);
		if (lastv > *k) {

/*                 W := W + C1 * V1 */

		    i__1 = lastv - *k;
		    dgemm_("No transpose", "No transpose", &lastc, k, &i__1, &
			    c_b14, &c__[c_offset], ldc, &v[v_offset], ldv, &
			    c_b14, &work[work_offset], ldwork);
		}

/*              W := W * T  or  W * T' */

		dtrmm_("Right", "Lower", trans, "Non-unit", &lastc, k, &c_b14,
			 &t[t_offset], ldt, &work[work_offset], ldwork);

/*              C := C - W * V' */

		if (lastv > *k) {

/*                 C1 := C1 - W * V1' */

		    i__1 = lastv - *k;
		    dgemm_("No transpose", "Transpose", &lastc, &i__1, k, &
			    c_b25, &work[work_offset], ldwork, &v[v_offset],
			    ldv, &c_b14, &c__[c_offset], ldc);
		}

/*              W := W * V2' */

		dtrmm_("Right", "Upper", "Transpose", "Unit", &lastc, k, &
			c_b14, &v[lastv - *k + 1 + v_dim1], ldv, &work[
			work_offset], ldwork);

/*              C2 := C2 - W */

		i__1 = *k;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = lastc;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			c__[i__ + (lastv - *k + j) * c_dim1] -= work[i__ + j *
				 work_dim1];
/* L110: */
		    }
/* L120: */
		}
	    }
	}

    } else if (lsame_(storev, "R")) {

	if (lsame_(direct, "F")) {

/*           Let  V =  ( V1  V2 )    (V1: first K columns) */
/*           where  V1  is unit upper triangular. */

	    if (lsame_(side, "L")) {

/*              Form  H * C  or  H' * C  where  C = ( C1 ) */
/*                                                  ( C2 ) */

/* Computing MAX */
		i__1 = *k, i__2 = iladlc_(k, m, &v[v_offset], ldv);
		lastv = max(i__1,i__2);
		lastc = iladlc_(&lastv, n, &c__[c_offset], ldc);

/*              W := C' * V'  =  (C1'*V1' + C2'*V2') (stored in WORK) */

/*              W := C1' */

		i__1 = *k;
		for (j = 1; j <= i__1; ++j) {
		    dcopy_(&lastc, &c__[j + c_dim1], ldc, &work[j * work_dim1
			    + 1], &c__1);
/* L130: */
		}

/*              W := W * V1' */

		dtrmm_("Right", "Upper", "Transpose", "Unit", &lastc, k, &
			c_b14, &v[v_offset], ldv, &work[work_offset], ldwork);
		if (lastv > *k) {

/*                 W := W + C2'*V2' */

		    i__1 = lastv - *k;
		    dgemm_("Transpose", "Transpose", &lastc, k, &i__1, &c_b14,
			     &c__[*k + 1 + c_dim1], ldc, &v[(*k + 1) * v_dim1
			    + 1], ldv, &c_b14, &work[work_offset], ldwork);
		}

/*              W := W * T'  or  W * T */

		dtrmm_("Right", "Upper", transt, "Non-unit", &lastc, k, &
			c_b14, &t[t_offset], ldt, &work[work_offset], ldwork);

/*              C := C - V' * W' */

		if (lastv > *k) {

/*                 C2 := C2 - V2' * W' */

		    i__1 = lastv - *k;
		    dgemm_("Transpose", "Transpose", &i__1, &lastc, k, &c_b25,
			     &v[(*k + 1) * v_dim1 + 1], ldv, &work[
			    work_offset], ldwork, &c_b14, &c__[*k + 1 +
			    c_dim1], ldc);
		}

/*              W := W * V1 */

		dtrmm_("Right", "Upper", "No transpose", "Unit", &lastc, k, &
			c_b14, &v[v_offset], ldv, &work[work_offset], ldwork);

/*              C1 := C1 - W' */

		i__1 = *k;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = lastc;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			c__[j + i__ * c_dim1] -= work[i__ + j * work_dim1];
/* L140: */
		    }
/* L150: */
		}

	    } else if (lsame_(side, "R")) {

/*              Form  C * H  or  C * H'  where  C = ( C1  C2 ) */

/* Computing MAX */
		i__1 = *k, i__2 = iladlc_(k, n, &v[v_offset], ldv);
		lastv = max(i__1,i__2);
		lastc = iladlr_(m, &lastv, &c__[c_offset], ldc);

/*              W := C * V'  =  (C1*V1' + C2*V2')  (stored in WORK) */

/*              W := C1 */

		i__1 = *k;
		for (j = 1; j <= i__1; ++j) {
		    dcopy_(&lastc, &c__[j * c_dim1 + 1], &c__1, &work[j *
			    work_dim1 + 1], &c__1);
/* L160: */
		}

/*              W := W * V1' */

		dtrmm_("Right", "Upper", "Transpose", "Unit", &lastc, k, &
			c_b14, &v[v_offset], ldv, &work[work_offset], ldwork);
		if (lastv > *k) {

/*                 W := W + C2 * V2' */

		    i__1 = lastv - *k;
		    dgemm_("No transpose", "Transpose", &lastc, k, &i__1, &
			    c_b14, &c__[(*k + 1) * c_dim1 + 1], ldc, &v[(*k +
			    1) * v_dim1 + 1], ldv, &c_b14, &work[work_offset],
			     ldwork);
		}

/*              W := W * T  or  W * T' */

		dtrmm_("Right", "Upper", trans, "Non-unit", &lastc, k, &c_b14,
			 &t[t_offset], ldt, &work[work_offset], ldwork);

/*              C := C - W * V */

		if (lastv > *k) {

/*                 C2 := C2 - W * V2 */

		    i__1 = lastv - *k;
		    dgemm_("No transpose", "No transpose", &lastc, &i__1, k, &
			    c_b25, &work[work_offset], ldwork, &v[(*k + 1) *
			    v_dim1 + 1], ldv, &c_b14, &c__[(*k + 1) * c_dim1
			    + 1], ldc);
		}

/*              W := W * V1 */

		dtrmm_("Right", "Upper", "No transpose", "Unit", &lastc, k, &
			c_b14, &v[v_offset], ldv, &work[work_offset], ldwork);

/*              C1 := C1 - W */

		i__1 = *k;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = lastc;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			c__[i__ + j * c_dim1] -= work[i__ + j * work_dim1];
/* L170: */
		    }
/* L180: */
		}

	    }

	} else {

/*           Let  V =  ( V1  V2 )    (V2: last K columns) */
/*           where  V2  is unit lower triangular. */

	    if (lsame_(side, "L")) {

/*              Form  H * C  or  H' * C  where  C = ( C1 ) */
/*                                                  ( C2 ) */

/* Computing MAX */
		i__1 = *k, i__2 = iladlc_(k, m, &v[v_offset], ldv);
		lastv = max(i__1,i__2);
		lastc = iladlc_(&lastv, n, &c__[c_offset], ldc);

/*              W := C' * V'  =  (C1'*V1' + C2'*V2') (stored in WORK) */

/*              W := C2' */

		i__1 = *k;
		for (j = 1; j <= i__1; ++j) {
		    dcopy_(&lastc, &c__[lastv - *k + j + c_dim1], ldc, &work[
			    j * work_dim1 + 1], &c__1);
/* L190: */
		}

/*              W := W * V2' */

		dtrmm_("Right", "Lower", "Transpose", "Unit", &lastc, k, &
			c_b14, &v[(lastv - *k + 1) * v_dim1 + 1], ldv, &work[
			work_offset], ldwork);
		if (lastv > *k) {

/*                 W := W + C1'*V1' */

		    i__1 = lastv - *k;
		    dgemm_("Transpose", "Transpose", &lastc, k, &i__1, &c_b14,
			     &c__[c_offset], ldc, &v[v_offset], ldv, &c_b14, &
			    work[work_offset], ldwork);
		}

/*              W := W * T'  or  W * T */

		dtrmm_("Right", "Lower", transt, "Non-unit", &lastc, k, &
			c_b14, &t[t_offset], ldt, &work[work_offset], ldwork);

/*              C := C - V' * W' */

		if (lastv > *k) {

/*                 C1 := C1 - V1' * W' */

		    i__1 = lastv - *k;
		    dgemm_("Transpose", "Transpose", &i__1, &lastc, k, &c_b25,
			     &v[v_offset], ldv, &work[work_offset], ldwork, &
			    c_b14, &c__[c_offset], ldc);
		}

/*              W := W * V2 */

		dtrmm_("Right", "Lower", "No transpose", "Unit", &lastc, k, &
			c_b14, &v[(lastv - *k + 1) * v_dim1 + 1], ldv, &work[
			work_offset], ldwork);

/*              C2 := C2 - W' */

		i__1 = *k;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = lastc;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			c__[lastv - *k + j + i__ * c_dim1] -= work[i__ + j *
				work_dim1];
/* L200: */
		    }
/* L210: */
		}

	    } else if (lsame_(side, "R")) {

/*              Form  C * H  or  C * H'  where  C = ( C1  C2 ) */

/* Computing MAX */
		i__1 = *k, i__2 = iladlc_(k, n, &v[v_offset], ldv);
		lastv = max(i__1,i__2);
		lastc = iladlr_(m, &lastv, &c__[c_offset], ldc);

/*              W := C * V'  =  (C1*V1' + C2*V2')  (stored in WORK) */

/*              W := C2 */

		i__1 = *k;
		for (j = 1; j <= i__1; ++j) {
		    dcopy_(&lastc, &c__[(lastv - *k + j) * c_dim1 + 1], &c__1,
			     &work[j * work_dim1 + 1], &c__1);
/* L220: */
		}

/*              W := W * V2' */

		dtrmm_("Right", "Lower", "Transpose", "Unit", &lastc, k, &
			c_b14, &v[(lastv - *k + 1) * v_dim1 + 1], ldv, &work[
			work_offset], ldwork);
		if (lastv > *k) {

/*                 W := W + C1 * V1' */

		    i__1 = lastv - *k;
		    dgemm_("No transpose", "Transpose", &lastc, k, &i__1, &
			    c_b14, &c__[c_offset], ldc, &v[v_offset], ldv, &
			    c_b14, &work[work_offset], ldwork);
		}

/*              W := W * T  or  W * T' */

		dtrmm_("Right", "Lower", trans, "Non-unit", &lastc, k, &c_b14,
			 &t[t_offset], ldt, &work[work_offset], ldwork);

/*              C := C - W * V */

		if (lastv > *k) {

/*                 C1 := C1 - W * V1 */

		    i__1 = lastv - *k;
		    dgemm_("No transpose", "No transpose", &lastc, &i__1, k, &
			    c_b25, &work[work_offset], ldwork, &v[v_offset],
			    ldv, &c_b14, &c__[c_offset], ldc);
		}

/*              W := W * V2 */

		dtrmm_("Right", "Lower", "No transpose", "Unit", &lastc, k, &
			c_b14, &v[(lastv - *k + 1) * v_dim1 + 1], ldv, &work[
			work_offset], ldwork);

/*              C1 := C1 - W */

		i__1 = *k;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = lastc;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			c__[i__ + (lastv - *k + j) * c_dim1] -= work[i__ + j *
				 work_dim1];
/* L230: */
		    }
/* L240: */
		}

	    }

	}
    }

    return 0;

/*     End of DLARFB */

} /* dlarfb_ */

/* Subroutine */ int dlarfg_(integer *n, doublereal *alpha, doublereal *x,
	integer *incx, doublereal *tau)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Local variables */
    integer j, knt;
    doublereal beta;
    extern doublereal dnrm2_(integer *, doublereal *, integer *);
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *,
	    integer *);
    doublereal xnorm;
    extern doublereal dlapy2_(doublereal *, doublereal *), dlamch_(char *);
    doublereal safmin, rsafmn;


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLARFG generates a real elementary reflector H of order n, such */
/*  that */

/*        H * ( alpha ) = ( beta ),   H' * H = I. */
/*            (   x   )   (   0  ) */

/*  where alpha and beta are scalars, and x is an (n-1)-element real */
/*  vector. H is represented in the form */

/*        H = I - tau * ( 1 ) * ( 1 v' ) , */
/*                      ( v ) */

/*  where tau is a real scalar and v is a real (n-1)-element */
/*  vector. */

/*  If the elements of x are all zero, then tau = 0 and H is taken to be */
/*  the unit matrix. */

/*  Otherwise  1 <= tau <= 2. */

/*  Arguments */
/*  ========= */

/*  N       (input) INTEGER */
/*          The order of the elementary reflector. */

/*  ALPHA   (input/output) DOUBLE PRECISION */
/*          On entry, the value alpha. */
/*          On exit, it is overwritten with the value beta. */

/*  X       (input/output) DOUBLE PRECISION array, dimension */
/*                         (1+(N-2)*abs(INCX)) */
/*          On entry, the vector x. */
/*          On exit, it is overwritten with the vector v. */

/*  INCX    (input) INTEGER */
/*          The increment between elements of X. INCX > 0. */

/*  TAU     (output) DOUBLE PRECISION */
/*          The value tau. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    --x;

    /* Function Body */
    if (*n <= 1) {
	*tau = 0.;
	return 0;
    }

    i__1 = *n - 1;
    xnorm = dnrm2_(&i__1, &x[1], incx);

    if (xnorm == 0.) {

/*        H  =  I */

	*tau = 0.;
    } else {

/*        general case */

	d__1 = dlapy2_(alpha, &xnorm);
	beta = -d_sign(&d__1, alpha);
	safmin = dlamch_("S") / dlamch_("E");
	knt = 0;
	if (abs(beta) < safmin) {

/*           XNORM, BETA may be inaccurate; scale X and recompute them */

	    rsafmn = 1. / safmin;
L10:
	    ++knt;
	    i__1 = *n - 1;
	    dscal_(&i__1, &rsafmn, &x[1], incx);
	    beta *= rsafmn;
	    *alpha *= rsafmn;
	    if (abs(beta) < safmin) {
		goto L10;
	    }

/*           New BETA is at most 1, at least SAFMIN */

	    i__1 = *n - 1;
	    xnorm = dnrm2_(&i__1, &x[1], incx);
	    d__1 = dlapy2_(alpha, &xnorm);
	    beta = -d_sign(&d__1, alpha);
	}
	*tau = (beta - *alpha) / beta;
	i__1 = *n - 1;
	d__1 = 1. / (*alpha - beta);
	dscal_(&i__1, &d__1, &x[1], incx);

/*        If ALPHA is subnormal, it may lose relative accuracy */

	i__1 = knt;
	for (j = 1; j <= i__1; ++j) {
	    beta *= safmin;
/* L20: */
	}
	*alpha = beta;
    }

    return 0;

/*     End of DLARFG */

} /* dlarfg_ */

/* Subroutine */ int dlarfp_(integer *n, doublereal *alpha, doublereal *x,
	integer *incx, doublereal *tau)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Local variables */
    integer j, knt;
    doublereal beta;
    extern doublereal dnrm2_(integer *, doublereal *, integer *);
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *,
	    integer *);
    doublereal xnorm;
    extern doublereal dlapy2_(doublereal *, doublereal *), dlamch_(char *);
    doublereal safmin, rsafmn;


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLARFP generates a real elementary reflector H of order n, such */
/*  that */

/*        H * ( alpha ) = ( beta ),   H' * H = I. */
/*            (   x   )   (   0  ) */

/*  where alpha and beta are scalars, beta is non-negative, and x is */
/*  an (n-1)-element real vector.  H is represented in the form */

/*        H = I - tau * ( 1 ) * ( 1 v' ) , */
/*                      ( v ) */

/*  where tau is a real scalar and v is a real (n-1)-element */
/*  vector. */

/*  If the elements of x are all zero, then tau = 0 and H is taken to be */
/*  the unit matrix. */

/*  Otherwise  1 <= tau <= 2. */

/*  Arguments */
/*  ========= */

/*  N       (input) INTEGER */
/*          The order of the elementary reflector. */

/*  ALPHA   (input/output) DOUBLE PRECISION */
/*          On entry, the value alpha. */
/*          On exit, it is overwritten with the value beta. */

/*  X       (input/output) DOUBLE PRECISION array, dimension */
/*                         (1+(N-2)*abs(INCX)) */
/*          On entry, the vector x. */
/*          On exit, it is overwritten with the vector v. */

/*  INCX    (input) INTEGER */
/*          The increment between elements of X. INCX > 0. */

/*  TAU     (output) DOUBLE PRECISION */
/*          The value tau. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    --x;

    /* Function Body */
    if (*n <= 0) {
	*tau = 0.;
	return 0;
    }

    i__1 = *n - 1;
    xnorm = dnrm2_(&i__1, &x[1], incx);

    if (xnorm == 0.) {

/*        H  =  [+/-1, 0; I], sign chosen so ALPHA >= 0 */

	if (*alpha >= 0.) {
/*           When TAU.eq.ZERO, the vector is special-cased to be */
/*           all zeros in the application routines.  We do not need */
/*           to clear it. */
	    *tau = 0.;
	} else {
/*           However, the application routines rely on explicit */
/*           zero checks when TAU.ne.ZERO, and we must clear X. */
	    *tau = 2.;
	    i__1 = *n - 1;
	    for (j = 1; j <= i__1; ++j) {
		x[(j - 1) * *incx + 1] = 0.;
	    }
	    *alpha = -(*alpha);
	}
    } else {

/*        general case */

	d__1 = dlapy2_(alpha, &xnorm);
	beta = d_sign(&d__1, alpha);
	safmin = dlamch_("S") / dlamch_("E");
	knt = 0;
	if (abs(beta) < safmin) {

/*           XNORM, BETA may be inaccurate; scale X and recompute them */

	    rsafmn = 1. / safmin;
L10:
	    ++knt;
	    i__1 = *n - 1;
	    dscal_(&i__1, &rsafmn, &x[1], incx);
	    beta *= rsafmn;
	    *alpha *= rsafmn;
	    if (abs(beta) < safmin) {
		goto L10;
	    }

/*           New BETA is at most 1, at least SAFMIN */

	    i__1 = *n - 1;
	    xnorm = dnrm2_(&i__1, &x[1], incx);
	    d__1 = dlapy2_(alpha, &xnorm);
	    beta = d_sign(&d__1, alpha);
	}
	*alpha += beta;
	if (beta < 0.) {
	    beta = -beta;
	    *tau = -(*alpha) / beta;
	} else {
	    *alpha = xnorm * (xnorm / *alpha);
	    *tau = *alpha / beta;
	    *alpha = -(*alpha);
	}
	i__1 = *n - 1;
	d__1 = 1. / *alpha;
	dscal_(&i__1, &d__1, &x[1], incx);

/*        If BETA is subnormal, it may lose relative accuracy */

	i__1 = knt;
	for (j = 1; j <= i__1; ++j) {
	    beta *= safmin;
/* L20: */
	}
	*alpha = beta;
    }

    return 0;

/*     End of DLARFP */

} /* dlarfp_ */

/* Subroutine */ int dlarft_(char *direct, char *storev, integer *n, integer *
	k, doublereal *v, integer *ldv, doublereal *tau, doublereal *t,
	integer *ldt)
{
    /* Table of constant values */

    integer c__1 = 1;
    doublereal c_b8 = 0.;

    /* System generated locals */
    integer t_dim1, t_offset, v_dim1, v_offset, i__1, i__2, i__3;
    doublereal d__1;

    /* Local variables */
    integer i__, j, prevlastv;
    doublereal vii;
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int dgemv_(char *, integer *, integer *,
	    doublereal *, doublereal *, integer *, doublereal *, integer *,
	    doublereal *, doublereal *, integer *);
    integer lastv;
    extern /* Subroutine */ int dtrmv_(char *, char *, char *, integer *,
	    doublereal *, integer *, doublereal *, integer *);


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLARFT forms the triangular factor T of a real block reflector H */
/*  of order n, which is defined as a product of k elementary reflectors. */

/*  If DIRECT = 'F', H = H(1) H(2) . . . H(k) and T is upper triangular; */

/*  If DIRECT = 'B', H = H(k) . . . H(2) H(1) and T is lower triangular. */

/*  If STOREV = 'C', the vector which defines the elementary reflector */
/*  H(i) is stored in the i-th column of the array V, and */

/*     H  =  I - V * T * V' */

/*  If STOREV = 'R', the vector which defines the elementary reflector */
/*  H(i) is stored in the i-th row of the array V, and */

/*     H  =  I - V' * T * V */

/*  Arguments */
/*  ========= */

/*  DIRECT  (input) CHARACTER*1 */
/*          Specifies the order in which the elementary reflectors are */
/*          multiplied to form the block reflector: */
/*          = 'F': H = H(1) H(2) . . . H(k) (Forward) */
/*          = 'B': H = H(k) . . . H(2) H(1) (Backward) */

/*  STOREV  (input) CHARACTER*1 */
/*          Specifies how the vectors which define the elementary */
/*          reflectors are stored (see also Further Details): */
/*          = 'C': columnwise */
/*          = 'R': rowwise */

/*  N       (input) INTEGER */
/*          The order of the block reflector H. N >= 0. */

/*  K       (input) INTEGER */
/*          The order of the triangular factor T (= the number of */
/*          elementary reflectors). K >= 1. */

/*  V       (input/output) DOUBLE PRECISION array, dimension */
/*                               (LDV,K) if STOREV = 'C' */
/*                               (LDV,N) if STOREV = 'R' */
/*          The matrix V. See further details. */

/*  LDV     (input) INTEGER */
/*          The leading dimension of the array V. */
/*          If STOREV = 'C', LDV >= max(1,N); if STOREV = 'R', LDV >= K. */

/*  TAU     (input) DOUBLE PRECISION array, dimension (K) */
/*          TAU(i) must contain the scalar factor of the elementary */
/*          reflector H(i). */

/*  T       (output) DOUBLE PRECISION array, dimension (LDT,K) */
/*          The k by k triangular factor T of the block reflector. */
/*          If DIRECT = 'F', T is upper triangular; if DIRECT = 'B', T is */
/*          lower triangular. The rest of the array is not used. */

/*  LDT     (input) INTEGER */
/*          The leading dimension of the array T. LDT >= K. */

/*  Further Details */
/*  =============== */

/*  The shape of the matrix V and the storage of the vectors which define */
/*  the H(i) is best illustrated by the following example with n = 5 and */
/*  k = 3. The elements equal to 1 are not stored; the corresponding */
/*  array elements are modified but restored on exit. The rest of the */
/*  array is not used. */

/*  DIRECT = 'F' and STOREV = 'C':         DIRECT = 'F' and STOREV = 'R': */

/*               V = (  1       )                 V = (  1 v1 v1 v1 v1 ) */
/*                   ( v1  1    )                     (     1 v2 v2 v2 ) */
/*                   ( v1 v2  1 )                     (        1 v3 v3 ) */
/*                   ( v1 v2 v3 ) */
/*                   ( v1 v2 v3 ) */

/*  DIRECT = 'B' and STOREV = 'C':         DIRECT = 'B' and STOREV = 'R': */

/*               V = ( v1 v2 v3 )                 V = ( v1 v1  1       ) */
/*                   ( v1 v2 v3 )                     ( v2 v2 v2  1    ) */
/*                   (  1 v2 v3 )                     ( v3 v3 v3 v3  1 ) */
/*                   (     1 v3 ) */
/*                   (        1 ) */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Quick return if possible */

    /* Parameter adjustments */
    v_dim1 = *ldv;
    v_offset = 1 + v_dim1;
    v -= v_offset;
    --tau;
    t_dim1 = *ldt;
    t_offset = 1 + t_dim1;
    t -= t_offset;

    /* Function Body */
    if (*n == 0) {
	return 0;
    }

    if (lsame_(direct, "F")) {
	prevlastv = *n;
	i__1 = *k;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    prevlastv = max(i__,prevlastv);
	    if (tau[i__] == 0.) {

/*              H(i)  =  I */

		i__2 = i__;
		for (j = 1; j <= i__2; ++j) {
		    t[j + i__ * t_dim1] = 0.;
/* L10: */
		}
	    } else {

/*              general case */

		vii = v[i__ + i__ * v_dim1];
		v[i__ + i__ * v_dim1] = 1.;
		if (lsame_(storev, "C")) {
/*                 Skip any trailing zeros. */
		    i__2 = i__ + 1;
		    for (lastv = *n; lastv >= i__2; --lastv) {
			if (v[lastv + i__ * v_dim1] != 0.) {
			    break;
			}
		    }
		    j = min(lastv,prevlastv);

/*                 T(1:i-1,i) := - tau(i) * V(i:j,1:i-1)' * V(i:j,i) */

		    i__2 = j - i__ + 1;
		    i__3 = i__ - 1;
		    d__1 = -tau[i__];
		    dgemv_("Transpose", &i__2, &i__3, &d__1, &v[i__ + v_dim1],
			     ldv, &v[i__ + i__ * v_dim1], &c__1, &c_b8, &t[
			    i__ * t_dim1 + 1], &c__1);
		} else {
/*                 Skip any trailing zeros. */
		    i__2 = i__ + 1;
		    for (lastv = *n; lastv >= i__2; --lastv) {
			if (v[i__ + lastv * v_dim1] != 0.) {
			    break;
			}
		    }
		    j = min(lastv,prevlastv);

/*                 T(1:i-1,i) := - tau(i) * V(1:i-1,i:j) * V(i,i:j)' */

		    i__2 = i__ - 1;
		    i__3 = j - i__ + 1;
		    d__1 = -tau[i__];
		    dgemv_("No transpose", &i__2, &i__3, &d__1, &v[i__ *
			    v_dim1 + 1], ldv, &v[i__ + i__ * v_dim1], ldv, &
			    c_b8, &t[i__ * t_dim1 + 1], &c__1);
		}
		v[i__ + i__ * v_dim1] = vii;

/*              T(1:i-1,i) := T(1:i-1,1:i-1) * T(1:i-1,i) */

		i__2 = i__ - 1;
		dtrmv_("Upper", "No transpose", "Non-unit", &i__2, &t[
			t_offset], ldt, &t[i__ * t_dim1 + 1], &c__1);
		t[i__ + i__ * t_dim1] = tau[i__];
		if (i__ > 1) {
		    prevlastv = max(prevlastv,lastv);
		} else {
		    prevlastv = lastv;
		}
	    }
/* L20: */
	}
    } else {
	prevlastv = 1;
	for (i__ = *k; i__ >= 1; --i__) {
	    if (tau[i__] == 0.) {

/*              H(i)  =  I */

		i__1 = *k;
		for (j = i__; j <= i__1; ++j) {
		    t[j + i__ * t_dim1] = 0.;
/* L30: */
		}
	    } else {

/*              general case */

		if (i__ < *k) {
		    if (lsame_(storev, "C")) {
			vii = v[*n - *k + i__ + i__ * v_dim1];
			v[*n - *k + i__ + i__ * v_dim1] = 1.;
/*                    Skip any leading zeros. */
			i__1 = i__ - 1;
			for (lastv = 1; lastv <= i__1; ++lastv) {
			    if (v[lastv + i__ * v_dim1] != 0.) {
				break;
			    }
			}
			j = max(lastv,prevlastv);

/*                    T(i+1:k,i) := */
/*                            - tau(i) * V(j:n-k+i,i+1:k)' * V(j:n-k+i,i) */

			i__1 = *n - *k + i__ - j + 1;
			i__2 = *k - i__;
			d__1 = -tau[i__];
			dgemv_("Transpose", &i__1, &i__2, &d__1, &v[j + (i__
				+ 1) * v_dim1], ldv, &v[j + i__ * v_dim1], &
				c__1, &c_b8, &t[i__ + 1 + i__ * t_dim1], &
				c__1);
			v[*n - *k + i__ + i__ * v_dim1] = vii;
		    } else {
			vii = v[i__ + (*n - *k + i__) * v_dim1];
			v[i__ + (*n - *k + i__) * v_dim1] = 1.;
/*                    Skip any leading zeros. */
			i__1 = i__ - 1;
			for (lastv = 1; lastv <= i__1; ++lastv) {
			    if (v[i__ + lastv * v_dim1] != 0.) {
				break;
			    }
			}
			j = max(lastv,prevlastv);

/*                    T(i+1:k,i) := */
/*                            - tau(i) * V(i+1:k,j:n-k+i) * V(i,j:n-k+i)' */

			i__1 = *k - i__;
			i__2 = *n - *k + i__ - j + 1;
			d__1 = -tau[i__];
			dgemv_("No transpose", &i__1, &i__2, &d__1, &v[i__ +
				1 + j * v_dim1], ldv, &v[i__ + j * v_dim1],
				ldv, &c_b8, &t[i__ + 1 + i__ * t_dim1], &c__1);
			v[i__ + (*n - *k + i__) * v_dim1] = vii;
		    }

/*                 T(i+1:k,i) := T(i+1:k,i+1:k) * T(i+1:k,i) */

		    i__1 = *k - i__;
		    dtrmv_("Lower", "No transpose", "Non-unit", &i__1, &t[i__
			    + 1 + (i__ + 1) * t_dim1], ldt, &t[i__ + 1 + i__ *
			     t_dim1], &c__1)
			    ;
		    if (i__ > 1) {
			prevlastv = min(prevlastv,lastv);
		    } else {
			prevlastv = lastv;
		    }
		}
		t[i__ + i__ * t_dim1] = tau[i__];
	    }
/* L40: */
	}
    }
    return 0;

/*     End of DLARFT */

} /* dlarft_ */

/* Subroutine */ int dlartg_(doublereal *f, doublereal *g, doublereal *cs,
	doublereal *sn, doublereal *r__)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Local variables */
    integer i__;
    doublereal f1, g1, eps, scale;
    integer count;
    doublereal safmn2, safmx2;
    extern doublereal dlamch_(char *);
    doublereal safmin;


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLARTG generate a plane rotation so that */

/*     [  CS  SN  ]  .  [ F ]  =  [ R ]   where CS**2 + SN**2 = 1. */
/*     [ -SN  CS  ]     [ G ]     [ 0 ] */

/*  This is a slower, more accurate version of the BLAS1 routine DROTG, */
/*  with the following other differences: */
/*     F and G are unchanged on return. */
/*     If G=0, then CS=1 and SN=0. */
/*     If F=0 and (G .ne. 0), then CS=0 and SN=1 without doing any */
/*        floating point operations (saves work in DBDSQR when */
/*        there are zeros on the diagonal). */

/*  If F exceeds G in magnitude, CS will be positive. */

/*  Arguments */
/*  ========= */

/*  F       (input) DOUBLE PRECISION */
/*          The first component of vector to be rotated. */

/*  G       (input) DOUBLE PRECISION */
/*          The second component of vector to be rotated. */

/*  CS      (output) DOUBLE PRECISION */
/*          The cosine of the rotation. */

/*  SN      (output) DOUBLE PRECISION */
/*          The sine of the rotation. */

/*  R       (output) DOUBLE PRECISION */
/*          The nonzero component of the rotated vector. */

/*  This version has a few statements commented out for thread safety */
/*  (machine parameters are computed on each entry). 10 feb 03, SJH. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     LOGICAL            FIRST */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Save statement .. */
/*     SAVE               FIRST, SAFMX2, SAFMIN, SAFMN2 */
/*     .. */
/*     .. Data statements .. */
/*     DATA               FIRST / .TRUE. / */
/*     .. */
/*     .. Executable Statements .. */

/*     IF( FIRST ) THEN */
    safmin = dlamch_("S");
    eps = dlamch_("E");
    d__1 = dlamch_("B");
    i__1 = (integer) (log(safmin / eps) / log(dlamch_("B")) / 2.);
    safmn2 = pow_di(&d__1, &i__1);
    safmx2 = 1. / safmn2;
/*        FIRST = .FALSE. */
/*     END IF */
    if (*g == 0.) {
	*cs = 1.;
	*sn = 0.;
	*r__ = *f;
    } else if (*f == 0.) {
	*cs = 0.;
	*sn = 1.;
	*r__ = *g;
    } else {
	f1 = *f;
	g1 = *g;
/* Computing MAX */
	d__1 = abs(f1), d__2 = abs(g1);
	scale = max(d__1,d__2);
	if (scale >= safmx2) {
	    count = 0;
L10:
	    ++count;
	    f1 *= safmn2;
	    g1 *= safmn2;
/* Computing MAX */
	    d__1 = abs(f1), d__2 = abs(g1);
	    scale = max(d__1,d__2);
	    if (scale >= safmx2) {
		goto L10;
	    }
/* Computing 2nd power */
	    d__1 = f1;
/* Computing 2nd power */
	    d__2 = g1;
	    *r__ = sqrt(d__1 * d__1 + d__2 * d__2);
	    *cs = f1 / *r__;
	    *sn = g1 / *r__;
	    i__1 = count;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		*r__ *= safmx2;
/* L20: */
	    }
	} else if (scale <= safmn2) {
	    count = 0;
L30:
	    ++count;
	    f1 *= safmx2;
	    g1 *= safmx2;
/* Computing MAX */
	    d__1 = abs(f1), d__2 = abs(g1);
	    scale = max(d__1,d__2);
	    if (scale <= safmn2) {
		goto L30;
	    }
/* Computing 2nd power */
	    d__1 = f1;
/* Computing 2nd power */
	    d__2 = g1;
	    *r__ = sqrt(d__1 * d__1 + d__2 * d__2);
	    *cs = f1 / *r__;
	    *sn = g1 / *r__;
	    i__1 = count;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		*r__ *= safmn2;
/* L40: */
	    }
	} else {
/* Computing 2nd power */
	    d__1 = f1;
/* Computing 2nd power */
	    d__2 = g1;
	    *r__ = sqrt(d__1 * d__1 + d__2 * d__2);
	    *cs = f1 / *r__;
	    *sn = g1 / *r__;
	}
	if (abs(*f) > abs(*g) && *cs < 0.) {
	    *cs = -(*cs);
	    *sn = -(*sn);
	    *r__ = -(*r__);
	}
    }
    return 0;

/*     End of DLARTG */

} /* dlartg_ */

/* Subroutine */ int dlarz_(char *side, integer *m, integer *n, integer *l,
	doublereal *v, integer *incv, doublereal *tau, doublereal *c__,
	integer *ldc, doublereal *work)
{
    /* Table of constant values */

    integer c__1 = 1;
    doublereal c_b5 = 1.;

    /* System generated locals */
    integer c_dim1, c_offset;
    doublereal d__1;

    /* Local variables */
    extern /* Subroutine */ int dger_(integer *, integer *, doublereal *,
	    doublereal *, integer *, doublereal *, integer *, doublereal *,
	    integer *);
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int dgemv_(char *, integer *, integer *,
	    doublereal *, doublereal *, integer *, doublereal *, integer *,
	    doublereal *, doublereal *, integer *), dcopy_(integer *,
	    doublereal *, integer *, doublereal *, integer *), daxpy_(integer
	    *, doublereal *, doublereal *, integer *, doublereal *, integer *)
	    ;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLARZ applies a real elementary reflector H to a real M-by-N */
/*  matrix C, from either the left or the right. H is represented in the */
/*  form */

/*        H = I - tau * v * v' */

/*  where tau is a real scalar and v is a real vector. */

/*  If tau = 0, then H is taken to be the unit matrix. */


/*  H is a product of k elementary reflectors as returned by DTZRZF. */

/*  Arguments */
/*  ========= */

/*  SIDE    (input) CHARACTER*1 */
/*          = 'L': form  H * C */
/*          = 'R': form  C * H */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix C. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix C. */

/*  L       (input) INTEGER */
/*          The number of entries of the vector V containing */
/*          the meaningful part of the Householder vectors. */
/*          If SIDE = 'L', M >= L >= 0, if SIDE = 'R', N >= L >= 0. */

/*  V       (input) DOUBLE PRECISION array, dimension (1+(L-1)*abs(INCV)) */
/*          The vector v in the representation of H as returned by */
/*          DTZRZF. V is not used if TAU = 0. */

/*  INCV    (input) INTEGER */
/*          The increment between elements of v. INCV <> 0. */

/*  TAU     (input) DOUBLE PRECISION */
/*          The value tau in the representation of H. */

/*  C       (input/output) DOUBLE PRECISION array, dimension (LDC,N) */
/*          On entry, the M-by-N matrix C. */
/*          On exit, C is overwritten by the matrix H * C if SIDE = 'L', */
/*          or C * H if SIDE = 'R'. */

/*  LDC     (input) INTEGER */
/*          The leading dimension of the array C. LDC >= max(1,M). */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension */
/*                         (N) if SIDE = 'L' */
/*                      or (M) if SIDE = 'R' */

/*  Further Details */
/*  =============== */

/*  Based on contributions by */
/*    A. Petitet, Computer Science Dept., Univ. of Tenn., Knoxville, USA */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    --v;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    --work;

    /* Function Body */
    if (lsame_(side, "L")) {

/*        Form  H * C */

	if (*tau != 0.) {

/*           w( 1:n ) = C( 1, 1:n ) */

	    dcopy_(n, &c__[c_offset], ldc, &work[1], &c__1);

/*           w( 1:n ) = w( 1:n ) + C( m-l+1:m, 1:n )' * v( 1:l ) */

	    dgemv_("Transpose", l, n, &c_b5, &c__[*m - *l + 1 + c_dim1], ldc,
		    &v[1], incv, &c_b5, &work[1], &c__1);

/*           C( 1, 1:n ) = C( 1, 1:n ) - tau * w( 1:n ) */

	    d__1 = -(*tau);
	    daxpy_(n, &d__1, &work[1], &c__1, &c__[c_offset], ldc);

/*           C( m-l+1:m, 1:n ) = C( m-l+1:m, 1:n ) - ... */
/*                               tau * v( 1:l ) * w( 1:n )' */

	    d__1 = -(*tau);
	    dger_(l, n, &d__1, &v[1], incv, &work[1], &c__1, &c__[*m - *l + 1
		    + c_dim1], ldc);
	}

    } else {

/*        Form  C * H */

	if (*tau != 0.) {

/*           w( 1:m ) = C( 1:m, 1 ) */

	    dcopy_(m, &c__[c_offset], &c__1, &work[1], &c__1);

/*           w( 1:m ) = w( 1:m ) + C( 1:m, n-l+1:n, 1:n ) * v( 1:l ) */

	    dgemv_("No transpose", m, l, &c_b5, &c__[(*n - *l + 1) * c_dim1 +
		    1], ldc, &v[1], incv, &c_b5, &work[1], &c__1);

/*           C( 1:m, 1 ) = C( 1:m, 1 ) - tau * w( 1:m ) */

	    d__1 = -(*tau);
	    daxpy_(m, &d__1, &work[1], &c__1, &c__[c_offset], &c__1);

/*           C( 1:m, n-l+1:n ) = C( 1:m, n-l+1:n ) - ... */
/*                               tau * w( 1:m ) * v( 1:l )' */

	    d__1 = -(*tau);
	    dger_(m, l, &d__1, &work[1], &c__1, &v[1], incv, &c__[(*n - *l +
		    1) * c_dim1 + 1], ldc);

	}

    }

    return 0;

/*     End of DLARZ */

} /* dlarz_ */

/* Subroutine */ int dlarzb_(char *side, char *trans, char *direct, char *
	storev, integer *m, integer *n, integer *k, integer *l, doublereal *v,
	 integer *ldv, doublereal *t, integer *ldt, doublereal *c__, integer *
	ldc, doublereal *work, integer *ldwork)
{
    /* Table of constant values */

    integer c__1 = 1;
    doublereal c_b13 = 1.;
    doublereal c_b23 = -1.;

    /* System generated locals */
    integer c_dim1, c_offset, t_dim1, t_offset, v_dim1, v_offset, work_dim1,
	    work_offset, i__1, i__2;

    /* Local variables */
    integer i__, j, info;
    extern /* Subroutine */ int dgemm_(char *, char *, integer *, integer *,
	    integer *, doublereal *, doublereal *, integer *, doublereal *,
	    integer *, doublereal *, doublereal *, integer *);
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int dcopy_(integer *, doublereal *, integer *,
	    doublereal *, integer *), dtrmm_(char *, char *, char *, char *,
	    integer *, integer *, doublereal *, doublereal *, integer *,
	    doublereal *, integer *), xerbla_(
	    char *, integer *);
    char transt[1];


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLARZB applies a real block reflector H or its transpose H**T to */
/*  a real distributed M-by-N  C from the left or the right. */

/*  Currently, only STOREV = 'R' and DIRECT = 'B' are supported. */

/*  Arguments */
/*  ========= */

/*  SIDE    (input) CHARACTER*1 */
/*          = 'L': apply H or H' from the Left */
/*          = 'R': apply H or H' from the Right */

/*  TRANS   (input) CHARACTER*1 */
/*          = 'N': apply H (No transpose) */
/*          = 'C': apply H' (Transpose) */

/*  DIRECT  (input) CHARACTER*1 */
/*          Indicates how H is formed from a product of elementary */
/*          reflectors */
/*          = 'F': H = H(1) H(2) . . . H(k) (Forward, not supported yet) */
/*          = 'B': H = H(k) . . . H(2) H(1) (Backward) */

/*  STOREV  (input) CHARACTER*1 */
/*          Indicates how the vectors which define the elementary */
/*          reflectors are stored: */
/*          = 'C': Columnwise                        (not supported yet) */
/*          = 'R': Rowwise */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix C. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix C. */

/*  K       (input) INTEGER */
/*          The order of the matrix T (= the number of elementary */
/*          reflectors whose product defines the block reflector). */

/*  L       (input) INTEGER */
/*          The number of columns of the matrix V containing the */
/*          meaningful part of the Householder reflectors. */
/*          If SIDE = 'L', M >= L >= 0, if SIDE = 'R', N >= L >= 0. */

/*  V       (input) DOUBLE PRECISION array, dimension (LDV,NV). */
/*          If STOREV = 'C', NV = K; if STOREV = 'R', NV = L. */

/*  LDV     (input) INTEGER */
/*          The leading dimension of the array V. */
/*          If STOREV = 'C', LDV >= L; if STOREV = 'R', LDV >= K. */

/*  T       (input) DOUBLE PRECISION array, dimension (LDT,K) */
/*          The triangular K-by-K matrix T in the representation of the */
/*          block reflector. */

/*  LDT     (input) INTEGER */
/*          The leading dimension of the array T. LDT >= K. */

/*  C       (input/output) DOUBLE PRECISION array, dimension (LDC,N) */
/*          On entry, the M-by-N matrix C. */
/*          On exit, C is overwritten by H*C or H'*C or C*H or C*H'. */

/*  LDC     (input) INTEGER */
/*          The leading dimension of the array C. LDC >= max(1,M). */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (LDWORK,K) */

/*  LDWORK  (input) INTEGER */
/*          The leading dimension of the array WORK. */
/*          If SIDE = 'L', LDWORK >= max(1,N); */
/*          if SIDE = 'R', LDWORK >= max(1,M). */

/*  Further Details */
/*  =============== */

/*  Based on contributions by */
/*    A. Petitet, Computer Science Dept., Univ. of Tenn., Knoxville, USA */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Quick return if possible */

    /* Parameter adjustments */
    v_dim1 = *ldv;
    v_offset = 1 + v_dim1;
    v -= v_offset;
    t_dim1 = *ldt;
    t_offset = 1 + t_dim1;
    t -= t_offset;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    work_dim1 = *ldwork;
    work_offset = 1 + work_dim1;
    work -= work_offset;

    /* Function Body */
    if (*m <= 0 || *n <= 0) {
	return 0;
    }

/*     Check for currently supported options */

    info = 0;
    if (! lsame_(direct, "B")) {
	info = -3;
    } else if (! lsame_(storev, "R")) {
	info = -4;
    }
    if (info != 0) {
	i__1 = -info;
	xerbla_("DLARZB", &i__1);
	return 0;
    }

    if (lsame_(trans, "N")) {
	*(unsigned char *)transt = 'T';
    } else {
	*(unsigned char *)transt = 'N';
    }

    if (lsame_(side, "L")) {

/*        Form  H * C  or  H' * C */

/*        W( 1:n, 1:k ) = C( 1:k, 1:n )' */

	i__1 = *k;
	for (j = 1; j <= i__1; ++j) {
	    dcopy_(n, &c__[j + c_dim1], ldc, &work[j * work_dim1 + 1], &c__1);
/* L10: */
	}

/*        W( 1:n, 1:k ) = W( 1:n, 1:k ) + ... */
/*                        C( m-l+1:m, 1:n )' * V( 1:k, 1:l )' */

	if (*l > 0) {
	    dgemm_("Transpose", "Transpose", n, k, l, &c_b13, &c__[*m - *l +
		    1 + c_dim1], ldc, &v[v_offset], ldv, &c_b13, &work[
		    work_offset], ldwork);
	}

/*        W( 1:n, 1:k ) = W( 1:n, 1:k ) * T'  or  W( 1:m, 1:k ) * T */

	dtrmm_("Right", "Lower", transt, "Non-unit", n, k, &c_b13, &t[
		t_offset], ldt, &work[work_offset], ldwork);

/*        C( 1:k, 1:n ) = C( 1:k, 1:n ) - W( 1:n, 1:k )' */

	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *k;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		c__[i__ + j * c_dim1] -= work[j + i__ * work_dim1];
/* L20: */
	    }
/* L30: */
	}

/*        C( m-l+1:m, 1:n ) = C( m-l+1:m, 1:n ) - ... */
/*                            V( 1:k, 1:l )' * W( 1:n, 1:k )' */

	if (*l > 0) {
	    dgemm_("Transpose", "Transpose", l, n, k, &c_b23, &v[v_offset],
		    ldv, &work[work_offset], ldwork, &c_b13, &c__[*m - *l + 1
		    + c_dim1], ldc);
	}

    } else if (lsame_(side, "R")) {

/*        Form  C * H  or  C * H' */

/*        W( 1:m, 1:k ) = C( 1:m, 1:k ) */

	i__1 = *k;
	for (j = 1; j <= i__1; ++j) {
	    dcopy_(m, &c__[j * c_dim1 + 1], &c__1, &work[j * work_dim1 + 1], &
		    c__1);
/* L40: */
	}

/*        W( 1:m, 1:k ) = W( 1:m, 1:k ) + ... */
/*                        C( 1:m, n-l+1:n ) * V( 1:k, 1:l )' */

	if (*l > 0) {
	    dgemm_("No transpose", "Transpose", m, k, l, &c_b13, &c__[(*n - *
		    l + 1) * c_dim1 + 1], ldc, &v[v_offset], ldv, &c_b13, &
		    work[work_offset], ldwork);
	}

/*        W( 1:m, 1:k ) = W( 1:m, 1:k ) * T  or  W( 1:m, 1:k ) * T' */

	dtrmm_("Right", "Lower", trans, "Non-unit", m, k, &c_b13, &t[t_offset]
, ldt, &work[work_offset], ldwork);

/*        C( 1:m, 1:k ) = C( 1:m, 1:k ) - W( 1:m, 1:k ) */

	i__1 = *k;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		c__[i__ + j * c_dim1] -= work[i__ + j * work_dim1];
/* L50: */
	    }
/* L60: */
	}

/*        C( 1:m, n-l+1:n ) = C( 1:m, n-l+1:n ) - ... */
/*                            W( 1:m, 1:k ) * V( 1:k, 1:l ) */

	if (*l > 0) {
	    dgemm_("No transpose", "No transpose", m, l, k, &c_b23, &work[
		    work_offset], ldwork, &v[v_offset], ldv, &c_b13, &c__[(*n
		    - *l + 1) * c_dim1 + 1], ldc);
	}

    }

    return 0;

/*     End of DLARZB */

} /* dlarzb_ */

/* Subroutine */ int dlarzt_(char *direct, char *storev, integer *n, integer *
	k, doublereal *v, integer *ldv, doublereal *tau, doublereal *t,
	integer *ldt)
{
    /* Table of constant values */

    doublereal c_b8 = 0.;
    integer c__1 = 1;

    /* System generated locals */
    integer t_dim1, t_offset, v_dim1, v_offset, i__1;
    doublereal d__1;

    /* Local variables */
    integer i__, j, info;
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int dgemv_(char *, integer *, integer *,
	    doublereal *, doublereal *, integer *, doublereal *, integer *,
	    doublereal *, doublereal *, integer *), dtrmv_(char *,
	    char *, char *, integer *, doublereal *, integer *, doublereal *,
	    integer *), xerbla_(char *, integer *);


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLARZT forms the triangular factor T of a real block reflector */
/*  H of order > n, which is defined as a product of k elementary */
/*  reflectors. */

/*  If DIRECT = 'F', H = H(1) H(2) . . . H(k) and T is upper triangular; */

/*  If DIRECT = 'B', H = H(k) . . . H(2) H(1) and T is lower triangular. */

/*  If STOREV = 'C', the vector which defines the elementary reflector */
/*  H(i) is stored in the i-th column of the array V, and */

/*     H  =  I - V * T * V' */

/*  If STOREV = 'R', the vector which defines the elementary reflector */
/*  H(i) is stored in the i-th row of the array V, and */

/*     H  =  I - V' * T * V */

/*  Currently, only STOREV = 'R' and DIRECT = 'B' are supported. */

/*  Arguments */
/*  ========= */

/*  DIRECT  (input) CHARACTER*1 */
/*          Specifies the order in which the elementary reflectors are */
/*          multiplied to form the block reflector: */
/*          = 'F': H = H(1) H(2) . . . H(k) (Forward, not supported yet) */
/*          = 'B': H = H(k) . . . H(2) H(1) (Backward) */

/*  STOREV  (input) CHARACTER*1 */
/*          Specifies how the vectors which define the elementary */
/*          reflectors are stored (see also Further Details): */
/*          = 'C': columnwise                        (not supported yet) */
/*          = 'R': rowwise */

/*  N       (input) INTEGER */
/*          The order of the block reflector H. N >= 0. */

/*  K       (input) INTEGER */
/*          The order of the triangular factor T (= the number of */
/*          elementary reflectors). K >= 1. */

/*  V       (input/output) DOUBLE PRECISION array, dimension */
/*                               (LDV,K) if STOREV = 'C' */
/*                               (LDV,N) if STOREV = 'R' */
/*          The matrix V. See further details. */

/*  LDV     (input) INTEGER */
/*          The leading dimension of the array V. */
/*          If STOREV = 'C', LDV >= max(1,N); if STOREV = 'R', LDV >= K. */

/*  TAU     (input) DOUBLE PRECISION array, dimension (K) */
/*          TAU(i) must contain the scalar factor of the elementary */
/*          reflector H(i). */

/*  T       (output) DOUBLE PRECISION array, dimension (LDT,K) */
/*          The k by k triangular factor T of the block reflector. */
/*          If DIRECT = 'F', T is upper triangular; if DIRECT = 'B', T is */
/*          lower triangular. The rest of the array is not used. */

/*  LDT     (input) INTEGER */
/*          The leading dimension of the array T. LDT >= K. */

/*  Further Details */
/*  =============== */

/*  Based on contributions by */
/*    A. Petitet, Computer Science Dept., Univ. of Tenn., Knoxville, USA */

/*  The shape of the matrix V and the storage of the vectors which define */
/*  the H(i) is best illustrated by the following example with n = 5 and */
/*  k = 3. The elements equal to 1 are not stored; the corresponding */
/*  array elements are modified but restored on exit. The rest of the */
/*  array is not used. */

/*  DIRECT = 'F' and STOREV = 'C':         DIRECT = 'F' and STOREV = 'R': */

/*                                              ______V_____ */
/*         ( v1 v2 v3 )                        /            \ */
/*         ( v1 v2 v3 )                      ( v1 v1 v1 v1 v1 . . . . 1 ) */
/*     V = ( v1 v2 v3 )                      ( v2 v2 v2 v2 v2 . . . 1   ) */
/*         ( v1 v2 v3 )                      ( v3 v3 v3 v3 v3 . . 1     ) */
/*         ( v1 v2 v3 ) */
/*            .  .  . */
/*            .  .  . */
/*            1  .  . */
/*               1  . */
/*                  1 */

/*  DIRECT = 'B' and STOREV = 'C':         DIRECT = 'B' and STOREV = 'R': */

/*                                                        ______V_____ */
/*            1                                          /            \ */
/*            .  1                           ( 1 . . . . v1 v1 v1 v1 v1 ) */
/*            .  .  1                        ( . 1 . . . v2 v2 v2 v2 v2 ) */
/*            .  .  .                        ( . . 1 . . v3 v3 v3 v3 v3 ) */
/*            .  .  . */
/*         ( v1 v2 v3 ) */
/*         ( v1 v2 v3 ) */
/*     V = ( v1 v2 v3 ) */
/*         ( v1 v2 v3 ) */
/*         ( v1 v2 v3 ) */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Check for currently supported options */

    /* Parameter adjustments */
    v_dim1 = *ldv;
    v_offset = 1 + v_dim1;
    v -= v_offset;
    --tau;
    t_dim1 = *ldt;
    t_offset = 1 + t_dim1;
    t -= t_offset;

    /* Function Body */
    info = 0;
    if (! lsame_(direct, "B")) {
	info = -1;
    } else if (! lsame_(storev, "R")) {
	info = -2;
    }
    if (info != 0) {
	i__1 = -info;
	xerbla_("DLARZT", &i__1);
	return 0;
    }

    for (i__ = *k; i__ >= 1; --i__) {
	if (tau[i__] == 0.) {

/*           H(i)  =  I */

	    i__1 = *k;
	    for (j = i__; j <= i__1; ++j) {
		t[j + i__ * t_dim1] = 0.;
/* L10: */
	    }
	} else {

/*           general case */

	    if (i__ < *k) {

/*              T(i+1:k,i) = - tau(i) * V(i+1:k,1:n) * V(i,1:n)' */

		i__1 = *k - i__;
		d__1 = -tau[i__];
		dgemv_("No transpose", &i__1, n, &d__1, &v[i__ + 1 + v_dim1],
			ldv, &v[i__ + v_dim1], ldv, &c_b8, &t[i__ + 1 + i__ *
			t_dim1], &c__1);

/*              T(i+1:k,i) = T(i+1:k,i+1:k) * T(i+1:k,i) */

		i__1 = *k - i__;
		dtrmv_("Lower", "No transpose", "Non-unit", &i__1, &t[i__ + 1
			+ (i__ + 1) * t_dim1], ldt, &t[i__ + 1 + i__ * t_dim1]
, &c__1);
	    }
	    t[i__ + i__ * t_dim1] = tau[i__];
	}
/* L20: */
    }
    return 0;

/*     End of DLARZT */

} /* dlarzt_ */

/* Subroutine */ int dlascl_(char *type__, integer *kl, integer *ku,
	doublereal *cfrom, doublereal *cto, integer *m, integer *n,
	doublereal *a, integer *lda, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4, i__5;

    /* Local variables */
    integer i__, j, k1, k2, k3, k4;
    doublereal mul, cto1;
    logical done;
    doublereal ctoc;
    extern logical lsame_(char *, char *);
    integer itype;
    doublereal cfrom1;
    extern doublereal dlamch_(char *);
    doublereal cfromc;
    extern logical disnan_(doublereal *);
    extern /* Subroutine */ int xerbla_(char *, integer *);
    doublereal bignum, smlnum;


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLASCL multiplies the M by N real matrix A by the real scalar */
/*  CTO/CFROM.  This is done without over/underflow as long as the final */
/*  result CTO*A(I,J)/CFROM does not over/underflow. TYPE specifies that */
/*  A may be full, upper triangular, lower triangular, upper Hessenberg, */
/*  or banded. */

/*  Arguments */
/*  ========= */

/*  TYPE    (input) CHARACTER*1 */
/*          TYPE indices the storage type of the input matrix. */
/*          = 'G':  A is a full matrix. */
/*          = 'L':  A is a lower triangular matrix. */
/*          = 'U':  A is an upper triangular matrix. */
/*          = 'H':  A is an upper Hessenberg matrix. */
/*          = 'B':  A is a symmetric band matrix with lower bandwidth KL */
/*                  and upper bandwidth KU and with the only the lower */
/*                  half stored. */
/*          = 'Q':  A is a symmetric band matrix with lower bandwidth KL */
/*                  and upper bandwidth KU and with the only the upper */
/*                  half stored. */
/*          = 'Z':  A is a band matrix with lower bandwidth KL and upper */
/*                  bandwidth KU. */

/*  KL      (input) INTEGER */
/*          The lower bandwidth of A.  Referenced only if TYPE = 'B', */
/*          'Q' or 'Z'. */

/*  KU      (input) INTEGER */
/*          The upper bandwidth of A.  Referenced only if TYPE = 'B', */
/*          'Q' or 'Z'. */

/*  CFROM   (input) DOUBLE PRECISION */
/*  CTO     (input) DOUBLE PRECISION */
/*          The matrix A is multiplied by CTO/CFROM. A(I,J) is computed */
/*          without over/underflow if the final result CTO*A(I,J)/CFROM */
/*          can be represented without over/underflow.  CFROM must be */
/*          nonzero. */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A.  M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A.  N >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          The matrix to be multiplied by CTO/CFROM.  See TYPE for the */
/*          storage type. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,M). */

/*  INFO    (output) INTEGER */
/*          0  - successful exit */
/*          <0 - if INFO = -i, the i-th argument had an illegal value. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    *info = 0;

    if (lsame_(type__, "G")) {
	itype = 0;
    } else if (lsame_(type__, "L")) {
	itype = 1;
    } else if (lsame_(type__, "U")) {
	itype = 2;
    } else if (lsame_(type__, "H")) {
	itype = 3;
    } else if (lsame_(type__, "B")) {
	itype = 4;
    } else if (lsame_(type__, "Q")) {
	itype = 5;
    } else if (lsame_(type__, "Z")) {
	itype = 6;
    } else {
	itype = -1;
    }

    if (itype == -1) {
	*info = -1;
    } else if (*cfrom == 0. || disnan_(cfrom)) {
	*info = -4;
    } else if (disnan_(cto)) {
	*info = -5;
    } else if (*m < 0) {
	*info = -6;
    } else if (*n < 0 || (itype == 4 && *n != *m) || (itype == 5 && *n != *m)) {
	*info = -7;
    } else if (itype <= 3 && *lda < max(1,*m)) {
	*info = -9;
    } else if (itype >= 4) {
/* Computing MAX */
	i__1 = *m - 1;
	if (*kl < 0 || *kl > max(i__1,0)) {
	    *info = -2;
	} else /* if(complicated condition) */ {
/* Computing MAX */
	    i__1 = *n - 1;
	    if (*ku < 0 || *ku > max(i__1,0) || ((itype == 4 || itype == 5) &&
		    *kl != *ku)) {
		*info = -3;
	    } else if ((itype == 4 && *lda < *kl + 1) || (itype == 5 && *lda < *
		    ku + 1) || (itype == 6 && *lda < (*kl << 1) + *ku + 1)) {
		*info = -9;
	    }
	}
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DLASCL", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0 || *m == 0) {
	return 0;
    }

/*     Get machine parameters */

    smlnum = dlamch_("S");
    bignum = 1. / smlnum;

    cfromc = *cfrom;
    ctoc = *cto;

L10:
    cfrom1 = cfromc * smlnum;
    if (cfrom1 == cfromc) {
/*        CFROMC is an inf.  Multiply by a correctly signed zero for */
/*        finite CTOC, or a NaN if CTOC is infinite. */
	mul = ctoc / cfromc;
	done = TRUE_;
	cto1 = ctoc;
    } else {
	cto1 = ctoc / bignum;
	if (cto1 == ctoc) {
/*           CTOC is either 0 or an inf.  In both cases, CTOC itself */
/*           serves as the correct multiplication factor. */
	    mul = ctoc;
	    done = TRUE_;
	    cfromc = 1.;
	} else if (abs(cfrom1) > abs(ctoc) && ctoc != 0.) {
	    mul = smlnum;
	    done = FALSE_;
	    cfromc = cfrom1;
	} else if (abs(cto1) > abs(cfromc)) {
	    mul = bignum;
	    done = FALSE_;
	    ctoc = cto1;
	} else {
	    mul = ctoc / cfromc;
	    done = TRUE_;
	}
    }

    if (itype == 0) {

/*        Full matrix */

	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		a[i__ + j * a_dim1] *= mul;
/* L20: */
	    }
/* L30: */
	}

    } else if (itype == 1) {

/*        Lower triangular matrix */

	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (i__ = j; i__ <= i__2; ++i__) {
		a[i__ + j * a_dim1] *= mul;
/* L40: */
	    }
/* L50: */
	}

    } else if (itype == 2) {

/*        Upper triangular matrix */

	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = min(j,*m);
	    for (i__ = 1; i__ <= i__2; ++i__) {
		a[i__ + j * a_dim1] *= mul;
/* L60: */
	    }
/* L70: */
	}

    } else if (itype == 3) {

/*        Upper Hessenberg matrix */

	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
/* Computing MIN */
	    i__3 = j + 1;
	    i__2 = min(i__3,*m);
	    for (i__ = 1; i__ <= i__2; ++i__) {
		a[i__ + j * a_dim1] *= mul;
/* L80: */
	    }
/* L90: */
	}

    } else if (itype == 4) {

/*        Lower half of a symmetric band matrix */

	k3 = *kl + 1;
	k4 = *n + 1;
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
/* Computing MIN */
	    i__3 = k3, i__4 = k4 - j;
	    i__2 = min(i__3,i__4);
	    for (i__ = 1; i__ <= i__2; ++i__) {
		a[i__ + j * a_dim1] *= mul;
/* L100: */
	    }
/* L110: */
	}

    } else if (itype == 5) {

/*        Upper half of a symmetric band matrix */

	k1 = *ku + 2;
	k3 = *ku + 1;
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
/* Computing MAX */
	    i__2 = k1 - j;
	    i__3 = k3;
	    for (i__ = max(i__2,1); i__ <= i__3; ++i__) {
		a[i__ + j * a_dim1] *= mul;
/* L120: */
	    }
/* L130: */
	}

    } else if (itype == 6) {

/*        Band matrix */

	k1 = *kl + *ku + 2;
	k2 = *kl + 1;
	k3 = (*kl << 1) + *ku + 1;
	k4 = *kl + *ku + 1 + *m;
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
/* Computing MAX */
	    i__3 = k1 - j;
/* Computing MIN */
	    i__4 = k3, i__5 = k4 - j;
	    i__2 = min(i__4,i__5);
	    for (i__ = max(i__3,k2); i__ <= i__2; ++i__) {
		a[i__ + j * a_dim1] *= mul;
/* L140: */
	    }
/* L150: */
	}

    }

    if (! done) {
	goto L10;
    }

    return 0;

/*     End of DLASCL */

} /* dlascl_ */

/* Subroutine */ int dlas2_(doublereal *f, doublereal *g, doublereal *h__,
	doublereal *ssmin, doublereal *ssmax)
{
    /* System generated locals */
    doublereal d__1, d__2;

    /* Local variables */
    doublereal c__, fa, ga, ha, as, at, au, fhmn, fhmx;


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLAS2  computes the singular values of the 2-by-2 matrix */
/*     [  F   G  ] */
/*     [  0   H  ]. */
/*  On return, SSMIN is the smaller singular value and SSMAX is the */
/*  larger singular value. */

/*  Arguments */
/*  ========= */

/*  F       (input) DOUBLE PRECISION */
/*          The (1,1) element of the 2-by-2 matrix. */

/*  G       (input) DOUBLE PRECISION */
/*          The (1,2) element of the 2-by-2 matrix. */

/*  H       (input) DOUBLE PRECISION */
/*          The (2,2) element of the 2-by-2 matrix. */

/*  SSMIN   (output) DOUBLE PRECISION */
/*          The smaller singular value. */

/*  SSMAX   (output) DOUBLE PRECISION */
/*          The larger singular value. */

/*  Further Details */
/*  =============== */

/*  Barring over/underflow, all output quantities are correct to within */
/*  a few units in the last place (ulps), even in the absence of a guard */
/*  digit in addition/subtraction. */

/*  In IEEE arithmetic, the code works correctly if one matrix element is */
/*  infinite. */

/*  Overflow will not occur unless the largest singular value itself */
/*  overflows, or is within a few ulps of overflow. (On machines with */
/*  partial overflow, like the Cray, overflow may occur if the largest */
/*  singular value is within a factor of 2 of overflow.) */

/*  Underflow is harmless if underflow is gradual. Otherwise, results */
/*  may correspond to a matrix modified by perturbations of size near */
/*  the underflow threshold. */

/*  ==================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    fa = abs(*f);
    ga = abs(*g);
    ha = abs(*h__);
    fhmn = min(fa,ha);
    fhmx = max(fa,ha);
    if (fhmn == 0.) {
	*ssmin = 0.;
	if (fhmx == 0.) {
	    *ssmax = ga;
	} else {
/* Computing 2nd power */
	    d__1 = min(fhmx,ga) / max(fhmx,ga);
	    *ssmax = max(fhmx,ga) * sqrt(d__1 * d__1 + 1.);
	}
    } else {
	if (ga < fhmx) {
	    as = fhmn / fhmx + 1.;
	    at = (fhmx - fhmn) / fhmx;
/* Computing 2nd power */
	    d__1 = ga / fhmx;
	    au = d__1 * d__1;
	    c__ = 2. / (sqrt(as * as + au) + sqrt(at * at + au));
	    *ssmin = fhmn * c__;
	    *ssmax = fhmx / c__;
	} else {
	    au = fhmx / ga;
	    if (au == 0.) {

/*              Avoid possible harmful underflow if exponent range */
/*              asymmetric (true SSMIN may not underflow even if */
/*              AU underflows) */

		*ssmin = fhmn * fhmx / ga;
		*ssmax = ga;
	    } else {
		as = fhmn / fhmx + 1.;
		at = (fhmx - fhmn) / fhmx;
/* Computing 2nd power */
		d__1 = as * au;
/* Computing 2nd power */
		d__2 = at * au;
		c__ = 1. / (sqrt(d__1 * d__1 + 1.) + sqrt(d__2 * d__2 + 1.));
		*ssmin = fhmn * c__ * au;
		*ssmin += *ssmin;
		*ssmax = ga / (c__ + c__);
	    }
	}
    }
    return 0;

/*     End of DLAS2 */

} /* dlas2_ */

/* Subroutine */ int dlaset_(char *uplo, integer *m, integer *n, doublereal *
	alpha, doublereal *beta, doublereal *a, integer *lda)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;

    /* Local variables */
    integer i__, j;
    extern logical lsame_(char *, char *);


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLASET initializes an m-by-n matrix A to BETA on the diagonal and */
/*  ALPHA on the offdiagonals. */

/*  Arguments */
/*  ========= */

/*  UPLO    (input) CHARACTER*1 */
/*          Specifies the part of the matrix A to be set. */
/*          = 'U':      Upper triangular part is set; the strictly lower */
/*                      triangular part of A is not changed. */
/*          = 'L':      Lower triangular part is set; the strictly upper */
/*                      triangular part of A is not changed. */
/*          Otherwise:  All of the matrix A is set. */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A.  M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A.  N >= 0. */

/*  ALPHA   (input) DOUBLE PRECISION */
/*          The constant to which the offdiagonal elements are to be set. */

/*  BETA    (input) DOUBLE PRECISION */
/*          The constant to which the diagonal elements are to be set. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On exit, the leading m-by-n submatrix of A is set as follows: */

/*          if UPLO = 'U', A(i,j) = ALPHA, 1<=i<=j-1, 1<=j<=n, */
/*          if UPLO = 'L', A(i,j) = ALPHA, j+1<=i<=m, 1<=j<=n, */
/*          otherwise,     A(i,j) = ALPHA, 1<=i<=m, 1<=j<=n, i.ne.j, */

/*          and, for all UPLO, A(i,i) = BETA, 1<=i<=min(m,n). */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,M). */

/* ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    if (lsame_(uplo, "U")) {

/*        Set the strictly upper triangular or trapezoidal part of the */
/*        array to ALPHA. */

	i__1 = *n;
	for (j = 2; j <= i__1; ++j) {
/* Computing MIN */
	    i__3 = j - 1;
	    i__2 = min(i__3,*m);
	    for (i__ = 1; i__ <= i__2; ++i__) {
		a[i__ + j * a_dim1] = *alpha;
/* L10: */
	    }
/* L20: */
	}

    } else if (lsame_(uplo, "L")) {

/*        Set the strictly lower triangular or trapezoidal part of the */
/*        array to ALPHA. */

	i__1 = min(*m,*n);
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (i__ = j + 1; i__ <= i__2; ++i__) {
		a[i__ + j * a_dim1] = *alpha;
/* L30: */
	    }
/* L40: */
	}

    } else {

/*        Set the leading m-by-n submatrix to ALPHA. */

	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		a[i__ + j * a_dim1] = *alpha;
/* L50: */
	    }
/* L60: */
	}
    }

/*     Set the first min(M,N) diagonal elements to BETA. */

    i__1 = min(*m,*n);
    for (i__ = 1; i__ <= i__1; ++i__) {
	a[i__ + i__ * a_dim1] = *beta;
/* L70: */
    }

    return 0;

/*     End of DLASET */

} /* dlaset_ */

/* Subroutine */ int dlasq1_(integer *n, doublereal *d__, doublereal *e,
	doublereal *work, integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;
    integer c__2 = 2;
    integer c__0 = 0;

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2, d__3;

    /* Local variables */
    integer i__;
    doublereal eps;
    extern /* Subroutine */ int dlas2_(doublereal *, doublereal *, doublereal
	    *, doublereal *, doublereal *);
    doublereal scale;
    integer iinfo;
    doublereal sigmn;
    extern /* Subroutine */ int dcopy_(integer *, doublereal *, integer *,
	    doublereal *, integer *);
    doublereal sigmx;
    extern /* Subroutine */ int dlasq2_(integer *, doublereal *, integer *);
    extern doublereal dlamch_(char *);
    extern /* Subroutine */ int dlascl_(char *, integer *, integer *,
	    doublereal *, doublereal *, integer *, integer *, doublereal *,
	    integer *, integer *);
    doublereal safmin;
    extern /* Subroutine */ int xerbla_(char *, integer *), dlasrt_(
	    char *, integer *, doublereal *, integer *);


/*  -- LAPACK routine (version 3.2)                                    -- */

/*  -- Contributed by Osni Marques of the Lawrence Berkeley National   -- */
/*  -- Laboratory and Beresford Parlett of the Univ. of California at  -- */
/*  -- Berkeley                                                        -- */
/*  -- November 2008                                                   -- */

/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLASQ1 computes the singular values of a real N-by-N bidiagonal */
/*  matrix with diagonal D and off-diagonal E. The singular values */
/*  are computed to high relative accuracy, in the absence of */
/*  denormalization, underflow and overflow. The algorithm was first */
/*  presented in */

/*  "Accurate singular values and differential qd algorithms" by K. V. */
/*  Fernando and B. N. Parlett, Numer. Math., Vol-67, No. 2, pp. 191-230, */
/*  1994, */

/*  and the present implementation is described in "An implementation of */
/*  the dqds Algorithm (Positive Case)", LAPACK Working Note. */

/*  Arguments */
/*  ========= */

/*  N     (input) INTEGER */
/*        The number of rows and columns in the matrix. N >= 0. */

/*  D     (input/output) DOUBLE PRECISION array, dimension (N) */
/*        On entry, D contains the diagonal elements of the */
/*        bidiagonal matrix whose SVD is desired. On normal exit, */
/*        D contains the singular values in decreasing order. */

/*  E     (input/output) DOUBLE PRECISION array, dimension (N) */
/*        On entry, elements E(1:N-1) contain the off-diagonal elements */
/*        of the bidiagonal matrix whose SVD is desired. */
/*        On exit, E is overwritten. */

/*  WORK  (workspace) DOUBLE PRECISION array, dimension (4*N) */

/*  INFO  (output) INTEGER */
/*        = 0: successful exit */
/*        < 0: if INFO = -i, the i-th argument had an illegal value */
/*        > 0: the algorithm failed */
/*             = 1, a split was marked by a positive value in E */
/*             = 2, current block of Z not diagonalized after 30*N */
/*                  iterations (in inner while loop) */
/*             = 3, termination criterion of outer while loop not met */
/*                  (program created more than N unreduced blocks) */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    --work;
    --e;
    --d__;

    /* Function Body */
    *info = 0;
    if (*n < 0) {
	*info = -2;
	i__1 = -(*info);
	xerbla_("DLASQ1", &i__1);
	return 0;
    } else if (*n == 0) {
	return 0;
    } else if (*n == 1) {
	d__[1] = abs(d__[1]);
	return 0;
    } else if (*n == 2) {
	dlas2_(&d__[1], &e[1], &d__[2], &sigmn, &sigmx);
	d__[1] = sigmx;
	d__[2] = sigmn;
	return 0;
    }

/*     Estimate the largest singular value. */

    sigmx = 0.;
    i__1 = *n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	d__[i__] = (d__1 = d__[i__], abs(d__1));
/* Computing MAX */
	d__2 = sigmx, d__3 = (d__1 = e[i__], abs(d__1));
	sigmx = max(d__2,d__3);
/* L10: */
    }
    d__[*n] = (d__1 = d__[*n], abs(d__1));

/*     Early return if SIGMX is zero (matrix is already diagonal). */

    if (sigmx == 0.) {
	dlasrt_("D", n, &d__[1], &iinfo);
	return 0;
    }

    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MAX */
	d__1 = sigmx, d__2 = d__[i__];
	sigmx = max(d__1,d__2);
/* L20: */
    }

/*     Copy D and E into WORK (in the Z format) and scale (squaring the */
/*     input data makes scaling by a power of the radix pointless). */

    eps = dlamch_("Precision");
    safmin = dlamch_("Safe minimum");
    scale = sqrt(eps / safmin);
    dcopy_(n, &d__[1], &c__1, &work[1], &c__2);
    i__1 = *n - 1;
    dcopy_(&i__1, &e[1], &c__1, &work[2], &c__2);
    i__1 = (*n << 1) - 1;
    i__2 = (*n << 1) - 1;
    dlascl_("G", &c__0, &c__0, &sigmx, &scale, &i__1, &c__1, &work[1], &i__2,
	    &iinfo);

/*     Compute the q's and e's. */

    i__1 = (*n << 1) - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing 2nd power */
	d__1 = work[i__];
	work[i__] = d__1 * d__1;
/* L30: */
    }
    work[*n * 2] = 0.;

    dlasq2_(n, &work[1], info);

    if (*info == 0) {
	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    d__[i__] = sqrt(work[i__]);
/* L40: */
	}
	dlascl_("G", &c__0, &c__0, &scale, &sigmx, n, &c__1, &d__[1], n, &
		iinfo);
    }

    return 0;

/*     End of DLASQ1 */

} /* dlasq1_ */

/* Subroutine */ int dlasq2_(integer *n, doublereal *z__, integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;
    integer c__2 = 2;
    integer c__10 = 10;
    integer c__3 = 3;
    integer c__4 = 4;
    integer c__11 = 11;

    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal d__1, d__2;

    /* Local variables */
    doublereal d__, e, g;
    integer k;
    doublereal s, t;
    integer i0, i4, n0;
    doublereal dn;
    integer pp;
    doublereal dn1, dn2, dee, eps, tau, tol;
    integer ipn4;
    doublereal tol2;
    logical ieee;
    integer nbig;
    doublereal dmin__, emin, emax;
    integer kmin, ndiv, iter;
    doublereal qmin, temp, qmax, zmax;
    integer splt;
    doublereal dmin1, dmin2;
    integer nfail;
    doublereal desig, trace, sigma;
    integer iinfo, ttype;
    extern /* Subroutine */ int dlasq3_(integer *, integer *, doublereal *,
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     integer *, integer *, integer *, logical *, integer *,
	    doublereal *, doublereal *, doublereal *, doublereal *,
	    doublereal *, doublereal *, doublereal *);
    extern doublereal dlamch_(char *);
    doublereal deemin;
    integer iwhila, iwhilb;
    doublereal oldemn, safmin;
    extern /* Subroutine */ int xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *,
	    integer *, integer *);
    extern /* Subroutine */ int dlasrt_(char *, integer *, doublereal *,
	    integer *);


/*  -- LAPACK routine (version 3.2)                                    -- */

/*  -- Contributed by Osni Marques of the Lawrence Berkeley National   -- */
/*  -- Laboratory and Beresford Parlett of the Univ. of California at  -- */
/*  -- Berkeley                                                        -- */
/*  -- November 2008                                                   -- */

/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLASQ2 computes all the eigenvalues of the symmetric positive */
/*  definite tridiagonal matrix associated with the qd array Z to high */
/*  relative accuracy are computed to high relative accuracy, in the */
/*  absence of denormalization, underflow and overflow. */

/*  To see the relation of Z to the tridiagonal matrix, let L be a */
/*  unit lower bidiagonal matrix with subdiagonals Z(2,4,6,,..) and */
/*  let U be an upper bidiagonal matrix with 1's above and diagonal */
/*  Z(1,3,5,,..). The tridiagonal is L*U or, if you prefer, the */
/*  symmetric tridiagonal to which it is similar. */

/*  Note : DLASQ2 defines a logical variable, IEEE, which is true */
/*  on machines which follow ieee-754 floating-point standard in their */
/*  handling of infinities and NaNs, and false otherwise. This variable */
/*  is passed to DLASQ3. */

/*  Arguments */
/*  ========= */

/*  N     (input) INTEGER */
/*        The number of rows and columns in the matrix. N >= 0. */

/*  Z     (input/output) DOUBLE PRECISION array, dimension ( 4*N ) */
/*        On entry Z holds the qd array. On exit, entries 1 to N hold */
/*        the eigenvalues in decreasing order, Z( 2*N+1 ) holds the */
/*        trace, and Z( 2*N+2 ) holds the sum of the eigenvalues. If */
/*        N > 2, then Z( 2*N+3 ) holds the iteration count, Z( 2*N+4 ) */
/*        holds NDIVS/NIN^2, and Z( 2*N+5 ) holds the percentage of */
/*        shifts that failed. */

/*  INFO  (output) INTEGER */
/*        = 0: successful exit */
/*        < 0: if the i-th argument is a scalar and had an illegal */
/*             value, then INFO = -i, if the i-th argument is an */
/*             array and the j-entry had an illegal value, then */
/*             INFO = -(i*100+j) */
/*        > 0: the algorithm failed */
/*              = 1, a split was marked by a positive value in E */
/*              = 2, current block of Z not diagonalized after 30*N */
/*                   iterations (in inner while loop) */
/*              = 3, termination criterion of outer while loop not met */
/*                   (program created more than N unreduced blocks) */

/*  Further Details */
/*  =============== */
/*  Local Variables: I0:N0 defines a current unreduced segment of Z. */
/*  The shifts are accumulated in SIGMA. Iteration count is in ITER. */
/*  Ping-pong is controlled by PP (alternates between 0 and 1). */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments. */
/*     (in case DLASQ2 is not called by DLASQ1) */

    /* Parameter adjustments */
    --z__;

    /* Function Body */
    *info = 0;
    eps = dlamch_("Precision");
    safmin = dlamch_("Safe minimum");
    tol = eps * 100.;
/* Computing 2nd power */
    d__1 = tol;
    tol2 = d__1 * d__1;

    if (*n < 0) {
	*info = -1;
	xerbla_("DLASQ2", &c__1);
	return 0;
    } else if (*n == 0) {
	return 0;
    } else if (*n == 1) {

/*        1-by-1 case. */

	if (z__[1] < 0.) {
	    *info = -201;
	    xerbla_("DLASQ2", &c__2);
	}
	return 0;
    } else if (*n == 2) {

/*        2-by-2 case. */

	if (z__[2] < 0. || z__[3] < 0.) {
	    *info = -2;
	    xerbla_("DLASQ2", &c__2);
	    return 0;
	} else if (z__[3] > z__[1]) {
	    d__ = z__[3];
	    z__[3] = z__[1];
	    z__[1] = d__;
	}
	z__[5] = z__[1] + z__[2] + z__[3];
	if (z__[2] > z__[3] * tol2) {
	    t = (z__[1] - z__[3] + z__[2]) * .5;
	    s = z__[3] * (z__[2] / t);
	    if (s <= t) {
		s = z__[3] * (z__[2] / (t * (sqrt(s / t + 1.) + 1.)));
	    } else {
		s = z__[3] * (z__[2] / (t + sqrt(t) * sqrt(t + s)));
	    }
	    t = z__[1] + (s + z__[2]);
	    z__[3] *= z__[1] / t;
	    z__[1] = t;
	}
	z__[2] = z__[3];
	z__[6] = z__[2] + z__[1];
	return 0;
    }

/*     Check for negative data and compute sums of q's and e's. */

    z__[*n * 2] = 0.;
    emin = z__[2];
    qmax = 0.;
    zmax = 0.;
    d__ = 0.;
    e = 0.;

    i__1 = (*n - 1) << 1;
    for (k = 1; k <= i__1; k += 2) {
	if (z__[k] < 0.) {
	    *info = -(k + 200);
	    xerbla_("DLASQ2", &c__2);
	    return 0;
	} else if (z__[k + 1] < 0.) {
	    *info = -(k + 201);
	    xerbla_("DLASQ2", &c__2);
	    return 0;
	}
	d__ += z__[k];
	e += z__[k + 1];
/* Computing MAX */
	d__1 = qmax, d__2 = z__[k];
	qmax = max(d__1,d__2);
/* Computing MIN */
	d__1 = emin, d__2 = z__[k + 1];
	emin = min(d__1,d__2);
/* Computing MAX */
	d__1 = max(qmax,zmax), d__2 = z__[k + 1];
	zmax = max(d__1,d__2);
/* L10: */
    }
    if (z__[(*n << 1) - 1] < 0.) {
	*info = -((*n << 1) + 199);
	xerbla_("DLASQ2", &c__2);
	return 0;
    }
    d__ += z__[(*n << 1) - 1];
/* Computing MAX */
    d__1 = qmax, d__2 = z__[(*n << 1) - 1];
    qmax = max(d__1,d__2);
    zmax = max(qmax,zmax);

/*     Check for diagonality. */

    if (e == 0.) {
	i__1 = *n;
	for (k = 2; k <= i__1; ++k) {
	    z__[k] = z__[(k << 1) - 1];
/* L20: */
	}
	dlasrt_("D", n, &z__[1], &iinfo);
	z__[(*n << 1) - 1] = d__;
	return 0;
    }

    trace = d__ + e;

/*     Check for zero data. */

    if (trace == 0.) {
	z__[(*n << 1) - 1] = 0.;
	return 0;
    }

/*     Check whether the machine is IEEE conformable. */

    ieee = ilaenv_(&c__10, "DLASQ2", "N", &c__1, &c__2, &c__3, &c__4) == 1 && ilaenv_(&c__11, "DLASQ2", "N", &c__1, &c__2,
	     &c__3, &c__4) == 1;

/*     Rearrange data for locality: Z=(q1,qq1,e1,ee1,q2,qq2,e2,ee2,...). */

    for (k = *n << 1; k >= 2; k += -2) {
	z__[k * 2] = 0.;
	z__[(k << 1) - 1] = z__[k];
	z__[(k << 1) - 2] = 0.;
	z__[(k << 1) - 3] = z__[k - 1];
/* L30: */
    }

    i0 = 1;
    n0 = *n;

/*     Reverse the qd-array, if warranted. */

    if (z__[(i0 << 2) - 3] * 1.5 < z__[(n0 << 2) - 3]) {
	ipn4 = (i0 + n0) << 2;
	i__1 = (i0 + n0 - 1) << 1;
	for (i4 = i0 << 2; i4 <= i__1; i4 += 4) {
	    temp = z__[i4 - 3];
	    z__[i4 - 3] = z__[ipn4 - i4 - 3];
	    z__[ipn4 - i4 - 3] = temp;
	    temp = z__[i4 - 1];
	    z__[i4 - 1] = z__[ipn4 - i4 - 5];
	    z__[ipn4 - i4 - 5] = temp;
/* L40: */
	}
    }

/*     Initial split checking via dqd and Li's test. */

    pp = 0;

    for (k = 1; k <= 2; ++k) {

	d__ = z__[(n0 << 2) + pp - 3];
	i__1 = (i0 << 2) + pp;
	for (i4 = ((n0 - 1) << 2) + pp; i4 >= i__1; i4 += -4) {
	    if (z__[i4 - 1] <= tol2 * d__) {
		z__[i4 - 1] = -0.;
		d__ = z__[i4 - 3];
	    } else {
		d__ = z__[i4 - 3] * (d__ / (d__ + z__[i4 - 1]));
	    }
/* L50: */
	}

/*        dqd maps Z to ZZ plus Li's test. */

	emin = z__[(i0 << 2) + pp + 1];
	d__ = z__[(i0 << 2) + pp - 3];
	i__1 = ((n0 - 1) << 2) + pp;
	for (i4 = (i0 << 2) + pp; i4 <= i__1; i4 += 4) {
	    z__[i4 - (pp << 1) - 2] = d__ + z__[i4 - 1];
	    if (z__[i4 - 1] <= tol2 * d__) {
		z__[i4 - 1] = -0.;
		z__[i4 - (pp << 1) - 2] = d__;
		z__[i4 - (pp << 1)] = 0.;
		d__ = z__[i4 + 1];
	    } else if (safmin * z__[i4 + 1] < z__[i4 - (pp << 1) - 2] &&
		    safmin * z__[i4 - (pp << 1) - 2] < z__[i4 + 1]) {
		temp = z__[i4 + 1] / z__[i4 - (pp << 1) - 2];
		z__[i4 - (pp << 1)] = z__[i4 - 1] * temp;
		d__ *= temp;
	    } else {
		z__[i4 - (pp << 1)] = z__[i4 + 1] * (z__[i4 - 1] / z__[i4 - (
			pp << 1) - 2]);
		d__ = z__[i4 + 1] * (d__ / z__[i4 - (pp << 1) - 2]);
	    }
/* Computing MIN */
	    d__1 = emin, d__2 = z__[i4 - (pp << 1)];
	    emin = min(d__1,d__2);
/* L60: */
	}
	z__[(n0 << 2) - pp - 2] = d__;

/*        Now find qmax. */

	qmax = z__[(i0 << 2) - pp - 2];
	i__1 = (n0 << 2) - pp - 2;
	for (i4 = (i0 << 2) - pp + 2; i4 <= i__1; i4 += 4) {
/* Computing MAX */
	    d__1 = qmax, d__2 = z__[i4];
	    qmax = max(d__1,d__2);
/* L70: */
	}

/*        Prepare for the next iteration on K. */

	pp = 1 - pp;
/* L80: */
    }

/*     Initialise variables to pass to DLASQ3. */

    ttype = 0;
    dmin1 = 0.;
    dmin2 = 0.;
    dn = 0.;
    dn1 = 0.;
    dn2 = 0.;
    g = 0.;
    tau = 0.;

    iter = 2;
    nfail = 0;
    ndiv = (n0 - i0) << 1;

    i__1 = *n + 1;
    for (iwhila = 1; iwhila <= i__1; ++iwhila) {
	if (n0 < 1) {
	    goto L170;
	}

/*        While array unfinished do */

/*        E(N0) holds the value of SIGMA when submatrix in I0:N0 */
/*        splits from the rest of the array, but is negated. */

	desig = 0.;
	if (n0 == *n) {
	    sigma = 0.;
	} else {
	    sigma = -z__[(n0 << 2) - 1];
	}
	if (sigma < 0.) {
	    *info = 1;
	    return 0;
	}

/*        Find last unreduced submatrix's top index I0, find QMAX and */
/*        EMIN. Find Gershgorin-type bound if Q's much greater than E's. */

	emax = 0.;
	if (n0 > i0) {
	    emin = (d__1 = z__[(n0 << 2) - 5], abs(d__1));
	} else {
	    emin = 0.;
	}
	qmin = z__[(n0 << 2) - 3];
	qmax = qmin;
	for (i4 = n0 << 2; i4 >= 8; i4 += -4) {
	    if (z__[i4 - 5] <= 0.) {
		goto L100;
	    }
	    if (qmin >= emax * 4.) {
/* Computing MIN */
		d__1 = qmin, d__2 = z__[i4 - 3];
		qmin = min(d__1,d__2);
/* Computing MAX */
		d__1 = emax, d__2 = z__[i4 - 5];
		emax = max(d__1,d__2);
	    }
/* Computing MAX */
	    d__1 = qmax, d__2 = z__[i4 - 7] + z__[i4 - 5];
	    qmax = max(d__1,d__2);
/* Computing MIN */
	    d__1 = emin, d__2 = z__[i4 - 5];
	    emin = min(d__1,d__2);
/* L90: */
	}
	i4 = 4;

L100:
	i0 = i4 / 4;
	pp = 0;

	if (n0 - i0 > 1) {
	    dee = z__[(i0 << 2) - 3];
	    deemin = dee;
	    kmin = i0;
	    i__2 = (n0 << 2) - 3;
	    for (i4 = (i0 << 2) + 1; i4 <= i__2; i4 += 4) {
		dee = z__[i4] * (dee / (dee + z__[i4 - 2]));
		if (dee <= deemin) {
		    deemin = dee;
		    kmin = (i4 + 3) / 4;
		}
/* L110: */
	    }
	    if ((kmin - i0) << 1 < n0 - kmin && deemin <= z__[(n0 << 2) - 3] *
		    .5) {
		ipn4 = (i0 + n0) << 2;
		pp = 2;
		i__2 = (i0 + n0 - 1) << 1;
		for (i4 = i0 << 2; i4 <= i__2; i4 += 4) {
		    temp = z__[i4 - 3];
		    z__[i4 - 3] = z__[ipn4 - i4 - 3];
		    z__[ipn4 - i4 - 3] = temp;
		    temp = z__[i4 - 2];
		    z__[i4 - 2] = z__[ipn4 - i4 - 2];
		    z__[ipn4 - i4 - 2] = temp;
		    temp = z__[i4 - 1];
		    z__[i4 - 1] = z__[ipn4 - i4 - 5];
		    z__[ipn4 - i4 - 5] = temp;
		    temp = z__[i4];
		    z__[i4] = z__[ipn4 - i4 - 4];
		    z__[ipn4 - i4 - 4] = temp;
/* L120: */
		}
	    }
	}

/*        Put -(initial shift) into DMIN. */

/* Computing MAX */
	d__1 = 0., d__2 = qmin - sqrt(qmin) * 2. * sqrt(emax);
	dmin__ = -max(d__1,d__2);

/*        Now I0:N0 is unreduced. */
/*        PP = 0 for ping, PP = 1 for pong. */
/*        PP = 2 indicates that flipping was applied to the Z array and */
/*               and that the tests for deflation upon entry in DLASQ3 */
/*               should not be performed. */

	nbig = (n0 - i0 + 1) * 30;
	i__2 = nbig;
	for (iwhilb = 1; iwhilb <= i__2; ++iwhilb) {
	    if (i0 > n0) {
		goto L150;
	    }

/*           While submatrix unfinished take a good dqds step. */

	    dlasq3_(&i0, &n0, &z__[1], &pp, &dmin__, &sigma, &desig, &qmax, &
		    nfail, &iter, &ndiv, &ieee, &ttype, &dmin1, &dmin2, &dn, &
		    dn1, &dn2, &g, &tau);

	    pp = 1 - pp;

/*           When EMIN is very small check for splits. */

	    if (pp == 0 && n0 - i0 >= 3) {
		if (z__[n0 * 4] <= tol2 * qmax || z__[(n0 << 2) - 1] <= tol2 *
			 sigma) {
		    splt = i0 - 1;
		    qmax = z__[(i0 << 2) - 3];
		    emin = z__[(i0 << 2) - 1];
		    oldemn = z__[i0 * 4];
		    i__3 = (n0 - 3) << 2;
		    for (i4 = i0 << 2; i4 <= i__3; i4 += 4) {
			if (z__[i4] <= tol2 * z__[i4 - 3] || z__[i4 - 1] <=
				tol2 * sigma) {
			    z__[i4 - 1] = -sigma;
			    splt = i4 / 4;
			    qmax = 0.;
			    emin = z__[i4 + 3];
			    oldemn = z__[i4 + 4];
			} else {
/* Computing MAX */
			    d__1 = qmax, d__2 = z__[i4 + 1];
			    qmax = max(d__1,d__2);
/* Computing MIN */
			    d__1 = emin, d__2 = z__[i4 - 1];
			    emin = min(d__1,d__2);
/* Computing MIN */
			    d__1 = oldemn, d__2 = z__[i4];
			    oldemn = min(d__1,d__2);
			}
/* L130: */
		    }
		    z__[(n0 << 2) - 1] = emin;
		    z__[n0 * 4] = oldemn;
		    i0 = splt + 1;
		}
	    }

/* L140: */
	}

	*info = 2;
	return 0;

/*        end IWHILB */

L150:

/* L160: */
	;
    }

    *info = 3;
    return 0;

/*     end IWHILA */

L170:

/*     Move q's to the front. */

    i__1 = *n;
    for (k = 2; k <= i__1; ++k) {
	z__[k] = z__[(k << 2) - 3];
/* L180: */
    }

/*     Sort and compute sum of eigenvalues. */

    dlasrt_("D", n, &z__[1], &iinfo);

    e = 0.;
    for (k = *n; k >= 1; --k) {
	e += z__[k];
/* L190: */
    }

/*     Store trace, sum(eigenvalues) and information on performance. */

    z__[(*n << 1) + 1] = trace;
    z__[(*n << 1) + 2] = e;
    z__[(*n << 1) + 3] = (doublereal) iter;
/* Computing 2nd power */
    i__1 = *n;
    z__[(*n << 1) + 4] = (doublereal) ndiv / (doublereal) (i__1 * i__1);
    z__[(*n << 1) + 5] = nfail * 100. / (doublereal) iter;
    return 0;

/*     End of DLASQ2 */

} /* dlasq2_ */

/* Subroutine */ int dlasq3_(integer *i0, integer *n0, doublereal *z__,
	integer *pp, doublereal *dmin__, doublereal *sigma, doublereal *desig,
	 doublereal *qmax, integer *nfail, integer *iter, integer *ndiv,
	logical *ieee, integer *ttype, doublereal *dmin1, doublereal *dmin2,
	doublereal *dn, doublereal *dn1, doublereal *dn2, doublereal *g,
	doublereal *tau)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Local variables */
    doublereal s, t;
    integer j4, nn;
    doublereal eps, tol;
    integer n0in, ipn4;
    doublereal tol2, temp;
    extern /* Subroutine */ int dlasq4_(integer *, integer *, doublereal *,
	    integer *, integer *, doublereal *, doublereal *, doublereal *,
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     doublereal *), dlasq5_(integer *, integer *, doublereal *,
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, logical *), dlasq6_(
	    integer *, integer *, doublereal *, integer *, doublereal *,
	    doublereal *, doublereal *, doublereal *, doublereal *,
	    doublereal *);
    extern doublereal dlamch_(char *);
    extern logical disnan_(doublereal *);


/*  -- LAPACK routine (version 3.2)                                    -- */

/*  -- Contributed by Osni Marques of the Lawrence Berkeley National   -- */
/*  -- Laboratory and Beresford Parlett of the Univ. of California at  -- */
/*  -- Berkeley                                                        -- */
/*  -- November 2008                                                   -- */

/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLASQ3 checks for deflation, computes a shift (TAU) and calls dqds. */
/*  In case of failure it changes shifts, and tries again until output */
/*  is positive. */

/*  Arguments */
/*  ========= */

/*  I0     (input) INTEGER */
/*         First index. */

/*  N0     (input) INTEGER */
/*         Last index. */

/*  Z      (input) DOUBLE PRECISION array, dimension ( 4*N ) */
/*         Z holds the qd array. */

/*  PP     (input/output) INTEGER */
/*         PP=0 for ping, PP=1 for pong. */
/*         PP=2 indicates that flipping was applied to the Z array */
/*         and that the initial tests for deflation should not be */
/*         performed. */

/*  DMIN   (output) DOUBLE PRECISION */
/*         Minimum value of d. */

/*  SIGMA  (output) DOUBLE PRECISION */
/*         Sum of shifts used in current segment. */

/*  DESIG  (input/output) DOUBLE PRECISION */
/*         Lower order part of SIGMA */

/*  QMAX   (input) DOUBLE PRECISION */
/*         Maximum value of q. */

/*  NFAIL  (output) INTEGER */
/*         Number of times shift was too big. */

/*  ITER   (output) INTEGER */
/*         Number of iterations. */

/*  NDIV   (output) INTEGER */
/*         Number of divisions. */

/*  IEEE   (input) LOGICAL */
/*         Flag for IEEE or non IEEE arithmetic (passed to DLASQ5). */

/*  TTYPE  (input/output) INTEGER */
/*         Shift type. */

/*  DMIN1, DMIN2, DN, DN1, DN2, G, TAU (input/output) DOUBLE PRECISION */
/*         These are passed as arguments in order to save their values */
/*         between calls to DLASQ3. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. External Function .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    --z__;

    /* Function Body */
    n0in = *n0;
    eps = dlamch_("Precision");
    tol = eps * 100.;
/* Computing 2nd power */
    d__1 = tol;
    tol2 = d__1 * d__1;

/*     Check for deflation. */

L10:

    if (*n0 < *i0) {
	return 0;
    }
    if (*n0 == *i0) {
	goto L20;
    }
    nn = (*n0 << 2) + *pp;
    if (*n0 == *i0 + 1) {
	goto L40;
    }

/*     Check whether E(N0-1) is negligible, 1 eigenvalue. */

    if (z__[nn - 5] > tol2 * (*sigma + z__[nn - 3]) && z__[nn - (*pp << 1) -
	    4] > tol2 * z__[nn - 7]) {
	goto L30;
    }

L20:

    z__[(*n0 << 2) - 3] = z__[(*n0 << 2) + *pp - 3] + *sigma;
    --(*n0);
    goto L10;

/*     Check  whether E(N0-2) is negligible, 2 eigenvalues. */

L30:

    if (z__[nn - 9] > tol2 * *sigma && z__[nn - (*pp << 1) - 8] > tol2 * z__[
	    nn - 11]) {
	goto L50;
    }

L40:

    if (z__[nn - 3] > z__[nn - 7]) {
	s = z__[nn - 3];
	z__[nn - 3] = z__[nn - 7];
	z__[nn - 7] = s;
    }
    if (z__[nn - 5] > z__[nn - 3] * tol2) {
	t = (z__[nn - 7] - z__[nn - 3] + z__[nn - 5]) * .5;
	s = z__[nn - 3] * (z__[nn - 5] / t);
	if (s <= t) {
	    s = z__[nn - 3] * (z__[nn - 5] / (t * (sqrt(s / t + 1.) + 1.)));
	} else {
	    s = z__[nn - 3] * (z__[nn - 5] / (t + sqrt(t) * sqrt(t + s)));
	}
	t = z__[nn - 7] + (s + z__[nn - 5]);
	z__[nn - 3] *= z__[nn - 7] / t;
	z__[nn - 7] = t;
    }
    z__[(*n0 << 2) - 7] = z__[nn - 7] + *sigma;
    z__[(*n0 << 2) - 3] = z__[nn - 3] + *sigma;
    *n0 += -2;
    goto L10;

L50:
    if (*pp == 2) {
	*pp = 0;
    }

/*     Reverse the qd-array, if warranted. */

    if (*dmin__ <= 0. || *n0 < n0in) {
	if (z__[(*i0 << 2) + *pp - 3] * 1.5 < z__[(*n0 << 2) + *pp - 3]) {
	    ipn4 = (*i0 + *n0) << 2;
	    i__1 = (*i0 + *n0 - 1) << 1;
	    for (j4 = *i0 << 2; j4 <= i__1; j4 += 4) {
		temp = z__[j4 - 3];
		z__[j4 - 3] = z__[ipn4 - j4 - 3];
		z__[ipn4 - j4 - 3] = temp;
		temp = z__[j4 - 2];
		z__[j4 - 2] = z__[ipn4 - j4 - 2];
		z__[ipn4 - j4 - 2] = temp;
		temp = z__[j4 - 1];
		z__[j4 - 1] = z__[ipn4 - j4 - 5];
		z__[ipn4 - j4 - 5] = temp;
		temp = z__[j4];
		z__[j4] = z__[ipn4 - j4 - 4];
		z__[ipn4 - j4 - 4] = temp;
/* L60: */
	    }
	    if (*n0 - *i0 <= 4) {
		z__[(*n0 << 2) + *pp - 1] = z__[(*i0 << 2) + *pp - 1];
		z__[(*n0 << 2) - *pp] = z__[(*i0 << 2) - *pp];
	    }
/* Computing MIN */
	    d__1 = *dmin2, d__2 = z__[(*n0 << 2) + *pp - 1];
	    *dmin2 = min(d__1,d__2);
/* Computing MIN */
	    d__1 = z__[(*n0 << 2) + *pp - 1], d__2 = z__[(*i0 << 2) + *pp - 1]
		    , d__1 = min(d__1,d__2), d__2 = z__[(*i0 << 2) + *pp + 3];
	    z__[(*n0 << 2) + *pp - 1] = min(d__1,d__2);
/* Computing MIN */
	    d__1 = z__[(*n0 << 2) - *pp], d__2 = z__[(*i0 << 2) - *pp], d__1 =
		     min(d__1,d__2), d__2 = z__[(*i0 << 2) - *pp + 4];
	    z__[(*n0 << 2) - *pp] = min(d__1,d__2);
/* Computing MAX */
	    d__1 = *qmax, d__2 = z__[(*i0 << 2) + *pp - 3], d__1 = max(d__1,
		    d__2), d__2 = z__[(*i0 << 2) + *pp + 1];
	    *qmax = max(d__1,d__2);
	    *dmin__ = -0.;
	}
    }

/*     Choose a shift. */

    dlasq4_(i0, n0, &z__[1], pp, &n0in, dmin__, dmin1, dmin2, dn, dn1, dn2,
	    tau, ttype, g);

/*     Call dqds until DMIN > 0. */

L70:

    dlasq5_(i0, n0, &z__[1], pp, tau, dmin__, dmin1, dmin2, dn, dn1, dn2,
	    ieee);

    *ndiv += *n0 - *i0 + 2;
    ++(*iter);

/*     Check status. */

    if (*dmin__ >= 0. && *dmin1 > 0.) {

/*        Success. */

	goto L90;

    } else if (*dmin__ < 0. && *dmin1 > 0. && z__[((*n0 - 1) << 2) - *pp] < tol
	    * (*sigma + *dn1) && abs(*dn) < tol * *sigma) {

/*        Convergence hidden by negative DN. */

	z__[((*n0 - 1) << 2) - *pp + 2] = 0.;
	*dmin__ = 0.;
	goto L90;
    } else if (*dmin__ < 0.) {

/*        TAU too big. Select new TAU and try again. */

	++(*nfail);
	if (*ttype < -22) {

/*           Failed twice. Play it safe. */

	    *tau = 0.;
	} else if (*dmin1 > 0.) {

/*           Late failure. Gives excellent shift. */

	    *tau = (*tau + *dmin__) * (1. - eps * 2.);
	    *ttype += -11;
	} else {

/*           Early failure. Divide by 4. */

	    *tau *= .25;
	    *ttype += -12;
	}
	goto L70;
    } else if (disnan_(dmin__)) {

/*        NaN. */

	if (*tau == 0.) {
	    goto L80;
	} else {
	    *tau = 0.;
	    goto L70;
	}
    } else {

/*        Possible underflow. Play it safe. */

	goto L80;
    }

/*     Risk of underflow. */

L80:
    dlasq6_(i0, n0, &z__[1], pp, dmin__, dmin1, dmin2, dn, dn1, dn2);
    *ndiv += *n0 - *i0 + 2;
    ++(*iter);
    *tau = 0.;

L90:
    if (*tau < *sigma) {
	*desig += *tau;
	t = *sigma + *desig;
	*desig -= t - *sigma;
    } else {
	t = *sigma + *tau;
	*desig = *sigma - (t - *tau) + *desig;
    }
    *sigma = t;

    return 0;

/*     End of DLASQ3 */

} /* dlasq3_ */

/* Subroutine */ int dlasq4_(integer *i0, integer *n0, doublereal *z__,
	integer *pp, integer *n0in, doublereal *dmin__, doublereal *dmin1,
	doublereal *dmin2, doublereal *dn, doublereal *dn1, doublereal *dn2,
	doublereal *tau, integer *ttype, doublereal *g)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Local variables */
    doublereal s, a2, b1, b2;
    integer i4, nn, np;
    doublereal gam, gap1, gap2;


/*  -- LAPACK routine (version 3.2)                                    -- */

/*  -- Contributed by Osni Marques of the Lawrence Berkeley National   -- */
/*  -- Laboratory and Beresford Parlett of the Univ. of California at  -- */
/*  -- Berkeley                                                        -- */
/*  -- November 2008                                                   -- */

/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLASQ4 computes an approximation TAU to the smallest eigenvalue */
/*  using values of d from the previous transform. */

/*  I0    (input) INTEGER */
/*        First index. */

/*  N0    (input) INTEGER */
/*        Last index. */

/*  Z     (input) DOUBLE PRECISION array, dimension ( 4*N ) */
/*        Z holds the qd array. */

/*  PP    (input) INTEGER */
/*        PP=0 for ping, PP=1 for pong. */

/*  NOIN  (input) INTEGER */
/*        The value of N0 at start of EIGTEST. */

/*  DMIN  (input) DOUBLE PRECISION */
/*        Minimum value of d. */

/*  DMIN1 (input) DOUBLE PRECISION */
/*        Minimum value of d, excluding D( N0 ). */

/*  DMIN2 (input) DOUBLE PRECISION */
/*        Minimum value of d, excluding D( N0 ) and D( N0-1 ). */

/*  DN    (input) DOUBLE PRECISION */
/*        d(N) */

/*  DN1   (input) DOUBLE PRECISION */
/*        d(N-1) */

/*  DN2   (input) DOUBLE PRECISION */
/*        d(N-2) */

/*  TAU   (output) DOUBLE PRECISION */
/*        This is the shift. */

/*  TTYPE (output) INTEGER */
/*        Shift type. */

/*  G     (input/output) REAL */
/*        G is passed as an argument in order to save its value between */
/*        calls to DLASQ4. */

/*  Further Details */
/*  =============== */
/*  CNST1 = 9/16 */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     A negative DMIN forces the shift to take that absolute value */
/*     TTYPE records the type of shift. */

    /* Parameter adjustments */
    --z__;

    /* Function Body */
    if (*dmin__ <= 0.) {
	*tau = -(*dmin__);
	*ttype = -1;
	return 0;
    }

    nn = (*n0 << 2) + *pp;
    if (*n0in == *n0) {

/*        No eigenvalues deflated. */

	if (*dmin__ == *dn || *dmin__ == *dn1) {

	    b1 = sqrt(z__[nn - 3]) * sqrt(z__[nn - 5]);
	    b2 = sqrt(z__[nn - 7]) * sqrt(z__[nn - 9]);
	    a2 = z__[nn - 7] + z__[nn - 5];

/*           Cases 2 and 3. */

	    if (*dmin__ == *dn && *dmin1 == *dn1) {
		gap2 = *dmin2 - a2 - *dmin2 * .25;
		if (gap2 > 0. && gap2 > b2) {
		    gap1 = a2 - *dn - b2 / gap2 * b2;
		} else {
		    gap1 = a2 - *dn - (b1 + b2);
		}
		if (gap1 > 0. && gap1 > b1) {
/* Computing MAX */
		    d__1 = *dn - b1 / gap1 * b1, d__2 = *dmin__ * .5;
		    s = max(d__1,d__2);
		    *ttype = -2;
		} else {
		    s = 0.;
		    if (*dn > b1) {
			s = *dn - b1;
		    }
		    if (a2 > b1 + b2) {
/* Computing MIN */
			d__1 = s, d__2 = a2 - (b1 + b2);
			s = min(d__1,d__2);
		    }
/* Computing MAX */
		    d__1 = s, d__2 = *dmin__ * .333;
		    s = max(d__1,d__2);
		    *ttype = -3;
		}
	    } else {

/*              Case 4. */

		*ttype = -4;
		s = *dmin__ * .25;
		if (*dmin__ == *dn) {
		    gam = *dn;
		    a2 = 0.;
		    if (z__[nn - 5] > z__[nn - 7]) {
			return 0;
		    }
		    b2 = z__[nn - 5] / z__[nn - 7];
		    np = nn - 9;
		} else {
		    np = nn - (*pp << 1);
		    b2 = z__[np - 2];
		    gam = *dn1;
		    if (z__[np - 4] > z__[np - 2]) {
			return 0;
		    }
		    a2 = z__[np - 4] / z__[np - 2];
		    if (z__[nn - 9] > z__[nn - 11]) {
			return 0;
		    }
		    b2 = z__[nn - 9] / z__[nn - 11];
		    np = nn - 13;
		}

/*              Approximate contribution to norm squared from I < NN-1. */

		a2 += b2;
		i__1 = (*i0 << 2) - 1 + *pp;
		for (i4 = np; i4 >= i__1; i4 += -4) {
		    if (b2 == 0.) {
			goto L20;
		    }
		    b1 = b2;
		    if (z__[i4] > z__[i4 - 2]) {
			return 0;
		    }
		    b2 *= z__[i4] / z__[i4 - 2];
		    a2 += b2;
		    if (max(b2,b1) * 100. < a2 || .563 < a2) {
			goto L20;
		    }
/* L10: */
		}
L20:
		a2 *= 1.05;

/*              Rayleigh quotient residual bound. */

		if (a2 < .563) {
		    s = gam * (1. - sqrt(a2)) / (a2 + 1.);
		}
	    }
	} else if (*dmin__ == *dn2) {

/*           Case 5. */

	    *ttype = -5;
	    s = *dmin__ * .25;

/*           Compute contribution to norm squared from I > NN-2. */

	    np = nn - (*pp << 1);
	    b1 = z__[np - 2];
	    b2 = z__[np - 6];
	    gam = *dn2;
	    if (z__[np - 8] > b2 || z__[np - 4] > b1) {
		return 0;
	    }
	    a2 = z__[np - 8] / b2 * (z__[np - 4] / b1 + 1.);

/*           Approximate contribution to norm squared from I < NN-2. */

	    if (*n0 - *i0 > 2) {
		b2 = z__[nn - 13] / z__[nn - 15];
		a2 += b2;
		i__1 = (*i0 << 2) - 1 + *pp;
		for (i4 = nn - 17; i4 >= i__1; i4 += -4) {
		    if (b2 == 0.) {
			goto L40;
		    }
		    b1 = b2;
		    if (z__[i4] > z__[i4 - 2]) {
			return 0;
		    }
		    b2 *= z__[i4] / z__[i4 - 2];
		    a2 += b2;
		    if (max(b2,b1) * 100. < a2 || .563 < a2) {
			goto L40;
		    }
/* L30: */
		}
L40:
		a2 *= 1.05;
	    }

	    if (a2 < .563) {
		s = gam * (1. - sqrt(a2)) / (a2 + 1.);
	    }
	} else {

/*           Case 6, no information to guide us. */

	    if (*ttype == -6) {
		*g += (1. - *g) * .333;
	    } else if (*ttype == -18) {
		*g = .083250000000000005;
	    } else {
		*g = .25;
	    }
	    s = *g * *dmin__;
	    *ttype = -6;
	}

    } else if (*n0in == *n0 + 1) {

/*        One eigenvalue just deflated. Use DMIN1, DN1 for DMIN and DN. */

	if (*dmin1 == *dn1 && *dmin2 == *dn2) {

/*           Cases 7 and 8. */

	    *ttype = -7;
	    s = *dmin1 * .333;
	    if (z__[nn - 5] > z__[nn - 7]) {
		return 0;
	    }
	    b1 = z__[nn - 5] / z__[nn - 7];
	    b2 = b1;
	    if (b2 == 0.) {
		goto L60;
	    }
	    i__1 = (*i0 << 2) - 1 + *pp;
	    for (i4 = (*n0 << 2) - 9 + *pp; i4 >= i__1; i4 += -4) {
		a2 = b1;
		if (z__[i4] > z__[i4 - 2]) {
		    return 0;
		}
		b1 *= z__[i4] / z__[i4 - 2];
		b2 += b1;
		if (max(b1,a2) * 100. < b2) {
		    goto L60;
		}
/* L50: */
	    }
L60:
	    b2 = sqrt(b2 * 1.05);
/* Computing 2nd power */
	    d__1 = b2;
	    a2 = *dmin1 / (d__1 * d__1 + 1.);
	    gap2 = *dmin2 * .5 - a2;
	    if (gap2 > 0. && gap2 > b2 * a2) {
/* Computing MAX */
		d__1 = s, d__2 = a2 * (1. - a2 * 1.01 * (b2 / gap2) * b2);
		s = max(d__1,d__2);
	    } else {
/* Computing MAX */
		d__1 = s, d__2 = a2 * (1. - b2 * 1.01);
		s = max(d__1,d__2);
		*ttype = -8;
	    }
	} else {

/*           Case 9. */

	    s = *dmin1 * .25;
	    if (*dmin1 == *dn1) {
		s = *dmin1 * .5;
	    }
	    *ttype = -9;
	}

    } else if (*n0in == *n0 + 2) {

/*        Two eigenvalues deflated. Use DMIN2, DN2 for DMIN and DN. */

/*        Cases 10 and 11. */

	if (*dmin2 == *dn2 && z__[nn - 5] * 2. < z__[nn - 7]) {
	    *ttype = -10;
	    s = *dmin2 * .333;
	    if (z__[nn - 5] > z__[nn - 7]) {
		return 0;
	    }
	    b1 = z__[nn - 5] / z__[nn - 7];
	    b2 = b1;
	    if (b2 == 0.) {
		goto L80;
	    }
	    i__1 = (*i0 << 2) - 1 + *pp;
	    for (i4 = (*n0 << 2) - 9 + *pp; i4 >= i__1; i4 += -4) {
		if (z__[i4] > z__[i4 - 2]) {
		    return 0;
		}
		b1 *= z__[i4] / z__[i4 - 2];
		b2 += b1;
		if (b1 * 100. < b2) {
		    goto L80;
		}
/* L70: */
	    }
L80:
	    b2 = sqrt(b2 * 1.05);
/* Computing 2nd power */
	    d__1 = b2;
	    a2 = *dmin2 / (d__1 * d__1 + 1.);
	    gap2 = z__[nn - 7] + z__[nn - 9] - sqrt(z__[nn - 11]) * sqrt(z__[
		    nn - 9]) - a2;
	    if (gap2 > 0. && gap2 > b2 * a2) {
/* Computing MAX */
		d__1 = s, d__2 = a2 * (1. - a2 * 1.01 * (b2 / gap2) * b2);
		s = max(d__1,d__2);
	    } else {
/* Computing MAX */
		d__1 = s, d__2 = a2 * (1. - b2 * 1.01);
		s = max(d__1,d__2);
	    }
	} else {
	    s = *dmin2 * .25;
	    *ttype = -11;
	}
    } else if (*n0in > *n0 + 2) {

/*        Case 12, more than two eigenvalues deflated. No information. */

	s = 0.;
	*ttype = -12;
    }

    *tau = s;
    return 0;

/*     End of DLASQ4 */

} /* dlasq4_ */

/* Subroutine */ int dlasq5_(integer *i0, integer *n0, doublereal *z__,
	integer *pp, doublereal *tau, doublereal *dmin__, doublereal *dmin1,
	doublereal *dmin2, doublereal *dn, doublereal *dnm1, doublereal *dnm2,
	 logical *ieee)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Local variables */
    doublereal d__;
    integer j4, j4p2;
    doublereal emin, temp;


/*  -- LAPACK routine (version 3.2)                                    -- */

/*  -- Contributed by Osni Marques of the Lawrence Berkeley National   -- */
/*  -- Laboratory and Beresford Parlett of the Univ. of California at  -- */
/*  -- Berkeley                                                        -- */
/*  -- November 2008                                                   -- */

/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLASQ5 computes one dqds transform in ping-pong form, one */
/*  version for IEEE machines another for non IEEE machines. */

/*  Arguments */
/*  ========= */

/*  I0    (input) INTEGER */
/*        First index. */

/*  N0    (input) INTEGER */
/*        Last index. */

/*  Z     (input) DOUBLE PRECISION array, dimension ( 4*N ) */
/*        Z holds the qd array. EMIN is stored in Z(4*N0) to avoid */
/*        an extra argument. */

/*  PP    (input) INTEGER */
/*        PP=0 for ping, PP=1 for pong. */

/*  TAU   (input) DOUBLE PRECISION */
/*        This is the shift. */

/*  DMIN  (output) DOUBLE PRECISION */
/*        Minimum value of d. */

/*  DMIN1 (output) DOUBLE PRECISION */
/*        Minimum value of d, excluding D( N0 ). */

/*  DMIN2 (output) DOUBLE PRECISION */
/*        Minimum value of d, excluding D( N0 ) and D( N0-1 ). */

/*  DN    (output) DOUBLE PRECISION */
/*        d(N0), the last value of d. */

/*  DNM1  (output) DOUBLE PRECISION */
/*        d(N0-1). */

/*  DNM2  (output) DOUBLE PRECISION */
/*        d(N0-2). */

/*  IEEE  (input) LOGICAL */
/*        Flag for IEEE or non IEEE arithmetic. */

/*  ===================================================================== */

/*     .. Parameter .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    --z__;

    /* Function Body */
    if (*n0 - *i0 - 1 <= 0) {
	return 0;
    }

    j4 = (*i0 << 2) + *pp - 3;
    emin = z__[j4 + 4];
    d__ = z__[j4] - *tau;
    *dmin__ = d__;
    *dmin1 = -z__[j4];

    if (*ieee) {

/*        Code for IEEE arithmetic. */

	if (*pp == 0) {
	    i__1 = (*n0 - 3) << 2;
	    for (j4 = *i0 << 2; j4 <= i__1; j4 += 4) {
		z__[j4 - 2] = d__ + z__[j4 - 1];
		temp = z__[j4 + 1] / z__[j4 - 2];
		d__ = d__ * temp - *tau;
		*dmin__ = min(*dmin__,d__);
		z__[j4] = z__[j4 - 1] * temp;
/* Computing MIN */
		d__1 = z__[j4];
		emin = min(d__1,emin);
/* L10: */
	    }
	} else {
	    i__1 = (*n0 - 3) << 2;
	    for (j4 = *i0 << 2; j4 <= i__1; j4 += 4) {
		z__[j4 - 3] = d__ + z__[j4];
		temp = z__[j4 + 2] / z__[j4 - 3];
		d__ = d__ * temp - *tau;
		*dmin__ = min(*dmin__,d__);
		z__[j4 - 1] = z__[j4] * temp;
/* Computing MIN */
		d__1 = z__[j4 - 1];
		emin = min(d__1,emin);
/* L20: */
	    }
	}

/*        Unroll last two steps. */

	*dnm2 = d__;
	*dmin2 = *dmin__;
	j4 = ((*n0 - 2) << 2) - *pp;
	j4p2 = j4 + (*pp << 1) - 1;
	z__[j4 - 2] = *dnm2 + z__[j4p2];
	z__[j4] = z__[j4p2 + 2] * (z__[j4p2] / z__[j4 - 2]);
	*dnm1 = z__[j4p2 + 2] * (*dnm2 / z__[j4 - 2]) - *tau;
	*dmin__ = min(*dmin__,*dnm1);

	*dmin1 = *dmin__;
	j4 += 4;
	j4p2 = j4 + (*pp << 1) - 1;
	z__[j4 - 2] = *dnm1 + z__[j4p2];
	z__[j4] = z__[j4p2 + 2] * (z__[j4p2] / z__[j4 - 2]);
	*dn = z__[j4p2 + 2] * (*dnm1 / z__[j4 - 2]) - *tau;
	*dmin__ = min(*dmin__,*dn);

    } else {

/*        Code for non IEEE arithmetic. */

	if (*pp == 0) {
	    i__1 = (*n0 - 3) << 2;
	    for (j4 = *i0 << 2; j4 <= i__1; j4 += 4) {
		z__[j4 - 2] = d__ + z__[j4 - 1];
		if (d__ < 0.) {
		    return 0;
		} else {
		    z__[j4] = z__[j4 + 1] * (z__[j4 - 1] / z__[j4 - 2]);
		    d__ = z__[j4 + 1] * (d__ / z__[j4 - 2]) - *tau;
		}
		*dmin__ = min(*dmin__,d__);
/* Computing MIN */
		d__1 = emin, d__2 = z__[j4];
		emin = min(d__1,d__2);
/* L30: */
	    }
	} else {
	    i__1 = (*n0 - 3) << 2;
	    for (j4 = *i0 << 2; j4 <= i__1; j4 += 4) {
		z__[j4 - 3] = d__ + z__[j4];
		if (d__ < 0.) {
		    return 0;
		} else {
		    z__[j4 - 1] = z__[j4 + 2] * (z__[j4] / z__[j4 - 3]);
		    d__ = z__[j4 + 2] * (d__ / z__[j4 - 3]) - *tau;
		}
		*dmin__ = min(*dmin__,d__);
/* Computing MIN */
		d__1 = emin, d__2 = z__[j4 - 1];
		emin = min(d__1,d__2);
/* L40: */
	    }
	}

/*        Unroll last two steps. */

	*dnm2 = d__;
	*dmin2 = *dmin__;
	j4 = ((*n0 - 2) << 2) - *pp;
	j4p2 = j4 + (*pp << 1) - 1;
	z__[j4 - 2] = *dnm2 + z__[j4p2];
	if (*dnm2 < 0.) {
	    return 0;
	} else {
	    z__[j4] = z__[j4p2 + 2] * (z__[j4p2] / z__[j4 - 2]);
	    *dnm1 = z__[j4p2 + 2] * (*dnm2 / z__[j4 - 2]) - *tau;
	}
	*dmin__ = min(*dmin__,*dnm1);

	*dmin1 = *dmin__;
	j4 += 4;
	j4p2 = j4 + (*pp << 1) - 1;
	z__[j4 - 2] = *dnm1 + z__[j4p2];
	if (*dnm1 < 0.) {
	    return 0;
	} else {
	    z__[j4] = z__[j4p2 + 2] * (z__[j4p2] / z__[j4 - 2]);
	    *dn = z__[j4p2 + 2] * (*dnm1 / z__[j4 - 2]) - *tau;
	}
	*dmin__ = min(*dmin__,*dn);

    }

    z__[j4 + 2] = *dn;
    z__[(*n0 << 2) - *pp] = emin;
    return 0;

/*     End of DLASQ5 */

} /* dlasq5_ */

/* Subroutine */ int dlasq6_(integer *i0, integer *n0, doublereal *z__,
	integer *pp, doublereal *dmin__, doublereal *dmin1, doublereal *dmin2,
	 doublereal *dn, doublereal *dnm1, doublereal *dnm2)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Local variables */
    doublereal d__;
    integer j4, j4p2;
    doublereal emin, temp;
    extern doublereal dlamch_(char *);
    doublereal safmin;


/*  -- LAPACK routine (version 3.2)                                    -- */

/*  -- Contributed by Osni Marques of the Lawrence Berkeley National   -- */
/*  -- Laboratory and Beresford Parlett of the Univ. of California at  -- */
/*  -- Berkeley                                                        -- */
/*  -- November 2008                                                   -- */

/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLASQ6 computes one dqd (shift equal to zero) transform in */
/*  ping-pong form, with protection against underflow and overflow. */

/*  Arguments */
/*  ========= */

/*  I0    (input) INTEGER */
/*        First index. */

/*  N0    (input) INTEGER */
/*        Last index. */

/*  Z     (input) DOUBLE PRECISION array, dimension ( 4*N ) */
/*        Z holds the qd array. EMIN is stored in Z(4*N0) to avoid */
/*        an extra argument. */

/*  PP    (input) INTEGER */
/*        PP=0 for ping, PP=1 for pong. */

/*  DMIN  (output) DOUBLE PRECISION */
/*        Minimum value of d. */

/*  DMIN1 (output) DOUBLE PRECISION */
/*        Minimum value of d, excluding D( N0 ). */

/*  DMIN2 (output) DOUBLE PRECISION */
/*        Minimum value of d, excluding D( N0 ) and D( N0-1 ). */

/*  DN    (output) DOUBLE PRECISION */
/*        d(N0), the last value of d. */

/*  DNM1  (output) DOUBLE PRECISION */
/*        d(N0-1). */

/*  DNM2  (output) DOUBLE PRECISION */
/*        d(N0-2). */

/*  ===================================================================== */

/*     .. Parameter .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Function .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    --z__;

    /* Function Body */
    if (*n0 - *i0 - 1 <= 0) {
	return 0;
    }

    safmin = dlamch_("Safe minimum");
    j4 = (*i0 << 2) + *pp - 3;
    emin = z__[j4 + 4];
    d__ = z__[j4];
    *dmin__ = d__;

    if (*pp == 0) {
	i__1 = (*n0 - 3) << 2;
	for (j4 = *i0 << 2; j4 <= i__1; j4 += 4) {
	    z__[j4 - 2] = d__ + z__[j4 - 1];
	    if (z__[j4 - 2] == 0.) {
		z__[j4] = 0.;
		d__ = z__[j4 + 1];
		*dmin__ = d__;
		emin = 0.;
	    } else if (safmin * z__[j4 + 1] < z__[j4 - 2] && safmin * z__[j4
		    - 2] < z__[j4 + 1]) {
		temp = z__[j4 + 1] / z__[j4 - 2];
		z__[j4] = z__[j4 - 1] * temp;
		d__ *= temp;
	    } else {
		z__[j4] = z__[j4 + 1] * (z__[j4 - 1] / z__[j4 - 2]);
		d__ = z__[j4 + 1] * (d__ / z__[j4 - 2]);
	    }
	    *dmin__ = min(*dmin__,d__);
/* Computing MIN */
	    d__1 = emin, d__2 = z__[j4];
	    emin = min(d__1,d__2);
/* L10: */
	}
    } else {
	i__1 = (*n0 - 3) << 2;
	for (j4 = *i0 << 2; j4 <= i__1; j4 += 4) {
	    z__[j4 - 3] = d__ + z__[j4];
	    if (z__[j4 - 3] == 0.) {
		z__[j4 - 1] = 0.;
		d__ = z__[j4 + 2];
		*dmin__ = d__;
		emin = 0.;
	    } else if (safmin * z__[j4 + 2] < z__[j4 - 3] && safmin * z__[j4
		    - 3] < z__[j4 + 2]) {
		temp = z__[j4 + 2] / z__[j4 - 3];
		z__[j4 - 1] = z__[j4] * temp;
		d__ *= temp;
	    } else {
		z__[j4 - 1] = z__[j4 + 2] * (z__[j4] / z__[j4 - 3]);
		d__ = z__[j4 + 2] * (d__ / z__[j4 - 3]);
	    }
	    *dmin__ = min(*dmin__,d__);
/* Computing MIN */
	    d__1 = emin, d__2 = z__[j4 - 1];
	    emin = min(d__1,d__2);
/* L20: */
	}
    }

/*     Unroll last two steps. */

    *dnm2 = d__;
    *dmin2 = *dmin__;
    j4 = ((*n0 - 2) << 2) - *pp;
    j4p2 = j4 + (*pp << 1) - 1;
    z__[j4 - 2] = *dnm2 + z__[j4p2];
    if (z__[j4 - 2] == 0.) {
	z__[j4] = 0.;
	*dnm1 = z__[j4p2 + 2];
	*dmin__ = *dnm1;
	emin = 0.;
    } else if (safmin * z__[j4p2 + 2] < z__[j4 - 2] && safmin * z__[j4 - 2] <
	    z__[j4p2 + 2]) {
	temp = z__[j4p2 + 2] / z__[j4 - 2];
	z__[j4] = z__[j4p2] * temp;
	*dnm1 = *dnm2 * temp;
    } else {
	z__[j4] = z__[j4p2 + 2] * (z__[j4p2] / z__[j4 - 2]);
	*dnm1 = z__[j4p2 + 2] * (*dnm2 / z__[j4 - 2]);
    }
    *dmin__ = min(*dmin__,*dnm1);

    *dmin1 = *dmin__;
    j4 += 4;
    j4p2 = j4 + (*pp << 1) - 1;
    z__[j4 - 2] = *dnm1 + z__[j4p2];
    if (z__[j4 - 2] == 0.) {
	z__[j4] = 0.;
	*dn = z__[j4p2 + 2];
	*dmin__ = *dn;
	emin = 0.;
    } else if (safmin * z__[j4p2 + 2] < z__[j4 - 2] && safmin * z__[j4 - 2] <
	    z__[j4p2 + 2]) {
	temp = z__[j4p2 + 2] / z__[j4 - 2];
	z__[j4] = z__[j4p2] * temp;
	*dn = *dnm1 * temp;
    } else {
	z__[j4] = z__[j4p2 + 2] * (z__[j4p2] / z__[j4 - 2]);
	*dn = z__[j4p2 + 2] * (*dnm1 / z__[j4 - 2]);
    }
    *dmin__ = min(*dmin__,*dn);

    z__[j4 + 2] = *dn;
    z__[(*n0 << 2) - *pp] = emin;
    return 0;

/*     End of DLASQ6 */

} /* dlasq6_ */

/* Subroutine */ int dlasr_(char *side, char *pivot, char *direct, integer *m,
	 integer *n, doublereal *c__, doublereal *s, doublereal *a, integer *
	lda)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;

    /* Local variables */
    integer i__, j, info;
    doublereal temp;
    extern logical lsame_(char *, char *);
    doublereal ctemp, stemp;
    extern /* Subroutine */ int xerbla_(char *, integer *);


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLASR applies a sequence of plane rotations to a real matrix A, */
/*  from either the left or the right. */

/*  When SIDE = 'L', the transformation takes the form */

/*     A := P*A */

/*  and when SIDE = 'R', the transformation takes the form */

/*     A := A*P**T */

/*  where P is an orthogonal matrix consisting of a sequence of z plane */
/*  rotations, with z = M when SIDE = 'L' and z = N when SIDE = 'R', */
/*  and P**T is the transpose of P. */

/*  When DIRECT = 'F' (Forward sequence), then */

/*     P = P(z-1) * ... * P(2) * P(1) */

/*  and when DIRECT = 'B' (Backward sequence), then */

/*     P = P(1) * P(2) * ... * P(z-1) */

/*  where P(k) is a plane rotation matrix defined by the 2-by-2 rotation */

/*     R(k) = (  c(k)  s(k) ) */
/*          = ( -s(k)  c(k) ). */

/*  When PIVOT = 'V' (Variable pivot), the rotation is performed */
/*  for the plane (k,k+1), i.e., P(k) has the form */

/*     P(k) = (  1                                            ) */
/*            (       ...                                     ) */
/*            (              1                                ) */
/*            (                   c(k)  s(k)                  ) */
/*            (                  -s(k)  c(k)                  ) */
/*            (                                1              ) */
/*            (                                     ...       ) */
/*            (                                            1  ) */

/*  where R(k) appears as a rank-2 modification to the identity matrix in */
/*  rows and columns k and k+1. */

/*  When PIVOT = 'T' (Top pivot), the rotation is performed for the */
/*  plane (1,k+1), so P(k) has the form */

/*     P(k) = (  c(k)                    s(k)                 ) */
/*            (         1                                     ) */
/*            (              ...                              ) */
/*            (                     1                         ) */
/*            ( -s(k)                    c(k)                 ) */
/*            (                                 1             ) */
/*            (                                      ...      ) */
/*            (                                             1 ) */

/*  where R(k) appears in rows and columns 1 and k+1. */

/*  Similarly, when PIVOT = 'B' (Bottom pivot), the rotation is */
/*  performed for the plane (k,z), giving P(k) the form */

/*     P(k) = ( 1                                             ) */
/*            (      ...                                      ) */
/*            (             1                                 ) */
/*            (                  c(k)                    s(k) ) */
/*            (                         1                     ) */
/*            (                              ...              ) */
/*            (                                     1         ) */
/*            (                 -s(k)                    c(k) ) */

/*  where R(k) appears in rows and columns k and z.  The rotations are */
/*  performed without ever forming P(k) explicitly. */

/*  Arguments */
/*  ========= */

/*  SIDE    (input) CHARACTER*1 */
/*          Specifies whether the plane rotation matrix P is applied to */
/*          A on the left or the right. */
/*          = 'L':  Left, compute A := P*A */
/*          = 'R':  Right, compute A:= A*P**T */

/*  PIVOT   (input) CHARACTER*1 */
/*          Specifies the plane for which P(k) is a plane rotation */
/*          matrix. */
/*          = 'V':  Variable pivot, the plane (k,k+1) */
/*          = 'T':  Top pivot, the plane (1,k+1) */
/*          = 'B':  Bottom pivot, the plane (k,z) */

/*  DIRECT  (input) CHARACTER*1 */
/*          Specifies whether P is a forward or backward sequence of */
/*          plane rotations. */
/*          = 'F':  Forward, P = P(z-1)*...*P(2)*P(1) */
/*          = 'B':  Backward, P = P(1)*P(2)*...*P(z-1) */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A.  If m <= 1, an immediate */
/*          return is effected. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A.  If n <= 1, an */
/*          immediate return is effected. */

/*  C       (input) DOUBLE PRECISION array, dimension */
/*                  (M-1) if SIDE = 'L' */
/*                  (N-1) if SIDE = 'R' */
/*          The cosines c(k) of the plane rotations. */

/*  S       (input) DOUBLE PRECISION array, dimension */
/*                  (M-1) if SIDE = 'L' */
/*                  (N-1) if SIDE = 'R' */
/*          The sines s(k) of the plane rotations.  The 2-by-2 plane */
/*          rotation part of the matrix P(k), R(k), has the form */
/*          R(k) = (  c(k)  s(k) ) */
/*                 ( -s(k)  c(k) ). */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          The M-by-N matrix A.  On exit, A is overwritten by P*A if */
/*          SIDE = 'R' or by A*P**T if SIDE = 'L'. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,M). */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input parameters */

    /* Parameter adjustments */
    --c__;
    --s;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    info = 0;
    if (! (lsame_(side, "L") || lsame_(side, "R"))) {
	info = 1;
    } else if (! (lsame_(pivot, "V") || lsame_(pivot,
	    "T") || lsame_(pivot, "B"))) {
	info = 2;
    } else if (! (lsame_(direct, "F") || lsame_(direct,
	    "B"))) {
	info = 3;
    } else if (*m < 0) {
	info = 4;
    } else if (*n < 0) {
	info = 5;
    } else if (*lda < max(1,*m)) {
	info = 9;
    }
    if (info != 0) {
	xerbla_("DLASR ", &info);
	return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0) {
	return 0;
    }
    if (lsame_(side, "L")) {

/*        Form  P * A */

	if (lsame_(pivot, "V")) {
	    if (lsame_(direct, "F")) {
		i__1 = *m - 1;
		for (j = 1; j <= i__1; ++j) {
		    ctemp = c__[j];
		    stemp = s[j];
		    if (ctemp != 1. || stemp != 0.) {
			i__2 = *n;
			for (i__ = 1; i__ <= i__2; ++i__) {
			    temp = a[j + 1 + i__ * a_dim1];
			    a[j + 1 + i__ * a_dim1] = ctemp * temp - stemp *
				    a[j + i__ * a_dim1];
			    a[j + i__ * a_dim1] = stemp * temp + ctemp * a[j
				    + i__ * a_dim1];
/* L10: */
			}
		    }
/* L20: */
		}
	    } else if (lsame_(direct, "B")) {
		for (j = *m - 1; j >= 1; --j) {
		    ctemp = c__[j];
		    stemp = s[j];
		    if (ctemp != 1. || stemp != 0.) {
			i__1 = *n;
			for (i__ = 1; i__ <= i__1; ++i__) {
			    temp = a[j + 1 + i__ * a_dim1];
			    a[j + 1 + i__ * a_dim1] = ctemp * temp - stemp *
				    a[j + i__ * a_dim1];
			    a[j + i__ * a_dim1] = stemp * temp + ctemp * a[j
				    + i__ * a_dim1];
/* L30: */
			}
		    }
/* L40: */
		}
	    }
	} else if (lsame_(pivot, "T")) {
	    if (lsame_(direct, "F")) {
		i__1 = *m;
		for (j = 2; j <= i__1; ++j) {
		    ctemp = c__[j - 1];
		    stemp = s[j - 1];
		    if (ctemp != 1. || stemp != 0.) {
			i__2 = *n;
			for (i__ = 1; i__ <= i__2; ++i__) {
			    temp = a[j + i__ * a_dim1];
			    a[j + i__ * a_dim1] = ctemp * temp - stemp * a[
				    i__ * a_dim1 + 1];
			    a[i__ * a_dim1 + 1] = stemp * temp + ctemp * a[
				    i__ * a_dim1 + 1];
/* L50: */
			}
		    }
/* L60: */
		}
	    } else if (lsame_(direct, "B")) {
		for (j = *m; j >= 2; --j) {
		    ctemp = c__[j - 1];
		    stemp = s[j - 1];
		    if (ctemp != 1. || stemp != 0.) {
			i__1 = *n;
			for (i__ = 1; i__ <= i__1; ++i__) {
			    temp = a[j + i__ * a_dim1];
			    a[j + i__ * a_dim1] = ctemp * temp - stemp * a[
				    i__ * a_dim1 + 1];
			    a[i__ * a_dim1 + 1] = stemp * temp + ctemp * a[
				    i__ * a_dim1 + 1];
/* L70: */
			}
		    }
/* L80: */
		}
	    }
	} else if (lsame_(pivot, "B")) {
	    if (lsame_(direct, "F")) {
		i__1 = *m - 1;
		for (j = 1; j <= i__1; ++j) {
		    ctemp = c__[j];
		    stemp = s[j];
		    if (ctemp != 1. || stemp != 0.) {
			i__2 = *n;
			for (i__ = 1; i__ <= i__2; ++i__) {
			    temp = a[j + i__ * a_dim1];
			    a[j + i__ * a_dim1] = stemp * a[*m + i__ * a_dim1]
				     + ctemp * temp;
			    a[*m + i__ * a_dim1] = ctemp * a[*m + i__ *
				    a_dim1] - stemp * temp;
/* L90: */
			}
		    }
/* L100: */
		}
	    } else if (lsame_(direct, "B")) {
		for (j = *m - 1; j >= 1; --j) {
		    ctemp = c__[j];
		    stemp = s[j];
		    if (ctemp != 1. || stemp != 0.) {
			i__1 = *n;
			for (i__ = 1; i__ <= i__1; ++i__) {
			    temp = a[j + i__ * a_dim1];
			    a[j + i__ * a_dim1] = stemp * a[*m + i__ * a_dim1]
				     + ctemp * temp;
			    a[*m + i__ * a_dim1] = ctemp * a[*m + i__ *
				    a_dim1] - stemp * temp;
/* L110: */
			}
		    }
/* L120: */
		}
	    }
	}
    } else if (lsame_(side, "R")) {

/*        Form A * P' */

	if (lsame_(pivot, "V")) {
	    if (lsame_(direct, "F")) {
		i__1 = *n - 1;
		for (j = 1; j <= i__1; ++j) {
		    ctemp = c__[j];
		    stemp = s[j];
		    if (ctemp != 1. || stemp != 0.) {
			i__2 = *m;
			for (i__ = 1; i__ <= i__2; ++i__) {
			    temp = a[i__ + (j + 1) * a_dim1];
			    a[i__ + (j + 1) * a_dim1] = ctemp * temp - stemp *
				     a[i__ + j * a_dim1];
			    a[i__ + j * a_dim1] = stemp * temp + ctemp * a[
				    i__ + j * a_dim1];
/* L130: */
			}
		    }
/* L140: */
		}
	    } else if (lsame_(direct, "B")) {
		for (j = *n - 1; j >= 1; --j) {
		    ctemp = c__[j];
		    stemp = s[j];
		    if (ctemp != 1. || stemp != 0.) {
			i__1 = *m;
			for (i__ = 1; i__ <= i__1; ++i__) {
			    temp = a[i__ + (j + 1) * a_dim1];
			    a[i__ + (j + 1) * a_dim1] = ctemp * temp - stemp *
				     a[i__ + j * a_dim1];
			    a[i__ + j * a_dim1] = stemp * temp + ctemp * a[
				    i__ + j * a_dim1];
/* L150: */
			}
		    }
/* L160: */
		}
	    }
	} else if (lsame_(pivot, "T")) {
	    if (lsame_(direct, "F")) {
		i__1 = *n;
		for (j = 2; j <= i__1; ++j) {
		    ctemp = c__[j - 1];
		    stemp = s[j - 1];
		    if (ctemp != 1. || stemp != 0.) {
			i__2 = *m;
			for (i__ = 1; i__ <= i__2; ++i__) {
			    temp = a[i__ + j * a_dim1];
			    a[i__ + j * a_dim1] = ctemp * temp - stemp * a[
				    i__ + a_dim1];
			    a[i__ + a_dim1] = stemp * temp + ctemp * a[i__ +
				    a_dim1];
/* L170: */
			}
		    }
/* L180: */
		}
	    } else if (lsame_(direct, "B")) {
		for (j = *n; j >= 2; --j) {
		    ctemp = c__[j - 1];
		    stemp = s[j - 1];
		    if (ctemp != 1. || stemp != 0.) {
			i__1 = *m;
			for (i__ = 1; i__ <= i__1; ++i__) {
			    temp = a[i__ + j * a_dim1];
			    a[i__ + j * a_dim1] = ctemp * temp - stemp * a[
				    i__ + a_dim1];
			    a[i__ + a_dim1] = stemp * temp + ctemp * a[i__ +
				    a_dim1];
/* L190: */
			}
		    }
/* L200: */
		}
	    }
	} else if (lsame_(pivot, "B")) {
	    if (lsame_(direct, "F")) {
		i__1 = *n - 1;
		for (j = 1; j <= i__1; ++j) {
		    ctemp = c__[j];
		    stemp = s[j];
		    if (ctemp != 1. || stemp != 0.) {
			i__2 = *m;
			for (i__ = 1; i__ <= i__2; ++i__) {
			    temp = a[i__ + j * a_dim1];
			    a[i__ + j * a_dim1] = stemp * a[i__ + *n * a_dim1]
				     + ctemp * temp;
			    a[i__ + *n * a_dim1] = ctemp * a[i__ + *n *
				    a_dim1] - stemp * temp;
/* L210: */
			}
		    }
/* L220: */
		}
	    } else if (lsame_(direct, "B")) {
		for (j = *n - 1; j >= 1; --j) {
		    ctemp = c__[j];
		    stemp = s[j];
		    if (ctemp != 1. || stemp != 0.) {
			i__1 = *m;
			for (i__ = 1; i__ <= i__1; ++i__) {
			    temp = a[i__ + j * a_dim1];
			    a[i__ + j * a_dim1] = stemp * a[i__ + *n * a_dim1]
				     + ctemp * temp;
			    a[i__ + *n * a_dim1] = ctemp * a[i__ + *n *
				    a_dim1] - stemp * temp;
/* L230: */
			}
		    }
/* L240: */
		}
	    }
	}
    }

    return 0;

/*     End of DLASR */

} /* dlasr_ */

/* Subroutine */ int dlasrt_(char *id, integer *n, doublereal *d__, integer *
	info)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Local variables */
    integer i__, j;
    doublereal d1, d2, d3;
    integer dir;
    doublereal tmp;
    integer endd;
    extern logical lsame_(char *, char *);
    integer stack[64]	/* was [2][32] */;
    doublereal dmnmx;
    integer start;
    extern /* Subroutine */ int xerbla_(char *, integer *);
    integer stkpnt;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  Sort the numbers in D in increasing order (if ID = 'I') or */
/*  in decreasing order (if ID = 'D' ). */

/*  Use Quick Sort, reverting to Insertion sort on arrays of */
/*  size <= 20. Dimension of STACK limits N to about 2**32. */

/*  Arguments */
/*  ========= */

/*  ID      (input) CHARACTER*1 */
/*          = 'I': sort D in increasing order; */
/*          = 'D': sort D in decreasing order. */

/*  N       (input) INTEGER */
/*          The length of the array D. */

/*  D       (input/output) DOUBLE PRECISION array, dimension (N) */
/*          On entry, the array to be sorted. */
/*          On exit, D has been sorted into increasing order */
/*          (D(1) <= ... <= D(N) ) or into decreasing order */
/*          (D(1) >= ... >= D(N) ), depending on ID. */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Local Arrays .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input paramters. */

    /* Parameter adjustments */
    --d__;

    /* Function Body */
    *info = 0;
    dir = -1;
    if (lsame_(id, "D")) {
	dir = 0;
    } else if (lsame_(id, "I")) {
	dir = 1;
    }
    if (dir == -1) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DLASRT", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*n <= 1) {
	return 0;
    }

    stkpnt = 1;
    stack[0] = 1;
    stack[1] = *n;
L10:
    start = stack[(stkpnt << 1) - 2];
    endd = stack[(stkpnt << 1) - 1];
    --stkpnt;
    if (endd - start <= 20 && endd - start > 0) {

/*        Do Insertion sort on D( START:ENDD ) */

	if (dir == 0) {

/*           Sort into decreasing order */

	    i__1 = endd;
	    for (i__ = start + 1; i__ <= i__1; ++i__) {
		i__2 = start + 1;
		for (j = i__; j >= i__2; --j) {
		    if (d__[j] > d__[j - 1]) {
			dmnmx = d__[j];
			d__[j] = d__[j - 1];
			d__[j - 1] = dmnmx;
		    } else {
			goto L30;
		    }
/* L20: */
		}
L30:
		;
	    }

	} else {

/*           Sort into increasing order */

	    i__1 = endd;
	    for (i__ = start + 1; i__ <= i__1; ++i__) {
		i__2 = start + 1;
		for (j = i__; j >= i__2; --j) {
		    if (d__[j] < d__[j - 1]) {
			dmnmx = d__[j];
			d__[j] = d__[j - 1];
			d__[j - 1] = dmnmx;
		    } else {
			goto L50;
		    }
/* L40: */
		}
L50:
		;
	    }

	}

    } else if (endd - start > 20) {

/*        Partition D( START:ENDD ) and stack parts, largest one first */

/*        Choose partition entry as median of 3 */

	d1 = d__[start];
	d2 = d__[endd];
	i__ = (start + endd) / 2;
	d3 = d__[i__];
	if (d1 < d2) {
	    if (d3 < d1) {
		dmnmx = d1;
	    } else if (d3 < d2) {
		dmnmx = d3;
	    } else {
		dmnmx = d2;
	    }
	} else {
	    if (d3 < d2) {
		dmnmx = d2;
	    } else if (d3 < d1) {
		dmnmx = d3;
	    } else {
		dmnmx = d1;
	    }
	}

	if (dir == 0) {

/*           Sort into decreasing order */

	    i__ = start - 1;
	    j = endd + 1;
L60:
L70:
	    --j;
	    if (d__[j] < dmnmx) {
		goto L70;
	    }
L80:
	    ++i__;
	    if (d__[i__] > dmnmx) {
		goto L80;
	    }
	    if (i__ < j) {
		tmp = d__[i__];
		d__[i__] = d__[j];
		d__[j] = tmp;
		goto L60;
	    }
	    if (j - start > endd - j - 1) {
		++stkpnt;
		stack[(stkpnt << 1) - 2] = start;
		stack[(stkpnt << 1) - 1] = j;
		++stkpnt;
		stack[(stkpnt << 1) - 2] = j + 1;
		stack[(stkpnt << 1) - 1] = endd;
	    } else {
		++stkpnt;
		stack[(stkpnt << 1) - 2] = j + 1;
		stack[(stkpnt << 1) - 1] = endd;
		++stkpnt;
		stack[(stkpnt << 1) - 2] = start;
		stack[(stkpnt << 1) - 1] = j;
	    }
	} else {

/*           Sort into increasing order */

	    i__ = start - 1;
	    j = endd + 1;
L90:
L100:
	    --j;
	    if (d__[j] > dmnmx) {
		goto L100;
	    }
L110:
	    ++i__;
	    if (d__[i__] < dmnmx) {
		goto L110;
	    }
	    if (i__ < j) {
		tmp = d__[i__];
		d__[i__] = d__[j];
		d__[j] = tmp;
		goto L90;
	    }
	    if (j - start > endd - j - 1) {
		++stkpnt;
		stack[(stkpnt << 1) - 2] = start;
		stack[(stkpnt << 1) - 1] = j;
		++stkpnt;
		stack[(stkpnt << 1) - 2] = j + 1;
		stack[(stkpnt << 1) - 1] = endd;
	    } else {
		++stkpnt;
		stack[(stkpnt << 1) - 2] = j + 1;
		stack[(stkpnt << 1) - 1] = endd;
		++stkpnt;
		stack[(stkpnt << 1) - 2] = start;
		stack[(stkpnt << 1) - 1] = j;
	    }
	}
    }
    if (stkpnt > 0) {
	goto L10;
    }
    return 0;

/*     End of DLASRT */

} /* dlasrt_ */

/* Subroutine */ int dlassq_(integer *n, doublereal *x, integer *incx,
	doublereal *scale, doublereal *sumsq)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;

    /* Local variables */
    integer ix;
    doublereal absxi;
    extern logical disnan_(doublereal *);


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLASSQ  returns the values  scl  and  smsq  such that */

/*     ( scl**2 )*smsq = x( 1 )**2 +...+ x( n )**2 + ( scale**2 )*sumsq, */

/*  where  x( i ) = X( 1 + ( i - 1 )*INCX ). The value of  sumsq  is */
/*  assumed to be non-negative and  scl  returns the value */

/*     scl = max( scale, abs( x( i ) ) ). */

/*  scale and sumsq must be supplied in SCALE and SUMSQ and */
/*  scl and smsq are overwritten on SCALE and SUMSQ respectively. */

/*  The routine makes only one pass through the vector x. */

/*  Arguments */
/*  ========= */

/*  N       (input) INTEGER */
/*          The number of elements to be used from the vector X. */

/*  X       (input) DOUBLE PRECISION array, dimension (N) */
/*          The vector for which a scaled sum of squares is computed. */
/*             x( i )  = X( 1 + ( i - 1 )*INCX ), 1 <= i <= n. */

/*  INCX    (input) INTEGER */
/*          The increment between successive values of the vector X. */
/*          INCX > 0. */

/*  SCALE   (input/output) DOUBLE PRECISION */
/*          On entry, the value  scale  in the equation above. */
/*          On exit, SCALE is overwritten with  scl , the scaling factor */
/*          for the sum of squares. */

/*  SUMSQ   (input/output) DOUBLE PRECISION */
/*          On entry, the value  sumsq  in the equation above. */
/*          On exit, SUMSQ is overwritten with  smsq , the basic sum of */
/*          squares from which  scl  has been factored out. */

/* ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    --x;

    /* Function Body */
    if (*n > 0) {
	i__1 = (*n - 1) * *incx + 1;
	i__2 = *incx;
	for (ix = 1; i__2 < 0 ? ix >= i__1 : ix <= i__1; ix += i__2) {
	    absxi = (d__1 = x[ix], abs(d__1));
	    if (absxi > 0. || disnan_(&absxi)) {
		if (*scale < absxi) {
/* Computing 2nd power */
		    d__1 = *scale / absxi;
		    *sumsq = *sumsq * (d__1 * d__1) + 1;
		    *scale = absxi;
		} else {
/* Computing 2nd power */
		    d__1 = absxi / *scale;
		    *sumsq += d__1 * d__1;
		}
	    }
/* L10: */
	}
    }
    return 0;

/*     End of DLASSQ */

} /* dlassq_ */

/* Subroutine */ int dlasv2_(doublereal *f, doublereal *g, doublereal *h__,
	doublereal *ssmin, doublereal *ssmax, doublereal *snr, doublereal *
	csr, doublereal *snl, doublereal *csl)
{
    /* Table of constant values */

    doublereal c_b3 = 2.;
    doublereal c_b4 = 1.;

    /* System generated locals */
    doublereal d__1;

    /* Local variables */
    doublereal a, d__, l, m, r__, s, t, fa, ga, ha, ft, gt, ht, mm, tt, clt,
	    crt, slt, srt;
    integer pmax;
    doublereal temp;
    logical swap;
    doublereal tsign;
    extern doublereal dlamch_(char *);
    logical gasmal;


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLASV2 computes the singular value decomposition of a 2-by-2 */
/*  triangular matrix */
/*     [  F   G  ] */
/*     [  0   H  ]. */
/*  On return, abs(SSMAX) is the larger singular value, abs(SSMIN) is the */
/*  smaller singular value, and (CSL,SNL) and (CSR,SNR) are the left and */
/*  right singular vectors for abs(SSMAX), giving the decomposition */

/*     [ CSL  SNL ] [  F   G  ] [ CSR -SNR ]  =  [ SSMAX   0   ] */
/*     [-SNL  CSL ] [  0   H  ] [ SNR  CSR ]     [  0    SSMIN ]. */

/*  Arguments */
/*  ========= */

/*  F       (input) DOUBLE PRECISION */
/*          The (1,1) element of the 2-by-2 matrix. */

/*  G       (input) DOUBLE PRECISION */
/*          The (1,2) element of the 2-by-2 matrix. */

/*  H       (input) DOUBLE PRECISION */
/*          The (2,2) element of the 2-by-2 matrix. */

/*  SSMIN   (output) DOUBLE PRECISION */
/*          abs(SSMIN) is the smaller singular value. */

/*  SSMAX   (output) DOUBLE PRECISION */
/*          abs(SSMAX) is the larger singular value. */

/*  SNL     (output) DOUBLE PRECISION */
/*  CSL     (output) DOUBLE PRECISION */
/*          The vector (CSL, SNL) is a unit left singular vector for the */
/*          singular value abs(SSMAX). */

/*  SNR     (output) DOUBLE PRECISION */
/*  CSR     (output) DOUBLE PRECISION */
/*          The vector (CSR, SNR) is a unit right singular vector for the */
/*          singular value abs(SSMAX). */

/*  Further Details */
/*  =============== */

/*  Any input parameter may be aliased with any output parameter. */

/*  Barring over/underflow and assuming a guard digit in subtraction, all */
/*  output quantities are correct to within a few units in the last */
/*  place (ulps). */

/*  In IEEE arithmetic, the code works correctly if one matrix element is */
/*  infinite. */

/*  Overflow will not occur unless the largest singular value itself */
/*  overflows or is within a few ulps of overflow. (On machines with */
/*  partial overflow, like the Cray, overflow may occur if the largest */
/*  singular value is within a factor of 2 of overflow.) */

/*  Underflow is harmless if underflow is gradual. Otherwise, results */
/*  may correspond to a matrix modified by perturbations of size near */
/*  the underflow threshold. */

/* ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    ft = *f;
    fa = abs(ft);
    ht = *h__;
    ha = abs(*h__);

/*     PMAX points to the maximum absolute element of matrix */
/*       PMAX = 1 if F largest in absolute values */
/*       PMAX = 2 if G largest in absolute values */
/*       PMAX = 3 if H largest in absolute values */

    pmax = 1;
    swap = ha > fa;
    if (swap) {
	pmax = 3;
	temp = ft;
	ft = ht;
	ht = temp;
	temp = fa;
	fa = ha;
	ha = temp;

/*        Now FA .ge. HA */

    }
    gt = *g;
    ga = abs(gt);
    if (ga == 0.) {

/*        Diagonal matrix */

	*ssmin = ha;
	*ssmax = fa;
	clt = 1.;
	crt = 1.;
	slt = 0.;
	srt = 0.;
    } else {
	gasmal = TRUE_;
	if (ga > fa) {
	    pmax = 2;
	    if (fa / ga < dlamch_("EPS")) {

/*              Case of very large GA */

		gasmal = FALSE_;
		*ssmax = ga;
		if (ha > 1.) {
		    *ssmin = fa / (ga / ha);
		} else {
		    *ssmin = fa / ga * ha;
		}
		clt = 1.;
		slt = ht / gt;
		srt = 1.;
		crt = ft / gt;
	    }
	}
	if (gasmal) {

/*           Normal case */

	    d__ = fa - ha;
	    if (d__ == fa) {

/*              Copes with infinite F or H */

		l = 1.;
	    } else {
		l = d__ / fa;
	    }

/*           Note that 0 .le. L .le. 1 */

	    m = gt / ft;

/*           Note that abs(M) .le. 1/macheps */

	    t = 2. - l;

/*           Note that T .ge. 1 */

	    mm = m * m;
	    tt = t * t;
	    s = sqrt(tt + mm);

/*           Note that 1 .le. S .le. 1 + 1/macheps */

	    if (l == 0.) {
		r__ = abs(m);
	    } else {
		r__ = sqrt(l * l + mm);
	    }

/*           Note that 0 .le. R .le. 1 + 1/macheps */

	    a = (s + r__) * .5;

/*           Note that 1 .le. A .le. 1 + abs(M) */

	    *ssmin = ha / a;
	    *ssmax = fa * a;
	    if (mm == 0.) {

/*              Note that M is very tiny */

		if (l == 0.) {
		    t = d_sign(&c_b3, &ft) * d_sign(&c_b4, &gt);
		} else {
		    t = gt / d_sign(&d__, &ft) + m / t;
		}
	    } else {
		t = (m / (s + t) + m / (r__ + l)) * (a + 1.);
	    }
	    l = sqrt(t * t + 4.);
	    crt = 2. / l;
	    srt = t / l;
	    clt = (crt + srt * m) / a;
	    slt = ht / ft * srt / a;
	}
    }
    if (swap) {
	*csl = srt;
	*snl = crt;
	*csr = slt;
	*snr = clt;
    } else {
	*csl = clt;
	*snl = slt;
	*csr = crt;
	*snr = srt;
    }

/*     Correct signs of SSMAX and SSMIN */

    if (pmax == 1) {
	tsign = d_sign(&c_b4, csr) * d_sign(&c_b4, csl) * d_sign(&c_b4, f);
    }
    if (pmax == 2) {
	tsign = d_sign(&c_b4, snr) * d_sign(&c_b4, csl) * d_sign(&c_b4, g);
    }
    if (pmax == 3) {
	tsign = d_sign(&c_b4, snr) * d_sign(&c_b4, snl) * d_sign(&c_b4, h__);
    }
    *ssmax = d_sign(ssmax, &tsign);
    d__1 = tsign * d_sign(&c_b4, f) * d_sign(&c_b4, h__);
    *ssmin = d_sign(ssmin, &d__1);
    return 0;

/*     End of DLASV2 */

} /* dlasv2_ */

/* Subroutine */ int dlaswp_(integer *n, doublereal *a, integer *lda, integer
	*k1, integer *k2, integer *ipiv, integer *incx)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4;

    /* Local variables */
    integer i__, j, k, i1, i2, n32, ip, ix, ix0, inc;
    doublereal temp;


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLASWP performs a series of row interchanges on the matrix A. */
/*  One row interchange is initiated for each of rows K1 through K2 of A. */

/*  Arguments */
/*  ========= */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the matrix of column dimension N to which the row */
/*          interchanges will be applied. */
/*          On exit, the permuted matrix. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A. */

/*  K1      (input) INTEGER */
/*          The first element of IPIV for which a row interchange will */
/*          be done. */

/*  K2      (input) INTEGER */
/*          The last element of IPIV for which a row interchange will */
/*          be done. */

/*  IPIV    (input) INTEGER array, dimension (K2*abs(INCX)) */
/*          The vector of pivot indices.  Only the elements in positions */
/*          K1 through K2 of IPIV are accessed. */
/*          IPIV(K) = L implies rows K and L are to be interchanged. */

/*  INCX    (input) INTEGER */
/*          The increment between successive values of IPIV.  If IPIV */
/*          is negative, the pivots are applied in reverse order. */

/*  Further Details */
/*  =============== */

/*  Modified by */
/*   R. C. Whaley, Computer Science Dept., Univ. of Tenn., Knoxville, USA */

/* ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Interchange row I with row IPIV(I) for each of rows K1 through K2. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --ipiv;

    /* Function Body */
    if (*incx > 0) {
	ix0 = *k1;
	i1 = *k1;
	i2 = *k2;
	inc = 1;
    } else if (*incx < 0) {
	ix0 = (1 - *k2) * *incx + 1;
	i1 = *k2;
	i2 = *k1;
	inc = -1;
    } else {
	return 0;
    }

    n32 = *n / 32 << 5;
    if (n32 != 0) {
	i__1 = n32;
	for (j = 1; j <= i__1; j += 32) {
	    ix = ix0;
	    i__2 = i2;
	    i__3 = inc;
	    for (i__ = i1; i__3 < 0 ? i__ >= i__2 : i__ <= i__2; i__ += i__3)
		    {
		ip = ipiv[ix];
		if (ip != i__) {
		    i__4 = j + 31;
		    for (k = j; k <= i__4; ++k) {
			temp = a[i__ + k * a_dim1];
			a[i__ + k * a_dim1] = a[ip + k * a_dim1];
			a[ip + k * a_dim1] = temp;
/* L10: */
		    }
		}
		ix += *incx;
/* L20: */
	    }
/* L30: */
	}
    }
    if (n32 != *n) {
	++n32;
	ix = ix0;
	i__1 = i2;
	i__3 = inc;
	for (i__ = i1; i__3 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__3) {
	    ip = ipiv[ix];
	    if (ip != i__) {
		i__2 = *n;
		for (k = n32; k <= i__2; ++k) {
		    temp = a[i__ + k * a_dim1];
		    a[i__ + k * a_dim1] = a[ip + k * a_dim1];
		    a[ip + k * a_dim1] = temp;
/* L40: */
		}
	    }
	    ix += *incx;
/* L50: */
	}
    }

    return 0;

/*     End of DLASWP */

} /* dlaswp_ */

/* Subroutine */ int dlatrz_(integer *m, integer *n, integer *l, doublereal *
	a, integer *lda, doublereal *tau, doublereal *work)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;

    /* Local variables */
    integer i__;
    extern /* Subroutine */ int dlarz_(char *, integer *, integer *, integer *
, doublereal *, integer *, doublereal *, doublereal *, integer *,
	    doublereal *), dlarfp_(integer *, doublereal *,
	    doublereal *, integer *, doublereal *);


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLATRZ factors the M-by-(M+L) real upper trapezoidal matrix */
/*  [ A1 A2 ] = [ A(1:M,1:M) A(1:M,N-L+1:N) ] as ( R  0 ) * Z, by means */
/*  of orthogonal transformations.  Z is an (M+L)-by-(M+L) orthogonal */
/*  matrix and, R and A1 are M-by-M upper triangular matrices. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A.  M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A.  N >= 0. */

/*  L       (input) INTEGER */
/*          The number of columns of the matrix A containing the */
/*          meaningful part of the Householder vectors. N-M >= L >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the leading M-by-N upper trapezoidal part of the */
/*          array A must contain the matrix to be factorized. */
/*          On exit, the leading M-by-M upper triangular part of A */
/*          contains the upper triangular matrix R, and elements N-L+1 to */
/*          N of the first M rows of A, with the array TAU, represent the */
/*          orthogonal matrix Z as a product of M elementary reflectors. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,M). */

/*  TAU     (output) DOUBLE PRECISION array, dimension (M) */
/*          The scalar factors of the elementary reflectors. */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (M) */

/*  Further Details */
/*  =============== */

/*  Based on contributions by */
/*    A. Petitet, Computer Science Dept., Univ. of Tenn., Knoxville, USA */

/*  The factorization is obtained by Householder's method.  The kth */
/*  transformation matrix, Z( k ), which is used to introduce zeros into */
/*  the ( m - k + 1 )th row of A, is given in the form */

/*     Z( k ) = ( I     0   ), */
/*              ( 0  T( k ) ) */

/*  where */

/*     T( k ) = I - tau*u( k )*u( k )',   u( k ) = (   1    ), */
/*                                                 (   0    ) */
/*                                                 ( z( k ) ) */

/*  tau is a scalar and z( k ) is an l element vector. tau and z( k ) */
/*  are chosen to annihilate the elements of the kth row of A2. */

/*  The scalar tau is returned in the kth element of TAU and the vector */
/*  u( k ) in the kth row of A2, such that the elements of z( k ) are */
/*  in  a( k, l + 1 ), ..., a( k, n ). The elements of R are returned in */
/*  the upper triangular part of A1. */

/*  Z is given by */

/*     Z =  Z( 1 ) * Z( 2 ) * ... * Z( m ). */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

/*     Quick return if possible */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    --work;

    /* Function Body */
    if (*m == 0) {
	return 0;
    } else if (*m == *n) {
	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    tau[i__] = 0.;
/* L10: */
	}
	return 0;
    }

    for (i__ = *m; i__ >= 1; --i__) {

/*        Generate elementary reflector H(i) to annihilate */
/*        [ A(i,i) A(i,n-l+1:n) ] */

	i__1 = *l + 1;
	dlarfp_(&i__1, &a[i__ + i__ * a_dim1], &a[i__ + (*n - *l + 1) *
		a_dim1], lda, &tau[i__]);

/*        Apply H(i) to A(1:i-1,i:n) from the right */

	i__1 = i__ - 1;
	i__2 = *n - i__ + 1;
	dlarz_("Right", &i__1, &i__2, l, &a[i__ + (*n - *l + 1) * a_dim1],
		lda, &tau[i__], &a[i__ * a_dim1 + 1], lda, &work[1]);

/* L20: */
    }

    return 0;

/*     End of DLATRZ */

} /* dlatrz_ */

/* Subroutine */ int dorg2r_(integer *m, integer *n, integer *k, doublereal *
	a, integer *lda, doublereal *tau, doublereal *work, integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;
    doublereal d__1;

    /* Local variables */
    integer i__, j, l;
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *,
	    integer *), dlarf_(char *, integer *, integer *, doublereal *,
	    integer *, doublereal *, doublereal *, integer *, doublereal *), xerbla_(char *, integer *);


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DORG2R generates an m by n real matrix Q with orthonormal columns, */
/*  which is defined as the first n columns of a product of k elementary */
/*  reflectors of order m */

/*        Q  =  H(1) H(2) . . . H(k) */

/*  as returned by DGEQRF. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix Q. M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix Q. M >= N >= 0. */

/*  K       (input) INTEGER */
/*          The number of elementary reflectors whose product defines the */
/*          matrix Q. N >= K >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the i-th column must contain the vector which */
/*          defines the elementary reflector H(i), for i = 1,2,...,k, as */
/*          returned by DGEQRF in the first k columns of its array */
/*          argument A. */
/*          On exit, the m-by-n matrix Q. */

/*  LDA     (input) INTEGER */
/*          The first dimension of the array A. LDA >= max(1,M). */

/*  TAU     (input) DOUBLE PRECISION array, dimension (K) */
/*          TAU(i) must contain the scalar factor of the elementary */
/*          reflector H(i), as returned by DGEQRF. */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (N) */

/*  INFO    (output) INTEGER */
/*          = 0: successful exit */
/*          < 0: if INFO = -i, the i-th argument has an illegal value */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    --work;

    /* Function Body */
    *info = 0;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0 || *n > *m) {
	*info = -2;
    } else if (*k < 0 || *k > *n) {
	*info = -3;
    } else if (*lda < max(1,*m)) {
	*info = -5;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DORG2R", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*n <= 0) {
	return 0;
    }

/*     Initialise columns k+1:n to columns of the unit matrix */

    i__1 = *n;
    for (j = *k + 1; j <= i__1; ++j) {
	i__2 = *m;
	for (l = 1; l <= i__2; ++l) {
	    a[l + j * a_dim1] = 0.;
/* L10: */
	}
	a[j + j * a_dim1] = 1.;
/* L20: */
    }

    for (i__ = *k; i__ >= 1; --i__) {

/*        Apply H(i) to A(i:m,i:n) from the left */

	if (i__ < *n) {
	    a[i__ + i__ * a_dim1] = 1.;
	    i__1 = *m - i__ + 1;
	    i__2 = *n - i__;
	    dlarf_("Left", &i__1, &i__2, &a[i__ + i__ * a_dim1], &c__1, &tau[
		    i__], &a[i__ + (i__ + 1) * a_dim1], lda, &work[1]);
	}
	if (i__ < *m) {
	    i__1 = *m - i__;
	    d__1 = -tau[i__];
	    dscal_(&i__1, &d__1, &a[i__ + 1 + i__ * a_dim1], &c__1);
	}
	a[i__ + i__ * a_dim1] = 1. - tau[i__];

/*        Set A(1:i-1,i) to zero */

	i__1 = i__ - 1;
	for (l = 1; l <= i__1; ++l) {
	    a[l + i__ * a_dim1] = 0.;
/* L30: */
	}
/* L40: */
    }
    return 0;

/*     End of DORG2R */

} /* dorg2r_ */

/* Subroutine */ int dorgbr_(char *vect, integer *m, integer *n, integer *k,
	doublereal *a, integer *lda, doublereal *tau, doublereal *work,
	integer *lwork, integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;
    integer c_n1 = -1;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;

    /* Local variables */
    integer i__, j, nb, mn;
    extern logical lsame_(char *, char *);
    integer iinfo;
    logical wantq;
    extern /* Subroutine */ int xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *,
	    integer *, integer *);
    extern /* Subroutine */ int dorglq_(integer *, integer *, integer *,
	    doublereal *, integer *, doublereal *, doublereal *, integer *,
	    integer *), dorgqr_(integer *, integer *, integer *, doublereal *,
	     integer *, doublereal *, doublereal *, integer *, integer *);
    integer lwkopt;
    logical lquery;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DORGBR generates one of the real orthogonal matrices Q or P**T */
/*  determined by DGEBRD when reducing a real matrix A to bidiagonal */
/*  form: A = Q * B * P**T.  Q and P**T are defined as products of */
/*  elementary reflectors H(i) or G(i) respectively. */

/*  If VECT = 'Q', A is assumed to have been an M-by-K matrix, and Q */
/*  is of order M: */
/*  if m >= k, Q = H(1) H(2) . . . H(k) and DORGBR returns the first n */
/*  columns of Q, where m >= n >= k; */
/*  if m < k, Q = H(1) H(2) . . . H(m-1) and DORGBR returns Q as an */
/*  M-by-M matrix. */

/*  If VECT = 'P', A is assumed to have been a K-by-N matrix, and P**T */
/*  is of order N: */
/*  if k < n, P**T = G(k) . . . G(2) G(1) and DORGBR returns the first m */
/*  rows of P**T, where n >= m >= k; */
/*  if k >= n, P**T = G(n-1) . . . G(2) G(1) and DORGBR returns P**T as */
/*  an N-by-N matrix. */

/*  Arguments */
/*  ========= */

/*  VECT    (input) CHARACTER*1 */
/*          Specifies whether the matrix Q or the matrix P**T is */
/*          required, as defined in the transformation applied by DGEBRD: */
/*          = 'Q':  generate Q; */
/*          = 'P':  generate P**T. */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix Q or P**T to be returned. */
/*          M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix Q or P**T to be returned. */
/*          N >= 0. */
/*          If VECT = 'Q', M >= N >= min(M,K); */
/*          if VECT = 'P', N >= M >= min(N,K). */

/*  K       (input) INTEGER */
/*          If VECT = 'Q', the number of columns in the original M-by-K */
/*          matrix reduced by DGEBRD. */
/*          If VECT = 'P', the number of rows in the original K-by-N */
/*          matrix reduced by DGEBRD. */
/*          K >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the vectors which define the elementary reflectors, */
/*          as returned by DGEBRD. */
/*          On exit, the M-by-N matrix Q or P**T. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A. LDA >= max(1,M). */

/*  TAU     (input) DOUBLE PRECISION array, dimension */
/*                                (min(M,K)) if VECT = 'Q' */
/*                                (min(N,K)) if VECT = 'P' */
/*          TAU(i) must contain the scalar factor of the elementary */
/*          reflector H(i) or G(i), which determines Q or P**T, as */
/*          returned by DGEBRD in its array argument TAUQ or TAUP. */

/*  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK)) */
/*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK. */

/*  LWORK   (input) INTEGER */
/*          The dimension of the array WORK. LWORK >= max(1,min(M,N)). */
/*          For optimum performance LWORK >= min(M,N)*NB, where NB */
/*          is the optimal blocksize. */

/*          If LWORK = -1, then a workspace query is assumed; the routine */
/*          only calculates the optimal size of the WORK array, returns */
/*          this value as the first entry of the WORK array, and no error */
/*          message related to LWORK is issued by XERBLA. */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    --work;

    /* Function Body */
    *info = 0;
    wantq = lsame_(vect, "Q");
    mn = min(*m,*n);
    lquery = *lwork == -1;
    if (! wantq && ! lsame_(vect, "P")) {
	*info = -1;
    } else if (*m < 0) {
	*info = -2;
    } else if (*n < 0 || (wantq && (*n > *m || *n < min(*m,*k))) || (! wantq && (
	    *m > *n || *m < min(*n,*k)))) {
	*info = -3;
    } else if (*k < 0) {
	*info = -4;
    } else if (*lda < max(1,*m)) {
	*info = -6;
    } else if (*lwork < max(1,mn) && ! lquery) {
	*info = -9;
    }

    if (*info == 0) {
	if (wantq) {
	    nb = ilaenv_(&c__1, "DORGQR", " ", m, n, k, &c_n1);
	} else {
	    nb = ilaenv_(&c__1, "DORGLQ", " ", m, n, k, &c_n1);
	}
	lwkopt = max(1,mn) * nb;
	work[1] = (doublereal) lwkopt;
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DORGBR", &i__1);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0) {
	work[1] = 1.;
	return 0;
    }

    if (wantq) {

/*        Form Q, determined by a call to DGEBRD to reduce an m-by-k */
/*        matrix */

	if (*m >= *k) {

/*           If m >= k, assume m >= n >= k */

	    dorgqr_(m, n, k, &a[a_offset], lda, &tau[1], &work[1], lwork, &
		    iinfo);

	} else {

/*           If m < k, assume m = n */

/*           Shift the vectors which define the elementary reflectors one */
/*           column to the right, and set the first row and column of Q */
/*           to those of the unit matrix */

	    for (j = *m; j >= 2; --j) {
		a[j * a_dim1 + 1] = 0.;
		i__1 = *m;
		for (i__ = j + 1; i__ <= i__1; ++i__) {
		    a[i__ + j * a_dim1] = a[i__ + (j - 1) * a_dim1];
/* L10: */
		}
/* L20: */
	    }
	    a[a_dim1 + 1] = 1.;
	    i__1 = *m;
	    for (i__ = 2; i__ <= i__1; ++i__) {
		a[i__ + a_dim1] = 0.;
/* L30: */
	    }
	    if (*m > 1) {

/*              Form Q(2:m,2:m) */

		i__1 = *m - 1;
		i__2 = *m - 1;
		i__3 = *m - 1;
		dorgqr_(&i__1, &i__2, &i__3, &a[(a_dim1 << 1) + 2], lda, &tau[
			1], &work[1], lwork, &iinfo);
	    }
	}
    } else {

/*        Form P', determined by a call to DGEBRD to reduce a k-by-n */
/*        matrix */

	if (*k < *n) {

/*           If k < n, assume k <= m <= n */

	    dorglq_(m, n, k, &a[a_offset], lda, &tau[1], &work[1], lwork, &
		    iinfo);

	} else {

/*           If k >= n, assume m = n */

/*           Shift the vectors which define the elementary reflectors one */
/*           row downward, and set the first row and column of P' to */
/*           those of the unit matrix */

	    a[a_dim1 + 1] = 1.;
	    i__1 = *n;
	    for (i__ = 2; i__ <= i__1; ++i__) {
		a[i__ + a_dim1] = 0.;
/* L40: */
	    }
	    i__1 = *n;
	    for (j = 2; j <= i__1; ++j) {
		for (i__ = j - 1; i__ >= 2; --i__) {
		    a[i__ + j * a_dim1] = a[i__ - 1 + j * a_dim1];
/* L50: */
		}
		a[j * a_dim1 + 1] = 0.;
/* L60: */
	    }
	    if (*n > 1) {

/*              Form P'(2:n,2:n) */

		i__1 = *n - 1;
		i__2 = *n - 1;
		i__3 = *n - 1;
		dorglq_(&i__1, &i__2, &i__3, &a[(a_dim1 << 1) + 2], lda, &tau[
			1], &work[1], lwork, &iinfo);
	    }
	}
    }
    work[1] = (doublereal) lwkopt;
    return 0;

/*     End of DORGBR */

} /* dorgbr_ */

/* Subroutine */ int dorgl2_(integer *m, integer *n, integer *k, doublereal *
	a, integer *lda, doublereal *tau, doublereal *work, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;
    doublereal d__1;

    /* Local variables */
    integer i__, j, l;
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *,
	    integer *), dlarf_(char *, integer *, integer *, doublereal *,
	    integer *, doublereal *, doublereal *, integer *, doublereal *), xerbla_(char *, integer *);


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DORGL2 generates an m by n real matrix Q with orthonormal rows, */
/*  which is defined as the first m rows of a product of k elementary */
/*  reflectors of order n */

/*        Q  =  H(k) . . . H(2) H(1) */

/*  as returned by DGELQF. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix Q. M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix Q. N >= M. */

/*  K       (input) INTEGER */
/*          The number of elementary reflectors whose product defines the */
/*          matrix Q. M >= K >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the i-th row must contain the vector which defines */
/*          the elementary reflector H(i), for i = 1,2,...,k, as returned */
/*          by DGELQF in the first k rows of its array argument A. */
/*          On exit, the m-by-n matrix Q. */

/*  LDA     (input) INTEGER */
/*          The first dimension of the array A. LDA >= max(1,M). */

/*  TAU     (input) DOUBLE PRECISION array, dimension (K) */
/*          TAU(i) must contain the scalar factor of the elementary */
/*          reflector H(i), as returned by DGELQF. */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension (M) */

/*  INFO    (output) INTEGER */
/*          = 0: successful exit */
/*          < 0: if INFO = -i, the i-th argument has an illegal value */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    --work;

    /* Function Body */
    *info = 0;
    if (*m < 0) {
	*info = -1;
    } else if (*n < *m) {
	*info = -2;
    } else if (*k < 0 || *k > *m) {
	*info = -3;
    } else if (*lda < max(1,*m)) {
	*info = -5;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DORGL2", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*m <= 0) {
	return 0;
    }

    if (*k < *m) {

/*        Initialise rows k+1:m to rows of the unit matrix */

	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (l = *k + 1; l <= i__2; ++l) {
		a[l + j * a_dim1] = 0.;
/* L10: */
	    }
	    if (j > *k && j <= *m) {
		a[j + j * a_dim1] = 1.;
	    }
/* L20: */
	}
    }

    for (i__ = *k; i__ >= 1; --i__) {

/*        Apply H(i) to A(i:m,i:n) from the right */

	if (i__ < *n) {
	    if (i__ < *m) {
		a[i__ + i__ * a_dim1] = 1.;
		i__1 = *m - i__;
		i__2 = *n - i__ + 1;
		dlarf_("Right", &i__1, &i__2, &a[i__ + i__ * a_dim1], lda, &
			tau[i__], &a[i__ + 1 + i__ * a_dim1], lda, &work[1]);
	    }
	    i__1 = *n - i__;
	    d__1 = -tau[i__];
	    dscal_(&i__1, &d__1, &a[i__ + (i__ + 1) * a_dim1], lda);
	}
	a[i__ + i__ * a_dim1] = 1. - tau[i__];

/*        Set A(i,1:i-1) to zero */

	i__1 = i__ - 1;
	for (l = 1; l <= i__1; ++l) {
	    a[i__ + l * a_dim1] = 0.;
/* L30: */
	}
/* L40: */
    }
    return 0;

/*     End of DORGL2 */

} /* dorgl2_ */

/* Subroutine */ int dorglq_(integer *m, integer *n, integer *k, doublereal *
	a, integer *lda, doublereal *tau, doublereal *work, integer *lwork,
	integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;
    integer c_n1 = -1;
    integer c__3 = 3;
    integer c__2 = 2;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;

    /* Local variables */
    integer i__, j, l, ib, nb, ki, kk, nx, iws, nbmin, iinfo;
    extern /* Subroutine */ int dorgl2_(integer *, integer *, integer *,
	    doublereal *, integer *, doublereal *, doublereal *, integer *),
	    dlarfb_(char *, char *, char *, char *, integer *, integer *,
	    integer *, doublereal *, integer *, doublereal *, integer *,
	    doublereal *, integer *, doublereal *, integer *), dlarft_(char *, char *, integer *, integer *,
	    doublereal *, integer *, doublereal *, doublereal *, integer *), xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *,
	    integer *, integer *);
    integer ldwork, lwkopt;
    logical lquery;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DORGLQ generates an M-by-N real matrix Q with orthonormal rows, */
/*  which is defined as the first M rows of a product of K elementary */
/*  reflectors of order N */

/*        Q  =  H(k) . . . H(2) H(1) */

/*  as returned by DGELQF. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix Q. M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix Q. N >= M. */

/*  K       (input) INTEGER */
/*          The number of elementary reflectors whose product defines the */
/*          matrix Q. M >= K >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the i-th row must contain the vector which defines */
/*          the elementary reflector H(i), for i = 1,2,...,k, as returned */
/*          by DGELQF in the first k rows of its array argument A. */
/*          On exit, the M-by-N matrix Q. */

/*  LDA     (input) INTEGER */
/*          The first dimension of the array A. LDA >= max(1,M). */

/*  TAU     (input) DOUBLE PRECISION array, dimension (K) */
/*          TAU(i) must contain the scalar factor of the elementary */
/*          reflector H(i), as returned by DGELQF. */

/*  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK)) */
/*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK. */

/*  LWORK   (input) INTEGER */
/*          The dimension of the array WORK. LWORK >= max(1,M). */
/*          For optimum performance LWORK >= M*NB, where NB is */
/*          the optimal blocksize. */

/*          If LWORK = -1, then a workspace query is assumed; the routine */
/*          only calculates the optimal size of the WORK array, returns */
/*          this value as the first entry of the WORK array, and no error */
/*          message related to LWORK is issued by XERBLA. */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument has an illegal value */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    --work;

    /* Function Body */
    *info = 0;
    nb = ilaenv_(&c__1, "DORGLQ", " ", m, n, k, &c_n1);
    lwkopt = max(1,*m) * nb;
    work[1] = (doublereal) lwkopt;
    lquery = *lwork == -1;
    if (*m < 0) {
	*info = -1;
    } else if (*n < *m) {
	*info = -2;
    } else if (*k < 0 || *k > *m) {
	*info = -3;
    } else if (*lda < max(1,*m)) {
	*info = -5;
    } else if (*lwork < max(1,*m) && ! lquery) {
	*info = -8;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DORGLQ", &i__1);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible */

    if (*m <= 0) {
	work[1] = 1.;
	return 0;
    }

    nbmin = 2;
    nx = 0;
    iws = *m;
    if (nb > 1 && nb < *k) {

/*        Determine when to cross over from blocked to unblocked code. */

/* Computing MAX */
	i__1 = 0, i__2 = ilaenv_(&c__3, "DORGLQ", " ", m, n, k, &c_n1);
	nx = max(i__1,i__2);
	if (nx < *k) {

/*           Determine if workspace is large enough for blocked code. */

	    ldwork = *m;
	    iws = ldwork * nb;
	    if (*lwork < iws) {

/*              Not enough workspace to use optimal NB:  reduce NB and */
/*              determine the minimum value of NB. */

		nb = *lwork / ldwork;
/* Computing MAX */
		i__1 = 2, i__2 = ilaenv_(&c__2, "DORGLQ", " ", m, n, k, &c_n1);
		nbmin = max(i__1,i__2);
	    }
	}
    }

    if (nb >= nbmin && nb < *k && nx < *k) {

/*        Use blocked code after the last block. */
/*        The first kk rows are handled by the block method. */

	ki = (*k - nx - 1) / nb * nb;
/* Computing MIN */
	i__1 = *k, i__2 = ki + nb;
	kk = min(i__1,i__2);

/*        Set A(kk+1:m,1:kk) to zero. */

	i__1 = kk;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (i__ = kk + 1; i__ <= i__2; ++i__) {
		a[i__ + j * a_dim1] = 0.;
/* L10: */
	    }
/* L20: */
	}
    } else {
	kk = 0;
    }

/*     Use unblocked code for the last or only block. */

    if (kk < *m) {
	i__1 = *m - kk;
	i__2 = *n - kk;
	i__3 = *k - kk;
	dorgl2_(&i__1, &i__2, &i__3, &a[kk + 1 + (kk + 1) * a_dim1], lda, &
		tau[kk + 1], &work[1], &iinfo);
    }

    if (kk > 0) {

/*        Use blocked code */

	i__1 = -nb;
	for (i__ = ki + 1; i__1 < 0 ? i__ >= 1 : i__ <= 1; i__ += i__1) {
/* Computing MIN */
	    i__2 = nb, i__3 = *k - i__ + 1;
	    ib = min(i__2,i__3);
	    if (i__ + ib <= *m) {

/*              Form the triangular factor of the block reflector */
/*              H = H(i) H(i+1) . . . H(i+ib-1) */

		i__2 = *n - i__ + 1;
		dlarft_("Forward", "Rowwise", &i__2, &ib, &a[i__ + i__ *
			a_dim1], lda, &tau[i__], &work[1], &ldwork);

/*              Apply H' to A(i+ib:m,i:n) from the right */

		i__2 = *m - i__ - ib + 1;
		i__3 = *n - i__ + 1;
		dlarfb_("Right", "Transpose", "Forward", "Rowwise", &i__2, &
			i__3, &ib, &a[i__ + i__ * a_dim1], lda, &work[1], &
			ldwork, &a[i__ + ib + i__ * a_dim1], lda, &work[ib +
			1], &ldwork);
	    }

/*           Apply H' to columns i:n of current block */

	    i__2 = *n - i__ + 1;
	    dorgl2_(&ib, &i__2, &ib, &a[i__ + i__ * a_dim1], lda, &tau[i__], &
		    work[1], &iinfo);

/*           Set columns 1:i-1 of current block to zero */

	    i__2 = i__ - 1;
	    for (j = 1; j <= i__2; ++j) {
		i__3 = i__ + ib - 1;
		for (l = i__; l <= i__3; ++l) {
		    a[l + j * a_dim1] = 0.;
/* L30: */
		}
/* L40: */
	    }
/* L50: */
	}
    }

    work[1] = (doublereal) iws;
    return 0;

/*     End of DORGLQ */

} /* dorglq_ */

/* Subroutine */ int dorgqr_(integer *m, integer *n, integer *k, doublereal *
	a, integer *lda, doublereal *tau, doublereal *work, integer *lwork,
	integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;
    integer c_n1 = -1;
    integer c__3 = 3;
    integer c__2 = 2;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;

    /* Local variables */
    integer i__, j, l, ib, nb, ki, kk, nx, iws, nbmin, iinfo;
    extern /* Subroutine */ int dorg2r_(integer *, integer *, integer *,
	    doublereal *, integer *, doublereal *, doublereal *, integer *),
	    dlarfb_(char *, char *, char *, char *, integer *, integer *,
	    integer *, doublereal *, integer *, doublereal *, integer *,
	    doublereal *, integer *, doublereal *, integer *), dlarft_(char *, char *, integer *, integer *,
	    doublereal *, integer *, doublereal *, doublereal *, integer *), xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *,
	    integer *, integer *);
    integer ldwork, lwkopt;
    logical lquery;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DORGQR generates an M-by-N real matrix Q with orthonormal columns, */
/*  which is defined as the first N columns of a product of K elementary */
/*  reflectors of order M */

/*        Q  =  H(1) H(2) . . . H(k) */

/*  as returned by DGEQRF. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix Q. M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix Q. M >= N >= 0. */

/*  K       (input) INTEGER */
/*          The number of elementary reflectors whose product defines the */
/*          matrix Q. N >= K >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the i-th column must contain the vector which */
/*          defines the elementary reflector H(i), for i = 1,2,...,k, as */
/*          returned by DGEQRF in the first k columns of its array */
/*          argument A. */
/*          On exit, the M-by-N matrix Q. */

/*  LDA     (input) INTEGER */
/*          The first dimension of the array A. LDA >= max(1,M). */

/*  TAU     (input) DOUBLE PRECISION array, dimension (K) */
/*          TAU(i) must contain the scalar factor of the elementary */
/*          reflector H(i), as returned by DGEQRF. */

/*  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK)) */
/*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK. */

/*  LWORK   (input) INTEGER */
/*          The dimension of the array WORK. LWORK >= max(1,N). */
/*          For optimum performance LWORK >= N*NB, where NB is the */
/*          optimal blocksize. */

/*          If LWORK = -1, then a workspace query is assumed; the routine */
/*          only calculates the optimal size of the WORK array, returns */
/*          this value as the first entry of the WORK array, and no error */
/*          message related to LWORK is issued by XERBLA. */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument has an illegal value */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    --work;

    /* Function Body */
    *info = 0;
    nb = ilaenv_(&c__1, "DORGQR", " ", m, n, k, &c_n1);
    lwkopt = max(1,*n) * nb;
    work[1] = (doublereal) lwkopt;
    lquery = *lwork == -1;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0 || *n > *m) {
	*info = -2;
    } else if (*k < 0 || *k > *n) {
	*info = -3;
    } else if (*lda < max(1,*m)) {
	*info = -5;
    } else if (*lwork < max(1,*n) && ! lquery) {
	*info = -8;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DORGQR", &i__1);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible */

    if (*n <= 0) {
	work[1] = 1.;
	return 0;
    }

    nbmin = 2;
    nx = 0;
    iws = *n;
    if (nb > 1 && nb < *k) {

/*        Determine when to cross over from blocked to unblocked code. */

/* Computing MAX */
	i__1 = 0, i__2 = ilaenv_(&c__3, "DORGQR", " ", m, n, k, &c_n1);
	nx = max(i__1,i__2);
	if (nx < *k) {

/*           Determine if workspace is large enough for blocked code. */

	    ldwork = *n;
	    iws = ldwork * nb;
	    if (*lwork < iws) {

/*              Not enough workspace to use optimal NB:  reduce NB and */
/*              determine the minimum value of NB. */

		nb = *lwork / ldwork;
/* Computing MAX */
		i__1 = 2, i__2 = ilaenv_(&c__2, "DORGQR", " ", m, n, k, &c_n1);
		nbmin = max(i__1,i__2);
	    }
	}
    }

    if (nb >= nbmin && nb < *k && nx < *k) {

/*        Use blocked code after the last block. */
/*        The first kk columns are handled by the block method. */

	ki = (*k - nx - 1) / nb * nb;
/* Computing MIN */
	i__1 = *k, i__2 = ki + nb;
	kk = min(i__1,i__2);

/*        Set A(1:kk,kk+1:n) to zero. */

	i__1 = *n;
	for (j = kk + 1; j <= i__1; ++j) {
	    i__2 = kk;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		a[i__ + j * a_dim1] = 0.;
/* L10: */
	    }
/* L20: */
	}
    } else {
	kk = 0;
    }

/*     Use unblocked code for the last or only block. */

    if (kk < *n) {
	i__1 = *m - kk;
	i__2 = *n - kk;
	i__3 = *k - kk;
	dorg2r_(&i__1, &i__2, &i__3, &a[kk + 1 + (kk + 1) * a_dim1], lda, &
		tau[kk + 1], &work[1], &iinfo);
    }

    if (kk > 0) {

/*        Use blocked code */

	i__1 = -nb;
	for (i__ = ki + 1; i__1 < 0 ? i__ >= 1 : i__ <= 1; i__ += i__1) {
/* Computing MIN */
	    i__2 = nb, i__3 = *k - i__ + 1;
	    ib = min(i__2,i__3);
	    if (i__ + ib <= *n) {

/*              Form the triangular factor of the block reflector */
/*              H = H(i) H(i+1) . . . H(i+ib-1) */

		i__2 = *m - i__ + 1;
		dlarft_("Forward", "Columnwise", &i__2, &ib, &a[i__ + i__ *
			a_dim1], lda, &tau[i__], &work[1], &ldwork);

/*              Apply H to A(i:m,i+ib:n) from the left */

		i__2 = *m - i__ + 1;
		i__3 = *n - i__ - ib + 1;
		dlarfb_("Left", "No transpose", "Forward", "Columnwise", &
			i__2, &i__3, &ib, &a[i__ + i__ * a_dim1], lda, &work[
			1], &ldwork, &a[i__ + (i__ + ib) * a_dim1], lda, &
			work[ib + 1], &ldwork);
	    }

/*           Apply H to rows i:m of current block */

	    i__2 = *m - i__ + 1;
	    dorg2r_(&i__2, &ib, &ib, &a[i__ + i__ * a_dim1], lda, &tau[i__], &
		    work[1], &iinfo);

/*           Set rows 1:i-1 of current block to zero */

	    i__2 = i__ + ib - 1;
	    for (j = i__; j <= i__2; ++j) {
		i__3 = i__ - 1;
		for (l = 1; l <= i__3; ++l) {
		    a[l + j * a_dim1] = 0.;
/* L30: */
		}
/* L40: */
	    }
/* L50: */
	}
    }

    work[1] = (doublereal) iws;
    return 0;

/*     End of DORGQR */

} /* dorgqr_ */

/* Subroutine */ int dorm2r_(char *side, char *trans, integer *m, integer *n,
	integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *
	c__, integer *ldc, doublereal *work, integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;

    /* System generated locals */
    integer a_dim1, a_offset, c_dim1, c_offset, i__1, i__2;

    /* Local variables */
    integer i__, i1, i2, i3, ic, jc, mi, ni, nq;
    doublereal aii;
    logical left;
    extern /* Subroutine */ int dlarf_(char *, integer *, integer *,
	    doublereal *, integer *, doublereal *, doublereal *, integer *,
	    doublereal *);
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int xerbla_(char *, integer *);
    logical notran;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DORM2R overwrites the general real m by n matrix C with */

/*        Q * C  if SIDE = 'L' and TRANS = 'N', or */

/*        Q'* C  if SIDE = 'L' and TRANS = 'T', or */

/*        C * Q  if SIDE = 'R' and TRANS = 'N', or */

/*        C * Q' if SIDE = 'R' and TRANS = 'T', */

/*  where Q is a real orthogonal matrix defined as the product of k */
/*  elementary reflectors */

/*        Q = H(1) H(2) . . . H(k) */

/*  as returned by DGEQRF. Q is of order m if SIDE = 'L' and of order n */
/*  if SIDE = 'R'. */

/*  Arguments */
/*  ========= */

/*  SIDE    (input) CHARACTER*1 */
/*          = 'L': apply Q or Q' from the Left */
/*          = 'R': apply Q or Q' from the Right */

/*  TRANS   (input) CHARACTER*1 */
/*          = 'N': apply Q  (No transpose) */
/*          = 'T': apply Q' (Transpose) */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix C. M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix C. N >= 0. */

/*  K       (input) INTEGER */
/*          The number of elementary reflectors whose product defines */
/*          the matrix Q. */
/*          If SIDE = 'L', M >= K >= 0; */
/*          if SIDE = 'R', N >= K >= 0. */

/*  A       (input) DOUBLE PRECISION array, dimension (LDA,K) */
/*          The i-th column must contain the vector which defines the */
/*          elementary reflector H(i), for i = 1,2,...,k, as returned by */
/*          DGEQRF in the first k columns of its array argument A. */
/*          A is modified by the routine but restored on exit. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A. */
/*          If SIDE = 'L', LDA >= max(1,M); */
/*          if SIDE = 'R', LDA >= max(1,N). */

/*  TAU     (input) DOUBLE PRECISION array, dimension (K) */
/*          TAU(i) must contain the scalar factor of the elementary */
/*          reflector H(i), as returned by DGEQRF. */

/*  C       (input/output) DOUBLE PRECISION array, dimension (LDC,N) */
/*          On entry, the m by n matrix C. */
/*          On exit, C is overwritten by Q*C or Q'*C or C*Q' or C*Q. */

/*  LDC     (input) INTEGER */
/*          The leading dimension of the array C. LDC >= max(1,M). */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension */
/*                                   (N) if SIDE = 'L', */
/*                                   (M) if SIDE = 'R' */

/*  INFO    (output) INTEGER */
/*          = 0: successful exit */
/*          < 0: if INFO = -i, the i-th argument had an illegal value */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    --work;

    /* Function Body */
    *info = 0;
    left = lsame_(side, "L");
    notran = lsame_(trans, "N");

/*     NQ is the order of Q */

    if (left) {
	nq = *m;
    } else {
	nq = *n;
    }
    if (! left && ! lsame_(side, "R")) {
	*info = -1;
    } else if (! notran && ! lsame_(trans, "T")) {
	*info = -2;
    } else if (*m < 0) {
	*info = -3;
    } else if (*n < 0) {
	*info = -4;
    } else if (*k < 0 || *k > nq) {
	*info = -5;
    } else if (*lda < max(1,nq)) {
	*info = -7;
    } else if (*ldc < max(1,*m)) {
	*info = -10;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DORM2R", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0 || *k == 0) {
	return 0;
    }

    if ((left && ! notran) || (! left && notran)) {
	i1 = 1;
	i2 = *k;
	i3 = 1;
    } else {
	i1 = *k;
	i2 = 1;
	i3 = -1;
    }

    if (left) {
	ni = *n;
	jc = 1;
    } else {
	mi = *m;
	ic = 1;
    }

    i__1 = i2;
    i__2 = i3;
    for (i__ = i1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {
	if (left) {

/*           H(i) is applied to C(i:m,1:n) */

	    mi = *m - i__ + 1;
	    ic = i__;
	} else {

/*           H(i) is applied to C(1:m,i:n) */

	    ni = *n - i__ + 1;
	    jc = i__;
	}

/*        Apply H(i) */

	aii = a[i__ + i__ * a_dim1];
	a[i__ + i__ * a_dim1] = 1.;
	dlarf_(side, &mi, &ni, &a[i__ + i__ * a_dim1], &c__1, &tau[i__], &c__[
		ic + jc * c_dim1], ldc, &work[1]);
	a[i__ + i__ * a_dim1] = aii;
/* L10: */
    }
    return 0;

/*     End of DORM2R */

} /* dorm2r_ */

/* Subroutine */ int dormbr_(char *vect, char *side, char *trans, integer *m,
	integer *n, integer *k, doublereal *a, integer *lda, doublereal *tau,
	doublereal *c__, integer *ldc, doublereal *work, integer *lwork,
	integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;
    integer c_n1 = -1;
    integer c__2 = 2;

    /* System generated locals */
    address a__1[2];
    integer a_dim1, a_offset, c_dim1, c_offset, i__1, i__2, i__3[2];
    char ch__1[2];

    /* Local variables */
    integer i1, i2, nb, mi, ni, nq, nw;
    logical left;
    extern logical lsame_(char *, char *);
    integer iinfo;
    extern /* Subroutine */ int xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *,
	    integer *, integer *);
    extern /* Subroutine */ int dormlq_(char *, char *, integer *, integer *,
	    integer *, doublereal *, integer *, doublereal *, doublereal *,
	    integer *, doublereal *, integer *, integer *);
    logical notran;
    extern /* Subroutine */ int dormqr_(char *, char *, integer *, integer *,
	    integer *, doublereal *, integer *, doublereal *, doublereal *,
	    integer *, doublereal *, integer *, integer *);
    logical applyq;
    char transt[1];
    integer lwkopt;
    logical lquery;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  If VECT = 'Q', DORMBR overwrites the general real M-by-N matrix C */
/*  with */
/*                  SIDE = 'L'     SIDE = 'R' */
/*  TRANS = 'N':      Q * C          C * Q */
/*  TRANS = 'T':      Q**T * C       C * Q**T */

/*  If VECT = 'P', DORMBR overwrites the general real M-by-N matrix C */
/*  with */
/*                  SIDE = 'L'     SIDE = 'R' */
/*  TRANS = 'N':      P * C          C * P */
/*  TRANS = 'T':      P**T * C       C * P**T */

/*  Here Q and P**T are the orthogonal matrices determined by DGEBRD when */
/*  reducing a real matrix A to bidiagonal form: A = Q * B * P**T. Q and */
/*  P**T are defined as products of elementary reflectors H(i) and G(i) */
/*  respectively. */

/*  Let nq = m if SIDE = 'L' and nq = n if SIDE = 'R'. Thus nq is the */
/*  order of the orthogonal matrix Q or P**T that is applied. */

/*  If VECT = 'Q', A is assumed to have been an NQ-by-K matrix: */
/*  if nq >= k, Q = H(1) H(2) . . . H(k); */
/*  if nq < k, Q = H(1) H(2) . . . H(nq-1). */

/*  If VECT = 'P', A is assumed to have been a K-by-NQ matrix: */
/*  if k < nq, P = G(1) G(2) . . . G(k); */
/*  if k >= nq, P = G(1) G(2) . . . G(nq-1). */

/*  Arguments */
/*  ========= */

/*  VECT    (input) CHARACTER*1 */
/*          = 'Q': apply Q or Q**T; */
/*          = 'P': apply P or P**T. */

/*  SIDE    (input) CHARACTER*1 */
/*          = 'L': apply Q, Q**T, P or P**T from the Left; */
/*          = 'R': apply Q, Q**T, P or P**T from the Right. */

/*  TRANS   (input) CHARACTER*1 */
/*          = 'N':  No transpose, apply Q  or P; */
/*          = 'T':  Transpose, apply Q**T or P**T. */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix C. M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix C. N >= 0. */

/*  K       (input) INTEGER */
/*          If VECT = 'Q', the number of columns in the original */
/*          matrix reduced by DGEBRD. */
/*          If VECT = 'P', the number of rows in the original */
/*          matrix reduced by DGEBRD. */
/*          K >= 0. */

/*  A       (input) DOUBLE PRECISION array, dimension */
/*                                (LDA,min(nq,K)) if VECT = 'Q' */
/*                                (LDA,nq)        if VECT = 'P' */
/*          The vectors which define the elementary reflectors H(i) and */
/*          G(i), whose products determine the matrices Q and P, as */
/*          returned by DGEBRD. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A. */
/*          If VECT = 'Q', LDA >= max(1,nq); */
/*          if VECT = 'P', LDA >= max(1,min(nq,K)). */

/*  TAU     (input) DOUBLE PRECISION array, dimension (min(nq,K)) */
/*          TAU(i) must contain the scalar factor of the elementary */
/*          reflector H(i) or G(i) which determines Q or P, as returned */
/*          by DGEBRD in the array argument TAUQ or TAUP. */

/*  C       (input/output) DOUBLE PRECISION array, dimension (LDC,N) */
/*          On entry, the M-by-N matrix C. */
/*          On exit, C is overwritten by Q*C or Q**T*C or C*Q**T or C*Q */
/*          or P*C or P**T*C or C*P or C*P**T. */

/*  LDC     (input) INTEGER */
/*          The leading dimension of the array C. LDC >= max(1,M). */

/*  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK)) */
/*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK. */

/*  LWORK   (input) INTEGER */
/*          The dimension of the array WORK. */
/*          If SIDE = 'L', LWORK >= max(1,N); */
/*          if SIDE = 'R', LWORK >= max(1,M). */
/*          For optimum performance LWORK >= N*NB if SIDE = 'L', and */
/*          LWORK >= M*NB if SIDE = 'R', where NB is the optimal */
/*          blocksize. */

/*          If LWORK = -1, then a workspace query is assumed; the routine */
/*          only calculates the optimal size of the WORK array, returns */
/*          this value as the first entry of the WORK array, and no error */
/*          message related to LWORK is issued by XERBLA. */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */

/*  ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    --work;

    /* Function Body */
    *info = 0;
    applyq = lsame_(vect, "Q");
    left = lsame_(side, "L");
    notran = lsame_(trans, "N");
    lquery = *lwork == -1;

/*     NQ is the order of Q or P and NW is the minimum dimension of WORK */

    if (left) {
	nq = *m;
	nw = *n;
    } else {
	nq = *n;
	nw = *m;
    }
    if (! applyq && ! lsame_(vect, "P")) {
	*info = -1;
    } else if (! left && ! lsame_(side, "R")) {
	*info = -2;
    } else if (! notran && ! lsame_(trans, "T")) {
	*info = -3;
    } else if (*m < 0) {
	*info = -4;
    } else if (*n < 0) {
	*info = -5;
    } else if (*k < 0) {
	*info = -6;
    } else /* if(complicated condition) */ {
/* Computing MAX */
	i__1 = 1, i__2 = min(nq,*k);
	if ((applyq && *lda < max(1,nq)) || (! applyq && *lda < max(i__1,i__2))) {
	    *info = -8;
	} else if (*ldc < max(1,*m)) {
	    *info = -11;
	} else if (*lwork < max(1,nw) && ! lquery) {
	    *info = -13;
	}
    }

    if (*info == 0) {
	if (applyq) {
	    if (left) {
/* Writing concatenation */
		i__3[0] = 1, a__1[0] = side;
		i__3[1] = 1, a__1[1] = trans;
		s_cat(ch__1, a__1, i__3, &c__2, (ftnlen)2);
		i__1 = *m - 1;
		i__2 = *m - 1;
		nb = ilaenv_(&c__1, "DORMQR", ch__1, &i__1, n, &i__2, &c_n1);
	    } else {
/* Writing concatenation */
		i__3[0] = 1, a__1[0] = side;
		i__3[1] = 1, a__1[1] = trans;
		s_cat(ch__1, a__1, i__3, &c__2, (ftnlen)2);
		i__1 = *n - 1;
		i__2 = *n - 1;
		nb = ilaenv_(&c__1, "DORMQR", ch__1, m, &i__1, &i__2, &c_n1);
	    }
	} else {
	    if (left) {
/* Writing concatenation */
		i__3[0] = 1, a__1[0] = side;
		i__3[1] = 1, a__1[1] = trans;
		s_cat(ch__1, a__1, i__3, &c__2, (ftnlen)2);
		i__1 = *m - 1;
		i__2 = *m - 1;
		nb = ilaenv_(&c__1, "DORMLQ", ch__1, &i__1, n, &i__2, &c_n1);
	    } else {
/* Writing concatenation */
		i__3[0] = 1, a__1[0] = side;
		i__3[1] = 1, a__1[1] = trans;
		s_cat(ch__1, a__1, i__3, &c__2, (ftnlen)2);
		i__1 = *n - 1;
		i__2 = *n - 1;
		nb = ilaenv_(&c__1, "DORMLQ", ch__1, m, &i__1, &i__2, &c_n1);
	    }
	}
	lwkopt = max(1,nw) * nb;
	work[1] = (doublereal) lwkopt;
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DORMBR", &i__1);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible */

    work[1] = 1.;
    if (*m == 0 || *n == 0) {
	return 0;
    }

    if (applyq) {

/*        Apply Q */

	if (nq >= *k) {

/*           Q was determined by a call to DGEBRD with nq >= k */

	    dormqr_(side, trans, m, n, k, &a[a_offset], lda, &tau[1], &c__[
		    c_offset], ldc, &work[1], lwork, &iinfo);
	} else if (nq > 1) {

/*           Q was determined by a call to DGEBRD with nq < k */

	    if (left) {
		mi = *m - 1;
		ni = *n;
		i1 = 2;
		i2 = 1;
	    } else {
		mi = *m;
		ni = *n - 1;
		i1 = 1;
		i2 = 2;
	    }
	    i__1 = nq - 1;
	    dormqr_(side, trans, &mi, &ni, &i__1, &a[a_dim1 + 2], lda, &tau[1]
, &c__[i1 + i2 * c_dim1], ldc, &work[1], lwork, &iinfo);
	}
    } else {

/*        Apply P */

	if (notran) {
	    *(unsigned char *)transt = 'T';
	} else {
	    *(unsigned char *)transt = 'N';
	}
	if (nq > *k) {

/*           P was determined by a call to DGEBRD with nq > k */

	    dormlq_(side, transt, m, n, k, &a[a_offset], lda, &tau[1], &c__[
		    c_offset], ldc, &work[1], lwork, &iinfo);
	} else if (nq > 1) {

/*           P was determined by a call to DGEBRD with nq <= k */

	    if (left) {
		mi = *m - 1;
		ni = *n;
		i1 = 2;
		i2 = 1;
	    } else {
		mi = *m;
		ni = *n - 1;
		i1 = 1;
		i2 = 2;
	    }
	    i__1 = nq - 1;
	    dormlq_(side, transt, &mi, &ni, &i__1, &a[(a_dim1 << 1) + 1], lda,
		     &tau[1], &c__[i1 + i2 * c_dim1], ldc, &work[1], lwork, &
		    iinfo);
	}
    }
    work[1] = (doublereal) lwkopt;
    return 0;

/*     End of DORMBR */

} /* dormbr_ */

/* Subroutine */ int dorml2_(char *side, char *trans, integer *m, integer *n,
	integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *
	c__, integer *ldc, doublereal *work, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, c_dim1, c_offset, i__1, i__2;

    /* Local variables */
    integer i__, i1, i2, i3, ic, jc, mi, ni, nq;
    doublereal aii;
    logical left;
    extern /* Subroutine */ int dlarf_(char *, integer *, integer *,
	    doublereal *, integer *, doublereal *, doublereal *, integer *,
	    doublereal *);
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int xerbla_(char *, integer *);
    logical notran;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DORML2 overwrites the general real m by n matrix C with */

/*        Q * C  if SIDE = 'L' and TRANS = 'N', or */

/*        Q'* C  if SIDE = 'L' and TRANS = 'T', or */

/*        C * Q  if SIDE = 'R' and TRANS = 'N', or */

/*        C * Q' if SIDE = 'R' and TRANS = 'T', */

/*  where Q is a real orthogonal matrix defined as the product of k */
/*  elementary reflectors */

/*        Q = H(k) . . . H(2) H(1) */

/*  as returned by DGELQF. Q is of order m if SIDE = 'L' and of order n */
/*  if SIDE = 'R'. */

/*  Arguments */
/*  ========= */

/*  SIDE    (input) CHARACTER*1 */
/*          = 'L': apply Q or Q' from the Left */
/*          = 'R': apply Q or Q' from the Right */

/*  TRANS   (input) CHARACTER*1 */
/*          = 'N': apply Q  (No transpose) */
/*          = 'T': apply Q' (Transpose) */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix C. M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix C. N >= 0. */

/*  K       (input) INTEGER */
/*          The number of elementary reflectors whose product defines */
/*          the matrix Q. */
/*          If SIDE = 'L', M >= K >= 0; */
/*          if SIDE = 'R', N >= K >= 0. */

/*  A       (input) DOUBLE PRECISION array, dimension */
/*                               (LDA,M) if SIDE = 'L', */
/*                               (LDA,N) if SIDE = 'R' */
/*          The i-th row must contain the vector which defines the */
/*          elementary reflector H(i), for i = 1,2,...,k, as returned by */
/*          DGELQF in the first k rows of its array argument A. */
/*          A is modified by the routine but restored on exit. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A. LDA >= max(1,K). */

/*  TAU     (input) DOUBLE PRECISION array, dimension (K) */
/*          TAU(i) must contain the scalar factor of the elementary */
/*          reflector H(i), as returned by DGELQF. */

/*  C       (input/output) DOUBLE PRECISION array, dimension (LDC,N) */
/*          On entry, the m by n matrix C. */
/*          On exit, C is overwritten by Q*C or Q'*C or C*Q' or C*Q. */

/*  LDC     (input) INTEGER */
/*          The leading dimension of the array C. LDC >= max(1,M). */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension */
/*                                   (N) if SIDE = 'L', */
/*                                   (M) if SIDE = 'R' */

/*  INFO    (output) INTEGER */
/*          = 0: successful exit */
/*          < 0: if INFO = -i, the i-th argument had an illegal value */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    --work;

    /* Function Body */
    *info = 0;
    left = lsame_(side, "L");
    notran = lsame_(trans, "N");

/*     NQ is the order of Q */

    if (left) {
	nq = *m;
    } else {
	nq = *n;
    }
    if (! left && ! lsame_(side, "R")) {
	*info = -1;
    } else if (! notran && ! lsame_(trans, "T")) {
	*info = -2;
    } else if (*m < 0) {
	*info = -3;
    } else if (*n < 0) {
	*info = -4;
    } else if (*k < 0 || *k > nq) {
	*info = -5;
    } else if (*lda < max(1,*k)) {
	*info = -7;
    } else if (*ldc < max(1,*m)) {
	*info = -10;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DORML2", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0 || *k == 0) {
	return 0;
    }

    if ((left && notran) || (! left && ! notran)) {
	i1 = 1;
	i2 = *k;
	i3 = 1;
    } else {
	i1 = *k;
	i2 = 1;
	i3 = -1;
    }

    if (left) {
	ni = *n;
	jc = 1;
    } else {
	mi = *m;
	ic = 1;
    }

    i__1 = i2;
    i__2 = i3;
    for (i__ = i1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {
	if (left) {

/*           H(i) is applied to C(i:m,1:n) */

	    mi = *m - i__ + 1;
	    ic = i__;
	} else {

/*           H(i) is applied to C(1:m,i:n) */

	    ni = *n - i__ + 1;
	    jc = i__;
	}

/*        Apply H(i) */

	aii = a[i__ + i__ * a_dim1];
	a[i__ + i__ * a_dim1] = 1.;
	dlarf_(side, &mi, &ni, &a[i__ + i__ * a_dim1], lda, &tau[i__], &c__[
		ic + jc * c_dim1], ldc, &work[1]);
	a[i__ + i__ * a_dim1] = aii;
/* L10: */
    }
    return 0;

/*     End of DORML2 */

} /* dorml2_ */

/* Subroutine */ int dormlq_(char *side, char *trans, integer *m, integer *n,
	integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *
	c__, integer *ldc, doublereal *work, integer *lwork, integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;
    integer c_n1 = -1;
    integer c__2 = 2;
    integer c__65 = 65;

    /* System generated locals */
    address a__1[2];
    integer a_dim1, a_offset, c_dim1, c_offset, i__1, i__2, i__3[2], i__4,
	    i__5;
    char ch__1[2];

    /* Local variables */
    integer i__;
    doublereal t[4160]	/* was [65][64] */;
    integer i1, i2, i3, ib, ic, jc, nb, mi, ni, nq, nw, iws;
    logical left;
    extern logical lsame_(char *, char *);
    integer nbmin, iinfo;
    extern /* Subroutine */ int dorml2_(char *, char *, integer *, integer *,
	    integer *, doublereal *, integer *, doublereal *, doublereal *,
	    integer *, doublereal *, integer *), dlarfb_(char
	    *, char *, char *, char *, integer *, integer *, integer *,
	    doublereal *, integer *, doublereal *, integer *, doublereal *,
	    integer *, doublereal *, integer *), dlarft_(char *, char *, integer *, integer *, doublereal
	    *, integer *, doublereal *, doublereal *, integer *), xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *,
	    integer *, integer *);
    logical notran;
    integer ldwork;
    char transt[1];
    integer lwkopt;
    logical lquery;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DORMLQ overwrites the general real M-by-N matrix C with */

/*                  SIDE = 'L'     SIDE = 'R' */
/*  TRANS = 'N':      Q * C          C * Q */
/*  TRANS = 'T':      Q**T * C       C * Q**T */

/*  where Q is a real orthogonal matrix defined as the product of k */
/*  elementary reflectors */

/*        Q = H(k) . . . H(2) H(1) */

/*  as returned by DGELQF. Q is of order M if SIDE = 'L' and of order N */
/*  if SIDE = 'R'. */

/*  Arguments */
/*  ========= */

/*  SIDE    (input) CHARACTER*1 */
/*          = 'L': apply Q or Q**T from the Left; */
/*          = 'R': apply Q or Q**T from the Right. */

/*  TRANS   (input) CHARACTER*1 */
/*          = 'N':  No transpose, apply Q; */
/*          = 'T':  Transpose, apply Q**T. */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix C. M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix C. N >= 0. */

/*  K       (input) INTEGER */
/*          The number of elementary reflectors whose product defines */
/*          the matrix Q. */
/*          If SIDE = 'L', M >= K >= 0; */
/*          if SIDE = 'R', N >= K >= 0. */

/*  A       (input) DOUBLE PRECISION array, dimension */
/*                               (LDA,M) if SIDE = 'L', */
/*                               (LDA,N) if SIDE = 'R' */
/*          The i-th row must contain the vector which defines the */
/*          elementary reflector H(i), for i = 1,2,...,k, as returned by */
/*          DGELQF in the first k rows of its array argument A. */
/*          A is modified by the routine but restored on exit. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A. LDA >= max(1,K). */

/*  TAU     (input) DOUBLE PRECISION array, dimension (K) */
/*          TAU(i) must contain the scalar factor of the elementary */
/*          reflector H(i), as returned by DGELQF. */

/*  C       (input/output) DOUBLE PRECISION array, dimension (LDC,N) */
/*          On entry, the M-by-N matrix C. */
/*          On exit, C is overwritten by Q*C or Q**T*C or C*Q**T or C*Q. */

/*  LDC     (input) INTEGER */
/*          The leading dimension of the array C. LDC >= max(1,M). */

/*  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK)) */
/*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK. */

/*  LWORK   (input) INTEGER */
/*          The dimension of the array WORK. */
/*          If SIDE = 'L', LWORK >= max(1,N); */
/*          if SIDE = 'R', LWORK >= max(1,M). */
/*          For optimum performance LWORK >= N*NB if SIDE = 'L', and */
/*          LWORK >= M*NB if SIDE = 'R', where NB is the optimal */
/*          blocksize. */

/*          If LWORK = -1, then a workspace query is assumed; the routine */
/*          only calculates the optimal size of the WORK array, returns */
/*          this value as the first entry of the WORK array, and no error */
/*          message related to LWORK is issued by XERBLA. */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Local Arrays .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    --work;

    /* Function Body */
    *info = 0;
    left = lsame_(side, "L");
    notran = lsame_(trans, "N");
    lquery = *lwork == -1;

/*     NQ is the order of Q and NW is the minimum dimension of WORK */

    if (left) {
	nq = *m;
	nw = *n;
    } else {
	nq = *n;
	nw = *m;
    }
    if (! left && ! lsame_(side, "R")) {
	*info = -1;
    } else if (! notran && ! lsame_(trans, "T")) {
	*info = -2;
    } else if (*m < 0) {
	*info = -3;
    } else if (*n < 0) {
	*info = -4;
    } else if (*k < 0 || *k > nq) {
	*info = -5;
    } else if (*lda < max(1,*k)) {
	*info = -7;
    } else if (*ldc < max(1,*m)) {
	*info = -10;
    } else if (*lwork < max(1,nw) && ! lquery) {
	*info = -12;
    }

    if (*info == 0) {

/*        Determine the block size.  NB may be at most NBMAX, where NBMAX */
/*        is used to define the local array T. */

/* Computing MIN */
/* Writing concatenation */
	i__3[0] = 1, a__1[0] = side;
	i__3[1] = 1, a__1[1] = trans;
	s_cat(ch__1, a__1, i__3, &c__2, (ftnlen)2);
	i__1 = 64, i__2 = ilaenv_(&c__1, "DORMLQ", ch__1, m, n, k, &c_n1);
	nb = min(i__1,i__2);
	lwkopt = max(1,nw) * nb;
	work[1] = (doublereal) lwkopt;
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DORMLQ", &i__1);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0 || *k == 0) {
	work[1] = 1.;
	return 0;
    }

    nbmin = 2;
    ldwork = nw;
    if (nb > 1 && nb < *k) {
	iws = nw * nb;
	if (*lwork < iws) {
	    nb = *lwork / ldwork;
/* Computing MAX */
/* Writing concatenation */
	    i__3[0] = 1, a__1[0] = side;
	    i__3[1] = 1, a__1[1] = trans;
	    s_cat(ch__1, a__1, i__3, &c__2, (ftnlen)2);
	    i__1 = 2, i__2 = ilaenv_(&c__2, "DORMLQ", ch__1, m, n, k, &c_n1);
	    nbmin = max(i__1,i__2);
	}
    } else {
	iws = nw;
    }

    if (nb < nbmin || nb >= *k) {

/*        Use unblocked code */

	dorml2_(side, trans, m, n, k, &a[a_offset], lda, &tau[1], &c__[
		c_offset], ldc, &work[1], &iinfo);
    } else {

/*        Use blocked code */

	if ((left && notran) || (! left && ! notran)) {
	    i1 = 1;
	    i2 = *k;
	    i3 = nb;
	} else {
	    i1 = (*k - 1) / nb * nb + 1;
	    i2 = 1;
	    i3 = -nb;
	}

	if (left) {
	    ni = *n;
	    jc = 1;
	} else {
	    mi = *m;
	    ic = 1;
	}

	if (notran) {
	    *(unsigned char *)transt = 'T';
	} else {
	    *(unsigned char *)transt = 'N';
	}

	i__1 = i2;
	i__2 = i3;
	for (i__ = i1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {
/* Computing MIN */
	    i__4 = nb, i__5 = *k - i__ + 1;
	    ib = min(i__4,i__5);

/*           Form the triangular factor of the block reflector */
/*           H = H(i) H(i+1) . . . H(i+ib-1) */

	    i__4 = nq - i__ + 1;
	    dlarft_("Forward", "Rowwise", &i__4, &ib, &a[i__ + i__ * a_dim1],
		    lda, &tau[i__], t, &c__65);
	    if (left) {

/*              H or H' is applied to C(i:m,1:n) */

		mi = *m - i__ + 1;
		ic = i__;
	    } else {

/*              H or H' is applied to C(1:m,i:n) */

		ni = *n - i__ + 1;
		jc = i__;
	    }

/*           Apply H or H' */

	    dlarfb_(side, transt, "Forward", "Rowwise", &mi, &ni, &ib, &a[i__
		    + i__ * a_dim1], lda, t, &c__65, &c__[ic + jc * c_dim1],
		    ldc, &work[1], &ldwork);
/* L10: */
	}
    }
    work[1] = (doublereal) lwkopt;
    return 0;

/*     End of DORMLQ */

} /* dormlq_ */

/* Subroutine */ int dormqr_(char *side, char *trans, integer *m, integer *n,
	integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *
	c__, integer *ldc, doublereal *work, integer *lwork, integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;
    integer c_n1 = -1;
    integer c__2 = 2;
    integer c__65 = 65;

    /* System generated locals */
    address a__1[2];
    integer a_dim1, a_offset, c_dim1, c_offset, i__1, i__2, i__3[2], i__4,
	    i__5;
    char ch__1[2];

    /* Local variables */
    integer i__;
    doublereal t[4160]	/* was [65][64] */;
    integer i1, i2, i3, ib, ic, jc, nb, mi, ni, nq, nw, iws;
    logical left;
    extern logical lsame_(char *, char *);
    integer nbmin, iinfo;
    extern /* Subroutine */ int dorm2r_(char *, char *, integer *, integer *,
	    integer *, doublereal *, integer *, doublereal *, doublereal *,
	    integer *, doublereal *, integer *), dlarfb_(char
	    *, char *, char *, char *, integer *, integer *, integer *,
	    doublereal *, integer *, doublereal *, integer *, doublereal *,
	    integer *, doublereal *, integer *), dlarft_(char *, char *, integer *, integer *, doublereal
	    *, integer *, doublereal *, doublereal *, integer *), xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *,
	    integer *, integer *);
    logical notran;
    integer ldwork, lwkopt;
    logical lquery;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DORMQR overwrites the general real M-by-N matrix C with */

/*                  SIDE = 'L'     SIDE = 'R' */
/*  TRANS = 'N':      Q * C          C * Q */
/*  TRANS = 'T':      Q**T * C       C * Q**T */

/*  where Q is a real orthogonal matrix defined as the product of k */
/*  elementary reflectors */

/*        Q = H(1) H(2) . . . H(k) */

/*  as returned by DGEQRF. Q is of order M if SIDE = 'L' and of order N */
/*  if SIDE = 'R'. */

/*  Arguments */
/*  ========= */

/*  SIDE    (input) CHARACTER*1 */
/*          = 'L': apply Q or Q**T from the Left; */
/*          = 'R': apply Q or Q**T from the Right. */

/*  TRANS   (input) CHARACTER*1 */
/*          = 'N':  No transpose, apply Q; */
/*          = 'T':  Transpose, apply Q**T. */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix C. M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix C. N >= 0. */

/*  K       (input) INTEGER */
/*          The number of elementary reflectors whose product defines */
/*          the matrix Q. */
/*          If SIDE = 'L', M >= K >= 0; */
/*          if SIDE = 'R', N >= K >= 0. */

/*  A       (input) DOUBLE PRECISION array, dimension (LDA,K) */
/*          The i-th column must contain the vector which defines the */
/*          elementary reflector H(i), for i = 1,2,...,k, as returned by */
/*          DGEQRF in the first k columns of its array argument A. */
/*          A is modified by the routine but restored on exit. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A. */
/*          If SIDE = 'L', LDA >= max(1,M); */
/*          if SIDE = 'R', LDA >= max(1,N). */

/*  TAU     (input) DOUBLE PRECISION array, dimension (K) */
/*          TAU(i) must contain the scalar factor of the elementary */
/*          reflector H(i), as returned by DGEQRF. */

/*  C       (input/output) DOUBLE PRECISION array, dimension (LDC,N) */
/*          On entry, the M-by-N matrix C. */
/*          On exit, C is overwritten by Q*C or Q**T*C or C*Q**T or C*Q. */

/*  LDC     (input) INTEGER */
/*          The leading dimension of the array C. LDC >= max(1,M). */

/*  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK)) */
/*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK. */

/*  LWORK   (input) INTEGER */
/*          The dimension of the array WORK. */
/*          If SIDE = 'L', LWORK >= max(1,N); */
/*          if SIDE = 'R', LWORK >= max(1,M). */
/*          For optimum performance LWORK >= N*NB if SIDE = 'L', and */
/*          LWORK >= M*NB if SIDE = 'R', where NB is the optimal */
/*          blocksize. */

/*          If LWORK = -1, then a workspace query is assumed; the routine */
/*          only calculates the optimal size of the WORK array, returns */
/*          this value as the first entry of the WORK array, and no error */
/*          message related to LWORK is issued by XERBLA. */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Local Arrays .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    --work;

    /* Function Body */
    *info = 0;
    left = lsame_(side, "L");
    notran = lsame_(trans, "N");
    lquery = *lwork == -1;

/*     NQ is the order of Q and NW is the minimum dimension of WORK */

    if (left) {
	nq = *m;
	nw = *n;
    } else {
	nq = *n;
	nw = *m;
    }
    if (! left && ! lsame_(side, "R")) {
	*info = -1;
    } else if (! notran && ! lsame_(trans, "T")) {
	*info = -2;
    } else if (*m < 0) {
	*info = -3;
    } else if (*n < 0) {
	*info = -4;
    } else if (*k < 0 || *k > nq) {
	*info = -5;
    } else if (*lda < max(1,nq)) {
	*info = -7;
    } else if (*ldc < max(1,*m)) {
	*info = -10;
    } else if (*lwork < max(1,nw) && ! lquery) {
	*info = -12;
    }

    if (*info == 0) {

/*        Determine the block size.  NB may be at most NBMAX, where NBMAX */
/*        is used to define the local array T. */

/* Computing MIN */
/* Writing concatenation */
	i__3[0] = 1, a__1[0] = side;
	i__3[1] = 1, a__1[1] = trans;
	s_cat(ch__1, a__1, i__3, &c__2, (ftnlen)2);
	i__1 = 64, i__2 = ilaenv_(&c__1, "DORMQR", ch__1, m, n, k, &c_n1);
	nb = min(i__1,i__2);
	lwkopt = max(1,nw) * nb;
	work[1] = (doublereal) lwkopt;
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DORMQR", &i__1);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0 || *k == 0) {
	work[1] = 1.;
	return 0;
    }

    nbmin = 2;
    ldwork = nw;
    if (nb > 1 && nb < *k) {
	iws = nw * nb;
	if (*lwork < iws) {
	    nb = *lwork / ldwork;
/* Computing MAX */
/* Writing concatenation */
	    i__3[0] = 1, a__1[0] = side;
	    i__3[1] = 1, a__1[1] = trans;
	    s_cat(ch__1, a__1, i__3, &c__2, (ftnlen)2);
	    i__1 = 2, i__2 = ilaenv_(&c__2, "DORMQR", ch__1, m, n, k, &c_n1);
	    nbmin = max(i__1,i__2);
	}
    } else {
	iws = nw;
    }

    if (nb < nbmin || nb >= *k) {

/*        Use unblocked code */

	dorm2r_(side, trans, m, n, k, &a[a_offset], lda, &tau[1], &c__[
		c_offset], ldc, &work[1], &iinfo);
    } else {

/*        Use blocked code */

	if ((left && ! notran) || (! left && notran)) {
	    i1 = 1;
	    i2 = *k;
	    i3 = nb;
	} else {
	    i1 = (*k - 1) / nb * nb + 1;
	    i2 = 1;
	    i3 = -nb;
	}

	if (left) {
	    ni = *n;
	    jc = 1;
	} else {
	    mi = *m;
	    ic = 1;
	}

	i__1 = i2;
	i__2 = i3;
	for (i__ = i1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {
/* Computing MIN */
	    i__4 = nb, i__5 = *k - i__ + 1;
	    ib = min(i__4,i__5);

/*           Form the triangular factor of the block reflector */
/*           H = H(i) H(i+1) . . . H(i+ib-1) */

	    i__4 = nq - i__ + 1;
	    dlarft_("Forward", "Columnwise", &i__4, &ib, &a[i__ + i__ *
		    a_dim1], lda, &tau[i__], t, &c__65)
		    ;
	    if (left) {

/*              H or H' is applied to C(i:m,1:n) */

		mi = *m - i__ + 1;
		ic = i__;
	    } else {

/*              H or H' is applied to C(1:m,i:n) */

		ni = *n - i__ + 1;
		jc = i__;
	    }

/*           Apply H or H' */

	    dlarfb_(side, trans, "Forward", "Columnwise", &mi, &ni, &ib, &a[
		    i__ + i__ * a_dim1], lda, t, &c__65, &c__[ic + jc *
		    c_dim1], ldc, &work[1], &ldwork);
/* L10: */
	}
    }
    work[1] = (doublereal) lwkopt;
    return 0;

/*     End of DORMQR */

} /* dormqr_ */

/* Subroutine */ int dormr3_(char *side, char *trans, integer *m, integer *n,
	integer *k, integer *l, doublereal *a, integer *lda, doublereal *tau,
	doublereal *c__, integer *ldc, doublereal *work, integer *info)
{
    /* System generated locals */
    integer a_dim1, a_offset, c_dim1, c_offset, i__1, i__2;

    /* Local variables */
    integer i__, i1, i2, i3, ja, ic, jc, mi, ni, nq;
    logical left;
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int dlarz_(char *, integer *, integer *, integer *
, doublereal *, integer *, doublereal *, doublereal *, integer *,
	    doublereal *), xerbla_(char *, integer *);
    logical notran;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DORMR3 overwrites the general real m by n matrix C with */

/*        Q * C  if SIDE = 'L' and TRANS = 'N', or */

/*        Q'* C  if SIDE = 'L' and TRANS = 'T', or */

/*        C * Q  if SIDE = 'R' and TRANS = 'N', or */

/*        C * Q' if SIDE = 'R' and TRANS = 'T', */

/*  where Q is a real orthogonal matrix defined as the product of k */
/*  elementary reflectors */

/*        Q = H(1) H(2) . . . H(k) */

/*  as returned by DTZRZF. Q is of order m if SIDE = 'L' and of order n */
/*  if SIDE = 'R'. */

/*  Arguments */
/*  ========= */

/*  SIDE    (input) CHARACTER*1 */
/*          = 'L': apply Q or Q' from the Left */
/*          = 'R': apply Q or Q' from the Right */

/*  TRANS   (input) CHARACTER*1 */
/*          = 'N': apply Q  (No transpose) */
/*          = 'T': apply Q' (Transpose) */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix C. M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix C. N >= 0. */

/*  K       (input) INTEGER */
/*          The number of elementary reflectors whose product defines */
/*          the matrix Q. */
/*          If SIDE = 'L', M >= K >= 0; */
/*          if SIDE = 'R', N >= K >= 0. */

/*  L       (input) INTEGER */
/*          The number of columns of the matrix A containing */
/*          the meaningful part of the Householder reflectors. */
/*          If SIDE = 'L', M >= L >= 0, if SIDE = 'R', N >= L >= 0. */

/*  A       (input) DOUBLE PRECISION array, dimension */
/*                               (LDA,M) if SIDE = 'L', */
/*                               (LDA,N) if SIDE = 'R' */
/*          The i-th row must contain the vector which defines the */
/*          elementary reflector H(i), for i = 1,2,...,k, as returned by */
/*          DTZRZF in the last k rows of its array argument A. */
/*          A is modified by the routine but restored on exit. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A. LDA >= max(1,K). */

/*  TAU     (input) DOUBLE PRECISION array, dimension (K) */
/*          TAU(i) must contain the scalar factor of the elementary */
/*          reflector H(i), as returned by DTZRZF. */

/*  C       (input/output) DOUBLE PRECISION array, dimension (LDC,N) */
/*          On entry, the m-by-n matrix C. */
/*          On exit, C is overwritten by Q*C or Q'*C or C*Q' or C*Q. */

/*  LDC     (input) INTEGER */
/*          The leading dimension of the array C. LDC >= max(1,M). */

/*  WORK    (workspace) DOUBLE PRECISION array, dimension */
/*                                   (N) if SIDE = 'L', */
/*                                   (M) if SIDE = 'R' */

/*  INFO    (output) INTEGER */
/*          = 0: successful exit */
/*          < 0: if INFO = -i, the i-th argument had an illegal value */

/*  Further Details */
/*  =============== */

/*  Based on contributions by */
/*    A. Petitet, Computer Science Dept., Univ. of Tenn., Knoxville, USA */

/*  ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    --work;

    /* Function Body */
    *info = 0;
    left = lsame_(side, "L");
    notran = lsame_(trans, "N");

/*     NQ is the order of Q */

    if (left) {
	nq = *m;
    } else {
	nq = *n;
    }
    if (! left && ! lsame_(side, "R")) {
	*info = -1;
    } else if (! notran && ! lsame_(trans, "T")) {
	*info = -2;
    } else if (*m < 0) {
	*info = -3;
    } else if (*n < 0) {
	*info = -4;
    } else if (*k < 0 || *k > nq) {
	*info = -5;
    } else if (*l < 0 || (left && *l > *m) || (! left && *l > *n)) {
	*info = -6;
    } else if (*lda < max(1,*k)) {
	*info = -8;
    } else if (*ldc < max(1,*m)) {
	*info = -11;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DORMR3", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0 || *k == 0) {
	return 0;
    }

    if ((left && ! notran) || (! left && notran)) {
	i1 = 1;
	i2 = *k;
	i3 = 1;
    } else {
	i1 = *k;
	i2 = 1;
	i3 = -1;
    }

    if (left) {
	ni = *n;
	ja = *m - *l + 1;
	jc = 1;
    } else {
	mi = *m;
	ja = *n - *l + 1;
	ic = 1;
    }

    i__1 = i2;
    i__2 = i3;
    for (i__ = i1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {
	if (left) {

/*           H(i) or H(i)' is applied to C(i:m,1:n) */

	    mi = *m - i__ + 1;
	    ic = i__;
	} else {

/*           H(i) or H(i)' is applied to C(1:m,i:n) */

	    ni = *n - i__ + 1;
	    jc = i__;
	}

/*        Apply H(i) or H(i)' */

	dlarz_(side, &mi, &ni, l, &a[i__ + ja * a_dim1], lda, &tau[i__], &c__[
		ic + jc * c_dim1], ldc, &work[1]);

/* L10: */
    }

    return 0;

/*     End of DORMR3 */

} /* dormr3_ */

/* Subroutine */ int dormrz_(char *side, char *trans, integer *m, integer *n,
	integer *k, integer *l, doublereal *a, integer *lda, doublereal *tau,
	doublereal *c__, integer *ldc, doublereal *work, integer *lwork,
	integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;
    integer c_n1 = -1;
    integer c__2 = 2;
    integer c__65 = 65;

    /* System generated locals */
    address a__1[2];
    integer a_dim1, a_offset, c_dim1, c_offset, i__1, i__2, i__3[2], i__4,
	    i__5;
    char ch__1[2];

    /* Local variables */
    integer i__;
    doublereal t[4160]	/* was [65][64] */;
    integer i1, i2, i3, ib, ic, ja, jc, nb, mi, ni, nq, nw, iws;
    logical left;
    extern logical lsame_(char *, char *);
    integer nbmin, iinfo;
    extern /* Subroutine */ int dormr3_(char *, char *, integer *, integer *,
	    integer *, integer *, doublereal *, integer *, doublereal *,
	    doublereal *, integer *, doublereal *, integer *),
	     xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *,
	    integer *, integer *);
    extern /* Subroutine */ int dlarzb_(char *, char *, char *, char *,
	    integer *, integer *, integer *, integer *, doublereal *, integer
	    *, doublereal *, integer *, doublereal *, integer *, doublereal *,
	     integer *), dlarzt_(char *, char
	    *, integer *, integer *, doublereal *, integer *, doublereal *,
	    doublereal *, integer *);
    logical notran;
    integer ldwork;
    char transt[1];
    integer lwkopt;
    logical lquery;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     January 2007 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DORMRZ overwrites the general real M-by-N matrix C with */

/*                  SIDE = 'L'     SIDE = 'R' */
/*  TRANS = 'N':      Q * C          C * Q */
/*  TRANS = 'T':      Q**T * C       C * Q**T */

/*  where Q is a real orthogonal matrix defined as the product of k */
/*  elementary reflectors */

/*        Q = H(1) H(2) . . . H(k) */

/*  as returned by DTZRZF. Q is of order M if SIDE = 'L' and of order N */
/*  if SIDE = 'R'. */

/*  Arguments */
/*  ========= */

/*  SIDE    (input) CHARACTER*1 */
/*          = 'L': apply Q or Q**T from the Left; */
/*          = 'R': apply Q or Q**T from the Right. */

/*  TRANS   (input) CHARACTER*1 */
/*          = 'N':  No transpose, apply Q; */
/*          = 'T':  Transpose, apply Q**T. */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix C. M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix C. N >= 0. */

/*  K       (input) INTEGER */
/*          The number of elementary reflectors whose product defines */
/*          the matrix Q. */
/*          If SIDE = 'L', M >= K >= 0; */
/*          if SIDE = 'R', N >= K >= 0. */

/*  L       (input) INTEGER */
/*          The number of columns of the matrix A containing */
/*          the meaningful part of the Householder reflectors. */
/*          If SIDE = 'L', M >= L >= 0, if SIDE = 'R', N >= L >= 0. */

/*  A       (input) DOUBLE PRECISION array, dimension */
/*                               (LDA,M) if SIDE = 'L', */
/*                               (LDA,N) if SIDE = 'R' */
/*          The i-th row must contain the vector which defines the */
/*          elementary reflector H(i), for i = 1,2,...,k, as returned by */
/*          DTZRZF in the last k rows of its array argument A. */
/*          A is modified by the routine but restored on exit. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A. LDA >= max(1,K). */

/*  TAU     (input) DOUBLE PRECISION array, dimension (K) */
/*          TAU(i) must contain the scalar factor of the elementary */
/*          reflector H(i), as returned by DTZRZF. */

/*  C       (input/output) DOUBLE PRECISION array, dimension (LDC,N) */
/*          On entry, the M-by-N matrix C. */
/*          On exit, C is overwritten by Q*C or Q**H*C or C*Q**H or C*Q. */

/*  LDC     (input) INTEGER */
/*          The leading dimension of the array C. LDC >= max(1,M). */

/*  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK)) */
/*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK. */

/*  LWORK   (input) INTEGER */
/*          The dimension of the array WORK. */
/*          If SIDE = 'L', LWORK >= max(1,N); */
/*          if SIDE = 'R', LWORK >= max(1,M). */
/*          For optimum performance LWORK >= N*NB if SIDE = 'L', and */
/*          LWORK >= M*NB if SIDE = 'R', where NB is the optimal */
/*          blocksize. */

/*          If LWORK = -1, then a workspace query is assumed; the routine */
/*          only calculates the optimal size of the WORK array, returns */
/*          this value as the first entry of the WORK array, and no error */
/*          message related to LWORK is issued by XERBLA. */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */

/*  Further Details */
/*  =============== */

/*  Based on contributions by */
/*    A. Petitet, Computer Science Dept., Univ. of Tenn., Knoxville, USA */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Local Arrays .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;
    --work;

    /* Function Body */
    *info = 0;
    left = lsame_(side, "L");
    notran = lsame_(trans, "N");
    lquery = *lwork == -1;

/*     NQ is the order of Q and NW is the minimum dimension of WORK */

    if (left) {
	nq = *m;
	nw = max(1,*n);
    } else {
	nq = *n;
	nw = max(1,*m);
    }
    if (! left && ! lsame_(side, "R")) {
	*info = -1;
    } else if (! notran && ! lsame_(trans, "T")) {
	*info = -2;
    } else if (*m < 0) {
	*info = -3;
    } else if (*n < 0) {
	*info = -4;
    } else if (*k < 0 || *k > nq) {
	*info = -5;
    } else if (*l < 0 || (left && *l > *m) || (! left && *l > *n)) {
	*info = -6;
    } else if (*lda < max(1,*k)) {
	*info = -8;
    } else if (*ldc < max(1,*m)) {
	*info = -11;
    }

    if (*info == 0) {
	if (*m == 0 || *n == 0) {
	    lwkopt = 1;
	} else {

/*           Determine the block size.  NB may be at most NBMAX, where */
/*           NBMAX is used to define the local array T. */

/* Computing MIN */
/* Writing concatenation */
	    i__3[0] = 1, a__1[0] = side;
	    i__3[1] = 1, a__1[1] = trans;
	    s_cat(ch__1, a__1, i__3, &c__2, (ftnlen)2);
	    i__1 = 64, i__2 = ilaenv_(&c__1, "DORMRQ", ch__1, m, n, k, &c_n1);
	    nb = min(i__1,i__2);
	    lwkopt = nw * nb;
	}
	work[1] = (doublereal) lwkopt;

	if (*lwork < max(1,nw) && ! lquery) {
	    *info = -13;
	}
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DORMRZ", &i__1);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0) {
	work[1] = 1.;
	return 0;
    }

    nbmin = 2;
    ldwork = nw;
    if (nb > 1 && nb < *k) {
	iws = nw * nb;
	if (*lwork < iws) {
	    nb = *lwork / ldwork;
/* Computing MAX */
/* Writing concatenation */
	    i__3[0] = 1, a__1[0] = side;
	    i__3[1] = 1, a__1[1] = trans;
	    s_cat(ch__1, a__1, i__3, &c__2, (ftnlen)2);
	    i__1 = 2, i__2 = ilaenv_(&c__2, "DORMRQ", ch__1, m, n, k, &c_n1);
	    nbmin = max(i__1,i__2);
	}
    } else {
	iws = nw;
    }

    if (nb < nbmin || nb >= *k) {

/*        Use unblocked code */

	dormr3_(side, trans, m, n, k, l, &a[a_offset], lda, &tau[1], &c__[
		c_offset], ldc, &work[1], &iinfo);
    } else {

/*        Use blocked code */

	if ((left && ! notran) || (! left && notran)) {
	    i1 = 1;
	    i2 = *k;
	    i3 = nb;
	} else {
	    i1 = (*k - 1) / nb * nb + 1;
	    i2 = 1;
	    i3 = -nb;
	}

	if (left) {
	    ni = *n;
	    jc = 1;
	    ja = *m - *l + 1;
	} else {
	    mi = *m;
	    ic = 1;
	    ja = *n - *l + 1;
	}

	if (notran) {
	    *(unsigned char *)transt = 'T';
	} else {
	    *(unsigned char *)transt = 'N';
	}

	i__1 = i2;
	i__2 = i3;
	for (i__ = i1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {
/* Computing MIN */
	    i__4 = nb, i__5 = *k - i__ + 1;
	    ib = min(i__4,i__5);

/*           Form the triangular factor of the block reflector */
/*           H = H(i+ib-1) . . . H(i+1) H(i) */

	    dlarzt_("Backward", "Rowwise", l, &ib, &a[i__ + ja * a_dim1], lda,
		     &tau[i__], t, &c__65);

	    if (left) {

/*              H or H' is applied to C(i:m,1:n) */

		mi = *m - i__ + 1;
		ic = i__;
	    } else {

/*              H or H' is applied to C(1:m,i:n) */

		ni = *n - i__ + 1;
		jc = i__;
	    }

/*           Apply H or H' */

	    dlarzb_(side, transt, "Backward", "Rowwise", &mi, &ni, &ib, l, &a[
		    i__ + ja * a_dim1], lda, t, &c__65, &c__[ic + jc * c_dim1]
, ldc, &work[1], &ldwork);
/* L10: */
	}

    }

    work[1] = (doublereal) lwkopt;

    return 0;

/*     End of DORMRZ */

} /* dormrz_ */

/* Subroutine */ int dtzrzf_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *tau, doublereal *work, integer *lwork, integer *info)
{
    /* Table of constant values */

    integer c__1 = 1;
    integer c_n1 = -1;
    integer c__3 = 3;
    integer c__2 = 2;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4, i__5;

    /* Local variables */
    integer i__, m1, ib, nb, ki, kk, mu, nx, iws, nbmin;
    extern /* Subroutine */ int xerbla_(char *, integer *), dlarzb_(
	    char *, char *, char *, char *, integer *, integer *, integer *,
	    integer *, doublereal *, integer *, doublereal *, integer *,
	    doublereal *, integer *, doublereal *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *,
	    integer *, integer *);
    extern /* Subroutine */ int dlarzt_(char *, char *, integer *, integer *,
	    doublereal *, integer *, doublereal *, doublereal *, integer *), dlatrz_(integer *, integer *, integer *,
	    doublereal *, integer *, doublereal *, doublereal *);
    integer ldwork, lwkopt;
    logical lquery;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DTZRZF reduces the M-by-N ( M<=N ) real upper trapezoidal matrix A */
/*  to upper triangular form by means of orthogonal transformations. */

/*  The upper trapezoidal matrix A is factored as */

/*     A = ( R  0 ) * Z, */

/*  where Z is an N-by-N orthogonal matrix and R is an M-by-M upper */
/*  triangular matrix. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A.  M >= 0. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A.  N >= M. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the leading M-by-N upper trapezoidal part of the */
/*          array A must contain the matrix to be factorized. */
/*          On exit, the leading M-by-M upper triangular part of A */
/*          contains the upper triangular matrix R, and elements M+1 to */
/*          N of the first M rows of A, with the array TAU, represent the */
/*          orthogonal matrix Z as a product of M elementary reflectors. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A.  LDA >= max(1,M). */

/*  TAU     (output) DOUBLE PRECISION array, dimension (M) */
/*          The scalar factors of the elementary reflectors. */

/*  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK)) */
/*          On exit, if INFO = 0, WORK(1) returns the optimal LWORK. */

/*  LWORK   (input) INTEGER */
/*          The dimension of the array WORK.  LWORK >= max(1,M). */
/*          For optimum performance LWORK >= M*NB, where NB is */
/*          the optimal blocksize. */

/*          If LWORK = -1, then a workspace query is assumed; the routine */
/*          only calculates the optimal size of the WORK array, returns */
/*          this value as the first entry of the WORK array, and no error */
/*          message related to LWORK is issued by XERBLA. */

/*  INFO    (output) INTEGER */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */

/*  Further Details */
/*  =============== */

/*  Based on contributions by */
/*    A. Petitet, Computer Science Dept., Univ. of Tenn., Knoxville, USA */

/*  The factorization is obtained by Householder's method.  The kth */
/*  transformation matrix, Z( k ), which is used to introduce zeros into */
/*  the ( m - k + 1 )th row of A, is given in the form */

/*     Z( k ) = ( I     0   ), */
/*              ( 0  T( k ) ) */

/*  where */

/*     T( k ) = I - tau*u( k )*u( k )',   u( k ) = (   1    ), */
/*                                                 (   0    ) */
/*                                                 ( z( k ) ) */

/*  tau is a scalar and z( k ) is an ( n - m ) element vector. */
/*  tau and z( k ) are chosen to annihilate the elements of the kth row */
/*  of X. */

/*  The scalar tau is returned in the kth element of TAU and the vector */
/*  u( k ) in the kth row of A, such that the elements of z( k ) are */
/*  in  a( k, m + 1 ), ..., a( k, n ). The elements of R are returned in */
/*  the upper triangular part of A. */

/*  Z is given by */

/*     Z =  Z( 1 ) * Z( 2 ) * ... * Z( m ). */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input arguments */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --tau;
    --work;

    /* Function Body */
    *info = 0;
    lquery = *lwork == -1;
    if (*m < 0) {
	*info = -1;
    } else if (*n < *m) {
	*info = -2;
    } else if (*lda < max(1,*m)) {
	*info = -4;
    }

    if (*info == 0) {
	if (*m == 0 || *m == *n) {
	    lwkopt = 1;
	} else {

/*           Determine the block size. */

	    nb = ilaenv_(&c__1, "DGERQF", " ", m, n, &c_n1, &c_n1);
	    lwkopt = *m * nb;
	}
	work[1] = (doublereal) lwkopt;

	if (*lwork < max(1,*m) && ! lquery) {
	    *info = -7;
	}
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DTZRZF", &i__1);
	return 0;
    } else if (lquery) {
	return 0;
    }

/*     Quick return if possible */

    if (*m == 0) {
	return 0;
    } else if (*m == *n) {
	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    tau[i__] = 0.;
/* L10: */
	}
	return 0;
    }

    nbmin = 2;
    nx = 1;
    iws = *m;
    if (nb > 1 && nb < *m) {

/*        Determine when to cross over from blocked to unblocked code. */

/* Computing MAX */
	i__1 = 0, i__2 = ilaenv_(&c__3, "DGERQF", " ", m, n, &c_n1, &c_n1);
	nx = max(i__1,i__2);
	if (nx < *m) {

/*           Determine if workspace is large enough for blocked code. */

	    ldwork = *m;
	    iws = ldwork * nb;
	    if (*lwork < iws) {

/*              Not enough workspace to use optimal NB:  reduce NB and */
/*              determine the minimum value of NB. */

		nb = *lwork / ldwork;
/* Computing MAX */
		i__1 = 2, i__2 = ilaenv_(&c__2, "DGERQF", " ", m, n, &c_n1, &
			c_n1);
		nbmin = max(i__1,i__2);
	    }
	}
    }

    if (nb >= nbmin && nb < *m && nx < *m) {

/*        Use blocked code initially. */
/*        The last kk rows are handled by the block method. */

/* Computing MIN */
	i__1 = *m + 1;
	m1 = min(i__1,*n);
	ki = (*m - nx - 1) / nb * nb;
/* Computing MIN */
	i__1 = *m, i__2 = ki + nb;
	kk = min(i__1,i__2);

	i__1 = *m - kk + 1;
	i__2 = -nb;
	for (i__ = *m - kk + ki + 1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1;
		i__ += i__2) {
/* Computing MIN */
	    i__3 = *m - i__ + 1;
	    ib = min(i__3,nb);

/*           Compute the TZ factorization of the current block */
/*           A(i:i+ib-1,i:n) */

	    i__3 = *n - i__ + 1;
	    i__4 = *n - *m;
	    dlatrz_(&ib, &i__3, &i__4, &a[i__ + i__ * a_dim1], lda, &tau[i__],
		     &work[1]);
	    if (i__ > 1) {

/*              Form the triangular factor of the block reflector */
/*              H = H(i+ib-1) . . . H(i+1) H(i) */

		i__3 = *n - *m;
		dlarzt_("Backward", "Rowwise", &i__3, &ib, &a[i__ + m1 *
			a_dim1], lda, &tau[i__], &work[1], &ldwork);

/*              Apply H to A(1:i-1,i:n) from the right */

		i__3 = i__ - 1;
		i__4 = *n - i__ + 1;
		i__5 = *n - *m;
		dlarzb_("Right", "No transpose", "Backward", "Rowwise", &i__3,
			 &i__4, &ib, &i__5, &a[i__ + m1 * a_dim1], lda, &work[
			1], &ldwork, &a[i__ * a_dim1 + 1], lda, &work[ib + 1],
			 &ldwork)
			;
	    }
/* L20: */
	}
	mu = i__ + nb - 1;
    } else {
	mu = *m;
    }

/*     Use unblocked code to factor the last or only block */

    if (mu > 0) {
	i__2 = *n - *m;
	dlatrz_(&mu, n, &i__2, &a[a_offset], lda, &tau[1], &work[1]);
    }

    work[1] = (doublereal) lwkopt;

    return 0;

/*     End of DTZRZF */

} /* dtzrzf_ */

integer ieeeck_(integer *ispec, real *zero, real *one)
{
    /* System generated locals */
    integer ret_val;

    /* Local variables */
    real nan1, nan2, nan3, nan4, nan5, nan6, neginf, posinf, negzro, newzro;


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  IEEECK is called from the ILAENV to verify that Infinity and */
/*  possibly NaN arithmetic is safe (i.e. will not trap). */

/*  Arguments */
/*  ========= */

/*  ISPEC   (input) INTEGER */
/*          Specifies whether to test just for inifinity arithmetic */
/*          or whether to test for infinity and NaN arithmetic. */
/*          = 0: Verify infinity arithmetic only. */
/*          = 1: Verify infinity and NaN arithmetic. */

/*  ZERO    (input) REAL */
/*          Must contain the value 0.0 */
/*          This is passed to prevent the compiler from optimizing */
/*          away this code. */

/*  ONE     (input) REAL */
/*          Must contain the value 1.0 */
/*          This is passed to prevent the compiler from optimizing */
/*          away this code. */

/*  RETURN VALUE:  INTEGER */
/*          = 0:  Arithmetic failed to produce the correct answers */
/*          = 1:  Arithmetic produced the correct answers */

/*     .. Local Scalars .. */
/*     .. */
/*     .. Executable Statements .. */
    ret_val = 1;

    posinf = *one / *zero;
    if (posinf <= *one) {
	ret_val = 0;
	return ret_val;
    }

    neginf = -(*one) / *zero;
    if (neginf >= *zero) {
	ret_val = 0;
	return ret_val;
    }

    negzro = *one / (neginf + *one);
    if (negzro != *zero) {
	ret_val = 0;
	return ret_val;
    }

    neginf = *one / negzro;
    if (neginf >= *zero) {
	ret_val = 0;
	return ret_val;
    }

    newzro = negzro + *zero;
    if (newzro != *zero) {
	ret_val = 0;
	return ret_val;
    }

    posinf = *one / newzro;
    if (posinf <= *one) {
	ret_val = 0;
	return ret_val;
    }

    neginf *= posinf;
    if (neginf >= *zero) {
	ret_val = 0;
	return ret_val;
    }

    posinf *= posinf;
    if (posinf <= *one) {
	ret_val = 0;
	return ret_val;
    }




/*     Return if we were only asked to check infinity arithmetic */

    if (*ispec == 0) {
	return ret_val;
    }

    nan1 = posinf + neginf;

    nan2 = posinf / neginf;

    nan3 = posinf / posinf;

    nan4 = posinf * *zero;

    nan5 = neginf * negzro;

    nan6 = nan5 * 0.f;

    if (nan1 == nan1) {
	ret_val = 0;
	return ret_val;
    }

    if (nan2 == nan2) {
	ret_val = 0;
	return ret_val;
    }

    if (nan3 == nan3) {
	ret_val = 0;
	return ret_val;
    }

    if (nan4 == nan4) {
	ret_val = 0;
	return ret_val;
    }

    if (nan5 == nan5) {
	ret_val = 0;
	return ret_val;
    }

    if (nan6 == nan6) {
	ret_val = 0;
	return ret_val;
    }

    return ret_val;
} /* ieeeck_ */

integer iladlc_(integer *m, integer *n, doublereal *a, integer *lda)
{
    /* System generated locals */
    integer a_dim1, a_offset, ret_val, i__1;

    /* Local variables */
    integer i__;


/*  -- LAPACK auxiliary routine (version 3.2.1)                        -- */

/*  -- April 2009                                                      -- */

/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  ILADLC scans A for its last non-zero column. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A. */

/*  A       (input) DOUBLE PRECISION array, dimension (LDA,N) */
/*          The m by n matrix A. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A. LDA >= max(1,M). */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Quick test for the common case where one corner is non-zero. */
    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    if (*n == 0) {
	ret_val = *n;
    } else if (a[*n * a_dim1 + 1] != 0. || a[*m + *n * a_dim1] != 0.) {
	ret_val = *n;
    } else {
/*     Now scan each column from the end, returning with the first non-zero. */
	for (ret_val = *n; ret_val >= 1; --ret_val) {
	    i__1 = *m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		if (a[i__ + ret_val * a_dim1] != 0.) {
		    return ret_val;
		}
	    }
	}
    }
    return ret_val;
} /* iladlc_ */

integer iladlr_(integer *m, integer *n, doublereal *a, integer *lda)
{
    /* System generated locals */
    integer a_dim1, a_offset, ret_val, i__1;

    /* Local variables */
    integer i__, j;


/*  -- LAPACK auxiliary routine (version 3.2.1)                        -- */

/*  -- April 2009                                                      -- */

/*  -- LAPACK is a software package provided by Univ. of Tennessee,    -- */
/*  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..-- */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  ILADLR scans A for its last non-zero row. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix A. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix A. */

/*  A       (input) DOUBLE PRECISION array, dimension (LDA,N) */
/*          The m by n matrix A. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array A. LDA >= max(1,M). */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Quick test for the common case where one corner is non-zero. */
    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    if (*m == 0) {
	ret_val = *m;
    } else if (a[*m + a_dim1] != 0. || a[*m + *n * a_dim1] != 0.) {
	ret_val = *m;
    } else {
/*     Scan up each column tracking the last zero row seen. */
	ret_val = 0;
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    for (i__ = *m; i__ >= 1; --i__) {
		if (a[i__ + j * a_dim1] != 0.) {
		    break;
		}
	    }
	    ret_val = max(ret_val,i__);
	}
    }
    return ret_val;
} /* iladlr_ */

integer ilaenv_(integer *ispec, char *name__, char *opts, integer *n1,
	integer *n2, integer *n3, integer *n4)
{
    /* Table of constant values */

    integer c__1 = 1;
    real c_b163 = 0.f;
    real c_b164 = 1.f;
    integer c__0 = 0;

    /* System generated locals */
    integer ret_val;

    /* Local variables */
    integer i__;
    char c1[1], c2[2], c3[3], c4[2];
    integer ic, nb, iz, nx;
    logical cname;
    integer nbmin;
    logical sname;
    extern integer ieeeck_(integer *, real *, real *);
    char subnam[6];
    extern integer iparmq_(integer *, char *, char *, integer *, integer *,
	    integer *, integer *);

    ftnlen name_len, opts_len;

    name_len = (ftnlen)strlen (name__);
    opts_len = (ftnlen)strlen (opts);

/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     January 2007 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  ILAENV is called from the LAPACK routines to choose problem-dependent */
/*  parameters for the local environment.  See ISPEC for a description of */
/*  the parameters. */

/*  ILAENV returns an INTEGER */
/*  if ILAENV >= 0: ILAENV returns the value of the parameter specified by ISPEC */
/*  if ILAENV < 0:  if ILAENV = -k, the k-th argument had an illegal value. */

/*  This version provides a set of parameters which should give good, */
/*  but not optimal, performance on many of the currently available */
/*  computers.  Users are encouraged to modify this subroutine to set */
/*  the tuning parameters for their particular machine using the option */
/*  and problem size information in the arguments. */

/*  This routine will not function correctly if it is converted to all */
/*  lower case.  Converting it to all upper case is allowed. */

/*  Arguments */
/*  ========= */

/*  ISPEC   (input) INTEGER */
/*          Specifies the parameter to be returned as the value of */
/*          ILAENV. */
/*          = 1: the optimal blocksize; if this value is 1, an unblocked */
/*               algorithm will give the best performance. */
/*          = 2: the minimum block size for which the block routine */
/*               should be used; if the usable block size is less than */
/*               this value, an unblocked routine should be used. */
/*          = 3: the crossover point (in a block routine, for N less */
/*               than this value, an unblocked routine should be used) */
/*          = 4: the number of shifts, used in the nonsymmetric */
/*               eigenvalue routines (DEPRECATED) */
/*          = 5: the minimum column dimension for blocking to be used; */
/*               rectangular blocks must have dimension at least k by m, */
/*               where k is given by ILAENV(2,...) and m by ILAENV(5,...) */
/*          = 6: the crossover point for the SVD (when reducing an m by n */
/*               matrix to bidiagonal form, if max(m,n)/min(m,n) exceeds */
/*               this value, a QR factorization is used first to reduce */
/*               the matrix to a triangular form.) */
/*          = 7: the number of processors */
/*          = 8: the crossover point for the multishift QR method */
/*               for nonsymmetric eigenvalue problems (DEPRECATED) */
/*          = 9: maximum size of the subproblems at the bottom of the */
/*               computation tree in the divide-and-conquer algorithm */
/*               (used by xGELSD and xGESDD) */
/*          =10: ieee NaN arithmetic can be trusted not to trap */
/*          =11: infinity arithmetic can be trusted not to trap */
/*          12 <= ISPEC <= 16: */
/*               xHSEQR or one of its subroutines, */
/*               see IPARMQ for detailed explanation */

/*  NAME    (input) CHARACTER*(*) */
/*          The name of the calling subroutine, in either upper case or */
/*          lower case. */

/*  OPTS    (input) CHARACTER*(*) */
/*          The character options to the subroutine NAME, concatenated */
/*          into a single character string.  For example, UPLO = 'U', */
/*          TRANS = 'T', and DIAG = 'N' for a triangular routine would */
/*          be specified as OPTS = 'UTN'. */

/*  N1      (input) INTEGER */
/*  N2      (input) INTEGER */
/*  N3      (input) INTEGER */
/*  N4      (input) INTEGER */
/*          Problem dimensions for the subroutine NAME; these may not all */
/*          be required. */

/*  Further Details */
/*  =============== */

/*  The following conventions have been used when calling ILAENV from the */
/*  LAPACK routines: */
/*  1)  OPTS is a concatenation of all of the character options to */
/*      subroutine NAME, in the same order that they appear in the */
/*      argument list for NAME, even if they are not used in determining */
/*      the value of the parameter specified by ISPEC. */
/*  2)  The problem dimensions N1, N2, N3, N4 are specified in the order */
/*      that they appear in the argument list for NAME.  N1 is used */
/*      first, N2 second, and so on, and unused problem dimensions are */
/*      passed a value of -1. */
/*  3)  The parameter value returned by ILAENV is checked for validity in */
/*      the calling subroutine.  For example, ILAENV is used to retrieve */
/*      the optimal blocksize for STRTRI as follows: */

/*      NB = ILAENV( 1, 'STRTRI', UPLO // DIAG, N, -1, -1, -1 ) */
/*      IF( NB.LE.1 ) NB = MAX( 1, N ) */

/*  ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    switch (*ispec) {
	case 1:  goto L10;
	case 2:  goto L10;
	case 3:  goto L10;
	case 4:  goto L80;
	case 5:  goto L90;
	case 6:  goto L100;
	case 7:  goto L110;
	case 8:  goto L120;
	case 9:  goto L130;
	case 10:  goto L140;
	case 11:  goto L150;
	case 12:  goto L160;
	case 13:  goto L160;
	case 14:  goto L160;
	case 15:  goto L160;
	case 16:  goto L160;
    }

/*     Invalid value for ISPEC */

    ret_val = -1;
    return ret_val;

L10:

/*     Convert NAME to upper case if the first character is lower case. */

    ret_val = 1;
    s_copy(subnam, name__, (ftnlen)1, name_len);
    ic = *(unsigned char *)subnam;
    iz = 'Z';
    if (iz == 90 || iz == 122) {

/*        ASCII character set */

	if (ic >= 97 && ic <= 122) {
	    *(unsigned char *)subnam = (char) (ic - 32);
	    for (i__ = 2; i__ <= 6; ++i__) {
		ic = *(unsigned char *)&subnam[i__ - 1];
		if (ic >= 97 && ic <= 122) {
		    *(unsigned char *)&subnam[i__ - 1] = (char) (ic - 32);
		}
/* L20: */
	    }
	}

    } else if (iz == 233 || iz == 169) {

/*        EBCDIC character set */

	if ((ic >= 129 && ic <= 137) || (ic >= 145 && ic <= 153) || (ic >= 162 &&
		ic <= 169)) {
	    *(unsigned char *)subnam = (char) (ic + 64);
	    for (i__ = 2; i__ <= 6; ++i__) {
		ic = *(unsigned char *)&subnam[i__ - 1];
		if ((ic >= 129 && ic <= 137) || (ic >= 145 && ic <= 153) || (ic >=
			162 && ic <= 169)) {
		    *(unsigned char *)&subnam[i__ - 1] = (char) (ic + 64);
		}
/* L30: */
	    }
	}

    } else if (iz == 218 || iz == 250) {

/*        Prime machines:  ASCII+128 */

	if (ic >= 225 && ic <= 250) {
	    *(unsigned char *)subnam = (char) (ic - 32);
	    for (i__ = 2; i__ <= 6; ++i__) {
		ic = *(unsigned char *)&subnam[i__ - 1];
		if (ic >= 225 && ic <= 250) {
		    *(unsigned char *)&subnam[i__ - 1] = (char) (ic - 32);
		}
/* L40: */
	    }
	}
    }

    *(unsigned char *)c1 = *(unsigned char *)subnam;
    sname = *(unsigned char *)c1 == 'S' || *(unsigned char *)c1 == 'D';
    cname = *(unsigned char *)c1 == 'C' || *(unsigned char *)c1 == 'Z';
    if (! (cname || sname)) {
	return ret_val;
    }
    s_copy(c2, subnam + 1, (ftnlen)1, (ftnlen)2);
    s_copy(c3, subnam + 3, (ftnlen)1, (ftnlen)3);
    s_copy(c4, c3 + 1, (ftnlen)1, (ftnlen)2);

    switch (*ispec) {
	case 1:  goto L50;
	case 2:  goto L60;
	case 3:  goto L70;
    }

L50:

/*     ISPEC = 1:  block size */

/*     In these examples, separate code is provided for setting NB for */
/*     real and complex.  We assume that NB will take the same value in */
/*     single or double precision. */

    nb = 1;

    if (s_cmp(c2, "GE", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "TRF", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nb = 64;
	    } else {
		nb = 64;
	    }
	} else if (s_cmp(c3, "QRF", (ftnlen)1, (ftnlen)3) == 0 || s_cmp(c3,
		"RQF", (ftnlen)1, (ftnlen)3) == 0 || s_cmp(c3, "LQF", (ftnlen)
		1, (ftnlen)3) == 0 || s_cmp(c3, "QLF", (ftnlen)1, (ftnlen)3)
		== 0) {
	    if (sname) {
		nb = 32;
	    } else {
		nb = 32;
	    }
	} else if (s_cmp(c3, "HRD", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nb = 32;
	    } else {
		nb = 32;
	    }
	} else if (s_cmp(c3, "BRD", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nb = 32;
	    } else {
		nb = 32;
	    }
	} else if (s_cmp(c3, "TRI", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nb = 64;
	    } else {
		nb = 64;
	    }
	}
    } else if (s_cmp(c2, "PO", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "TRF", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nb = 64;
	    } else {
		nb = 64;
	    }
	}
    } else if (s_cmp(c2, "SY", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "TRF", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nb = 64;
	    } else {
		nb = 64;
	    }
	} else if (sname && s_cmp(c3, "TRD", (ftnlen)1, (ftnlen)3) == 0) {
	    nb = 32;
	} else if (sname && s_cmp(c3, "GST", (ftnlen)1, (ftnlen)3) == 0) {
	    nb = 64;
	}
    } else if (cname && s_cmp(c2, "HE", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "TRF", (ftnlen)1, (ftnlen)3) == 0) {
	    nb = 64;
	} else if (s_cmp(c3, "TRD", (ftnlen)1, (ftnlen)3) == 0) {
	    nb = 32;
	} else if (s_cmp(c3, "GST", (ftnlen)1, (ftnlen)3) == 0) {
	    nb = 64;
	}
    } else if (sname && s_cmp(c2, "OR", (ftnlen)1, (ftnlen)2) == 0) {
	if (*(unsigned char *)c3 == 'G') {
	    if (s_cmp(c4, "QR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "RQ",
		    (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "LQ", (ftnlen)1, (
		    ftnlen)2) == 0 || s_cmp(c4, "QL", (ftnlen)1, (ftnlen)2) ==
		     0 || s_cmp(c4, "HR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(
		    c4, "TR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "BR", (
		    ftnlen)1, (ftnlen)2) == 0) {
		nb = 32;
	    }
	} else if (*(unsigned char *)c3 == 'M') {
	    if (s_cmp(c4, "QR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "RQ",
		    (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "LQ", (ftnlen)1, (
		    ftnlen)2) == 0 || s_cmp(c4, "QL", (ftnlen)1, (ftnlen)2) ==
		     0 || s_cmp(c4, "HR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(
		    c4, "TR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "BR", (
		    ftnlen)1, (ftnlen)2) == 0) {
		nb = 32;
	    }
	}
    } else if (cname && s_cmp(c2, "UN", (ftnlen)1, (ftnlen)2) == 0) {
	if (*(unsigned char *)c3 == 'G') {
	    if (s_cmp(c4, "QR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "RQ",
		    (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "LQ", (ftnlen)1, (
		    ftnlen)2) == 0 || s_cmp(c4, "QL", (ftnlen)1, (ftnlen)2) ==
		     0 || s_cmp(c4, "HR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(
		    c4, "TR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "BR", (
		    ftnlen)1, (ftnlen)2) == 0) {
		nb = 32;
	    }
	} else if (*(unsigned char *)c3 == 'M') {
	    if (s_cmp(c4, "QR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "RQ",
		    (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "LQ", (ftnlen)1, (
		    ftnlen)2) == 0 || s_cmp(c4, "QL", (ftnlen)1, (ftnlen)2) ==
		     0 || s_cmp(c4, "HR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(
		    c4, "TR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "BR", (
		    ftnlen)1, (ftnlen)2) == 0) {
		nb = 32;
	    }
	}
    } else if (s_cmp(c2, "GB", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "TRF", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		if (*n4 <= 64) {
		    nb = 1;
		} else {
		    nb = 32;
		}
	    } else {
		if (*n4 <= 64) {
		    nb = 1;
		} else {
		    nb = 32;
		}
	    }
	}
    } else if (s_cmp(c2, "PB", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "TRF", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		if (*n2 <= 64) {
		    nb = 1;
		} else {
		    nb = 32;
		}
	    } else {
		if (*n2 <= 64) {
		    nb = 1;
		} else {
		    nb = 32;
		}
	    }
	}
    } else if (s_cmp(c2, "TR", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "TRI", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nb = 64;
	    } else {
		nb = 64;
	    }
	}
    } else if (s_cmp(c2, "LA", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "UUM", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nb = 64;
	    } else {
		nb = 64;
	    }
	}
    } else if (sname && s_cmp(c2, "ST", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "EBZ", (ftnlen)1, (ftnlen)3) == 0) {
	    nb = 1;
	}
    }
    ret_val = nb;
    return ret_val;

L60:

/*     ISPEC = 2:  minimum block size */

    nbmin = 2;
    if (s_cmp(c2, "GE", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "QRF", (ftnlen)1, (ftnlen)3) == 0 || s_cmp(c3, "RQF", (
		ftnlen)1, (ftnlen)3) == 0 || s_cmp(c3, "LQF", (ftnlen)1, (
		ftnlen)3) == 0 || s_cmp(c3, "QLF", (ftnlen)1, (ftnlen)3) == 0)
		 {
	    if (sname) {
		nbmin = 2;
	    } else {
		nbmin = 2;
	    }
	} else if (s_cmp(c3, "HRD", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nbmin = 2;
	    } else {
		nbmin = 2;
	    }
	} else if (s_cmp(c3, "BRD", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nbmin = 2;
	    } else {
		nbmin = 2;
	    }
	} else if (s_cmp(c3, "TRI", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nbmin = 2;
	    } else {
		nbmin = 2;
	    }
	}
    } else if (s_cmp(c2, "SY", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "TRF", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nbmin = 8;
	    } else {
		nbmin = 8;
	    }
	} else if (sname && s_cmp(c3, "TRD", (ftnlen)1, (ftnlen)3) == 0) {
	    nbmin = 2;
	}
    } else if (cname && s_cmp(c2, "HE", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "TRD", (ftnlen)1, (ftnlen)3) == 0) {
	    nbmin = 2;
	}
    } else if (sname && s_cmp(c2, "OR", (ftnlen)1, (ftnlen)2) == 0) {
	if (*(unsigned char *)c3 == 'G') {
	    if (s_cmp(c4, "QR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "RQ",
		    (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "LQ", (ftnlen)1, (
		    ftnlen)2) == 0 || s_cmp(c4, "QL", (ftnlen)1, (ftnlen)2) ==
		     0 || s_cmp(c4, "HR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(
		    c4, "TR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "BR", (
		    ftnlen)1, (ftnlen)2) == 0) {
		nbmin = 2;
	    }
	} else if (*(unsigned char *)c3 == 'M') {
	    if (s_cmp(c4, "QR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "RQ",
		    (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "LQ", (ftnlen)1, (
		    ftnlen)2) == 0 || s_cmp(c4, "QL", (ftnlen)1, (ftnlen)2) ==
		     0 || s_cmp(c4, "HR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(
		    c4, "TR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "BR", (
		    ftnlen)1, (ftnlen)2) == 0) {
		nbmin = 2;
	    }
	}
    } else if (cname && s_cmp(c2, "UN", (ftnlen)1, (ftnlen)2) == 0) {
	if (*(unsigned char *)c3 == 'G') {
	    if (s_cmp(c4, "QR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "RQ",
		    (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "LQ", (ftnlen)1, (
		    ftnlen)2) == 0 || s_cmp(c4, "QL", (ftnlen)1, (ftnlen)2) ==
		     0 || s_cmp(c4, "HR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(
		    c4, "TR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "BR", (
		    ftnlen)1, (ftnlen)2) == 0) {
		nbmin = 2;
	    }
	} else if (*(unsigned char *)c3 == 'M') {
	    if (s_cmp(c4, "QR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "RQ",
		    (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "LQ", (ftnlen)1, (
		    ftnlen)2) == 0 || s_cmp(c4, "QL", (ftnlen)1, (ftnlen)2) ==
		     0 || s_cmp(c4, "HR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(
		    c4, "TR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "BR", (
		    ftnlen)1, (ftnlen)2) == 0) {
		nbmin = 2;
	    }
	}
    }
    ret_val = nbmin;
    return ret_val;

L70:

/*     ISPEC = 3:  crossover point */

    nx = 0;
    if (s_cmp(c2, "GE", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "QRF", (ftnlen)1, (ftnlen)3) == 0 || s_cmp(c3, "RQF", (
		ftnlen)1, (ftnlen)3) == 0 || s_cmp(c3, "LQF", (ftnlen)1, (
		ftnlen)3) == 0 || s_cmp(c3, "QLF", (ftnlen)1, (ftnlen)3) == 0)
		 {
	    if (sname) {
		nx = 128;
	    } else {
		nx = 128;
	    }
	} else if (s_cmp(c3, "HRD", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nx = 128;
	    } else {
		nx = 128;
	    }
	} else if (s_cmp(c3, "BRD", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nx = 128;
	    } else {
		nx = 128;
	    }
	}
    } else if (s_cmp(c2, "SY", (ftnlen)1, (ftnlen)2) == 0) {
	if (sname && s_cmp(c3, "TRD", (ftnlen)1, (ftnlen)3) == 0) {
	    nx = 32;
	}
    } else if (cname && s_cmp(c2, "HE", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "TRD", (ftnlen)1, (ftnlen)3) == 0) {
	    nx = 32;
	}
    } else if (sname && s_cmp(c2, "OR", (ftnlen)1, (ftnlen)2) == 0) {
	if (*(unsigned char *)c3 == 'G') {
	    if (s_cmp(c4, "QR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "RQ",
		    (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "LQ", (ftnlen)1, (
		    ftnlen)2) == 0 || s_cmp(c4, "QL", (ftnlen)1, (ftnlen)2) ==
		     0 || s_cmp(c4, "HR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(
		    c4, "TR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "BR", (
		    ftnlen)1, (ftnlen)2) == 0) {
		nx = 128;
	    }
	}
    } else if (cname && s_cmp(c2, "UN", (ftnlen)1, (ftnlen)2) == 0) {
	if (*(unsigned char *)c3 == 'G') {
	    if (s_cmp(c4, "QR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "RQ",
		    (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "LQ", (ftnlen)1, (
		    ftnlen)2) == 0 || s_cmp(c4, "QL", (ftnlen)1, (ftnlen)2) ==
		     0 || s_cmp(c4, "HR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(
		    c4, "TR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "BR", (
		    ftnlen)1, (ftnlen)2) == 0) {
		nx = 128;
	    }
	}
    }
    ret_val = nx;
    return ret_val;

L80:

/*     ISPEC = 4:  number of shifts (used by xHSEQR) */

    ret_val = 6;
    return ret_val;

L90:

/*     ISPEC = 5:  minimum column dimension (not used) */

    ret_val = 2;
    return ret_val;

L100:

/*     ISPEC = 6:  crossover point for SVD (used by xGELSS and xGESVD) */

    ret_val = (integer) ((real) min(*n1,*n2) * 1.6f);
    return ret_val;

L110:

/*     ISPEC = 7:  number of processors (not used) */

    ret_val = 1;
    return ret_val;

L120:

/*     ISPEC = 8:  crossover point for multishift (used by xHSEQR) */

    ret_val = 50;
    return ret_val;

L130:

/*     ISPEC = 9:  maximum size of the subproblems at the bottom of the */
/*                 computation tree in the divide-and-conquer algorithm */
/*                 (used by xGELSD and xGESDD) */

    ret_val = 25;
    return ret_val;

L140:

/*     ISPEC = 10: ieee NaN arithmetic can be trusted not to trap */

/*     ILAENV = 0 */
    ret_val = 1;
    if (ret_val == 1) {
	ret_val = ieeeck_(&c__1, &c_b163, &c_b164);
    }
    return ret_val;

L150:

/*     ISPEC = 11: infinity arithmetic can be trusted not to trap */

/*     ILAENV = 0 */
    ret_val = 1;
    if (ret_val == 1) {
	ret_val = ieeeck_(&c__0, &c_b163, &c_b164);
    }
    return ret_val;

L160:

/*     12 <= ISPEC <= 16: xHSEQR or one of its subroutines. */

    ret_val = iparmq_(ispec, name__, opts, n1, n2, n3, n4)
	    ;
    return ret_val;

/*     End of ILAENV */

} /* ilaenv_ */

integer iparmq_(integer *ispec, char *name__, char *opts, integer *n, integer
	*ilo, integer *ihi, integer *lwork)
{
    /* System generated locals */
    integer ret_val, i__1, i__2;
    real r__1;

    /* Local variables */
    integer nh, ns;


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */

/*  Purpose */
/*  ======= */

/*       This program sets problem and machine dependent parameters */
/*       useful for xHSEQR and its subroutines. It is called whenever */
/*       ILAENV is called with 12 <= ISPEC <= 16 */

/*  Arguments */
/*  ========= */

/*       ISPEC  (input) integer scalar */
/*              ISPEC specifies which tunable parameter IPARMQ should */
/*              return. */

/*              ISPEC=12: (INMIN)  Matrices of order nmin or less */
/*                        are sent directly to xLAHQR, the implicit */
/*                        double shift QR algorithm.  NMIN must be */
/*                        at least 11. */

/*              ISPEC=13: (INWIN)  Size of the deflation window. */
/*                        This is best set greater than or equal to */
/*                        the number of simultaneous shifts NS. */
/*                        Larger matrices benefit from larger deflation */
/*                        windows. */

/*              ISPEC=14: (INIBL) Determines when to stop nibbling and */
/*                        invest in an (expensive) multi-shift QR sweep. */
/*                        If the aggressive early deflation subroutine */
/*                        finds LD converged eigenvalues from an order */
/*                        NW deflation window and LD.GT.(NW*NIBBLE)/100, */
/*                        then the next QR sweep is skipped and early */
/*                        deflation is applied immediately to the */
/*                        remaining active diagonal block.  Setting */
/*                        IPARMQ(ISPEC=14) = 0 causes TTQRE to skip a */
/*                        multi-shift QR sweep whenever early deflation */
/*                        finds a converged eigenvalue.  Setting */
/*                        IPARMQ(ISPEC=14) greater than or equal to 100 */
/*                        prevents TTQRE from skipping a multi-shift */
/*                        QR sweep. */

/*              ISPEC=15: (NSHFTS) The number of simultaneous shifts in */
/*                        a multi-shift QR iteration. */

/*              ISPEC=16: (IACC22) IPARMQ is set to 0, 1 or 2 with the */
/*                        following meanings. */
/*                        0:  During the multi-shift QR sweep, */
/*                            xLAQR5 does not accumulate reflections and */
/*                            does not use matrix-matrix multiply to */
/*                            update the far-from-diagonal matrix */
/*                            entries. */
/*                        1:  During the multi-shift QR sweep, */
/*                            xLAQR5 and/or xLAQRaccumulates reflections and uses */
/*                            matrix-matrix multiply to update the */
/*                            far-from-diagonal matrix entries. */
/*                        2:  During the multi-shift QR sweep. */
/*                            xLAQR5 accumulates reflections and takes */
/*                            advantage of 2-by-2 block structure during */
/*                            matrix-matrix multiplies. */
/*                        (If xTRMM is slower than xGEMM, then */
/*                        IPARMQ(ISPEC=16)=1 may be more efficient than */
/*                        IPARMQ(ISPEC=16)=2 despite the greater level of */
/*                        arithmetic work implied by the latter choice.) */

/*       NAME    (input) character string */
/*               Name of the calling subroutine */

/*       OPTS    (input) character string */
/*               This is a concatenation of the string arguments to */
/*               TTQRE. */

/*       N       (input) integer scalar */
/*               N is the order of the Hessenberg matrix H. */

/*       ILO     (input) INTEGER */
/*       IHI     (input) INTEGER */
/*               It is assumed that H is already upper triangular */
/*               in rows and columns 1:ILO-1 and IHI+1:N. */

/*       LWORK   (input) integer scalar */
/*               The amount of workspace available. */

/*  Further Details */
/*  =============== */

/*       Little is known about how best to choose these parameters. */
/*       It is possible to use different values of the parameters */
/*       for each of CHSEQR, DHSEQR, SHSEQR and ZHSEQR. */

/*       It is probably best to choose different parameters for */
/*       different matrices and different parameters at different */
/*       times during the iteration, but this has not been */
/*       implemented --- yet. */


/*       The best choices of most of the parameters depend */
/*       in an ill-understood way on the relative execution */
/*       rate of xLAQR3 and xLAQR5 and on the nature of each */
/*       particular eigenvalue problem.  Experiment may be the */
/*       only practical way to determine which choices are most */
/*       effective. */

/*       Following is a list of default values supplied by IPARMQ. */
/*       These defaults may be adjusted in order to attain better */
/*       performance in any particular computational environment. */

/*       IPARMQ(ISPEC=12) The xLAHQR vs xLAQR0 crossover point. */
/*                        Default: 75. (Must be at least 11.) */

/*       IPARMQ(ISPEC=13) Recommended deflation window size. */
/*                        This depends on ILO, IHI and NS, the */
/*                        number of simultaneous shifts returned */
/*                        by IPARMQ(ISPEC=15).  The default for */
/*                        (IHI-ILO+1).LE.500 is NS.  The default */
/*                        for (IHI-ILO+1).GT.500 is 3*NS/2. */

/*       IPARMQ(ISPEC=14) Nibble crossover point.  Default: 14. */

/*       IPARMQ(ISPEC=15) Number of simultaneous shifts, NS. */
/*                        a multi-shift QR iteration. */

/*                        If IHI-ILO+1 is ... */

/*                        greater than      ...but less    ... the */
/*                        or equal to ...      than        default is */

/*                                0               30       NS =   2+ */
/*                               30               60       NS =   4+ */
/*                               60              150       NS =  10 */
/*                              150              590       NS =  ** */
/*                              590             3000       NS =  64 */
/*                             3000             6000       NS = 128 */
/*                             6000             infinity   NS = 256 */

/*                    (+)  By default matrices of this order are */
/*                         passed to the implicit double shift routine */
/*                         xLAHQR.  See IPARMQ(ISPEC=12) above.   These */
/*                         values of NS are used only in case of a rare */
/*                         xLAHQR failure. */

/*                    (**) The asterisks (**) indicate an ad-hoc */
/*                         function increasing from 10 to 64. */

/*       IPARMQ(ISPEC=16) Select structured matrix multiply. */
/*                        (See ISPEC=16 above for details.) */
/*                        Default: 3. */

/*     ================================================================ */
/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */
    if (*ispec == 15 || *ispec == 13 || *ispec == 16) {

/*        ==== Set the number simultaneous shifts ==== */

	nh = *ihi - *ilo + 1;
	ns = 2;
	if (nh >= 30) {
	    ns = 4;
	}
	if (nh >= 60) {
	    ns = 10;
	}
	if (nh >= 150) {
/* Computing MAX */
	    r__1 = log((real) nh) / log(2.f);
	    i__1 = 10, i__2 = nh / i_nint(&r__1);
	    ns = max(i__1,i__2);
	}
	if (nh >= 590) {
	    ns = 64;
	}
	if (nh >= 3000) {
	    ns = 128;
	}
	if (nh >= 6000) {
	    ns = 256;
	}
/* Computing MAX */
	i__1 = 2, i__2 = ns - ns % 2;
	ns = max(i__1,i__2);
    }

    if (*ispec == 12) {


/*        ===== Matrices of order smaller than NMIN get sent */
/*        .     to xLAHQR, the classic double shift algorithm. */
/*        .     This must be at least 11. ==== */

	ret_val = 75;

    } else if (*ispec == 14) {

/*        ==== INIBL: skip a multi-shift qr iteration and */
/*        .    whenever aggressive early deflation finds */
/*        .    at least (NIBBLE*(window size)/100) deflations. ==== */

	ret_val = 14;

    } else if (*ispec == 15) {

/*        ==== NSHFTS: The number of simultaneous shifts ===== */

	ret_val = ns;

    } else if (*ispec == 13) {

/*        ==== NW: deflation window size.  ==== */

	if (nh <= 500) {
	    ret_val = ns;
	} else {
	    ret_val = ns * 3 / 2;
	}

    } else if (*ispec == 16) {

/*        ==== IACC22: Whether to accumulate reflections */
/*        .     before updating the far-from-diagonal elements */
/*        .     and whether to use 2-by-2 block structure while */
/*        .     doing it.  A small amount of work could be saved */
/*        .     by making this choice dependent also upon the */
/*        .     NH=IHI-ILO+1. */

	ret_val = 0;
	if (ns >= 14) {
	    ret_val = 1;
	}
	if (ns >= 14) {
	    ret_val = 2;
	}

    } else {
/*        ===== invalid value of ispec ===== */
	ret_val = -1;

    }

/*     ==== End of IPARMQ ==== */

    return ret_val;
} /* iparmq_ */

logical lsame_(char *ca, char *cb)
{
    /* System generated locals */
    logical ret_val;

    /* Local variables */
    integer inta, intb, zcode;


/*  -- LAPACK auxiliary routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  LSAME returns .TRUE. if CA is the same letter as CB regardless of */
/*  case. */

/*  Arguments */
/*  ========= */

/*  CA      (input) CHARACTER*1 */

/*  CB      (input) CHARACTER*1 */
/*          CA and CB specify the single characters to be compared. */

/* ===================================================================== */

/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */

/*     Test if the characters are equal */

    ret_val = *(unsigned char *)ca == *(unsigned char *)cb;
    if (ret_val) {
	return ret_val;
    }

/*     Now test for equivalence if both characters are alphabetic. */

    zcode = 'Z';

/*     Use 'Z' rather than 'A' so that ASCII can be detected on Prime */
/*     machines, on which ICHAR returns a value with bit 8 set. */
/*     ICHAR('A') on Prime machines returns 193 which is the same as */
/*     ICHAR('A') on an EBCDIC machine. */

    inta = *(unsigned char *)ca;
    intb = *(unsigned char *)cb;

    if (zcode == 90 || zcode == 122) {

/*        ASCII is assumed - ZCODE is the ASCII code of either lower or */
/*        upper case 'Z'. */

	if (inta >= 97 && inta <= 122) {
	    inta += -32;
	}
	if (intb >= 97 && intb <= 122) {
	    intb += -32;
	}

    } else if (zcode == 233 || zcode == 169) {

/*        EBCDIC is assumed - ZCODE is the EBCDIC code of either lower or */
/*        upper case 'Z'. */

	if ((inta >= 129 && inta <= 137) || (inta >= 145 && inta <= 153) || (inta
		>= 162 && inta <= 169)) {
	    inta += 64;
	}
	if ((intb >= 129 && intb <= 137) || (intb >= 145 && intb <= 153) || (intb
		>= 162 && intb <= 169)) {
	    intb += 64;
	}

    } else if (zcode == 218 || zcode == 250) {

/*        ASCII is assumed, on Prime machines - ZCODE is the ASCII code */
/*        plus 128 of either lower or upper case 'Z'. */

	if (inta >= 225 && inta <= 250) {
	    inta += -32;
	}
	if (intb >= 225 && intb <= 250) {
	    intb += -32;
	}
    }
    ret_val = inta == intb;

/*     RETURN */

/*     End of LSAME */

    return ret_val;
} /* lsame_ */

/* Subroutine */ int xerbla_(char *srname, integer *info)
{

/*  -- LAPACK auxiliary routine (preliminary version) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  XERBLA  is an error handler for the LAPACK routines. */
/*  It is called by an LAPACK routine if an input parameter has an */
/*  invalid value.  A message is printed and execution stops. */

/*  Installers may consider modifying the STOP statement in order to */
/*  call system-specific exception-handling facilities. */

/*  Arguments */
/*  ========= */

/*  SRNAME  (input) CHARACTER*(*) */
/*          The name of the routine which called XERBLA. */

/*  INFO    (input) INTEGER */
/*          The position of the invalid parameter in the parameter list */
/*          of the calling routine. */

/* ===================================================================== */

/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

	printf("** On entry to %6s, parameter number %2i had an illegal value\n",
		srname, *info);


/*     End of XERBLA */

    return 0;
} /* xerbla_ */


/*
 * =============================================================================
 * Copyright (c) ESI ITI GmbH
 * All rights reserved.
 * =============================================================================
 */

#define _ABS_RHS_BORDER

#define a_ref(a_1,a_2) a[(a_2)*a_dim1 + a_1]
#define b_ref(a_1,a_2) b[(a_2)*b_dim1 + a_1]
#define ker_ref(a_1,a_2) ker[(a_2)*a_dim2 + a_1]

/* ITI Subroutine */ int iti_dtrsm_(char *side, char *uplo, char *transa, char *diag, integer *m, integer *n, doublereal *alpha, doublereal *a, integer *lda, doublereal *b, integer *ldb, integer *info)
{
    /* ITI: Is mostly identical to function dtrsm_. Differences are commented with "ITI". */
    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, i__1, i__2, i__3;
    /* Local variables */
    doublereal temp;
    integer i__, j, k;
    logical lside;
    integer nrowa;
    logical upper;
    logical nounit;

/*  Purpose
    =======
    DTRSM  solves one of the matrix equations
       op( A )*X = alpha*B,   or   X*op( A ) = alpha*B,
    where alpha is a scalar, X and B are m by n matrices, A is a unit, or
    non-unit,  upper or lower triangular matrix  and  op( A )  is one  of
       op( A ) = A   or   op( A ) = A'.
    The matrix X is overwritten on B.
    Parameters
    ==========
    SIDE   - CHARACTER*1.
             On entry, SIDE specifies whether op( A ) appears on the left
             or right of X as follows:
                SIDE = 'L' or 'l'   op( A )*X = alpha*B.
                SIDE = 'R' or 'r'   X*op( A ) = alpha*B.
             Unchanged on exit.
    UPLO   - CHARACTER*1.
             On entry, UPLO specifies whether the matrix A is an upper or
             lower triangular matrix as follows:
                UPLO = 'U' or 'u'   A is an upper triangular matrix.
                UPLO = 'L' or 'l'   A is a lower triangular matrix.
             Unchanged on exit.
    TRANSA - CHARACTER*1.
             On entry, TRANSA specifies the form of op( A ) to be used in
             the matrix multiplication as follows:
                TRANSA = 'N' or 'n'   op( A ) = A.
                TRANSA = 'T' or 't'   op( A ) = A'.
                TRANSA = 'C' or 'c'   op( A ) = A'.
             Unchanged on exit.
    DIAG   - CHARACTER*1.
             On entry, DIAG specifies whether or not A is unit triangular
             as follows:
                DIAG = 'U' or 'u'   A is assumed to be unit triangular.
                DIAG = 'N' or 'n'   A is not assumed to be unit triangular.
             Unchanged on exit.
    M      - INTEGER.
             On entry, M specifies the number of rows of B. M must be at
             least zero.
             Unchanged on exit.
    N      - INTEGER.
             On entry, N specifies the number of columns of B.  N must be
             at least zero.
             Unchanged on exit.
    ALPHA  - DOUBLE PRECISION.
             On entry,  ALPHA specifies the scalar  alpha. When  alpha is
             zero then  A is not referenced and  B need not be set before
             entry.
             Unchanged on exit.
    A      - DOUBLE PRECISION array of DIMENSION ( LDA, k ), where k is m
             when  SIDE = 'L' or 'l'  and is  n  when  SIDE = 'R' or 'r'.
             Before entry  with  UPLO = 'U' or 'u',  the  leading  k by k
             upper triangular part of the array  A must contain the upper
             triangular matrix  and the strictly lower triangular part of
             A is not referenced.
             Before entry  with  UPLO = 'L' or 'l',  the  leading  k by k
             lower triangular part of the array  A must contain the lower
             triangular matrix  and the strictly upper triangular part of
             A is not referenced.
             Note that when  DIAG = 'U' or 'u',  the diagonal elements of
             A  are not referenced either,  but are assumed to be  unity.
             Unchanged on exit.
    LDA    - INTEGER.
             On entry, LDA specifies the first dimension of A as declared
             in the calling (sub) program.  When  SIDE = 'L' or 'l'  then
             LDA  must be at least  __max( 1, m ),  when  SIDE = 'R' or 'r'
             then LDA must be at least __max( 1, n ).
             Unchanged on exit.
    B      - DOUBLE PRECISION array of DIMENSION ( LDB, n ).
             Before entry,  the leading  m by n part of the array  B must
             contain  the  right-hand  side  matrix  B,  and  on exit  is
             overwritten by the solution matrix  X.
    LDB    - INTEGER.
             On entry, LDB specifies the first dimension of B as declared
             in  the  calling  (sub)  program.   LDB  must  be  at  least
             __max( 1, m ).
             Unchanged on exit.
    Level 3 Blas routine.
    -- Written on 8-February-1989.
       Jack Dongarra, Argonne National Laboratory.
       Iain Duff, AERE Harwell.
       Jeremy Du Croz, Numerical Algorithms Group Ltd.
       Sven Hammarling, Numerical Algorithms Group Ltd.
       Test the input parameters.
       Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1 * 1;
    b -= b_offset;
    /* Function Body */
    lside = lsame_(side, "L");
    if (lside) {
        nrowa = *m;
    } else {
        nrowa = *n;
    }
    nounit = lsame_(diag, "N");
    upper = lsame_(uplo, "U");
    *info = 0;
    if (!lside && !lsame_(side, "R")) {
        *info = 1;
    } else if (!upper && !lsame_(uplo, "L")) {
        *info = 2;
    } else if (!lsame_(transa, "N") && !lsame_(transa, "T") && !lsame_(transa, "C")) {
        *info = 3;
    } else if (!lsame_(diag, "U") && !lsame_(diag, "N")) {
        *info = 4;
    } else if (*m < 0) {
        *info = 5;
    } else if (*n < 0) {
        *info = 6;
    } else if (*lda < max(1, nrowa)) {
        *info = 9;
    } else if (*ldb < max(1, *m)) {
        *info = 11;
    }
    if (*info != 0) {
        xerbla_("DTRSM ", info);
        return 0;
    }
/*     Quick return if possible. */
    if (*n == 0) {
        return 0;
    }
/*     And when  alpha.eq.zero. */
    if (*alpha == 0.) {
        i__1 = *n;
        for (j = 1; j <= i__1; ++j) {
            i__2 = *m;
            for (i__ = 1; i__ <= i__2; ++i__) {
                b_ref(i__, j) = 0.;
/* L10: */
            }
/* L20: */
        }
        return 0;
    }
/*     Start the operations. */
    if (lside) {
        if (lsame_(transa, "N")) {
/*           Form  B := alpha*inv( A )*B. */
            if (upper) {
                i__1 = *n;
                for (j = 1; j <= i__1; ++j) {
                    if (*alpha != 1.) {
                        i__2 = *m;
                        for (i__ = 1; i__ <= i__2; ++i__) {
                            b_ref(i__, j) = *alpha * b_ref(i__, j);
/* L30: */
                        }
                    }
                    for (k = *m; k >= 1; --k) {
                        if (b_ref(k, j) != 0.) {
                            if (nounit) {
                                if (a_ref(k, k) != 0.0)
                                    /* ITI */ b_ref(k, j) = b_ref(k, j) / a_ref(k, k);
                                else {
                                    /* ITI */
#if defined _ABS_RHS_BORDER
                                    if (fabs(b_ref(k, j)) > 4.44089209850063e-013)
#endif
                                    {
                                        *info = k;
                                    }
#if defined _ABS_RHS_BORDER
                                    b_ref(k, j) = 0.0;
#endif
                                }
                            }
                            i__2 = k - 1;
                            for (i__ = 1; i__ <= i__2; ++i__) {
                                b_ref(i__, j) = b_ref(i__, j) - b_ref(k, j) * a_ref(i__, k);
/* L40: */
                            }
                        }
/* L50: */
                    }
/* L60: */
                }
            } else {
                i__1 = *n;
                for (j = 1; j <= i__1; ++j) {
                    if (*alpha != 1.) {
                        i__2 = *m;
                        for (i__ = 1; i__ <= i__2; ++i__) {
                            b_ref(i__, j) = *alpha * b_ref(i__, j);
/* L70: */
                        }
                    }
                    i__2 = *m;
                    for (k = 1; k <= i__2; ++k) {
                        if (b_ref(k, j) != 0.) {
                            if (nounit) {
                                b_ref(k, j) = b_ref(k, j) / a_ref(k, k);
                            }
                            i__3 = *m;
                            for (i__ = k + 1; i__ <= i__3; ++i__) {
                                b_ref(i__, j) = b_ref(i__, j) - b_ref(k, j) * a_ref(i__, k);
/* L80: */
                            }
                        }
/* L90: */
                    }
/* L100: */
                }
            }
        } else {
/*           Form  B := alpha*inv( A' )*B. */
            if (upper) {
                i__1 = *n;
                for (j = 1; j <= i__1; ++j) {
                    i__2 = *m;
                    for (i__ = 1; i__ <= i__2; ++i__) {
                        temp = *alpha * b_ref(i__, j);
                        i__3 = i__ - 1;
                        for (k = 1; k <= i__3; ++k) {
                            temp -= a_ref(k, i__) * b_ref(k, j);
/* L110: */
                        }
                        /* ITI */
                        if (nounit && (a_ref(i__, i__) != 0.0)) {
                            temp /= a_ref(i__, i__);
                        }
                        /* ITI */
                        if (nounit && (a_ref(i__, i__) == 0.0) && (fabs(temp) > 10 * i__2 * DBL_EPSILON * fabs(*alpha * b_ref(i__, j)))) {
#if defined _ABS_RHS_BORDER
                            if (fabs(temp) > 4.44089209850063e-013)
#endif
                            {
                                *info = i__;
                            }
#if defined _ABS_RHS_BORDER
                            temp = 0.0;
#endif
                        }
                        b_ref(i__, j) = temp;
/* L120: */
                    }
/* L130: */
                }
            } else {
                i__1 = *n;
                for (j = 1; j <= i__1; ++j) {
                    for (i__ = *m; i__ >= 1; --i__) {
                        temp = *alpha * b_ref(i__, j);
                        i__2 = *m;
                        for (k = i__ + 1; k <= i__2; ++k) {
                            temp -= a_ref(k, i__) * b_ref(k, j);
/* L140: */
                        }
                        if (nounit) {
                            temp /= a_ref(i__, i__);
                        }
                        b_ref(i__, j) = temp;
/* L150: */
                    }
/* L160: */
                }
            }
        }
    } else {
        if (lsame_(transa, "N")) {
/*           Form  B := alpha*B*inv( A ). */
            if (upper) {
                i__1 = *n;
                for (j = 1; j <= i__1; ++j) {
                    if (*alpha != 1.) {
                        i__2 = *m;
                        for (i__ = 1; i__ <= i__2; ++i__) {
                            b_ref(i__, j) = *alpha * b_ref(i__, j);
/* L170: */
                        }
                    }
                    i__2 = j - 1;
                    for (k = 1; k <= i__2; ++k) {
                        if (a_ref(k, j) != 0.) {
                            i__3 = *m;
                            for (i__ = 1; i__ <= i__3; ++i__) {
                                b_ref(i__, j) = b_ref(i__, j) - a_ref(k, j) * b_ref(i__, k);
/* L180: */
                            }
                        }
/* L190: */
                    }
                    if (nounit) {
                        temp = 1. / a_ref(j, j);
                        i__2 = *m;
                        for (i__ = 1; i__ <= i__2; ++i__) {
                            b_ref(i__, j) = temp * b_ref(i__, j);
/* L200: */
                        }
                    }
/* L210: */
                }
            } else {
                for (j = *n; j >= 1; --j) {
                    if (*alpha != 1.) {
                        i__1 = *m;
                        for (i__ = 1; i__ <= i__1; ++i__) {
                            b_ref(i__, j) = *alpha * b_ref(i__, j);
/* L220: */
                        }
                    }
                    i__1 = *n;
                    for (k = j + 1; k <= i__1; ++k) {
                        if (a_ref(k, j) != 0.) {
                            i__2 = *m;
                            for (i__ = 1; i__ <= i__2; ++i__) {
                                b_ref(i__, j) = b_ref(i__, j) - a_ref(k, j) * b_ref(i__, k);
/* L230: */
                            }
                        }
/* L240: */
                    }
                    if (nounit) {
                        temp = 1. / a_ref(j, j);
                        i__1 = *m;
                        for (i__ = 1; i__ <= i__1; ++i__) {
                            b_ref(i__, j) = temp * b_ref(i__, j);
/* L250: */
                        }
                    }
/* L260: */
                }
            }
        } else {
/*           Form  B := alpha*B*inv( A' ). */
            if (upper) {
                for (k = *n; k >= 1; --k) {
                    if (nounit) {
                        temp = 1. / a_ref(k, k);
                        i__1 = *m;
                        for (i__ = 1; i__ <= i__1; ++i__) {
                            b_ref(i__, k) = temp * b_ref(i__, k);
/* L270: */
                        }
                    }
                    i__1 = k - 1;
                    for (j = 1; j <= i__1; ++j) {
                        if (a_ref(j, k) != 0.) {
                            temp = a_ref(j, k);
                            i__2 = *m;
                            for (i__ = 1; i__ <= i__2; ++i__) {
                                b_ref(i__, j) = b_ref(i__, j) - temp * b_ref(i__, k);
/* L280: */
                            }
                        }
/* L290: */
                    }
                    if (*alpha != 1.) {
                        i__1 = *m;
                        for (i__ = 1; i__ <= i__1; ++i__) {
                            b_ref(i__, k) = *alpha * b_ref(i__, k);
/* L300: */
                        }
                    }
/* L310: */
                }
            } else {
                i__1 = *n;
                for (k = 1; k <= i__1; ++k) {
                    if (nounit) {
                        temp = 1. / a_ref(k, k);
                        i__2 = *m;
                        for (i__ = 1; i__ <= i__2; ++i__) {
                            b_ref(i__, k) = temp * b_ref(i__, k);
/* L320: */
                        }
                    }
                    i__2 = *n;
                    for (j = k + 1; j <= i__2; ++j) {
                        if (a_ref(j, k) != 0.) {
                            temp = a_ref(j, k);
                            i__3 = *m;
                            for (i__ = 1; i__ <= i__3; ++i__) {
                                b_ref(i__, j) = b_ref(i__, j) - temp * b_ref(i__, k);
/* L330: */
                            }
                        }
/* L340: */
                    }
                    if (*alpha != 1.) {
                        i__2 = *m;
                        for (i__ = 1; i__ <= i__2; ++i__) {
                            b_ref(i__, k) = *alpha * b_ref(i__, k);
/* L350: */
                        }
                    }
/* L360: */
                }
            }
        }
    }
    return 0;
/*     End of DTRSM . */
} /* iti_dtrsm_ */

/* ITI Subroutine */ int iti_dgetf2_(integer *m, integer *n, doublereal *a, integer *lda, integer *ipiv, integer *colpiv, integer *info)
{
/* ITI: Is mostly identical to function dgetf2_. Differences are commented
                with "ITI".
*/
/*  -- LAPACK routine (version 3.0) --
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
       Courant Institute, Argonne National Lab, and Rice University
       June 30, 1992


    Purpose
    =======

    DGETF2 computes an LU factorization of a general m-by-n matrix A
    using partial pivoting with row (ITI: and column) interchanges.

    The factorization has the form
       A = P * L * U (ITI: * Q)
    where P is a permutation matrix, L is lower triangular with unit
    diagonal elements (lower trapezoidal if m > n), and U is upper
    triangular (upper trapezoidal if m < n) (ITI: Q is a permutation matrix).

    This is the right-looking Level 2 BLAS version of the algorithm.

    Arguments
    =========

    M       (input) INTEGER
            The number of rows of the matrix A.  M >= 0.

    N       (input) INTEGER
            The number of columns of the matrix A.  N >= 0.

    A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
            On entry, the m by n matrix to be factored.
            On exit, the factors L and U from the factorization
            A = P*L*U (ITI: * Q); the unit diagonal elements of L are not stored.

    LDA     (input) INTEGER
            The leading dimension of the array A.  LDA >= __max(1,M).

    IPIV    (output) INTEGER array, dimension (__min(M,N))
            The pivot indices; for 1 <= i <= __min(M,N), row i of the
            matrix was interchanged with row IPIV(i).

    COLPIV  (ITI: output) INTEGER array, dimension (__min(M,N))
            The column pivot indices; for 1 <= i <= __min(M,N), column i of the
            matrix was interchanged with column COLPIV(i).

    INFO    (output) INTEGER
            = 0: successful exit
            < 0: if INFO = -k, the k-th argument had an illegal value
            > 0: if INFO = k, U(k,k) is exactly zero. The factorization
                 has been completed, but the factor U is exactly
                 singular, and division by zero will occur if it is used
                 to solve a system of equations.

    =====================================================================


       Test the input parameters.

       Parameter adjustments */
    /* Table of constant values */
    integer c__1 = 1;
    doublereal c_b6 = -1.;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    doublereal d__1;
    /* Local variables */
    integer j, /* ITI */ k;
    integer jp;


    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --ipiv;
    --colpiv; /* ITI */

    /* Function Body */
    *info = 0;
    if (*m < 0) {
        *info = -1;
    } else if (*n < 0) {
        *info = -2;
    } else if (*lda < max(1, *m)) {
        *info = -4;
    }
    if (*info != 0) {
        i__1 = -(*info);
        xerbla_("DGETF2", &i__1);
        return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0) {
        return 0;
    }

    i__1 = min(*m, *n);
    for (j = 1; j <= i__1; ++j) {

/*        Find pivot and test for singularity. */

        i__2 = *m - j + 1;
        jp = j - 1 + idamax_(&i__2, &a_ref(j, j), &c__1);
        ipiv[j] = jp;
        colpiv[j] = j; /* ITI */
        if (a_ref(jp, j) != 0.) {

/*           Apply the interchange to columns 1:N. */

            if (jp != j) {
                dswap_(n, &a_ref(j, 1), lda, &a_ref(jp, 1), lda);
            }

/*           Compute elements J+1:M of J-th column. */

            if (j < *m) {
                i__2 = *m - j;
                d__1 = 1. / a_ref(j, j);
                dscal_(&i__2, &d__1, &a_ref(j + 1, j), &c__1);
            }

        } else { /* ITI */
            for (k = j + 1; k <= *n; ++k) {
                jp = j - 1 + idamax_(&i__2, &a_ref(j, k), &c__1);
                if (a_ref(jp, k) != 0.) {
                    ipiv[j] = jp;
                    colpiv[j] = k;

                    /*           Apply the interchange to columns 1:N. */
                    if (jp != j) {
                        dswap_(n, &a_ref(j, 1), lda, &a_ref(jp, 1), lda);
                    }
                    dswap_(m, &a_ref(1, j), &c__1, &a_ref(1, k), &c__1);

                    /*           Compute elements J+1:M of J-th column. */
                    if (j < *m) {
                        i__2 = *m - j;
                        d__1 = 1. / a_ref(j, j);
                        dscal_(&i__2, &d__1, &a_ref(j + 1, j), &c__1);
                    }
                    break;
                }
            }
            if ((colpiv[j] == j) && (*info == 0)) {
                *info = j;
            }
        }

        if (j < min(*m, *n)) {

/*           Update trailing submatrix. */

            i__2 = *m - j;
            i__3 = *n - j;
            dger_(&i__2, &i__3, &c_b6, &a_ref(j + 1, j), &c__1, &a_ref(j, j + 1), lda, &a_ref(j + 1, j + 1), lda);
        }
/* L10: */
    }
    return 0;

/*     End of DGETF2 */

} /* iti_dgetf2_ */

/* ITI Subroutine */ int iti_dgetrf_(integer *m, integer *n, doublereal *a, integer *lda, integer *ipiv, integer *colpiv, integer *info)
{
/* ITI: Is mostly identical to function dgetrf_. Differences are commented
                with "ITI".
*/
/*  -- LAPACK routine (version 3.0) --
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
       Courant Institute, Argonne National Lab, and Rice University
       March 31, 1993


    Purpose
    =======

    DGETRF computes an LU factorization of a general M-by-N matrix A
    using partial pivoting with row (ITI: and column) interchanges.

    The factorization has the form
       A = P * L * U (ITI: * Q)
    where P is a permutation matrix, L is lower triangular with unit
    diagonal elements (lower trapezoidal if m > n), and U is upper
    triangular (upper trapezoidal if m < n) (ITI: Q is a permutation matrix).

    This is the right-looking Level 3 BLAS version of the algorithm.

    Arguments
    =========

    M       (input) INTEGER
            The number of rows of the matrix A.  M >= 0.

    N       (input) INTEGER
            The number of columns of the matrix A.  N >= 0.

    A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
            On entry, the M-by-N matrix to be factored.
            On exit, the factors L and U from the factorization
            A = P*L*U (ITI: * Q); the unit diagonal elements of L are not stored.

    LDA     (input) INTEGER
            The leading dimension of the array A.  LDA >= __max(1,M).

    IPIV    (output) INTEGER array, dimension (__min(M,N))
            The pivot indices; for 1 <= i <= __min(M,N), row i of the
            matrix was interchanged with row IPIV(i).

    COLPIV  (ITI: output) INTEGER array, dimension (__min(M,N))
            The column pivot indices; for 1 <= i <= __min(M,N), column i of the
            matrix was interchanged with column COLPIV(i).

    INFO    (output) INTEGER
            = 0:  successful exit
            < 0:  if INFO = -i, the i-th argument had an illegal value
            > 0:  if INFO = i, U(i,i) is exactly zero. The factorization
                  has been completed, but the factor U is exactly
                  singular, and division by zero will occur if it is used
                  to solve a system of equations.

    =====================================================================


       Test the input parameters.

       Parameter adjustments */
    /* Table of constant values */
    integer c__1 = 1;
    integer c_n1 = -1;
    doublereal c_b16 = 1.;
    doublereal c_b19 = -1.;

    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4, i__5;
    /* Local variables */
    integer i__, j;
    integer iinfo;
    integer jb, nb;

    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --ipiv;
    --colpiv; /* ITI */

    /* Function Body */
    *info = 0;
    if (*m < 0) {
        *info = -1;
    } else if (*n < 0) {
        *info = -2;
    } else if (*lda < max(1, *m)) {
        *info = -4;
    }
    if (*info != 0) {
        i__1 = -(*info);
        xerbla_("DGETRF", &i__1);
        return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0) {
        return 0;
    }

/*     Determine the block size for this environment. */

    nb = ilaenv_(&c__1, "DGETRF", " ", m, n, &c_n1, &c_n1);
    if (nb <= 1 || nb >= min(*m, *n)) {

/*        Use unblocked code. */

        iti_dgetf2_(m, n, &a[a_offset], lda, &ipiv[1], &colpiv[1], info); /* ITI */
    } else {

/*        Use blocked code. */

        i__1 = min(*m, *n);
        i__2 = nb;
        for (j = 1; i__2 < 0 ? j >= i__1 : j <= i__1; j += i__2) {
/* Computing MIN */
            i__3 = min(*m, *n) - j + 1;
            jb = min(i__3, nb);

/*           Factor diagonal and subdiagonal blocks and test for exact
             singularity. */

            i__3 = *m - j + 1;
            iti_dgetf2_(&i__3, &jb, &a_ref(j, j), lda, &ipiv[j], &colpiv[j], &iinfo); /* ITI */

/*           Adjust INFO and the pivot indices. */

            if (*info == 0 && iinfo > 0) {
                *info = iinfo + j - 1;
            }
/* Computing MIN */
            i__4 = *m, i__5 = j + jb - 1;
            i__3 = min(i__4, i__5);
            for (i__ = j; i__ <= i__3; ++i__) {
                ipiv[i__] = j - 1 + ipiv[i__];
                colpiv[i__] = j - 1 + colpiv[i__]; /* ITI */
/* L10: */
            }

/*           Apply interchanges to columns 1:J-1. */

            i__3 = j - 1;
            i__4 = j + jb - 1;
            dlaswp_(&i__3, &a[a_offset], lda, &j, &i__4, &ipiv[1], &c__1);
            iti_dlaswp_(&i__3, &a[a_offset], lda, &j, &i__4, &colpiv[1]); /* ITI */
            if (j + jb <= *m) { /* ITI */
                i__3 = *m - j - jb + 1;
                i__4 = j + jb - 1;
                iti_dlaswp_(&i__3, &a_ref(j + jb, 1), lda, &j, &i__4, &colpiv[1]);
            }
            if (j + jb <= *n) {

/*              Apply interchanges to columns J+JB:N. */

                i__3 = *n - j - jb + 1;
                i__4 = j + jb - 1;
                dlaswp_(&i__3, &a_ref(1, j + jb), lda, &j, &i__4, &ipiv[1], &c__1);

/*              Compute block row of U. */

                i__3 = *n - j - jb + 1;
                dtrsm_("Left", "Lower", "No transpose", "Unit", &jb, &i__3, &c_b16, &a_ref(j, j), lda, &a_ref(j, j + jb), lda);
                if (j + jb <= *m) {

/*                 Update trailing submatrix. */

                    i__3 = *m - j - jb + 1;
                    i__4 = *n - j - jb + 1;
                    dgemm_("No transpose", "No transpose", &i__3, &i__4, &jb, &c_b19, &a_ref(j + jb, j), lda, &a_ref(j, j + jb), lda, &c_b16, &a_ref(j + jb, j + jb), lda);
                }
            }
/* L20: */
        }
    }
    return 0;

/*     End of DGETRF */

} /* iti_dgetrf_ */

/* ITI Subroutine */ int iti_dgetrs_(char *trans, integer *n, integer *nrhs, doublereal *a, integer *lda, integer *ipiv, integer *colpiv, doublereal *b, integer *ldb, integer *info)
{
/* ITI: Is mostly identical to function dgetrs_. Differences are commented
                with "ITI".
*/
/*  -- LAPACK routine (version 3.0) --
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
       Courant Institute, Argonne National Lab, and Rice University
       March 31, 1993


    Purpose
    =======

    DGETRS solves a system of linear equations
       A * X = B  or  A' * X = B
    with a general N-by-N matrix A using the LU factorization computed
    by DGETRF.

    Arguments
    =========

    TRANS   (input) CHARACTER*1
            Specifies the form of the system of equations:
            = 'N':  A * X = B  (No transpose)
            = 'T':  A'* X = B  (Transpose)
            = 'C':  A'* X = B  (Conjugate transpose = Transpose)

    N       (input) INTEGER
            The order of the matrix A.  N >= 0.

    NRHS    (input) INTEGER
            The number of right hand sides, i.e., the number of columns
            of the matrix B.  NRHS >= 0.

    A       (input) DOUBLE PRECISION array, dimension (LDA,N)
            The factors L and U from the factorization A = P*L*U
            as computed by DGETRF.

    LDA     (input) INTEGER
            The leading dimension of the array A.  LDA >= __max(1,N).

    IPIV    (input) INTEGER array, dimension (N)
            The pivot indices from DGETRF; for 1<=i<=N, row i of the
            matrix was interchanged with row IPIV(i).

        COLPIV        (ITI: input) INTEGER array, dimension (N) wie in iti_dgetrf_ (DGETRF)
                        The column pivot indices from DGETRF; for 1<=i<=N, column i of the
                        matrix was interchanged with column COLPIV(i).

    B       (input/output) DOUBLE PRECISION array, dimension (LDB,NRHS)
            On entry, the right hand side matrix B.
            On exit, the solution matrix X.

    LDB     (input) INTEGER
            The leading dimension of the array B.  LDB >= __max(1,N).

    INFO    (output) INTEGER
            = 0:  successful exit
            < 0:  if INFO = -i, the i-th argument had an illegal value

    =====================================================================


       Test the input parameters.

       Parameter adjustments */
    /* Table of constant values */
    integer c__1 = 1;
    doublereal c_b12 = 1.;
    integer c_n1 = -1;

    integer iti_info = *info; /* ITI */

    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, i__1;
    /* Local variables */
    logical notran;

    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --ipiv;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1 * 1;
    b -= b_offset;

    /* Function Body */
    *info = 0;
    notran = lsame_(trans, "N");
    if (!notran && !lsame_(trans, "T") && !lsame_(trans, "C")) {
        *info = -1;
    } else if (*n < 0) {
        *info = -2;
    } else if (*nrhs < 0) {
        *info = -3;
    } else if (*lda < max(1, *n)) {
        *info = -5;
    } else if (*ldb < max(1, *n)) {
        *info = -8;
    }
    if (*info != 0) {
        i__1 = -(*info);
        xerbla_("DGETRS", &i__1);
        return 0;
    }

/*     Quick return if possible */

    if (*n == 0 || *nrhs == 0) {
        return 0;
    }

    if (notran) {

/*        Solve A * X = B.

          Apply row interchanges to the right hand sides. */

        dlaswp_(nrhs, &b[b_offset], ldb, &c__1, n, &ipiv[1], &c__1);

/*        Solve L*X = B, overwriting B with X. */

        dtrsm_("Left", "Lower", "No transpose", "Unit", n, nrhs, &c_b12, &a[a_offset], lda, &b[b_offset], ldb);

/*        Solve U*X = B, overwriting B with X. */

        if (iti_info == 0) {
            dtrsm_("Left", "Upper", "No transpose", "Non-unit", n, nrhs, &c_b12, &a[a_offset], lda, &b[b_offset], ldb);
        }
        /* ITI */
        else {
            iti_dtrsm_("Left", "Upper", "No transpose", "Non-unit", n, nrhs, &c_b12, &a[a_offset], lda, &b[b_offset], ldb, info);
/*                        ITI: Apply column interchanges to the solution vectors. */
            dlaswp_(nrhs, &b[b_offset], ldb, &c__1, n, colpiv, &c_n1); /* ITI */
        }
    } else {

/*        Solve A' * X = B.

          Solve U'*X = B, overwriting B with X. */

        if (iti_info == 0) {
            dtrsm_("Left", "Upper", "Transpose", "Non-unit", n, nrhs, &c_b12, &a[a_offset], lda, &b[b_offset], ldb);
        }
        /* ITI */
        else {
/*                        ITI: Apply column interchanges to the residual vectors. */
            dlaswp_(nrhs, &b[b_offset], ldb, &c__1, n, colpiv, &c__1); /* ITI */
            iti_dtrsm_("Left", "Upper", "Transpose", "Non-unit", n, nrhs, &c_b12, &a[a_offset], lda, &b[b_offset], ldb, info);
        }

/*        Solve L'*X = B, overwriting B with X. */

        dtrsm_("Left", "Lower", "Transpose", "Unit", n, nrhs, &c_b12, &a[a_offset], lda, &b[b_offset], ldb);

/*        Apply row interchanges to the solution vectors. */

        dlaswp_(nrhs, &b[b_offset], ldb, &c__1, n, &ipiv[1], &c_n1);
    }

    return 0;

/*     End of DGETRS */

} /* iti_dgetrs_ */

/* ITI Subroutine */ int iti_dgetrs_rect_normal_(integer *m, integer *n, doublereal *a, integer *ipiv, integer *colpiv, doublereal *b, integer *info, doublereal *ker, doublereal *kercopy, doublereal *veccopy, doublereal *dWork, integer *lPermVecCol, doublereal error)
{
/* ITI: Ist eine Weiterentwicklung und komplette Ueberarbeitung von dgetrs_ und dtrsm_ (DTRSM)
        fuer rechteckige moeglicherweise singulaere Dreieckszerlegungen mit spaltenweiser Speicherung.
*/
/*  -- LAPACK routine (version 3.0) --
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
       Courant Institute, Argonne National Lab, and Rice University
       March 31, 1993


    Purpose
    =======

    DGETRS solves a system of linear equations
       A * X = B
    with a general M-by-N matrix A using the LU factorization computed
    by DGETRF.

    Arguments
    =========

        M                ITI: (input) INTEGER
                        Zeilendimension von A. M >= 0

    N       (input) INTEGER
            The order of the matrix A.  N >= 0. ITI: Spaltendimension von A.

    A       (input) DOUBLE PRECISION array, dimension (M,N)
            The factors L and U from the factorization A = P*L*U (ITI: * Q)
            as computed by DGETRF.

    IPIV    (input) INTEGER array, dimension (N) ITI: (__min(M,N)) wie in dgetrf_ (DGETRF)
            The pivot indices from DGETRF; for 1<=i<=N ITI:__min(M,N), row i of the
            matrix was interchanged with row IPIV(i).

        COLPIV        (ITI: input) INTEGER array, dimension (__min(M,N)) wie in iti_dgetrf_ (DGETRF)
                        The column pivot indices from DGETRF; for 1<=i<=__min(M,N), column i of the
                        matrix was interchanged with column COLPIV(i).

    B       (input/output) DOUBLE PRECISION array, dimension (LDB,NRHS) ITI: (__max(M,N))
            On entry, the right hand side matrix B.
            On exit, the solution matrix X.

    INFO    (output) INTEGER
            = 0:  successful exit
            < 0:  if INFO = -i, the i-th argument had an illegal value
                        ITI: > 0: i-te transformierte Gleichung ist nicht erfuellbar

        KER                ITI: DOUBLE PRECISION array, Zwischenspeicher fuer Kern bei N > M

        ...

        ERROR        aus dem unvermeidlichen Fehler berechnete Fehlerschranke fuer die rechte Seite

    =====================================================================


       Test the input parameters.

       Parameter adjustments */
    /* Table of constant values */
    integer c__1 = 1;
    integer c_n1 = -1;

 /* ITI */
    integer nrhs = 1;
    integer ldb = max(*m, *n);
    integer end = min(*m, *n);
    integer kerdim = (*n - end);
    logical singular = 0;

    /* System generated locals */
    integer a_dim1, a_dim2, i__1;
    /* Local variables */
    integer i__, j, k;

    a_dim1 = *m; /* ITI statt lda; */
    a_dim2 = *n; /* ITI */

    /* Function Body */
    *info = 0;
    if (*m < 0) {
        *info = -1;
    } else if (*n < 0) {
        *info = -2;
    }
    if (*info != 0) {
        i__1 = -(*info);
        xerbla_("DGETRS", &i__1);
        return 0;
    }

/*     Quick return if possible */

    if (*n == 0 || *m /* ITI statt *nrhs */  == 0) {
        return 0;
    }

/*        Solve A * X = B.

          Apply row interchanges to the right hand sides. */

    dlaswp_(&nrhs, b, &ldb, &c__1, &end, ipiv, &c__1);

/*        Solve L*X = B, overwriting B with X. */
    /* ITI */
    i__1 = *m;
    for (k = 0; k < end; ++k) {
        if (b[k] != 0.) {
            for (i__ = k + 1; i__ < i__1; ++i__) {
                b[i__] -= b[k] * a_ref(i__, k);
            }
        }
    }
    for (i__ = end; i__ < i__1; ++i__) {
#if defined _ABS_RHS_BORDER
        if (fabs(b[i__]) > error /*4.44089209850063e-013 */ )
#endif
        {
            *info = i__ + 1;
        }
    }

/*        Solve U*X = B, overwriting B with X. */
    /* ITI */
    for (k = end - 1; k >= 0; --k) {
        if (b[k] != 0.) {
            if (a_ref(k, k) != 0.0) {
                b[k] = b[k] / a_ref(k, k);
            } else {
                singular = 1;
#if defined _ABS_RHS_BORDER
                if (fabs(b[k]) > error /*4.44089209850063e-013 */ )
#endif
                {
                    *info = k + 1;
                }
#if defined _ABS_RHS_BORDER
                b[k] = 0.0;
#endif
            }
            for (i__ = 0; i__ < k; ++i__) {
                b[i__] = b[i__] - b[k] * a_ref(i__, k);
            }
        }
    }

    if (!singular) {
        i__1 = *n;
        for (j = end; j < i__1; ++j) {
            b[j] = 0.0;
            i__ = j - end;
            for (k = 0; k < end; ++k) {
                ker_ref(k, i__) = -a_ref(k, j);
            }
            for (k = end; k < i__1; ++k) {
                ker_ref(k, i__) = 0.0;
            }
            ker_ref(j, i__) = 1.0;
        }
        for (j = 0; j < kerdim; ++j) {
            for (i__ = end - 1; i__ >= 0; --i__) {
                if (ker_ref(i__, j) != 0.) {
                    ker_ref(i__, j) = ker_ref(i__, j) / a_ref(i__, i__);
                    for (k = 0; k < i__; ++k) {
                        ker_ref(k, j) -= a_ref(k, i__) * ker_ref(i__, j);
                    }
                }
            }
        }
        if (kerdim > 0) {
            integer lOne = 1;
            doublereal dInvCond = 1.0e-200;
            integer lRank;
            integer lDimWork = 35 * kerdim + 32;
            integer lIllegalValue = 0;

            for (j = 0; j < a_dim2 * kerdim; ++j) {
                kercopy[j] = ker[j];
            }
            for (j = 0; j < a_dim2; ++j) {
                veccopy[j] = b[j];
            }

            dgelsy_(n, &kerdim, &lOne, kercopy, n, veccopy, n, lPermVecCol, &dInvCond, &lRank, dWork, &lDimWork, &lIllegalValue);

            for (j = 0; j < kerdim; ++j) {
                for (k = 0; k < a_dim2; ++k) {
                    b[k] -= ker_ref(k, j) * veccopy[j];
                }
            }
        }
    }

/*        Apply column interchanges to the solution vectors. */

    dlaswp_(&nrhs, b, &ldb, &c__1, &end, colpiv, &c_n1);
    /* ITI */
    return 0;

/*     End of DGETRS */

}

/* ITI Subroutine */ int iti_dlaswp_(integer *n, doublereal *a, integer *lda, integer *k1, integer *k2, integer *colpiv)
{
/* ITI: Is mostly identical to function dlaswp_. Differences are commented with "ITI". */
/*  -- LAPACK auxiliary routine (version 3.0) --
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
       Courant Institute, Argonne National Lab, and Rice University
       June 30, 1999


    Purpose
    =======

    DLASWP performs a series of (ITI: column) interchanges on the matrix A.
    One (ITI: column) interchange is initiated for each of (ITI: columns) K1 through K2 of A.

    Arguments
    =========

    N       (input) INTEGER
            The number of (ITI: rows) of the matrix A.

    A       (input/output) DOUBLE PRECISION array
            On entry, the matrix of (ITI: row) dimension N to which the (ITI: column)
            interchanges will be applied.
            On exit, the permuted matrix.

    LDA     (input) INTEGER
            The leading dimension of the array A.

    K1      (input) INTEGER
            The first element of (ITI: COLPIV) for which a (ITI: column) interchange will
            be done.

    K2      (input) INTEGER
            The last element of (ITI: COLPIV) for which a (ITI: column) interchange will
            be done.

    COLPIV  (ITI) (input) INTEGER array
            The vector of pivot indices. Only the elements in positions
            K1 through K2 of (ITI: COLPIV) are accessed.
            (ITI: COLPIV)(K) = L implies (ITI: columns) K and L are to be interchanged.

    Further Details
    ===============

    Modified by
     R. C. Whaley, Computer Science Dept., Univ. of Tenn., Knoxville, USA

   =====================================================================


       Interchange (ITI: column) I with (ITI: column) (ITI: COLPIV)(I) for each of (ITI: columns) K1 through K2.

       Parameter adjustments */
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4;
    /* Local variables */
    doublereal temp;
    integer i__, j, k, i1, i2, n32, ip, ix, ix0, inc;

    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --colpiv; /* ITI */

    /* Function Body */ /* ITI: only used part */
    ix0 = *k1;
    i1 = *k1;
    i2 = *k2;
    inc = 1;

    n32 = *n / 32 << 5;
    if (n32 != 0) {
        i__1 = n32;
        for (j = 1; j <= i__1; j += 32) {
            ix = ix0;
            i__2 = i2;
            i__3 = inc;
            for (i__ = i1; i__ <= i__2; i__ += i__3) {
                ip = colpiv[ix]; /* ITI */
                if (ip != i__) {
                    i__4 = j + 31;
                    for (k = j; k <= i__4; ++k) {
                        temp = a_ref(k, i__); /* ITI */
                        a_ref(k, i__) = a_ref(k, ip); /* ITI */
                        a_ref(k, ip) = temp; /* ITI */
/* L10: */
                    }
                }
                ix += inc; /* ITI */
/* L20: */
            }
/* L30: */
        }
    }
    if (n32 != *n) {
        ++n32;
        ix = ix0;
        i__1 = i2;
        i__3 = inc;
        for (i__ = i1; i__ <= i__1; i__ += i__3) {
            ip = colpiv[ix]; /* ITI */
            if (ip != i__) {
                i__2 = *n;
                for (k = n32; k <= i__2; ++k) {
                    temp = a_ref(k, i__); /* ITI */
                    a_ref(k, i__) = a_ref(k, ip); /* ITI */
                    a_ref(k, ip) = temp; /* ITI */
/* L40: */
                }
            }
            ix += inc; /* ITI */
/* L50: */
        }
    }

    return 0;

/*     End of DLASWP */

} /* iti_dlaswp_ */

#undef ker_ref
#undef b_ref
#undef a_ref

#undef _ABS_RHS_BORDER

/*
   lls_init, lls_fact, lls_solv are based on LAPACK subroutine DGELSY.
   For help on parameters see DGELSY.
 */

void lls_init(ITI_LLSData *data)
{
    /* Table of constant values */
    integer c__1 = 1;
    integer c_n1 = -1;

    integer nb, mn;
    integer nb1, nb2, nb3, nb4;

    data->rcond = DBL_EPSILON;

    /* Get machine parameters */
    data->smlnum = dlamch_("S") / dlamch_("P");
    data->bignum = 1. / data->smlnum;

    mn = min(data->m, data->n);

    /* Figure out optimal block size */
    nb1 = ilaenv_(&c__1, "DGEQRF", " ", &data->m, &data->n, &c_n1, &c_n1);
    nb2 = ilaenv_(&c__1, "DGERQF", " ", &data->m, &data->n, &c_n1, &c_n1);
    nb3 = ilaenv_(&c__1, "DORMQR", " ", &data->m, &data->n, &c__1, &c_n1);
    nb4 = ilaenv_(&c__1, "DORMRQ", " ", &data->m, &data->n, &c__1, &c_n1);
    nb = max(nb1, nb2);
    nb = max(nb, nb3);
    nb = max(nb, nb4);
    data->lwork = mn + 2 * data->n + nb * (data->n + 1);
}

void lls_fact(ITI_LLSData *data)
{
    /* Table of constant values */
    integer c__0 = 0;
    integer c__1 = 1;
    integer c__2 = 2;

    doublereal smin, smax, c1, c2, s1, s2, sminpr, smaxpr;
    integer info, i;
    doublereal *ap1, *ap2;

    /* m, n may be smaller than in lls_init */
    data->mn = min(data->m, data->n);

    data->wp1 = data->work + data->mn;
    data->wp2 = data->work + 2 * data->mn;

    /* Scale A if max entries outside range [SMLNUM,BIGNUM] */
    data->anrm = dlange_("M", &data->m, &data->n, data->a, &data->m, data->work);
    data->iascl = 0;
    if (data->anrm > 0. && data->anrm < data->smlnum) {
        /* Scale matrix norm up to SMLNUM */
        dlascl_("G", &c__0, &c__0, &data->anrm, &data->smlnum, &data->m, &data->n, data->a, &data->m, &info);
        data->iascl = 1;
    } else if (data->anrm > data->bignum) {
        /* Scale matrix norm down to BIGNUM */
        dlascl_("G", &c__0, &c__0, &data->anrm, &data->bignum, &data->m, &data->n, data->a, &data->m, &info);
        data->iascl = 2;
    } else if (data->anrm == 0.) {
        /* Matrix all zero. */
        data->rank = 0;
        return;
    }

    /*
       Compute QR factorization with column pivoting of A:
       A * P = Q * R
     */
    i = data->lwork - data->mn;
    dgeqp3_(&data->m, &data->n, data->a, &data->m, data->jpvt, data->work, data->wp1, &i, &info);
    /*
       workspace: MN+2*N+NB*(N+1)
       Details of Householder rotations stored in WORK(1:MN).
     */

    /* Determine RANK using incremental condition estimation */
    data->wp1[0] = 1.;
    data->wp2[0] = 1.;
    smax = abs(data->a[0]);
    smin = smax;
    data->rank = 1;

    while (data->rank < data->mn) {
        i = data->rank;
        ap1 = data->a + i * data->m;
        ap2 = data->a + i * (data->m + 1);
        dlaic1_(&c__2, &data->rank, data->wp1, &smin, ap1, ap2, &sminpr, &s1, &c1);
        dlaic1_(&c__1, &data->rank, data->wp2, &smax, ap1, ap2, &smaxpr, &s2, &c2);

        if (smaxpr * data->rcond > sminpr)
            break;

        for (i = 0; i < data->rank; ++i) {
            data->wp1[i] *= s1;
            data->wp2[i] *= s2;
        }
        data->wp1[data->rank] = c1;
        data->wp2[data->rank] = c2;
        smin = sminpr;
        smax = smaxpr;
        ++data->rank;
    }
    /* workspace: 3*MN */

    /*
       Logically partition R = [ R11 R12 ]
       [  0  R22 ]
       where R11 = R(1:RANK,1:RANK)

       [R11,R12] = [ T11, 0 ] * Y
     */
    if (data->rank < data->n) {
        i = data->lwork - 2 * data->mn;
        dtzrzf_(&data->rank, &data->n, data->a, &data->m, data->wp1, data->wp2, &i, &info);
    }
    /*
       workspace: (2+NB)*MN
       Details of Householder rotations stored in WORK(MN+1:2*MN)
     */
}

void lls_solv(ITI_LLSData *data)
{
    /* Table of constant values */
    integer c__0 = 0;
    integer c__1 = 1;
    doublereal one = 1.;

    int ibscl;
    integer info, i, i2;
    doublereal bnrm;

    /* Scale B if max entries outside range [SMLNUM,BIGNUM] */
    bnrm = dlange_("M", &data->m, &c__1, data->b, &data->ldb, data->work);
    ibscl = 0;
    if (bnrm > 0. && bnrm < data->smlnum) {
        /* Scale matrix norm up to SMLNUM */
        dlascl_("G", &c__0, &c__0, &bnrm, &data->smlnum, &data->m, &c__1, data->b, &data->ldb, &info);
        ibscl = 1;
    } else if (bnrm > data->bignum) {
        /* Scale matrix norm down to BIGNUM */
        dlascl_("G", &c__0, &c__0, &bnrm, &data->bignum, &data->m, &c__1, data->b, &data->ldb, &info);
        ibscl = 2;
    }

    /* B(1:M) := Q' * B(1:M) */
    i = data->lwork - 2 * data->mn;
    dormqr_("Left", "Transpose", &data->m, &c__1, &data->mn, data->a, &data->m, data->work, data->b, &data->ldb, data->wp2, &i, &info);
    /* workspace: 2*MN+NB */

    /* B(1:RANK) := inv(T11) * B(1:RANK) */
    dtrsm_("Left", "Upper", "No transpose", "Non-unit", &data->rank, &c__1, &one, data->a, &data->m, data->b, &data->ldb);

    for (i = data->rank; i < data->n; ++i)
        data->b[i] = 0.;

    /* B(1:N) := Y' * B(1:N) */
    if (data->rank < data->n) {
        i = data->n - data->rank;
        i2 = data->lwork - 2 * data->mn;
        dormrz_("Left", "Transpose", &data->n, &c__1, &data->rank, &i, data->a, &data->m, data->wp1, data->b, &data->ldb, data->wp2, &i2, &info);
    }
    /* workspace: 2*MN+NB */

    /* B(1:N) := P * B(1:N) */ /* ITI: Do not change WORK(1:2*MN)! */
    for (i = 0; i < data->n; ++i)
        data->wp2[data->jpvt[i] - 1] = data->b[i];
    dcopy_(&data->n, data->wp2, &c__1, data->b, &c__1);
    /* workspace: 2*MN+N */

    /* Undo scaling */
    if (data->iascl == 1)
        dlascl_("G", &c__0, &c__0, &data->anrm, &data->smlnum, &data->n, &c__1, data->b, &data->ldb, &info);
    else if (data->iascl == 2)
        dlascl_("G", &c__0, &c__0, &data->anrm, &data->bignum, &data->n, &c__1, data->b, &data->ldb, &info);
    if (ibscl == 1)
        dlascl_("G", &c__0, &c__0, &data->smlnum, &bnrm, &data->n, &c__1, data->b, &data->ldb, &info);
    else if (ibscl == 2)
        dlascl_("G", &c__0, &c__0, &data->bignum, &bnrm, &data->n, &c__1, data->b, &data->ldb, &info);
}
