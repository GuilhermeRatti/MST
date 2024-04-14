#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "Ponto.h"

struct Ponto{
    char *id;
    double *dimensoes;
    int grupo;
    int tamanho_grupo;
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


int ponto_retorna_grupo(pPonto ponto)
{
    return ponto->grupo;
}

void ponto_registra_grupo(pPonto ponto, int grupo)
{
    ponto->grupo = grupo;
}

int ponto_retorna_nfilhos(pPonto ponto)
{
    return ponto->tamanho_grupo;
}

void ponto_incrementa_nfilhos(pPonto receptor, pPonto doador)
{   
    receptor->tamanho_grupo += doador->tamanho_grupo;
}

void ponto_setup_de_ordenacao(pPonto *vetor_pontos, int tamanho_vet_pontos)
{
    printf("TAMANHO: %d\n",tamanho_vet_pontos);
    qsort(vetor_pontos, tamanho_vet_pontos, sizeof(pPonto), _ponto_comparador_alfabetico); // Ordena por ordem alfabetica
    
    // Atribui grupos
    for(int i=0; i<tamanho_vet_pontos; i++) 
    {
        vetor_pontos[i]->grupo = i;
        vetor_pontos[i]->tamanho_grupo = 1;
    }
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