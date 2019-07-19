/*
ID: zjd32151
TASK: runround
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
#define DEBUG
#ifdef DEBUG
	#define debug printf
#else
	#define debug(...)
#endif
int check1(int n)
{
	int cnt[10] = {0};
	while(n)
	{
		cnt[n % 10]++;
		n /= 10;
	}
	if(cnt[0] != 0)
	{
		return 0;
	}
	for(int i = 0;i <= 9; ++i)
	{
		if(cnt[i] > 1)
		{
			return 0;
		}
	}
	return 1;
}
bool ok(int i)
{
	if(check1(i))
	{
		vector<int> p;
		p.clear();
		int i2 = i;
		while(i2)
		{
			p.push_back(i2 % 10);
			i2 /= 10;
		}
		reverse(p.begin(),p.end());
		int vis[10] = {0};
		int pos = 0;
		for(int j = 0;j <= p.size(); ++j)
		{
			vis[pos]++;
			pos = (pos + p[pos]) % int(p.size());
		}
		int flag = 1;
		for(int j = 1;j < p.size(); ++j)
		{
			if(vis[j] != 1)
			{
				flag = 0;
				break;
			}
		}
		if(vis[0] != 2)
		{
			flag = 0;
		}
		if(flag)
		{
			printf("%d\n",i);
			exit(0);
		}
	}
}
int main(int argc, char const *argv[])
{
	freopen("runround.in","r",stdin);
	freopen("runround.out","w",stdout);
	int n;
	cin>>n;
	while(1)
	{
		++n;
		ok(n);
	}
	return 0;
}