/*
ID: zjd32151
TASK: contact
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
map<int,int> mp;
int cmp(pair<int,int> a,pair<int,int> b)
{
	if(a.second == b.second)
	{
		return a.first < b.first;
	}
	return a.second > b.second;
}
void display(int n)
{
	string str = "";
	while(n)
	{
		str += char((n % 2) + '0');
		n /= 2;
	}
	for(int i = str.size() - 2;i >= 0; --i)
	{
		putchar(str[i]);
	}
}
int main(int argc, char const *argv[])
{
	freopen("contact.in","r",stdin);
	freopen("contact.out","w",stdout);
	int a,b,n;
	cin>>a>>b>>n;
	string s;
	string str;
	while(cin>>s)
	{
		str += s;
	}
	// cin>>str;
	for(int i = 0;i < str.size(); ++i)
	{
		int now = 1;
		for(int j = 1;j < a; ++j)
		{
			now = (now << 1) + int(str[i + j - 1] - '0');
		}
		for(int j = a;j <= b && i + j - 1 < str.size(); ++j)
		{
			// printf("%s ",str.substr(i,j).c_str());
			now = (now << 1) + int(str[i + j - 1] - '0');
			mp[now]++;
			// printf("%d\n",now);
		}
	}
	// printf("\n");
	vector< pair<int,int> > v(mp.begin(),mp.end());
	sort(v.begin(),v.end(),cmp);
	int cur = 0;
	// printf("\n");
	// for(int i = 0;i < v.size(); ++i)
	// {
	// 	printf("%d %d\n",v[i].first,v[i].second);
	// }
	// printf("\n");
	for(int i = 0;i < v.size() && cur < n; ++cur)
	{
		int now = v[i].second;
		printf("%d\n",now);
		display(v[i++].first);
		int cnt = 1;
		for(;i < v.size() && v[i].second == now; ++i)
		{
			if(cnt % 6 != 0)
			{
				printf(" ");
			}
			display(v[i].first);
			++cnt;
			if(cnt % 6 == 0)
			{
				printf("\n");
			}
		}
		if(cnt % 6 != 0)
		{
			printf("\n");
		}
	}
	return 0;
}