/*
ID: zjd32151
TASK: kimbits
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
// #define DEBUG
#ifdef DEBUG
	#define debug printf
#else
	#define debug(...)
#endif
const int maxn = 50;
ll c[maxn][maxn];
ll dp[maxn][maxn];
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
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]);
        }
    }
    for(int i = 1;i < maxn; ++i)
    {
    	dp[i][0] = 1;
    	for(int j = 1;j < maxn; ++j)
    	{
    		dp[i][j] = dp[i][j - 1] + c[i][j];
    	}
    }
}
int main(int argc, char const *argv[])
{
	freopen("kimbits.in","r",stdin);
	freopen("kimbits.out","w",stdout);
	make();
	ll n,l,p;
	cin>>n>>l>>p;
	ll cnt = 0;
	for(int i = n;i >= 1; --i)
	{
		debug("dp[%lld][%lld] = %lld\n",i - 1,l - cnt,dp[i - 1][l - cnt]);
		if(p == 1 && dp[i - 1][l - cnt] == 0)
		{
			printf("0");
			continue;
		}
		if(dp[i - 1][l - cnt] >= p)
		{
			printf("0");
		}
		else
		{
			p -= dp[i - 1][l - cnt];
			printf("1");
			cnt++;
		}
		debug("\np = %lld\n",p);
	}
	printf("\n");
	return 0;
}