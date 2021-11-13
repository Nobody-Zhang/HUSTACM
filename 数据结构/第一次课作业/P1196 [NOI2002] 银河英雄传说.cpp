#include<bits/stdc++.h>
using namespace std;
const int N=30000;
int f[N+10],s[N+10],len[N+10];//len表示到root/father的距离

int findfa(int x)
{
	if(f[x]==x) return x;
	int root=findfa(f[x]);
	len[x]=len[f[x]]+len[x];
	f[x]=root;
	return root;
}

int findso(int x)
{
	if(s[x]==x) return x;
	return s[x]=findso(s[x]);
}

int main()
{
	for(int i=1;i<=N;i++)
		f[i]=i,s[i]=i;
	int m;
	scanf("%d",&m);
	while(m--)
	{
		char op[2];
		int i,j;
		scanf("%s%d%d",op,&i,&j);
		if(*op=='M')
		{//把iroot接到json里面
			int fi=findfa(i);
			int sj=findso(j);
			f[fi]=sj;s[sj]=fi;
			len[fi]=1;
		}
		else
		{
			if(findfa(i)!=findfa(j)) printf("-1\n");
			else
			{
				if(i==j) printf("0\n");
				else
				printf("%d\n",abs(len[i]-len[j])-1);
			}
		}
	}
//	for(int i=1;i<=5;i++)
//		cout<<len[i]<<' ';
//	cout<<endl;
//	for(int i=1;i<=5;i++)
//		cout<<f[i]<<' ';
//	cout<<endl;
//	for(int i=1;i<=5;i++)
//		cout<<s[i]<<' ';
//	cout<<endl;
	return 0;
}