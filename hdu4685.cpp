/*
*    author : twocodlz
*    date : Tue, 05 Nov 2013 18:27:22 +0800 
*    强联通图，公主和王子没有匹配时，需要虚拟匹配
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=505;
struct node
{
	int v,nxt;
}edge[N*N];
int head[N];
int mk[N],mk2[N];
bool vis[N];
int love[N][N];
int dfn[N],low[N],stack[N],wh[N];
bool ins[N];
int n,m,e;
int num,cnt,top;

void Init()
{
	e=0;
	memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v)
{
	//printf("u=%d v=%d\n",u,v);
	edge[e].v=v;
	edge[e].nxt=head[u];
	head[u]=e++;
}

bool Hungary(int u)
{
	for(int i=1;i<=love[u][0];i++)
	{
		int v=love[u][i];
		if(!vis[v])
		{
			vis[v]=1;
			if(mk[v]==-1||Hungary(mk[v]))
			{
				mk[v]=u;
				mk2[u]=v;
				return 1;
			}
		}
	}
	return 0;
}

void tarjan(int u)
{
	dfn[u]=low[u]=++num;
	stack[top++]=u;
	ins[u]=1;
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		int v=edge[i].v;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(ins[v])
		{
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u])
	{
		int j;
		cnt++;
		do
		{
			j=stack[--top];
			ins[j]=0;
			wh[j]=cnt;
		}while(j!=u);
	}
}

void SCC()
{
	memset(dfn,0,sizeof(dfn));
	memset(ins,0,sizeof(ins));
	memset(wh,0,sizeof(wh));
	num=cnt=top=0;
	for(int i=1;i<=m+1;i++)
	{
		if(!dfn[i])
		{
			tarjan(i);
		}
	}
}

int main()
{
	int cases,id=1;
	scanf("%d",&cases);
	while(cases--)
	{	
		Init();
		printf("Case #%d:\n",id++);
		scanf("%d %d",&n,&m);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",love[i]+0);
			for(int j=1;j<=love[i][0];j++)
			{
				scanf("%d",love[i]+j);
			}
		}
		memset(mk,-1,sizeof(mk));
		memset(mk2,-1,sizeof(mk2));
		for(int i=1;i<=n;i++)
		{
			memset(vis,0,sizeof(vis));
			Hungary(i);
		}
		for(int i=1;i<=n;i++)
		{
			if(mk2[i]==-1)
			{
				mk2[i]=m+1;   //key point
			}
			for(int j=1;j<=love[i][0];j++)
			{
				if(mk2[i]!=love[i][j])
					AddEdge(mk2[i],love[i][j]);
			}
			if(mk2[i]!=m+1)    //key point
				AddEdge(mk2[i],m+1);
		}
		for(int i=1;i<=m;i++)
		{
			if(mk[i]==-1)
			{
				for(int j=1;j<=m+1;j++)
				{
					if(i!=j)
					{
						AddEdge(i,j);
					}
				}
			}
		}
		SCC();
		for(int i=1;i<=n;i++)
		{
			int ans=0;
			int tmp[N];
			for(int j=1;j<=love[i][0];j++)
			{
				if(wh[mk2[i]]==wh[love[i][j]])
					tmp[ans++]=love[i][j];
			}
			printf("%d",ans);
			sort(tmp,tmp+ans);
			for(int j=0;j<ans;j++)
				printf(" %d",tmp[j]);
			printf("\n");
		}
	}
	return 0;	
}
