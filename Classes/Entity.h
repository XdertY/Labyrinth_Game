#ifndef UNTITLED3_ENTITY_H
#define UNTITLED3_ENTITY_H


#include <utility>

class Entity {
public:
    std::vector<std::pair<int,int>> path;
    virtual bool generatePath(Graph graphMap) = 0;
    virtual void printShortestPath() = 0;
    virtual std::vector<std::pair<int,int>> getPath() = 0;
};



#endif //UNTITLED3_ENTITY_H
