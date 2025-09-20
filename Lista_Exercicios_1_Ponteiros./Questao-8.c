#include <stdio.h>

void calculadoraBasica(float n1, float n2, float *soma, float *sub, float *mult, float *div) {
    *soma = n1 + n2;
    *sub = n1 - n2;
    *mult = n1 * n2;
    if (n2 != 0) {
        *div = n1 / n2;
    } else {
        *div = 0; // Resultado indefinido para divisão por zero
    }
}

int main() {
    float num1, num2;
    float res_soma, res_sub, res_mult, res_div;

    printf("Digite o primeiro número: ");
    scanf("%f", &num1);
    printf("Digite o segundo número: ");
    scanf("%f", &num2);

    calculadoraBasica(num1, num2, &res_soma, &res_sub, &res_mult, &res_div);

    printf("\n--- Resultados para %.2f e %.2f ---\n", num1, num2);
    printf("Soma: %.2f\n", res_soma);
    printf("Subtração: %.2f\n", res_sub);
    printf("Multiplicação: %.2f\n", res_mult);

    if (num2 != 0) {
        printf("Divisão: %.2f\n", res_div);
    } else {
        printf("Divisão: Impossível dividir por zero.\n");
    }

    return 0;
}
