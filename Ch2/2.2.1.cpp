/*
ID: zjd32151
TASK: preface
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
string turn(int num)
{
    string ret;
    const string roman[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
    int value[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
    for(int i = 0;num; ++i)
    {
        while(num >= value[i])
        {
            num -= value[i];
            ret += roman[i];
        }
    }
    return ret;
}
int ans[30];
const string s = "IVXLCDM";
int main(int argc, char const *argv[])
{
    freopen("preface.in","r",stdin);
    freopen("preface.out","w",stdout);
    int n;
    cin>>n;
    for(int i = 1;i <= n; ++i)
    {
        string res = turn(i);
        for(int i = 0;i < res.size(); ++i)
        {
            ans[res[i] - 'A']++;
        }
    }
    for(int i = 0;i < s.size(); ++i)
    {
        if(ans[s[i] - 'A'])
        {
            printf("%c %d\n",s[i],ans[s[i] - 'A']);
        }
    }
    return 0;
}