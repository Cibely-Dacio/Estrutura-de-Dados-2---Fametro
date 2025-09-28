#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

/*
Commands:
CALL <nomeFunc> <sp>
RET
PEEK
TRACE
EXIT
*/

int main() {
    Pilha s;
    pilha_init(&s);
    char line[256];
    printf("Pilha de processos - comandos CALL/RET/PEEK/TRACE/EXIT\\n");
    while (fgets(line, sizeof(line), stdin)) {
        char cmd[16];
        if (sscanf(line, "%15s", cmd) != 1) continue;
        if (strcmp(cmd, "EXIT")==0) break;
        else if (strcmp(cmd, "CALL")==0) {
            char nome[48];
            int sp;
            if (sscanf(line+5, "%47s %d", nome, &sp) != 2) { printf("Formato: CALL <nomeFunc> <sp>\\n"); continue; }
            if (push(&s, nome, sp)) printf("CALL ok\\n"); else printf("Falha ao empilhar\\n");
        } else if (strcmp(cmd, "RET")==0) {
            Frame f;
            if (pop(&s, &f)) printf("RET %s %d\\n", f.func, f.sp);
            else printf("Erro: pilha vazia\\n");
        } else if (strcmp(cmd, "PEEK")==0) {
            Frame f;
            if (peek(&s, &f)) printf("TOPO %s %d\\n", f.func, f.sp);
            else printf("Pilha vazia\\n");
        } else if (strcmp(cmd, "TRACE")==0) {
            printf("TRACE (topo->fundo):\\n");
            Frame *it = s.topo;
            int lvl=0;
            while (it) {
                printf("[%d] %s %d\\n", lvl, it->func, it->sp);
                it = it->baixo;
                lvl++;
            }
        } else {
            printf("Comando desconhecido\\n");
        }
    }
    limpar(&s);
    return 0;
}