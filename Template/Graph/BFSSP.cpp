#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;
/*
BFS求最短路

*/


struct P
{
    int v, w;//v 顶点 w 最短距离
    bool operator <(const P &a)const{
        return a.w < w;//按w  从小到大排序
    }
};
struct node//前向星
{
    int v, w;//v 顶点  w权重
    int next;//下一个位置
};
node edge[2003];
int head[203];//头指针数组
int cnt, s, t;// cnt 下标

void add(int u, int v, int w)//加边操作
{
    edge[cnt].v = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

void BFS()
{
    priority_queue<P>que;//优先队列   按w从小到大
    bool vis[203];//标记数组， 标记是否被访问过
    P p, q;
    int i, v;

    memset(vis,false,sizeof(vis));//初始化
    p.v = s;//顶点为 s
    p.w = 0;//距离为 0
    que.push(p);//放入队列
    while(que.empty() == false){//队列不为空
        p = que.top();//取出队列的队首
        que.pop();//删除
        if(p.v == t){//若找到终点
            printf("%d\n",p.w);//输出结果
            return ;//返回
        }
        vis[p.v] = true;//此点标记为访问过
        for(i=head[p.v];i!=-1;i=edge[i].next)//查找与该点相连的点
        {
            v = edge[i].v;
            if(vis[v] == false){//若点未被访问过
                q.v = v;//存入结构体
                q.w = p.w+edge[i].w;//距离更新
                que.push(q);//放入队列
            }
        }
    }
    printf("-1\n");//若没有到达终点  输出-1
}

int main()
{
    int m, u, v, w, n;

    while(scanf("%d %d",&n,&m)==2){//获取点的个数  边的个数
        memset(head,-1,sizeof(head));//初始化
        cnt = 0;//初始化
        while(m--){
            scanf("%d %d %d",&u,&v,&w);//获取u,v,w
            add(u,v,w);//加边
            add(v,u,w);//无向图   双向加边
        }
        scanf("%d %d",&s,&t);//获取起止点
        BFS();
    }
    return 0;
}

题解