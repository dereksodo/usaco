/*
ID: zjd32151
TASK: milk6
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
const int maxn = 20005;
const int inf = 0x3f3f3f3f;
int n,m,cnt;
struct edge{
	int to,next,flow;
}e[maxn];
int head[maxn],dep[maxn],gap[maxn],arc[maxn],vis[maxn];
struct input{
	int x,y,flow,index;
}in[maxn];
void addedge(int a,int b,int c)
{
	e[cnt].to = b;
	e[cnt].next = head[a];
	e[cnt].flow = c;
	head[a] = cnt++;
	
	e[cnt].to = a;
	e[cnt].next = head[b];
	e[cnt].flow = 0;
	head[b] = cnt++;
}
void bfs(int t)
{
	queue<int> q;
	q.push(t);
	memset(dep,0x00,sizeof(dep));
	memset(gap,0x00,sizeof(gap));
	dep[t] = 1;
	gap[1] = 1;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = head[u];i != -1; i = e[i].next)
		{
			int v = e[i].to;
			if(!dep[v])
			{
				dep[v] = dep[u] + 1;
				gap[dep[v]]++;
				q.push(v);
			}
		}
	}
}
vector<int> trace;
int dfs(int s,int t,int u,int flow)
{
	if(u == t)
	{
		return flow;
	}
	int ans = 0;
	for(int i = arc[u];i != -1;i = e[i].next)
	{
		int v = e[i].to;
		if(dep[u] == dep[v] + 1)
		{
			int cur = dfs(s,t,v,min(flow,e[i].flow));
			e[i].flow -= cur;
			e[i ^ 1].flow += cur;
			flow -= cur;
			ans += cur;
			if(!flow)
			{
				return ans;
			}
		}
	}
	if(!(--gap[dep[u]]))
	{
		dep[s] = m + 1;
	}
	dep[u]++;
	gap[dep[u]]++;
	arc[u] = head[u];
	return ans;
}
int sap(int s,int t)
{
	bfs(t);
	for(int i = 1;i <= n; ++i)
	{
		debug("dep[%d] = %d\n",i,dep[i]);
	}
	memcpy(arc,head,sizeof(arc));
	int ans = dfs(s,t,s,inf);
	while(dep[s] <= m)
	{	
		int cur = dfs(s,t,s,inf);
		ans += cur;
		debug("ans = %d\n",ans);
	}
	return ans;
}
int cmp(const void* aa,const void* bb)
{
	input a = *(input*)aa;
	input b = *(input*)bb;
	if(a.flow < b.flow)
	{
		return 1;
	}
	if(a.flow > b.flow)
	{
		return -1;
	}
	return 0;
}
int main(int argc, char const *argv[])
{
	freopen("milk6.in","r",stdin);
	freopen("milk6.out","w",stdout);
	cin>>n>>m;
	cnt = 0;
	memset(head,-1,sizeof(head));
	for(int i = 0;i < m; ++i)
	{
		scanf("%d%d%d",&in[i].x,&in[i].y,&in[i].flow);
		addedge(in[i].x,in[i].y,in[i].flow);
		in[i].index = i;
	}
	int ans = sap(1,n);
	printf("%d ",ans);
	memset(vis,true,sizeof(vis));
	qsort(in,m,sizeof(input),cmp);
	debug("\n**********************\n");
	for(int i = 0;i < m; ++i)
	{
		debug("%d ",in[i].flow);
	}
	debug("\n**********************\n");
	for(int i = 0;i < m; ++i)
	{
		if(ans == 0)
		{
			break;
		}
		if(in[i].flow <= ans)
		{
			cnt = 0;
			memset(head,-1,sizeof(head));
			for(int j = 0;j < m; ++j)
			{
				if((i == j) || (!vis[in[j].index]))
				{
					continue;
				}
				addedge(in[j].x,in[j].y,in[j].flow);
			}
			int now = sap(1,n);
			if(now + in[i].flow == ans)
			{
				debug("e[%d].flow = %d\n",i,in[i].flow);
				ans -= in[i].flow;
				debug("ans = %d\n",ans);
				vis[in[i].index] = 0;
				trace.push_back(in[i].index);
			}
		}
	}
	printf("%d\n",(int)trace.size());
	sort(trace.begin(),trace.end());
	for(int i = 0;i < trace.size(); ++i)
	{
		printf("%d\n",trace[i] + 1);
	}
	return 0;
}