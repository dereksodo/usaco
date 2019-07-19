/*
ID: zjd32151
TASK: fence
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
const int maxn = 1030;
int ans[maxn];
int degree[maxn];
vector<int> G[maxn];
int cnt;
void dfs(int u)
{
	while(!G[u].empty())
	{
		int v = G[u].back();
		G[u].pop_back();
		for(vector<int>::iterator iter = G[v].begin();iter != G[v].end(); ++iter)
		{
			if(*iter == u)
			{
				G[v].erase(iter,iter + 1);
				break;
			}
		}
		dfs(v);
	}
	ans[cnt++] = u;
}
int main(int argc, char const *argv[])
{
	freopen("fence.in","r",stdin);
	freopen("fence.out","w",stdout);
	int n;
	cin>>n;
	for(int i = 1;i < maxn; ++i)
	{
		degree[i] = 0;
		G[i].clear();
	}
	int minp = maxn;
	for(int i = 0;i < n; ++i)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		G[a].push_back(b);
		G[b].push_back(a);
		degree[a]++;
		degree[b]++;
		minp = min(minp,a);
	}
	for(int i = 1;i < maxn; ++i)
	{
		if(degree[i])
		{
			sort(G[i].begin(),G[i].end());
			reverse(G[i].begin(),G[i].end());
		}
	}
	int begin = minp;
	for(int i = 1;i < maxn; ++i)
	{
		if(degree[i] & 1)
		{
			begin = i;
			break;
		}
	}
	cnt = 0;
	dfs(begin);
	for(int i = cnt - 1;i >= 0; --i)
	{
		printf("%d\n",ans[i]);
	}
	return 0;
}