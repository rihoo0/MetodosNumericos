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

/// FUNCION QUE IMPLEMENTA EL CALCULO DE LAS RAICES DE UN POLINOMIO DE GRADO 2
/// DEVUELVE EL NÚMERO DE RAÍCES OBTENIDAS
/// LAS RAÍCES SALEN ORDENADAS POR VALOR ABSOLUTO. ES DECIR |x1|<=|x2|
int mn_ceros_pol_grado_2(
real a, real b, real c, // coeficientes polinomio de grado 2
real &x1, // primera raíz
real &x2) // segunda raíz
{
  if(a==0.) return(0);
  real dis=b*b-4*a*c;
  if(dis<0.) return(0);
  else if(dis==0.){
    x1=-b/(2*a);
    return(1);
  }
  dis=sqrt(dis);
  if(b>0){
    x1=(-b+dis)/(2*a);
    x2=(-b-dis)/(2*a);
  }
  else{
    x1=(-b-dis)/(2*a);
    x2=(-b+dis)/(2*a);
  }
  return(2);
}

/// FUNCION QUE IMPLEMENTA EL METODO DE MULLER USANDO UNA APROXIMACIÓN DE LAS DERIVADAS
/// LA FUNCIÓN DEVUELVE EL NÚMERO DE ITERACIONES REALIZADAS SI TERMINA BIEN Y DEVUELVE -1
/// EN CASO CONTRARIO
int mn_muller (
real (*f)( real), /// funcion sobre la que se calcula el cero
real &x0, /// raíz inicial que actualiza la función
int NiterMax, /// número de iteraciones máximo
real TOL) /// tolerancia para parar el algoritmo
{

    ///HACER ALUMNO

    real f_x0 = f(x0);

    for(int Niter = 0; Niter < NiterMax; Niter++){

        if(f_x0 == 0) return Niter;

        real z1, z2;
        real fp = mn_derivada1(f, x0);
        real fpp = mn_derivada2(f, x0);


        real Nroots = mn_ceros_pol_grado_2(fpp / 2, fp, f_x0, z1, z2);

        if(Nroots == 0) return Niter;

        real x1 = x0 + z1;

        if(mn_distancia(x1, x0) < TOL){
            x0 = x1;
            return Niter + 1;
        }

        x0 = x1;
        f_x0 = f(x0);

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

/// APROXIMACIÓN DERIVADA SEGUNDA DE UNA FUNCIÓN
real mn_derivada2(
real (*f)( real), /// función que se deriva
real x) /// punto donde se evalúa la derivada primera
{
   /// CALCULO DE LA RAIZ CUADRADA DE LA UNIDAD DE REDONDEO u
   static real sqrt_u = sqrt( (double) mn_precision_aritmetica());

   /// CALCULO DESPLAZAMIENTO DE x PARA CALCULAR LA DERIVADA
   /// NOS ALEJAMOS DE x CON LA MITAD DE BITS QUE PERMITE LA ARITMÉTICA
   real h=(mn_abs(x)+1.)*sqrt_u;

   return (f(x+h)+f(x-h)-2*f(x))/(h*h);

}
