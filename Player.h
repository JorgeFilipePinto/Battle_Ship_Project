//
// Created by jorge on 24/11/2023.
//

#pragma once
#include <iostream>
#include "Boat.h"
#include "Map.h"

class Player{
public:
    std::string name;
    int health{0};
    std::vector<Boat> boats;
    Map map, enemyMap;
    Player(std::string name);
    void addBoat(Boat name);
    std::string tempBoatHitName;
    bool hitBoat{false};
};
/*O ficheiro header ou .h serve para criar a Classe e iniciar a mesma declarando assim todas as nossas variáveis e métodos
 * que iram fazer parte da nossa Classe. Podendo assim aqui também poder definir quais ficam com acesso externo há classe ou não
 * através a tipologia de publico ou privado
 */