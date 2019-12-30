//
// Created by Alex Bakalov on 30.12.19.
//
#ifndef UNTITLED3_ENEMY_H
#define UNTITLED3_ENEMY_H

#include "Entity.h"

class Enemy : public Entity {
    int movementState;

public:
    std::pair<int, int> getPosition() override;
    void movement(char *map) override;
};


#endif //UNTITLED3_ENEMY_H
