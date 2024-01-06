#include "jogador.h"
#include "cenario.h"
#include "monstro.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

Jogador:: Jogador(int numVidas): vidas(numVidas) {}

void Jogador:: addMedalha(Elemento elemento){
    Medalha medalha;
    medalha.elemento = elemento;
    medalhas.push_back(medalha);
}

vector<Medalha> Jogador:: getMedalhas() const{
    return medalhas;
}

int Jogador:: getVidas() const{
    return vidas;
}

bool Jogador:: batalhar(Monstro monstro1, string opcaoCenarioBatalha){
    Elemento elementoEscolhido;
    if (opcaoCenarioBatalha == "AGUA")
        elementoEscolhido = AGUA;
    else if(opcaoCenarioBatalha == "FOGO")
        elementoEscolhido = FOGO;
    else if(opcaoCenarioBatalha == "AR")
        elementoEscolhido = AR;
    else
        elementoEscolhido = GRAMA;
    
    
    if(elementoEscolhido == monstro1.fraqueza){
        cout << "monstro derrotado!" << endl;
        addMedalha(monstro1.elemento);
        return true;
    }
    else{
        cout << "elemento erradoo! menos uma vida" << endl;
        if(this->vidas>1)
            this->vidas -= 1;
        else
            executarMorte();

        return false;
    }
}

void Jogador:: executarMorte(){
    
}

void Jogador:: setCenarioAtual(Cenario* cenario){
    cenarioAtual = cenario;
}

Cenario* Jogador:: getCenarioAtual() const{
    return cenarioAtual;
}