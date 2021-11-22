#include<bits/stdc++.h>
using namespace std;
const int N=1010;

struct Segment{
	double x,y1,y2;
	int k;
	bool operator <(const Segment &t)const{
		return x<t.x;
	}
}seg[N*2];

struct Node{
	int l,r,cnt;
	double len1,len2;//至少被覆盖一次/两次的
}tr[N*8];

int n;
vector <double> ys;

int find(double x)
{
	return lower_bound(ys.begin(),ys.end(),x)-ys.begin();
}

void pushup(int u)
{
	if(tr[u].cnt>=2)
	{
		tr[u].len2=ys[tr[u].r+1]-ys[tr[u].l];
		tr[u].len1=tr[u].len1;
	}
	else if(tr[u].cnt==1)
	{
		tr[u].len1=ys[tr[u].r+1]-ys[tr[u].l];
		if(tr[u].l!=tr[u].r)
			tr[u].len2=tr[u<<1].len1+tr[u<<1|1].len1;
		else
			tr[u].len2=0;
	}
	else
	{
		tr[u].len2=tr[u<<1].len2+tr[u].len2;//被覆盖两次肯定没有
		if(tr[u].l!=tr[u].r) tr[u].len1=tr[u<<1].len1+tr[u<<1|1].len1;
		else tr[u].len1=0;
	}
}

void build(int u,int l,int r)
{
	tr[u]={l,r,0,0,0};
	if(l!=r)
	{
		int mid=l+r>>1;
		build(u<<1,l,mid);
		build(u<<1|1,mid+1,r);
	}
}

void modify(int u,int l,int r,int k)
{
	if(l<=tr[u].l&&tr[u].r<=r)
	{
		tr[u].cnt+=k;
		pushup(u);
		return;
	}
	int mid=tr[u].l+tr[u].r>>1;
	if(l<=mid) modify(u<<1,l,r,k);
	if(r>mid) modify(u<<1|1,l,r,k);
	pushup(u);
	return;
}
 
void f()
{
	ys.clear();
	scanf("%d",&n);
	for(int i=0,j=0;i<n;i++)
	{
		double x1,x2,y1,y2;
		scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
		seg[j++]={x1,y1,y2,1};seg[j++]={x2,y1,y2,-1};
		ys.push_back(y1);ys.push_back(y2);
	}
	sort(ys.begin(),ys.end());
	ys.erase(unique(ys.begin(),ys.end()),ys.end());
	build(1,0,ys.size()-2);
	sort(seg,seg+2*n);
	double ans=0.0;
	for(int i=0;i<2*n;i++)
	{
		if(i) ans=ans+1.0*(seg[i].x-seg[i-1].x)*tr[1].len2;//2代表被完全覆盖两次
		modify(1,find(seg[i].y1),find(seg[i].y2)-1,seg[i].k);
	}
	printf("%.2lf\n",ans);
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
		f();
	return 0;
}