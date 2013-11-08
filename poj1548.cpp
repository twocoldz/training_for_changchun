/*
*   author : twocoldz
*   date : Fri, 08 Nov 2013 14:33:23 +0800 
*   最小路径覆盖
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=900;
struct node
{
	int v,nxt;
}edge[N*N];
int head[N];
int mk[N];
bool vis[N];
int x[N],y[N];
int n,m,e;

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

bool Hungary(int u)
{
	for(int i=head[u];~i;i=edge[i].nxt)
	{
		int v=edge[i].v;
		if(!vis[v])
		{
			vis[v]=1;
			if(mk[v]==-1||Hungary(mk[v]))
			{
				mk[v]=u;
				return 1;
			}
		}
	}
	return 0;
}

int main()
{
	int a,b;
	while(scanf("%d %d",&a,&b)&&(a!=-1||b!=-1))
	{
		int cnt=0;
		x[cnt]=a;
		y[cnt++]=b;
		while(scanf("%d %d",&a,&b)&&(a+b))
		{
			x[cnt]=a;
			y[cnt++]=b;
		}
		Init();
		for(int i=0;i<cnt;i++)
		{
			for(int j=0;j<cnt;j++)
			{
				if(i==j)
					continue;
				else
				{
					if(x[j]>=x[i]&&y[j]>=y[i])
					{
						AddEdge(i,j);
					}
				}
			}
		}
		int ans=0;
		memset(mk,-1,sizeof(mk));
		for(int i=0;i<cnt;i++)
		{
			memset(vis,0,sizeof(vis));
			if(Hungary(i))
				ans++;
		}
		printf("%d\n",cnt-ans);
	}
	return 0;
}
