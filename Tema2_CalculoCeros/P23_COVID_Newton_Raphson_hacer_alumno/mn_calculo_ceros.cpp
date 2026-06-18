<<<<<<< HEAD
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

/// FUNCION QUE IMPLEMENTA EL METODO DE NEWTON-RAPHSON APROXIMANDO LA FUNCION DERIVADA
/// LA FUNCIÓN DEVUELVE EL NÚMERO DE ITERACIONES REALIZADAS SI TERMINA BIEN Y DEVUELVE -1
/// EN CASO CONTRARIO
int mn_newton_raphson (
real (*f)( real), /// funcion sobre la que se calcula el cero
real &x0, /// raíz inicial que actualiza la función
int NiterMax, /// número de iteraciones máximo
real TOL) /// tolerancia para parar el algoritmo
{
  /// HACER ALUMNO
    real f_x0 = f(x0);
    real x1;
    real derivada;
    for(int Niter = 0; Niter < NiterMax; Niter++){

        if(f_x0 == 0) return Niter;

        derivada = mn_derivada1(f, x0);
        if(derivada == 0) return Niter;

        x1 = x0 - (f_x0 / derivada);
        f_x0 = f(x1);

        if(mn_distancia(x1, x0) < TOL){
            x0 = x1;
            return Niter + 1;
        }
        x0 = x1;
    }
    return -1;
}



/// APROXIMACIÓN DERIVADA PRIMERA DE UNA FUNCIÓN
real mn_derivada1(
real (*f)( real), /// función que se deriva
real x) /// punto donde se evalúa la derivada primera
{
   /// CALCULO DE LA RAIZ CUADRADA DE LA UNIDAD DE REDONDEO u
   static real sqrt_u = sqrt( (double) mn_precision_aritmetica());

   /// CALCULO DESPLAZAMIENTO DE x PARA CALCULAR LA DERIVADA
   /// NOS ALEJAMOS DE x CON LA MITAD DE BITS QUE PERMITE LA ARITMÉTICA
   real h=(mn_abs(x)+1.)*sqrt_u;

   return (f(x+h)-f(x-h))/(2.*h);

}
=======
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

/// FUNCION QUE IMPLEMENTA EL METODO DE NEWTON-RAPHSON APROXIMANDO LA FUNCION DERIVADA
/// LA FUNCIÓN DEVUELVE EL NÚMERO DE ITERACIONES REALIZADAS SI TERMINA BIEN Y DEVUELVE -1
/// EN CASO CONTRARIO
int mn_newton_raphson (
real (*f)( real), /// funcion sobre la que se calcula el cero
real &x0, /// raíz inicial que actualiza la función
int NiterMax, /// número de iteraciones máximo
real TOL) /// tolerancia para parar el algoritmo
{
  /// HACER ALUMNO
    real fx0 = f(x0);                               //Se calcula el valor de x0 en la funcion

    for(int i = 0; i < NiterMax; i++){             //Se hace un bucle para llegar al limite de las iteraciones dadas por el ejercicio
        if(fx0 == 0) return i;                      //Si x0 en f ==, tenemos el punto que buscamos, por tanto devolvemos el Niter

        real derivada = mn_derivada1(f, x0);        //Se calcula la derivada de x0 en f
        if(derivada == 0) return -1;                //Si la derivada vale 0 se devuelve -1

        real x1 = x0 - (fx0/derivada);              //Calculamos el valor de x1 y comprobamos
        if(mn_distancia(x1, x0) < TOL){
            x0 = x1;
            return i;                               //Si la distancia es menor modulo de una TOL se indica que x0 = x1 y se devuelve el numero de iteraciones
        }

        x0 = x1;
        fx0 = f(x1);                                //Cambiamos los valores para continuar buscando
    }
    return -1;
}



/// APROXIMACIÓN DERIVADA PRIMERA DE UNA FUNCIÓN
real mn_derivada1(
real (*f)( real), /// función que se deriva
real x) /// punto donde se evalúa la derivada primera
{
   /// CALCULO DE LA RAIZ CUADRADA DE LA UNIDAD DE REDONDEO u
   static real sqrt_u = sqrt( (double) mn_precision_aritmetica());

   /// CALCULO DESPLAZAMIENTO DE x PARA CALCULAR LA DERIVADA
   /// NOS ALEJAMOS DE x CON LA MITAD DE BITS QUE PERMITE LA ARITMÉTICA
   real h=(mn_abs(x)+1.)*sqrt_u;

   return (f(x+h)-f(x-h))/(2.*h);

}
>>>>>>> 6afedf6becadd2a3b25221d7d4400d720c22d1ef
