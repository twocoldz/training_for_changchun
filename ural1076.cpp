/*
*
*   author : twocoldz
*   date : Mon, 11 Nov 2013 23:33:12 +0800 
*   km算法，理解题意，垃圾分类，思路转换
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define inf 0x3f3f3f3f
using namespace std;
const int N=305;
int lx[N],ly[N],mx[N],my[N];
bool vx[N],vy[N];
int w[N][N];
int slack[N];
int nx,ny;

bool Dfs(int u)
{
	vx[u]=1;
	for(int i=1;i<=ny;i++)
	{
		if(!vy[i])
		{
			int t=lx[u]+ly[i]-w[u][i];
			if(t==0)
			{
				vy[i]=1;
				if(my[i]==-1||Dfs(my[i]))
				{
					my[i]=u;
					mx[u]=i;
					return 1;
				}
			}
			else if(t<slack[i])
				slack[i]=t;
		}
	}
	return false;
}

int KM()
{
	memset(ly,0,sizeof(ly));
	memset(mx,-1,sizeof(mx));
	memset(my,-1,sizeof(my));
	for(int i=1;i<=nx;i++)
	{
		lx[i]=-inf;
		for(int j=1;j<=ny;j++)
			lx[i]=max(w[i][j],lx[i]);
	}
	for(int u=1;u<=nx;u++)
	{
		memset(slack,0x3f,sizeof(slack));
		//printf("u=%d\n",u);
		while(1)
		{
			memset(vx,0,sizeof(vx));
			memset(vy,0,sizeof(vy));
			if(Dfs(u))
				break;
			int d=inf;
			for(int i=1;i<=ny;i++)
				if(!vy[i]&&slack[i]<d)
					d=slack[i];
			//printf("d=%d\n",d);
			for(int i=1;i<=nx;i++)
				if(vx[i])
					lx[i]-=d;
			for(int i=1;i<=ny;i++)
				if(vy[i])
					ly[i]+=d;
				else
					slack[i]-=d;
		}
		//printf("%d\n",mx[u]);
	}
	return 0;
}

int main()
{
	int n;
	while(scanf("%d",&n)==1)
	{
		int sum=0;
		nx=ny=n;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				scanf("%d",w[i]+j),sum+=w[i][j];
		KM();
		for(int i=1;i<=n;i++)
			sum-=w[i][mx[i]];
		printf("%d\n",sum);
	}
	return 0;
}
