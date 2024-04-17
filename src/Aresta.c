#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "UnionFind.h"
#include "Aresta.h"
#include "Ponto.h"

typedef struct Aresta{
    int idx_ponto1, idx_ponto2; // Index dos pontos 1 e 2 no vetorzao de pontos; eh mais barato que salvar o ponteiro
    double distancia;
}Aresta;

Aresta* aresta_cria_vetor(int quantidade_arestas)
{
    return (Aresta*)malloc(quantidade_arestas*sizeof(struct Aresta));
}

// Funcao para criar distancias entre dois pontos
static Aresta _aresta_cria(int idx_p1, int idx_p2, double distancia)
{
    Aresta aresta;
    aresta.idx_ponto1 = idx_p1;
    aresta.idx_ponto2 = idx_p2;
    aresta.distancia = distancia;

    return aresta;
}

// O proposito de usar min heap eh que conseguimos acessar o menor valor com tempo constante e reorganizar a heap com tempo de logN
// No final, usando heap ao inves de Qsort teremos um pequeno ganho de velocidade, pois apesar de o pior caso dos 2 ser ~NlogN
// O heap sera chamado somente ~(P-K)logA, sendo P o numero de pontos, K o numero de clusters que queremos e A o numero de arestas,
// tal que A >> P e K; o heap pode demorar um pouco mais de acordo com a qtd de ligacoes circulares encontradas. 
// O qsort por outro lado tera pior caso como ~AlogA, oq eh muito maior, pois eh necessario percorrer o vetor de arestas A inteiro
void _min_heapify(int quantidade_arestas, Aresta *vetor_arestas, int idx)
{
    int filho_esquerda = 2*idx+1, filho_direita = 2*idx + 2, menor_val = idx;
    
    // Verifica se o filho da esquerda nao estourou o limite
    if(filho_esquerda < quantidade_arestas)
    {
        // Verifica se o filho da esquerda eh menor que o pai
        if(vetor_arestas[filho_esquerda].distancia < vetor_arestas[idx].distancia)
        {
            menor_val = filho_esquerda;
        }
    }
    // Verifica se o filho da direita nao estourou o limite
    if(filho_direita < quantidade_arestas)
    {
        // Verifica se o filho da direita eh menor que o filho da esquerda ou o pai (depende do resultado da operacao acima)
        if(vetor_arestas[filho_direita].distancia < vetor_arestas[menor_val].distancia)
        {
            menor_val = filho_direita;
        }
    }
    
    // Ve se uma troca eh necessaria
    if(menor_val != idx)
    {
        Aresta aux = vetor_arestas[idx];
        vetor_arestas[idx] = vetor_arestas[menor_val];
        vetor_arestas[menor_val] = aux;
        // Chamada recursiva da funcao
        _min_heapify(quantidade_arestas,vetor_arestas,menor_val);
    }
}       

// Transforma um vetor desordenado em um heap
void build_heap(int quantidade_arestas, Aresta *vetor_arestas)
{
    //Complexidade ~N
    for(int i = (quantidade_arestas/2-1); i>=0; i--)
        _min_heapify(quantidade_arestas, vetor_arestas, i);
}

// Registro das distancias no vetor
void arestas_preenche_vetor(Aresta *vetor_arestas, pPonto *vetor_pontos, int quantidade_pontos, int quantidade_arestas, int dimensoes, int limite_unioes)
{
    int k=0;
    for(int i=0; i<quantidade_pontos; i++)
        for(int l=i+1; l<quantidade_pontos; l++) // Calcula a distancia entre os pontos vetor[i] e vetor[l] para registrar
            vetor_arestas[k++] = _aresta_cria(i,l,ponto_calcula_distancia(vetor_pontos[i], vetor_pontos[l], dimensoes));
}

// Retorna a menor aresta e reordena o vetor para que vet[0] tenha o proximo menor valor
void aresta_retorna_vertices_menor_distancia(Aresta *vetor_arestas, int quantidade_arestas, int vertices[])
{   
    //printf("qtd_arestas: %d\n",quantidade_arestas);
    Aresta menor_aresta = vetor_arestas[0];
    vertices[0] = menor_aresta.idx_ponto1;
    vertices[1] = menor_aresta.idx_ponto2;

    vetor_arestas[0] = vetor_arestas[quantidade_arestas-1];
    _min_heapify(quantidade_arestas-1,vetor_arestas,0); //LogN
}

// Destroi o vetor de arestas
void aresta_destroi_vetor(Aresta *vetor_aresta)
{
    free(vetor_aresta);
}