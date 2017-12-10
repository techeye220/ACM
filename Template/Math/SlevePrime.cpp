#include <cstdlib>
#include <cstdio> 
#include <cstring>
#include <cmath>

const int M = 1000; // M : size
bool mark[M]; // true : prime number
void sieve_prime()
{
	memset(mark, true, sizeof(mark));
	mark[0] = mark[1] = false;
	for(int i=2; i <= sqrt(M) ;i++) {
		if(mark[i]) {
			for(int j=i*i; j < M ;j+=i)
			mark[j] = false;
		}
	}
}

int main()
{
	
}
