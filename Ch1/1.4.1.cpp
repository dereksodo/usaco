/*
ID: zjd32151
TASK: milk
LANG: C++
*/
#include <iostream>
#include <algorithm>
using namespace std;
pair<int,int> p[5005];
int main(int argc, char const *argv[])
{
	freopen("milk.in","r",stdin);
	freopen("milk.out","w",stdout);
    int n,m;
    cin>>n>>m;
    for(int i = 0;i < m; ++i)
    {
        cin>>p[i].first>>p[i].second;
    }
    sort(p,p + m);
    int x = 0;
    int now = 0;
    for(int i = 0;i < m; ++i)
    {
        if(now + p[i].second >= n)
        {
            x += (n - now) * p[i].first;
            break;
        }
        else
        {
            x += p[i].second * p[i].first;
            now += p[i].second;
        }
    }
    cout<<x<<endl;
    return 0;
}
