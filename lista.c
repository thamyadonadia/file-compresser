#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct celula Celula;

struct celula{
    Celula* ant;
    Celula* prox;
    Arvore* arv;
};

struct lista{
    Celula* prim;
    Celula* ult;
};

Lista* inicializaLista(){
    Lista* lista = (Lista*) malloc(sizeof(Lista));
    lista->prim = NULL;
    lista->ult = NULL;
    return lista;
}

void insereLista(Arvore* arv);

void retiraLista(Lista* lista);

void ordenaLista(Lista* lista);

void liberaLista(Lista* lista);
