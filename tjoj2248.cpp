/*
*
*   author : twocoldz
*   date : Sat, 16 Nov 2013 03:07:28 +0800 
*   最小树形图，模板题
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#define inf 0x3f3f3f3f
using namespace std;
const int N=105;
struct node
{
	int u,v,cost;
}edge[N*N];
int in[N],id[N],pre[N];
int vis[N];
int n,m;

int Directed_MST(int root)
{
	int ans=0;
	while(true)
	{
		int nodecnt=0;
		memset(in,inf,sizeof(in));
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

int main()
{
	while(scanf("%d %d",&n,&m)&&(n+m))
	{
		for(int i=0;i<m;i++)
		{
			scanf("%d %d %d",&edge[i].u,&edge[i].v,&edge[i].cost);
		}
		int ret=Directed_MST(1);
		if(ret==-1)
			printf("impossible\n");
		else
			printf("%d\n",ret);
	}
	return 0;
}
