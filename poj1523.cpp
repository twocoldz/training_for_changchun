/*
*
*   author : twocoldz
*   date : Thu, 07 Nov 2013 12:05:24 +0800 
*   割点，分类讨论
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=1005;
struct node
{
	int v,nxt;
}edge[N*N];
int head[N];
bool map[N][N];
int dfn[N],low[N],cut[N];
int vis[N];
int n,m,e;
int num,cnt,top,id;

void Init()
{
	e=0;
	memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v)
{
	edge[e].v=v;
	edge[e].nxt=head[u];
	head[u]=e++;
}

void tarjan_cut(int u,int fa)
{
	dfn[u]=low[u]=++num;
	vis[u]=1;
	int son=0;
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		int v=edge[i].v;
		if(v==fa)
			continue;
		if(!dfn[v])
		{
			son++;
			tarjan_cut(v,u);
			low[u]=min(low[v],low[u]);
			if(fa!=-1&&low[v]>=dfn[u])
				cut[u]++;
					
		}
		else if(vis[v]==1)
			low[u]=min(low[u],dfn[v]);
	}
	if(fa==-1)
		cut[u]=son==1?0:son;
	else if(fa!=-1&&cut[u])
		cut[u]++;
}

void Get_Cut()
{
	num=cnt=top=0;
	memset(dfn,0,sizeof(dfn));
	memset(vis,0,sizeof(vis));
	memset(cut,0,sizeof(cut));
	tarjan_cut(1,-1);
	printf("Network #%d\n",id++);
	int f=0;
	for(int i=1;i<=n;i++)
	{
		if(cut[i])
			f=1,printf("  SPF node %d leaves %d subnets\n",i,cut[i]);
	}
	if(!f)
		printf("  No SPF nodes\n");
}


int main()
{
	int a,b;
	id=1;
	while(scanf("%d",&a)&&a)
	{
		if(id>1)
			printf("\n");
		n=a;
		Init();
		scanf("%d",&b);
		n=max(n,b);
		AddEdge(a,b);
		AddEdge(b,a);
		while(scanf("%d",&a)&&a)
		{
			scanf("%d",&b);
			AddEdge(a,b);
			AddEdge(b,a);
			n=max(n,a);
			n=max(n,b);
		}
		//printf("Read Over\n");
		Get_Cut();
	}
	return 0;
}
