#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1e5+10;

struct tree
{
	int left,right;
	LL sum,add;
}tr[4*N];
int a[N];

void pushup(int u)
{
	tr[u].sum=tr[u<<1].sum+tr[u<<1|1].sum;
	return;
}

void pushdown(int u)
{
	auto &root=tr[u],&l=tr[u<<1],&r=tr[u<<1|1];
	if(root.add)
	{
		l.add+=root.add; l.sum+=(LL)(l.right-l.left+1)*root.add;
		r.add+=root.add; r.sum+=(LL)(r.right-r.left+1)*root.add;
		root.add=0;
	}
}

void modify(int u,int x,int y,int k)
{
	int l=tr[u].left,r=tr[u].right;
	if(x<=l&&r<=y)
	{
		tr[u].sum+=(LL)(r-l+1)*k;
		tr[u].add+=k;
	}
	else
	{
		pushdown(u);
		int mid=l+r>>1;
		if(x<=mid) modify(u<<1,x,y,k);
		if(y>mid) modify(u<<1|1,x,y,k);
		pushup(u);
	}
}

LL query(int u,int x,int y)
{//目前是u节点，
	int l=tr[u].left,r=tr[u].right;
	if(x<=l&&r<=y) return tr[u].sum;
	LL sum=0;int mid=l+r>>1;
	pushdown(u);
	if(x<=mid) sum=query(u<<1,x,y);
	if(y>mid) sum+=query(u<<1|1,x,y);
	return sum;
}

void build(int u,int l,int r)
{
	if(l==r)
	{
		tr[u].left=l,tr[u].right=r,tr[u].sum=a[l];
		return;
	}
	tr[u]={l,r};
	int mid=l+r>>1;
	build(u<<1,l,mid);build(u<<1|1,mid+1,r);
	pushup(u);
	return;
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(1,1,n);
	while(m--)
	{
		int op,x,y,k;
		scanf("%d%d%d",&op,&x,&y);
		if(op==1)
		{//[x,y]+=k;
			scanf("%d",&k);
			modify(1,x,y,k);
		}
		else
		{
			printf("%lld\n",query(1,x,y));
		}
	}
	return 0;
}