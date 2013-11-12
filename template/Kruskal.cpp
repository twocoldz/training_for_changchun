#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=1010;
const int M=15010;
struct node
{
	int u,v,w;
	bool operator < (const node &a) const
	{
		return w<a.w;
	}
}edge[M];
int fa[N],n,m;
int vis[M];
int find(int x)
{
	if(x!=fa[x])
		fa[x]=find(fa[x]);
	return fa[x];
}



int main(int argc, char *argv[])
{
	while(scanf("%d %d",&n,&m)==2)
	{
		for(int i=1;i<=n;i++) fa[i]=i;
		for(int i=1;i<=m;i++)
		{
			vis[i]=0;
			scanf("%d %d %d",&edge[i].u,&edge[i].v,&edge[i].w);
		}
		sort(edge+1,edge+1+m);
		int ans=0;
		for(int i=1;i<=m;i++)
		{
			int fx=find(edge[i].u);
			int fy=find(edge[i].v);
			if(fx!=fy)
			{
				vis[i]=1;
				fa[fx]=fy;
				ans=edge[i].w;
			}
		}
		printf("%d\n",ans);
		printf("%d\n",n-1);
		for(int i=1;i<=m;i++)
		{
			if(vis[i])
				printf("%d %d\n",edge[i].u,edge[i].v);
		}
	}
	return 0;
}
