/*
ID: zjd32151
TASK: packrec
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
#define x first
#define y second
const int n = 4;
pair<int,int> a[5];
int ans;
set< pair<int,int> > s;
void update(int w,int h)
{
	if(w > h)
	{
		swap(w,h);
	}
	int ret = w * h;
	if(ret < ans)
	{
		s.clear();
		s.insert(make_pair(w,h));
		ans = w * h;
	}
	else if(ret == ans)
	{
		s.insert(make_pair(w,h));
	}
}
int cmp(pair<int,int> p1,pair<int,int> p2)
{
	return p1.y < p2.y;
}
void calc()
{
	{
		//[ 1]
		//[ 1][ 2]
		//[ 1][ 2][ 3]
		//[ 1][ 2][ 3][ 4]
		//[ 1][ 2][ 3][ 4]
		//case 1:
		int xmax = max(max(a[1].x,a[2].x),max(a[3].x,a[4].x));
		int ymax = a[1].y + a[2].y + a[3].y + a[4].y;
		update(xmax,ymax);
	}

	{
		//           [ 4] 
		//       [ 3][ 4]  
		//       [ 3][ 4] 
		//   [ 2][ 3][ 4]
		//   [ 2][ 3][ 4]
		//[		 1 		]
		//case 2:
		int xmax = max(max(a[1].x,a[2].x),a[3].x) + a[4].x;
		int ymax = max(a[4].y,a[1].y + a[2].y + a[3].y);
		update(xmax,ymax);
	}

	{
		//          [1]
		//       [2][1]
		//    [3][2][1]
		//    [3][2][1]
		//    [3][2][1]
		//[    4   ][1]
		//case 3:
		int xmax = max(a[4].x,max(a[1].x,a[2].x) + a[3].x);
		int ymax = max(a[1].y + a[2].y,a[3].y) + a[4].y;
		update(xmax,ymax);
	}

	{
		//[ 4]
		//[ 4][ 1][ 3]
		//[ 4][ 1][ 3]
		//[ 4][ 2][ 3]
		//[ 4][ 2][ 3]
		//case 4:
		int xmax = max(a[1].x,max(a[2].x + a[3].x,a[4].x));
		int ymax = a[1].y + max(a[2].y,a[3].y) + a[4].y;
		update(xmax,ymax);
	}

	{
		//         [4]
		//      [3][4]
		//[1]   [3][4]
		//[1]   [3][4]
		//[2][2][3][4]
		//[2][2][3][4]
		//case 5:
		int xmax = max(a[1].x,a[2].x) + a[3].x + a[4].x;
		int ymax = max(a[1].y,a[2].y) + a[3].y + a[4].y;
		update(xmax,ymax);
	}

	{
		//      [1][1][1][1]	
		//   [2][2][4][4][4]
		//   [2][2][4][4][4]
		//[3][3][3][4][4][4]
		//[3][3][3][4][4][4]
		//[3][3][3][4][4][4]
		//case 6:
		if(a[1].y <= a[2].y && a[2].x <= a[4].x)
		{
			int xmax = max(a[1].x + a[2].x,a[3].x + a[4].x);
			int ymax = max(a[2].y + a[4].y,a[1].y + a[3].y);
			update(xmax,ymax);
		}
	}
}
void rotate(int index)
{
	if(index > n)
	{
		calc();
		return;
	}
	rotate(index + 1);
	swap(a[index].x,a[index].y);
	rotate(index + 1);
	swap(a[index].x,a[index].y);
}
void permutation(int index)
{
	if(index > n)
	{
		rotate(1);
		return;
	}
	for(int i = index;i <= n; ++i)
	{
		swap(a[i],a[index]);
		permutation(index + 1);
		swap(a[i],a[index]);
	}
}
int main(int argc, char const *argv[])
{
	freopen("packrec.in","r",stdin);
	freopen("packrec.out","w",stdout);
	for(int i = 1;i <= n; ++i)
	{
		scanf("%d%d",&a[i].x,&a[i].y);
	}
	ans = 0x3f3f3f3f;
	permutation(1);
	printf("%d\n",(s.begin()->x) * (s.begin()->y));
	for(set< pair<int,int> >::iterator iter = s.begin();iter != s.end(); ++iter)
	{
		printf("%d %d\n",iter->x,iter->y);
	}
	return 0;
}