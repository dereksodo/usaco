/*
ID: zjd32151
TASK: butter
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
const int maxn = 805;
int vis[maxn];
int d[maxn][maxn];
int cnt[maxn];
int dis[maxn];
vector< pair<int,int> > G[maxn];
const int inf = 1e9;
struct node{
	int index;
	int dist;
	node(int a,int b):index(a),dist(b){};
	bool operator <(const node &b)const
	{
		return dist > b.dist;
	}
	void print()
	{
		debug("index = %d,dist = %d\n",index,dist);
	}
};
void dijkstra_log(int start)
{
	priority_queue<node> q;
	for(int i = 0;i < maxn; ++i)
	{
		dis[i] = inf;
		vis[i] = 0;
	}
	dis[start] = 0;
	q.push(node(start,0));
	while(!q.empty())
	{
		node u = q.top();
		q.pop();

		u.print();

		int min_index = u.index;
		if(vis[min_index])
		{
			continue;
		}
		vis[min_index] = 1;

		for(int i = 0;i < G[min_index].size(); ++i)
		{
			debug("v = %d,",G[min_index][i].first);
			int v = G[min_index][i].first;
			int value = G[min_index][i].second;
			if(!vis[v] && dis[v] > dis[min_index] + value)
			{
				dis[v] = dis[min_index] + value;
				q.push(node(v,dis[v]));
			}
		}
	}
	memcpy(d[start],dis,sizeof(dis));
}
int main(int argc, char const *argv[])
{
	freopen("butter.in","r",stdin);
	freopen("butter.out","w",stdout);
	int p,n,m;
	cin>>p>>n>>m;
	for(int i = 0;i < p; ++i)
	{
		int x;
		scanf("%d",&x);
		cnt[x]++;
	}
	for(int i = 0;i < m; ++i)
	{
		int a,b,x;
		scanf("%d%d%d",&a,&b,&x);
		G[a].push_back(make_pair(b,x));
		G[b].push_back(make_pair(a,x));
	}
	for(int i = 1;i <= n; ++i)
	{
		dijkstra_log(i);
	}
	int ans = 1e9;
	for(int i = 1;i <= n; ++i)
	{
		int now = 0;
		for(int j = 1;j <= n; ++j)
		{
			now += cnt[j] * d[i][j];
		}
		ans = min(ans,now);
	}
	cout<<ans<<endl;
	return 0;
}