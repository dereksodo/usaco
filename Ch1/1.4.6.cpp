/*
ID: zjd32151
TASK: skidesign
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
const int maxn = 1005;
int a[maxn];
int main(int argc, char const *argv[])
{
	freopen("skidesign.in","r",stdin);
	freopen("skidesign.out","w",stdout);
	int n;
	cin>>n;
	for(int i = 0;i < n; ++i)
	{
		scanf("%d",&a[i]);
	}
	int ans = 1e9;
	for(int i = 0;i <= 120; ++i)//least
	{
		int now = 0;
		for(int j = 0;j < n; ++j)
		{
			if(a[j] < i)
			{
				now += (i - a[j]) * (i - a[j]);
			}
			else if(a[j] - 17 > i)
			{
				now += (a[j] - 17 - i) * (a[j] - 17 - i);
			}
		}
		ans = min(ans,now);
	}
	cout<<ans<<endl;
	return 0;
}