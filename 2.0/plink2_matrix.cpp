// This file is part of PLINK 2.00, copyright (C) 2005-2017 Shaun Purcell,
// Christopher Chang.
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include "plink2_matrix.h"

#ifndef NOLAPACK
  #ifndef __APPLE__

    #ifdef __cplusplus
extern "C" {
    #endif

    #ifdef _WIN32
      // openblas is easy enough to set up on Windows nowadays.
      // not worth the trouble of ripping out vector extensions, etc. just so
      // we can compile with Visual Studio and gain access to MKL
      #ifndef USE_OPENBLAS
        #error "Windows build currently requires OpenBLAS's LAPACK."
      #endif
      #define HAVE_LAPACK_CONFIG_H
      #define LAPACK_COMPLEX_STRUCTURE
      #include "lapacke.h"

  void dgemm_(char* transa, char* transb, int* m, int* n, int* k,
              double* alpha, double* a, int* lda, double* b, int* ldb,
              double* beta, double* c, int* ldc);

  void dgetrf_(__CLPK_integer* m, __CLPK_integer* n,
               __CLPK_doublereal* a, __CLPK_integer* lda,
               __CLPK_integer* ipiv, __CLPK_integer* info);

  void dsyrk_(char* uplo, char* trans, __CLPK_integer* n, __CLPK_integer* k,
              __CLPK_doublereal* alpha, __CLPK_doublereal* a,
              __CLPK_integer* lda, __CLPK_doublereal* beta,
              __CLPK_doublereal* c, __CLPK_integer* ldc);

  void sgemm_(char* transa, char* transb, int* m, int* n, int* k,
              float* alpha, float* a, int* lda, float* b, int* ldb,
              float* beta, float* c, int* ldc);

  void ssyrk_(char* uplo, char* trans, __CLPK_integer* n, __CLPK_integer* k,
              float* alpha, float* a, __CLPK_integer* lda, float* beta,
              float* c, __CLPK_integer* ldc);

    #else // Linux
      #ifndef USE_MKL
  int dgetrf_(__CLPK_integer* m, __CLPK_integer* n,
              __CLPK_doublereal* a, __CLPK_integer* lda,
              __CLPK_integer* ipiv, __CLPK_integer* info);

  int dgetri_(__CLPK_integer* n, __CLPK_doublereal* a,
              __CLPK_integer* lda, __CLPK_integer* ipiv,
              __CLPK_doublereal* work, __CLPK_integer* lwork,
              __CLPK_integer* info);

  double dlange_(char* norm, __CLPK_integer* m, __CLPK_integer* n,
                 __CLPK_doublereal* a, __CLPK_integer* lda,
                 __CLPK_doublereal* work);

  double dlansy_(char* norm, char* uplo, __CLPK_integer* n,
                 __CLPK_doublereal* a, __CLPK_integer* lda,
                 __CLPK_doublereal* work);

  int dgecon_(char* norm, __CLPK_integer* n, __CLPK_doublereal* a,
              __CLPK_integer* lda, __CLPK_doublereal* anorm,
              __CLPK_doublereal* rcond, __CLPK_doublereal* work,
              __CLPK_integer* iwork, __CLPK_integer* info);

  int dpocon_(char* uplo, __CLPK_integer* n, __CLPK_doublereal* a,
              __CLPK_integer* lda, __CLPK_doublereal* anorm,
              __CLPK_doublereal* rcond, __CLPK_doublereal* work,
              __CLPK_integer* iwork, __CLPK_integer* info);

  /*
  void dgesdd_(char* jobs, __CLPK_integer* m, __CLPK_integer* n,
               __CLPK_doublereal* a, __CLPK_integer* lda, __CLPK_doublereal* s,
               __CLPK_doublereal* u, __CLPK_integer* ldu,
               __CLPK_doublereal* vt, __CLPK_integer* ldvt,
               __CLPK_doublereal* work, __CLPK_integer* lwork,
               __CLPK_integer* iwork, __CLPK_integer* info);
  */

  void dgesvd_(char* jobu, char* jobvt, __CLPK_integer* m, __CLPK_integer* n,
               __CLPK_doublereal* a, __CLPK_integer* lda, __CLPK_doublereal* s,
               __CLPK_doublereal* u, __CLPK_integer* ldu,
               __CLPK_doublereal* vt, __CLPK_integer* ldvt,
               __CLPK_doublereal* work, __CLPK_integer* lwork,
               __CLPK_integer* info);

  int dsyevr_(char* jobz, char* range, char* uplo, __CLPK_integer* n,
              __CLPK_doublereal* a, __CLPK_integer* lda, __CLPK_doublereal* vl,
              __CLPK_doublereal* vu, __CLPK_integer* il, __CLPK_integer* iu,
              __CLPK_doublereal* abstol, __CLPK_integer* m,
              __CLPK_doublereal* w, __CLPK_doublereal* z, __CLPK_integer* ldz,
              __CLPK_integer* isuppz, __CLPK_doublereal* work,
              __CLPK_integer* lwork, __CLPK_integer* iwork,
              __CLPK_integer* liwork, __CLPK_integer* info);

  int dpotrf_(char* uplo, __CLPK_integer* n, __CLPK_doublereal* a,
              __CLPK_integer* lda, __CLPK_integer* info);


  void dpotrs_(char* uplo, __CLPK_integer* n, __CLPK_integer* nrhs,
               __CLPK_doublereal* a, __CLPK_integer* lda, __CLPK_doublereal* b,
               __CLPK_integer* ldb, __CLPK_integer* info);

  int dpotri_(char* uplo, __CLPK_integer* n, __CLPK_doublereal* a,
              __CLPK_integer* lda, __CLPK_integer* info);

        #ifndef USE_CBLAS_XGEMM
  void dgemm_(char* transa, char* transb, __CLPK_integer* m, __CLPK_integer* n,
              __CLPK_integer* k, __CLPK_doublereal* alpha,
              __CLPK_doublereal* a, __CLPK_integer* lda, __CLPK_doublereal* b,
              __CLPK_integer* ldb, __CLPK_doublereal* beta,
              __CLPK_doublereal* c, __CLPK_integer* ldc);

  void sgemm_(char* transa, char* transb, __CLPK_integer* m, __CLPK_integer* n,
              __CLPK_integer* k, float* alpha, float* a, __CLPK_integer* lda,
              float* b, __CLPK_integer* ldb, float* beta, float* c,
              __CLPK_integer* ldc);

  void dsyrk_(char* uplo, char* trans, __CLPK_integer* n, __CLPK_integer* k,
              __CLPK_doublereal* alpha, __CLPK_doublereal* a,
              __CLPK_integer* lda, __CLPK_doublereal* beta,
              __CLPK_doublereal* c, __CLPK_integer* ldc);

  void ssyrk_(char* uplo, char* trans, __CLPK_integer* n, __CLPK_integer* k,
              float* alpha, float* a, __CLPK_integer* lda, float* beta,
              float* c, __CLPK_integer* ldc);
        #endif
      #endif // !USE_MKL
    #endif // Linux

  void xerbla_(void);
    #ifdef __cplusplus
} // extern "C"
    #endif // __cplusplus
    void xerbla_(void) {} // fix static linking error
  #endif // not __APPLE__

