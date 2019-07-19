/*
ID: zjd32151
TASK: nocows
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
const int mod = 9901;
const int maxn = 205;
int pre[maxn][maxn];
int c[maxn][maxn];
void make()
{
    for(int i = 1;i < maxn; ++i)
    {
        c[i][0] = 1;
        c[0][i] = 0;
    }
    c[0][0] = 1;
    for(int i = 1;i < maxn; ++i)
    {
        for(int j = 1;j < maxn; ++j)
        {
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
        }
    }
}
int main(int argc, char const *argv[])
{
    freopen("nocows.in","r",stdin);
    freopen("nocows.out","w",stdout);
    make();
    int n,h;
    cin>>n>>h;
    pre[1][1] = 1;
    for(int i = 1;i < h; ++i)//we have considered to level i
    {
        int dp[maxn][maxn] = {0};
        for(int j = 1;j <= n; ++j)//we have used j nodes
        {
            //k = 1
            for(int t = 1;t <= 1 && j + 2 * t <= n; ++t)
            {
                dp[j + 2 * t][2 * t] += (pre[j][1] * c[1][t]) % mod;
                dp[j + 2 * t][2 * t] %= mod;
            }
            for(int k = 2;k <= n; k += 2)//the number of nodes in level i
            {
                if(pre[j][k] == 0)
                {
                    continue;
                }
                for(int t = 1;t <= k && j + 2 * t <= n; ++t)//how many of them have children
                {
                    dp[j + 2 * t][2 * t] += (pre[j][k] * c[k][t]) % mod;
                    dp[j + 2 * t][2 * t] %= mod;
                }
            }
        }
        // printf("i = %d\n",i);
        // for(int j = 1;j <= n; ++j)
        // {
        // 	for(int k = 1;k <= n; ++k)
        // 	{
        // 		if(dp[j][k] != 0)
        // 		{
        // 			printf("dp[%d][%d] = %d\n",j,k,dp[j][k]);
        // 		}
        // 	}
        // }
        memcpy(pre,dp,sizeof(pre));
    }
    int ans = 0;
    for(int i = 2;i <= n; i += 2)
    {
        ans += pre[n][i];
        ans %= mod;
    }
    cout<<ans<<endl;
    return 0;
}