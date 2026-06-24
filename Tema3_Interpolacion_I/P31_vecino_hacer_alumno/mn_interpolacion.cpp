#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"

/// INTERPOLACION VECINO
real mn_interpolacion_vecino(
Array1D<real> &x, /// puntos de interpolación
Array1D<real> &f, /// valores de función en los puntos de interpolación
real x0)  /// punto donde se evalua la función interpolada
{
  /// HACER ALUMNO
    int mejor = 0;              //Para saber cual es mejor
    for(int i = 1; i < x.dim(); i++){
        if(mn_abs(x0 - x[i]) < mn_abs(x0 - x[mejor])) mejor = i;    //Si la distancia entre x0 - xi es menor que x0-x[mejor] significa que el indice en i es mejor
    }
    return f[mejor];    //Se devuelve la opcion mas cercana
}


