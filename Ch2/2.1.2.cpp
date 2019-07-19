/*
ID: zjd32151
TASK: frac1
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
int gcd(int a,int b)
{
	return b == 0 ? a : (gcd(b,a % b));
}
int cmp(pair<int,int> a,pair<int,int> b)
{
	return (a.first * b.second) < (a.second * b.first);
}
int main(int argc, char const *argv[])
{
	freopen("frac1.in","r",stdin);
	freopen("frac1.out","w",stdout);
	int n;
	cin>>n;
	vector< pair<int,int> > v;
	for(int b = 1;b <= n; ++b)
	{
		for(int a = 0;a <= b; ++a)
		{
			if(gcd(a,b) == 1)
			{
				v.push_back({a,b});
			}
		}
	}
	sort(v.begin(),v.end(),cmp);
	for(int i = 0;i < v.size(); ++i)
	{
		printf("%d/%d\n",v[i].first,v[i].second);
	}
	return 0;
}