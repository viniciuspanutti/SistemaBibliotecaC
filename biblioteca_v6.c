// Versao 6: integra cadastro, consultas, emprestimos e devolucoes.
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
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

// Retorna 1 para entrada valida, 0 para entrada invalida e -1 para fim da entrada.
int lerInteiro(const char *mensagem, int *valor) {
    char linha[256], *fim;
    long numero;
    int caractere;

    printf("%s", mensagem);
    if (fgets(linha, sizeof(linha), stdin) == NULL) return -1;
    if (strchr(linha, '\n') == NULL && !feof(stdin)) {
        while ((caractere = getchar()) != '\n' && caractere != EOF) {}
        return 0;
    }
    errno = 0;
    numero = strtol(linha, &fim, 10);
    if (fim == linha || errno == ERANGE || numero < INT_MIN || numero > INT_MAX) return 0;
    while (*fim == ' ' || *fim == '\t' || *fim == '\n') fim++;
    if (*fim != '\0') return 0;
    *valor = (int)numero;
    return 1;
}

int lerTexto(const char *mensagem, char destino[]) {
    char linha[256];
    int caractere, temConteudo = 0;
    size_t tamanho;

    printf("%s", mensagem);
    if (fgets(linha, sizeof(linha), stdin) == NULL) return -1;
    tamanho = strcspn(linha, "\n");
    if (linha[tamanho] != '\n' && !feof(stdin)) {
        while ((caractere = getchar()) != '\n' && caractere != EOF) {}
        return 0;
    }
    if (tamanho == 0 || tamanho >= TAM_TEXTO) return 0;
    for (size_t i = 0; i < tamanho; i++) {
        if (linha[i] != ' ' && linha[i] != '\t') temConteudo = 1;
    }
    if (!temConteudo) return 0;
    linha[tamanho] = '\0';
    strcpy(destino, linha);
    return 1;
}

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

void cadastrarLivro(Livro livros[], int *qtdLivros) {
    Livro novo;
    if (*qtdLivros == MAX_LIVROS) {
        printf("Limite de tres livros atingido.\n");
        return;
    }
    if (lerInteiro("Codigo do livro: ", &novo.codigo) != 1) {
        printf("Codigo invalido.\n");
        return;
    }
    if (novo.codigo <= 0 || buscarLivro(livros, *qtdLivros, novo.codigo) != -1) {
        printf("O codigo deve ser positivo e ainda nao cadastrado.\n");
        return;
    }
    if (lerInteiro("Exemplares em estoque: ", &novo.estoque) != 1 || novo.estoque < 0) {
        printf("O estoque deve ser zero ou maior.\n");
        return;
    }
    if (lerTexto("Descricao (titulo; autor; ano; tema): ", novo.descricao) != 1) {
        printf("Descricao obrigatoria, com ate 120 caracteres.\n");
        return;
    }
    // O cadastro so e gravado depois de todos os campos serem validados.
    livros[*qtdLivros] = novo;
    (*qtdLivros)++;
    printf("Livro cadastrado.\n");
}

void cadastrarUsuario(Usuario usuarios[], int *qtdUsuarios) {
    Usuario novo;
    if (*qtdUsuarios == MAX_USUARIOS) {
        printf("Limite de tres usuarios atingido.\n");
        return;
    }
    if (lerInteiro("Codigo do usuario: ", &novo.codigo) != 1) {
        printf("Codigo invalido.\n");
        return;
    }
    if (novo.codigo <= 0 || buscarUsuario(usuarios, *qtdUsuarios, novo.codigo) != -1) {
        printf("O codigo deve ser positivo e ainda nao cadastrado.\n");
        return;
    }
    if (lerTexto("Dados pessoais em uma linha: ", novo.dados) != 1) {
        printf("Dados obrigatorios, com ate 120 caracteres.\n");
        return;
    }
    novo.codigoLivroEmprestado = -1;
    usuarios[*qtdUsuarios] = novo;
    (*qtdUsuarios)++;
    printf("Usuario cadastrado.\n");
}

void listarLivros(Livro livros[], int qtdLivros) {
    if (qtdLivros == 0) printf("Nenhum livro cadastrado.\n");
    for (int i = 0; i < qtdLivros; i++) {
        printf("Codigo: %d | Estoque: %d | %s\n", livros[i].codigo,
               livros[i].estoque, livros[i].descricao);
    }
}

void listarUsuarios(Usuario usuarios[], int qtdUsuarios) {
    if (qtdUsuarios == 0) printf("Nenhum usuario cadastrado.\n");
    for (int i = 0; i < qtdUsuarios; i++) {
        printf("Codigo: %d | %s | Livro emprestado: %d\n",
               usuarios[i].codigo, usuarios[i].dados,
               usuarios[i].codigoLivroEmprestado);
    }
}

int emprestarLivro(Livro *livro, Usuario *usuario) {
    if (livro->estoque <= 0 || usuario->codigoLivroEmprestado != -1) return 0;
    livro->estoque--;
    usuario->codigoLivroEmprestado = livro->codigo;
    return 1;
}

int devolverLivro(Livro *livro, Usuario *usuario) {
    if (usuario->codigoLivroEmprestado != livro->codigo || livro->estoque == INT_MAX) return 0;
    livro->estoque++;
    usuario->codigoLivroEmprestado = -1;
    return 1;
}

