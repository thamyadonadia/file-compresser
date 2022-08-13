#ifndef LISTA_H
#define LISTA_H

#include "arvore.h"

typedef struct lista Lista;

typedef struct celula Celula;

/* Inciailiza uma lista de Árvores
 *inputs: não ha
 *output: Lista alocada
 *pre-condicao: não ha
 *pos-condicao: Lista alocada e passada*/
Lista* inicializaLista();

/* Insere uma árvore em uma celula e essa celula no final da lista
 *inputs: Lista e arvore a ser inserida
 *output: nao ha
 *pre-condicao: não ha
 *pos-condicao: Arvore inserida no final da lista*/
void insereLista(Lista* lista, Arvore* arv);

/* Retira uma Árvore da lista, sem liberar o conteudo
 *inputs: Lista e arvore a ser retirada
 *output: nao ha
 *pre-condicao: nao ha
 *pos-condicao: Arvore retirada da lista*/
void retiraLista(Lista* lista, Arvore* arv);

/* Consegue a celula da lista correspondente ao indice
 *inputs: Lista e o indice da celula
 *output: Celula correspondente ao indice
 *pre-condicao: nao ha
 *pos-condicao: Celula passada corretamente*/
Celula* getCelIndice(Lista* lista, int idx);

/* Retorna a árvore dentro da celula
 *inputs: Celula
 *output: Arvore dentro da celula
 *pre-condicao: nao ha
 *pos-condicao: Arvore retornada com sucesso*/
Arvore* getArvCel(Celula* cel);

/* Ordena a lista de árvores pela ordem decrescente de pesos das arvores 
 * dentro das celulas
 *inputs: Lista a ser ordenada
 *output: nao ha
 *pre-condicao: nao ha
 *pos-condicao: Lista ordenada*/
void ordenaLista(Lista* lista);

/* Repetidamente ordena e junta as duas primeiras arvores da lista, assim
 * como o algoritmo de Huffman
 *inputs: Lista a ser juntada
 *output: nao ha
 *pre-condicao: Lista não nula e lista com mais de uma arvore
 *pos-condicao: Lista com uma arvore e ordenada corretamente*/
void juntaArvoresLista(Lista* lista);

/* Libera o espaço ocupado pela lista de arvores, sem liberar seu conteudo
 *inputs: Lista a ser liberada
 *output: nao ha
 *pre-condicao: nao ha
 *pos-condicao: Lista devidamente liberada*/
void liberaLista(Lista* lista);

#endif // LISTA_H