#include <iostream>
#include <vector>
#include <utility>
#include <cstring>
#include <stack>
#include <queue>
#include <ctime>
using namespace std;
const int maxn = 10000;
const int inf = 1e9 + 7;
struct edge{
	int from;
	int to;
	int weight;
	edge(int a,int b,int c):from(a),to(b),weight(c){};
	const bool operator < (const edge &b)const
	{
		return weight > b.weight;
	}
};
struct node_for_dijkstra_fast{
	int ind;
	int dist;
	node_for_dijkstra_fast(int a,int b):ind(a),dist(b){};
	bool operator <(const node_for_dijkstra_fast &b)const
	{
		return dist > b.dist;
	}
	void print()
	{
		printf("index = %d,dist = %d\n",ind,dist);
	}
};
int FILE_GRAPH;
string FILENAME;
vector<int> G[maxn];
vector< pair<int,int> > G_value[maxn];
int floyd_dist[maxn][maxn];
int father[maxn];
int A[maxn][maxn];
int C[maxn][maxn];//used for euler
int degree[maxn];
int dis[maxn];
int enter_cnt[maxn];
int euler_ans[maxn];
bool vis[maxn];
priority_queue<edge> q;
vector< pair<int,int> > tree_trace;
int n,m;
int minp = inf;
int euler_cnt;

int findfather(int index)
{
	if(father[index] == index)
	{
		return index;
	}
	return father[index] = findfather(father[index]);
}

void bfs(int index)
{
	//use G[][]
	memset(vis,0x00,sizeof(vis));
	queue<int> q;
	q.push(index);
	vis[index] = 1;
	while(!q.empty())
	{
		int cur = q.front();
		printf("%d ",cur);
		q.pop();
		vis[cur] = 1;
		for(int i = 0;i < G[cur].size(); ++i)
		{
			if(!vis[G[cur][i]])
			{
				q.push(G[cur][i]);
				vis[G[cur][i]] = 1;
			}
		}
	}
	memset(vis,0x00,sizeof(vis));
	printf("\n");
}

void dfs(int index)
{
	//use G[][]
	printf("%d ",index);
	vis[index] = 1;
	for(int i = 0;i < G[index].size(); ++i)
	{
		int cur = G[index][i];
		if(!vis[cur])
		{
			vis[cur] = 1;
			dfs(cur);
		}
	}
}

//directed graph.
void toposort()
{
	// use G[][],degree
	vector<int> v,ans;
	for(int i = 1;i <= n; ++i)
	{
		if(!degree[i])
		{
			v.push_back(i);
		}
	}
	while(v.size())
	{
		int cur = v[0];
		v.erase(v.begin());
		ans.push_back(cur);
		for(int i = 0;i < G[cur].size(); ++i)
		{
			int index = G[cur][i];
			degree[index]--;
			if(!degree[index])
			{
				v.push_back(index);
			}
		}
	}
	for(int i = 0;i < ans.size(); ++i)
	{
		printf("%d ",ans[i]);
	}
	printf("\n");
}

//not directed graph,联通
void prim()
{
	int MST = 0;
	int pos = 0;
	memset(dis,inf,sizeof(dis));
	memset(vis,0x00,sizeof(vis));
	vis[minp] = 1;
	for(int i = 1;i <= n; ++i)
	{
		dis[i] = A[minp][i];
	}
	int k = 1;
	while(k++ < n)
	{
		int minx = inf;
		for(int i = 1;i <= n; ++i)
		{
			if(!vis[i] && minx > dis[i])
			{
				minx = dis[i];
				pos = i;
			}
		}
		vis[pos] = 1;
		tree_trace.push_back(make_pair(k,pos));
		MST += minx;
		for(int i = 1;i <= n; ++i)
		{
			if(!vis[i] && dis[i] > A[pos][i])
			{
				dis[i] = A[pos][i];
			}
		}
	}
	printf("MST = %d\n",MST);
	return;
}

