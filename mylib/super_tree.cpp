#include <iostream>
#include <stack>
#include <queue>
#include <cstdio>
#include <map>
#include <utility>
using namespace std;
typedef long long ll;
const int maxn = 100005;
struct tree{
	int index,value,left,right;
	string ascii;
	tree(int a = 0,int v = 0,int l = 0,int r = 0,string asc = "")
	{
		index = a,value = v,left = l,right = r,ascii = asc;
	}
	bool operator <(const tree &t)const{
		return value > t.value;
	}
};
tree node[maxn];
int node_cnt = 0;
vector< pair<char,int> > vp; 
#define max(a,b) (a) > (b) ? (a) : (b)
void build(tree a[],int num)
{
	for(int i = 1;i <= num; ++i)
	{
		node[i].value = a[i].value;
		node[i].left = a[i].left;
		node[i].right = a[i].right;
	}
}
void bfs(int index)
{
	queue<int> q;
	q.push(index);
	while(!q.empty())
	{
		int cur = q.front();
		q.pop();
		printf("%d %d\n",cur,node[cur].value);
		if(node[cur].left != -1)
		{
			q.push(node[cur].left);
		}
		if(node[cur].right != -1)
		{
			q.push(node[cur].right);
		}
	}
}
int countnode(int index)
{
	if(index == -1)
	{
		return 0;
	}
	return countnode(node[index].left) + countnode(node[index].right) + 1;
}
int countleaf(int index)
{
	if(index == -1)
	{
		return 0;
	}
	if(node[index].right == -1 && node[index].left == -1)
	{
		return 1;
	}
	return countleaf(node[index].left) + countleaf(node[index].right);
}
int countdepth(int index)
{
	return index == -1 ? 0 : max(countdepth(node[index].left) + 1,countdepth(node[index].right) + 1);
}
int countdepth_k(int index,int k)
{
	if(index == -1)
	{
		return 0;
	}
	if(k == 1)
	{
		return 1;
	}
	return countdepth_k(node[index].left,k - 1) + countdepth_k(node[index].right,k - 1);
}
void preorder(int index)
{
	printf("(%d,%d) ",index,node[index].value);
	if(node[index].left != -1)
	{
		preorder(node[index].left);
	}
	if(node[index].right != -1)
	{
		preorder(node[index].right);
	}
}
void inorder(int index)
{
	if(node[index].left != -1)
	{
		inorder(node[index].left);
	}
	printf("(%d,%d) ",index,node[index].value);
	if(node[index].right != -1)
	{
		inorder(node[index].right);
	}
}
void postorder(int index)
{
	if(node[index].left != -1)
	{
		postorder(node[index].left);
	}
	if(node[index].right != -1)
	{
		postorder(node[index].right);
	}
	printf("(%d,%d) ",index,node[index].value);
}
void preorder_advance(int index)
{
	stack<int> s;
	printf("%d:%d\n",index,node[index].value);
	s.push(index);
	index = node[index].left;
	while(!s.empty() || index != -1)
	{
		while(index != -1)
		{
			printf("(%d,%d) ",index,node[index].value);
			s.push(index);
			index = node[index].left;
		}
		index = node[s.top()].right;
		s.pop();
	}
	printf("\n");
}
void inorder_advance(int index)
{
	stack<int> s;
	s.push(index);
	index = node[index].left;
	while(!s.empty() || index != -1)
	{
		while(index != -1)
		{
			s.push(index);
			index = node[index].left;
		}
		int cur = s.top();
		printf("(%d,%d) ",cur,node[cur].value);
		index = node[cur].right;
		s.pop();
	}
	printf("\n");
}
void postorder_advance(int index)
{
	stack<int> s;
	s.push(index);
	int flag = 0;
	while(!s.empty())
	{
		if((node[index].right == -1 && node[index].left == -1)
		 || (flag && (flag == node[index].left || flag == node[index].right)))
		{
			printf("(%d,%d) ",index,node[index].value);
			flag = index;
			s.pop();
		}
		else
		{
			if(node[index].right != -1)
			{
				s.push(node[index].right);
			}
			if(node[index].left != -1)
			{
				s.push(node[index].left);
			}
		}
		if(!s.empty())
		{
			index = s.top();
		}
	}
	printf("\n");
}
void mirror(int index)
{
	if(index == -1)
	{
		return;
	}
	swap(node[index].left,node[index].right);
	mirror(node[index].left);
	mirror(node[index].right);
}
int findLCA(int index,int left_index,int right_index)
{
	if(index == -1)
	{
		return -1;
	}
	if(index == left_index || index == right_index)
	{
		return index;
	}
	int left = findLCA(node[index].left,left_index,right_index);
	int right = findLCA(node[index].right,left_index,right_index);
	if(left != -1 && right != -1)
	{
		return index;
	}
	if(left != -1)
	{
		return left;
	}
	if(right != -1)
	{
		return right;
	}
	return -1;
}
int findlevel(int index,int need)
{
	if(index == -1)
	{
		return -1;
	}
	if(index == need)
	{
		return 0;
	}
	int level = findlevel(node[index].left,need);
	if(level == -1)
	{
		level = findlevel(node[index].right,need);
	}
	if(level != -1)
	{
		return level + 1;
	}
	return -1;
}
int finddis(int root,int index1,int index2)
{
	int a = findLCA(root,index1,index2);
	return findlevel(a,index1) + findlevel(a,index2);
}
int judgedirection(int root,int index)
{
	int left = findLCA(root,node[root].left,index);
	if(left != root)
	{
		return 1;
	}
	return -1;
}
int find_ancestors(int index,int need,vector<int> &path)
{
	if(index == -1)
	{
		return 0;
	}
	if(index == need)
	{
		path.push_back(need);
		return 1;
	}
	if(find_ancestors(node[index].left,need,path) || find_ancestors(node[index].right,need,path))
	{
		path.push_back(index);
		return 1;
	}
	return 0;
}
void Huffman(vector< pair<string,int> > vp)
{
	priority_queue<tree> pq;
	for(int i = 1;i < vp.size(); ++i)
	{
		node[i] = tree(i,vp[i].second,-1,-1);
		pq.push(node[i]);
	}
	int rot = 0;
	int cnt = int(vp.size());
	while(!pq.empty())
	{
		tree left,right;
		left = pq.top();
		pq.pop();
		right = pq.top();
		pq.pop();
		node[cnt] = tree(cnt,left.value + right.value,left.index,right.index);
		rot = node[cnt].index;
		if(!pq.empty())
		{
			pq.push(node[cnt++]);
		}
		else
		{
			break;
		}
	}
	queue<int> q;
	q.push(rot);
	while(!q.empty())
	{
		int cur = q.front();
		q.pop();
		if(node[cur].left == -1 && node[cur].right == -1)
		{
			printf("%s->%s\n",vp[node[cur].index].first.c_str(),node[cur].ascii.c_str());
		}
		if(node[cur].left != -1)
		{
			node[node[cur].left].ascii = node[cur].ascii + "0";
			q.push(node[cur].left);
		}
		if(node[cur].right != -1)
		{
			node[node[cur].right].ascii = node[cur].ascii + "1";
			q.push(node[cur].right);
		}
	}
}

