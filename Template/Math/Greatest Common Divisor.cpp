#include <iostream>
using namespace std;

int GCD(int x, int y)
{
	int t;
	while(y > 0){
		t = x % y;
		x = y;
		y = t;
	}
	return x;
}
int main()
{
	cout << GCD(99, 3) << endl;
	return 0;
} 
