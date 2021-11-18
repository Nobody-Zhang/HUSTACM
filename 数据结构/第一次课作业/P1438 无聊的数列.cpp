#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;

struct Node{
	int l,r,add,sum;//add tag表示当前的子树里面每个东东都要加上的东西
	//sum表示仅考虑当前的节点和父节点所有的addtag，得到的值
}tr[N*4];
int n,m,a[N];

void pushup(int u)
{
	tr[u].sum=tr[u<<1].sum+tr[u<<1|1].sum;
}

void pushdown(int u)
{
	if(tr[u].add)
	{
		Node &lef=tr[u<<1],&root=tr[u],&rig=tr[u<<1|1];
		lef.add+=root.add,rig.add+=root.add;
		lef.sum=lef.sum+(lef.r-lef.l+1)*root.add;
		rig.sum=rig.sum+(rig.r-rig.l+1)*root.add;
		tr[u].add=0;
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
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	pushup(u);
}

void modify(int u,int l,int r,int k)
{
	if(l<=tr[u].l&&tr[u].r<=r)
	{
		tr[u].add+=k;
		tr[u].sum+=(tr[u].r-tr[u].l+1)*k;
		return;
	}
	pushdown(u);
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid) modify(u<<1,l,r,k);
	if(r>mid) modify(u<<1|1,l,r,k);
	pushup(u);
}

int query(int u,int l,int r)
{
	if(l<=tr[u].l&&tr[u].r<=r)
	{
		return tr[u].sum;
	}
	pushdown(u);
	int mid=tr[u].l+tr[u].r>>1,ans=0;
	if(l<=mid) ans=query(u<<1,l,r);
	if(r>mid) ans+=query(u<<1|1,l,r);
	return ans;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=n;i>=1;i--)
		a[i]-=a[i-1];//进行差分
	
	build(1,1,n);//建线段树
	while(m--)
	{
		int op;
		scanf("%d",&op);
		if(op==1)
		{
			int l,r,k,d;
			scanf("%d%d%d%d",&l,&r,&k,&d);
			modify(1,l,l,k);//l加上k
			if(l+1<=r)modify(1,l+1,r,d);//[l+1,r]加上d,注意判断左右相等or not
			if(r!=n) modify(1,r+1,r+1,-(k+(r-l)*d));
		}
		else
		{
			int p;
			scanf("%d",&p);
			printf("%d\n",query(1,1,p));
		}
	}
	return 0;
}