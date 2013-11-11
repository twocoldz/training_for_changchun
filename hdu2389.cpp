/*
*    author : twocoldz
*    date : Mon, 11 Nov 2013 16:01:35 +0800 
*    二分图最大匹配，hk算法
*    为什么要用vector建图+queue bfs才不会TLE 不科学啊 不科学
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
const int N=3005;
int mx[N],my[N];
int dx[N],dy[N];
vector<int> vv[N];
int n,m,e,k;

bool Bfs()
{
	memset(dx,0,sizeof(dx));
	memset(dy,0,sizeof(dy));
	queue<int> q;
	for(int i=1;i<=n;i++)
		if(mx[i]==-1)
			q.push(i);
	int yes=0;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=0;i<vv[u].size();i++)
		{
			int v=vv[u][i];
			if(!dy[v])
			{
				dy[v]=dx[u]+1;
				if(my[v]==-1)
					yes++;
				else
				{
					dx[my[v]]=dy[v]+1;
					q.push(my[v]);
				}
			}
		}
	}
	return yes;
}

bool Dfs(int u)
{
	for(int i=0;i<vv[u].size();i++)
	{
		int v=vv[u][i];
		if(dy[v]==dx[u]+1)
		{
			dy[v]=0;
			if(my[v]==-1||Dfs(my[v]))
			{
				my[v]=u;
				mx[u]=v;
				return 1;
			}
		}
	}
	return 0;
}

int gx[N],gy[N],ux[N],uy[N],sp[N];
inline int sqr(int x)
{
	return x*x;
}
int main()
{
	int cases,id=1;
	scanf("%d",&cases);
	while(cases--)
	{
		int t;
		scanf("%d",&t);
		scanf("%d",&m);
		for(int i=1;i<=m;i++)
		{
			scanf("%d %d %d",gx+i,gy+i,sp+i);
		}
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d %d",ux+i,uy+i);
		}
		memset(vv,0,sizeof(vv));
		for(int i=1;i<=m;i++)
		{
			for(int j=1;j<=n;j++)
			{
				int dis=sqr(gx[i]-ux[j])+sqr(gy[i]-uy[j]);
				int spt=sqr(sp[i]*t);
				if(dis<=spt)
				{
					//AddEdge(i,j);
					vv[j].push_back(i);
					//printf("guest=%d umbler=%d\n",i,j);
				}
			}
		}
		memset(mx,-1,sizeof(mx));
		memset(my,-1,sizeof(my));
		int ans=0;
		while(Bfs())
		{
			for(int i=1;i<=n;i++)
				if(mx[i]==-1&&Dfs(i))
					ans++;
		}
		printf("Scenario #%d:\n",id++);
		printf("%d\n\n",ans);
	}
	return 0;	
}
