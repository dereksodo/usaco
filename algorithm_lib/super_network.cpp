#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define DEBUG
#ifdef DEBUG
	#define debug printf
#else
	#define debug(...)
#endif
const int maxn = 100005;
const int inf = 0x3f3f3f3f;
struct edge{
	int to,next,flow,cost;
}e[maxn << 1];
int f[maxn],head[maxn],dist[maxn],vis[maxn],pre[maxn],last[maxn],arcs[maxn],surplus[maxn];
int dep[maxn],gap[maxn],h[maxn];
int cnt,n,m;
void addedge(int x,int y,int flow,int cost = 0)
{
	e[cnt].to = y;
	e[cnt].next = head[x];
	e[cnt].flow = flow;
	e[cnt].cost = cost;
	head[x] = cnt++;
	e[cnt].to = x;
	e[cnt].next = head[y];
	e[cnt].flow = 0;
	e[cnt].cost = -cost;
	head[y] = cnt++;
}
namespace ek{
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
			debug("now = %d\n",now);
			now = pre[now];
		}
		debug("now = %d\n",now);
		return pre[t] != -1;
	}
	int ek(int s,int t)
	{
		int maxflow = 0;
		while(spfa(s,t))
		{
			int now = t;
			maxflow += f[t];
			debug("f[%d] = %d\n",t,f[t]);
			debug("*********************************\n");
			while(now != s)
			{
				e[last[now]].flow -= f[t];
				e[last[now] ^ 1].flow += f[t];
				now = pre[now];
			}
		}
		return maxflow;
	}
	int main()
	{
		printf("%d\n",ek(1,m));
		return 0;
	}
};

namespace dinic{
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
		for(int i = 1;i <= m; ++i)
		{
			debug("dep[%d] = %d\n",i,dep[i]);
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
				debug("nowflow = %d\n",nowflow);
				debug("*********************\n");
				maxflow += nowflow;
			}
		}
		return maxflow;
	}
	int main()
	{
		printf("%d\n",dinic(1,m));
		return 0;
	}
};

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
		memcpy(&arcs[1],&head[1],sizeof(int) * m);
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
	int main()
	{
		printf("%d\n",sap(1,m));
	}
};

namespace hlpp{

	struct cmp{
		bool operator()(int a,int b)const
		{
			return h[a] < h[b];
		}
	};
	priority_queue<int,vector<int>,cmp> pq;
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
	            debug("v = %d\n",v);
	            relabel(v);
	            debug("v = %d\n",v);
	            printf("h[%d] = %d\n",v,h[v]);
	            gap[h[v]]++;
	            pq.push(v);
	            vis[v] = 1;
	        }
	    }
	    return surplus[t];
	}
	int main()
	{
		printf("%d\n",hlpp(1,m));
	}
};

namespace ff{
	int maxflow,flag;
	int dfs(int t,int u,int flow)
	{
		if(u == t)
		{
			debug("flow = %d\n",flow);
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
	int main()
	{
		ff(1,m);
		printf("%d\n",maxflow);
	}
};

int ShowMenu()
{
	printf("---------------------------------------------\n");
    printf("|对网络的操作如下:                          |\n");
    printf("---------------------------------------------\n");
    printf("| 1.建立网络          | 2.最大流(ek)        |\n");
    printf("| 3.最大流(dinic)     | 4.最大流(sap)       |\n");
    printf("| 5.最大流(hlpp)      | 6.最大流(ff)	    |\n");
    printf("| 7.exit              |	                    |\n");
	printf("---------------------------------------------\n");
    printf("请选择想要进行的操作:\n");
    int choose = 0;
    cin>>choose;
    return choose % 8;
}
int main(int argc, char const *argv[])
{
	printf("Welcome to Network Space!\n");
	printf("\n");
	while(1)
	{
		int c = ShowMenu();
		if(c == 1)
		{
			memset(head,-1,sizeof(head));
			memset(vis,0x00,sizeof(vis));
			printf("输入边数,终点\n");
			cin>>n>>m;
			cnt = 0;
			printf("输入顶点,顶点,边权\n");
			for(int i = 0;i < n; ++i)
			{
				int x,y,flow,cost;
				scanf("%d%d%d",&x,&y,&flow/*,&cost*/);
				addedge(x,y,flow);
				// addedge(x,y,flow,cost);//x,y,flow,cost
				// addedge(y,x,0,-cost);//y,x,0,0
			}
		}
		else if(c == 2)
		{
			ek::main();
		}
		else if(c == 3)
		{
			dinic::main();
		}
		else if(c == 4)
		{
			sap::main();
		}
		else if(c == 5)
		{
			hlpp::main();
		}
		else if(c == 6)
		{
			ff::main();
		}
		else
		{
			printf("\nGoodbye\n");
			break;
		}
	}
	return 0;
}