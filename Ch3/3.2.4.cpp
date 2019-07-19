/*
ID: zjd32151
TASK: ratios
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
struct p{
	int a,b,c;
	void get()
	{
		scanf("%d%d%d",&a,&b,&c);
	}
}tar,p[3];
int gcd(int a,int b)
{
	return b == 0 ? a : gcd(b,a % b);
}
int main(int argc, char const *argv[])
{
	freopen("ratios.in","r",stdin);
	freopen("ratios.out","w",stdout);
	tar.get();
	for(int i = 0;i < 3; ++i)
	{
		p[i].get();
	}
	for(int i = 0;i <= 100; ++i)
	{
		for(int j = 0;j <= 100; ++j)
		{
			for(int k = 0;k <= 100; ++k)
			{
				if(i + j + k == 0)
				{
					continue;
				}
				int first = p[0].a * i + p[1].a * j + p[2].a * k;
				int second = p[0].b * i + p[1].b * j + p[2].b * k;
				int third = p[0].c * i + p[1].c * j + p[2].c * k;
				int t = 0;
				if(tar.a != 0 && first != 0)
				{
					t = first / tar.a;
				}
				else if(tar.b != 0 && second != 0)
				{
					t = second / tar.b;
				}
				else if(tar.c != 0 && third != 0)
				{
					t = third / tar.c;
				}
				if(tar.a * t == first && tar.b * t == second && tar.c * t == third)
				{
					printf("%d %d %d %d\n",i,j,k,t);
					return 0;
				} 
			}
		}
	}
	printf("NONE\n");
	return 0;
}