/*
*
*   author : twocoldz
*   date : Thu, 14 Nov 2013 16:33:27 +0800 
*   最优比例生成树  二分实现
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define inf 0x3f3f3f3
using namespace std;
const int N=1005;
const double eps=1e-5;
double w[N][N];
double d[N][N];
double wd[N][N];
double dis[N];
bool vis[N];
double x[N],y[N],r[N];
int n;


inline double Dis(int i,int j)
{
	return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}

double Prim(double mid)
{
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
	{
		dis[i]=inf;
		wd[i][i]=0;
		for(int j=i+1;j<=n;j++)
		{
			wd[i][j]=wd[j][i]=w[i][j]-mid*d[i][j];
		}
	}
	dis[1]=0;
	double ans=0;
	for(int u=1;u<=n;u++)
	{
		int v=-1;
		for(int i=1;i<=n;i++)
			if(!vis[i]&&(v==-1||dis[v]>dis[i]))
				v=i;
		vis[v]=1;
		ans+=dis[v];
		//printf("v=%d dis[v]=%lf\n",v,dis[v]);
		for(int i=1;i<=n;i++)
			if(!vis[i]&&dis[i]>wd[v][i])
				dis[i]=wd[v][i];
	}
	//printf("%lf %lf\n",mid,ans);
	return ans;
}

int main()
{
	while(scanf("%d",&n)==1&&n)
	{
		double R=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%lf %lf %lf",x+i,y+i,r+i);
			d[i][i]=w[i][i]=0;
			for(int j=1;j<i;j++)
			{
				d[j][i]=d[i][j]=Dis(i,j);
				w[j][i]=w[i][j]=abs(r[i]-r[j]);
				R=max(w[i][j]/d[i][j],R);
			}
		}
		double L=0.0;
		double ans;
		while(L<=R)
		{
			double mid=(L+R)/2;
			if(Prim(mid)>=0)
			{
				L=mid+eps;
			}
			else
			{
				R=mid-eps;
				ans=mid;
			}
		}
		printf("%.3lf\n",ans);
	}
	return 0;
}
