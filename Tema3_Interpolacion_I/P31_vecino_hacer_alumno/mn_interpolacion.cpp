#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"

/// INTERPOLACION VECINO
real mn_interpolacion_vecino(
Array1D<real> &x, /// puntos de interpolación
Array1D<real> &f, /// valores de función en los puntos de interpolación
real x0)  /// punto donde se evalua la función interpolada
{
  /// HACER ALUMNO

    int N = x.dim();

    if(x0 <= x[0]) return f[0];

    if(x0 >= x[N - 1]) return f[N - 1];

    for(int i = 0; i < N - 1; i++){
        if(x[i] <= x0 && x0 <= x[i + 1]){
            if(mn_abs(x0 - x[i]) <= mn_abs(x0 - x[i + 1])){
                return f[i];
            } else {
                return f[i + 1];
            }
        }
    }
    return -1;

}



