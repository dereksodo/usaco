/*
ID: zjd32151
TASK: milk2
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
const int maxn = 5005;
pair<int,int> p[maxn];
int father[maxn],vis[maxn];
int nowmin,nowmax;
int findf(int u)
{
	if(father[u] == u)
	{
		return u;
	}
	return findf(father[u]);
}
void join(int u,int v)
{
	father[findf(u)] = findf(v);
}
int main(int argc, char const *argv[])
{
	freopen("milk2.in","r",stdin);
	freopen("milk2.out","w",stdout);
	int n;
	cin>>n;
	for(int i = 1;i <= n; ++i)
	{
		scanf("%d%d",&p[i].first,&p[i].second);
		father[i] = i;
	}
	sort(p + 1,p + n + 1);
	for(int i = 1;i <= n; ++i)
	{
		for(int j = i + 1;j <= n; ++j)
		{
			if(p[j].first <= p[i].second)
			{
				join(j,i);
			}
		}
	}
	vector< pair<int,int> > v;
	int ans = 0;
	for(int i = 1;i <= n; ++i)
	{
		if(!vis[i])
		{
			nowmin = 1e9 + 7;
			nowmax = -1;
			for(int j = 1;j <= n; ++j)
			{
				if(father[i] == father[j])
				{
					vis[j] = 1;
					nowmin = min(nowmin,p[j].first);
					nowmax = max(nowmax,p[j].second);
				}
			}
			v.push_back(make_pair(nowmin,nowmax));
			ans = max(ans,nowmax - nowmin);
		}
	}
	cout<<ans<<" ";
	ans = 0;
	for(int i = 0;i < v.size() - 1; ++i)
	{
		ans = max(ans,v[i + 1].first - v[i].second);
	}
	cout<<ans<<endl;
	return 0;
}
