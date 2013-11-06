/*
*
*	author : twocoldz
*   date : Wed, 06 Nov 2013 12:25:06 +0800 
*   求割点去掉后能分为几个联通块，注意根与非根的区别
*
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=10005;
struct node
{
	int v,nxt;
}edge[N*100];
int head[N];
int dfn[N],low[N],cut[N];
int vis[N];
int n,m,e;
int num,cnt;

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
				cut[u]++;
		}
		else if(vis[v]==1)
			low[u]=min(low[u],dfn[v]);
	}
	vis[u]=2;
	if(fa==-1)
		cut[u]=son;
	else
		cut[u]++;
}

void GetCut()
{
	memset(cut,0,sizeof(cut));
	memset(dfn,0,sizeof(dfn));
	memset(vis,0,sizeof(vis));
	cnt=0;
	for(int i=0;i<n;i++)
	{
		if(!dfn[i])
			num=0,cnt++,tarjan_cut(i,-1);
	}
	int ans=0;
	for(int i=0;i<n;i++)
	{
		if(cut[i])
			ans=max(ans,cut[i]-1);
	}
	printf("%d\n",ans+cnt);
}

int main() 
{
	// your code goes here
	while(scanf("%d %d",&n,&m)==2&&(m+n))
	{
		if(m==0)
		{
			printf("%d\n",n-1);
			continue;
		}
		Init();
		int a,b;
		for(int i=0;i<m;i++)
		{
			scanf("%d %d",&a,&b);
			AddEdge(a,b);
			AddEdge(b,a);
		}
		GetCut();
	}
	return 0;
}
