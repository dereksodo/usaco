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
int dep[maxn2],gap[maxn2],head[maxn2],arcs[maxn2];
int cnt,n,m;
void addedge(int x,int y,int flow,int cost)
{
	e[cnt].to = y;
	e[cnt].next = head[x];
	e[cnt].flow = flow;
	e[cnt].cost = cost;
	head[x] = cnt++;
}
void bfs(int s)
{
	memset(dep,0x00,sizeof(dep));
	memset(gap,0x00,sizeof(gap));
	queue<int> q;
	dep[s] = 1;
	gap[1] = 1;
	q.push(s);
	while(!q.empty())
	{
		int v = q.front();
		q.pop();
		for(int i = head[v];i != -1; i = e[i].next)
		{
			int u = e[i].to;
			if(!dep[u])
			{
				q.push(u);
				dep[u] = dep[v] + 1;
				gap[dep[u]]++;
			}
		}
	}
}
int dfs(int s,int u,int t,int dis)
{
	if(u == t)
	{
		return dis;
	}
	int sum = 0;
	for(int i = arcs[u];i != -1; i = e[i].next)
	{
		int v = e[i].to;
		if(dep[u] == dep[v] + 1)
		{
			int nowflow = dfs(s,v,t,min(dis,e[i].flow));
			sum += nowflow;
			dis -= nowflow;
			e[i].flow -= nowflow;
			e[i ^ 1].flow += nowflow;
			if(!dis)
			{
				return sum;
			}
		}
	}
	if(!(--gap[dep[u]]))
	{
		dep[s] = m + 1;
	}
	dep[u]++;
	gap[dep[u]]++;
	arcs[u] = head[u];
	return sum;
}
int sap(int s,int t)
{
	int maxflow = 0;
	bfs(t);
	memcpy(&arcs[1],&head[1],sizeof(int) * m);
	maxflow = dfs(s,s,t,inf);
	while(dep[s] <= m)
	{
		maxflow += dfs(s,s,t,inf);
	}
	return maxflow;
}
int main(int argc, char const *argv[])
{
	freopen("ditch.in","r",stdin);
	freopen("ditch.out","w",stdout);
	memset(arcs,-1,sizeof(arcs));
	memset(head,-1,sizeof(head));
	cin>>n>>m;
	for(int i = 0;i < n; ++i)
	{
		int x,y,flow;
		scanf("%d%d%d",&x,&y,&flow);
		addedge(x,y,flow,0);
		addedge(y,x,0,0);
	}
	printf("%d\n",sap(1,m));
	return 0;
}