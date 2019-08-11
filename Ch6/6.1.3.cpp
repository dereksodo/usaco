/*
ID: zjd32151
TASK: cowxor
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
const int maxn = 100005;
int a[maxn],b[maxn];
int ch[maxn * 10][2],node;
void insert(int num)
{
	int u = 0;
	for(int i = 20;i >= 0; --i)
	{
		int c = ((b[num] >> i) & 1);
		if(ch[u][c])
		{
			u = ch[u][c];
		}
		else
		{
			ch[u][c] = ++node;
			u = node;
		}
	}
	ch[u][0] = num;
}
int solve(int num)
{
	int u = 0;
	for(int i = 20;i >= 0; --i)
	{
		int c = ((b[num] >> i) & 1);
		if(ch[u][c ^ 1])
		{
			u = ch[u][c ^ 1];
		}
		else
		{
			u = ch[u][c];
		}
	}
	return ch[u][0];
}
int main(int argc, char const *argv[])
{
	freopen("cowxor.in","r",stdin);
	freopen("cowxor.out","w",stdout);
	int n;
	scanf("%d",&n);
	node = 0;
	for(int i = 0;i < n; ++i)
	{
		scanf("%d",&a[i]);
	}
	int ansst = 0,ansed = 0,ans = 0;
	b[0] = a[0];
	for(int i = 1;i < n; ++i)
	{
		b[i] = b[i - 1] ^ a[i];
	}
	for(int i = 0;i < n; ++i)
	{
		int j = solve(i);
		if(i == j)
		{
			if(a[i] > ans)
			{
				ans = a[i];
				ansed = i,ansst = j;
			}
		}
		else
		{
			int ret = b[i] ^ b[j];
			if(ret > ans)
			{
				ans = ret;
				ansed = i,ansst = j + 1;
			}
		}
		insert(i);
	}
	printf("%d %d %d\n",ans,ansst + 1,ansed + 1);
	return 0;
}