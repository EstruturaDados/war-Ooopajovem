// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
//int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

//    return 0;
//}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MISSOES 5
#define MAX_JOGADORES 2

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

struct Jogador {
    char nome[20];
    char cor[10];
    char* missao;  // Missão atribuída dinamicamente
    int missaoCumprida;
};

// Protótipos das funções
void cadastrarTerritorios(struct Territorio** mapa, int* totalTerritorios);
void exibirTerritorios(struct Territorio* mapa, int totalTerritorios);
void atacar(struct Territorio* atacante, struct Territorio* defensor);
void liberarMemoria(struct Territorio* mapa, struct Jogador* jogadores);
void simularAtaque(struct Territorio* mapa, int totalTerritorios);

// Novas funções para o sistema de missões
void inicializarMissoes(char* missoes[]);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
void exibirMissao(struct Jogador jogador);
int verificarMissao(char* missao, struct Territorio* mapa, int tamanho, char* corJogador);
void inicializarJogadores(struct Jogador* jogadores, char* missoes[]);
void verificarVitoria(struct Jogador* jogadores, struct Territorio* mapa, int totalTerritorios);

int main() {
    struct Territorio* mapa = NULL;
    int totalTerritorios = 0;
    int opcao;
    int turno = 0;
    
    // Vetor de missões pré-definidas
    char* missoes[MAX_MISSOES];
    
    // Array de jogadores
    struct Jogador jogadores[MAX_JOGADORES];
    
    // Inicializar gerador de números aleatórios
    srand(time(NULL));
    
    // Inicializar sistema de missões
    inicializarMissoes(missoes);
    inicializarJogadores(jogadores, missoes);
    
    printf("=== SISTEMA WAR ESTRUTURADO COM MISSOES ===\n");
    printf("Missoes atribuidas aos jogadores!\n\n");
    
    do {
        printf("\n=== TURNO %d ===\n", ++turno);
        printf("1. Cadastrar territorios\n");
        printf("2. Exibir territorios\n");
        printf("3. Simular ataque\n");
        printf("4. Exibir minha missao\n");
        printf("5. Verificar vitoria\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                cadastrarTerritorios(&mapa, &totalTerritorios);
                break;
            case 2:
                exibirTerritorios(mapa, totalTerritorios);
                break;
            case 3:
                simularAtaque(mapa, totalTerritorios);
                // Verificar missões após cada ataque
                if (mapa != NULL) {
                    verificarVitoria(jogadores, mapa, totalTerritorios);
                }
                break;
            case 4:
                printf("\nEscolha o jogador (1 ou 2): ");
                int jogador;
                scanf("%d", &jogador);
                if (jogador >= 1 && jogador <= 2) {
                    exibirMissao(jogadores[jogador-1]);
                } else {
                    printf("Jogador invalido!\n");
                }
                break;
            case 5:
                if (mapa != NULL) {
                    verificarVitoria(jogadores, mapa, totalTerritorios);
                } else {
                    printf("Cadastre territorios primeiro!\n");
                }
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while(opcao != 0);
    
    liberarMemoria(mapa, jogadores);
    return 0;
}

// ========== SISTEMA DE MISSÕES ==========

/**
 * @brief Inicializa o vetor de missões pré-definidas
 * @param missoes Vetor de strings para armazenar as missões
 */
void inicializarMissoes(char* missoes[]) {
    missoes[0] = "Conquistar 3 territorios seguidos";
    missoes[1] = "Eliminar todas as tropas da cor vermelha";
    missoes[2] = "Controlar pelo menos 5 territorios";
    missoes[3] = "Destruir o exercito azul completamente";
    missoes[4] = "Manter 10 tropas em um unico territorio";
}

/**
 * @brief Atribui uma missão aleatória a um jogador
 * @param destino Ponteiro onde a missão será armazenada
 * @param missoes Vetor de missões disponíveis
 * @param totalMissoes Número total de missões
 */
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indiceMissao = rand() % totalMissoes;
    strcpy(destino, missoes[indiceMissao]);
}

/**
 * @brief Exibe a missão de um jogador
 * @param jogador Jogador cuja missão será exibida
 */
void exibirMissao(struct Jogador jogador) {
    printf("\n=== MISSAO DO JOGADOR %s (%s) ===\n", 
           jogador.nome, jogador.cor);
    printf("Missao: %s\n", jogador.missao);
    printf("Status: %s\n", jogador.missaoCumprida ? "CUMPRIDA!" : "Em andamento");
}

/**
 * @brief Verifica se a missão do jogador foi cumprida
 * @param missao Missão a ser verificada
 * @param mapa Vetor de territórios
 * @param tamanho Número total de territórios
 * @param corJogador Cor do jogador para verificação
 * @return 1 se missão cumprida, 0 caso contrário
 */
int verificarMissao(char* missao, struct Territorio* mapa, int tamanho, char* corJogador) {
    // Missão 1: Conquistar 3 territórios seguidos
    if (strstr(missao, "3 territorios seguidos")) {
        int consecutivos = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                consecutivos++;
                if (consecutivos >= 3) return 1;
            } else {
                consecutivos = 0;
            }
        }
        return 0;
    }
    
    // Missão 2: Eliminar todas as tropas da cor vermelha
    if (strstr(missao, "cor vermelha")) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }
    
    // Missão 3: Controlar pelo menos 5 territórios
    if (strstr(missao, "5 territorios")) {
        int territoriosControlados = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                territoriosControlados++;
            }
        }
        return territoriosControlados >= 5;
    }
    
    // Missão 4: Destruir o exercito azul completamente
    if (strstr(missao, "exercito azul")) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }
    
    // Missão 5: Manter 10 tropas em um único território
    if (strstr(missao, "10 tropas")) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas >= 10) {
                return 1;
            }
        }
        return 0;
    }
    
    return 0;
}

