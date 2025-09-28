#ifndef PILHA_H
#define PILHA_H

#include <stdbool.h>

typedef struct Frame {
    char func[48];
    int sp;
    struct Frame *baixo;
} Frame;

typedef struct {
    Frame *topo;
} Pilha;

void pilha_init(Pilha*);
bool push(Pilha*, const char *func, int sp);
bool pop(Pilha*, Frame *out);
bool peek(Pilha*, Frame *out);
bool vazia(Pilha*);
void limpar(Pilha*);
#endif