/*
ID: zjd32151
TASK: calfflac
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
const int maxn = 20005;
char a[maxn],s[maxn << 1],b[maxn << 1];
int pal[maxn << 1];
int n;
map<int,int> mp,mp2;
pair<int,int> manacher()
{
	s[0] = '~';
	s[1] = '#';
	for(int i = 0;i < n; ++i)
	{
		s[i * 2 + 2] = a[i];
		mp[i * 2 + 2] = i;
		s[i * 2 + 3] = '#';
	}
	n = n * 2 + 2;
	// printf("%s\n",s);
	int maxright = 0,mid = 0;
	int ans = 0;
	int p = 0;
	for(int i = 1;i < n; ++i)
	{
		if(i < maxright)
		{
			pal[i] = min(pal[(mid << 1) - i],maxright - i);
		}
		else
		{
			pal[i] = 1;
		}
		while(s[i + pal[i]] == s[i - pal[i]])
		{
			pal[i]++;
		}
		if(pal[i] + i > maxright)
		{
			maxright = pal[i] + i;
			mid = i;
		}
		if(pal[i] > ans)
		{
			// printf("s[%d] = %c\n",i,s[i]);
			// printf("pal[%d] = %d\n",i,pal[i]);
			p = i;
			ans = pal[i];
		}
		// printf("pal[%d] = %d\n",i,pal[i]);
	}
	return make_pair(mp[p] - (ans - 2) / 2,ans - 1);
}
int main(int argc, char const *argv[])
{
	freopen("calfflac.in","r",stdin);
	freopen("calfflac.out","w",stdout);
	n = 0;
	int bn = 0;
	char c;
	while(scanf("%c",&c) != EOF)
	{
		b[bn++] = c;
		if(isalpha(c))
		{
			a[n++] = tolower(c);
			mp2[n - 1] = bn - 1;
		}
	}
	pair<int,int> res = manacher();
	// printf("Res.first = %d(%c),res.second = %d\n",res.first,a[res.first],res.second);
	printf("%d\n",res.second);
	for(int i = mp2[res.first];res.second; ++i)
	{
		// printf("i = %d\n",i);
		if(isalpha(b[i]))
		{
			res.second--;
		}
		printf("%c",b[i]);
	}
	printf("\n");
	return 0;
}