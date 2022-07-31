#ifndef COMPACTADOR_H
#define COMPACTADOR_H

#include "bitmap.h"
#include "encoder.h"

bitmap* criaBitMap(Arvore* arv);



void compacta(bitmap* bits, FILE* arquivo);

#endif // COMPACTADOR_H