#define MAX 26
const int maxnode=4000*100+100;//预计字典树最大节点数目
const int sigma_size=26;//每个节点的最多儿子数

struct Trie
{
    //这里ch用vector<26元素的数组> ch；实现的话，可以做到动态内存
    int ch[maxnode][sigma_size];//ch[i][j]==k表示第i个节点的第j个儿子是节点k
    int val[maxnode];//val[i]==x表示第i个节点的权值为x
    int sz;//字典树一共有sz个节点,从0到sz-1标号

    //初始化
    void clear()
    {
        sz=1;
        memset(ch[0],0,sizeof(ch[0]));//ch值为0表示没有儿子
    }

    //返回字符c应该对应的儿子编号
    int idx(char c)
    {
        return c-'a';
    }

    //在字典树中插入单词s,但是如果已经存在s单词会重复插入且覆盖权值
    //所以执行insert前需要判断一下是否已经存在s单词了
    void insert(char *s)
    {
        int u=0,n=strlen(s);
        for(int i=0;i<n;i++)
        {
            int id=idx(s[i]);
            if(ch[u][id]==0)//无该儿子
            {
                ch[u][id]=sz;
                memset(ch[sz],0,sizeof(ch[sz]));
                val[sz++]=0;
            }
            u=ch[u][id];
        }
        val[u]=n;
    }

    //在字典树中查找单词s
    bool search(char *s)
    {
        int n=strlen(s),u=0;
        for(int i=0;i<n;i++)
        {
            int id=idx(s[i]);
            if(ch[u][id]==0)
                return false;
            u=ch[u][id];
        }
        return val[u];
    }
};
Trie trie;//定义一个字典树