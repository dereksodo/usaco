/*
ID: zjd32151
TASK: race3
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
// #define DEBUG
#ifdef DEBUG
	#define debug printf
#else
	#define debug(...)
#endif
const int maxn = 55;
int G[maxn][maxn];
int n;
int vis[maxn];
int ans1[maxn],cnt1;
int ans2[maxn],cnt2;
int main(int argc, char const *argv[])
{
	freopen("race3.in","r",stdin);
	freopen("race3.out","w",stdout);
	int x;
	scanf("%d",&x);
	n = 0;
	while(x != -1)
	{
		while(x != -2)
		{
			G[n][x] = 1;
			scanf("%d",&x);
		}
		scanf("%d",&x);
		++n;
	}
	--n;
	debug("n = %d\n",n);
	for(int i = 0;i <= n; ++i)
	{
		for(int j = 0;j <= n; ++j)
		{
			debug("%d ",G[i][j]);
		}
		debug("\n");
	}
	for(int i = 1;i < n; ++i)
	{
		memset(vis,0x00,sizeof(vis));
		vis[0] = 1;
		queue<int> q;
		q.push(0);
		debug("***************************\ni = %d\n",i);
		while(!q.empty())
		{
			int v = q.front();
			q.pop();
			debug("v = %d\n",v);
			for(int j = 0;j <= n; ++j)
			{
				if(G[v][j] && j != i && !vis[j])
				{
					vis[j] = 1;
					q.push(j);
				}
			}
		}
		if(vis[n] == 0)
		{
			ans1[cnt1++] = i;
			bool flag = 1;
			for(int j = 0;j <= n; ++j)
			{
				if(!vis[j])
				{
					for(int k = 0;k <= n; ++k)
					{
						if(G[j][k] && vis[k])
						{
							flag = 0;
							break;
						}
					}
				}
			}
			if(flag)
			{
				ans2[cnt2++] = i;
			}
		}
	}
	printf("%d",cnt1);
	for(int i = 0;i < cnt1; ++i)
	{
		printf(" %d",ans1[i]);
	}
	printf("\n");
	printf("%d",cnt2);
	for(int i = 0;i < cnt2; ++i)
	{
		printf(" %d",ans2[i]);
	}
	printf("\n");
	return 0;
}