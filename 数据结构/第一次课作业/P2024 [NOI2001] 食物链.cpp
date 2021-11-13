#include<bits/stdc++.h>
using namespace std;
const int N=101;
int f[N],len[N];
int find(int x)
{
	if(x==f[x]) return x;
	int r=find(f[x]);
	len[x]=len[x]+len[f[x]];
	f[x]=r;
	return r;
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)	
		f[i]=i;
	int t=0;
	while(m--)
	{
		int x,y,op;
		scanf("%d%d%d",&op,&x,&y);
		if(x>n||y>n)
		{
			t++;continue;
		}
		int fx=find(x),fy=find(y);
		if(op==1)
		{
			if(fx!=fy)
			{
				f[fx]=fy;
				len[fx]=len[y]-len[x];
			}
			else
			{
				if((len[x]-len[y])%3!=0) t++;
			}
		}
		else
		{
			if(x==y)
			{
				t++;continue;
			}
			if(fx!=fy)
			{
				f[fx]=fy;
				len[fx]=len[y]-len[x]+1;
			}
			else
			{
				if((len[x]-len[y]-1)%3!=0) t++;
			}
		}
	}
	cout<<t<<endl;
	return 0;
}