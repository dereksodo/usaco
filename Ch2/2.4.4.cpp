/*
ID: zjd32151
TASK: comehome
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
const int maxn = 60;
const int inf = 1e9 + 7;
int G[maxn + 5][maxn + 5];
int zh(char c)
{
    if(c >= 'A' && c <= 'Z')
    {
        return c - 'A' + 1;
    }
    return c - 'a' + 27;
}
char rzh(int c)
{
    if(c >= 1 && c <= 26)
    {
        return char(c - 1 + 'A');
    }
    return char(c - 27 + 'a');
}
int main(int argc, char const *argv[])
{
    freopen("comehome.in","r",stdin);
    freopen("comehome.out","w",stdout);
    ios::sync_with_stdio(0);
    int n;
    cin>>n;

    for(int i = 0;i < maxn; ++i)
    {
        for(int j = 0;j < maxn; ++j)
        {
            G[i][j] = inf;
        }
    }

    for(int i = 0;i < n; ++i)
    {
        char a,b;
        int x;
        cin>>a>>b>>x;
        G[zh(a)][zh(b)] = G[zh(b)][zh(a)] = min(G[zh(a)][zh(b)],x);
        G[zh(a)][zh(a)] = G[zh(b)][zh(b)] = 0;
    }
    
    // debug("G:\n");
    // for(int i = 0;i < maxn; ++i)
    // {
    // 	for(int j = 0;j < maxn; ++j)
    // 	{
    // 		if(G[i][j] == inf)
    // 		{
    // 			continue;
    // 		}
    // 		debug("G[%c][%c] = %d\n",rzh(i),rzh(j),G[i][j]);
    // 	}
    // }

    for(int k = 0;k < maxn; ++k)
    {
        for(int i = 0;i < maxn; ++i)
        {
            for(int j = 0;j < maxn; ++j)
            {
                G[i][j] = min(G[i][j],G[i][k] + G[k][j]);
            }
        }
    }

    // debug("G:\n");
    // for(int i = 0;i < maxn; ++i)
    // {
    // 	for(int j = 0;j < maxn; ++j)
    // 	{
    // 		if(G[i][j] == inf)
    // 		{
    // 			continue;
    // 		}
    // 		debug("G[%c][%c] = %d\n",rzh(i),rzh(j),G[i][j]);
    // 	}
    // }

    int ans = 1e9,pos = 0;
    for(int i = 0;i < maxn; ++i)
    {
        if(rzh(i) >= 'A' && rzh(i) < 'Z')
        {
            if(G[i][zh('Z')] < ans)
            {
                ans = G[i][zh('Z')];
                pos = i;
            }
        }
    }

    printf("%c %d\n",rzh(pos),ans);
    return 0;
}