#endif // !NOLAPACK


#ifdef __cplusplus
namespace plink2 {
#endif

void reflect_matrix(uint32_t dim, double* matrix) {
  const uintptr_t dim_p1l = dim + 1;
  double* write_row = matrix;
  for (uint32_t row_idx = 0; row_idx < dim; ++row_idx) {
    double* read_col_iter = &(matrix[dim_p1l * row_idx + dim]);
    for (uint32_t col_idx = row_idx + 1; col_idx < dim; ++col_idx) {
      write_row[col_idx] = *read_col_iter;
      read_col_iter = &(read_col_iter[dim]);
    }
    write_row = &(write_row[dim]);
  }
}

void reflect_fmatrix(uint32_t dim, uint32_t stride, float* matrix) {
  const uintptr_t stride_p1l = stride + 1;
  float* write_row = matrix;
  for (uint32_t row_idx = 0; row_idx < dim; ++row_idx) {
    float* read_col_iter = &(matrix[stride_p1l * row_idx + stride]);
    for (uint32_t col_idx = row_idx + 1; col_idx < dim; ++col_idx) {
      write_row[col_idx] = *read_col_iter;
      read_col_iter = &(read_col_iter[stride]);
    }
    write_row = &(write_row[stride]);
  }
}

void reflect_fmatrixz(uint32_t dim, uint32_t stride, float* matrix) {
  const uintptr_t stride_p1l = stride + 1;
  float* write_row = matrix;
  for (uint32_t row_idx = 0; row_idx < dim; ++row_idx) {
    float* read_col_iter = &(matrix[stride_p1l * row_idx + stride]);
    for (uint32_t col_idx = row_idx + 1; col_idx < dim; ++col_idx) {
      write_row[col_idx] = *read_col_iter;
      read_col_iter = &(read_col_iter[stride]);
    }
    fill_float_zero(stride - dim, &(write_row[dim]));
    write_row = &(write_row[stride]);
  }
}

inline double SQR(const double a) {
  return a * a;
}

#ifdef __cplusplus
inline double SIGN(const double &a, const double &b) {
  // PLINK helper.h SIGN() template specialized to doubles.
  return (b >= 0)? (a >= 0 ? a : -a) : (a >= 0 ? -a : a);
}
#else
inline double SIGN(const double a, const double b) {
  // PLINK helper.h SIGN() template specialized to doubles.
  return (b >= 0)? (a >= 0 ? a : -a) : (a >= 0 ? -a : a);
}
#endif

double pythag(const double a, const double b) {
  // PLINK stats.cpp pythag().
  double absa,absb;

  absa=fabs(a);
  absb=fabs(b);
  if (absa > absb) return absa*sqrt(1.0+SQR(absb/absa));
  else return (absb == 0.0 ? 0.0 : absb*sqrt(1.0+SQR(absa/absb)));
}

#ifdef NOLAPACK
uint32_t svdcmp_c(int32_t m, double* a, double* w, double* v) {
  // C port of PLINK stats.cpp svdcmp().
  // Now thread-safe.
  double* rv1 = &(w[(uint32_t)m]);
  int32_t n = m;
  int32_t flag;
  int32_t l = 0; // suppress compile warning
  int32_t i,its,j,jj,k,nm;
  double anorm,c,f,g,h,s,scale,x,y,z;
  double temp;

  g=scale=anorm=0.0;
  for (i=0;i<n;i++) {
    l=i+2;
    rv1[i]=scale*g;
    g=s=scale=0.0;
    if (i < m) {
      for (k=i;k<m;k++) scale += fabs(a[k * m + i]);
      if (scale != 0.0) {
        for (k=i;k<m;k++) {
          a[k * m + i] /= scale;
          s += a[k * m + i]*a[k * m + i];
        }
        f=a[i * m + i];
        g = -SIGN(sqrt(s),f);
        h=f*g-s;
        a[i * m + i]=f-g;
        for (j=l-1;j<n;j++) {
          for (s=0.0,k=i;k<m;k++) s += a[k * m + i]*a[k * m + j];
          f=s/h;
          for (k=i;k<m;k++) a[k * m + j] += f*a[k * m + i];
        }
        for (k=i;k<m;k++) a[k * m + i] *= scale;
      }
    }
    w[i]=scale *g;
    g=s=scale=0.0;
    if (i+1 <= m && i+1 != n) {
      for (k=l-1;k<n;k++) scale += fabs(a[i * m + k]);
      if (scale != 0.0) {
        for (k=l-1;k<n;k++) {
          a[i * m + k] /= scale;
          s += a[i * m + k]*a[i * m + k];
        }
        f=a[i * m + l-1];
        g = -SIGN(sqrt(s),f);
        h=f*g-s;
        a[i * m + l-1]=f-g;
        for (k=l-1;k<n;k++) rv1[k]=a[i * m + k]/h;
        for (j=l-1;j<m;j++) {
          for (s=0.0,k=l-1;k<n;k++) s += a[j * m + k]*a[i * m + k];
          for (k=l-1;k<n;k++) a[j * m + k] += s*rv1[k];
        }
        for (k=l-1;k<n;k++) a[i * m + k] *= scale;
      }
    }
    anorm=MAXV(anorm,(fabs(w[i])+fabs(rv1[i])));
  }
  for (i=n-1;i>=0;i--) {
    if (i < n-1) {
      if (g != 0.0) {
        for (j=l;j<n;j++)
          v[j * m + i]=(a[i * m + j]/a[i * m + l])/g;
        for (j=l;j<n;j++) {
          for (s=0.0,k=l;k<n;k++) s += a[i * m + k]*v[k * m + j];
          for (k=l;k<n;k++) v[k * m + j] += s*v[k * m + i];
        }
      }
      for (j=l;j<n;j++) v[i * m + j]=v[j * m + i]=0.0;
    }
    v[i * m + i]=1.0;
    g=rv1[i];
    l=i;
  }
  for (i=MINV(m,n)-1;i>=0;i--) {
    l=i+1;
    g=w[i];
    for (j=l;j<n;j++) a[i * m + j]=0.0;
    if (g != 0.0) {
      g=1.0/g;
      for (j=l;j<n;j++) {
        for (s=0.0,k=l;k<m;k++) s += a[k * m + i]*a[k * m + j];
        f=(s/a[i * m + i])*g;
        for (k=i;k<m;k++) a[k * m + j] += f*a[k * m + i];
      }
      for (j=i;j<m;j++) a[j * m + i] *= g;
    } else for (j=i;j<m;j++) a[j * m + i]=0.0;
    ++a[i * m + i];
  }
  for (k=n-1;k>=0;k--) {
    for (its=0;its<30;its++) {
      flag=1;
      for (l=k;l>=0;l--) {
        nm=l-1;
        temp=fabs(rv1[l])+anorm;
        if (temp == anorm) {
          flag=0;
          break;
        }
        temp=fabs(w[nm])+anorm;
        if (temp == anorm) break;
      }
      if (flag) {
        c=0.0;
        s=1.0;
        for (i=l;i<k+1;i++) {
          f=s*rv1[i];
          rv1[i]=c*rv1[i];
          temp = fabs(f)+anorm;
          if (temp == anorm) break;
          g=w[i];
          h=pythag(f,g);
          w[i]=h;
          h=1.0/h;
          c=g*h;
          s = -f*h;
          for (j=0;j<m;j++) {
            y=a[j * m + nm];
            z=a[j * m + i];
            a[j * m + nm]=y*c+z*s;
            a[j * m + i]=z*c-y*s;
          }
        }
      }
      z=w[k];
      if (l == k) {
        if (z < 0.0) {
          w[k] = -z;
          for (j=0;j<n;j++) v[j * m + k] = -v[j * m + k];
        }
        break;
      }
      if (its == 29)
        return 0; // cannot converge: multi-collinearity?
      x=w[l];
      nm=k-1;
      y=w[nm];
      g=rv1[nm];
      h=rv1[k];
      f=((y-z)*(y+z)+(g-h)*(g+h))/(2.0*h*y);
      g=pythag(f,1.0);
      f=((x-z)*(x+z)+h*((y/(f+SIGN(g,f)))-h))/x;
      c=s=1.0;
      for (j=l;j<=nm;j++) {
        i=j+1;
        g=rv1[i];
        y=w[i];
        h=s*g;
        g=c*g;
        z=pythag(f,h);
        rv1[j]=z;
        c=f/z;
        s=h/z;
        f=x*c+g*s;
        g=g*c-x*s;
        h=y*s;
        y *= c;
        for (jj=0;jj<n;jj++) {
          x=v[jj * m + j];
          z=v[jj * m + i];
          v[jj * m + j]=x*c+z*s;
          v[jj * m + i]=z*c-x*s;
        }
        z=pythag(f,h);
        w[j]=z;
        if (z) {
          z=1.0/z;
          c=f*z;
          s=h*z;
        }
        f=c*g+s*y;
        x=c*y-s*g;
        for (jj=0;jj<m;jj++) {
          y=a[jj * m + j];
          z=a[jj * m + i];
          a[jj * m + j]=y*c+z*s;
          a[jj * m + i]=z*c-y*s;
        }
      }
      rv1[l]=0.0;
      rv1[k]=f;
      w[k]=x;
    }
  }
  return 1;
}

boolerr_t invert_matrix(int32_t dim, double* matrix, matrix_invert_buf1_t* dbl_1d_buf, double* dbl_2d_buf) {
  // C port of PLINK stats.cpp's svd_inverse() function.

  // w -> dbl_1d_buf
  // v -> dbl_2d_buf
  const double eps = 1e-24;
  if (!svdcmp_c(dim, matrix, dbl_1d_buf, dbl_2d_buf)) {
    return 1;
  }

  // Look for singular values
  double wmax = 0;
  int32_t i;
  for (i=0; i<dim; i++) {
    wmax = dbl_1d_buf[i] > wmax ? dbl_1d_buf[i] : wmax;
  }
  double wmin = wmax * eps;
  for (i=0; i<dim; i++) {
    dbl_1d_buf[i] = dbl_1d_buf[i] < wmin ? 0 : (1 / dbl_1d_buf[i]);
  }

  int32_t j;
  for (i=0; i<dim; i++) {
    for (j=0; j<dim; j++) {
      matrix[i * dim + j] = matrix[i * dim + j] * dbl_1d_buf[j];
    }
  }

  int32_t k;
  // [nxn].[t(v)]
  for (i=0; i<dim; i++) {
    fill_double_zero(dim, dbl_1d_buf);
    for (j=0; j<dim; j++) {
      for (k=0; k<dim; k++) {
        dbl_1d_buf[j] += matrix[i * dim + k] * dbl_2d_buf[j * dim + k];
      }
    }
    for (j = 0; j < dim; j++) {
      matrix[i * dim + j] = dbl_1d_buf[j];
    }
  }
  for (i=1; i<dim; ++i) {
    for(j=0; j<i; ++j) {
      const double tmp = matrix[i * dim + j];
      matrix[i * dim + j] = matrix[j * dim + i];
      matrix[j * dim + i] = tmp;
    }
  }
  return 0;
}

boolerr_t invert_fmatrix_first_half(int32_t dim, uint32_t stride, const float* matrix, double* half_inverted, matrix_invert_buf1_t* dbl_1d_buf, double* dbl_2d_buf) {
  const float* read_row = matrix;
  double* write_row = half_inverted;
  for (uint32_t row_idx = 0; row_idx < (uint32_t)dim; ++row_idx) {
    for (uint32_t col_idx = 0; col_idx < (uint32_t)dim; ++col_idx) {
      write_row[col_idx] = (double)read_row[col_idx];
    }
    read_row = &(read_row[stride]);
    write_row = &(write_row[(uint32_t)dim]);
  }

  return (!svdcmp_c(dim, half_inverted, dbl_1d_buf, dbl_2d_buf));
}

void invert_fmatrix_second_half(__CLPK_integer dim, uint32_t stride, double* half_inverted, float* inverted_result, matrix_invert_buf1_t* dbl_1d_buf, double* dbl_2d_buf) {
  // Look for singular values
  double wmax = 0;
  int32_t i;
  for (i=0; i<dim; i++) {
    wmax = dbl_1d_buf[i] > wmax ? dbl_1d_buf[i] : wmax;
  }
  double wmin = wmax * eps;
  for (i=0; i<dim; i++) {
    dbl_1d_buf[i] = dbl_1d_buf[i] < wmin ? 0 : (1 / dbl_1d_buf[i]);
  }

  int32_t j;
  for (i=0; i<dim; i++) {
    for (j=0; j<dim; j++) {
      half_inverted[i * dim + j] = half_inverted[i * dim + j] * dbl_1d_buf[j];
    }
  }

  int32_t k;
  // [nxn].[t(v)]
  for (i=0; i<dim; i++) {
    fill_double_zero(dim, dbl_1d_buf);
    for (j=0; j<dim; j++) {
      for (k=0; k<dim; k++) {
        dbl_1d_buf[j] += half_inverted[i * dim + k] * dbl_2d_buf[j * dim + k];
      }
    }
    for (j = 0; j < dim; j++) {
      half_inverted[i * dim + j] = dbl_1d_buf[j];
    }
  }
  inverted_result[0] = (float)half_inverted[0];
  for (i=1; i<dim; ++i) {
    for(j=0; j<i; ++j) {
      inverted_result[i * stride + j] = (float)half_inverted[j * dim + i];
      inverted_result[j * stride + i] = (float)half_inverted[i * dim + j];
    }
    inverted_result[i * stride + i] = (float)half_inverted[i * stride + i];
  }
  return 0;
}
#else // !NOLAPACK
boolerr_t invert_matrix(__CLPK_integer dim, double* matrix, matrix_invert_buf1_t* int_1d_buf, double* dbl_2d_buf) {
  // invert_symmdef_matrix() is noticeably faster in the symmetric
  // positive-semidefinite case.
  __CLPK_integer info;
  dgetrf_(&dim, &dim, matrix, &dim, int_1d_buf, &info);
  if (info) {
    return 1;
  }
  __CLPK_integer lwork = dim * dim;
  dgetri_(&dim, matrix, &dim, int_1d_buf, dbl_2d_buf, &lwork, &info);
  assert(info == 0);
  return 0;
}

boolerr_t invert_matrix_checked(__CLPK_integer dim, double* matrix, matrix_invert_buf1_t* int_1d_buf, double* dbl_2d_buf) {
  // This used to fall back on PLINK 1.07's SVD-based implementation when the
  // rcond estimate was too small, but in practice that just slowed things down
  // without meaningfully improving inversion of nonsingular matrices.  So now
  // this just exits a bit earlier, while leaving the old "binary search for
  // the first row/column causing multicollinearity" logic to the caller.
  char cc = '1';
  double norm = dlange_(&cc, &dim, &dim, matrix, &dim, dbl_2d_buf);
  __CLPK_integer info;
  dgetrf_(&dim, &dim, matrix, &dim, int_1d_buf, &info);
  if (info > 0) {
    return 1;
  }
  double rcond;
  dgecon_(&cc, &dim, matrix, &dim, &norm, &rcond, dbl_2d_buf, &(int_1d_buf[(uint32_t)dim]), &info);
  if (rcond < kMatrixSingularRcond) {
    return 1;
  }
  __CLPK_integer lwork = dim * dim;
  dgetri_(&dim, matrix, &dim, int_1d_buf, dbl_2d_buf, &lwork, &info);
  return 0;
}

boolerr_t invert_symmdef_matrix(__CLPK_integer dim, double* matrix, __maybe_unused matrix_invert_buf1_t* int_1d_buf, __maybe_unused double* dbl_2d_buf) {
  char uplo = 'U';
  __CLPK_integer info;
  dpotrf_(&uplo, &dim, matrix, &dim, &info);
  if (info) {
    return 1;
  }
  dpotri_(&uplo, &dim, matrix, &dim, &info);
  assert(info == 0);
  return 0;
}

boolerr_t invert_symmdef_matrix_checked(__CLPK_integer dim, double* matrix, matrix_invert_buf1_t* int_1d_buf, double* dbl_2d_buf) {
  char cc = '1';
  char uplo = 'U';
  double norm = dlansy_(&cc, &uplo, &dim, matrix, &dim, dbl_2d_buf);
  __CLPK_integer info;
  dpotrf_(&uplo, &dim, matrix, &dim, &info);
  if (info > 0) {
    return 1;
  }
  double rcond;
  dpocon_(&uplo, &dim, matrix, &dim, &norm, &rcond, dbl_2d_buf, int_1d_buf, &info);
  if (rcond < kMatrixSingularRcond) {
    return 1;
  }
  dpotri_(&uplo, &dim, matrix, &dim, &info);
  return 0;
}

// quasi-bugfix (20 Sep 2017): give up on doing this with single-precision
// numbers.  Instead, convert to double-precision, then perform the usual
// inversion, then downcode back to single-precision.
boolerr_t invert_fmatrix_first_half(__CLPK_integer dim, uint32_t stride, const float* matrix, double* half_inverted, matrix_invert_buf1_t* int_1d_buf, double* dbl_2d_buf) {
  const float* read_row = matrix;
  double* write_row = half_inverted;
  for (uint32_t row_idx = 0; row_idx < (uint32_t)dim; ++row_idx) {
    for (uint32_t col_idx = 0; col_idx < (uint32_t)dim; ++col_idx) {
      write_row[col_idx] = (double)read_row[col_idx];
    }
    read_row = &(read_row[stride]);
    write_row = &(write_row[(uint32_t)dim]);
  }

  char cc = '1';
  double norm = dlange_(&cc, &dim, &dim, half_inverted, &dim, dbl_2d_buf);
  __CLPK_integer info;
  dgetrf_(&dim, &dim, half_inverted, &dim, int_1d_buf, &info);
  if (info > 0) {
    return 1;
  }
  double rcond;
  dgecon_(&cc, &dim, half_inverted, &dim, &norm, &rcond, dbl_2d_buf, &(int_1d_buf[(uint32_t)dim]), &info);
  return (rcond < kMatrixSingularRcond);
}

boolerr_t invert_symmdef_fmatrix_first_half(__CLPK_integer dim, uint32_t stride, float* matrix, double* half_inverted, matrix_invert_buf1_t* int_1d_buf, double* dbl_2d_buf) {
  const float* read_row = matrix;
  double* write_row = half_inverted;
  for (uint32_t row_idx = 0; row_idx < (uint32_t)dim; ++row_idx) {
    for (uint32_t col_idx = 0; col_idx <= row_idx; ++col_idx) {
      write_row[col_idx] = (double)read_row[col_idx];
    }
    read_row = &(read_row[stride]);
    write_row = &(write_row[(uint32_t)dim]);
  }

  char cc = '1';
  char uplo = 'U';
  double norm = dlansy_(&cc, &uplo, &dim, half_inverted, &dim, dbl_2d_buf);
  __CLPK_integer info;
  dpotrf_(&uplo, &dim, half_inverted, &dim, &info);
  if (info > 0) {
    return 1;
  }
  double rcond;
  dpocon_(&uplo, &dim, half_inverted, &dim, &norm, &rcond, dbl_2d_buf, int_1d_buf, &info);
  return (rcond < kMatrixSingularRcond);
}

void invert_fmatrix_second_half(__CLPK_integer dim, uint32_t stride, double* half_inverted, float* inverted_result, matrix_invert_buf1_t* int_1d_buf, double* dbl_2d_buf) {
  __CLPK_integer lwork = dim * dim;
  __CLPK_integer info;
  dgetri_(&dim, half_inverted, &dim, int_1d_buf, dbl_2d_buf, &lwork, &info);
  const double* read_row = half_inverted;
  float* write_row = inverted_result;
  for (uint32_t row_idx = 0; row_idx < (uint32_t)dim; ++row_idx) {
    for (uint32_t col_idx = 0; col_idx < (uint32_t)dim; ++col_idx) {
      write_row[col_idx] = (float)read_row[col_idx];
    }
    read_row = &(read_row[(uint32_t)dim]);
    write_row = &(write_row[stride]);
  }
}

void invert_symmdef_fmatrix_second_half(__CLPK_integer dim, uint32_t stride, double* half_inverted, float* inverted_result, __maybe_unused matrix_invert_buf1_t* int_1d_buf, __maybe_unused double* dbl_2d_buf) {
  char uplo = 'U';
  __CLPK_integer info;
  dpotri_(&uplo, &dim, half_inverted, &dim, &info);
  const double* read_row = half_inverted;
  float* write_row = inverted_result;
  for (uint32_t row_idx = 0; row_idx < (uint32_t)dim; ++row_idx) {
    for (uint32_t col_idx = 0; col_idx <= row_idx; ++col_idx) {
      write_row[col_idx] = (float)read_row[col_idx];
    }
    read_row = &(read_row[(uint32_t)dim]);
    write_row = &(write_row[stride]);
  }
}
#endif // !NOLAPACK

void col_major_matrix_multiply(const double* inmatrix1, const double* inmatrix2, __CLPK_integer row1_ct, __CLPK_integer col2_ct, __CLPK_integer common_ct, double* outmatrix) {
#ifdef NOLAPACK
  const uintptr_t row1_ct_l = row1_ct;
  const uintptr_t col2_ct_l = col2_ct;
  const uintptr_t common_ct_l = common_ct;
  // not optimized
  for (uintptr_t col_idx = 0; col_idx < col2_ct_l; ++col_idx) {
    for (uintptr_t row_idx = 0; row_idx < row1_ct_l; ++row_idx) {
      double cur_dotprod = 0.0;
      const double* dptr = &(inmatrix2[col_idx * common_ct]);
      for (uintptr_t com_idx = 0; com_idx < common_ct_l; ++com_idx) {
        cur_dotprod += (*dptr++) * inmatrix1[com_idx * row1_ct_l + row_idx];
      }
      *outmatrix++ = cur_dotprod;
    }
  }
#else
  #ifndef USE_CBLAS_XGEMM
  char blas_char = 'N';
  double dyy = 1;
  double dzz = 0;
  // const_cast
  dgemm_(&blas_char, &blas_char, &row1_ct, &col2_ct, &common_ct, &dyy, (double*)((uintptr_t)inmatrix1), &row1_ct, (double*)((uintptr_t)inmatrix2), &common_ct, &dzz, outmatrix, &row1_ct);
  #else
  // bugfix (30 Aug 2017): this fails on OS X when LDB > sqrt(2^31).
  // update: Windows does not have the same problem
  // update 2 (6 Sep 2017): the OS X failure seems to have been driven by 128k
  //   thread stack size; going up to the usual 512k appears to solve the
  //   problem
  // #ifdef LAPACK_ILP64
  cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, row1_ct, col2_ct, common_ct, 1.0, inmatrix1, row1_ct, inmatrix2, common_ct, 0.0, outmatrix, row1_ct);
  /*
    #else
  if (common_ct <= 46340) {
    cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, row1_ct, col2_ct, common_ct, 1.0, inmatrix1, row1_ct, inmatrix2, common_ct, 0.0, outmatrix, row1_ct);
    return;
  }
  for (__CLPK_integer col_idx = 0; col_idx < col2_ct; ++col_idx) {
    cblas_dgemv(CblasColMajor, CblasNoTrans, row1_ct, common_ct, 1.0, inmatrix1, row1_ct, inmatrix2, 1, 0.0, outmatrix, 1);
    inmatrix2 = &(inmatrix2[(uint32_t)common_ct]);
    outmatrix = &(outmatrix[(uint32_t)row1_ct]);
  }
    #endif
  */
  #endif // USE_CBLAS_XGEMM
#endif // !NOLAPACK
}

