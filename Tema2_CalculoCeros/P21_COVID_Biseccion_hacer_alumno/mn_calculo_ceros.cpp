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


/// FUNCION QUE IMPLEMENTA EL METODO DE LA BISECCION
real mn_biseccion (
real (*f)(const real), /// función a la cual se calcula un cero
real &a, real &b, /// intervalo inicial para buscar la raíz
const real TOL,  /// tolerancia para parar las iteraciones del algoritmo
int &Niter) /// número de iteraciones realizadas por el método
            ///       Si Niter=-1 la función ha terminado mal
{

  /// HACER ALUMNO
  ///a y b son los puntos y f es la funcion que hay que dividir para calcular los ceros
  real f_a = f(a);
  real f_b = f(b);

  if(f_a * f_b > 0.){
    Niter = -1;
    return(-1.);
  }

  Niter = 0;
  while(mn_distancia(a, b) >= TOL){
    real paso = (a + b) * 0.5;
    real f_paso = f(paso);

    if(f_paso == 0.) return paso;
    if(f_a * f_paso < 0.){
        b = paso;
        f_b = f_paso;
    } else {
        a = paso;
        f_a = f_paso;
    }
    Niter++;
  }
  return ((a + b) * 0.5);
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


/// FUNCION QUE IMPLEMENTA EL METODO DE LA BISECCION
real mn_biseccion (
real (*f)(const real), /// función a la cual se calcula un cero
real &a, real &b, /// intervalo inicial para buscar la raíz
const real TOL,  /// tolerancia para parar las iteraciones del algoritmo
int &Niter) /// número de iteraciones realizadas por el método
            ///       Si Niter=-1 la función ha terminado mal
{

  /// HACER ALUMNO
    //Se comprueba los puntos a y b
    real fa = f(a);
    real fb = f(b);

    if(fa * fb > 0){Niter = -1; return 0.;} //Si la funcion tiene signo postivo no hacemos iteracion pq estamos en el punto 0.
    Niter = 0;
    //Mientras la distancia modulo a y b sea mayor que la toleracia comprobamos y avanazamos para hayar el punto que buscamos
    while(mn_distancia(a, b) > TOL){
        real m = (a + b) * 0.5; //Calculamos el punto medio m
        real fm = f(m);         //Y si valor en la funcion
        Niter++;                //Aumentamos el numeor de iteraciones

        if(fm == 0) return m;   //si la funcion en el punto medio es igual a 0, quiere decir que ya hemos dado con el punto que buscamos
        if(fa * fm < 0){        // si al hacer le producto cambia de signo, procedomos a sustuir para coger un nuevo intervalo
            b = m;
            fb = fm;
        } else{
            a = m;
            fa = fm;
        }
    }
    return (a + b) * 0.5;   //Cuando termine el bucle devolvemos el punto medio de con a y b actualiazados
}



>>>>>>> 6afedf6becadd2a3b25221d7d4400d720c22d1ef
