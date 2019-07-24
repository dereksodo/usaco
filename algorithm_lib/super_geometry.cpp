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
typedef double ld;
#define DEBUG
#ifdef DEBUG
	#define debug printf
#else
	#define debug(...)
#endif
const int maxn = 10005;
const ld eps = 1e-8;
struct point{
	ld x,y;
};
ld cross(point a,point b,point c)
{
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}
ld dis(point a,point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
struct polygon{
	point v[maxn];
	stack<point> sk;
	point start;
	bool cmp1(point a,point b)
	{
		if(fabs(a.y - b.y) < eps)
		{
			return a.x < b.x;
		}
		return a.y < b.y;
	}
	bool cmp2(point a,point b)//极角
	{
		if((atan2(a.y - start.y,a.x - start.x)) != atan2(b.y - start.y,b.x - start.x))
		{
			return (atan2(a.y - start.y,a.x - start.x)) < atan2(b.y - start.y,b.x - start.x);
		}
		return a.x < b.x;
	}
	bool cmp2_2(point a,point b)
	{
		ld m = cross(v[0],a,b);
		if(m > eps)
		{
			return 1;
		}
		else if(m >= 0 && m < eps && dis(v[0],a) - dis(v[0],b) <= 0)
		{
			return 1;
		}
		return 0;
	}
};
int main(int argc, char const *argv[])
{
	
	return 0;
}