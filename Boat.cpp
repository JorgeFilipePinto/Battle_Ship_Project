//
// Created by jorge on 22/11/2023.
//

#include "Boat.h"

/*Contrutor da Classe Boat serve para criar o nosso objeto da Classe, o construtor irá receber:
 * - a rotação do barco,
 * - o seu tamanho,
 * - uma estrutura com a posição de x e y,
 * - nome do barco que se irá criar
 */
Boat::Boat(bool rotation, point2D pos, int size, std::string name){
    this->rotation = rotation;                                      //Rotação do barco que será uma BOOL
    this->size = size;                                              //Tamanho do barco que será INT
    this->pos = pos;                                                //pos é um Poit2D que é uma estrutura que armazena a posição x e y do barco
    this->name = name;                                              //Nome do barco
}

//Método para verificação se o tiro dado pelo jogador adversário acertou em algum barco
bool Boat::doesHitYou(int x, int y){
    auto boatCells = getAllCells();
    for(auto cell: boatCells){
        if(cell.x == x && cell.y == y){return true;}
    }
    return false;
}

//vetor para se obter todas as células ocupadas por cada barco
std::vector<point2D> Boat::getAllCells(){
    std::vector<point2D> boatCells;
    for (int i=0; i< this->size; i++){
        if(this->rotation){
            boatCells.emplace_back(point2D{pos.x+i,pos.y});
        }else{
            boatCells.emplace_back(point2D{pos.x,pos.y+i});
        }
    }
    return boatCells;
}

