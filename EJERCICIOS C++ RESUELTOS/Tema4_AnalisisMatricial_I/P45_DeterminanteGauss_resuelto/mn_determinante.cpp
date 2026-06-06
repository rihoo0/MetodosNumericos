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
  if(M.dim1()==0 || M.dim1()!=M.dim2()) return 0.;

  Array2D< real > A=M.copy();
  real determinante;

  int Npiv=0;
  for(int k=0;k<A.dim1();k++){
    int kmax=max_pos(A,k);
    if(A[kmax][k]==0.) return 0.;

    if(kmax!=k){
      Npiv++;
      for(int i=0;i<A.dim1();i++) mn_pivotar(A[k][i],A[kmax][i]);
    }

    for(int j=k+1;j<A.dim1();j++){
        real mul=-A[j][k]/A[k][k];
        A[j][k]=0.;
        for(int n=k+1;n<A.dim1();n++) A[j][n]+=mul*A[k][n];
    }
  }

  determinante=1;
  for(int k=0;k<A.dim1();k++) determinante*=A[k][k];

  if(Npiv%2==1) return(-determinante);
  return determinante;

}

