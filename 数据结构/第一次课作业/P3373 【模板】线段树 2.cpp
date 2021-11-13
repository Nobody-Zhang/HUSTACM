#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N=1e5+10;

struct Node{
	int l,r;
	LL sum,add,mul;
	Node()
	{
		l=r=0;sum=add=0;mul=1;
	}
}tr[N*4];
int p,n,m;
LL a[N];

void eval(int u,LL add,LL mul)
{
	tr[u].sum=(LL) (tr[u].sum*mul)+add*(tr[u].r-tr[u].l+1);
	tr[u].mul=(LL) tr[u].mul*mul;
	tr[u].add=(LL) tr[u].add*mul+add;
	tr[u].sum%=p; tr[u].add%=p; tr[u].mul%=p;
	return;
}

void pushup(int u)
{
	tr[u].sum=tr[u<<1].sum+tr[u<<1|1].sum;
}

void pushdown(int u)
{
	auto &root=tr[u],&lef=tr[u<<1],&rig=tr[u<<1|1];
	if(root.mul!=1||root.add!=0)
	{
		eval(u<<1,root.add,root.mul);
		eval(u<<1|1,root.add,root.mul);
		root.mul=1;root.add=0;
	}
}

void build(int u,int l,int r)
{
	tr[u].l=l,tr[u].r=r;
	if(l==r)
	{
		tr[u].sum=a[l];
		return;
	}
	int mid=l+r>>1;
	build(u<<1,l,mid); build(u<<1|1,mid+1,r);
	pushup(u);
	return;
}

void modify(int u,int x,int y,LL add,LL mul)
{
	int l=tr[u].l,r=tr[u].r;
	if(x<=l&&r<=y)
	{
		eval(u,add,mul);
		return;
	}
	pushdown(u);
	int mid=l+r>>1;
	if(x<=mid) modify(u<<1,x,y,add,mul);
	if(y>mid) modify(u<<1|1,x,y,add,mul);
	pushup(u);
}

LL query(int u,int x,int y)
{
	int l=tr[u].l,r=tr[u].r;
	if(x<=l&&r<=y)
	{
		return tr[u].sum;
	}
	pushdown(u);
	int mid=l+r>>1;
	LL ans=0;
	if(x<=mid) ans=query(u<<1,x,y);
	if(y>mid)  ans+=query(u<<1|1,x,y);
	ans%=p;
	return ans;
}

int main()
{
	cin.tie(0); ios::sync_with_stdio(false);
	cin>>n>>m>>p;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	build(1,1,n);
	while(m--)
	{
		int x,y,op;
		cin>>op>>x>>y;
		if(op==1)
		{
			LL k;
			cin>>k;
			modify(1,x,y,0,k);
		}
		else if(op==2)
		{
			LL k;
			cin>>k;
			modify(1,x,y,k,1);
		}
		else cout<<query(1,x,y)<<endl;
	}
	return 0;
}