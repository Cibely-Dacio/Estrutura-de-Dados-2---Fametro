# Questao 2 - Fila para Venda Digital de Ingressos

Arquivos:
- fila.h, fila.c: implementação da fila e operações.
- main.c: aplicação de venda.

Compilar:
```bash
gcc -std=c11 -Wall main.c fila.c -o questao2
```

Executar:
```bash
./questao2
```
Ao iniciar, será solicitado o estoque inicial (número inteiro).
Comandos:
- ADD <id> <qtd>
- START
- REL
- EXIT

Complexidades (Big-O):
- inicializar: O(1)
- enfileirar: O(1)
- desenfileirar: O(1)
- vazia: O(1)
- limpar: O(n)