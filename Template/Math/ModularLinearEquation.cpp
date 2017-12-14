//如果 GCD(a, b)不能整除 c, 则 ax + by = c 没有整数解
// ax ≡ b (mod n) n > 0
//上式等价于二元一次方程 ax – ny = b

void modular_linear_equation(int a, int b, int n)
{
	int d, x, y, x0, gcd;
	// 可以减少扩展欧几里德溢出的可能
	gcd = GCD(a, n);
	if(b % gcd != 0){
		cout << "No Solution" << endl;
		return;
	}
	a /= gcd;
	b /= gcd;
	n /= gcd;
	d = extended_euclid(a, n, x, y);
	if(b % d == 0){
		x0 = (x*(b/d)) % n;
		int ans = n;
		for (int i = 0; i < d; i ++){
			ans = (x0 + i*(n/d)) % n;
			cout << ans << endl;
		}
	}
	else{
		cout << "No Solution" << endl;
	}
}


























