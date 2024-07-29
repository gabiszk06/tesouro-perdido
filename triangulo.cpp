#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// Definição das constantes
const int TAMANHO_MINA = 6;  // Tamanho da matriz da mina (6x6 neste exemplo)

// Estrutura para representar cada jogador
struct Jogador {
    string nome;
    int quilates;
};

// Classe Mina, que encapsula toda a lógica do jogo
class Mina {
private:
    vector<vector<int>> mina;  // Matriz da mina com os quilates dos diamantes
    vector<vector<char>> marcadores;  // Matriz para marcar jogadores e armadilhas/pistas
    vector<Jogador> jogadores;  // Vetor de jogadores
    int num_jogadores;  // Número de jogadores

public:
    // Construtor que inicializa a mina com valores aleatórios e distribui armadilhas/pistas
    Mina(int n_jogadores) : num_jogadores(n_jogadores) {
        // Inicialização da mina com diamantes de 1 a 10
        mina = vector<vector<int>>(TAMANHO_MINA, vector<int>(TAMANHO_MINA));
        for (int i = 1; i < TAMANHO_MINA; ++i) {
            for (int j = 1; j < TAMANHO_MINA; ++j) {
                mina[i][j] = rand() % 10 + 1;  // diamantes de 1 a 10 quilates
            }
        }

        // Inicialização dos marcadores com pontos ('.' indica espaço vazio)
        marcadores = vector<vector<char>>(TAMANHO_MINA, vector<char>(TAMANHO_MINA, '.'));

        // Distribuição de pistas (5%) e armadilhas (10%)
        distribuirPistasEArmadilhas();
        
        // Inicialização dos jogadores
        inicializarJogadores();
    }

    // Função para distribuir pistas (+), túneis sem saída (O) e esconderijos secretos (-)
    void distribuirPistasEArmadilhas() {
        srand(static_cast<unsigned int>(time(nullptr)));

        // Calculando número de pistas e armadilhas
        int total_quadros = TAMANHO_MINA * TAMANHO_MINA;
        int num_pistas = total_quadros * 0.05;
        int num_armadilhas = total_quadros * 0.1;

        while (num_pistas > 0) {
            int linha = rand() % TAMANHO_MINA;
            int coluna = rand() % TAMANHO_MINA;
            if (marcadores[linha][coluna] == '.') {
                marcadores[linha][coluna] = '+';
                num_pistas--;
            }
        }

        while (num_armadilhas > 0) {
            int linha = rand() % TAMANHO_MINA;
            int coluna = rand() % TAMANHO_MINA;
            if (marcadores[linha][coluna] == '.') {
                if (rand() % 2 == 0) {
                    marcadores[linha][coluna] = 'O';  // Túnel sem saída
                } else {
                    marcadores[linha][coluna] = '-';  // Esconderijo secreto
                }
                num_armadilhas--;
            }
        }
    }

    // Função para inicializar os jogadores
    void inicializarJogadores() {
        for (int i = 0; i < num_jogadores; ++i) {
            Jogador jogador;
            cout << "Digite o nome do jogador " << i+1 << ": ";
            cin >> jogador.nome;
            jogador.quilates = 0;  // Inicia com 0 quilates
            jogadores.push_back(jogador);
        }
    }

    // Função para mover o jogador para uma posição na mina
    void moverJogador(int jogador_idx, int linha, int coluna) {
        if (linha >= 0 && linha < TAMANHO_MINA && coluna >= 0 && coluna < TAMANHO_MINA) {
            char& posicao = marcadores[linha][coluna];
            switch (posicao) {
                case '.':
                    // Quadrado vazio, o jogador move sem alterações
                    posicao = jogadores[jogador_idx].nome[0];  // Usar a inicial do nome como marcação
                    jogadores[jogador_idx].quilates += mina[linha][coluna];
                    break;
                case '+':
                    // Pista: acrescenta 3 quilates
                    posicao = jogadores[jogador_idx].nome[0];
                    jogadores[jogador_idx].quilates += mina[linha][coluna] + 3;
                    break;
                case '-':
                    // Esconderijo secreto: desconta 5 quilates do(s) oponente(s)
                    posicao = jogadores[jogador_idx].nome[0];
                    for (int i = 0; i < num_jogadores; ++i) {
                        if (i != jogador_idx) {
                            jogadores[i].quilates -= 5;
                        }
                    }
                    break;
                case 'O':
                    // Túnel sem saída: perde 10 quilates
                    posicao = jogadores[jogador_idx].nome[0];
                    jogadores[jogador_idx].quilates -= 10;
                    break;
                default:
                    // Outro jogador já está na posição
                    break;
            }
        }
    }

    // Função para exibir o estado atual da mina
    void imprimirMina() {
        cout << "Estado atual da mina:" << endl;
        for (int i = 0; i < TAMANHO_MINA; ++i) {
            for (int j = 0; j < TAMANHO_MINA; ++j) {
                cout << setw(3) << marcadores[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // Função para exibir o ranking atual dos jogadores
    void exibirRanking() {
        cout << "Ranking atual dos jogadores:" << endl;
        for (const auto& jogador : jogadores) {
            cout << jogador.nome << ": " << jogador.quilates << " quilates" << endl;
        }
        cout << endl;
    }

    // Função para verificar se o jogo terminou (todas as jogadas realizadas)
    bool jogoTerminou() {
        return jogadores[0].quilates != 0 && jogadores[1].quilates != 0 && jogadores[2].quilates != 0 && jogadores[3].quilates != 0;
    }

    // Função principal para executar o jogo
    void jogar() {
        int jogada = 0;
        while (!jogoTerminou()) {
            for (int i = 0; i < num_jogadores; ++i) {
                cout << "Vez do jogador " << jogadores[i].nome << endl;
                int linha, coluna;
                do {
                    cout << "Digite a linha e a coluna para jogar (ex: 0 1): ";
                    cin >> linha >> coluna;
                } while (linha < 0 || linha >= TAMANHO_MINA || coluna < 0 || coluna >= TAMANHO_MINA);

                moverJogador(i, linha, coluna);
                imprimirMina();
                exibirRanking();

                jogada++;
                if (jogada >= TAMANHO_MINA * TAMANHO_MINA) {
                    break;  // Se todas as jogadas foram feitas, interrompe o loop
                }
            }
        }

        // Após o término do jogo, exibir o ranking final
        cout << "Jogo terminado! Ranking final dos jogadores:" << endl;
        exibirRanking();
    }
};

int main() {
    int num_jogadores;
    do {
        cout << "Digite o número de jogadores (2, 3 ou 4): ";
        cin >> num_jogadores;
    } while (num_jogadores < 2 || num_jogadores > 4);

    Mina jogo(num_jogadores);
    jogo.jogar();

    return 0;
}
