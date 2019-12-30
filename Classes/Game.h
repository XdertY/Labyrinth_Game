#ifndef UNTITLED3_GAME_H
#define UNTITLED3_GAME_H

#include <vector>
#include "Labyrinth.h"
#include "Entity.h"
#include "Mage.h"
#include "Witch.h"
#include <fstream>
#include <iostream>

class Game {
    std::vector<Labyrinth> listOfValidLabyrinths;
    int currentLab = 0;
    Entity* player;
    void loadLabyrinths();
    void printCurrLab();
    void selectClass();
    void loop();
    void modifyCurrLab();
public:
    Game();
    void play();

};

Game::Game() {

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
    std::cout<<"1: Mage - While searching for path, the mage can teleport back to the last position where another way was available "<<std::endl;
    std::cout<<"2: Witch - Finds the fastest path in the labyrinth "<<std::endl;
    int choice;
    INPUT:std::cin>>choice;
    switch(choice) {
        case 1: {
            this->player = new Mage;
            break;
        }
        case 2: {
            this->player = new Witch;
            break;
        }
        default: {
            std::cout << "Incorect input, please try again" << std::endl;
            goto INPUT;
        }
    }
}

void Game::modifyCurrLab() {
    this->listOfValidLabyrinths[this->currentLab].modify();
}

void Game::loop() {
    for(this->currentLab ; this->currentLab < this->listOfValidLabyrinths.size(); this->currentLab++){
        this->printCurrLab();
        this->modifyCurrLab();
    }
}

void Game::play() {
    this->loadLabyrinths();
    this->selectClass();
    this->loop();
}

#endif
