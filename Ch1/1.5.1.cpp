/*
ID: zjd32151
TASK: ariprog
LANG: C++
*/
//map浪费太多时间
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
int n,m;
int mp[125005];
int p[625005];
int cnt;
void pre()
{
	for(int i = 0;i <= m; ++i)
	{
		for(int j = 0;j <= m; ++j)
		{
			if(mp[i * i + j * j] == 0)
			{
				p[cnt++] = i * i + j * j;
			}
			mp[i * i + j * j] = 1;
		}
	}
}
int main(int argc, char const *argv[])
{
	freopen("ariprog.in","r",stdin);
	freopen("ariprog.out","w",stdout);
	cin>>n>>m;
	pre();
	vector< pair<int,int> > ans;
	ans.clear();
	sort(p,p + cnt);
	for(int i = 0;i < cnt; ++i)
	{
		for(int k = i + 1;k < cnt; ++k)
		{
			int first = p[i];
			int second = p[k];
			int d = second - first;
			int last = first + d * (n - 1);
			if(last > p[cnt - 1])
			{
				break;
			}
			bool flag = 1;
			for(int j = second + d;j <= last; j += d)
			{
				if(!mp[j])
				{
					flag = 0;
					break;
				}
			}
			if(flag)
			{
				ans.push_back(make_pair(d,first));
			}
		}
	}
	if(ans.size() == 0)
	{
		printf("NONE\n");
		return 0;
	}
	sort(ans.begin(),ans.end());
	for(int i = 0;i < ans.size(); ++i)
	{
		printf("%d %d\n",ans[i].second,ans[i].first);
	}
	return 0;
}