//无向图的二分图判断
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
const int maxn=1000+5;

int n;//图节点数
vector<int> G[maxn];//G[i]表示i节点邻接的点
int color[maxn];//color[i]=0,1,2 表i节点 不涂颜色 涂白色 涂黑色

//判断无向图是否可二分
bool bipartite(int u)
{
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(color[v]==color[u]) return false;
        if(!color[v])
        {
            color[v]=3-color[u];
            if(!bipartite(v)) return false;
        }
    }
    return true;
}

