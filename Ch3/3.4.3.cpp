/*
ID: zjd32151
TASK: rockers
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
const int maxn = 25;
int a[maxn];
int dp[maxn][maxn];
int main(int argc, char const *argv[])
{
	freopen("rockers.in","r",stdin);
	freopen("rockers.out","w",stdout);
	int n,t,m;
	cin>>n>>t>>m;
	for(int i = 1;i <= n; ++i)
	{
		scanf("%d",&a[i]);
	}
	memset(dp[0],0x00,sizeof(dp[0]));
	//dp[i][j]:i -> have used i compact disks
	//		   j -> the i-th compact disk have used up for j minutes
	//		   dp[i][j] -> the maximum songs the be included
	for(int k = 1;k <= n; ++k)
	{
		for(int i = m;i >= 1; --i)
		{
			for(int j = t;j >= a[k]; --j)
			{
				dp[i][j] = max(dp[i][j],max(dp[i - 1][t] + 1,dp[i][j - a[k]] + 1));
			}
		}
	}
	cout<<dp[m][t]<<endl;
	return 0;
}