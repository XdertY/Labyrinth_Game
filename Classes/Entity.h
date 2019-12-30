#ifndef UNTITLED3_ENTITY_H
#define UNTITLED3_ENTITY_H


#include <utility>

class Entity {
    std::pair<int, int> position;
public:
    virtual std::pair<int, int> getPosition() =  0;
    virtual void movement(char* map) = 0;
};

#endif //UNTITLED3_ENTITY_H
