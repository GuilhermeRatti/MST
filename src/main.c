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
    //INICIO TEMPO TOTAL
    
    printf("Funcao:\t\t\t\tTempo:\n--------------------------------------------\n");

    clock_t total = clock ();
    
    // Verificacao de entrada valida
    if (argc < 4)
    {
        exit(printf("Quantidade insuficiente de parametros de entrada!\n"));
    }

    // Verifica a existencia do arquivo, a quantidade de pontos e as dimensoes dos pontos
    int *qtd_e_dim = arquivo_setup(argv[1]);
    int quantidade_pontos = qtd_e_dim[0], dimensoes = qtd_e_dim[1];
    free(qtd_e_dim); // Liberando o espaço alocado pelo vetor de resultados do arquivo_setup

    pPonto *vetor_pontos = (pPonto*)malloc(quantidade_pontos*sizeof(pPonto));

    //INICIO LEITURA DOS DADOS
    
    clock_t inicio = clock ();
    
    //Le todos os pontos e armazena eles no vetor
    arquivo_leitura_e_registro(argv[1],vetor_pontos,dimensoes,quantidade_pontos); 

    clock_t fim = clock ();
    double seconds = (( double ) fim - inicio ) / CLOCKS_PER_SEC ;
    printf ("Leitura dos Dados:\t\t%lf\n" , seconds );
    
    //FIM LEITURA DOS DADOS

    //INICIO CALCULO DAS DISTANCIAS
    
    inicio = clock ();

    // A ideia eh pre-ordenar os pontos por ordem alfabetica e depois atribuir os grupos iniciais
    // A ordenacao precisa vir primeiro pq caso contrario quebraria a funcao de union
    ponto_setup_de_ordenacao(vetor_pontos, quantidade_pontos);  
    
    int quantidade_arestas = (pow(quantidade_pontos,2) - quantidade_pontos)/2;
    int quantidade_clusters = atoi(argv[2]);
    int limite_unioes = quantidade_pontos - quantidade_clusters;

    // Aloca, calcula e preenche vetor de distancia de pontos
    Aresta *vetor_arestas = aresta_cria_vetor(quantidade_arestas);
    arestas_preenche_vetor(vetor_arestas,vetor_pontos,quantidade_pontos,quantidade_arestas,dimensoes,limite_unioes);

    fim = clock ();
    seconds = (( double ) fim - inicio ) / CLOCKS_PER_SEC ;
    printf ("Calculo das Distancias:\t\t%lf\n" , seconds );
    
    //FIM CALCULO DAS DISTANCIAS

    //INICIO ORDENACAO DAS DISTANCIAS

    inicio = clock ();

    // Ordenador das distancias (no caso garante a propriedade de heap em que vetor[0] eh o menor valor possivel)
    build_heap(quantidade_arestas,vetor_arestas);

    fim = clock ();
    seconds = (( double ) fim - inicio ) / CLOCKS_PER_SEC ;
    printf ("Ordenacao das Distancias:\t%lf\n" , seconds );
    
    //FIM ORDENACAO DAS DISTANCIAS

    //INICIO DEFINICAO CLUSTERS

    inicio = clock ();
    
    // Construcao dos clusters
    define_clusters(vetor_arestas, vetor_pontos, limite_unioes, quantidade_arestas);

    fim = clock ();
    seconds = (( double ) fim - inicio ) / CLOCKS_PER_SEC ;
    printf ("Definicao dos clusters:\t\t%lf\n" , seconds );

    //FIM DEFINICAO CLUSTERS
    
    // Destroi o vetor de arestas (nao sera mais usado então libera o maior gasto de memoria do programa)
    aresta_destroi_vetor(vetor_arestas);

    //INICIO PARTE FINAL

    // Impressao dos clusters
    imprime_clusters(argv[3], vetor_pontos, quantidade_pontos, quantidade_clusters);

    //FIM PARTE FINAL

    // Desalocacao de memoria dos pontos
    for(int i=0; i<quantidade_pontos; i++)
        ponto_destroi(vetor_pontos[i]);
    free(vetor_pontos);

    clock_t termino = clock ();
    seconds = (( double ) termino - total ) / CLOCKS_PER_SEC ;
    printf ("Tempo Total:\t\t\t%lf\n" , seconds );
    //FIM TEMPO TOTAL
    return 0;
}

void define_clusters(Aresta *arestas, pPonto *pontos, int limite_unioes, int quantidade_arestas)
{
    int unioes_feitas = 0;
    int vertices[2] = {-1,-1};

    while (unioes_feitas < limite_unioes)
    {
        aresta_retorna_vertices_menor_distancia(arestas,quantidade_arestas,vertices);      
    
        // Tenta unir os vertices evitando unioes circulares (retorno 0)
        if (UF_union(pontos, vertices[0], vertices[1])) unioes_feitas++;

        quantidade_arestas--;
    }
}
