#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mn_ceros_pol_grado_2.h"

/// FUNCION QUE IMPLEMENTA EL CALCULO DE LAS RAICES DE UN POLINOMIO DE GRADO 2
/// P(x)=ax^2 + bx + c EVITANDO ERRORES DE CANCELACIÓN. DEVUELVE EL NÚMERO DE
/// RAÍCES ENCONTRADAS. LAS RAÍCES SE DEVUELVEN EN LAS VARIABLES x1 Y x2 QUE
/// ENTRAN COMO PARÁMETROS. HAY QUE TENER EN CUENTA TODAS LAS OPCIONES QUE SE
/// PUEDEN DAR CON a=0 y/o b=0
int mn_ceros_pol_grado_2(
real &a, real &b, real &c, /// coeficientes polinomio de grado 2
real &x1,real &x2) /// raíces del polinomio
{
  /// HACER ALUMNO
  if(a==0){
    if(b==0) return(0);
    x1=-c/b;
    return(1);
  }
  real dis=b*b-4*a*c;
  if(dis<0) return(0);
  dis=sqrt(dis);
  if(b>0){
    x1=(-b-dis)/(2*a);
    x2=c/(x1*a);
    return(2);
  }
  else{
    x1=(-b+dis)/(2*a);
    if(x1==0){
      x2=0;
      return(2);
    }
    x2=c/(x1*a);
    return(2);
  }
}


