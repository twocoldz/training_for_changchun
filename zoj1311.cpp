/*
*   author : twcoldz
*   date :Wed, 06 Nov 2013 00:37:16 +0800 
*   求割点，对根和非根分别处理。这题读入是个坑
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=105;
struct node
{
	int v,nxt;
}edge[N*N];
int head[N];
int dfn[N],low[N],stack[N];
bool cut[N];
int vis[N];
int n,m,e;
int num,top,cnt,pos;
char str[N*N];

char *read(char str[],char *p)
{
    while(*p && *p!=' ') p++;
    while(*p && *p==' ') p++;
    return p;
}

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

int change(char *str)
{
	int x=0;
	for(;str[pos]>='0'&&str[pos]<='9';pos++)
	{
		x=x*10+str[pos]-'0';
	}
	pos++;
	return x;
}

void tarjan_cut(int u,int fa)
{
	dfn[u]=low[u]=++num;
	vis[u]=1;
	int son=0;
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		int v=edge[i].v;
		if(v==fa)
			continue;
		if(!vis[v])
		{
			son++;
			tarjan_cut(v,u);
			low[u]=min(low[u],low[v]);
			if(fa!=-1&&low[v]>=dfn[u])
				cut[u]=1;
		}
		else if(vis[v]==1)
			low[u]=min(low[u],dfn[v]);
	}
	vis[u]=2;
	if(fa==-1&&son>1)
		cut[u]=1;
}

void GetCut()
{
	memset(dfn,0,sizeof(dfn));
	memset(cut,0,sizeof(cut));
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
	{
		if(!dfn[i])
		{
			num=0;
			tarjan_cut(i,-1);
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		if(cut[i])
			ans++;
	printf("%d\n",ans);
}

int main()
{
	while(scanf("%d",&n)==1&&n)
	{
		getchar();
		Init();
		int x,y;
		while(scanf("%d",&x)&&x)
		{
			gets(str);
			char *p;
			for(p=read(str,str);sscanf(p,"%d",&y)!=EOF;p=read(str,p))
			{
				AddEdge(x,y);
				AddEdge(y,x);
			}
		}
		GetCut();
	}
	return 0;
}
