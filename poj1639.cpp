/*
* 
*   author : twocoldz 
*   date : Wed, 13 Nov 2013 22:43:02 +0800 
*   最小k度生成树 
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#define inf 0x3f3f3f3f
using namespace std;
const int N=25;
struct node
{
	int u,v,nxt,w;
}edge[10000];
int head[N];
int w[N][N];
char name[N][N];
int fa[N];
int dis[N],ma[N];
bool vis[N];
int n,m,e,k,ans;

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

int find(char *str)
{
	for(int i=0;i<n;i++)
		if(strcmp(name[i],str)==0)
			return i;
	strcpy(name[n],str);
	n++;
	return n-1;
}

void Dfs(int u,int f)
{
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		int v=edge[i].v;
		if(v!=f)
		{
			ma[v]=max(ma[u],edge[i].w);
			fa[v]=u;
			Dfs(v,u);
		}
	}
}

void Dfs(int u)
{
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		int v=edge[i].v;
		if(fa[v]==u)
		{
			ma[v]=max(ma[u],edge[i].w);
			Dfs(v);
		}
	}
}
void Prim(int s)
{
	int mi=inf,v;
	while(true)
	{
		int u=-1;
		for(int i=1;i<n;i++)
			if(!vis[i]&&(u==-1||dis[u]>dis[i]))
				u=i;
		if(u==-1||dis[u]==inf)
			break;
		if(fa[u]!=-1)
		{
			AddEdge(fa[u],u,dis[u]);
			AddEdge(u,fa[u],dis[u]);
		}
		if(w[0][u]<mi)
		{
			mi=w[0][u];
			v=u;	
		}
		ans+=dis[u];
		vis[u]=1;
		for(int i=1;i<n;i++)
			if(!vis[i]&&w[u][i]<dis[i])
				dis[i]=w[u][i],fa[i]=u;
	}
	ma[v]=0;
	ans+=mi;
	fa[v]=0;
	Dfs(v,-1);
}

void solve()
{
	memset(dis,inf,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(fa,-1,sizeof(fa));
	dis[0]=0;
	ans=0;
	Init();
	int cnt=0;
	for(int i=1;i<n;i++)
	{
		if(!vis[i])
		{
			cnt++;
			dis[i]=0;
			Prim(i);
		}
	}
	for(;cnt<k;cnt++)
	{
		int mi=inf;
		int v=-1;
		for(int i=1;i<n;i++)
		{
			if(fa[i]!=0&&w[0][i]-ma[i]<mi)
				v=i,mi=w[0][i]-ma[i];
		}
		if(v==-1||mi>=0)
			break;
		ans+=mi;
		fa[v]=0;
		ma[v]=0;
		Dfs(v);
	}
	printf("Total miles driven: %d\n",ans);
}

int main()
{
	//freopen("A.dat","r",stdin);
	while(scanf("%d",&m)!=EOF)
	{
		char str1[N],str2[N];
		int a,b,c;
		n=0;
		strcpy(name[n],"Park");
		n++;
		memset(w,inf,sizeof(w));
		for(int i=0;i<m;i++)
		{
			scanf("%s %s %d",str1,str2,&c);
			a=find(str1);
			b=find(str2);
			if(c<w[a][b])
				w[a][b]=w[b][a]=c;
		}
		scanf("%d",&k);
		solve();
	}
	return 0;
}
