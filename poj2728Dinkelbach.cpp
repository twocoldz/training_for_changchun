/*
*
*   author : twocoldz
*   date : Thu, 14 Nov 2013 17:42:03 +0800 
*   最优比例生成树 Dinkelbach迭代实现 
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define inf 0x3f3f3f3f
#define eps 1e-4
using namespace std;
const int N=1005;
double x[N],y[N],r[N];
double d[N][N],w[N][N];
int pre[N];
bool vis[N];
double dis[N];
int n;

inline double sqr(double x)
{
	return x*x;
} 

inline double Dis(int i,int j)
{
	return sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j]));
}

double Prim(double R)
{
	memset(vis,0,sizeof(vis));
//	memset(d[0],0,sizeof(d[0]));
//	memset(w[0],0,sizeof(w[0]));
	for(int i=1;i<=n;i++)
		dis[i]=inf;
	dis[1]=0,pre[1]=0;
	double s1=0,s2=0;
	for(int u=1;u<=n;u++)
	{
		int v=-1;
		for(int i=1;i<=n;i++)
			if(!vis[i]&&(v==-1||dis[v]>dis[i]))
				v=i;
		//printf("v=%d pre[v]=%d w=%lf d=%lf\n",v,pre[v],w[pre[v]][v],d[pre[v]][v]);
		s1+=w[pre[v]][v];
		s2+=d[pre[v]][v];
		vis[v]=1;
		for(int i=1;i<=n;i++)
			if(!vis[i]&&(dis[i]>w[v][i]-R*d[v][i]))
				dis[i]=w[v][i]-R*d[v][i],pre[i]=v;
	}
	return s1/s2;
}

int main()
{
	while(scanf("%d",&n)!=EOF&&n)
	{
		for(int i=1;i<=n;i++)
		{
			scanf("%lf %lf %lf",x+i,y+i,r+i);
			for(int j=1;j<i;j++)
			{
				d[i][j]=d[j][i]=Dis(i,j);
				w[i][j]=w[j][i]=abs(r[i]-r[j]);
			}
		}
		double ans=0;
		while(true)
		{
			double tmp=Prim(ans);
			//printf("%lf\n",tmp);
			if(fabs(ans-tmp)<=eps)
				break;
			ans=tmp;
		}
		printf("%.3f\n",ans);
	}
	return 0;
}
