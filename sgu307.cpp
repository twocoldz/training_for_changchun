/*
*
*   author : twocoldz
*   date : Tue, 26 Nov 2013 19:52:09 +0800 
*   2-SAT 数学关系 建图 输出可行解
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int N=605;
struct node
{
	int u,v,nxt;
}edge[N*N*4];
int head[N*2];
int a[N][N];
int sum[N][N];
int c[N][N];
int n,m,e;
int dfn[N*2],low[N*2],stack[N*2],deg[N*2];
int wh[N*2],op[N*2],col[N*2],ans[N*2];
bool ins[N*2];
int num,cnt,top;

void Init()
{
	e=0;
	memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v)
{
	edge[e].u=u;
	edge[e].v=v;
	edge[e].nxt=head[u];
	head[u]=e++;
}

void tarjan(int u)
{
	dfn[u]=low[u]=++num;
	stack[++top]=u;
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
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		int j;
		cnt++;
		op[cnt]=u;
		do
		{
			j=stack[top--];
			ins[j]=0;
			wh[j]=cnt;
		}while(j!=u);
	}
}

void SCC()
{
	memset(dfn,0,sizeof(dfn));
	memset(ins,0,sizeof(ins));
	num=cnt=top=0;
	for(int i=0;i<(n+m-2)*2;i++)
		if(!dfn[i])
			tarjan(i);
}

bool solve()
{
	for (int stop=0;stop<2 ; stop++ )
	{
		memset(c,0,sizeof(c));
		c[0][0]=stop;
		for(int i=1;i<n;i++)
		{
			for(int j=1;j<m;j++)
				c[i][j]=sum[i][j]-c[i-1][j]-c[i][j-1]-c[i-1][j-1];
		}
		Init();
		for(int i=1;i<n;i++)
		{
			for(int j=1;j<m;j++)
			{
				int x=(i&1)?-1:1;
				int y=(j&1)?-1:1;
				int z=(i+j+1)%2?-1:1;
				for(int k=0;k<2;k++)
				{
					for(int l=0;l<2;l++)
					{
						int tmp=c[i][j]+x*l+y*k;
						if(tmp<0||tmp>1)
						{
							int u=((i-1)<<1)+k;
							int v=((j-1+n-1)<<1)+l;
							AddEdge(u,v^1);
							AddEdge(v,u^1);
						}
					}
				 }
			}
		}
		SCC();
		int f=0;
		for(int i=0;i<(n+m-2)*2;i+=2)
			if(wh[i]==wh[i|1])
			{
				f=1;
				break;
			}
		if(f)
			continue;
		memset(col,-1,sizeof(col));
		for(int i=1;i<=cnt;i++)
			if(col[i]==-1)
				col[i]=1,col[wh[op[i]^1]]=0;
		for(int i=1;i<n;i++)
			c[i][0]=col[wh[((i-1)<<1)|1]];
		for(int i=1;i<m;i++)
			c[0][i]=col[wh[((i+n-2)<<1)|1]];
		c[0][0]=stop;
		for(int i=1;i<n;i++)
			for(int j=1;j<m;j++)
				c[i][j]=sum[i][j]-c[i-1][j]-c[i][j-1]-c[i-1][j-1];
		return 1;
	}
	return false;
}

int main()
{
	while(scanf("%d %d",&n,&m)==2)
	{
		char str[N];
		for(int i=1;i<n;i++)
		{
			scanf("%s",str);
			for(int j=1;j<m;j++)
				sum[i][j]=str[j-1]-'0';
		}
		if(solve())
			for(int i=0;i<n;i++,puts(""))
				for(int j=0;j<m;j++)
					printf("%d",c[i][j]);
		else
			puts("CORRUPT");
	}
	return 0;
}
