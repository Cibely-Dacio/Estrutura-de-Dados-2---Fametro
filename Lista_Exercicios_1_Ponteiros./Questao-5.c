#include <stdio.h>

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void copiarString(char *origem, char *destino) {
    while (*origem != '\0') {
        *destino = *origem;
        origem++;
        destino++;
    }
    *destino = '\0';
}

int main() {
    char str_origem[100]; // Define um tamanho máximo para a string de origem
    char str_destino[100];

    printf("Digite uma string para ser copiada: ");
  
    fgets(str_origem, sizeof(str_origem), stdin);
  
    for (int i = 0; str_origem[i] != '\0'; i++) {
        if (str_origem[i] == '\n') {
            str_origem[i] = '\0';
            break;
        }
    }

    copiarString(str_origem, str_destino);

    printf("\nString Original: %s\n", str_origem);
    printf("String Destino (copiada): %s\n", str_destino);

    return 0;
}
