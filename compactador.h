#ifndef COMPACTADOR_H
#define COMPACTADOR_H

#include "bitmap.h"
#include "lista.h"

// ------------- codificação de Huffman ----------------

/* Coleta os pesos de cada caracter presente no arquivo
 *inputs: String com o nome do arquivo
 *output: Vetor de pesos de cada caractere possivel
 *pre-condicao: Nao ha
 *pos-condicao: Vetor de pesos de caractere montado e preenchido*/
int* getCaracteresArquivo(char* nomeArquivo);

/* Cria a Arvore Otima apartir do vetor de pesos
 *inputs: Vetor de pesos (frequencia de caracteres)
 *output: Arvore otima montada
 *pre-condicao: nao ha
 *pos-condicao: Arvore alocada corretamente e optimizada*/
Arvore* criaArvoreOtima(int* caracteres);
// ----------------------------------------------------

/* Cria um bit com a arvore otima devidamente codificada
 *inputs: Arvore Otima
 *output: Bitmap alocado com a codificação da Arvore Otima
 *pre-condicao: arvore nao nula
 *pos-condicao: bitmap devidamente criado*/
bitmap* criaArvore_bm(Arvore* arv);

/* Cria um vetor de Bitmaps e preenche com o caminho de arvore para
 * cada um deles
 *inputs: Arvore Otima
 *output: Vetor de bitmap
 *pre-condicao: Nao ha
 *pos-condicao: Vetor de bitmap criado*/
bitmap** criaTabelaCodificacao(Arvore* arv);

/* Macro Função que junta todas as etapas da compactação do arquivo
 *inputs: Nome do arquivo
 *output: Nao ha
 *pre-condicao: Nao ha
 *pos-condicao: Arquivo compactado criado*/
void compacta(char* nomeArquivo);

/* Função que libera a tabela de codificação (vetor de bitmap)
 *inputs: Tabela de codificação
 *output: nao ha
 *pre-condicao: nao ha
 *pos-condicao: Tabela liberada*/
void liberaTabelaCodificacao(bitmap** tabela);

#endif // COMPACTADOR_H