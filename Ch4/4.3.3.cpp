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
// #define DEBUG
#ifdef DEBUG
	#define debug printf
#else
	#define debug(...)
#endif
char s[10],t[10];
string str[40005];
const int score[] = {2,5,4,4,1,6,5,5,1,7,6,3,5,2,3,5,7,2,1,2,4,6,6,7,5,7};
struct word{
	int cnt[30];
	int value;
	void make_word(char *p)
	{
		memset(cnt,0x00,sizeof(cnt));
		value = 0;
		int len = strlen(p);
		for(int i = 0;i < len; ++i)
		{
			cnt[p[i] - 'a']++;
			value += score[p[i] - 'a'];
		}
	}
	bool operator <=(word &b)const
	{
		for(int i = 0;i < 26; ++i)
		{
			if(cnt[i] > b.cnt[i])
			{
				return 0;
			}
		}
		return 1;
	}
}p[40005],tar,cur;
word operator +(word &a,word &b)
{
	word c;
	for(int i = 0;i < 26; ++i)
	{
		c.cnt[i] = a.cnt[i] + b.cnt[i];
	}
	c.value = a.value + b.value;
	return c;
}
vector<string> v;
int main(int argc, char const *argv[])
{
	FILE *in,*out;
	in = fopen("lgame.in","r");

	fscanf(in,"%s",s);

	tar.make_word(s);
	int n = strlen(s);

	in = fopen("lgame.dict","r");
	int m = 0;

	while(fscanf(in,"%s",t) != EOF && t[0] != '.')
	{
		if(strlen(t) > n)
		{
			continue;
		}
		cur.make_word(t);
		if(cur <= tar)
		{
			p[m] = cur;
			str[m++] = t;
		}
	}

	int ans = 0;
	for(int i = 0;i < m; ++i)
	{
		debug("str[%d] = %s,value = %d\n",i,str[i].c_str(),p[i].value);
		ans = max(ans,p[i].value);
	}

	for(int i = 0;i < m; ++i)
	{
		for(int j = i + 1;j < m; ++j)
		{
			word c = p[i] + p[j];
			if(c <= tar)
			{
				ans = max(ans,c.value);
			}
		}
	}

	debug("ans = %d\n",ans);

	for(int i = 0;i < m; ++i)
	{
		if(p[i].value == ans)
		{
			v.push_back(str[i]);
		}
	}

	for(int i = 0;i < m; ++i)
	{
		for(int j = i + 1;j < m; ++j)
		{
			word c = p[i] + p[j];
			if(c <= tar && c.value == ans)
			{
				v.push_back(min(str[i] + " " + str[j],str[j] + " " + str[i]));
			}
		}
	}

	sort(v.begin(),v.end());

	out = fopen("lgame.out","w");
	fprintf(out,"%d\n",ans);
	for(int i = 0;i < v.size(); ++i)
	{
		fprintf(out,"%s\n",v[i].c_str());
	}
	return 0;
}