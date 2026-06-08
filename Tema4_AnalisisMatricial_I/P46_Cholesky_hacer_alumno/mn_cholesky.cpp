#include "mn_cholesky.h"
#include "mn_lapack.h"
#include <stdlib.h>
#include <stdio.h>

/// Función que calcula las matrices de descomposición de Cholesky. Se implementa
///   en una sola matriz pues se trata de una matriz triangular inferior y su traspuesta
Array2D< real > mn_cholesky_factorization(const Array2D< real > &A)
{
   /// HACER ALUMNO
    int N = A.dim1();
    if(A.dim1() != A.dim2()) return Array2D<real>();

    Array2D<real> B(N, N);

    for(int i = 0; i < N; i++){
        real sum = 0.;
        for(int k = 0; k < i; k++) sum += B[i][k] * B[i][k];

        if(A[i][i] < sum) return Array2D<real>();
        B[i][i] = sqrt(A[i][i] - sum);

        for(int j = i + 1; j < N; j++){
            sum = 0.;
            for(int k = 0; k < i; k++) sum += B[j][k] * B[i][k];
            if(A[i][i] < sum) return Array2D<real>();

            B[j][i] = (A[j][i] - sum) / B[i][i];
            B[i][j] = B[j][i];
        }
    }
    return B;
}


/// FUNCION PARA RESOLVER UN SISTEMA POR EL METODO DE CHOLESKY
Array1D< real > mn_cholesky (const Array2D< real > &A, const Array1D< real > &b)
{
    /// HACER ALUMNO
    Array2D<real> CH = mn_cholesky_factorization(A);
    if(CH.dim1() == 0) return Array1D<real>();

    Array1D<real> z = mn_descenso(CH, b);
    if(z.dim1() == 0) return Array1D<real>();

    Array1D<real> u = mn_remonte(CH, z);
    if(u.dim1() == 0) return Array1D<real>();
    return u;
}

/// FUNCION PARA RESOLVER UN SISTEMA TRIANGULAR INFERIOR
Array1D< real > mn_descenso (const Array2D< real > &B, const Array1D< real > &b)
{
   int i,j;
   if(B.dim1()!=B.dim2() || B.dim1()!=b.dim() ) return(Array1D< real >());
   int N=B.dim1();
   Array1D< real > z(N);

   /// INICIAMOS EL DESCENSO
   for (i=0;i<N;i++){
      if (B[i][i]==0) { /// comprobamos que la diagonal es distinto de cero
         return(Array1D< real >());
      }
      z[i]=b[i]; /// inicializamos la solucion
      for (j=0;j<i;j++){ /// aplicamos la formula para calcular la solucion
         z[i]=z[i] - B[i][j]*z[j];
      }
      z[i]=z[i]/B[i][i];
  }
  return(z);
}

/// FUNCION PARA RESOLVER UN SISTEMA TRIANGULAR SUPERIOR
Array1D< real > mn_remonte (const Array2D< real > &B, const Array1D< real > &z)
{
   int i,j;
   if(B.dim1()!=B.dim2()  || B.dim1()!=z.dim() ) return(Array1D< real >());
   int N=B.dim1();
   Array1D< real > DU(N);

   /// INICIAMOS EL REMONTE
   for (i=N-1;i>=0;i--){
      if (B[i][i]==0){  /// comprobamos que la diagonal es distinto de cero
         return(Array1D< real >());
      }
      DU[i]=z[i]; /// inicializamos la solucion
      for  (j=i+1;j<N;j++){ /// aplicamos la formula para calcular la solución
         DU[i]=DU[i] - B[i][j]*DU[j];
      }
      DU[i]=DU[i]/B[i][i];
  }
  return(DU);
}
