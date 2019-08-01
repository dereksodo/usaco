#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef unsigned long long ull;
typedef long long ll;
typedef struct point{
	double x,y;
	point(double x = 0,double y = 0):x(x),y(y){};
}Point;
#define sizes(n) (int)n.size()
ld mypow(ld k,int n)
{
	if(n == 0)
	{
		return 1.0;
	}
	else if(n == 1)
	{
		return k;
	}
	ld t = pow(k,n / 2);
	return t * t * pow(k,n % 2);
}
ld mypow2(ld k,int n)
{
	if(n == 0)
	{
		return 1.0;
	}
	ld ans = 1;
	while(n)
	{
		if(n % 2)
		{
			ans *= k;
		}
		k *= k;
		n /= 2;
	}
	return ans;
}
ull mygcd(ull a,ull b)
{
	if(!b)
	{
		return a;
	}
	return mygcd(b,a % b);
}
ull mygcd2(ull a,ull b)
{
	while(b)
	{
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}
ull mylcm(ull a,ull b)
{
	return a * b / mygcd2(a,b);
}
struct Decimal
{
	ll first,second;
	Decimal():first(1),second(1){};
	Decimal(ll x,ll y)
	{
		first = x;
		second = y;
		fix();
	}
	void yuefen()
	{
		ll x = __gcd(first,second);
		first /= x,second /= x;
	}
	Decimal operator +(const Decimal b)const
	{
		ll cur1 = second * b.second;
		ll cur2 = second * b.first + first * b.second;
		return Decimal(cur2,cur1);
	}
	Decimal operator -(const Decimal b)const
	{
		ll cur1 = second * b.second;
		ll cur2 = first * b.second - b.first * second;
		return Decimal(cur2,cur1);
	}
	Decimal operator *(const Decimal b)const
	{
		return Decimal(first * b.first,second * b.second);
	}
	Decimal operator /(const Decimal b)const
	{
		return (*this) * Decimal(b.second,b.first);
	}
	Decimal operator +=(const Decimal b)
	{
		(*this) = (*this) + b;
		return (*this);
	}
	Decimal operator -=(const Decimal b)
	{
		(*this) = (*this) - b;
		return (*this);
	}
	Decimal operator *=(const Decimal b)
	{
		(*this) = (*this) * b;
		return (*this);
	}
	Decimal operator /=(const Decimal b)
	{
		(*this) = (*this) / b;
		return (*this);
	}
	Decimal operator +(ll b)const
	{
		return (*this) + Decimal(b,1ll);
	}
	Decimal operator -(ll b)const
	{
		return (*this) - Decimal(b,1ll);
	}
	Decimal operator *(ll b)const
	{
		return (*this) * Decimal(b,1ll);
	}
	Decimal operator /(ll b)const
	{
		return (*this) / Decimal(b,1ll);
	}
	Decimal operator +=(ll b)
	{
		(*this) = (*this) + b;
		return (*this);
	}
	Decimal operator -=(ll b)
	{
		(*this) = (*this) - b;
		return (*this);
	}
	Decimal operator *=(ll b)
	{
		(*this) = (*this) * b;
		return (*this);
	}
	Decimal operator /=(ll b)
	{
		(*this) = (*this) / b;
		return (*this);
	}
	void fix()
	{
		yuefen();
		if(second < 0)
		{
			second *= -1;
			first *= -1;
		}
		if(second == 0)
		{
			first = 0;
			second = 1;
		}
	}
	void prll()
	{
		cout << "#first = " << first << endl;
		cout << "#second = " << second << endl;
	}
	bool operator <(const Decimal b)const
	{
		return first * b.second < b.first * second;
	}
	bool operator ==(const Decimal b)const
	{
		return first == b.first && second == b.second;
	}
	bool operator <=(const Decimal b)const
	{
		return (*this) < b || (*this) == b;
	}
	bool operator >(const Decimal b)const
	{
		return !((*this) <= b);
	}
	bool operator >=(const Decimal b)const
	{
		return !((*this) < b);
	}
	bool operator !=(const Decimal b)const
	{
		return !((*this) == b);
	}
};
struct Bigint{
	string a;
	int sign;
	Bigint(){};
	Bigint(string b)
	{
		(*this) = b;
	}
	int size()
	{
		return a.size();
	}
	Bigint inverseSign()
	{
		sign *= -1;
		return (*this);
	}
	Bigint normalize(int newSign)
	{
		for(int i = a.size() - 1;i > 0 && a[i] == '0'; --i)
		{
			a.erase(a.begin() + 1);
		}
		sign = (a.size() == 1 && a[0] == '0') ? 1 : newSign;
		return (*this);
	}
	void operator =(string b)
	{
		a = b[0] == '-' ? b.substr(1) : b;
		reverse(a.begin(),a.end());
		this->normalize(b[0] == '-' ? -1 : 1);
	}
	bool operator <(const Bigint &b)const
	{
		if(sign != b.sign)
		{
			return sign < b.sign;
		}
		if(a.size() != b.a.size())
		{
			return sign == -1 ? a.size() < b.a.size() : a.size() > b.a.size();
		}
		for(int i = a.size() - 1;i >= 0; --i)
		{
			if(a[i] != b.a[i])
			{
				return sign == 1 ? a[i] < b.a[i] : a[i] > b.a[i];
			}
		}
		return 0;
	}
	bool operator ==(const Bigint &b)const 
	{
		return a == b.a && sign == b.sign;
	}
	bool operator >(const Bigint &b)const
	{
		return !((*this) < b) && !((*this) == b);
	}
	bool operator <=(const Bigint &b)const
	{
		return !((*this > b));
	}
	bool operator >=(const Bigint &b)const
	{
		return !((*this) < b);
	}
	bool operator !=(const Bigint &b)const
	{
		return !((*this) == b);
	}
	Bigint operator +(Bigint b)
	{
		if(sign != b.sign)
		{
			return (*this) - b.inverseSign();
		}
		Bigint c;
		for(int i = 0,carry = 0;i < a.size() || i < b.size() || carry; ++i)
		{
			carry += (i < a.size() ? a[i] - 48 : 0) + (i < b.size() ? b.a[i] - 48 : 0);
			c.a += (carry % 10 + 48);
			carry /= 10;
		}
		return c.normalize(sign);
	}
	Bigint operator +=(Bigint b)
	{
		(*this) = (*this) + b;
		return (*this);
	}
	Bigint operator -=(Bigint b)
	{
		(*this) = (*this) - b;
		return (*this);
	}
	Bigint operator -(Bigint b)
	{
		if(sign != b.sign)
		{
			return (*this) + b.inverseSign();
		}
		int s = sign;
		sign = b.sign = 1;
		if((*this) < b)
		{
			return ((b - (*this))).inverseSign().normalize(-s);
		}
		Bigint c;
		for(int i = 0,borrow = 0;i < a.size(); ++i)
		{
			borrow = a[i] - borrow - (i < b.size() ? b.a[i] : 48);
			c.a += borrow >= 0 ? borrow + 48 : borrow + 58;
			borrow = borrow >= 0 ? 0 : 1;
		}
		return c.normalize(s);
	}
	Bigint operator *(Bigint b)
	{
		Bigint c("0");
		for(int i = 0,k = a[i] - 48;i < a.size(); ++i,k = a[i] - 48)
		{
			while(k--)
			{
				c += b;
			}
			b.a.insert(b.a.begin(),'0');
		}
		return c.normalize(sign * b.sign);
	}
	Bigint operator /(Bigint b)
	{
		if(b.size() == 1 && b.a[0] == '0')
		{
			b.a[0] /= (b.a[0] - 48);
		}
	}
};
typedef vector<int> lnum;
const int base = 1000;
bool operator <(const lnum &a,const lnum &b)
{
	if(a.size() > b.size())
	{
		return 0;
	}
	else if(a.size() < b.size())
	{
		return 1;
	}
	for(int i = a.size() - 1;i >= 0; --i)
	{
		if(a[i] != b[i])
		{
			return a[i] < b[i];
		}
	}
	return 0;
}
lnum operator +(const lnum &a,const lnum &b)
{
	lnum ret;
	int large = max((int)a.size(),(int)b.size());
	ret.assign(large + 1,0);
	int carry = 0;
	for(int i = 0;i < large || carry; ++i)
	{
		int ai = (i > a.size() - 1 ? 0 : a[i]);
		int bi = (i > b.size() - 1 ? 0 : b[i]);
		ret[i] = ai + bi + carry;
		carry = ret[i] / base;
		ret[i] %= base;
	}
	while(ret.size() > 1 && !ret.back())
	{
		ret.pop_back();
	}
	return ret;
}
lnum operator *(const lnum &a,const lnum &b)
{
	lnum ret;
	ret.assign(a.size() + b.size(),0);
	for(int i = 0;i < a.size(); ++i)
	{
		int carry = 0;
		for(int j = 0;j < b.size() || carry; ++j)
		{
			int bj = (j > b.size() - 1 ? 0 : b[j]);
			ret[i + j] += a[i] * bj + carry;
			carry = ret[i + j] / base;
			ret[i + j] %= base;
		}
	}
	while(ret.size() > 1 && !ret.back())
	{
		ret.pop_back();
	}
	return ret;
}
lnum operator -(const lnum &a,const lnum &b)
{
	lnum ret;
	int large = max((int)a.size(),(int)b.size());
	ret.assign(large,0);
	int carry = 0;
	for(int i = 0;i < large || carry; ++i)
	{
		int ai = (i > a.size() - 1 ? 0 : a[i]);
		int bi = (i > b.size() - 1 ? 0 : b[i]);
		ret[i] = ai - bi - carry;
		if(ret[i] < 0)
		{
			ret[i] += base;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
	}
	while(ret.size() > 1 && !ret.back())
	{
		ret.pop_back();
	}
	return ret;
}
void Print(lnum a)
{
	for(int i = a.size() - 1;i >= 0; --i)
	{
		if(i == a.size() - 1)
		{
			printf("%d",a[i]);
		}
		else
		{
			printf("%03d",a[i]);
		}
	}
	printf("\n");
}
int stringtoint(string s)
{
	int ret = 0;
	for(int i = 0;i < s.size(); ++i)
	{
		ret = ret * 10 + s[i] - '0';
	}
	return ret;
}
lnum fromint(int n)
{
	lnum ret;
	if(!n)
	{
		ret.push_back(0);
		return ret;
	}
	while(n)
	{
		ret.push_back(n % base);
		n /= base;
	}
	return ret;
}
lnum fromstring(string s)
{
	int p__ = 0;
	for(int i = 0;i < s.size(); ++i)
	{
		if(s[i] > '0' && s[i] <= '9')
		{
			p__ = i;
			break;
		}
	}
	s = s.substr(p__);
	int len = s.length();
	int k = len % 3,p = len / 3;
	lnum ret;
	if(k)
	{
		ret.push_back(stringtoint(s.substr(0,k)));
	}
	int pos = k;
	while(p--)
	{
		ret.push_back(stringtoint(s.substr(pos,3)));
		pos += 3;
	}
	reverse(ret.begin(),ret.end());
	return ret;
}
int main(int argc,char const *Argv[])
{
	// freopen("~/Desktop/2018/2018down/7-3/out.txt","w",stdout);
	// ld n;
	// int m;
	// cin>>n>>m;
	// printf("%LF\n",pow(n,m));
	// ull a,b;
	// cin>>a>>b;
	// cout<<gcd(a,b)<<endl;
	// ull n,m;
	// cin>>n>>m;
	// cout<<mylcm(n,m)<<endl;
	//pi -> 180 degree
	//pi / 6 -> 30 degree
	// for(float sita = 0.0;sita <= pi / 2; sita += 0.1)
	// {
	// 	printf("%f\n",tan(sita));
	// }
	// printf("%f\n",tan(pi / 2));
	// printf("%lf\n",area(point(0,1.5),point(0,0),point(2.8,0)));
	lnum a = fromstring("123412341234");
	lnum b = fromstring("12345678");
	Print(a * b);
	return 0;
}