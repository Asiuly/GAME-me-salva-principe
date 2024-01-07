#include "cenario.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

Cenario:: Cenario(string descricao): descricao(descricao) { }

void Cenario:: addOpcao(string opcao){
    opcoes.push_back(opcao);
}

void Cenario:: addMonstro(Elemento elemento){
    monstro = new Monstro(elemento);
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

void Cenario:: addBuraco(Jogador player){
    player.executarMorte();
}

string Cenario:: addBau(string escolhaDoJogador, Jogador &player, int* resultado){
    //bau encontrado
    if(escolhaDoJogador=="IGNORAR"){
        *resultado = 0;
        return "Alguns nao nasceram com a coragem suficiente para olhar dentro de um bau! Tudo bem, continue sua jornada, Ninguem ficara sabendo desse seu ato de covardia…";
    }
    else{
        //sortear um numero de 1 a 5 para o jogador receber sua recompensa
        srand(static_cast<int>(time(nullptr)));
        int numeroSorteado = rand() % 5 + 1;
        *resultado = numeroSorteado;

        if(numeroSorteado==1){
            player.setVidas((player.getVidas() + 1));
            return "Parabens, acaba de ganhar uma vida extra! Parece que a sorte esta com voce, continue sua jornada!.";
        }
        else if(numeroSorteado==2){
            string cor = "azul";
            player.addAcessorio(cor);
            return "Uau! Que acessorio lindo! Com certeza a princesa ira gostar! Você acaba de achar uma tiara azul, podera ve-la na princesa se chegar ao topo da masmorra!";
        }
        else if(numeroSorteado == 3){
            string cor = "rosa";
            player.addAcessorio(cor);
            return "Uau! Que acessorio lindo! Com certeza a princesa ira gostar! Você acaba de achar uma tiara rosa, podera ve-la na princesa se chegar ao topo da masmorra!";
        }
        else if(numeroSorteado==4){
            Elemento elemento = aleatorizarElemento();

            player.addMedalha(elemento);
            return "AHAHAHA, que sorte! Agora voce pode se exibir para a princesa, apenas eu e voce saberemos que voce nao matou esse monstro.. Parabens pela medalha!";
        }
        else{
            return "Que azar!! Parece que a sorte nao esta com voce, esse bau estava aprisionando um monstro! Boa sorte guerreiro!";
        }
    }
}

Elemento Cenario:: aleatorizarElemento() const{
    srand(static_cast<int>(time(nullptr)));
    int numeroSorteado = rand() % 4 + 1;
    Elemento elemento;

    if(numeroSorteado==1)
        elemento = AR;
    else if(numeroSorteado==2)
        elemento = GRAMA;
    else if(numeroSorteado==3)
        elemento = AGUA;
    else
        elemento = FOGO;

    return elemento;
}

string Cenario:: getDescricao() const{
    return descricao;
}