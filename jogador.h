#ifndef JOGADOR_H
#define JOGADOR_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Monstro;
class Cenario;

enum Elemento{
    AGUA,
    GRAMA,
    FOGO,
    AR
};

struct Medalha{
    Elemento elemento;
};

class Jogador {
    private:
        int vidas;
        Cenario* cenarioAtual;
    public:
        vector<Medalha> medalhas;

        Jogador(int);
        void addMedalha(Elemento);
        int getVidas() const;
        vector<Medalha> getMedalhas() const;
        bool batalhar(Monstro, string);
        void executarMorte();
        void setCenarioAtual(Cenario* cenario);
        Cenario* getCenarioAtual() const;
        ~Jogador(){}
};

#endif