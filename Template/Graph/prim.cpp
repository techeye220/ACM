/*
prim算法求最小生成树
*/
const int n = 1000;
const inf = 1e9;
int grond[n][n];
int vis[n],dis[n];
int  prim(int start){
	int ma  = 0;
    for(int i =0 ;i<n;i++){
        dis[i]=grond[0][i];
        vis[i]=0;
    }
    vis[start] = 1;
    dis[start] = inf;
    for(int i = 1;i<n;i++){
        int b = 0;
        for(int j = 1;j<n;j++){		//找到当前范围最短路
            if(!vis[j] && dis[j] < dis[b])
                b=j;
        }
        if(b){
			ma += dis[b];//总路径长度
            vis[b]=1;
            for(int j = 0;j<n;j++){	//更新其他点最短路
                if(!vis[j] && dis[j]>grond[j][b])
                    dis[j]=grond[j][b];
            }
        }
    }
	return ma;
	/*
	求最长路径
    for(int i = 1;i<n;i++)
        if(dis[i]>ma)
            ma = dis[i];
    return ma;
	*/
}