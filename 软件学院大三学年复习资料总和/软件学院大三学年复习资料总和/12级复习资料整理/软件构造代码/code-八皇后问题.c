//	N�ʺ�����

#include <iostream>
using namespace std;

#define N 8

bool matrix[N][N] = {0};
// ��¼��ǰ����

bool IsLegal(bool matrix[N][N], const int &i, const int &j)   //�ж��Ƿ���ڳ�ͻ
{
	// �ж�ǰ���i-1��������matrix[i][j]�Ƿ��ͻ
	// ��һ����iΪ1ʱһ���Ϸ�
	for (int m = 1; m <= i - 1; ++m) {
		for (int n = 1; n <= N; ++n) {	//	ʵ��ÿһ��ֻ��һ������
			if (matrix[m][n] == 1) {
				if ( n == j || abs(i - m) == abs(j - n) )	//	key, not bad
					return false;
			}
			// ����i��֮ǰ���еĵ�
			// �����ǰ���лʺ�������ж�
			// �����ǰ��͸ûʺ���������ͬ��������һ��б���ϣ���õ㲻�ܷŻʺ�
		}
	}
	return true;
}

void Print(bool matrix[N][N])   //�����ǰ�ĺϷ�����
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
	// ���뱾����ʱ����N*N������ǰi-1���ѷ����˻���������i-1������
	// �ִӵ�i�������Ϊ��������ѡ�����λ��
	// ���������еݹ飬������������ڳ�ͻ

	if (i > N)	//	�����ǰ�ĺϷ�����
		Print(matrix);
	else
		// ��ǰδ������
		// ������ǰ��һ�е����е�
		for (int j = 1; j <= N; ++j) {
			// ����Ϊ�ʺ�
			matrix[i][j] = 1;
			// ����ж�����Ҫ���������һ��
			if ( IsLegal(matrix, i, j) )
				Trial(i + 1); //���Խ�����һ��
			// ����
			matrix[i][j] = 0;
		}
}

int main(void)
{
	Trial(1);

	return 0;
}