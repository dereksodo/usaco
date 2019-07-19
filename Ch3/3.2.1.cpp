/*
ID: zjd32151
TASK: fact4
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
const ll maxn = 100000000;
int main(int argc, char const *argv[])
{
	freopen("fact4.in","r",stdin);
	freopen("fact4.out","w",stdout);
	ll n;
	cin>>n;
	ll now = 1;
	for(ll i = 2;i <= n; ++i)
	{
		now = now * i;
		while(now % 10 == 0)
		{
			now /= 10;
		}
		now %= maxn;
	}
	cout<<now % 10<<endl;
	return 0;
}