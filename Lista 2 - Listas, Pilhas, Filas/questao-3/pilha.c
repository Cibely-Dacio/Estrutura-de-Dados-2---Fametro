#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

void pilha_init(Pilha *p) {
    p->topo = NULL;
}

bool push(Pilha *p, const char *func, int sp) {
    Frame *f = malloc(sizeof(Frame));
    if (!f) return false;
    strncpy(f->func, func, sizeof(f->func));
    f->func[sizeof(f->func)-1] = '\\0';
    f->sp = sp;
    f->baixo = p->topo;
    p->topo = f;
    return true;
}

bool pop(Pilha *p, Frame *out) {
    if (!p->topo) return false;
    Frame *t = p->topo;
    if (out) *out = *t;
    p->topo = t->baixo;
    free(t);
    return true;
}

bool peek(Pilha *p, Frame *out) {
    if (!p->topo) return false;
    if (out) *out = *p->topo;
    return true;
}

bool vazia(Pilha *p) {
    return p->topo == NULL;
}

void limpar(Pilha *p) {
    Frame tmp;
    while (pop(p, &tmp));
}