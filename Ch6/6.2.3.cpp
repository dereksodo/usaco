/*
ID: zjd32151
TASK: rect1
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
const int maxn = 1005;
struct rect{
	int x1,y1,x2,y2,col;
	rect(){};
	rect(int xx1,int yy1,int xx2,int yy2,int co = 0)
	{
		x1 = xx1;
		y1 = yy1;
		x2 = xx2;
		y2 = yy2;
		col = co;
	}
};
rect r[maxn];
int cnt[maxn << 2],n;
int floatup(rect re,int k)
{
	if(re.x2 < re.x1 || re.y2 < re.y1)
	{
		return 0;
	}
	if(k == n + 1)
	{
		return (re.x2 - re.x1 + 1) * (re.y2 - re.y1 + 1);
	}
	if(re.x1 > r[k].x2 || re.x2 < r[k].x1 || re.y1 > r[k].y2 || re.y2 < r[k].y1)
	{
		return floatup(rect(re.x1,re.y1,re.x2,re.y2),k + 1);
	}
	return floatup(rect(re.x1,re.y1,r[k].x1 - 1,re.y2),k + 1) + floatup(rect(max(re.x1,r[k].x1),re.y1,min(re.x2,r[k].x2),r[k].y1 - 1),k + 1)
			+ floatup(rect(max(re.x1,r[k].x1),r[k].y2 + 1,min(re.x2,r[k].x2),re.y2),k + 1) + floatup(rect(r[k].x2 + 1,re.y1,re.x2,re.y2),k + 1);
}
int main(int argc, char const *argv[])
{
	freopen("rect1.in","r",stdin);
	freopen("rect1.out","w",stdout);
	r[0] = rect(0,0,0,0,1);
	scanf("%d%d%d",&r[0].x2,&r[0].y2,&n);
	--r[0].x2,--r[0].y2;
	for(int i = 1;i <= n; ++i)
	{
		scanf("%d%d%d%d%d",&r[i].x1,&r[i].y1,&r[i].x2,&r[i].y2,&r[i].col);
		r[i].x1 = max(r[i].x1,r[0].x1);
		r[i].y1 = max(r[i].y1,r[0].y1);
		r[i].x2 = min(r[i].x2 - 1,r[0].x2);
		r[i].y2 = min(r[i].y2 - 1,r[0].y2);
	}
	cnt[r[n].col] = (r[n].x2 - r[n].x1 + 1) * (r[n].y2 - r[n].y1 + 1);
	for(int i = n - 1;i >= 0; --i)
	{
		cnt[r[i].col] += floatup(r[i],i + 1);
	}
	for(int i = 1;i <= 2500; ++i)
	{
		if(cnt[i])
		{
			printf("%d %d\n",i,cnt[i]);
		}
	}
	return 0;
}