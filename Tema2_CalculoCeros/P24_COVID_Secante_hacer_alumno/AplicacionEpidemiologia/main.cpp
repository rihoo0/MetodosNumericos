#include <stdio.h>
#include "../mn_calculo_de_ceros.h"
#include <stdlib.h>
using namespace std;

/// PRACTICA PROGRAMACIÓN TEMA 2
/// ESTUDIO DEL TIEMPO QUE TARDAN EN PRESENTAR SÍNTOMAS LAS PERSONAS INFECTADAS POR LA COVID-19
/// ESTUDIAREMOS EL INTERVALO DE TIEMPO EN QUE LA MAYOR PARTE DE LOS INFECTADOS PRESENTAN SÍNTOMAS
/// Y EL DÍA TRAS LA INFECCIÓN DONDE ES MÁS PROBABLE PRESENTAR SÍNTOMAS
/// PARA ESTIMAR EL INTERVALO DE TIEMPO DONDE LA MAYOR PARTE DE INFECTADO PRESENTA SÍNTOMAS
/// ESTUDIAREMOS EN QUE DÍA EL 1% DE LOS INFECTADOS EMPIEZA A PRESENTAR SINTOMAS. EXISTEN DOS RESPUESTAS POSIBLES:
///    (1) EN LOS PRIMEROS DÍAS QUE CORRESPONDE AL PRINCIPIO DEL PERIODO EN QUE LOS INFECTADOS EMPIEZAN A PRESENTAR SÍNTOMAS (ESTE GRUPO DE PERSONAS PRESENTA SÍNTOMAS MUY PRONTO)
///    (2) EN LOS ÚLTIMOS DÍAS QUE CORRESPONDE AL FINAL DEL PERIODO EN QUE LOS INFECTADOS PUEDEN PRESENTAR SÍNTOMAS (ESTE GRUPO DE PERSONAS PRESENTA SÍNTOMAS MUY TARDE)
/// PARA RESPONDER A ESTAS PREGUNTAS SE UTILIZA UNA MUESTRA DEL NÚMERO DE CASOS QUE PRESENTAN SINTOMAS EN FUNCIÓN DE LOS DÍAS PASADOS DESDE LA INFECCIÓN
/// LOS DATOS DE ESTA MUESTRA SE ENCUENTRAN EN EL FICHERO muestra.csv
/// LA MUESTRA SE APROXIMA POR UNA DISTRIBUCIÓN GAMMA Y SE CALCULARÁ A PARTIR DE ELLA LAS SOLUCIONES AL PROBLEMA

/// PARAMETROS DE LA DISTRIBUCIÓN Gamma
extern real d,alfa,beta;

/// DEFINIMOS UNA FUNCIÓN AUXILIAR PARA EXPRESAR LA ECUACIÓN Gamma(x)=0.01 COMO f(x)=0
real f(real x){ return Gamma(x)-0.01;}

///    PROGRAMA PRINCIPAL
int main()
{
  /// LEEMOS LA MUESTRA DEL NÚMERO DE CASOS QUE PRESENTAN SINTOMAS
  /// EN FUNCIÓN DE LOS DÍAS PASADOS DESDE LA INFECCIÓN
  Array1D<real> data("muestra.csv");

  /// CALCULAMOS LA MEDIA Y VARIANZA MUESTRALES DEL NÚMERO DE DÍAS
  ///QUE PASAN DESDE LA INFECCIÓN A PRESENTAR SÍNTOMAS
  real media=0,varianza=0,NumeroCasos=0;
  for(int k=0;k<data.dim();k++){
    media+=k*data[k];
    NumeroCasos+=data[k];
  }
  media/=NumeroCasos;

  for(int k=0;k<data.dim();k++){
    varianza+=data[k]*(media-k)*(media-k);
  }
  varianza/=NumeroCasos;

  cout << "media = " << media  << " varianza = " << varianza << "\n";

  /// CALCULAMOS LOS PARÁMETROS DE LA DISTRIBUCIÓN GAMMA A PARTIR
  /// DE LA MEDIA Y VARIANZA MUESTRALES
  calculo_parametros_Gamma(media,varianza);

  /// CALCULAMOS CUANDO Gamma(x)=0.01 USANDO EL MÉTODO DE LA SECANTE
  /// CALCULO EN LOS PRIMEROS DÍAS TRAS LA INFECCIÓN
  real TOL=1e-8;
  int NumeroIteraciones,NiterMax=10000;
  real x0=2.,x1=1.;
  NumeroIteraciones = mn_secante(f,x0,x1,NiterMax,TOL);
  cout << "\nSecante     : x1 = " << x1 << " , N. iteraciones = " <<
  NumeroIteraciones << " , Gamma(x1) = " << Gamma(x1) << "\n";

  /// CALCULO EN LOS ÚLTIMOS DÍAS TRAS LA INFECCIÓN
  real y0=20,y1=19;
  NumeroIteraciones = mn_secante(f,y0,y1,NiterMax,TOL);
  cout << "\nSecante     : y1 = " << y1 << " , N. iteraciones = " <<
  NumeroIteraciones << " , Gamma(y1) = " << Gamma(y1) << "\n";

  /// CALCULO DE DONDE ALCANZA EL MÁXIMO LA DISTRIBUCIÓN GAMMA
  ///USANDO EL MÉTODO DE LA SECANTE
  real z0=7;
  real z1=6;
  NumeroIteraciones = mn_secante(Gammap,z0,z1,NiterMax,TOL);
  cout << "\nSecante     : z1 = " << z1 << " , N. iteraciones = " <<
  NumeroIteraciones << " , Gamma(z1) = " << Gamma(z1) <<", Gammap(z1) = " << Gammap(z1) <<"\n";

  /// POR TANTO, LAS CONCLUSIONES DEL ESTUDIO BASADOS EN ESTA MUESTRA Y SU APROXIMACIÓN POR UNA DISTRIBUCIÓN GAMMA SON LAS SIGUIENTES:
  cout << "\nCONCLUSIONES DEL ESTUDIO\n";
  cout << "La mayor parte de infectados que presenta sintomas, lo hace entre los dias "  << x1 << " y " << y1 << " despues de la infeccion\n";
  cout << "La media de dias que se tarda en presentar sintomas es : "  << media << "\n";
  cout << "El dia que es mas probable presentar sintomas es : "  << z1 << " dias despues de la infeccion\n";


}


