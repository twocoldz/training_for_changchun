/*
*    author : twocoldz
*    date : Thu, 07 Nov 2013 22:05:29 +0800 
*    最小路径覆盖，拆点，建二分图   最小路径覆盖=V - 最大匹配
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
#define inf 0x3f3f3f3f
const int Q=25;
const int N=205;
struct node
{
	int v,nxt;
}edge[N*N];
int head[N];
int dis[N][N];
struct task
{
	int s,e,q;
}tsk[N];
int mk[N];
bool vis[N];
int n,m,e;

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
				return true;
			}
		}
	}
	return 0;
}

void Floyd()
{
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
}

int main()
{
	while(scanf("%d %d",&n,&m)&&(n+m))
	{
		int x;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
			{
				scanf("%d",&x);
				if(x==-1)
					dis[i][j]=inf;
				else
					dis[i][j]=x;
			}
		Floyd();
		int ans=0;
		for(int i=1;i<=m;i++)
		{
			scanf("%d %d %d",&tsk[i].q,&tsk[i].s,&x);
			tsk[i].e=tsk[i].s+x;
		}
		Init();
		for(int i=1;i<=m;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(i==j)
					continue;
				if(tsk[i].e+dis[tsk[i].q][tsk[j].q]<=tsk[j].s)
				{
					AddEdge(i,j);
				}
			}
		}
		memset(mk,-1,sizeof(mk));
		for(int i=1;i<=m;i++)
		{
			memset(vis,0,sizeof(vis));
			if(Hungary(i))
				ans++;
		}
		printf("%d\n",m-ans);
	}
	return 0;
}
