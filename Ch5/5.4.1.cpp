/*
ID: zjd32151
TASK: tour
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
const int maxn = 105;
map<string,int> mp;
int dp[maxn][maxn],G[maxn][maxn];
int main(int argc, char const *argv[])
{
	freopen("tour.in","r",stdin);
	freopen("tour.out","w",stdout);
	int n,m;
	cin>>n>>m;
	for(int i = 1;i <= n; ++i)
	{
		string s;
		cin>>s;
		mp[s] = i;
	}
	memset(G,0x00,sizeof(G));
	for(int i = 0;i < m; ++i)
	{
		string s,t;
		cin>>s>>t;
		G[mp[s]][mp[t]] = G[mp[t]][mp[s]] = 1;
	}
	dp[1][1] = 1;
	for(int i = 1;i < n; ++i)
	{
		for(int j = i + 1;j <= n; ++j)
		{
			for(int k = 1;k < j; ++k)
			{
				if(G[j][k] && dp[i][k])
				{
					dp[i][j] = dp[j][i] = max(dp[i][j],dp[i][k] + 1);
				}
			}
		}
	}
	int ans = 1;
	for(int i = 1;i <= n; ++i)
	{
		if(G[n][i])
		{
			ans = max(ans,dp[n][i]);
		}
	}
	cout<<ans<<endl;
	return 0;
}