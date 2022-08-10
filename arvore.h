#ifndef ARVORE_H
#define ARVORE_H

typedef struct arvore Arvore;

/* Inicializa a Arvore vazia com ID de nó galho
 *inputs: nao ha
 *output: Arvore devidamente alocada
 *pre-condicao: nao ha
 *pos-condicao: Arvore alocada e identificada*/
Arvore* inicializaArvore();

/* Recebe um byte e cria uma Arvore apontando para ela
 *inputs: um byte (unsigned char)
 *output: Arvore alocada e classificada como no folha
 *pre-condicao: nao ha
 *pos-condicao: Arvore alocada e classficada*/
Arvore* insereArvore(unsigned char carac);

/* Recebe duas Arvores, cria uma Arvore que liga as duas, somando seus
 * pesos e tomando como seu
 *inputs: Duas arvores
 *output: Arvore alocada, unindo as duas entregues, e com peso atualizado
 *pre-condicao: nao ha
 *pos-condicao: Arvore alocada, unindo as duas entregues, e com peso atualizado*/
Arvore* uneArvores(Arvore* dir, Arvore* esq);

/* Verifica se a arvore é Nula
 *inputs: Arvore a ser testada
 *output: int booleano indicando se é ou não nulo
 *pre-condicao: nao ha
 *pos-condicao: booleano indicando corretamente*/
int arvoreVazia(Arvore* arv);

/* Retorna o byte que é apontado pela arvore
 *inputs: Arvore
 *output: byte que a arvore aponta
 *pre-condicao: nao ha
 *pos-condicao: byte retornado*/
unsigned char getCaractere(Arvore* arv);

/* Recebe o int que indica que tipo de nó que esta arvore é 
 *inputs: Arvore
 *output: o tipo que categoriza o nó
 *pre-condicao: nao ha
 *pos-condicao: int retornado*/
int getTipo(Arvore* arv);

/* Recebe a arvore que esta à esquerda da arvore passada
 * SAE (SubArvore da Esquerda)
 *inputs: Arvore
 *output: Arvore da esquerda
 *pre-condicao: nao ha
 *pos-condicao: Arvore retornado*/
Arvore* getSAE(Arvore* arv);

/* Recebe a arvore que esta à direita da arvore passada
 * SAD (SubArvore da Direita)
 *inputs: Arvore
 *output: Arvore da Direita
 *pre-condicao: nao ha
 *pos-condicao: Arvore retornado*/
Arvore* getSAD(Arvore* arv);

/* Recebe uma arvore e retorna o peso (frequencia) dela
 *inputs: Arvore
 *output: Peso de tal Arvore
 *pre-condicao: nao ha
 *pos-condicao: Peso da Arvore retornado*/
long int getPeso(Arvore* arv);

/* Atribui o valor de peso à Arvore
 *inputs: Arvore a ter valor atribuido e o valor a atribuir
 *output: nao ha
 *pre-condicao: Arvore não nula
 *pos-condicao: Peso da arvore atualizado*/
void setPeso(Arvore* arv, long int peso);

/* Função recursiva que mede o tamanho necessario para gurdar a 
 * arvore em bits para o cabeçalho
 *inputs: Topo da arvore otima
 *output: numero do tamanho necessario em bits
 *pre-condicao: nao ha
 *pos-condicao: numero corretamente calculado*/
unsigned int getTamanhoArvore(Arvore* arv);

/* Função recursiva que calcula a distancia entre o caractere e o
 * topo da arvore
 *inputs: arvore e caractere a ser encontrado
 *output: a altura do no especifico ate o topo
 *pre-condicao: nao ha
 *pos-condicao: altura do caractere ate o topo*/
long int getAlturaCaractere(Arvore* arv, unsigned char carac);

/* Função recursiva que retorna uma string contendo o caminho (direita - 1 e esquerda - 0)
 * que leva do topo ate o no que contem o caractere passado
 *inputs: Arvore e caractere
 *output: string alocada com o caminho
 *pre-condicao: Arvore deve ser não nula
 *pos-condicao: String com o caminho certo*/
unsigned char* buscaArvore(Arvore* arv,unsigned char carac);

/* Função recursiva que libera a Arvore
 *inputs: Arvore a ser liberada
 *output: nao ha
 *pre-condicao: nao ha
 *pos-condicao: Arvore liberada*/
void liberaArvore(Arvore* arv);

#endif // ARVORE_H


