/*
ID: zjd32151
TASK: fence9
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
int gcd(int a,int b)
{
	return b == 0 ? a : gcd(b,a % b);
}
int main(int argc, char const *argv[])
{
	freopen("fence9.in","r",stdin);
	freopen("fence9.out","w",stdout);
	int n,m,p;
	cin>>n>>m>>p;
	int area = (p * m) / 2;
	int dot_on_edge = gcd(n,m) + gcd(abs(p - n),m) + p;
	printf("%d\n",area - dot_on_edge / 2 + 1);
	return 0;
}