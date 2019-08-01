#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
const int inf = INT_MAX;
const int maxn = 105;
//start 3:45
//end 3:58
struct heap{
	int a[maxn];
	int size;
	heap()
	{
		clear();
	}
	void clear()
	{
		memset(a,0,sizeof(a));
		size = 0;
	}
	void insert(int p)
	{
		if(size == maxn)
		{
			printf("The heap is full,cannot insert more.\n");
			return;
		}
		a[++size] = p;
		int pos = size;
		while(pos > 1)
		{
			int cur = pos / 2;
			if(a[pos] < a[cur])
			{
				swap(a[pos],a[cur]);
				pos = cur;
			}
			else
			{
				break;
			}
		}
	}
	int pop()
	{
		if(size == 0)
		{
			printf("There is no element left.\n");
			return inf;
		}
		int ret = a[1];
		a[1] = a[size--];
		int pos = 1;
		while(2 * pos <= size)
		{
			int cur = pos * 2;
			if(cur + 1 <= size)
			{
				if(a[cur] > a[cur + 1])
				{
					cur++;
				}
			}
			if(a[pos] > a[cur])
			{
				swap(a[pos],a[cur]);
				pos = cur;
			}
			else
			{
				break;
			}
		}
		return ret;
	}
	void print()
	{
		for(int i = 1;i <= size; ++i)
		{
			printf("%d ",a[i]);
		}
		printf("\n");
	}
};

struct RMQ{
	static const int maxn = 100005;
	int dp[maxn][30];
	int a[maxn];
	int m,n;
	void build()
	{
		for(int i = 0;i < m; ++i)
		{
			dp[i][0] = a[i];
		}
		for(int k = 1;(1 << k) <= m; ++k)
		{
			for(int i = 0;i + (1 << k) <= m; ++i)
			{
				dp[i][k] = min(dp[i][k - 1],dp[i + (1 << (k - 1))][k - 1]);
			}
		}
	}
	void query(int begin,int end)
	{
		int siz = end - begin + 1;
		int cnt = 0;
		while((1 << cnt) <= siz)
		{
			cnt++;
		}
		--cnt;
		printf("%d ",min(dp[begin][cnt],dp[end - (1 << cnt) + 1][cnt]));
	}
};

struct findLCA{
	static const int maxn = 500005;
	static const int maxn2 = 21;
	struct edge{
		int to,next;
	}e[maxn << 1];
	int tot = 0,head[maxn],depth[maxn],fa[maxn][maxn2];
	int n,m;

	void addedge(int x,int y)
	{
		e[++tot].to = y;
		e[tot].next = head[x];
		head[x] = tot;

		e[++tot].to = x;
		e[tot].next = head[y];
		head[y] = tot;
	}

	void dfs(int u)
	{
		for(int i = head[u];i; i = e[i].next)
		{
			int v = e[i].to;
			if(v == fa[u][0])
			{
				continue;
			}
			fa[v][0] = u;
			depth[v] = depth[u] + 1;
			dfs(v);
		}
	}

	void pre()
	{
		for(int j = 1;j < maxn2; ++j)
		{
			for(int i = 1;i <= n; ++i)
			{
				fa[i][j] = fa[fa[i][j - 1]][j - 1];
			}
		}
	}

	int LCA(int x,int y)
	{
		if(depth[x] < depth[y])
		{
			swap(x,y);
		}
		int t = depth[x] - depth[y];
		for(int i = 20;i >= 0; --i)
		{
			if(t & (1 << i))
			{
				x = fa[x][i];
			}
		}
		if(x == y)
		{
			return x;
		}
		
		for(int i = 20;i >= 0; --i)
		{
			if(fa[x][i] != fa[y][i])
			{
				x = fa[x][i];
				y = fa[y][i];
			}
		}
		if(x != y)
		{
			return fa[x][0];
		}
		return x;
	}
	//first,addedge
	//second,dfs(root)
	//third,pre()
	//finally,LCA()
};
int main(int argc, char const *argv[])
{
	heap a;
	a.insert(3);
	a.insert(4);
	a.insert(5);
	a.insert(6);
	a.print();
	printf("%d\n",a.pop());
	printf("%d\n",a.pop());
	a.insert(1);
	printf("%d\n",a.pop());
	a.print();
	a.clear();
	a.print();
	return 0;
}