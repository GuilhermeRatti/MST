#pragma once

typedef struct Ponto *pPonto;
typedef struct Distancia *pDistancia;

// *******************************
// ****** FUNCOES DE PONTOS ******
// *******************************
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

// ***********************************
// ****** FUNCOES DE DISTANCIAS ******
// ***********************************

// Funcao para criar uma estrutura distancia
pDistancia distancia_cria(int idx_p1, int idx_p2, double distancia);

// Funcao para criar e registrar as distancias em seu respectivo vetor
void distancia_preenche_vetor(pDistancia *vetor_distancias, pPonto *vetor_pontos, int quantidade_pontos, int dimensoes);

// Funcao para ordenar o vetor de distancias em ordem crescente
void distancia_ordena(pDistancia *vetor_distancias, int quantidade_distancias);

void distancia_print(pDistancia d);

void distancia_destroi(pDistancia d);