/*
ID: zjd32151
TASK: shopping
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
const int maxs = 105;
struct coupon{
	int n;
	vector< pair<int,int> > v;
	int cnt[maxs];
	int value;
	void scan()
	{
		v.clear();
		cin>>n;
		for(int i = 0;i < n; ++i)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			v.push_back(make_pair(x,y));
		}
		cin>>value;
	}
}cou[maxs];
int need[10],pre[10];
int dp[10][10][10][10][10];
map<int,int> mp;
int cnt = 0;
const int inf = 1e9;
int main(int argc, char const *argv[])
{
	freopen("shopping.in","r",stdin);
	freopen("shopping.out","w",stdout);
	int s;
	cin>>s;
	for(int i = 1;i <= s; ++i)
	{
		cou[i].scan();
	}
	int b;
	cin>>b;
	for(int i = 1;i <= b; ++i)
	{
		int x;
		scanf("%d",&x);
		if(!mp[x])
		{
			mp[x] = ++cnt;
		}
		cin>>need[mp[x]]>>pre[mp[x]];
	}
	memset(dp,inf,sizeof(dp));
	for(int i = 0;i <= need[1]; ++i)
	{
		for(int j = 0;j <= need[2]; ++j)
		{
			for(int c = 0;c <= need[3]; ++c)
			{
				for(int k = 0;k <= need[4]; ++k)
				{
					for(int o = 0;o <= need[5]; ++o)
					{
						dp[i][j][c][k][o] = pre[1] * i + pre[2] * j + pre[3] * c + pre[4] * k + pre[5] * o;
					}
				}
			}
		}
	}
	for(int i = 1;i <= s; ++i)
	{
		for(int j = 0;j < cou[i].v.size(); ++j)
		{
			cou[i].cnt[mp[cou[i].v[j].first]] = cou[i].v[j].second;
		}
	}
	for(int i = 1;i <= s; ++i)
	{
		for(int i1 = cou[i].cnt[1];i1 <= need[1]; ++i1)
		{
			for(int i2 = cou[i].cnt[2];i2 <= need[2]; ++i2)
			{
				for(int i3 = cou[i].cnt[3];i3 <= need[3]; ++i3)
				{
					for(int i4 = cou[i].cnt[4];i4 <= need[4]; ++i4)
					{
						for(int i5 = cou[i].cnt[5];i5 <= need[5]; ++i5)
						{
							dp[i1][i2][i3][i4][i5] = min(dp[i1][i2][i3][i4][i5],dp[i1 - cou[i].cnt[1]][i2 - cou[i].cnt[2]][i3 - cou[i].cnt[3]][i4 - cou[i].cnt[4]][i5 - cou[i].cnt[5]] + cou[i].value);
						}
					}
				}
			}
		}
	}
	printf("%d\n",dp[need[1]][need[2]][need[3]][need[4]][need[5]]);
	return 0;
}