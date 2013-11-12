/*
*
*   author : twocoldz
*   date : Tue, 12 Nov 2013 17:41:10 +0800 
*   次小生成树  Prim
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#define inf 0x3f3f3f3f
using namespace std;
const int N=105;
struct node
{
	int v,nxt,w,u;
}edge[N*N];
int head[N];
int dis[N],fa[N];
int w[N][N];
bool vis[N],used[N*N];
int n,m,e;
void Init()
{
	e=0;
	memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v,int w)
{
	edge[e].v=v;
	edge[e].u=u;
	edge[e].w=w;
	edge[e].nxt=head[u];
	head[u]=e++;
}

void Prim()
{
	memset(vis,0,sizeof(vis));
	memset(dis,inf,sizeof(dis));
	memset(w,0,sizeof(w));
	memset(fa,-1,sizeof(fa));
	memset(used,0,sizeof(used));
	dis[1]=0;
	int ans=0,flag=0;
	for(int u=1;u<=n;u++)
	{
		int v=-1;
		for(int i=1;i<=n;i++)
			if(!vis[i]&&(v==-1||dis[i]<dis[v]))
				v=i;
		if(dis[v]==inf)
		{
			flag=1;
			break;
		}
		ans+=dis[v];
		vis[v]=1;
		if(u!=1)
			used[fa[v]>>1]=1;
		for(int i=head[v];~i;i=edge[i].nxt)
		{
			int x=edge[i].v;
			if(!vis[x]&&edge[i].w<dis[x])
				dis[x]=edge[i].w,fa[x]=i;
		}
		if(u!=1)
			for(int i=1;i<=n;i++)
				if(i!=v)
					w[v][i]=w[i][v]=max(w[i][edge[fa[v]].u],dis[v]);
	}
	/*
	for(int i=1;i<=n;i++)
	{
		printf("%d ",fa[i]);
	}
	printf("\n");
	for(int i=1;i<=n;i++,printf("\n"))
		for(int j=1;j<=n;j++)
			printf("%d ",w[i][j]);
	*/
	/*if(flag)
	{
		printf("0\n");
		return ;
	}
	*/
	int dif=inf;
	for(int i=0;i<e;i+=2)
	{
		if(!used[i>>1])
		{
//			printf("i=%d\n",i);
			int t=edge[i].w-w[edge[i].u][edge[i].v];
			dif=min(dif,t);
		}
	}
	if(dif)
		printf("%d\n",ans);
	else
		printf("Not Unique!\n");
	return ;
}

int main()
{
	int cases;
	scanf("%d",&cases);
	while(cases--)
	{
		int a,b,c;
		scanf("%d %d",&n,&m);
		Init();
		for(int i=0;i<m;i++)
		{
			scanf("%d %d %d",&a,&b,&c);
			AddEdge(a,b,c);
			AddEdge(b,a,c);
		}
		Prim();
	}
	return 0;
}
