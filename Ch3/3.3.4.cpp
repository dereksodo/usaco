/*
ID: zjd32151
TASK: range
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
const int maxn = 255;
int a[maxn][maxn];
int sum[maxn][maxn];
int cnt[maxn][maxn];
int n;
int go(int index)
{
	int ret = 0;
	for(int i = 1;i + index <= n; ++i)
	{
		for(int j = 1;j + index <= n; ++j)
		{
			int nx = i + index;
			int ny = j + index;
			int sum = cnt[nx][ny] - cnt[nx][j - 1] - cnt[i - 1][ny] + cnt[i - 1][j - 1];
			debug("%d:%d %d %d\n",index,i,j,sum);
			if(sum == 0)
			{
				ret++;
			}
		}
	}
	return ret;
}
int main(int argc, char const *argv[])
{
	freopen("range.in","r",stdin);
	freopen("range.out","w",stdout);
	cin>>n;
	cin.get();
	for(int i = 1;i <= n; ++i)
	{
		string s;
		cin>>s;
		s = " " + s;
		for(int j = 1;j <= n; ++j)
		{
			a[i][j] = 1 - int(s[j] - '0');
			sum[i][j] = sum[i][j - 1] + a[i][j];
		}
	}
	for(int i = 1;i <= n; ++i)
	{
		for(int j = 1;j <= n; ++j)
		{
			cnt[i][j] = cnt[i - 1][j] + sum[i][j];
			debug("cnt[%d][%d] = %d\n",i,j,cnt[i][j]);
		}
	}
	for(int i = 1;i < n; ++i)
	{
		int ret = go(i);
		if(ret)
		{
			printf("%d %d\n",i + 1,ret);
		}
	}
	return 0;
}