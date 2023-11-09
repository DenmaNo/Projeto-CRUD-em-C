#include <stdio.h>
//Segunda biblioteca necessária para comandos com o cmd, como o void "limparTela".
#include <stdlib.h>

//Usado depois de algum seguimento do código, deixando organizado. Por si só, avança apenas se digitar enter.
//Útil em alguns casos para que terminam sem um "printf".
void prosseguir() {
    printf("\nPressione enter para voltar ao menu...");
    getchar();
}

//Usado geralmente depois de um Scanf, por o scanf tem problemas ao ler coisas com \n, deixando o código bugado. 
//O scanf as vezes lê caracteres que não são necessários, que não existem, bugando assim a variavel.
void debugScan() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Retira as informações padrões que aparecem no cmd, como diretório... Além de retirar informações do antigo menu, porém sem perder nenhum dado.
void limparTela() {
#ifdef _WIN32
    system("cls");
#endif
}

//Informações do cadastro ondem serão guardadas, é possivel adicionar mais informações caso queira.
struct cadastro {
    int idade;
    char nome[40];
    char endereco[50];
    char genero[15];
};

//Função para editar cadastro, feita em forma de função para não poluir o case 3, onde deus espaço a códigos mais complexos.
void editarCadastro(struct cadastro* pessoa) {
    limparTela();
    printf("===========================================\n");
    printf("Digite o novo nome: ");
    fgets(pessoa->nome, sizeof(pessoa->nome), stdin);
    printf("Digite a nova idade: ");
    scanf("%d", &pessoa->idade);
    debugScan(); // Alteração da chamada para a função debugScan
    printf("Digite o novo endereco: ");
    fgets(pessoa->endereco, sizeof(pessoa->endereco), stdin);
    printf("Digite o novo genero: ");
    fgets(pessoa->genero, sizeof(pessoa->genero), stdin);
    printf("Cadastro editado com sucesso!\n");
    prosseguir();
}

//Função de listar as informações, feita função pois ela é chamada no case 2, 3 e 4, e ter que repetir estes códigos várias vezes é desnecessário.
//Sem falar também que organizei de forma a ficar mais bonito no cmd, com "="
//Função simples de for pra ir dando continuadade da ordem de cadastros, ex: cad 1, cad 2, cad 3... De forma organizada.
void listarCadastros(struct cadastro* pessoas, int numCadastros) {
    for (int i = 0; i < numCadastros; i++) {
        printf("===========================================\n");
        printf("Cadastro %d:\n", i + 1);
        printf("Nome: %s", pessoas[i].nome);
        printf("Idade: %d\n", pessoas[i].idade);
        printf("Endereco: %s", pessoas[i].endereco);
        printf("Genero: %s", pessoas[i].genero);
    }
}

int main() {
    int opcao;
    int numCadastros = 0;
    struct cadastro pessoas[100];

    //  Utilizei um while porque o código pode ficar em loop até a pessoa decidir sair do código, que no caso é o número 6.
    while (1) {
        limparTela();
        // Menu principal e "bem vindo".
        printf("===========================================\n");
        printf("Bem-vindo ao menu de cadastros\n");
        printf("===========================================\n");

        printf("\nMenu de Cadastros:\n");
        printf("1. Novo cadastro\n");
        printf("2. Visualizar cadastros\n");
        printf("3. Editar cadastros\n");
        printf("4. Deletar cadastros\n");
        printf("5. Sobre o programa\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        debugScan(); // Alteração da chamada para a função debugScan
        limparTela();

        switch (opcao) {
            case 1:
                // Adicionar novo cadastro, limitando a um máximo de 100, invalidando caso insira errado.
                if (numCadastros < 100) {
                    printf("===========================================\n");
                    printf("Digite o nome: ");
                    fgets(pessoas[numCadastros].nome, sizeof(pessoas[numCadastros].nome), stdin);
                    printf("Digite a idade: ");
                    scanf("%d", &pessoas[numCadastros].idade);
                    debugScan(); // Alteração da chamada para a função debugScan
                    printf("Digite o endereco: ");
                    fgets(pessoas[numCadastros].endereco, sizeof(pessoas[numCadastros].endereco), stdin);
                    printf("Digite o genero: ");
                    fgets(pessoas[numCadastros].genero, sizeof(pessoas[numCadastros].genero), stdin);
                    // Adciona ao contador de cadastros após a adição bem-sucedida.
                    numCadastros++;
                    prosseguir();
                } else {
                    // Nega o cadastro caso tenha atingido o limite, definido no "numCadastros".
                    printf("Limite de cadastros atingido!\n");
                    prosseguir();
                }
                break;
            case 2:
                // Listar cadastros caso exista algum, definido com o "if", caso não haja, invalida.
                if (numCadastros > 0) {
                    listarCadastros(pessoas, numCadastros);
                    printf("===========================================\n");
                } else {
                    printf("Nenhum cadastro encontrado.\n");
                }
                    prosseguir();
                break;
            case 3:
                //Editar cadastros, mostrando antes todos cadastros registrados.
                //Edita baseado na sequência dos cadastros.
                if (numCadastros > 0) {
                    int cadastroParaEditar;
                    listarCadastros(pessoas, numCadastros);
                    printf("===========================================\n");
                    printf("Digite o numero do cadastro a ser editado: ");
                    scanf("%d", &cadastroParaEditar);
                    debugScan(); // Alteração da chamada para a função debugScan

                    if (cadastroParaEditar >= 1 && cadastroParaEditar <= numCadastros) {
                        editarCadastro(&pessoas[cadastroParaEditar - 1]);
                    } else {
                        printf("Numero de cadastro invalido.\n");
                        prosseguir();
                    }
                } else {
                    printf("Nenhum cadastro para editar.\n");
                    prosseguir();
                }
                break;
            case 4:
                // Deletar cadastros baseado em número sequencial, também mostrando antes os disponiveis.
                if (numCadastros > 0) {
                    int cadastroParaDeletar;
                    listarCadastros(pessoas, numCadastros);
                    printf("===========================================\n");
                    printf("Digite o numero do cadastro a ser deletado: ");
                    scanf("%d", &cadastroParaDeletar);
                    debugScan();

                    // Validação de cadastros com opção condiconal, valida o número do usuario começando do 1.
                    if (cadastroParaDeletar >= 1 && cadastroParaDeletar <= numCadastros) {
                        for (int i = cadastroParaDeletar - 1; i < numCadastros - 1; i++) {
                            pessoas[i] = pessoas[i + 1];
                        }
                        numCadastros--;
                        printf("Cadastro deletado com sucesso!\n");
                        prosseguir();
                    } else {
                        printf("Numero de cadastro invalido. Tente novamente.\n");
                        prosseguir();
                    }
                } else {
                    // Resposta caso não haja cadastros.
                    printf("Nenhum cadastro para deletar.\n");
                    prosseguir();
                }
                break;
            case 5:
                //Comentário para explicar sobre o software e suas funcoes.
                printf("Este software foi projetado como inspiracao de um CRUD, visando funcionar como um cadastro\n"
                "geral de informacoes, podendo editar, deletar, criar e visualizar informacoes em cima dos cadastros.\n");
                prosseguir();
                break;
            case 6:
                //Sair do programa, porém sem fechar o CMD.
                printf("Saindo do programa... \n");
                return 0;
                break;
            default:
                printf("===========================================\n");
                printf("Opcao invalida.\n");
                prosseguir();
                break;
        }
    }
    return 0;
}
