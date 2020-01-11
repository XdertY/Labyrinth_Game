#ifndef UNTITLED3_WITCH_H
#define UNTITLED3_WITCH_H

#include <vector>
#include "Entity.h"

class Witch : public Entity {
    std::vector<std::pair<int, int>> shortestPath;

public:
    bool generatePath(Graph graphMap) override ;
    std::vector<std::pair<int,int>> getPath() override;
    bool djikstra(int src, Graph graphMap);
    void buildShortestPath(int parent[], int j, Graph graphMap);
    int minDistance(int *dist, bool *sptSet, int numberOfVec);
    void printShortestPath() override ;
};


bool Witch::generatePath(Graph graphMap) {
    this->shortestPath.clear();
    return this->djikstra(0, graphMap);
}

bool Witch::djikstra (int src, Graph graphMap ) {
    int numberOfVec = graphMap.getNumberOfVec();
    int dist[numberOfVec];
    bool sptSet[numberOfVec];
    int parent[numberOfVec];
    for (int i = 0; i < numberOfVec; i++) {
        parent[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[src] = 0;

    for (int count = 0; count < numberOfVec - 1; count++) {

        int u = minDistance(dist, sptSet, numberOfVec);


        sptSet[u] = true;


        for (int v = 0; v < numberOfVec; v++)


            if (!sptSet[v] && graphMap.getAdjMatrix()[u][v] &&
                dist[u] + graphMap.getAdjMatrix()[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graphMap.getAdjMatrix()[u][v];
            }
    }
    if(dist[numberOfVec - 1] > numberOfVec) {
        return false;
    }

    std::pair<int,int> start;
    start.first = 0, start.second = 0;
    this->shortestPath.push_back(start);
    this->buildShortestPath(parent, numberOfVec-1, graphMap);

    return true;
}

int Witch::minDistance(int *dist, bool *sptSet, int numberOfVec) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < numberOfVec ; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}
void Witch::buildShortestPath(int parent[], int j, Graph graphMap)
{

    // Base Case : If j is source
    if (parent[j] == - 1)
        return;

    buildShortestPath(parent, parent[j], graphMap);

    this->shortestPath.push_back(graphMap.parseNodeToCoordinates(j));
}

void Witch::printShortestPath() {
    for(std::pair<int,int> a : this->shortestPath) {
        std::cout<<a.first<<","<<a.second<< " ";
    }
}

std::vector<std::pair<int,int>> Witch::getPath() {
    return this->shortestPath;
}



#endif //UNTITLED3_WITCH_H
