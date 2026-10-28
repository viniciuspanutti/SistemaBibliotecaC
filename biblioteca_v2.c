// Versao 2: cada titulo recebe uma descricao em uma unica linha.
#include <stdio.h>
#include <string.h>

#define MAX_TITULOS 3
#define TAM_TEXTO 121

int main(void) {
    int codigos[MAX_TITULOS];
    int estoques[MAX_TITULOS];
    char descricao1[TAM_TEXTO], descricao2[TAM_TEXTO], descricao3[TAM_TEXTO];
    int qtdTitulos = 0;

    while (qtdTitulos < MAX_TITULOS) {
        int codigo, estoque, repetido = 0;
        char *descricao;
        int caractere;

        printf("Codigo do livro %d: ", qtdTitulos + 1);
        if (scanf("%d", &codigo) != 1) return 1;
        for (int i = 0; i < qtdTitulos; i++) {
            if (codigos[i] == codigo) repetido = 1;
        }
        if (codigo <= 0 || repetido) {
            printf("Codigo invalido ou repetido.\n");
            continue;
        }

        printf("Estoque: ");
        if (scanf("%d", &estoque) != 1) return 1;
        if (estoque < 0) {
            printf("O estoque nao pode ser negativo.\n");
            continue;
        }

        // Retira o restante da linha antes de ler uma descricao com espacos.
        while ((caractere = getchar()) != '\n' && caractere != EOF) {}
        if (qtdTitulos == 0) descricao = descricao1;
        else if (qtdTitulos == 1) descricao = descricao2;
        else descricao = descricao3;

        printf("Descricao (titulo; autor; ano; tema): ");
        if (fgets(descricao, TAM_TEXTO, stdin) == NULL) return 1;
        size_t tamanho = strcspn(descricao, "\n");
        if (descricao[tamanho] == '\n') {
            descricao[tamanho] = '\0';
        } else {
            int longo = 0;
            while ((caractere = getchar()) != '\n' && caractere != EOF) longo = 1;
            if (longo) {
                printf("A descricao deve ter no maximo 120 caracteres.\n");
                continue;
            }
        }
        if (tamanho == 0) {
            printf("A descricao nao pode ficar vazia.\n");
            continue;
        }

        codigos[qtdTitulos] = codigo;
        estoques[qtdTitulos] = estoque;
        qtdTitulos++;
    }

    int total = 0;
    printf("\nLivros cadastrados:\n");
    for (int i = 0; i < qtdTitulos; i++) {
        const char *descricao;
        if (i == 0) descricao = descricao1;
        else if (i == 1) descricao = descricao2;
        else descricao = descricao3;
        printf("Codigo: %d | Estoque: %d | %s\n", codigos[i], estoques[i], descricao);
        total += estoques[i];
    }
    printf("Total de exemplares: %d\n", total);

    int codigoBusca, posicao = -1;
    printf("Codigo para busca: ");
    if (scanf("%d", &codigoBusca) != 1) return 1;
    for (int i = 0; i < qtdTitulos; i++) {
        if (codigos[i] == codigoBusca) posicao = i;
    }
    if (posicao == -1) {
        printf("Livro nao encontrado.\n");
    } else {
        const char *descricao;
        if (posicao == 0) descricao = descricao1;
        else if (posicao == 1) descricao = descricao2;
        else descricao = descricao3;
        printf("%s | Estoque: %d\n", descricao, estoques[posicao]);
        printf("%s\n", estoques[posicao] > 0 ? "Disponivel" : "Indisponivel");
    }
    return 0;
}
