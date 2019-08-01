#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
#include <cstring>
using namespace std;
typedef double ld;
const ld PI = acos(-1);
const ld EPS = 1e-8;
const ld inf = 0x3f3f3f3f;
#define zero(x) (((x) > 0) ? (x) : (-(x)) < EPS)
#define _sign(x) ((x) > EPS ? 1 : ((x) < -EPS) ? 2 : 0)
struct point{
	ld x,y;
	point(ld x_ = 0,ld y_ = 0)
	{
		x = x_;
		y = y_;
	}
	void scan()
	{
		scanf("%lf%lf",&x,&y);
	}
	void print()
	{
		printf("***point(%lf,%lf)***\n",x,y);
	}
};
struct line{
	point a,b;
	line(point a_,point b_)
	{
		a = a_;
		b = b_;
	}
	void scan()
	{
		a.scan();
		b.scan();
	}
	void print()
	{
		printf("line::(%lf,%lf)   (%lf,%lf)\n",a.x,a.y,b.x,b.y);
	}
};
ld xmult(point p1,point p2,point p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p1.y - p3.y) * (p2.x - p3.x);
}
ld dis_ptop(point p1,point p2)
{
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
ld area(point p1,point p2,point c)
{
	return fabs(xmult(p1,p2,c)) / 2.0;
}
int same_line(point p1,point p2,point c)
{
	return zero(xmult(p1,p2,c));
}
// int isonseg(point p,line l)
// {
// 	bool sameline = same_line(p,l.a,l.b);
// 	bool inside = ((l.a.x - p.x) * (l.b.x - p.x) < EPS) && ((l.a.y - p.y) * (l.b.y - p.y) < EPS);
// 	return sameline && inside;
// }
int isonseg(point p,line l)
{
	return fabs(dis_ptop(l.a,l.b) - dis_ptop(p,l.a) - dis_ptop(p,l.b)) < EPS;
}
int isonline(point p,line l)
{
	return _sign(xmult(l.a,p,l.b)) == 0;
}
int same_side(point a,point b,line l)
{
	return _sign(xmult(l.a,a,l.b) * xmult(l.a,b,l.b)) == 1;
}
int parallel(line l1,line l2)
{
	return zero((l1.a.x - l1.b.x) * (l2.a.y - l2.b.y) - (l1.a.y - l1.b.y) * (l2.a.x - l2.b.x));
}
int is_convex(vector<point> vp)
{
	int s[3] = {1};
	for(int i = 0;i < vp.size() && (s[1] | s[2]); ++i)
	{
		ld value = xmult(vp[(i + 1) % vp.size()],vp[(i + 2) % vp.size()],vp[i]);
		s[_sign(value)] = 0;
	}
	return s[1] | s[2];
	//如果不允许共线情况,也要加入对s[0]的判断
	//return s[0] && (s[1] | s[2])
}
int inside_convex(point p,vector<point> vp)
{
	//如果边上也算是内部的话，去掉对s[0]的判断
	int s[3] = {1};
	for(int i = 0;i < vp.size() && s[0] && s[1] | s[2]; ++i)
	{
		s[_sign(xmult(vp[(i + 1) % vp.size()],p,vp[i]))] = 0;
	}
	return s[0] && s[1] | s[2];
}
ld dis_ptol(point p,line l)
{
	return fabs(xmult(p,l.a,l.b)) / dis_ptop(l.a,l.b);
}
ld area(vector<point> vp)
{
	ld ret = 0.0;
	for(int i = 0;i < vp.size(); ++i)
	{
		int j = (i + 1) % vp.size();
		ret += vp[i].x * vp[j].y;
		ret -= vp[i].y * vp[j].x;
	}
	return fabs(ret) / 2;
}
ld area_2(vector<point> vp)
{
	ld s1 = 0.0,s2 = 0.0;
	//ld ret = 0.0;
	for(int i = 0;i < vp.size(); ++i)
	{
		s1 += vp[(i + 1) % vp.size()].y * vp[i].x;
		s2 += vp[(i + 1) % vp.size()].y * vp[(i + 2) % vp.size()].x;
		//ret += area(vp[(i + 1) % vp.size()],vp[(i + 2) % vp.size()],vp[i]);
	}
	return fabs(s1 - s2) / 2;
	//return ret;
}
point intersection(line u,line v);
// {
// 	if(parallel(u,v))
// 	{
// 		return point(inf,inf);
// 	}
// 	point ret = u.a;
// 	ld t = ((u.a.x - v.a.x) * (v.a.y - v.b.y) - (u.a.y - v.a.y) * (v.a.x - v.b.x))
// }
ld dis_ptoseg(point p,line l)
{
	point t = p;
	t.x += l.a.y - l.b.y;
	t.y += l.b.x - l.a.x;
	if(same_side(l.a,l.b,line(t,p)))
	{
		return min(dis_ptop(l.a,p),dis_ptop(l.b,p));
	}
	return dis_ptol(p,l);
}
int perpendicular(line l1,line l2)
{
	return zero((l1.a.x - l1.b.x) * (l2.a.x - l2.b.x) + (l1.a.y - l1.b.y) * (l2.a.y - l2.b.y));
}
int opposite_side(point p1,point p2,line l)
{
	return _sign(xmult(l.a,p1,l.b) * xmult(l.a,p2,l.b)) == 2;
}
namespace CountAera{
	const int maxn = 1005;
	struct segtree{
		struct node_for_segtree{
			double x,y1,y2;
			int k;
			node_for_segtree(){};
			node_for_segtree(double a,double b,double c,int kk):x(a),y1(b),y2(c),k(kk){};
			bool operator <(const node_for_segtree &b)const
			{
				return x < b.x;
			}
		};
		node_for_segtree node[maxn << 2];
		double y[maxn << 2],len[maxn << 2];
		int cov[maxn << 2];
		void pushup(int index,int l,int r)
		{
			if(cov[index] > 0)
			{
				len[index] = y[r + 1] - y[l];
			}
			else if(l == r)
			{
				len[index] = 0;
			}
			else
			{
				len[index] = len[index << 1] + len[index << 1 | 1];
			}
		}
		void update(int l,int r,int v,int index,int lnow,int rnow)
		{
			printf("l = %d,r = %d,v = %d,index = %d,lnow = %d,rnow = %d\n",l,r,v,index,lnow,rnow);
			if(l <= lnow && rnow <= r)
			{
				cov[index] += v;
				pushup(index,lnow,rnow);
				return;
			}
			int mid = (lnow + rnow) >> 1;
			if(l <= mid)
			{
				update(l,r,v,index << 1,lnow,mid);
			}
			if(r > mid)
			{
				update(l,r,v,index << 1 | 1,mid + 1,rnow);
			}
			pushup(index,lnow,rnow);
		}
		double CountAera_()
		{
			int n;
			cin>>n;
			double x1,y1,x2,y2;
			int k = 0;
			for(int i = 0;i < n; ++i)
			{
				scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
				y[k] = y1;
				node[k++] = node_for_segtree(x1,y1,y2,1);
				y[k] = y2;
				node[k++] = node_for_segtree(x2,y1,y2,-1);
			}
			sort(y,y + k);
			sort(node,node + k);
			int t = unique(y,y + k) - y;
			printf("t = %d\n",t);
			memset(cov,0x00,sizeof(cov));
			memset(len,0x00,sizeof(len));
			double ans = 0.0;
			for(int i = 0;i < k; ++i)
			{
				int left = lower_bound(y,y + t,node[i].y1) - y;
				int right = lower_bound(y,y + t,node[i].y2) - y;
				printf("left = %d,right = %d\n",left,right);
				update(left,right - 1,node[i].k,1,0,t);
				ans += (node[i + 1].x - node[i].x) * len[1];
			}
			return ans;
		}
	};
	segtree st;
	int main()
	{
		printf("%lf\n",st.CountAera_());
		return 0;
	}
};
namespace Countlen{
	const int maxn = 5005;
	struct segtree{
		int len[maxn << 2],sum[maxn << 2];
		int li[maxn << 2],ri[maxn << 2];
		int num[maxn << 2];
		struct node_{
			int x,y1,y2,k;
			node_(){};
			node_(int a,int b,int c,int d)
			{
				x = a,y1 = b,y2 = c,k = d;
			}
			bool operator <(const node_ &b)const
			{
				return x < b.x;
			}
		};
		node_ node[maxn << 2];
		int y[maxn << 2];
		void pushup(int index,int l,int r)
		{
			if(sum[index] > 0)
			{
				len[index] = y[r + 1] - y[l];
				li[index] = ri[index] = num[index] = 1;
			}
			else if(l == r)
			{
				li[index] = ri[index] = len[index] = num[index] = 0;
			}
			else
			{
				len[index] = len[index << 1] + len[index << 1 | 1];
				num[index] = num[index << 1] + num[index << 1 | 1];
				if(ri[index << 1] == 1 && li[index << 1 | 1] == 1)
				{
					num[index]--;
				}
				li[index] = li[index << 1];
				ri[index] = ri[index << 1 | 1];
			}
		}
		void update(int l,int r,int v,int index,int lnow,int rnow)
		{
			if(l <= lnow && rnow <= r)
			{
				sum[index] += v;
				pushup(index,lnow,rnow);
				return;
			}
			int mid = lnow + rnow >> 1;
			if(l <= mid)
			{
				update(l,r,v,index << 1,lnow,mid);
			}
			if(mid < r)
			{
				update(l,r,v,index << 1 | 1,mid + 1,rnow);
			}
			pushup(index,lnow,rnow);
		}
		int Countlen_(int n)
		{
			int x1,y1,x2,y2;
			int k = 0;
			for(int i = 0;i < n; ++i)
			{
				scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
				y[k] = y1;
				node[k++] = node_(x1,y1,y2,1);
				y[k] = y2;
				node[k++] = node_(x2,y1,y2,-1);
			}
			sort(y,y + k);
			sort(node,node + k);
			node[k].x = node[k - 1].x;
			int t = unique(y,y + k) - y;
			memset(sum,0x00,sizeof(sum));
			memset(len,0x00,sizeof(len));
			memset(num,0x00,sizeof(num));
			memset(li,0x00,sizeof(li));
			memset(ri,0x00,sizeof(ri));
			int ans = 0,last = 0;
			for(int i = 0;i < k; ++i)
			{
				int left = lower_bound(y,y + t,node[i].y1) - y;
				int right = lower_bound(y,y + t,node[i].y2) - y;
				update(left,right - 1,node[i].k,1,0,t);
				ans += abs(len[1] - last) + (node[i + 1].x - node[i].x) * 2 * num[1];
				last = len[1];
			}
			return ans;
		}
	};
	segtree st;
	int main(int n)
	{
		printf("%d\n",st.Countlen_(n));
	}
};
int main(int argc, char const *argv[])
{
	int n;
	cin>>n;
	Countlen::main(n);
	return 0;
}