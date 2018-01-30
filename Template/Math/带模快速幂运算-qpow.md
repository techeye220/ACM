/* 带模快速计算N的K次方,p为取模的数 */
ll qpow(ll n, ll k)
{
    ll res = 1;
    while(k){
        if(k & 1) res = (res % p) * (n % p) % p;
        n = (n % p)*(n % p) % p;
        k >>= 1;
    }
    return res;
}