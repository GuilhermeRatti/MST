#include "Ponto.h"
#include <stdio.h>

int UF_find( pPonto *vet, int i) {
    while (i != ponto_retorna_grupo(vet[i])){
        // O registro a seguir causa o efeito de halving da arvore
        ponto_registra_grupo(
            vet[i],
            //O parametro encadeado a seguir retorna o grupo do "pai" do ponto atual ("avo")
            ponto_retorna_grupo(vet[
                ponto_retorna_grupo(vet[i])
            ])
        );

        i = ponto_retorna_grupo(vet[i]); // Buscar o pai ate a raiz.
    } 
    return i; // Profundidade de i acessos.
}

int UF_union(pPonto *vet, int p, int q) {
    int i = UF_find(vet, p); // Modifique raiz de p para a raiz de q.
    int j = UF_find(vet, q); // Profundidade de p+q acessos.
    // Operacao circular evitada
    if (i == j) return 0;

    // Verficacao para fins de balanceamento da arvore
    if (ponto_retorna_nfilhos(vet[i]) < ponto_retorna_nfilhos(vet[j])) 
    {
        ponto_registra_grupo(vet[i], j);            // Processo de registro de grupo
        ponto_incrementa_nfilhos(vet[j], vet[i]);   // Incremento no tamanho da raiz 
        return -1;
    }
        
    ponto_registra_grupo(vet[j], i);                // Processo de registro de grupo 
    ponto_incrementa_nfilhos(vet[i], vet[j]);       // Incremento no tamanho da raiz
    return 1;
}
