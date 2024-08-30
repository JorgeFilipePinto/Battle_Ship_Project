//
// Created by jorge on 22/11/2023.
//
#pragma once
#include<iostream>
#include"Boat.h"


class Map{
public:
    static const int mapSizeX=10, mapSizeY=10;
    static const char water='~', hit='X', boatChar='B', unknown=' ';
    static const int numberOfBoats{5};
    void addBoat(Boat);
    void mapVeiw();
    Map(char);
    bool checkBoatSpace(Boat b);
    void hitBoat(int hitY, int hitX, char defaultStatus);
    void tryHitBoat(int coordinateY, int coordinateX);
    bool isAlive(Boat);
private:

    char map[Map::mapSizeY][mapSizeX];
};
/*O ficheiro header ou .h serve para criar a Classe e iniciar a mesma declarando assim todas as nossas variáveis e métodos
 * que iram fazer parte da nossa Classe. Podendo assim aqui também poder definir quais ficam com acesso externo há classe ou não
 * através a tipologia de publico ou privado
 */
