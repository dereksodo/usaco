/*
ID: zjd32151
TASK: stamps
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
const int maxn = 2000005;
int a[55];
int c[maxn];
int k,n;
const int inf = 1e9;
int main(int argc, char const *argv[])
{
	freopen("stamps.in","r",stdin);
	freopen("stamps.out","w",stdout);
	int k,n;
	cin>>k>>n;
	for(int i = 0;i < n; ++i)
	{
		scanf("%d",&a[i]);
	}
	sort(a,a + n);
	c[0] = 0;
	for(int i = 1;; ++i)
	{
		c[i] = inf;
		for(int j = 0;j < n && a[j] <= i; ++j)
		{
			c[i] = min(c[i],c[i - a[j]] + 1);
		}
		if(c[i] > k)
		{
			printf("%d\n",i - 1);
			return 0;
		}
	}
	return 0;
}