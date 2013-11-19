/*
*
*   author : twocoldz
*   date : Tue, 19 Nov 2013 18:54:35 +0800 
*   最小树形图 为啥结构体构造函数和自己写的赋值语句时间差这么多 跪了
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define inf 0x3f3f3f3f
using namespace std;
const int N=1005;
struct node
{
	int u,v,cost;
	node(){}
	node(int u,int v,int cost):u(u),v(v),cost(cost){}
}edge[N*N];

int in[N],id[N],pre[N];
int vis[N];
int X,Y,Z;
struct Point
{
	int x,y,z;
}p[N];

inline int Directed_MST(int root,int n,int m)
{
	int ans=0;
	while(true)
	{
		int nodecnt=0;
		for(int i=0;i<n;i++)
			in[i]=inf;
		for(int i=0;i<m;i++)
		{
			int u=edge[i].u;
			int v=edge[i].v;
			if(in[v]>edge[i].cost&&u!=v)
			{
				in[v]=edge[i].cost;
				pre[v]=u;
			}
		}
		memset(vis,-1,sizeof(vis));
		memset(id,-1,sizeof(id));
		in[root]=0;
		for(int i=0;i<n;i++)
		{
			ans+=in[i];
			int v=i;
			while(vis[v] != i && id[v] == -1 && v != root)
			{
				vis[v]=i;
				v=pre[v];
			}
			if(v!=root&&id[v]==-1)
			{
				for(int j=pre[v];j!=v;j=pre[j])
					id[j]=nodecnt;
				id[v]=nodecnt++;
			}
		}
		if(nodecnt==0)
			break;
		for(int i=0;i<n;i++)
			if(id[i]==-1)
				id[i]=nodecnt++;
		int j=0;
		for(int i=0;i<m;i++)
		{
			int v=edge[i].v;
			if(id[edge[i].u]!=id[edge[i].v])
			{
				edge[j].cost=edge[i].cost-in[v];
				edge[j].u=id[edge[i].u];
				edge[j++].v=id[v];
			}
		}
		root=id[root];
		n=nodecnt;
		m=j;
	}
	return ans;
}

int x[N],y[N],z[N];

inline int Dis(int i,int j)
{
	int ret=abs(x[i]-x[j])+abs(y[i]-y[j])+abs(z[i]-z[j]);
	if(z[i]<z[j])
		return ret*Y+Z;
	return ret*Y;
}

int main()
{
	int a,k,m,n;
	while(scanf("%d %d %d %d",&n,&X,&Y,&Z)==4&&(n||X||Y||Z))
	{
		m=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d %d %d",x+i,y+i,z+i);
			edge[m++]=node(0,i,X*z[i]);
			//edge[m].u=0;
			//edge[m].v=i;
			//edge[m].cost=X*z[i];
			//m++;
		}
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&k);
			while(k--)
			{
				scanf("%d",&a);
				if(a!=i)
				{
					edge[m++]=node(i,a,Dis(i,a));
					//edge[m].u=i;
					//edge[m].v=a;
					//edge[m].cost=Dis(i,a)+z[a]<=z[i]?0:Z;
					//m++;
				}
			}
		}
		int ans=Directed_MST(0,n+1,m);
		printf("%d\n",ans);
	}
	return 0;
}

