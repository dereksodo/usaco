/*
ID: zjd32151
TASK: humble
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
const int maxn = 100005;
int s[maxn],a[105],b[105];
int main(int argc, char const *argv[])
{
	// freopen("humble.in","r",stdin);
	// freopen("humble.out","w",stdout);
	int n,m;
	cin>>n>>m;
	for(int i = 1;i <= n; ++i)
	{
		cin>>a[i];
	}
	s[0] = 1;
	for(int i = 1;i <= m; ++i)
	{
		int minx = INT_MAX;
		for(int j = 1;j <= n; ++j)
		{
			while(a[j] * s[b[j]] <= s[i - 1])
			{
				b[j]++;
			}
			minx = min(minx,a[j] * s[b[j]]);
		}
		s[i] = minx;
	}
	printf("%d\n",s[m]);
	return 0;
}