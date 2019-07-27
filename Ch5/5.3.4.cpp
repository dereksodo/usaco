/*
ID: zjd32151
TASK: bigbrn
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
using namespace std;
const int maxn = 1005;
int a[maxn][maxn],dp[maxn][maxn];
int main()
{
	freopen("bigbrn.in","r",stdin);
	freopen("bigbrn.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n; ++i)
	{
		for(int j = 1;j <= n; ++j)
		{
			a[i][j] = 1;
		}
	}
	for(int i = 1;i <= m; ++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		a[x][y] = 0;
	}
	int ans = 0;
	for(int i = 1;i <= n; ++i)
	{
		for(int j = 1;j <= n; ++j)
		{
			if(a[i][j])
			{
				dp[i][j] = min(dp[i][j - 1],min(dp[i - 1][j],dp[i - 1][j - 1])) + 1;
				ans = max(ans,dp[i][j]);
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}