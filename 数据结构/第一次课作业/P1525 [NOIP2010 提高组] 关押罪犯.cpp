#include<bits/stdc++.h>
using namespace std;
const int N=20010,M=100010;
struct data{
	int x,y,c;
}da[M];
int en[N],f[N];
bool cmp(data A,data B)
{
	return A.c>B.c;
}
int find(int x)
{
	if(x==f[x]) return x;
	return f[x]=find(f[x]);
}
void unionn(int x,int y)
{
	x=find(x);y=find(y);
	f[x]=y;
}
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&da[i].x,&da[i].y,&da[i].c);
	sort(da+1,da+1+m,cmp);
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=m;i++)
	{
		if(find(da[i].x)==find(da[i].y))
		{
			printf("%d",da[i].c);
			return 0;
		}
		else
		{
			if(!en[da[i].x]) en[da[i].x]=da[i].y;
			else{
				unionn(en[da[i].x],da[i].y);
			}
			if(!en[da[i].y]) en[da[i].y]=da[i].x;
			else{
				unionn(en[da[i].y],da[i].x);
			}
		}
	}
	printf("0");
	return 0;
}