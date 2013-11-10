/*
*
*   author : twocoldz
*   date : Sun, 10 Nov 2013 19:24:13 +0800 
*   最大团，水
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=105;
int g[N][N];
int path[N];
int num[N];
int bro[N];
int n,m,e,best;

void Init()
{
	memset(g,0,sizeof(g));
}

bool Dfs(int *v,int tot,int cnt)
{
	if(tot==0)
	{
		if(cnt>best)
		{
			best=cnt;
			for(int i=1;i<=cnt;i++)
				path[i]=bro[i];
			return true;
		}
		return false;
	}
	int x[N];
	for(int i=0;i<tot;i++)
	{
		if(cnt+tot-i<=best)
			return false;
		if(cnt+num[v[i]]<=best)
			return false;
		int tmp=0;
		for(int j=i+1;j<tot;j++)
			if(g[v[i]][v[j]])
				x[tmp++]=v[j];
		bro[cnt+1]=v[i];
		if(Dfs(x,tmp,cnt+1))
			return true;
	}
	return false;
}

int Clique()
{
	int v[N];
	best=0;
	for(int i=n;i>0;i--)
	{
		int tmp=0;
		for(int j=i+1;j<=n;j++)
			if(g[i][j])
				v[tmp++]=j;
		bro[1]=i;
		Dfs(v,tmp,1);
		num[i]=best;
		//printf("%d %d\n",tmp,best);
	}
	return 0;
}

int main()
{
	while(scanf("%d",&n)&&n)
	{
		char str[50];
		Init();
		for(int i=1;i<=n;i++)
		{
			scanf("%s",str);
			int a=str[0]-'A'+1,b;
			for(int j=2;str[j];j++)
			{
				g[a][str[j]-'A'+1]=1;
			}
		}
		Clique();
		if(best==1)
			printf("1 channel needed.\n",best);
		else
			printf("%d channels needed. \n",best);
	}
	return 0;
}
