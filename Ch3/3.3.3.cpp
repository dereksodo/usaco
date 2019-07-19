//https://train.usaco.org/usacogate
//zjd32151 zc65zud
/*
ID: zjd32151
TASK: camelot
LANG: C++
*/
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long ll;
#define DEBUG
#ifdef DEBUG
	#define debug printf
#else
	#define debug(...)
#endif
const int dx[] = {-2,-1,-2,1,2,2,1,-1};
const int dy[] = {-1,2,1,2,1,-1,-2,-2};
int n,m;
const int maxn = 120005;
int k;
int dp[50][30][50][30];
const int inf = 1e9;
struct K{
	int x;
	int y;
	int scan()
	{
		char a;
		if(!(cin>>a>>x))
		{
			k -= 2;
			return 0;
		}
		cin.get();
		y = a - 'A' + 1;
		return 1;
	}
	void print()
	{
		printf("x = %d,y = %d\n",x,y);
	}
}Knight[maxn],King;
struct node{
	int x,y,dis;
}q[maxn];
bool vis[50][30];
int head,tail;
int ok(int x,int y)
{
	return x >= 1 && x <= n && y >= 1 && y <= m && !vis[x][y];
}
void bfs(int x,int y)
{
	head = 1;
	tail = 2;
	q[head].x = x;
	q[head].y = y;
	q[head].dis = 0;
	dp[x][y][x][y] = 0;
	memset(vis,0x00,sizeof(vis));
	vis[x][y] = 1;
	while(head < tail)
	{
		if(tail == n * m + 1)
		{
			break;
		}
		for(int i = 0;i <= 7; ++i)
		{
			int nx = q[head].x + dx[i];
			int ny = q[head].y + dy[i];
			if(ok(nx,ny))
			{
				vis[nx][ny] = 1;
				q[tail].x = nx;
				q[tail].y = ny;
				q[tail].dis = q[head].dis + 1;
				dp[x][y][nx][ny] = dp[nx][ny][x][y] = q[tail++].dis;
			}
		}
		++head;
	}
}
void build_dp()
{
	memset(dp,1,sizeof(dp));
	for(int i = 1;i <= n; ++i)
	{
		for(int j = 1;j <= m; ++j)
		{
			bfs(i,j);
		}
	}
}
int carry()
{
	int ans = inf;
	for(int mx = 1;mx <= n; ++mx)//meet x,y
	{
		for(int my = 1;my <= m; ++my)
		{
			int cur = inf;
			int dis = 0;
			bool flag = 0;
			for(int s = 1;s <= k; ++s)
			{
				dis += dp[Knight[s].x][Knight[s].y][mx][my];
				if(dp[Knight[s].x][Knight[s].y][mx][my] >= dp[0][0][0][0])
				{
					flag = 1;
					break;
				}
			}
			if(flag)
			{
				continue;
			}
			for(int s = 1;s <= k; ++s)
			{
				int dis2 = inf;
				for(int i = King.x - 4;i <= King.x + 4; ++i)
				{
					if(i >= 1 && i <= n)
					{
						for(int j = King.y - 4;j <= King.y + 4; ++j)
						{
							if(j >= 1 && j <= m)
							{
								dis2 = min(dis2,max(abs(i - King.x),abs(j - King.y)) + dp[Knight[s].x][Knight[s].y][i][j] + dp[i][j][mx][my]);
							}
						}
					}
				}
				cur = min(cur,dis - dp[Knight[s].x][Knight[s].y][mx][my] + dis2);
			}
			ans = min(ans,cur);
		}
	}
	return ans;
}
int main()
{
	freopen("camelot.in","r",stdin);
	freopen("camelot.out","w",stdout);
	scanf("%d%d",&n,&m);
	getchar();
	char c;
	int x,y;
	int first = 0;
	while(cin>>c)
	{
		y = c - 'A' + 1;
		scanf("%d",&x);
		if(first == 0)
		{
			King.x = x;
			King.y = y;
			first = 1;
		}
		else
		{
			Knight[++k].x = x;
			Knight[k].y = y;
		}
	}
	if(k == 0)
	{
		printf("0\n");
	}
	else
	{
		build_dp();
		printf("%d\n",carry());
	}
	return 0;
}