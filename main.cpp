#include "jogador.h"
#include "cenario.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void seguirJornada(Jogador* jogador, string *opcaoEscolhida){
    if(jogador->getCenarioAtual()->getCaminho(1) == jogador->getCenarioAtual()->getCaminho(2)){
        //PASSA O JOGADOR PARA O PROXIMO CENARIO
        jogador->setCenarioAtual("unico");
    }

    //DESCREVE CENARIO DE PASSAGEM
    cout << jogador->getCenarioAtual()->getDescricao() << endl;
    int escolhaDoJogador;
    cin >> escolhaDoJogador;

    //JOGADOR ESCOLHE CAMINHO
    *opcaoEscolhida = jogador->getCenarioAtual()->captarEscolha(escolhaDoJogador);

    // INDO PARA CAMINHO ESCOLHIDO
    jogador->setCenarioAtual(*opcaoEscolhida);
    cout << jogador->getCenarioAtual()->getDescricao() << endl;
}

void exeMonstro(Jogador* jogador, string* opcaoEscolhida){
    //DESCRIÇÃO DO MONSTRO
    jogador->getCenarioAtual()->getMonstro().exibirMonstro();
    //JOGADOR ESCOLHE ELEMENTO
    int escolhaDoJogador;
    cin >> escolhaDoJogador;
    *opcaoEscolhida = jogador->getCenarioAtual()->captarEscolha(escolhaDoJogador);
    //BATALHA DEFINE VITÓRIA OU DERROTA DE ACORDO COM OPÇÃO DO PLAYER
    jogador->batalhar(jogador->getCenarioAtual()->getMonstro(), *opcaoEscolhida);
}

