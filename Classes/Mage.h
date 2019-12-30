#ifndef UNTITLED3_MAGE_H
#define UNTITLED3_MAGE_H

#include <vector>
#include "Entity.h"

class Mage : public Entity {
    std::vector<std::pair<int, int>> shortestPath;

public:
    std::pair<int, int> getPosition();
    void movement(char *map) override;
};

std::pair<int, int> Mage::getPosition() {

}

void Mage::movement(char *map) {

}

#endif //UNTITLED3_MAGE_H