void col_major_matrix_multiply_strided_addassign(const double* inmatrix1, const double* inmatrix2, __CLPK_integer row1_ct, __CLPK_integer stride1, __CLPK_integer col2_ct, __CLPK_integer stride2, __CLPK_integer common_ct, __CLPK_integer stride3, double beta, double* outmatrix) {
  // stride1 should be close to row1_ct
  // stride2 should be close to common_ct
  // output matrix uses stride3, which should be close to row1_ct
#ifdef NOLAPACK
  const uintptr_t row1_ct_l = row1_ct;
  const uintptr_t col2_ct_l = col2_ct;
  const uintptr_t common_ct_l = common_ct;
  // not optimized, no beta == 0 special case
  for (uintptr_t col_idx = 0; col_idx < col2_ct_l; ++col_idx) {
    double* outmatrix_row_iter = &(outmatrix[col_idx * stride3]);
    for (uintptr_t row_idx = 0; row_idx < row1_ct_l; ++row_idx) {
      double cur_entry = 0.0;
      const double* col2_iter = &(inmatrix2[col_idx * stride2]);
      for (uintptr_t com_idx = 0; com_idx < common_ct_l; com_idx++) {
        cur_entry += (*col2_iter++) * inmatrix1[com_idx * stride1 + row_idx];
      }
      *outmatrix_row_iter = (*outmatrix_row_iter) * beta + cur_entry;
      ++outmatrix_row_iter;
    }
  }
#else
  #ifndef USE_CBLAS_XGEMM
  char blas_char = 'N';
  double alpha = 1;
  // const_cast
  dgemm_(&blas_char, &blas_char, &row1_ct, &col2_ct, &common_ct, &alpha, (double*)((uintptr_t)inmatrix1), &stride1, (double*)((uintptr_t)inmatrix2), &stride2, &beta, outmatrix, &stride3);
  #else
  cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, row1_ct, col2_ct, common_ct, 1.0, inmatrix1, stride1, inmatrix2, stride2, beta, outmatrix, stride3);
  #endif // USE_CBLAS_XGEMM
