#include <stdio.h>
#include <string.h>

void inverterString(char *str) {
    str[strcspn(str, "\n")] = 0;

    int tamanho = strlen(str);
    char *inicio = str;
    char *fim = str + tamanho - 1;
    char temp;

    while (inicio < fim) {
        temp = *inicio;
        *inicio = *fim;
        *fim = temp;
        inicio++;
        fim--;
    }
}

int main() {
    char minha_string[100];
    
    printf("Digite uma string para inverter: ");
    fgets(minha_string, sizeof(minha_string), stdin);
    
    printf("\nString Original: %s", minha_string);
    
    inverterString(minha_string);
    
    printf("String Invertida: %s\n", minha_string);

    return 0;
}
