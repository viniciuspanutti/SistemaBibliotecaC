// Versao 3: cadastro, listagem, busca e calculos separados em funcoes.
#include <stdio.h>
#include <string.h>

#define MAX_TITULOS 3
#define TAM_TEXTO 121

int buscarTitulo(int codigos[], int qtdTitulos, int codigoBuscado);
int cadastrarTitulo(int codigos[], int estoques[], char descricao1[],
                   char descricao2[], char descricao3[], int qtdTitulos);
void listarTitulos(int codigos[], int estoques[], char descricao1[],
                  char descricao2[], char descricao3[], int qtdTitulos);
int calcularQtdExemplares(int estoques[], int qtdTitulos);
int disponibilidadeTitulo(int qtdEstoque);

int main(void) {
    int codigos[MAX_TITULOS], estoques[MAX_TITULOS];
    char descricao1[TAM_TEXTO], descricao2[TAM_TEXTO], descricao3[TAM_TEXTO];
    int qtdTitulos = 0;

    while (qtdTitulos < MAX_TITULOS) {
        qtdTitulos = cadastrarTitulo(codigos, estoques, descricao1, descricao2,
                                    descricao3, qtdTitulos);
        if (qtdTitulos == -1) return 1;
    }

    listarTitulos(codigos, estoques, descricao1, descricao2, descricao3, qtdTitulos);
    int codigoBuscado;
    printf("Codigo para busca: ");
    if (scanf("%d", &codigoBuscado) != 1) return 1;
    int posicao = buscarTitulo(codigos, qtdTitulos, codigoBuscado);
    if (posicao == -1) {
        printf("Livro nao encontrado.\n");
    } else {
        char *descricao = posicao == 0 ? descricao1 :
                          posicao == 1 ? descricao2 : descricao3;
        printf("Codigo: %d | %s | Estoque: %d\n", codigos[posicao],
               descricao, estoques[posicao]);
        printf("%s\n", disponibilidadeTitulo(estoques[posicao]) ?
               "Disponivel" : "Indisponivel");
    }
    printf("Total de exemplares: %d\n",
           calcularQtdExemplares(estoques, qtdTitulos));
    return 0;
}

int buscarTitulo(int codigos[], int qtdTitulos, int codigoBuscado) {
    for (int i = 0; i < qtdTitulos; i++) {
        if (codigos[i] == codigoBuscado) return i;
    }
    return -1;
}

int cadastrarTitulo(int codigos[], int estoques[], char descricao1[],
                   char descricao2[], char descricao3[], int qtdTitulos) {
    int codigo, estoque, caractere;
    char *descricao = qtdTitulos == 0 ? descricao1 :
                      qtdTitulos == 1 ? descricao2 : descricao3;

    printf("Codigo do livro %d: ", qtdTitulos + 1);
    if (scanf("%d", &codigo) != 1) return -1;
    if (codigo <= 0 || buscarTitulo(codigos, qtdTitulos, codigo) != -1) {
        printf("Codigo invalido ou repetido.\n");
        return qtdTitulos;
    }
    printf("Estoque: ");
    if (scanf("%d", &estoque) != 1) return -1;
    if (estoque < 0) {
        printf("O estoque nao pode ser negativo.\n");
        return qtdTitulos;
    }
    while ((caractere = getchar()) != '\n' && caractere != EOF) {}
    printf("Descricao (titulo; autor; ano; tema): ");
    if (fgets(descricao, TAM_TEXTO, stdin) == NULL) return -1;
    size_t tamanho = strcspn(descricao, "\n");
    if (descricao[tamanho] == '\n') {
        descricao[tamanho] = '\0';
    } else {
        int longo = 0;
        while ((caractere = getchar()) != '\n' && caractere != EOF) longo = 1;
        if (longo) {
            printf("A descricao deve ter no maximo 120 caracteres.\n");
            return qtdTitulos;
        }
    }
    if (tamanho == 0) {
        printf("A descricao nao pode ficar vazia.\n");
        return qtdTitulos;
    }
    codigos[qtdTitulos] = codigo;
    estoques[qtdTitulos] = estoque;
    return qtdTitulos + 1;
}

void listarTitulos(int codigos[], int estoques[], char descricao1[],
                  char descricao2[], char descricao3[], int qtdTitulos) {
    printf("\nLivros cadastrados:\n");
    for (int i = 0; i < qtdTitulos; i++) {
        char *descricao = i == 0 ? descricao1 : i == 1 ? descricao2 : descricao3;
        printf("Codigo: %d | Estoque: %d | %s\n", codigos[i], estoques[i], descricao);
    }
}

int calcularQtdExemplares(int estoques[], int qtdTitulos) {
    int total = 0;
    for (int i = 0; i < qtdTitulos; i++) total += estoques[i];
    return total;
}

int disponibilidadeTitulo(int qtdEstoque) {
    return qtdEstoque > 0;
}
