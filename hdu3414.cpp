/*
*   auther ： twocoldz
*   date  ：Mon, 04 Nov 2013 13:19:22 +0800 
*   锦赛图必有哈密顿路径
*   枚举起始点
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=1005;
struct node
{
	int v,nxt;
}edge[N*N];
int map[N][N];
int ans[N];
int n,m,e;

void Init()
{
	e=0;
	//memset(map,0,sizeof(map));
}


int main()
{
	int cases;
	//scanf("%d",&cases);
	while(scanf("%d",&n)!=EOF&&n)
	{
		Init();
		int a,b;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				scanf("%d",map[i]+j);
			}
		}
		for(int i=1;i<=n;i++)
			map[0][i]=1;
		int head,flag=0,k;
		for(k=1;k<=n;k++)  //枚举某点先不加入链中，最后判断是否能通过该点连接首尾
		{
			e=0;
			edge[e].v=0;
			edge[e].nxt=-1;
			head=e++;
			for(int i=1;i<=n;i++)
			{
				if(i==k)
					continue;
				int p=head;
				//printf("%d\n",edge[p].nxt);
				while(edge[p].nxt!=-1&&!(map[edge[p].v][i]&&map[i][edge[edge[p].nxt].v]))
				{
					//printf("p=%d edge[p].nxt=%d edge[p].v=%d\n",p,edge[p].nxt,edge[p].v);
					p=edge[p].nxt;
				}
				edge[e].v=i;
				edge[e].nxt=edge[p].nxt;
				edge[p].nxt=e++;
			}
			int p=head;
			p=edge[p].nxt;
			for(int i=1;i<n;i++)
			{
				ans[i]=edge[p].v;
				p=edge[p].nxt;
			}
			if(map[ans[n-1]][k]&&map[k][ans[1]])
			{
				flag=1;
				break;
			}
		}
		
		if(flag==0)
		{
			printf("-1\n");
			continue;
		}
		int p=head;
		p=edge[p].nxt;
		for(int i=1;i<n;i++)
		{
			printf("%d ",edge[p].v);
			p=edge[p].nxt;
		}
		printf("%d\n",k);
	}
	return 0;
}
