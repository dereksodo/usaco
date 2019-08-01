/*
ID: zjd32151
TASK: twofive
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
int dp[6][6][6][6][6];
char s[10000],t[10000];
int check(int cnt,int now)
{
	return (!s[now] || (s[now] == cnt + 'A'));
}
int dfs(int a,int b,int c,int d,int e,int cnt)
{
	if(cnt == 25)
	{
		return 1;
	}
	int ret = dp[a][b][c][d][e];
	if(ret)
	{
		return ret;
	}
	if(a < 5 && check(cnt,a))
	{
		ret += dfs(a + 1,b,c,d,e,cnt + 1);
	}
	if(b < a && check(cnt,b + 5))
	{
		ret += dfs(a,b + 1,c,d,e,cnt + 1);
	}
	if(c < b && check(cnt,c + 10))
	{
		ret += dfs(a,b,c + 1,d,e,cnt + 1);
	}
	if(d < c && check(cnt,d + 15))
	{
		ret += dfs(a,b,c,d + 1,e,cnt + 1);
	}
	if(e < d && check(cnt,e + 20))
	{
		ret += dfs(a,b,c,d,e + 1,cnt + 1);
	}
	return dp[a][b][c][d][e] = ret;
}
int main(int argc, char const *argv[])
{
	// freopen("twofive.in","r",stdin);
	// freopen("twofive.out","w",stdout);
	char c;
	cin>>c;
	if(c == 'N')
	{
		int num;
		cin>>num;
		for(int i = 0;i < 25; ++i)
		{
			for(s[i] = 'A';; ++s[i])
			{
				memset(dp,0,sizeof(dp));
				int ret = dfs(0,0,0,0,0,0);
				if(ret >= num)
				{
					break;
				}
				num -= ret;
			}
		}
		printf("%s\n",s);
	}
	else
	{
		scanf("%s",t);
		int ret = 0;
		for(int i = 0;i < 25; ++i)
		{
			for(s[i] = 'A';s[i] < t[i]; ++s[i])
			{
				memset(dp,0x00,sizeof(dp));
				ret += dfs(0,0,0,0,0,0);
			}
		}
		printf("%d\n",ret + 1);
	}
	return 0;
}