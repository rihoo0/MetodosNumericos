#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"

/// INTERPOLACION LINEAL
real mn_interpolacion_lineal(
Array1D<real> &x, /// puntos de interpolación
Array1D<real> &f, /// valores de función en los puntos de interpolación
real x0)  /// punto donde se evalua la función interpolada
{
  /// HACER ALUMNO
    
    for(int i = x.dim() - 2; i > 0; i--){
        if(x[i] < x0) return f[i] + ((f[i + 1] - f[i]) / (x[i + 1] - x[i])) * (x0 - x[i]);
    }
    return  f[0] + ((f[1] - f[0]) / (x[1] - x[0])) * (x0 - x[0]);
}



