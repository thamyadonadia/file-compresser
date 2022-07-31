#ifndef ARVORE_H
#define ARVORE_H

typedef struct arvore Arvore;

Arvore* inicializaArvore();

Arvore* insereArvore(unsigned char carac);

Arvore* uneArvores(Arvore* dir, Arvore* esq);

unsigned char getCaractere(Arvore* arv);

long int getPeso(Arvore* arv);

void setPeso(Arvore* arv, long int peso);

void liberaArvore(Arvore* arv);

//USADO PARA TESTES
void arv_imprime(Arvore* arv);

#endif // ARVORE_H


