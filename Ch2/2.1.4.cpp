/*
ID: zjd32151
TASK: holstein
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
const int maxn = 30;
int tar[maxn],n,m;
int a[maxn][maxn];
int t[maxn],vis[maxn],anst[maxn];
int ans = 1e9;
void dfs(int index,vector<int> pa,int cnt)
{
	if(cnt > ans)
	{
		return;
	}
	bool flag = 1;
	for(int i = 1;i <= n; ++i)
	{
		if(pa[i] < tar[i])
		{
			flag = 0;
			break;
		}
	}
	if(flag)
	{
		int sum = 0;
		for(int i = 1;i <= m; ++i)
		{
			sum += vis[i];
		}
		if(sum < ans)
		{
			ans = sum;
			for(int i = 1;i <= m; ++i)
			{
				anst[i] = vis[i];
			}
			// printf("%d",sum);
			// for(int i = 1;i <= m; ++i)
			// {
			// 	if(anst[i])
			// 	{
			// 		printf(" %d",i);
			// 	}
			// }
			// printf("\n");
			// for(int i = 1;i <= n; ++i)
			// {
			// 	printf("pa[%d] = %d,tar[%d] = %d\n",i,pa[i],i,tar[i]);
			// }
			// printf("\n");
		}
	}
	else
	{
		for(int i = index + 1;i <= m; ++i)
		{
			if(!vis[i])
			{
				vis[i] = 1;
				for(int j = 1;j <= n; ++j)
				{
					pa[j] += a[i][j];
				}
				dfs(i,pa,cnt + 1);
				vis[i] = 0;
				for(int j = 1;j <= n; ++j)
				{
					pa[j] -= a[i][j];
				}
			}
		}
	}
}
int main(int argc, char const *argv[])
{
	freopen("holstein.in","r",stdin);
	freopen("holstein.out","w",stdout);
	cin>>n;
	for(int i = 1;i <= n; ++i)
	{
		scanf("%d",&tar[i]);
	}
	cin>>m;
	for(int i = 1;i <= m; ++i)
	{
		for(int j = 1;j <= n; ++j)
		{
			scanf("%d",&a[i][j]);
		}
	}
	vector<int> pa(n + 1,0);
	dfs(0,pa,0);
	int sum = 0;
	for(int i = 1;i <= m; ++i)
	{
		sum += anst[i];
	}
	printf("%d",sum);
	for(int i = 1;i <= m; ++i)
	{
		if(anst[i])
		{
			printf(" %d",i);
		}
	}
	printf("\n");
	return 0;
}