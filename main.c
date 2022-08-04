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
    buscaArvore(arv, letra);
    

    // long int altura = getAlturaCaractere(arv, '6');
    // printf("Altura da letra 6: %ld\n", altura);

    // altura = getAlturaCaractere(arv, 'o');
    // printf("Altura da letra o: %ld\n", altura);

    // altura = getAlturaCaractere(arv, 'm');
    // printf("Altura da letra m: %ld\n", altura);

    // altura = getAlturaCaractere(arv, 'e');
    // printf("Altura da letra e: %ld\n", altura);

    // altura = getAlturaCaractere(arv, 's');
    // printf("Altura da letra s: %ld\n", altura);

    // altura = getAlturaCaractere(arv, ' ');
    // printf("Altura do espaço: %ld\n", altura);

    liberaArvore(arv);

    return 0;
}
