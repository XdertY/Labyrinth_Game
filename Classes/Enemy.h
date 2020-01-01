#ifndef UNTITLED3_ENEMY_H
#define UNTITLED3_ENEMY_H


class Enemy {
    int movementState;
    std::pair<int,int> position;

public:
    Enemy(int n, int m, char** map);
    std::pair<int, int> getPosition();
    void movement(char** map, int n, int m) ;
    void printMap(char** map, int n, int m);
};

Enemy::Enemy(int n, int m, char** map) {
    this->movementState = 1;
    srand(time(0));
    std::pair<int,int> position;
    position.first = rand() % n;
    position.second = rand() % m;
    if(map[position.first][position.second] == '#') {
        Enemy(n,m,map);
    }
    else{
        this->position = position;
    }

}

std::pair<int,int> Enemy::getPosition() {
    return this->position;
}

void Enemy::movement(char** map, int n, int m) {
    if(this->movementState == 1) {
        if(this->position.first - 1 > -1) {
            if (map[this->position.first - 1][this->position.second] != '#') {
                this->position.first -= 1;
                //this->printMap(map,n,m);
            }
            else {
                this->movementState = 2;
            }
        }
        else {
            this->movementState = 2;
        }
    }
    if(this->movementState == 2) {
        if(this->position.second - 1 > -1) {
            if(map[this->position.first][this->position.second - 1] != '#'){
                this->position.second -= 1;
                //this->printMap(map,n,m);

            }
            else {
                this->movementState = 3;
            }
        }
        else {
            this->movementState = 3;
        }

    }
    if(this->movementState == 3) {
        if(this->position.first + 1 < n ) {
            if(map[this->position.first + 1][this->position.second] != '#') {
                this->position.first += 1;
                //this->printMap(map,n,m);

            }
            else {
                this->movementState = 4;
            }
        }
        else {
            this->movementState = 4;
        }

    }
    if(this->movementState == 4) {
        if(this->position.second + 1 < m) {
            if(map[this->position.first][this->position.second +1] != '#') {
                this->position.second += 1;
                //this->printMap(map,n,m);

            }
            else {
                this->movementState = 1;
                this->movement(map, n, m);
            }
        }
        else {
            this->movementState = 1;
            this->movement(map, n, m);
        }
    }
}

void Enemy::printMap(char **map, int n, int m) {
    for(int i = 0; i < n ; i++) {
        for(int k = 0; k < m; k++) {
            if(i == this->position.first && k == this->position.second) {
                std::cout<<"X";
            }
            else{
                std::cout<<map[i][k];
            }
        }
        std::cout<<std::endl;
    }
}

#endif //UNTITLED3_ENEMY_H
