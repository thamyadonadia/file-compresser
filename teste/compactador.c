#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compactador.h"
#include "bitmap.h"


// funções que seram utilizadas para a compactação do arquivo 
int* decimalParaBinario(unsigned char carac){ // trocar nome: charParaBinário_compactador 
    int c = carac; int* bin = (int*) malloc(sizeof(int)*8); 

    for(int i=7; i>=0; i--){
        bin[i] = c%2;
        c /= 2;     
    }
    
    return bin;
}

/*static int* decimalLongoParaBinario(unsigned char carac){
    int c = carac;
    int* bin = (int*) malloc(sizeof(int)*16); 

    for(int i = 0; i<15; i++){
        bin[i] = c%2;
        c /= 2;
    }

    return bin;
}*/

static void preencheArvore_bm(Arvore* arv, bitmap* bm){
    if(arv==NULL){
        return;

    //se é um nó folha
    }else if(getTipo(arv) == 1){
        int* bin = decimalParaBinario(getCaractere(arv));
        bitmapAppendLeastSignificantBit(bm, 1);
        printf(" 1 ");

        printf("\n\n");
        for(int i =0; i<8; i++){
            bitmapAppendLeastSignificantBit(bm, bin[i]);
            printf("%d", bin[i]);
        }

        printf("\n\n");
        free(bin);
    //se é um nó normal
    }else if(getTipo(arv) == 0){
        bitmapAppendLeastSignificantBit(bm, 0);
        printf(" 0 ");
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
                printf("caminho[%d]: %c\n", j, caminho[j]);
                if(caminho[j] == '0'){

                    bitmapAppendLeastSignificantBit(tabela[i],0);
                }else if(caminho[j]=='1'){
                    bitmapAppendLeastSignificantBit(tabela[i],1);

                }
        
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

static void ImprimeTabelaCodificacao(bitmap** tabela){
    printf("IMPRIMINDO A TABELA DE CODIFICACAO:\n");
    for(int i=0; i<128; i++){
        if(tabela[i]==NULL){
            continue;
        }

        printf("caminho correspondente a %c:", i);
        for(int j=0; j<bitmapGetLength(tabela[i]); j++){
            char c = bitmapGetBit(tabela[i], j);
            printf("%d",c);
        }
        
        printf("\n");
    }
}

void compacta(char* nomeArquivo){
    //Coleta de pesos no arquivo
    int* pesos = getCharsFile(nomeArquivo);

    //Criacao de arvore otima, tabela de codificacao e contagem de chars
    Arvore* arvoreOtima = createOptimalTree(pesos);
    long int numCaracteres = getPeso(arvoreOtima);
    bitmap** tabelaCodificacao = criaTabelaCodificacao(arvoreOtima);
    bitmap* arvoreOtima_bm = criaArvore_bm(arvoreOtima);

    //Organizando o nome dos arquivos
    char* nomeArquivoComp = (char*) malloc(sizeof(char)*(strlen(nomeArquivo)+2));
    nomeArquivoComp = "teste.comp";

    //abrindo arquivo de teste
    FILE* arquivoComp = fopen("teste.comp", "wb"); // GAMBIARRA - SOS TROCAR 

    //-------------- NUMERO DE CARACTERES ----------------
    unsigned int numBits = getTamanhoBitmapCompactar(pesos,tabelaCodificacao);
    fwrite(&numBits, sizeof(unsigned int), 1, arquivoComp);
    
    //----------------- ARVORE OTIMA --------------------
    unsigned char caractere, endereco;
    unsigned int max_sizeInBits = (bitmapGetMaxSize(arvoreOtima_bm));
    unsigned int max_sizeInBytes=(max_sizeInBits+7)/8;
    printf("Max size in bits (comapactador) é : %d\n",max_sizeInBits);
    fwrite(&max_sizeInBits, sizeof(unsigned int), 1, arquivoComp);
    for(unsigned int i=0; i<max_sizeInBytes; i++){
        //fprintf(arquivoComp, bitmapGetBit(arvoreOtima_bm, i));
        caractere = bitmapGetContents(arvoreOtima_bm)[i];
        fwrite(&caractere, sizeof(unsigned char), 1, arquivoComp);
    }

    //--------------- TEXTO COMPACTADO -------------------
    bitmap* textoCompactadoBm = bitmapInit(numBits);
    FILE* arquivo = fopen(nomeArquivo, "r");
  
    while(!feof(arquivo)){
        fscanf(arquivo, "%c",&endereco);
        for(unsigned int j=0; j<bitmapGetLength(tabelaCodificacao[endereco]);j++){
            caractere = bitmapGetBit(tabelaCodificacao[endereco],j);
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
    fclose(arquivo);
}

void liberaTabelaCodificacao(bitmap** tabela){
    for(int i=0;i<128;i++){
        bitmapLibera(tabela[i]);
    }
    free(tabela);
}
