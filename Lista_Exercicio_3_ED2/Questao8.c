#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Para toupper()

#define MAX 50

// --- Estrutura da Fila de Tipos ---
typedef struct {
    char letra;
    float percentualImposto;
} Tipo;

typedef struct {
    int inicio, fim, total;
    Tipo dados[MAX];
} FilaTipos;

// --- Estrutura da Fila de Produtos ---
typedef struct {
    int codigo;
    float preco;
    char tipo; // Chave de ligação
} Produto;

typedef struct {
    int inicio, fim, total;
    Produto dados[MAX];
} FilaProdutos;

// --- Variáveis Globais ---
FilaTipos fTipos;
FilaProdutos fProdutos;
int proximoCodProduto = 1; // Gerador automático

// --- Funções da Fila de Tipos ---
void criaFilaTipos() { fTipos.inicio = 0; fTipos.fim = 0; fTipos.total = 0; }
int filaTiposVazia() { return fTipos.total == 0; }
int filaTiposCheia() { return fTipos.total == MAX; }
void enqueueTipo(Tipo t) {
    if (!filaTiposCheia()) {
        fTipos.dados[fTipos.fim] = t;
        fTipos.fim = (fTipos.fim + 1) % MAX;
        fTipos.total++;
    }
}
Tipo dequeueTipo() {
    // Assume que não está vazia
    Tipo t = fTipos.dados[fTipos.inicio];
    fTipos.inicio = (fTipos.inicio + 1) % MAX;
    fTipos.total--;
    return t;
}

// --- Funções da Fila de Produtos ---
void criaFilaProdutos() { fProdutos.inicio = 0; fProdutos.fim = 0; fProdutos.total = 0; }
int filaProdutosVazia() { return fProdutos.total == 0; }
int filaProdutosCheia() { return fProdutos.total == MAX; }
void enqueueProduto(Produto p) {
    if (!filaProdutosCheia()) {
        fProdutos.dados[fProdutos.fim] = p;
        fProdutos.fim = (fProdutos.fim + 1) % MAX;
        fProdutos.total++;
    }
}

// --- Funções Auxiliares (Consultas) ---

// Verifica se tipo existe
int existeTipo(char letraTipo) {
    if (filaTiposVazia()) return 0;
    
    int idx = fTipos.inicio;
    for (int i = 0; i < fTipos.total; i++) {
        // Compara maiúsculas para não diferenciar 'a' de 'A'
        if (toupper(fTipos.dados[idx].letra) == toupper(letraTipo)) {
            return 1; // Existe
        }
        idx = (idx + 1) % MAX;
    }
    return 0; // Não existe
}

// Pega o imposto de um tipo
float getPercentualImposto(char letraTipo) {
    int idx = fTipos.inicio;
    for (int i = 0; i < fTipos.total; i++) {
        if (toupper(fTipos.dados[idx].letra) == toupper(letraTipo)) {
            return fTipos.dados[idx].percentualImposto;
        }
        idx = (idx + 1) % MAX;
    }
    return 0; // Se não achar
}

// Verifica se existem produtos de um tipo
int existeProdutoDoTipo(char letraTipo) {
    if (filaProdutosVazia()) return 0;
    
    int idx = fProdutos.inicio;
    for (int i = 0; i < fProdutos.total; i++) {
        if (toupper(fProdutos.dados[idx].tipo) == toupper(letraTipo)) {
            return 1; // Existe produto
        }
        idx = (idx + 1) % MAX;
    }
    return 0; // Não existe
}

// --- Funções do Menu ---

// 1- Cadastrar tipo
void cadastrarTipo() {
    if (filaTiposCheia()) {
        printf("Mensagem: Fila de tipos cheia.\n");
        return;
    }
    Tipo novoTipo;
    printf("Digite a letra que representa o tipo: ");
    scanf(" %c", &novoTipo.letra);
    printf("Digite o percentual de imposto (ex: 15.5): ");
    scanf("%f", &novoTipo.percentualImposto);
    
    enqueueTipo(novoTipo);
    printf("Tipo cadastrado.\n");
}

// 2- Cadastrar produto
void cadastrarProduto() {
    if (filaProdutosCheia()) {
        printf("Mensagem: Fila de produtos cheia.\n");
        return;
    }
    if (filaTiposVazia()) {
        printf("Mensagem: Cadastre um TIPO antes de cadastrar um produto.\n");
        return;
    }
    
    Produto novoProduto;
    novoProduto.codigo = proximoCodProduto; // Automático
    
    printf("Digite o preco do produto (Codigo %d): ", novoProduto.codigo);
    scanf("%f", &novoProduto.preco);
    
    printf("Digite o tipo (letra) do produto: ");
    scanf(" %c", &novoProduto.tipo);

    // Validação: Produto só pode ser cadastrado se o tipo existir
    if (existeTipo(novoProduto.tipo)) {
        enqueueProduto(novoProduto);
        proximoCodProduto++;
        printf("Produto cadastrado.\n");
    } else {
        printf("Tipo de produto inexistente.\n");
    }
}

