#include<stdio.h>
#include<stdlib.h>
#include <string.h>

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
    arv->letra=-1;

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
    setPeso(arv,getPeso(dir)+getPeso(esq));
    return arv;
}

unsigned char getCaractere(Arvore* arv){
    return arv->letra;
}

int getTipo(Arvore* arv){
    return arv->id;
}


Arvore* getSAE(Arvore* arv){
    return arv->esq;
}

Arvore* getSAD(Arvore* arv){
    return arv->dir;
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

int arvoreVazia(Arvore* arv){
    if(arv==NULL){
        return 1;
    }

    return 0;
}

static long int maximo(long int a, long int b){
    if(a>=b){
        return a;
    }

    return b;
}

long int getAlturaCaractere(Arvore* arv, unsigned char carac){
    if(arvoreVazia(arv)){
        return -2147483648;

    }else if(arv->letra == carac){
        return 0;

    }else{int getTipo(Arvore* arv);

        long int altura = (maximo(getAlturaCaractere(arv->esq, carac), getAlturaCaractere(arv->dir, carac)));
        return altura + 1;
        
    }   
}


static long int buscaNoArvore(Arvore* arv, unsigned char carac, unsigned char* codigo, long int alturaCaractere){
    long int d = -1, e = -1;
    
    if(arv == NULL){
        return -1;

    }else if(arv->id == 1){
        if(arv->letra == carac){
            return alturaCaractere;
        
        }else{
            return -1;
        }
    
    }

    if(arv->dir!=NULL){
        d = buscaNoArvore(arv->dir, carac, codigo, alturaCaractere);
    }

    if(arv->esq!=NULL){
        e = buscaNoArvore(arv->esq, carac, codigo, alturaCaractere);
    }

    if(d == -1 && e == -1){
        return -1;
    
    }else if(d == -1){
        codigo[e] = '0';
        return e-1;      
    
    }else if(e == -1){
        codigo[d] = '1';
        return d-1;
    }

    return -1;
}


unsigned char* buscaArvore(Arvore* arv, unsigned char carac){
    long int alturaCaractere = getAlturaCaractere(arv, carac);

    // caractere inexistente na árvore ou árvore nula 
    if(alturaCaractere<0){
        return NULL;
    }

    unsigned char* codigo = (unsigned char*) malloc(sizeof(unsigned char)*(alturaCaractere+1));
    codigo[alturaCaractere] = '\0';
    buscaNoArvore(arv, carac, codigo, alturaCaractere-1);
    
    return codigo;
}


unsigned int getTamanhoArvore(Arvore* arv){
    unsigned int tamanho = 0;

    if(arv==NULL){
        return 0;

    }else if(arv->id == 1){
        return 9;
    
    }else if(arv->id == 0){
        tamanho += getTamanhoArvore(arv->dir) + getTamanhoArvore(arv->esq);
        return tamanho + 1;
    }

    return 0;
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

static void imprimeArvore (Arvore* arv, int space){


    if (arv == NULL){
        return;
    }


    space += 10;

    imprimeArvore (arv->dir, space);

    printf("\n");
    for (int i = 10; i < space; i++){
        printf(" ");
    }

    if(getCaractere(arv)<128&&getCaractere(arv)>=0){
        printf("%c\n", getCaractere(arv));
    }else{
        printf("O");
    }
    imprimeArvore (arv->esq, space);

}

void arv_imprime(Arvore* arv){
    imprimeArvore(arv, 0);
    return;
}