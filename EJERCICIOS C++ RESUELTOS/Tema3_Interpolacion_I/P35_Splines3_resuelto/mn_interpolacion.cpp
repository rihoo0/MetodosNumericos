/*========================================================================
  FUNCIONES PARA LA INTERPOLACION DE FUNCIONES
  ======================================================================== */

// INCLUSION DE LA LIBRERIA PARA GESTIONAR LA ARITMETICA
#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"

/**
 FUNCIÓN AUXILIAR PARA RESOLVER EL SISTEMA PARA CALCULAR c
*/
Array1D< real > solucion_sistema(
Array1D< real > &L,
Array1D< real > &M,
Array1D< real > &U,
Array1D< real > &B
)
{
  Array1D< real > c(M.dim());
  c[0]=B[0];
  c[c.dim()-1]=B[B.dim()-1];

  for(int k=0;k<10000;k++){
    real error=0;
    for(int n=1;n<M.dim()-1;n++){
        real temp=c[n];
        c[n]= (-L[n-1]*c[n-1]-U[n]*c[n+1]+B[n])/M[n];
        error+=mn_distancia(temp,c[n]);
    }
    if(error<1e-8) return c;
  }
  return Array1D< real >();

}

/**
 LA INTERPOLACION POR SPLINES DE GRADO 3 SEGÚN SE EXPLICÓ EN CLASE.
 LA FUNCION DEVUELVE -1 SI ENCUENTRA ALGÚN PROBLEMA Y 0 EN CASO CONTRARIO.
 HAY QUE USAR LA FUNCIÓN solucion_sistema() QUE SE VE ARRIBA
*/
int mn_calculo_splines_3(
const Array1D< real > &x, /// vector con los puntos de interpolación
const Array1D< real > &f, /// vector con los valores de la función
const real c0,            /// primer valor del vector c[] asignado como parámetro
const real cN,            /// último valor del vector c[] asignado como parámetro
Array1D< real > &a,       /// vector de salida con los coeficientes a[i] del spline de grado 2
Array1D< real > &b,       /// vector de salida con los coeficientes b[i] del spline de grado 2
Array1D< real > &c,       /// vector de salida con los coeficientes c[i] del spline de grado 2
Array1D< real > &d)       /// vector de salida con los coeficientes d[i] del spline de grado 2
{
  /// HACER ALUMNO
  if(x.dim()!=f.dim() || x.dim()==0) return -1;

  int N=x.dim()-1;
  Array1D< real > h(N);
  for(int i=0;i<N;i++) h[i]= x[i+1]-x[i];

  Array1D< real > M(N+1,1.);
  for(int i=1;i<N;i++) M[i]= 2*(h[i-1]+h[i]);

  Array1D< real > L=h.copy();
  L[N-1]=0;

  Array1D< real > U=h.copy();
  U[0]=0;

  Array1D< real > B(N+1);
  for(int i=1;i<N;i++) B[i]= 3*(f[i+1]-f[i])/h[i] - 3*(f[i]-f[i-1])/h[i-1];
  B[0]=c0;
  B[N]=cN;

  c=solucion_sistema(L,M,U,B);

  if(c.dim()==0) return(-1);

  a=Array1D< real >(N);
  b=Array1D< real >(N);
  d=Array1D< real >(N);

  for(int i=0;i<N;i++){
    a[i]=f[i];
    d[i]=(c[i+1]-c[i])/(3*h[i]);
    b[i]=(f[i+1]-f[i])/h[i] - h[i]*(2*c[i]+c[i+1])/3;
  }

  return 0;
}

/**
  EVALUACIÓN SPLINE DE GRADO 3. SE DEVUELVE EL VALOR DE LA
  EVALUACIÓN EN x0
*/
real mn_evaluar_splines_3(
const Array1D< real > &x,
Array1D< real > &a,
Array1D< real > &b,
Array1D< real > &c,
Array1D< real > &d,
real x0 ){
  /// HACER ALUMNO
  for(int i=x.dim()-2;i>0;i--){
    if(x[i]<x0){
      real z=x0-x[i];
      return a[i] + b[i]*z + c[i]*z*z + d[i]*z*z*z ;
    }
  }
  real z=x0-x[0];
  return a[0] + b[0]*z + c[0]*z*z + d[0]*z*z*z ;
}

