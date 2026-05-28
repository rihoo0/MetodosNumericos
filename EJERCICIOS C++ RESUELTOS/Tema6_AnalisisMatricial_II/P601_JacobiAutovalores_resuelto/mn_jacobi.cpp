#include "mn_jacobi.h"

/******************************************************************************
// FUNCION QUE CALCULA LOS AUTOVALORES DE UNA MATRIZ (LOS DEVUELVE EN UN ARRAY)
//*****************************************************************************/
Array1D< real > jacobi (Array2D< real >&A, /// matriz original
Array2D< real >&Autovectores,  /// matriz de salida con los autovectores
const int NMaxIter,  /// número máximo de iteraciones
const real TOL, /// tolerancia para detener el algoritmo
int &Niter) /// variable de salida con el numero  de iteraciones
{
  /** COMPROBAMOS QUE LAS DIMENSIONES SON COHERENTES */
  if(A.dim1()!=A.dim2() || A.dim1()!=Autovectores.dim1()
     || A.dim2()!=Autovectores.dim2() ){
         return(Array1D< real >());
  }

  /** COMPROBAMOS QUE LA MATRIZ A ES SIMÉTRICA */
  int N=A.dim1();
  for(int i=0;i<N;i++){
    for(int j=i+1;j<N;j++){
      if(A[i][j]!=A[j][i]){
        return(Array1D< real >());
      }
    }
  }

  /** HACER ALUMNO */
  Array1D< real > autovalores(N);
  Autovectores=Array2D< real>(N,N,0.);
  for(int i=0;i<N;i++) Autovectores[i][i]=1.;

  for (Niter=0;Niter<NMaxIter;Niter++){
    int p=0;
    int q=1;
    real Max = 0;
    for (int i=0;i<N;i++){
      for (int j=i+1;j<N;j++){
        if (fabs(A[i][j])>Max){
          Max=fabs(A[i][j]);
          p=i;
          q=j;
        }
      }
    }
    if (Max<TOL){
      for(int l=0;l<N;l++) autovalores[l]=A[l][l];
      return (autovalores);
    }

    real alfa=0.5*atan( (2.*A[p][q])/(A[q][q]-A[p][p]) );
    real co=cos(alfa);
    real si=sin(alfa);

    for(int k=0;k<N;k++){
      real temp= Autovectores[k][p];
      Autovectores[k][p]=co*temp-si*Autovectores[k][q];
      Autovectores[k][q]=co*Autovectores[k][q]+si*temp;
      if(k==p || k==q) continue;
      temp=A[p][k];
      A[k][p]=A[p][k]=co*temp-si*A[q][k];
      A[k][q]=A[q][k]=co*A[q][k]+si*temp;
    }
    real App=A[p][p];
    A[p][p]=co*(co*App-si*A[p][q])-si*(co*A[p][q]-si*A[q][q]);
    A[q][q]=co*(co*A[q][q]+si*A[p][q])+si*(co*A[p][q]+si*App);
    A[p][q]=A[q][p]=0.;

  }

  return(Array1D< real >());
}

