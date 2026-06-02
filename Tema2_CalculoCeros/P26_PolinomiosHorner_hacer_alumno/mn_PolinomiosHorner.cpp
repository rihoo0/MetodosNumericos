#include "mn_aritmeticas.h"
#include "mn_PolinomiosHorner.h"

/// *************************************************************************************
///         EVALUACIÓN DE UN POLINOMIO a EN UN PUNTO x
/// *************************************************************************************
real mn_evaluar_polinomio(
Array1D< real > &a /** coeficientes polinomio */,
real x /** valor donde se evalua el polinomio */){
  real Px=0;
  real xk=1;
  for(int k=0;k<a.dim();k++){
    Px+=a[k]*xk;
    xk*=x;
  }
  return Px;
}

/// *************************************************************************************
///  EVALUACIÓN DE UN POLINOMIO Y SU DERIVADA POR EL MÉTODO DE HORNER
/// *************************************************************************************
void mn_evaluar_polinomio_horner(
Array1D< real > &a /** coeficientes polinomio */,
real x /** valor donde se evalua el polinomio */,
real &Px /** evaluación del polinomio en x*/,
real &PPx /** evaluación de la derivada del polinomio en x*/){
  /// HACER ALUMNO
    Px = a[a.dim() - 1];
    PPx = a[a.dim() - 1];

    for(int i = a.dim() - 2; i > 0; i-- ){
        Px = Px * x + a[i];
        PPx = PPx * x + Px;
    }

    Px = Px * x + a[0];

}

/// ****************************************************
///  CALCULO POLINOMIO DERIVADA
///  DEVUELVE UN VECTOR CON EL POLINOMIO DERIVADA
/// ****************************************************
Array1D< real > mn_calcular_derivada_polinomio(
Array1D< real > &a /** coeficientes del polinomio */){
  /// HACER ALUMNO

    if(a.dim() == 1){
        return Array1D < real > ();
    }

    Array1D< real > b(a.dim()-1);

    for(int k = 0; k < b.dim(); k++){
        b[k] = (k + 1) * a[k + 1];
    }

    return b;

}





