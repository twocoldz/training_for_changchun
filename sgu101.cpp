/*
*
*  author : twocoldz
*  date : 11/20/2013  10:26:44
*  欧拉回路
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=105;
struct node
{
    int v,nxt;
}edge[N*2];
int head[10];
bool vis[N],used[N*2];
int deg[10];
int ans[N];
int n,m,e,cnt;

void Init()
{
    e=0;
    memset(head,-1,sizeof(head));
    memset(deg,0,sizeof(deg));
}

void AddEdge(int u,int v)
{
    edge[e].v=v;
    edge[e].nxt=head[u];
    head[u]=e++;
}

void Dfs(int u)
{
    for(int i=head[u];~i;i=edge[i].nxt)
    {
        if(!vis[i>>1])
        {
            vis[i>>1]=1;
            used[i>>1]=i&1;
            int v=edge[i].v;
            Dfs(v);
            ans[cnt++]=(i>>1);
        }
    }
}

int main()
{
    while(scanf("%d",&n)==1&&n)
    {
        int a,b;
        Init();
        for(int i=0;i<n;i++)
        {
            scanf("%d %d",&a,&b);
            deg[a]++;
            deg[b]++;
            AddEdge(a,b);
            AddEdge(b,a);
        }
        int t=0,root=-1;
        for(int i=0;i<=6;i++)
            if(deg[i]&1)
            {
                t++;
                if(t==1)
                    root=i;
            }
        if(t>2)
            printf("No solution\n");
        else
        {
            memset(vis,0,sizeof(vis));
            memset(used,0,sizeof(used));
            cnt=0;
            if(root==-1)
                root=edge[0].v;
            Dfs(root);
            if(cnt<n)
                printf("No solution\n");
            else
            {
                for(int i=cnt-1;i>=0;i--)
                {
                    printf("%d %c\n",ans[i]+1,used[ans[i]]?'-':'+');
                }
            }
        }
    }
    return 0;
}
