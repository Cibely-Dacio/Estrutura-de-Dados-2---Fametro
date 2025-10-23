#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 50

typedef struct {
    int inicio, fim, total;
    int dados[MAX];
} Fila;

void criaFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaVazia(Fila *f) {
    return f->total == 0;
}

int filaCheia(Fila *f) {
    return f->total == MAX;
}

void enqueue(Fila *f, int valor) {
    if (filaCheia(f)) {
        printf("Fila cheia!\n");
    } else {
        f->dados[f->fim] = valor;
        f->fim = (f->fim + 1) % MAX;
        f->total++;
    }
}

int dequeue(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return -1; // Valor de erro
    } else {
        int valor = f->dados[f->inicio];
        f->inicio = (f->inicio + 1) % MAX;
        f->total--;
        return valor;
    }
}

int tamanhoFila(Fila *f) {
    return f->total;
}

void saoIguais(Fila *f1, Fila *f2) {
    if (tamanhoFila(f1) != tamanhoFila(f2)) {
        printf("As filas nao sao iguais.\n");
        if (tamanhoFila(f1) > tamanhoFila(f2)) { // 
            printf("A fila F1 e maior (possui %d elementos).\n", tamanhoFila(f1));
        } else {
            printf("A fila F2 e maior (possui %d elementos).\n", tamanhoFila(f2)); // 
        }
        return;
    }

    Fila aux1, aux2;
    criaFila(&aux1);
    criaFila(&aux2);
    int sao_iguais = 1;

    while (!filaVazia(f1)) {
        int v1 = dequeue(f1);
        int v2 = dequeue(f2);
        if (v1 != v2) {
            sao_iguais = 0;
        }
        enqueue(&aux1, v1);
        enqueue(&aux2, v2);
    }

    while (!filaVazia(&aux1)) {
        enqueue(f1, dequeue(&aux1));
        enqueue(f2, dequeue(&aux2));
    }

    if (sao_iguais) {
        printf("As filas F1 e F2 sao iguais.\n"); // 
    } else {
        printf("As filas F1 e F2 nao sao iguais.\n");
    }
}

// 
void estatisticasFila(Fila *f) {
    if (filaVazia(f)) {
        printf("A fila esta vazia.\n");
        return;
    }

    Fila aux;
    criaFila(&aux);

    int maior = INT_MIN;
    int menor = INT_MAX;
    double soma = 0;
    int contador = 0;

    while (!filaVazia(f)) {
        int valor = dequeue(f);
        if (valor > maior) maior = valor;
        if (valor < menor) menor = valor;
        soma += valor;
        contador++;
        enqueue(&aux, valor);
    }

    while (!filaVazia(&aux)) {
        enqueue(f, dequeue(&aux));
    }

    printf("------------------------\n");
    printf("Maior elemento: %d\n", maior); // 
    printf("Menor elemento: %d\n", menor); // 
    printf("Media aritmetica: %.2f\n", soma / contador); // 
}

// 
void transfereF1paraF2(Fila *f1, Fila *f2) {
    Fila aux;
    criaFila(&aux);
    criaFila(f2);

    while (!filaVazia(f1)) {
        int valor = dequeue(f1);
        enqueue(&aux, valor);
        enqueue(f2, valor);
    }

    while (!filaVazia(&aux)) {
        enqueue(f1, dequeue(&aux));
    }
    printf("F1 copiado para F2.\n");
}

// 
int contaImpares(Fila *f) {
    Fila aux;
    criaFila(&aux);
    int impares = 0;

    while (!filaVazia(f)) {
        int valor = dequeue(f);
        if (valor % 2 != 0) {
            impares++;
        }
        enqueue(&aux, valor);
    }
    // Restaura f
    while (!filaVazia(&aux)) {
        enqueue(f, dequeue(&aux));
    }
    return impares;
}

// 
int contaPares(Fila *f) {
    Fila aux;
    criaFila(&aux);
    int pares = 0;

    while (!filaVazia(f)) {
        int valor = dequeue(f);
        if (valor % 2 == 0) {
            pares++;
        }
        enqueue(&aux, valor);
    }
    while (!filaVazia(&aux)) {
        enqueue(f, dequeue(&aux));
    }
    return pares;
}


void preencherFila(Fila *f, char nomeFila) {
    int n, valor;
    printf("Quantidade Fila %c? ", nomeFila);
    scanf("%d", &n);
    for (int i = 0; i < n && i < MAX; i++) {
        printf("Valor (%d) para F%c: ", i + 1, nomeFila);
        scanf("%d", &valor);
        enqueue(f, valor);
    }
}

int main() {
    Fila F1, F2;
    criaFila(&F1);
    criaFila(&F2);

    printf("---Fila 1----\n");
    preencherFila(&F1, '1');
    printf("\n----Fila 2 ---\n");
    preencherFila(&F2, '2');

    printf("\n---------------\n"); // [cite: 4, 5]
    saoIguais(&F1, &F2);

    printf("\n--------------\n"); // 
    estatisticasFila(&F1);
    
    printf("\n-------------\n");
    printf("F1 tem %d elementos pares.\n", contaPares(&F1)); // 
    printf("F1 tem %d elementos impares.\n", contaImpares(&F1)); // 

    printf("\n--------------\n"); // 
    transfereF1paraF2(&F1, &F2);
    
    printf("\n------------\n");
    estatisticasFila(&F2);

    return 0;
}