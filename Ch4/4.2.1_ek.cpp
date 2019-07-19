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
int f[maxn2],head[maxn2],dist[maxn2],vis[maxn2],pre[maxn2],last[maxn2];
int cnt;
void addedge(int x,int y,int flow,int cost)
{
	e[cnt].to = y;
	e[cnt].next = head[x];
	e[cnt].flow = flow;
	e[cnt].cost = cost;
	head[x] = cnt++;
}
bool spfa(int s,int t)
{
	queue<int> q;
	memset(vis,0x00,sizeof(vis));
	memset(f,inf,sizeof(f));
	memset(dist,inf,sizeof(dist));
	q.push(s);
	dist[s] = 0;
	pre[t] = -1;
	vis[s] = 1;
	while(!q.empty())
	{
		int now = q.front();
		q.pop();
		vis[now] = 0;
		for(int i = head[now];i != -1; i = e[i].next)
		{
			int v = e[i].to;
			if(e[i].flow > 0 && dist[v] > dist[now] + e[i].cost)
			{
				dist[v] = dist[now] + e[i].cost;
				pre[v] = now;
				last[v] = i;
				f[v] = min(f[now],e[i].flow);
				if(!vis[v])
				{
					q.push(v);
					vis[v] = 1;
				}
			}
		}
	}
	int now = t;
	while(now != s && now != -1)
	{
		// printf("now = %d\n",now);
		now = pre[now];
	}
	// printf("now = %d\n",s);
	return pre[t] != -1;
}
int ek(int s,int t)
{
	int maxflow = 0;
	while(spfa(s,t))
	{
		int now = t;
		maxflow += f[t];
		// printf("f[%d] = %d\n",t,f[t]);
		// printf("*********************************\n");
		while(now != s)
		{
			e[last[now]].flow -= f[t];
			e[last[now] ^ 1].flow += f[t];
			now = pre[now];
		}
	}
	return maxflow;
}
int main(int argc, char const *argv[])
{
	freopen("ditch.in","r",stdin);
	freopen("ditch.out","w",stdout);
	memset(head,-1,sizeof(head));
	int n,m;
	cin>>n>>m;
	for(int i = 0;i < n; ++i)
	{
		//cost = 0
		int x,y,flow;
		scanf("%d%d%d",&x,&y,&flow);
		addedge(x,y,flow,0);//x,y,flow,cost
		addedge(y,x,0,0);//y,x,0,-cost
	}
	printf("%d\n",ek(1,m));
	return 0;
}