/**
 * @brief Inicializa os jogadores com nomes, cores e missões
 * @param jogadores Array de jogadores
 * @param missoes Vetor de missões disponíveis
 */
void inicializarJogadores(struct Jogador* jogadores, char* missoes[]) {
    // Jogador 1
    strcpy(jogadores[0].nome, "Jogador1");
    strcpy(jogadores[0].cor, "vermelho");
    jogadores[0].missao = (char*)malloc(100 * sizeof(char));
    atribuirMissao(jogadores[0].missao, missoes, MAX_MISSOES);
    jogadores[0].missaoCumprida = 0;
    
    // Jogador 2
    strcpy(jogadores[1].nome, "Jogador2");
    strcpy(jogadores[1].cor, "azul");
    jogadores[1].missao = (char*)malloc(100 * sizeof(char));
    atribuirMissao(jogadores[1].missao, missoes, MAX_MISSOES);
    jogadores[1].missaoCumprida = 0;
    
    printf("Jogadores inicializados:\n");
    printf("- %s (%s)\n", jogadores[0].nome, jogadores[0].cor);
    printf("- %s (%s)\n", jogadores[1].nome, jogadores[1].cor);
}

/**
 * @brief Verifica se algum jogador cumpriu sua missão
 * @param jogadores Array de jogadores
 * @param mapa Vetor de territórios
 * @param totalTerritorios Número total de territórios
 */
void verificarVitoria(struct Jogador* jogadores, struct Territorio* mapa, int totalTerritorios) {
    for (int i = 0; i < MAX_JOGADORES; i++) {
        if (!jogadores[i].missaoCumprida) {
            int cumprida = verificarMissao(jogadores[i].missao, mapa, totalTerritorios, jogadores[i].cor);
            if (cumprida) {
                jogadores[i].missaoCumprida = 1;
                printf("\n🎉🎉🎉 VITORIA! 🎉🎉🎉\n");
                printf("O %s (%s) cumpriu sua missao!\n", 
                       jogadores[i].nome, jogadores[i].cor);
                printf("Missao: %s\n", jogadores[i].missao);
                printf("Parabens! O jogo acabou.\n");
            }
        }
    }
}

// ========== FUNÇÕES ORIGINAIS (COM MELHORIAS) ==========

