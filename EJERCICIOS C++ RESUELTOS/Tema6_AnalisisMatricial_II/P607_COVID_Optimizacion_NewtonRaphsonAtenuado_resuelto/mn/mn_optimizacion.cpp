#include "mn_optimizacion.h"
#include "mn_lapack.h"
#include "mn_utilidades.h"
#include <stdlib.h>
#include <stdio.h>

/// VARIABLE GLOBAL CON EL VALOR DE LA POTENCIA p DEL FUNCIONAL ERROR A MINIMIZAR
real p_;

/// -------------------------------------------------------------
/// EVALUACIÓN DEL ERROR AL APROXIMAR POR UNA LOG-NORMAL
real Error_p(Array1D<real> &u){

  /// LEEMOS LOS DÍAS QUE TARDAN EN PRODUCIRSE SÍNTOMAS ENTRE
  /// UN CASO PRIMARIO Y SECUNDARIO (EL ARRAY VA DESDE -5 HASTA 24)
  static Array1D<real> x("dias.csv");

  /// LEEMOS EL HISTOGRAMA DEL NUMERO DE CASOS, y[k], DONDE EL CASO
  /// SECUNDARIO PRESENTA SÍNTOMAS x[k] DÍAS DESPUÉS DEL CASO PRIMARIO
  static Array1D<real> y("serial_interval.csv");

  /// ACUMULAMOS EL ERROR USANDO LA FÓRMULA
  real error=0.;
  for(int k=0;k<y.dim();k++){
    error+=pow(fabs(log_normal((real) x[k],u)-y[k]),p_);
  }
  /// DEVOLVEMOS EL ERROR
  return error;

}

/// -------------------------------------------------------------
/// FUNCIÓN QUE CALCULA EL GRADIENTE DE LA FUNCIÓN f()
Array1D<real> grad_f(
real (*f)(Array1D<real> &u), /// FUNCIÓN A LA QUE SE CALCULA EL GRADIENTE
Array1D<real> &u, /// PARAMETROS DE LA FUNCIÓN DONDE SE CALCULA EL GRADIENTE
real h) /// PASO PARA CALCULAR LAS DERIVADAS
{
  /// VECTOR DONDE GUARDAMOS EL GRADIENTE DE LA FUNCIÓN f()
  Array1D<real> G(u.dim(),0.);

  /// APROXIMAMOS LAS DERIVADAS PARCIALES DE f()
  for(int k=0;k<u.dim();k++){
    Array1D<real> v=u.copy();
    v[k]+=h;
    G[k]=(f(v)-f(u))/h;
  }

  /// DEVOLVEMOS EL VECTOR GRADIENTE
  return G;
}


/// -------------------------------------------------------------
/// CÁLCULO MATRIZ DERIVADA
Array2D< real > matriz_derivada(
real (*f)(Array1D<real> &u), /// FUNCIÓN A LA QUE SE CALCULA LA MATRIZ DERIVADA SEGUNDA
Array1D<real> &u, /// PARAMETROS DE LA FUNCIÓN
real h) /// PASO PARA CALCULAR LAS DERIVADAS
{
  /// MATRIZ DONDE GUARDAMOS LA DERIVADA DE LA FUNCIÓN f()
  Array2D< real > derivada(u.dim(),u.dim());

  /// HACEMOS UNA COPIA DEL VECTOR u PARA CALCULAR LAS DERIVADAS PARCIALES
  Array1D< real > u2=u.copy();

  /// CALCULO DEL VECTOR GRADIENTE DE f() EN u
  Array1D< real> grad_fu = grad_f(f,u,h);

  /// CALCULAMOS LA MATRIS DERIVADA
  for(int k=0;k<u.dim();k++){
    /// INCREMENTAMOS EN h LA COMPONENTE k DEL VECTOR
    u2[k]+=h;
    /// CALCULAMOS EL VECTOR GRADIENTE PARA ESE NUEVO VECTOR
    Array1D< real > grad_fu2=grad_f(f,u2,h);
    if(grad_fu2.dim()==0) return Array2D< real >();
    /// CALCULAMOS LA DERIVADA PARCIAL DEL GRADIENTE Y LO ALMACENAMOS EN LA MATRIZ DERIVADA
    Array1D< real > derivada_parcial=(grad_fu2-grad_fu)/h;
    for(int l=0;l<u.dim();l++) derivada[l][k]=derivada_parcial[l];
    u2[k]=u[k];
  }

  /// DEVOLVEMOS LA MATRIZ DERIVADA
  return(derivada);
}

/// -------------------------------------------------------------
/// MÉTODO DE NEWTON-RAPHSON ATENUADO PARA MINIMIZAR f()
/// ACTUALIZA EL VECTOR DE PARÁMETROS u[] Y DEVUELVE EL
/// NÚMERO DE ITERACIONES
/// PARA RESOLVER SISTEMAS SE USA LA FUNCIÓN mn_gauss()
int mn_newton_raphson_atenuado(
real (*f)(Array1D<real> &u), /// FUNCIÓN A MINIMIZAR
Array1D<real> &u, /// PARAMETROS DE ENTRADA/SALIDA LA FUNCIÓN f()
real h, /// PASO PARA CALCULAR LAS DERIVADAS
real TOL, /// TOLERANCIA PARA PARAR LAS ITERACIONES
int Nmax) /// NÚMERO MÁXIMO DE ITERACIONES
{
  /// HACER ALUMNO
  real lambda=1.;

  real Error=f(u);
  Array1D<real> grad_fu=grad_f(f,u,h);
  if(grad_fu.dim()==0) return(-1);

  for(int i=0;i<Nmax;i++){
    if(grad_fu.norm()==0. || lambda<1e-20){return(i);}
    Array2D<real> Derivada=matriz_derivada(f,u,h)*lambda;
    if(Derivada.dim1()==0) return(i);
    for(int k=0;k<Derivada.dim1();k++) Derivada[k][k]+=1;
    Array1D<real> sol=mn_gauss(Derivada,grad_fu*(-lambda));
    if(sol.dim()==0){
      lambda/=10.;
      continue;
    }
    if(sol.norm()<TOL) return(i);
    Array1D<real> u_new=u+sol;
    real ErrorNew=f(u_new);
    if(ErrorNew<Error){
      grad_fu=grad_f(f,u_new,h);
      if(grad_fu.dim()==0) return(i);
      u=u_new;
      Error=ErrorNew;
      lambda*=10.;
    }
    else{
      lambda/=10.;
    }
  }
  return(Nmax);
}

























