#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

struct lista{
    Celula* prim;
    Celula* ult;
};

struct celula{
    Celula* ant;
    Celula* prox;
    Arvore* arv;
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
                lista->prim = NULL;
                lista->ult = NULL;
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

static Celula* getMenorPeso(Celula* cel){
    Celula* p; Celula* menor= cel;
    long int menorpeso = getPeso(cel->arv);

    for(p=cel; p!=NULL; p=p->prox){
        if(getPeso(p->arv)<menorpeso){
            menorpeso = getPeso(p->arv);
            menor = p;
        }
    }
    return menor;
}

Celula* getCelIndice(Lista* lista, int idx){
    Celula* p; int i;
    
    for(i=0, p=lista->prim; i<idx && p!=NULL; i++, p=p->prox); 
    
    if(p==NULL){
        return NULL;
    }else{
        return p;
    }
}

Arvore* getArvCel(Celula* cel){
    return cel->arv;
}

void ordenaLista(Lista* lista){
    Celula* p; Celula* m;
    Celula* prox; Celula* ant;
    int i;

    for(i = 0, p=getCelIndice(lista,i);p!=NULL; i++,p=getCelIndice(lista,i)){
        m=getMenorPeso(p);
        if(m==p){
            continue;
        }else{
            //armazena ponteiros do menor
            prox = m->prox;
            if(p==m->ant){
                ant=m;
            }else{
                ant = m->ant;
            }
            if(m==lista->ult){
                lista->ult=p;
            }

            //passa ponteiros do maior para o menor
            if(m==p->prox){
                m->prox=p;
            }else{
                m->prox=p->prox;
            }
            
            m->ant=p->ant;

            if(p==lista->prim){
                lista->prim = m;
            }else{
                p->ant->prox=m;
            }
            if(p->prox!=m){
                p->prox->ant = m;
            }
            

            //passa os armazenados para o maior
            p->ant=ant;
            p->prox=prox;

            if(lista->ult!=p){
                prox->ant=p;
            }
            p->ant->prox=p;

        }

    }

}

static int getTamLista(Lista* lista){
    if(lista == NULL){
        return -1;
    }
    
    if(lista->prim==lista->ult){
        return 1;
    }

    Celula* p; int i = 1;

    for(p=lista->prim; p!=NULL; p=p->prox){
        i++;
    }
    return i;
}

void juntaArvoresLista(Lista* lista){
    if((lista == NULL) || (getTamLista(lista) == 1)){
        return;
    }
    
    Arvore* pri;Arvore* seg;Arvore* nova;
    
    while(getTamLista(lista)!=1){
        pri=getArvCel(getCelIndice(lista,0));
        seg=getArvCel(getCelIndice(lista,1));
        nova = uneArvores(seg,pri);

        insereLista(lista, nova);
        retiraLista(lista,pri);
        retiraLista(lista,seg);
        ordenaLista(lista);
    }
}

void liberaLista(Lista* lista){
    Celula* p = lista->prim; Celula* temp;
    
    while(p!=NULL){
        temp = p->prox;
        free(p);
        p = temp;
    }

    free(lista);
}
