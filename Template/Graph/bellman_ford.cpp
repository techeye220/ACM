#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
/*
bellman_ford 算法
求最短路
*/
struct node
{
    int u, v, w;
};
node edge[2003];
int n, m, s, t;

void bellman_ford()
{
    int i, j;
    bool flag;//用于优化的
    int dis[203];//保存最短路径
    //初始化
    fill(dis,dis+n,MAX);//其他点为+∞
    dis[s] = 0;//源点初始化为0
     m = m<<1;//此处和m = 2*m是一样的，因为建立的无向图
    for(i=1;i<n;i++)//进行|V|-1次
    {
        flag = false;//刚刚开始标记为假
        for(j=0;j<m;j++)//对每个边
        {   
            //if  (v.d>u.d+w(u,v))
            if(dis[edge[j].u]>dis[edge[j].v]+edge[j].w){//进行松弛操作
                dis[edge[j].u] = dis[edge[j].v]+edge[j].w;//松弛成功
                flag = true;//若松弛成功则标记为真
            }
        }
        if(!flag)//若所有的边i的循环中没有松弛成功的
            break;//退出循环
        //此优化可以大大提高效率。
    }
    /*
    for(i=0;i<m;i++)
         if(dis[edge[i].u]>dis[edge[i].v]+edge[i].w)//进行|V|-1次操作后  有边还能进行松弛  说明
             return true;//存在负环
    */
    
    printf("%d\n",dis[t]==MAX?-1:dis[t]);//输出结果
}

int main()
{
    int i;

    while(scanf("%d %d",&n,&m)==2){//输入点的总数n，边的总数m
        for(i=0;i<m;i++)
        {
            scanf("%d %d %d",&edge[i].u,&edge[i].v,&edge[i].w);//每条边的u,v,w的输入
            edge[i+m].u = edge[i].v;//因为为无向图所以u—>v和v—>u 是一样的
            edge[i+m].v = edge[i].u;//So...
            edge[i+m].w = edge[i].w;//So...
        }
        scanf("%d %d",&s,&t);//起点和终点
        bellman_ford();//调用算法部分
    }
    return 0;
}
