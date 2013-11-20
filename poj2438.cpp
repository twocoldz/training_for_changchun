/*
*
*    author : twocoldz
*    date : 11/21/2013
*    哈密顿回路 模板题
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=505;
int map[N][N],ans[N];
bool vis[N];

int index,n,m,s,t;

void Init()
{
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(i==j)
                map[i][j]=0;
            else
                map[i][j]=1;
    memset(ans,0,sizeof(ans));
    memset(vis,0,sizeof(vis));
    index=0;
}

void reverse(int a,int b)
{
    while(a<b)
    {
        swap(ans[a],ans[b]);
        a++;
        b--;
    }
}

void expand()
{
    while(true)
    {
        int i;
        for(i=1;i<=n;i++)
        {
            if(!vis[i]&&map[i][t])
            {
                ans[index++]=i;
                vis[i]=1;
                t=i;
                break;
            }
        }
        if(i>n)
            break;
    }
}

void Hamilton()
{
    s=1;
    for(int i=1;i<=n;i++)
        if(map[i][s])
        {
            t=i;
            break;
        }

    vis[s]=true;
    vis[t]=true;

    ans[index++]=s;
    ans[index++]=t;

    while(true)
    {
        expand();
        reverse(0,index-1);
        swap(s,t);
        expand();

        if(!map[s][t])
        {
            for(int i=1;i<index-2;i++)
            {
                if(map[ans[i+1]][s]&&map[ans[i]][t])
                {
                    reverse(i+1,index-1);
                    t=ans[index-1];
                    break;
                }
            }
        }

        if(index==n)
            return ;
        for(int j=1;j<=n;j++)
        {
            if(!vis[j])
            {
                int i;
                for(i=1;i<index-1;i++)
                {
                    if(map[ans[i]][j])
                    {
                        s=ans[i-1];
                        t=j;
                        reverse(0,i-1);
                        reverse(i,index-1);
                        ans[index++]=j;
                        vis[j]=true;
                        break;
                    }
                }
                if(map[ans[i]][j])
                    break;
            }
        }
    }
}

int main()
{
    while(scanf("%d %d",&n,&m)&&(n+m))
    {
        n*=2;
        Init();
        int a,b;
        for(int i=0;i<m;i++)
        {
            scanf("%d %d",&a,&b);
            map[a][b]=map[b][a]=0;
        }
        Hamilton();
        for(int i=0;i<index;i++)
            i+1==index?printf("%d\n",ans[i]):printf("%d ",ans[i]);
    }
    return 0;
}
