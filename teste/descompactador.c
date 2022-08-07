#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "descompactador.h"

static int* charParaBinario_descompactador(unsigned char carac){
    int c = carac; int* bin = (int*) malloc(sizeof(int)*8); 
    
    for(int i=7; i>=0; i--){
        bin[i] = c%2;
        c /= 2; 
    }

    return bin;
}

static unsigned char binarioParaChar_descompactador(int* bin){
    unsigned char carac = 0; int mult=1,bit,j;
    
    for(int i=0;i<8;i++){
        bit=bin[i];
        for(j=0, mult=1; j<i; j++){
            mult *=2;
        }
        carac += bit* mult;
    }
    printf("%c\n",carac);
    return carac;
}

static Arvore* reconstroiNoArvoreOtima(bitmap* bm,int* indice){
    unsigned char bit = bitmapGetBit(bm,*(indice));
    *(indice) = *(indice) + 1;
    Arvore* arv;
    printf("%c\n",bit);
    if(bit == 0){
        printf("Passou em 0 aqui com indice %d\n",*(indice));
        arv=uneArvores(reconstroiNoArvoreOtima(bm,indice),reconstroiNoArvoreOtima(bm,indice));
        return arv;
    }
    if(bit == 1){
        printf("Passou em 1 aqui com indice %d\n",*(indice));
        int* bin = malloc(sizeof(int)*8);
        for(int j=7;j>=0;j--){
            bin[j] = bitmapGetBit(bm,*(indice));
            *(indice) = *(indice) + 1;
        }
        arv=insereArvore(binarioParaChar_descompactador(bin));
        free(bin);
        return arv;

    }
    return NULL;
}

Arvore* reconstroiArvoreOtima(FILE* arquivoComp){
    bitmap* arvoreOtima_bm; Arvore* arvoreOtima;
    unsigned char caractere;  unsigned int bitNum; 

    fread(&bitNum,sizeof(unsigned int),1,arquivoComp);
    unsigned int byteNum=(bitNum+7)/8;
    arvoreOtima_bm=bitmapInit(byteNum*8);

    for(int i=0;i<byteNum;i++){
        fread(&caractere, sizeof(unsigned char), 1, arquivoComp);
        int* bin =  charParaBinario_descompactador(caractere);
        
        for(int j=0;j<8;j++){
            
            if(bin[j]==1){
                bitmapAppendLeastSignificantBit(arvoreOtima_bm,1);

            }else if(bin[j]==0){
                bitmapAppendLeastSignificantBit(arvoreOtima_bm,0);
            }
        }

        free(bin);
    }

    // reconstroi a árvore ótima 
    int* indice = malloc(sizeof(int)); *(indice) = 0;
    arvoreOtima = reconstroiNoArvoreOtima(arvoreOtima_bm,indice);
    arv_imprime(arvoreOtima);
    free(indice);
    return arvoreOtima;
}

bitmap* coletaTexto_bm(FILE* arquivoComp, bitmap* texto){
    unsigned char caractere; 

    for(int i=0;i<bitmapGetMaxSize(texto);){
        fread(&caractere, sizeof(unsigned char), 1, arquivoComp);
        int* bin =  charParaBinario_descompactador(caractere);
        printf("%d\n",i);
        for(int j=0;j<8 ;j++,i++){
            printf("%d",j);
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

void reconstroiTexto(FILE* arquivo, bitmap* texto, Arvore* arvoreOtima, int* indice, unsigned int numBits){
    if(arvoreOtima==NULL || *(indice)<numBits){
        return;

    }else if(getTipo(arvoreOtima) == 1){
        unsigned char caractere = getCaractere(arvoreOtima);
        fwrite(&caractere, sizeof(unsigned char), 1, arquivo);
        return;

    }else if(getTipo(arvoreOtima) == 0){
        unsigned char bit = bitmapGetBit(texto, *(indice));
        *(indice) += 1; 

        if(bit == '0'){
            reconstroiTexto(arquivo, texto, getSAE(arvoreOtima), indice, numBits);
            return;

        }else if(bit == '1'){
            reconstroiTexto(arquivo, texto, getSAD(arvoreOtima), indice, numBits);
            return;
        }
    }
}


void descompacta (char* nomeArquivoComp){
    FILE* arquivoComp = fopen(nomeArquivoComp, "rb");

    // leitura da quantidade de caracteres do texto original
    unsigned int numBits;
    fread(&numBits, sizeof(unsigned int), 1, arquivoComp);
    printf("num bits: %d\n", numBits);
    
    // reconstrução da árvore ótima a partir do binário do arquivo compactado 
    Arvore* arvoreOtima = reconstroiArvoreOtima(arquivoComp);

    // constroi o bitmap do texto 
    int numMax = ((numBits)/8)*8;
    printf("NumMax é igual a: %d\n",numMax);
    bitmap* texto = bitmapInit(numMax); 
    texto = coletaTexto_bm(arquivoComp, texto);

    int* indice = (int*) malloc(sizeof(int)); *(indice) = 0;
    // TROCAR ISSO POR FAVOR SOS GAMBIARRA
    FILE* arquivo = fopen("teste.txt", "w");
    
    for(int i =0; *(indice)<numBits; i++){
        reconstroiTexto(arquivo, texto, arvoreOtima, indice, numBits);
    }

    bitmapLibera(texto);
    liberaArvore(arvoreOtima);
    fclose(arquivoComp);
    fclose(arquivo);
}
