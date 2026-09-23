#include <stdio.h>

#define MAX_TITULOS 3

int main(){
    int codigos[MAX_TITULOS] = {0};
    int estoques[MAX_TITULOS] = {0};

    int qtdTitulos = 0;
    int temp = 0;

    while (qtdTitulos < MAX_TITULOS){
        printf("\n\nDigite um novo codigo para um novo titulo.\n");
        scanf("%d", &temp);

        if (temp >= 0 || temp != 0){
            temp = codigos[MAX_TITULOS];
        }

        if(codigos[MAX_TITULOS] == codigos[i]){
            printf("Está repetido\n\n");
        }

        while (codigos[MAX_TITULOS] < 0){
            printf("\n\nDigite um novo codigo para um novo titulo.\n");
            scanf("%d", &temp);
        }

        codigos[MAX_TITULOS] = [];
    }


    // 8. Solicite a quantidade de exemplares em estoque desse título....

    int cadastros[];

    for (int i = 0; i < cadastros[i]; i++){

    }

}
