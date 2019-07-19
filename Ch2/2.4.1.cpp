/*
ID: zjd32151
TASK: ttwo
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
const int maxn = 15;
string mp[maxn];
const int n = 10;
const int dx[] = {-1,0,1,0};//NESW
const int dy[] = {0,1,0,-1};
void nxt(int &x,int &y,int &pos)
{
    int nx = x + dx[pos];
    int ny = y + dy[pos];
    if(mp[nx][ny] == '*')
    {
        pos++;
        if(pos == 4)
        {
            pos = 0;
        }
    }
    else
    {
        x = nx;
        y = ny;
    }
}
int main(int argc, char const *argv[])
{
    freopen("ttwo.in","r",stdin);
    freopen("ttwo.out","w",stdout);
    int Cowx,Cowy,Farx,Fary;
    int Cowpos,Farpos;
    mp[0] = mp[n + 1] = "**************";
    for(int i = 1;i <= n; ++i)
    {
        cin>>mp[i];
        mp[i] = "*" + mp[i] + "*";
        for(int j = 1;j <= n; ++j)
        {
            if(mp[i][j] == 'C')
            {
                Cowx = i;
                Cowy = j;
            }
            if(mp[i][j] == 'F')
            {
                Farx = i;
                Fary = j;
            }
        }
    }
    Cowpos = Farpos = 0;
    int step = 0;
    while(step < 10000)
    {
        if(Cowx == Farx && Cowy == Fary)
        {
            printf("%d\n",step);
            return 0;
        }
        step++;
        nxt(Cowx,Cowy,Cowpos);
        nxt(Farx,Fary,Farpos);
        // for(int i = 1;i <= n; ++i)
        // {
        // 	for(int j = 1;j <= n; ++j)
        // 	{
        // 		if(mp[i][j] == '*')
        // 		{
        // 			printf("*");
        // 		}
        // 		else if(i == Cowx && j == Cowy)
        // 		{
        // 			printf("C");
        // 		}
        // 		else if(i == Farx && j == Fary)
        // 		{
        // 			printf("F");
        // 		}
        // 		else
        // 		{
        // 			printf(".");
        // 		}
        // 	}
        // 	printf("\n\n");
        // }
        // for(int i = 0;i < 100000000; ++i);
    }
    printf("0\n");
    return 0;
}