/*
ID: zjd32151
TASK: buylow
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
typedef long double ll;
// #define DEBUG
#ifdef DEBUG
	#define debug printf
#else
	#define debug(...)
#endif
const int maxn = 5005;
ll a[maxn],ans,ret,dp[maxn],cnt[maxn];
int main(int argc, char const *argv[])
{
	freopen("buylow.in","r",stdin);
	freopen("buylow.out","w",stdout);
	ll n;
	cin>>n;
	for(int i = 1;i <= n; ++i)
	{
		scanf("%LF",&a[i]);
		dp[i] = 1;
		cnt[i] = 1;
		for(int j = 1;j < i; ++j)
		{
			if(a[j] > a[i])
			{
				if(dp[j] + 1 > dp[i])
				{
					dp[i] = dp[j] + 1;
					cnt[i] = cnt[j];
				}
				else if(dp[j] + 1 == dp[i])
				{
					cnt[i] += cnt[j];
				}
			}
		}
		for(int j = 1;j < i; ++j)
		{
			if(dp[i] == dp[j] && a[i] == a[j])
			{
				cnt[j] = 0;
			}
		}
		ans = max(ans,dp[i]);
		debug("dp[%LF] = %LF,cnt[%LF] = %LF\n",i,dp[i],i,cnt[i]);
	}
	for(int i = 1;i <= n; ++i)
	{
		if(dp[i] == ans)
		{
			ret += cnt[i];
		}
	}
	printf("%.0LF %.0LF\n",ans,ret);
	return 0;
}