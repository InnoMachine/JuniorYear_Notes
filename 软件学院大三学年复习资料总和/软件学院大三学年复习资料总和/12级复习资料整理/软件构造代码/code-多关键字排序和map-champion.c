// F1比赛问题
// 总共有t场比赛
// 每场只能有n个人拿到成绩
// 现在有两种排名方式
// 一种是按照传统的计分方式，1-10名为25, 18, 15, 12, 10, 8, 6, 4, 2, 1(每次比赛不一定取到10名)，若有平的情况，则继续比较第一名
// 的次数第二名的次数一直到不同
// 第二钟是按照比赛拿到第一名的次数，如果相同则比较分数，再比较第二名获得次数
// http://codeforces.com/problemset/problem/24/B

#include <iostream>
#include <string>
#include <map>
using namespace std;
const short Maxn = 50;
const short Maxb = 10;
short bon[Maxb] = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};
struct racer {
       short points;
       short was[Maxn];
	   // 总分数和每场比赛的排名
};
int t, n;
map <string, racer> R;
// 由string来索引选手的map

bool Better1(const racer &r1, const racer &r2)
{
     if (r1.points != r2.points) return r1.points > r2.points;   //如果分数不同那么直接给出名次
     for (int i = 0; i < Maxn; i++)  //分数相同时候 根据局数来比较
         if (r1.was[i] != r2.was[i]) return r1.was[i] > r2.was[i];  //如果不相等时 就返回结果
     return false;
}
// 先比较分数在比较排名
bool Better2(const racer &r1, const racer &r2)
{
     if (r1.was[0] != r2.was[0]) return r1.was[0] > r2.was[0];//如果根据第一名的个数比较直接看出来了
     return Better1(r1, r2);
}
// 先比较第一名的次数，如果相同和情况1相同的比较
int main()
{
    cin >> t;
    while (t--) {   //t场比赛
          cin >> n;
          for (int i = 0; i < n; i++) {  //n个比赛人员
              string s;
			  cin >> s;        //输入名字
              short pnt = 0;    
              if (i < Maxb) pnt = bon[i]; // 如果是前10名 计算它对应的分数
              R[s].points += pnt;
			  R[s].was[i]++;
			  // 每组数据都加入到选手Struct中
          }
    }
	
    string w1 = R.begin()->first, w2 = R.begin()->first;
	//w1,w2均指向R的开始索引string
	// 遍历map
    for (map <string, racer>::iterator it = R.begin(); it != R.end(); it++) {
        if (Better1(it->second, R[w1])) w1 = it->first;
		// 第一种排序
        if (Better2(it->second, R[w2])) w2 = it->first;
		// 第二钟排序
    }
	
    cout << w1 << endl << w2 << endl;
    return 0;
}
