#ifndef FILA_H
#define FILA_H

#include <stdbool.h>

typedef struct Cliente {
    char id[24];
    int qtd;
    struct Cliente *prox;
} Cliente;

typedef struct {
    Cliente *ini, *fim;
} Fila;

void inicializar(Fila*);
void enfileirar(Fila*, Cliente);
bool desenfileirar(Fila*, Cliente *out);
bool vazia(Fila*);
void limpar(Fila*);
#endif