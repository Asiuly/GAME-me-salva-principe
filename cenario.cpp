#include "cenario.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h> 
#include <chrono>

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
    while(escolha <= 0 || escolha > opcoes.size()){
        cout << "Escolha invalida! Por favor, escolha um numero entre 1 e " << opcoes.size() << "." << endl;
        cin >> escolha;
    }
    return opcoes[escolha-1];
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
        exibirBauAberto();
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
            return "Uau! Que acessorio lindo! Com certeza a princesa ira gostar! Voce acaba de achar uma tiara azul, podera ve-la na princesa se chegar ao topo da masmorra!";
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
void Cenario:: setCaminho(Cenario* proximoCenario, int direcao){
    if(direcao == 1)
        dir = proximoCenario;
    else if(direcao == 2)
        esq = proximoCenario;
    else{ // Cenário com caminho único (Exemplo: sala de monstro só vai para a de passagem)
        dir = proximoCenario;
        esq = proximoCenario;
    }
}


//retorna o proximo cenario
Cenario* Cenario:: getCaminho(int direcao) const{
    if(direcao == 1)
        return dir;
    else
        return esq;
}

void Cenario:: exibirBauFechado() const{
    cout << " _________________________________________" << endl;
    cout << "/                                         \\" << endl;
    cout << "|               Sala do Tesouro             |" << endl;
    cout << "|                                           |" << endl;
    cout << "|          ____...------------...____       |" << endl;
    cout << "|     .-`-/o/__ ____ __ __  __ \\o\\_--._     |" << endl;
    cout << "|   .'    / /                    \\ \\    '.  |" << endl;
    cout << "|   |====/o/======================\\o\\====|  |" << endl;
    cout << "|   |___/_/________..____..________\\_\\___|  |" << endl;
    cout << "|   /  _/ \\_     <_o#\\__/#o_>     _/ \\_  \\  |" << endl;
    cout << "|         \\_________\\####/_________/        |" << endl;
    cout << "|   |===\\!/========================\\!/===|  |" << endl;
    cout << "|   |   |=|          .---.         |=|   |  |" << endl;
    cout << "|   |===|o|=========/     \\========|o|===|  |" << endl;
    cout << "|   |   | |         \\() ()/        | |   |  |" << endl;
    cout << "|   |===|o|======{'-.) A (.-'}=====|o|===|  |" << endl;
    cout << "|   | __/ \\__     '-. uuu/.-'    __/ \\__ |  |" << endl;
    cout << "|   |        |==== .'.'^'.'.====|        |  |" << endl;                    
    cout << "|   |  _\\o/   __  {.' __  '.} _   _\\o/  _|  |" << endl;
    cout << "|   `====================================`  |" << endl;
    cout << "|                                           |" << endl;
    cout << "|      | 1- IGNORAR |     | 2 - ABRIR |     |" << endl;
    cout << "|                                           |" << endl;
    cout << "\\__________________________________________//" << endl;
}

void Cenario:: exibirBauAberto() const{
    cout << " _________________________________________" << endl;
    cout << "/                                         \\" << endl;
    cout << "|              BAÚ ABERTO!!               |" << endl;
    cout << "|                                         |" << endl;
    cout << "|               __________                |" << endl;
    cout << "|              /\\____;;___\\               |" << endl;
    cout << "|             | /         /               |" << endl;
    cout << "|             `. ())oo() .                |" << endl;
    cout << "|              |\\(%()*^^()^\\              |" << endl;
    cout << "|             %| |-%-------|              |" << endl;
    cout << "|            % \\ | %  ))   |              |" << endl;
    cout << "|            %  \\|%________|              |" << endl;
    cout << "|                                         |" << endl;
    cout << " \\_______________________________________/" << endl;
}

