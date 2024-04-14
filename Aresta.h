#if !defined(_ARESTA_H_)
#define _ARESTA_H_

#include "Ponto.h"

typedef struct Aresta *pAresta;

// Funcao para criar uma estrutura arestas
pAresta aresta_cria(int idx_p1, int idx_p2, MACRO_TAMANHO distancia);

// Funcao para criar e registrar as arestas em seu respectivo vetor
void aresta_preenche_vetor(pAresta *vetor_arestas, pPonto *vetor_pontos, int quantidade_pontos, int dimensoes);

// Funcao para ordenar o vetor de arestas em ordem crescente
void aresta_ordena(pAresta *vetor_arestas, int quantidade_arestas);

pAresta aresta_retorna_menor_distancia(pAresta *vetor_arestas, int quantidade_arestas);

void aresta_retorna_vertices(pAresta aresta, int retorno[2]);

double aresta_retorna_distancia(pAresta a);

void aresta_print(pAresta a);

void aresta_destroi(pAresta a);

#endif // _ARESTA_H_