void cadastrarTerritorios(struct Territorio** mapa, int* totalTerritorios) {
    printf("\nQuantos territorios deseja cadastrar? ");
    scanf("%d", totalTerritorios);
    
    *mapa = (struct Territorio*)calloc(*totalTerritorios, sizeof(struct Territorio));
    
    if (*mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return;
    }
    
    printf("\n=== CADASTRO DE TERRITORIOS ===\n");
    for(int i = 0; i < *totalTerritorios; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("Nome: ");
        scanf("%s", (*mapa)[i].nome);
        printf("Cor do exercito (vermelho/azul/verde/amarelo): ");
        scanf("%s", (*mapa)[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &(*mapa)[i].tropas);
    }
    printf("\nCadastro concluido!\n");
}

void exibirTerritorios(struct Territorio* mapa, int totalTerritorios) {
    if(mapa == NULL || totalTerritorios == 0) {
        printf("\nNenhum territorio cadastrado!\n");
        return;
    }
    
    printf("\n=== MAPA DO MUNDO - ESTADO ATUAL ===\n");
    for(int i = 0; i < totalTerritorios; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("- Nome: %s\n", mapa[i].nome);
        printf("- Dominado por: Exercito %s\n", mapa[i].cor);
        printf("- Tropas: %d\n", mapa[i].tropas);
        printf("----------------------------\n");
    }
}

void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    printf("\n=== SIMULACAO DE ATAQUE ===\n");
    printf("Atacante: %s (%s) com %d tropas\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) com %d tropas\n", defensor->nome, defensor->cor, defensor->tropas);
    
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    
    printf("\nDados rolados:\n");
    printf("Atacante: %d\n", dadoAtacante);
    printf("Defensor: %d\n", dadoDefensor);
    
    if(dadoAtacante > dadoDefensor) {
        printf("\n>>> VITORIA DO ATACANTE! <<<\n");
        
        int tropasConquistadas = defensor->tropas / 2;
        atacante->tropas += tropasConquistadas;
        defensor->tropas -= tropasConquistadas;
        
        strcpy(defensor->cor, atacante->cor);
        
        printf("O territorio %s agora pertence ao exercito %s!\n", defensor->nome, atacante->cor);
        printf("Tropas transferidas: %d\n", tropasConquistadas);
        
    } else if(dadoAtacante < dadoDefensor) {
        printf("\n>>> VITORIA DO DEFENSOR! <<<\n");
        
        if(atacante->tropas > 1) {
            atacante->tropas--;
            printf("O atacante perdeu 1 tropa!\n");
        } else {
            printf("O atacante nao tem tropas para perder!\n");
        }
        
    } else {
        printf("\n>>> EMPATE! Nada acontece. <<<\n");
    }
    
    printf("\nSituacao apos a batalha:\n");
    printf("Atacante: %d tropas\n", atacante->tropas);
    printf("Defensor: %d tropas (%s)\n", defensor->tropas, defensor->cor);
}

void simularAtaque(struct Territorio* mapa, int totalTerritorios) {
    if(mapa == NULL || totalTerritorios < 2) {
        printf("\nEh necessario pelo menos 2 territorios para simular um ataque!\n");
        return;
    }
    
    int idxAtacante, idxDefensor;
    
    printf("\n=== SIMULAR ATAQUE ===\n");
    exibirTerritorios(mapa, totalTerritorios);
    
    printf("\nEscolha o territorio ATACANTE (1 a %d): ", totalTerritorios);
    scanf("%d", &idxAtacante);
    idxAtacante--;
    
    if(idxAtacante < 0 || idxAtacante >= totalTerritorios) {
        printf("Territorio invalido!\n");
        return;
    }
    
    printf("Escolha o territorio DEFENSOR (1 a %d): ", totalTerritorios);
    scanf("%d", &idxDefensor);
    idxDefensor--;
    
    if(idxDefensor < 0 || idxDefensor >= totalTerritorios) {
        printf("Territorio invalido!\n");
        return;
    }
    
    if(idxAtacante == idxDefensor) {
        printf("Um territorio nao pode atacar a si mesmo!\n");
        return;
    }
    
    if(strcmp(mapa[idxAtacante].cor, mapa[idxDefensor].cor) == 0) {
        printf("Territorios do mesmo exercito nao podem se atacar!\n");
        return;
    }
    
    atacar(&mapa[idxAtacante], &mapa[idxDefensor]);
}

void liberarMemoria(struct Territorio* mapa, struct Jogador* jogadores) {
    if(mapa != NULL) {
        free(mapa);
    }
    
    // Liberar memória das missões dos jogadores
    for(int i = 0; i < MAX_JOGADORES; i++) {
        if(jogadores[i].missao != NULL) {
            free(jogadores[i].missao);
        }
    }
    
    printf("\nMemoria liberada com sucesso!\n");
}