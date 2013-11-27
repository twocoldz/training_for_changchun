/*
*
*    author : twocoldz
*    date : Wed, 27 Nov 2013 11:30:41 +0800 
*    lca + tarjan
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=50005;
struct node
{
	int v,w,nxt;
}edge[N*2],qedge[N*3];
int head[N],qhead[N];
int ans[N*2];
int dis[N];
int f[N];
bool vis[N];
int n,m,e;

void Init()
{
	e=0;
	memset(head,-1,sizeof(head));
	memset(qhead,-1,sizeof(qhead));
	memset(ans,-1,sizeof(ans));
	memset(vis,0,sizeof(vis));
	for(int i=0;i<=n;i++)
		f[i]=i;
}

int find(int x)
{
	if(x!=f[x])
		f[x]=find(f[x]);
	return f[x];
}

void AddEdge(int u,int v,int w)
{
	edge[e].v=v;
	edge[e].w=w;
	edge[e].nxt=head[u];
	head[u]=e++;
}

void AddQuery(int u,int v)
{
	qedge[e].v=v;
	qedge[e].nxt=qhead[u];
	qhead[u]=e++;
}

void Dfs(int u,int fa)
{
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		int v=edge[i].v;
		if(v!=fa)
		{
			dis[v]=dis[u]+edge[i].w;
			Dfs(v,u);
		}
	}
}

void tarjan(int u,int fa)
{
	vis[u]=1;
	for(int i=qhead[u];~i;i=qedge[i].nxt)
	{
		int v=qedge[i].v;
		if(vis[v]&&ans[i>>1]==-1)
		{
			ans[i>>1]=dis[u]+dis[v]-2*dis[find(v)];
		}
	}
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		int v=edge[i].v;
		if(v!=fa)
		{
			tarjan(v,u);
			f[v]=u;
		}
	}
}

int main()
{
	int a,b,w,q;
	while(scanf("%d",&n)==1)
	{
		Init();
		for(int i=0;i<n-1;i++)
		{
			scanf("%d %d %d",&a,&b,&w);
			AddEdge(a,b,w);
			AddEdge(b,a,w);
		}
		dis[0]=0;
		Dfs(0,-1);
		e=0;
		scanf("%d",&q);
		for(int i=0;i<q;i++)
		{
			scanf("%d %d",&a,&b);
			if(a==b)
				ans[i]=0;
			AddQuery(a,b),AddQuery(b,a);
		}
		tarjan(0,-1);
		for(int i=0;i<q;i++)
		{
			printf("%d\n",ans[i]);
		}
	}
	return 0;
}
