#include <stdio.h>
#include <stdlib.h>

#include "encoder.h"

int* getCharsFile(char* fileName){
    FILE* file;
    file = fopen(fileName,"r");

    int* vetor = malloc(128*sizeof(int));
    for(int i=0;i<128;i++){
        vetor[i]=0;
    }

    unsigned char letra;

    while(!feof(file)){
        fscanf(file, "%c",&letra);
        vetor[letra]++;
    }
    fclose(file);
    
    return vetor; 
}

Arvore* createOptimalTree(int* chars){
    Lista* lista;
    lista=inicializaLista();
    Arvore* arvtemp;
    unsigned char l;

    for(int i=0;i<128;i++){
        if(chars[i]==0){
            continue;
        }
        printf("%c -- %d\n",i,chars[i]);
        l = i;
        arvtemp=insereArvore(l);
        setPeso(arvtemp,chars[i]);
        insereLista(lista,arvtemp);
    }


    free(chars);

    ordenaLista(lista);
    printf("\n\n\n\n");
    imprimeLista(lista);

    juntaArvoresLista(lista);
    arvtemp=getArvCel(getCelIndice(lista,0));
    liberaLista(lista);
    return arvtemp;
}