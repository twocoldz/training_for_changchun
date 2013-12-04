/*
*
*   author : twocoldz
*   date : Wed, 04 Dec 2013 15:00:06 +0800 
*   上下有界 网络流 最小流
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define inf 0x3f3f3f3f
using namespace std;
const int N=105;
struct node
{
	int v,nxt,f;
}edge[N*N];
int head[N];
int dis[N];
int du[N];
int low[N*N];
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
		int a,b,c,d;
		for(int i=0;i<m;i++)
		{
			scanf("%d %d %d %d",&a,&b,&c,&d);
			if(d)
			{
				du[a]-=c;
				du[b]+=c;
				low[i]=c;
				AddEdge(a,b,0);
				AddEdge(b,a,0);
			}
			else
			{
				low[i]=0;
				AddEdge(a,b,c);
				AddEdge(b,a,0);
			}
		}
		int s=0,t=n+1;
		for(int i=1;i<=n;i++)
		{
			if(du[i]>0)
				AddEdge(s,i,du[i]),AddEdge(i,s,0);
			if(du[i]<0)
				AddEdge(i,t,-du[i]),AddEdge(t,i,0);
		}
		Dinic(s,t);
		AddEdge(n,1,inf);
		AddEdge(1,n,0);
		Dinic(s,t);
		int flag=0;
		for(int i=head[s];~i;i=edge[i].nxt)
		{
			if(edge[i].f>0)
			{
				flag=1;
				break;
			}
		}
		if(flag)
			printf("Impossible\n");
		else
		{
			printf("%d\n",edge[e-1].f);
			for(int i=0;i<m;i++)
			{
				i+1==m?printf("%d\n",edge[(i<<1)|1].f+low[i]):printf("%d ",edge[(i<<1)|1].f+low[i]);
			}
		}
	}
	return 0;
}
