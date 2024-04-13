#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "IO.h"
#include "Ponto.h"

int main(int argc, char const *argv[])
{
    char *caminho_arquivo="dados_teste/1.txt";

    // verifica a existencia do arquivo, a quantidade de pontos e as dimensoes dos pontos
    int *qtd_e_dim = arquivo_setup(caminho_arquivo);
    int qtd_pontos = qtd_e_dim[0], dimensoes = qtd_e_dim[1];
    free(qtd_e_dim); // Liberando o espaço alocado pelo vetor de resultados do arquivo_setup

    pPonto *vetor_pontos = (pPonto*)malloc(qtd_pontos*sizeof(pPonto));

    arquivo_leitura_e_registro(caminho_arquivo,vetor_pontos,dimensoes,qtd_pontos); //Le todos os pontos e armazena eles no vetor
    ponto_setup_de_ordenacao(vetor_pontos, qtd_pontos);   // A ideia eh pre-ordenar os pontos por ordem alfabetica e depois atribuir os grupos iniciais
                                                          // A ordenacao precisa vir primeiro pq caso contrario quebraria a funcao de union
    
    //saida_printa_vetor_pontos(vetor_pontos,qtd_pontos); // Usei so pra ver se tava printando certo, vamo reaproveitar pra printas os grupos dps

    // Aloca, calcula e preenche vetor de distancia de pontos
    int qtd_distancias = (pow(qtd_pontos,2)-qtd_pontos)/2;
    pDistancia *vetor_distancias = (pDistancia*)malloc(qtd_distancias*sizeof(pDistancia));
    distancia_preenche_vetor(vetor_distancias,vetor_pontos,qtd_pontos,dimensoes);

    // Ordena vetor de distancias pela distancia ao quadrado
    distancia_ordena(vetor_distancias,qtd_distancias);

    // Desalocacao de memoria das distancias
    for(int i=0; i<qtd_distancias; i++)
        distancia_destroi(vetor_distancias[i]);
    free(vetor_distancias);

    // Desalocacao de memoria dos pontos
    for(int i=0; i<qtd_pontos; i++)
        ponto_destroi(vetor_pontos[i]);
    free(vetor_pontos);

    return 0;
}