/*
ID: zjd32151
TASK: inflate
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
const int maxn = 10005;
int value[maxn],t[maxn],dp[maxn];
int main(int argc, char const *argv[])
{
	freopen("inflate.in","r",stdin);
	freopen("inflate.out","w",stdout);
	int m,n;
	cin>>m>>n;
	for(int i = 1;i <= n; ++i)
	{
		scanf("%d%d",&value[i],&t[i]);
	}
	for(int i = 1;i <= n; ++i)
	{
		for(int j = t[i];j <= m; ++j)
		{
			dp[j] = max(dp[j],dp[j - t[i]] + value[i]);
		}
	}
	printf("%d\n",dp[m]);
	return 0;
}