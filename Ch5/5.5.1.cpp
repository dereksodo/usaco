/*
ID: zjd32151
TASK: picture
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
namespace Countlen{
	const ll maxn = 5005;
	struct segtree{
		ll len[maxn << 2],sum[maxn << 2];
		bool li[maxn << 2],ri[maxn << 2];
		ll num[maxn << 2];
		struct node_{
			ll x,y1,y2,k;
			node_(){};
			node_(ll a,ll b,ll c,ll d)
			{
				x = a,y1 = b,y2 = c,k = d;
			}
			bool operator <(const node_ &b)const
			{
				return (x == b.x) ? (k > b.k) : (x < b.x);
			}
		};
		node_ node[maxn << 2];
		ll y[maxn << 2];
		void pushup(ll index,ll l,ll r)
		{
			if(sum[index] > 0)
			{
				len[index] = y[r + 1] - y[l];
				li[index] = ri[index] = num[index] = 1;
			}
			else if(l == r)
			{
				li[index] = ri[index] = len[index] = num[index] = 0;
			}
			else
			{
				len[index] = len[index << 1] + len[index << 1 | 1];
				num[index] = num[index << 1] + num[index << 1 | 1];
				if(ri[index << 1] == 1 && li[index << 1 | 1] == 1)
				{
					num[index]--;
				}
				li[index] = li[index << 1];
				ri[index] = ri[index << 1 | 1];
			}
		}
		void update(ll l,ll r,ll v,ll index,ll lnow,ll rnow)
		{
			if(l <= lnow && rnow <= r)
			{
				sum[index] += v;
				pushup(index,lnow,rnow);
				return;
			}
			ll mid = lnow + rnow >> 1;
			if(l <= mid)
			{
				update(l,r,v,index << 1,lnow,mid);
			}
			if(mid < r)
			{
				update(l,r,v,index << 1 | 1,mid + 1,rnow);
			}
			pushup(index,lnow,rnow);
		}
		ll Countlen_(ll n)
		{
			ll x1,y1,x2,y2;
			ll k = 0;
			for(ll i = 0;i < n; ++i)
			{
				scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
				y[k] = y1;
				node[k++] = node_(x1,y1,y2,1);
				y[k] = y2;
				node[k++] = node_(x2,y1,y2,-1);
			}
			sort(y,y + k);
			sort(node,node + k);
			node[k].x = node[k - 1].x;
			ll t = unique(y,y + k) - y;
			memset(sum,0x00,sizeof(sum));
			memset(len,0x00,sizeof(len));
			memset(num,0x00,sizeof(num));
			memset(li,0x00,sizeof(li));
			memset(ri,0x00,sizeof(ri));
			ll ans = 0,last = 0;
			for(ll i = 0;i < k; ++i)
			{
				ll left = lower_bound(y,y + t,node[i].y1) - y;
				ll right = lower_bound(y,y + t,node[i].y2) - y;
				update(left,right - 1,node[i].k,1,0,t);
				ans += abs(len[1] - last) + (node[i + 1].x - node[i].x) * 2 * num[1];
				last = len[1];
			}
			return ans;
		}
	};
	segtree st;
	int main(ll n)
	{
		printf("%lld\n",st.Countlen_(n));
		return 0;
	}
};
int main(int argc, char const *argv[])
{
	freopen("picture.in","r",stdin);
	freopen("picture.out","w",stdout);
	ll n;
	cin>>n;
	Countlen::main(n);
	return 0;
}