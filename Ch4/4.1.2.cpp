/*
ID: zjd32151
TASK: fence6
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
const int maxn = 505;
const int inf = 1e9;
struct edge{
	int len;
	int index;
	int l_cnt,r_cnt;
	int l[maxn],r[maxn];
	int l_index,r_index;
};
edge G[maxn];
int dis[maxn][maxn],mp[maxn][maxn];
int main(int argc, char const *argv[])
{
	freopen("fence6.in","r",stdin);
	freopen("fence6.out","w",stdout);
	int n;
	cin>>n;
	for(int i = 1;i <= n; ++i)
	{
		cin>>G[i].index;
		int id = G[i].index;
		cin>>G[id].len>>G[id].l_cnt>>G[id].r_cnt;
		for(int j = 1;j <= G[id].l_cnt; ++j)
		{
			scanf("%d",&G[id].l[j]);
		}
		for(int j = 1;j <= G[id].r_cnt; ++j)
		{
			scanf("%d",&G[id].r[j]);
		}
	}

	for(int i = 1;i <= n; ++i)
	{
		for(int j = 1;j <= n; ++j)
		{
			if(i == j)
			{
				continue;
			}
			dis[i][j] = mp[i][j] = inf;
		}
	}

	int num = 0;
	for(int i = 1;i <= n; ++i)
	{
		if(!G[i].l_index)
		{
			G[i].l_index = ++num;
		}
		for(int j = 1;j <= G[i].l_cnt; ++j)
		{
			int x = G[i].l[j];
			bool flag = 0;
			for(int k = 1;k <= G[x].l_cnt; ++k)
			{
				if(G[x].l[k] == i)
				{
					flag = 1;
					break;
				}
			}
			if(flag)
			{
				G[x].l_index = G[i].l_index;
			}
			else
			{
				G[x].r_index = G[i].l_index;
			}
		}

		if(!G[i].r_index)
		{
			G[i].r_index = ++num;
		}
		for(int j = 1;j <= G[i].r_cnt; ++j)
		{
			int x = G[i].r[j];
			bool flag = 0;
			for(int k = 1;k <= G[x].l_cnt; ++k)
			{
				if(G[x].l[k] == i)
				{
					flag = 1;
					break;
				}
			}
			if(flag)
			{
				G[x].l_index = G[i].r_index;
			}
			else
			{
				G[x].r_index = G[i].r_index;
			}
		}
	}

	for(int i = 1;i <= n; ++i)
	{
		mp[G[i].l_index][G[i].r_index] = dis[G[i].l_index][G[i].r_index] = G[i].len;
		mp[G[i].r_index][G[i].l_index] = dis[G[i].r_index][G[i].l_index] = G[i].len;
	}

	int ans = inf;
	for(int k = 1;k <= num; ++k)
	{
		for(int i = 1;i < k; ++i)
		{
			for(int j = i + 1;j < k; ++j)
			{
				ans = min(ans,dis[i][j] + mp[i][k] + mp[k][j]);
			}
		}

		for(int i = 1;i <= num; ++i)
		{
			for(int j = 1;j <= num; ++j)
			{
				dis[i][j] = min(dis[i][j],dis[i][k] + dis[k][j]);
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}