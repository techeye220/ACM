/* 带模计算组合数C(N, K),p为取模的数, qpow为带模的快速幂运算, 其中将除法运算转成乘法运算是通过费马小定理实现的 */
ll C(ll n, ll k)
{
    if(n < k) return 0;
    if(n - k < k){
        k = n - k;
    }
    ll res = 1;
    for (ll i = 1; i <= k; i ++)s
    {
        ll a = (n - k + i) % p;
        ll b = i % p;
        res = res * (a * qpow(b, p - 2) % p) % p;
    }
    return res % p;
}