//not directed graph,可以不联通
int kruskal()
{
	for(int i = 1;i <= n; ++i)
	{
		father[i] = i;
	}
	int num = 0;
	int MST = 0;
	while(!q.empty() && num != n - 1)
	{
		edge cur = q.top();
		int f1 = findfather(cur.from);
		int f2 = findfather(cur.to);
		q.pop();
		if(f1 != f2)
		{
			father[f1] = f2;
			MST += cur.weight;
			tree_trace.push_back(make_pair(cur.from,cur.to));
			num++;
		}
	}
	printf("MST = %d\n",MST);
	return MST;
}

//单源 ，有向，无向图，不带负权边
void dijkstra(int index)
{
	memset(dis,inf,sizeof(dis));
	memset(vis,0x00,sizeof(dis));
	for(int i = 1;i <= n; ++i)
	{
		dis[i] = A[index][i];
	}
	vis[index] = 1;
	int pos = 0;
	for(int i = 1;i <= n; ++i)
	{
		int minx = inf;
		for(int j = 1;j <= n; ++j)
		{
			if(!vis[j] && minx > dis[j])
			{
				minx = dis[j];
				pos = j;
			}
		}
		vis[pos] = 1;
		for(int j = 1;j <= n; ++j)
		{
			if(!vis[j] && dis[j] > minx + A[pos][j])
			{
				dis[j] = minx + A[pos][j];
			}
		}
	}
	for(int i = 1;i <= n; ++i)
	{
		if(i == index)
		{
			continue;
		}
		if(dis[i] == inf)
		{
			printf("%d到不了%d\n",index,i);
			continue;
		}
		printf("%d->%d的最短距离为%d\n",index,i,dis[i]);
	}
}

//单源 ，有向，无向图，不带负权边
void dijkstra_fast(int index)
{
	priority_queue<node_for_dijkstra_fast> q;
	for(int i = 0;i < maxn; ++i)
	{
		dis[i] = inf;
		vis[i] = 0;
	}
	dis[index] = 0;
	q.push(node_for_dijkstra_fast(index,0));
	while(!q.empty())
	{
		node_for_dijkstra_fast u = q.top();
		q.pop();

		int min_index = u.ind;
		if(vis[min_index])
		{
			continue;
		}
		vis[min_index] = 1;

		for(int i = 0;i < G_value[min_index].size(); ++i)
		{
			int v = G_value[min_index][i].first;
			int value = G_value[min_index][i].second;
			if(!vis[v] && dis[v] > dis[min_index] + value)
			{
				dis[v] = dis[min_index] + value;
				q.push(node_for_dijkstra_fast(v,dis[v]));
			}
		}
	}
	for(int i = 1;i <= n; ++i)
	{
		if(i == index)
		{
			continue;
		}
		if(dis[i] == inf)
		{
			printf("%d到不了%d\n",index,i);
			continue;
		}
		printf("%d->%d的最短距离为%d\n",index,i,dis[i]);
	}
}

//单源 ，有向，无向图，
bool spfa(int index)
{
	memset(dis,inf,sizeof(dis));
	memset(vis,0x00,sizeof(vis));
	queue<int> q;
	q.push(index);
	vis[index] = 1;
	dis[index] = 0;
	bool flag = 0;
	while(!q.empty())
	{
		int cur = q.front();
		q.pop();
		for(int i = 1;i <= n; ++i)
		{
			if(A[cur][i] != inf)
			{
				if(dis[i] > dis[cur] + A[cur][i])
				{
					dis[i] = dis[cur] + A[cur][i];
					if(!vis[i])
					{
						q.push(i);
						enter_cnt[i]++;
						if(enter_cnt[i] >= n)
						{
							return 0;
						}
						vis[i] = 1;
					}
				}
			}
		}
	}
	for(int i = 1;i <= n; ++i)
	{
		if(i == index)
		{
			continue;
		}
		printf("%d->%d的最短距离为%d\n",index,i,dis[i]);
	}
	return 1;
}