//segment tree
namespace segment_tree{
	struct segtree{
		struct node_for_segtree{
			int sum,add;
		};
		node_for_segtree node[maxn];
		int ql,qr;
		void pushup(int index)
		{
			node[index].sum = node[index << 1].sum + node[index << 1 | 1].sum;
		}
		void pushdown(int index,int len)
		{
			if(node[index].add)
			{
				int left_num = len >> 1;
				int right_num = len - left_num;
				node[index << 1].add += node[index].add;
				node[index << 1 | 1].add += node[index].add;
				node[index << 1].sum += node[index].add * left_num;
				node[index << 1 | 1].sum += node[index].add * right_num;
				node[index].add = 0;
			}
		}
		void build(int index,int l,int r)
		{
			if(l == r)
			{
				scanf("%d",&node[index].sum);
				node[index].add = 0;
				return;
			}
			int mid = (l + r) >> 1;
			build(index << 1,l,mid);
			build(index << 1 | 1,mid + 1,r);
			pushup(index);
		}
		void update1(int index,int l,int r,int v)//segment
		{
			if(ql > r || qr < l)
			{
				return;
			}
			if(ql <= l && r <= qr)
			{
				node[index].add += v;
				node[index].sum += (r - l + 1) * v;
				return;
			}
			pushdown(index,r - l + 1);
			int mid = (l + r) >> 1;
			update1(index << 1,l,mid,v);
			update1(index << 1 | 1,mid + 1,r,v);
			pushup(index);
		}
		void update1(int index,int l,int r,int v,int target)//point
		{
			if(l == r)
			{
				if(l == target)
				{
					node[index].sum += v;
				}
				return;
			}
			pushdown(index,r - l + 1);
			int mid = (l + r) >> 1;
			if(index <= mid)
			{
				update1(index << 1,l,mid,v,target);
			}
			else
			{
				update1(index << 1 | 1,mid + 1,r,v,target);
			}
			pushup(index);
		}
		void update2(int index,int l,int r,int v)//segment
		{
			if(ql > r || qr < l)
			{
				return;
			}
			if(ql <= l && r <= qr)
			{
				node[index].add = v;
				node[index].sum = (r - l + 1) * v;
				return;
			}
			pushdown(index,r - l + 1);
			int mid = (l + r) >> 1;
			update2(index << 1,l,mid,v);
			update2(index << 1 | 1,mid + 1,r,v);
			pushup(index);
		}
		void update2(int index,int l,int r,int v,int target)//point
		{
			if(l == r)
			{
				if(l == target)
				{
					node[index].sum = v;
				}
				return;
			}
			pushdown(index,r - l + 1);
			int mid = (l + r) >> 1;
			if(index <= mid)
			{
				update2(index << 1,l,mid,v,target);
			}
			else
			{
				update2(index << 1 | 1,mid + 1,r,v,target);
			}
			pushup(index);
		}
		int query(int index,int l,int r)
		{
			if(ql > r || qr < l)
			{
				return 0;
			}
			if(ql <= l && r <= qr)
			{
				return node[index].sum;
			}
			pushdown(index,r - l + 1);
			int mid = (l + r) >> 1;
			int ans = 0;
			if(ql <= mid)
			{
				ans += query(index << 1,l,mid);
			}
			if(qr > mid)
			{
				ans += query(index << 1 | 1,mid + 1,r);
			}
			return ans;
		}
		void print(int index,int l,int r)
		{
			if(l == r)
			{
				printf("%d ",node[index].sum);
				return;
			}
			pushdown(index,r - l + 1);
			int mid = (l + r) >> 1;
			print(index << 1,l,mid);
			print(index << 1 | 1,mid + 1,r);
		}
	};
	segtree s;
	int ShowMenu()
	{
		printf("----------------------------------\n");
	    printf("|对线段树的操作如下:             |\n");
	    printf("----------------------------------\n");
	    printf("| 1.建立序列	   | 2.单点修改  |\n");
	    printf("| 3.区间修改	   | 4.查询区间和|\n");
	    printf("| 5.打印序列	   | 6.exit      |\n");
		printf("----------------------------------\n");
	    printf("请选择想要进行的操作:\n");
	    int choose;
	    while(cin>>choose)
	    {
	    	if(choose >= 1 || choose <= 6)
	    	{
	    		break;
	    	}
	    }
	    return choose;
	}
	int main()
	{
		printf("Welcome to Segment_tree Space!\n\n");
		int n;
		while(1)
		{
			int c = ShowMenu();
			if(c == 1)
			{
				printf("输入总数\n");
				scanf("%d",&n);
				printf("输入每一个数\n");
				s.build(1,1,n);
				s.ql = s.qr = 0;
			}
			else if(c == 2)
			{
				int ind,flag,x;
				printf("请输入编号\n");
				scanf("%d",&ind);
				printf("请选择:\n	1.加上x\n	2.变成x\n");
				scanf("%d",&flag);
				printf("请输入x\n");
				scanf("%d",&x);
				if(flag == 1)
				{
					s.update1(1,1,n,x,ind);
				}
				else if(flag == 2)
				{
					s.update2(1,1,n,x,ind);
				}
				else
				{
					printf("无法识别\n");
					continue;
				}
			}
			else if(c == 3)
			{
				int flag,x;
				printf("请输入左端点,右端点\n");
				scanf("%d%d",&s.ql,&s.qr);
				printf("请选择:\n	1.都加上x\n	2.都变成x\n");
				scanf("%d",&flag);
				printf("请输入x\n");
				scanf("%d",&x);
				if(flag == 1)
				{
					s.update1(1,1,n,x);
				}
				else if(flag == 2)
				{
					s.update2(1,1,n,x);
				}
				else
				{
					printf("无法识别\n");
					continue;
				}
			}
			else if(c == 4)
			{
				printf("请输入左端点,右端点\n");
				scanf("%d%d",&s.ql,&s.qr);
				printf("%d\n",s.query(1,1,n));
			}
			else if(c == 5)
			{
				s.print(1,1,n);
				printf("\n");
			}
			else
			{
				printf("\nGoodbye\n");
				return 0;
			}
		}
	}
};

