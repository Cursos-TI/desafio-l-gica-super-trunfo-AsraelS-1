#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura para armazenar os dados da carta
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

// Função para comparar cartas com base no atributo escolhido pelo usuário
void compararCartas(const CartaSuperTrunfo *carta1, const CartaSuperTrunfo *carta2, int atributo) {
    float valor1, valor2;
    const char *atributoNome;
    
    switch (atributo) {
        case 1: atributoNome = "Populacao"; valor1 = carta1->populacao; valor2 = carta2->populacao; break;
        case 2: atributoNome = "Area"; valor1 = carta1->area; valor2 = carta2->area; break;
        case 3: atributoNome = "PIB"; valor1 = carta1->pib; valor2 = carta2->pib; break;
        case 4: atributoNome = "Densidade Populacional"; valor1 = carta1->area > 0 ? carta1->populacao / carta1->area : 0;
                valor2 = carta2->area > 0 ? carta2->populacao / carta2->area : 0; break;
        case 5: atributoNome = "PIB per capita"; valor1 = carta1->populacao > 0 ? (carta1->pib * 1000) / carta1->populacao : 0;
                valor2 = carta2->populacao > 0 ? (carta2->pib * 1000) / carta2->populacao : 0; break;
        default: printf("Atributo invalido!\n"); return;
    }
    
    printf("\nComparacao de cartas (Atributo: %s):\n", atributoNome);
    printf("Carta 1 - %s (%c): %.2f\n", carta1->nomeCidade, carta1->estado, valor1);
    printf("Carta 2 - %s (%c): %.2f\n", carta2->nomeCidade, carta2->estado, valor2);
    
    if ((atributo == 4 && valor1 < valor2) || (atributo != 4 && valor1 > valor2)) {
        printf("Resultado: Carta 1 (%s) venceu!\n", carta1->nomeCidade);
    } else if (valor1 == valor2) {
        printf("Resultado: Empate!\n");
    } else {
        printf("Resultado: Carta 2 (%s) venceu!\n", carta2->nomeCidade);
    }
}

int main() {
    CartaSuperTrunfo carta1, carta2;
    int atributo;

    // Leitura dos dados das cartas
    lerCarta(&carta1, 1);
    lerCarta(&carta2, 2);

    // Exibição dos dados das cartas
    exibirCarta(&carta1, 1);
    exibirCarta(&carta2, 2);
    
    // Escolha do atributo de comparação
    printf("\nEscolha um atributo para comparar:\n");
    printf("1 - Populacao\n2 - Area\n3 - PIB\n4 - Densidade Populacional\n5 - PIB per capita\n");
    printf("Digite o numero do atributo: ");
    scanf("%d", &atributo);
    // Comparação das cartas
    compararCartas(&carta1, &carta2, atributo);

    return 0;
}
