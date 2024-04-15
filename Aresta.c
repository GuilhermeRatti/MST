#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "UnionFind.h"
#include "Aresta.h"
#include "Ponto.h"

typedef struct Aresta{
    int idx_ponto1, idx_ponto2; // Index dos pontos 1 e 2 no vetorzao de pontos; eh mais barato que salvar o ponteiro
    MACRO_TAMANHO distancia;
}Aresta;

// Funcao para criar distancias entre dois pontos
static Aresta aresta_cria(int idx_p1, int idx_p2, MACRO_TAMANHO distancia)
{
    Aresta aresta;
    aresta.idx_ponto1 = idx_p1;
    aresta.idx_ponto2 = idx_p2;
    aresta.distancia = distancia;

    return aresta;
}

void _min_heapify(int quantidade_arestas, Aresta *vetor_arestas, int idx)
{
    int filho_esquerda = 2*idx+1, filho_direita = 2*idx + 2, menor_val = idx;
    
    if(filho_esquerda < quantidade_arestas)
    {
        
        if(vetor_arestas[filho_esquerda].distancia < vetor_arestas[idx].distancia)
        {
            menor_val = filho_esquerda;
        }
    }
    if(filho_direita < quantidade_arestas)
    {
        if(vetor_arestas[filho_direita].distancia < vetor_arestas[menor_val].distancia)
        {
            menor_val = filho_direita;
        }
    }
    
    if(menor_val != idx)
    {
        Aresta aux = vetor_arestas[idx];
        vetor_arestas[idx] = vetor_arestas[menor_val];
        vetor_arestas[menor_val] = aux;
        _min_heapify(quantidade_arestas,vetor_arestas,menor_val);
    }
}       

void _build_heap(int quantidade_arestas, Aresta *vetor_arestas)
{
    for(int i = (quantidade_arestas/2-1); i>=0; i--)
        _min_heapify(quantidade_arestas, vetor_arestas, i);
}

void _define_clusters(pPonto *pontos, int limite_unioes, int quantidade_arestas, Aresta *arestas)
{
    int unioes_feitas = 0;
    int vertices[2] = {-1,-1};

    while (unioes_feitas < limite_unioes)
    {
        Aresta menor_aresta = arestas[0];
        arestas[0] = arestas[quantidade_arestas-1];
        _min_heapify(quantidade_arestas-1,arestas,0); //LogN

        // Tenta unir os vertices evitando unioes circulares (retorno 0)
        if (UF_union(pontos, menor_aresta.idx_ponto1, menor_aresta.idx_ponto2)) unioes_feitas++;

        quantidade_arestas--;
    }
}

// Registro das distancias no vetor
void arestas_preenche_vetor_e_calcula_clusters(pPonto *vetor_pontos, int quantidade_pontos, int dimensoes, int limite_unioes)
{
    int quantidade_arestas = (pow(quantidade_pontos,2)-quantidade_pontos)/2;

    Aresta *vetor_arestas = (Aresta*)malloc(quantidade_arestas*sizeof(Aresta));
    int k=0;
    for(int i=0; i<quantidade_pontos; i++)
        for(int j=i+1; j<quantidade_pontos; j++) // Calcula a distancia entre os pontos vetor[i] e vetor[j] para registrar
            vetor_arestas[k++] = aresta_cria(i,j,ponto_calcula_distancia(vetor_pontos[i], vetor_pontos[j], dimensoes));
    
    // Ordenador das distancias
    _build_heap(quantidade_arestas,vetor_arestas);

    _define_clusters(vetor_pontos, limite_unioes, quantidade_arestas, vetor_arestas);

    free(vetor_arestas);
}

// void aresta_retorna_vertices(Aresta aresta, int retorno[2])
// {
//     retorno[0] = aresta.idx_ponto1;
//     retorno[1] = aresta.idx_ponto2;
// }

double aresta_retorna_distancia(Aresta a)
{
    return a.distancia;
}