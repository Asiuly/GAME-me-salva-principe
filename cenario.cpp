#include "cenario.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

Cenario:: Cenario(string descricao): descricao(descricao) { }

void Cenario:: addOpcao(string opcao){
    opcoes.push_back(opcao);
}

void Cenario:: addMonstro(Elemento elemento, Elemento fraqueza){
    monstro = new Monstro(elemento, fraqueza);
}

Monstro Cenario:: getMonstro() const{
    return *monstro;
}

string Cenario:: captarEscolha(int escolha){
    if(escolha <= 0 || escolha > opcoes.size()){
        cout << "escolha invalida";
        return "0!";
    }
    else{
        return opcoes[escolha-1];
    }
}