//多源多点 有向，无向图，
void floyd()
{
	for(int i = 1;i <= n; ++i)
	{
		for(int j = 1;j <= n; ++j)
		{
			floyd_dist[i][j] = A[i][j];
		}
	}
	for(int k = 1;k <= n; ++k)
	{
		for(int i = 1;i <= n; ++i)
		{
			for(int j = 1;j <= n; ++j)
			{
				if(floyd_dist[i][k] != inf && floyd_dist[k][j] != inf 
					&& floyd_dist[i][j] > floyd_dist[i][k] + floyd_dist[k][j])
				{
					floyd_dist[i][j] = floyd_dist[i][k] + floyd_dist[k][j];
				}
			}
		}
	}
	for(int i = 1;i <= n; ++i)
	{
		for(int j = 1;j <= n; ++j)
		{
			if(i == j)
			{
				continue;
			}
			if(floyd_dist[i][j] == inf)
			{
				printf("%d到不了%d\n",i,j);
			}
			else
			{
				printf("%d->%d的最短距离为%d\n",i,j,floyd_dist[i][j]);
			}
		}
		cout<<endl;
	}
}

void dfs_euler_1(int u)
{
	while(!G[u].empty())
	{
		int v = G[u].back();
		G[u].pop_back();
		for(vector<int>::iterator iter = G[v].begin();iter != G[v].end(); ++iter)
		{
			if(*iter == u)
			{
				G[v].erase(iter,iter + 1);
				break;
			}
		}
		dfs_euler_1(v);
	}
	euler_ans[euler_cnt++] = u;
}
void dfs_euler_2(int u)
{
	for(int i = 1;i <= n; ++i)
	{
		if(C[u][i] > 0)
		{
			C[u][i]--;
			C[i][u]--;
			dfs_euler_2(i);
		}
	}
	euler_ans[euler_cnt++] = u;
}
void euler_path()
{
	memset(euler_ans,0x00,sizeof(euler_ans));
	int deg_2_cnt = 0;
	for(int i = 1;i <= n; ++i)
	{
		if(degree[i] & 1)
		{
			deg_2_cnt++;
		}
	}
	if(deg_2_cnt != 2 && deg_2_cnt != 0)
	{
		printf("无欧拉路径\n");
		return;
	}
	int begin = minp;
	for(int i = 1;i <= n; ++i)
	{
		if(degree[i] & 1)
		{
			begin = i;
			break;
		}
	}
	euler_cnt = 0;
	printf("路径:\n");
	dfs_euler_2(begin);//可改成dfs_euler_1(begin)
	for(int i = euler_cnt - 1;i > 0; --i)
	{
		printf("%d->",euler_ans[i]);
	}
	printf("%d\n",euler_ans[0]);
	printf("原图已被清除\n");
	return;
}
void euler_circuit()
{
	memset(euler_ans,0x00,sizeof(euler_ans));
	for(int i = 1;i <= n; ++i)
	{
		if(degree[i] & 1)
		{
			printf("无欧拉回路\n");
			return;
		}
	}
	int begin = minp;
	for(int i = 1;i <= n; ++i)
	{
		if(degree[i] & 1)
		{
			begin = i;
			break;
		}
	}
	euler_cnt = 0;
	printf("路径:\n");
	dfs_euler_2(begin);//可改成dfs_euler_1(begin)
	for(int i = euler_cnt - 1;i > 0; --i)
	{
		printf("%d->",euler_ans[i]);
	}
	printf("%d\n",euler_ans[0]);
	printf("原图已被清除\n");
	return;
}

void h()
{
	return;
}

void random_graph(int Max_node,int Max_edge,int Max_value,string filename)
{
	FILE_GRAPH = 1;
	FILENAME = filename;
	FILE *out;
	out = fopen(filename.c_str(),"w");
	int realn = rand() % (Max_node) + 1;
	int realm = rand() % (Max_edge) + 1;
	fprintf(out,"%d %d\n",realn,realm);
	for(int i = 0;i < realm; ++i)
	{
		fprintf(out,"%d %d %d\n",rand() % (realn) + 1,rand() % (realm) + 1,rand() % Max_value + 1);
	}
	fclose(out);
	return;
}

