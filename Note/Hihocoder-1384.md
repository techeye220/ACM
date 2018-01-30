#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;
const int MAXN = 500010;
int T, N, M, cnt, a[MAXN], b[MAXN];
ll limit, maxdiff;
inline bool Cmp(int x, int y)
{
    return b[x] < b[y];
}
inline void cal(int left, int right)
{
    int n = 0;
    for (int i = left; i <= right; i ++)
        a[n ++] = b[i];
    maxdiff = 0;
    sort(a, a + n);
    for (int i = 0, j = n - 1; i < j && i < M; i ++, j --)
    {
        maxdiff += 1LL * (a[i] - a[j]) * (a[i] - a[j]);
        if(maxdiff > limit) break;
    }
}
inline void cal2(int right)
{
    maxdiff = 0;
    for (int i = 0, j = cnt - 1, k = M; k; i ++, j --, k --)
    {
        while(i < j && a[i] > right) i ++;
        while(i < j && a[j] > right) j --;
        if(i >= j)
            return;
        maxdiff += 1LL * (b[a[i]] - b[a[j]]) * (b[a[i]] - b[a[j]]);
        if(maxdiff > limit) break;
    }
}
inline void Init(int left, int right)
{
    cnt = 0;
    for (int i = left; i <= right; i ++)
    {
        a[cnt ++] = i;
    }
    sort(a, a + cnt, Cmp);
}
inline int solve()
{
    int left, right, mid, now = 0;
    int i, j, t;
    for (i = 1; i <= N; i = t + 1)
    {
        for (j = 1; i + (1 << j) - 1 <= N; j ++)
        {
            cal(i, i + (1 << j) - 1);
            if(maxdiff > limit)
                break;
        }
        t = i, left = i + (1 << (j - 1)) - 1, right = i + (1 << j) - 1;
        if(right > N)
            right = N;
        Init(i, right);
        while(left <= right)
        {
            cal2(mid = (left + right) >> 1);
            if(maxdiff <= limit)
            {
                t = mid;
                left = mid + 1;
            }else{
                right = mid - 1;
            }
        }
        now ++;
    }
    return now;
}
int main()
{
    //freopen("22.in", "r", stdin);
    cin >> T;
    while(T -- )
    {
        cin >> N >> M >> limit;
        for (int i = 1; i <= N; i ++)
            cin >> b[i];
        cout << solve() << endl;
    }
    return 0;
}


























