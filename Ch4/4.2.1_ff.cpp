/*
ID: zjd32151
TASK: ditch
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
const int maxn = 200005;
const int maxn2 = maxn / 2;
const int inf = 0x3f3f3f3f;
struct edge{
	int to,next,flow,cost;
}e[maxn];
int cnt,n,m,flag,maxflow;
int head[maxn2];
int vis[maxn2];
void addedge(int x,int y,int flow,int cost)
{
	e[cnt].to = y;
	e[cnt].next = head[x];
	e[cnt].flow = flow;
	e[cnt].cost = cost;
	head[x] = cnt++;
}
int dfs(int t,int u,int flow)
{
	if(u == t)
	{
		maxflow += flow;
		flag = 1;
		return flow;
	}
	vis[u] = 1;
	for(int i = head[u];i != -1; i = e[i].next)
	{
		int v = e[i].to;
		if(vis[v] || e[i].flow == 0)
		{
			continue;
		}
		int nowflow = dfs(t,v,min(flow,e[i].flow));
		if(flag)
		{
			e[i].flow -= nowflow;
			e[i ^ 1].flow += nowflow;
			return nowflow;
		}
	}
	return 0;
}
void ff(int s,int t)
{
	memset(vis,0x00,sizeof(vis));
	flag = 0;
	dfs(t,s,inf);
	while(flag)
	{
		memset(vis,0x00,sizeof(vis));
		flag = 0;
		dfs(t,s,inf);
	}
}
int main(int argc, char const *argv[])
{
	// freopen("ditch.in","r",stdin);
	// freopen("ditch.out","w",stdout);
	memset(head,-1,sizeof(head));
	cin>>n>>m;
	for(int i = 0;i < n; ++i)
	{
		int x,y,flow;
		scanf("%d%d%d",&x,&y,&flow);
		addedge(x,y,flow,0);
		addedge(y,x,0,0);
	}
	ff(1,m);
	cout<<maxflow<<endl;
	return 0;
}