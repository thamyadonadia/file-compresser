#ifndef ARVORE_H
#define ARVORE_H

typedef struct arvore Arvore;

Arvore* inicializaArvore();

Arvore* insereArvore(unsigned char carac);

Arvore* uneArvores(Arvore* dir, Arvore* esq);

unsigned char getCaractere(Arvore* arv);

int getTipo(Arvore* arv);

Arvore* getSAE(Arvore* arv);

Arvore* getSAD(Arvore* arv);

long int getPeso(Arvore* arv);

void setPeso(Arvore* arv, long int peso);

unsigned char* buscaArvore(Arvore* arv,unsigned char carac);

void liberaArvore(Arvore* arv);

unsigned int getTamanhoArvore(Arvore* arv);

long int getAlturaCaractere(Arvore* arv, unsigned char carac);

int arvoreVazia(Arvore* arv);

//USADO PARA TESTES
void arv_imprime(Arvore* arv);

#endif // ARVORE_H


