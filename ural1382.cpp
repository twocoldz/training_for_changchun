/*
*
*   author : twocoldz
*   date : Tue, 26 Nov 2013 12:15:25 +0800 
*   2-SAT 重建图 注意边复用的时候顺序问题
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
const int N=1005;
struct node
{
	int v,nxt,u;
}edge[N*N];
int head[N*2];
int dfn[N*2],low[N*2],wh[N*2];
int stack[N*2];
int deg[N*2],col[N*2],op[N*2];
bool ins[N*2];
int n,m,e;
int num,top,cnt;

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
			low[u]=min(low[u],dfn[v]);
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
	for(int i=0;i<n+n;i++)
		if(!dfn[i])
			tarjan(i);
}

void TopSort()
{
	queue<int> q;
	for(int i=1;i<=cnt;i++)
		if(deg[i]==0)
			q.push(i);
	memset(col,0,sizeof(col));
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		if(col[u]==0)
		{
			col[u]=1;
			col[op[u]]=2;
		}
		for(int i=head[u];~i;i=edge[i].nxt)
		{
			int v=edge[i].v;
			deg[v]--;
			if(deg[v]==0)
				q.push(v);
		}
	}
}

int x[N+N],y[N+N];

int main()
{
	while(scanf("%d",&n)==1)
	{
		Init();
		int a,b,c;
		for(int i=0;i<n;i++)
		{
			scanf("%d %d %d",&a,&b,&c);
			a--,b--,c--;
			x[i]=i,y[i]=a,x[i+n]=b,y[i+n]=c;
		}
		for(int i=0;i<n+n;i++)
		{
			for(int j=i+1;j<n+n;j++)
			{
				if((x[i]==x[j]&&y[i]!=y[j])||(y[i]==y[j]&&x[i]!=x[j]))
				{
					if(j<n&&i!=j+n)
						AddEdge(i,j+n);
					else
						if(j>=n&&i!=j-n)
							AddEdge(i,j-n);
					if(i<n&&j!=i+n)
						AddEdge(j,i+n);
					else
						if(i>=n&&j!=i-n)
							AddEdge(j,i-n);
				}
			}
		}
		SCC();
		for(int i=0;i<n;i++)
		{
			op[wh[i]]=wh[i+n];
			op[wh[i+n]]=wh[i];
		}
		int ee=e;
		Init();
		memset(deg,0,sizeof(deg));
		for(int i=0;i<ee;i++)
		{
			if(wh[edge[i].u]!=wh[edge[i].v])
			{
				deg[wh[edge[i].u]]++;                   //这里这句一定在前，不然edge[i].u的值会改变
				AddEdge(wh[edge[i].v],wh[edge[i].u]);   //与原来的边方向相反 
				
			}
		}
		TopSort();
		for(int i=0;i<n;i++)
		{
			i+1==n?printf("%d\n",col[wh[i]]):printf("%d ",col[wh[i]]);
		}
	}
	return 0;
}

