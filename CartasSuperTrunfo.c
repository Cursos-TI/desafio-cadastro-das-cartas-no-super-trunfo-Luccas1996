#include <stdio.h>

// Estrutura para organizar melhor os dados
typedef struct {
    char estado;                 // A-H
    char codigo[5];              // ex: A01 (+ '\0')
    char nome[50];               // nome (sem espaços, p/ simplificar scanf)
    int populacao;
    int pontos_turisticos;
    float area;                  // km²
    float pib;                   // bilhões (use a unidade que preferir)
    float densidade;             // hab/km² (calculada)
} Carta;

// Função auxiliar para ler uma carta
void ler_carta(Carta *c, int indice) {
    printf("Carta %d:\n", indice);

    printf("Digite o Estado (A-H): ");
    scanf(" %c", &c->estado); // espaço antes de %c consome o \n anterior

    printf("Digite o Código da Carta (ex: A01): ");
    scanf("%4s", c->codigo);

    // Observação: para aceitar nomes com espaços, seria melhor usar fgets.
    // Para manter simples, seguimos o enunciado usando scanf sem espaços.
    printf("Digite o nome do pais/cidade (sem espacos): ");
    scanf("%49s", c->nome);

    printf("Digite a Populacao: ");
    scanf("%d", &c->populacao);

    printf("Digite a Area em km²: ");
    scanf("%f", &c->area);

    printf("Digite o PIB: ");
    scanf("%f", &c->pib);

    printf("Digite o Numero de Pontos Turisticos: ");
    scanf("%d", &c->pontos_turisticos);

    // Calcula densidade com proteção contra divisão por zero/negativo
    if (c->area > 0.0f) {
        c->densidade = (float)c->populacao / c->area;
    } else {
        c->densidade = 0.0f;
        printf("Aviso: area <= 0. Densidade ajustada para 0.\n");
    }
    printf("\n");
}

// Mostra as cartas cadastradas
void exibir_cartas(const Carta *c1, const Carta *c2) {
    printf("\n--- Cartas Cadastradas ---\n");

    printf("\nCarta 1:\n");
    printf("Estado: %c\n", c1->estado);
    printf("Codigo: %s\n", c1->codigo);
    printf("Nome: %s\n", c1->nome);
    printf("Populacao: %d\n", c1->populacao);
    printf("Area: %.2f km²\n", c1->area);
    printf("PIB: %.2f\n", c1->pib);
    printf("Pontos Turisticos: %d\n", c1->pontos_turisticos);
    printf("Densidade: %.2f hab/km²\n", c1->densidade);

    printf("\nCarta 2:\n");
    printf("Estado: %c\n", c2->estado);
    printf("Codigo: %s\n", c2->codigo);
    printf("Nome: %s\n", c2->nome);
    printf("Populacao: %d\n", c2->populacao);
    printf("Area: %.2f km²\n", c2->area);
    printf("PIB: %.2f\n", c2->pib);
    printf("Pontos Turisticos: %d\n", c2->pontos_turisticos);
    printf("Densidade: %.2f hab/km²\n\n", c2->densidade);
}

