#include <stdio.h>
#include <stdlib.h>
#include "Aresta.h"
#include "Ponto.h"

struct Aresta{
    int idx_ponto1, idx_ponto2; // Index dos pontos 1 e 2 no vetorzao de pontos; eh mais barato que salvar o ponteiro
    MACRO_TAMANHO distancia;
}Aresta;

int _aresta_comparador(const void* a1, const void *a2)
{
    // Como estamos comparando doubles para retornar um inteiro, necessita-se de if else's
    if((*(pAresta*)a1)->distancia > (*(pAresta*)a2)->distancia) { return 1; }
    else if((*(pAresta*)a1)->distancia < (*(pAresta*)a2)->distancia) { return -1; }
    else { return 0; }
}

// Funcao para criar distancias entre dois pontos
pAresta aresta_cria(int idx_p1, int idx_p2, MACRO_TAMANHO distancia)
{
    pAresta arest = (pAresta)malloc(sizeof(struct Aresta));
    arest->idx_ponto1 = idx_p1;
    arest->idx_ponto2 = idx_p2;
    arest->distancia = distancia;

    return arest;
}

void _max_heapify(pAresta *vetor_arestas, int quantidade_arestas, int idx)
{
    int filho_esquerda = 2*idx, filho_direita = 2*idx + 1, maior_val = idx;

    if(filho_esquerda < quantidade_arestas && vetor_arestas[filho_esquerda]->distancia > vetor_arestas[idx]->distancia)
        maior_val = filho_esquerda;
    if(filho_direita < quantidade_arestas && vetor_arestas[filho_direita]->distancia > vetor_arestas[maior_val]->distancia)
        maior_val = filho_direita;
    if(maior_val != idx)
    {
        pAresta aux = vetor_arestas[idx];
        vetor_arestas[idx] = vetor_arestas[maior_val];
        vetor_arestas[maior_val] = vetor_arestas[idx];
    }
}       

void _build_heap(pAresta *vetor_arestas, int quantidade_arestas)
{
    for(int i = 0; i<quantidade_arestas/2; i++)
        _max_heapify(vetor_arestas, quantidade_arestas, i);
    
}

// Registro das distancias no vetor
void aresta_preenche_vetor(pAresta *vetor_arestas, pPonto *vetor_pontos, int quantidade_pontos, int dimensoes)
{
    int k=0;
    for(int i=0; i<quantidade_pontos; i++)
        for(int j=i+1; j<quantidade_pontos; j++) // Calcula a distancia entre os pontos vetor[i] e vetor[j] para registrar
            vetor_arestas[k++] = aresta_cria(i,j,ponto_calcula_distancia(vetor_pontos[i], vetor_pontos[j], dimensoes));
            // if()
}

// Ordenador das distancias
void aresta_ordena(pAresta *vetor_arestas, int quantidade_distancias)
{
    qsort(vetor_arestas, quantidade_distancias, sizeof(pAresta), _aresta_comparador);
}

void aresta_retorna_vertices(pAresta aresta, int retorno[2])
{
    retorno[0] = aresta->idx_ponto1;
    retorno[1] = aresta->idx_ponto2;
}

// Print das distancias pra visualizacao de ordenacao (TUDO OK!)
void aresta_print(pAresta a)
{
    printf("DISTANCIA: %lf | PONTOS: %d e %d.\n", a->distancia, a->idx_ponto1, a->idx_ponto2);
}

// Destroi uma estrutura distancia
void aresta_destroi(pAresta a)
{
    free(a);
}
