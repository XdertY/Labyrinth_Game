#ifndef LABYRINTH_GAME_LABYRINTH_H
#define LABYRINTH_GAME_LABYRINTH_H

#include "Graph.h"

class Labyrinth {
    Graph map;
    int numberOfMonsters;

public:
    Labyrinth(Graph map, int numberOfMonsters);
};


#endif //LABYRINTH_GAME_LABYRINTH_H
