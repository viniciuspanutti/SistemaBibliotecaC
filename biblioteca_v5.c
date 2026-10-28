// Versao 5: funcoes alteram as structs originais por meio de ponteiros.
#include <stdio.h>
#include <string.h>

#define MAX_LIVROS 3
#define MAX_USUARIOS 3
#define TAM_TEXTO 121

typedef struct {
    int codigo;
    char descricao[TAM_TEXTO];
    int estoque;
} Livro;

typedef struct {
    int codigo;
    char dados[TAM_TEXTO];
    int codigoLivroEmprestado;
} Usuario;

int buscarLivro(Livro livros[], int qtd, int codigo) {
    for (int i = 0; i < qtd; i++) {
        if (livros[i].codigo == codigo) return i;
    }
    return -1;
}

int buscarUsuario(Usuario usuarios[], int qtd, int codigo) {
    for (int i = 0; i < qtd; i++) {
        if (usuarios[i].codigo == codigo) return i;
    }
    return -1;
}

void alterarEstoque(Livro *livro, int valor) {
    livro->estoque += valor;
}

void registrarEmprestimo(Usuario *usuario, int codigoLivro) {
    usuario->codigoLivroEmprestado = codigoLivro;
}

void encerrarEmprestimo(Usuario *usuario) {
    usuario->codigoLivroEmprestado = -1;
}

// Le uma linha de ate 120 caracteres, inclusive com espacos e acentos.
int lerTexto(char destino[]) {
    int caractere;
    if (fgets(destino, TAM_TEXTO, stdin) == NULL) return 0;
    size_t tamanho = strcspn(destino, "\n");
    if (destino[tamanho] == '\n') destino[tamanho] = '\0';
    else {
        int longo = 0;
        while ((caractere = getchar()) != '\n' && caractere != EOF) longo = 1;
        if (longo) return 0;
    }
    return tamanho > 0;
}

int main(void) {
    Livro livros[MAX_LIVROS];
    Usuario usuarios[MAX_USUARIOS];
    int qtdLivros = 0, qtdUsuarios = 0;

    while (qtdLivros < MAX_LIVROS) {
        Livro novo;
        int caractere;
        printf("Codigo do livro %d: ", qtdLivros + 1);
        if (scanf("%d", &novo.codigo) != 1) return 1;
        if (novo.codigo <= 0 || buscarLivro(livros, qtdLivros, novo.codigo) != -1) {
            printf("Codigo invalido ou repetido.\n");
            continue;
        }
        printf("Estoque: ");
        if (scanf("%d", &novo.estoque) != 1) return 1;
        if (novo.estoque < 0) {
            printf("O estoque nao pode ser negativo.\n");
            continue;
        }
        while ((caractere = getchar()) != '\n' && caractere != EOF) {}
        printf("Descricao (titulo; autor; ano; tema): ");
        if (!lerTexto(novo.descricao)) {
            printf("Descricao vazia ou maior que 120 caracteres.\n");
            continue;
        }
        livros[qtdLivros++] = novo;
    }

    while (qtdUsuarios < MAX_USUARIOS) {
        Usuario novo;
        int caractere;
        printf("Codigo do usuario %d: ", qtdUsuarios + 1);
        if (scanf("%d", &novo.codigo) != 1) return 1;
        if (novo.codigo <= 0 || buscarUsuario(usuarios, qtdUsuarios, novo.codigo) != -1) {
            printf("Codigo invalido ou repetido.\n");
            continue;
        }
        while ((caractere = getchar()) != '\n' && caractere != EOF) {}
        printf("Dados pessoais em uma linha: ");
        if (!lerTexto(novo.dados)) {
            printf("Dados vazios ou maiores que 120 caracteres.\n");
            continue;
        }
        novo.codigoLivroEmprestado = -1;
        usuarios[qtdUsuarios++] = novo;
    }

    printf("\nLivros cadastrados:\n");
    for (int i = 0; i < qtdLivros; i++) {
        printf("Codigo: %d | %s | Estoque: %d\n", livros[i].codigo,
               livros[i].descricao, livros[i].estoque);
    }
    printf("Usuarios cadastrados:\n");
    for (int i = 0; i < qtdUsuarios; i++) {
        printf("Codigo: %d | %s | Livro emprestado: %d\n", usuarios[i].codigo,
               usuarios[i].dados, usuarios[i].codigoLivroEmprestado);
    }

    int codigo;
    printf("Codigo do livro para busca: ");
    if (scanf("%d", &codigo) != 1) return 1;
    int posicao = buscarLivro(livros, qtdLivros, codigo);
    if (posicao == -1) printf("Livro nao encontrado.\n");
    else printf("Codigo: %d | %s | Estoque: %d\n", livros[posicao].codigo,
                livros[posicao].descricao, livros[posicao].estoque);
    // Nesta versao, uma operacao simples comprova que as alteracoes persistem.
    // As validacoes completas de emprestimo e devolucao entram na versao 6.
    int codigoUsuario, indiceLivro, indiceUsuario;
    printf("Codigo do livro para testar ponteiros: ");
    if (scanf("%d", &codigo) != 1) return 1;
    printf("Codigo do usuario: ");
    if (scanf("%d", &codigoUsuario) != 1) return 1;
    indiceLivro = buscarLivro(livros, qtdLivros, codigo);
    indiceUsuario = buscarUsuario(usuarios, qtdUsuarios, codigoUsuario);
    if (indiceLivro == -1 || indiceUsuario == -1) {
        printf("Livro ou usuario nao encontrado.\n");
        return 0;
    }
    if (livros[indiceLivro].estoque == 0) {
        printf("Livro sem estoque.\n");
        return 0;
    }

    alterarEstoque(&livros[indiceLivro], -1);
    registrarEmprestimo(&usuarios[indiceUsuario], codigo);
    printf("Apos emprestimo: estoque %d, livro do usuario %d\n",
           livros[indiceLivro].estoque,
           usuarios[indiceUsuario].codigoLivroEmprestado);
    alterarEstoque(&livros[indiceLivro], 1);
    encerrarEmprestimo(&usuarios[indiceUsuario]);
    printf("Apos devolucao: estoque %d, livro do usuario %d\n",
           livros[indiceLivro].estoque,
           usuarios[indiceUsuario].codigoLivroEmprestado);
    return 0;
}
