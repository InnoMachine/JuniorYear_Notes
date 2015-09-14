#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<limits>

using namespace std;

const int MAX = 1280;
// �������

/*ÿ����ֲ��Ľṹ*/
struct point {
	int x,y,value;

	point(int a, int b, int c) {
		x = a;
		y = b;
		value = c;
	}
};

void calculate(int,int);
// ����ƽ����ȷ����������������������
void analyse(int);
// ������ǰ���ϵ�Ҫ���㸲������aimNum��������Ҫ����������
// ͨ��ȷ������ƽ����x���ֱ�ߣ�����ƽ����y���ֱ������������������Ӷ�ȡ����Сֵ
int aimNum;
// Ŀ�긲�ǵ�������Ŀ
vector<point> melons;
// �洢�������ϵ������ֵ
int row[MAX],col[MAX];
// row������ֲ���������������
// col������ֲ������������ϸ���

int minX,maxX;
// һ����x����Сֵ�����ֵ

int result;
// ÿһ������Ľ��

int main(void) {
	int dataNum;
	// ��������

	cin >> dataNum;
	// ��ȡ��������
	// ��������
	for (int time = 0; time < dataNum; time++) {
		int number;
		cin >> number >> aimNum;

		// ��ʼ�������С
		minX = MAX + 1;
		maxX = 0;
		melons.clear();

		for (int j = 0; j < number; j++) {
			int x,y,value;
			cin >> x >> y >> value;
			// ��ȡ���ϵķֲ�
			row[j] = y;
			minX = min(minX,x);
			maxX = max(maxX,x);
			// ��¼�����Сֵ
			melons.push_back(point(x,y,value));   //������ �ӽ�ȥ
		}
		// ����
		analyse(number);
	}
	return 0;
}

void analyse(int number) {
		sort(row,row + number);
		int length = unique(row,row + number) - row;
		// �����ϲ�yֵ��ͬ�����꣬���õ���ǰyֵ�����ǵĳ���
		if (length == 1) {
			// yֵֻ��һ��������϶���СΪ0
			cout << 0 << endl;
			return;
		}
		result = 0x7fffffff;
		// ��ʼ�����
		for (int i = 0; i < length; i++) {
			for (int j = i + 1; j < length; j++) {
				// �������е�ƽ�б�
				for (int num = minX; num < maxX + 1; num++)
					col[num] = 0;
				// ��ʼ����¼value������
				for (int k = 0; k < number; k++) {
					if (melons[k].y <= row[j] && melons[k].y >= row[i]) {
						col[melons[k].x] += melons[k].value;
					}
					// ���ϵ�ǰy���������ڵĵ㽫��ֵ������
				}
				calculate(row[i],row[j]);
				// ���㵱ǰ��ֵ
			}
		}
		// ������
		cout << result << endl;
}


void calculate(int minY, int maxY) {
	int width = maxY - minY;
	int left,right;
	int carry = col[minX];	// ��ǰ�����ǵ�������
	left = right = minX;

	// rightһֱ����ֱ���������л��ߵ�ǰvalue֮���Ѿ����㣬�����󶼱ȵ�ǰС����right���䣬�������
	while (right <= maxX) {
		if (carry >= aimNum) {
			result = min(result, width * (right - left));
			carry -= col[left];
			left++;
		} else {
			right++;
			carry += col[right];
		}
	}
}