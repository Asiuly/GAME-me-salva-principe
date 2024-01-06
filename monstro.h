#ifndef MONSTRO_H
#define MONSTRO_H
#include "jogador.h"
#include <iostream>
#include <string>

class Monstro{
public:
    Elemento elemento;
    Elemento fraqueza;
    string tipo;

    Monstro(Elemento elemento, Elemento fraqueza): elemento(elemento), fraqueza(fraqueza), tipo("MONSTRO") {} 
    void atacar(Jogador player) const{
    
    }
    ~Monstro() {}
};

#endif