#ifndef UNTITLED3_MAGE_H
#define UNTITLED3_MAGE_H

#include <vector>
#include "Entity.h"

class Mage : public Entity {
    std::vector<std::pair<int,int>> path;
    bool pathFound = false;

public:
    bool generatePath(Graph graphMap) override ;
    void printShortestPath() override ;
    std::vector<std::pair<int,int>> getPath() override ;
    void DFS(int v , bool* visited, Graph graphMap);
};


bool Mage::generatePath(Graph graphMap) {
    bool* visited = new bool[graphMap.getNumberOfVec()];
    for(int i = 0 ; i < graphMap.getNumberOfVec(); i++) {
        visited[i] = false;
    }
    this->DFS(0, visited, graphMap);
    delete[] visited;
    return this->pathFound;
}

void Mage::DFS(int v, bool* visited, Graph graphMap) {
    this->path.push_back(graphMap.parseNodeToCoordinates(v));
    visited[v] = true;
    if(v == graphMap.getNumberOfVec() - 1) {
        this->pathFound = true;
        return;
    }
    for(int i = 0; i < graphMap.getNumberOfVec(); i++) {
        if(graphMap.getAdjMatrix()[v][i] == 1 && !visited[i] && !this->pathFound) {
            DFS(i, visited, graphMap);
        }
    }
}

void Mage::printShortestPath() {
    for(int i = 0 ; i < path.size(); i++) {
        std::cout<<path[i].first<<','<<path[i].second<<" ";
    }
}

std::vector<std::pair<int,int>> Mage::getPath() {
    return this->path;
}

#endif //UNTITLED3_MAGE_H
