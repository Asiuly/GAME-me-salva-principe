#include "jogador.h"
#include "cenario.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    Jogador jogador(3);
    
    Cenario cenarioEntrada("Voce se ve parado na frente de uma masmorra com duas portas laterais, decide entrar pela esquerda ou pela direita: (1 para esquerda, 2 para direita)");
    cenarioEntrada.addOpcao("Esquerda");
    cenarioEntrada.addOpcao("Direita");
    
    Cenario cenarioMonstro("Oh Nao! Voce nao ouviu os barulhos? Acabou de entrar em uma sala com um monstro! Para enfrenta-lo, precisa o atacar com seu elemento oposto, sera que você vai conseguir? (1 - agua, 2- fogo, 3-grama, 4- ar)");
    cenarioMonstro.addOpcao("AGUA");
    cenarioMonstro.addOpcao("FOGO");
    cenarioMonstro.addOpcao("GRAMA");
    cenarioMonstro.addOpcao("AR");
    cenarioMonstro.addMonstro(cenarioMonstro.aleatorizarElemento());

    Cenario cenarioBau("Que sorte! Voce encontra um bau do tesouro! Uma caixa arredondada com detalhes dourados ao lado, sera uma armadilha? Deseja abrir o bau? (1 para ignorar, 2 para abrir) \n> ");
    cenarioBau.addOpcao("IGNORAR");
    cenarioBau.addOpcao("ABRIR");

    jogador.setCenarioAtual(&cenarioEntrada);
    cout << cenarioEntrada.getDescricao() << endl;

    int escolhaDoJogador;

    string opcaoEscolhida = jogador.getCenarioAtual()->captarEscolha(escolhaDoJogador);

    if(opcaoEscolhida == "Esquerda"){
        jogador.setCenarioAtual(&cenarioMonstro);
        cout << jogador.getCenarioAtual()->getMonstro().descricao;
        cout << cenarioMonstro.getDescricao() << endl;
        cin >> escolhaDoJogador;

        opcaoEscolhida = jogador.getCenarioAtual()->captarEscolha(escolhaDoJogador);
        jogador.batalhar(jogador.getCenarioAtual()->getMonstro(), opcaoEscolhida);
    }
    else{
        jogador.setCenarioAtual(&cenarioBau);
        cout << cenarioBau.getDescricao() << endl;
        cin >> escolhaDoJogador;

        opcaoEscolhida = jogador.getCenarioAtual()->captarEscolha(escolhaDoJogador);
        int resultadoBau;
        cout << cenarioBau.addBau(opcaoEscolhida, jogador, &resultadoBau) << endl;

        if(resultadoBau == 5){
            jogador.setCenarioAtual(&cenarioMonstro);
            cout << "escolha um elemento para combater o monstro, (1- agua, 2- fogo, 3- grama, 4-ar) \n>";
            cout << jogador.getCenarioAtual()->getMonstro().descricao;
            cin >> escolhaDoJogador;
            opcaoEscolhida = jogador.getCenarioAtual()->captarEscolha(escolhaDoJogador);
            jogador.batalhar(jogador.getCenarioAtual()->getMonstro(), opcaoEscolhida);
        }
    }

    jogador.exibirMedalhasAcessorios();

    return 0;
}