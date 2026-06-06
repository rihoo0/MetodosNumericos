/// INCLUSION DE LIBRERIAS NECESARIAS
#include <stdio.h>
#include "EjerciciosBasicos.h"

/// P11.1 FUNCIÓN QUE CALCULA LA MEDIA DE UN VECTOR
real mn_media(Array1D< real > &u){

}

/// P11.2 FUNCIÓN QUE CALCULA EL MAXIMO DE UN VECTOR
real mn_max(Array1D< real > &u){

}

/// P11.3 FUNCIÓN QUE CALCULA EL MINIMO DE UN VECTOR
real mn_min(Array1D< real > &u){

}

/// P11.4 FUNCIÓN QUE ORDENA UN VECTOR DE MENOR A MAYOR
void mn_ordenar(Array1D< real > &u){

}

/// P11.5 FUNCIÓN PARA MULTIPLICAR UNA MATRIZ POR UN VECTOR
Array1D< real > mn_multiplicacion_matriz_vector(Array2D< real > &A,Array1D< real > &u){

}

/// P11.6 FUNCIÓN QUE DETERMINA SI UN NÚMERO ENTERO ES PRIMO
bool mn_es_primo(int i){

}

/// P11.7 FUNCIÓN QUE CALCULA EL FACTORIAL DE UN NÚMERO NATURAL
real mn_factorial(int n){

}


/// P11.8 FUNCIÓN QUE CALCULA UNA POTENCIA CON UN NÚMERO NATURAL
/// NO SE PUEDE USAR LA FUNCIÓN pow()
real mn_potencia(real x,int n){

}

/// P11.9 FUNCIÓN QUE CALCULA EL DESARROLLO DE TAYLOR DE e^x
/// e^x = 1 + x + x^2/2! + ...... +x^n/n!
real mn_exp(real x,int n){

}

/// P11.10 FUNCIÓN QUE CALCULA EL DESARROLLO DE TAYLOR DE e^x
/// SE HACE LA SUMA HASTA QUE x^n/n! == 0 (EN PRECISIÓN float)
/// e^x = 1 + x + x^2/2! + ...... +x^n/n!
float mn_exp(float x){

}

/// P11.11 FUNCIÓN QUE CALCULA EL DESARROLLO DE TAYLOR DE cos(x)
///  cos(x) = 1 - x^2/2! + x^4/4! - x^6/6!+...... +- x^(2n)/(2n)!
real mn_cos(real x,int n){

}

/// P11.12 FUNCIÓN QUE CALCULA EL DESARROLLO DE TAYLOR DE sin(x)
///  sin(x) = x - x^3/3! + x^5/5! - x^7/7!+...... +- x^(2n+1)/(2n+1)!
real mn_sin(real x,int n){

}

/// P11.13 FUNCIÓN QUE CALCULA EL DESARROLLO DE TAYLOR DE ln(x)
/// ln(x) = (x-1) - ((x-1)^2)/2 + ((x-1)^3)/3 - ((x-1)^4)/4+...... +- ((x-1)^n)/n
real mn_ln(real x,int n){

}

/// P11.14 FUNCIÓN QUE CALCULA y^x DONDE y,x SON NÚMERO REALES
/// USAR LAS FUNCIONES IMPLEMENTADAS mn_exp() y mn_ln() TENIENDO EN CUENTA y^x=e^(x*ln(y))
real mn_pow(real y,real x,int n){

}

/// P11.13 FUNCIÓN QUE CALCULA EL LIMITE DE LA SECUENCIA  yn=(1.+1./n).^n CUANDO n TIENDE A
/// INFINITO EL ALGORITMO PARA CUANDO LA DIFERENCIA EN VALOR ABSOLUTO DE LA DIFERENCIA
/// ENTRE UN VALOR DE LA SECUENCIA Y EL ANTERIOR ES INFERIOR AL PARAMETRO tolerancia
/// EL LIMITE DE LA SECUENCIA ES EL NUMERO e=2.71828182846
/// IMPORTANTE : PARA QUE LAS CONSTANTES LAS TRATE COMO NÚMEROS REALES HAY QUE AÑADIR UN .,
/// ES DECIR, POR EJEMPLO  1. (EN LUGAR DE 1). SI HACEMOS 1/2 EL RESULTADO ES CERO PORQUE HACE
/// LA DIVISIÓN EN PRECISIÓN ENTERA. SIN EMBARGO  1./2.=1./2=1/2.=0.5
real mn_limite1(real tolerancia){

}

/// P11.15 FUNCIÓN QUE CALCULA EL LIMITE DE LA FUNCIÓN f(x)=sin(x)/x CUANDO x TIENDE HACIA 0.
/// EL PARAMETRO tolerancia SE UTILIZA PARA PARAR EL ALGORITMO CUANDO ESTAMOS CERCA DEL LÍMITE
/// EL VALOR DEL LÍMITE ES 1.
real mn_limite2(real tolerancia){

}

/// P11.16 FUNCIÓN QUE CALCULA EL LIMITE DE LA SECUENCIA  yn=X(n+1)/X(n) DONDE X(n) ES LA
/// SUCESIÓN DE FIBONACCI DEFINIDA COMO X(n+1)=X(n)+X(n-1) EMPEZANDO POR X(1)=X(2)=1
/// EL ALGORITMO PARA CUANDO LA DIFERENCIA EN VALOR ABSOLUTO
/// ENTRE UN VALOR DE LA SECUENCIA yn Y EL ANTERIOR ES INFERIOR AL PARAMETRO tolerancia
/// EL LIMITE DE LA SECUENCIA yn ES EL NÚMERO AÚREO IGUAL A (1+SQRT(5))/2 = 1.618033988....
real mn_limite3(real tolerancia){

}

/// P11.16 CÁLCULO DEL NÚMERO PI POR EL MÉTODO DE MONTECARLO. EL ÁREA DEL CÍRCULO DE RADIO
/// 1 ES PI. Y EL AREA DEL CUADRADO DE LADO 2 DONDE SE INSCRIBE EL CÍRCULO ES 4. POR TANTO
/// SI SE ELIGE UN PUNTO AL AZAR EN EL CUADRADO, LA PROBABILIDAD DE QUE CAIGA EN
/// EL CÍRCULO ES PI/4. EL MÉTODO DE MONTECARLO APROXIMA PI COGIENDO PUNTOS AL AZAR EN
/// EL CUADRADO [-1,1]x[-1,1] Y VIENDO QUE PROPORCIÓN CAE EN EL CÍRCULO.
/// NOTA : LA FUNCIÓN rand() DEVUELVE UN VALOR ENTERO ALEATORIO ENTRE 0 Y RAND_MAX
real calculo_pi_montecarlo(int Nintentos){

}
