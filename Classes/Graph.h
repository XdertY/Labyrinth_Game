#ifndef LABYRINTH_GAME_GRAPH_H
#define LABYRINTH_GAME_GRAPH_H
#include <list>


class Graph {
    int numberOfVec;
    std::list<char> *adj;

public:
    Graph(int numberOfVec);
    void addEdge(int edge, int newEdge);
    std::list<char>* getAdj();
};


Graph::Graph(int numberOfVec) {
    this->numberOfVec = numberOfVec;
    this->adj = new std::list<char> [numberOfVec];
}

void Graph::addEdge(int edge, int newEdge) {
    this->adj[edge].push_back(newEdge);
    this->adj[newEdge].push_back(edge);
}

std::list<char>* Graph::getAdj() {
    return this->adj;
}





#endif