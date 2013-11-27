/*
*
*    author :twocoldz
*    date : Wed, 27 Nov 2013 10:25:20 +0800 
*    2-SAT 
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=100005;
struct node
{
	int u,v,nxt;
}edge[N*10];
int head[N*2];
int dfn[N*2],low[N*2],ins[N*2],wh[N*2],stack[N*2];
int dif[2][3];
int n,m,flag,e;
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
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);
}

int x[2];

int main()
{
	int cases;
	scanf("%d",&cases);
	while(cases--)
	{
		flag=0;
		scanf("%d %d",&n,&m);
		Init();
		int k,a;
		for(int i=1;i<=m;i++)
		{
			scanf("%d",&k);
			if(k>5)
				flag=1;
			x[0]=x[1]=0;
			while(k--)
			{
				scanf("%d",&a);
				if(flag)
					continue;
				if(x[a%2]>1)
				{
					flag=1;
					continue;
				}
				dif[a%2][x[a%2]++]=a;
			}
			if(flag)
				continue;
			if(x[0]==2)
			{
				AddEdge(dif[0][0],dif[0][1]+n);
				AddEdge(dif[0][1],dif[0][0]+n);
				AddEdge(dif[0][0]+n,dif[0][1]);
				AddEdge(dif[0][1]+n,dif[0][0]);
			}
			if(x[1]==2)
			{
				AddEdge(dif[1][0],dif[1][1]+n);
				AddEdge(dif[1][1],dif[1][0]+n);
				AddEdge(dif[1][0]+n,dif[1][1]);
				AddEdge(dif[1][1]+n,dif[1][0]);
			}
		}
		if(flag)
		{
			printf("rejected\n");
			continue;
		}
		for(int i=1;i<=n;i++)
		{
			if(i&1)
			{
				if(i>1)
					AddEdge(i+n,i-1+n);
				if(i<n)
					AddEdge(i+n,i+1+n);	
			}
			else
			{
				if(i>1)
					AddEdge(i,i-1);
				else
					AddEdge(i,i+1);
			}
		}
		SCC();
		for(int i=1;i<=n;i++)
		{
			if(wh[i]==wh[i+n])
				flag=1;
		}
		if(flag)
			printf("rejected\n");
		else
			printf("approved\n");
	}
	return 0;
}
