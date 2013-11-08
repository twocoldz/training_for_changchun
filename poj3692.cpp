/*
*
*   author : twocoldz
*   date : Sat, 09 Nov 2013 01:30:37 +0800 
*   最大团，补图，最大匹配   ans=v-补图的最大匹配
*/
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
bool vis[N];
int map[N][N];
int n,m,k,e;

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
	return false;
}

int main()
{
	int id=1;
	while(scanf("%d %d %d",&n,&m,&k)==3&&(n+m+k))
	{	
		Init();
		int a,b;
		memset(map,0,sizeof(map));
		for(int i=1;i<=k;i++)
		{
			scanf("%d %d",&a,&b);
			map[a][b]=1;
		}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(!map[i][j])
					AddEdge(i,j);//printf("%d %d\n",i,j);
		memset(mk,-1,sizeof(mk));
		int ans=n+m;
		for(int i=1;i<=n;i++)
		{
			memset(vis,0,sizeof(vis));
			if(Hungary(i))
				ans--;
		}
		printf("Case %d: %d\n",id++,ans);
	}
	return 0;
}
