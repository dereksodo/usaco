/*
ID: zjd32151
TASK: schlnet
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
const int maxn = 50000;
struct edge{
	int to,next;
}e[maxn];
int dfn[maxn],low[maxn],head[maxn],in[maxn],out[maxn];
int color[maxn],vis[maxn];
int G[maxn][3];
int n,cnt,col,sum;
int s[maxn],top;
void addedge(int u,int v)
{
	e[++cnt].to = v;
	e[cnt].next = head[u];
	head[u] = cnt;
}
void tarjan(int v)
{
	sum++;
	dfn[v] = low[v] = sum;
	s[top++] = v;
	vis[v] = 1;
	for(int u = head[v];u != -1;u = e[u].next)
	{
		if(vis[e[u].to] == 0)
		{
			tarjan(e[u].to);
			low[v] = min(low[v],low[e[u].to]);
		}
		else if(vis[e[u].to] == 1)
		{
			low[v] = min(low[v],dfn[e[u].to]);
		}
	}
	if(dfn[v] == low[v])
	{
		col++;
		do{
			--top;
			color[s[top]] = col;

			vis[s[top]] = -1;
		}while(s[top] != v);
	}
}
int main(int argc, char const *argv[])
{
	freopen("schlnet.in","r",stdin);
	freopen("schlnet.out","w",stdout);
	cin>>n;
	int cnt2 = 0;
	memset(head,-1,sizeof(head));
	for(int i = 1;i <= n; ++i)
	{
		int x;
		while(scanf("%d",&x) && x != 0)
		{
			addedge(i,x);
			G[++cnt2][1] = i;
			G[cnt2][2] = x;
		}
	}
	for(int i = 1;i <= n; ++i)
	{
		if(!vis[i])
		{
			tarjan(i);
		}
	}
	for(int i = 1;i <= cnt2; ++i)
	{
		if(color[G[i][1]] != color[G[i][2]])
		{
			in[color[G[i][2]]]++;
			out[color[G[i][1]]]++;
		}
	}
	int ansin = 0,ansout = 0;
	for(int i = 1;i <= col; ++i)
	{
		if(in[i] == 0)
		{
			ansin++;
		}
		if(out[i] == 0)
		{
			ansout++;
		}
	}
	if(col == 1)
	{
		printf("1\n0\n");
	}
	else
	{
		printf("%d\n%d\n",ansin,max(ansin,ansout));
	}
	return 0;
}