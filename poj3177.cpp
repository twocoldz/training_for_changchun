/*
*
*   author : twocoldz
*   date :  Wed, 06 Nov 2013 15:18:13 +0800 
*   求桥，缩点，求叶子节点，ans=（left+1）/2 注意重边阿。。。。。
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=5005;
struct node
{
	int v,u,nxt;
}edge[N*10];
int head[N];
int dfn[N],low[N];
int deg[N];
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
	edge[e].u=u;
	edge[e].nxt=head[u];
	head[u]=e++;
}

void tarjan_bridge(int u,int fa)
{
	dfn[u]=low[u]=++num;
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		int v=edge[i].v;
		if(!dfn[v])
		{
			tarjan_bridge(v,u);
			low[u]=min(low[u],low[v]);
		}
		else if(v!=fa)
		{
			low[u]=min(low[u],dfn[v]);
		}
	}
}

void GetBridge()
{
	num=top=cnt=0;
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	for(int i=1;i<=n;i++)
	{
		deg[i]=0;
		if(!dfn[i])
			tarjan_bridge(i,-1);
	}
	int ans=0;
	for(int i=0;i<e;i++)
	{
		if(low[edge[i].v]!=low[edge[i].u])
		{
			//printf("%d\n",low[edge[i].v]);
			deg[low[edge[i].v]]++;
		}
	}
	for(int i=1;i<=n;i++)
		if(deg[i]==1)
			ans++;
	printf("%d\n",(ans+1)/2);
}

bool map[N][N];

int main()
{
	while(scanf("%d %d",&n,&m)==2)
	{
		Init();
		int a,b;
		memset(map,0,sizeof(map));
		for(int i=1;i<=m;i++)
		{
		
			scanf("%d %d",&a,&b);
			if(!map[a][b])
			{
				map[a][b]=map[b][a]=1;
				AddEdge(a,b);
				AddEdge(b,a);
			}
		}
		GetBridge();
	}
	return 0;
}