#endif // !NOLAPACK
}

// er, should make this _addassign for consistency...
void col_major_fmatrix_multiply_strided(const float* inmatrix1, const float* inmatrix2, __CLPK_integer row1_ct, __CLPK_integer stride1, __CLPK_integer col2_ct, __CLPK_integer stride2, __CLPK_integer common_ct, __CLPK_integer stride3, float* outmatrix) {
#ifdef NOLAPACK
  const uintptr_t row1_ct_l = row1_ct;
  const uintptr_t col2_ct_l = col2_ct;
  const uintptr_t common_ct_l = common_ct;
  // not optimized
  for (uintptr_t col_idx = 0; col_idx < col2_ct_l; ++col_idx) {
    float* outmatrix_row_iter = &(outmatrix[col_idx * stride3]);
    for (uintptr_t row_idx = 0; row_idx < row1_ct_l; ++row_idx) {
      float cur_entry = 0.0;
      const float* col2_iter = &(inmatrix2[col_idx * stride2]);
      for (uintptr_t com_idx = 0; com_idx < common_ct_l; com_idx++) {
        cur_entry += (*col2_iter++) * inmatrix1[com_idx * stride1 + row_idx];
      }
      *outmatrix_row_iter++ = cur_entry;
    }
  }
#else
  #ifndef USE_CBLAS_XGEMM
  char blas_char = 'N';
  float fyy = 1;
  float fzz = 0;
  // const_cast
  sgemm_(&blas_char, &blas_char, &row1_ct, &col2_ct, &common_ct, &fyy, (float*)((uintptr_t)inmatrix1), &stride1, (float*)((uintptr_t)inmatrix2), &stride2, &fzz, outmatrix, &stride3);
  #else
  cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, row1_ct, col2_ct, common_ct, 1.0, inmatrix1, stride1, inmatrix2, stride2, 0.0, outmatrix, stride3);
  #endif // USE_CBLAS_XGEMM
