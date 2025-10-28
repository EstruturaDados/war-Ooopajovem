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
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Protótipos das funções
void cadastrarTerritorios(struct Territorio** mapa, int* totalTerritorios);
void exibirTerritorios(struct Territorio* mapa, int totalTerritorios);
void atacar(struct Territorio* atacante, struct Territorio* defensor);
void liberarMemoria(struct Territorio* mapa);
void simularAtaque(struct Territorio* mapa, int totalTerritorios);

int main() {
    struct Territorio* mapa = NULL;
    int totalTerritorios = 0;
    int opcao;
    
    // Inicializar gerador de números aleatórios
    srand(time(NULL));
    
    do {
        printf("\n=== SISTEMA WAR ESTRUTURADO ===\n");
        printf("1. Cadastrar territorios\n");
        printf("2. Exibir territorios\n");
        printf("3. Simular ataque\n");
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
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while(opcao != 0);
    
    liberarMemoria(mapa);
    return 0;
}

// Função para cadastrar territórios com alocação dinâmica
void cadastrarTerritorios(struct Territorio** mapa, int* totalTerritorios) {
    printf("\nQuantos territorios deseja cadastrar? ");
    scanf("%d", totalTerritorios);
    
    // Alocar memória para o vetor de territórios
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
        printf("Cor do exercito: ");
        scanf("%s", (*mapa)[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &(*mapa)[i].tropas);
    }
    printf("\nCadastro concluido!\n");
}

// Função para exibir todos os territórios
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

// Função principal de ataque entre territórios
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    printf("\n=== SIMULACAO DE ATAQUE ===\n");
    printf("Atacante: %s (%s) com %d tropas\n", atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) com %d tropas\n", defensor->nome, defensor->cor, defensor->tropas);
    
    // Simular dados de batalha (1-6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;
    
    printf("\nDados rolados:\n");
    printf("Atacante: %d\n", dadoAtacante);
    printf("Defensor: %d\n", dadoDefensor);
    
    if(dadoAtacante > dadoDefensor) {
        // Atacante vence
        printf("\n>>> VITORIA DO ATACANTE! <<<\n");
        
        // Transferir metade das tropas do defensor para o atacante
        int tropasConquistadas = defensor->tropas / 2;
        atacante->tropas += tropasConquistadas;
        defensor->tropas -= tropasConquistadas;
        
        // Mudar a cor do território defensor
        strcpy(defensor->cor, atacante->cor);
        
        printf("O territorio %s agora pertence ao exercito %s!\n", defensor->nome, atacante->cor);
        printf("Tropas transferidas: %d\n", tropasConquistadas);
        
    } else if(dadoAtacante < dadoDefensor) {
        // Defensor vence
        printf("\n>>> VITORIA DO DEFENSOR! <<<\n");
        
        // Atacante perde uma tropa
        if(atacante->tropas > 1) {
            atacante->tropas--;
            printf("O atacante perdeu 1 tropa!\n");
        } else {
            printf("O atacante nao tem tropas para perder!\n");
        }
        
    } else {
        // Empate
        printf("\n>>> EMPATE! Nada acontece. <<<\n");
    }
    
    printf("\nSituacao apos a batalha:\n");
    printf("Atacante: %d tropas\n", atacante->tropas);
    printf("Defensor: %d tropas (%s)\n", defensor->tropas, defensor->cor);
}

// Função para simular o ataque com interface do usuário
void simularAtaque(struct Territorio* mapa, int totalTerritorios) {
    if(mapa == NULL || totalTerritorios < 2) {
        printf("\nEh necessario pelo menos 2 territorios para simular um ataque!\n");
        return;
    }
    
    int idxAtacante, idxDefensor;
    
    printf("\n=== SIMULAR ATAQUE ===\n");
    exibirTerritorios(mapa, totalTerritorios);
    
    // Escolher território atacante
    printf("\nEscolha o territorio ATACANTE (1 a %d): ", totalTerritorios);
    scanf("%d", &idxAtacante);
    idxAtacante--; // Ajustar para índice do array
    
    if(idxAtacante < 0 || idxAtacante >= totalTerritorios) {
        printf("Territorio invalido!\n");
        return;
    }
    
    // Escolher território defensor
    printf("Escolha o territorio DEFENSOR (1 a %d): ", totalTerritorios);
    scanf("%d", &idxDefensor);
    idxDefensor--; // Ajustar para índice do array
    
    if(idxDefensor < 0 || idxDefensor >= totalTerritorios) {
        printf("Territorio invalido!\n");
        return;
    }
    
    // Validar se não é o mesmo território
    if(idxAtacante == idxDefensor) {
        printf("Um territorio nao pode atacar a si mesmo!\n");
        return;
    }
    
    // Validar se não são do mesmo exército
    if(strcmp(mapa[idxAtacante].cor, mapa[idxDefensor].cor) == 0) {
        printf("Territorios do mesmo exercito nao podem se atacar!\n");
        return;
    }
    
    // Executar o ataque
    atacar(&mapa[idxAtacante], &mapa[idxDefensor]);
}

// Função para liberar memória alocada
void liberarMemoria(struct Territorio* mapa) {
    if(mapa != NULL) {
        free(mapa);
        printf("\nMemoria liberada com sucesso!\n");
    }
}