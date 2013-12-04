/*
*
*   author : twocoldz
*   date : Wed, 04 Dec 2013 10:45:16 +0800 
*   上下有界 网络流 有源汇
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define inf 0x3f3f3f3f
using namespace std;
const int N=1500;
struct node
{
	int v,nxt,f;
}edge[N*100];
int head[N];
int dis[N];
int du[N];
int low[N][N];
int id[N][N];
int n,m,e;

void Init()
{
	e=0;
	memset(head,-1,sizeof(head));
	memset(du,0,sizeof(du));
}

void AddEdge(int u,int v,int f)
{
	edge[e].v=v;
	edge[e].f=f;
	edge[e].nxt=head[u];
	head[u]=e++;
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
		if(dis[s]+1==dis[v]&&edge[i].f>0)
		{
			int tmp=Dfs(v,t,min(limit-cost,edge[i].f));
			if(tmp)
			{
				cost+=tmp;
				edge[i].f-=tmp;
				edge[i^1].f+=tmp;
			}
			if(cost==limit)
				break;
		}
	}
	if(cost==0)
		dis[s]=-1;
	return cost;
}

int Dinic(int s,int t)
{
	int ans=0;
	while(Bfs(s,t))
		ans+=Dfs(s,t,inf);
	return ans;
}

int main()
{
	while(scanf("%d %d",&n,&m)==2)
	{
		Init();
		int s=0,t=n+m+1;
		int g,a,c,d,u;
		for(int i=1;i<=m;i++)
		{
			scanf("%d",&g);
			du[i+n]-=g;
			du[t]+=g;
			AddEdge(i+n,t,inf-g);
			AddEdge(t,i+n,0);
		}
		for(int i=1;i<=n;i++)
		{
			scanf("%d %d",&c,&d);
			AddEdge(s,i,d);
			AddEdge(i,s,0);
			for(int j=1;j<=c;j++)
			{
				scanf("%d %d %d",&a,low[i]+j,&u);
				du[i]-=low[i][j];
				du[n+a+1]+=low[i][j];
				AddEdge(i,n+a+1,u-low[i][j]);
				AddEdge(n+a+1,i,0);
				id[i][j]=e-1;
			}
			low[i][0]=c;
		}
		AddEdge(t,s,inf);
		AddEdge(s,t,0);
		s=t+1;
		t=s+1;
		int sum=0;
		for(int i=0;i<=n+m+1;i++)
		{
			if(du[i]>0)
				AddEdge(s,i,du[i]),AddEdge(i,s,0),sum+=du[i];
			if(du[i]<0)
				AddEdge(i,t,-du[i]),AddEdge(t,i,0);
		}
		int ans=Dinic(s,t);
		if(ans!=sum)
		{
			printf("-1\n\n");
			continue;
		}
		s=0,t=n+m+1;
		ans=Dinic(s,t);
		printf("%d\n",ans);
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=low[i][0];j++)
			{
				printf("%d\n",edge[id[i][j]].f+low[i][j]);
			}
		}
		printf("\n");
	}
	return 0;
}

