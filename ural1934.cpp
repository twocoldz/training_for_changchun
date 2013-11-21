/*
* 
*  author : twocoldz 
*  date : Thu, 21 Nov 2013 22:15:23 +0800 
*  最短路
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
//#include <unistd.h>
#define inf 0x3f3f3f3f
using namespace std;
const int N=100005;
struct node
{
	int v,nxt;
	double p;
}edge[N*2];
int head[N];
double r[N];
int dis[N],inq[N];
int pre[N];
int n,m,e;

void Init()
{
	e=0;
	memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v,int p)
{
	edge[e].v=v;
	edge[e].p=1.0*p/100;
	edge[e].nxt=head[u];
	head[u]=e++;
}

void Bfs(int s,int t)
{
	memset(dis,inf,sizeof(dis));
	dis[s]=1;
	r[s]=0;
	queue<int> q;
	q.push(s);
	memset(inq,0,sizeof(inq));
	inq[s]=1;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		inq[u]=0;
		for(int i=head[u];~i;i=edge[i].nxt)
		{
			int v=edge[i].v;
			if(dis[v]>dis[u]+1||(dis[v]==dis[u]+1&&(r[u]+(1-r[u])*edge[i].p)<r[v]))
			{
				dis[v]=dis[u]+1;
				r[v]=r[u]+(1-r[u])*edge[i].p;
				pre[v]=u;
				if(!inq[v])
					q.push(v),inq[v]=1;
			}
		}
	}
}

int main()
{
	int s,t,a,b,p;
	while(scanf("%d %d",&n,&m)==2)
	{
		scanf("%d %d",&s,&t);
		Init();
		for(int i=0;i<m;i++)
		{
			scanf("%d %d %d",&a,&b,&p);
			AddEdge(a,b,p);
			AddEdge(b,a,p);
		}
		Bfs(t,s);
		printf("%d %lf\n",dis[s],r[s]);
		//sleep(10);
		while(s!=t)
		{
			printf("%d ",s);
			s=pre[s];
		}
		printf("%d\n",t);
	}
	return 0;
}
