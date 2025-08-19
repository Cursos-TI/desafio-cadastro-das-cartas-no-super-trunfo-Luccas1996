#include <stdio.h>

int main() {
    // Carta 1
    char estado1;
    char codigo1[5];
    char nome_cidade1[50];
    int populacao1, pontos_turisticos1;
    float area1, pib1;

    // Carta 2
    char estado2;
    char codigo2[5];
    char nome_cidade2[50];
    int populacao2, pontos_turisticos2;
    float area2, pib2;

    // Entrada de dados - Carta 1
    printf("Carta 1:\n");

    printf("Digite o Estado (A-H): ");
    scanf(" %c", &estado1); // espaço antes do %c

    printf("Digite o Código da Carta (ex: A01): ");
    scanf("%s", codigo1);

    printf("Digite o nome da cidade (sem espaços): ");
    scanf("%s", nome_cidade1);

    printf("Digite a Populacao: ");
    scanf("%d", &populacao1);

    printf("Digite a Area em km²: ");
    scanf("%f", &area1);

    printf("Digite o PIB: ");
    scanf("%f", &pib1);

    printf("Digite o Numero de Pontos Turisticos: ");
    scanf("%d", &pontos_turisticos1);

    // Entrada de dados - Carta 2
    printf("\nCarta 2:\n");

    printf("Digite o Estado (A-H): ");
    scanf(" %c", &estado2); // espaço antes do %c

    printf("Digite o Código da Carta (ex: A01): ");
    scanf("%s", codigo2);

    printf("Digite o nome da cidade (sem espaços): ");
    scanf("%s", nome_cidade2);

    printf("Digite a Populacao: ");
    scanf("%d", &populacao2);

    printf("Digite a Area em km²: ");
    scanf("%f", &area2);

    printf("Digite o PIB: ");
    scanf("%f", &pib2);

    printf("Digite o Numero de Pontos Turisticos: ");
    scanf("%d", &pontos_turisticos2);

    // Exibição dos dados formatados
    printf("\n--- Cartas Cadastradas ---\n");

    printf("\nCarta 1:\n");
    printf("Estado: %c\n", estado1);
    printf("Codigo: %s\n", codigo1);
    printf("Nome da Cidade: %s\n", nome_cidade1);
    printf("Populacao: %d\n", populacao1);
    printf("Area: %.2f km²\n", area1);
    printf("PIB: %.2f bilhoes de reais\n", pib1);
    printf("Numero de Pontos Turisticos: %d\n", pontos_turisticos1);

    printf("\nCarta 2:\n");
    printf("Estado: %c\n", estado2);
    printf("Codigo: %s\n", codigo2);
    printf("Nome da Cidade: %s\n", nome_cidade2);
    printf("Populacao: %d\n", populacao2);
    printf("Area: %.2f km²\n", area2);
    printf("PIB: %.2f bilhoes de reais\n", pib2);
    printf("Numero de Pontos Turisticos: %d\n", pontos_turisticos2);

    return 0;
}