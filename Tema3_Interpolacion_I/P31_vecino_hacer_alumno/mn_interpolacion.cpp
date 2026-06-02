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

    if(x0 <= x[0]) return f[0];  ///Se comprueba si esta por debajo del primer valor

    if(x0 >= x[N - 1]) return f[N - 1]; ///Se comprueba si el valor esta por encima del ultimo valor

    for(int i = 0; i < N - 1; i++){
            if(mn_abs(x0 - x[i]) <= mn_abs(x0 - x[i + 1])){ ///S
        if(x[i] <= x0 && x0 <= x[i + 1]){   ///Se comprueba si x0 esta entre el valor actual y el siguiente
                return f[i];    ///Si es menor es menor que el siguiente se devuelve el valor actual
            } else {
                return f[i + 1];    ///Si es mayor se devuelve el siguiente
            }
        }
    }
    return -1;

}



