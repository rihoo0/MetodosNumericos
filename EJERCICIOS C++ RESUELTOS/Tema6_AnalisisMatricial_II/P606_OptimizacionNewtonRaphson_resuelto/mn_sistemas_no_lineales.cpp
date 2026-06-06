#include "mn_sistemas_no_lineales.h"
#include "mn_lapack.h"
#include <stdlib.h>
#include <stdio.h>


/// FUNCIÓN GRADIENTE PARA AJUSTE DE PARÁMETROS DEL MODELO Cobb--Douglas
/// LA FUNCIÓN RETORNA EL GRADIENTE DEL ERROR CUADRÁTICO QUE SE MINIMIZA EN EL AJUSTE
Array1D< real > grad_f(Array1D< real > u){ /// EL VECTOR u[]={a,b,c,d}

  /// VECTORES CON LOS DATOS DE LA EMPRESA EN LOS ÚLTIMOS 5 AÑOS
  static real P[5]={50.35701647,51.74230552,48.59446689,56.25049311,43.18192399};
  static real K[5]={10,11,9,12,8};
  static real L[5]={100,95,99,105,90};
  static real M[5]={1,1.1,1,1.2,0.8};

  /// DECLARACIÓN E INICIALIZACIÓN VECTOR QUE DEFINE LA FUNCIÓN DE AJUSTE
  Array1D< real > grad_fu(u.dim(),0.);

  /// CALCULO DEL GRADIENTE DE LA FUNCIÓN DE AJUSTE
  real a=u[0];
  real b=u[1];
  real c=u[2];
  real d=u[3];
  for(int i=0;i<5;i++){
    real Ki=pow(K[i],a);
    real Li=pow(L[i],b);
    real Mi=pow(M[i],c);
    real aux1=Ki*Li*Mi*d;
    real aux2=aux1-P[i];
    real aux3=2.*aux1*aux2;
    grad_fu[0]+=aux3*log(Ki);
    grad_fu[1]+=aux3*log(Li);
    grad_fu[2]+=aux3*log(Mi);
    grad_fu[3]+=aux3;
  }
  return(grad_fu);
}

/// EVALUACIÓN CALIDAD DEL AJUSTE DE PARÁMETROS DEL MODELO Cobb--Douglas
/// LA FUNCIÓN RETORNA EL ERROR CUADRÁTICO QUE SE MINIMIZA EN EL AJUSTE
real error_ajuste(Array1D< real > u){ /// EL VECTOR u[]={a,b,c,d}
  /// VECTORES CON LOS DATOS DE LA EMPRESA EN LOS ÚLTIMOS 5 AÑOS
  static real P[5]={50.35701647,51.74230552,48.59446689,56.25049311,43.18192399};
  static real K[5]={10,11,9,12,8};
  static real L[5]={100,95,99,105,90};
  static real M[5]={1,1.1,1,1.2,0.8};

  /// DECLARACIÓN ERROR CUADRÁTICO
  real error=0;

  /// CALCULO DE LA FUNCIÓN
  real a=u[0];
  real b=u[1];
  real c=u[2];
  real d=u[3];
  for(int i=0;i<5;i++){
    real Ki=pow(K[i],a);
    real Li=pow(L[i],b);
    real Mi=pow(M[i],c);
    real aux1=Ki*Li*Mi*d;
    error+=(aux1-P[i])*(aux1-P[i]);
  }

  return(error);
}



/** FUNCIONES PARA CALCULAR EL PASO h PARA CALCULAR LAS DERIVADAS EN FUNCION
DE LA MAGNITUD DE LA VARIABLE x */
float mn_calcular_h( float x){  return fabsf(x)/(1<<12) +1e-30; }
double mn_calcular_h( double x){  return fabs(x)/(1<<26) +1e-300; }
long double mn_calcular_h( long double x){  return fabsl(x)/(1<<31) +1e-4000; }

/** Función que calcula la matriz derivada de una función de varias variables utilizando
siempre la aproximación de la derivada tipo (f(x+h)-f(x))/h
Utilizar la función mn_calcular_h() que está encima para calcular el paso h de forma automática
*/
Array2D< real > matriz_derivada(
Array1D< real >  (*f)(Array1D< real >), ///función de varias variables a derivar
Array1D< real > &u) /// vector donde se calcula la derivada
{
  int N=u.dim(); /// tamaño del vector
  Array2D< real > derivada(N,N);

  Array1D< real > u2=u.copy(); // vector auxiliar
  for(int k=0;k<N;k++){
    real h=mn_calcular_h(u2[k]);
    u2[k]+=h;
    Array1D< real > derivada_parcial=(f(u2)-f(u))/h;
    for(int l=0;l<N;l++) derivada[l][k]=derivada_parcial[l];
    u2[k]=u[k];
  }
  return(derivada);
}

/** función que implementa el método de Newton-Raphson para sistemas
devuelve el número de iteraciones si termina bien y -1 si termina mal.
Se puede utilizar la función mn_gauss(A,b) para resolver el sistema lineal
en cada iteración*/
int mn_newton_raphson_sistemas(
Array1D< real >  (*f)(Array1D< real >), /** función */
Array1D< real > &u, /** aproximación de la solución que es actulizada por la función */
real TOL, /** tolerancia para parar las iteraciones */
int Nmax) /** número máximo de iteraciones */
{
  /** HACER ALUMNO */
  Array1D<real> fu=f(u);
  for(int i=0;i<Nmax;i++){
    if(fu.norm()<TOL){return(i);}
    Array2D<real> Derivada=matriz_derivada(f,u);
    Array1D<real> sol=mn_gauss(Derivada,fu*(-1.));
    if(sol.dim()==0) return(-1);
    if(sol.norm()<TOL) return(i);
    u=u+sol;
    fu=f(u);

  }
  return(-1);
}


