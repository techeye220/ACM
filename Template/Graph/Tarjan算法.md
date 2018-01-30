#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

const int T_MAXN = 1000;
int DFN[T_MAXN], Low[T_MAXN], belong[T_MAXN]; // inStack记录是否入栈，belong记录每个点所属的连通分量编号
bool vis[T_MAXN], inStack[T_MAXN];
int SCC_CNT = 0;
int index = 0;
vector< vector<int> > T_map;
stack<int> stI;
void Tarjan(int cur)
{
    DFN[cur] = Low[cur] = ++ index;
    vis[cur] = true;
    stI.push(cur);
    inStack[cur] = true;
    for (int i = 0; i < T_map[cur].size(); i ++)
    {
        int temp = T_map[cur][i];
        if(!vis[temp])
        {
            Tarjan(temp);
            if(Low[temp] < Low[cur])
                Low[cur] = Low[temp];
        }else if(inStack[temp] && DFN[temp] < Low[cur])
        {
            Low[cur] = DFN[temp];
        }
    }
    if(DFN[cur] == Low[cur])
    {
        int temp = 0;
        SCC_CNT ++;
        do{
            temp = stI.top();
            stI.pop();
            inStack[temp] = false;
            belong[temp] = SCC_CNT;
            cout << temp << " ";
        }while(cur != temp);
        cout << endl;
    }
}

int main()
{
    freopen("22.in", "r", stdin);
    int n, m;
    int x, y;
    scanf("%d %d", &n, &m);
    T_map.resize(n + 1);
    for (int i = 0; i < m; i ++)
    {
        scanf("%d %d", &x, &y);
        x--;
        y--;
        T_map[x].push_back(y);
    }
    for (int i = 0; i < n; i ++)
    {
        if(!vis[i])
            Tarjan(i);
    }
    return 0;
}
