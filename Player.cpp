//
// Created by jorge on 22/11/2023.
//

#include "Player.h"

/*Construtor da Class, o construtor irá receber o nome do jogador e em seguida irá
 * criar dois mapas ou seja dois objetos da Class Map que é o seu map e o mapa enimigo
 */
Player::Player(std::string name) : map{Map::water}, enemyMap{Map::unknown}{
    this->name = name;
}

/*Quando criado um barco o mesmo é colocado dentro de um vetor,
 * O jogador irá ter um valor de vida em que o valor do mesmo é atribuido consoante o tamanho
 * dos barcos que são adicionados a mesma irá descer a cada tiro em que seja atingido
 */
void Player::addBoat(Boat boat){
    this->boats.emplace_back(boat);
    this->health+=boat.size;
    this->map.addBoat(boat);
}