#pragma once

typedef struct Ponto *pPonto;

/*
    Cria um ponto com o identificador e coordenadas passados
*/
pPonto ponto_cria(char *id, double *coordenadas);

// Funcao para definir valores como quantidade de pontos a serem lidos e quantidade de dimensoes de um ponto
void ponto_setup_de_ordenacao(pPonto *vetor_pontos, int tamanho);

// Funcao para calcular a distancia euclidiana ao quadrado entre os pontos p1 e p2
double ponto_calcula_distancia(pPonto p1, pPonto p2, int dimensoes);

void ponto_print(pPonto p);

void ponto_destroi(pPonto p);
