/*
ID: zjd32151
TASK: transform
LANG: C++
*/
#include <iostream>
#include <cstring>
using namespace std;
const int maxn = 15;
int n;
struct mat{
	int a[maxn][maxn];
	void display()
	{
		for(int i = 0;i < n; ++i)
		{
			for(int j = 0;j < n; ++j)
			{
				printf("%d",a[i][j]);
			}
			printf("\n");
		}
	}
};
mat pre,des;
void getm()
{
	cin>>n;
	for(int i = 0;i < n; ++i)
	{
		string s;
		cin>>s;
		for(int j = 0;j < n; ++j)
		{
			if(s[j] == '-')
			{
				pre.a[i][j] = 1;
			}
			else
			{
				pre.a[i][j] = 0;
			}
		}
	}
	for(int i = 0;i < n; ++i)
	{
		string s;
		cin>>s;
		for(int j = 0;j < n; ++j)
		{
			if(s[j] == '-')
			{
				des.a[i][j] = 1;
			}
			else
			{
				des.a[i][j] = 0;
			}
		}
	}
}
mat rotate(mat a)
{
	mat ret;
	for(int i = 0;i < n; ++i)
	{
		for(int j = 0;j < n; ++j)
		{
			ret.a[j][n - i - 1] = a.a[i][j];
		}
	}
	return ret;
}
mat rotate(mat a,int t)
{
	if(t == 1)
	{
		return rotate(a);
	}
	else if(t == 2)
	{
		return rotate(rotate(a));
	}
	else
	{
		return rotate(rotate(rotate(a)));
	}
}
mat mirror(mat a)
{
	mat ret;
	for(int i = 0;i < n; ++i)
	{
		for(int j = 0;j < n; ++j)
		{
			ret.a[i][j] = a.a[i][n - j - 1];
		}
	}
	return ret;
}
const bool operator ==(const mat &a,const mat &b)
{
	for(int i = 0;i < n; ++i)
	{
		for(int j = 0;j < n; ++j)
		{
			if(a.a[i][j] != b.a[i][j])
			{
				return 0;
			}
		}
	}
	return 1;
}
int main(int argc,char const *argv[])
{
	freopen("transform.in","r",stdin);
	freopen("transform.out","w",stdout);
	getm();
	if(rotate(pre) == des)
	{
		printf("1\n");
	}
	else if(rotate(pre,2) == des)
	{
		printf("2\n");
	}
	else if(rotate(pre,3) == des)
	{
		printf("3\n");
	}
	else if(mirror(pre) == des)
	{
		printf("4\n");
	}
	else if(mirror(rotate(pre)) == des
			|| mirror(rotate(pre,2)) == des
			|| mirror(rotate(pre,3)) == des)
			{
				printf("5\n");
			}
	else if(pre == des)
	{
		printf("6\n");
	}
	else
	{
		printf("7\n");
	}
	return 0;
}
