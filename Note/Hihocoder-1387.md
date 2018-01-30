#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>

using namespace std;

const int N = 300000;
map<string, int> mp;
int v[N],n,m,Name;
pair<int, pair<int, int> > d[N];
namespace LCA
{
    //N指代最大的节点个数
    bool vis[N];
    int dp[N][20],tot,tot1;
    //dp[i][j]记录的是以i为起点、2的j次方长度内的深度最小点的编号
    int head[N],ver[N],R[N],first[N],dir[N];
    //ver为访问的节点依次编号，dep记录编号对应的节点的深度，因为访问2n-1次，所有这两个数组长度乘2
    struct Node
    {
        int v;
        int next;
    };

    struct Node e[N];

    void AddNode(int from, int to)
    {
        e[tot1].v=to;
        e[tot1].next=head[from];
        head[from]=tot1++;
    }

    void init()
    {
        tot1=tot=0;
        dir[1]=0;
        memset(head,-1,sizeof(head));
        memset(vis,0,sizeof(vis));
    }

    void dfs(int u ,int dep)
    {
        vis[u] = true; ver[++tot] = u; first[u] = tot; R[tot] = dep;
        for(int k=head[u]; k!=-1; k=e[k].next)
            if( !vis[e[k].v] )
            {
                int v = e[k].v;
                dir[v] = dir[u] + 1;
                dfs(v,dep+1);
                ver[++tot] = u; R[tot] = dep;
            }
    }
    void ST(int n)   //ST算法，用于求解RMQ问题,n为需要处理的范围，如果有LMC规约到RMQ，则应该为2*n - 1
    {
        for(int i=1;i<=n;i++)
            dp[i][0] = i;
        for(int j=1;(1<<j)<=n;j++)
        {
            for(int i=1;i+(1<<j)-1<=n;i++)
            {
                int a = dp[i][j-1] , b = dp[i+(1<<(j-1))][j-1];
                dp[i][j] = R[a]<R[b]?a:b;
            }
        }
    }

    int RMQ(int l,int r) //RMQ在前者的基础上返回结果
    {
        int k=0;
        while((1<<(k+1))<=r-l+1)
            k++;
        int a = dp[l][k], b = dp[r-(1<<k)+1][k];
        return R[a]<R[b]?a:b;
    }

    int lca(int u ,int v) //lca在前者的基础上返回结果
    {
        int x = first[u] , y = first[v];
        if(x > y) swap(x,y);
        int res = RMQ(x,y);
        return ver[res];
    }

    int dist(int x ,int y)   //通过LCA计算每两个点之间的距离，由于本题中最小距离为1，故加一
    {
        return dir[x] + dir[y] - 2*dir[lca(x,y)]+1;
    }
}


int main()
{
    freopen("22.in", "r", stdin);
    while(~scanf("%d %d", &n, &m))
    {
        mp.clear();
        LCA::init();
        memset(d, 0, sizeof(d));
        char name[10];
        Name ++;
        for (int i = 1; i <= n; i ++)
        {
            scanf("%s", name);
            if(mp[name] == 0)
                v[i] = mp[name] = ++ Name;
            else
                v[i] = mp[name];
        }
        for (int i = 1; i < n; i ++)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            LCA::AddNode(u, v);
            LCA::AddNode(v, u);
        }
        LCA::dfs(1, 0); //dfs用于求解层数等必要参数
        LCA::ST(n*2 - 1); //藉由参数，进一步计算RMQ
        for (int i = 1; i <= n; i ++)
        {
            if(d[v[i]].second.first == 0 && d[v[i]].second.second == 0)
            {
                d[v[i]].second.first = d[v[i]].second.second = i;
                d[v[i]].first = 1;
            }else{
                int x = d[v[i]].second.first;
                int y = d[v[i]].second.second;
                int z = i;
                int len1 = LCA::dist(x, z);
                int len2 = LCA::dist(y, z);
                if(len1 > d[v[i]].first)
                {
                    d[v[i]].second.first = x;
                    d[v[i]].second.second = z;
                    d[v[i]].first = len1;
                }
                if(len2 > d[v[i]].first)
                {
                    d[v[i]].second.first = y;
                    d[v[i]].second.second = z;
                    d[v[i]].first = len2;
                }
            }
        }
        while(m --)
        {
           char name1[10], name2[10];
           scanf("%s %s", &name1, &name2);
           int x = mp[name1], y = mp[name2];
           if(x == 0 || y == 0)
           {
               printf("-1\n");
               continue;
           }
           if(x == y)
           {
               printf("%d\n", d[x].first);
               continue;
           }
           int ans = 0;
           ans=max(ans,LCA::dist(d[x].second.first,d[y].second.first));
           ans=max(ans,LCA::dist(d[x].second.first,d[y].second.second));
           ans=max(ans,LCA::dist(d[x].second.second,d[y].second.first));
           ans=max(ans,LCA::dist(d[x].second.second,d[y].second.second));
           printf("%d\n", ans);
        }
    }
    return 0;
}











