#include "cenario.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

//inicializando a descrição que aparecerá no gráfico do cenário
Cenario:: Cenario(string descricao): descricao(descricao) { }

//adiciona uma opção que será inserida em uma caixa de seleção para o jogador
void Cenario:: addOpcao(string opcao){
    opcoes.push_back(opcao);
}

//cria um monstro para o cenario com um elemento de parametro
void Cenario:: addMonstro(Elemento elemento){
    monstro = new Monstro(elemento);
}

//retorna o monstro que habita aquele cenário
Monstro Cenario:: getMonstro() const{
    return *monstro;
}

//no momento, está sendo realizada lógica da escolha com numeros, mas após a parte
//gráfica ser implementada, vai captar a escolha do usuário e retornar
string Cenario:: captarEscolha(int escolha){
    if(escolha <= 0 || escolha > opcoes.size()){
        cout << "Escolha inválida! Por favor, escolha um número entre 1 e " << opcoes.size() << "." << endl;
        return "0!";
    }
    else{
        return opcoes[escolha-1];
    }
}

//adiciona armadilha mortal no cenario
void Cenario:: addBuraco(Jogador player){
    player.executarMorte();
}

//executa ação do baú, caso desejem abrir ou ignora-lo
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
        *resultado = numeroSorteado; //monitorar se apareceu um monstro

        //vida extra
        if(numeroSorteado==1){
            player.setVidas((player.getVidas() + 1));
            return "Parabens, acaba de ganhar uma vida extra! Parece que a sorte esta com voce, continue sua jornada!.";
        }
        //acessório azul
        else if(numeroSorteado==2){
            string cor = "azul";
            player.addAcessorio(cor);
            return "Uau! Que acessorio lindo! Com certeza a princesa ira gostar! Você acaba de achar uma tiara azul, podera ve-la na princesa se chegar ao topo da masmorra!";
        }
        //acessório rosa
        else if(numeroSorteado == 3){
            string cor = "rosa";
            player.addAcessorio(cor);
            return "Uau! Que acessorio lindo! Com certeza a princesa ira gostar! Você acaba de achar uma tiara rosa, podera ve-la na princesa se chegar ao topo da masmorra!";
        }
        //medalha de um elemento aleatório
        else if(numeroSorteado==4){
            Elemento elemento = aleatorizarElemento();

            player.addMedalha(elemento);
            return "AHAHAHA, que sorte! Agora voce pode se exibir para a princesa, apenas eu e voce saberemos que voce nao matou esse monstro.. Parabens pela medalha!";
        }
        //vai começar uma batalha contra um monstro
        else{
            return "Que azar!! Parece que a sorte nao esta com voce, esse bau estava aprisionando um monstro! Boa sorte guerreiro!";
        }
    }
}

//aleatoriza um elemento para gerar monstros e medalhas
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

//retorna descrição do cenario
string Cenario:: getDescricao() const{
    return descricao;
}

//Utilizado para monitorar a estrutura de nós de cenários com next
void Cenario:: setProximoCenario(Cenario* proximoCenario){
    this->proximoCenario = proximoCenario;
}

//retorna o proximo cenario
Cenario* Cenario:: getProximoCenario() const{
    return proximoCenario;
}