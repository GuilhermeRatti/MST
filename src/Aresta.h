#if !defined(_ARESTA_H_)
#define _ARESTA_H_

#include "Ponto.h"

typedef struct Aresta Aresta;

// Funcao para criar uma estrutura arestas
Aresta* aresta_cria_vetor(int quantidade_arestas);

// Funcao para criar e registrar as arestas em seu respectivo vetor
void arestas_preenche_vetor(Aresta *vetor_arestas, pPonto *vetor_pontos, int quantidade_pontos, int quantidade_arestas, int dimensoes, int limite_unioes);

void aresta_retorna_vertices_menor_distancia(Aresta *vetor_arestas, int quantidade_arestas, int vertices[]);

// Ordenador das distancias (no caso garante a propriedade de heap em que vetor[0] eh o menor valor possivel)
void build_heap(int quantidade_arestas, Aresta *vetor_arestas);

void aresta_destroi_vetor(Aresta *vetor_aresta);

#endif // _ARESTA_H_