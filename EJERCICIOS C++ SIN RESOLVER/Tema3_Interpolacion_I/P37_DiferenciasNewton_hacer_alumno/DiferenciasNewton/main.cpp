#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../mn_aritmeticas.h"
#include "../mn_interpolacion.h"

main()
{
   /// PRÁCTICA DE INTERPOLACIÓN POR EL MÉTODO DE DIFERENCIAS DE NEWTON
   /// SE ESTUDIA EL NÚMERO DE FALLECIMIENTOS POR EDAD DE LA PRIMERA OLA DE
   /// LA COVID EN ESPAÑA. COMO LOS DATOS PÚBLICOS SON POR GRUPOS DE EDAD,
   /// PARA ESTIMAR LOS FALLECIDOS POR CADA EDAD HACE FALTA UN PROCESO DE
   /// INTERPOLACIÓN. TOMAMOS COMO PUNTOS DE INTERPOLACIÓN LA MEDIA DE EDAD
   /// DE CADA GRUPO QUE SON 10, 22.5, 35, 45, 55, 65, 75 Y 85 AÑOS, Y
   /// TOMAMOS COMO VALORES DE LA FUNCIÓN A INTERPOLAR EL NÚMERO DE FALLECIDOS
   /// OBSERVADOS PARA ESE TRAMO DE EDAD DIVIDIDO POR EL NÚMERO DE EDADES DEL GRUPO
   /// TODA LA INFORMACIÓN LA LEEMOS DE FICHEROS

  /// LEEMOS LOS DATOS
  Array1D< real > edad("COVID_edad.txt");
  Array1D< real > fallecimientos("COVID_fallecimientos.txt");

  /// CALCULAMOS EL POLINOMIO INTERPOLADOR POR DIFERENCIAS DIVIDIDAS
  Array1D< real > A=mn_construir_polinomio_interpolador(edad,fallecimientos);

  /// COMPARAMOS LOS RESULTADOS OBTENIDOS CON LOS QUE DEBERÍAN SALIR Y
  /// QUE PREVIAMENTE HEMOS ALMACENADO EN A_sol.csv
  Array1D< real > A_sol("A_sol.csv");

  printf("COMPARACION COEFICIENTES POLINOMIO OBTENIDO POR EL ALUMNO CON EL REAL\n");
  printf("         alumno   -    real\n");
  for(int k=0;k<A_sol.dim();k++){
    if(k<A.dim()){
      printf("A[%d] : %lf  -  %lf\n",k,A[k],A_sol[k]);
      continue;
    }
    else{
      printf("A[%d] :  NO CALCULADO  -  %lf\n ",k,A_sol[k]);
    }
  }

  /// COMPARAMOS LOS RESULTADOS OBTENIDOS CON LOS QUE DEBERÍAN SALIR Y
  /// QUE PREVIAMENTE HEMOS ALMACENADO EN interpolacion.csv
  Array1D< real > res("interpolacion.csv");

  printf("\n      edad     alumno   -    real\n");
  for(int k=0;k<res.dim();k++){
    printf("edad = %d ->  %lf - %lf\n",5+5*k,mn_evaluar_polinomio_interpolador(A,edad,5.+5.*k),res[k]);
  }

}



