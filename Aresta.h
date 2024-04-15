#if !defined(_ARESTA_H_)
#define _ARESTA_H_

#include "Ponto.h"

// Funcao para criar uma estrutura arestas
// Aresta aresta_cria(int idx_p1, int idx_p2, MACRO_TAMANHO distancia);

// Funcao para criar e registrar as arestas em seu respectivo vetor
void arestas_preenche_vetor_e_calcula_clusters(pPonto *vetor_pontos, int quantidade_pontos, int dimensoes, int limite_unioes);

// // Funcao para ordenar o vetor de arestas em ordem crescente
// void aresta_ordena(int quantidade_arestas, Aresta vetor_arestas[]);

// Aresta aresta_retorna_menor_distancia(int quantidade_arestas, Aresta vetor_arestas[]);

// void aresta_retorna_vertices(Aresta aresta, int retorno[2]);

// double aresta_retorna_distancia(Aresta a);

#endif // _ARESTA_H_