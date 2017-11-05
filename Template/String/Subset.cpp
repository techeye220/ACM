#include <iostream>
#include <set>
#include <vector>
#include <bitset>
#include <string>
using namespace std;

void SubSet(const int size)
{
	for(int i = 1; i < (1 << size); i ++)
	{
		string binary_string = bitset<25>(i).to_string();
		set<int> res;
		for (int j = 0; j < binary_string.size(); j ++)
		{
			if(binary_string[j] == '1')
			{
				res.insert(j);
			}
		}
	}
} 
int main()
{
	SubSet(25);
	return 0;
}
























