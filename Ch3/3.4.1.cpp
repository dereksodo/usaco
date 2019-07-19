/*
ID: zjd32151
TASK: heritage
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
void dfs(string t,string s)
{
	if(t.empty() || s.empty())
	{
		return;
	}
	int pos = t.find(s[0]);
	dfs(t.substr(0,pos),s.substr(1,pos));
	dfs(t.substr(pos + 1),s.substr(pos + 1));
	cout<<s[0];
}
int main(int argc, char const *argv[])
{
	freopen("heritage.in","r",stdin);
	freopen("heritage.out","w",stdout);
	string a,b;
	cin>>a>>b;
	dfs(a,b);
	printf("\n");
	return 0;
}