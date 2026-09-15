#include "mn_determinante.h"
#include <stdlib.h>
#include <stdio.h>

/// CÁLCULO DEL DETERMINANTE DE UNA MATRIZ USANDO UN ALGORITMO RECURSIVO
/// DESARROLLANDO EL DETERMINANTE POR LA PRIMERA FILA
/// DEVUELVE 0 SI LA MATRIZ ESTÁ VACÍA O NO ES CUADRADA
real mn_determinante_recursivo(Array2D< real > &A)
{
  /// HACER ALUMNO,
    if(A.dim1() == 0 || A.dim1() != A.dim2()) return 0;
    int N = A.dim1();
    real determinante = 0;
    
    if(N > 1){
        
        for(int k = 0; k < N; k++){
            Array2D<real> Ak(N - 1, N - 1);
            
            for(int i = 1git; i < N; i++){
                int col = 0;
                for(int j = 0; j < N; j++){
                    if(j == k) continue;
                    Ak[i - 1][col] = A[i][j];
                    col++;
                }
            }
            real signo = (k % 2 == 0) ? 1: -1;
            determinante += A[0][k] * signo * mn_determinante_recursivo(Ak);
        }
    } else {
        determinante = A[0][0];
    }
    return determinante;
}

