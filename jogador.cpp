#include "jogador.h"
#include "cenario.h"
#include "monstro.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//inicializa o jogador com um numero de vidas e no cecnario de entrada criado na main(onde estamos monitorando os cenarios)
Jogador:: Jogador(int numVidas, Cenario* cenarioEntrada): vidas(numVidas), cenarioAtual(cenarioEntrada) {}

//adiciona uma medalha à coleção do player
void Jogador:: addMedalha(Elemento elemento){
    Medalha medalha;
    medalha.elemento = elemento;
    medalhas.push_back(medalha);
}

//retorna todas as medalhas do player
vector<Medalha> Jogador:: getMedalhas() const{
    return medalhas;
}

//retorna o número de vidas restantes
int Jogador:: getVidas() const{
    return vidas;
}

//de acordo com a opção do jogador, verifica se o monstro será derrotado
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
    //convertendo string para elemento
    
    if(elementoEscolhido == monstro1.fraqueza){
        cout << "Muito bem! Parece que voce entende de elementos! Aqui esta uma medalha por sua bela conquista! A princesa ficara orgulhosa, pode prosseguir seu caminho em paz!" << endl;
        addMedalha(monstro1.elemento);
        return true;
        //derrotou o monstro ganhou a medalha
    }
    else{
        cout << "Naoo! Parece que voce se confundiu ao atacar os elementos, Ninguem ira ficar sabendo dessa falha, voce perdeu uma vida!" << endl;

        if(this->vidas>1){
            cout << "Parece que voce deu sorte dessa vez! Escapou do elementar por pouco! Fuja dessa sala imediatamente e esconda esse fracasso… Boa sorte da proxima vez!" << endl;
            this->vidas -= 1;
        }
        else{
            cout << "Parece que esse elementar era mais do que voce podia lidar, infelizmente sua jornada de heroi acaba aqui! Dê uma olhada no seu legado:" << endl;
            executarMorte();//jogador morre se tiver apenas 1 vida
        }
        
        return false;
    }
}

void Jogador:: executarMorte(){
    cout << "O jogo acabou, você perdeu! aqui está seu legado:" << endl;
    vidas = 0;
    exibirMedalhasAcessorios();
    cout << "fim do jogo";
    delete this;
}

//passa para o proximo cenario pré-definido
void Jogador:: setCenarioAtual(){
    cenarioAtual = this->getCenarioAtual()->getProximoCenario();
}

//retorna o cenário atual do jogador
Cenario* Jogador:: getCenarioAtual() const{
    return cenarioAtual;
}

//atualiza quantidade de vidas
void Jogador:: setVidas(int vida) {
    this->vidas = vida;
}

//adiciona um acessório à coleção do jogador
void Jogador:: addAcessorio(string cor){
    Acessorio acessorio;
    acessorio.cor = cor;

    acessorios.push_back(acessorio);
}

//retorna todos os acessórios adquiridos pelo player
vector<Acessorio> Jogador:: getAcessorio() const{
    return acessorios;
}

//exibe o legado do jogador
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