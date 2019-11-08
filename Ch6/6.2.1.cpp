/*
ID: zjd32151
TASK: calfflac
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
const int maxn = 400005;
string a;
char tem[85];
int pos[maxn];
char arr[maxn];
int P[maxn];
int e;
bool isch(char ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}
int manacher()
{
	int len = 2 * e + 1;
	int id = 0,mx = 0;
	int outlen = 0,output = 0;
	for(int i = 1;i <= len; ++i)
	{
		P[i] = (mx > i) ? min(mx - i,P[2 * id - i]) : 0;
		while(arr[i + P[i] + 1] == arr[i - P[i] - 1])
		{
			++P[i];
		}
		if(i + P[i] > mx)
		{
			mx = i + P[i];
			id = i;
		}
		if(P[i] > outlen)
		{
			output = i;
			outlen = P[i];
		}
	}
	return output;
}
int main(int argc, char const *argv[])
{
	freopen("calfflac.in","r",stdin);
	freopen("calfflac.out","w",stdout);
	while(cin.getline(tem,82,'\n') && !cin.eof())
	{
		a += tem;
		a += "\n";
	}
	arr[0] = '$';
	arr[1] = '#';
	for(int i = 0;i < a.size(); ++i)
	{
		if(isch(a[i]))
		{
			pos[e] = i;
			arr[2 * e + 2] = (a[i] <= 'Z' ? 'a' + a[i] - 'A' : a[i]);
			arr[2 * e + 3] = '#';
			++e;
		}
	}
	arr[2 * e + 2] = '$';
	int centre = manacher();
	int st = (centre - P[centre] - 1) / 2;
	int ed = (centre + P[centre] - 3) / 2;
	cout<<P[centre]<<endl;
	for(int i = pos[st];i <= pos[ed]; ++i)
	{
		cout<<a[i];
	}
	cout<<endl;
	return 0;
}