#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

void inicializar(Fila *f) {
    f->ini = f->fim = NULL;
}

static Cliente* novo_cliente(Cliente c) {
    Cliente *n = malloc(sizeof(Cliente));
    if (!n) return NULL;
    *n = c;
    n->prox = NULL;
    return n;
}

void enfileirar(Fila *f, Cliente c) {
    Cliente *n = novo_cliente(c);
    if (!n) return;
    if (!f->fim) {
        f->ini = f->fim = n;
    } else {
        f->fim->prox = n;
        f->fim = n;
    }
}

bool desenfileirar(Fila *f, Cliente *out) {
    if (!f->ini) return false;
    Cliente *t = f->ini;
    if (out) *out = *t;
    f->ini = t->prox;
    if (!f->ini) f->fim = NULL;
    free(t);
    return true;
}

bool vazia(Fila *f) {
    return f->ini == NULL;
}

void limpar(Fila *f) {
    Cliente tmp;
    while (desenfileirar(f, &tmp));
    f->ini = f->fim = NULL;
}