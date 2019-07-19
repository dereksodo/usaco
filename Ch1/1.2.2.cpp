/*
ID: zjd32151
TASK: gift1
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
const int maxn = 15;
string name[maxn];
map<string,int> mp;
int money[maxn];
int main(int argc, char const *argv[])
{
	freopen("gift1.in","r",stdin);
	freopen("gift1.out","w",stdout);
	int n;
	cin>>n;
	cin.get();
	for(int i = 0;i < n; ++i)
	{
		cin>>name[i];
		mp[name[i]] = i;
	}
	for(int i = 0;i < n; ++i)
	{
		string s;
		cin>>s;
		int id = mp[s];
		int a,b;
		cin>>a>>b;
		cin.get();
		if(b == 0)
		{
			money[id] += a;
			continue;
		}
		money[id] -= a;
		int every = a / b;
		money[id] += a - every * b;
		for(int i = 0;i < b; ++i)
		{
			string s;
			cin>>s;
			money[mp[s]] += every;
		}
		// printf("i = %d\n",i);
	}
	for(int i = 0;i < n; ++i)
	{
		printf("%s %d\n",name[i].c_str(),money[i]);
	}
	return 0;
}