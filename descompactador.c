#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "descompactador.h"

static int* charParaBinario_descompactador(unsigned char carac){ //OK
    int c = carac; int* bin = (int*) malloc(sizeof(int)*8); 
    
    for(int i=7; i>=0; i--){
        bin[i] = c%2;
        c /= 2; 
    }

    
    return bin;
}

static unsigned char binarioParaChar_descompactador(int* bin){ //OK
    unsigned char carac = 0; int mult=1,bit,j;
    
    for(int i=0;i<8;i++){
        bit=bin[i];
        
        for(j=0, mult=1; j<i; j++){
            mult *=2;
        }
        
        carac += bit* mult;
    }


    return carac;
}

static Arvore* reconstroiNoArvoreOtima(bitmap* bm, int* indice){ //OK
    unsigned char bit = bitmapGetBit(bm,*(indice));
    *(indice) = *(indice) + 1;  Arvore* arv;
    
    if(bit == 0){
        arv = uneArvores(reconstroiNoArvoreOtima(bm,indice),reconstroiNoArvoreOtima(bm,indice));
        return arv;

    }else if(bit == 1){
        int* bin = malloc(sizeof(int)*8);
        
        for(int j=7; j>=0; j--){
            bin[j] = bitmapGetBit(bm,*(indice));
            *(indice) = *(indice) + 1;
        }
        
        arv = insereArvore(binarioParaChar_descompactador(bin));
        free(bin);
        return arv;
    }

    return NULL;
}

Arvore* reconstroiArvoreOtima(FILE* arquivoComp){
    bitmap* arvoreOtima_bm; Arvore* arvoreOtima;
    unsigned char caractere; unsigned int bitNum; 

    fread(&bitNum, sizeof(unsigned int), 1, arquivoComp);
    unsigned int byteNum = (bitNum+7)/8;
    arvoreOtima_bm = bitmapInit(byteNum*8);

    for(int i=0; i<byteNum; i++){
        fread(&caractere, sizeof(unsigned char), 1, arquivoComp);
        int* bin = charParaBinario_descompactador(caractere);
        
        for(int j=0; j<8; j++){
            if(bin[j]==1){
                bitmapAppendLeastSignificantBit(arvoreOtima_bm,1);

            }else if(bin[j]==0){
                bitmapAppendLeastSignificantBit(arvoreOtima_bm,0);
            }
        }

        free(bin);
    }

    // reconstroi a árvore ótima 
    int* indice = (int*) malloc(sizeof(int)); *(indice) = 0;
    arvoreOtima = reconstroiNoArvoreOtima(arvoreOtima_bm, indice);
    bitmapLibera(arvoreOtima_bm);
    free(indice);
    return arvoreOtima;
}

bitmap* coletaTexto_bm(FILE* arquivoComp, bitmap* texto){
    unsigned char caractere; unsigned int numMax = bitmapGetMaxSize(texto)/8;

    for(int i=0; i<numMax; i++){
        fread(&caractere, sizeof(unsigned char), 1, arquivoComp);
        int* bin = charParaBinario_descompactador(caractere);

        for(int j=0; j<8; j++){
            if(bin[j]==1){
                bitmapAppendLeastSignificantBit(texto,1);

            }else if(bin[j]==0){
                bitmapAppendLeastSignificantBit(texto,0);
            }
        }
        
        free(bin);
    }

    return texto; 
}

void reconstroiTexto(FILE* arquivo, bitmap* texto, Arvore* arvoreOtima, int* indice, unsigned int numBits){ //nao passou
    if(arvoreOtima==NULL || *(indice)>numBits){
        return;

    }else if(getTipo(arvoreOtima) == 1){
        unsigned char caractere = getCaractere(arvoreOtima);
        fwrite(&caractere, sizeof(unsigned char), 1, arquivo);
        return;

    }else if(getTipo(arvoreOtima) == 0){
        unsigned char bit = bitmapGetBit(texto, *(indice));
        *(indice) = *(indice) + 1; 

        if(bit == 0){
            reconstroiTexto(arquivo, texto, getSAE(arvoreOtima), indice, numBits);
            return;

        }else if(bit == 1){
            reconstroiTexto(arquivo, texto, getSAD(arvoreOtima), indice, numBits);
            return;
        }
    }
}


void descompacta (char* nomeArquivoComp){
    FILE* arquivoComp = fopen(nomeArquivoComp, "rb");

    //leitura da quantidade de chars que compoem o sufixo
    unsigned int sufix_size;

    fread(&sufix_size, sizeof(unsigned int),1,arquivoComp);

    char* sufix = malloc(sizeof(char)*(sufix_size+1));

    for(int i=0;i<sufix_size;i++){
        fread(&sufix[i],sizeof(char),1,arquivoComp);
    }

    // leitura da quantidade de caracteres do texto original
    unsigned long int numBits;
    fread(&numBits, sizeof(unsigned long int), 1, arquivoComp);
    
    // reconstrução da árvore ótima a partir do binário do arquivo compactado 
    Arvore* arvoreOtima = reconstroiArvoreOtima(arquivoComp);

    // constroi o bitmap do texto 
    unsigned int numMax = ((numBits+7)/8)*8;
    bitmap* texto = bitmapInit(numMax); 
    texto = coletaTexto_bm(arquivoComp, texto);

    int* indice = (int*) malloc(sizeof(int)); *(indice) = 0;
    
    // escrita do arquivo descompactado 
    char* temp = strdup(nomeArquivoComp); strtok(temp, ".");
    char* nomeArquivo = (char*) malloc(sizeof(char)*(strlen(temp)+3+strlen(sufix)));
    strcpy(nomeArquivo, temp); strcat(nomeArquivo, "."); strcat(nomeArquivo, sufix);strcat(nomeArquivo, "\0");
    
    FILE* arquivo = fopen(nomeArquivo, "wb");
    
    for(int i =0; *(indice)<numBits; i++){
        reconstroiTexto(arquivo, texto, arvoreOtima, indice, numBits);
    }

    free(indice); free(nomeArquivo); free(temp);
    bitmapLibera(texto);
    liberaArvore(arvoreOtima);
    fclose(arquivoComp);
    fclose(arquivo);
}