namespace bst{
	struct splay{
		int ch[maxn][2],fa[maxn],siz[maxn];
		int cnt[maxn],key[maxn],root,sz;
		int get(int x)
		{
			return ch[fa[x]][1] == x;
		}
		void clear(int x)
		{
			ch[x][0] = ch[x][1] = siz[x] = fa[x] = cnt[x] = key[x] = 0;
		}
		void update(int x)
		{
			if(x)
			{
				siz[x] = cnt[x];
			}
			if(ch[x][0])
			{
				siz[x] += siz[ch[x][0]];
			}
			if(ch[x][1])
			{
				siz[x] += siz[ch[x][1]];
			}
		}
		void rotate(int x,int &k)
		{
			int old = fa[x],oldf = fa[old];
			int which = get(x);
			if(old == k)
			{
				k = x;
			}
			else
			{
				if(ch[oldf][0] == old)
				{
					ch[oldf][0] = x;
				}
				else
				{
					ch[oldf][1] = x;
				}
			}
			ch[old][which] = ch[x][which ^ 1];
			fa[ch[old][which]] = old;
			fa[old] = x;
			ch[x][which ^ 1] = old;
			fa[x] = oldf;
			update(old);
			update(x);
		}
		void splay_(int x,int &k)
		{
			while(x != k)
			{
				int old = fa[x],oldf = fa[old];
				if(old != k)
				{
					if((ch[old][0] == x) ^ (ch[oldf][0] == old))
					{
						rotate(x,k);
					}
					else
					{
						rotate(old,k);
					}
				}
				rotate(x,k);
			}
		}
		void insert(int v)
		{
			if(root == 0)
			{
				sz++;
				ch[sz][0] = ch[sz][1] = fa[sz] = 0;
				key[sz] = v;
				cnt[sz] = siz[sz] = 1;
				root = sz;
				return;
			}
			int now = root,f = 0;
			while(1)
			{
				if(key[now] == v)
				{
					cnt[now]++;
					update(now);
					update(f);
					splay_(now,root);
					break;
				}
				f = now;
				now = ch[now][key[now] < v];
				if(now == 0)
				{
					sz++;
					ch[sz][0] = ch[sz][1] = 0;
					key[sz] = v;
					siz[sz] = cnt[sz] = 1;
					fa[sz] = f;
					ch[f][key[f] < v] = sz;
					update(f);
					splay_(sz,root);
					break;
				}
			}
		}
		int find(int v)
		{
			int ans = 0,now = root;
			while(1)
			{
				if(v < key[now])
				{
					now = ch[now][0];
				}
				else
				{
					ans += (ch[now][0] ? siz[ch[now][0]] : 0);
					if(v == key[now])
					{
						splay_(now,root);
						return ans + 1;
					}
					ans += cnt[now];
					now = ch[now][1];
				}
			}
		}
		int findx(int x)
		{
			int now = root;
			while(1)
			{
				if(ch[now][0] && x <= siz[ch[now][0]])
				{
					now = ch[now][0];
				}
				else
				{
					int temp = (ch[now][0] ? siz[ch[now][0]] : 0) + cnt[now];
					if(x <= temp)
					{
						return key[now];
					}
					x -= temp;
					now = ch[now][1];
				}
			}
		}
		int pre()//return an index
		{
			int now = ch[root][0];
			while(ch[now][1])
			{
				now = ch[now][1];
			}
			return now;
		}
		int nxt()//return an index
		{
			int now = ch[root][1];
			while(ch[now][0])
			{
				now = ch[now][0];
			}
			return now;
		}
		void del(int x)
		{
			find(x);
			if(cnt[root] > 1)
			{
				cnt[root]--;
				update(root);
				return;
			}
			if(!ch[root][0] && !ch[root][1])
			{
				clear(root);
				root = 0;
				return;
			}
			if(!ch[root][0])
			{
				int oldroot = root;
				root = ch[root][1];
				fa[root] = 0;
				clear(oldroot);
				return;
			}
			else if(!ch[root][0])
			{
				int oldroot = root;
				root = ch[root][0];
				fa[root] = 0;
				clear(oldroot);
				return;
			}
			int leftbig = pre(),oldroot = root;
			splay_(leftbig,root);
			fa[ch[oldroot][1]] = root;
			ch[root][1] = ch[oldroot][1];
			clear(oldroot);
			update(root);
		}
	};
	struct splay_2{
		struct node_for_splay_2{
		int ch[2],fa,siz,cnt,key;
		};
		int root,sz;
		node_for_splay_2 s[maxn];
		int get(int x)
		{
			return s[s[x].fa].ch[1] == x;
		}
		void clear(int x)
		{
			s[x].ch[0] = s[x].ch[1] = s[x].siz = s[x].fa = s[x].cnt = s[x].key = 0;
		}
		void update(int x)
		{
			if(x)
			{
				s[x].siz = s[x].cnt;
			}
			if(s[x].ch[0])
			{
				s[x].siz += s[s[x].ch[0]].siz;
			}
			if(s[x].ch[1])
			{
				s[x].siz += s[s[x].ch[1]].siz;
			}
		}
		void rotate(int x,int &k)
		{
			int old = s[x].fa,oldf = s[old].fa;
			int which = get(x);
			if(old == k)
			{
				k = x;
			}
			else
			{
				if(s[oldf].ch[0] == old)
				{
					s[oldf].ch[0] = x;
				}
				else
				{
					s[oldf].ch[1] = x;
				}
			}
			s[old].ch[which] = s[x].ch[which ^ 1];
			s[s[old].ch[which]].fa = old;
			s[old].fa = x;
			s[x].ch[which ^ 1] = old;
			s[x].fa = oldf;
			update(old);
			update(x);
		}
		void splay_(int x,int &k)
		{
			while(x != k)
			{
				int old = s[x].fa,oldf = s[old].fa;
				if(old != k)
				{
					if((s[old].ch[0] == x) ^ (s[oldf].ch[0] == old))
					{
						rotate(x,k);
					}
					else
					{
						rotate(old,k);
					}
				}
				rotate(x,k);
			}
		}
		void insert(int v)
		{
			if(root == 0)
			{
				sz++;
				s[sz].ch[0] = s[sz].ch[1] = s[sz].fa = 0;
				s[sz].key = v;
				s[sz].cnt = s[sz].siz = 1;
				root = sz;
				return;
			}
			int now = root,f = 0;
			while(1)
			{
				if(s[now].key == v)
				{
					s[now].cnt++;
					update(now);
					update(f);
					splay_(now,root);
					break;
				}
				f = now;
				now = s[now].ch[s[now].key < v];
				if(now == 0)
				{
					sz++;
					s[sz].ch[0] = s[sz].ch[1] = 0;
					s[sz].key = v;
					s[sz].siz = s[sz].cnt = 1;
					s[sz].fa = f;
					s[f].ch[s[f].key < v] = sz;
					update(f);
					splay_(sz,root);
					break;
				}
			}
		}
		int find(int v)
		{
			int ans = 0,now = root;
			while(1)
			{
				if(v < s[now].key)
				{
					now = s[now].ch[0];
				}
				else
				{
					ans += (s[now].ch[0] ? s[s[now].ch[0]].siz : 0);
					if(v == s[now].key)
					{
						splay_(now,root);
						return ans + 1;
					}
					ans += s[now].cnt;
					now = s[now].ch[1];
				}
			}
		}
		int findx(int x)
		{
			int now = root;
			while(1)
			{
				if(s[now].ch[0] && x <= s[s[now].ch[0]].siz)
				{
					now = s[now].ch[0];
				}
				else
				{
					int temp = (s[now].ch[0] ? s[s[now].ch[0]].siz : 0) + s[now].cnt;
					if(x <= temp)
					{
						return s[now].key;
					}
					x -= temp;
					now = s[now].ch[1];
				}
			}
		}
		int pre()//return an index
		{
			int now = s[root].ch[0];
			while(s[now].ch[1])
			{
				now = s[now].ch[1];
			}
			return now;
		}
		int nxt()//return an index
		{
			int now = s[root].ch[1];
			while(s[now].ch[0])
			{
				now = s[now].ch[0];
			}
			return now;
		}
		void del(int x)
		{
			find(x);
			if(s[root].cnt > 1)
			{
				s[root].cnt--;
				update(root);
				return;
			}
			if(!s[root].ch[0] && !s[root].ch[1])
			{
				clear(root);
				root = 0;
				return;
			}
			if(!s[root].ch[0])
			{
				int oldroot = root;
				root = s[root].ch[1];
				s[root].fa = 0;
				clear(oldroot);
				return;
			}
			else if(!s[root].ch[0])
			{
				int oldroot = root;
				root = s[root].ch[0];
				s[root].fa = 0;
				clear(oldroot);
				return;
			}
			int leftbig = pre(),oldroot = root;
			splay_(leftbig,root);
			s[s[oldroot].ch[1]].fa = root;
			s[root].ch[1] = s[oldroot].ch[1];
			clear(oldroot);
			update(root);
		}
	};
	splay sp;
	int ShowMenu()
	{
		printf("----------------------------------------\n");
	    printf("|对二叉查找树的操作如下:               |\n");
	    printf("----------------------------------------\n");
	    printf("| 1.插入           | 2.删除            |\n");
	    printf("| 3.询问排名       | 4.查询排名为x的数 |\n");
	    printf("| 5.求x的前驱      | 6.求x的后继       |\n");
		printf("| 7.exit			       |\n");
		printf("----------------------------------------\n");
	    printf("请选择想要进行的操作:\n");
	    int choose;
	    while(cin>>choose)
	    {
	    	if(choose >= 1 || choose <= 7)
	    	{
	    		break;
	    	}
	    }
	    return choose;
	}
	int main()
	{
		printf("Welcome to BST Space!\n\n");
		while(1)
		{
			int c = ShowMenu();
			if(c == 1)
			{
				printf("请输入插入值\n");
				int x;
				scanf("%d",&x);
				sp.insert(x);
			}
			else if(c == 2)
			{
				printf("请输入删除值\n");
				int x;
				scanf("%d",&x);
				sp.del(x);
			}
			else if(c == 3)
			{
				printf("请输入询问值\n");
				int x;
				scanf("%d",&x);
				printf("%d\n",sp.find(x));
			}
			else if(c == 4)
			{
				printf("请输入询问值\n");
				int x;
				scanf("%d",&x);
				printf("%d\n",sp.findx(x));
			}
			else if(c == 5)
			{
				printf("请输入询问值\n");
				int x;
				scanf("%d",&x);
				sp.insert(x);
				printf("%d\n",sp.key[sp.pre()]);
				sp.del(x);
			}
			else if(c == 6)
			{
				printf("请输入询问值\n");
				int x;
				scanf("%d",&x);
				sp.insert(x);
				printf("%d\n",sp.key[sp.nxt()]);
				sp.del(x);
			}
			else
			{
				printf("\nGoodbye\n");
				return 0;
			}
		}
	}
};
int ShowMenu()
{
	printf("----------------------------------------------\n");
    printf("|对树的操作如下:                             |\n");
    printf("----------------------------------------------\n");
    printf("| 1.进入线段树空间   | 2.进入二叉查找树空间  |\n");
    printf("| 3.建立树           | 4.求霍夫曼编码        |\n");
    printf("| 5.求节点个数       | 6.求先序遍历	     |\n");
    printf("| 7.求后序遍历       | 8.求中序遍历	     |\n");
    printf("| 9.求子树最大深度   | 10.求第k层子树节点个数|\n");
    printf("| 11.求叶子结点个数  | 12.翻转子树	     |\n");
    printf("| 13.求节点深度      | 14.求LCA              |\n");
    printf("| 15.求两个节点的距离| 16.求节点到根的路径   |\n");
    printf("| 17.求节点的方向    | 18.exit         	     |\n");
	printf("----------------------------------------------\n");
    printf("请选择想要进行的操作:\n");
    int choose;
    while(cin>>choose)
    {
    	if(choose >= 1 || choose <= 18)
    	{
    		break;
    	}
    }
    return choose;
}
int main(int argc, char const *argv[])
{
	printf("Welcome to Tree Space!\n\n");
	int n;
	while(1)
	{
		int c = ShowMenu();
		if(c == 1)
		{
			segment_tree::main();
		}
		else if(c == 2)
		{
			bst::main();
		}
		else if(c == 3)
		{
			tree a[maxn];
			printf("输入节点个数\n");
			cin>>n;
			printf("输入节点值,左儿子编号,右儿子编号\n");
			for(int i = 1;i <= n; ++i)
			{
				a[i].index = i;
				scanf("%d%d%d",&a[i].value,&a[i].left,&a[i].right);
			}
			build(a,n);
		}
		else if(c == 4)
		{
			printf("输入节点个数\n");
			cin>>n;
			vector< pair<string,int> > vp(n + 1);
			printf("输入字符(串),频率\n");
			for(int i = 1;i <= n; ++i)
			{
				cin>>vp[i].first>>vp[i].second;
			}
			Huffman(vp);
		}
		else if(c == 5)
		{
			printf("输入根节点\n");
			int rt;
			cin>>rt;
			printf("%d\n",countnode(rt));
		}
		else if(c == 6)
		{
			printf("输入根节点\n");
			int rt;
			cin>>rt;
			preorder(rt);
			printf("\n");
		}
		else if(c == 7)
		{
			printf("输入根节点\n");
			int rt;
			cin>>rt;
			postorder(rt);
			printf("\n");
		}
		else if(c == 8)
		{
			printf("输入根节点\n");
			int rt;
			cin>>rt;
			inorder(rt);
			printf("\n");
		}
		else if(c == 9)
		{
			printf("输入根节点\n");
			int rt;
			cin>>rt;
			printf("%d\n",countdepth(rt));
		}
		else if(c == 10)
		{
			printf("输入根节点,层数\n");
			int rt,k;
			cin>>rt>>k;
			printf("%d\n",countdepth_k(rt,k));
		}
		else if(c == 11)
		{
			printf("输入根节点\n");
			int rt;
			cin>>rt;
			printf("%d\n",countleaf(rt));
		}
		else if(c == 12)
		{
			printf("输入根节点\n");
			int rt;
			cin>>rt;
			mirror(rt);
		}
		else if(c == 13)
		{
			printf("输入根节点,要查询的节点\n");
			int rt,k;
			cin>>rt>>k;
			printf("%d\n",findlevel(rt,k));
		}
		else if(c == 14)
		{
			printf("输入两个节点\n");
			int node1,node2;
			cin>>node1>>node2;
			printf("%d\n",findLCA(1,node1,node2));
		}
		else if(c == 15)
		{
			printf("输入两个节点,根\n");
			int node1,node2,rt;
			cin>>node1>>node2>>rt;
			printf("%d\n",finddis(rt,node1,node2));
		}
		else if(c == 16)
		{
			printf("输入根,要查询的节点\n");
			int rt,k;
			cin>>rt>>k;
			vector<int> v;
			v.clear();
			if(find_ancestors(rt,k,v))
			{
				while(!v.empty())
				{
					printf("%d ",v.back());
					v.pop_back();
				}
				printf("\n");
			}
			else
			{
				printf("No Such Path!\n");
			}
		}
		else if(c == 17)
		{
			printf("输入根,要查询的节点\n");
			int rt,k;
			cin>>rt>>k;
			printf("%s\n",judgedirection(rt,k) == 1 ? "left" : "right");
		}
		else
		{
			printf("\nGoodbye\n");
			break;
		}
	}
	return 0;
}