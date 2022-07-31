#include<stdio.h>
#include<stdlib.h>
#include"encoder.h"

int main(int argc, char const *argv[])
{

    int* chars;
    Arvore* arv;
    
    if(argc<=1){
        printf("ERRO, NAO ENCONTRADO DIRETORIO!\n");
        exit(0);
    }
    char fileName[100];
    sscanf(argv[1], "%s", fileName);
    printf("%s\n",fileName);
    chars=getCharsFile(fileName);
    arv=createOptimalTree(chars);

    arv_imprime(arv);

    unsigned char letra;
    unsigned char* codigo;

    printf("\n\n Digite uma letra para ser buscada:\n");
    scanf("%c",&letra);

    codigo = buscaArvore(arv,letra);
    
    liberaArvore(arv);

    return 0;
}
