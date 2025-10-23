#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int topo;
    int dados[MAX];
} Pilha;

typedef struct {
    int inicio, fim, total;
    int dados[MAX];
} Fila;

void criaPilha(Pilha *p) { p->topo = -1; }
int pilhaVazia(Pilha *p) { return p->topo == -1; }
int pilhaCheia(Pilha *p) { return p->topo == MAX - 1; }
void push(Pilha *p, int v) {
    if (!pilhaCheia(p)) { p->topo++; p->dados[p->topo] = v; }
}
int pop(Pilha *p) {
    if (pilhaVazia(p)) return -1;
    return p->dados[p->topo--];
}

void criaFila(Fila *f) { f->inicio = 0; f->fim = 0; f->total = 0; }
int filaVazia(Fila *f) { return f->total == 0; }
int filaCheia(Fila *f) { return f->total == MAX; }
void enqueue(Fila *f, int v) {
    if (!filaCheia(f)) {
        f->dados[f->fim] = v;
        f->fim = (f->fim + 1) % MAX;
        f->total++;
    }
}
int dequeue(Fila *f) {
    if (filaVazia(f)) return -1;
    int v = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    return v;
}

void mostrarPilha(Pilha *p) {
    printf("Pilha Digitada (Topo -> Base):\n");
    if (pilhaVazia(p)) {
        printf("(Pilha Vazia)\n");
        return;
    }
    for (int i = p->topo; i >= 0; i--) {
        printf("%d\n", p->dados[i]);
    }
}

void mostrarFila(Fila *f, char* nomeFila) {
    printf("Fila Gerada (%s):\n", nomeFila);
    if (filaVazia(f)) {
        printf("Mensagem: Fila vazia.\n"); 
        return;
    }
    
    int idx = f->inicio;
    for (int i = 0; i < f->total; i++) {
        printf("%d ", f->dados[idx]);
        idx = (idx + 1) % MAX;
    }
    printf("\n");
}


int main() {
    Pilha p;
    Fila fPares, fImpares;
    Pilha pAux; 
    
    criaPilha(&p);
    criaPilha(&pAux);
    criaFila(&fPares);
    criaFila(&fImpares);
    
    int valor;
    printf("--- Cadastro na Pilha ---\n");
    printf("Digite numeros (digite < 0 para finalizar):\n");  

    do {
        scanf("%d", &valor);
        if (valor >= 0) {
            if (pilhaCheia(&p)) {
                printf("Pilha cheia, parando a leitura.\n");
                break;
            }
            push(&p, valor); 
        }
    } while (valor >= 0);

    while (!pilhaVazia(&p)) {
        push(&pAux, pop(&p));
    }
    while (!pilhaVazia(&pAux)) {
        int v = pop(&pAux);
        if (v % 2 == 0) {
            enqueue(&fPares, v); 
        } else {
            enqueue(&fImpares, v); 
        }
        push(&p, v);
    }

    printf("\n\n--- RESULTADOS ---\n");
    mostrarPilha(&p); 
    printf("\n");
    mostrarFila(&fPares, "Pares");
    printf("\n");
    mostrarFila(&fImpares, "Impares"); 
    
    return 0;
}
