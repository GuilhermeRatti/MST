#include <stdlib.h>
#include <string.h>
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

void ponto_print(pPonto p1)
{
    printf("%s | GRUPO: %d\n",p1->id,p1->grupo);
}

void ponto_destroi(pPonto p)
{
    free(p->dimensoes);
    free(p->id);
    free(p);
}