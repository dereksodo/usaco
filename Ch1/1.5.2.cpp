/*
ID: zjd32151
TASK: milk3
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
int p[3];
set<int> ans;
int vis[25][25][25];
void dfs(int milk[])
{
	if(vis[milk[0]][milk[1]][milk[2]])
	{
		return;
	}
	vis[milk[0]][milk[1]][milk[2]] = 1;
	if(milk[0] == 0)
	{
		ans.insert(milk[2]);
	}
	for(int i = 0;i < 3; ++i)
	{
		for(int j = 0;j < 3; ++j)
		{
			if(i == j)
			{
				continue;
			}
			int sc = milk[i];
			int sd = milk[j];
			if(milk[i] >= p[j] - milk[j])
			{
				milk[i] -= (p[j] - milk[j]);
				milk[j] = p[j];
			}
			else
			{
				milk[j] += milk[i];
				milk[i] = 0;
			}
			dfs(milk);
			milk[i] = sc;
			milk[j] = sd;
		}
	}
}
int main(int argc, char const *argv[])
{
	freopen("milk3.in","r",stdin);
	freopen("milk3.out","w",stdout);
	cin>>p[0]>>p[1]>>p[2];
	int a[] = {0,0,p[2]};
	dfs(a);
	vector<int> v;
	for(set<int>::iterator iter = ans.begin();iter != ans.end(); ++iter)
	{
		v.push_back(*iter);
	}
	for(int i = 0;i < v.size() - 1; ++i)
	{
		printf("%d ",v[i]);
	}
	printf("%d\n",v.back());
	return 0;
}