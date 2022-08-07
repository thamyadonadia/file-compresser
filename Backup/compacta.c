#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "compactador.h"

int main(int argc, char const *argv[]){
    char* nomeArquivo; 

    if(argc<=1){
        printf("ERRO: NAO FOI INFORMADO NOME DO ARQUIVO A SER COMPACTADO\n");
        return 1;
    }

    nomeArquivo = strdup(argv[1]);
    printf("%s\n", nomeArquivo);
    compacta(nomeArquivo);
    free(nomeArquivo);

    return 0;
}