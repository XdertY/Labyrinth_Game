#ifndef LABYRINTH_GAME_LABYRINTH_H
#define LABYRINTH_GAME_LABYRINTH_H

#include "Graph.h"
#include "Enemy.h"

class Labyrinth {
    int n,m;
    char** map;
    int numberOfMonsters;
//    std::vector<Enemy> enemies;
//    std::vector<std::pair<int, int>> blockedPositions;


public:
    Labyrinth(char** map, int numberOfMonsters, int n, int m);
    void addEnemies();
    void blockPath();
    void printLabyrinth();
    void modify();

};

Labyrinth::Labyrinth(char** map, int numberOfMonsters, int n, int m) {
    this->map = map;
    this->numberOfMonsters = numberOfMonsters;
    this->n = n;
    this->m = m;
}

void Labyrinth::addEnemies() {

}

void Labyrinth::blockPath() {

}

void Labyrinth::printLabyrinth() {
    for(int i = 0 ; i < n; i++) {
        for(int j = 0; j < m; j++) {
            std::cout<<this->map[i][j]<< ' ';
        }
        std::cout<<std::endl;
    }
}

void Labyrinth::modify() {
    int free = 0;
    for(int i = 0 ; i < n; i++) {
        for(int k = 0; k < m ; k++) {
            if(this->map[i][k] == '.') {
                free++;
            }
        }
    }
    char decision;
    std::cout<<"You can block up to "<<free - 2 - this->numberOfMonsters<<" tiles. Do you want to? (y/n)"<<std::endl;
    INPUT:std::cin>>decision;
    if(decision == 'y'){
        std::cout<<"How many tiles do you want to block?"<<std::endl;
        COUNT:int count;
        std::cin>>count;
        if(count > free - 2 - this->numberOfMonsters) {
            std::cout<<"You can block only up to "<<free - 2 - this->numberOfMonsters<<" tiles. Please try again!"<<std::endl;
            goto COUNT;
        }
        else {
            std::cout<<"Type the coordinates of the tile you want to block: "<<std::endl;
            std::vector<std::pair<int,int>> blocked;
            for(int i = 0; i < count; i++) {
                std::pair<int, int> temp;
                std::cin>>temp.first;
                std::cin>>temp.second;
                if(temp.first <= n && temp.second <= m ) {
                    blocked.push_back(temp);
                }
                else{
                    std::cout<<"Invalid coordinates, Please try again!"<<std::endl;
                    i--;
                }
            }
        }
    }
    else if(decision == 'n'){

    }
    else {
        std::cout<<"Invalid input, please try again!"<<std::endl;
        goto INPUT;
    }
}


#endif //LABYRINTH_GAME_LABYRINTH_H