// Lógica de comparação (com if-else aninhado onde faz sentido)
void comparar(const Carta *c1, const Carta *c2, int atributo) {
    const char *nomeAtributo = "";
    float v1f = 0.0f, v2f = 0.0f;
    int v1i = 0, v2i = 0;
    int tipoFloat = 0; // 0 = int, 1 = float, 2 = nome

    switch (atributo) {
        case 1: // Nome do país (apenas exibição)
            nomeAtributo = "Nome do pais";
            tipoFloat = 2;
            printf("Comparacao por \"%s\": apenas exibir informacoes.\n", nomeAtributo);
            printf("Carta 1: %s | Carta 2: %s\n", c1->nome, c2->nome);
            printf("Nao ha vencedor por nome. Escolha outro atributo.\n\n");
            return;

        case 2: // População (maior vence)
            nomeAtributo = "Populacao";
            tipoFloat = 0;
            v1i = c1->populacao;
            v2i = c2->populacao;
            break;

        case 3: // Área (maior vence)
            nomeAtributo = "Area (km²)";
            tipoFloat = 1;
            v1f = c1->area;
            v2f = c2->area;
            break;

        case 4: // PIB (maior vence)
            nomeAtributo = "PIB";
            tipoFloat = 1;
            v1f = c1->pib;
            v2f = c2->pib;
            break;

        case 5: // Pontos turísticos (maior vence)
            nomeAtributo = "Pontos Turisticos";
            tipoFloat = 0;
            v1i = c1->pontos_turisticos;
            v2i = c2->pontos_turisticos;
            break;

        case 6: // Densidade (menor vence) — regra invertida
            nomeAtributo = "Densidade Demografica (hab/km²)";
            tipoFloat = 1;
            v1f = c1->densidade;
            v2f = c2->densidade;
            break;

        default:
            printf("Opcao invalida. Tente novamente.\n\n");
            return;
    }

    // Exibe valores e aplica as regras
    printf("Atributo: %s\n", nomeAtributo);
    if (tipoFloat == 0) {
        printf("%s (Carta 1 - %s): %d\n", nomeAtributo, c1->nome, v1i);
        printf("%s (Carta 2 - %s): %d\n", nomeAtributo, c2->nome, v2i);

        // if-else ANINHADO: primeiro verifica empate, depois regras
        if (v1i == v2i) {
            printf("Empate!\n\n");
        } else {
            // Regra geral: maior vence (para ints, exceto densidade que não cai aqui)
            if (v1i > v2i) {
                printf("Vencedora: Carta 1 (%s)\n\n", c1->nome);
            } else {
                printf("Vencedora: Carta 2 (%s)\n\n", c2->nome);
            }
        }
    } else if (tipoFloat == 1) {
        printf("%s (Carta 1 - %s): %.2f\n", nomeAtributo, c1->nome, v1f);
        printf("%s (Carta 2 - %s): %.2f\n", nomeAtributo, c2->nome, v2f);

        // if-else ANINHADO: empate -> senão aplica regra normal ou invertida
        if (v1f == v2f) {
            printf("Empate!\n\n");
        } else {
            if (atributo == 6) { // densidade -> menor vence
                if (v1f < v2f) {
                    printf("Vencedora: Carta 1 (%s) [menor densidade]\n\n", c1->nome);
                } else {
                    printf("Vencedora: Carta 2 (%s) [menor densidade]\n\n", c2->nome);
                }
            } else { // regra geral: maior vence
                if (v1f > v2f) {
                    printf("Vencedora: Carta 1 (%s)\n\n", c1->nome);
                } else {
                    printf("Vencedora: Carta 2 (%s)\n\n", c2->nome);
                }
            }
        }
    }
}

int main(void) {
    Carta c1, c2;
    int opcao;

    printf("=== SUPER TRUNFO — Nivel Aventureiro ===\n\n");

    // Entrada de dados das duas cartas (mantendo seu fluxo)
    ler_carta(&c1, 1);
    ler_carta(&c2, 2);

    exibir_cartas(&c1, &c2);

    // Menu interativo com switch
    do {
        printf("Escolha um atributo para comparar:\n");
        printf("1 - Nome do pais (apenas exibir)\n");
        printf("2 - Populacao (maior vence)\n");
        printf("3 - Area (maior vence)\n");
        printf("4 - PIB (maior vence)\n");
        printf("5 - Pontos Turisticos (maior vence)\n");
        printf("6 - Densidade Demografica (MENOR vence)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");

        if (scanf("%d", &opcao) != 1) {
            // Entrada inválida (ex: letra). Limpa stdin grosso modo.
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {}
            printf("Entrada invalida. Tente novamente.\n\n");
            continue;
        }

        switch (opcao) {
            case 0:
                printf("Saindo... Obrigado por jogar!\n");
                break;
            case 1: case 2: case 3: case 4: case 5: case 6:
                comparar(&c1, &c2, opcao);
                break;
            default:
                printf("Opcao inexistente. Use 0, 1, 2, 3, 4, 5 ou 6.\n\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
