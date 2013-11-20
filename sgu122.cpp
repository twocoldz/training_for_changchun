/*
*
*   author : twocoldz
*   date : 11/21/2013 1:49:00
*   哈密顿回路 模板，上次的模板貌似有错
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
const int N=1005;
bool map[N][N];
int vis[N],ans[N],n,m,index;

void reverse(int a,int b)
{
	while(a<b)
	{
		swap(ans[a],ans[b]);
		a++;
		b--;
	}
}

void Hamilton()
{
    int i,j,mid,flag;
    index=0;
	ans[index++]=1;
	memset(vis,0,sizeof(vis));
	vis[1]=1;
	while(1)
	{
		while(1)
		{
			flag=0;
			for(i=1;i<=n&&!flag;i++)
			    if(!vis[i]&&map[ans[index-1]][i])
				    ans[index++]=i,flag=1,vis[i]=1;
			if(!flag) break;
		}
		reverse(0,index-1);
		while(1)
		{
			flag=0;
			for(i=1;i<=n&&!flag;i++)
			    if(!vis[i]&&map[ans[index-1]][i])
				    ans[index++]=i,flag=1,vis[i]=1;
			if(!flag) break;
		}
		mid=0;
		if(!map[ans[0]][ans[index-1]])
		{
			for(i=1;i<=index-2;i++)
			    if(map[ans[i]][ans[index-1]]&&map[ans[0]][ans[i+1]])
			    {
			        reverse(i+1,index-1);
				    break;
			    }
		}
		if(index==n)
		    break;
		for(i=1;i<=n;i++)
		    if(!vis[i])
		    {
			    for(j=1;j<=index-2;j++)
                    if(map[i][ans[j]])
                    {
                        reverse(0,j-1);
                        reverse(j,index-1);
                        ans[index++]=i;
                        vis[i]=1;
                        break;
                    }
			    if(j<index-1)
			        break;
		    }
    }
}

void print()
{
    int i,j;
    for(i=0;i<index;i++) if(ans[i]==1) break;
    for(j=0;j<index;j++)
    {
        printf("%d ",ans[i++]);
        if(i==n) i=0;
    }
    puts("1");
}

int main()
{
	while(scanf("%d",&n)!=-1)
	{
		memset(map,0,sizeof(map));
		int i,k;
		for(i=1;i<=n;i++)
		{
			while(1)
			{
			    scanf("%d",&k);
			    map[i][k]=1;
			    k=getchar();
			    if(k=='\n'||k=='\r'||k==EOF)
			        break;
			}
		}
		Hamilton();
		print();
	}
	return 0;
}
