#include<stdio.h>
#include<stdlib.h>

#include"arvore.h"

struct arvore{
    Arvore* esq;
    Arvore* dir;
    long int peso;
    unsigned char letra;
    int id;
};

Arvore* inicializaArvore(){
    Arvore* arv;
    arv = malloc(sizeof(Arvore));
    arv->dir=NULL;
    arv->esq=NULL;
    arv->peso=0;
    arv->id=0;

    return arv;
}

Arvore* insereArvore(unsigned char carac){
    Arvore* arv = inicializaArvore();
    arv->letra=carac;
    arv->id=1;
    return arv;
}

Arvore* uneArvores(Arvore* dir, Arvore* esq){
    Arvore* arv;
    arv = inicializaArvore();
    arv->dir=dir;
    arv->esq=esq;
    return arv;
}

unsigned char getCaractere(Arvore* arv){
    return arv->letra;
}

long int getPeso(Arvore* arv){
    return arv->peso;
}

void setPeso(Arvore* arv, long int peso){
    if(arv!=NULL){
        arv->peso=peso;
    }
    return;
}

void liberaArvore(Arvore* arv){
    if(arv==NULL){
        return;

    }else if(arv->dir==NULL&&arv->esq==NULL){
        free(arv);
        return;
    }

    if(arv->esq!=NULL){
        liberaArvore(arv->esq);
    }
    
    if(arv->dir!=NULL){
        liberaArvore(arv->dir);
    }
    free(arv);
    return;
}






static void imprimeArvore (Arvore* arv){
    
    if(arv != NULL){
        if(arv->esq!=NULL){
        printf("%c -- %c\n",arv->letra,arv->esq->letra);
        }
        if(arv->dir!=NULL){
        printf("%c -- %c\n",arv->letra,arv->dir->letra);
        }
        imprimeArvore(arv->esq);
        imprimeArvore(arv->dir);
    }

    
    return;
}

void arv_imprime(Arvore* arv){
    printf("\nstrict graph{\n");
    imprimeArvore(arv);
    printf("}\n");
    return;
}