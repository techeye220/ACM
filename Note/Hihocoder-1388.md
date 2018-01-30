#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 240040;
const double eps=1e-8;
const double PI = acos(-1.0);
typedef long long LL;
typedef long long ll;

struct Complex {
    double real, image;
    Complex(double real, double image):real(real),image(image) {}
    Complex() {}
    friend Complex operator + (const Complex &c1, const Complex &c2) {
        return Complex(c1.real + c2.real, c1.image + c2.image);
    }
    friend Complex operator - (const Complex &c1, const Complex &c2) {
        return Complex(c1.real - c2.real, c1.image - c2.image);
    }
    friend Complex operator * (const Complex &c1, const Complex &c2) {
        return Complex(c1.real*c2.real - c1.image*c2.image, c1.real*c2.image + c1.image*c2.real);
    }
}A[maxn],B[maxn];

struct IterativeFFT {
    Complex A[maxn];

    int rev(int id, int len) {
        int ret = 0;
        for(int i = 0; (1 << i) < len; i++) {
            ret <<= 1;
            if(id & (1 << i)) ret |= 1;
        }
        return ret;
    }

    //当DFT= 1时是DFT, DFT = -1则是逆DFT
    //对长度为len(2的幂)的数组进行DFT变换
    void FFT(Complex *a,int len, int DFT) {
        for(int i = 0; i < len; i++)
            A[rev(i, len)] = a[i];
        for(int s = 1; (1 << s) <= len; s++) {
            int m = (1 << s);
            Complex wm = Complex(cos(DFT*2*PI/m), sin(DFT*2*PI/m));
            //这一层结点的包含数组元素个数都是(1 << s)
            for(int k = 0; k < len; k += m) {
                Complex w = Complex(1, 0);
                //折半引理, 根据两个子节点计算父亲节点
                for(int j = 0; j < (m >> 1); j++) {
                    Complex t = w*A[k + j + (m >> 1)];
                    Complex u = A[k + j];
                    A[k + j] = u + t;
                    A[k + j + (m >> 1)] = u - t;
                    w = w*wm;
                }
            }
        }
        if(DFT == -1) for(int i = 0; i < len; i++) A[i].real /= len, A[i].image /= len;
        for(int i=0; i<len; i++) a[i]=A[i];
    }

    int solve(Complex* a,Complex* b,int len,int n){
        FFT(a, len, 1);
        FFT(b, len, 1);
        for (int i = 0; i < len; i ++)
        {
            a[i] = a[i] * b[i];
        }
        FFT(a, len, -1);
        ll maxi = a[n - 1].real + a[2 * n - 1].real;
        int pos = 0;
        for (int i = 0; i <= n - 2; i ++)
        {
            if(maxi + eps < a[i].real + a[i + n].real)
            {
                pos = n - 1 - i;
                maxi = a[i].real + a[i + n].real;
            }
        }
        return pos;
    }

} myfft;

ll a[maxn / 4], b[maxn / 4];
int main()
{
    freopen("22.in", "r", stdin);
    int T, N;
    scanf("%d", &T);
    while(T --)
    {
        scanf("%d", &N);
        int len = 1;
        ll res = 0;
        while(len < N * 2)
        {
            len <<= 1;
        }
        for (int i = 0; i < N; i ++)
        {
            scanf("%lld", &a[i]);
        }
        for (int i = 0; i < N; i ++)
        {
            scanf("%lld", &b[i]);
        }
        for (int i = 0; i < len; i ++)
        {
            A[i] = Complex(0, 0);
            B[i] = Complex(0, 0);
        }
        for (int i = 0; i < N; i ++)
        {
            A[i] = Complex(a[i], 0);
            B[i] = Complex(b[N - 1 - i], 0);
        }
        int pos = myfft.solve(A, B, len, N);
//        cout << "POS: " << pos << endl;
        for (int i = 0; i < N; i ++)
        {
            res += (a[i] - b[(i+pos)%N]) * (a[i] - b[(i+pos)%N]);
        }
        cout << res << endl;
    }
    return 0;
}
