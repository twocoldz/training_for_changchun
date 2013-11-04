/*
*
*   auther : twocoldz
*   date :  Mon, 04 Nov 2013 20:03:52 +0800 
*   状态dp
*
*/


#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=15;
int dp[1<<N][3][8];
int c[1<<N];
int a[N][N];

void Init()
{
	for(int i=0;i<(1<<N);i++)
	{
		c[i]=0;
		int k=1;
		for(int j=0;j<N;j++)
		{
			if(i&k)
				c[i]++;
			k<<=1;
		}
	}
}

int main()
{
	int n;
	Init();
	//printf("%d %d\n",c[5],c[7]);
	while(scanf("%d",&n)==1&&n)
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				scanf("%d",a[i]+j);
			}	
		}
		
		memset(dp,-1,sizeof(dp));
		dp[0][0][0]=0;
		for(int i=0;i<(1<<n);i++)
		{
			for(int j=0;j<n;j++)
			{
				if(!(i&(1<<j)))
				{
					int t=i|(1<<j);
					int cnt=c[i];
					for(int k=0;k<3;k++)
					{
						for(int m=0;m<8;m++)
						{
						
							if(dp[i][k][m]==-1)
								continue;
							//printf("i=%d j=%d k=%d m=%d dp[i][k][m]=%d\n",i,j,k,m,dp[i][k][m]);
							if(a[j][cnt]==0)
							{
								if(k==2)
									break;
								dp[t][k+1][m]=max(dp[t][k+1][m],dp[i][k][m]);
							}
							else if(a[j][cnt]==1)
							{
								if(k==2)
									break;
								dp[t][k+1][(m<<1)%8]=max(dp[t][k+1][(m<<1)%8],dp[i][k][m]+(m<<1)/8);
							}
							else if(a[j][cnt]==2)
							{
								dp[t][k][(m<<1)%8+1]=max(dp[t][k][(m<<1)%8+1],dp[i][k][m]+(m<<1)/8);
							}
							else
							{
								dp[t][k][0]=max(dp[t][k][0],dp[i][k][m]+c[m]+1);
			//					printf("%d %d %d %d %d\n",i,k,m,c[m],dp[i][k][m]);
							}
						}
					}
				}
			}
		}
		int ans=0;
		for(int i=0;i<(1<<n);i++)
		{
			for(int j=0;j<3;j++)
			{
				for(int k=0;k<8;k++)
				{
					ans=max(dp[i][j][k],ans);
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

/*
5
0 2 0 2 2
1 0 2 0 3
0 2 1 2 0
0 2 2 1 2
2 1 0 2 0
*/
