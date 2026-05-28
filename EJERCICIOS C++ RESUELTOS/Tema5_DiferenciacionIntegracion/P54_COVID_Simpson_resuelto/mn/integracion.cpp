#include "integracion.h"
#include <stdlib.h>
#include <stdio.h>

/// INTERPOLACION LINEAL (SE SUPONE QUE LOS PUNTOS DE INTERPOLACIÓN SON x[k]=k)
real interpolacion_lineal(
Array1D<real> &f, /// valores de función en los puntos de interpolación
real x)  /// punto donde se evalua la función interpolada
{
  if(f.dim()==1) return f[0];
  //if(x>f.dim()-1) return f[f.dim()-1];
  int i=x;

  if(i<0) i=0;
  else if(i>=f.dim()-1) i=f.dim()-2;

  return f[i]+(x-i)*(f[i+1]-f[i]);
}


/// FUNCION PARA CALCULAR UNA INTEGRAL POR EL METODO DE SIMPSON
/// UTILIZANDO N INTERVALOS EN UN INTERVALO [a,b]
real simpson(
real (*f)(real x) /** funcion que se integra */,
real a /** extremo izquierdo del intervalo */,
real b /** extremo derecho del invervalo*/,
int N /** numero de intervalos para calcular la integral */)
{
   /// HACER ALUMNO
   real integral=0;
   real h=(b-a)/N;
   real xk,xk1;
   xk=a;
   real fk=f(xk);
   real S=(b-a)/(6.*N);

   for(int k=0;k<N;k++){
      xk1=a+(k+1)*h;
      real xm=(xk+xk1)/2;
      real fm=f(xm);
      real fk1=f(xk1);
      integral+=(fk+fk1+4.*fm);
      xk=xk1;
      fk=fk1;
   }
   return S*integral;
}
