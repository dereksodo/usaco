/*
ID: zjd32151
TASK: kimbits
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
ll dp[34][34];
void pre()
{
	for(int i = 0;i <= 32; ++i)
	{
		dp[0][i] = 1;
	}
	for(int i = 1;i <= 32; ++i)
	{
		for(int j = 0;j <= 32; ++j)
		{
			if(j == 0)
			{
				dp[i][j] = 1;
			}
			else
			{
				dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
			}
		}
	}
}
void print(ll bits,ll nones,ll index)
{
	if(bits == 0)
	{
		return;
	}
	bits--;
	ll s = dp[bits][nones];
	if(s <= index)
	{
		printf("1");
		print(bits,nones - 1,index - s);
	}
	else
	{
		printf("0");
		print(bits,nones,index);
	}
}
int main(int argc, char const *argv[])
{
	// freopen("kimbits.in","r",stdin);
	// freopen("kimbits.out","w",stdout);
	ll bits,nones,index;
	cin>>bits>>nones>>index;
	pre();
	print(bits,nones,index - 1);
	printf("\n");
	return 0;
}