#endif // !NOLAPACK
}

// Briefly experimented with trying to speed this up, didn't make any progress.
void transpose_copy(const double* old_matrix, uint32_t old_maj, uint32_t new_maj, double* new_matrix_iter) {
  for (uint32_t new_maj_idx = 0; new_maj_idx < new_maj; ++new_maj_idx) {
    const double* old_matrix_col_iter = &(old_matrix[new_maj_idx]);
    for (uint32_t old_maj_idx = 0; old_maj_idx < old_maj; ++old_maj_idx) {
      *new_matrix_iter++ = *old_matrix_col_iter;
      old_matrix_col_iter = &(old_matrix_col_iter[new_maj]);
    }
  }
}

void transpose_copy_float(const float* old_matrix, uint32_t old_maj, uint32_t new_maj, uint32_t new_maj_max, float* new_matrix_iter) {
  // new_maj = in-memory stride of old_matrix rows
  // new_maj_max = actual number of rows in new_matrix
  // (distinction is necessary for SSE alignment)
  for (uint32_t new_maj_idx = 0; new_maj_idx < new_maj_max; ++new_maj_idx) {
    const float* old_matrix_col_iter = &(old_matrix[new_maj_idx]);
    for (uint32_t old_maj_idx = 0; old_maj_idx < old_maj; ++old_maj_idx) {
      *new_matrix_iter++ = *old_matrix_col_iter;
      old_matrix_col_iter = &(old_matrix_col_iter[new_maj]);
    }
  }
}

