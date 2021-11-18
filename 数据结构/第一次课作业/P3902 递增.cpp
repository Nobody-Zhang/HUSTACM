#include<bits/stdc++.h>
using namespace std;

const int N=1e5+10;

int n,a[N],stk[N],p;

int find(int x)
{//找到第一个大于x的东西
	int l=1,r=p;
	while(l!=r)
	{
		int mid=l+r>>1;
		if(stk[mid]>x) r=mid;
		else l=mid+1;
	}
	return l;
}

void f(int x)
{
	if(stk[p]<x) stk[++p]=x;
	else
	{
		stk[find(x)]=x;
	 } 
}

int main()
{//最长上升子序列
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		f(a[i]);
	printf("%d",n-p);
	return 0;
}