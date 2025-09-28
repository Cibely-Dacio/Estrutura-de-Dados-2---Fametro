#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

/*
Commands:
At start, provide estoque_inicial (integer)
ADD <id> <qtd>
START
REL
EXIT
*/

#define MAXLINE 256

typedef struct {
    int total_vendido;
    int num_atendidos;
    int top_k[3];
    int top_k_qtd[3];
    Fila nao_atendidos;
    int estoque;
} Relatorio;

static void init_rel(Relatorio *r, int estoque) {
    r->total_vendido = 0;
    r->num_atendidos = 0;
    for (int i=0;i<3;i++){ r->top_k[i]=-1; r->top_k_qtd[i]=0;}
    inicializar(&r->nao_atendidos);
    r->estoque = estoque;
}

static void consider_topk(Relatorio *r, const char *id, int qtd) {
    // keep top-3 by qtd (simple)
    for (int i=0;i<3;i++) {
        if (qtd > r->top_k_qtd[i]) {
            // shift down
            for (int j=2;j>i;j--) {
                r->top_k[j] = r->top_k[j-1];
                r->top_k_qtd[j] = r->top_k_qtd[j-1];
            }
            // store index to id mapping by hashing is complex; we will not store id names here,
            // instead print the qtd only in REL. (Simplification)
            r->top_k_qtd[i] = qtd;
            return;
        }
    }
}

int main() {
    char line[MAXLINE];
    int estoque;
    printf("Informe estoque inicial (numero inteiro): ");
    if (!fgets(line, sizeof(line), stdin)) return 0;
    if (sscanf(line, "%d", &estoque) != 1) {
        printf("Estoque invalido\\n");
        return 0;
    }
    Fila fila;
    inicializar(&fila);
    Relatorio rel;
    init_rel(&rel, estoque);

    printf("Comandos: ADD <id> <qtd> | START | REL | EXIT\\n");
    while (fgets(line, sizeof(line), stdin)) {
        char cmd[16];
        if (sscanf(line, "%15s", cmd) != 1) continue;
        if (strcmp(cmd, "EXIT")==0) break;
        else if (strcmp(cmd, "ADD")==0) {
            char id[24];
            int qtd;
            if (sscanf(line+4, "%23s %d", id, &qtd) != 2) { printf("Formato: ADD <id> <qtd>\\n"); continue; }
            Cliente c;
            strncpy(c.id, id, sizeof(c.id)); c.id[sizeof(c.id)-1]='\\0';
            c.qtd = qtd;
            enfileirar(&fila, c);
            printf("ADDED\\n");
        } else if (strcmp(cmd, "START")==0) {
            while (!vazia(&fila) && rel.estoque > 0) {
                Cliente c;
                desenfileirar(&fila, &c);
                if (c.qtd <= rel.estoque) {
                    rel.estoque -= c.qtd;
                    rel.total_vendido += c.qtd;
                    rel.num_atendidos++;
                    consider_topk(&rel, c.id, c.qtd);
                    printf("Cliente %s atendido: %d\\n", c.id, c.qtd);
                } else {
                    // offer available
                    printf("Cliente %s solicitou %d, disponivel %d. Aceita venda parcial? (S/N): ", c.id, c.qtd, rel.estoque);
                    fflush(stdout);
                    char resp[8];
                    if (!fgets(resp, sizeof(resp), stdin)) break;
                    if (resp[0]=='S' || resp[0]=='s') {
                        rel.total_vendido += rel.estoque;
                        rel.num_atendidos++;
                        consider_topk(&rel, c.id, rel.estoque);
                        printf("Cliente %s atendido parcialmente: %d\\n", c.id, rel.estoque);
                        rel.estoque = 0;
                    } else {
                        // register as not attended
                        enfileirar(&rel.nao_atendidos, c);
                        printf("Cliente %s registrado como nao atendido\\n", c.id);
                    }
                }
                if (rel.estoque == 0) {
                    printf("Estoque esgotado. Processamento finalizado.\\n");
                    break;
                }
            }
            if (vazia(&fila)) printf("Fila processada\\n");
        } else if (strcmp(cmd, "REL")==0) {
            printf("Total vendido: %d\\n", rel.total_vendido);
            printf("Numero de clientes atendidos: %d\\n", rel.num_atendidos);
            printf("Top-3 maiores compras (apenas quantidades): ");
            for (int i=0;i<3;i++) printf("%d ", rel.top_k_qtd[i]);
            printf("\\n");
            printf("Quantidade restante em estoque: %d\\n", rel.estoque);
            printf("Lista de nao atendidos:\\n");
            listar_nao_atendidos:
            // iterate nao_atendidos
            Cliente *it = rel.nao_atendidos.ini;
            while (it) {
                printf("%s %d\\n", it->id, it->qtd);
                it = it->prox;
            }
        } else {
            printf("Comando desconhecido\\n");
        }
    }

    limpar(&fila);
    limpar(&rel.nao_atendidos);
    return 0;
}