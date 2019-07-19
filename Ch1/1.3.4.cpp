/*
ID: zjd32151
TASK: palsquare
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
void display(vector<int> d)
{
	reverse(d.begin(),d.end());
	for(int i = 0;i < d.size(); ++i)
	{
		if(d[i] <= 9)
		{
			printf("%d",d[i]);
		}
		else
		{
			printf("%c",(d[i] - 10 + 'A'));
		}
	}
}
int main(int argc,char const *argv[])
{
	 freopen("palsquare.in","r",stdin);
	 freopen("palsquare.out","w",stdout);
	int n;
	cin>>n;
	for(int i = 1;i <= 300; ++i)
	{
		if(palindrome(turn(i * i,n)))
		{
			display(turn(i,n));
			printf(" ");
		    display(turn(i * i,n));
			printf("\n");	
		}
	}
	return 0;
}

