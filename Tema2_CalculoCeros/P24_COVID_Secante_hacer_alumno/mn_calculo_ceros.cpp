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


/// FUNCION QUE IMPLEMENTA EL METODO DE LA SECANTE
/// LA FUNCIÓN DEVUELVE EL NÚMERO DE ITERACIONES REALIZADAS SI TERMINA BIEN Y DEVUELVE -1
/// EN CASO CONTRARIO
int mn_secante (
real (*f)( real), /// funcion sobre la que se calcula el cero
real &x0, /// primera aproximación raíz que actualiza la función
real &x1, /// segunda aproximación raíz que actualiza la función
int NiterMax, /// número de iteraciones máximo
real TOL) /// tolerancia para para el algoritmo
{
  /// HACER ALUMNO
    for(int i = 0; i < NiterMax; i++){
        real fx0 = f(x0);
        real fx1 = f(x1);

        if(fx1 == 0) return i;
        if(fx1 == fx0) return -1;

        real x2 = x1 - fx1 * ((x1 -x0) / (fx1 -fx0));

        if(mn_distancia(x2, x1) < TOL){
            x0 = x1;
            x1 = x2;
            return i + 1;
        }
        x0 = x1;
        x1 = x2;
    }
    return -1;
}

