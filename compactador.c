#include <stdio.h>
#include <stdlib.h>

#include "compactador.h"
#include "bitmap.h"


// funções que seram utilizadas para a compactação do arquivo 
static int* decimalParaBinario(unsigned char carac){
    int c = carac;
    int* bin = (int*) malloc(sizeof(int)*8); 

    for(int i = 0; i<7; i++){
        bin[i] = c%2;
        c /= 2;
    }

    return bin;
}

static void preencheArvore_bm(Arvore* arv, bitmap* bm){
    if(arv==NULL){
        return;

    }else if(getTipo(arv) == 1){
        int* bin = decimalParaBinario(getCaractere(arv));
        bitmapAppendLeastSignificantBit(bm, 1);

        for(int i =0; i<7; i++){
            bitmapAppendLeastSignificantBit(bm, bin[i]);
        }
    
    }else if(getTipo(arv) == 0){
        bitmapAppendLeastSignificantBit(bm, 0);
        preencheArvore_bm(getSAE(arv), bm);
        preencheArvore_bm(getSAD(arv), bm);
    }
}

// função que cria a árvore no formato de bitmap
bitmap* criaArvore_bm(Arvore* arv){ 
    bitmap* arvore_bm = bitmapInit(getTamanhoArvore(arv));
    preencheArvore_bm(arv, arvore_bm);
}


