#include <stdio.h>
#include <stdlib.h>

#define MAX 100 
// Define o 'n' fixo aqui
#define N_FIBONACCI 20

// --- Estrutura da Pilha Estática ---
typedef struct {
    int topo;
    // Usamos long long para evitar overflow (Fibonacci cresce rapido)
    long long dados[MAX]; 
} Pilha;

// --- Funções Básicas da Pilha ---
void criaPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX - 1;
}

void push(Pilha *p, long long valor) {
    if (pilhaCheia(p)) {
        printf("Erro: Pilha cheia!\n");
    } else {
        p->topo++;
        p->dados[p->topo] = valor;
    }
}

long long pop(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Erro: Pilha vazia!\n");
        return -1;
    } else {
        long long valor = p->dados[p->topo];
        p->topo--;
        return valor;
    }
}

// Função para mostrar a pilha (sem destruir)
void mostrarPilha(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Pilha de Fibonacci esta vazia.\n");
        return;
    }
    printf("Pilha de Fibonacci (do topo para a base):\n");
    Pilha aux;
    criaPilha(&aux);
    while (!pilhaVazia(p)) {
        long long valor = pop(p);
        printf("%lld\n", valor);
        push(&aux, valor);
    }
    // Restaura p
    while (!pilhaVazia(&aux)) {
        push(p, pop(&aux));
    }
}


int main() {
    Pilha fibPilha;
    criaPilha(&fibPilha);
    
    // N é fixo (20) conforme solicitado, sem input
    int n = N_FIBONACCI; 
    
    if (n > MAX) {
        printf("Erro: N_FIBONACCI (%d) muito grande (maximo %d).\n", n, MAX);
        return 1;
    }

    long long a = 0;
    long long b = 1;

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            push(&fibPilha, a);
        } else if (i == 1) {
            push(&fibPilha, b);
        } else {
            long long prox = a + b;
            a = b;
            b = prox;
            push(&fibPilha, prox);
        }
    }

    printf("\n%d valores de Fibonacci acumulados na pilha.\n", n);
    mostrarPilha(&fibPilha);

    return 0;
}