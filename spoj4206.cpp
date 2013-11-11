/*
*
*    author : twocoldz
*    date : Mon, 11 Nov 2013 14:53:40 +0800 
*    二分图最大匹配 hk算法
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=50005;
struct node
{
	int v,nxt;
}edge[N*3];
int head[N];
int mx[N],my[N];
int dx[N],dy[N];
int q[N];
int n,m,e,k;

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

bool Bfs()
{
	memset(dx,0,sizeof(dx));
	memset(dy,0,sizeof(dy));
	int h=0,t=0;
	for(int i=1;i<=n;i++)
		if(mx[i]==-1)
			q[t++]=i;
	int yes=0;
	while(h<t)
	{
		int u=q[h++];
		for(int i=head[u];~i;i=edge[i].nxt)
		{
			int v=edge[i].v;
			if(!dy[v])
			{
				dy[v]=dx[u]+1;
				if(my[v]==-1)
					yes++;
				else
				{
					dx[my[v]]=dy[v]+1;
					q[++t]=my[v];
				}
			}
		}
	}
	return yes;
}

bool Dfs(int u)
{
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		int v=edge[i].v;
		if(dy[v]==dx[u]+1)
		{
			dy[v]=0;
			if(my[v]==-1||Dfs(my[v]))
			{
				my[v]=u;
				mx[u]=v;
				return 1;
			}
		}
	}
	return 0;
}

int main()
{
	while(scanf("%d %d %d",&n,&m,&k)==3)
	{
		int a,b;
		Init();
		for(int i=0;i<k;i++)
		{
			scanf("%d %d",&a,&b);
			AddEdge(a,b);
		}
		memset(mx,-1,sizeof(mx));
		memset(my,-1,sizeof(my));
		int ans=0;
		while(Bfs())
		{
			for(int i=1;i<=n;i++)
				if(mx[i]==-1&&Dfs(i))
					ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
