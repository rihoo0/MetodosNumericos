#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"


/// FUNCION QUE CALCULA EL POLINOMIO INTERPOLADOR POR LAS DIFERENCIAS DE NEWTON
/// DEVUELVE UN VECTOR CON LOS COEFICIENTES DEL POLINOMIO O UN VECTOR VACÍO SI ALGO VA MAL
Array1D< real > mn_construir_polinomio_interpolador(
const Array1D< real > &X, /// VECTOR CON LOS VALORES DE LOS PUNTOS DE INTERPOLACION
const Array1D< real > &F) /// VECTOR DE VALORES DE LA FUNCION EN LOS PUNTOS DE INTERPOLACION
{
  /// HACER ALUMNO

  Array1D<real> A(X.dim());

  Array1D<real> B(F.dim());
  for(int i = 0; i < F.dim(); i++){
    B[i] = F[i];
  }
  A[0] = B[0];

  for(int k = 1; k < X.dim(); k++){
    for(int l = 0; l < X.dim() - k; l++){
            if(X[k + l] == X[l]) return Array1D<real>();
        B[l] = (B[l + 1] - B[l]) / (X[k + l] - X[l]);
    }
    A[k] = B[0];
  }
  return A;

}


/// FUNCION QUE EVALUA EL POLINOMIO INTERPOLADOR DE NEWTON EN UN PUNTO
real mn_evaluar_polinomio_interpolador(
const Array1D< real > &A, /// VECTOR CON LOS COEFICIENTES DEL POLINOMIO
const Array1D< real > &X, /// VECTOR CON LOS VALORES DE LOS PUNTOS DE INTERPOLACION
const real x0) /// VALOR DONDE SE INTERPOLA EL POLINOMIO
{
  /// HACER ALUMNO
    int n = A.dim();
    real b = A[n - 1];
    for(int i = n - 2; i >= 0; i--){
        b = A[i] + b * (x0 - X[i]);
    }
    return b;
}


