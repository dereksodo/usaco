/*
ID: zjd32151
TASK: frameup
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
// #define DEBUG
#ifdef DEBUG
	#define debug printf
#else
	#define debug(...)
#endif
char mp[35][35];
char color[35];
int color_cnt;
int vis[35];
struct rect{
	int left_i,left_j,right_i,right_j;
	void print()
	{
		debug("%d %d %d %d\n",left_i,left_j,right_i,right_j);
	}
	void update(int i,int j)
	{
		left_i = min(left_i,i);
		left_j = min(left_j,j);
		right_i = max(right_i,i);
		right_j = max(right_j,j);
	}
}rec[30];
vector<string> vec;
int n,m;
void PPP(int dep)
{
	for(int i = 0;i < dep; ++i)
	{
		debug("	");
	}
}
void Print(int dep)
{
	debug("\n");
	for(int i = 1;i <= n; ++i)
	{
		PPP(dep);debug("%s\n",mp[i] + 1);
	}
	debug("\n");
}
int check()
{
	for(int i = 1;i <= n; ++i)
	{
		for(int j = 1;j <= m; ++j)
		{
			if(mp[i][j] != '.')
			{
				return 0;
			}
		}
	}
	return 1;
}
int aa(char c,char tar)
{
	if(c == '.')
	{
		return 0;
	}
	if(c == tar)
	{
		return 0;
	}
	return 1;
}
int ok(int index,int dep)
{
	int x = color[index] - 'A';
	PPP(dep);
	rec[x].print();
	for(int j = rec[x].left_j;j <= rec[x].right_j; ++j)
	{
		PPP(dep);
		debug("%d %d\n",rec[x].left_i,j);
		PPP(dep);
		debug("%d %d\n",rec[x].right_i,j);
		if(aa(mp[rec[x].left_i][j],color[index]) || aa(mp[rec[x].right_i][j],color[index]))
		{
			return 0;
		}
	}
	for(int i = rec[x].left_i;i <= rec[x].right_i; ++i)
	{
		PPP(dep);
		debug("%d %d\n",i,rec[x].left_j);
		PPP(dep);
		debug("%d %d\n",i,rec[x].right_j);
		if(aa(mp[i][rec[x].left_j],color[index]) || aa(mp[i][rec[x].right_j],color[index]))
		{
			return 0;
		}
	}
	return 1;
}
void del(int index)
{
	int x = color[index] - 'A';
	for(int j = rec[x].left_j;j <= rec[x].right_j; ++j)
	{
		mp[rec[x].left_i][j] = mp[rec[x].right_i][j] = '.';
	}
	for(int i = rec[x].left_i;i <= rec[x].right_i; ++i)
	{
		mp[i][rec[x].left_j] = mp[i][rec[x].right_j] = '.';
	}
}
void dfs(string s,int dep)
{
	PPP(dep);
	debug("%s\n",s.c_str());
	PPP(dep);
	Print(dep);
	// getchar();
	if(s.size() == color_cnt)
	{
		Print(dep);
		if(check())
		{
			vec.push_back(s);
		}
		return;
	}
	char mp2[35][35];
	memcpy(mp2,mp,sizeof(mp));
	for(int i = 1;i <= color_cnt; ++i)
	{
		if(!vis[i])
		{
			PPP(dep);
			debug("color[%d] = %c\n",i,color[i]);
			memcpy(mp,mp2,sizeof(mp));
			if(ok(i,dep))
			{
				Print(dep);
				PPP(dep);
				debug("***color[%d] = %c\n",i,color[i]);
				vis[i] = 1;
				del(i);
				string t = s;
				t += color[i];
				dfs(t,dep + 1);
				vis[i] = 0;
			}
		}
	}
}
int main(int argc, char const *argv[])
{
	freopen("frameup.in","r",stdin);
	freopen("frameup.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n; ++i)
	{
		scanf("%s",mp[i] + 1);
		for(int j = 1;j <= m; ++j)
		{
			if(mp[i][j] != '.')
			{
				int x = mp[i][j] - 'A';
				if(!vis[x])
				{
					vis[x] = 1;
					color[++color_cnt] = mp[i][j];
					rec[x].left_i = rec[x].left_j = 50;
					rec[x].right_i = rec[x].right_j = 0;
				}
				rec[x].update(i,j);
			}
		}
	}

	for(int i = 1;i <= color_cnt; ++i)
	{
		debug("%c:",color[i]);
		rec[color[i] - 'A'].print();
	}

	memset(vis,0x00,sizeof(vis));
	dfs("",0);

	for(int i = 0;i < vec.size(); ++i)
	{
		reverse(vec[i].begin(),vec[i].end());
		// printf("%s\n",vec[i].c_str());
	}

	sort(vec.begin(),vec.end());

	for(int i = 0;i < vec.size(); ++i)
	{
		// reverse(vec[i].begin(),vec[i].end());
		printf("%s\n",vec[i].c_str());
	}
	return 0;
}