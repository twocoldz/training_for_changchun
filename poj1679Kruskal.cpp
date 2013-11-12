/*
*
*   author : twocoldz
*   date : Wed, 13 Nov 2013 01:53:59 +0800 
*   次小生成树 Kruskal实现
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#define inf 0x3f3f3f3f
using namespace std;
const int N=105;
struct node
{
	int v,u,w,nxt;
}E[N*N],edge[N*N],tedge[N*N];
int head[N],thead[N];
int fa[N];
int num[N];
int n,m,e,diff;

bool cmp(node a,node b)
{
	return a.w<b.w;
}

void Init()
{
	e=0;
	memset(head,-1,sizeof(head));
	memset(thead,-1,sizeof(thead));
	for(int i=1;i<=n;i++)
		num[i]=1,fa[i]=i;
}

void AddEdge(int u,int v,int w,int *head,struct node *edge)
{
	edge[e].v=v;
	edge[e].u=u;
	edge[e].w=w;
	edge[e].nxt=head[u];
	head[u]=e++;
}

int Find(int x)
{
	if(x!=fa[x])
		fa[x]=Find(fa[x]);
	return fa[x];
}

void UpdateDiff(int u,int y,int w,int k)
{
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		if((i>>1)!=k)
		{
			int v=Find(edge[i].v);
			if(v==y)
				diff=min(diff,w-edge[i].w);//printf("u=%d v=%d w=%d %d\n",u,edge[i].v,w,edge[i].w);
		}
	}
}

void Kruskal()
{
	int cnt=0,ans=0;
	diff=inf,e=0;
	for(int i=0;cnt+1<n&&i<m;i++)
	{
		int fx=Find(E[i].u);
		int fy=Find(E[i].v);
		if(fx!=fy)
		{
			ans+=E[i].w;
			cnt++;
			if(num[fx]>num[fy])
				swap(fx,fy);
			//printf("%d %d\n",fx,fy);
			UpdateDiff(fx,fy,E[i].w,i);
			for(int j=thead[fx];~j;j=tedge[j].nxt)
				UpdateDiff(tedge[j].v,fy,E[i].w,i);
			for(int j=thead[fx];~j;j=tedge[j].nxt)
				AddEdge(fy,tedge[j].v,1,thead,tedge);
			AddEdge(fy,fx,1,thead,tedge);
			fa[fx]=fy;
			num[fy]+=num[fx];
		}
	}
	if(diff)
		printf("%d\n",ans);
	else
		printf("Not Unique!\n");
}

int main()
{
	int cases;
	scanf("%d",&cases);
	while(cases--)
	{
		scanf("%d %d",&n,&m);
		Init();
		for(int i=0;i<m;i++)
		{
			scanf("%d %d %d",&E[i].u,&E[i].v,&E[i].w);
			AddEdge(E[i].u,E[i].v,E[i].w,head,edge);
			AddEdge(E[i].v,E[i].u,E[i].w,head,edge);
		}
		sort(E,E+m,cmp);
		Kruskal();
	}
	return 0;
}

