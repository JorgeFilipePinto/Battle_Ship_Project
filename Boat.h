//
// Created by jorge on 24/11/2023.
//

#pragma once
#include <iostream>
#include <vector>


struct point2D{
    int x;
    int y;
};

class Boat{
public:
    Boat(bool rotation, point2D, int, std::string);
    bool doesHitYou(int, int);
    std::vector<point2D> getAllCells();
    int size;
    bool rotation;
    std::string name;
    point2D pos;
private:
};
/*O ficheiro header ou .h serve para criar a Classe e iniciar a mesma declarando assim todas as nossas variáveis e métodos
 * que iram fazer parte da nossa Classe. Podendo assim aqui também poder definir quais ficam com acesso externo há classe ou não
 * através a tipologia de publico ou privado
 */