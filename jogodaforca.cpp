#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;


string palavra_secreta;
vector<char> acertos;

bool chute_acertou(char chute) {
    for (char letra : palavra_secreta) {
        if (chute == letra) {
            acertos.push_back(chute);
            return true;
        }
    }

    return false;
}

void imprimir_palavra() {

    bool achou = false;

    for (char letra : palavra_secreta) {
        for (char acerto : acertos) {
            if (acerto == letra) {
                cout << letra << " ";
                achou = true;
                break;
            }

        }
        if (!achou) {
            cout << "_ ";
        }

        achou = false;
    }

    cout << endl;
}

bool ganhou() {

    bool tem_letra = false;

    for (char letra : palavra_secreta) {
        for (char acerto : acertos) {
            if (letra == acerto) {
                tem_letra = true;
            }
        }

        if (!tem_letra) {
            return false;
        }

        tem_letra = false;
    }

    return true;
}

void abrir_arquivo() {
    ifstream arquivo;
    arquivo.open("arquivo.txt");

    if (!arquivo.is_open()) {
        cout << "Não foi possível abrir a base de dados do jogo" << endl;
        exit(1);
    }

    int quantidade_de_palavras;

    arquivo >> quantidade_de_palavras;

    unsigned seed = time(0);

    srand(seed);

    int numero_aleatorio = rand()%(quantidade_de_palavras + 1);

    string palavra_lida;

    for (int i = -1; i < numero_aleatorio; i++) {
        arquivo >> palavra_lida;
    }

    palavra_secreta = palavra_lida;
}

int main() {
    
    cout << "*************************" << endl;
    cout << "******Jogo da Forca******" << endl;
    cout << "*************************" << endl;
    cout << endl;

    abrir_arquivo();

    int numero_de_erros = 5;

    while (numero_de_erros > 0 && !ganhou()) {

        cout << "Você pode errar " << numero_de_erros << " vezes" << endl;

        imprimir_palavra();

        char chute;

        cin >> chute;
        
        if (chute_acertou(chute)) {
            cout << "Parabéns! A letra " << chute << " está na palavra." << endl;
        } else {
            cout << "A letra " << chute << " não está na palavra." << endl;
            --numero_de_erros;
        } 
    }

    if (numero_de_erros == 0) {
        cout << "Você perdeu! Tente novamente!" << endl;
        cout << "A palavra era: " << palavra_secreta << endl;
    } else {
        cout << "Parabéns! Você acertou a palavra: " << palavra_secreta << endl;
    }
}
