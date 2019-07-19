/*
ID: zjd32151
TASK: fact4
LANG: C++
*/
//正解
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
const int mul[4] = {6,8,4,2};//8^1,8^2,8^3,8^4
int main(int argc, char const *argv[])
{
	freopen("fact4.in","r",stdin);
	freopen("fact4.out","w",stdout);
	int n;
	cin>>n;
	if(n == 1)
	{
		printf("1\n");
		return 0;
	}
	int ans = 1;
	while(n)
	{
		for(int i = 1;i <= n % 10; ++i)
		{
			if(i != 5)
			{
				ans *= i;
				ans %= 10;
			}
		}
		n /= 5;
		ans *= mul[n % 4];
		ans %= 10;
	}
	cout<<ans<<endl;
	return 0;
}