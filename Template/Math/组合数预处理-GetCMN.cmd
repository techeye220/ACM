/* 注意如果按照公式进行计算，除法有可能出现取整或者溢出的情况 */

void GetCMN()
{
    c[0][0] = c[1][0] = c[1][1] = 1;
    for (int i = 2; i < MAXN; i ++)
    {
        c[i][0] = 1;
        for (int j = 1; j <= i; j ++)
        {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % p;
        }
    }
    return;
}