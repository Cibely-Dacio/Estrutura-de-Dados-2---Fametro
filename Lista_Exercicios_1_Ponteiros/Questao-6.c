#include <stdio.h>
#include <ctype.h> 

void contarVogaisConsoantes(char *str, int *vogais, int *consoantes) {
    *vogais = 0;
    *consoantes = 0;
    char c;

    while (*str != '\0') {
        c = tolower(*str);
        if (c >= 'a' && c <= 'z') {
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                (*vogais)++;
            } else {
                (*consoantes)++;
            }
        }
        str++;
    }
}

int main() {
    char texto[100];
    int num_vogais, num_consoantes;

    printf("Digite uma frase: ");
    fgets(texto, sizeof(texto), stdin);

    contarVogaisConsoantes(texto, &num_vogais, &num_consoantes);

    printf("\nNa string que você digitou, há:\n");
    printf("Número de vogais: %d\n", num_vogais);
    printf("Número de consoantes: %d\n", num_consoantes);

    return 0;
}
