/// INCLUSION DE LIBRERIAS NECESARIAS
#include <stdio.h>
#include "mn_lapack.h"

/** FUNCIÓN QUE CALCULA LA POSICIÓN DE LA DIAGONAL HACIA ABAJO DONDE SE ENCUENTRA
EL MÁXIMO EN VALOR ABSOLUTO DE UNA MATRIZ */
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

/** FUNCION PARA RESOLVER SISTEMAS POR EL METODO DE GAUSS CON PIVOTACIÓN FÍSICA
    DEVUELVE EL VECTOR SOLUCIÓN DEL SISTEMA SI TERMINA BIEN
    DEVUELVE UN VECTOR VACÍO EN CASO DE ERROR.
    SE PUEDE USAR LA FUNCION max_pos() PARA CALCULAR EL MÁXIMO DE LA COLUMNA
    HACIA ABAJO Y mn_pivotar() PARA INTERCAMBIAR DOS VALORES */
Array1D< real > mn_gauss(
Array2D< real > &A_original  /** MATRIZ DEL SISTEMA */,
Array1D< real > &b_original) /** VECTOR DE TERMINOS INDEPENDINENTES */
{
  /// HACER ALUMNO
  Array2D< real > A=A_original.copy();
  Array1D< real > b=b_original.copy();

  if(A.dim1()!=A.dim2() || A.dim1()!=b.dim() || b.dim()==0) return Array1D<real>();

  for(int k=0;k<b.dim()-1;k++){
    int kmax=max_pos(A,k);
    if(A[kmax][k]==0.) return Array1D<real>();
    if(kmax!=k){
      for(int j=k;j<b.dim();j++){
        mn_pivotar(A[k][j],A[kmax][j]);
      }
      mn_pivotar(b[kmax],b[k]);
    }
    for(int j=k+1;j<b.dim();j++){
          real mul=-A[j][k]/A[k][k];
          A[j][k]=0.;
          for(int n=k+1;n<b.dim();n++) A[j][n]+=mul*A[k][n];
          b[j]+=mul*b[k];
    }
  }

  return mn_remonte(A,b);
}

/// -----------------------------------------------------------
/// FUNCION PARA RESOLVER UN SISTEMA TRIANGULAR A TRAVES DE UN REMONTE
/// ------------------------------------------------------------
Array1D< real > mn_remonte (const Array2D< real > &B, const Array1D< real > &z)
{
   int i,j;
   if(B.dim1()!=B.dim2()  || B.dim1()!=z.dim() ) return(Array1D< real >());
   int N=B.dim1();
   Array1D< real > DU(N);

   /// INICIAMOS EL REMONTE
   for (i=N-1;i>=0;i--){
      if (B[i][i]==0){  /// comprobamos que la diagonal es distinto de cero
         return(Array1D< real >());
      }
      DU[i]=z[i]; /// inicializamos la solucion
      for  (j=i+1;j<N;j++){ /// aplicamos la formula para calcular la solución
         DU[i]=DU[i] - B[i][j]*DU[j];
      }
      DU[i]=DU[i]/B[i][i];
  }
  return(DU);
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












