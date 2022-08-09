#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compactador.h"

// ------------- codificação de Huffman ----------------
int* getCaracteresArquivo(char* nomeArquivo){
    FILE* arquivo = fopen(nomeArquivo,"r");
    int* pesos = (int*) malloc(sizeof(int)*256);
    unsigned char caractere;

    // incialização do vetor 
    for(int i=0; i<256; i++){
        pesos[i]=0;
    }

    while(!feof(arquivo)){
        if(fread(&caractere, sizeof(unsigned char), 1, arquivo)){
            pesos[caractere]++;
        }
    }

    fclose(arquivo);
    return pesos; 
}

Arvore* criaArvoreOtima(int* caracteres){
    Lista* lista = inicializaLista();
    Arvore* arvOtima; unsigned char l;

    for(int i=0; i<256; i++){
        if(caracteres[i]==0){
            continue;
        }

        l = i;
        arvOtima = insereArvore(l);
        setPeso(arvOtima,caracteres[i]);
        insereLista(lista,arvOtima);
    }

    ordenaLista(lista);
    juntaArvoresLista(lista);
    arvOtima = getArvCel(getCelIndice(lista,0));
    liberaLista(lista);
    return arvOtima;
}
// ----------------------------------------------------

static int* charParaBinario_compactador(unsigned char carac){ 
    int c = carac; int* bin = (int*) malloc(sizeof(int)*8); 

    for(int i=7; i>=0; i--){
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
        int* bin = charParaBinario_compactador(getCaractere(arv));
        bitmapAppendLeastSignificantBit(bm, 1);

        for(int i =0; i<8; i++){
            bitmapAppendLeastSignificantBit(bm, bin[i]);
        }

        free(bin);

    //se é um nó normal
    }else if(getTipo(arv) == 0){
        bitmapAppendLeastSignificantBit(bm, 0);
        preencheArvore_bm(getSAE(arv), bm);
        preencheArvore_bm(getSAD(arv), bm);
    }
}

bitmap* criaArvore_bm(Arvore* arv){ 
    bitmap* arvore_bm = bitmapInit(getTamanhoArvore(arv));
    preencheArvore_bm(arv, arvore_bm);
    return arvore_bm;
}

bitmap** criaTabelaCodificacao(Arvore* arv){
    bitmap** tabela = malloc(sizeof(bitmap*)*256);
    
    for(int i = 0; i<256; i++){
        unsigned char* caminho = buscaArvore(arv,i);
        
        if(caminho!=NULL){
            tabela[i] = bitmapInit(strlen((char*)caminho));
            
            for(int j = 0; j<strlen((char*)caminho); j++){
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

static unsigned int getTamanhoBitmapCompactar(int* pesos, bitmap** tabela){
    unsigned int tamanho = 0;

    for(int i=0; i<256; i++){
        if(pesos[i]==0 || tabela[i]==NULL){
            continue;
        }

        tamanho += (bitmapGetLength(tabela[i])) * pesos[i];
    }

    return tamanho;
}

void compacta(char* nomeArquivo){
    // Coleta de pesos, árvore ótima, tabela de codificação e contagem de caracteres 
    int* pesos = getCaracteresArquivo(nomeArquivo);
    Arvore* arvoreOtima = criaArvoreOtima(pesos);
    bitmap** tabelaCodificacao = criaTabelaCodificacao(arvoreOtima);
    bitmap* arvoreOtima_bm = criaArvore_bm(arvoreOtima);

    // Organizando o nome dos arquivos
    char* temp = strdup(nomeArquivo); strtok(temp, ".");

    
    

    char* nomeArquivoComp = (char*) malloc(sizeof(char)*(strlen(temp)+6));
    strcpy(nomeArquivoComp, temp); strcat(nomeArquivoComp, ".comp\0");

    // Abrindo arquivo compactado 
    FILE* arquivoComp = fopen(nomeArquivoComp, "wb"); 


    //-------------- NÚMERO DE SUFIXO ----------------

    char* sufix = strtok(NULL ,"\0");

    int sufix_size = strlen(sufix);

    fwrite(&sufix_size, sizeof(int),1,arquivoComp);

    char caractere_sufix;

    for(int i=0 ; i<sufix_size;i++){
        caractere_sufix = sufix[i];
        fwrite(&caractere_sufix, sizeof(char), 1, arquivoComp);
    }

    //-------------- NÚMERO DE CARACTERES ----------------
    unsigned int numBits = getTamanhoBitmapCompactar(pesos,tabelaCodificacao);
    fwrite(&numBits, sizeof(unsigned int), 1, arquivoComp);
    
    //----------------- ÁRVORE ÓTIMA --------------------
    unsigned char caractere, endereco;
    unsigned int max_sizeInBits = (bitmapGetMaxSize(arvoreOtima_bm));
    unsigned int max_sizeInBytes=(max_sizeInBits+7)/8;
    
    fwrite(&max_sizeInBits, sizeof(unsigned int), 1, arquivoComp);

    for(unsigned int i=0; i<max_sizeInBytes; i++){
        caractere = bitmapGetContents(arvoreOtima_bm)[i];
        fwrite(&caractere, sizeof(unsigned char), 1, arquivoComp);
    }

    //--------------- TEXTO COMPACTADO -------------------
    bitmap* textoCompactado_bm = bitmapInit(numBits);
    FILE* arquivo = fopen(nomeArquivo, "r");

    while(!feof(arquivo)){
        //fscanf(arquivo, "%c",&endereco);
        if(fread(&endereco, sizeof(unsigned char), 1, arquivo)){
        
            for(unsigned int j=0; j<bitmapGetLength(tabelaCodificacao[endereco]);j++){
                caractere = bitmapGetBit(tabelaCodificacao[endereco],j);
                bitmapAppendLeastSignificantBit(textoCompactado_bm,caractere);
            }
        }
    }

    max_sizeInBytes = (bitmapGetMaxSize(textoCompactado_bm)+7)/8;
    
    for(unsigned int i=0; i<max_sizeInBytes; i++){
        caractere = bitmapGetContents(textoCompactado_bm)[i];
        fwrite(&caractere, sizeof(unsigned char), 1, arquivoComp);
    }

    free(pesos); free(temp); free(nomeArquivoComp);
    liberaArvore(arvoreOtima);
    bitmapLibera(arvoreOtima_bm);
    liberaTabelaCodificacao(tabelaCodificacao);
    bitmapLibera(textoCompactado_bm);
    fclose(arquivoComp);
    fclose(arquivo);
}

void liberaTabelaCodificacao(bitmap** tabela){
    for(int i=0;i<256;i++){
        if(tabela[i]==NULL){
            continue;
        }else{
            bitmapLibera(tabela[i]);
        }
        
    }

    free(tabela);
}
