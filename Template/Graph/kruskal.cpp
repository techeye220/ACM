/*
kruskal算法求最小生成树
*/
int grond[n][n];
int n,e;
 
typedef struct node  
{  
    int u;     //边的起始顶点   
    int v;     //边的终止顶点   
    int w;     //边的权值   
}Edge; 

void kruskal()  
{  
    int i,j,k;  
    int vset[n];       //辅助数组，判定两个顶点是否连通   
    int E[e];            //存放所有的边   
    k=0;//E数组的下标从0开始   
    for (i=0;i<n;i++)  
    {  
        for (j=0;j<n;j++)  
        {  
            if (grond[i][j]!=0 && grond[i][j]!=INF)  
            {  
                E[k].u=i;  
                E[k].v=j;  
                E[k].w=grond[i][j];  
                k++;  
            }  
        }  
    }     
    sort(E,E+k);                            //堆排序，按权值从小到大排列       
    for (i=0;i<G.n;i++)                                    //初始化辅助数组   
    {  
        vset[i]=i;  
    }  
    k=1;                                                   //生成的边数，最后要刚好为总边数   
    j=0;                                                   //E中的下标   
    while (k<n)  
    {   
        sn1=vset[E[j].u];  
        sn2=vset[E[j].v];      //得到两顶点属于的集合编号   
        if (sn1!=sn2)          //不在同一集合编号内的话，把边加入最小生成树   
        {
            //printf("%d ---> %d, %d",E[j].u,E[j].v,E[j].w);       
            k++;  
            for (i=0;i<G.n;i++)  
            {  
                if (vset[i]==sn2)  
                {  
                    vset[i]=sn1;  
                }  
            }             
        }  
        j++;  
    }  
} 