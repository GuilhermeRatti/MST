#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IO.h"

int* arquivo_setup(char *caminho_arquivo)
{
    // Verificando se o arquivo existe e erros na abertura
    FILE *arquivo = fopen(caminho_arquivo, "r");
    if(arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return NULL;
    }

    // Contabilizando a quantidade de linhas existentes no arquivo
    char *linha = NULL;
    size_t size = 0;
    int qtd_pontos = 0, dimensoes = 0;
    while (feof(arquivo) == 0)
    {
        getline(&linha, &size, arquivo);
        qtd_pontos++;
    }

    // Contabilizando a quantidade de dimensoes a partir da ultima linha lida no arquivo
    char* token = strtok(linha, ",");
    while (token!=NULL)
    {
        token = strtok(NULL, ",");
        dimensoes++;
    }
    dimensoes--; //retirando 1 dimensao porque o primeiro termo lido eh o identificador do ponto

    // Importante dar free no ponteiro linha e do arquivo para liberar a memoria alocada pelas funcoes nativas
    free(linha);
    fclose(arquivo);

    // Alocando um vetor de inteiros para retornar a quantidade de pontos e dimensoes
    int *vetor = (int*)calloc(2,sizeof(int));
    vetor[0] = qtd_pontos;
    vetor[1] = dimensoes;

    return vetor;
}

// FUNCAO NAO TERMINADA TABOM, NAO TESTEI NAO SEI SE TA FUNFANDO E NAO IMPLEMENTEI A FUNCAO ponto_cria()
void arquivo_leitura_e_registro(char *caminho_arquivo, pPonto *pontos, int dimensoes, int quantidade_pontos)
{
    // Verificando se o arquivo existe e erros na abertura
    FILE *arquivo = fopen(caminho_arquivo, "r");
    if(arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return NULL;
    }

    // Lendo o arquivo e registrando os pontos
    char *linha = NULL;
    size_t size = 0;
    int qtd_pontos_registrados = 0;
    while (feof(arquivo) == 0)
    {
        getline(&linha, &size, arquivo);
        char* token = strtok(linha, ",");
        char* id = token;
        double *coordenadas = (double*)calloc(dimensoes,sizeof(double));
        for (int i = 0; i < dimensoes; i++)
        {
            token = strtok(NULL, ",");
            coordenadas[i] = atof(token);
        }

        pontos[qtd_pontos_registrados] = ponto_cria(id, coordenadas);
        qtd_pontos_registrados++;
    }
    free(linha);
}