void consultarLivro(Livro livros[], int qtdLivros) {
    int codigo, posicao;
    if (lerInteiro("Codigo do livro para busca: ", &codigo) != 1) {
        printf("Codigo invalido.\n");
        return;
    }
    posicao = buscarLivro(livros, qtdLivros, codigo);
    if (posicao == -1) printf("Livro nao encontrado.\n");
    else printf("Codigo: %d | Estoque: %d | %s | %s\n", livros[posicao].codigo,
                livros[posicao].estoque, livros[posicao].descricao,
                livros[posicao].estoque > 0 ? "Disponivel" : "Indisponivel");
}

void consultarUsuario(Usuario usuarios[], int qtdUsuarios) {
    int codigo, posicao;
    if (lerInteiro("Codigo do usuario para busca: ", &codigo) != 1) {
        printf("Codigo invalido.\n");
        return;
    }
    posicao = buscarUsuario(usuarios, qtdUsuarios, codigo);
    if (posicao == -1) printf("Usuario nao encontrado.\n");
    else printf("Codigo: %d | %s | Livro emprestado: %d\n",
                usuarios[posicao].codigo, usuarios[posicao].dados,
                usuarios[posicao].codigoLivroEmprestado);
}

void realizarEmprestimo(Livro livros[], int qtdLivros,
                       Usuario usuarios[], int qtdUsuarios) {
    int codigoLivro, codigoUsuario;
    if (lerInteiro("Codigo do livro: ", &codigoLivro) != 1 ||
        lerInteiro("Codigo do usuario: ", &codigoUsuario) != 1) {
        printf("Codigo invalido.\n");
        return;
    }
    int indiceLivro = buscarLivro(livros, qtdLivros, codigoLivro);
    int indiceUsuario = buscarUsuario(usuarios, qtdUsuarios, codigoUsuario);
    if (indiceLivro == -1 || indiceUsuario == -1) {
        printf("Livro ou usuario nao encontrado.\n");
        return;
    }
    if (emprestarLivro(&livros[indiceLivro], &usuarios[indiceUsuario]))
        printf("Emprestimo realizado.\n");
    else printf("Emprestimo recusado: livro sem estoque ou usuario ja possui livro.\n");
}

void realizarDevolucao(Livro livros[], int qtdLivros,
                      Usuario usuarios[], int qtdUsuarios) {
    int codigoLivro, codigoUsuario;
    if (lerInteiro("Codigo do livro: ", &codigoLivro) != 1 ||
        lerInteiro("Codigo do usuario: ", &codigoUsuario) != 1) {
        printf("Codigo invalido.\n");
        return;
    }
    int indiceLivro = buscarLivro(livros, qtdLivros, codigoLivro);
    int indiceUsuario = buscarUsuario(usuarios, qtdUsuarios, codigoUsuario);
    if (indiceLivro == -1 || indiceUsuario == -1) {
        printf("Livro ou usuario nao encontrado.\n");
        return;
    }
    if (devolverLivro(&livros[indiceLivro], &usuarios[indiceUsuario]))
        printf("Devolucao realizada.\n");
    else printf("Devolucao recusada: o usuario nao possui esse livro.\n");
}

void atualizarEstoque(Livro livros[], int qtdLivros) {
    int codigo, novoEstoque;
    if (lerInteiro("Codigo do livro: ", &codigo) != 1) {
        printf("Codigo invalido.\n");
        return;
    }
    int posicao = buscarLivro(livros, qtdLivros, codigo);
    if (posicao == -1) {
        printf("Livro nao encontrado.\n");
        return;
    }
    if (lerInteiro("Novo estoque disponivel: ", &novoEstoque) != 1 || novoEstoque < 0) {
        printf("O estoque deve ser zero ou maior.\n");
        return;
    }
    livros[posicao].estoque = novoEstoque;
    printf("Estoque atualizado.\n");
}

int main(void) {
    Livro livros[MAX_LIVROS];
    Usuario usuarios[MAX_USUARIOS];
    int qtdLivros = 0, qtdUsuarios = 0, opcao, leitura;

    while (1) {
        printf("\n1 - Cadastrar livro\n2 - Cadastrar usuario\n"
               "3 - Listar livros\n4 - Buscar livro\n5 - Emprestar livro\n"
               "6 - Devolver livro\n7 - Buscar usuario\n8 - Listar usuarios\n"
               "9 - Atualizar estoque\n0 - Sair\n");
        leitura = lerInteiro("Opcao: ", &opcao);
        if (leitura == -1) break;
        if (leitura == 0) {
            printf("Opcao invalida.\n");
            continue;
        }
        switch (opcao) {
            case 0: return 0;
            case 1: cadastrarLivro(livros, &qtdLivros); break;
            case 2: cadastrarUsuario(usuarios, &qtdUsuarios); break;
            case 3: listarLivros(livros, qtdLivros); break;
            case 4: consultarLivro(livros, qtdLivros); break;
            case 5: realizarEmprestimo(livros, qtdLivros, usuarios, qtdUsuarios); break;
            case 6: realizarDevolucao(livros, qtdLivros, usuarios, qtdUsuarios); break;
            case 7: consultarUsuario(usuarios, qtdUsuarios); break;
            case 8: listarUsuarios(usuarios, qtdUsuarios); break;
            case 9: atualizarEstoque(livros, qtdLivros); break;
            default: printf("Opcao invalida.\n");
        }
    }
    return 0;
}
