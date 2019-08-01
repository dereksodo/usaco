#include <iostream>
#include <cstring>
#include <sys/time.h>
using namespace std;
const int maxn = 100000000;
int prime[maxn],plen;
bool a[maxn];
// Miller_Rabin*****

void doit1()//O(log n * log n * n)
{
	memset(prime,0x00,sizeof(prime));
	memset(a,0x00,sizeof(a));
	plen = 0;
	for(int i = 2;i < maxn; ++i)
	{
		if(!a[i])
		{
			prime[plen++] = i;
			for(int j = i * 2;j < maxn; j += i)
			{
				a[j] = 1;
			}
		}
	}
}
bool is_prime(int n)//O(sqrt n)
{
	if(n < 2)
	{
		return 0;
	}
	if(n == 2)
	{
		return 1;
	}
	for(int i = 2;i * i <= n; ++i)
	{
		if(n % i == 0)
		{
			return 0;
		}
	}
	return 1;
}
bool is_prime2(int a)//O(sqrt(n) / 6)
{
	if(a < 2)
	{
		return 0;
	}
	if(a == 2 || a == 3)
	{
		return 1;
	}
	if(a % 6 != 1 && a % 6 != 5)
	{
		return 0;
	}
	for(int i = 5;i * i <= a; i += 6)
	{
		if(a % i == 0 || a % (i + 2) == 0)
		{
			return 0;
		}
	}
	return 1;
}
void doit2()//O(n)
{
	memset(prime,0x00,sizeof(prime));
	memset(a,0x00,sizeof(a));
	plen = 0;
	for(int i = 2;i < maxn; ++i)
	{
		if(!a[i])
		{
			prime[plen++] = i;
		}
		for(int j = 0;j < plen && i * prime[j] <= maxn; ++j)
		{
			a[i * prime[j]] = 1;
			if(i % prime[j] == 0)
			{
				break;
			}
		}
	}
}
int main(int argc, char const *argv[])
{
	
	return 0;
}