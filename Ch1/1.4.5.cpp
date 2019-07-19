/*
ID: zjd32151
TASK: wormhole
LANG: C++
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
const int maxn = 15;
int n;
struct point{
	int x,y;
	void scan()
	{
		scanf("%d%d",&x,&y);
	}
};
point p[maxn];
int cmp(point a,point b)
{
	if(a.y != b.y)
	{
		return a.y < b.y;
	}
	return a.x < b.x;
}
int vis[maxn],vis2[maxn];
map<int,int> mp;
bool cycle(int k)
{
	memset(vis2,0x00,sizeof(vis2));
	while(1)
	{
		k = mp[k];
		vis2[k]++;
		if(vis2[k] == 3)//********
		{
			return 1;
		}
		if(k == n || p[k + 1].y != p[k].y)
		{
			return 0;
		}
		k++;
		vis2[k]++;
	}
}
int ans;
void dfs(int now)
{
	if(now == n + 1)
	{
		for(int i = 1;i <= n; ++i)
		{
			if(cycle(i))
			{
				// for(int j = 1;j <= n; ++j)
				// {
				// 	printf("(%d->%d)\n",j,mp[j]);
				// }
				// printf("beginning = %d\n",i);
				// printf("\n");
				ans++;
				break;
			}
		}
		return;
	}
	if(vis[now])
	{
		dfs(now + 1);
		return;
	}
	for(int i = now + 1;i <= n; ++i)
	{
		if(!vis[i])
		{
			mp[i] = now;
			mp[now] = i;
			vis[i] = 1;
			vis[now] = 1;
			dfs(now + 1);
			vis[i] = 0;
			vis[now] = 0;
			mp[i] = 0;
			mp[now] = 0;
		}
	}
}
int main(int argc,char const *argv[])
{
	freopen("wormhole.in","r",stdin);
	freopen("wormhole.out","w",stdout);
	cin>>n;
	for(int i = 1;i <= n; ++i)
	{
		p[i].scan();
	}
	sort(p + 1,p + n + 1,cmp);
	dfs(1);
	cout<<ans<<endl;
	return 0;
}