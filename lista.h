#ifndef LISTA_H
#define LISTA_H

#include "arvore.h"

typedef struct lista Lista;

Lista* inicializaLista();

void insereLista(Arvore* arv);

void retiraLista(Lista* lista);

void ordenaLista(Lista* lista);

void liberaLista(Lista* lista);

#endif // LISTA_H