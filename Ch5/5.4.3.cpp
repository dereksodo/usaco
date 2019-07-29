/*
ID: zjd32151
TASK: telecow
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
const int maxn = 100005;
const int inf = 0x3f3f3f3f;
struct edge{
	int to,next,flow;
}e[maxn << 1];
struct in{
	int x[maxn],y[maxn];
}input;
int head[maxn],vis[maxn],arcs[maxn];
int dep[maxn],gap[maxn];
int cnt,n,m;
vector<int> trace;
void addedge(int x,int y,int flow)
{
	e[cnt].to = y;
	e[cnt].next = head[x];
	e[cnt].flow = flow;
	head[x] = cnt++;
}
namespace sap{
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
		memcpy(&arcs[1],&head[1],sizeof(int) * cnt);
		maxflow = dfs(s,s,t,inf);
		debug("nowflow = %d\n",maxflow);
		while(dep[s] <= m)
		{
			int cur = dfs(s,s,t,inf);
			maxflow += cur;
			debug("nowflow = %d\n",cur);
		}
		return maxflow;
	}
	int main(int s,int t)
	{
		int ret = sap(s,t);
		return ret;
	}
};
int main(int argc, char const *argv[])
{
	freopen("telecow.in","r",stdin);
	freopen("telecow.out","w",stdout);
	memset(head,-1,sizeof(head));
	memset(arcs,-1,sizeof(arcs));
	int s,t;
	cin>>n>>m>>s>>t;
	cnt = 0;
	for(int i = 1;i <= n; ++i)
	{
		addedge(i,i + n,1);
		addedge(i + n,i,0);
	}
	for(int i = 0;i < m; ++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		input.x[i] = x;
		input.y[i] = y;
		addedge(x + n,y,inf);
		addedge(y,x + n,0);
		addedge(y + n,x,inf);
		addedge(x,y + n,0);
	}
	int ans = sap::main(s + n,t);
	printf("%d\n",ans);
	memset(vis,0x00,sizeof(vis));
	for(int i = 1;i <= n; ++i)
	{
		if(ans == 0)
		{
			break;
		}
		if(i == s || i == t)
		{
			continue;
		}
		cnt = 0;
		memset(head,-1,sizeof(head));
		memset(arcs,-1,sizeof(arcs));
		for(int j = 1;j <= n; ++j)
		{
			if(i != j && !vis[j])
			{
				addedge(j,j + n,1);
				addedge(j + n,j,0);
			}
		}
		for(int j = 0;j < m; ++j)
		{
			int x = input.x[j];
			int y = input.y[j];
			if(x != i && !vis[x]
				&& y != i && !vis[y])
			{
				addedge(x + n,y,inf);
				addedge(y,x + n,0);
				addedge(y + n,x,inf);
				addedge(x,y + n,0);
			}
		}
		int now = sap::main(s + n,t);
		debug("erase %d:now = %d\n",i,now);
		if(now + 1 == ans)
		{
			ans--;
			vis[i]= 1;
			trace.push_back(i);
		}
	}
	printf("%d",trace[0]);
	for(int i = 1;i < trace.size(); ++i)
	{
		printf(" %d",trace[i]);
	}
	printf("\n");
	return 0;
}