#include "crout.h"
#include "lapack.h"
#include <stdlib.h>
#include <stdio.h>

/** la función crout_descenso() resuelve un sistema triangular inferior usando
una matriz triangular como la que sale al descomponer la matriz por el método de Crout
el vector t[] es el término independiente del sistema. La función devuelve el vector solución */
Array1D< real > crout_descenso (Array1D< real > &l,Array1D< real > &m,Array1D< real > &t)
{
  if(t.dim()!=l.dim() || t.dim()!=(m.dim()+1)) return(Array1D< real >());
  Array1D< real > z(l.dim());
  if(l[0]==0) return(Array1D< real >());
  z[0]=t[0]/l[0];
  for(int i=1;i<z.dim();i++){
    if(l[i]==0) return(Array1D< real >());
    z[i]=(t[i]-z[i-1]*m[i-1])/l[i];
  }
  return(z);
}

/** la función crout_remonte() resuelve un sistema triangular superior usando
una matriz triangular como la que sale al descomponer la matriz por el método de Crout
el vector z[] es el término independiente del sistema. La función devuelve el vector solución */
Array1D< real > crout_remonte(
Array1D< real > &u,
Array1D< real > &z)
{
  if(z.dim()!=(u.dim()+1)) return(Array1D< real >());
  Array1D< real > v(z.dim());
  v[z.dim()-1]=z[z.dim()-1];
  for(int i=z.dim()-2;i>=0;i--){
    v[i]=(z[i]-v[i+1]*u[i]);
  }
  return(v);
}


/** la función crout_descomposicion() calcula los vectores l[],m[] y u[] del
metodo de Crout visto en Clase a partir de una matriz tridiagonal dada por los
vectores a[] (la diagonal de la matriz) y  b[] y c[] (las codiagonales de la matriz)
la función devuelve 0 si termina correctamente y un número negativo en caso
contrario */
int crout_descomposicion(
Array1D< real > &a,
Array1D< real > &b,
Array1D< real > &c,
Array1D< real > &l,
Array1D< real > &m,
Array1D< real > &u)
{
  /// HACER ALUMNO
    int N = a.dim1();

    l[0] = a[0];
    u[0] = b[0] / l[0];

    for(int i = 1; i < N - 1; i++){
        m[i - 1] = c[i - 1];
        l[i] = a[i] - m[i - 1] * u[i - 1];
        u[i] = b[i] / l[i];
    }

    m[N - 2] = c[N - 2];
    l[N - 1] = a[N - 1] - m[N - 2] * u[N - 2];

    return 0;
}

/** la función crout_metodo_completo() resuelve un sistema tridiagonal usando el método de Crout
el vector t[] es el término independiente del sistema. La función devuelve el vector solución */
Array1D< real > crout_metodo_completo(Array1D< real > &a,Array1D< real > &b,Array1D< real > &c,Array1D< real > &t)
{
  /// HACER ALUMNO
  Array1D<real> l(a.dim());
  Array1D<real> m(c.dim());
  Array1D<real> u(b.dim());

  int error = crout_descomposicion(a, b, c, l, m, u);
  if(error < 0) return Array1D<real>();

  Array1D<real> z = crout_descenso(l, m, t);

  return crout_remonte(u, z);


}





