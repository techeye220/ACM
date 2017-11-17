#include <iostream>
#include <map>
using namespace std;
void exch(int &a,int &b)
{
    int t=a;
    a=b;
    b=t;
}
void charu(int a[],int n){
    for(int i=1;i<n;i++){
        for(int j=i;j>0&&a[j]<a[j-1];j--)
            exch(a[j],a[j-1]);
    }
}
void maopao(int a[],int n){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        if(a[i]>a[j]) exch(a[i],a[j]);
}
void xuanze(int a[],int n){
    for(int i=0;i<n;i++)
    {
        int mi=a[i];
        int t = -1;
        for(int j=i+1;j<n;j++)
            if(a[j]<mi)
                {mi=a[j];t = j;}
        if(t!=-1)
            exch(a[i],a[t]);
    }
}
void xir(int a[],int n)
{
    int h=1;
    while(h<n/3) h=3*h+1;//1,4,13,40,121,364,1093...
    while(h>=1)
    {
        for(int i=h;i<n;i++)
        {
            for(int j=i;j>=h&&a[j]<a[j-h];j-=h)
                exch(a[j],a[j-h]);

        }
        h/=3;
    }
}
int b[1000];
void guibing(int a[],int lo,int mid,int hi)
{
    int i=lo;
    int j=mid+1;
    for(int k=lo;k<=hi;k++)
        b[k]=a[k];
    for(int k=lo;k<=hi;k++)
        if(i>mid) a[k]=b[j++];
        else if(j>hi) a[k]=b[i++];
        else if(b[j]<b[i]) a[k]=b[j++];
        else a[k]=b[i++];
}
void guibingsort(int a[],int lo,int hi)
{
    if(hi<=lo) return ;
    int mid=lo+(hi-lo)/2;
    guibingsort(a,lo,mid);
    guibingsort(a,mid+1,hi);
    guibing(a,lo,mid,hi);
}
void guibingxiadaoshang(int a[],int n)
{
    for(int sz=1;sz<n;sz+=sz)
        for(int lo=0;lo<n-sz;lo+=sz+sz)
        guibing(a,lo,lo+sz-1,min(lo+sz+sz-1,n-1));
}
int qiefen(int a[],int lo,int hi)
{
    int i=lo;int j=hi+1;
    if(j<=i) return i;
    int v = a[lo];
    while(1)
    {
        while(i<j && v<a[--j]);
        while(i<j && a[++i]<v);
        if(i>=j) break;
        exch(a[i],a[j]);
    }
    exch(a[lo],a[j]);
    return j;
}
void quicksort(int a[],int lo,int hi)
{
    if(hi<=lo) return ;
    int j=qiefen(a,lo,hi);
    quicksort(a,lo,j-1);
    quicksort(a,j+1,hi);
}
void sink(int a[],int k,int n)
{
    while(2*k<=n)
    {
        int j=2*k;
        if(j<n && a[j]<a[j+1])j++;
        if(a[k]>=a[j]) break;
        exch(a[k],a[j]);
        k=j;
    }
}
void duipaixu(int a[],int n)
{
    for(int k=n/2;k>=1;k--)
        sink(a,k,n);
    while(n>1){
        exch(a[1],a[n--]);//左节点2k所以是a[1]，若左节点是2k-1这里就是a[0]
        sink(a,1,n);
    }
}

int main()
{
    int aaa[]={7,5,3,2,1,4,8,9};
    int bbb[]={7,5,3,2,1,4,8,9};
    int ccc[]={7,5,3,2,1,4,8,9};
    int ddd[]={7,5,3,2,1,4,8,9};
    int fff[]={0,7,5,3,2,1,4,8,9};
    xuanze(ddd,9);
    guibingsort(aaa,0,7);
    guibingxiadaoshang(bbb,8);
    duipaixu(fff,8);
    quicksort(ccc,0,7);
    for(int i=0;i<8;i++)
        cout<<aaa[i];
    cout<<endl;
    for(int i=0;i<8;i++)
        cout<<bbb[i];
    cout<<endl;
    for(int i=0;i<8;i++)
        cout<<ccc[i];
    cout<<endl;
    for(int i=0;i<8;i++)
        cout<<ddd[i];
    cout<<endl;
    for(int i=1;i<9;i++)
        cout<<fff[i];
    cout<<endl;
    return 0;
}
