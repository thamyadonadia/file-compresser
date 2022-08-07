#ifndef COMPACTADOR_H
#define COMPACTADOR_H

#include "bitmap.h"
#include "encoder.h" //so chamar arvore?

bitmap* criaArvore_bm(Arvore* arv);

bitmap** criaTabelaCodificacao(Arvore* arv);



void compacta(char* nomeArquivo);

void liberaTabelaCodificacao(bitmap** tabela);

#endif // COMPACTADOR_H