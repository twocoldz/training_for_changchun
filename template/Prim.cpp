#include <cstdio>
#include <cstring>
#include <algorithm>
#define inf 0x3f3f3f3f
using namespace std;
const int N=105;
struct node
{
	int v,nxt,w;
}edge[N*N];
int head[N];
int st[N];
int dis[N];
bool vis[N];
int n,m,e;

void Init()
{
	e=0;
	memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v,int w)
{
	edge[e].v=v;
	edge[e].w=w;
	edge[e].nxt=head[u];
	head[u]=e++;
}

void Prim()
{
	memset(vis,0,sizeof(vis));
	memset(dis,inf,sizeof(dis));
	for(int i=0;i<m;i++)   //已经在集合中的点
		dis[st[i]]=0;
	int ans=0;
	for(int u=1;u<=n;u++)
	{
		int v=-1;
		for(int i=1;i<=n;i++)
			if(!vis[i]&&(v==-1||dis[i]<dis[v]))
				v=i;
		ans+=dis[v];
		vis[v]=1;
		for(int i=head[v];~i;i=edge[i].nxt)
		{
			int x=edge[i].v;
			if(!vis[x]&&edge[i].w<dis[x])
				dis[x]=edge[i].w;
		}
	}
	printf("%d\n",ans);
}

int main()
{
	while(scanf("%d %d",&n,&m)==2)
	{
		int w;
		Init();
		for(int i=0;i<m;i++)
			scanf("%d",st+i);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				scanf("%d",&w);
				if(i!=j)
					AddEdge(i,j,w);
			}
		Prim();
	}
	return 0;
}
