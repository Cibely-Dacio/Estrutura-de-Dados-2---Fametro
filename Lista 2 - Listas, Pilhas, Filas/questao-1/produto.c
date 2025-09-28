#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"

static Produto* novo_produto(Produto p) {
    Produto *n = malloc(sizeof(Produto));
    if (!n) return NULL;
    *n = p;
    n->prox = NULL;
    return n;
}

Produto* inserir_inicio(Produto *L, Produto p) {
    Produto *n = novo_produto(p);
    if (!n) return L;
    n->prox = L;
    return n;
}

int cmp_codigo(const char *a, const char *b) {
    return strcmp(a,b);
}

Produto* inserir_ordenado_por_codigo(Produto *L, Produto p) {
    // if codigo exists, update qtd and preco
    Produto *cur = L;
    while (cur) {
        if (strcmp(cur->codigo, p.codigo)==0) {
            cur->qtd = p.qtd;
            cur->preco = p.preco;
            return L;
        }
        cur = cur->prox;
    }
    // insert in order
    Produto *n = novo_produto(p);
    if (!n) return L;
    if (!L || cmp_codigo(n->codigo, L->codigo) < 0) {
        n->prox = L;
        return n;
    }
    Produto *prev = NULL;
    cur = L;
    while (cur && cmp_codigo(cur->codigo, n->codigo) < 0) {
        prev = cur;
        cur = cur->prox;
    }
    prev->prox = n;
    n->prox = cur;
    return L;
}

Produto* remover_por_codigo(Produto *L, const char *codigo) {
    Produto *cur = L, *prev = NULL;
    while (cur) {
        if (strcmp(cur->codigo, codigo)==0) {
            if (prev) prev->prox = cur->prox;
            else L = cur->prox;
            free(cur);
            return L;
        }
        prev = cur;
        cur = cur->prox;
    }
    return L;
}

Produto* ajustar_quantidade(Produto *L, const char *codigo, int delta_qtd) {
    Produto *p = buscar(L, codigo);
    if (!p) return L;
    int nova = p->qtd + delta_qtd;
    if (nova < 0) {
        // do not allow negative
        return L;
    }
    p->qtd = nova;
    return L;
}

Produto* buscar(Produto *L, const char *codigo) {
    while (L) {
        if (strcmp(L->codigo, codigo)==0) return L;
        L = L->prox;
    }
    return NULL;
}

void listar(Produto *L) {
    printf("Código\tNome\tQtd\tPreço\n");
    while (L) {
        printf("%s\t%s\t%d\t%.2f\n", L->codigo, L->nome, L->qtd, L->preco);
        L = L->prox;
    }
}

Produto* limpar(Produto *L) {
    Produto *cur = L;
    while (cur) {
        Produto *t = cur->prox;
        free(cur);
        cur = t;
    }
    return NULL;
}