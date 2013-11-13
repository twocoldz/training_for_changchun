/*
*   
*   author : twocoldz
*   date : Wed, 13 Nov 2013 15:10:36 +0800 
*   求最小生成树中第k大的边 
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int N=505;
typedef struct node
{
	int u,v,w;
	bool operator < (const node &b) const
	{
		return w<b.w;
	}
}node;
node edge[N*N];
int n,k,e;
int x[N],y[N];
int fa[N];

int sqr(int x)
{
	return x*x;
}

int Find(int x)
{
	if(x!=fa[x])
	{
		fa[x]=Find(fa[x]);
	}
	return fa[x];
}

void AddEdge(int u,int v)
{
	edge[e].v=v;
	edge[e].u=u;
	edge[e++].w=sqr(x[u]-x[v])+sqr(y[u]-y[v]);
}

int main()
{
	int cases;
	scanf("%d",&cases);
	while(cases--)
	{
		e=0;
		scanf("%d %d",&k,&n);
		for(int i=1;i<=n;i++)
			scanf("%d %d",x+i,y+i),fa[i]=i;
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				AddEdge(i,j);
		sort(edge,edge+e);
		double ans;
		int cnt=0;
		for(int i=0;i<e&&cnt<n-1;i++)
		{
			int fx=Find(edge[i].u);
			int fy=Find(edge[i].v);
			if(fx!=fy)
			{
				cnt++;
				if(cnt+k==n)
				{
					ans=edge[i].w;
				}
				fa[fx]=fy;
			}
		}
		printf("%.2lf\n",sqrt(ans));
	}
	return 0;
}
