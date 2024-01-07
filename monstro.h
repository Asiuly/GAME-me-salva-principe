#ifndef MONSTRO_H
#define MONSTRO_H
#include "jogador.h"
#include <iostream>
#include <string>

class Monstro{
public:
    //atributos publicos
    Elemento elemento;
    Elemento fraqueza;
    string descricao;

    //construtor definindo fraqueza de acordo com elemento do monstro
    Monstro(Elemento elemento): elemento(elemento){
        if(elemento == AR){
            fraqueza = GRAMA;
            descricao = "A sala esta toda revirada! Parece ate que passou um furacao! Parece que esse monstro é um elementar do Ar!\n";
        }
        else if(elemento == GRAMA){
            fraqueza = FOGO;
            descricao = "A sala esta toda suja de terra e lama! Parece que esse monstro e um elementar da Grama! Deseja ataca-lo com qual elemento?\n";
        }
        else if(elemento == FOGO){
            fraqueza = AGUA;
            descricao = "A sala esta quente, um calor de 40 graus! Parece que esse monstro e um elementar do Fogo! Deseja ataca-lo com qual elemento?\n";
        }
        else{
            fraqueza = AR;
            descricao = "A sala esta toda molhada, pegue seu pe de pato! Parece que esse monstro e um elementar da Agua! Deseja ataca-lo com qual elemento?\n";
        }
    } 
    
    ~Monstro() {}
};

#endif