/*
ID: zjd32151
TASK: cowtour
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
const int maxn = 155;
pair<int,int> pos[maxn];
double dis[maxn][maxn],ans[maxn],maxi[maxn];
int n;
double calc(int i,int j)
{
    return sqrt((pos[i].first - pos[j].first) * (pos[i].first - pos[j].first) 
                + (pos[i].second - pos[j].second) * (pos[i].second - pos[j].second) + 0.0);
}
int main(int argc, char const *argv[])
{
    freopen("cowtour.in","r",stdin);
    freopen("cowtour.out","w",stdout);
    cin>>n;
    for(int i = 1;i <= n; ++i)
    {
        scanf("%d%d",&pos[i].first,&pos[i].second);
    }

    string s;
    getline(cin,s);

    for(int i = 1;i <= n; ++i)
    {
        getline(cin,s);
        for(int j = 0;j < s.size(); ++j)
        {
            if(s[j] == '1')
            {
                dis[i][j + 1] = calc(i,j + 1);
            }
            else if(i != (j + 1))
            {
                dis[i][j + 1] = 1e9;
            }
        }
    }

    for(int k = 1;k <= n; ++k)
    {
        for(int i = 1;i <= n; ++i)
        {
            for(int j = 1;j <= n; ++j)
            {
                dis[i][j] = min(dis[i][j],dis[i][k] + dis[k][j]);
            }
        }
    }

    debug("Shortest:\n");
    for(int i = 1;i <= n; ++i)
    {
        for(int j = 1;j <= n; ++j)
        {
            debug("%lf ",dis[i][j]);
        }
        debug("\n");
    }
    debug("\n");

    double pre = 0.0;
    for(int i = 1;i <= n; ++i)
    {
        for(int j = 1;j <= n; ++j)
        {
            if(dis[i][j] != 1e9)
            {
                maxi[i] = max(maxi[i],dis[i][j]);
                pre = max(pre,maxi[i]);
            }
        }
    }

    double now = 1e9;
    for(int i = 1;i <= n; ++i)
    {
        for(int j = 1;j <= n; ++j)
        {
            if(dis[i][j] == 1e9)
            {
                now = min(now,maxi[i] + calc(i,j) + maxi[j]);
            }
        }
    }
    printf("%.6lf\n",max(pre,now));
    return 0;
}