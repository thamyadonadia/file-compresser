#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int* decimalLongoParaBinario(unsigned char carac){
    int c = carac;
    int* bin = (int*) malloc(sizeof(int)*16); 

    for(int i = 0; i<15; i++){
        bin[i] = c%2;
        c /= 2;
    }

    return bin;
}

static void preencheArvore_bm(Arvore* arv, bitmap* bm){
    if(arv==NULL){
        return;

    //se é um nó folha
    }else if(getTipo(arv) == 1){
        int* bin = decimalParaBinario(getCaractere(arv));
        bitmapAppendLeastSignificantBit(bm, 1);

        for(int i =0; i<7; i++){
            bitmapAppendLeastSignificantBit(bm, bin[i]);
        }
    
    //se é um nó normal
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
    return arvore_bm;
}

bitmap** criaTabelaCodificacao(Arvore* arv){
    bitmap** tabela = malloc(sizeof(bitmap*)*128);
    

    for(int i = 0; i<128; i++){
        unsigned char* caminho = buscaArvore(arv,i);
        
        if(caminho!=NULL){
            tabela[i]=bitmapInit(strlen((char*)caminho));
            
            for(int j = 0; j<strlen((char*)caminho); j++){
                bitmapAppendLeastSignificantBit(tabela[i],caminho[j]);
            }

        }else{
            tabela[i] = NULL;
            continue;
        }
        
        free(caminho);
    }

    return tabela; 
}

static unsigned int getTamanhoBitmapCompactar (int* pesos, bitmap** tabela){
    unsigned int tamanho=0;

    for(int i=0;i<128;i++){
        
        if(pesos[i]==0||tabela[i]==NULL){
            continue;
        }

        tamanho += ((bitmapGetLength(tabela[i]))*pesos[i]);
    }

    return tamanho;
}

void compacta(char* nomeArquivo){
    int* pesos = getCharsFile(nomeArquivo);
    Arvore* arvoreOtima = createOptimalTree(pesos);
    long int numCaracteres = getPeso(arvoreOtima);
    bitmap** tabelaCodificacao = criaTabelaCodificacao(arvoreOtima);
    bitmap* arvoreOtima_bm = criaArvore_bm(arvoreOtima); 

    char* nomeArquivoComp = (char*) malloc(sizeof(char)*(strlen(nomeArquivo)+2));
    nomeArquivoComp = strcpy(nomeArquivoComp, strtok(nomeArquivo, "."));
    strcat(nomeArquivoComp, ".comp");
    strcat(nomeArquivo, ".txt"); // GAMBIARRA, TROCAR PARA FUNCIONAR COM QUALQUER EXTENSÃO


    
    FILE* arquivoComp = fopen(nomeArquivoComp, "wb");

    //-------------- NUMERO DE CARACTERES ----------------
    //ESCREVER ISSO EM BIT 
    char* num = malloc(sizeof(char)*10);
    sprintf(num, "%ld", numCaracteres);
    fwrite(num, sizeof(char), strlen(num), arquivoComp);


    //fprintf(arquivoComp, num);
    
    //----------------- ARVORE OTIMA --------------------- 

    unsigned char caractere, endereco;
    long int max_sizeInBytes=((bitmapGetMaxSize(arvoreOtima_bm))+7)/8; 
    for(unsigned int i=0; i<max_sizeInBytes; i++){
        //fprintf(arquivoComp, bitmapGetBit(arvoreOtima_bm, i));
        caractere = bitmapGetContents(arvoreOtima_bm)[i];
        printf("%c", caractere);
        fwrite(&caractere, sizeof(unsigned char), 1, arquivoComp);
    }

    //--------------- TEXTO COMPACTADO -------------------
    bitmap* textoCompactadoBm = bitmapInit(getTamanhoBitmapCompactar(pesos,tabelaCodificacao));

    FILE* arquivo = fopen(nomeArquivo, "r");
    printf("\n\n");

    while(!feof(arquivo)){
        fscanf(arquivo, "%c",&endereco);
        for(unsigned int j=0; j<bitmapGetLength(tabelaCodificacao[endereco]);j++){
            caractere = bitmapGetBit(tabelaCodificacao[endereco],j);
            printf("%c", caractere);
            bitmapAppendLeastSignificantBit(textoCompactadoBm,caractere);
           //fprintf(arquivoComp,bitmapGetBit(tabelaCodificacao[caractere],j));
        }
    }

    max_sizeInBytes = (bitmapGetMaxSize(textoCompactadoBm)+7)/8;
    for(unsigned int i=0; i<max_sizeInBytes; i++){
        //fprintf(arquivoComp, bitmapGetBit(textoCompactadoBm, i));
        //printf("rodada %d\n",i);
        caractere = bitmapGetContents(textoCompactadoBm)[i];
        fwrite(&caractere, sizeof(unsigned char), 1, arquivoComp);
    }

    liberaArvore(arvoreOtima);
    bitmapLibera(arvoreOtima_bm);

    fclose(arquivoComp);
    
    free(nomeArquivoComp);
    fclose(arquivo);
    free(num);
   
}

void liberaTabelaCodificacao(bitmap** tabela){
    for(int i=0;i<128;i++){
        bitmapLibera(tabela[i]);
    }
    free(tabela);
}
