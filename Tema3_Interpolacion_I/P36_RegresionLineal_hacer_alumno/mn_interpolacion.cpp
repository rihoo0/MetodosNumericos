#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"

///* FUNCION QUE CALCULA LA RECTA DE REGRESION LINEAL y=ax+b PARA APROXIMAR UNA
/// NUBE DE PUNTOS (x[k],y[k]). LA FUNCION DEVUELVE 0 SI TERMINA BIEN Y -1 SI
/// TERMINA MAL
/// */
int mn_regresion_lineal(
Array1D< real > &x, /// VECTOR DE COORDENADAS x DE LA NUBE DE PUNTOS
Array1D< real > &y, /// VECTOR DE COORDENADAS y DE LA NUBE DE PUNTOS
real &a, /// COMPONENTE a DE LA RECTA DE REGRESIÓN. (PARÁMETRO DE SALIDA)
real &b) /// COMPONENTE b DE LA RECTA DE REGRESIÓN. (PARÁMETRO DE SALIDA)
{
  ///HACER ALUMNO
    if(x.dim() != y.dim() || x.dim() == 0) return -1;

    int N = x.dim();
    real sx=0, sy=0, sxx=0, sxy=0;
    for(int i = 0; i < N; i++){
        sx += x[i];
        sy += y[i];
        sxy += x[i] * y[i];
        sxx += x[i] * x[i];
    }
    if((N*sxx - sx*sx) == 0) return -1;
    a = (N*sxy - sx*sy) / (N*sxx - sx*sx);
    b = (sxx*sy - sxy*sx) / (N*sxx - sx*sx);

    return 0;
}



