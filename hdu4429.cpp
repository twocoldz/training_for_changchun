/*
*
*   author : twocoldz
*   date : Sun, 24 Nov 2013 01:38:52 +0800 
*   LCA
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
struct Node
{
    int lson,rson,f;
    int dep;
    int lx,ly,rx,ry;
    void Init(int d,int fa)
    {
        lson=rson=0;
        f=fa;
        dep=d;
    }
    void Update(int a,int b,int c,int d)
    {
        lx=a,ly=b,rx=c,ry=d;
    }
}node[2005];
int num[2005];
int tot;

int Find(int root,int x,int y)
{
    int t=root,tt;
    while(true)
    {
        if(node[t].lson==0)
            return t;
        tt=node[t].lson;
        if(x>=node[tt].lx&&x<=node[tt].rx&&y>=node[tt].ly&&y<=node[tt].ry)
            t=tt;
        else
            t=node[t].rson;
    }
}

int GetNum(int root)
{
    num[root]=0;
    if(node[root].lson==0)
        return num[root]=1;
    else
    {
        num[root]+=GetNum(node[root].lson);
        num[root]+=GetNum(node[root].rson);
    }
    return num[root];
}

int main()
{
    int lx,rx,ly,ry;
    int n,Q,root;
    while(scanf("%d%d%d%d",&lx,&ly,&rx,&ry)!=EOF)
    {
        root=0;
        node[root].Init(0,-1);
        node[root].Update(lx,ly,rx,ry);
        tot=1;
        scanf("%d%d",&n,&Q);
        for(int i=0;i<n;i++)
        {
            scanf("%d%d%d%d",&lx,&ly,&rx,&ry);
            if(lx>rx)
                swap(lx,rx);
            if(ly>ry)
                swap(ly,ry);
            int t=Find(root,(lx+rx)/2,(ly+ry)/2);
            int d=node[t].dep;

            node[t].lson=tot;
            node[tot].Init(d+1,t);
            node[tot].Update(node[t].lx,node[t].ly,rx,ry);
            tot++;

            node[t].rson=tot;
            node[tot].Init(d+1,t);
            node[tot].Update(lx,ly,node[t].rx,node[t].ry);
            tot++;
        }
        GetNum(root);
        while(Q--)
        {
            scanf("%d%d%d%d",&lx,&ly,&rx,&ry);
            int t1=Find(root,lx,ly);
            int t2=Find(root,rx,ry);

            while(t1!=t2)
            {
                if(node[t1].dep>node[t2].dep)
                    t1=node[t1].f;
                else if(node[t1].dep<node[t2].dep)
                    t2=node[t2].f;
                else
                {
                    t1=node[t1].f;
                    t2=node[t2].f;
                }
            }
            printf("%d\n",n+1-num[t1]+1);
        }
    }
    return 0;
}
