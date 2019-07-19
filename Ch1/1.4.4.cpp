/*
ID: zjd32151
TASK: combo
LANG: C++
*/
#include <bits/stdc++.h>
using namespace std;
int a[3],b[3];
int n;
int dis(int c,int d)
{
	if(d >= c)
	{
//		printf("c = %d,d = %d,c + n - d = %d,d - c = %d\n",c,d,c + n - d,d - c);
//		getchar();
		return (min(c + n - d,d - c) <= 2);
	}
	else
	{
		return (min(d + n - c,c - d) <= 2);
	}
}
int ok(int i,int j,int k)
{
	if(i == 0 || j == 0 || k == 0)
	{
		printf("NO\n");
	}
	return (dis(i,a[0]) && dis(j,a[1]) && dis(k,a[2]))
			|| (dis(i,b[0]) && dis(j,b[1]) && dis(k,b[2]));
}
int main(int argc,char const *argv[])
{
	freopen("combo.in","r",stdin);
	freopen("combo.out","w",stdout);
	cin>>n;
	for(int i = 0;i < 3; ++i)
	{
		scanf("%d",a + i);
	}
	for(int i = 0;i < 3; ++i)
	{
		scanf("%d",b + i);
	}
	int ans = 0;
	for(int i = 1;i <= n; ++i)
	{
		for(int j = 1;j <= n; ++j)
		{
			for(int k = 1;k <= n; ++k)
			{
				if(ok(i,j,k))
				{
					ans++;
//					printf("%d %d %d\n",i,j,k);
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}