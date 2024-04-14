#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "Ponto.h"

struct Ponto{
    char *id;
    double *dimensoes;
    int grupo;
}Ponto;

// Funcao para comparar pontos quanto a sua respectiva ordem alfabetica
int _ponto_comparador_alfabetico(const void* p1, const void* p2)
{
    return strcmp((*(pPonto*)p1)->id,(*(pPonto*)p2)->id);
}

// Funcao para criar pontos; grupos serao definidos apos a ordenacao dos pontos por ordem alfabetica.
pPonto ponto_cria(char *id, double *dims)
{
    pPonto ponto = (pPonto)malloc(sizeof(struct Ponto));
    ponto->id = id;
    ponto->dimensoes = dims;

    return ponto;
}

void ponto_setup_de_ordenacao(pPonto *vetor_pontos, int tamanho)
{
    qsort(vetor_pontos, tamanho, sizeof(pPonto), _ponto_comparador_alfabetico); // Ordena por ordem alfabetica
    
    // Atribui grupos
    for(int i=0; i<tamanho; i++) 
        vetor_pontos[i]->grupo = i;

    // A ideia aqui eh que se ordenassemos em ordem alfabetica depois de fazer as operacoes de union, quebraria tudo
    // porque os grupos vao ser referenciados por posicao... por ex.: grupo 2 significa que o ponto em questao ta no
    // mesmo grupo que o ponto na posicao 2 do vetor. Se ordenar depois vai embaralhar tudo e quebra o union.
}

// Funcao para calcular distancia entre dois pontos; como isto vai servir somente para comparar distancias,
// seria melhor armazenar o quadrado das distancias, pois nao faz a menor diferenca, matematicamente, comparar
// o quadrado entre as distancias ou a raiz das distancias. Salva um passo a menos para calcular.
double ponto_calcula_distancia(pPonto p1, pPonto p2, int dimensoes)
{
    double quadrado_distancia=0;
    for(int i=0; i<dimensoes; i++)
        quadrado_distancia = pow(p1->dimensoes[i]-p2->dimensoes[i],2);
    
    return quadrado_distancia;
}

// Print de um ponto para visualizacao
void ponto_print(pPonto p)
{
    printf("%s | GRUPO: %d\n",p->id,p->grupo);
}

// Destroi um ponto e seus atributos alocados
void ponto_destroi(pPonto p)
{
    free(p->dimensoes);
    free(p->id);
    free(p);
}

// =====================================================================================================================================
// =====================================================================================================================================

struct Aresta{
    int idx_ponto1, idx_ponto2; // Index dos pontos 1 e 2 no vetorzao de pontos; eh mais barato que salvar o ponteiro
    double distancia;
}Aresta;

int _aresta_comparador(const void* a1, const void *a2)
{
    // Como estamos comparando doubles para retornar um inteiro, necessita-se de if else's
    if((*(pAresta*)a1)->distancia > (*(pAresta*)a2)->distancia) { return 1; }
    else if((*(pAresta*)a1)->distancia < (*(pAresta*)a2)->distancia) { return -1; }
    else { return 0; }
}

// Funcao para criar distancias entre dois pontos
pAresta aresta_cria(int idx_p1, int idx_p2, double distancia)
{
    pAresta arest = (pAresta)malloc(sizeof(struct Aresta));
    arest->idx_ponto1 = idx_p1;
    arest->idx_ponto2 = idx_p2;
    arest->distancia = distancia;

    return arest;
}

// Registro das distancias no vetor
void aresta_preenche_vetor(pAresta *vetor_arestas, pPonto *vetor_pontos, int quantidade_pontos, int dimensoes)
{
    int k=0;
    for(int i=0; i<quantidade_pontos; i++)
        for(int j=i+1; j<quantidade_pontos; j++) // Calcula a distancia entre os pontos vetor[i] e vetor[j] para registrar
            vetor_arestas[k++] = aresta_cria(i,j,aresta_calcula(vetor_pontos[i], vetor_pontos[j], dimensoes));
}

// Ordenador das distancias
void aresta_ordena(pAresta *vetor_arestas, int quantidade_distancias)
{
    qsort(vetor_arestas, quantidade_distancias, sizeof(pAresta), _aresta_comparador);
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
