#include <stdio.h>
#include <stdlib.h> 

void encontrarMaiorMenor(int *array, int tamanho, int *maior, int *menor) {
    if (tamanho <= 0) return;

    *maior = array[0];
    *menor = array[0];

    for (int i = 1; i < tamanho; i++) {
        if (array[i] > *maior) {
            *maior = array[i];
        }
        if (array[i] < *menor) {
            *menor = array[i];
        }
    }
}

int main() {
    int tamanho;
    printf("Digite o tamanho do array:");
    scanf("%d", &tamanho);

    if (tamanho <= 0) {
        printf("Tamanho inválido.\n");
        return 1;
    }
    int *numeros = (int*) malloc(tamanho * sizeof(int));
    if (numeros == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    printf("Digite os %d elementos do array:\n", tamanho);
    for (int i = 0; i < tamanho; i++) {
        printf("Elemento %d: ", i + 1);
        scanf("%d", &numeros[i]);
    }
    
    int maior, menor;
    encontrarMaiorMenor(numeros, tamanho, &maior, &menor);

    printf("\nO maior elemento do array: %d\n", maior);
    printf("O menor elemento do array: %d\n", menor);

    free(numeros);

    return 0;
}
