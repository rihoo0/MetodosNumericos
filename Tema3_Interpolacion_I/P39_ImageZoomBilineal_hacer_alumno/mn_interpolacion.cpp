#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"

/// FUNCI�N PARA CALCULAR UN ZOOM DE FACTOR z A UN Array2D< real >
/// USANDO INTERPOLACI�N BILINEAL
/// SE CONSIDERA QUE LA DISTANCIA ENTRE LOS PIXELS DEL Array2D ES 1
/// DADO UN PUNTO EN LA IMAGEN DE �NDICES (i,j) SI AL ACCEDER AL
/// PUNTO (i+1,j) NOS SALIMOS DE LA IMAGEN, TOMAMOS EN SU LUGAR EL PUNTO (i,j)
/// LO MISMO SI NOS SALIMOS AL ACCEDER A (i,j+1) O (i+1,j+1)
Array2D< real > zoom_bilineal(
Array2D< real > &A /** IMAGEN ORIGINAL */,
real z /** FACTOR DE ZOOM */)
{
  /// HACER ALUMNO
  int dim1New=A.dim1()*z;
  int dim2New=A.dim2()*z;

  if(dim1New<=0 || dim2New<=0) return Array2D< real >();

  Array2D< real > B(dim1New,dim2New);

  for(int ip=0;ip<B.dim1();ip++){
    for(int jp=0;jp<B.dim2();jp++){
      real x=ip/z;
      real y=jp/z;
      int i=x;
      int j=y;
      int i1=min(i+1,A.dim1()-1);
      int j1=min(j+1,A.dim2()-1);
      real dx=x-i;
      real dy=y-j;
      B[ip][jp] = (1.-dy) * ( (1.-dx)*A[i][j] + dx*A[i1][j] ) +
                      dy  * ( (1.-dx)*A[i][j1] + dx*A[i1][j1] );
    }
  }
  return B;
}
