/*
*
*   author : twocoldz
*   date : Mon, 25 Nov 2013 11:57:59 +0800 
*   最短路+最大流 26次提交
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define inf 0x3f3f3f3f
using namespace std;
const int N=401;
struct node
{
	int v,nxt,w,f;
}edge[N*N];
int g[N][N];
int dis[N];
bool inq[N];
short head[N];
int n,m,e;

void Init()
{
	e=0;
	memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v,int w,int f)
{
	edge[e].v=v;
	edge[e].w=w;
	edge[e].f=f;
	edge[e].nxt=head[u];
	head[u]=e++;
}

bool bfs(int s,int t)
{
	memset(dis,inf,sizeof(dis));
	memset(inq,0,sizeof(inq));
	dis[s]=0;
	queue<int> q;
	q.push(s);
	inq[s]=1;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		inq[u]=0;
		for(int i=1;i<=n;i++)
		{
			if(g[u][i]!=-1&&dis[i]>dis[u]+g[u][i])
			{
				dis[i]=dis[u]+g[u][i];
				if(!inq[i])
					q.push(i),inq[i]=1;
			}
		}
	}
	return dis[t]!=inf;
}

void dfs(int u)
{
	if(u==n)
	{
		printf("%d\n",u);
		return ;
	}
	else
	{
		printf("%d ",u);
	}
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		if(edge[i].f==0&&i%2==0)
		{
			edge[i].f=1;
			dfs(edge[i].v);
			return ;
		}
	}
}

bool Bfs(int s,int t)
{
	memset(dis,-1,sizeof(dis));
	dis[s]=0;
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head[u];~i;i=edge[i].nxt)
		{
			int v=edge[i].v;
			if(dis[v]==-1&&edge[i].f>0)
			{
				dis[v]=dis[u]+1;
				q.push(v);
				if(v==t)
					return true;
			}
		}
	}
	return false;
}


int Dfs(int s,int t,int limit)
{
	if(s==t)
		return limit;
	int cost=0;
	for(int i=head[s];~i;i=edge[i].nxt)
	{
		int v=edge[i].v;
		if(dis[s]+1==dis[v]&&edge[i].f)
		{
			int tmp=Dfs(v,t,min(edge[i].f,limit-cost));
			if(tmp)
			{
				edge[i].f-=tmp;
				edge[i^1].f+=tmp;
				cost+=tmp;
			}
			if(limit==cost)
				break;
		}
	}
	if(cost==0)
		dis[s]=inf;
	return cost;
}

int Dinic(int s,int t)
{
	int ans=0;
	bfs(s,t);
	if(dis[t]==inf)
		return ans;
	Init();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(g[i][j]!=-1&&dis[i]+g[i][j]==dis[j])
				AddEdge(i,j,g[i][j],1),AddEdge(j,i,g[i][j],0);
	while(Bfs(s,t))
		ans+=Dfs(s,t,inf);
	return ans;
}


int main()
{
	while(scanf("%d %d",&n,&m)==2)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				g[i][j]=-1;
		int a,b,w;
		for(int i=0;i<m;i++)
		{
			scanf("%d %d %d",&a,&b,&w);
			g[a][b]=g[b][a]=w;
		}
		int ans=Dinic(1,n);
		if(ans<2)
		{
			printf("No solution\n");
		}
		else
		{
			dfs(1);
			dfs(1);
		}
	}
	return 0;
}
