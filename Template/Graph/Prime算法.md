int map[505][505];
int v;
int prime()
{
  bool vis[505];
  int dist[505];
    int i,j,sum=0;
  for(i=1;i<=v;i++)
  {
    vis[i]=0;
    //先假设编号为1的点加入MST 
    dist[i]=map[1][i];
  }
  vis[1]=1;
  for(i=1;i<v;i++)
  {
    int k,min=0x3f3f3f3f;
    for(j=1;j<=v;j++)
    {
      if(!vis[j]&&dist[j]<min)
      {
        min=dist[j];
        k=j;
      }
    }
    /*
    在这也统计下加入了几天边，判断是否构成MST 
    */
    sum+=dist[k];
    vis[k]=1;
    //下面更新已加入最小生成树的点离其它点的最短距离 
    for(j=1;j<=v;j++)
    {
      if(!vis[j]&&dist[j]>map[k][j])
        dist[j]=map[k][j];
    }
  }
  return sum;
}