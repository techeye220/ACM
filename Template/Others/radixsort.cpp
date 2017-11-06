#include<iostream>
using namespace std;

#define   MAXSIZE   10000
//获取一个数的长度
int length(int a){
    int num = 0;
    while(a){
        a/=10;
        num++;
    }
    return num;
}
//获取数组最长的数的长度
int maxLength(int ar[],int n) {
        int malen = 0;
        for (int i = 0; i < n; i++) {
            int currentLength = length(ar[i]);
            if (malen < currentLength) {
                malen = currentLength;
            }
        }
        return malen;
    }
//获取x右往左从0开始的第d位数字
int getdigit(int x, int d) {
        int a[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };
        return ((x / a[d]) % 10);
}

void lsdradix_sort(int arr[],int d,int n)
{
    const int radix = 10;
    int count[radix], i, j;
    int *bucket = new int[n];

    //按照分配标准依次进行排序过程
    for(int k = 1; k <= d; ++k)
    {
        //置空
        for(i = 0; i < radix; i++)
        {
            count[i] = 0;
        }
        //统计各个桶中所盛数据个数
        for(i = 0; i < n; i++)
        {
           count[getdigit(arr[i], k)]++;
        }
        //count[i]表示第i个桶的右边界索引
        for(i = 1; i < radix; i++)
        {
            count[i] = count[i] + count[i-1];
        }
        for(i = n-1;i >= 0; --i)        //这里要从右向左扫描，保证排序稳定性
        {
            j = getdigit(arr[i], k);  //例如：576的第3位是5
            bucket[count[j]-1] = arr[i];
            /**
            这里要注意的是，count的内容是不会重复的
            因为在上一个循环中就已经规定了各位占多少位数了。
            */
            --count[j];               //对应桶的装入数据索引减一
        }
        //注意：此时count[i]为第i个桶左边界
        //从各个桶中收集数据
        for(i = 0,j = 0; i < n; ++i, ++j)
        {
            arr[i] = bucket[j];
        }
    }
    delete [] bucket;
}

int main()
{
    int  br[10] = {789, 80, 90, 589, 998, 965, 852, 123, 456, 20};
    int len = maxLength(br,10);
    lsdradix_sort(br,len,3);
    for(int i=0;i<10;i++)
        cout<<br[i]<<" ";
    cout<<endl;
    return 0;
}
