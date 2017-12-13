#include <iostream>
using namespace std;

#define MAXN 10000
#define _cp(a,b) ((a)<(b))
typedef int elem_t;
elem_t h[MAXN];
int n;
void init()
{
    n=0;
}
void exchange(int a,int b){
    int t = h[a];
    h[a]=h[b];
    h[b]=t;
}
//由下到上的有序化
void swim(int k){
    while( k > 1 && _cp(h[k/2],h[k]) ){
        exchange(k/2,k);
        k=k/2;
    }
}
//由上到下的有序化
void sink(int k){
    while(2*k<=n){
        int j = 2*k;
        if( j < n && _cp(h[j],h[j+1])) j++;
        if(!_cp(h[k],h[j])) break;
        exchange(k,j);
        k=j;
    }
}

void ins(elem_t e){
    h[++n] = e;
    swim(n);
}

elem_t delmax(){
    elem_t ma = h[1];
    exchange(1,n--);
    h[n+1]= 0 ;
    sink(1);
    return ma;
}

int del(elem_t& e){
    if (!n)
        return 0;
    int p,c;
    for (e=h[p=1] , c=2 ; c<n && _cp( h[c+=(c<n-1&&_cp(h[c+1],h[c]))] , h[n]) ; h[p]=h[c] ,p=c , c<<=1) ;
    h[p]=h[n--];return 1;
}
int main()
{
    int asd;
    cin>>asd;
    for(int i = 0;i<asd;i++)
    {
        int qq ;
        cin>>qq;
        ins(qq);
    }
    for(int i = 1;i<=n;i++)
        cout<<" "<<h[i];
    cout<<endl;
    return 0;
}
