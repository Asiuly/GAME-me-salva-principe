#include "jogador.h"
#include "cenario.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    Jogador jogador(3);
    
    Cenario cenarioEntrada("Voce se ve parado na frente de uma masmorra com duas portas laterais, precisa decidir uma direcao a seguir:\n1- Esquerda\n2- Direita ");
    cenarioEntrada.addOpcao("Esquerda");
    cenarioEntrada.addOpcao("Direita");
    
    Cenario cenarioMonstro("Oh Nao! Voce nao ouviu os barulhos? Acabou de entrar em uma sala com um monstro! Para enfrenta-lo, precisa o atacar com seu elemento oposto, sera que voce vai conseguir? escolha um Elemento para combater o monstro:\n1- Agua\n2- Fogo\n3- Grama\n4- Ar ");
    cenarioMonstro.addOpcao("AGUA");
    cenarioMonstro.addOpcao("FOGO");
    cenarioMonstro.addOpcao("GRAMA");
    cenarioMonstro.addOpcao("AR");
    cenarioMonstro.addMonstro(cenarioMonstro.aleatorizarElemento());

    Cenario cenarioBau("Que sorte! Voce encontra um bau do tesouro! Uma caixa arredondada com detalhes dourados ao lado, sera uma armadilha? Deseja abrir o bau?\n1- Ignorar\n2- Abrir ");
    cenarioBau.addOpcao("IGNORAR");
    cenarioBau.addOpcao("ABRIR");

    Cenario cenarioPassagem("Ufa! Um pouco de descanso, voce se depara com uma sala de passagem, parece que voce tem 2 direcoes a seguir:\n1- Esquerda\n2- Direita ");
    cenarioPassagem.addOpcao("Esquerda");
    cenarioPassagem.addOpcao("Direita");

    Cenario cenarioMortal("Nao! Que azar, voce abriu a porta e entrou sem prestar atençao, caiu em um buraco de mais de 20 metros! Infelizmente nenhuma vida extra e capaz de te salvar agora, sua jornada de heroi acaba aqui!");

    Cenario cenarioArmadilha("Oh nao! escolha errada, voce perdeu uma vida, siga em frente sua jornada cavalheiro....");

    jogador.setCenarioAtual(&cenarioEntrada);
    cout << cenarioEntrada.getDescricao() << endl;

    int escolhaDoJogador;
    cin >> escolhaDoJogador;

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
            cout << jogador.getCenarioAtual()->getMonstro().descricao;
            cout << "escolha um Elemento para combater o monstro:\n1- Agua\n2- Fogo\n3- Grama\n4- Ar";
            cin >> escolhaDoJogador;
            opcaoEscolhida = jogador.getCenarioAtual()->captarEscolha(escolhaDoJogador);
            jogador.batalhar(jogador.getCenarioAtual()->getMonstro(), opcaoEscolhida);
        }
    }

    jogador.setCenarioAtual(&cenarioPassagem);
    cout << cenarioPassagem.getDescricao() << endl;
    cin >> escolhaDoJogador;
    opcaoEscolhida = jogador.getCenarioAtual()->captarEscolha(escolhaDoJogador);

    if(opcaoEscolhida == "Esquerda"){
        jogador.setCenarioAtual(&cenarioArmadilha);
        cout << cenarioArmadilha.getDescricao();
        jogador.setVidas((jogador.getVidas() - 1)); // criar funcao perde vida? MELHOR (verificacao de se vida =1 morre).
    }
    else{
        jogador.setCenarioAtual(&cenarioMonstro);
        cout << jogador.getCenarioAtual()->getMonstro().descricao;
        cout << cenarioMonstro.getDescricao() << endl;
        cin >> escolhaDoJogador;
        opcaoEscolhida = jogador.getCenarioAtual()->captarEscolha(escolhaDoJogador);
        jogador.batalhar(jogador.getCenarioAtual()->getMonstro(), opcaoEscolhida);
    }

    jogador.exibirMedalhasAcessorios();

    return 0;
}