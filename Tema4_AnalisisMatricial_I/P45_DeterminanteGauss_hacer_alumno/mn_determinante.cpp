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

    real deter = 1.;

    for(int k = 0; k < M.dim1(); k++){
        int kmax = max_pos(M, k);
        if(kmax != k){
            for(int j = 0; j < M.dim1(); j++){
                mn_pivotar(M[k][j], M[kmax][j]);
            }
            deter *= -1.;
        }
        for(int i = k + 1; i < M.dim1(); i++){
            real m = -M[i][k] / M[k][k];
            for(int j = k + 1; j < M.dim1(); j++) M[i][j] += m * M[k][j];
        }
    }
    for(int k = 0; k < M.dim1(); k++) deter *= M[k][k];
    return deter;
}

