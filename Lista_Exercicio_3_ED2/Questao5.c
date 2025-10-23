#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Para INT_MIN

#define MAX 100

// --- Estrutura da Pilha Estática ---
typedef struct {
    int topo;
    int dados[MAX];
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

// --- Funções de Pilha (Internas/Silenciosas) ---
// Estas funções APENAS fazem a lógica, sem imprimir mensagens de menu.

// Empilha silenciosamente. Retorna 1 (sucesso) ou 0 (falha).
int push_interno(Pilha *p, int valor) {
    if (pilhaCheia(p)) {
        return 0; // Falha
    }
    p->topo++;
    p->dados[p->topo] = valor;
    return 1; // Sucesso
}

// Desempilha silenciosamente. Retorna o valor ou INT_MIN (erro).
int pop_interno(Pilha *p) {
    if (pilhaVazia(p)) {
        return INT_MIN; 
    }
    int valor = p->dados[p->topo];
    p->topo--;
    return valor;
}

// --- Funções do Menu (Externas/Verbais) ---

// 1- Cadastrar número
void cadastrarNumero(Pilha *p) {
    int valor;
    printf("Digite o numero a ser cadastrado: ");
    scanf("%d", &valor);
    
    if (push_interno(p, valor)) {
        printf("Numero %d cadastrado com sucesso.\n", valor);
    } else {
        // Mensagem caso a opção não possa ser realizada
        printf("Mensagem: Pilha cheia! Nao foi possivel cadastrar.\n");
    }
}

// 2- Mostrar números pares (CORRIGIDO)
void mostrarPares(Pilha *p) {
    if (pilhaVazia(p)) {
        // Mensagem caso a opção não possa ser realizada
        printf("Mensagem: Pilha vazia! Nao ha numeros para mostrar.\n");
        return;
    }

    Pilha aux;
    criaPilha(&aux);
    int encontrouPar = 0;

    printf("Numeros pares na pilha (do topo para a base):\n");
    
    // Esvazia p, verifica e guarda em aux
    while (!pilhaVazia(p)) {
        int valor = pop_interno(p);
        if (valor % 2 == 0) {
            printf("%d\n", valor); // Mostra o par
            encontrouPar = 1;
        }
        push_interno(&aux, valor); // Usa a função silenciosa
    }

    if (!encontrouPar) {
        printf("Nenhum numero par encontrado na pilha.\n");
    }

    // Restaura p
    while (!pilhaVazia(&aux)) {
        push_interno(p, pop_interno(&aux)); // Usa a função silenciosa
    }
}

// 3- Excluir número
void excluirNumero(Pilha *p) {
    int valorExcluido = pop_interno(p);
    
    if (valorExcluido == INT_MIN) {
        // Mensagem caso a opção não possa ser realizada
        printf("Mensagem: Pilha vazia! Nao ha numero para excluir.\n");
    } else {
        printf("Numero %d (topo) excluido com sucesso.\n", valorExcluido);
    }
}


void mostrarMenu() {
    printf("\n--- MENU ---\n");
    printf("1- Cadastrar numero\n");
    printf("2- Mostrar numeros pares\n");
    printf("3- Excluir numero\n");
    printf("4- Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    Pilha p;
    criaPilha(&p);
    int opcao;

    do {
        mostrarMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarNumero(&p);
                break;
            case 2:
                mostrarPares(&p);
                break;
            case 3:
                excluirNumero(&p);
                break;
            case 4:
                printf("Saindo...\n");
                break;
            default:
                // Mostrar mensagem para opção inválida
                printf("Mensagem: Opcao invalida do menu!\n");
        }
    } while (opcao != 4);

    return 0;
}