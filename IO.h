#include <stdio.h>
#include <stdlib.h>
#include "Ponto.h"

/*
    Verifica um pre_setup a ser feito na alocacao de memoria para a leitura do arquivo como: quantidade de pontos e dimensoes
    
    retorna um vetor de inteiros sendo:
    vet[0] = quantidade de pontos
    vet[1] = dimensoes
*/
int* arquivo_setup(char *arquivo);

/*
    Le um arquivo e registra os pontos em um vetor de ponteiros de pontos

    arquivo: arquivo a ser lido
    pontos: vetor de ponteiros de pontos
    dimensoes: dimensoes dos pontos
    quantidade_pontos: quantidade de pontos a serem lidos
*/
void arquivo_leitura_e_registro(char *caminho_arquivo, pPonto *pontos, int dimensoes, int quantidade_pontos);