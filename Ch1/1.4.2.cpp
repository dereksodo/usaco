/*
ID: zjd32151
TASK: barn1
LANG: C++
*/
#include <bits/stdc++.h>
using namespace std;
//#define DEBUG
#ifdef DEBUG
	#define debug printf
#else
	#define debug(...)
#endif
const int maxn = 205;
int vis[maxn];
vector< pair<int,int> > v;
int main(int argc,char const *argv[])
{
//	freopen("barn1.in","r",stdin);
//	freopen("barn1.out","w",stdout);
	int m,s,c;
	cin>>m>>s>>c;
	for(int i = 0;i < c; ++i)
	{
		int x;
		scanf("%d",&x);
		vis[x - 1] = 1;
	}
	for(int i = 0;i < s;)
	{
		if(vis[i])
		{
			int j = i;
			while(vis[j])
			{
				++j;
			}
			--j;
			v.push_back(make_pair(i,j));
			i = j + 1;
		}
		else
		{
			++i;
		}
	}
	for(int i = 0;i < v.size(); ++i)
	{
		debug("%d %d\n",v[i].first + 1,v[i].second + 1);
	}
	vector<int> k;
	k.clear();
	for(int i = 0;i < v.size() - 1; ++i)
	{
		k.push_back(v[i + 1].first - v[i].second - 1);
	}
	sort(k.begin(),k.end());
	for(int i = 0;i < k.size(); ++i)
	{
		debug("%d ",k[i]);
	}
	debug("\n");
	int ans = c;
	if(m < v.size())
	{
		for(int i = 1;i <= v.size() - m; ++i)
		{
			ans += k[i - 1];
			debug("+%d\n",k[i - 1]);
		}
	}
	cout<<ans<<endl;
	return 0;
}

