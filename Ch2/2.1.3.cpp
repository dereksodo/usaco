/*
ID: zjd32151
TASK: sort3
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
int cnt[4],a[1005];
int n;
void display()
{
	for(int i = 0;i < n; ++i)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
}
int s[4][4];
int main(int argc, char const *argv[])
{
	freopen("sort3.in","r",stdin);
	freopen("sort3.out","w",stdout);
	int n;
	cin>>n;
	for(int i = 0;i < n; ++i)
	{
		cin>>a[i];
		cnt[a[i]]++;
	}
	int sum = 0;
	for(int i = 0;i < cnt[1]; ++i)
	{
		if(a[i] != 1)
		{
			s[1][a[i]]++;
			sum++;
		}
	}
	for(int i = cnt[1];i < cnt[2] + cnt[1]; ++i)
	{
		if(a[i] != 2)
		{
			s[2][a[i]]++;
			sum++;
		}
	}
	for(int i = cnt[1] + cnt[2];i < n; ++i)
	{
		if(a[i] != 3)
		{
			s[3][a[i]]++;
			sum++;
		}
	}
	int now = min(s[1][2],s[2][1]) + min(s[1][3],s[3][1]) + min(s[2][3],s[3][2]);
	now += ((sum - now * 2) / 3) * 2;
	cout<<now<<endl;
	return 0;
}