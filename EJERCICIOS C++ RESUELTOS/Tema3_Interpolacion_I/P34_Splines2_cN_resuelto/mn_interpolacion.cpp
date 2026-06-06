#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"

/**
 LA INTERPOLACION POR SPLINES DE GRADO 2 SEGÚN SE EXPLICÓ EN CLASE.
 EN ESTE CASO SE SUPONE CONOCIDO EL ÚLTIMO VALOR DEL VECTOR c Y SE CALCULA EL RESTO DE COEFICIENTES
 LA FUNCION DEVUELVE -1 SI ENCUENTRA ALGÚN PROBLEMA Y 0 EN CASO CONTRARIO
*/
int mn_calculo_splines_2(
const Array1D< real > &x, /// vector con los puntos de interpolación
const Array1D< real > &f, /// vector con los valores de la función
const real &cLast,        /// último valor del vector c[] asignado como parámetro
Array1D< real > &a,       /// vector de salida con los coeficientes a[i] del spline de grado 2
Array1D< real > &b,       /// vector de salida con los coeficientes b[i] del spline de grado 2
Array1D< real > &c)       /// vector de salida con los coeficientes c[i] del spline de grado 2
{
  /// HACER ALUMNO
  if(f.dim()!=x.dim() || f.dim()<2 ) return -1;

  for(int k=1;k<x.dim();k++){
    if(x[k]<=x[k-1]) return -1;
  }

  a=Array1D< real >(x.dim()-1);
  b=Array1D< real >(x.dim()-1);
  c=Array1D< real >(x.dim()-1);

  a[a.dim()-1]=f[a.dim()-1];
  b[a.dim()-1]=(f[a.dim()]-f[a.dim()-1]-cLast*(x[a.dim()]-x[a.dim()-1])*(x[a.dim()]-x[a.dim()-1]))/(x[a.dim()]-x[a.dim()-1]);
  c[a.dim()-1]=cLast;

  for(int i=a.dim()-2;i>=0;i--){
    a[i]=f[i];
    b[i]=2*(f[i+1]-f[i])/(x[i+1]-x[i])-b[i+1];
    c[i]=(b[i+1]*(x[i+1]-x[i])+f[i]-f[i+1])/((x[i+1]-x[i])*(x[i+1]-x[i]));
  }

  return 0;
}

/**
  EVALUACIÓN SPLINE DE GRADO DOS. SE DEVUELVE EL VALOR DE LA
  EVALUACIÓN EN x0
*/
real mn_evaluar_splines_2(
const Array1D< real > &x,
Array1D< real > &a,
Array1D< real > &b,
Array1D< real > &c,
real x0 ){
  /// HACER ALUMNO
  for(int i=a.dim()-1;i>=0;i--){
    if(x[i]<x0) return a[i]+b[i]*(x0-x[i])+c[i]*(x0-x[i])*(x0-x[i]);
  }
  return a[0]+b[0]*(x0-x[0])+c[0]*(x0-x[0])*(x0-x[0]);
}

