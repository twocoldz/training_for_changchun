/*
#include <cstdio>
#include <cstring>
#include <algorithm>
#define inf 0x3f3f3f3f
using namespace std;
const int N=505;
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
		if(v==-1||dis[v]==inf)
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
	
	int dif=inf;
	for(int i=0;i<e;i+=2)
	{
		if(!used[i>>1])
		{
		//	printf("i=%d\n",i);
			int t=edge[i].w-w[edge[i].u][edge[i].v];
			dif=min(dif,t);
		}
	}
	if(dif!=inf)
		printf("Cost: %d\nCost: %d\n",ans,ans+dif);
	else
		printf("Cost: %d\nCost: -1\n",ans);
	return ;
}

int main()
{
	while(scanf("%d %d",&n,&m)==2)
	{
		Init();
		int a,b,c;
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
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#define inf 0x3f3f3f3f
using namespace std;
const int N=505;
struct node
{
	int v,u,w,nxt;
}E[N*N],edge[N*N],tedge[N*N];
int head[N],thead[N];
int fa[N];
int num[N];
int n,m,e,diff;

bool cmp(node a,node b)
{
	return a.w<b.w;
}

void Init()
{
	e=0;
	memset(head,-1,sizeof(head));
	memset(thead,-1,sizeof(thead));
	for(int i=1;i<=n;i++)
		num[i]=1,fa[i]=i;
}

void AddEdge(int u,int v,int w,int *head,struct node *edge)
{
	edge[e].v=v;
	edge[e].u=u;
	edge[e].w=w;
	edge[e].nxt=head[u];
	head[u]=e++;
}

int Find(int x)
{
	if(x!=fa[x])
		fa[x]=Find(fa[x]);
	return fa[x];
}

void UpdateDiff(int u,int y,int w,int k)
{
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		if((i>>1)!=k)
		{
			int v=Find(edge[i].v);
			if(v==y)
				diff=min(diff,w-edge[i].w);//printf("u=%d v=%d w=%d %d\n",u,edge[i].v,w,edge[i].w);
		}
	}
}

void Kruskal()
{
	int cnt=0,ans=0;
	diff=inf,e=0;
	for(int i=0;cnt+1<n&&i<m;i++)
	{
		int fx=Find(E[i].u);
		int fy=Find(E[i].v);
		if(fx!=fy)
		{
			ans+=E[i].w;
			cnt++;
			if(num[fx]>num[fy])
				swap(fx,fy);
			//printf("%d %d\n",fx,fy);
			UpdateDiff(fx,fy,E[i].w,i);
			for(int j=thead[fx];~j;j=tedge[j].nxt)
				UpdateDiff(tedge[j].v,fy,E[i].w,i);
			for(int j=thead[fx];~j;j=tedge[j].nxt)
				AddEdge(fy,tedge[j].v,1,thead,tedge);
			AddEdge(fy,fx,1,thead,tedge);
			fa[fx]=fy;
			num[fy]+=num[fx];
		}
	}
	if(diff!=inf)
		printf("Cost: %d\nCost: %d\n",ans,ans+diff);
	else
		printf("Cost: %d\nCost: -1\n",ans);
}

int main()
{
	while(scanf("%d %d",&n,&m)==2)
	{
		Init();
		for(int i=0;i<m;i++)
		{
			scanf("%d %d %d",&E[i].u,&E[i].v,&E[i].w);
			AddEdge(E[i].u,E[i].v,E[i].w,head,edge);
			AddEdge(E[i].v,E[i].u,E[i].w,head,edge);
		}
		sort(E,E+m,cmp);
		Kruskal();
	}
	return 0;
}
