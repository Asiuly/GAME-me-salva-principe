#ifndef CENARIO_H
#define CENARIO_H
#include "jogador.h"
#include "monstro.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
using namespace std;


class Cenario {
    private:
        string descricao; //descrição do cenario
        vector<string> opcoes; //opções para o player selecionar
        Monstro* monstro; //monstro do cenario (se houver)
        Cenario* dir; // Opção 1
        Cenario* esq; // Opção 2


    public: //funções explicadas no arquivo cpp
        Cenario(string);
        void addOpcao(string);
        void addMonstro(Elemento);
        void addBuraco(Jogador);
        void setCaminho(Cenario*, int);
        Cenario* getCaminho(int) const;
        Monstro getMonstro() const;
        string captarEscolha(int);
        string addBau(string, Jogador &, int*);
        Elemento aleatorizarElemento() const;
        string getDescricao() const;

        //gráficos
        void exibirBauFechado() const;
        void exibirBauAberto() const;
        void exibirEntrada() const;
        void exibirSalaDePassagem() const;
        void exibirArmadilha() const;
        void exibirMorte() const;
        void exibirMonstroFogo() const;
        void exibirPrincesa(Jogador) const;
       
        ~Cenario() { delete monstro;}
};


#endif