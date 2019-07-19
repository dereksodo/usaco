/*
ID: zjd32151
TASK: lamps
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
int n,c;
vector<int> v1,v2,ans;
bool ok(vector<int> res)
{
	for(int i = 0;i < v1.size(); ++i)
	{
		if(!res[v1[i]])
		{
			return 0;
		}
	}
	for(int i = 0;i < v2.size(); ++i)
	{
		if(res[v2[i]])
		{
			return 0;
		}
	}
	return 1;
}
void doit1(vector<int> &a,int num)
{
	if(num == 1)
    {
        for(int i = 1;i <= n; ++i)
        {
            a[i] = 1 - a[i];
        }
    }
    if(num == 2)
    {
        for(int i = 1;i <= n; i += 2)
        {
            a[i] = 1 - a[i];
        }
    }
    if(num == 3)
    {
        for(int i = 2;i <= n; i += 2)
        {
            a[i] = 1 - a[i];
        }
    }
    if(num == 4)
    {
        for(int i = 1;i <= n; i += 3)
        {
            a[i] = 1 - a[i];
        }
    }
}
vector< vector<int> > v;
void doit(int k1,int k2,int k3,int k4)
{
	int k[5] = {0,k1,k2,k3,k4};
	int a[4] = {1,2,3,4};
	do{
		vector<int> p(n + 1,1);
		for(int i = 0;i < 4; ++i)
		{
			if(k[a[i]])
			{
				doit1(p,a[i]);
			}
		}
		if(ok(p))
		{
			v.push_back(p);
		}
	}while(next_permutation(a,a + 4));
}
int main(int argc, char const *argv[])
{
	freopen("lamps.in","r",stdin);
	freopen("lamps.out","w",stdout);
	cin>>n>>c;
	int x;
	while(cin>>x && x != -1)
	{
		v1.push_back(x);
	}
	while(cin>>x && x != -1)
	{
		v2.push_back(x);
	}
	for(int k = 0;k < 16; ++k)
	{
		int k1 = (k >> 3) & 1;
		int k2 = (k >> 2) & 1;
		int k3 = (k >> 1) & 1;
		int k4 = (k >> 0) & 1;
		if((((k1 + k2 + k3 + k4) & 1) == (c & 1))//注意，位运算优先级低
			&& (k1 + k2 + k3 + k4 <= c))
		{
			doit(k1,k2,k3,k4);
		}
	}
	if(v.size() == 0)
	{
		printf("IMPOSSIBLE\n");
		return 0;
	}
	sort(v.begin(),v.end());
	int pos = unique(v.begin(),v.end()) - v.begin();
	for(int i = 0;i < pos; ++i)
	{
		for(int j = 1;j < v[i].size(); ++j)
		{
			printf("%d",v[i][j]);
		}
		printf("\n");
	}
	return 0;
}