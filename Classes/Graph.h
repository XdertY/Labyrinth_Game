#ifndef LABYRINTH_GAME_GRAPH_H
#define LABYRINTH_GAME_GRAPH_H
#include <list>
#include <iostream>


class Graph {
    int numberOfVec, n, m;
    int **adjMatrix;
    int** redoneMatrix;

public:
    Graph(int numberOfVec);
    void buildMatrix(char **matrix, int n, int m);
    int getNumberOfVec();
    int** getAdjMatrix();
    std::pair<int,int> parseNodeToCoordinates(int node);
};


Graph::Graph(int numberOfVec) {
    this->adjMatrix = new int*[numberOfVec];
    for(int i = 0 ; i < numberOfVec; i++) {
        this->adjMatrix[i] = new int[numberOfVec];
    }
    this->numberOfVec = numberOfVec;
    for(int i = 0; i < numberOfVec; i++) {
        for(int k = 0 ; k < numberOfVec; k++) {
            adjMatrix[i][k] = 0;
        }
    }
}

void Graph::buildMatrix(char** matrix, int n, int m) {
    this->n = n;
    this->m = m;
    this->redoneMatrix = new int*[n];
    for(int i = 0; i < m ; i ++) {
        redoneMatrix[i] = new int[m];
    }

    int tempel = 0;
    for(int i = 0; i < n; i ++) {
        for(int k = 0; k < m ; k++) {
            if(matrix[i][k] == '.') {
                redoneMatrix[i][k] = tempel;
            }
            else {
                redoneMatrix[i][k] = -1;
            }
            tempel++;
        }
    }

    for(int i = 0; i < n; i++) {
        for(int k = 0; k < m; k++){
            if(redoneMatrix[i][k] != -1 ) {
                if(i + 1 < n) {
                   if(redoneMatrix[i+1][k] != -1 ){
                       this->adjMatrix[redoneMatrix[i][k]][redoneMatrix[i+1][k]] = 1;
                   }
                }
                if(i-1 > -1) {
                   if(redoneMatrix[i-1][k] != -1) {
                       this->adjMatrix[redoneMatrix[i][k]][redoneMatrix[i-1][k]] = 1;
                   }
                }
                if(k+1 < m) {
                   if(redoneMatrix[i][k+1] != -1) {
                       this->adjMatrix[redoneMatrix[i][k]][redoneMatrix[i][k + 1]] = 1;
                   }
                }
                if(k-1 > -1) {
                    if(redoneMatrix[i][k-1] != -1) {
                        this->adjMatrix[redoneMatrix[i][k]][redoneMatrix[i][k-1]] = 1;
                    }

                }
            }
        }

    }
//    for(int i = 0; i < this->numberOfVec; i++) {
//        for(int k = 0;k < this->numberOfVec; k++) {
//            std::cout<<this->adjMatrix[i][k]<<" ";
//        }
//        std::cout<<std::endl;
//    }
}

int Graph::getNumberOfVec() {
    return this->numberOfVec;
}

int** Graph::getAdjMatrix() {
    return this->adjMatrix;
}

std::pair<int, int> Graph::parseNodeToCoordinates(int node) {
    for(int i = 0 ; i < n; i++) {
        for(int k = 0 ; k < m ; k++) {
            if(this->redoneMatrix[i][k] == node) {
                std::pair<int, int> coord ;
                coord.first = i;
                coord.second = k;
                return coord;
            }
        }
    }
}

#endif