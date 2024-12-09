//Lara Fernandes e Victoria Valicelle
#include <stdio.h>
#include <stdlib.h>

void ImprimirVogais(char *vet, int pos, int n){
    if (pos == n){
        int contA = 0;
        int contEI = 0;
        for(int i = 0; i < n; i++){
            if(vet[i] == 'a')
                contA++;
            else
                contEI++;
        }
        if (contA > contEI){
            for (int j=0; j<n; j++){
                printf("%c ", vet[j]);
            }
            printf("\n");
        }
    } else {
        char vogais[] = {'a', 'e', 'i'};
        for (int k=0; k<3; k++){
            vet[pos] = vogais[k];
            ImprimirVogais(vet, pos+1, n);
        }
    }
}

void ImprimirPares(int *vet, int pos, int n){
    if (pos == n){
        int soma = 0;
        for(int i = 0; i < n; i++){
            soma = soma + vet[i];
        }
        if (soma % 2 == 0){
            for(int j=0; j<n; j++){
                printf("%d ", vet[j]);
            }
            printf("\n");
        }
    } else{
        int elementos[] = {15, 31, 55, 44};

        for (int k=0; k<4; k++){
            vet[pos] = elementos[k];
            ImprimirPares(vet, pos+1, n);
        }
    }
}

void ImprimirCentavos(int *vet, int pos, int valor, int *moedas, int n){
    if (valor == 0){
        for (int i=0; i<pos; i++){
            printf("%d ", vet[i]);
        }
        printf("\n");
    } else{
        for (int j=n; j<5; j++){
            if(moedas[j] <= valor){
                vet[pos] = moedas[j];
                ImprimirCentavos(vet, pos+1, valor - moedas[j], moedas, j);
            }
        }
    }
}


int main(void){
    int x;

    while (1) {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Combinacoes de {a, e, i} com numero de 'a' maior que 'e' + 'i'\n");
        printf("2 - Combinacoes de {15, 31, 55, 44} com soma par\n");
        printf("3 - Representar valor com moedas\n");
        printf("4 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &x);

        switch (x) {
            case 1: {
                int n;
                printf("Digite o tamanho das combinacoes: ");
                scanf("%d", &n);

                char vet[n];
                printf("Combinacoes validas de {a, e, i}:\n");
                ImprimirVogais(vet, 0, n);
                break;
            }
            case 2: {
                int n;
                printf("Digite o tamanho das combinacoes: ");
                scanf("%d", &n);

                int vet[n];
                printf("Combinacoes cuja soma eh par:\n");
                ImprimirPares(vet, 0, n);
                break;
            }
            case 3: {
                int valor;
                printf("Digite o valor em centavos: ");
                scanf("%d", &valor);

                int moedas[] = {50, 25, 10, 5, 1};
                int vet[100];
                printf("Maneiras de representar %d centavos:\n", valor);
                ImprimirCentavos(vet, 0, valor, moedas, 0);
                break;
            }
            case 4: {
                return 0;
            }
            default: {
                printf("Opcao invalida. Tente novamente.\n");
            }
        }
    }
}