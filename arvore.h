#ifndef ARVORE_H
#define ARVORE_H

typedef struct arvore Arvore;

Arvore* criaArvoreVazia();

Arvore* criaArvore(Arvore* arv, unsigned char carac);

Arvore* uneArvores(Arvore* dir, Arvore* esq);

Arvore* insereArvore(Arvore* arv, unsigned char carac);

unsigned char getCaractere(Arvore* arv);

long int getPeso(Arvore* arv);

void setPeso(Arvore* arv, long int peso);

void liberaArvore(Arvore* arv);

#endif // ARVORE_H


