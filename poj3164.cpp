/*
*
*    author : twocoldz
*    date : Mon, 18 Nov 2013 23:04:43 +0800 
*    最小树形图，这个模板看来没问题
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <math.h>
#define inf 0x3f3f3f3f
using namespace std;
const int N=105;
struct node
{
        int u,v;
        double cost;
}edge[N*N];
double in[N];
int id[N],pre[N];
int vis[N];
int n,m;

double Directed_MST(int root)
{
	double ans=0;
	while(true)
	{
		int nodecnt=0;
		for(int i=1;i<=n;i++)
			in[i]=inf;
		memset(pre,-1,sizeof(pre));
		for(int i=0;i<m;i++)
		{
			//printf("%d %d\n",edge[i].u,edge[i].v);
			if(in[edge[i].v]>edge[i].cost)
				in[edge[i].v]=edge[i].cost,pre[edge[i].v]=edge[i].u;
		}
		for(int i=1;i<=n;i++)
			if(i!=root&&pre[i]==-1)
				return -1;
		memset(vis,0,sizeof(vis));
		memset(id,-1,sizeof(id));
		in[root]=0;
		for(int i=1;i<=n;i++)
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
				nodecnt++;
				for(int j=pre[v];j!=v;j=pre[j])
					id[j]=nodecnt;
				id[v]=nodecnt;
			}
		}
		if(nodecnt==0)
			break;
		for(int i=1;i<=n;i++)
			if(id[i]==-1)
				id[i]=++nodecnt;
		int j=0;
		for(int i=0;i<m;i++)
		{
			if(id[edge[i].u]!=id[edge[i].v])
			{
				edge[j].cost=edge[i].cost-in[edge[i].v];
				edge[j].u=id[edge[i].u];
				edge[j++].v=id[edge[i].v];
			}
		}
		m=j;
		root=id[root];
		n=nodecnt;
	}
	return ans;
}
double x[N],y[N];


int main()
{
    int mm;
    while(scanf("%d %d",&n,&mm)==2)
    {
        m=0;
        int a,b;
        for(int i=1;i<=n;i++)
            scanf("%lf %lf",x+i,y+i);
        for(int i=0;i<mm;i++)
        {
            scanf("%d %d",&a,&b);
            if(a==b)
                continue;
            edge[m].u=a;
            edge[m].v=b;
            edge[m++].cost=sqrt((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]));
        }
        double ans=Directed_MST(1);
        if(ans<0)
            printf("poor snoopy\n");
        else
            printf("%.2f\n",ans);
    }
    return 0;
}

