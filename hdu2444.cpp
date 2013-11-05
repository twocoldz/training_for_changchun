#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=205;
struct node
{
	int v,nxt;
}edge[N*N];
int head[N];
int mk[N];
int c[N];
bool vis[N];
int n,m,e,flag;

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
				return 1;
			}
		}
	}
	return 0;
}

void Dfs(int u,int fa)
{
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		int v=edge[i].v;
		if(v!=fa)
		{
			if(c[v]==-1)
			{
				c[v]=!c[u];
				Dfs(v,u);
			}
			else if(c[v]==c[u])
			{
				flag=0;
				return ;
			}
		}
	}
	return ;
}

bool Judge()
{
	flag=1;
	for(int i=1;i<=n;i++)
	{
		if(c[i]==-1)
		{
			c[i]=0;
			Dfs(i,-1);
			if(flag==0)
				break;
		}
	}
	return flag;
}

int main()
{
	while(scanf("%d%d",&n,&m)==2)
	{
		Init();
		int a,b;
		for(int i=0;i<m;i++)
		{
			scanf("%d %d",&a,&b);
			AddEdge(a,b);
			AddEdge(b,a);
		}
		memset(c,-1,sizeof(c));
		if(Judge())
		{
			int ans=0;
			memset(mk,-1,sizeof(mk));
			for(int i=1;i<=n;i++)
			{
				if(!c[i])
				{
					memset(vis,0,sizeof(vis));
					if(Hungary(i))
						ans++;
				}
			}
			printf("%d\n",ans);
		}
		else
		{
			printf("No\n");
		}
	}
}
