#include "mn_calculo_de_ceros.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

/// PARAMETROS DE LA DISTRIBUCION GAMMA
real alfa,beta1,d;

/// DISTRIBUCIÓN GAMMA
real Gamma(real x){
  if(x<0) return 0;
  return d*pow(x,alfa-1.)*exp(-beta1*x);
}

/// DERIVADA DE LA DISTRIBUCIÓN GAMMA
real Gammap(real x){
  if(x<0) return 0;
  return d*(alfa-1)*pow(x,alfa-2.)*exp(-beta1*x)-d*beta1*pow(x,alfa-1.)*exp(-beta1*x);
}

/// CALCULO DE LOS PARÁMETROS DE LA DISTRIBUCIÓN GAMMA A PARTIR DE LA
/// MEDIA Y VARIANZA MUESTRAL
void calculo_parametros_Gamma(real media, real varianza){
  /// calculo de alfa y beta1
  beta1=media/varianza;
  alfa=media*beta1;

  /// calculo de d a través de la integral (se verá en el tema 5)
  real h=0.001;
  real suma=0;
  for(real x=0;x<100;x+=h) suma+=h*pow(x,alfa-1.)*exp(-beta1*x);
  d=1./suma;

  cout << "\nalfa = " << alfa << " beta1 = " << beta1 << " d = " << d << "\n";

}


/// FUNCION QUE IMPLEMENTA EL METODO DE LA REGULA FALSI  Y DEVUELVE EL NÚMERO DE ITERACIONES
/// SI ALGO VA MAL DEVUELVE -1.  LA RAÍZ SE DEVUELVE COMO PARÁMETRO
int mn_regula_falsi (
real (*f)( real), /// función a la cual se calcula un cero
real &a, real &b, /// intervalo inicial para buscar la raíz
real &x, /// valor de salida de la raíz
real TOL,  /// tolerancia para parar las iteraciones del algoritmo
int NiterMax) /// número máximo de iteraciones permitidas
{
  /// HACER ALUMNO
    real fa = f(a);
    real fb = f(b);
    x = a-((b - a)/(fb - fa))*fa;
    real fx =f(x);

    for(int i = 0; i < NiterMax;i++){
        if(fa * fb > 0) return -1;
        if(fx == 0) return i;

        if(fa * fx < 0){
            b = x;
            fb = fx;
        } else {
            a = x;
            fa = fx;
        }
        real xnew = a-((b - a)/(fb - fa))*fa;;
        if(mn_distancia(x, xnew) <= TOL){
            x = xnew;
            return i;
        }
        x = xnew;
        fx = f(x);
    }
    return -1;
}



