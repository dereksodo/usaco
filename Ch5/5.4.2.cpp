/*
ID: zjd32151
TASK: charrec
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
const char str[] = " abcdefghijklmnopqrstuvwxyz";
char font[550][25];
char input[1205][30];
int dp[1205][3],mat[1205][550],f[1205];
char cur[1205][3];
string ans[1205];
int notmatch(int col1,int col2)
{
	int cnt = 0;
	for(int i = 0;i < 20; ++i)
	{
		if(input[col1][i] != font[col2][i])
		{
			cnt++;
		}
	}
	return cnt;
}
int main(int argc, char const *argv[])
{
	FILE *in,*out;
	in = fopen("font.in","r");
	int aa;
	fscanf(in,"%d",&aa);
	for(int i = 1;i <= aa; ++i)
	{
		fscanf(in,"%s",font[i]);
	}
	in = fopen("charrec.in","r");
	int n;
	fscanf(in,"%d",&n);
	for(int i = 1;i <= n; ++i)
	{
		fscanf(in,"%s",input[i]);
	}

	memset(dp,0x3f3f3f3f,sizeof(dp));
	for(int i = 1;i <= aa; ++i)
	{
		for(int j = 1;j <= n; ++j)
		{
			mat[j][i] = notmatch(j,i);
		}
	}
	for(int k = 1;k <= aa; k += 20)
	{
		for(int i = 1;i <= n; ++i)
		{
			if(i + 19 <= n)
			{
				int temp = 0;
				for(int l = 1;l <= 20; ++l)
				{
					temp += mat[i + l - 1][k + l - 1];
				}
				if(temp < dp[i][1])
				{
					cur[i][1] = (temp > 120 ? '?' : str[k / 20]);
					dp[i][1] = temp;
				}
			}
			for(int j = 1;j <= 21; ++j)
			{
				if(j < 21 && i + 18 <= n)
				{
					int temp = 0;
					for(int l = 1;l < j; ++l)
					{
						temp += mat[i + l - 1][k + l - 1];
					}
					for(int l = j;l <= 19; ++l)
					{
						temp += mat[i + l - 1][k + l];
					}
					if(temp < dp[i][0])
					{
						cur[i][0] = (temp > 120 ? '?' : str[k / 20]);
						dp[i][0] = temp;
					}
				}
				if(i + 20 <= n)
				{
					int temp = 0;
					for(int l = 1;l < j; ++l)
					{
						temp += mat[i + l - 1][k + l - 1];
					}
					for(int l = j;l <= 21; ++l)
					{
						temp += mat[i + l][k + l - 1];
					}
					if(temp < dp[i][2])
					{
						cur[i][2] = (temp > 120 ? '?' : str[k / 20]);
						dp[i][2] = temp;
					}
				}
			}
		}
	}
	f[0] = 0;
	ans[0] = "";
	for(int i = 1;i < 19; ++i)
	{
		ans[i] = "?";
		f[i] = 0x3f3f3f3f;
	}
	for(int i = 19;i <= n; ++i)
	{
		f[i] = f[i - 19] + dp[i - 18][0];
		ans[i] = ans[i - 19] + cur[i - 18][0];
		if(i > 19 && f[i] > f[i - 20] + dp[i - 19][1])
		{
			f[i] = f[i - 20] + dp[i - 19][1];
			ans[i] = ans[i - 20] + cur[i - 19][1];
		}
		if(i > 20 && f[i] > f[i - 21] + dp[i - 20][2])
		{
			f[i] = f[i - 21] + dp[i - 20][2];
			ans[i] = ans[i - 21] + cur[i - 20][2];
		}
	}
	out = fopen("charrec.out","w");
	fprintf(out,"%s\n",ans[n].c_str());
	return 0;
}