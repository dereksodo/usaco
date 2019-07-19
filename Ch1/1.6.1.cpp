/*
ID: zjd32151
TASK: numtri
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
const int maxn = 1005;
int a[maxn][maxn];
int dp[maxn][maxn];
const int inf = 1e9 + 5; 
int main()
{
	freopen("numtri.in","r",stdin);
	freopen("numtri.out","w",stdout);
    int n;
    cin>>n;
    memset(a,inf,sizeof(a));
    for(int i = 1;i <= n; ++i)
    {
        for(int j = 1;j <= i; ++j)
        {
            scanf("%d",&a[i][j]);
        }
    }
    memset(dp,-inf,sizeof(dp));
    for(int i = 1;i <= n; ++i)
    {
        for(int j = 1;j <= i; ++j)
        {
            if(i == 1 && j == 1)
            {
                dp[i][j] = a[i][j];
                continue;	
            } 
            dp[i][j] = max(dp[i - 1][j - 1],dp[i - 1][j]) + a[i][j];
        }
    }
    int ans = 0;
    for(int i = 1;i <= n; ++i)
    {
        ans = max(ans,dp[n][i]);
    }
    cout<<ans<<endl;
    return 0;
}