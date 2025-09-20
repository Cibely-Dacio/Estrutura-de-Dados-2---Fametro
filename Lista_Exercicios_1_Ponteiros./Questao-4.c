#include <stdio.h>

void dobrar(int *num) {
    *num = *num * 2;
}

int main() {
    int numero;

    printf("Digite um número para dobrar: ");
    scanf("%d", &numero);

    printf("Valor original: %d\n", numero);

    dobrar(&numero);

    printf("Valor dobrado: %d\n", numero);

    return 0;
}
