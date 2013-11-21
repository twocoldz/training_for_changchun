/*
*
*   author : twocoldz
*   date : 11/20/2013  11:00:11
*   欧拉回路
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=10005;
struct node
{
    int v,nxt;
} edge[N*10];
int head[N];
int ans[N*10];
bool vis[N*10];
int n,m,e,cnt;

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

void Dfs(int u)
{
    for(int i=head[u]; ~i; i=edge[i].nxt)
    {
        if(!vis[i])
        {
            vis[i]=1;
            int v=edge[i].v;
            Dfs(v);
        }
    }
    ans[cnt++]=u;
}

int main()
{
    while(scanf("%d %d",&n,&m)==2)
    {
        Init();
        int a,b;
        for(int i=1; i<=m; i++)
        {
            scanf("%d %d",&a,&b);
            AddEdge(a,b);
            AddEdge(b,a);
        }
        cnt=0;
        memset(vis,0,sizeof(vis));
        Dfs(1);
        for(int i=cnt-1; i>=0; i--)
        {
            printf("%d\n",ans[i]);
        }
    }
    return 0;
}
