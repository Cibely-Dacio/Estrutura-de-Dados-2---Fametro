#include <stdio.h>
void trocarValores(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int valor1, valor2;

    printf("Digite o primeiro valor: ");
    scanf("%d", &valor1);
    printf("Digite o segundo valor: ");
    scanf("%d", &valor2);

    printf("\nValores originais: valor1 = %d, valor2 = %d\n", valor1, valor2);

    trocarValores(&valor1, &valor2);

    printf("Valores trocados: valor1 = %d, valor2 = %d\n", valor1, valor2);

    return 0;
}
