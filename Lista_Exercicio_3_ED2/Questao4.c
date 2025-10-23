#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No* prox;
} No;

typedef struct {
    No* topo;
} PilhaDinamica;

typedef struct {
    No* inicio;
    No* fim;
} FilaDinamica;


void criaPilha(PilhaDinamica* p) {
    p->topo = NULL;
}

int pilhaVazia(PilhaDinamica* p) {
    return p->topo == NULL;
}

void push(PilhaDinamica* p, int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro de alocacao de memoria (pilha)!\n");
        return;
    }
    novoNo->dado = valor;
    novoNo->prox = p->topo;
    p->topo = novoNo;
}

int pop(PilhaDinamica* p) {
    if (pilhaVazia(p)) {
        printf("Erro: Pilha vazia!\n");
        return -1;
    }
    No* temp = p->topo;
    int valor = temp->dado;
    p->topo = temp->prox;
    free(temp);
    return valor;
}

void criaFila(FilaDinamica* f) {
    f->inicio = NULL;
    f->fim = NULL;
}

int filaVazia(FilaDinamica* f) {
    return f->inicio == NULL;
}

void enqueue(FilaDinamica* f, int valor) {
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro de alocacao de memoria (fila)!\n");
        return;
    }
    novoNo->dado = valor;
    novoNo->prox = NULL;
    
    if (filaVazia(f)) {
        f->inicio = novoNo;
        f->fim = novoNo;
    } else {
        f->fim->prox = novoNo;
        f->fim = novoNo;
    }
}

int dequeue(FilaDinamica* f) {
    if (filaVazia(f)) {
        printf("Erro: Fila vazia!\n");
        return -1;
    }
    No* temp = f->inicio;
    int valor = temp->dado;
    f->inicio = temp->prox;
    
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    free(temp);
    return valor;
}

int existeNaPilha(PilhaDinamica* p, int valor) {
    No* atual = p->topo;
    while (atual != NULL) {
        if (atual->dado == valor) {
            return 1; 
        }
        atual = atual->prox;
    }
    return 0;
}

int existeNaFila(FilaDinamica* f, int valor) {
    No* atual = f->inicio;
    while (atual != NULL) {
        if (atual->dado == valor) {
            return 1; 
        }
        atual = atual->prox;
    }
    return 0;
}

void relatorioPilha(PilhaDinamica* p) {
    printf("Relatorio III: Numeros na Pilha\n");
    if (pilhaVazia(p)) {
        printf("(Pilha vazia)\n");
        return;
    }
    No* atual = p->topo;
    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->prox;
    }
    printf("\n");
}

void relatorioFila(FilaDinamica* f) {
    printf("Relatorio II: Numeros na Fila\n");
    if (filaVazia(f)) {
        printf("(Fila vazia)\n");
        return;
    }
    No* atual = f->inicio;
    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->prox;
    }
    printf("\n");
}

void relatorioComuns(PilhaDinamica* p, FilaDinamica* f) {
    printf("Relatorio I: Numeros em ambas as estruturas\n");
    if (pilhaVazia(p) || filaVazia(f)) {
        printf("(Nenhum em comum, uma ou ambas estao vazias)\n");
        return;
    }
    
    No* atualPilha = p->topo;
    int encontrou = 0;
    while (atualPilha != NULL) {
        if (existeNaFila(f, atualPilha->dado)) {
            printf("%d ", atualPilha->dado);
            encontrou = 1;
        }
        atualPilha = atualPilha->prox;
    }
    
    if (!encontrou) {
        printf("(Nenhum numero em comum encontrado)\n");
    }
    printf("\n");
}


int main() {
    PilhaDinamica p;
    FilaDinamica f;
    criaPilha(&p);
    criaFila(&f);
    int valor;

    printf("---FILA ---\n");
    for (int i = 0; i < 5; i++) {
        printf("%d.: ", i + 1);
        scanf("%d", &valor);
        enqueue(&f, valor);
    }

    printf("\n--- PILHA ---\n");
    for (int i = 0; i < 5; i++) {
        printf("%d: ", i + 1);
        scanf("%d", &valor);
        push(&p, valor);
    }

    printf("\n\n---------------\n");
    relatorioComuns(&p, &f);  
    printf("\n");
    relatorioFila(&f);         
    printf("\n");
    relatorioPilha(&p);      

    while (!pilhaVazia(&p)) pop(&p);
    while (!filaVazia(&f)) dequeue(&f);

    return 0;

}
