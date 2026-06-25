#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"

/// FUNCIÓN PARA CALCULAR UN ZOOM DE FACTOR z A UN Array2D< real >
/// USANDO INTERPOLACIÓN POR EL VECINO MÁS CERCANO
/// SE CONSIDERA QUE LA DISTANCIA ENTRE LOS PIXELS DEL Array2D ES 1
/// DADO UN PUNTO EN LA IMAGEN DE ÍNDICES (i,j) SI AL ACCEDER AL
/// PUNTO (i+1,j) NOS SALIMOS DE LA IMAGEN, TOMAMOS EN SU LUGAR EL PUNTO (i,j)
/// LO MISMO SI NOS SALIMOS AL ACCEDER A (i,j+1) O (i+1,j+1)
Array2D< real > zoom_vecino(
Array2D< real > &A /** IMAGEN ORIGINAL */,
real z /** FACTOR DE ZOOM */)
{
  /// HACER ALUMNO

  Array2D<real> F(z * A.dim1(), z*A.dim2());
  int dF1 = F.dim1();
  int dF2 = F.dim2();

  for(int ip = 0; ip < dF1; ip++){
    for(int jp = 0; jp < dF2; jp++){
        real x = ip/z;
        real y = jp/z;
        int i = x;
        int j = y;
        if((x-i)>0.5 && i+1<A.dim1()) i=i+1;
        if((y-j)>0.5 && j+1<A.dim2()) j=j+1;
        F[ip][jp] = A[i][j];
    }
  }
  return F;
}
