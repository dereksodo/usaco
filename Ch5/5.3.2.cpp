/*
ID: zjd32151
TASK: window
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
const int maxn = 1000;
char ca[maxn];
int cnt;
struct window{
	int x1,y1,x2,y2;
	char c;
	window(int _x1 = 0,int _y1 = 0,int _x2 = 0,int _y2 = 0,int _c = 0):x1(_x1),y1(_y1),x2(_x2),y2(_y2),c(_c){};
	void print()
	{
		printf("%d %d %d %d\n",x1,y1,x2,y2);
	}
	bool operator ==(const window &b)const
	{
		return c == b.c;
	}
}w[maxn],a[maxn];
double ans;
void move(window tmp,int op)
{
	int pos = 0;
	for(int i = 1;i <= cnt; ++i)
	{
		if(a[i] == tmp)
		{
			pos = i;
			break;
		}
	}
	if(op == 0)
	{
		for(int i = pos;i >= 2; --i)
		{
			swap(a[i],a[i - 1]);
		}
	}
	else
	{
		for(int i = pos;i < cnt; ++i)
		{
			swap(a[i],a[i + 1]);
		}
	}
}
void del(window tmp)
{
	int pos = 0;
	for(int i = 1;i <= cnt; ++i)
	{
		if(a[i] == tmp)
		{
			pos = i;
			break;
		}
	}
	w[tmp.c] = window(0,0,0,0,0);
	for(int i = pos + 1;i <= cnt; ++i)
	{
		a[i - 1] = a[i];
	}
	cnt--;
}
void dfs(int k,int x1,int y1,int x2,int y2)
{
	if(x1 == x2 || y1 == y2)
	{
		return;
	}
	if(!k)
	{
		ans += (double)(x2 - x1 + 0.0) * (y2 - y1);
		return;
	}
	int X1 = a[k].x1,X2 = a[k].x2,Y1 = a[k].y1,Y2 = a[k].y2;
	if(X2 < x1 || X1 > x2 || Y2 < y1 || Y1 > y2)
	{
		dfs(k - 1,x1,y1,x2,y2);
		return;
	}
	if(X1 <= x1 && x2 <= X2 && Y1 <= y1 && y2 <= Y2)
	{
		return;
	}
	dfs(k - 1,x1,min(y2,Y2),min(x2,X2),y2);
	dfs(k - 1,min(x2,X2),max(y1,Y1),x2,y2);
	dfs(k - 1,max(x1,X1),y1,x2,max(y1,Y1));
	dfs(k - 1,x1,y1,max(x1,X1),min(y2,Y2));
}
int main(int argc, char const *argv[])
{
	freopen("window.in","r",stdin);
	freopen("window.out","w",stdout);
	char op;
	while(cin>>op)
	{
		char index;
		if(op == 'w')
		{
			int x1,y1,x2,y2;
			scanf("(%c,%d,%d,%d,%d)",&index,&x1,&y1,&x2,&y2);
			if(x1 > x2)
			{
				swap(x1,x2);
			}
			if(y1 > y2)
			{
				swap(y1,y2);
			}
			window tmp = window(x1,y1,x2,y2,index);
			w[index] = a[++cnt] = tmp;
			move(tmp,0);
		}
		else if(op == 't')
		{
			scanf("(%c)",&index);
			window tmp = window(0,0,0,0,index);
			move(tmp,0);
		}
		else if(op == 'b')
		{
			scanf("(%c)",&index);
			window tmp = window(0,0,0,0,index);
			move(tmp,1);
		}
		else if(op == 'd')
		{
			scanf("(%c)",&index);
			window tmp = window(0,0,0,0,index);
			del(tmp);
		}
		else
		{
			scanf("(%c)",&index);
			int pos = 0;
			for(int i = 1;i <= cnt; ++i)
			{
				if(a[i] == w[index])
				{
					pos = i;
					break;
				}
			}
			ans = 0.0;
			double area = (a[pos].x2 - a[pos].x1 + 0.0) * (a[pos].y2 - a[pos].y1);
			dfs(pos - 1,a[pos].x1,a[pos].y1,a[pos].x2,a[pos].y2);
			printf("%.3lf\n",ans * 100 / area);
		}
		getchar();
	}
	return 0;
}