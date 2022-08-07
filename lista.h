#ifndef LISTA_H
#define LISTA_H

#include "arvore.h"

typedef struct lista Lista;

typedef struct celula Celula;

Lista* inicializaLista();

void insereLista(Lista* lista, Arvore* arv);

void retiraLista(Lista* lista, Arvore* arv);

Celula* getCelIndice(Lista* lista, int idx);

Arvore* getArvCel(Celula* cel);

void ordenaLista(Lista* lista); // VAMOS REFAZER ESSA FUNÇÃO? 

void juntaArvoresLista(Lista* lista);

void liberaLista(Lista* lista);

//funções de teste
//void imprimeLista(Lista* lista);

#endif // LISTA_H