/*
ID: zjd32151
TASK: fc
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
const int maxn = 10005;
const double inf = 0x3f3f3f3f;
struct point{
	double x,y;
	void print()
	{
		printf("x = %.2lf,y = %.2lf\n",x,y);
	}
}p[maxn];
int n,st[maxn],top;
double ans;
int cmp(point a,point b)
{
	return a.y == b.y ? a.x < b.x : a.y < b.y;
}
double dis(int a,int b)
{
	return sqrt((p[a].x - p[b].x) * (p[a].x - p[b].x) + (p[a].y - p[b].y) * (p[a].y - p[b].y));
}
int judge(int a,int b,int c)
{
	return (p[a].y - p[b].y) * (p[b].x - p[c].x) > (p[a].x - p[b].x) * (p[b].y - p[c].y);
}
int main(int argc, char const *argv[])
{
	freopen("fc.in","r",stdin);
	freopen("fc.out","w",stdout);
	cin>>n;
	for(int i = 1;i <= n; ++i)
	{
		scanf("%lf%lf",&p[i].x,&p[i].y);
	}
	sort(p + 1,p + n + 1,cmp);

	st[1] = 1;
	st[2] = 2;
	top = 2;
	for(int i = 3;i <= n; ++i)
	{
		while(top > 1 && !judge(i,st[top],st[top - 1]))
		{
			top--;
		}
		st[++top] = i;
	}

	for(int i = 1;i < top; ++i)
	{
		ans += dis(st[i],st[i + 1]);
	}

	st[1] = 1;
	st[2] = 2;
	top = 2;
	for(int i = 3;i <= n; ++i)
	{
		while(top > 1 && judge(i,st[top],st[top - 1]))
		{
			top--;
		}
		st[++top] = i;
	}
	for(int i = 1;i < top; ++i)
	{
		ans += dis(st[i],st[i + 1]);
	}
	printf("%.2lf\n",ans);
	return 0;
}