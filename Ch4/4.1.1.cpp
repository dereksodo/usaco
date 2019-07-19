/*
ID: zjd32151
TASK: nuggets
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
const int maxn = 200005;
char mp[maxn];
int n;
int a[15];
int main(int argc, char const *argv[])
{
	freopen("nuggets.in","r",stdin);
	freopen("nuggets.out","w",stdout);
	cin>>n;
	for(int i = 0;i < n; ++i)
	{
		cin>>a[i];
	}
	mp[0] = 1;
	for(int i = 0;i < n; ++i)
	{
		for(int j = a[i];j < maxn; ++j)
		{
			mp[j] = mp[j] | mp[j - a[i]];
		}
	}
	int ans = 0;
	for(int i = maxn - 1;i >= 0; --i)
	{
		if(mp[i] == 0)
		{
			ans = i;
			break;
		}
	}
	if(ans > 100000)
	{
		ans = 0;
	}
	cout<<ans<<endl;
	return 0;
}