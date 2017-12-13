#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
// TREAP基本
struct Node
{
    Node *ch[2];
    int r;//优先级,构成大顶堆
    int v;//键值,构成排序二叉树

    int cmp(int x)//比较键值大小
    {
        if(x==v) return -1;
        return x<v?0:1;
    }
};

//d=0表示左旋,d=1表示右旋
void rotate(Node* &o,int d)
{
    Node *k=o->ch[d^1];
    o->ch[d^1]=k->ch[d];
    k->ch[d]=o;
    o=k;
}

//插入值为x的节点
void insert(Node* &o,int x)
{
    if(o==NULL)
    {
        o=new Node();
        o->ch[0]=o->ch[1]=NULL;
        o->v=x;
        o->r=rand();//在cstdlib头声明
    }
    else
    {
        //如这里改成int d=o->cmp(x);
        //就不可以插入相同的值，因为d可能为-1
        int d=x<(o->v)?0:1;
        insert(o->ch[d],x);
        if(o->ch[d]->r > o->r)
            rotate(o,d^1);
    }
}

//删除v值为x的节点
void remove(Node *&o,int v)
{
    if(o==NULL) return ;//空时返回

    int d=o->cmp(v);
    if(d==-1)//o就是需要删除的节点
    {
        Node *u=o;
        if(o->ch[0] && o->ch[1])
        {
            int d2 = o->ch[0]->r < o->ch[1]->r ?0:1;
            rotate(o,d2);
            remove(o->ch[d2],v);
        }
        else
        {
            if(o->ch[0]==NULL)o=o->ch[1];
            else o=o->ch[0];
            delete u;//记得删除节点
        }
    }
    else remove(o->ch[d],v);
}
int find(Node *o,int x)
{
    while(o)
    {
        int d=o->cmp(x);
        if(d==-1)return 1; //存在
        o=o->ch[d];
    }
    return 0;              //不存在
}