/*
__CLPK_integer qr_square_factor_float_get_lwork(uint32_t dim) {
  __CLPK_integer dim_i = (__CLPK_integer)dim;
  __CLPK_integer sgeqrf_lwork = -1;
  float work[1];
  __CLPK_integer info;
  float dummy;
  float dummy2;
  sgeqrf_(&dim_i, &dim_i, &dummy, &dim_i, &dummy2, work, &sgeqrf_lwork, &info);
  assert(info == 0);
  sgeqrf_lwork = (__CLPK_integer)work[0];
  __CLPK_integer sorgqr_lwork = -1;
  sorgqr_(&dim_i, &dim_i, &dim_i, &dummy, &dim_i, &dummy2, work, &sorgqr_lwork, &info);
  assert(info == 0);
  sorgqr_lwork = (__CLPK_integer)work[0];
  return MAXV(sgeqrf_lwork, sorgqr_lwork);
}

boolerr_t qr_square_factor_float(const float* input_matrix, uint32_t dim, uintptr_t stride, __CLPK_integer lwork, float* qq, float* r_determinant_ptr, float* tau_buf, float* work_buf) {
  // only returns Q and, optionally, the product of R's diagonal entries (which
  // should be the determinant of the original matrix).
  // tau_buf should have space for dim entries
  if (dim == stride) {
    memcpy(qq, input_matrix, dim * ((uintptr_t)dim) * sizeof(float));
  } else {
    for (uintptr_t col_idx = 0; col_idx < dim; ++col_idx) {
      memcpy(&(qq[col_idx * dim]), &(input_matrix[col_idx * stride]), dim * sizeof(float));
    }
  }
  __CLPK_integer dim_i = (__CLPK_integer)dim;
  __CLPK_integer info;
  sgeqrf_(&dim_i, &dim_i, qq, &dim_i, tau_buf, work_buf, &lwork, &info);
  if (info != 0) {
    return 1;
  }
  if (r_determinant_ptr) {
    const uintptr_t dimp1 = dim + 1;
    float prod = qq[0];
    for (uintptr_t col_idx = 1; col_idx < dim; ++col_idx) {
      prod *= qq[col_idx * dimp1];
    }
    *r_determinant_ptr = prod;
  }
  sorgqr_(&dim_i, &dim_i, &dim_i, qq, &dim_i, tau_buf, work_buf, &lwork, &info);
  if (info != 0) {
    return 1;
  }
  return 0;
}
*/