// 3- Consultar preco de um produto
void consultarPreco() {
    if (filaProdutosVazia()) {
        printf("Fila vazia.\n");
        return;
    }
    
    int codConsulta;
    printf("Digite o codigo (numero) do produto a consultar: ");
    scanf("%d", &codConsulta);

    int idx = fProdutos.inicio;
    int encontrou = 0;
    for (int i = 0; i < fProdutos.total; i++) {
        Produto p = fProdutos.dados[idx];
        if (p.codigo == codConsulta) {
            float impostoPerc = getPercentualImposto(p.tipo);
            float valorImposto = p.preco * (impostoPerc / 100.0);
            float precoFinal = p.preco - valorImposto;
            
            printf("Produto Cod: %d, Tipo: %c\n", p.codigo, p.tipo);
            printf("Preco Bruto: R$ %.2f\n", p.preco);
            printf("Imposto (%.2f%%): R$ %.2f\n", impostoPerc, valorImposto);
            printf("Preco = %.2f\n", precoFinal);
            encontrou = 1;
            break;
        }
        idx = (idx + 1) % MAX;
    }
    
    if (!encontrou) {
        printf("Produto nao encontrado.\n");
    }
}

// 4- Excluir tipo
void excluirTipo() {
    if (filaTiposVazia()) {
        printf("Mensagem: Fila de tipos vazia.\n");
        return;
    }

    // Pega o primeiro tipo da fila (sem remover)
    Tipo tipoParaExcluir = fTipos.dados[fTipos.inicio]; 
    
    // Validação: Um tipo só pode ser excluído se não existir nenhum produto cadastrado para ele
    if (existeProdutoDoTipo(tipoParaExcluir.letra)) {
        printf("Mensagem: O tipo %c nao pode ser excluido.\n", tipoParaExcluir.letra);
        printf("Existem produtos cadastrados para este tipo.\n");
    } else {
        dequeueTipo(); // Remove o tipo do início da fila (regra da fila)
        printf("Tipo %c (percentual %.2f%%) excluido com sucesso.\n", 
               tipoParaExcluir.letra, tipoParaExcluir.percentualImposto);
    }
}

// 5- Listar Tipos (NOVO)
void listarTipos() {
    if (filaTiposVazia()) {
        printf("Nenhum tipo (categoria) cadastrado.\n");
        return;
    }
    printf("--- TIPOS CADASTRADOS (Inicio -> Fim) ---\n");
    int idx = fTipos.inicio;
    for (int i = 0; i < fTipos.total; i++) {
        Tipo t = fTipos.dados[idx];
        printf("Tipo: %c | Imposto: %.2f%%\n", t.letra, t.percentualImposto);
        idx = (idx + 1) % MAX;
    }
}

// 6- Listar Produtos (NOVO)
void listarProdutos() {
    if (filaProdutosVazia()) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    printf("--- PRODUTOS CADASTRADOS (Inicio -> Fim) ---\n");
    int idx = fProdutos.inicio;
    for (int i = 0; i < fProdutos.total; i++) {
        Produto p = fProdutos.dados[idx];
        printf("Cod: %d | Preco Bruto: R$ %.2f | Tipo: %c\n", p.codigo, p.preco, p.tipo);
        idx = (idx + 1) % MAX;
    }
}


void mostrarMenu() {
    printf("\n--- MENU PRODUTOS/TIPOS ---\n");
    printf("1- Cadastrar tipo\n");
    printf("2- Cadastrar produto\n");
    printf("3- Consultar preco de um produto\n");
    printf("4- Excluir tipo\n");
    printf("5- Listar Tipos (Categorias)\n"); 
    printf("6- Listar Produtos\n");        
    printf("7- Sair\n");                     
    printf("Escolha uma opcao: ");
}

int main() {
    criaFilaTipos();
    criaFilaProdutos();
    int opcao;

    do {
        mostrarMenu();
        if (scanf("%d", &opcao) != 1) {
            // Limpa o buffer de entrada se não for um número
            while (getchar() != '\n');
            opcao = -1; // Força a opção inválida
        }

        switch (opcao) {
            case 1: cadastrarTipo(); break;
            case 2: cadastrarProduto(); break;
            case 3: consultarPreco(); break;
            case 4: excluirTipo(); break;
            case 5: listarTipos(); break;
            case 6: listarProdutos(); break;
            case 7: printf("Saindo...\n"); break;
            default:
                printf("Mensagem de opcao invalida no menu.\n");
        }
    } while (opcao != 7); // Sair é a opção 7 agora

    return 0;
}