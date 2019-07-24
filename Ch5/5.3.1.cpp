/*
ID: zjd32151
TASK: milk4
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
int bn,flag;
int ans[105],now[105];
int milk[105];
int n,m;
void dfs(int basket_num,int surplus,int index)
{
	if(basket_num == bn)
	{
		if(surplus == 0)
		{
			memcpy(ans,now,sizeof(ans));
			flag = 1;
		}
		return;
	}
	if(index > n || milk[index] > ans[basket_num])
	{
		return;
	}
	now[basket_num] = milk[index];
	for(int i = 1;i * milk[index] <= surplus; ++i)
	{
		dfs(basket_num + 1,surplus - i * milk[index],index + 1);
	}
	if(index < n)
	{
		dfs(basket_num,surplus,index + 1);
	}
}
int main(int argc, char const *argv[])
{
	freopen("milk4.in","r",stdin);
	freopen("milk4.out","w",stdout);
	cin>>m>>n;
	for(int i = 1;i <= n; ++i)
	{
		scanf("%d",&milk[i]);
	}
	memset(ans,0x3f3f3f3f,sizeof(ans));
	sort(milk + 1,milk + n + 1);
	for(bn = 1;bn <= n; ++bn)
	{
		dfs(0,m,1);
		if(flag)
		{
			break;
		}
	}
	printf("%d",bn);
	for(int i = 0;i < bn; ++i)
	{
		printf(" %d",ans[i]);
	}
	printf("\n");
	return 0;
}