void Cenario:: exibirEntrada() const{
    cout << "   /\\                                                       /\\\n";
    cout << "  |  |                                                      |  |\n";
    cout << " /----\\                ME SALVA PRÍNCIPE!                 /----\\\n";
    cout << "[______]           APENAS PARA OS MAIS CORAJOSOS          [______]\n";
    cout << " |    |         _____                        _____         |    |\n";
    cout << " |[]  |        [     ]                      [     ]        |  []|\n";
    cout << " |    |       [_______][ ][ ][ ][][ ][ ][ ][_______]       |    |\n";
    cout << " |    [ ][ ][ ]|     |  ,----------------,  |     |[ ][ ][ ]    |\n";
    cout << " |             |     |/'    ____..____    '\\|     |             |\n";
    cout << "  \\  []        |     |    /'    ||    '\\    |     |        []  /\n";
    cout << "   |      []   |     |   |o     ||     o|   |     |  []       |\n";
    cout << "   |           |  _  |   |     _||_     |   |  _  |           |\n";
    cout << "   |   []      | (_) |   |    (_||_)    |   | (_) |       []  |\n";
    cout << "   |           |     |   |     (||)     |   |     |           |\n";
    cout << "   |           |     |   |      ||      |   |     |           |\n";
    cout << " /''           |     |   |o     ||     o|   |     |           ''\\\n";
    cout << "[_____________[_______]--'------''------'--[_______]_____________]\n";
    cout << "__________________________________________________________________\n";
    cout << "|                                                                |" << endl;
    cout << "|                | 1- ESQUERDA |     | 2 - DIREITA |             |" << endl;
    cout << "|                                                                |" << endl;
    cout << "\\______________________________________________________________//" << endl;
}

void Cenario:: exibirSalaDePassagem() const{
    cout << " ______________________________________________ \n";
    cout << "/                                              \\\n";
    cout << "|           SALA DE PASSAGEM                    |\n";
    cout << "|                                               |\n";
    cout << "|         ______                 ______         |\n"; 
    cout << "|      ,-' ;  ! `-.           ,-' ;  ! `-.      |\n";
    cout << "|     / :  !  :  . \\         / :  !  :  . \\     |\n";
    cout << "|    |_ ;   __:  ;  |       |_ ;   __:  ;  |    |\n";
    cout << "|    )| .  :)(.  !  |       )| .  :)(.  !  |    |\n";
    cout << "|    |    (##)  _   |       |    (##)  _   |    |\n";
    cout << "|    |  :  ;`'  (_) (       ) (_) :  ;`' ; |    |\n";
    cout << "|    |  :  :  .     |       |  :  :  .     |    |\n";
    cout << "|    )_ !  ,  ;  ;  |       )_ !  ,  ;  ;  |    |\n";
    cout << "|    || .  .  :  :  |       || .  .  :  :  |    |\n";
    cout << "|    |; .  |  :  .  |       |; .  |  :  .  |    |\n";
    cout << "|    |. ,._;----.___|       |. ,._;----.___|    |\n";
    cout << "|                                               |\n";
    cout << "|    | 1 - Esquerda |        | 2 - Direita |    |\n";
    cout << "|                                               |\n";
    cout << "\\_____________________________________________//\n";
}

void Cenario:: exibirArmadilha() const{
    cout << " _____________________________________________________" << endl;
    cout << "|                                                       |" << endl;
    cout << "|      OH NÃO, UMA ARMADILHA!! :( -1 VIDA, CONTINUE     |" << endl;    
    cout << "|                                                       |" << endl;
    cout << "|                         _.-'                          |" << endl;
    cout << "|         _____________.-'________________________.     |" << endl;
    cout << "|                /         _.-' O           /|          |" << endl;
    cout << "|               /  i====_======O  _________/ /          |" << endl;
    cout << "|              /  /    XX    O  /     _   /|/           |" << endl;
    cout << "|             /  /   XXXX o  /     (   / /              |" << endl;
    cout << "|            /  /    XXX   O  /_________/ /             |" << endl;
    cout << "|           /  L===========O           /|/              |" << endl;
    cout << "|          /__________________________/ /               |" << endl;
    cout << "|          __________________________|/                 |" << endl;
    cout << "|                                                       |" << endl;
    cout << "|                                                       |" << endl;
    cout << "|_______________________________________________________|" << endl;
}

