/*
ID: zjd32151
TASK: rectbarn
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
const int maxn = 3005;
bool a[maxn][maxn];
int H[2][maxn];
int n,m;
int q[maxn],L[maxn],R[maxn];
int ans;
int Max_area()
{
	for(int i = 1;i <= n; ++i)
	{
		H[0][i] = 0;
	}
	int top = 0;
	for(int i = 1;i <= n; ++i)
	{
		for(int j = 1;j <= m; ++j)
		{
			if(a[i][j] == 0)
			{
				H[i % 2][j] = 0;
			}
			else
			{
				H[i % 2][j] = H[(i - 1) % 2][j] + 1;
			}
		}
		top = 0;q[top] = 0;
		for(int j = 1;j <= m; ++j)
		{
			if(!a[i][j])
			{
				top = 1;
				q[top] = j;
				L[j] = 0;
				continue;
			}
			while(top > 0 && H[i % 2][j] <= H[i % 2][q[top]])
			{
				top--;
			}
			L[j] = j - q[top];
			top++;
			q[top] = j;
		}
		top = 0;
		q[top] = m + 1;
		for(int j = m;j; --j)
		{
			if(!a[i][j])
			{
				top = 1;
				q[top] = j;
				R[j] = 0;
			}
			while(top > 0 && H[i % 2][j] <= H[i % 2][q[top]])
			{
				top--;
			}
			R[j] = q[top] - j - 1;
			top++;
			q[top] = j;
		}
		for(int j = 1;j <= m; ++j)
		{
			ans = max(ans,H[i % 2][j] * (L[j] + R[j]));
		}
	}
	return ans;
}
int main(int argc, char const *argv[])
{
	freopen("rectbarn.in","r",stdin);
	freopen("rectbarn.out","w",stdout);
	int p;
	cin>>n>>m>>p;
	for(int i = 0;i < maxn; ++i)
	{
		for(int j = 0;j < maxn; ++j)
		{
			a[i][j] = 1;
		}
	}
	while(p--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		a[x][y] = 0;
	}
	printf("%d\n",Max_area());
	return 0;
}