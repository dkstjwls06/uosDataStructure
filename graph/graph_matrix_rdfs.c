#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 8
char vName[N] = {'A','B','C','D','E','F','G','H'};

int Graph[N][N] ={
    {0,1,1,0,0,0,0,0},
    {1,0,0,1,0,0,0,0},
    {1,0,0,1,1,0,0,0},
    {0,1,1,0,0,1,0,0},
    {0,0,1,0,0,0,1,1},
    {0,0,0,1,0,0,0,0},
    {0,0,0,0,1,0,0,1},
    {0,0,0,0,1,0,1,0}
};

void rDFS(bool visited[], int s){
    visited[s] = true;
    printf("[%c] ",vName[s]);
    for(int t = 0; t < N; t++){
        if(Graph[s][t] == 1 && visited[t] == false)
        rDFS(visited, t);
    }
}


int main(){
    bool visited[N] = {false};

    rDFS(visited, 2); puts("");
}