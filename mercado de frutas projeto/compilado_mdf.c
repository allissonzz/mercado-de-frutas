#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definicao da estrutura para Fruta
typedef struct {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
} Fruta;

// Funcao para cadastrar uma nova fruta
void cadastrarFruta(Fruta** lista, int* totalFrutas) {
    int i;
    Fruta* novaFruta = (Fruta*)malloc(sizeof(Fruta));
    if (novaFruta == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    printf("Digite o codigo da fruta: ");
    scanf("%d", &novaFruta->codigo);

    // Verificar se o codigo ja foi cadastrado
    for (i = 0; i < *totalFrutas; i++) {
        if (lista[i]->codigo == novaFruta->codigo) {
            printf("Erro: Codigo de fruta ja cadastrado!\n");
            free(novaFruta);
            return;
        }
    }

    printf("Digite o nome da fruta: ");
    scanf(" %[^\n]s", novaFruta->nome); // Leitura de string com espacos

    printf("Digite a quantidade de frutas em estoque: ");
    scanf("%d", &novaFruta->quantidade);

    printf("Digite o preco da fruta: ");
    scanf("%f", &novaFruta->preco);

    lista[*totalFrutas] = novaFruta; // Adiciona a lista
    (*totalFrutas)++; // Incrementa o total de frutas cadastradas

    printf("Fruta cadastrada com sucesso!\n");
}

// Funcao para listar todas as frutas cadastradas
void listarFrutas(Fruta** lista, int totalFrutas) {
    int i;

    if (totalFrutas == 0) {
        printf("Nenhuma fruta cadastrada.\n");
        return;
    }

    for (i = 0; i < totalFrutas; i++) {
        printf("Codigo: %d\n", lista[i]->codigo);
        printf("Nome: %s\n", lista[i]->nome);
        printf("Quantidade: %d\n", lista[i]->quantidade);
        printf("Preco: R$%.2f\n\n", lista[i]->preco);
    }
}

// Funcao para buscar uma fruta pelo codigo
void buscarFruta(Fruta** lista, int totalFrutas) {
    int i, codigo;

    printf("Digite o codigo da fruta a ser buscada: ");
    scanf("%d", &codigo);

    for (i = 0; i < totalFrutas; i++) {
        if (lista[i]->codigo == codigo) {
            printf("Fruta encontrada:\n");
            printf("Codigo: %d\n", lista[i]->codigo);
            printf("Nome: %s\n", lista[i]->nome);
            printf("Quantidade: %d\n", lista[i]->quantidade);
            printf("Preco: R$%.2f\n", lista[i]->preco);
            return;
        }
    }

    printf("Fruta com codigo %d nao encontrada.\n", codigo);
}

// Funcao para alterar os dados de uma fruta
void alterarFruta(Fruta** lista, int totalFrutas) {
    int i, codigo;

    printf("Digite o codigo da fruta a ser alterada: ");
    scanf("%d", &codigo);

    for (i = 0; i < totalFrutas; i++) {
        if (lista[i]->codigo == codigo) {
            printf("Digite o novo nome da fruta: ");
            scanf(" %[^\n]s", lista[i]->nome); // Leitura de string com espacos

            printf("Digite a nova quantidade em estoque: ");
            scanf("%d", &lista[i]->quantidade);

            printf("Digite o novo preco da fruta: ");
            scanf("%f", &lista[i]->preco);

            printf("Fruta alterada com sucesso!\n");
            return;
        }
    }

    printf("Fruta com codigo %d nao encontrada.\n", codigo);
}

// Funcao para excluir uma fruta (somente se a quantidade for 0)
void excluirFruta(Fruta** lista, int* totalFrutas) {
    int i, j, codigo;

    printf("Digite o codigo da fruta a ser excluida: ");
    scanf("%d", &codigo);

    for (i = 0; i < *totalFrutas; i++) {
        if (lista[i]->codigo == codigo) {
            if (lista[i]->quantidade > 0) {
                printf("Nao e possivel excluir. A fruta ainda possui estoque.\n");
                return;
            }

            free(lista[i]); // Libera a memoria da fruta

            // Move todas as frutas seguintes para ocupar o espaco
            for (j = i; j < *totalFrutas - 1; j++) {
                lista[j] = lista[j + 1];
            }

            (*totalFrutas)--; // Decrementa o total de frutas
            printf("Fruta excluida com sucesso!\n");
            return;
        }
    }

    printf("Fruta com codigo %d nao encontrada.\n", codigo);
}

// Funcao para realizar a venda de uma fruta
void venderFruta(Fruta** lista, int totalFrutas) {
    int i, codigo, quantidade;

    printf("Digite o codigo da fruta a ser vendida: ");
    scanf("%d", &codigo);

    for (i = 0; i < totalFrutas; i++) {
        if (lista[i]->codigo == codigo) {
            printf("Digite a quantidade a ser vendida: ");
            scanf("%d", &quantidade);

            if (quantidade > lista[i]->quantidade) {
                printf("Quantidade insuficiente em estoque.\n");
                return;
            }

            lista[i]->quantidade -= quantidade; // Atualiza o estoque
            printf("Venda realizada com sucesso! Quantidade restante: %d\n", lista[i]->quantidade);

            // Registro da venda no arquivo vendas.txt
            FILE* arquivo = fopen("vendas.txt", "a");
            if (arquivo != NULL) {
                fprintf(arquivo, "Codigo: %d, Nome: %s, Quantidade: %d, Preco unitario: R$%.2f\n",
                        lista[i]->codigo, lista[i]->nome, quantidade, lista[i]->preco);
                fclose(arquivo);
            } else {
                printf("Erro ao registrar a venda.\n");
            }
            return;
        }
    }

    printf("Fruta com codigo %d nao encontrada.\n", codigo);
}

int main() {
    Fruta* lista[100]; // Lista de frutas
    int totalFrutas = 0; // Contador de frutas cadastradas
    int opcao;
    int i; // Declaracao da variavel i para os loops

    do {
        printf("\nMenu:\n");
        printf("1 - Cadastrar fruta\n");
        printf("2 - Listar frutas\n");
        printf("3 - Buscar fruta\n");
        printf("4 - Alterar fruta\n");
        printf("5 - Excluir fruta\n");
        printf("6 - Vender fruta\n");
        printf("7 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarFruta(lista, &totalFrutas);
                break;
            case 2:
                listarFrutas(lista, totalFrutas);
                break;
            case 3:
                buscarFruta(lista, totalFrutas);
                break;
            case 4:
                alterarFruta(lista, totalFrutas);
                break;
            case 5:
                excluirFruta(lista, &totalFrutas);
                break;
            case 6:
                venderFruta(lista, totalFrutas);
                break;
            case 7:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 7);

    // Liberando memoria antes de sair
    for (i = 0; i < totalFrutas; i++) {
        free(lista[i]);
    }

    return 0;
}
