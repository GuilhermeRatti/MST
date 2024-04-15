#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "IO.h"
#include "Ponto.h"
#include "Aresta.h"
#include "UnionFind.h"
#include <time.h>

// Funcao de definicao dos grupos de clusters
void define_clusters(Aresta *arestas, pPonto *pontos, int limite_unioes, int quantidade_arestas);

int main(int argc, char const *argv[])
{
    //clock_t start = clock ();
    
    if (argc < 4)
    {
        exit(printf("Quantidade insuficiente de parametros de entrada!\n"));
    }

    // verifica a existencia do arquivo, a quantidade de pontos e as dimensoes dos pontos
    int *qtd_e_dim = arquivo_setup(argv[1]);
    int quantidade_pontos = qtd_e_dim[0], dimensoes = qtd_e_dim[1];
    free(qtd_e_dim); // Liberando o espaço alocado pelo vetor de resultados do arquivo_setup

    pPonto *vetor_pontos = (pPonto*)malloc(quantidade_pontos*sizeof(pPonto));

    arquivo_leitura_e_registro(argv[1],vetor_pontos,dimensoes,quantidade_pontos); //Le todos os pontos e armazena eles no vetor
    ponto_setup_de_ordenacao(vetor_pontos, quantidade_pontos);  // A ideia eh pre-ordenar os pontos por ordem alfabetica e depois atribuir os grupos iniciais
                                                                // A ordenacao precisa vir primeiro pq caso contrario quebraria a funcao de union
    
    int quantidade_arestas = (pow(quantidade_pontos,2) - quantidade_pontos)/2;
    int quantidade_clusters = atoi(argv[2]);
    int limite_unioes = quantidade_pontos - quantidade_clusters;

    // Aloca, calcula e preenche vetor de distancia de pontos
    Aresta *vetor_arestas = aresta_cria_vetor(quantidade_arestas);
    arestas_preenche_vetor(vetor_arestas,vetor_pontos,quantidade_pontos,quantidade_arestas,dimensoes,limite_unioes);

    // Construcao dos clusters
    define_clusters(vetor_arestas, vetor_pontos, limite_unioes, quantidade_arestas);

    // Destroi o vetor de arestas (nao sera mais usado então libera o maior gasto de memoria do programa)
    aresta_destroi_vetor(vetor_arestas);

    // Impressao dos clusters
    imprime_clusters(argv[3], vetor_pontos, quantidade_pontos, quantidade_clusters);

    // Desalocacao de memoria dos pontos
    for(int i=0; i<quantidade_pontos; i++)
        ponto_destroi(vetor_pontos[i]);
    free(vetor_pontos);

    // clock_t end = clock ();
    // double seconds = (( double ) end - start ) / CLOCKS_PER_SEC ;
    // printf ("Tempo Total: %lf\n" , seconds );
    return 0;
}

void define_clusters(Aresta *arestas, pPonto *pontos, int limite_unioes, int quantidade_arestas)
{
    int unioes_feitas = 0;
    int vertices[2] = {-1,-1};

    while (unioes_feitas < limite_unioes)
    {
        // printf("qtd_unioes: %d | limite: %d\n",unioes_feitas,limite_unioes);
        aresta_retorna_vertices_menor_distancia(arestas,quantidade_arestas,vertices);      
        // printf("p1: %d | p2: %d\n",vertices[0],vertices[1]);
    
        // Tenta unir os vertices evitando unioes circulares (retorno 0)
        if (UF_union(pontos, vertices[0], vertices[1])) unioes_feitas++;

        quantidade_arestas--;
    }
}
