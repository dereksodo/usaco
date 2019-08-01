#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define DEBUG
#ifdef DEBUG
#define debug printf
#else
#define debug(...)
#endif
const int maxn = 205;
typedef vector<int> lnum;
const int base = 1000;
lnum fromint(int n);
lnum dp[8][maxn][maxn];
lnum c[maxn << 1][maxn << 1];
lnum ask(int i,int j)
{
	if(i < 0 || j < 0)
	{
		return fromint(0);
	}
	if(i == 0 || j == 0)
	{
		return fromint(0);
	}
	if(i == 1 || j == 1)
	{
		return fromint(0);
	}
	return dp[0][i][j];
}
bool operator <(const lnum &a,const lnum &b)
{
	if(a.size() > b.size())
	{
		return 0;
	}
	else if(a.size() < b.size())
	{
		return 1;
	}
	for(int i = a.size() - 1;i >= 0; --i)
	{
		if(a[i] != b[i])
		{
			return a[i] < b[i];
		}
	}
	return 0;
}
lnum operator +(const lnum &a,const lnum &b)
{
	lnum ret;
	int large = max((int)a.size(),(int)b.size());
	ret.assign(large + 1,0);
	int carry = 0;
	for(int i = 0;i < large || carry; ++i)
	{
		int ai = (i > (int)a.size() - 1 ? 0 : a[i]);
		int bi = (i > (int)b.size() - 1 ? 0 : b[i]);
		ret[i] = ai + bi + carry;
		carry = ret[i] / base;
		ret[i] %= base;
	}
	while((int)ret.size() > 1 && !ret.back())
	{
		ret.pop_back();
	}
	return ret;
}
lnum operator *(const lnum &a,const lnum &b)
{
	lnum ret;
	ret.assign((int)a.size() + (int)b.size(),0);
	for(int i = 0;i < (int)a.size(); ++i)
	{
		int carry = 0;
		for(int j = 0;j < (int)b.size() || carry; ++j)
		{
			int bj = (j > (int)b.size() - 1 ? 0 : b[j]);
			ret[i + j] += a[i] * bj + carry;
			carry = ret[i + j] / base;
			ret[i + j] %= base;
		}
	}
	while((int)ret.size() > 1 && !ret.back())
	{
		ret.pop_back();
	}
	return ret;
}
void Print(lnum a)
{
	for(int i = a.size() - 1;i >= 0; --i)
	{
		if(i == a.size() - 1)
		{
			printf("%d",a[i]);
		}
		else
		{
			printf("%03d",a[i]);
		}
	}
	printf("\n");
}
lnum fromint(int n)
{
	lnum ret;
	if(n == 0)
	{
		ret.push_back(0);
		return ret;
	}
	while(n)
	{
		ret.push_back(n % base);
		n /= base;
	}
	return ret;
}
lnum mypow(lnum k,int n)
{
	if(n == 0)
	{
		return fromint(0);
	}
	else if(n == 1)
	{
		return k;
	}
	lnum t = mypow(k,n / 2);
	return t * t * mypow(k,n % 2);
}
//如果球相同，p += 1 * 4,否则p += 0 * 4
//如果盒子相同，p += 1 * 2,否则p += 0 * 2
//如果可以有空盒子，p += 1 * 1,否则p += 0 * 1
//现在有n个球，m个盒子，dp[p][n][m]即为答案
void doit0()//球不同，盒子不同，没有空盒子
{
	// for(int n = 1;n < maxn; ++n)
	// {
	// 	for(int m = 1;m < maxn; ++m)
	// 	{
	// 		for(int i = 1;i <= n - m + 1; ++i)
	// 		{
	// 			dp[0][n][m] = dp[0][n][m] + (ask(n - i,m - 1) * c[n][i]);
	// 		}
	// 	}
	// }
	lnum now = fromint(1);
	for(int n = 1;n < maxn; ++n)
	{
		now = now * fromint(n);
		for(int m = 1;m < maxn; ++m)
		{
			dp[0][n][m] = now * dp[2][n][m];
		}
	}
}
void doit1()//球不同，盒子不同，有空盒子
{
	for(int n = 1;n < maxn; ++n)
	{
		for(int m = 1;m < maxn; ++m)
		{
			dp[1][n][m] = mypow(fromint(m),n);
		}
	}
}
void doit2()//球不同，盒子相同，没有空盒子
{
	for(int n = 1;n < maxn; ++n)
	{
		for(int m = 1;m < maxn; ++m)
		{
			dp[2][n][m] = (fromint(m) * dp[2][n - 1][m]) + dp[2][n - 1][m - 1];
		}
	}
}
void doit3()//球不同，盒子相同，有空盒子
{
	for(int n = 1;n < maxn; ++n)
	{
		for(int m = 1;m < maxn; ++m)
		{
			for(int i = 1;i < maxn; ++i)
			{
				dp[3][n][m] = dp[3][n][m] + dp[2][n][i];
			}
		}
	}
}
void doit4()//球相同，盒子不同，没有空盒子
{
	for(int n = 1;n < maxn; ++n)
	{
		for(int m = 1;m < maxn; ++m)
		{
			dp[4][n][m] = c[n - 1][m - 1];
		}
	}
}
void doit5()//球相同，盒子不同，有空盒子
{
	for(int n = 1;n < maxn; ++n)
	{
		for(int m = 1;m < maxn; ++m)
		{
			dp[5][n][m] = c[n + m - 1][m - 1];
		}
	}
}
void doit6()//球相同，盒子相同，没有空盒子
{
	for(int n = 1;n < maxn; ++n)
	{
		for(int m = 1;m < maxn; ++m)
		{
			dp[6][n][m] = dp[7][n - m][m];
		}
	}
}
void doit7()//球相同，盒子相同，有空盒子
{
	for(int n = 1;n < maxn; ++n)
	{
		dp[7][n][1] = fromint(1);
		dp[7][1][n] = fromint(1);
		dp[7][0][n] = fromint(1);
	}
	for(int n = 1;n < maxn; ++n)
	{
		for(int m = 1;m < maxn; ++m)
		{
			if(n >= m)
			{
				dp[7][n][m] = dp[7][n][m - 1] + dp[7][n - m][m];
			}
			else
			{
				dp[7][n][m] = dp[7][n][m - 1];
			}
		}
	}
}
void doit()
{
	for(int i = 0;i < 8; ++i)
	{
		for(int j = 0;j < maxn; ++j)
		{
			for(int k = 0;k < maxn; ++k)
			{
				dp[i][j][k] = fromint(0);
			}
		}
	}
	for(int i = 0;i < maxn << 1; ++i)
	{
		for(int j = 0;j < maxn << 1; ++j)
		{
			c[i][j] = fromint(0);
		}
	}
	c[0][0] = fromint(1);
	for(int i = 0;i < maxn << 1; ++i)
	{
		for(int j = 0;j < maxn << 1; ++j)
		{
			if(i > 0)
			{
				c[i][j] = c[i][j] + c[i - 1][j];
			}
			if(i > 0 && j > 0)
			{
				c[i][j] = c[i][j] + c[i - 1][j - 1];
			}
		}
	}
	
	doit4();
	debug("hi4\n");
	doit5();
	debug("hi5\n");
	doit2();
	debug("hi2\n");
	doit3();
	debug("hi3\n");
	doit0();
	debug("hi0\n");
	doit1();
	debug("hi1\n");
	doit7();
	debug("hi7\n");
	doit6();
	debug("hi6\n");
	debug("time = %.2lf\n",(clock() + 0.0) / CLOCKS_PER_SEC);
}
int main(int argc, char const *argv[])
{
	doit();
	while(1)
	{
		int t,n,m;
		cin>>t>>n>>m;
		Print(dp[t][n][m]);
	}
	return 0;
}