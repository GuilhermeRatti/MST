#if !defined(_PONTO_H_)
#define _PONTO_H_

typedef struct Ponto *pPonto;

/*
    Cria um ponto com o identificador e coordenadas passados
*/
pPonto ponto_cria(char *id, double *coordenadas);

// Retorna o grupo de um ponto
int ponto_retorna_grupo(pPonto ponto);

// Altera o grupo de um ponto
void ponto_registra_grupo(pPonto ponto, int grupo);

// Retorna o numero de filhos de um ponto
int ponto_retorna_nfilhos(pPonto ponto);

// Incrementa o numero de filhos de um ponto baseado nos filhos de outro ponto
void ponto_incrementa_nfilhos(pPonto receptor, pPonto doador);

// Retorna o nome de um ponto
char *ponto_retorna_id(pPonto ponto);

// Funcao para definir valores como quantidade de pontos a serem lidos e quantidade de dimensoes de um ponto
void ponto_setup_de_ordenacao(pPonto *vetor_pontos, int tamanho);

// Funcao para calcular a distancia euclidiana ao quadrado entre os pontos p1 e p2
double ponto_calcula_distancia(pPonto p1, pPonto p2, int dimensoes);

void ponto_print(pPonto *v, pPonto p, int i);

void ponto_destroi(pPonto p);

#endif // _PONTO_H_