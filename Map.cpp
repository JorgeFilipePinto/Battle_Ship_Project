//
// Created by jorge on 22/11/2023.
//

#include "Map.h"
#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define AZUL "\x1b[34m"

/*Construtor da Class map, o construtor irá receber um Char de defaultStatus que não é mais nem menos que o
 * caracter que se pretende para inicializar o mapa do jogador e o mapa inimigo neste caso
 * um til para o jogador e um espaço para o mapa inimigo estes podem ser alterados na Classe
 */
Map::Map(char defaultStatus){
    for(int i = 0; i < mapSizeY; i++){
        for(int j = 0; j < mapSizeX; j++){
            this->map[i][j] = defaultStatus;
        }
    }
}

//Método para vizualização do mapa
void Map::mapVeiw(){
    char rowLetter = 'A';
    std::cout<<"    1  2  3  4  5  6  7  8  9  10\n";
    for(int i=0; i < mapSizeY; i++){
        std::cout<< rowLetter <<" [";
        rowLetter++;
        for(int j=0; j < mapSizeX; j++) {
            if (this->map[i][j] == this->boatChar) {
                std::cout << GRN;
            } else if (this->map[i][j] == this->hit) {
                std::cout << RED;
            }else if(this->map[i][j] == this->water){
                std::cout << AZUL;
            }else{
                std::cout << NC;
            }
            std::cout << " " << this->map[i][j] << " " << NC;
            if(j==9){std::cout<<" ]\n";}
        }
    }
}
//Método em que elimina o ~ do mapa do jogador para ir controlando onde o adversário está a disparar, só se verifica esta situação quando o tiro falha.
void Map::tryHitBoat(int coordinateY, int coordinateX){
    map[coordinateY][coordinateX] = this->unknown;
}

//Método para inserir o character que pretendemos quando o barco é atingido.
void Map::hitBoat(int hitY, int hitX, char defaultStatus){
    map[hitY][hitX] = defaultStatus;
}


//Método para adicionar o barco ao mapa do jogador
void Map::addBoat(Boat boat){
    /*O auto serve para detetar automaticamente a tipologia da variável a seguir
     * Iremos inserir no nosso vetor todas as células do nosso barco com as suas respetivas coordenadas X e Y
     * em que para isso utilizamos o nosso método getAllCells da nossa Classe Boat
     */
    auto cells = boat.getAllCells();
    /*Quando criado o nosso vetor utilizamos o mesmo num ciclo para utilizarmos as suas coordenadas para a
     * adição do nosso CHAR á matriz para se poder vizualizar o nosso barco no mapa
     */
    for(auto cell: cells){
        map[cell.y][cell.x] = boatChar;
    }
}

//Método para verificação se o barco que se irá inserir cabe dentro do mapa.
bool Map::checkBoatSpace(Boat b){
    auto cells = b.getAllCells();
    for(auto cell : cells){
        if(!((cell.y >= 0 && cell.y < Map::mapSizeY) && (cell.x >= 0 && cell.x < Map::mapSizeX))){
            std::cout << RED << "Please insert valid coordenates!!\n" << NC;
            return false;
        }
        if(this->map[cell.y][cell.x] != this->water){
            std::cout << RED << "Boat has no space here!!\n" << NC;
            return false;
        }
    }
    return true;
};


//Validação se o barco ainda está vivo ou não
bool Map::isAlive(Boat boat){
    auto cells = boat.getAllCells();
    for(auto cell : cells) {
        if (map[cell.y][cell.x] == this->boatChar) { return true; }
    }
    return false;
};