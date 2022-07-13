#include<iostream>
#include<algorithm>
using namespace std;
const int N = 15;
const int MAXN = 0x3f3f3f3f;
struct POINT {
	int x, y;
};
POINT p[16];
double dp[101][101];
int path[101][101];
double dist(int x, int y, int m, int n)
{
	return sqrt(pow((x - m), 2) + pow((y - n), 2));
}
bool cmp(POINT a, POINT b)
{
	return a.x < b.x;
}
void MIN_PATH()
{
	dp[1][2] = dist(p[1].x, p[1].y, p[2].x, p[2].y);
	path[1][2] = 1;
	for (int j = 3; j <= N; j++)
	{
		for (int i = 1; i <= j - 2; i++)//j-2>i
		{
			dp[i][j] = dp[i][j - 1] + dist(p[j - 1].x, p[j - 1].y, p[j].x, p[j].y);
			path[i][j] = j - 1;
		}
		dp[j - 1][j] = MAXN;
		for (int i = 1; i <= j - 2; i++) //j-1 = i
		{
			double lmin = dp[i][j - 1] + dist(p[i].x, p[i].y, p[j].x, p[j].y);
			if (lmin < dp[j - 1][j])
			{
				dp[j - 1][j] = lmin;
				path[j - 1][j] = i;
			}
		}
	}
	dp[N][N] = dp[N - 1][N] + dist(p[N - 1].x, p[N - 1].y, p[N].x, p[N].y);
	path[N][N] = N - 1;
	cout << dp[N][N] << endl;
}
void PATH_SHOW(int i,int j)
{
	if (i >= j)
	{
		if (i == 2 && j == 1)
		{
			return;
		}
		cout<<path[j][i]<<" ";
		PATH_SHOW(path[j][i], j);
	}
	else
	{
		if (i == 1 && j == 2)
		{
			return;
		}
		PATH_SHOW(i, path[i][j]);
		cout << path[i][j] << " ";
	}
}
int main()
{
	for (int i = 1; i <= 15; i++)
	{
		cin >> p[i].x;
	}
	for (int i = 1; i <= 15; i++)
	{
		cin >> p[i].y;
	}
	sort(p + 1, p + 16, cmp);
	MIN_PATH();
	PATH_SHOW(N,N);
	cout << endl;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			printf(" %d", path[i][j]);
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			printf(" %.1lf", dp[i][j]);
		}
		cout << endl;
	}
}