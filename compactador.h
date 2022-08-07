#ifndef COMPACTADOR_H
#define COMPACTADOR_H

#include "bitmap.h"
#include "lista.h"

// ------------- codificação de Huffman ----------------
int* getCaracteresArquivo(char* nomeArquivo);

Arvore* criaArvoreOtima(int* caracteres);
// ----------------------------------------------------

bitmap* criaArvore_bm(Arvore* arv);

bitmap** criaTabelaCodificacao(Arvore* arv);

void compacta(char* nomeArquivo);

void liberaTabelaCodificacao(bitmap** tabela);

#endif // COMPACTADOR_H