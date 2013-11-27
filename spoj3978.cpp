/*
*
*   author : twocoldz 
*   date : Wed, 27 Nov 2013 16:11:37 +0800 
*   lca  tarjan变形
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#define inf 0x3f3f3f3f
using namespace std;
const int N=100005;
struct node
{
	int u,v,w,nxt;
}edge[N*2],qedge[N*2];
int head[N],qhead[N];
int f[N],ma[N],mi[N];
int ans[N][2];
bool vis[N];
int n,m,e;
queue<int> q[N];

void Init()
{
	e=0;
	memset(head,-1,sizeof(head));
	memset(qhead,-1,sizeof(qhead));
	memset(vis,0,sizeof(vis));
	for(int i=0;i<=n;i++)
		f[i]=i,mi[i]=inf,ma[i]=0;
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
	qedge[e].u=u;
	qedge[e].v=v;
	qedge[e].nxt=qhead[u];
	qhead[u]=e++;
}

int find(int x)
{
	int fa=f[x];
	if(x!=f[x])
	{
		f[x]=find(f[x]);
		ma[x]=max(ma[x],ma[fa]);
		mi[x]=min(mi[x],mi[fa]);
	}
	return f[x];
}

void tarjan(int u,int fa)
{
	vis[u]=1;
	for(int i=qhead[u];~i;i=qedge[i].nxt)
	{
		int v=qedge[i].v;
		if(vis[v]&&ans[i>>1][0]==-1)
		{
			int x=find(v);
			q[x].push(i);
		}
	}
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		int v=edge[i].v;
		if(v!=fa)
		{
			tarjan(v,u);
			f[v]=u;
			mi[v]=ma[v]=edge[i].w;
		}
	}
	while(!q[u].empty())
	{
		int i=q[u].front();
		q[u].pop();
		int x=qedge[i].u;
		int y=qedge[i].v;
		find(x);
		find(y);
		ans[i>>1][0]=min(mi[x],mi[y]);
		ans[i>>1][1]=max(ma[x],ma[y]);
	}
}

int main()
{
	while(scanf("%d",&n)==1)
	{
		int a,b,w,Q;
		Init();
		for(int i=0;i<n-1;i++)
		{
			scanf("%d %d %d",&a,&b,&w);
			AddEdge(a,b,w);
			AddEdge(b,a,w);
		}
		e=0;
		scanf("%d",&Q);
		for(int i=0;i<Q;i++)
		{
			scanf("%d %d",&a,&b);
			if(a==b)
				ans[i][0]=ans[i][1]=0;
			else
				ans[i][0]=ans[i][1]=-1;
			AddQuery(a,b);
			AddQuery(b,a);	
		}
		tarjan(1,-1);
		for(int i=0;i<Q;i++)
		{
			printf("%d %d\n",ans[i][0],ans[i][1]);
		}
	}
	return 0;
}
