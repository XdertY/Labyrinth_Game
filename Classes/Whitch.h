#ifndef UNTITLED3_WHITCH_H
#define UNTITLED3_WHITCH_H

#include <vector>
#include "Entity.h"

class Whitch : public Entity {
    std::vector<std::pair<int, int>> shortestPath;

public:
    bool generatePath(Graph graphMap) override ;
    std::vector<std::pair<int,int>> getPath() override;
    bool djikstra(int src, Graph graphMap);
    void buildShortestPath(int parent[], int j, Graph graphMap);
    int minDistance(int *dist, bool *sptSet, int numberOfVec);
    void printShortestPath() override ;
};


bool Whitch::generatePath(Graph graphMap) {
    return this->djikstra(0, graphMap);
}

bool Whitch::djikstra (int src, Graph graphMap ) {
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

    this->buildShortestPath(parent, numberOfVec-1, graphMap);

    return true;
}

int Whitch::minDistance(int *dist, bool *sptSet, int numberOfVec) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < numberOfVec ; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}
void Whitch::buildShortestPath(int parent[], int j, Graph graphMap)
{

    // Base Case : If j is source
    if (parent[j] == - 1)
        return;

    buildShortestPath(parent, parent[j], graphMap);

    this->shortestPath.push_back(graphMap.parseNodeToCoordinates(j));
}

void Whitch::printShortestPath() {
    for(std::pair<int,int> a : this->shortestPath) {
        std::cout<<a.first<<","<<a.second<< " ";
    }
}

std::vector<std::pair<int,int>> Whitch::getPath() {
    return this->shortestPath;
}



#endif //UNTITLED3_WHITCH_H
