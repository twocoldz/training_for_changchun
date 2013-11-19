/*
*
*   author : twocolda
*   date : Tue, 19 Nov 2013 12:59:22 +0800 
*   无定根最小生成树
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#define inf 0x3f3f3f3f
using namespace std;
const int N=1005;
struct node
{
	int u,v,cost;
}edge[N*N];
int in[N],id[N],pre[N];
int vis[N];
int n,m,minroot;

int Directed_MST(int root,int n,int m)
{
	int ans=0;
	while(true)
	{
		int nodecnt=0;
		for(int i=0;i<n;i++)
			in[i]=inf;
		memset(pre,-1,sizeof(pre));
		for(int i=0;i<m;i++)
		{
			//printf("%d %d\n",edge[i].u,edge[i].v);
			if(edge[i].v!=edge[i].u&&in[edge[i].v]>edge[i].cost)
			{
				in[edge[i].v]=edge[i].cost;
				pre[edge[i].v]=edge[i].u;
				if(edge[i].u==root)
					minroot=i;
			}
		}
		for(int i=0;i<n;i++)
			if(i!=root&&pre[i]==-1)
				return -1;
		memset(vis,-1,sizeof(vis));
		memset(id,-1,sizeof(id));
		in[root]=0;
		for(int i=0;i<n;i++)
		{
			ans+=in[i];
			int v=i;
			while(vis[v] != i && id[v] == -1 && v != root)
			{
				vis[v]=i;
				v=pre[v];
			}
			//printf("root=%d v=%d\n",root,v);
			if(v!=root&&id[v]==-1)
			{
				for(int j=pre[v];j!=v;j=pre[j])
					id[j]=nodecnt;
				id[v]=nodecnt++;
			}
		}
		if(nodecnt==0)
			break;
		for(int i=0;i<n;i++)
			if(id[i]==-1)
				id[i]=nodecnt++;
		int j=0;
		for(int i=0;i<m;i++)
		{
			int v=edge[i].v;
			edge[i].u=id[edge[i].u];
			edge[i].v=id[edge[i].v];
			if(edge[i].u!=edge[i].v)
				edge[i].cost-=in[v];
		}
		root=id[root];
		n=nodecnt;
	}
	return ans;
}

int main()
{
	while(scanf("%d %d",&n,&m)!=EOF)
	{
		int r=0;
		for(int i=0;i<m;i++)
		{
			scanf("%d %d %d",&edge[i].u,&edge[i].v,&edge[i].cost);
			r+=edge[i].cost;
		}
		r++;
		int mm=m;
		for(int i=0;i<n;i++)
		{
			edge[m].u=n;
			edge[m].v=i;
			edge[m++].cost=r;
		}
		int ans=Directed_MST(n,n+1,m);
		if(ans==-1||ans>=r*2)
			printf("impossible\n");
		else
			printf("%d %d\n",ans-r,minroot-mm);
		puts("");
	}
	return 0;
}
