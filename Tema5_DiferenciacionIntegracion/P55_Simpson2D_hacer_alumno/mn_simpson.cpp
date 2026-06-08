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

    for(int k = 0; k <= M; k++){
        real x = a + hx*k;
        real wx;
        if(k == 0 || k == M)    wx = 1.;
        else if(k % 2 != 0) wx = 4.;
        else    wx = 2.;

        for(int n = 0; n <= N; n++){
            real y = c + hy * n;
            real wy;
            if(n == 0 || n == N)    wy = 1.;
            else if(n % 2 != 0) wy = 4.;
            else    wy = 2.;
            integral += wx*wy*F(x, y);
        }
    }
    return integral * hy * hx / 9.;

}

