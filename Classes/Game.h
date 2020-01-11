#ifndef UNTITLED3_GAME_H
#define UNTITLED3_GAME_H

#include <vector>
#include "Labyrinth.h"
#include "Entity.h"
#include "Witch.h"
#include "Mage.h"
#include <fstream>
#include <iostream>

class Game {
    std::vector<Labyrinth> listOfValidLabyrinths;
    int currentLab;
    bool GAMEOVER ;
    Entity* player;
    void loadLabyrinths();
    void printCurrLab();
    void selectClass();
    void loop();
    void modifyCurrLab(Entity* player);
    void playThroughLab();
    void sortLabyrints();
public:
    Game();
    void play();

};

Game::Game() {
    this->currentLab = 0;
    this->GAMEOVER = false;
}

void Game::loadLabyrinths() {
    std::ifstream labyrinthsFile;
    labyrinthsFile.open("../LabyrinthFile.txt");
    int n, m;
    while(labyrinthsFile >> n) {
        labyrinthsFile>>m;
        bool valid = true;
        char** map = new char*[n];
        for(int i = 0 ; i < n ; i++) {
            map[i] = new char[m];
        }
        for(int i = 0 ; i < n ; i++){
            for(int j = 0; j < m ; j++) {
                char pos;
                labyrinthsFile>>pos;
                map[i][j] = pos;
                if(pos != '.' && pos != '#') {
                    valid = false;
                }
            }
        }
        int numberOfMonsters ;
        labyrinthsFile>>numberOfMonsters;
        if(valid) {
            Labyrinth lab(map, numberOfMonsters, n, m);
            this->listOfValidLabyrinths.push_back(lab);
        }
    }
}

void Game::printCurrLab() {
    this->listOfValidLabyrinths[this->currentLab].printLabyrinth();
}

void Game::selectClass() {
    std::cout<<"Please select a class: "<<std::endl;
    std::cout<<"1: Witch - Finds the fastest path in the labyrinth"<<std::endl;
    std::cout<<"2: Mage - While searching for path, the mage can teleport back to the last position where another way was available  "<<std::endl;
    int choice;
    INPUT:std::cin>>choice;
    switch(choice) {
        case 1: {
            this->player = new Witch;
            break;
        }
        case 2: {
            this->player = new Mage;
            break;
        }
        default: {
            std::cout << "Incorect input, please try again" << std::endl;
            goto INPUT;
        }
    }
}

void Game::modifyCurrLab(Entity* player) {
    this->listOfValidLabyrinths[this->currentLab].modify(this->player);
}

void Game::loop() {
    for(this->currentLab ; this->currentLab < this->listOfValidLabyrinths.size(); this->currentLab++){
        this->printCurrLab();
        this->modifyCurrLab(this->player);
        this->playThroughLab();
        if(this->GAMEOVER) {
            return;
        }
        else if(this->currentLab == this->listOfValidLabyrinths.size() - 1) {
            std::cout<<"YOU HAVE WON!!"<<std::endl;
        }
    }
}

void Game::playThroughLab() {
    int curr = 0;
    while(true){
        this->listOfValidLabyrinths[this->currentLab].moveEnemies(player->getPath()[curr]);
        std::cout<<"Player's position : "<<this->player->getPath()[curr].first<<" "<<this->player->getPath()[curr].second<<std::endl;
        for(Enemy e : this->listOfValidLabyrinths[this->currentLab].getEnemiesList()) {
            if(player->getPath()[curr] == e.getPosition()) {
                std::cout << "You have been killed! GAME OVER!!" << std::endl;
                this->GAMEOVER = true;
                return;
            }
        }
        if(player->getPath().back().first == player->getPath()[curr].first) {
            if(player->getPath().back().second == player->getPath()[curr].second){
                std::cout<<"MAZE COMPLETED!"<<std::endl;
                return;
            }
        }
        curr++;
    }
}

void Game::sortLabyrints() {
    for (int i = 0; i < this->listOfValidLabyrinths.size()-1; i++)

        for (int j = 0; j < this->listOfValidLabyrinths.size()-i-1; j++)
            if (this->listOfValidLabyrinths[j+1] > this->listOfValidLabyrinths[j])
                std::swap(this->listOfValidLabyrinths[j], this->listOfValidLabyrinths[j+1]);
}

void Game::play() {
    this->loadLabyrinths();
    this->selectClass();
    this->sortLabyrints();
    this->loop();
}

#endif
