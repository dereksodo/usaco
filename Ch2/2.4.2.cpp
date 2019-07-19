/*
ID: zjd32151
TASK: maze1
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

int n,m;
const int maxn = 205;
string mp[maxn];
int vis[maxn][maxn];
int dp[maxn][maxn];

struct ii{
    int x,y,dis;
    void print()
    {
    	debug("x = %d,y = %d,dis = %d\n",x,y,dis);
    }
};
ii D1,D2;

const int dx[] = {0,0,2,-2};
const int dy[] = {2,-2,0,0};

const int dbeginx[] = {0,0,1,-1};
const int dbeginy[] = {1,-1,0,0};

ii make(int a,int b,int c)
{
    ii ret;
    ret.x = a;
    ret.y = b;
    ret.dis = c;
    return ret;
}

int ok(int x,int y)
{
    return x >= 0 && x < n && y >= 0 && y < m && mp[x][y] == ' ' && !vis[x][y];
}

void bfs(ii begin)
{
    memset(vis,0x00,sizeof(vis));
    queue<ii> q;
    vis[begin.x][begin.y] = 1;
    for(int i = 0;i < 4; ++i)
    {
        int nx = begin.x + dbeginx[i];
        int ny = begin.y + dbeginy[i];
        if(ok(nx,ny))
        {
            vis[nx][ny] = 1;
            q.push(make(nx,ny,1));
        }
    }

    while(!q.empty())
    {
        ii cur = q.front();
        q.pop();

        if(dp[cur.x][cur.y] <= cur.dis)
        {
            continue;
        }

        vis[cur.x][cur.y] = 1;
        dp[cur.x][cur.y] = cur.dis;
        debug("dp[%d][%d] = %d\n",cur.x,cur.y,dp[cur.x][cur.y]);

        for(int i = 0;i < 4; ++i)
        {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            int midx = (cur.x + nx) / 2;
            int midy = (cur.y + ny) / 2;

            debug("nx = %d,ny = %d,midx = %d,midy = %d\n",nx,ny,midx,midy);
            debug("%d %d\n",ok(nx,ny),ok(midx,midy));
            debug("%d %d\n",vis[nx][ny],vis[midx][midy]);

            if(ok(nx,ny) && ok(midx,midy))
            {
                q.push(make(nx,ny,cur.dis + 1));
            }
        }
    }
}
int main(int argc, char const *argv[])
{
    freopen("maze1.in","r",stdin);
    freopen("maze1.out","w",stdout);
    cin>>m>>n;

    m = 2 * m + 1;
    n = 2 * n + 1;
    getline(cin,mp[0]);

    D1.x = -1;
    D1.dis = 0;
    D2.dis = 0;

    for(int i = 0;i < n; ++i)
    {
        getline(cin,mp[i]);
        for(int j = 0;j < m; ++j)
        {
        	if(i == 0 || j == 0 || i == n - 1 || j == m - 1)
        	{
        		if(mp[i][j] == ' ')
        		{
        			if(D1.x == -1)
            		{
            			D1.x = i,D1.y = j;
            		}
            		else
            		{
            			D2.x = i,D2.y = j;
            		}
        		}
        	}
        	dp[i][j] = 1e9;
        }
    }

   	bfs(D1);
   	debug("**************************************************************\n");
   	bfs(D2);

   	int ans = 0;
   	for(int i = 1;i < n; i += 2)
   	{
   		for(int j = 1;j < m; j += 2)
   		{
   			if(mp[i][j] == ' ')
   			{
   				// debug("dp[%d][%d] = %d\n",i,j,dp[i][j]);
   				ans = max(ans,dp[i][j]);
   			}
   		}
   	}
   	cout<<ans<<endl;
    return 0;
}