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
	int to,next,flow;
}e[maxn];
int head[maxn2],dep[maxn2];
int cnt,n,m;

void addedge(int x,int y,int flow)
{
	e[cnt].to = y;
	e[cnt].next = head[x];
	e[cnt].flow = flow;
	head[x] = cnt++;
}

bool bfs(int s,int t)
{
	queue<int> q;
	memset(dep,-1,sizeof(dep));
	dep[s] = 1;
	q.push(s);
	while(!q.empty())
	{
		int v = q.front();
		q.pop();
		for(int i = head[v];i != -1; i = e[i].next)
		{
			int u = e[i].to;
			int f = e[i].flow;
			if(f > 0 && dep[u] == -1)
			{
				dep[u] = dep[v] + 1;
				q.push(u);
			}
		}
	}
	return dep[t] != -1;
}

int dfs(int s,int t,int dis)
{
	if(s == t)
	{
		return dis;
	}
	for(int i = head[s];i != -1; i = e[i].next)
	{
		int v = e[i].to;
		int f = e[i].flow;
		if((dep[v] == dep[s] + 1) && f != 0)
		{
			int df = dfs(v,t,min(dis,f));
			if(df > 0)
			{
				e[i].flow -= df;
				e[i ^ 1].flow += df;
				return df;
			}
		}
	}
	return 0;
}
int dinic(int s,int t)
{
	int maxflow = 0;
	int nowflow = 0;
	while(bfs(s,t))
	{
		nowflow = inf;
		while(nowflow)
		{
			nowflow = dfs(s,t,inf);
			maxflow += nowflow;
		}
	}
	return maxflow;
}
int main(int argc, char const *argv[])
{
	freopen("ditch.in","r",stdin);
	freopen("ditch.out","w",stdout);
	memset(head,-1,sizeof(head));
	scanf("%d%d",&n,&m);
	cnt = 0;
	for(int i = 0;i < n; ++i)
	{
		int x,y,flow;
		scanf("%d%d%d",&x,&y,&flow);
		addedge(x,y,flow);
		addedge(y,x,0);
	}
	printf("%d\n",dinic(1,m));
	return 0;
}