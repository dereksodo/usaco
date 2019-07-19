/*
ID: zjd32151
TASK: hamming
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
vector<int> v;
int check(int a,int b,int d)
{
	int res = 0;
	while(a != 0 || b != 0)
	{
		int nowa = a & 1;
		int nowb = b & 1;
		res += (nowa != nowb);
		a >>= 1;
		b >>= 1;
	}
	return res >= d;
}
int ok(int n,int d)
{
	for(int i = 0;i < v.size(); ++i)
	{
		if(!check(v[i],n,d))
		{
			return 0;
		}
	}
	return 1;
}
int main(int argc, char const *argv[])
{
	freopen("hamming.in","r",stdin);
	freopen("hamming.out","w",stdout);
	int n,b,d;
	cin>>n>>b>>d;
	int last = 0;
	while(n--)
	{
		int i = last;
		for(;i <= (1 << b); ++i)
		{
			if(v.empty() || ok(i,d))
			{
				v.push_back(i);
				break;
			}
		}
		last = i + 1;
	}
	for(int i = 0;i < v.size(); i += 10)
	{
		printf("%d",v[i]);
		for(int j = i + 1;j < min((int)v.size(),i + 10); ++j)
		{
			printf(" %d",v[j]);
		}
		printf("\n");
	}
	return 0;
}