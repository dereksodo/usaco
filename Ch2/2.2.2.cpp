/*
ID: zjd32151
TASK: subset
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
const int maxn = 500;
int dp[maxn][maxn];
int main(int argc, char const *argv[])
{
	freopen("subset.in","r",stdin);
	freopen("subset.out","w",stdout);
	int n;
	cin>>n;
	int sum = (n + 1) * n / 2;
	if(sum & 1)
	{
		printf("0\n");
		return 0;
	}
	dp[1][1] = 1;
	dp[1][0] = 1;
	for(int i = 2;i <= n; ++i)
	{
		for(int j = 0;j <= sum; ++j)
		{
			if(j > i)
			{
				dp[i][j] = dp[i - 1][j] + dp[i - 1][j - i];
			}
			else
			{
				dp[i][j] = dp[i - 1][j];
			}
		}
	}
	printf("%d\n",dp[n][sum / 2]);
	return 0;
}