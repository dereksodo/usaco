/*
ID: zjd32151
TASK: castle
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
int n,m,now;
const int maxn = 55;
const int dx[] = {0,-1,0,1};
const int dy[] = {-1,0,1,0};
struct point{
	int wall[4];//west,north,east,south
};
point mp[maxn][maxn];
int vis[maxn][maxn],maxp,ansi,ansj,pos;
const string s = "WNES";
bool ok(int x,int y)
{
	return x >= 1 && x <= n && y >= 1 && y <= m && !vis[x][y];
}
void dfs(int x,int y)
{
	now++;
	vis[x][y] = 1;
	for(int i = 0;i < 4; ++i)
	{
		if(mp[x][y].wall[i] == 0)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(ok(nx,ny))
			{
				dfs(nx,ny);
			}
		}
	}
}
int getopp(int a)
{
	if(a == 0)
	{
		return 2;
	}
	if(a == 1)
	{
		return 3;
	}
	if(a == 2)
	{
		return 0;
	}
	return 1;
}
void ah(int i,int j,int k)
{
	// printf("i = %d,j = %d,k = %d\n",i,j,k);
	if(k == 1)
	{
		ansi = i;
		ansj = j;
		pos = k;
	}
	else if(k == 2)
	{
		ansi = i;
		ansj = j;
		pos = k;
	}
	else if(k == 3)
	{
		ansi = i + 1;
		ansj = j;
		pos = 1;
	}
	else
	{
		ansi = i;
		ansj = j - 1;
		pos = 2;
	}
}
vector< pair< pair<int,int>,int > > v;
void push(int i,int j)
{
	memset(vis,0x00,sizeof(vis));
	for(int k = 0;k < 4; ++k)
	{
		int ni = i + dx[k];
		int nj = j + dy[k];
		if(ok(ni,nj) && mp[i][j].wall[k] == 1)
		{
			mp[i][j].wall[k] = mp[ni][nj].wall[getopp(k)] == 0;
			now = 0;
			memset(vis,0x00,sizeof(vis));
			dfs(i,j);
			if(now == maxp)
			{
				v.push_back({{j,-i},k});
			}
			else if(now > maxp)
			{
				v.clear();
				maxp = now;
				v.push_back({{j,-i},k});
			}
			mp[i][j].wall[k] = mp[ni][nj].wall[getopp(k)] == 1;
		}
	}
}
int main(int argc, char const *argv[])
{
	freopen("castle.in","r",stdin);
	freopen("castle.out","w",stdout);
	cin>>n>>m;
	swap(n,m);
	for(int i = 1;i <= n; ++i)
	{
		for(int j = 1;j <= m; ++j)
		{
			int ws;
			scanf("%d",&ws);
			for(int k = 0;k < 4; ++k)
			{
				mp[i][j].wall[k] = (ws >> k) & 1;
				// printf("ws >> %d = %d\n",k,ws >> k);
				// printf("mp[%d][%d].wall[%d] = %d\n",i,j,k,mp[i][j].wall[k]);
			}
		}
	}
	int p = 0;
	for(int i = 1;i <= n; ++i)
	{
		for(int j = 1;j <= m; ++j)
		{
			if(!vis[i][j])
			{
				p++;
				now = 0;
				dfs(i,j);
				maxp = max(maxp,now);
			}
		}
	}
	printf("%d\n%d\n",p,maxp);
	maxp = 0;
	v.clear();
	for(int j = 1;j <= m; ++j)
	{
		for(int i = n;i >= 1; --i)
		{
			push(i,j);
		}
	}
	for(int i = 0;i < v.size(); ++i)
	{
		if(s[v[i].second] == 'W')
		{
			v[i].first.first--;
			v[i].second = 2;
		}
		else if(s[v[0].second] == 'S')
		{
			v[i].first.second++;
			v[i].second = 1;
		}
	}
	sort(v.begin(),v.end());
	printf("%d\n%d %d %c\n",maxp,-v[0].first.second,v[0].first.first,s[v[0].second]);
	return 0;
}