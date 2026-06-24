#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"

/**
 LA INTERPOLACION POR SPLINES DE GRADO 2 SEGÚN SE EXPLICÓ EN CLASE.
 EN ESTE CASO SE SUPONE CONOCIDO c[0] Y SE CALCULA EL RESTO DE COEFICIENTES
 LA FUNCION DEVUELVE -1 SI ENCUENTRA ALGÚN PROBLEMA Y 0 EN CASO CONTRARIO
*/
int mn_calculo_splines_2(
 Array1D< real > &x, /// vector con los puntos de interpolación
 Array1D< real > &f, /// vector con los valores de la función
 real &c0,           /// valor de c[0] asignado como parámetro
Array1D< real > &a,       /// vector de salida con los coeficientes a[i] del spline de grado 2
Array1D< real > &b,       /// vector de salida con los coeficientes b[i] del spline de grado 2
Array1D< real > &c)       /// vector de salida con los coeficientes c[i] del spline de grado 2
{
  /// HACER ALUMNO
    if(x.dim() != f.dim() || f.dim() < 2) return -1;

    a = Array1D<real>(x.dim() - 1);
    b = Array1D<real>(x.dim() - 1);
    c = Array1D<real>(x.dim() - 1);

    a[0] = f[0];
    b[0] = (f[1] - f[0] - c0 * ((x[1] - x[0]) * (x[1] - x[0]))) / (x[1] - x[0]);
    c[0] = c0;

    for(int i = 1; i < a.dim(); i++){
        a[i] = f[i];
        b[i] = b[i - 1] + 2 * c[i - 1] * (x[i] - x[i - 1]);
        c[i] = (f[i + 1] - f[i] - b[i] * (x[i + 1] - x[i])) / ((x[i + 1] - x[i]) * (x[i + 1] - x[i]));
    }
    return 0;
}

/**
  EVALUACIÓN SPLINE DE GRADO DOS. SE DEVUELVE EL VALOR DE LA
  EVALUACIÓN EN x0
*/
real mn_evaluar_splines_2(
Array1D< real > &x,
Array1D< real > &a,
Array1D< real > &b,
Array1D< real > &c,
real x0 ){
  /// HACER ALUMNO
    for(int i = a.dim() - 1; i >= 0; i--){
        if(x[i] < x0) return a[i] + (b[i] + c[i] * (x0 - x[i])) * (x0 - x[i]);
    }

    return a[0] + (b[0] + c[0] * (x0 - x[0])) * (x0 - x[0]);
}

