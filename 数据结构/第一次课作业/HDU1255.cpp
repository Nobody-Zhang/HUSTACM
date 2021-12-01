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
	double len1,len2;//至少被覆盖一次/两次的长度
}tr[N*8];

int n;
vector <double> ys;

int find(double x)
{
	return lower_bound(ys.begin(),ys.end(),x)-ys.begin();
}

void pushup(int u)
{
	if(tr[u].cnt)
	{
		tr[u].len1=ys[tr[u].r+1]-ys[tr[u].l];
	}
	else if(tr[u].l!=tr[u].r) tr[u].len1=tr[u<<1].len1+tr[u<<1|1].len1;
	else tr[u].len1=0;//前面的操作更新len1（一次被覆盖的长度）
	if(tr[u].cnt>=2)
	{
		tr[u].len2=ys[tr[u].r+1]-ys[tr[u].l];//>=2，说明被完全覆盖过，直接更新
	}
	else if(tr[u].l==tr[u].r) tr[u].len2=0;//如果l=r，活命已经到叶节点（注意这个必须得在if后面的第一个
	else if(tr[u].cnt==1) tr[u].len2=tr[u<<1].len1+tr[u<<1|1].len1;//如果当前被完全覆盖一次，则更新为
	//儿子的至少一次覆盖的面积
	else tr[u].len2=tr[u<<1|1].len2+tr[u<<1].len2;//如果没有被完全覆盖过，则直接用儿子的至少覆盖两次的
	//面积更新
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
	double ans=0;
	for(int i=0;i<2*n;i++)
	{
		if(i) ans+=(double)(seg[i].x-seg[i-1].x)*tr[1].len2;//2代表被完全覆盖两次
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