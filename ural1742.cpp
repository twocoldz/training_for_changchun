/*
*   author :twocoldz
*   date :Tue, 05 Nov 2013 16:16:13 +0800 
*   求强联通分量个数和无入度强联通分量个数
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=100005;
struct node
{
	int v,nxt;
}edge[N];
int head[N];
int dfn[N],low[N],stack[N];
int deg[N],wh[N];
bool ins[N];
int n,m,e;
int num,cnt,top;

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

void tarjan(int u)
{
	dfn[u]=low[u]=++num;
	stack[top++]=u;
	ins[u]=1;
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		int v=edge[i].v;
		if(!dfn[v])
		{
			tarjan(v);
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
	memset(ins,0,sizeof(ins));
	memset(dfn,0,sizeof(dfn));
	memset(deg,0,sizeof(deg));
	for(int i=1;i<=n;i++)
	{
		if(!dfn[i])
		{
			tarjan(i);
		}
	}
	for(int u=1;u<=n;u++)
	{
		for(int i=head[u];~i;i=edge[i].nxt)
		{
			int v=edge[i].v;
			if(wh[u]!=wh[v])
			{
				deg[wh[v]]++;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=cnt;i++)
		if(!deg[i])
			ans++;
	printf("%d %d\n",ans,cnt);
}

int main()
{
	while(scanf("%d",&n)==1)
	{
		Init();
		int a;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a);
			if(a!=i)
				AddEdge(i,a);
		}
		SCC();
	}
	return 0;
}
