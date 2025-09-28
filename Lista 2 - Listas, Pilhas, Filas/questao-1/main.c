#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"

/*
Commands:
ADD <cod> "<nome>" <qtd> <preco>
UPD <cod> <delta_qtd>
DEL <cod>
FIND <cod>
LIST
REL
EXIT
*/

static void print_rel(Produto *L) {
    int total_distintos = 0;
    double valor_total = 0.0;
    Produto *maior = NULL;
    for (Produto *p = L; p; p = p->prox) {
        total_distintos++;
        valor_total += p->qtd * p->preco;
        if (!maior || (p->qtd * p->preco) > (maior->qtd * maior->preco)) maior = p;
    }
    printf("Total distintos: %d\n", total_distintos);
    printf("Valor total estoque: %.2f\n", valor_total);
    if (maior) {
        printf("Produto com maior valor imobilizado: %s %s (valor %.2f)\n", maior->codigo, maior->nome, maior->qtd * maior->preco);
    } else {
        printf("Sem produtos.\n");
    }
}

int main() {
    Produto *L = NULL;
    char line[256];
    printf("Controle de Estoque - digite comandos (EXIT para sair)\\n");
    while (fgets(line, sizeof(line), stdin)) {
        // trim newline
        char cmd[16];
        if (sscanf(line, "%15s", cmd) != 1) continue;
        if (strcmp(cmd, "EXIT")==0) break;
        else if (strcmp(cmd, "ADD")==0) {
            char codigo[16], nome[64];
            int qtd;
            float preco;
            // parse: ADD <cod> "<nome>" <qtd> <preco>
            char *p = strchr(line, ' ');
            if (!p) continue;
            // move past "ADD "
            p++;
            // read codigo
            if (sscanf(p, "%15s", codigo) != 1) continue;
            // find first quote
            char *q = strchr(p, '\"');
            if (!q) continue;
            q++;
            char *r = strchr(q, '\"');
            if (!r) continue;
            size_t len = r - q;
            if (len >= sizeof(nome)) len = sizeof(nome)-1;
            strncpy(nome, q, len);
            nome[len] = '\\0';
            // after r, read qtd and preco
            if (sscanf(r+1, "%d %f", &qtd, &preco) != 2) continue;
            Produto prod;
            strncpy(prod.codigo, codigo, sizeof(prod.codigo));
            prod.codigo[sizeof(prod.codigo)-1]='\\0';
            strncpy(prod.nome, nome, sizeof(prod.nome));
            prod.nome[sizeof(prod.nome)-1]='\\0';
            prod.qtd = qtd;
            prod.preco = preco;
            L = inserir_ordenado_por_codigo(L, prod);
            printf("ADD OK\\n");
        } else if (strcmp(cmd, "UPD")==0) {
            char codigo[16];
            int delta;
            if (sscanf(line+4, "%15s %d", codigo, &delta) != 2) {
                printf("Formato UPD: UPD <cod> <delta_qtd>\\n");
                continue;
            }
            Produto *p = buscar(L, codigo);
            if (!p) { printf("Produto nao encontrado\\n"); continue; }
            if (p->qtd + delta < 0) { printf("Operacao negada: quantidade negativa\\n"); continue; }
            L = ajustar_quantidade(L, codigo, delta);
            printf("UPD OK\\n");
        } else if (strcmp(cmd, "DEL")==0) {
            char codigo[16];
            if (sscanf(line+4, "%15s", codigo) != 1) continue;
            L = remover_por_codigo(L, codigo);
            printf("DEL OK\\n");
        } else if (strcmp(cmd, "FIND")==0) {
            char codigo[16];
            if (sscanf(line+5, "%15s", codigo) != 1) continue;
            Produto *p = buscar(L, codigo);
            if (p) printf("Encontrado: %s %s %d %.2f\\n", p->codigo, p->nome, p->qtd, p->preco);
            else printf("Nao encontrado\\n");
        } else if (strcmp(cmd, "LIST")==0) {
            listar(L);
        } else if (strcmp(cmd, "REL")==0) {
            print_rel(L);
        } else {
            printf("Comando desconhecido\\n");
        }
    }
    L = limpar(L);
    return 0;
}