#include <stdio.h>
#include "../integracion.h"
#include <stdlib.h>

/**
   El módelo epidemiológico de Kermack y McKendrick simula la evolución de
   una ola epidémica dividiendo a la población en 3 grupos
     - susceptibles (no contagiados)
     - activos (contagiados que pueden contagiar a otros)
     - recuperados (han pasado la enfermedad y ya no pueden contagiar a otros)
   El objetivo de la práctica es hacer una simulación de una ola epidémica
   usando este modelo donde utilizaremos técnicas de integración vistas
   en la asignatura
*/

/// VARIABLES GLOBALES
/// PARÁMETROS DEL MODELO
real b=0.15; /// PARÁMETRO b DE LA FUNCIÓN B(s)=e^(-b*s) QUE DETERMINA
             /// RITMO AL QUE LOS INFECTADOS PASAN A RECUPERADOS
real R0=1.5; /// NÚMERO DE CONTAGIOS (EN MEDIA) QUE INICIALMENTE GENERA CADA
             /// INFECTADO AL PRINCIPIO DE LA EPIDEMIA

/// DIA EN EL QUE SE VAN CALCULANDO TODAS LAS VARIABLES EMPEZANDO EN t=0
/// QUE CORRESPONDE AL PRINCIPIO DE LA EPIDEMIA
int t=0;

/// VECTOR CON LOS DATOS DE LA INCIDENCIA DIARIA. ES DECIR EL NÚMERO DE
/// CONTAGIOS NUEVOS QUE SE PRODUCEN CADA DÍA
Array1D<real> i(1,1.); /// LA EPIDEMIA EMPIEZA EN t=0 CON UN ÚNICO CASO
                       /// POR ESO SE INICIALIZA LA INCIDENCIA A UN ÚNICO
                       /// CASO CON i[0]=1 QUE CORRESPONDE A t=0

/// FUNCIÓN QUE DETERMINA EL PASO DE INFECTADOS ACTIVOS A RECUPERADOS
/// A PARTIR DE LA INCIDENCIA DIARIA
real B(real s){ return exp(-b*s);}

/// FUNCIÓN PARA CALCULAR LOS RECUPERADOS POR INTEGRACIÓN
real fR(real s){ return (1-B(s))*interpolacion_lineal(i,t-s);}



