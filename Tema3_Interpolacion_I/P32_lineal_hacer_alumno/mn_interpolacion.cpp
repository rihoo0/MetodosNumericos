#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"

/// INTERPOLACION LINEAL
real mn_interpolacion_lineal(
Array1D<real> &x, /// puntos de interpolación
Array1D<real> &f, /// valores de función en los puntos de interpolación
real x0)  /// punto donde se evalua la función interpolada
{
  /// HACER ALUMNO

    int N = x.dim();

    if(x0 <= x[0]){ ///Se comprueba si el valor esta por debajo del valor en la posicion 0
        return f[0] + ((f[1] - f[0])/(x[1] - x[0])) * (x0 - x[0]);
    }

    if(x0 >= x[N - 1]){ ///Se comprueba si elv alor esta por arriba del valor en la ultima posicion
        return f[N - 2] + ((f[N - 1] - f[N - 2])/(x[N - 1] - x[N - 2])) * (x0 - x[N - 2]);
    }

    for(int i = 0; i < N - 1; i++){
        if(x[i] <= x0 && x0 <= x[i + 1]){   ///Se comprueba si el valor esta entre el valor actual y el siguiente
            return f[i] + ((f[i + 1] - f[i])/(x[i + 1] - x[i])) * (x0 - x[i]);
        }
    }
    return -1;

}



