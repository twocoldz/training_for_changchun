/*
*
*   author : twocoldz
*   date : Thu, 28 Nov 2013 14:37:00 +0800 
*   lca 求turn的次数 
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
const int dx[]={0,1,0,-1};
const int dy[]={-1,0,1,0};
const int N=100005;
struct node
{
    int v,nxt;
}edge[N*2];
struct P
{
    int x,y;
}p[N];
int head[N*2];
int dis[N];
int ans[N],f[N],dir[N];
bool vis[N];
char **map;
int **id;
int n,m,cnt,e;

void Init()
{
    e=0;
    memset(head,-1,sizeof(head));
    for(int i=0;i<=cnt;i++)
	    f[i]=i;
}

void AddQuery(int u,int v)
{
    edge[e].v=v;
    edge[e].nxt=head[u];
    head[u]=e++;
}

bool Judge(int x,int y)
{
    if(x<0||x>=n||y<0||y>=m)
        return false;
    return true;
}

int find(int x)
{
    int fa=f[x];
    if(fa==f[fa])
    {
        f[x]=fa;
    }
    else
    {
        f[x]=find(f[x]);
        dir[x]=dir[fa];
    }
    return f[x];
}

void Bfs(int x,int y)
{
    queue<int> q;
    int sx=x,sy=y;
    memset(dis,-1,sizeof(int)*(cnt+2));
	dis[id[x][y]]=0;
	for(int i=0;i<4;i++)
	{
		int tx=x+dx[i],ty=y+dy[i];
		while(Judge(tx,ty)&&map[tx][ty]=='#'&&dis[id[tx][ty]]==-1)
		{
			dis[id[tx][ty]]=0;
			q.push(tx*m+ty);
			tx+=dx[i],ty+=dy[i];
		}
	}
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		x=u/m;
		y=u%m;
		for(int i=0;i<4;i++)
		{
			int tx=x+dx[i],ty=y+dy[i];
			while(Judge(tx,ty)&&map[tx][ty]=='#'&&dis[id[tx][ty]]==-1)
			{
				dis[id[tx][ty]]=dis[id[x][y]]+1;
				q.push(tx*m+ty);
				tx+=dx[i],ty+=dy[i];
			}
		}
	}
	dis[id[sx][sy]]=-1;
}

void tarjan(int sx,int sy,int fa)
{
    int u=id[sx][sy];
    vis[u]=1;
    for(int i=head[u];~i;i=edge[i].nxt)
    {
        int v=edge[i].v;
        if(vis[v]&&ans[i>>1]==-1)
        {
            int x;
            if(f[v]!=v)
            {
                x=find(v);
                int vvx=p[x].x+dx[dir[v]],vvy=p[x].y+dy[dir[v]];
                int uux=p[x].x+dx[dir[x]],uuy=p[x].y+dy[dir[x]];
                int vvid=id[vvx][vvy],uuid=id[uux][uuy];
                ans[i>>1]=dis[u]+dis[v]-dis[vvid]-dis[uuid];
                if(abs(dir[v]-dir[x])!=2)
                    ans[i>>1]++;
            }
            else
            {
                x=v;
                int vx=p[x].x,vy=p[x].y;
                int vvx=vx+dx[dir[x]],vvy=vy+dy[dir[x]];
                int vvid=id[vvx][vvy];
                if(dis[vvid]!=dis[x])
                    ans[i>>1]=max(0,dis[u]-dis[x]-1);
                else
                    ans[i>>1]=max(0,dis[u]-dis[x]);
            }
        }
    }
    for(int i=0;i<4;i++)
    {
        int x=sx+dx[i],y=sy+dy[i];
        dir[u]=i;
        if(Judge(x,y)&&map[x][y]=='#'&&!vis[id[x][y]])
        {
            int v=id[x][y];
            tarjan(x,y,u);
            f[v]=u;
            dir[v]=i;
        }
    }
}

int main()
{
    int Q,a,b,c,d;
	scanf("%d %d",&n,&m);
    map = new char* [n+2];
	id = new int *[n+2];
	for(int i=0;i<n+2;i++)
	{
		map[i]=new char [m+2];
		id[i]=new int [m+2];
		memset(map[i],'\0',sizeof(map[i]));
		memset(id[i],0,sizeof(id[i]));
	}
	cnt=0;
	for(int i=0;i<n;i++)
	{
		scanf("%s",map[i]);
		for(int j=0;j<m;j++)
		{
			if(map[i][j]=='#')
			{
				id[i][j]=++cnt;
				p[cnt].x=i;
				p[cnt].y=j;
			}
		}
	}
    Bfs(p[1].x,p[1].y);
    scanf("%d",&Q);
    Init();
    memset(ans,-1,sizeof(int)*Q);
    for(int i=0;i<Q;i++)
    {
        scanf("%d %d %d %d",&a,&b,&c,&d);
        a--,b--,c--,d--;
        int x=id[a][b],y=id[c][d];
        if(x==y)
            ans[i]=0;
        AddQuery(x,y);
        AddQuery(y,x);
    }
    memset(vis,0,sizeof(vis));
    tarjan(p[1].x,p[1].y,-1);
    for(int i=0;i<Q;i++)
    {
        printf("%d\n",ans[i]);
    }
	return 0;
}
