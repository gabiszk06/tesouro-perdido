#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Estrutura para representar um jogador
struct Player {
    string name;
    int score;

    Player(string n) : name(n), score(0) {}
};

// Função para inicializar a mina com diamantes, armadilhas e espaços vazios
void initializeMine(vector<vector<char>>& mine) {
    srand(time(nullptr));  // inicializa a semente para gerar números aleatórios

    int rows = mine.size();
    int cols = mine[0].size();

    // Preenche a mina com espaços vazios inicialmente
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mine[i][j] = ' ';
        }
    }

    // Coloca diamantes (de 1 a 10)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (rand() % 100 < 50) {  // 50% de chance de ter um diamante
                mine[i][j] = '0' + (rand() % 10 + 1);  // números de '1' a '10'
            }
        }
    }

    // Coloca armadilhas e pistas
    int totalCells = rows * cols;
    int trapCells = totalCells * 0.10;  // 10% de células serão armadilhas ou pistas
    int clueCells = totalCells * 0.05;  // 5% de células serão pistas

    while (trapCells > 0) {
        int r = rand() % rows;
        int c = rand() % cols;
        if (mine[r][c] == ' ') {
            int type = rand() % 3;  // 0 para 'O', 1 para '-', 2 para '+'
            if (type == 0) mine[r][c] = 'O';
            else if (type == 1) mine[r][c] = '-';
            else if (type == 2) mine[r][c] = '+';
            trapCells--;
        }
    }
}

// Função para imprimir o estado atual da mina
void printMine(const vector<vector<char>>& mine) {
    int rows = mine.size();
    int cols = mine[0].size();

    cout << "Estado atual da mina:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << mine[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

// Função para imprimir o ranking dos jogadores
void printRanking(const vector<Player>& players) {
    cout << "Ranking dos jogadores:" << endl;
    for (const Player& player : players) {
        cout << player.name << ": " << player.score << " pontos" << endl;
    }
    cout << endl;
}

int main() {
    int numPlayers;
    cout << "Informe o número de jogadores (2, 3 ou 4): ";
    cin >> numPlayers;

    vector<Player> players;
    for (int i = 0; i < numPlayers; ++i) {
        string name;
        cout << "Informe o nome do jogador " << i+1 << ": ";
        cin >> name;
        players.emplace_back(name);
    }

    int rows = 6;  // número mínimo de linhas da mina
    int cols = 6;  // número mínimo de colunas da mina
    vector<vector<char>> mine(rows, vector<char>(cols, ' '));

    initializeMine(mine);

    bool gameOver = false;
    int currentPlayer = 0;
    int totalMoves = rows * cols;
    int movesLeft = totalMoves;

    while (!gameOver) {
        cout << "Jogador atual: " << players[currentPlayer].name << endl;
        printMine(mine);

        // Simulação da jogada (aqui seria implementada a lógica de movimentação na mina)

        // Exemplo: jogador move para uma posição válida e atualiza a pontuação

        // Atualização da pontuação do jogador
        players[currentPlayer].score += 5;  // Exemplo de atualização

        printRanking(players);

        movesLeft--;
        currentPlayer = (currentPlayer + 1) % numPlayers;

        if (movesLeft == 0) {
            gameOver = true;
            cout << "Fim do jogo!" << endl;
        }
    }

    return 0;
}
