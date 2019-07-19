/*
ID: zjd32151
TASK: friday
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
int a[10];
int month_[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
int print_[] = {6,7,1,2,3,4,5};
int leap(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}
int query(int year,int month)
{
	if(leap(year))
	{
		if(month == 2)
		{
			return 29;
		}
	}
	return month_[month];
}
int main(int argc, char const *argv[])
{
	// freopen("friday.in","r",stdin);
	// freopen("friday.out","w",stdout);
	int n;
	cin>>n;
	int year = 1900,month = 1,date = 0;
	int day = 0;
	while(1)
	{
		if(year == 1900 + n)
		{
			break;
		}
		if(date == 13)
		{
			a[day]++;
		}
		if(month == 12 && date == 31)
		{
			year++;
			month = 1;
			date = 1;
			// printf("year = %d,month = %d,date = %d,day = %d\n",year,month,date,day);
			// getchar();
		}
		else if(query(year,month) == date)
		{
			month++;
			date = 1;
		}
		else
		{
			date++;
		}
		day++;
		if(day == 8)
		{
			day = 1;
		}
		// printf("year = %d,month = %d,date = %d,day = %d\n",year,month,date,day);
		// getchar();
	}
	for(int i = 0;i < 6; ++i)
	{
		printf("%d ",a[print_[i]]);
	}
	printf("%d\n",a[print_[6]]);
	return 0;
}