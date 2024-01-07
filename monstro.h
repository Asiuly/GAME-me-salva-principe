#ifndef MONSTRO_H
#define MONSTRO_H
#include "jogador.h"
#include <iostream>
#include <string>

class Monstro{
public:
    Elemento elemento;
    Elemento fraqueza;
    string descricao;

    Monstro(Elemento elemento): elemento(elemento){
        if(elemento == AR){
            fraqueza = GRAMA;
            descricao = "A sala está toda revirada! Parece ate que passou um furacao! Parece que esse monstro é um elementar do Ar!";
        }
        else if(elemento == GRAMA){
            fraqueza = FOGO;
            descricao = "A sala esta toda suja de terra e lama! Parece que esse monstro e um elementar da Grama! Deseja ataca-lo com qual elemento?";
        }
        else if(elemento == FOGO){
            fraqueza = AGUA;
            descricao = "A sala esta quente, um calor de 40º! Parece que esse monstro e um elementar do Fogo! Deseja ataca-lo com qual elemento?";
        }
        else{
            fraqueza = AR;
            descricao = "A sala está toda suja de terra e lama! Parece que esse monstro é um elementar da Grama!";
        }
    } 
    
    void atacar(Jogador player) const{
    
    }
    ~Monstro() {}
};

#endif