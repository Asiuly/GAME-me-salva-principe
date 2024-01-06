#ifndef CENARIO_H
#define CENARIO_H
#include "jogador.h"
#include "monstro.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Cenario {
    private:
        string descricao;
        vector<string> opcoes;
        vector<Cenario*> caminhosSeguintes;
        Monstro* monstro;

    public:
        Cenario(string);
        void addOpcao(string opcao);
        void retirarVida(Jogador);
        void addMonstro(Elemento elemento, Elemento fraqueza);
        Monstro getMonstro() const;
        string captarEscolha(int);

        ~Cenario() {}
};

#endif