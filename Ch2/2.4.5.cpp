/*
ID: zjd32151
TASK: fracdec
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
const int maxn = 1000005;
int n,m;
char output[maxn];
int vis[maxn];
int pos = 0;
void Num()
{
	int k = n / m;
	if(k == 0)
	{
		output[pos++] = '0';
		return;
	}
	while(k)
	{
		output[pos++] = char(k % 10 + '0');
		k /= 10;
	}
	reverse(output,output + pos);
}
int lef;
void Dec()
{
	output[pos++] = '.';
	lef = -1;
	int k = n % m;
	if(k == 0)
	{
		output[pos++] = '0';
		return;
	}
	while(k)
	{
		if(vis[k])
		{
			lef = vis[k];
			break;
		}
		vis[k] = pos;
		k *= 10;
		output[pos++] = char(k / m + '0');
		k %= m;
	}
	if(lef != -1)
	{
		output[pos++] = ')';
	}
}
void Print()
{
	int cnt = 0;
	for(int i = 0;i < pos; ++i)
	{
		if(i == lef)
		{
			printf("(");
			cnt++;
			if(cnt % 76 == 0)
			{
				printf("\n");
			}
		}
		printf("%c",output[i]);
		cnt++;
		if(cnt % 76 == 0)
		{
			printf("\n");
		}
	}
	if(cnt % 76 != 0)
	{
		printf("\n");
	}
}
int main(int argc, char const *argv[])
{
	// freopen("fracdec.in","r",stdin);
	// freopen("fracdec.out","w",stdout);
	cin>>n>>m;
	Num();
	Dec();
	Print();
	return 0;
}