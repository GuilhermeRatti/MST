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

struct Distancia{
    int idx_ponto1, idx_ponto2; // Index dos pontos 1 e 2 no vetorzao de pontos; eh mais barato que salvar o ponteiro
    double distancia;
}Distancia;

int _distancia_comparador(const void* d1, const void *d2)
{
    // Como estamos comparando doubles para retornar um inteiro, necessita-se de if else's
    if((*(pDistancia*)d1)->distancia > (*(pDistancia*)d2)->distancia) { return 1; }
    else if((*(pDistancia*)d1)->distancia < (*(pDistancia*)d2)->distancia) { return -1; }
    else { return 0; }
}

// Funcao para criar distancias entre dois pontos
pDistancia distancia_cria(int idx_p1, int idx_p2, double distancia)
{
    pDistancia dist = (pDistancia)malloc(sizeof(struct Distancia));
    dist->idx_ponto1 = idx_p1;
    dist->idx_ponto2 = idx_p2;
    dist->distancia = distancia;

    return dist;
}

// Registro das distancias no vetor
void distancia_preenche_vetor(pDistancia *vetor_distancias, pPonto *vetor_pontos, int quantidade_pontos, int dimensoes)
{
    int k=0;
    for(int i=0; i<quantidade_pontos; i++)
        for(int j=i+1; j<quantidade_pontos; j++) // Calcula a distancia entre os pontos vetor[i] e vetor[j] para registrar
            vetor_distancias[k++] = distancia_cria(i,j,distancia_calcula(vetor_pontos[i], vetor_pontos[j], dimensoes));
}

// Ordenador das distancias
void distancia_ordena(pDistancia *vetor_distancias, int quantidade_distancias)
{
    qsort(vetor_distancias, quantidade_distancias, sizeof(pDistancia), _distancia_comparador);
}

// Print das distancias pra visualizacao de ordenacao (TUDO OK!)
void distancia_print(pDistancia d)
{
    printf("DISTANCIA: %lf | PONTOS: %d e %d.\n", d->distancia, d->idx_ponto1, d->idx_ponto2);
}

// Destroi uma estrutura distancia
void distancia_destroi(pDistancia d)
{
    free(d);
}
