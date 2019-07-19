/*
ID: zjd32151
TASK: game1
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
const int inf = 1e9;
int a[maxn];
int dp[maxn][maxn];
int sum[maxn];
int main(int argc, char const *argv[])
{
	freopen("game1.in","r",stdin);
	freopen("game1.out","w",stdout);
	int n;
	cin>>n;
	for(int i = 1;i <= n; ++i)
	{
		cin>>a[i];
		sum[i] = sum[i - 1] + a[i];
	}
	for(int i = 1;i <= n; ++i)
	{
		dp[i][i] = a[i];
	}
	for(int i = n;i >= 1; --i)
	{
		for(int j = 1;j <= n; ++j)
		{
			dp[i][j] = max(max((sum[j] - sum[i - 1] - dp[i][j - 1]),(sum[j] - sum[i - 1] - dp[i + 1][j])),dp[i][j]);
			// printf("%d %d %d\n",i,j,dp[i][j]);
		}
	}
	printf("%d %d\n",dp[1][n],sum[n] - dp[1][n]);
	return 0;
}