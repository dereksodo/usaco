/*
ID: zjd32151
TASK: spin
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
const int n = 5;
struct wheel{
	int speed;
	int cnt;
	vector< pair<int,int> > v;
}w[n];
int d[365];
int main(int argc, char const *argv[])
{
	freopen("spin.in","r",stdin);
	freopen("spin.out","w",stdout);
	for(int i = 0;i < n; ++i)
	{
		cin>>w[i].speed>>w[i].cnt;
		w[i].v.clear();
		for(int j = 0;j < w[i].cnt; ++j)
		{
			int x,y;
			cin>>x>>y;
			w[i].v.push_back(make_pair(x,y));
		}
	}
	for(int k = 0;k < 360; ++k)
	{
		for(int angle = 0;angle < 360; ++angle)
		{
			d[angle] = 0;
		}
		for(int i = 0;i < n; ++i)
		{
			for(int j = 0;j < w[i].cnt; ++j)
			{
				int end = w[i].v[j].first + w[i].v[j].second;
				if(w[i].v[j].first > end)
				{
					for(int h = w[i].v[j].first;h < 360; ++h)
					{
						d[(h + k * w[i].speed) % 360]++;
					}
					for(int h = 0;h <= end; ++h)
					{
						d[(h + k * w[i].speed) % 360]++;
					}
				}
				else
				{
					for(int h = w[i].v[j].first;h <= end; ++h)
					{
						d[(h + k * w[i].speed) % 360]++;
					}
				}
			}
		}
		for(int angle = 0;angle < 360; ++angle)
		{
			if(d[angle] == 5)
			{
				printf("%d\n",k);
				return 0;
			}
		}
	}
	printf("none\n");
	return 0;
}