#include "mn_determinante.h"
#include "mn_lapack.h"
#include <stdlib.h>
#include <stdio.h>

/** FUNCIÓN QUE CALCULA LA POSICIÓN DE LA DIAGONAL HACIA ABAJO DONDE SE ENCUENTRA
EL MÁXIMO EN VALOR ABSOLUTO DE UNA MATRIZ */
int max_pos(
Array2D< real > &A /** matriz */,
int k /** posición diagonal */){
  real max=fabs(A[k][k]);
  int kmax=k;
  for(int m=k+1;m<A.dim1();m++){
    if(fabs(A[m][k])>max){
      max=fabs(A[m][k]);
      kmax=m;
    }
  }
  return kmax;
}

/// CÁLCULO DEL DETERMINANTE DE UNA MATRIZ USANDO UN ALGORITMO DEL
/// MÉTODO DE GAUSS PARA CONVERTIR A UNA MATRIZ EN TRIANGULAR USANDO PIVOTACIÓN FÍSIC
/// DEVUELVE 0 SI LA MATRIZ ESTÁ VACÍA O NO ES CUADRADA.
/// SE PUEDE USAR LA FUNCION max_pos() PARA CALCULAR EL MÁXIMO DE LA COLUMNA
/// HACIA ABAJO Y mn_pivotar() PARA INTERCAMBIAR DOS VALORES
real mn_determinante_Gauss(Array2D< real > &M)
{
  /// HACER ALUMNO
    Array2D<real> a = M.copy();

    real signo = 1.;

    for(int k = 0; k < a.dim1(); k++){
        int kmax = max_pos(a, k);
        if(kmax != k){
            for(int j = k; j < a.dim1(); j++){
                mn_pivotar(a[k][j], a[kmax][j]);
            }
        }

        for(int i = k + 1; i < a.dim1(); i++){
            real m = -a[i][k] / a[k][k];
            a[i][k] = 0.;
            for(int j = k + 1; j < a.dim1(); j++){
                a[i][j] += m * a[k][j];
            }
        }
    }

    real det = signo;
    for(int i = 0; i < a.dim1(); i++) det *= a[i][i];
    return det;
}