/// PROGRAMA PRINCIPAL
int main()
{
  /// POBLACIÓN EN CANARIAS
  real POBLACION = 2175952;

  /// VECTOR DONDE SE GUARDAN EL TOTAL DE INFECTADOS ACTIVOS HASTA EL DÍA  t
  /// EN EL DÍA 0 HAY UN INFECTADO ACTIVO QUE CORRESPONDE AL PRIMER INFECTADO
  Array1D<real> A(1,1.);

  /// VECTOR DONDE SE GUARDAN EL TOTAL DE RECUPERADOS HASTA EL DÍA t
  Array1D<real> R(1,0.); /// EN EL DÍA 0 HAY 0 RECUPERADOS

  /// VECTOR DONDE SE GUARDAN LOS SUSCEPTIBLES EN CADA DÍA t
  /// EN EL DÍA 0 LOS SUSCEPTIBLES SON EL TOTAL DE LA POBLACIÓN
  /// MENOS EL PRIMER INFECTADO
  Array1D<real> S(1,POBLACION-1);

  /// VAMOS CALCULANDO TODOS LOS COMPARTIMENTOS HASTA QUE
  /// LA INCIDENCIA DIARIA CAIGA POR DEBAJO DE 1 Y HAYAN
  /// PASADO AL MENOS 30 DÍAS DESDE EL COMIENZO DE LA EPIDEMIA
  real total_infectados = i[0];
  while(i[t]>=1 || t<30){
     /// CALCULAMOS LOS CASOS NUEVOS DEL DÍA t+1 A PARTIR DE LOS CASOS ACTIVOS
     /// Y LOS SUSCEPTIBLES DEL DÍA t Y LO AÑADIMOS AL VECTOR DE INCIDENCIA
     i.push_back(R0*S[t]/POBLACION*b*A[t]);
     /// ACTUALIZAMOS EL VALOR DEL DÍA
     t++;
     /// ACUMULAMOS LOS CASOS NUEVOS AL TOTAL DE CASOS
     total_infectados += i[t];
     /// CALCULAMOS LOS RECUPERADOS EL DÍA t Y LO AÑADIMOS AL VECTOR DE RECUPERADOS
     /// PARA CALCULAR LAS INTEGRALES ENTRE 0 Y t USAMOS 2*t INTERVALOS
     R.push_back(trapecio(fR,0,t,2*t) );
     /// CALCULAMOS LOS ACTIVOS EL DÍA t Y LO AÑADIMOS AL VECTOR DE ACTIVOS
     A.push_back(total_infectados-R[t]);
     /// CALCULAMOS LOS SUSCEPTIBLES EL DÍA t Y LO AÑADIMOS AL VECTOR DE SUSCEPTIBLES
     S.push_back(POBLACION-total_infectados);

  }

  /// CALCULAMOS CUANDO SE PRODUCE EL PICO DE INCIDENCIA DIARIA EN LA OLA EPIDEMICA
  real pico=0;
  int posicion_pico=0;
  for(int k=0;k<i.dim();k++){
    if(i[k]>pico){
      posicion_pico=k;
      pico=i[k];
    }
  }

  /// IMPRIMIMOS RESULTADOS PRINCIPALES
  printf("Tamagno poblacion utilizada : %d\n",2175952);
  printf("Parametros del modelo : R0 =%lf, b=%lf\n",R0,b);
  printf("(real)   Duracion de la Ola Epidemica : %d dias\n",333);
  printf("(alumno) Duracion de la Ola Epidemica : %d dias\n",t);
  printf("(real)   El pico de incidencia diaria se alcanza a los %d dias con %1.0lf casos\n",155,27270.);
  printf("(alumno) El pico de incidencia diaria se alcanza a los %d dias con %1.0lf casos\n",posicion_pico,pico);
  printf("(real)   Total de personas contagiadas al final de la epidemia : %1.0lf  (%1.1lf%% de la poblacion) \n",1423142.,65.4);
  printf("(alumno) Total de personas contagiadas al final de la epidemia : %1.0lf  (%1.1lf%% de la poblacion) \n",total_infectados,100*total_infectados/POBLACION);


  ///  GUARDAMOS LOS RESULTADOS EN UN ARCHIVO
  FILE *f;
  f = fopen("KermackMcKendrick.csv","w");
  /// ESCRIBIMOS LOS TITULOS DE LAS COLUMNAS DEL FICHERO
  fprintf(f,"dia,activos,recuperados,susceptibles\n");
  /// ESCRIBIMOS EL RESULTADO DE LOS COMPARTIMENTOS TODOS LOS DÍAS
  for(int k=0;k<t;k++){
    fprintf(f,"%d,%1.2lf,%1.2lf,%1.2lf\n",k,A[k],R[k],S[k]);
  }
  /// CERRAMOS EL ARCHIVO
  fclose(f);

  printf("\nLA EVOLUCION DE ACTIVOS, RECUPERADOS Y SUSCEPTIBLES SE ESCRIBE EN\n");
  printf("EN EL FICHERO KermackMcKendrick.csv. EL ALUMNO DEBE AGNADIR A LA MEMORIA\n");
  printf("UNA GRAFICA EXCEL EXPLICADA CON LOS DATOS DEL FICHERO\n");

//  AYUDA MANEJO DE FICHEROS
//  /// GUARDAMOS LOS RESULTADOS EN UN FICHERO
//  FILE *f;
//  f = fopen("prueba.csv","w");
//  fprintf(f,"dia;incidencia;activos;recuperados;susceptibles\n");
//  fprintf(f,"%d;%1.2lf;%1.2lf;%1.2lf;%1.2lf\n",1,1.111,2.222,3.333,6.666);
//  fclose(f);

// AYUDA SINTAXIS C++ IMPRIMIR POR PANTALLA
//cout << "El numero " << 5 << " es entero, y el numero " << 5.1 << " es real\n";
//printf("El numero %d es entero, el numero %lf es real y %s es un string\n",5,5.1,"STRING");
//printf("El %1.1lf%% del total\n",5.12);


}


