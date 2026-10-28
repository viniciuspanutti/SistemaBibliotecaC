# Sistema de Biblioteca em C

Projeto da disciplina de ALP, desenvolvido em seis versões. Cada arquivo pode ser
compilado e executado separadamente.

| Versão | Arquivo | Conteúdo principal |
| --- | --- | --- |
| 1 | `biblioteca_v1.c` | Vetores de códigos e estoques |
| 2 | `biblioteca_v2.c` | Descrições em strings |
| 3 | `biblioteca_v3.c` | Funções para cadastro, busca e cálculos |
| 4 | `biblioteca_v4.c` | Structs de livros e usuários |
| 5 | `biblioteca_v5.c` | Alterações por ponteiros |
| 6 | `biblioteca_v6.c` | Menu, empréstimos, devoluções e estoque |

## Compilar e executar

É necessário ter um compilador C, como o GCC. Para a versão final:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic biblioteca_v6.c -o biblioteca_v6
./biblioteca_v6
```

Para outra versão, substitua o número no nome do arquivo e do executável. As
versões 1 a 5 fazem uma sequência de operações; a versão 6 tem menu contínuo.

## Como usar a versão 6

O menu permite cadastrar até três títulos e três usuários, listar e buscar os
registros, emprestar e devolver livros. As opções 7 e 8 mostram usuários e a opção
9 ajusta o estoque disponível de um livro. Digite `0` para sair.

Cada código deve ser um inteiro positivo e único dentro do seu cadastro. Informe
descrição e dados pessoais em uma linha de até 120 caracteres. A descrição do
livro reúne título, autor, ano e tema, separados por ponto e vírgula. O estoque
inicial pode ser zero, mas nunca negativo.

Um usuário pode ter um livro por vez. O empréstimo reduz o estoque disponível e
registra o código do livro no usuário. A devolução faz o inverso. Se algum dado
for inválido, o programa informa o erro e volta ao menu sem alterar os registros.

Os cadastros existem apenas durante a execução; ao encerrar, os dados são perdidos.
