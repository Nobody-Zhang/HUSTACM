#include<bits/stdc++.h>
using namespace std;
const int N=10010;

int a[N][5],n;//用来储存最开始的一抹多东西，直接两次搞一下就可以了

long long ans;//用来储存最后的答案

struct Segment{
	int x,y1,y2,k;
	bool operator < (const Segment &t)const
	{
		return x<t.x;
	}
}seg[N*2];//每个矩形都有左右两个线段

struct Node{
	int l,r,cnt,len;
}tr[N*8];

vector <int> ys;

int find(int y)
{
	return lower_bound(ys.begin(),ys.end(),y)-ys.begin();
}

void pushup(int u)
{
	if(tr[u].cnt) tr[u].len=ys[tr[u].r+1]-ys[tr[u].l];
	else if(tr[u].l==tr[u].r) tr[u].len=0;
	else tr[u].len=tr[u<<1].len+tr[u<<1|1].len;
	return;
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

void build(int u,int l,int r)
{
	tr[u]={l,r,0,0};
	if(l==r) return;
	int mid=l+r>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	return;
}

void f()
{
	for(int i=1,j=0;i<=n;i++)
	{
		int x1,x2,y1,y2;
		x1=a[i][1],y1=a[i][2],x2=a[i][3],y2=a[i][4];
		seg[j++]={x1,y1,y2,1};seg[j++]={x2,y1,y2,-1};
		ys.push_back(y1);ys.push_back(y2);
	}
	sort(ys.begin(),ys.end());
	ys.erase(unique(ys.begin(),ys.end()),ys.end());
	build(1,0,ys.size()-2);
	
	sort(seg,seg+2*n);
	
	for(int i=0;i<2*n;i++)
	{
		int tmp=tr[1].len;
		modify(1,find(seg[i].y1),find(seg[i].y2)-1,seg[i].k);
		ans=(long long)ans+abs(tr[1].len-tmp);
	}
	return;
}

void in()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=4;j++)
			scanf("%d",&a[i][j]);
	return;
}

void rever()
{
	for(int i=1;i<=n;i++)
	{
		swap(a[i][1],a[i][2]);
		swap(a[i][3],a[i][4]);
	}
	return;
}

void clear()
{
	ys.clear();
	for(int i=0;i<2*N;i++) seg[i]={0,0,0,0};
	for(int i=0;i<8*N;i++) tr[i]={0,0,0,0};
	return;
}

int main()
{
	while(cin>>n)
	{
		ans=0;
		clear();
		in();
		f();
		rever();
		clear();
		f();
		cout<<ans<<endl;
	}
	return 0;
}