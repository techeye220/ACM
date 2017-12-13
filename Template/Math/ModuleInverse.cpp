// ax ? 1(mod n)
int Inv(int a, int n)
{
	int d, x, y;
	d = extended_euclid(a, n, x, y);
	if(d == 1) return (x%n + n) % n;
	else return -1; // no solution
}
