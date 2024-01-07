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

void Jogador:: setVidas(int vida) {
    this->vidas = vida;
}

void Jogador:: addAcessorio(string cor){
    Acessorio acessorio;
    acessorio.cor = cor;

    acessorios.push_back(acessorio);
}

vector<Acessorio> Jogador:: getAcessorio() const{
    return acessorios;
}

void Jogador:: exibirMedalhasAcessorios() const{
    
    if(medalhas.size() == 0){
        cout << "medalhas: 0" << endl;
    }
    else{
        cout << "medalhas" << endl;
        for(int i=0; i<medalhas.size(); i++){
            if(medalhas[i].elemento==FOGO){
                cout << "+1 medalha de FOGO" << endl;
            }
            else if(medalhas[i].elemento == AGUA){
                cout << "+1 medalha de AGUA" << endl;
            }
            else if(medalhas[i].elemento == GRAMA){
                cout << "+1 medalha de GRAMA" << endl;
            }
            else{
                cout << "+1 medalha de AR" << endl;
            }
        }
    }

    if(acessorios.size() == 0){
        cout << "acessorios: 0" << endl;
    }
    else{
        cout << "acessorios" << endl;
        for(int i=0; i<acessorios.size(); i++){
            cout << "+1 acessorio da cor " << acessorios[i].cor << endl;
        }
    }

    cout << "quantidade de vidas: " << getVidas() << endl;

}