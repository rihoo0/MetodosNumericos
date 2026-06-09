#include "mn_simpson.h"
#include <stdio.h>

/************************************************************
// FUNCIÓN PARA CALCULAR UNA INTEGRAL POR EL METODO DE SIMPSON
// DE UNA FUNCION DE 2 VARIABLES EN [a,b]x[c,d]
// RETORNA EL VALOR DE LA INTEGRAL
//************************************************************/
real mn_simpson_2D(
real (*F)(real x,real y) /** funcion que se integra */,
real a /** extremo izquierdo del intervalo x */,
real b /** extremo derecho del invervalo x */,
real c /** extremo izquierdo del intervalo y */,
real d /** extremo derecho del invervalo y */,
int M /** numero de intervalos en x para calcular la integral */,
int N /** numero de intervalos en y para calcular la integral */)
{
   /** HACER ALUMNO.*/
    real integral = 0.;
    real hx = (b - a) / M;
    real hy = (d - c) / N;
    for(int i = 0; i <= M; i++){
        real x = a + hx * i;
        real wx;
        if(i == 0 || i == M) wx = 1.;
        else if(i % 2 != 0) wx = 4.;
        else    wx = 2.;

        for(int j = 0; j <= N; j++){
            real y = c + hy * j;
            real wy;
            if(j == 0 || j == N) wy = 1.;
            else if(j % 2 != 0) wy = 4.;
            else    wy = 2.;
            integral += F(x, y) * wx * wy;
        }
    }
    return integral * hy * hx /9.;
}

