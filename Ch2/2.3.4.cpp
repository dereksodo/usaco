/*
ID: zjd32151
TASK: money
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
const ll maxn = 1e5 + 5;
ll a[maxn],dp[maxn];
int main(int argc, char const *argv[])
{
    freopen("money.in","r",stdin);
    freopen("money.out","w",stdout);
    ll n,k;
    cin>>n>>k;
    for(int i = 0;i < n; ++i)
    {
        scanf("%lld",&a[i]);
    }
    dp[0] = 1;
    for(int i = 0;i < n; ++i)
    {
        for(int j = a[i];j < 10005; ++j)
        {
            dp[j] += dp[j - a[i]];      
        } 
    }
    cout<<dp[k]<<endl;
    return 0;
}