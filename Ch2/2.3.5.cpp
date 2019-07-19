/*
ID: zjd32151
TASK: concom
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
int a[maxn][maxn];
set<int> control[maxn];
int main(int argc, char const *argv[])
{
    freopen("concom.in","r",stdin);
    freopen("concom.out","w",stdout);
    int n;
    cin>>n;
    for(int i = 1;i <= 100; ++i)
    {
        control[i].insert(i);
    }
    for(int i = 0;i < n; ++i)
    {
        int x,y;
        cin>>x>>y>>a[x][y];
        if(a[x][y] > 50)
        {
            control[x].insert(y);
        }
    }
    for(int T = 1;T <= 50; ++T)//每次从头检查
    {
        for(int i = 1;i <= 100; ++i)
        {
            for(int j = 1;j <= 100; ++j)
            {
                if(i == j)
                {
                    continue;
                }
                int now = 0;
                for(set<int>::iterator iter = control[i].begin();iter != control[i].end(); ++iter)
                {
                    now += a[*iter][j];
                }
                if(now > 50)
                {
                    control[i].insert(j);
                }
            }
        }
    }
    for(int i = 1;i <= 100; ++i)
    {
        for(set<int>::iterator iter = control[i].begin();iter != control[i].end(); ++iter)
        {
            if(*iter != i)
            {
                printf("%d %d\n",i,*iter);
            }
        }
    }
    return 0;
}