// A(A^T), where A is row-major; result is dim x dim
// ONLY UPDATES LOWER TRIANGLE OF result[].
void multiply_self_transpose(const double* input_matrix, uint32_t dim, uint32_t col_ct, double* result) {
#ifdef NOLAPACK
  for (uintptr_t row1_idx = 0; row1_idx < dim; ++row1_idx) {
    const double* pred_row1 = &(input_matrix[row1_idx * col_ct]);
    double* result_row = &(result[row1_idx * dim]);
    for (uintptr_t row2_idx = 0; row2_idx <= row1_idx; ++row2_idx) {
      const double* pred_row2 = &(input_matrix[row2_idx * col_ct]);
      result_row[row2_idx] = dotprod_d(pred_row1, pred_row2, col_ct);
    }
  }
#else
  #ifndef USE_CBLAS_XGEMM
  char uplo = 'U';
  char trans = 'T';
  __CLPK_integer tmp_n = dim;
  __CLPK_integer tmp_k = col_ct;
  double alpha = 1.0;
  double beta = 0.0;
  // const_cast
  dsyrk_(&uplo, &trans, &tmp_n, &tmp_k, &alpha, (double*)((uintptr_t)input_matrix), &tmp_k, &beta, result, &tmp_n);
  #else
  // see col_major_matrix_multiply() remarks; same OS X issue here.
  // #ifdef LAPACK_ILP64
  cblas_dsyrk(CblasColMajor, CblasUpper, CblasTrans, dim, col_ct, 1.0, input_matrix, col_ct, 0.0, result, dim);
  /*
    #else
  if (col_ct <= 46340) {
    // bugfix (30 Aug 2017): for LDA > sqrt(2^31), this fails on OS X.
    cblas_dsyrk(CblasColMajor, CblasUpper, CblasTrans, dim, col_ct, 1.0, input_matrix, col_ct, 0.0, result, dim);
    return;
  }
  // this actually seems to be faster than dsyrk for small dim (at least on OS
  // X), but that might change in the future so I won't "optimize" dispatch
  for (uintptr_t row1_idx = 0; row1_idx < dim; ++row1_idx) {
    const double* pred_row1 = &(input_matrix[row1_idx * col_ct]);
    double* result_row = &(result[row1_idx * dim]);
    for (uintptr_t row2_idx = 0; row2_idx <= row1_idx; ++row2_idx) {
      const double* pred_row2 = &(input_matrix[row2_idx * col_ct]);
      result_row[row2_idx] = dotprod_d(pred_row1, pred_row2, col_ct);
    }
  }
    #endif
  */
  #endif
#endif
}

void multiply_self_transpose_strided_f(const float* input_matrix, uint32_t dim, uint32_t col_ct, uint32_t stride, float* result) {
#ifdef NOLAPACK
  for (uintptr_t row1_idx = 0; row1_idx < dim; ++row1_idx) {
    const float* pred_row1 = &(input_matrix[row1_idx * stride]);
    float* result_row = &(result[row1_idx * dim]);
    for (uintptr_t row2_idx = 0; row2_idx <= row1_idx; ++row2_idx) {
      const float* pred_row2 = &(input_matrix[row2_idx * stride]);
      result_row[row2_idx] = dotprod_f(pred_row1, pred_row2, col_ct);
    }
  }
#else
  #ifndef USE_CBLAS_XGEMM
  char uplo = 'U';
  char trans = 'T';
  __CLPK_integer tmp_n = dim;
  __CLPK_integer tmp_k = col_ct;
  __CLPK_integer tmp_lda = stride;
  float alpha = 1.0;
  float beta = 0.0;
  // const_cast
  ssyrk_(&uplo, &trans, &tmp_n, &tmp_k, &alpha, (float*)((uintptr_t)input_matrix), &tmp_lda, &beta, result, &tmp_n);
  #else
  cblas_ssyrk(CblasColMajor, CblasUpper, CblasTrans, dim, col_ct, 1.0, input_matrix, stride, 0.0, result, dim);
  #endif
#endif
}

void transpose_multiply_self_incr(double* input_part, uint32_t dim, uint32_t partial_row_ct, double* result) {
#ifdef NOLAPACK
  // friends do not let friends use this implementation
  const uintptr_t dim_l = dim;
  const uintptr_t row_ct_l = partial_row_ct;
  for (uintptr_t idx1 = 0; idx1 < dim_l; ++idx1) {
    const double* col1 = &(input_part[idx1]);
    double* write_iter = &(result[idx1 * dim_l]);
    for (uintptr_t idx2 = 0; idx2 <= idx1; ++idx2) {
      double cur_dotprod = *write_iter;
      const double* col2 = &(input_part[idx2]);
      for (uintptr_t row_idx = 0; row_idx < row_ct_l; ++row_idx) {
        cur_dotprod += col1[row_idx * dim_l] * col2[row_idx * dim_l];
      }
      *write_iter = cur_dotprod;
      ++write_iter;
    }
  }
#else
  #ifndef USE_CBLAS_XGEMM
  char uplo = 'U';
  char trans = 'N';
  __CLPK_integer tmp_n = dim;
  __CLPK_integer tmp_k = partial_row_ct;
  double alpha = 1.0;
  double beta = 1.0;
  dsyrk_(&uplo, &trans, &tmp_n, &tmp_k, &alpha, input_part, &tmp_n, &beta, result, &tmp_n);
  #else
  cblas_dsyrk(CblasColMajor, CblasUpper, CblasNoTrans, dim, partial_row_ct, 1.0, input_part, dim, 1.0, result, dim);
  #endif
#endif // !NOLAPACK
}

#ifndef NOLAPACK
boolerr_t get_svd_rect_lwork(uint32_t major_ct, uint32_t minor_ct, __CLPK_integer* lwork_ptr) {
  char jobu = 'S';
  char jobvt = 'O';
  __CLPK_integer tmp_m = minor_ct;
  __CLPK_integer tmp_n = major_ct;
  __CLPK_integer wkspace_size = -1;
  double wkspace_size_d;
  __CLPK_integer info;
  dgesvd_(&jobu, &jobvt, &tmp_m, &tmp_n, nullptr, &tmp_m, nullptr, nullptr, &tmp_m, nullptr, &tmp_m, &wkspace_size_d, &wkspace_size, &info);
  #ifdef LAPACK_ILP64
  if (info) {
    return 1;
  }
  #else
  if (info || (wkspace_size_d > 2147483640.0)) {
    return 1;
  }
  #endif
  *lwork_ptr = round_up_pow2((__CLPK_integer)wkspace_size_d, kCacheline / sizeof(double));
  return 0;
}

