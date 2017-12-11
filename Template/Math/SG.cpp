//f[]：可以取走的石子个数
//sg[]:0~n的SG函数值
//hash[]:mex{}
/*
如果sg[0]^sg[1]^....^sg[n]=1的话，先手赢
否则后手赢。
*/
int f[N],sg[N],hash[N];     
void getSG(int n)
{
    int i,j;
    memset(sg,0,sizeof(sg));
    for(i=1;i<=n;i++)
    {
        memset(hash,0,sizeof(hash));
        for(j=1;f[j]<=i;j++)
            hash[sg[i-f[j]]]=1;
        for(j=0;j<=n;j++)    //求mes{}中未出现的最小的非负整数
        {
            if(hash[j]==0)
            {
                sg[i]=j;
                break;
            }
        }
    }
}

//注意 S数组要按从小到大排序 SG函数要初始化为-1 对于每个集合只需初始化1遍
//n是集合s的大小 S[i]是定义的特殊取法规则的数组
int s[110],sg[10010],n;
int SG_dfs(int x)
{
    int i;
    if(sg[x]!=-1)
        return sg[x];
    bool vis[110];
    memset(vis,0,sizeof(vis));
    for(i=0;i<n;i++)
    {
        if(x>=s[i])
        {
            SG_dfs(x-s[i]);
            vis[sg[x-s[i]]]=1;
        }
    }
    int e;
    for(i=0;;i++)
        if(!vis[i])
        {
            e=i;
            break;
        }
    return sg[x]=e;
}