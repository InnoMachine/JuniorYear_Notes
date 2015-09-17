#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<limits>

using namespace std;

const int MAX = 1280;
// 最大数据

/*每个种植点的结构*/
struct point {
	int x,y,value;

	point(int a, int b, int c) {
		x = a;
		y = b;
		value = c;
	}
};

void calculate(int,int);
// 分析平行线确定的区域内满足题意的情况
void analyse(int);
// 分析当前西瓜地要满足覆盖至少aimNum个西瓜需要大棚多少面积
// 通过确定两个平行于x轴的直线，两个平行于y轴的直线来遍历所有情况，从而取得最小值
int aimNum;
// 目标覆盖的西瓜数目
vector<point> melons;
// 存储长有西瓜的坐标和值
int row[MAX],col[MAX];
// row储存种植西瓜区域的纵坐标
// col储存种植西瓜区域的西瓜个数

int minX,maxX;
// 一行上x的最小值和最大值

int result;
// 每一种情况的结果

int main(void) {
	int dataNum;
	// 数据组数

	cin >> dataNum;
	// 读取数据数组
	// 处理数据
	for (int time = 0; time < dataNum; time++) {
		int number;
		cin >> number >> aimNum;

		// 初始化最大最小
		minX = MAX + 1;
		maxX = 0;
		melons.clear();

		for (int j = 0; j < number; j++) {
			int x,y,value;
			cin >> x >> y >> value;
			// 读取西瓜的分布
			row[j] = y;
			minX = min(minX,x);
			maxX = max(maxX,x);
			// 记录最大最小值
			melons.push_back(point(x,y,value));   //将西瓜 加进去
		}
		// 分析
		analyse(number);
	}
	return 0;
}

void analyse(int number) {
		sort(row,row + number);
		int length = unique(row,row + number) - row;
		// 排序后合并y值相同的坐标，并得到当前y值所覆盖的长度
		if (length == 1) {
			// y值只有一种情况，肯定最小为0
			cout << 0 << endl;
			return;
		}
		result = 0x7fffffff;
		// 初始化结果
		for (int i = 0; i < length; i++) {
			for (int j = i + 1; j < length; j++) {
				// 遍历所有的平行边
				for (int num = minX; num < maxX + 1; num++)
					col[num] = 0;
				// 初始化记录value的数组
				for (int k = 0; k < number; k++) {
					if (melons[k].y <= row[j] && melons[k].y >= row[i]) {
						col[melons[k].x] += melons[k].value;
					}
					// 符合当前y定义区域内的点将其值加起来
				}
				calculate(row[i],row[j]);
				// 计算当前的值
			}
		}
		// 输出结果
		cout << result << endl;
}


void calculate(int minY, int maxY) {
	int width = maxY - minY;
	int left,right;
	int carry = col[minX];	// 当前所覆盖的西瓜数
	left = right = minX;

	// right一直增加直到到达最有或者当前value之后已经满足，在增大都比当前小，则right不变，增加左边
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