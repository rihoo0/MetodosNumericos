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

    int vecino = 0;
    real dis_min = mn_abs(x0 - x[0]);

    for(int i = 1; i < N; i ++){
        real dist = mn_abs(x0 - x[i]);
        if(dist < dis_min){
            dis_min = dist;
            vecino = i;
        }
    }
    return f[vecino];

}
