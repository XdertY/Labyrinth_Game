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
    std::vector<std::pair<int, int>> freePositions;


public:
    Labyrinth(char** map, int numberOfMonsters, int n, int m);
    bool operator > (Labyrinth& other);
    void printLabyrinth();
    void modify(Entity* player);
    void placeEnemies();
    void moveEnemies(std::pair<int,int> playerPos);
    std::vector<Enemy> getEnemiesList();
};

Labyrinth::Labyrinth(char** map, int numberOfMonsters, int n, int m) {
    this->map = map;
    this->numberOfMonsters = numberOfMonsters;
    this->n = n;
    this->m = m;
    for(int i = 0; i < n; i++) {
        for(int k = 0 ;k < m ; k++) {
            if(map[i][k] == '.') {
                if(!(i == 0 && k == 0)) {
                    std::pair<int, int> freePos;
                    freePos.first = i;
                    freePos.second = k;
                    freePositions.push_back(freePos);
                }
            }
        }
    }
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
    std::cout<<"@ - player | X - enemy | # - wall"<<std::endl;
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
        Enemy enemy(n,m,map, this->getEnemiesList(), &this->freePositions);
        this->enemies.push_back(enemy);
    }
}

void Labyrinth::moveEnemies(std::pair<int,int> playerPos) {
    for(int i = 0 ; i < enemies.size(); i++) {
        this->enemies[i].movement(map, n, m);
    }
    char** temp = new char*[n];
    for(int i = 0; i < n; i++) {
        temp[i] = new char[m];
    }

    for(int i = 0; i < n ; i++) {
        for(int k = 0; k < m ; k ++) {
            temp[i][k] = map[i][k];
        }
    }

    for(Enemy e : this->enemies) {
        temp[e.getPosition().first][e.getPosition().second] = 'X';
    }

    temp[playerPos.first][playerPos.second] = '@';

    std::cout<<std::endl;
    for(int i =0; i < n; i++) {
        for(int k = 0; k < m; k++) {
            std::cout<<temp[i][k];
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

}

std::vector<Enemy> Labyrinth::getEnemiesList() {
    return  this->enemies;
}

bool Labyrinth:: operator>(Labyrinth& other) {
    int size = this->n*this->m;
    if(size > (other.n*other.m)){
        return true;
    }
    if(size == other.n*other.m) {
        return this->numberOfMonsters > other.numberOfMonsters;
    }
    else
        return false;
}


#endif //LABYRINTH_GAME_LABYRINTH_H
