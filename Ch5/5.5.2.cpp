/*
ID: zjd32151
TASK: hidden
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
char s[5000005];
int n;
int getmin()
{
	int i = 0,j = 1,k = 0;
	while(i < n && j < n && k < n)
	{
		int t = s[(i + k) % n] - s[(j + k) % n];
		if(!t)
		{
			k++;
		}
		else
		{
			if(t > 0)
			{
				i += k + 1;
			}
			else
			{
				j += k + 1;
			}
			if(i == j)
			{
				j++;
			}
			k = 0;
		}
	}
	return min(i,j);
}
int main(int argc, char const *argv[])
{
	freopen("hidden.in","r",stdin);
	freopen("hidden.out","w",stdout);
	scanf("%d",&n);
	for(int i = 0;i < n;)
	{
		string str;
		cin>>str;
		for(int j = 0;j < str.size(); ++j,++i)
		{
			s[i] = str[j];
		}
	}
	printf("%d\n",getmin());
	return 0;
}