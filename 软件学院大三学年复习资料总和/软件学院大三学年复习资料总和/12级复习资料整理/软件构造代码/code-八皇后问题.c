//	N皇后问题

#include <iostream>
using namespace std;

#define N 8

bool matrix[N][N] = {0};
// 记录当前棋盘

bool IsLegal(bool matrix[N][N], const int &i, const int &j)   //判断是否存在冲突
{
	// 判断前面的i-1个棋子与matrix[i][j]是否冲突
	// 第一个即i为1时一定合法
	for (int m = 1; m <= i - 1; ++m) {
		for (int n = 1; n <= N; ++n) {	//	实际每一行只有一个棋子
			if (matrix[m][n] == 1) {
				if ( n == j || abs(i - m) == abs(j - n) )	//	key, not bad
					return false;
			}
			// 遍历i行之前所有的点
			// 如果当前点有皇后则进行判断
			// 如果当前点和该皇后纵坐标相同，或者在一条斜线上，则该点不能放皇后
		}
	}
	return true;
}

void Print(bool matrix[N][N])   //输出当前的合法布局
{
	static int count = 1;
	printf("Case %d:\n", count++);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			matrix[i][j] == 1 ? printf("%c ", 2) : printf(". ");
		}
		cout << endl;
	}
	cout << endl;
}

void Trial(const int i)
{
	// 进入本函数时，在N*N的棋盘前i-1行已放置了互不攻击的i-1个棋子
	// 现从第i行起继续为后续棋子选择合适位置
	// 按行数进行递归，则行数不会存在冲突

	if (i > N)	//	输出当前的合法布局
		Print(matrix);
	else
		// 当前未搜索完
		// 遍历当前这一行的所有点
		for (int j = 1; j <= N; ++j) {
			// 假设为皇后
			matrix[i][j] = 1;
			// 如果判断满足要求，则进行下一行
			if ( IsLegal(matrix, i, j) )
				Trial(i + 1); //可以进入下一层
			// 回溯
			matrix[i][j] = 0;
		}
}

int main(void)
{
	Trial(1);

	return 0;
}