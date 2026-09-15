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
    int N = x.dim();
    
    real xy = 0;
    for(int i = 0; i < N; i++) xy += x[i] * y[i];
    
    real xi = 0;
    for(int i = 0; i < N; i++) xi += x[i];
    
    real yi = 0;
    for(int i = 0; i < N; i++) yi += y[i];
    
    real x2 = 0;
    for(int i = 0; i < N; i++) x2 += x[i] * x[i];
    
    a = (N * xy - xi*yi) / (N * x2 - (xi * xi));
    b = (x2 * yi - xy * xi) / (N * x2 - (xi * xi));
    
    return 0;

}



