/*
ID: zjd32151
TASK: lgame
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
char s[10],t[10];
const int score[] = {2,5,4,4,1,6,5,5,7,6,3,5,2,3,5,7,2,1,2,4,6,6,7,5,7};
struct word{
	char cnt[30],sum;
	void make_word(char *p)
	{
		memset(cnt,0x00,sizeof(cnt));
		sum = 0;
		int len = strlen(p);
		for(int i = 0;i < len; ++i)
		{
			cnt[p[i] - 'a']++;
			sum += score[p[i] - 'a'];
		}
	}
	bool operator >(word &b)const
	{
		for(int i = 0;i < 26; ++i)
		{
			if(cnt[i] > b.cnt[i])
			{
				return 1;
			}
		}
		return 0;
	}
	void print()
	{

	}
}p[40005],tar,cur;
int main(int argc, char const *argv[])
{
	FILE *in,*out;
	in = fopen("lgame.in","r");

	fscanf(in,"%s",s);

	tar.make_word(s);
	int n = strlen(s);

	in = fopen("lgame.dict","r");
	int cnt = 0;

	while(fscanf(in,"%s",t) != EOF && t[0] != '.')
	{
		if(strlen(t) > n)
		{
			continue;
		}
		cur.make_word(t);
		if(cur > tar)
		{
			continue;
		}
		p[cnt++] = cur;
	}


	return 0;
}