boolerr_t svd_rect(uint32_t major_ct, uint32_t minor_ct, __CLPK_integer lwork, double* matrix, double* ss, unsigned char* svd_rect_wkspace) {
  double* work = (double*)svd_rect_wkspace;
  double* vv_buf = &(work[lwork]);
  char jobu = 'S';
  char jobvt = 'O';
  __CLPK_integer tmp_m = minor_ct;
  __CLPK_integer tmp_n = major_ct;
  __CLPK_integer info;
  dgesvd_(&jobu, &jobvt, &tmp_m, &tmp_n, matrix, &tmp_m, ss, vv_buf, &tmp_m, nullptr, &tmp_m, work, &lwork, &info);
  return (info != 0);
}

// dsyevr_ takes ~30% less time than dsyevd_ on OS X dev machine.  todo: retest
// for Linux 64-bit MKL.
boolerr_t get_extract_eigvecs_lworks(uint32_t dim, uint32_t pc_ct, __CLPK_integer* lwork_ptr, __CLPK_integer* liwork_ptr, uintptr_t* wkspace_byte_ct_ptr) {
  char jobz = 'V';
  char range = 'I';
  char uplo = 'U';
  __CLPK_integer tmp_n = dim;
  __CLPK_integer il = dim + 1 - pc_ct;
  __CLPK_integer iu = dim;
  double abstol = -1.0;
  __CLPK_integer lwork_dummy = -1;
  double lwork_d;
  __CLPK_integer liwork;
  __CLPK_integer info;
  dsyevr_(&jobz, &range, &uplo, &tmp_n, nullptr, &tmp_n, nullptr, nullptr, &il, &iu, &abstol, nullptr, nullptr, nullptr, &tmp_n, nullptr, &lwork_d, &lwork_dummy, &liwork, &lwork_dummy, &info);
#ifdef LAPACK_ILP64
  if (info) {
    return 1;
  }
#else
  if (info || (lwork_d > 2147483640.0)) {
    return 1;
  }
#endif
  const __CLPK_integer lwork = round_up_pow2((__CLPK_integer)lwork_d, kCacheline / sizeof(double));
  liwork = round_up_pow2(liwork, kCacheline / sizeof(__CLPK_integer));
  *lwork_ptr = lwork;
  *liwork_ptr = liwork;
  *wkspace_byte_ct_ptr = lwork * sizeof(double) + liwork * sizeof(__CLPK_integer) + round_up_pow2(2 * dim * sizeof(__CLPK_integer), kCacheline);
  return 0;
}

boolerr_t extract_eigvecs(uint32_t dim, uint32_t pc_ct, __CLPK_integer lwork, __CLPK_integer liwork, double* matrix, double* eigvals, double* reverse_eigvecs, unsigned char* extract_eigvecs_wkspace) {
  char jobz = 'V';
  char range = 'I';
  char uplo = 'U';
  __CLPK_integer tmp_n = dim;
  __CLPK_integer il = dim + 1 - pc_ct;
  __CLPK_integer iu = dim;
  double abstol = -1.0;
  __CLPK_integer out_m;
  double* work = (double*)extract_eigvecs_wkspace;
  __CLPK_integer* iwork = (__CLPK_integer*)(&(work[lwork]));
  __CLPK_integer* isuppz = &(iwork[liwork]);
  __CLPK_integer info;
  // vl and vu may actually be referenced in some implementations
  double dummy_d = 0.0;
  dsyevr_(&jobz, &range, &uplo, &tmp_n, matrix, &tmp_n, &dummy_d, &dummy_d, &il, &iu, &abstol, &out_m, eigvals, reverse_eigvecs, &tmp_n, isuppz, work, &lwork, iwork, &liwork, &info);
  return (info != 0);
}
#endif // !NOLAPACK

// can't use this, since we need (X^T X)^{-1} for validParameters() check
/*
void linear_regression_first_half(uint32_t sample_ct, uint32_t predictor_ct, double* pheno_d, double* predictors_pmaj, double* xt_y, double* xtx) {
  // Note that only the lower triangle of X^T X is filled.  (well, upper
  // triangle in column-major Fortran notation.)
  multiply_self_transpose(predictors_pmaj, predictor_ct, sample_ct, xtx);
  row_major_matrix_multiply(predictors_pmaj, pheno_d, predictor_ct, 1, sample_ct, xt_y);
}

#ifndef NOLAPACK
boolerr_t linear_regression_second_half(const double* xt_y, uint32_t predictor_ct, double* xtx_destroy, double* fitted_coefs) {
  // See e.g. wls.c in Alex Blocker's go-lm code
  // (https://github.com/awblocker/go-lm ).
  char uplo = 'U';
  __CLPK_integer tmp_n = predictor_ct;
  memcpy(fitted_coefs, xt_y, predictor_ct * sizeof(double));
  __CLPK_integer nrhs = 1;
  __CLPK_integer info;
  dposv_(&uplo, &tmp_n, &nrhs, xtx_destroy, &tmp_n, fitted_coefs, &tmp_n, &info);
  return (info != 0);
}
#endif // !NOLAPACK
*/

// now assumes xtx_inv is predictors_pmaj * transpose on input
// todo: support nrhs > 1 when permutation test implemented
boolerr_t linear_regression_inv(const double* pheno_d, double* predictors_pmaj, uint32_t predictor_ct, uint32_t sample_ct, double* xtx_inv, double* fitted_coefs, double* xt_y, __maybe_unused matrix_invert_buf1_t* mi_buf, __maybe_unused double* dbl_2d_buf) {
  // multiply_self_transpose(predictors_pmaj, predictor_ct, sample_ct, xtx_inv);
  row_major_matrix_multiply(predictors_pmaj, pheno_d, predictor_ct, 1, sample_ct, xt_y);
#ifdef NOLAPACK
  if (invert_symmdef_matrix(predictor_ct, xtx_inv, mi_buf, dbl_2d_buf)) {
    return 1;
  }
  row_major_matrix_multiply(xtx_inv, xt_y, predictor_ct, 1, predictor_ct, fitted_coefs);
  return 0;
#else
  char uplo = 'U';
  __CLPK_integer tmp_n = predictor_ct;
  __CLPK_integer info;
  dpotrf_(&uplo, &tmp_n, xtx_inv, &tmp_n, &info);
  if (info) {
    return 1;
  }
  memcpy(fitted_coefs, xt_y, predictor_ct * sizeof(double));
  __CLPK_integer nrhs = 1;
  dpotrs_(&uplo, &tmp_n, &nrhs, xtx_inv, &tmp_n, fitted_coefs, &tmp_n, &info);
  assert(!info);
  dpotri_(&uplo, &tmp_n, xtx_inv, &tmp_n, &info);
  return (info != 0);
#endif // !NOLAPACK
}

#ifdef __cplusplus
} // namespace plink2
#endif
