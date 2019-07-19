/*
ID: zjd32151
TASK: stall4
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
const int maxn = 205;
int n,m,ans,cow[maxn];
int vis[maxn],like[maxn][maxn];
int dfs(int x)
{
	for(int i = 1;i <= m; ++i)
	{
		if(!vis[i] && like[x][i])
		{
			vis[i] = 1;
			if(cow[i] == 0 || dfs(cow[i]))
			{
				cow[i] = x;
				return 1;
			}
		}
	}
	return 0;
}
int main(int argc, char const *argv[])
{
	freopen("stall4.in","r",stdin);
	freopen("stall4.out","w",stdout);
	cin>>n>>m;
	for(int i = 1;i <= n; ++i)
	{
		int p;
		cin>>p;
		while(p--)
		{
			int x;
			scanf("%d",&x);
			like[i][x] = 1;
		}
	}
	for(int i = 1;i <= n; ++i)
	{
		memset(vis,0x00,sizeof(vis));
		if(dfs(i))
		{
			ans++;
		}
	}
	cout<<ans<<endl;
	return 0;
}