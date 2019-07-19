/*
ID: zjd32151
TASK: dualpal
LANG: C++
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
vector<int> turn(int n,int i)
{
	vector<int> ret;
	ret.clear();
	while(n)
	{
		ret.push_back(n % i);
		n /= i;
	}
	return ret;//it should be reversed,but the palindrome is the same,so we don't have to
}
bool palindrome(vector<int> d)
{
	vector<int> ns;
	ns = d;
	reverse(ns.begin(),ns.end());
	return ns == d;
}
bool ok(int n)
{
	int cnt = 0;
	for(int i = 2;i <= 10; ++i)
	{
		vector<int> d = turn(n,i);
		if(palindrome(d))
		{
			cnt++;
		}
	}
	if(cnt >= 2)
	{
		printf("%d\n",n);
		return 1;
	}
	return 0;
}
int main(int argc,char const *argv[])
{
	freopen("dualpal.in","r",stdin);
	freopen("dualpal.out","w",stdout);
	int n,s;
	cin>>n>>s;
	for(int i = s + 1;n; ++i)
	{
		if(ok(i))
		{
			n--;
		}
	}
	return 0;
}