#include <stdio.h>

typedef struct {
    char estado;                 // A-H
    char codigo[5];              // ex: A01
    char nome[50];               // sem espaços (para simplificar o scanf)
    int  populacao;
    int  pontos_turisticos;
    float area;                  // km²
    float pib;                   // use a unidade que preferir
    float densidade;             // hab/km² (calculada)
} Carta;

/* ---------- Entrada das cartas (você pode aproveitar as já cadastradas) ---------- */
void ler_carta(Carta *c, int idx){
    printf("Carta %d:\n", idx);
    printf("Estado (A-H): ");               scanf(" %c", &c->estado);
    printf("Codigo (ex: A01): ");           scanf("%4s", c->codigo);
    printf("Nome do pais/cidade: ");        scanf("%49s", c->nome);
    printf("Populacao: ");                  scanf("%d",  &c->populacao);
    printf("Area (km2): ");                 scanf("%f",  &c->area);
    printf("PIB: ");                        scanf("%f",  &c->pib);
    printf("Pontos turisticos: ");          scanf("%d",  &c->pontos_turisticos);

    c->densidade = (c->area > 0.0f) ? ( (float)c->populacao / c->area ) : 0.0f;
    if (c->area <= 0.0f) puts("Aviso: area <= 0; densidade ajustada para 0.");
    puts("");
}

void exibir_carta(const Carta *c, const char* titulo){
    printf("\n%s\n", titulo);
    printf("Estado: %c | Cod: %s | Nome: %s\n", c->estado, c->codigo, c->nome);
    printf("Populacao: %d | Area: %.2f | PIB: %.2f | Pontos: %d | Densidade: %.2f\n",
           c->populacao, c->area, c->pib, c->pontos_turisticos, c->densidade);
}

/* ---------- Utilitários ---------- */
enum { ATR_POP=1, ATR_AREA, ATR_PIB, ATR_PONTOS, ATR_DENS=5 };

const char* nome_atributo(int atr){
    switch(atr){
        case ATR_POP:   return "Populacao";
        case ATR_AREA:  return "Area (km2)";
        case ATR_PIB:   return "PIB";
        case ATR_PONTOS:return "Pontos turisticos";
        case ATR_DENS:  return "Densidade demografica (hab/km2)";
        default:        return "Desconhecido";
    }
}

/* Retorna o valor do atributo em float para facilitar a soma/mostragem */
float valor_atributo_float(const Carta *c, int atr){
    switch(atr){
        case ATR_POP:    return (float)c->populacao;
        case ATR_AREA:   return c->area;
        case ATR_PIB:    return c->pib;
        case ATR_PONTOS: return (float)c->pontos_turisticos;
        case ATR_DENS:   return c->densidade;
        default:         return 0.0f;
    }
}

/* Para soma: regra coerente — densidade entra invertida (menor é melhor) */
float pontos_para_soma(const Carta *c, int atr){
    float v = valor_atributo_float(c, atr);
    return (atr == ATR_DENS) ? (-v) : v;    // operador ternário ✅
}

/* Compara um único atributo, imprimindo o vencedor/empate */
void comparar_unico(const Carta *c1, const Carta *c2, int atr){
    float v1 = valor_atributo_float(c1, atr);
    float v2 = valor_atributo_float(c2, atr);
    int menorVence = (atr == ATR_DENS);

    printf("\nAtributo: %s\n", nome_atributo(atr));
    printf("%s: %.2f\n", c1->nome, v1);
    printf("%s: %.2f\n", c2->nome, v2);

    if (v1 == v2){
        puts("Resultado: Empate!");
    } else {
        int carta1Vence = menorVence ? (v1 < v2) : (v1 > v2);   // ternário + lógica invertida ✅
        printf("Vencedora: %s\n", carta1Vence ? c1->nome : c2->nome);
    }
}

/* Menu dinâmico: oculta o já escolhido.
   used_mask: bit0=POP, bit1=AREA, bit2=PIB, bit3=PONTOS, bit4=DENS  */
int escolher_atributo(int used_mask){
    while(1){
        puts("\nEscolha um atributo NUMERICO:");
        if(!(used_mask & (1<<0))) printf("1 - Populacao (MAIOR vence)\n");
        if(!(used_mask & (1<<1))) printf("2 - Area (MAIOR vence)\n");
        if(!(used_mask & (1<<2))) printf("3 - PIB (MAIOR vence)\n");
        if(!(used_mask & (1<<3))) printf("4 - Pontos turisticos (MAIOR vence)\n");
        if(!(used_mask & (1<<4))) printf("5 - Densidade demografica (MENOR vence)\n");
        printf("Opcao: ");

        int op;
        if (scanf("%d", &op) != 1){
            int ch; while((ch=getchar())!='\n' && ch!=EOF){} // limpa lixo
            puts("Entrada invalida. Tente novamente.");
            continue;
        }

        int bit = -1;
        if(op==1) bit=0; else if(op==2) bit=1; else if(op==3) bit=2; else if(op==4) bit=3; else if(op==5) bit=4;

        if(bit==-1){
            puts("Opcao inexistente. Tente novamente.");
            continue;
        }
        if(used_mask & (1<<bit)){
            puts("Esse atributo ja foi escolhido. Selecione outro.");
            continue;
        }
        return op; // ok
    }
}

int main(void){
    Carta c1, c2;
    puts("=== SUPER TRUNFO — Nivel MESTRE ===\n");
    ler_carta(&c1, 1);
    ler_carta(&c2, 2);

    exibir_carta(&c1, "--- Carta 1 ---");
    exibir_carta(&c2, "--- Carta 2 ---");
    puts("");

    /* ====== Escolha de DOIS atributos diferentes (menu dinâmico) ====== */
    int used=0;
    int a1 = escolher_atributo(used);        // 1ª escolha
    used |= (1 << (a1-1));
    int a2 = escolher_atributo(used);        // 2ª escolha (1ª ocultada)
    used |= (1 << (a2-1));

    /* ====== Comparações individuais ====== */
    puts("\n==== Comparacoes individuais ====");
    comparar_unico(&c1, &c2, a1);
    comparar_unico(&c1, &c2, a2);

    /* ====== Soma (com densidade invertida para coerência) ====== */
    float s1 = pontos_para_soma(&c1, a1) + pontos_para_soma(&c1, a2);
    float s2 = pontos_para_soma(&c2, a1) + pontos_para_soma(&c2, a2);

    printf("\n==== Soma final (regra aplicada: densidade conta invertida) ====\n");
    printf("%s: soma = %.2f ( %s: %.2f + %s: %.2f )\n",
           c1.nome, s1, nome_atributo(a1), pontos_para_soma(&c1,a1),
           nome_atributo(a2), pontos_para_soma(&c1,a2));
    printf("%s: soma = %.2f ( %s: %.2f + %s: %.2f )\n",
           c2.nome, s2, nome_atributo(a1), pontos_para_soma(&c2,a1),
           nome_atributo(a2), pontos_para_soma(&c2,a2));

    if (s1 == s2){
        puts("Resultado final: Empate!");
    } else {
        printf("Resultado final: Vencedora = %s\n", (s1 > s2) ? c1.nome : c2.nome); // ternário ✅
    }

    puts("\nObrigado por jogar!");
    return 0;
}