int main() {
    // ---------------------------- CONSTRUÇÃO DO JOGO -------------------------------------
    // -- DEFININDO CENARIOS DE ACORDO COM ORDEM DO DOCUMENTO --
    Cenario cenarioEntrada("============================================================================================================\nVoce se ve parado na frente de uma masmorra com duas portas laterais, precisa decidir uma direcao a seguir:\n============================================================================================================\n");
   
    Cenario cenarioMonstro("============================================================================================================\nOh Nao! Voce nao ouviu os barulhos? Acabou de entrar em uma sala com um monstro!\nPara enfrenta-lo, precisa o atacar com seu elemento oposto! Escolha um Elemento para combater o monstro:\n============================================================================================================\n\n");

    Cenario cenarioBau("============================================================================================================\nQue sorte! Voce encontra um bau do tesouro! Uma caixa arredondada com detalhes dourados ao lado.\n Isso seria uma armadilha? Deseja abrir o bau?\n============================================================================================================\n>");

    Cenario cenarioPassagem("============================================================================================================\nUfa! Um pouco de descanso, voce se depara com uma sala de passagem, parece que voce tem 2 direcoes a seguir:\n============================================================================================================\n");

    Cenario cenarioMortal("============================================================================================================\nNao! Que azar, voce abriu a porta e entrou sem prestar atençao, caiu em um buraco de mais de 20 metros!\nInfelizmente nenhuma vida extra e capaz de te salvar agora, sua jornada de heroi acaba aqui!\n============================================================================================================\n");

    Cenario cenarioArmadilha("\n============================================================================================================\nOh nao! escolha errada, voce caiu em uma armadilha e perdeu uma vida... Siga em frente sua jornada cavalheiro....\n============================================================================================================\n");

    Cenario cenarioPrincesa("============================================================================================================\nParabens! Voce chegou ao topo da masmorra, a princesa fica muito feliz em ve-lo!\n============================================================================================================\n");
    // -- DEFININDO CENARIOS DE ACORDO COM ORDEM DO DOCUMENTO --

    // -- ADICIONANDO OS CAMINHOS DOS CENÁRIOS --
    cenarioEntrada.setCaminho(&cenarioBau, 1);
    cenarioEntrada.setCaminho(&cenarioMonstro, 2);
    
    //MONSTRO TENDO ELEMENTO ALEATORIZADO
    cenarioMonstro.addMonstro(cenarioMonstro.aleatorizarElemento());

    cenarioBau.setCaminho(&cenarioPassagem, 3);
    cenarioMonstro.setCaminho(&cenarioPassagem, 3);
    cenarioArmadilha.setCaminho(&cenarioPassagem, 3);
    cenarioMortal.setCaminho(&cenarioEntrada, 3); // RECOMEÇA O JOGO
    // -- ADICIONANDO OS CAMINHOS DOS CENÁRIOS --

    // -- ADICIONANDO AS OPÇÕES DOS CENÁRIOS --
    cenarioEntrada.addOpcao("Esquerda");
    cenarioEntrada.addOpcao("Direita");
   
    cenarioMonstro.addOpcao("AGUA");
    cenarioMonstro.addOpcao("FOGO");
    cenarioMonstro.addOpcao("GRAMA");
    cenarioMonstro.addOpcao("AR");

    cenarioBau.addOpcao("IGNORAR");
    cenarioBau.addOpcao("ABRIR");
   
    cenarioPassagem.addOpcao("Esquerda");
    cenarioPassagem.addOpcao("Direita");
    // -- ADICIONANDO AS OPÇÕES DOS CENÁRIOS --
    // ---------------------------- CONSTRUÇÃO DO JOGO -------------------------------------

    // ---------------------------- EXECUÇÃO DO JOGO -------------------------------------

    // Criação e posicionamento do jogador.
    Jogador jogador(3, &cenarioEntrada);
    jogador.getCenarioAtual()->exibirEntrada();
    string opcaoEscolhida;
    int escolhaDoJogador;
    seguirJornada(&jogador, &opcaoEscolhida);

    if(opcaoEscolhida == "Esquerda"){
        // Ao ir para a esquerda, jogador se depara com um monstro.
        exeMonstro(&jogador, &opcaoEscolhida);
    }
    else{
        // Decisão de abrir o baú
        jogador.getCenarioAtual()->exibirBauFechado();
        cin >> escolhaDoJogador;
        opcaoEscolhida = jogador.getCenarioAtual()->captarEscolha(escolhaDoJogador);
        int resultadoBau; // Caso saia um monstro
       
        // Aleatorização do conteúdo do baú
        cout << cenarioBau.addBau(opcaoEscolhida, jogador, &resultadoBau) << endl;

        // Caso o conteúdo seja um monstro.
        if(resultadoBau == 5){
            // Adiciona um novo monstro e leva o jogador a ele.
            cenarioMonstro.addMonstro(cenarioMonstro.aleatorizarElemento());
            cenarioBau.setCaminho(&cenarioMonstro, 3);
            jogador.setCenarioAtual("unico");
            
            // Luta contra o monstro
            cout << "escolha um Elemento para combater o monstro:\n1- Agua\n2- Fogo\n3- Grama\n4- Ar" << endl;
            exeMonstro(&jogador, &opcaoEscolhida);
        }
    }

    // ---------------------------- MANUTENCAO ------------------------------------- //
    // Verificando fim do jogo.
    if(jogador.getVidas() == 0){
        jogador.executarMorte();
        return 0;
    }

    // Mudando cenário de passagem.
    cenarioPassagem.setCaminho(&cenarioMonstro, 1);
    // Aleatorizando elemento do monstro.
    cenarioMonstro.addMonstro(cenarioMonstro.aleatorizarElemento());
    cenarioPassagem.setCaminho(&cenarioArmadilha, 2);

    jogador.getCenarioAtual()->exibirSalaDePassagem();
    seguirJornada(&jogador, &opcaoEscolhida);
    // ---------------------------- MANUTENCAO ------------------------------------- //

    if(opcaoEscolhida == "Esquerda"){
        // Ao ir para a esquerda, jogador cai em uma armadilha.
        jogador.getCenarioAtual()->exibirArmadilha();
        jogador.setVidas((jogador.getVidas() - 1));
    }
    else{
        // Ao ir para a direita, encontra um monstro.
        exeMonstro(&jogador, &opcaoEscolhida);
    }

    // ---------------------------- MANUTENCAO -------------------------------------
    // Verificando fim do jogo.
    if(jogador.getVidas() == 0){
        jogador.executarMorte();
        return 0;
    }

    // Mudando cenário de passagem
    cenarioPassagem.setCaminho(&cenarioMortal, 1);
    cenarioPassagem.setCaminho(&cenarioBau, 2);

    jogador.getCenarioAtual()->exibirSalaDePassagem();
    seguirJornada(&jogador, &opcaoEscolhida);
    // ---------------------------- MANUTENCAO -------------------------------------

    if(opcaoEscolhida == "Esquerda"){
        // Decisão de abrir o baú
        cin >> escolhaDoJogador;
        opcaoEscolhida = jogador.getCenarioAtual()->captarEscolha(escolhaDoJogador);
        int resultadoBau; // Caso saia um monstro
       
        // Aleatorização do conteúdo do baú
        cout << cenarioBau.addBau(opcaoEscolhida, jogador, &resultadoBau) << endl;
 
        // Caso o conteúdo seja um monstro.
        if(resultadoBau == 5){
            // Adiciona um novo monstro e leva o jogador a ele.
            cenarioMonstro.addMonstro(cenarioMonstro.aleatorizarElemento());
            cenarioBau.setCaminho(&cenarioMonstro, 3);
            jogador.setCenarioAtual("unico");
            
            // Luta contra o monstro
            jogador.getCenarioAtual()->getMonstro().exibirMonstro();
            exeMonstro(&jogador, &opcaoEscolhida);
        }
    }
    else{
        // Ao ir para a direita, jogador cai em uma armadilha mortal
        jogador.executarMorte();
        return 0;
    }

    // ---------------------------- MANUTENCAO ------------------------------------- //
    // Verificando fim do jogo.
    if(jogador.getVidas() == 0){
        jogador.executarMorte();
        return 0;
    }

    // Mudando cenário de passagem.
    cenarioPassagem.setCaminho(&cenarioArmadilha, 1);
    cenarioPassagem.setCaminho(&cenarioMonstro, 2);
    // Aleatorizando elemento do monstro.
    cenarioMonstro.addMonstro(cenarioMonstro.aleatorizarElemento());

    jogador.getCenarioAtual()->exibirSalaDePassagem();
    seguirJornada(&jogador, &opcaoEscolhida);
    // ---------------------------- MANUTENCAO ------------------------------------- //

    if(opcaoEscolhida == "Esquerda"){
        // Ao ir para a esquerda, jogador encontra um monstro.
        exeMonstro(&jogador, &opcaoEscolhida);
    }
    else{
        // Ao ir para a direita, jogador cai em uma armadilha.
        jogador.getCenarioAtual()->exibirArmadilha();
        jogador.setVidas((jogador.getVidas() - 1));
    }
    
    // ---------------------------- MANUTENCAO ------------------------------------- //
    // Verificando fim do jogo.
    if(jogador.getVidas() == 0){
        jogador.executarMorte();
        return 0;
    }

    // Editando Cenário final.
    cenarioArmadilha.setCaminho(&cenarioBau, 3);
    cenarioMonstro.setCaminho(&cenarioPrincesa, 3);
    cenarioBau.setCaminho(&cenarioPrincesa, 3);

    // Jogador anda ao próximo cenário
    jogador.setCenarioAtual("unico");
    
    // Descrição do cenário
    cout << jogador.getCenarioAtual()->getDescricao() << endl;
    // ---------------------------- MANUTENCAO ------------------------------------- //


    if(jogador.getCenarioAtual() == &cenarioBau){
        // Decisão de abrir o baú
        cin >> escolhaDoJogador;
        opcaoEscolhida = jogador.getCenarioAtual()->captarEscolha(escolhaDoJogador);
        int resultadoBau; // Caso saia um monstro
       
        // Aleatorização do conteúdo do baú
        cout << cenarioBau.addBau(opcaoEscolhida, jogador, &resultadoBau) << endl;

        // Caso o conteúdo seja um monstro.
        if(resultadoBau == 5){
            // Adiciona um novo monstro e leva o jogador a ele.
            cenarioMonstro.addMonstro(cenarioMonstro.aleatorizarElemento());
            cenarioBau.setCaminho(&cenarioMonstro, 3);
            jogador.setCenarioAtual("unico");
            
            // Luta contra o monstro
            jogador.getCenarioAtual()->getMonstro().exibirMonstro();
            exeMonstro(&jogador, &opcaoEscolhida);
        }
        
        // ---------------------------- MANUTENCAO ------------------------------------- //
        // Verificando fim do jogo.
        if(jogador.getVidas() == 0){
            jogador.executarMorte();
            return 0;
        }

        // Jogador anda ao próximo cenário
        jogador.setCenarioAtual("unico");
        // Descrição do cenário
        cout << jogador.getCenarioAtual()->getDescricao() << endl;
        // ---------------------------- MANUTENCAO ------------------------------------- //
    }

    // Fim
    jogador.getCenarioAtual()->exibirPrincesa(jogador);
    // ---------------------------- EXECUÇÃO DO JOGO -------------------------------------

    return 0;
}
