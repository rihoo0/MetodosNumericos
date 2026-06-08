#include "integracion.h"
#include <stdlib.h>
#include <stdio.h>

/// INTERPOLACION LINEAL (SE SUPONE QUE LOS PUNTOS DE INTERPOLACIÓN SON x[k]=k)
real interpolacion_lineal(
Array1D<real> &f, /// valores de función en los puntos de interpolación
real x)  /// punto donde se evalua la función interpolada
{
  if(f.dim()==1) return f[0];
  int i=x;

  if(i<0) i=0;
  else if(i>=f.dim()-1) i=f.dim()-2;

  return f[i]+(x-i)*(f[i+1]-f[i]);
}


/// FUNCION PARA CALCULAR UNA INTEGRAL POR EL METODO DEL RECTÁNGULO
/// UTILIZANDO N INTERVALOS EN UN INTERVALO [a,b]
real rectangulo(
real (*f)(real x) /** funcion que se integra */,
real a /** extremo izquierdo del intervalo */,
real b /** extremo derecho del invervalo*/,
int N /** numero de intervalos para calcular la integral */)
{
   /// HACER ALUMNO
    real integral = 0.;

    // anchura de cada rectángulo
    real h = (b - a) / N;

    // punto medio del primer rectángulo: a + h/2
    // (en vez de a + h*0 + h/2)
    real x0 = a + 0.5*h;

    // para cada rectángulo k, evaluamos f en su punto medio
    // y acumulamos la altura
    for(int k = 0; k < N; k++){
        // punto medio del rectángulo k = x0 + h*k
        integral += f(x0 + h * k);
    }

    // multiplicamos la suma de alturas por la anchura h
    // para obtener la suma de áreas
    return integral * h;
}
