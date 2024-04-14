#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IO.h"

int* arquivo_setup(const char *caminho_arquivo)
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
        if(getline(&linha, &size, arquivo)==-1) break;
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
    int *setup_resultados = (int*)malloc(2*sizeof(int));
    setup_resultados[0] = qtd_pontos;
    setup_resultados[1] = dimensoes;

    return setup_resultados;
}

void arquivo_leitura_e_registro(const char *caminho_arquivo, pPonto *pontos, int dimensoes, int quantidade_pontos)
{
    // Verificando se o arquivo existe e erros na abertura
    FILE *arquivo = fopen(caminho_arquivo, "r");
    if(arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    // Lendo o arquivo e registrando os pontos
    size_t size = 0;
    char *linha = NULL;
    int qtd_pontos_registrados = 0;
    
    int fim_da_leitura=0;
    while (feof(arquivo) == 0) // Essa parte ta dando problema, antes do arquivo terminar tem mais 1 blank space que nao conta
                               // como final de arquivo, nao finaliza o loop ai quebra o codigo logo abaixo pq vai tentar ler coisa que nao tem
    {
        if(getline(&linha, &size, arquivo) == -1) break;
       
        char* token = strtok(linha, ",");
        char* id = (char*)malloc(strlen(token)*sizeof(char)+1);         // Alocando espaco para armazenar o ID lido pelo strtok
                                                                        // Isso eh necessario por conta de um comportamento especifico do getline()
                                                                        // Caso contrario, assim que liberarmos o ponteiro line, vai tudo pro caralho
        strcpy(id,token);
        
        MACRO_TAMANHO *coordenadas = (MACRO_TAMANHO*)malloc(dimensoes*sizeof(MACRO_TAMANHO));// Aloca um vetor para armazenar as dimensoes do ponto
        for (int i = 0; i < dimensoes; i++)
        {
            token = strtok(NULL, ",");
            coordenadas[i] = atof(token);
        }

        pontos[qtd_pontos_registrados++] = ponto_cria(id, coordenadas); // Salvando o ponto criado no vetor
    }
    
    free(linha);        // Liberando espaço alocado pela variavel usada pela funcao getline()
    fclose(arquivo);    // Liberando espaço alocado pelo arquivo
}

void saida_printa_vetor_pontos(pPonto *pontos, int quantidade_pontos)
{
    for(int i = 0; i < quantidade_pontos; i++)
        ponto_print(pontos, pontos[i], i);
}