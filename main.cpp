#include "jogador.h"
#include "cenario.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {

    //DEFININDO CENARIOS DE ACORDO COM ORDEM DO DOCUMENTO
    Cenario cenarioEntrada("Voce se ve parado na frente de uma masmorra com duas portas laterais, precisa decidir uma direcao a seguir:\n1- Esquerda\n2- Direita ");
    
    Cenario cenarioMonstro("Oh Nao! Voce nao ouviu os barulhos? Acabou de entrar em uma sala com um monstro! Para enfrenta-lo, precisa o atacar com seu elemento oposto, sera que voce vai conseguir? escolha um Elemento para combater o monstro:\n1- Agua\n2- Fogo\n3- Grama\n4- Ar ");

    Cenario cenarioBau("Que sorte! Voce encontra um bau do tesouro! Uma caixa arredondada com detalhes dourados ao lado, sera uma armadilha? Deseja abrir o bau?\n1- Ignorar\n2- Abrir ");

    Cenario cenarioPassagem("Ufa! Um pouco de descanso, voce se depara com uma sala de passagem, parece que voce tem 2 direcoes a seguir:\n1- Esquerda\n2- Direita ");

    Cenario cenarioMortal("Nao! Que azar, voce abriu a porta e entrou sem prestar atençao, caiu em um buraco de mais de 20 metros! Infelizmente nenhuma vida extra e capaz de te salvar agora, sua jornada de heroi acaba aqui!");

    Cenario cenarioArmadilha("Oh nao! escolha errada, voce perdeu uma vida, siga em frente sua jornada cavalheiro....");

    //ADICIONANDO AS OPÇÕES DOS CENÁRIOS
    cenarioEntrada.addOpcao("Esquerda");
    cenarioEntrada.addOpcao("Direita");
    
    cenarioMonstro.addOpcao("AGUA");
    cenarioMonstro.addOpcao("FOGO");
    cenarioMonstro.addOpcao("GRAMA");
    cenarioMonstro.addOpcao("AR");
    //MONSTRO TENDO ELEMENTO ALEATORIZADO
    cenarioMonstro.addMonstro(cenarioMonstro.aleatorizarElemento()); 

    cenarioBau.addOpcao("IGNORAR");
    cenarioBau.addOpcao("ABRIR");
    
    cenarioPassagem.addOpcao("Esquerda");
    cenarioPassagem.addOpcao("Direita");

    //EXIBINDO DESCRIÇÃO DA ENTRADA DA MASMORRA
    cout << cenarioEntrada.getDescricao() << endl;

    //JOGADOR FAZ SUA ESCOLHA
    int escolhaDoJogador;
    cin >> escolhaDoJogador;

    //CRIANDO JOGADOR POSICIONANDO-O NA ENTRADA
    Jogador jogador(3, &cenarioEntrada);
    //CAPTA ESCOLHA DO JOGADOR E PASSA PARA UMA STRING
    string opcaoEscolhida = jogador.getCenarioAtual()->captarEscolha(escolhaDoJogador);

    //ANALISA ESCOLHA DO JOGADOR E APLICA CONSEQUENCIAS DA AÇÃO
    if(opcaoEscolhida == "Esquerda"){
        //AO IR PARA ESQUERDA, ENCONTRA UM MONSTRO
        cenarioEntrada.setProximoCenario(&cenarioMonstro);
        jogador.setCenarioAtual();

        //DESCRIÇÃO DA SALA
        cout << jogador.getCenarioAtual()->getMonstro().descricao;
        cout << cenarioMonstro.getDescricao() << endl;
        //JOGADOR ESCOLHE ELEMENTO
        cin >> escolhaDoJogador;
        opcaoEscolhida = jogador.getCenarioAtual()->captarEscolha(escolhaDoJogador);
        //BATALHA DEFINE VITÓRIA OU DERROTA DE ACORDO COM OPÇÃO DO PLAYER
        jogador.batalhar(jogador.getCenarioAtual()->getMonstro(), opcaoEscolhida);

        //PERDEENDO OU GANHANDO, VAMOS PARA SALA DE PASSAGEM
        cenarioMonstro.setProximoCenario(&cenarioPassagem);
    }
    else{
        //CASO A ESCOLHA TENHA SIDO A DIREITA, ENCONTRA UM BAÚ
        cenarioEntrada.setProximoCenario(&cenarioBau);
        jogador.setCenarioAtual();
        //DESCREVE A SALA
        cout << cenarioBau.getDescricao() << endl;
        //JOGADOR DECIDE SE ABRE OU NÃO O BAÚ
        cin >> escolhaDoJogador;
        opcaoEscolhida = jogador.getCenarioAtual()->captarEscolha(escolhaDoJogador);
        int resultadoBau; //MONITORA SE TEM MONSTRO NO BAU
        
        //RANDOMIZA UM PREMIO E EXECUTA A CONSEQUENCIA PARA O JOGADOR
        cout << cenarioBau.addBau(opcaoEscolhida, jogador, &resultadoBau) << endl;

        //CASO TENHA UM MONSTRO NO BAU
        if(resultadoBau == 5){
            //REUTILIZA O CENARIO DE MONSTRO POR DESCRIÇÃO E OPÇÕES
            cenarioMonstro.addMonstro(cenarioMonstro.aleatorizarElemento());
            cenarioBau.setProximoCenario(&cenarioMonstro);
            
            //JOGADOR VAI ATÉ O MONSTRO E ESCOLHE ELEMENTO
            jogador.setCenarioAtual();
            cout << jogador.getCenarioAtual()->getMonstro().descricao;
            cout << "escolha um Elemento para combater o monstro:\n1- Agua\n2- Fogo\n3- Grama\n4- Ar";
            cin >> escolhaDoJogador;
            opcaoEscolhida = jogador.getCenarioAtual()->captarEscolha(escolhaDoJogador);
            //BATALHA VITORIA OU DERROTA
            jogador.batalhar(jogador.getCenarioAtual()->getMonstro(), opcaoEscolhida);
        }
        //INDEPENDENTE DO PREMIO DO BAU, VAMOS PARA SALA DE PASSAGEM
        cenarioBau.setProximoCenario(&cenarioPassagem);
    }

    //PASSA O JOGADOR PARA O PROXIMO CENARIO
    jogador.setCenarioAtual();
    //DESCREVE CENARIO
    cout << cenarioPassagem.getDescricao() << endl;
    cin >> escolhaDoJogador;
    //JOGADOR ESCOLHE CAMINHO
    opcaoEscolhida = jogador.getCenarioAtual()->captarEscolha(escolhaDoJogador);


    if(opcaoEscolhida == "Esquerda"){
        cenarioPassagem.setProximoCenario(&cenarioArmadilha);
        jogador.setCenarioAtual();
        cout << cenarioArmadilha.getDescricao();
        jogador.setVidas((jogador.getVidas() - 1));
        cenarioArmadilha.setProximoCenario(&cenarioPassagem);
    }
    else{
        cenarioPassagem.setProximoCenario(&cenarioMonstro);
        jogador.setCenarioAtual();
        cout << jogador.getCenarioAtual()->getMonstro().descricao;
        cout << cenarioMonstro.getDescricao() << endl;
        cin >> escolhaDoJogador;
        opcaoEscolhida = jogador.getCenarioAtual()->captarEscolha(escolhaDoJogador);
        jogador.batalhar(jogador.getCenarioAtual()->getMonstro(), opcaoEscolhida);
        cenarioMonstro.setProximoCenario(&cenarioPassagem);
    }

    //ADICIONAR TODA SEQUENCIA DE CENARIOS

    jogador.exibirMedalhasAcessorios();

    return 0;
}