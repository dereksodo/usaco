/*
ID: zjd32151
TASK: theme
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
typedef unsigned long long ll;
#define DEBUG
#ifdef DEBUG
	#define debug prllf
#else
	#define debug(...)
#endif
const ll mod = 2007;
const ll rad = 1837467;
const ll maxn = 20005;
struct ss{
	ll num;
	ll pos;
	ss(ll a,ll b)
	{
		num = a,pos = b;
	}
};
vector<ss> G[mod];
ll n,len;
ll h[maxn],base[maxn];
ll data[maxn],a[maxn];
void init()
{
	base[0] = 1;
	for(ll i = 1;i < n; ++i)
	{
		a[i] = data[i + 1] - data[i];
	}
	len = n - 1;
	for(ll i = 1;i < n; ++i)
	{
		h[i] = h[i - 1] * rad + a[i];
		base[i] = base[i - 1] * rad;
	}
}
ll query(ll v,ll pos1,ll mid)
{
	ll x = v % mod;
	G[x].push_back(ss(v,pos1));
	for(ll i = 0;i < G[x].size(); ++i)
	{
		if(G[x][i].num == v && pos1 - G[x][i].pos >= mid + 1)
		{
			return 1;
		}
	}
	return 0;
}
ll check(ll mid)
{
	mid--;
	for(ll i = 0;i < mod; ++i)
	{
		G[i].clear();
	}
	for(ll i = 1;i <= len - mid + 1; ++i)
	{
		ll v = h[i + mid - 1] - h[i - 1] * base[mid];
		if(query(v,i,mid))
		{
			return 1;
		}
	}
	return 0;
}
int main(int argc, char const *argv[])
{
	freopen("theme.in","r",stdin);
	freopen("theme.out","w",stdout);
	cin>>n;
	for(ll i = 1;i <= n; ++i)
	{
		scanf("%llu",&data[i]);
	}
	init();
	ll l = 5,r = n,ans = 0;
	while(l < r)
	{
		ll mid = l + r >> 1;
		if(check(mid))
		{
			ans = mid;
			l = mid + 1;
		}
		else
		{
			r = mid;
		}
	}
	cout<<ans<<endl;
	return 0;
}