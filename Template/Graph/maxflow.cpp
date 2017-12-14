//最大流模板,可处理重边
//且节点编号从1到n,边编号从0到m-1
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#define INF 1e9
using namespace std;
const int maxn=15+5;//之前这里只写10+5,一直TLE,真是悲剧

struct Edge
{
    Edge(){}
    Edge(int from,int to,int cap,int flow):from(from),to(to),cap(cap),flow(flow){}
    int from,to,cap,flow;
};

struct Dinic
{
    int n,m,s,t;            //结点数,边数(包括反向弧),源点与汇点编号
    vector<Edge> edges;     //边表 edges[e]和edges[e^1]互为反向弧
    vector<int> G[maxn];    //邻接表,G[i][j]表示结点i的第j条边在e数组中的序号
    bool vis[maxn];         //BFS使用,标记一个节点是否被遍历过
    int d[maxn];            //d[i]表从起点s到i点的距离(层次)
    int cur[maxn];          //cur[i]表当前正访问i节点的第cur[i]条弧

    void init(int n,int s,int t)
    {
        this->n=n,this->s=s,this->t=t;
        for(int i=1;i<=n;i++) G[i].clear();
        edges.clear();
    }

    void AddEdge(int from,int to,int cap)
    {
        edges.push_back( Edge(from,to,cap,0) );
        edges.push_back( Edge(to,from,0,0) );
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool BFS()
    {
        memset(vis,0,sizeof(vis));
        queue<int> Q;//用来保存节点编号的
        Q.push(s);
        d[s]=0;
        vis[s]=true;
        while(!Q.empty())
        {
            int x=Q.front(); Q.pop();
            for(int i=0; i<G[x].size(); i++)
            {
                Edge& e=edges[G[x][i]];
                if(!vis[e.to] && e.cap>e.flow)
                {
                    vis[e.to]=true;
                    d[e.to] = d[x]+1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    //a表示从s到x目前为止所有弧的最小残量
    //flow表示从x到t的最小残量
    int DFS(int x,int a)
    {
        if(x==t || a==0)return a;
        int flow=0,f;//flow用来记录从x到t的最小残量
        for(int& i=cur[x]; i<G[x].size(); i++)
        {
            Edge& e=edges[G[x][i]];
            if(d[x]+1==d[e.to] && (f=DFS( e.to,min(a,e.cap-e.flow) ) )>0 )
            {
                e.flow +=f;
                edges[G[x][i]^1].flow -=f;
                flow += f;
                a -= f;
                if(a==0) break;
            }
        }
        return flow;
    }

    int Maxflow()
    {
        int flow=0;
        while(BFS())
        {
            memset(cur,0,sizeof(cur));
            flow += DFS(s,INF);
        }
        return flow;
    }
}DC;


int main()
{
    int T; scanf("%d",&T);
    for(int kase=1; kase<=T; ++kase)
    {
        int n,m;
        scanf("%d%d",&n,&m);
        DC.init(n,1,n);
        while(m--)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            DC.AddEdge(u,v,w);
        }
        printf("Case %d: %d\n",kase,DC.Maxflow());
    }
    return 0;
}
