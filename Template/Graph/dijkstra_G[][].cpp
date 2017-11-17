#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#define MAX 9999999

using namespace std;

int G[203][203];//二维数组 图的存储
int n, s, t;//n 点的个数 , s 起点 ,t 终点

void dijkstra()
{
    bool vis[203];//相当于集合Q的功能， 标记该点是否访问过
    int dis[203];//保存最短路径
    int i, j, k;

    for(i=0;i<n;i++)//初始化
        dis[i] = G[s][i];//s—>各个点的距离
    memset(vis,false,sizeof(vis));//初始化为假 表示未访问过
    dis[s] = 0;//s->s 距离为0
    vis[s] = true;//s点访问过了，标记为真
    for(i=1;i<n;i++)//G.V-1次操作+上面对s的访问 = G.V次操作
    {
        k = -1;
        for(j=0;j<n;j++)//从尚未访问过的点中选一个距离最小的点
            if(!vis[j] && (k==-1||dis[k]>dis[j]))//未访问过 && 是距离最小的
                k = j;
        if(k == -1)//若图是不连通的则提前结束
            break;//跳出循环
        vis[k] = true;//将k点标记为访问过了
        for(j=0;j<n;j++)//松弛操作
            if(!vis[j] && dis[j]>dis[k]+G[k][j])//该点为访问过 && 可以进行松弛
			{
                dis[j] = dis[k]+G[k][j];//j点的距离  大于当前点的距离+w(k,j) 则松弛成功，进行更新
				//pre[j]=k;		//路径还原用
			}
	}
    printf("%d\n",dis[t]==MAX?-1:dis[t]);//输出结果
    /*			路径还原用
		queue<int> que;//申请一个队列
		for(t;t!=-1;t=pre[t])//从t 一直寻找到s
		que.push(t);//放入队列
		printf("%d",que.front());//输出第一个
		que.pop();//删除
		while(!que.empty()){//队列不为空
			printf("——>%d",que.front());//输出
			que.pop();//删除
		}
	*/
}

int main()
{
    int m, i, j, u, v, w;

    while(scanf("%d %d",&n,&m)==2){//获取点的个数 边的个数
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                G[i][j] = i==j?0:MAX;//初始化，本身到本身的距离为0，其他的为无穷大
        while(m--){
            scanf("%d %d %d",&u,&v,&w);//获取u，v，w(u,v);
            if(G[u][v]>w)//因为初始化的操作  && 若有重边要去最小的权重值
                G[u][v] = G[v][u] = w;//无向图 双向
        }
        scanf("%d %d",&s,&t);//获取起止点
        dijkstra();
    }
    return 0;
}
