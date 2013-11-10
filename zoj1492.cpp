#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=105;
bool g[N][N];
int num[N];
int v[N],path[N];
int best,n;

void Dfs(int *obj,int tot,int cnt)
{
	int x[N];
	//printf("tot=%d cnt=%d\n",tot,cnt);
	if(tot==0)
	{
		if(cnt>best)
			best=cnt;//printf("update best=%d\n",best);
		for(int i=0;i<cnt;i++)
			path[i]=obj[i];
		return ;
	}
	for(int i=0;i<tot;i++)
	{
		if(cnt+(tot-i)<=best)
			return ;
		if(cnt+num[obj[i]]<=best)
			return ;
		int tmp=0;
		for(int j=i+1;j<tot;j++)
			if(g[obj[i]][obj[j]])
				x[tmp++]=obj[j];
		Dfs(x,tmp,cnt+1);		
	}
	return ;
}

void Best()
{
	best=0;
	for(int i=n;i>0;i--)
	{
		int tot=0;
		for(int j=i+1;j<=n;j++)
			if(g[i][j])
				v[tot++]=j;
		//printf("u=%d tot=%d\n",i,tot);
		Dfs(v,tot,1);
		num[i]=best;
		//printf("best=%d num=%d\n",best,num[i]);
	}
}

int main()
{
	while(scanf("%d",&n)==1&&n)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				scanf("%d",g[i]+j);
		Best();
		printf("%d\n",best);
	}
	return 0;
}
