/*
ID: zjd32151
TASK: msquare
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
const int n = 2,m = 4;
queue< pair< vector< vector<int> >,string> > q;
void A(pair< vector< vector<int> >,string> now)
{
	vector< vector<int> > b;
	b = now.first;
	swap(b[0],b[1]);
	q.push(make_pair(b,now.second + "A"));
}
void B(pair< vector< vector<int> >,string> now)
{
	vector< vector<int> > b;
	b = now.first;
	b[0][0] = now.first[0][3];
	b[0][1] = now.first[0][0];
	b[0][2] = now.first[0][1];
	b[0][3] = now.first[0][2];
	b[1][0] = now.first[1][3];
	b[1][1] = now.first[1][0];
	b[1][2] = now.first[1][1];
	b[1][3] = now.first[1][2];
	q.push(make_pair(b,now.second + "B"));
}
void C(pair< vector< vector<int> >,string> now)
{
	vector< vector<int> > b;
	b = now.first;
	b[0][1] = now.first[1][1];
	b[0][2] = now.first[0][1];
	b[1][1] = now.first[1][2];
	b[1][2] = now.first[0][2];
	q.push(make_pair(b,now.second + "C"));
}
vector< vector<int> > tar;
int check(vector< vector<int> > p)
{
	for(int i = 0;i < n; ++i)
	{
		for(int j = 0;j < m; ++j)
		{
			if(p[i][j] != tar[i][j])
			{
				return 0;
			}
		}
	}
	return 1;
}
char mp[500000];
int aa[10];
int mul(int n)
{
	if(n <= 1)
	{
		return 1;
	}
	if(aa[n])
	{
		return aa[n];
	}
	return aa[n] = n * mul(n - 1);
}
int cnt(vector< vector<int> > p)//康托
{
	int num = 0;
	for(int i = 0;i < n; ++i)
	{
		for(int j = 0;j < m; ++j)
		{
			int s = 0;
			for(int k = j + 1;k < m; ++k)
			{
				if(p[i][j] > p[i][k])
				{
					++s;
				}
			}
			if(i == 0)
			{
				for(int k = 0;k < m; ++k)
				{
					if(p[i][j] > p[1][k])
					{
						++s;
					}
				}
			}
			int cntnow = i * 4 + j + 1;
			num += s * mul(8 - cntnow);
		}
	}
	return num;
}
void bfs()
{
	vector< vector<int> > begins;
	begins.clear();
	begins.resize(2);
	begins[0].push_back(1);
	begins[0].push_back(2);
	begins[0].push_back(3);
	begins[0].push_back(4);
	begins[1].push_back(8);
	begins[1].push_back(7);
	begins[1].push_back(6);
	begins[1].push_back(5);
	q.push(make_pair(begins,""));
	while(!q.empty())
	{
		pair< vector< vector<int> >,string> p = q.front();
		// printf("hello %s\n",p.second.c_str());
		// for(int i = 0;i < n; ++i)
		// {
		// 	for(int j = 0;j < m; ++j)
		// 	{
		// 		printf("%d ",p.first[i][j]);
		// 	}
		// 	printf("\n");
		// }
		// printf("\n");
		// getchar();
		q.pop();
		int index = cnt(p.first);
		if(mp[index])
		{
			continue;
		}
		mp[index] = 1;
		if(check(p.first))
		{
			printf("%d\n%s\n",(int)p.second.size(),p.second.c_str());
			exit(0);
		}
		A(p);
		B(p);
		C(p);
	}
}
int main(int argc, char const *argv[])
{
	freopen("msquare.in","r",stdin);
	freopen("msquare.out","w",stdout);
	tar.clear();
	tar.resize(2);
	for(int i = 0;i < n; ++i)
	{
		for(int j = 0;j < m; ++j)
		{
			int x;
			cin>>x;
			tar[i].push_back(x);
		}
	}
	reverse(tar[1].begin(),tar[1].end());

	bfs();

	printf("NONE\n");
	return 0;
}