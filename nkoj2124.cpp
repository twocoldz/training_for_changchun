/*
*
*    author : twocoldz
*    date : Fri, 08 Nov 2013 00:59:27 +0800 
*    最小路径覆盖，最大流求解，路径输出
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <unistd.h>
#define inf 0x3f3f3f3f
using namespace std;
const int N=2005;
struct node
{
	int v,nxt,c,f;
}edge[N*N];
int head[N+N];
int dep[N+N];
int vis[N],mk[N],mk2[N];
int n,m,e;
int maxflow;

void Init()
{
	e=0;
	memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v,int w)
{
	edge[e].v=v;
	edge[e].c=w;
	edge[e].nxt=head[u];
	head[u]=e++;
}

bool Bfs(int s,int t)
{
	memset(dep,-1,sizeof(dep));
	dep[s]=0;
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head[u];~i;i=edge[i].nxt)
		{
			int v=edge[i].v;
			if(dep[v]==-1&&edge[i].c>0)
			{
				dep[v]=dep[u]+1;
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
		if(dep[s]+1==dep[v]&&edge[i].c>0)
		{
			int tmp=Dfs(v,t,min(edge[i].c,limit-cost));
			if(tmp)
			{
				edge[i].c-=tmp;
				edge[i^1].c+=tmp;
				cost+=tmp;
			}
			if(cost==limit)
				break;
		}
	}
	if(cost==0)
		dep[s]=-1;
	return cost;
}

void Dinic(int s,int t)
{
	while(Bfs(s,t))
		maxflow+=Dfs(s,t,inf);
}

bool Hungary(int u)
{
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		int v=edge[i].v;
		if(!vis[v])
		{
			vis[v]=1;
			if(mk[v]==-1||Hungary(mk[v]))
			{
				mk[v]=u;
				mk2[u]=v;
				return true;
			}
		}
	}
	return false;
}

int main()
{
	bool sq[N+N];
	memset(sq,0,sizeof(sq));
	for(int i=1;i<=60;i++)
		sq[i*i]=1;
	m=2000;
	int s=0,t=4001;
	while(scanf("%d",&n)!=EOF)
	{
		Init();
		maxflow=0;
		int ans;
		for(ans=1;;ans++)
		{
			AddEdge(s,ans,1);
			AddEdge(ans,s,0);
			AddEdge(ans+m,t,1);
			AddEdge(t,ans+m,0);
			for(int i=1;i<ans;i++)
			{
				if(sq[ans+i])
				{
					AddEdge(i,ans+m,1);
					AddEdge(ans+m,i,0);
				}
			}
			Dinic(s,t);
			if(ans-maxflow>n)
				break;
		}
		printf("%d\n",ans-1);
		Init();
		maxflow=0;
		for(int i=1;i<ans;i++)
		{
			for(int j=1;j<i;j++)
			{
				if(sq[i+j])
				{
					AddEdge(j,i,1);
				}
			}
		}
		memset(mk,-1,sizeof(mk));
		memset(mk2,-1,sizeof(mk2));
		for(int i=1;i<ans;i++)
		{
			memset(vis,0,sizeof(vis));
			Hungary(i);
		}
		for(int i=1;i<ans;i++)
		{
			if(mk[i]==-1)
			{
				int k=i;
				while(k!=-1)
				{
					k==i?printf("%d",k):printf(" %d",k);
					k=mk2[k];
				}
				printf("\n");
			}
		}
	}
	return 0;
}
