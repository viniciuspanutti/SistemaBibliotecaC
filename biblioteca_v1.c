// Inclui a biblioteca padrao de entrada e saida, necessaria para usar printf e scanf.
#include <stdio.h>

// Define uma constante para limitar o sistema a, no maximo, tres titulos diferentes.
#define MAX_TITULOS 3

// A funcao main e o ponto em que a execucao do programa comeca.
int main(void) {
    // Cria o vetor de codigos com tres posicoes e inicializa todas elas com zero.
    int codigos[MAX_TITULOS] = {0};
    // Cria o vetor de estoques; cada posicao corresponde a mesma posicao de codigos.
    int estoques[MAX_TITULOS] = {0};
    // Guarda quantos titulos diferentes ja foram cadastrados; inicialmente, nenhum.
    int qtdTitulos = 0;

    // Repete o cadastro enquanto ainda houver uma posicao livre nos vetores.
    while (qtdTitulos < MAX_TITULOS) {
        // Armazena temporariamente o codigo digitado antes de coloca-lo no vetor.
        int codigo;
        // Funciona como indicador: 0 significa nao repetido e 1 significa repetido.
        int codigoRepetido;
        // Armazena temporariamente a quantidade em estoque digitada pelo usuario.
        int estoque;

        // Repete a leitura do codigo enquanto ele for negativo ou estiver repetido.
        do {
            // Assume inicialmente que o novo codigo ainda nao foi cadastrado.
            codigoRepetido = 0;

            // Mostra qual titulo esta sendo cadastrado; soma 1 porque a contagem comeca em zero.
            printf("Digite o codigo do titulo %d: ", qtdTitulos + 1);
            // Le um numero inteiro e armazena o valor digitado na variavel codigo.
            scanf("%d", &codigo);

            // Percorre somente as posicoes que ja foram preenchidas no vetor de codigos.
            for (int i = 0; i < qtdTitulos; i++) {
                // Compara o novo codigo com o codigo que esta na posicao atual do vetor.
                if (codigo == codigos[i]) {
                    // Registra que o codigo e repetido para impedir que ele seja aceito.
                    codigoRepetido = 1;
                } // Encerra a verificacao do codigo da posicao atual.
            } // Encerra o percurso pelos codigos que ja foram cadastrados.

            // Verifica primeiro se o codigo informado e negativo.
            if (codigo < 0) {
                // Explica que codigos negativos nao sao aceitos pelo sistema.
                printf("Codigo invalido. Digite um valor maior ou igual a zero.\n");
            // Se nao for negativo, verifica se o codigo ja estava cadastrado.
            } else if (codigoRepetido) {
                // Informa que o usuario precisa escolher um codigo diferente.
                printf("Codigo ja cadastrado. Digite outro codigo.\n");
            } // Encerra as verificacoes e mensagens de erro do codigo.
        // Volta ao inicio do bloco se pelo menos uma das duas condicoes for verdadeira.
        } while (codigo < 0 || codigoRepetido);

        // Repete a leitura do estoque ate que o usuario informe zero ou um valor positivo.
        do {
            // Solicita a quantidade de exemplares do titulo que esta sendo cadastrado.
            printf("Digite a quantidade em estoque: ");
            // Le um numero inteiro e armazena o valor digitado na variavel estoque.
            scanf("%d", &estoque);

            // Verifica se a quantidade digitada e negativa e, portanto, invalida.
            if (estoque < 0) {
                // Explica que o estoque deve ser zero ou um numero positivo.
                printf("Estoque invalido. Digite um valor maior ou igual a zero.\n");
            } // Encerra a verificacao do estoque negativo.
        // Volta ao inicio do bloco somente quando o estoque informado for negativo.
        } while (estoque < 0);

        // Guarda o codigo valido na proxima posicao livre do vetor de codigos.
        codigos[qtdTitulos] = codigo;
        // Guarda o estoque na mesma posicao, mantendo os dois vetores relacionados.
        estoques[qtdTitulos] = estoque;
        // Informa que mais um titulo foi cadastrado e avanca para a proxima posicao.
        qtdTitulos++;
    } // Encerra o cadastro depois que as tres posicoes dos vetores forem preenchidas.

    // Cria o acumulador que recebera a soma dos estoques de todos os titulos.
    int qtdExemplares = 0;

    // Exibe um cabecalho antes de listar os livros cadastrados.
    printf("\nLivros cadastrados:\n");
    // Percorre todas as posicoes preenchidas dos vetores para listar e somar os dados.
    for (int i = 0; i < qtdTitulos; i++) {
        // Mostra o codigo e o estoque relacionados pela mesma posicao i dos vetores.
        printf("Codigo: %d | Estoque: %d\n", codigos[i], estoques[i]);
        // Adiciona o estoque da posicao atual ao total acumulado de exemplares.
        qtdExemplares += estoques[i];
    } // Encerra a listagem depois de percorrer todos os titulos cadastrados.

    // Exibe a soma dos exemplares existentes em todos os estoques.
    printf("Total de exemplares: %d\n", qtdExemplares);

    // Armazena o codigo que o usuario deseja procurar no acervo.
    int codigoBusca;
    // Comeca com -1 para representar que nenhuma posicao foi encontrada ate agora.
    int posBusca = -1;

    // Solicita ao usuario o codigo que sera pesquisado.
    printf("\nDigite o codigo do titulo que deseja buscar: ");
    // Le o codigo procurado e o armazena na variavel codigoBusca.
    scanf("%d", &codigoBusca);

    // Percorre somente as posicoes validas e preenchidas do vetor de codigos.
    for (int i = 0; i < qtdTitulos; i++) {
        // Compara o codigo procurado com o codigo guardado na posicao atual.
        if (codigoBusca == codigos[i]) {
            // Guarda a posicao encontrada para acessar depois o estoque correspondente.
            posBusca = i;
        } // Encerra a comparacao com o codigo da posicao atual.
    } // Encerra a busca depois que todos os codigos cadastrados forem verificados.

    // Se a posicao ainda for -1, o codigo procurado nao existe no vetor.
    if (posBusca == -1) {
        // Informa que nenhum titulo possui o codigo pesquisado.
        printf("Titulo nao encontrado no acervo.\n");
    // So acessa o vetor de estoques depois de confirmar que posBusca e uma posicao valida.
    } else if (estoques[posBusca] == 0) {
        // Informa que o titulo existe, mas nao possui exemplares disponiveis.
        printf("Titulo encontrado, mas temporariamente indisponivel.\n");
    // Este bloco e executado quando o titulo existe e seu estoque e maior que zero.
    } else {
        // Informa que o titulo esta disponivel e mostra sua quantidade em estoque.
        printf("Titulo disponivel. Exemplares em estoque: %d\n", estoques[posBusca]);
    } // Encerra a decisao sobre o resultado da busca e a disponibilidade do titulo.

    // Retorna zero ao sistema operacional para indicar que o programa terminou corretamente.
    return 0;
} // Encerra a funcao main e, consequentemente, o programa.
