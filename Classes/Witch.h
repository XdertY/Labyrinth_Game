#ifndef UNTITLED3_WITCH_H
#define UNTITLED3_WITCH_H

#include "Entity.h"

class Witch : public Entity {

public:
    std::pair<int, int> getPosition() override ;
    void movement(char *map) override;
};

std::pair<int, int> Witch::getPosition() {

}

void Witch::movement(char *map) {

}

#endif //UNTITLED3_WITCH_H
