#pragma once

typedef struct Ponto *pPonto;
typedef struct Aresta *pAresta;

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

// ********************************
// ****** FUNCOES DE ARESTAS ******
// ********************************

// Funcao para criar uma estrutura arestas
pAresta aresta_cria(int idx_p1, int idx_p2, double distancia);

// Funcao para criar e registrar as arestas em seu respectivo vetor
void aresta_preenche_vetor(pAresta *vetor_arestas, pPonto *vetor_pontos, int quantidade_pontos, int dimensoes);

// Funcao para ordenar o vetor de arestas em ordem crescente
void aresta_ordena(pAresta *vetor_arestas, int quantidade_arestas);

void aresta_print(pAresta a);

void aresta_destroi(pAresta a);