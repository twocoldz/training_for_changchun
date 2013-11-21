/*
*
*   author : twocoldz
*   date : Thu, 21 Nov 2013 22:14:21 +0800 
*   最短路，二分
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define inf 0x3f3f3f3f
#define eps 1e-7
#define MUL 1e9
using namespace std;
const int N=10005;
struct node
{
	int v,u,nxt;
	double s,len;
}edge[N*2];
int head[N];
double dis[N];
int pre[N],path[N],choose[N];
bool inq[N];
int n,m,e;

void Init()
{
	e=0;
	memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v,double s,double len)
{
	edge[e].v=v;
	edge[e].u=u;
	edge[e].s=s;
	edge[e].len=len;
	edge[e].nxt=head[u];
	head[u]=e++;
}

void Bfs(double add)
{
	for(int i=0;i<=n;i++)
		dis[i]=1e50;
	queue<int> q;
	q.push(n);
	inq[n]=1;
	dis[n]=0;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		inq[u]=0;
		for(int i=head[u];~i;i=edge[i].nxt)
		{  
			int v=edge[i].v;
			if(dis[v]>dis[u]+(edge[i].len)*MUL/(edge[i].s+add))
			{
				dis[v]=dis[u]+(edge[i].len)*MUL/(edge[i].s+add);
				pre[v]=i;
				if(!inq[v])
					q.push(v),inq[v]=1;
			}
		}
	}
}

int main()
{
	int a,b;
	double s,len,T;
	while(scanf("%d %d",&n,&m)==2)
	{
		Init();
		for(int i=0;i<m;i++)
		{
			scanf("%d %d %lf %lf\n",&a,&b,&s,&len);
			AddEdge(a,b,s,len);
			AddEdge(b,a,s,len);
		}
		scanf("%lf",&T);
		T*=MUL;
		double l=0,r=1e8,ans;
		while(l<=r)
		{
			double mid=(l+r)/2;
			Bfs(mid);
			//printf("%lf\n",dis[1]);
			if(dis[1]<=T)
			{
				ans=mid;
				for(int i=1;i<=n;i++)
					path[i]=pre[i];
				r=mid-eps;
			}
			else
			{
				l=mid+eps;
			}
		}
		printf("%.6f",ans);
		int s=1,t=n,num=0;
		while(s!=t)
		{
			num++;
			choose[num]=(path[s]>>1)+1;
			s=edge[path[s]].u;
		}
		printf(" %d\n",num);
		for(int i=1;i<=num;i++)
		{
			i==num?printf("%d\n",choose[i]):printf("%d ",choose[i]);
		}
	}
	return 0;
}
