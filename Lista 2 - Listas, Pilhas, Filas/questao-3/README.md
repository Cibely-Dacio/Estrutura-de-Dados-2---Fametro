# Questao 3 - Pilha de Processos (stack simulado)

Arquivos:
- pilha.h, pilha.c: implementação da pilha e operações.
- main.c: interface de comandos.

Compilar:
```bash
gcc -std=c11 -Wall main.c pilha.c -o questao3
```

Executar:
```bash
./questao3
```

Comandos:
- CALL <nomeFunc> <sp>
- RET
- PEEK
- TRACE
- EXIT

EXEMPLO:  
- CALL main 100
- CALL f1 200
- PEEK
- CALL f2 300
- TRACE
- RET
- TRACE
- RET
- RET
- EXIT



Complexidades (Big-O):
- pilha_init: O(1)
- push: O(1)
- pop: O(1)
- peek: O(1)
- vazia: O(1)
- limpar: O(n)
