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

void _min_heapify(pAresta *vetor_arestas, int quantidade_arestas, int idx)
{
    int filho_esquerda = 2*idx+1, filho_direita = 2*idx + 2, menor_val = idx;
    
    if(filho_esquerda < quantidade_arestas)
    {
        
        if(vetor_arestas[filho_esquerda]->distancia < vetor_arestas[idx]->distancia)
        {
            menor_val = filho_esquerda;
        }
    }
    if(filho_direita < quantidade_arestas)
    {
        if(vetor_arestas[filho_direita]->distancia < vetor_arestas[menor_val]->distancia)
        {
            menor_val = filho_direita;
        }
    }
    
    if(menor_val != idx)
    {
        pAresta aux = vetor_arestas[idx];
        vetor_arestas[idx] = vetor_arestas[menor_val];
        vetor_arestas[menor_val] = aux;
        _min_heapify(vetor_arestas,quantidade_arestas,menor_val);
    }
}       

void _build_heap(pAresta *vetor_arestas, int quantidade_arestas)
{
    for(int i = (quantidade_arestas/2-1); i>=0; i--)
        _min_heapify(vetor_arestas, quantidade_arestas, i);
}

// Registro das distancias no vetor
void aresta_preenche_vetor(pAresta *vetor_arestas, pPonto *vetor_pontos, int quantidade_pontos, int dimensoes)
{
    int k=0;
    for(int i=0; i<quantidade_pontos; i++)
        for(int j=i+1; j<quantidade_pontos; j++) // Calcula a distancia entre os pontos vetor[i] e vetor[j] para registrar
            vetor_arestas[k++] = aresta_cria(i,j,ponto_calcula_distancia(vetor_pontos[i], vetor_pontos[j], dimensoes));
}

// void aresta_preenche_vetor(pAresta *vetor_arestas, pPonto *vetor_pontos, int quantidade_pontos, int quantidade_arestas, int dimensoes)
// {
//     int k=0, heap_construido = 0;
//     for(int i=0; i<quantidade_pontos; i++)
//         for(int j=i+1; j<quantidade_pontos; j++) // Calcula a distancia entre os pontos vetor[i] e vetor[j] para registrar
//         {    
//             double distancia = ponto_calcula_distancia(vetor_pontos[i], vetor_pontos[j], dimensoes);
//             if(k<quantidade_arestas)
//                 vetor_arestas[k++] = aresta_cria(i,j,distancia);
//             else if(vetor_arestas[0]->distancia > distancia)
//             {
//                 aresta_destroi(vetor_arestas[0]);
//                 vetor_arestas[0] = aresta_cria(i,j,distancia);
//                 _min_heapify(vetor_arestas,quantidade_arestas,0);
//             }

//             if(k>=quantidade_arestas && heap_construido == 0) 
//             {
//                 heap_construido = 1;
//                 _build_heap(vetor_arestas,quantidade_arestas);
//             }
//         }  
// }

// Ordenador das distancias
void aresta_ordena(pAresta *vetor_arestas, int quantidade_arestas)
{
    _build_heap(vetor_arestas,quantidade_arestas);
}

pAresta aresta_retorna_menor_distancia(pAresta *vetor_arestas, int quantidade_arestas)
{
    pAresta menor_aresta = vetor_arestas[0];
    vetor_arestas[0] = vetor_arestas[quantidade_arestas-1];
    _min_heapify(vetor_arestas,quantidade_arestas-1,0); //LogN
    return menor_aresta;
}

void aresta_retorna_vertices(pAresta aresta, int retorno[2])
{
    retorno[0] = aresta->idx_ponto1;
    retorno[1] = aresta->idx_ponto2;
}

double aresta_retorna_distancia(pAresta a)
{
    return a->distancia;
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
