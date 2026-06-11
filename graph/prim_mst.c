#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 1000
#define N 7

char vName[N] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };

int graph[N][N] = {
    {   0,   7, INF, INF,   3,  10, INF },
    {   7,   0,   4,  10,   2,   6, INF },
    { INF,   4,   0,   2, INF, INF, INF },
    { INF,  10,   2,   0,  11,   9,   4 },
    {   3,   2, INF,  11,   0, INF,   5 },
    {  10,   6, INF,   9, INF,   0, INF },
    { INF, INF, INF,   4,   5, INF,   0 }
};

int visited[N], dist[N];

void init(){
    for(int i=0; i<N; i++){
        visited[i] = false;
        dist[i] = INF;
    }
}

int findMin(){
    int minVertex = 0, minDist = INF;
    for(int i=0; i<N;i++){
        if(!visited[i] && dist[i] < minDist){
            minDist = dist[i];
            minVertex = i;
        }
    }
    return minVertex;
}

void prim(int s){
    dist[s] = 0;
    for(int i=0; i<N; i++){
        s = findMin();

        visited[s] = true;
        printf("[%c, %d] ",vName[s], dist[s]); // ?

        for(int t = 0; t<N; t++)
            if(!visited[t] && graph[s][t] != INF)
                if(dist[t] > graph[s][t])
                    dist[t] = graph[s][t];
    }
    puts("");
    

}
void print(){
    for(int i=0; i<N; i++){
        if(dist[i] == INF){
            printf(" * ");
        } else printf("%2d ",dist[i]);

    }
    printf("\n");
}

int main(){
    init(); 

    prim(0);
}