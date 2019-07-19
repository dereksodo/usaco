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
int h[maxn2],head[maxn2],surplus[maxn2],vis[maxn2],gap[maxn2];
int cnt,n,m;
struct cmp{
	bool operator()(int a,int b)const
	{
		return h[a] < h[b];
	}
};
priority_queue<int,vector<int>,cmp> pq;
void addedge(int x,int y,int flow,int cost)
{
    e[cnt].to = y;
    e[cnt].next = head[x];
    e[cnt].flow = flow;
    e[cnt].cost = cost;
    head[x] = cnt++;
}
bool bfs(int s,int t)//backwards
{
    queue<int> q;
    memset(h,inf,sizeof(h));
    h[t] = 0;
    q.push(t);
    while(!q.empty())
    {
        int v = q.front();
        q.pop();
        for(int i = head[v];i != -1; i = e[i].next)
        {
            int u = e[i].to;
            if(e[i ^ 1].flow && h[u] > h[v] + 1)
            {
                h[u] = h[v] + 1;
                q.push(u);
            }
        }
    }
    return h[s] != inf;
}
void relabel(int u)
{
    h[u] = inf;
    for(int i = head[u];i != -1; i = e[i].next)
    {
        int v = e[i].to;
        debug("h[u] = %d,h[v] = %d,e[%d].flow = %d\n",h[u],h[v],i,e[i].flow);
        if(e[i].flow && (h[v] + 1 < h[u]))
        {
            h[u] = h[v] + 1;
        }
    }
}
void push(int s,int t,int u)
{
    for(int i = head[u];i != -1; i = e[i].next)
    {
        int v = e[i].to;
        if(e[i].flow && (h[v] + 1 == h[u]))
        {
            int nowflow = min(surplus[u],e[i].flow);
            e[i].flow -= nowflow;
            e[i ^ 1].flow += nowflow;
            surplus[u] -= nowflow;
            surplus[v] += nowflow;
            if(v != s && v != t && !vis[v])
            {
                pq.push(v);
                vis[v] = 1;
            }
            if(!surplus[u])
            {
                break;
            }
        }
    }
}
int hlpp(int s,int t)
{
    if(!bfs(s,t))
    {
        return 0;
    }
    h[s] = m;
    memset(gap,0x00,sizeof(gap));
    for(int i = 1;i <= m; ++i)
    {
        if(h[i] != inf)
        {
            gap[h[i]]++;
        }
    }
    for(int i = head[s];i != -1; i = e[i].next)
    {
        int v = e[i].to;
        if(e[i].flow)
        {
            int nowflow = e[i].flow;
            e[i].flow -= nowflow;
            e[i ^ 1].flow += nowflow;
            surplus[s] -= nowflow;
            surplus[v] += nowflow;
            if(v != s && v != t && !vis[v])
            {
                pq.push(v);
                vis[v] = 1;
            }
        }
    }
    while(!pq.empty())
    {
        int v = pq.top();
        pq.pop();
        vis[v] = 0;
        push(s,t,v);
        debug("surplus[%d] = %d\n",v,surplus[v]);
        if(surplus[v] && h[v] != inf)
        {
            debug("h[%d] = %d\n",v,h[v]);
            gap[h[v]]--;
            if(!gap[h[v]])
            {

                for(int i = 1;i <= m; ++i)
                {
                    if(i != s && i != t && h[i] > h[v] && h[i] < (m + 1))
                    {
                        h[i] = m + 1;
                    }
                }
            }
            relabel(v);
            gap[h[v]]++;
            pq.push(v);
            vis[v] = 1;
        }
    }
    return surplus[t];
}
int main(int argc, char const *argv[])
{
    freopen("ditch.in","r",stdin);
    freopen("ditch.out","w",stdout);
    memset(head,-1,sizeof(head));
    memset(vis,0x00,sizeof(vis));
    cin>>n>>m;
    for(int i = 0;i < n; ++i)
    {
        int x,y,flow;
        scanf("%d%d%d",&x,&y,&flow);
        addedge(x,y,flow,0);
        addedge(y,x,0,0);
    }
    printf("%d\n",hlpp(1,m));
    return 0;
}