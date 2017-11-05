#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int Size = 25;
set<int> GetSubset(int K)
{
	set<int> res;
	int comb = (1 << K) - 1;
	while(comb < 1 << Size)
	{
		res.insert(comb);
		int x = comb & -comb, y = comb + x;
		comb = ((comb & ~y) / x >> 1) | y;
	}
	return res;
}
int main()
{
	cout << GetSubset(2).size() << endl;
	return 0;
}
















