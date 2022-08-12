#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../descompactador.h"

int main(int argc, char const *argv[]){
    char* nomeArquivoComp; 

    if(argc<=1){
        printf("ERRO: NAO FOI INFORMADO NOME DO ARQUIVO A SER DESCOMPACTADO\n");
        return 1;
    }

    nomeArquivoComp = strdup(argv[1]);
    descompacta(nomeArquivoComp);
    free(nomeArquivoComp);

    return 0;
}
