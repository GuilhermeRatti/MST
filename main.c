#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IO.h"
#include "Ponto.h"
#include "Aresta.h"
#include "UnionFind.h"
#include <time.h>

// Funcao de definicao dos grupos de clusters
// int define_clusters(pPonto *pontos, pAresta *arestas, int limite_arestas, int quantidade_arestas);
// Funcao de impressao dos grupos de clusters em ordem alfabetica
void imprime_clusters(const char *nome_saida, pPonto *pontos, int qtd_pontos, int qtd_clusters);

int main(int argc, char const *argv[])
{
    clock_t start = clock ();
    if (argc < 4)
    {
        exit(printf("Quantidade insuficiente de parametros de entrada!\n"));
    }

    // verifica a existencia do arquivo, a quantidade de pontos e as dimensoes dos pontos
    int *qtd_e_dim = arquivo_setup(argv[1]);
    int qtd_pontos = qtd_e_dim[0], dimensoes = qtd_e_dim[1];
    free(qtd_e_dim); // Liberando o espaço alocado pelo vetor de resultados do arquivo_setup

    pPonto *vetor_pontos = (pPonto*)malloc(qtd_pontos*sizeof(pPonto));

    arquivo_leitura_e_registro(argv[1],vetor_pontos,dimensoes,qtd_pontos); //Le todos os pontos e armazena eles no vetor
    ponto_setup_de_ordenacao(vetor_pontos, qtd_pontos);   // A ideia eh pre-ordenar os pontos por ordem alfabetica e depois atribuir os grupos iniciais
                                                          // A ordenacao precisa vir primeiro pq caso contrario quebraria a funcao de union
    
    int qtd_clusters = atoi(argv[2]);
    int limite_unioes = qtd_pontos - qtd_clusters;
    // Aloca, calcula e preenche vetor de distancia de pontos
    arestas_preenche_vetor_e_calcula_clusters(vetor_pontos,qtd_pontos,dimensoes,limite_unioes);
    printf("Aloquei!\n");

    // Ordena vetor de arestas pela distancia ao quadrado
    printf("Ordenei!\n");

    // Construcao dos clusters
    
    // qtd_arestas = define_clusters(vetor_pontos, vetor_arestas, limite_unioes, qtd_arestas);

    printf("Clustei!\n");
    //saida_printa_vetor_pontos(vetor_pontos,qtd_pontos); // Usei so pra ver se tava printando certo, vamo reaproveitar pra printas os grupos dps

    // // Desalocacao de memoria das arestas
    // for(int i=0; i<qtd_arestas; i++)
    //     aresta_destroi(vetor_arestas[i]);
    // free(vetor_arestas);

    // Impressao dos clusters
    imprime_clusters(argv[3], vetor_pontos, qtd_pontos, qtd_clusters);

    // Desalocacao de memoria dos pontos
    for(int i=0; i<qtd_pontos; i++)
        ponto_destroi(vetor_pontos[i]);
    free(vetor_pontos);

    clock_t end = clock ();
    double seconds = (( double ) end - start ) / CLOCKS_PER_SEC ;
    printf ("%lf\n" , seconds );
    return 0;
}

// int define_clusters(pPonto *pontos, pAresta *arestas, int limite_unioes, int quantidade_arestas)
// {
//     int unioes_feitas = 0;
//     int vertices[2] = {-1,-1};

//     while (unioes_feitas < limite_unioes)
//     {
//         // Pega os vertices que compoem a aresta atual
//         // printf("QTD_A: %d | ",quantidade_arestas);
//         // printf("QTD_UF: %d\n",unioes_feitas);
//         // aresta_print(arestas[0]);
//         pAresta menor_aresta = aresta_retorna_menor_distancia(arestas,quantidade_arestas);

//         aresta_retorna_vertices(menor_aresta, vertices);
//         // Tenta unir os vertices evitando unioes circulares (retorno 0)
//         if (UF_union(pontos, vertices[0], vertices[1])) unioes_feitas++;

//         aresta_destroi(menor_aresta);
//         quantidade_arestas--;
//     }

//     return quantidade_arestas;
// }

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
