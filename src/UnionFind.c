#include "Ponto.h"
#include <stdio.h>

int UF_find( pPonto *vet, int i) {
    // COMPLEXIDADE tempo: ~(4*lg[N]) acessos ao vetor no pior caso, mas por causa do halving, 
    //                      a complexidade de acessos quase sempre vai ser 4 (constante).
    // COMPLEXIDADE espaco ~(lg[N]) stacks de recursao, mas quase sempre ~(1), msm justificativa acima.
    while (i != ponto_retorna_grupo(vet[i])){
        // 4 ACESSOS AO VETOR POR REPETICAO
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
    // COMPLEXIDADE tempo (dos 2 union somados): ~(8*lg[N]) ... mas quase sempre ~(8)
    // COMPLEXIDADE espaco (dos 2): ~(lg[N]) ...  mas quase sempre ~(1). Apesar do find aparecerem 2 vezes eles sao executados
    //                                            em tempos diferentes. Portanto a complexidade de espaco nao eh somada.
    int i = UF_find(vet, p); // Modifique raiz de p para a raiz de q.
    int l = UF_find(vet, q); // Profundidade de p+q acessos.
    // Operacao circular evitada (bem raro acontecer)
    if (i == l) return 0;

    // Verficacao para fins de balanceamento da arvore
    // 2 acessos ao vetor no minimo, 5 no maximo
    if (ponto_retorna_nfilhos(vet[i]) < ponto_retorna_nfilhos(vet[l])) 
    {
        ponto_registra_grupo(vet[i], l);            // Processo de registro de grupo
        ponto_incrementa_nfilhos(vet[l], vet[i]);   // Incremento no tamanho da raiz 
        return -1;
    }
    
    // 3 acessos ao vetor
    ponto_registra_grupo(vet[l], i);                // Processo de registro de grupo 
    ponto_incrementa_nfilhos(vet[i], vet[l]);       // Incremento no tamanho da raiz
    return 1;
}
