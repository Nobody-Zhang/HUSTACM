#include<bits/stdc++.h>
using namespace std;

const int N=10010;

int n;

struct Segment{
	double x,y1,y2;
	int k;
	bool operator < (const Segment &t)const
	{
		return x<t.x;
	}
}seg[N*2];

struct Node{
	int l,r;
	double len;
	int cnt;
}tr[N*8];

vector <double> ys;

int find(double y)
{
	return lower_bound(ys.begin(),ys.end(),y)-ys.begin();
}

void pushup(int u)
{
	if(tr[u].cnt)
	{//如果
		tr[u].len=ys[tr[u].r+1]-ys[tr[u].l];
	}
	else if(tr[u].l!=tr[u].r)
	{
		tr[u].len=tr[u<<1].len+tr[u<<1|1].len;
	}
	else
	{
		tr[u].len=0;
	}
}

void build(int u,int l,int r)
{
	tr[u]={l,r,0,0};
	if(l!=r)
	{
		int mid=l+r>>1;
		build(u<<1,l,mid);
		build(u<<1|1,mid+1,r);
	}
}

void modify(int u,int l,int r,int k)
{
	int lef=tr[u].l,rig=tr[u].r;
	if(l<=lef&&rig<=r)
	{
		tr[u].cnt+=k;
		pushup(u);
		return;
	}
	int mid=lef+rig>>1;
	if(l<=mid) modify(u<<1,l,r,k);
	if(r>mid) modify(u<<1|1,l,r,k);
	pushup(u);
	return;
}

int main()
{
	int T=1;
	while(scanf("%d",&n),n)
	{
		ys.clear();
		for(int i=0,j=0;i<n;i++)
		{
			double x1,x2,y1,y2;
			scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
			seg[j++]={x1,y1,y2,1};seg[j++]={x2,y1,y2,-1};
			ys.push_back(y1); ys.push_back(y2);
		}
		sort(ys.begin(),ys.end());
		ys.erase(unique(ys.begin(), ys.end()), ys.end());//去重，防止过度建点
		build(1,0,ys.size()-2);//-1是因为从1开始，再-1是因为从点要到线段
		
		sort(seg,seg+2*n);//从0到2n([0,2n-1])有数据
		double ans=0;
		for(int i=0;i<2*n;i++)
		{//所有的
			if(i>0) ans=ans+(double)(seg[i].x-seg[i-1].x)*tr[1].len;
			modify(1,find(seg[i].y1),find(seg[i].y2)-1,seg[i].k);
		}
		printf("Test case #%d\n",T++);
		printf("Total explored area: %.2lf\n",ans);
		printf("\n");
	}
	return 0;
}