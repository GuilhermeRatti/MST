#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IO.h"
#include "UnionFind.h"

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


void imprime_clusters(const char *nome_saida, pPonto *pontos, int qtd_pontos, int qtd_clusters)
{
    // Matriz de pontos para organizacao dos clusters, funciona como uma tabela hash onde o primeiro 
    // indice eh o grupo do cluster 
    pPonto **matriz_pontos = (pPonto **)calloc(qtd_pontos, sizeof(pPonto*));
    // Vetor paralelo de controle de inserção na matriz
    int *vet_idx_interno = (int *)calloc(qtd_pontos, sizeof(int));
    // Vetor de ordem de impressao dos clusters
    int *vet_ordem_clusters = (int *)calloc(qtd_clusters, sizeof(int));
    int idx_ordem_clusters = 0;
    
    int i = 0;
    int grupo_atual = -1;
    int idx_interno = -1;
    pPonto aux = NULL;
    //setup
    for (i = 0; i < qtd_pontos; i++)
    {
        aux = pontos[i];

        grupo_atual = UF_find(pontos, i);
        idx_interno = vet_idx_interno[grupo_atual]; 
        
        if (!idx_interno)
        {
            vet_ordem_clusters[idx_ordem_clusters] = grupo_atual;
            idx_ordem_clusters++;
            matriz_pontos[grupo_atual] = (pPonto *)malloc(ponto_retorna_nfilhos(pontos[grupo_atual])*sizeof(pPonto));
            matriz_pontos[grupo_atual][idx_interno] = aux;
            
            vet_idx_interno[grupo_atual]++;

            continue;
        }

        matriz_pontos[grupo_atual][idx_interno] = aux;
            
        vet_idx_interno[grupo_atual]++;
    }
    
    // Area da Impressao
    FILE *saida = fopen(nome_saida, "w");
    int tamanho_cluster = -1;
    int j = 0;
    
    for (i = 0; i < qtd_clusters; i++)
    {
        //Selecao do cluster a ser impresso
        grupo_atual = vet_ordem_clusters[i];
        tamanho_cluster = ponto_retorna_nfilhos(pontos[grupo_atual]);
        
        //Impressao do cluster selecionado
        for (j = 0; j < tamanho_cluster-1; j++)
        {
            fprintf(saida,"%s,", ponto_retorna_id(matriz_pontos[grupo_atual][j]));
        }
        fprintf(saida,"%s\n", ponto_retorna_id(matriz_pontos[grupo_atual][j]));
    }

    fclose(saida);

    //Liberacao dos vetores para print
    for ( i = 0; i < qtd_pontos; i++)
    {
        if (vet_idx_interno[i] != 0)
        {
            free(matriz_pontos[i]);
        }
    }
    free(matriz_pontos);
    free(vet_ordem_clusters);
    free(vet_idx_interno);
}
