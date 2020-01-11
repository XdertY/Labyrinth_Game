#ifndef UNTITLED3_ENEMY_H
#define UNTITLED3_ENEMY_H


class Enemy {
    int movementState;
    std::pair<int,int> position;

public:
    Enemy(int n, int m, char** map, std::vector<Enemy> enemiesPos, std::vector<std::pair<int,int>>* freePositions);
    std::pair<int, int> getPosition();
    void movement(char** map, int n, int m) ;
    bool isValid(std::vector<Enemy> enemiesPos);
    void generatePosition(int n , int m, char** map, std::vector<Enemy> enemyPos, std::vector<std::pair<int,int>>* freePositions);
};

Enemy::Enemy(int n, int m, char** map, std::vector<Enemy> enemiesPos, std::vector<std::pair<int,int>>* freePositions) {
    this->movementState = 1;
    this->generatePosition(n,m,map,enemiesPos, freePositions);
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

bool Enemy::isValid(std::vector<Enemy> enemiesPos) {
    for(Enemy e : enemiesPos) {
        if(e.position.first == this->position.first && e.position.second == this->position.second) {
            return false;
        }
    }
    return true;
}

void Enemy::generatePosition(int n , int m, char** map, std::vector<Enemy> enemyPos, std::vector<std::pair<int,int>>* freePositions) {
    srand(time(0));
    int position = rand() % freePositions->size();
    this->position = freePositions->at(position);
    freePositions->erase(freePositions->begin() + position);
    std::cout<<"ENEMY LOCATION "<<this->position.first<<" "<<this->position.second<<std::endl;
}


#endif //UNTITLED3_ENEMY_H
