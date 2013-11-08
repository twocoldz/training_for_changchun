/*
*
*   author : twocoldz
*   date : Sat, 09 Nov 2013 00:46:12 +0800 
*   最小边覆盖，无向图，拆点，建二分图  ans=v-最大匹配/2
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=405;
struct node
{
	int v,nxt;
}edge[N*N];
int head[N];
int mk[N];
bool vis[N];
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
				return true;
			}
		}
	}
	return false;
}
char str[50][50];
const int dx[]={1,0,-1,0};
const int dy[]={0,-1,0,1};

bool Judge(int x,int y)
{
	if(x<0||x>=n||y<0||y>=m)
		return false;
	return 1;
}
int main()
{	
	int cases;
	scanf("%d",&cases);
	while(cases--)
	{
		int cnt=0;
		scanf("%d %d",&n,&m);
		Init();
		for(int i=0;i<n;i++)
		{
			scanf("%s",str[i]);
		}
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
				if(str[i][j]=='*')
				{
					cnt++;
					for(int k=0;k<4;k++)
					{
						int tx=i+dx[k];
						int ty=j+dy[k];
						if(Judge(tx,ty)&&str[tx][ty]=='*')
						{
							AddEdge(i*m+j,tx*m+ty);
						}
					}
				}
			}
		}
		int ans=0;
		memset(mk,-1,sizeof(mk));
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
				if(str[i][j]=='*')
				{
					memset(vis,0,sizeof(vis));
					ans+=Hungary(i*m+j);
				}
			}
		}
		printf("%d\n",cnt-ans/2);
	}
	return 0;
}
