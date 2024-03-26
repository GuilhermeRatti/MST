#include <stdio.h>
#include <stdlib.h>

typedef struct Ponto *pPonto;

/*
    Cria um ponto com o identificador e coordenadas passados
*/
pPonto ponto_cria(char *id, double *coordenadas);

/*
    Retorna o valor da distancia euclidiana ao quadrado entre dois pontos
*/
double ponto_calcula_distancia(pPonto p1, pPonto p2);