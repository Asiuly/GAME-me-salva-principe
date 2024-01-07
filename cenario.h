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
        string descricao; //descrição do cenario
        vector<string> opcoes; //opções para o player selecionar
        Monstro* monstro; //monstro do cenario (se houver)
        Cenario* proximoCenario; //next cenario

    public: //funções explicadas no arquivo cpp
        Cenario(string);
        void addOpcao(string);
        void retirarVida(Jogador);
        void addMonstro(Elemento);
        void addBuraco(Jogador);
        void setProximoCenario(Cenario*);
        Cenario* getProximoCenario() const;
        Monstro getMonstro() const;
        string captarEscolha(int);
        string addBau(string, Jogador &, int*);
        Elemento aleatorizarElemento() const;
        string getDescricao() const;
        
        ~Cenario() { delete monstro;}
};

#endif