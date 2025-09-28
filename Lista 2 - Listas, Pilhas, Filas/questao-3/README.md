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

Exemplos:
-ADD P001 "Mouse Gamer" 10 150.00
-ADD P002 "Teclado Mecânico" 5 350.00
-LIST
-UPD P001 -3
-FIND P001
-REL
-DEL P002
-LIST
-EXIT


Complexidades (Big-O):
- pilha_init: O(1)
- push: O(1)
- pop: O(1)
- peek: O(1)
- vazia: O(1)
- limpar: O(n)
