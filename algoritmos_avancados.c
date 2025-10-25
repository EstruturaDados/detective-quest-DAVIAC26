#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// =======================
/// ESTRUTURAS DE DADOS
/// =======================

// Estrutura para representar uma sala da mansão
typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Estrutura para representar um nó da árvore de pistas (BST)
typedef struct PistaNode {
    char pista[100];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

/// =======================
/// FUNÇÕES DE CRIAÇÃO
/// =======================

/**
 * Função: criarSala
 * ------------------
 * Cria dinamicamente uma nova sala, com ou sem pista associada.
 */
Sala* criarSala(const char* nome, const char* pista) {
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    if (pista != NULL)
        strcpy(nova->pista, pista);
    else
        strcpy(nova->pista, ""); // Sem pista
    nova->esquerda = nova->direita = NULL;
    return nova;
}

/**
 * Função: inserirPista
 * ---------------------
 * Insere uma nova pista na árvore de pistas (BST), em ordem alfabética.
 */
PistaNode* inserirPista(PistaNode* raiz, const char* pista) {
    if (raiz == NULL) {
        PistaNode* novo = (PistaNode*) malloc(sizeof(PistaNode));
        strcpy(novo->pista, pista);
        novo->esquerda = novo->direita = NULL;
        return novo;
    }

    if (strcmp(pista, raiz->pista) < 0)
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->direita = inserirPista(raiz->direita, pista);

    return raiz;
}

/**
 * Função: exibirPistas
 * ---------------------
 * Exibe as pistas armazenadas na árvore BST em ordem alfabética (in-order).
 */
void exibirPistas(PistaNode* raiz) {
    if (raiz == NULL) return;
    exibirPistas(raiz->esquerda);
    printf("- %s\n", raiz->pista);
    exibirPistas(raiz->direita);
}

/// =======================
/// EXPLORAÇÃO DA MANSÃO
/// =======================

/**
 * Função: explorarSalasComPistas
 * -------------------------------
 * Permite ao jogador navegar entre as salas e coletar pistas.
 */
void explorarSalasComPistas(Sala* salaAtual, PistaNode** arvorePistas) {
    char escolha;

    if (salaAtual == NULL) return;

    while (1) {
        printf("\n📍 Você está no cômodo: %s\n", salaAtual->nome);

        // Exibir pista se existir
        if (strlen(salaAtual->pista) > 0) {
            printf("🔍 Pista encontrada: \"%s\"\n", salaAtual->pista);
            *arvorePistas = inserirPista(*arvorePistas, salaAtual->pista);
        } else {
            printf("Nenhuma pista neste cômodo.\n");
        }

        // Opções de navegação
        printf("\nEscolha seu caminho:\n");
        if (salaAtual->esquerda) printf(" (e) Ir para %s\n", salaAtual->esquerda->nome);
        if (salaAtual->direita)  printf(" (d) Ir para %s\n", salaAtual->direita->nome);
        printf(" (s) Sair da mansão\n> ");
        scanf(" %c", &escolha);

        if (escolha == 's') {
            printf("\n👋 Você decidiu sair da mansão.\n");
            break;
        } else if (escolha == 'e' && salaAtual->esquerda) {
            salaAtual = salaAtual->esquerda;
        } else if (escolha == 'd' && salaAtual->direita) {
            salaAtual = salaAtual->direita;
        } else {
            printf("❌ Caminho inválido!\n");
        }
    }
}

/// =======================
/// FUNÇÃO PRINCIPAL
/// =======================

int main() {
    // Criação do mapa fixo da mansão
    Sala* hall = criarSala("Hall de Entrada", "Pegadas misteriosas no tapete");
    Sala* salaEstar = criarSala("Sala de Estar", "Um retrato com olhos recortados");
    Sala* cozinha = criarSala("Cozinha", "Um copo quebrado no chão");
    Sala* biblioteca = criarSala("Biblioteca", "Um livro aberto em uma página marcada");
    Sala* escritorio = criarSala("Escritório", "Uma carta parcialmente queimada");

    // Estrutura da mansão (árvore binária)
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = escritorio;

    // Árvore de pistas inicialmente vazia
    PistaNode* arvorePistas = NULL;

    printf("🕵️‍♂️ Bem-vindo(a) à Mansão Enigma!\n");
    printf("Explore os cômodos e colete todas as pistas.\n");

    // Explorar as salas
    explorarSalasComPistas(hall, &arvorePistas);

    // Exibir todas as pistas coletadas
    printf("\n=============================\n");
    printf("📜 PISTAS COLETADAS (em ordem alfabética):\n");
    printf("=============================\n");
    if (arvorePistas)
        exibirPistas(arvorePistas);
    else
        printf("Nenhuma pista foi coletada.\n");

    printf("\nFim da exploração.\n");
    return 0;
}
