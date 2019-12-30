#ifndef LABYRINTH_GAME_FUNCTIONS_H
#define LABYRINTH_GAME_FUNCTIONS_H
#include <vector>
#include <iostream>
#include <fstream>
#import "../Classes/Graph.h"
#include "../Classes/Labyrinth.h"

using namespace std;

bool canAdd(int i, int j,int rows, int cols, vector<vector<char>> currElement)
{
    return !((i < 0 || i >= rows) ||
             (j < 0 || j >= cols) || currElement[i][j] == '.');
}

void loadLabyrinths (ifstream &labyrinthsFile) {
    int n, m;
    while(labyrinthsFile >> n) {
       labyrinthsFile>>m;
       bool valid = true;
       vector<vector<char>> map;

       for(int i = 0; i < n; i++) {
           vector<char> temp;
           for(int j = 0 ; j < m ; j++) {
                char tempCh;
                labyrinthsFile>>tempCh;
                temp.push_back(tempCh);
//                if(map[i][j] != '.' && map[i][j] != '#') {
//                    valid = false;
//                    break;
//                }
           }
           if(!valid) {
               break;
           }
           map.push_back(temp);
       }
        if(!valid) {
            continue;
        }
        Graph graphMap(n*m);
        for (int i =0 ; i < n; i++)
        {
            for (int j = 0, current = 0 ; j < m; j++)
            {
                if (map[i][j] != '#')
                {
                    if ( canAdd ( i , j+1 , n, m , map) )
                        graphMap.addEdge ( current , current+1 );
                    if ( canAdd ( i , j-1, n , m , map ) )
                        graphMap.addEdge ( current , current-1 );
                    if (j< m-1 && canAdd ( i+1 , j , n, m,  map ) )
                        graphMap.addEdge ( current , current+m );
                    if ( i > 0 && canAdd ( i-1 , j , n , m , map ) )
                        graphMap.addEdge ( current , current-m );
                }
                current++;
            }
        }
        for(int i = 0; i < n*m; i++) {
            list<char> temp = graphMap.getAdj()[i];
            cout<<"Current element's adj are: ";
            for(auto t = temp.begin(); t != temp.end(); t++) {
                cout<<*t<<" ";
            }
            cout<<endl;
        }


    }
    return ;
}



#endif //LABYRINTH_GAME_FUNCTIONS_H
