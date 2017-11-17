/*
SPFA算法
求最短路
SPFA() :

　　　　1   对图的建立和处理，dis[N]数组的初始化等等操作
　　　　2   Q += s //Q 为一个队列  s为源点
　　　　3   while Q ≠ ∅//队列不为空
　　　　4　 　	u = Q中的点//从Q中取出一个点u
　　　　5　　　把u点标记为为访问过的
　　　　6　　　 for each vertex v∈ G.Adj[u]//对所有的边
　　　　7  　　　　　　relax(u,v,w)//进行松弛
　　　　8             　　　　　if(v  未被访问过)//若v未被访问过
　　　　9　　　　　　　　　　　　Q += v;//加入队列
稀疏图最好用
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#define MAX 9999999

using namespace std;

struct node//前向星
{
    int v,w;//v 终点，w 权值
    int next;//下一个
};
node edge[5203];//前向星
int head[503];//头指针式的数组
int cnt;//下标
int n;//点的个数

void add(int u, int v, int w)
{
    edge[cnt].v = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

bool SPFA()
{
    int i, u, v;//u 从Q中取出的点  v找到的点
    int dis[503];//保存最短路径
    int flag[503];//保存某点加入队列的次数
    bool vis[503];//标记数组
    deque<int>que;//双向队列

    fill(dis,dis+n+1,MAX);
    memset(flag,0,sizeof(flag));
    memset(vis,false,sizeof(vis));
    dis[1] = 0;// s为1
    que.push_back(1);//将s = 1 加入队列
    while(!que.empty()){
        u = que.front();
        que.pop_front();
        vis[u] = false;//标记为未访问
        for(i=head[u];i!=-1;i=edge[i].next)//对所有与该边相连的边进行查找
        {
            v = edge[i].v;//保存点 便于操作
            if(dis[v]>dis[u]+edge[i].w){//进行松弛操作
                dis[v] = dis[u]+edge[i].w;//松弛成功
                if(!vis[v]){//若该点未被标记
                    vis[v] = true;//标记为真
                    flag[v]++;//该点入队列次数++
                    if(flag[v]>=n)//若该点进入队列次数超过n次 说明有负环
                        return true;//返回有负环
                    //一下为SLF优化
                    if(!que.empty() && dis[v]<dis[que.front()])//若为队列不为空 && 队列第一个点的最短距离大于当前点的最短距离
                        que.push_front(v);//将该点放到队首
                    else//不然
                        que.push_back(v);//放入队尾
                }
            }
        }
    }
    return false;//没有负环
}

int main()
{
    int u, v, w, m, k, t;
    
    scanf("%d",&t);//获取测试数据
    while(t--){
        memset(head,-1,sizeof(head));//初始化
        cnt = 0;//下标为0  初始化
        scanf("%d %d %d",&n,&m,&k);//获取点的个数 ，正边的个数， 负边的个数
        while(m--){
            scanf("%d %d %d",&u,&v,&w);//正边获取
            add(u,v,w);//无向图
            add(v,u,w);//双向建图
        }
        while(k--){
            scanf("%d %d %d",&u,&v,&w);
            add(u,v,-w);//单向图
        }
        printf("%s\n",SPFA()?"YES":"NO");//输出结果
    }
    return 0;
}