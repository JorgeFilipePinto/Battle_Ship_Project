//
// Created by jorge on 20/11/2023.
//

//Importação de bibliotecas e as classes do projeto
#include<iostream>
#include <limits>
#include "Player.h"
#include "Boat.h"
#include "Map.h"
#define NC "\e[0m"
#define RED "\e[0;31m"
#define REDS "\e[0;41m"
#define PRP "\e[0;35m"
#define PRPS "\e[0;45m"
#define GRN "\e[0;32m"
#define GRNS "\e[0;42m"
#define AZUL "\x1b[34m"

int main(){
    /*Array com os tamanhos dos barcos usados em jogo
     * Esta Array irá ser usada para inserir automaticamente o tamanho na criação do objeto BOAT
     */
    int boatSizes[5]{2,3,3,4,5};

    //Lista com os respetivos nomes dos objetos BOAT que iram ser criados
    std::string boatNames[5]{"Destroyer",
                             "Submarine",
                             "Cruiser",
                             "Battleship",
                             "Aircraft Carrier"
    };
    //Inicialização de variáveis
    bool rotation{true}, game{true};
    point2D pos{0,0};
    std::string nameP1;
    std::string nameP2;

    /*Inserção dos nomes do player 1 e player 2
     *Criação dos Objetos Player para player 1 e player 2
     */
    std::cout<< PRP << "Insert Player 1: " << NC;
    std::cin>>nameP1;
    Player p1{nameP1};
    std::cout << PRP << "Insert Player 2: " << NC;
    std::cin >> nameP2;
    Player p2{nameP2};
    Player players[2]{p1, p2};

    //Ciclo para adição dos barcos de cada jogador
    for(int p = 0; p < 2; p++){
        /*Cria um ponteiro currentPlayer em que o mesmo utiliza os objetos da Classe Player
         * Contudo este ponteiro utiliza a index do for para assim o currentPlayer ser o jogador atual no ciclo for.*/
        Player* currentPlayer = &(players[p]);
        //Coloca um output para a consola para indicar qual o jogador que está em jogo.
        std::cout << currentPlayer->name << "'s turn:\n";
        for(int i = 0; i < Map::numberOfBoats; i++) {
            currentPlayer->map.mapVeiw();
            //Declaração de variáveis
            char choiceRotation, choiceX, choiceY;
            bool checkBoat{false};
            while(!checkBoat) {
                //Para a colocação do barco necessitamos da sua rotação (BOOL) e das suas coordenadas Y em ASCII e X em inteiro
                std::cout << PRP << "Are you insert your " << PRPS << boatNames[i] << " with size " << boatSizes[i] << " in Horizontal?" << NC << "\n1 - Yes\nOther - No" << NC << std::endl;
                //controlo de erros CIN
                std::cin >> choiceRotation;
                rotation = choiceRotation == '1';
                //fflush(stdin);
                //std::cin.ignore(std::numeric_limits<int>::max(),'\n');
                std::cout << "\n" << REDS << "Use UPPERCASE CHAR!!" << NC << std::endl;
                std::cout << PRP << "Insert coordinate Y: " << NC;
                std::cin >> choiceY;
                //Conversão de ASCII para decimal e colocada numa estrutura chamada POIT2D em que armazena a coordenada de x e de y
                pos.y = choiceY - 65;
                std::cout << PRP << "Insert coordinate X: " << NC;
                std::cin >> choiceX;
                //Conversão de INPUT do utilizador para assim em vez de trabalhar com 1 a 10 trabalhar em 0 a 9
                pos.x = (choiceX - 48) - 1;
                Boat tempBoat{rotation, pos, boatSizes[i], boatNames[i]};
                checkBoat = currentPlayer->map.checkBoatSpace(tempBoat);

                //O objeto Boat é criado e adicionado ao Objeto Player que se encontra no nosso ponteiro currentPlayer
                if (checkBoat) {
                    currentPlayer->addBoat(tempBoat);
                    std::cout << GRN << "Your " << boatNames[i] << " is created successfully." << NC << std::endl;
                }
            }
            /*Realiza a verificação se o barco em questão cabe nas coordenadas indicadas caso sim sai do ciclo e o barco é criado
             *Esta verificação é realizada através de uma variavel mapSize que pertence á Classe map essa variável é responsavel
             * pelo tamanho do mapa em X e em Y assim caso se pretenda alterar o mesmo vasta alterar essa variável.
             * Caso seja verificado que quer na Horizontal (TRUE) realiza a operação aritmética em X caso contrário realiza a operação aritemética em Y
             */
            std::cout << GRNS << currentPlayer->name <<" life: " << currentPlayer->health << NC << std::endl;
        }
        //Realiza o Output do mapa do joagador
        currentPlayer->map.mapVeiw();
        std::cout << GRN << "Map create successfulL.\n" << NC;
        system("cls");
        system("pause");
    }

    //Inicialização de variaveis para a sua utilização no ciclo de jogo
    int choiceHitX{0};
    char choiceHitY, choiceX;
    bool hit, aliveBoat{true};
    Boat* currentBoat;
    Player* currentPlayer = &(players[0]);
    Player* enemyPlayer = &(players[1]);
    int p = 0;

    //Inicio do ciclo de jogo
    while(enemyPlayer->health > 0){
        //Ponteiros de jogadores
        currentPlayer = &(players[p]);
        enemyPlayer = &(players[1-p]);
        std::cout << PRPS << currentPlayer->name << "'s turn:" << NC << std::endl;
        std::cout << GRN << "You have got : " << currentPlayer->health << " health" << NC << std::endl;
        //verificação se algum barco foi atingido para dar notificação ao jogador
        if(currentPlayer->hitBoat){
            if(!aliveBoat){
                std::cout << RED << "Your " << currentPlayer->tempBoatHitName << " was sunken!!\n" << NC;
            }else {
                std::cout << RED << enemyPlayer->name << " HIT your " << currentPlayer->tempBoatHitName << NC << std::endl;
            }
            currentPlayer->hitBoat = false;
        }
        currentPlayer->map.mapVeiw();
        currentPlayer->enemyMap.mapVeiw();
        std::cout << REDS << "Use UPPERCASE!!" << NC << std::endl;
        std::cout << PRP << "Insert coordinate Y: " << NC;
        std::cin >> choiceHitY;
        choiceHitY -= 65;
        std::cout << PRP "Insert coordinate X: " << NC;
        std::cin >> choiceX;
        choiceHitX = (choiceX - 48) - 1;
        /*Ciclo para verificar se existe algum barco nas coordenadas de atack, o &boat serve para não criar cópias do respetivo boat
         * caso encontre a coordenada no vetor de boat irá realizar um break em que como importei o boat da minha lista Classe posso
         * agora ir buscar qualquer informação sobre o mesmo, pois o mesmo é guardado numa variavel para ser usado fora do ciclo for.*/
        for (auto &boat: enemyPlayer->boats) {
            hit = boat.doesHitYou(choiceHitX, choiceHitY);
            if (hit) {
                currentBoat = &boat;
                break;
            }
        }
        /*Realiza a verificação se houve ou não ataque e caso seja válido irá apresentar notificações em ambos os jogadores
         * e realizar as respetivas atuualizações em todos os mapas.*/
        if (hit) {
            std::cout << GRN << "You hit " << enemyPlayer->name << "\n" << NC;
            enemyPlayer->tempBoatHitName = currentBoat->name;
            enemyPlayer->hitBoat = true;
            enemyPlayer->map.hitBoat(choiceHitY, choiceHitX, Map::hit);
            currentPlayer->enemyMap.hitBoat(choiceHitY, choiceHitX, Map::boatChar);
            currentPlayer->enemyMap.mapVeiw();
            enemyPlayer->health -= 1;
            aliveBoat = enemyPlayer->map.isAlive(*currentBoat);
            if (!aliveBoat) {
                std::cout << RED << enemyPlayer->tempBoatHitName << " was sunken!!\n" << NC;
            }
        } else {
            std::cout << AZUL << "WATER!!\n" << NC;
            enemyPlayer->map.tryHitBoat(choiceHitY, choiceHitX);
            currentPlayer->enemyMap.hitBoat(choiceHitY, choiceHitX, Map::water);
            currentPlayer->enemyMap.mapVeiw();
        }
        system("pause");
        system("cls");

        /*Este operador ternário esta a fazer a vez de um ciclo for que possuia antigamente pois apenas com uma
         *simples linha posso manipular com mais eficiencia o currentePlayer e enemyPlayer no inicio do meu While.*/
        p = p == 0 ? 1 : 0; //Operador ternário

    }
    std::cout << GRN << currentPlayer->name << " is WINNER!" << NC;
    return EXIT_SUCCESS;
}