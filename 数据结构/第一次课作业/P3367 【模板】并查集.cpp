#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int f[N];
int find(int x)
{
	if(f[x]==x) return x;
	return f[x]=find(f[x]);
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		f[i]=i;
	while(m--)
	{
		int x,a,b;
		cin>>x>>a>>b;
		if(x==1) f[find(a)]=f[find(b)];
		else
		{
			if(find(a)==find(b))
				cout<<"Y"<<endl;
			else cout<<"N"<<endl;
		}
	}
}