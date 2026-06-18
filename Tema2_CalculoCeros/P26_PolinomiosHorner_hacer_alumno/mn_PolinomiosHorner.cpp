<<<<<<< HEAD
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

    Px = a [a.dim() - 1];
    PPx = a[a.dim() - 1];

    for(int k = a.dim() - 2; k > 0; k--){
        Px = Px * x + a[k];
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
    if(a.dim() == 1) return Array1D <real>();

    Array1D <real> b(a.dim() - 1);

    for(int k = 0; k < a.dim() - 1; k++){
        b[k] = (k + 1.) * a[k + 1];
    }

    return b;

}





=======
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

}

/// ****************************************************
///  CALCULO POLINOMIO DERIVADA
///  DEVUELVE UN VECTOR CON EL POLINOMIO DERIVADA
/// ****************************************************
Array1D< real > mn_calcular_derivada_polinomio(
Array1D< real > &a /** coeficientes del polinomio */){
  /// HACER ALUMNO

}





>>>>>>> 6afedf6becadd2a3b25221d7d4400d720c22d1ef
