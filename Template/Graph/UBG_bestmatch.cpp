#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=100+5;

//把W[maxn][maxn]数组的内容读进去之后，调用solve(n)即可计算出二分图最优匹配
//不过需要保证该图肯定有完美匹配
//因为本图用的W[][]来表示一个完全图，所以一定存在完美匹配的
struct Max_Match
{
    int W[maxn][maxn],n;  //W是权值矩阵,n为左右点集大小
    int Lx[maxn],Ly[maxn];//左右点集的可行顶标值
    bool S[maxn],T[maxn]; //标记左右点集是否已被访问过
    int left[maxn];       //left[i]=j表右i与左j匹配,为-1时表无匹配

    bool match(int i)
    {
        S[i]=true;
        for(int j=1;j<=n;j++)if(Lx[i]+Ly[j]==W[i][j] && !T[j])
        {
            T[j]=true;
            if(left[j]==-1 || match(left[j]))
            {
                left[j]=i;
                return true;
            }
        }
        return false;
    }

    //更新可行顶标,纳入更多的边进来
    void update()
    {
        int a=1<<30;
        for(int i=1;i<=n;i++)if(S[i])
        for(int j=1;j<=n;j++)if(!T[j])
        {
            a = min(a,Lx[i]+Ly[j]-W[i][j]);
        }
        for(int i=1;i<=n;i++)
        {
            if(S[i]) Lx[i]-=a;
            if(T[i]) Ly[i]+=a;
        }
    }

    int solve(int n)
    {
        this->n=n;
        memset(left,-1,sizeof(left));
        for(int i=1;i<=n;i++)//初始化可行顶标值
        {
            Lx[i]=Ly[i]=0;
            for(int j=1;j<=n;j++)
                Lx[i]=max(Lx[i], W[i][j]);
        }

        for(int i=1;i<=n;i++)
        {
            while(true)
            {
                for(int j=1;j<=n;j++) S[j]=T[j]=false;
                if(match(i)) break;
                else update();
            }
        }

        int ans=0;//最优完美匹配的权值
        for(int i=1;i<=n;i++) ans+= W[left[i]][i];
        return ans;
    }
}KM;