# Questao 1 - Lista ligada para Controle de Estoque

Arquivos:
- produto.h, produto.c: implementação da lista ligada e operações.
- main.c: interface textual.

Compilar:
```bash
gcc -std=c11 -Wall main.c produto.c -o questao1
```

Executar:
```bash
./questao1
```

Comandos suportados (digite no terminal):
- ADD <cod> "<nome>" <qtd> <preco>
- UPD <cod> <delta_qtd>
- DEL <cod>
- FIND <cod>
- LIST
- REL
- EXIT

Exemplos:
- ADD P001 "Mouse Gamer" 10 150.00
- ADD P002 "Teclado Mecânico" 5 350.00
- LIST
- UPD P001 -3
- FIND P001
- REL
- DEL P002
- LIST
- EXIT

Complexidades (Big-O):
- inserir_inicio: O(1)
- inserir_ordenado_por_codigo: O(n)
- remover_por_codigo: O(n)
- ajustar_quantidade: O(n) (usa buscar)
- buscar: O(n)
- listar: O(n)
- limpar: O(n)
