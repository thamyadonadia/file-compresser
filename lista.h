#ifndef LISTA_H
#define LISTA_H

#include "arvore.h"

typedef struct lista Lista;

Lista* inicializaLista();

void insereLista(Lista* lista, Arvore* arv);

void retiraLista(Lista* lista, Arvore* arv);

void ordenaLista(Lista* lista);

void liberaLista(Lista* lista);

#endif // LISTA_H