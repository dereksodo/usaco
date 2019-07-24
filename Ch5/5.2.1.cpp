/*
ID: zjd32151
TASK: snail
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
int n,m,ans;
int mp[150][150];
int vis[150][150];
const int dx[] = {0,0,1,-1};
const int dy[] = {1,-1,0,0};
int ok(int x,int y,int lx,int ly)
{
	return x >= 0 && x < n && y >= 0 && y < n && !(x == lx && y == ly);
}
void dfs(int x,int y,int lx,int ly,int dir,int cnt)
{
	int nx = x + dx[dir];
	int ny = y + dy[dir];
	debug("(%d,%d,%d,%d,%d,%d)->",x,y,lx,ly,dir,cnt);
	ans = max(ans,cnt);
	if(ok(nx,ny,lx,ly))
	{
		if(vis[nx][ny])
		{
			debug("\n");
			return;
		}
		if(mp[nx][ny])
		{
			for(int ndir = 4 - ((dir + 1) / 3) * 2 - 2;ndir <= 4 - ((dir + 1) / 3) * 2 - 1;++ndir)
			{
				nx = x + dx[ndir];
				ny = y + dy[ndir];
				if(x == 2 && y == 0)
				{
					debug("***");
				}
				debug("nx = %d,ny = %d\n",nx,ny);
				if(ok(nx,ny,lx,ly) && !vis[nx][ny] && !mp[nx][ny])
				{
					vis[x][y] = 1;
					vis[nx][ny] = 1;
					dfs(nx,ny,x,y,ndir,cnt + 1);
					vis[nx][ny] = 0;
					vis[x][y] = 0;
				}
			}
		}
		else
		{
			vis[x][y] = 1;
			vis[nx][ny] = 1;
			dfs(nx,ny,x,y,dir,cnt + 1);
			vis[nx][ny] = 0;
			vis[x][y] = 0;
		}
	}
	else
	{
		for(int ndir = 4 - ((dir + 1) / 3) * 2 - 2;ndir <= 4 - ((dir + 1) / 3) * 2 - 1;++ndir)
		{
			nx = x + dx[ndir];
			ny = y + dy[ndir];
			if(x == 2 && y == 0)
			{
				debug("***");
			}
			debug("nx = %d,ny = %d\n",nx,ny);
			if(ok(nx,ny,lx,ly) && !vis[nx][ny] && !mp[nx][ny])
			{
				vis[x][y] = 1;
				vis[nx][ny] = 1;
				dfs(nx,ny,x,y,ndir,cnt + 1);
				vis[nx][ny] = 0;
				vis[x][y] = 0;
			}
		}
	}
}
int main(int argc, char const *argv[])
{
	freopen("snail.in","r",stdin);
	freopen("snail.out","w",stdout);
	cin>>n>>m;
	for(int i = 0;i < m; ++i)
	{
		string s;
		cin>>s;
		mp[stoi(s.substr(1)) - 1][s[0] - 'A'] = 1;
	}
	vis[0][0] = 1;
	dfs(0,0,-1,-1,0,1);
	memset(vis,0x00,sizeof(vis));
	vis[0][0] = 1;
	dfs(0,0,-1,-1,2,1);
	debug("\n");
	cout<<ans<<endl;
	return 0;
}