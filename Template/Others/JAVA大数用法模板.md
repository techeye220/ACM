package Main;

import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	public static Scanner cin = new Scanner(System.in);
	public static BigInteger zero = BigInteger.valueOf(0);
	public static BigInteger one = BigInteger.valueOf(1);
	public static BigInteger two = BigInteger.valueOf(2);
	public static BigInteger bas[] = new BigInteger[4005];  
	public static BigInteger n, m;
	public static void Init()
	{
		bas[0] = one;
		for (int i = 1; i <= 4000; i ++)
		{
			bas[i] = bas[i - 1].multiply(two);
		}
	}
	public static void Solve()
	{
		int up = 0;
		BigInteger res = n, tmp, ans = zero;
		while(res.compareTo(zero) > 0)
		{
			res = res.subtract(m.multiply(bas[up]));
//			System.out.println(m.multiply(bas[up]));
//			System.out.println(res);
			up ++;
		}
		res = n;
		for (int i = up; i >= 0; i --)
		{
			tmp = bas[i].subtract(one);
			tmp = tmp.multiply(m);
			if(tmp.compareTo(res) >= 0)
			{
				continue;
			}
			BigInteger k = res.divide(bas[i]);
			k = k.min(m);
			res = res.subtract(bas[i].multiply(k));
			ans = ans.add(bas[i]);
		}
		System.out.println(ans.toString(10));
	}
	public static void main(String[] args)  
	{
		Init();
		int t;
		t = cin.nextInt();
		while(t -- > 0)
		{
			n = cin.nextBigInteger();
			m = cin.nextBigInteger();
			Solve();
		}
	}

}
