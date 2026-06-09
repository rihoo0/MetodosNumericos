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


/// FUNCION QUE IMPLEMENTA EL METODO DE LA BISECCION
real mn_biseccion (
real (*f)(const real), /// función a la cual se calcula un cero
real &a, real &b, /// intervalo inicial para buscar la raíz
const real TOL,  /// tolerancia para parar las iteraciones del algoritmo
int &Niter) /// número de iteraciones realizadas por el método
            ///       Si Niter=-1 la función ha terminado mal
{

  /// HACER ALUMNO
    real fa = f(a);
    real fb = f(b);

    if(fa * fb > 0){
        Niter = -1.;
        return 0;;
    }
    Niter = 0.;
    while(mn_distancia(a, b) >= TOL){
        real m = (a + b) * 0.5;
        real fm = f(m);
        if(fm == 0) return m;
        if(fa * fm < 0){
            b = m;
            fb = fm;
        } else{
            a=  m;
            fa = fm;
        }
        Niter++;
    }
    return (a + b) * 0.5;
}



