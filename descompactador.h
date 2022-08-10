#ifndef DESCOMPACTADOR_H
#define DESCOMPACTADOR_H    

#include "arvore.h"
#include "bitmap.h"

/* Recebe o ponteiro para o arquivo e reconstroi a arvore
 * apartir do codigo no cabeçalho do arquivo
 *inputs: ponteiro para arquivo
 *output: Arvore otima reconstruida
 *pre-condicao: nao ha
 *pos-condicao: Arvore alocada e reconstruida*/
Arvore* reconstroiArvoreOtima(FILE* arquivoComp);

/* Coleta todo o texto compactado e passa para um bitmap
 *inputs: Ponteiro para arquivo e o bitmap a ser preenchido
 *output: bitmap completo com o texto compactado
 *pre-condicao: nao ha
 *pos-condicao: bitmap completo*/
bitmap* coletaTexto_bm(FILE* arquivoComp, bitmap* texto);

/* Reconstroi o texto no arquivo descompactado
 *inputs: Ponteiro para o arquivo, o bitmap com o texto, 
 *indice para percorrer o bitmap, e o numero de bits ocupado pelo texto
 *output: nao ha
 *pre-condicao: arvore otima nao nula e numero de bits nao ultrapassado
 *pos-condicao: texto reescrito*/
void reconstroiTexto(FILE* arquivo, bitmap* texto, Arvore* arvoreOtima, int* indice, unsigned int numBits);

/* Macro Função que junta todas as etapas da descompactação do arquivo
 *inputs: Nome do arquivo
 *output: Nao ha
 *pre-condicao: Nao ha
 *pos-condicao: Arquivo descompactado criado*/
void descompacta(char* nomeArquivoComp);

#endif 