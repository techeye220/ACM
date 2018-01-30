//lucas原理，C(N, K)为带模的组合数求解
ll lucas(ll n, ll k)
{
    if(k == 0) return 1;
    return (C(n % p, k % p) % p) * (lucas(n / p, k / p) % p) % p;
}