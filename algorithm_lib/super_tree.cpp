#include <iostream>
#include <stack>
#include <queue>
#include <cstdio>
#include <map>
#include <utility>
using namespace std;
typedef long long ll;
typedef struct Tree{
	int index;
	int value;
	int left;
	int right;
	string ascii;
	bool operator <(const Tree &t)const{
		return value > t.value;
	}
}tree;
tree node[100000];
int node_cnt = 50;
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
void bfs_Huffman(int index)
{
	queue<int> q;
	node[index].ascii = "";
	q.push(index);
	while(!q.empty())
	{
		int cur = q.front();
		q.pop();
		if(node[cur].left == -1 && node[cur].right == -1)
		{
			printf("%c %d %s\n",char(node[cur].index + 'a'),node[cur].value,node[cur].ascii.c_str());
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
	printf("%d:%d\n",index,node[index].value);
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
	printf("%d:%d\n",index,node[index].value);
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
	printf("%d:%d\n",index,node[index].value);
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
			printf("%d:%d\n",index,node[index].value);
			s.push(index);
			index = node[index].left;
		}
		index = node[s.top()].right;
		s.pop();
	}
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
		printf("%d:%d\n",cur,node[cur].value);
		index = node[cur].right;
		s.pop();
	}
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
			printf("%d:%d\n",index,node[index].value);
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
bool find_ancestors(int index,int need)
{
	if(index == -1)
	{
		return 0;
	}
	if(index == need)
	{
		return 1;
	}
	if(find_ancestors(node[index].left,need) || find_ancestors(node[index].right,need))
	{
		printf("%d ",index);
		return 1;
	}
	return 0;
}
void Build_Huffman(vector< pair<char,int> > vp)
{
	priority_queue<tree> pq;
	for(int i = 0;i < vp.size(); ++i)
	{
		int index = vp[i].first - 'a';
		node[index].value = vp[i].second;
		node[index].index = index;
		node[index].left = node[index].right = -1;
		pq.push(node[index]);
	}	
	int rot = 0;
	while(!pq.empty())
	{
		tree left,right;
		left = pq.top();
		pq.pop();
		right = pq.top();
		pq.pop();
		node[node_cnt].value = left.value + right.value;
		node[node_cnt].left = left.index;
		node[node_cnt].right = right.index;
		node[node_cnt].index = node_cnt;
		rot = node[node_cnt].index;
		if(!pq.empty())
		{
			pq.push(node[node_cnt]);
			node_cnt++;
		}
		else
		{
			break;
		}
	}
	printf("root = %d\n",rot);
	bfs_Huffman(rot);
}
/*
6
a 9
b 12
c 6 
d 3
e 5
f 15



7
1 2 3 1
2 4 -1 1
3 5 -1 1
4 -1 6 1
5 -1 -1 1
6 -1 7 1
7 -1 -1 1

7
1 2 3 1
2 4 5 1
3 6 7 1
4 -1 -1 1
5 -1 -1 1
6 -1 -1 1
7 -1 -1 1

3 
68 3 7 1
3 -1 -1 1
7 -1 -1 1
*/




//segment tree

const ll maxn = 100007;

struct segtree{
	ll sum[maxn << 2],add[maxn << 2];//*4
	ll A[maxn];
	ll n;
	void pushup(ll ind)
	{
		sum[ind] = sum[ind << 1] + sum[ind << 1 | 1];
	}
	void pushdown(ll ind,ll leftnum,ll rightnum)
	{
		if(add[ind])
		{
			sum[ind << 1] += leftnum * add[ind];
			sum[ind << 1 | 1] += rightnum * add[ind];
			add[ind << 1] += add[ind];
			add[ind << 1 | 1] += add[ind];
			add[ind] = 0;
		}
	}
	void update(ll c,ll left,ll right,ll start,ll end,ll ind)
	{
		if(left <= start && end <= right)
		{
			sum[ind] += c * (end - start + 1);
			add[ind] += c;
			return;
		}
		ll mid = (start + end) >> 1;
		pushdown(ind,mid - start + 1,end - mid);
		if(left <= mid)
		{
			update(c,left,right,start,mid,ind << 1);
		}
		if(right > mid)
		{
			update(c,left,right,mid + 1,end,ind << 1 | 1);
		}
		pushup(ind);
	}
	void update(ll c,ll index,ll start,ll end,ll ind)
	{
		if(start == end)
		{
			sum[index] += c;
			return;
		}
		ll mid = (start + end) >> 1;
		if(mid >= index)
		{
			update(c,index,start,mid,ind << 1);
		}
		else
		{
			update(c,index,mid + 1,end,ind << 1 | 1);
		}
		pushup(ind);
	}
	void build(ll start,ll end,ll ind)
	{
		if(start == end)
		{
			sum[ind] = A[start];
			return;
		}
		ll mid = (start + end) >> 1;
		build(start,mid,ind << 1);
		build(mid + 1,end,ind << 1 | 1);
		pushup(ind);
	}
	ll query(ll left,ll right,ll start,ll end,ll ind)
	{
		if(left <= start && end <= right)
		{
			return sum[ind];
		}
		if(left > end || right < start)
		{
			return 0;
		}
		ll mid = (start + end) >> 1;
		pushdown(ind,mid - start + 1,end - mid);
		ll ans = 0;
		if(left <= mid)
		{
			ans += query(left,right,start,mid,ind << 1);
		}
		if(mid < right)
		{
			ans += query(left,right,mid + 1,end,ind << 1 | 1);
		}
		return ans;
	}
};
int main(int argc, char const *argv[])
{
	int n;
	/*cin>>n;
	for(int i = 1;i <= n; ++i)
	{
		int x;
		cin>>x;
		node[x].index = x;
		cin>>node[x].left>>node[x].right>>node[x].value;
	}*/
	// printf("preorder:\n");
	// preorder(1);
	// printf("\n");
	// printf("preorder_advance:\n");
	// preorder_advance(1);
	// printf("\n");
	// printf("inorder:\n");
	// inorder(1);
	// printf("\n");
	// printf("inorder_advance:\n");
	// inorder_advance(1);
	// printf("\n");
	// printf("postorder:\n");
	// postorder(1);
	// printf("\n");
	// printf("postorder_advance:\n");
	// postorder_advance(1);
	// printf("\n");
	// bfs(1);
	// cout<<countnode(1);
	// cout<<countleaf(1);
	// int k;
	// cin>>k;
	// mirror(1);
	// for(int i = 1;i <= n; ++i)
	// {
	// 	printf("%d %d %d\n",i,node[i].left,node[i].right);
	// }
	// cout<<finddis(1,5);
	// cout<<judgedirection(1,6)<<endl;
	// cin>>n;
	// for(int i = 0;i < n; ++i)
	// {
	// 	char c;
	// 	int a;
	// 	cin>>c>>a;
	// 	vp.push_back(make_pair(c,a));
	// }
	// Build_Huffman(vp);




	// memset(sum,0x00,sizeof(sum));
	// memset(add,0x00,sizeof(add));
	// long long m;
	// cin>>n>>m;
	// for(long long i = 1;i <= n; ++i)
	// {
	// 	cin>>A[i];
	// }
	// build(1,n,1);
	// while(m--)
	// {
	// 	long long f,x,y,k;
	// 	cin>>f;
	// 	if(f == 1)
	// 	{
	// 		cin>>x>>y>>k;
	// 		update(k,x,y,1,n,1);
	// 	}
	// 	if(f == 2)
	// 	{
	// 		cin>>x>>y;
	// 		printf("%lld\n",query(x,y,1,n,1));
	// 	}
	// }
	return 0;
}