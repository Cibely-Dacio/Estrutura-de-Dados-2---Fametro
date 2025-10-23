#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 50

typedef struct {
    int topo;
    int dados[MAX];
} Pilha;

void criaPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX - 1;
}

void push(Pilha *p, int valor) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia\n");
    } else {
        p->topo++;
        p->dados[p->topo] = valor;
    }
}

int pop(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia\n");
        return -1;
    } else {
        int valor = p->dados[p->topo];
        p->topo--;
        return valor;
    }
}

int tamanhoPilha(Pilha *p) {
    return p->topo + 1;
}

void saoIguais(Pilha *p1, Pilha *p2) {
    if (tamanhoPilha(p1) != tamanhoPilha(p2)) {
        printf("\n----------------------------\n");
        printf("As pilhas nao sao iguais.\n");
        if (tamanhoPilha(p1) > tamanhoPilha(p2)) {
            printf("\n----------------------------\n");
            printf("A pilha P1 é maior.\n", tamanhoPilha(p1));
        } else {
            printf("\n----------------------------\n");
            printf("A pilha P2 é maior.\n", tamanhoPilha(p2));
        }
        return;
    }

    Pilha aux1, aux2;
    criaPilha(&aux1);
    criaPilha(&aux2);
    int sao_iguais = 1;

    while (!pilhaVazia(p1)) {
        int v1 = pop(p1);
        int v2 = pop(p2);
        if (v1 != v2) {
            sao_iguais = 0;
        }
        push(&aux1, v1);
        push(&aux2, v2);
    }

    while (!pilhaVazia(&aux1)) {
        push(p1, pop(&aux1));
        push(p2, pop(&aux2));
    }

    if (sao_iguais) {
        printf("\n----------------------------\n");
        printf("As pilhas P1 e P2 sao iguais.\n"); // 
    } else {
        printf("\n----------------------------\n");
        printf("As pilhas P1 e P2 nao são iguais.\n");
    }
}

// 
void estatisticasPilha(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("A pilha esta vazia.\n");
        return;
    }

    Pilha aux;
    criaPilha(&aux);

    int maior = INT_MIN;
    int menor = INT_MAX;
    double soma = 0;
    int contador = 0;

    while (!pilhaVazia(p)) {
        int valor = pop(p);
        if (valor > maior) maior = valor;
        if (valor < menor) menor = valor;
        soma += valor;
        contador++;
        push(&aux, valor);
    }

    while (!pilhaVazia(&aux)) {
        push(p, pop(&aux));
    }
    printf("\n----------------------------\n"); 
    printf("\nMaior elemento: %d\n", maior); 
    printf("\nMenor elemento: %d\n", menor);
    printf("\nMedia aritmetica: %.2f\n", soma / contador);
}

// 
void transfereP1paraP2(Pilha *p1, Pilha *p2) {
    Pilha aux;
    criaPilha(&aux);
    criaPilha(p2);

    while (!pilhaVazia(p1)) {
        push(&aux, pop(p1));
    }

    while (!pilhaVazia(&aux)) {
        int valor = pop(&aux);
        push(p1, valor); // Restaura P1
        push(p2, valor); // Copia para P2
    }
    printf("----------------------------");
    printf("\nP1 copiado para P2.\n");
}

// 
int contaImpares(Pilha *p) {
    Pilha aux;
    criaPilha(&aux);
    int impares = 0;

    while (!pilhaVazia(p)) {
        int valor = pop(p);
        if (valor % 2 != 0) {
            impares++;
        }
        push(&aux, valor);
    }
    // Restaura p
    while (!pilhaVazia(&aux)) {
        push(p, pop(&aux));
    }
    return impares;
}

// 
int contaPares(Pilha *p) {
    Pilha aux;
    criaPilha(&aux);
    int pares = 0;

    while (!pilhaVazia(p)) {
        int valor = pop(p);
        if (valor % 2 == 0) {
            pares++;
        }
        push(&aux, valor);
    }
    // Restaura p
    while (!pilhaVazia(&aux)) {
        push(p, pop(&aux));
    }
    return pares;
}

void preencherPilha(Pilha *p, char nomePilha) {
    int n, valor;
    printf("Quantidade Pilha %c? ", nomePilha);
    scanf("%d", &n);
    for (int i = 0; i < n && i < MAX; i++) {
        printf("Valor (%d) para P%c: ", i + 1, nomePilha);
        scanf("%d", &valor);
        push(p, valor);
    }
}

int main() {
    Pilha P1, P2;
    criaPilha(&P1);
    criaPilha(&P2);

    printf("\n--- Pilha 1 ---\n");
    preencherPilha(&P1, '1');
    printf("\n--- Pilha 2 ---\n");
    preencherPilha(&P2, '2');

    saoIguais(&P1, &P2);

    estatisticasPilha(&P1);
    printf("\n----------------------------\n");
    printf("P1 tem %d elementos pares.\n", contaPares(&P1)); // 
    printf("P1 tem %d elementos impares.\n", contaImpares(&P1)); // 

    transfereP1paraP2(&P1, &P2);
    
    printf("\nApos Copia\n");
    estatisticasPilha(&P2);

    return 0;
}