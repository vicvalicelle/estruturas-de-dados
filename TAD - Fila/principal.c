#include <stdio.h>
#include "fila.h"

int main(void){
    int x;
    Fila f = Inicializar();

    while (1) {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Inserir um elemento na fila\n");
        printf("2 - Remover um elemento da fila\n");
        printf("3 - Imprimir fila\n");
        printf("4 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &x);

        switch (x) {
            case 1: {
                int n;
                printf("Digite o elemento a ser inserido: ");
                scanf("%d", &n);
                Inserir(f, n);
                break;
            }
            case 2: {
                int c;
                Remover(f, &c);
                printf("Removido: %d\n", c);
                break;
            }
            case 3: {
                Imprimir(f);
                break;
            }
            case 4: {
                Destruir(f);
                return 0;
            }
            default: {
                printf("Opcao invalida. Tente novamente.\n");
            }
        }
    }
}