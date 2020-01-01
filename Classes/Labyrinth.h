#ifndef LABYRINTH_GAME_LABYRINTH_H
#define LABYRINTH_GAME_LABYRINTH_H

#include "Graph.h"
#include "Enemy.h"
#include "Entity.h"

class Labyrinth {
    int n,m;
    char** map;
    int numberOfMonsters;
    std::vector<Enemy> enemies;
//    std::vector<Enemy> enemies;
//    std::vector<std::pair<int, int>> blockedPositions;


public:
    Labyrinth(char** map, int numberOfMonsters, int n, int m);
    void addEnemies();
    void blockPath();
    void printLabyrinth();
    void modify(Entity* player);
    void placeEnemies();
    void moveEnemies();
    std::vector<Enemy> getEnemiesList();

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

void Labyrinth::modify(Entity* player) {
    std::vector<std::pair<int,int>> blocked;
    int free = 0;
    for(int i = 0 ; i < n; i++) {
        for(int k = 0; k < m ; k++) {
            if(this->map[i][k] == '.') {
                free++;
            }
        }
    }
    char decision;
    QUESTION: std::cout<<"You can block up to "<<free - 2 - this->numberOfMonsters<<" tiles. Do you want to? (y/n)"<<std::endl;
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
            for(int i = 0; i < count; i++) {
                std::pair<int, int> temp;
                std::cin>>temp.first;
                std::cin>>temp.second;
                if(temp.first <= n && temp.second <= m && this->map[temp.first][temp.second] == '.') {
                    blocked.push_back(temp);
                }
                else{
                    std::cout<<"Invalid coordinates, Please try again!"<<std::endl;
                    i--;
                }
            }
            for(int i = 0 ; i < count ; i++) {
                this->map[blocked[i].first][blocked[i].second] = '*';
            }
        }
    }
    else if(decision == 'n'){

    }
    else {
        std::cout<<"Invalid input, please try again!"<<std::endl;
        goto INPUT;
    }
    Graph graphMap(this->n * this->m);
    graphMap.buildMatrix(this->map, this->n, this->m);
    if(player->generatePath(graphMap)) {
        this->placeEnemies();
    }
    else {
        std::cout<<"After modifying the labyrinth , there is no available path, please try again"<<std::endl;
        for(std::pair<int,int> a : blocked ) {
            this->map[a.first][a.second] = '.';
        }
        goto QUESTION;
    }
}

void Labyrinth::placeEnemies() {
    for(int i = 0 ; i < this->numberOfMonsters; i++) {
        Enemy enemy(n,m,map);
        this->enemies.push_back(enemy);
    }
}

void Labyrinth::moveEnemies() {
    for(Enemy e :this->enemies) {
        e.movement(map, n, m);
    }
    std::vector<std::pair<int,int>> tempPos;
    for(Enemy e :this->enemies) {
        tempPos.push_back(e.getPosition());
    }
    for(int i = 0; i < n ; i++) {
        for(int k = 0; k < m ; k ++) {
            bool printed = false;
            for(int j= 0; j < tempPos.size(); j ++) {
                if((i == tempPos[j].first) && (k == tempPos[j].second)) {
                    std::cout<<"X";
                    printed = true;
                    break;
                }
            }
            if(!printed) {
                std::cout<<this->map[i][k];
            }
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

}

std::vector<Enemy> Labyrinth::getEnemiesList() {
    return  this->enemies;
}


#endif //LABYRINTH_GAME_LABYRINTH_H
