#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

#define MAX 50


typedef struct {
    char letra;
    float percentualImposto;
} Tipo;

typedef struct {
    int inicio, fim, total;
    Tipo dados[MAX];
} FilaTipos;


typedef struct {
    int codigo;
    float preco;
    char tipo; 
} Produto;

typedef struct {
    int inicio, fim, total;
    Produto dados[MAX];
} FilaProdutos;


FilaTipos fTipos;
FilaProdutos fProdutos;
int proximoCodProduto = 1; 


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

    Tipo t = fTipos.dados[fTipos.inicio];
    fTipos.inicio = (fTipos.inicio + 1) % MAX;
    fTipos.total--;
    return t;
}


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




int existeTipo(char letraTipo) {
    if (filaTiposVazia()) return 0;
    
    int idx = fTipos.inicio;
    for (int i = 0; i < fTipos.total; i++) {
   
        if (toupper(fTipos.dados[idx].letra) == toupper(letraTipo)) {
            return 1; 
        }
        idx = (idx + 1) % MAX;
    }
    return 0; 
}

float getPercentualImposto(char letraTipo) {
    int idx = fTipos.inicio;
    for (int i = 0; i < fTipos.total; i++) {
        if (toupper(fTipos.dados[idx].letra) == toupper(letraTipo)) {
            return fTipos.dados[idx].percentualImposto;
        }
        idx = (idx + 1) % MAX;
    }
    return 0; 
}

int existeProdutoDoTipo(char letraTipo) {
    if (filaProdutosVazia()) return 0;
    
    int idx = fProdutos.inicio;
    for (int i = 0; i < fProdutos.total; i++) {
        if (toupper(fProdutos.dados[idx].tipo) == toupper(letraTipo)) {
            return 1;
        }
        idx = (idx + 1) % MAX;
    }
    return 0; 
}

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
    novoProduto.codigo = proximoCodProduto;
    
    printf("Digite o preco do produto (Codigo %d): ", novoProduto.codigo);
    scanf("%f", &novoProduto.preco);
    
    printf("Digite o tipo (letra) do produto: ");
    scanf(" %c", &novoProduto.tipo);

    if (existeTipo(novoProduto.tipo)) {
        enqueueProduto(novoProduto);
        proximoCodProduto++;
        printf("Produto cadastrado.\n");
    } else {
        printf("Tipo de produto inexistente.\n");
    }
}

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

void excluirTipo() {
    if (filaTiposVazia()) {
        printf("Mensagem: Fila de tipos vazia.\n");
        return;
    }

    Tipo tipoParaExcluir = fTipos.dados[fTipos.inicio]; 
    
    if (existeProdutoDoTipo(tipoParaExcluir.letra)) {
        printf("Mensagem: O tipo %c nao pode ser excluido.\n", tipoParaExcluir.letra);
        printf("Existem produtos cadastrados para este tipo.\n");
    } else {
        dequeueTipo();
        printf("Tipo %c (percentual %.2f%%) excluido com sucesso.\n", 
               tipoParaExcluir.letra, tipoParaExcluir.percentualImposto);
    }
}

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

            while (getchar() != '\n');
            opcao = -1;
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
    } while (opcao != 7);

    return 0;
}
