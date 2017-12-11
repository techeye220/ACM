#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int a[1010];
int c[1010];
int n;
inline int lowbit(int x) {
     return x & -x;
}
int sum(int x){
     return x ? c[x]+ sum( x - lowbit(x)):0;
}
/*
int getx(int x)
{
    int ans=0;
    while(x>0)
    {
        ans+=c[x];
        x-=lowbit(x);
    }
    return ans;
}
*/
void add(int x,int v){
    for(int i = x; i <= n; i += lowbit(i)){
        c[i] += v;
    }
}
/*
void add(int x,int v){
     if(x <= n){
         C[x]+= v, add( x + lowbit(i), v );
     }
}
*/
int main() {
    cin>>n;
    memset(c,0,sizeof(c));
    for(int i = 1;i<=n;i++){
        cin>>a[i];
        add(i,a[i]);
    }
    for(int i = 1;i<=n;i++)
        cout<<sum(i)<<endl;
    return 0;
}
