/* linalg/sytd.c
 * 
 * Copyright (C) 2001 Brian Gough
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/* Factorise a symmetric matrix A into
 *
 * A = Q T Q'
 *
 * where Q is orthogonal and T is symmetric tridiagonal.  Only the
 * diagonal and lower triangular part of A is referenced and modified.
 *
 * On exit, T is stored in the diagonal and first subdiagonal of
 * A. Since T is symmetric the upper diagonal is not stored.
 *
 * Q is stored as a packed set of Householder transformations in the
 * lower triangular part of the input matrix below the first subdiagonal.
 *
 *  * The full matrix for Q can be obtained as the product
 *
 *       Q = Q_N .. Q_2 Q_1
 *
 * where 
 *
 *       Q_i = (I - tau_i * v_i * v_i')
 *
 * and where v_i is a Householder vector
 *
 *       v_i = [1, A(i+2,i), A(i+3,i), ... , A(N,i)]
 *
 * This storage scheme is the same as in LAPACK.  See LAPACK's
 * ssytd2.f for details.
 *
 * See Golub & Van Loan, "Matrix Computations" (3rd ed), Section 8.3 */

#include <config.h>
#include <stdlib.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>

#include "gsl_linalg.h"

int 
gsl_linalg_symmtd_decomp (gsl_matrix * A, gsl_vector * tau)  
{
  if (A->size1 != A->size2)
    {
      GSL_ERROR ("symmetric tridiagonal decomposition requires square matrix",
                 GSL_ENOTSQR);
    }
  else if (tau->size + 1 != A->size1)
    {
      GSL_ERROR ("size of tau must be (matrix size - 1)", GSL_EBADLEN);
    }
  else
    {
      const size_t N = A->size1;
      size_t i;
  
      for (i = 0 ; i < N - 2; i++)
        {
          gsl_vector c = gsl_matrix_column (A, i);
          gsl_vector v = gsl_vector_subvector (&c, i + 1, N - (i + 1));
          double tau_i = gsl_linalg_householder_transform (&v);
          
          /* Apply the transformation H^T A H to the remaining columns */

          if (tau_i != 0.0) 
            {
              gsl_matrix m = gsl_matrix_submatrix (A, i + 1, i + 1, 
                                                   N - (i+1), N - (i+1));
              double ei = gsl_vector_get(&v, 0);
              gsl_vector x = gsl_vector_subvector (tau, i, N-(i+1));
              gsl_vector_set (&v, 0, 1.0);
              
              /* x = tau * A * v */
              gsl_blas_dsymv (CblasLower, tau_i, &m, &v, 0.0, &x);

              /* w = x - (1/2) tau * (x' * v) * v  */
              {
                double xv, alpha;
                gsl_blas_ddot(&x, &v, &xv);
                alpha = - (tau_i / 2.0) * xv;
                gsl_blas_daxpy(alpha, &v, &x);
              }
              
              /* apply the transformation A = A - v w' - w v' */
              gsl_blas_dsyr2(CblasLower, -1.0, &v, &x, &m);

              gsl_vector_set (&v, 0, ei);
            }
          
          gsl_vector_set (tau, i, tau_i);
        }
      
      return GSL_SUCCESS;
    }
}  


/*  Form the orthogonal matrix Q from the packed QR matrix */

int
gsl_linalg_symmtd_unpack (const gsl_matrix * A, 
                          const gsl_vector * tau,
                          gsl_matrix * Q, 
                          gsl_vector * diag, 
                          gsl_vector * sdiag)
{
  if (A->size1 !=  A->size2)
    {
      GSL_ERROR ("matrix A must be square", GSL_ENOTSQR);
    }
  else if (tau->size + 1 != A->size1)
    {
      GSL_ERROR ("size of tau must be (matrix size - 1)", GSL_EBADLEN);
    }
  else if (Q->size1 != A->size1 || Q->size2 != A->size1)
    {
      GSL_ERROR ("size of Q must match size of A", GSL_EBADLEN);
    }
  else if (diag->size != A->size1)
    {
      GSL_ERROR ("size of diagonal must match size of A", GSL_EBADLEN);
    }
  else if (sdiag->size + 1 != A->size1)
    {
      GSL_ERROR ("size of subdiagonal must be (matrix size - 1)", GSL_EBADLEN);
    }
  else
    {
      const size_t N = A->size1;

      size_t i;

      /* Initialize Q to the identity */

      gsl_matrix_set_identity (Q);

      for (i = N - 2; i > 0 && i--;)
	{
          const gsl_vector c = gsl_matrix_const_column (A, i);
          const gsl_vector h = gsl_vector_const_subvector (&c, i + 1, N - (i+1));
          double ti = gsl_vector_get (tau, i);

          gsl_matrix m = gsl_matrix_submatrix (Q, i + 1, i + 1, N-(i+1), N-(i+1));

          gsl_linalg_householder_hm (ti, &h, &m);
        }

      /* Copy diagonal into diag */

      for (i = 0; i < N; i++)
        {
          double Aii = gsl_matrix_get (A, i, i);
          gsl_vector_set (diag, i, Aii);
        }

      /* Copy subdiagonal into sd */

      for (i = 0; i < N - 1; i++)
        {
          double Aji = gsl_matrix_get (A, i+1, i);
          gsl_vector_set (sdiag, i, Aji);
        }

      return GSL_SUCCESS;
    }
}

int
gsl_linalg_symmtd_unpack_T (const gsl_matrix * A, 
                            gsl_vector * diag, 
                            gsl_vector * sdiag)
{
  if (A->size1 !=  A->size2)
    {
      GSL_ERROR ("matrix A must be square", GSL_ENOTSQR);
    }
  else if (diag->size != A->size1)
    {
      GSL_ERROR ("size of diagonal must match size of A", GSL_EBADLEN);
    }
  else if (sdiag->size + 1 != A->size1)
    {
      GSL_ERROR ("size of subdiagonal must be (matrix size - 1)", GSL_EBADLEN);
    }
  else
    {
      const size_t N = A->size1;

      size_t i;

      /* Copy diagonal into diag */

      for (i = 0; i < N; i++)
        {
          double Aii = gsl_matrix_get (A, i, i);
          gsl_vector_set (diag, i, Aii);
        }

      /* Copy subdiagonal into sdiag */

      for (i = 0; i < N - 1; i++)
        {
          double Aij = gsl_matrix_get (A, i+1, i);
          gsl_vector_set (sdiag, i, Aij);
        }

      return GSL_SUCCESS;
    }
}