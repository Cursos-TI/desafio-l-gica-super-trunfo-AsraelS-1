#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar os dados da carta
typedef struct {
    char estado;
    char codigo[4];
    char nomeCidade[50];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
} CartaSuperTrunfo;

// Função para limpar o buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para ler os dados de uma carta
void lerCarta(CartaSuperTrunfo *carta, int numero) {
    printf("\nDigite os dados da Carta %d:\n", numero);
    printf("Estado (A-H): ");
    scanf(" %c", &carta->estado);
    limparBuffer();
    printf("Codigo da Carta (ex: A01): ");
    scanf(" %3s", carta->codigo);
    limparBuffer();
    printf("Nome da Cidade: ");
    fgets(carta->nomeCidade, sizeof(carta->nomeCidade), stdin);
    carta->nomeCidade[strcspn(carta->nomeCidade, "\n")] = 0; // Remover nova linha
    printf("Populacao: ");
    scanf(" %d", &carta->populacao);
    printf("Area (em km2): ");
    scanf(" %f", &carta->area);
    printf("PIB (em bilhoes de reais): ");
    scanf(" %f", &carta->pib);
    printf("Numero de Pontos Turisticos: ");
    scanf(" %d", &carta->pontosTuristicos);
}

// Função para exibir os dados de uma carta
void exibirCarta(const CartaSuperTrunfo *carta, int numero) {
    printf("\nCarta %d:\n", numero);
    printf("Estado: %c\n", carta->estado);
    printf("Codigo: %s\n", carta->codigo);
    printf("Nome da Cidade: %s\n", carta->nomeCidade);
    printf("Populacao: %d\n", carta->populacao);
    printf("Area: %.2f km2\n", carta->area);
    printf("PIB: %.2f bilhoes de reais\n", carta->pib);
    printf("Numero de Pontos Turisticos: %d\n", carta->pontosTuristicos);
    printf("Densidade Populacional: %.2f hab/km2\n", carta->area > 0 ? carta->populacao / carta->area : 0);
    printf("PIB per capita: %.2f mil reais\n", carta->populacao > 0 ? (carta->pib * 1000) / carta->populacao : 0);
}

// Função para selecionar um atributo de forma dinâmica
int escolherAtributo(int atributoEscolhido) {
    int atributo;
    do {
        printf("\nEscolha um atributo para comparar:\n");
        printf("1 - Populacao\n2 - Area\n3 - PIB\n4 - Densidade Populacional\n5 - PIB per capita\n");
        printf("Digite o numero do atributo: ");
        if (scanf("%d", &atributo) != 1) {
            limparBuffer();
            printf("Entrada invalida! Tente novamente.\n");
            continue;
        }
        if (atributo >= 1 && atributo <= 5 && atributo != atributoEscolhido) break;
        printf("Opcao invalida ou ja escolhida! Escolha um numero entre 1 e 5 que ainda nao foi usado.\n");
    } while (1);
    return atributo;
}

// Função para obter o valor de um atributo específico
float obterValorAtributo(const CartaSuperTrunfo *carta, int atributo) {
    switch (atributo) {
        case 1: return carta->populacao;
        case 2: return carta->area;
        case 3: return carta->pib;
        case 4: return carta->area > 0 ? carta->populacao / carta->area : 0;
        case 5: return carta->populacao > 0 ? (carta->pib * 1000) / carta->populacao : 0;
        default: return 0;
    }
}

// Função para comparar cartas com base nos dois atributos escolhidos
void compararCartas(const CartaSuperTrunfo *carta1, const CartaSuperTrunfo *carta2, int atributo1, int atributo2) {
    float valor1A = obterValorAtributo(carta1, atributo1);
    float valor2A = obterValorAtributo(carta2, atributo1);
    float valor1B = obterValorAtributo(carta1, atributo2);
    float valor2B = obterValorAtributo(carta2, atributo2);

    float soma1 = valor1A + valor1B;
    float soma2 = valor2A + valor2B;

    printf("\nComparacao de cartas:\n");
    printf("Carta 1 - %s (%c): %.2f (Atributo 1) + %.2f (Atributo 2) = %.2f\n",
           carta1->nomeCidade, carta1->estado, valor1A, valor1B, soma1);
    printf("Carta 2 - %s (%c): %.2f (Atributo 1) + %.2f (Atributo 2) = %.2f\n",
           carta2->nomeCidade, carta2->estado, valor2A, valor2B, soma2);

    if (soma1 > soma2) {
        printf("Resultado: Carta 1 (%s) venceu!\n", carta1->nomeCidade);
    } else if (soma1 < soma2) {
        printf("Resultado: Carta 2 (%s) venceu!\n", carta2->nomeCidade);
    } else {
        printf("Resultado: Empate!\n");
    }
}

int main() {
    CartaSuperTrunfo carta1, carta2;
    int atributo1, atributo2;

    // Leitura dos dados das cartas
    lerCarta(&carta1, 1);
    lerCarta(&carta2, 2);

    // Exibição dos dados das cartas
    exibirCarta(&carta1, 1);
    exibirCarta(&carta2, 2);

    // Escolha de dois atributos diferentes para a comparação
    atributo1 = escolherAtributo(0);
    atributo2 = escolherAtributo(atributo1);

    // Comparação das cartas
    compararCartas(&carta1, &carta2, atributo1, atributo2);

    return 0;
}