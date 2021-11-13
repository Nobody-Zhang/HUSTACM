#include<bits/stdc++.h>
using namespace std;
const int N=5*1e5+10;

int a[N],n,m;

long long tr[N];

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
	long long ret=0;
	for(int i=x;i;i-=lowbit(i))
		ret+=tr[i];
	return ret;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	init();
	while(m--)
	{
		int op;
		scanf("%d",&op);
		if(op==1)
		{
			int x,k;
			scanf("%d%d",&x,&k);
			add(x,k);
		}
		else
		{
			int x,y;
			scanf("%d%d",&x,&y);
			printf("%lld\n",query(y)-query(x-1));
		}
	}
	return 0;
}