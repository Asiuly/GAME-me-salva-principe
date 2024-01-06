#include "jogador.h"
#include "cenario.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    Jogador jogador(3);

    
    Cenario cenario1("Voce se ve parado na frente de uma masmorra com duas portas laterais, decide entrar pela esquerda ou pela direita:");
    cenario1.addOpcao("Esquerda");
    cenario1.addOpcao("Direita");
    jogador.setCenarioAtual(&cenario1);

    Cenario cenario2("Você encontrou um monstro! adivinhe seu elemento e tente mata-lo com uma das seguintes opcoes");
    cenario2.addOpcao("AGUA");
    cenario2.addOpcao("FOGO");
    cenario2.addOpcao("GRAMA");
    cenario2.addOpcao("AR");
    cenario2.addMonstro(FOGO, AGUA);
    jogador.setCenarioAtual(&cenario2);

    int escolhaDoJogador;
    cout << "Escolha a opção que desejar(entre 1 e 4 nesse caso)";
    cin >> escolhaDoJogador;

    string opcaoEscolhida = jogador.getCenarioAtual()->captarEscolha(escolhaDoJogador);
    jogador.batalhar(jogador.getCenarioAtual()->getMonstro(), opcaoEscolhida);

    cout << "fim do jogo";

    return 0;
}