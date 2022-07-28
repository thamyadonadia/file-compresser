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

void insereLista(Lista* lista, Arvore* arv){
    Celula* nova = (Celula*) malloc(sizeof(Celula));
    nova->arv = arv;
    nova->prox = NULL;

    // caso seja o primeiro elemento a ser adicionado 
    if(lista->prim == NULL && lista->prim == NULL){
        lista->prim = nova; 
        nova->ant = NULL;

    }else{
        lista->ult->prox = nova;
        nova->ant = lista->ult;
    }

    lista->ult = nova;
}

void retiraLista(Lista* lista, Arvore* arv){
    Celula* p;

    for(p = lista->prim; p != NULL; p = p->prox){
        if(p->arv == arv){
            // caso seja o único elemento da lista 
            if(lista->prim == p && lista->ult == p){
                lista->prim == NULL;
                lista->ult == NULL;
                free(p);
                return;
                
            // caso seja o primeiro elemento da lista 
            }else if(lista->prim == p){
                lista->prim = p->prox;
                p->prox->ant = NULL;
                free(p);
                return;

            // caso seja o último elemento da lista
            }else if(p->prox == NULL){
                lista->ult = p->ant;
                p->ant->prox = NULL;
                free(p);
                return;
            
            // caso seja um elemento do meio da lista 
            }else{
                p->ant->prox = p->prox;
                p->prox->ant = p->ant;
                free(p);
                return;
            }

        }
    }
}

void ordenaLista(Lista* lista){
    long int pesoMax = getPeso(lista->prim->arv);
    Celula* p;

    for(p = lista->prim; p != NULL; p = p->prox);

}

void liberaLista(Lista* lista){
    Celula* p; Celula* temp;

    while(p!=NULL){
        temp = p->prox;
        free(p);
        p = temp;
    }

    free(lista);
}
