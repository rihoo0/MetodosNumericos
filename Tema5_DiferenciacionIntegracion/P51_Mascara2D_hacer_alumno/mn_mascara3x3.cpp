#include "mn_aritmeticas.h"
#include "mn_mascara3x3.h"



/// FUNCIÓN QUE APLICA UNA MÁSCARA 3X3 A UNA FUNCIÓN TABULADA F[][]
/// Y RETORNA LA MATRIZ RESULTADO
/// SE DEVUELVE UNA MATRIZ VACÍA SI HAY ALGÚN PROBLEMA
Array2D< real > mn_mascara3x3(
Array2D< real > &F, /// función tabulada
Array2D< real > &m) /// coeficientes máscara 3x3
{
  /// HACER ALUMNO
    if(F.dim1()<1 || F.dim2()<1 || m.dim1()!=3 || m.dim2()!=3) return Array2D< real >();

  Array2D< real > M(F.dim1(),F.dim2(),0.);

  for(int i=1;i<M.dim1()-1;i++){
    for(int j=1;j<M.dim2()-1;j++){
      for(int k=-1;k<2;k++){
        for(int l=-1;l<2;l++){
          M[i][j]+=m[k+1][l+1]*F[k+i][l+j];
        }
      }
    }
  }

   for(int j=1;j<M.dim2()-1;j++){
      for(int k=-1;k<2;k++){
        for(int l=-1;l<2;l++){
          M[0][j]+=m[k+1][l+1]*F[max(k,0)][l+j];
          M[M.dim1()-1][j]+=m[k+1][l+1]*F[M.dim1()-1+min(k,0)][l+j];
        }
      }
  }

  for(int i=1;i<M.dim1()-1;i++){
      for(int k=-1;k<2;k++){
        for(int l=-1;l<2;l++){
          M[i][0]+=m[k+1][l+1]*F[k+i][max(l,0)];
          M[i][M.dim2()-1]+=m[k+1][l+1]*F[k+i][M.dim2()-1+min(l,0)];
        }
      }
  }

  for(int k=-1;k<2;k++){
    for(int l=-1;l<2;l++){
      M[M.dim1()-1][M.dim2()-1]+=m[k+1][l+1]*F[M.dim1()-1+min(k,0)][M.dim2()-1+min(l,0)];
      M[0][M.dim2()-1]+=m[k+1][l+1]*F[max(k,0)][M.dim2()-1+min(l,0)];
      M[M.dim1()-1][0]+=m[k+1][l+1]*F[M.dim1()-1+min(k,0)][max(l,0)];
      M[0][0]+=m[k+1][l+1]*F[max(k,0)][max(l,0)];
    }
  }


  return M;

}

/// FUNCIÓN QUE CALCULA LOS BORDES DE UNA IMAGEN PREVIAMENTE SUAVIZADA
/// DEVUELVE UNA IMAGEN CON VALOR 0 SI NO ES BORDE Y 255 SI ES BORDE
/// ADEMÁS SE DEVUELVE A TRAVÉS DE UN PARÁMETRO LA IMAGEN SUAVIZADA
Array2D< real > mn_calculo_bordes(
Array2D< real > &I, /// IMAGEN DE ENTRADA
int NiteracionesFiltroSuavizado, /// NÚMERO DE ITERACIONES DEL FILTRO DE SUAVIZADO
double percentil_gradiente, /// PERCENTIL SOBRE EL VALOR DEL GRADIENTE PARA
                           /// DECIDIR CUANDO UN PIXEL ES BORDE
Array2D< real > &Ig /// IMAGEN DE SALIDA SUAVIZADA
)
{
  /// MÁSCARAS QUE SE USAN EN ESTA FUNCIÓN
  Array2D<real> mG(3,3); /// máscara suavizado
  mG[0][0]=0.0625;   mG[0][1]=0.125;  mG[0][2]=0.0625;
  mG[1][0]=0.125;    mG[1][1]=0.25;   mG[1][2]=0.125;
  mG[2][0]=0.0625;   mG[2][1]=0.125;  mG[2][2]=0.0625;

  Array2D<real> mx(3,3); /// máscara derivada horizontal
  mx[0][0]=-0.146447;  mx[0][1]=0.; mx[0][2]=0.146447;
  mx[1][0]=-0.207107;  mx[1][1]=0.; mx[1][2]=0.207107;
  mx[2][0]=-0.146447;  mx[2][1]=0.; mx[2][2]=0.146447;

  Array2D<real> my(3,3); /// máscara derivada vertical
  my[0][0]=0.146447;   my[0][1]=0.207107;  my[0][2]=0.146447;
  my[1][0]=0;          my[1][1]=0;         my[1][2]=0;
  my[2][0]=-0.146447;  my[2][1]=-0.207107; my[2][2]=-0.146447;

  /// SUAVIZADO DE LA IMAGEN
  Ig=I.copy();
  for(int k=0;k<NiteracionesFiltroSuavizado;k++) Ig=mn_mascara3x3(Ig,mG);

  /// CALCULO DEL GRADIENTE
  Array2D< real > Igx=mn_mascara3x3(Ig,mx);
  Array2D< real > Igy=mn_mascara3x3(Ig,my);

  /// CÁLCULO DE LA NORMA DEL GRADIENTE
  Array2D< real > Gn(I.dim1(),I.dim2());
  for(int i=0;i<I.dim1();i++){
    for(int j=0;j<I.dim2();j++){
      Gn[i][j]=sqrt( Igx[i][j]*Igx[i][j]+Igy[i][j]*Igy[i][j]);
    }
  }

  /// CÁLCULO PERCENTIL DE LA NORMA DEL GRADIENTE
  double p=Gn.percentil(percentil_gradiente);
  /// CÁLCULO DE LOS BORDES
   Array2D< real > Bordes(I.dim1(),I.dim2(),0.);
   for(int i=0;i<I.dim1();i++){
     for(int j=0;j<I.dim2();j++){
        if(Gn[i][j]>p) Bordes[i][j]=255;
     }
   }


   return Bordes;

}


