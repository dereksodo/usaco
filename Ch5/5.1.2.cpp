/*
ID: zjd32151
TASK: starry
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
struct star{
	int cnt;
	int x[205],y[205];
	int type;
	double dis;
}s[505];
int a[505][505],vis[505][505];
int s_cnt,type_cnt;
int m,n;
const double eps = 1e-5;
void dfs(int x,int y)
{
	int p = ++s[s_cnt].cnt;
	s[s_cnt].x[p] = x;
	s[s_cnt].y[p] = y;
	vis[x][y] = s_cnt;
	debug("vis[%d][%d] = %c\n",x,y,s_cnt + 'a' - 1);
	for(int i = -1;i <= 1; ++i)
	{
		for(int j = -1;j <= 1; ++j)
		{
			if(i == 0 && j == 0)
			{
				continue;
			}
			int nx = x + i;
			int ny = y + j;
			if(nx >= 1 && nx <= n && ny >= 1 && ny <= m)
			{
				if(a[nx][ny] == 1 && vis[nx][ny] == 0)
				{
					dfs(nx,ny);
				}
			}
		}
	}
}
double find_dis(int x1,int y1,int x2,int y2)
{
	return sqrt((x1 + 0.0 - x2) * (x1 + 0.0 - x2) + (y1 + 0.0 - y2) * (y1 + 0.0 - y2));
}
int check()
{
	s[s_cnt].dis = 0;
	for(int i = 1;i <= s[s_cnt].cnt; ++i)
	{
		for(int j = 1;j <= s[s_cnt].cnt; ++j)
		{
			s[s_cnt].dis += find_dis(s[s_cnt].x[i],s[s_cnt].y[i],s[s_cnt].x[j],s[s_cnt].y[j]);
		}
	}
	for(int i = 1;i < s_cnt; ++i)
	{
		debug("s[%c].dis - s[%c].dis = %lf\n",s_cnt + 'a' - 1,s[s_cnt].dis,
			i + 'a' - 1,s[i].dis);
		if(fabs(s[s_cnt].dis - s[i].dis) < eps)
		{
			return s[i].type;
		}
	}
	return 0;
}
int main(int argc, char const *argv[])
{
	freopen("starry.in","r",stdin);
	freopen("starry.out","w",stdout);
	cin>>m>>n;
	for(int i = 1;i <= n; ++i)
	{
		for(int j = 1;j <= m; ++j)
		{
			int x;
			scanf("%1d",&x);
			a[i][j] = x;
		}
	}
	memset(vis,0x00,sizeof(vis));
	for(int i = 1;i <= n; ++i)
	{
		for(int j = 1;j <= m; ++j)
		{
			if(a[i][j] && vis[i][j] == 0)
			{
				s_cnt++;
				dfs(i,j);
				int t = check();
				if(t == 0)
				{
					s[s_cnt].type = ++type_cnt;
				}
				else
				{
					s[s_cnt].type = t;
				}
				debug("s[%c].type = %d\n",s_cnt + 'a' - 1,s[s_cnt].type);
				debug("s[%c].dis = %lf\n",s_cnt + 'a' - 1,s[s_cnt].dis);
			}
		}
	}
	for(int i = 1;i <= n; ++i)
	{
		for(int j = 1;j <= m; ++j)
		{
			if(a[i][j])
			{
				printf("%c",s[vis[i][j]].type + 'a' - 1);
			}
			else
			{
				printf("0");
			}
		}
		printf("\n");
	}
	return 0;
}