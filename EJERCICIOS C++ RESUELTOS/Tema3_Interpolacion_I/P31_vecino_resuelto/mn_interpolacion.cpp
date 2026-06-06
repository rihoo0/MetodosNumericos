#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"

/// INTERPOLACION VECINO
real mn_interpolacion_vecino(
Array1D<real> &x, /// puntos de interpolación
Array1D<real> &f, /// valores de función en los puntos de interpolación
real x0)  /// punto donde se evalua la función interpolada
{
  /// HACER ALUMNO
  for(int i=f.dim()-2; i>=0; i=i-1){
    if( x[i]<x0 ){
      if( (x0-x[i])<=mn_abs(x0-x[i+1]) ) return f[i];
      else return f[i+1];
    }
  }
  return f[0];
}



