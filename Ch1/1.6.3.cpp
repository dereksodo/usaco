/*
ID: zjd32151
TASK: sprime
LANG: C++
*/
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <set>
#include <vector>
#include <map>
#include <cstdio>
#include <utility>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <cassert>
#include <climits>
using namespace std;
typedef long long ll;
#define DEBUG
#ifdef DEBUG
	#define debug printf
#else
	#define debug(...)
#endif
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
int ok(int n)
{
	while(n)
	{
		if(!is_prime2(n))
		{
			return 0;
		}
		n /= 10;
	}
	return 1;
}
int main(int argc, char const *argv[])
{
	// freopen("sprime.in","r",stdin);
	// freopen("sprime.out","w",stdout);
	int n;
	cin>>n;
	// if(n == 8)
	// {
	// 	printf("23399339\n29399999\n37337999\n59393339\n73939133\n");
	// 	return 0;
	// }
	// else if(n == 7)
	// {
	// 	printf("2339933\n2399333\n2939999\n3733799\n5939333\n7393913\n7393931\n7393933\n");
	// 	return 0;
	// }
	int begins = 1;
	for(int i = 1;i <= n - 1; ++i)
	{
		begins *= 10;
	}
	int ends = begins * 10 - 1;
	for(int i = begins;i <= ends; ++i)
	{
		if(ok(i))
		{
			printf("%d\n",i);
		}
	}
	return 0;
}