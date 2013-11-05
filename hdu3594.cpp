/*
*   auther : twocoldz
*   date :Tue, 05 Nov 2013 10:15:24 +0800 
*   有向仙人掌树判定
*   定义：
*     1）是一个强联通图
*     2）每条有向边属于且仅属于一个环
*   判断方法
*     1）图中没有横叉边（搞清楚树边，横叉边，后向边
*	  2）在dfs遍历中，对于任意点v为点u的儿子，则满足low[v] <= dfn[u]
*     3）设置一个量a[u]表示u的儿子v中满足low[v] < dfn[u]的个数
*          一个量b[u]表示u的后向边的条数则，a[u] + b[u] < 2
*     参考资料：http://www.gonglin91.com/gratedcactus/
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=20005;
struct node
{
	int v,nxt;
}edge[N*3];
int head[N];
int dfn[N],low[N],stack[N];
int back[N],son[N];
bool vis[N],ins[N];
int n,m,e;
int flag,num,top,cnt;

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

void tarjan(int u)
{
	dfn[u]=low[u]=++num;
	stack[top++]=u;
	ins[u]=1;
	back[u]=son[u]=0;
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		int v=edge[i].v;
		if(vis[v])
		{
			flag=1;
			break;
		}
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
			if(low[u]>dfn[u])
			{
				flag=1;
				break;
			}
			if(low[v]<dfn[u])
				son[u]++;
		}
		else if(ins[v])
		{
			low[u]=min(low[u],dfn[v]);
			back[u]++;
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
		}while(j!=u);
	}
	vis[u]=1;
	if(son[u]+back[u]>=2)
	{
		flag=1;
	}
	return ;
}

void SCC()
{
	top=num=cnt=flag=0;
	memset(vis,0,sizeof(vis));
	memset(ins,0,sizeof(ins));
	memset(dfn,0,sizeof(dfn));
	for(int i=0;i<n;i++)
	{
		if(!dfn[i])
		{
			tarjan(i);
			if(cnt>1||flag)
			{
				break;
			}
		}
	}
	if(cnt>1||flag)
		printf("NO\n");
	else
		printf("YES\n");
}

int main()
{
	int cases;
	scanf("%d",&cases);
	while(cases--)
	{
		scanf("%d",&n);
		int a,b;
		Init();
		while(scanf("%d %d",&a,&b)&&(a+b))
		{
			AddEdge(a,b);
		}
		SCC();
	}
	return 0;
}
