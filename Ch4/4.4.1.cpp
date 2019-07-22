/*
ID: zjd32151
TASK: shuttle
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
int res[500];
int main(int argc, char const *argv[])
{
	freopen("shuttle.in","r",stdin);
	freopen("shuttle.out","w",stdout);
	int n;
	cin>>n;
	int cnt = 0;
	for(int i = 1;i <= n + 1; ++i)
	{
		if(i & 1)
		{
			for(int j = n + i;j >= n - i + 2; j -= 2)
			{
				res[cnt++] = j;
			}
		}
		else
		{
			for(int j = n - i + 2;j <= n + i; j += 2)
			{
				res[cnt++] = j;
			}
		}
	}
	for(int i = n + 2;i <= 2 * n + 1; ++i)
	{
		int i2 = 2 * n + 2 - i;
		if(i2 & 1)
		{
			for(int j = n + i2;j >= n - i2 + 2; j -= 2)
			{
				res[cnt++] = j;
			}
		}
		else
		{
			for(int j = n - i2 + 2;j <= n + i2; j += 2)
			{
				res[cnt++] = j;
			}
		}
	}
	int cur = 1;
	printf("%d",res[1]);
	for(int i = 2;i < cnt; ++i)
	{
		printf(" %d",res[i]);
		cur++;
		if(cur == 20)
		{
			if(i == cnt - 1)
			{
				break;
			}
			printf("\n%d",res[++i]);
			cur = 1;
		}
	}
	if(cur != 0)
	{
		printf("\n");
	}
	return 0;
}