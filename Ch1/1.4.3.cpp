/*
ID: zjd32151
TASK: crypt1
LANG: C++
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 15;
int s[maxn];
bool ok(int p)
{
	while(p)
	{
		if(!s[p % 10])
		{
			return 0;
		}
		p /= 10;
	}
	return 1;
}
bool ok2(int n)
{
	return n >= 100 && n <= 999;
}
int main(int argc,char const *argv[])
{
	freopen("crypt1.in","r",stdin);
	freopen("crypt1.out","w",stdout);
	int n;
	cin>>n;
	for(int i = 0;i < n; ++i)
	{
		int x;
		scanf("%d",&x);
		s[x] = 1;
	}
	int cnt = 0;
	for(int i = 100;i <= 999; ++i)
	{
		for(int j = 10;j <= 99; ++j)
		{
			if(ok(i) && ok(j) && ok(i * (j / 10)) && ok(i * (j % 10)) && ok(i * j)
				&& ok2(i * (j / 10)) && ok2(i * (j % 10)))
			{
//				printf("%d * %d = %d\n",i,j,i * j);
				cnt++;
			}
		}
	}
	printf("%d\n",cnt);
	return 0;
}