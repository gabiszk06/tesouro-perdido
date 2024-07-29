#include <iostream>
#include <iomanip>
#include <cmath>
#include<string>
#define TAMANHO 6
#define QUANTIDADE 4
#define SIZE 100
using namespace std;
int main()
{
    int opcao;
    string jogador0, jogador1, jogador2, jogador3;
    bool sair = false;
    do
    {
        cout << "quantos jogadores irao jogar:\n";
        cout << "1 - dois jogadores\n";
        cout << "2 - tres jogadores\n";
        cout << "3 - quatro jogadores\n";
        cout << "4 - sair\n";
        cin >> opcao;
        switch (opcao)
        {
        case 1:
            cout << "nome do jogador 1:\n";
            cin.get();
            getline(cin, jogador0);
            cout << jogador0 << endl;
            cout << "nome do jogador 2:\n";
            getline(cin, jogador1);
            cout << jogador1 << endl;
            sair = true;
            break;
        case 2:
            cout << "nome do jogador 1:\n";
            cin.get();
            getline(cin, jogador0);
            cout << jogador0 << endl;
            cout << "nome do jogador 2:\n";
            getline(cin, jogador1);
            cout << jogador1 << endl;
            cout<<"nome do jogador 3:\n";
            getline(cin, jogador2);
            cout<<jogador2<<endl;
            sair = true;
            break;
        case 3:
           cout << "nome do jogador 1:\n";
            cin.get();
            getline(cin, jogador0);
            cout << jogador0 << endl;
            cout << "nome do jogador 2:\n";
            getline(cin, jogador1);
            cout << jogador1 << endl;
            cout<<"nome do jogador 3:\n";
            getline(cin, jogador2);
            cout<<jogador2<<endl;
            cout<<"nome do jogador 4:\n";
            getline(cin, jogador3);
            cout<<jogador3<<endl;
            sair = true;
            break;
        case 4:
            cout<<"fim de jogo"<<endl;
            break;
        default:
            cout<<"opcao invalida"<<endl;
            break;
        }
    } while (sair != true);
}