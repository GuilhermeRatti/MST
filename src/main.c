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
    
    // Verificacao de entrada valida
    if (argc < 4)
    {
        exit(printf("Quantidade insuficiente de parametros de entrada!\n"));
    }

    //INICIO LEITURA DOS DADOS

    // Verifica a existencia do arquivo, a quantidade de pontos e as dimensoes dos pontos
    int *qtd_e_dim = arquivo_setup(argv[1]);
    int quantidade_pontos = qtd_e_dim[0], dimensoes = qtd_e_dim[1];
    free(qtd_e_dim); // Liberando o espaço alocado pelo vetor de resultados do arquivo_setup

    pPonto *vetor_pontos = (pPonto*)malloc(quantidade_pontos*sizeof(pPonto));
    
    //Le todos os pontos e armazena eles no vetor
    arquivo_leitura_e_registro(argv[1],vetor_pontos,dimensoes,quantidade_pontos); 
    
    //FIM LEITURA DOS DADOS

    //INICIO CALCULO DAS DISTANCIAS

    // OBSERVACAO COMPLEXIDADE: TODAS AS COMPLEXIDADES APRESENTADAS NA MAIN VAO SER EM FUNCAO DA QTD DE PONTOS P.
    //                          A COMPLEXIDADE DENTRO DE CADA FUNCAO VAI SER ANALISADA 
    //                          INDIVIDUALMENTE EM FUNCAO DE N (elementos recebidos por aquela funcao)

    // A ideia eh pre-ordenar os pontos por ordem alfabetica e depois atribuir os grupos iniciais
    // A ordenacao precisa vir primeiro pq caso contrario quebraria a funcao de union
    // COMPLEXIDADE ~(6P*lg[P]) acessos ao vetor. 
    // COMPLEXIDADE ~(P) de espaco alocado.
    ponto_setup_de_ordenacao(vetor_pontos, quantidade_pontos);  
    
    int quantidade_arestas = (pow(quantidade_pontos,2) - quantidade_pontos)/2;
    int quantidade_clusters = atoi(argv[2]);
    int limite_unioes = quantidade_pontos - quantidade_clusters;

    // Aloca, calcula e preenche vetor de distancia de pontos
    Aresta *vetor_arestas = aresta_cria_vetor(quantidade_arestas);

    // traduz-se o numero de arestas como (P^2-P)/2
    // COMPLEXIDADE tempo: ~(DIM*P^2) acessos ao vetor. DIM eh uma constante representando numero de dimensoes.
    // COMPLEXIDADE espaco: ~((P/2)^2)
    arestas_preenche_vetor(vetor_arestas,vetor_pontos,quantidade_pontos,quantidade_arestas,dimensoes,limite_unioes);
   
    //FIM CALCULO DAS DISTANCIAS

    //INICIO ORDENACAO DAS DISTANCIAS

    // Ordenador das distancias (no caso garante a propriedade de heap em que vetor[0] eh o menor valor possivel)
    // COMPLEXIDADE tempo: ~(4*[(P^2-P)/2]) acessos ao vetor
    // COMPLEXIDADE espaco: ~(lg[(P^2-P)/2])
    build_heap(quantidade_arestas,vetor_arestas);

    //FIM ORDENACAO DAS DISTANCIAS

    //INICIO DEFINICAO CLUSTERS

    // Construcao dos clusters
    // Ignorando o fato de que a quantidade de arestas decresce a cada iteracao (a complexidade seria menor e mais dificil de calcular)
    // COMPLEXIDADE tempo: ~(4*[P]*lg[(P^2-P)/2])
    // COMPLEXIDADE espaco: ~(lg[(P^2-P)/2])
    define_clusters(vetor_arestas, vetor_pontos, limite_unioes, quantidade_arestas);

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

    //FIM TEMPO TOTAL
    return 0;
}

void define_clusters(Aresta *arestas, pPonto *pontos, int limite_unioes, int quantidade_arestas)
{
    int unioes_feitas = 0;
    int vertices[2] = {-1,-1};

    // Desconsiderando ligacoes circulares.
    // Havera (P-G) repeticoes, sendo P numero de pontos e G numero de grupos. Assume-se G como uma constante. Entao repeticoes: P
    // COMPLEXIDADE tempo: ~(4*P*lg[(P^2-P)/2]) acessos, sendo P o numero de pontos. traduz-se o numero de arestas como (P^2-P)/2
    // COMPLEXIDADE espaco: ~(lg[(P^2-P)/2])
    while (unioes_feitas < limite_unioes)
    {
        // COMPLEXIDADE tempo: ~(4*lg[N]) acesos ao vetor
        // COMPLEXIDADE espaco: ~(lg[N])
        aresta_retorna_vertices_menor_distancia(arestas,quantidade_arestas,vertices);      
    
        // Tenta unir os vertices evitando unioes circulares (retorno 0)
        // COMPLEXIDADE tempo: ~(8*lg[N]) acessos ao vetor ... mas quase sempre ~(16) acessos
        // COMPLEXIDADE espaco: ~(lg[N]) stacks de recursao ... mas quase sempre ~(1)
        if (UF_union(pontos, vertices[0], vertices[1])) unioes_feitas++;

        quantidade_arestas--;
    }
}