void Cenario:: exibirMorte() const{
    cout << ".                                                          .\n";
    cout << ".                      FIM DO JOGO                         .\n";
    cout << ".                                                          .\n";
    cout << ".                       ______                             .\n";                         
    cout << ".                    .-\"      \"-.                        .\n";
    cout << ".                   /            \\                        .\n";
    cout << ".       _          |              |          _             .\n";
    cout << ".      ( \\         |,  .-.  .-.  ,|         / )           .\n";
    cout << ".       > \"=._     | )(__/  \\__)( |     _.=\" <          .\n";
    cout << ".      (_/\"=._\"=._ |/     /\\     \\| _.=\"_.=\"\\_)     .\n";
    cout << ".             \"=._ (_     ^^     _)\"_.=\"                .\n";
    cout << ".                 \"=\\__|IIIIII|__/=\"                    .\n";
    cout << ".                _.=\"| \\IIIIII/ |\"=._                   .\n";
    cout << ".      _     _.=\"_.=\"\\          /\"=._\"=._     _       .\n";
    cout << ".     ( \\_.=\"_.=\"     `--------`     \"=._\"=._/ )      .\n";
    cout << ".      > _.=\"                            \"=._ <          .\n";
    cout << ".     (_/                                    \\_)          .\n";
}

void Cenario:: exibirPrincesa(Jogador player) const{
    Sleep(7000);
    system("cls");
    cout << "\nA princesa está logo ali, aguarde!!";
    Sleep(5000);
    system("cls");
    cout << "                          (,);    /\\                        \n";
    cout << "                         ((  ^_   ||            ...          \n";
    cout << "                          ' /  \\  ||           (()))         \n";
    cout << "                            L {=) ||           {' ())        \n";
    cout << "                             ) -  ||            )_ (()       \n";
    cout << "                           (_   \\====       @  (   (_)       \n";
    cout << "                           | (___/{ }        \\7 \\ _) |       \n";
    cout << "                            \\____\\/)          {)=== /\\       \n";
    cout << "                            |    |             \\ |    |      \n";
    cout << "                            |_\\/\\_|               |    |      \n";
    cout << "                             |  |                |    |      \n";
    cout << "                              ) )\\               |    |      \n";
    cout << "                            _/| |/               |    |      \n";
    cout << "                           ( ,\\ |_               '~~~~'      \n";
    cout << "                            \\_(___)               _/Y        \n";

    Sleep(1500);
    system("cls");

    cout << "                          ((  ^_.     (()))\n";
    cout << "                           ' / /_\\    {' ())\n";
    cout << "                             L( '}     )_ (())\n";
    cout << "                              ) (_    (   (_)\n";
    cout << "                            (_  / }{)===='_/\n";
    cout << "                            | `/\\/\\     |   \\\n";
    cout << "                            L___/ |     |    |\n";
    cout << "                             |  . \\     |    |\n";
    cout << "                             |_/ \\_\\    |    |\n";
    cout << "                             ( ____ )   |    |\n";
    cout << "                              | | | |   |    |\n";
    cout << "                          ( --' | \\ |_  '~~~~'\n";
    cout << "                          /_/---) (___)  _/Y\n";
    cout << "                             H\n";
    cout << "                     -=======H%%O   \n";
    cout << "                             H\n";

    Sleep(1500);
    system("cls");

    cout << "                                             (\\/)\n";
    cout << "                                              \\/\n";
    cout << "\n";
    cout << "                                        (,);\n";
    cout << "                                       ((  ^_.  ... \n";
    cout << "                                        ' / /_\\(()))\n";
    cout << "                                          L( '}{' ())\n";
    cout << "                                          ) (   )_ (())\n";
    cout << "                                        (_   \\ (   (_)\n";
    cout << "                                        | (__'__\\_) |\n";
    cout << "                                         \\___|_(}==/ \\\n";
    cout << "                                         |    |  |    |\n";
    cout << "                                         |_/\\_|  |    |\n";
    cout << "                                          |  |   |    |\n";
    cout << "                                           ) )\\  |    |\n";
    cout << "                                         _/| |/  |    \\\n";
    cout << "                                        ( ,\\ |_  '~~~~/7\n";
    cout << "                                         \\_(___)  _/Y\n";
    cout << "                                      H\n";
    cout << "                              -=======H%%O \n";

    cout<< "FIM DO JOGO\n\n";
    player.exibirMedalhasAcessorios();
}