namespace bipartite_graph{
	const int maxn = 1005;
	int A[maxn][maxn];
	int match[maxn];
	int n,m;
	int ShowMenu() 
	{
	    printf("----------------------------------------------\n");
	    printf("|对二分图的操作如下:                         |\n");
	    printf("----------------------------------------------\n");
	    printf("| 1.建立二分图         | 2.二分图最大匹配    |\n");
	    printf("| 3.exit				     |\n");
	    printf("----------------------------------------------\n");
	    printf("请选择想要进行的操作:\n");
	    int choose = 0;
	    cin>>choose;
	    return choose % 4;
	}
	int dfs(int x)
	{
		for(int i = 1;i <= m; ++i)
		{
			if(!vis[i] && A[x][i])
			{
				vis[i] = 1;
				if(match[i] == 0 || dfs(match[i]))
				{
					match[i] = x;
					return 1;
				}
			}
		}
		return 0;
	}
	int main()
	{
		printf("Welcome to Bipartite Graph Space!\n");
		memset(A,0x00,sizeof(A));
		int ans = 0;
		while(1)
		{
			int c = ShowMenu();
			if(c == 1)
			{
				printf("输入点数,边数\n");
				cin>>n>>m;
				printf("每次输入相邻点数,再输入相邻点的编号\n");
				for(int i = 1;i <= n; ++i)
				{
					int p;
					cin>>p;
					while(p--)
					{
						int x;
						scanf("%d",&x);
						A[i][x] = 1;
					}
				}
			}
			else if(c == 2)
			{
				ans = 0;
				for(int i = 1;i <= n; ++i)
				{
					memset(vis,0x00,sizeof(vis));
					if(dfs(i))
					{
						ans++;
					}
				}
				printf("最大匹配数为%d\n",ans);
				for(int i = 1;i <= m; ++i)
				{
					if(match[i] != 0)
					{
						printf("%d 匹配 %d\n",i,match[i]);
					}
				}
			}
			else
			{
				printf("\nGoodbye!\n");
				break;
			}
		}
		return 0;
	}
};
/*
5 7
1 2 1
1 3 5
1 4 7
1 5 2
2 3 4
2 4 3
3 5 10

7 7
1 3 1
1 2 2
3 4 3
2 4 4
4 5 6
4 6 5
6 7 7

4 3
1 2 1
1 3 2
2 4 3
//dfs,bfs

5 7
1 2 3
1 4 2
1 3 1
3 4 -2
4 2 3
4 5 3
3 5 3
负权边,有向

5 7
1 2 3
1 4 2
1 3 1
2 4 3
4 5 3
3 5 3
3 4 2
无向
*/
int ShowMenu() 
{
    printf("----------------------------------------------\n");
    printf("|对图的操作如下:                            |\n");
    printf("----------------------------------------------\n");
    printf("| 1.建立有向图         | 2.建立无向图       |\n");
    printf("| 3.欧拉回路           | 4.进行拓扑排序     |\n");
    printf("| 5.dfs                | 6.bfs              |\n");
    printf("| 7.prim最小生成树     | 8.kruskal最小生成树|\n");
    printf("| 9.dijkstra最短路径   | 10.floyd最短路径   |\n");
    printf("| 11.spfa最短路径      | 12.哈密顿回路      |\n");
    printf("| 13.欧拉路径(不同与3) | 14.快速dijkstra    |\n");
    printf("| 15.random图          | 16.进入二分图空间  |\n");
    printf("| 17.exit				    |\n");
    printf("---------------------------------------------\n");
    printf("请选择想要进行的操作:\n");
    int choose = 0;
    cin>>choose;
    return choose % 18;
}
int main(int argc,char const *argv[])
{
	printf("Welcome to Graph Space!\n");
	printf("\n");
	srand(time(NULL));
	memset(A,inf,sizeof(A));
	while(1)
	{
		int c = ShowMenu();
		int index = 0;
        if(c == 1)
        {
        	if(FILE_GRAPH)
        	{
        		FILE *in;
        		in = fopen(FILENAME.c_str(),"r");
        		fscanf(in,"%d%d",&n,&m);
        		for(int i = 0;i < m; ++i)
				{
					int x,y,w;
					fscanf(in,"%d%d%d",&x,&y,&w);
					q.push(edge(x,y,w));
					G_value[x].push_back(make_pair(y,w));
					minp = min(minp,x);
					minp = min(minp,y);
					G[x].push_back(y);
					degree[y]++;
					A[x][y] = w;
					A[x][y] = min(A[x][y],w);
					C[x][y]++;
				}
				FILE_GRAPH = 0;
				continue;
        	}
        	printf("输入:点数,边数\n");
        	cin>>n>>m;
        	printf("每行输入:顶点,顶点,边权\n");
            for(int i = 0;i < m; ++i)
			{
				int x,y,w;
				cin>>x>>y>>w;
				q.push(edge(x,y,w));
				G_value[x].push_back(make_pair(y,w));
				minp = min(minp,x);
				minp = min(minp,y);
				G[x].push_back(y);
				degree[y]++;
				A[x][y] = min(A[x][y],w);
				C[x][y]++;
			}
        }
        else if(c == 2)
        {
        	if(FILE_GRAPH)
        	{
        		FILE *in;
        		in = fopen(FILENAME.c_str(),"r");
        		fscanf(in,"%d%d",&n,&m);
        		for(int i = 0;i < m; ++i)
				{
					int x,y,w;
					fscanf(in,"%d%d%d",&x,&y,&w);
					q.push(edge(x,y,w));
					q.push(edge(y,x,w));
					G_value[x].push_back(make_pair(y,w));
					G_value[y].push_back(make_pair(x,w));
					minp = min(minp,x);
					minp = min(minp,y);
					G[x].push_back(y);
					G[y].push_back(x);
					degree[y]++;
					degree[x]++;
					A[x][y] = A[y][x] = min(A[x][y],w);	
					C[x][y]++;
					C[y][x]++;
				}
				FILE_GRAPH = 0;
				continue;
        	}
        	printf("输入:点数,边数\n");
            cin>>n>>m;
            printf("每行输入:顶点,顶点,边权\n");
            for(int i = 0;i < m; ++i)
			{
				int x,y,w;
				cin>>x>>y>>w;
				q.push(edge(x,y,w));
				q.push(edge(y,x,w));
				G_value[x].push_back(make_pair(y,w));
				G_value[y].push_back(make_pair(x,w));
				minp = min(minp,x);
				minp = min(minp,y);
				G[x].push_back(y);
				G[y].push_back(x);
				degree[y]++;
				degree[x]++;
				A[x][y] = A[y][x] = min(A[x][y],w);	
				C[x][y]++;
				C[y][x]++;
			}
        }
        else if(c == 3)
        {
           euler_circuit();
        }
        else if(c == 4)
        {
            toposort();
        }
        else if(c == 5)
        {
        	cin>>index;
			memset(vis,0x00,sizeof(vis));
			printf("输入:起始点\n");
            dfs(index);
            printf("\n");
        }
        else if(c == 6)
        {
        	printf("输入:起始点\n");
        	cin>>index;
            bfs(index);
        }
        else if(c == 7)
        {
            prim();
        }
        else if(c == 8)
        {
            kruskal();
        }
        else if(c == 9)
        {
        	printf("输入:起始点\n");
        	cin>>index;
            dijkstra(index);
        }
        else if(c == 10)
        {
        	floyd();
        }
        else if(c == 11)
        {
        	printf("输入:起始点\n");
        	cin>>index;
            spfa(index);
        }
        else if(c == 12)
        {
        	h();
        }
        else if(c == 13)
        {
        	euler_path();
        }
        else if(c == 14)
        {
        	printf("输入:起始点\n");
        	cin>>index;
        	dijkstra_fast(index);
        }
        else if(c == 15)
        {
        	printf("输入:最大点数,最大边数,最大权值,文件名\n");
        	int Max_node,Max_edge,Max_value;
        	string filename;
        	cin>>Max_node>>Max_edge>>Max_value>>filename;
        	random_graph(Max_node,Max_edge,Max_value,filename);
        }
        else if(c == 16)
        {
        	bipartite_graph::main();
        }
        else
        {
        	printf("\nGoodbye!\n");
        	break;
        }
	}
	return 0;
}