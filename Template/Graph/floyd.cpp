#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
/*
bellman_ford 算法
求最短路
*/

int G[100][100];
void floyd()
{
    int i, j, k;

    for(k=0;k<n;k++)
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                G[i][j] = min(G[i][j],G[i][k]+G[k][j]);
    printf("%d\n",G[s][t]==MAX?-1:G[s][t]);
}
int main()
{
    int i, j, m, u, v, w;

    while(scanf("%d %d",&n,&m)==2){
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                G[i][j] = i==j?0:MAX;
        while(m--){
            scanf("%d %d %d",&u,&v,&w);
            if(G[u][v]>w)
                G[u][v] = G[v][u] = w;
        }
        scanf("%d %d",&s,&t);
        floyd();
    }
    return 0;
}