/*
ID: zjd32151
TASK: zerosum
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
int n;
string s;
set<string> ans;
bool ok()
{
    int sum = 0;
    int num = 0;
    vector<int> v;
    for(int i = 0;i < s.size(); ++i)
    {
        if(isdigit(s[i]))
        {
            num = num * 10 + s[i] - '0';
        }
        if(s[i] == '+' || s[i] == '-')
        {
            v.push_back(num);
            num = 0;
        }
    }
    v.push_back(num);
    sum += v[0];
    int pos = 1;
    for(int i = 0;i < s.size(); ++i)
    {
        if(s[i] == '+')
        {
            sum += v[pos++];
        }
        if(s[i] == '-')
        {
            sum -= v[pos++];
        }
    }
    return sum == 0;
}
void dfs(int pos)
{
    if(pos >= 2 * n - 2)
    {
        if(ok())
        {
            ans.insert(s);
        }
        return;
    }
    s[pos] = '+';
    dfs(pos + 2);
    s[pos] = '-';
    dfs(pos + 2);
    s[pos] = ' ';
    dfs(pos + 2);
}
int main(int argc, char const *argv[])
{
    freopen("zerosum.in","r",stdin);
    freopen("zerosum.out","w",stdout);
    cin>>n;
    for(int i = 1;i <= n; ++i)
    {
        s += char(i + '0');
        s += " ";
    }
    s.pop_back();
    dfs(1);
    for(set<string>::iterator iter = ans.begin();iter != ans.end(); ++iter)
    {
        printf("%s\n",iter->c_str());
    }
    return 0;
}