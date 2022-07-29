#include<stdio.h>
#include<stdlib.h>

#include"encoder.h"

int* getCharsFile(char* fileName){
    FILE* file;
    file = fopen(fileName,"r");

    int* vetor = malloc(128*sizeof(int));
    for(int i=0;i<128;i++){
        vetor[i]=0;
    }

    char letra;

    while(!feof(file)){
        fscanf(file, "%c",letra);
        vetor[letra]++;
    }
    fclose(file);

    return vetor; 
}

Arvore* createOptimalTree(int* chars){
    Lista* lista;
    lista=inicializaLista();
    Arvore* arvtemp;

    for(int i=0;i<128;i++){
        if(chars[i]==0){
            continue;
        }
        arvtemp=insereArvore(i);
        setPeso(arvtemp,chars[i]);
        insereLista(lista,arvtemp);

    }

    free(chars);

    ordenaLista(lista);
    juntaArvoresLista(lista);
    arvtemp=getArvCel(getCelIndice(lista,0));
    liberaLista(lista);
    return arvtemp;
}