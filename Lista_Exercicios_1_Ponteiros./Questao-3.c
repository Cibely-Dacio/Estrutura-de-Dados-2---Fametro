#include <stdio.h>

int main() {
    int variavel;
    int *ponteiro = NULL;

    printf("Digite um valor inteiro: ");
    scanf("%d", &variavel);

    ponteiro = &variavel;

    printf("\n--- Resultados ---\n");
    printf("1. Valor da variável: %d\n", variavel);
    printf("2. Endereço: %p\n", (void*)&variavel);
    printf("3. Valor do ponteiro (endereço para onde aponta): %p\n", (void*)ponteiro);
    printf("4. Valor ponteiro: %d\n", *ponteiro);

    return 0;
}
