/*
*
*   author : twocoldz
*   date : Wed, 06 Nov 2013 23:56:31 +0800 
*   强联通，缩点，建树，lca。看清输出阿，太想当然了
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=100005;
struct node
{
	int v,u,nxt,w;
}edge[N*4];
int head[N];
int dfn[N],low[N],stack[N],wh[N],f[N],dep[N];
bool ins[N],vis[N*2];
int num,cnt,top;
int n,m,e;

void Init()
{
	e=0;
	memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v)
{
	edge[e].v=v;
	edge[e].u=u;
	edge[e].nxt=head[u];
	head[u]=e++;
}

void tarjan(int u,int fa)
{
	dfn[u]=low[u]=++num;
	stack[top++]=u;
	ins[u]=1;
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		if(vis[i>>1])
			continue;
		vis[i>>1]=1;
		int v=edge[i].v;
		if(!dfn[v])
		{
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
		}
		else if(ins[v])
		{
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(dfn[u]==low[u])
	{
		int j;
		cnt++;
		do
		{
			j=stack[--top];
			ins[j]=0;
			wh[j]=cnt;
		}while(j!=u);
	}
}

void SCC()
{
	memset(dfn,0,sizeof(dfn));
	memset(ins,0,sizeof(ins));
	memset(vis,0,sizeof(vis));
	num=cnt=top=0;
	for(int i=1;i<=n;i++)
	{
		if(!dfn[i])
			tarjan(i,-1);
	}
}

void Dfs(int u,int fa,int d)
{
	dep[u]=d;
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		int v=edge[i].v;
		if(v!=fa)
		{
			f[v]=i;
			Dfs(v,u,d+1);
		}
	}	
}

void Build_Tree()
{
	int ee=e;
	e=0;
	memset(head,-1,sizeof(head));
	memset(vis,0,sizeof(vis));
	for(int i=0;i<ee;i+=2)
	{
		if(wh[edge[i].v]!=wh[edge[i].u])
			AddEdge(wh[edge[i].v],wh[edge[i].u]),AddEdge(wh[edge[i].u],wh[edge[i].v]);
	}
	f[1]=-1;
	Dfs(1,-1,0);
}

void Lca(int x,int y)
{
	if(dep[x]>dep[y])
		swap(x,y);
	while(dep[y]>dep[x])
	{
		if(!vis[f[y]])
			vis[f[y]]=1,cnt--;
		y=edge[f[y]].u;
	}
	while(x!=y)
	{
		if(!vis[f[x]])
			vis[f[x]]=1,cnt--;
		if(!vis[f[y]])
			vis[f[y]]=1,cnt--;
		x=edge[f[x]].u;
		y=edge[f[y]].u;
	}
}

int main()
{
	int id=1;
	while(scanf("%d %d",&n,&m)&&(n+m))
	{
		printf("Case %d:\n",id++);
		Init();
		int a,b;
		for(int i=0;i<m;i++)
		{
			scanf("%d %d",&a,&b);
			AddEdge(a,b);
			AddEdge(b,a);
		}
		SCC();
		Build_Tree();
		int Q;
		scanf("%d",&Q);
		while(Q--)
		{
			scanf("%d %d",&a,&b);
			if(wh[a]==wh[b]||cnt==1)
				printf("%d\n",cnt-1);
			else
			{
				Lca(wh[a],wh[b]);
				printf("%d\n",cnt-1);				
			}
		}
		printf("\n");
	}
	return 0;
}
