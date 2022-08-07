#ifndef DESCOMPACTADOR_H
#define DESCOMPACTADOR_H    

#include "arvore.h"
#include "bitmap.h"

Arvore* reconstroiArvoreOtima(FILE* arquivoComp);

bitmap* coletaTexto_bm(FILE* arquivoComp, bitmap* texto);

void reconstroiTexto(FILE* arquivo, bitmap* texto, Arvore* arvoreOtima, int* indice, unsigned int numBits);

void descompacta(char* nomeArquivoComp);

#endif 