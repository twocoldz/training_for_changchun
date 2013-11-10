/*
*
*   author : twocoldz
*   date : Sun, 10 Nov 2013 19:52:19 +0800 
*   二分+最大团判定
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;
const int N=105;
int g[N][N];
int path[N];
int num[N];
int bro[N];
int dis[N][N];
int x[N],y[N];
int n,m,e,best;

void Init()
{
	memset(g,0,sizeof(g));
}

int sqr(int x)
{
	return x*x;
}

bool Dfs(int *v,int tot,int cnt)
{
	if(tot==0)
	{
		if(cnt>best)
		{
			best=cnt;
			for(int i=1;i<=cnt;i++)
				path[i]=bro[i];
			return true;
		}
		return false;
	}
	int x[N];
	for(int i=0;i<tot;i++)
	{
		if(cnt+tot-i<=best)
			return false;
		if(cnt+num[v[i]]<=best)
			return false;
		int tmp=0;
		for(int j=i+1;j<tot;j++)
			if(g[v[i]][v[j]])
				x[tmp++]=v[j];
		bro[cnt+1]=v[i];
		if(Dfs(x,tmp,cnt+1))
			return true;
	}
	return false;
}

int Clique()
{
	int v[N];
	best=0;
	for(int i=n;i>0;i--)
	{
		int tmp=0;
		for(int j=i+1;j<=n;j++)
			if(g[i][j])
				v[tmp++]=j;
		bro[1]=i;
		Dfs(v,tmp,1);
		num[i]=best;
		//printf("%d %d\n",tmp,best);
	}
	return 0;
}

void Build(int mid)
{
	Init();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i==j)
				continue;
			else if(dis[i][j]>=mid)
				g[i][j]=1;
}


int main()
{
	while(scanf("%d %d",&n,&m)!=EOF)
	{
		for(int i=1;i<=n;i++)
		{
			scanf("%d %d",x+i,y+i);
		}
		int r=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				dis[i][j]=sqr(x[i]-x[j])+sqr(y[i]-y[j]);
				r=max(r,dis[i][j]);
			}
		}
		int l=0;
		int ans;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			Build(mid);
			Clique();
			if(best>=m)
				l=mid+1,ans=mid;
			else
				r=mid-1;
		}
		printf("%.2lf\n",sqrt(ans));
	}
	return 0;
}
