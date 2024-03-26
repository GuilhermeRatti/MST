#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IO.h"

int main(int argc, char const *argv[])
{
    char *caminho_arquivo="dados_teste/1.txt";

    // verifica a existencia do arquivo, a quantidade de pontos e as dimensoes dos pontos
    int *qtd_e_dim = arquivo_setup(caminho_arquivo);

    int qtd_pontos = qtd_e_dim[0], dimensoes = qtd_e_dim[1];
    free(qtd_e_dim);
    printf("Quantidade de pontos: %d\n", qtd_pontos);
    printf("Quantidade de dimensoes: %d\n", dimensoes);

    pPonto *vetor_pontos = (pPonto*)calloc(qtd_pontos,sizeof(pPonto));


    free(vetor_pontos);

    return 0;
}