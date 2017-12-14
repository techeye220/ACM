//如果 GCD(a,b) = d, 则存在 x, y, 使 d = ax + by
//extended_euclid(a, b) = ax + by

#include <iostream>
using namespace std;
int extended_euclid(int a, int b, int &x, int & y)
{
	int d;
	if(b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	d = extended_euclid(b, a % b, y, x);
	y -= a / b * x;
	return d;
}

int main()
{
	int a = 10, b = 3;
	int x, y;
	cout << extended_euclid(a, b, x, y) << endl;
	cout << x << " " << y << endl;
	return 0;
}





