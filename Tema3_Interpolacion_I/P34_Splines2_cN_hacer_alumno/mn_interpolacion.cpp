#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"

/**
 LA INTERPOLACION POR SPLINES DE GRADO 2 SEG⁄N SE EXPLIC” EN CLASE.
 EN ESTE CASO SE SUPONE CONOCIDO EL ⁄LTIMO VALOR DEL VECTOR c Y SE CALCULA EL RESTO DE COEFICIENTES
 LA FUNCION DEVUELVE -1 SI ENCUENTRA ALG⁄N PROBLEMA Y 0 EN CASO CONTRARIO
*/
int mn_calculo_splines_2(
const Array1D< real > &x, /// vector con los puntos de interpolaciÛn
const Array1D< real > &f, /// vector con los valores de la funciÛn
const real &cLast,        /// ˙ltimo valor del vector c[] asignado como par·metro
Array1D< real > &a,       /// vector de salida con los coeficientes a[i] del spline de grado 2
Array1D< real > &b,       /// vector de salida con los coeficientes b[i] del spline de grado 2
Array1D< real > &c)       /// vector de salida con los coeficientes c[i] del spline de grado 2
{
  /// HACER ALUMNO
    int dim = x.dim() - 1;
    a = Array1D<real>(dim);
    b = Array1D<real>(dim);
    c = Array1D<real>(dim);
    
    for(int i = 0; i < dim; i++) a[i] = f[i];
    real hLast = x[dim] - x[dim - 1];
    if(hLast == 0) return -1;
    b[dim - 1] = (f[dim] - f[dim - 1]) / hLast - cLast * hLast;    c[dim - 1] = cLast;
    
    for(int i = dim - 1; i > 0; i--){
            real h = x[i] - x[i - 1];
            if(h == 0) return -1;
            c[i - 1] = (f[i - 1] - f[i] + b[i] * h) / (h * h);
            b[i - 1] = b[i] - 2 * c[i - 1] * h;
        }
    return 0;

}

/**
  EVALUACI”N SPLINE DE GRADO DOS. SE DEVUELVE EL VALOR DE LA
  EVALUACI”N EN x0
*/
real mn_evaluar_splines_2(
const Array1D< real > &x,
Array1D< real > &a,
Array1D< real > &b,
Array1D< real > &c,
real x0 ){
  /// HACER ALUMNO
    int dim = a.dim();
        for(int i = dim - 1; i > 0; i--){
            if(x0 >= x[i]) return a[i] + b[i]*(x0 - x[i]) + c[i]*(x0 - x[i])*(x0 - x[i]);
        }
        return a[0] + b[0]*(x0 - x[0]) + c[0]*(x0 - x[0])*(x0 - x[0]);
}

