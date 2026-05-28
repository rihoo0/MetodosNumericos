
/// INCLUSION DE LIBRERIAS NECESARIAS
#include <stdio.h>
#include "mn_lapack.h"

/// -----------------------------------------------------------
/// FUNCION PARA RESOLVER LOS SISTEMAS TRIANGULARES PARA CALCULAR LA INVERSA
/// ------------------------------------------------------------
Array2D< real > mn_remonte (Array2D< real > &A,Array2D< real > &B)
{
  /** DECLARAMOS LA MATRIZ Mi DONDE SE DEVUELVE LA MATRIZ INVERSA SI TODO VA BIEN */
  Array2D< real > Mi(A.dim1(),A.dim2());

  /// REMONTE
   for(int k=A.dim1()-1;k>=0;k--){
    for(int n=0;n<A.dim1();n++){
      if(A[k][k]==0.) return Array2D< real >();
      Mi[k][n]=B[k][n];
      for(int l=k+1;l<A.dim1();l++){
        Mi[k][n]-= A[k][l]*Mi[l][n];
      }
      Mi[k][n]/=A[k][k];
    }
  }
  return(Mi);
}

/** FUNCIÓN QUE CALCULA LA POSICIÓN DE LA DIAGONAL HACIA ABAJO DONDE SE ENCUENTRA
EL MÁXIMO EN VALOR ABOLUTO DE UNA MATRIZ */
int max_pos(
Array2D< real > &A /** matriz */,
int k /** posición diagonal */){
  real max=fabs(A[k][k]);
  int kmax=k;
  for(int m=k+1;m<A.dim1();m++){
    if(fabs(A[m][k])>max){
      max=fabs(A[m][k]);
      kmax=m;
    }
  }
  return kmax;
}

/** FUNCIÓN PARA CALCULAR LA INVERSA DE UNA MATRIZ POR EL METODO DE GAUSS CON  PIVOTACIÓN
    FÍSICA. DEVUELVE LA MATRIZ INVERSA SI TERMINA BIEN EN CASO CONTRARIO DEVUELVE UNA MATRIZ
    VACÍA. SE PUEDE USAR LA FUNCION max_pos() PARA CALCULAR EL MÁXIMO DE LA COLUMNA
    HACIA ABAJO Y mn_pivotar() PARA INTERCAMBIAR DOS VALORES
*/
Array2D< real > mn_gauss_inversa(
const Array2D< real > &A_original  /** MATRIZ  */)
{
  /// HACER ALUMNO
  Array2D< real > A=A_original.copy();
  if(A.dim1()!=A.dim2() || A.dim1()==0) return Array2D<real>();

  Array2D< real > B(A.dim1(),A.dim2(),0.);
  for(int k=0;k<A.dim1();k++) B[k][k]=1.;

  for(int k=0;k<A.dim1();k++){
    int kmax=max_pos(A,k);
    if(A[kmax][k]==0.) return Array2D< real >();

    if(kmax!=k){
      for(int i=0;i<A.dim1();i++){
        mn_pivotar(A[k][i],A[kmax][i]);
        mn_pivotar(B[k][i],B[kmax][i]);
      }
    }

    for(int j=k+1;j<A.dim1();j++){
          real mul=-A[j][k]/A[k][k];
          A[j][k]=0.;
          for(int n=k+1;n<A.dim1();n++) A[j][n]+=mul*A[k][n];
          for(int n=0;n<A.dim1();n++) B[j][n]+=mul*B[k][n];
    }
  }

  return mn_remonte (A,B);

}



///* FUNCION PARA LEER UNA MATRIZ DE DISCO DE DIMENSION dimension Y LO ALMACENA EN LA MATRIZ matriz  */
int mn_leer_matriz(
  char *nombrefichero,
  Array2D< real > &matriz)
{
  int dimension1,dimension2;
  float paso;
  FILE *f;
  if(f=fopen( nombrefichero, "r"),!f){
    printf("Problema con la apertura del fichero\n");
    return 1;
  }
  fscanf(f,"%d %d\n",&dimension1, &dimension2);
  if(dimension1<1 || dimension2<1) return(-1);

  /// RESERVAMOS MEMORIA PARA LA MATRIZ
  Array2D< real > m(dimension1,dimension2);

  for(int i=0;i<dimension1;i++){
    for(int j=0;j<dimension2;j++){

       fscanf(f,"%f ",&paso);
       m[i][j]=paso;
       //printf("paso=%e\n",(double) m[i][j]);
    }
    fscanf(f,"\n");
  }
  fclose(f);
  matriz=m.copy();
  return dimension1;
}

///* FUNCION PARA ESCRIBIR UNA MATRIZ EN DISCO */
int mn_escribir_matriz(
  char *nombrefichero,
  Array2D< real > &matriz)
{
  int i,j;
  FILE *f;
  if(f=fopen( nombrefichero, "w"),!f){
    printf("Problema con la escritura del fichero\n");
    return 1;
  }
  fprintf(f,"%d %d\n",matriz.dim1(),matriz.dim2());
  for(i=0;i<matriz.dim1();i++){
    for(j=0;j<matriz.dim2();j++){
       fprintf(f,"%f ",(float) matriz[i][j]);
    }
    fprintf(f,"\n");
  }
  fclose(f);
  return 0;
}












