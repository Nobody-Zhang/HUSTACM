#include<bits/stdc++.h>
using namespace std;
const int N=500010;
long long tr[N],a[N];
int n,m;
int lowbit(int x)
{
	return x&-x;
}
void init()
{
	for(int i=1;i<=n;i++)
	{
		tr[i]+=a[i];
		int j=i+lowbit(i);
		if(j<=n) tr[j]+=tr[i];
	}
	return;
}
void add(int x,int k)
{
	for(int i=x;i<=n;i+=lowbit(i))
		tr[i]+=k;
	return;
}
long long query(int x)
{
	long long ans=0;
	for(int i=x;i;i-=lowbit(i))
		ans+=tr[i];
	return ans;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=n;i>=2;i--)
		a[i]-=a[i-1];
	init();
	while(m--)
	{
		int op;
		scanf("%d",&op);
		if(op==1)
		{
			int x,y;long long k;
			cin>>x>>y>>k;
			add(x,k);
			add(y+1,-k);
		}
		else
		{
			int x;
			scanf("%d",&x);
			cout<<query(x)<<endl;
		}
	}
	return 0;
}