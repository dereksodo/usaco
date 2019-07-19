/*
ID: zjd32151
TASK: beads
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
int main(int argc, char const *argv[])
{
	freopen("beads.in","r",stdin);
	freopen("beads.out","w",stdout);
	int n;
	cin>>n;
	string s;
	cin>>s;
	int begins = s.size();
	int ends = s.size() + s.size() - 1;
	s += s;
	s += s;
	int ans = 0;
	for(int cut = begins;cut <= ends; ++cut)
	{
		int i = cut;
		char tar = s[cut];
		int now1 = 0;
		while(i >= 0 && (tar == 'w' || s[i] == tar || s[i] == 'w'))
		{
			if(tar == 'w' && s[i] != 'w')
			{
				tar = s[i];
			}
			--i;
			++now1;
		}
		++i;
		i = cut + 1;
		tar = s[i];
		int now2 = 0;
		while(i < s.size() && (tar == 'w' || s[i] == tar || s[i] == 'w'))
		{
			if(tar == 'w' && s[i] != 'w')
			{
				tar = s[i];
			}
			++i;
			++now2;
		}
		--i;
		ans = max(ans,min(now1 + now2,n));
	}
	cout<<ans<<endl;
	return 0;
}