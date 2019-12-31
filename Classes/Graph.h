#ifndef LABYRINTH_GAME_GRAPH_H
#define LABYRINTH_GAME_GRAPH_H
#include <list>
#include <iostream>


class Graph {
    int numberOfVec;
    int **adjMatrix;

public:
    Graph(int numberOfVec);

    void buildMatrix(char **matrix, int n, int m);

    bool isValid();

    void dijkstra(int src);

    void printPath(int parent[], int j);

    int minDistance(int dist[], bool sptSet[]);
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

int Graph::minDistance(int *dist, bool *sptSet) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < this->numberOfVec ; v++)
        if (sptSet[v] == false &&
            dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void Graph::buildMatrix(char** matrix, int n, int m) {
    int currentElement = 0;
    int** redoneMatrix = new int*[n];
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
                if(k+1 < n) {
                   if(redoneMatrix[i][k+1] != -1) {
                       this->adjMatrix[redoneMatrix[i][k]][redoneMatrix[i][k + 1]] = 1;
                   }
                }
                if(k-1 > -1) {
                    if(redoneMatrix[i][k-1] != -1) {
                        this->adjMatrix[redoneMatrix[i][k]][redoneMatrix[i][k-1]] = 1;
                    }

                }
                currentElement++;
            }
        }

    }
    for(int i = 0; i < this->numberOfVec; i++) {
        for(int k = 0;k < this->numberOfVec; k++) {
            std::cout<<this->adjMatrix[i][k]<<" ";
        }
        std::cout<<std::endl;
    }
}

void Graph::dijkstra (int src) {
    int dist[this->numberOfVec];
    bool sptSet[this->numberOfVec];
    int parent[this->numberOfVec];
    for (int i = 0; i < this->numberOfVec; i++) {
        parent[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[src] = 0;

    for (int count = 0; count < this->numberOfVec - 1; count++) {

        int u = minDistance(dist, sptSet);


        sptSet[u] = true;


        for (int v = 0; v < this->numberOfVec; v++)


            if (!sptSet[v] && adjMatrix[u][v] &&
                dist[u] + adjMatrix[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + this->adjMatrix[u][v];
            }
    }

    printf("Vertex\t Distance\tPath");
    for (int i = 1; i < this->numberOfVec; i++)
    {
        printf("\n%d -> %d \t\t %d\t\t%d ",
               src, i, dist[i], src);
        this->printPath(parent, i);
    }
}

void Graph::printPath(int parent[], int j)
{

    // Base Case : If j is source
    if (parent[j] == - 1)
        return;

    printPath(parent, parent[j]);

    printf("%d ", j);
}


bool Graph::isValid() {

}


#endif