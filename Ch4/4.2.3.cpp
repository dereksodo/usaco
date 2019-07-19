/*
ID: zjd32151
TASK: job
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
struct ii{
	int s,v;
	bool operator <(ii k)const
	{
		return s > k.s;
	}
}x;
priority_queue<ii> pq;
int t[maxn];
int main(int argc, char const *argv[])
{
	freopen("job.in","r",stdin);
	freopen("job.out","w",stdout);
	int n,a_cnt,b_cnt;
	cin>>n>>a_cnt>>b_cnt;
	for(int i = 0;i < a_cnt; ++i)
	{
		scanf("%d",&x.v);
		x.s = x.v;
		pq.push(x);
	}
	for(int i = 1;i <= n; ++i)
	{
		x = pq.top();
		pq.pop();
		t[i] = x.s;
		x.s += x.v;
		pq.push(x);
	}
	while(!pq.empty())
	{
		pq.pop();
	}
	for(int i = 0;i < b_cnt; ++i)
	{
		scanf("%d",&x.v);
		x.s = x.v;
		pq.push(x);
	}
	int ans = 0;
	for(int i = n;i >= 1; --i)
	{
		x = pq.top();
		pq.pop();
		ans = max(ans,x.s + t[i]);
		x.s += x.v;
		pq.push(x);
	}
	printf("%d %d\n",t[n],ans);
	return 0;
}