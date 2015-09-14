// F1��������
// �ܹ���t������
// ÿ��ֻ����n�����õ��ɼ�
// ����������������ʽ
// һ���ǰ��մ�ͳ�ļƷַ�ʽ��1-10��Ϊ25, 18, 15, 12, 10, 8, 6, 4, 2, 1(ÿ�α�����һ��ȡ��10��)������ƽ�������������Ƚϵ�һ��
// �Ĵ����ڶ����Ĵ���һֱ����ͬ
// �ڶ����ǰ��ձ����õ���һ���Ĵ����������ͬ��ȽϷ������ٱȽϵڶ�����ô���
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
	   // �ܷ�����ÿ������������
};
int t, n;
map <string, racer> R;
// ��string������ѡ�ֵ�map

bool Better1(const racer &r1, const racer &r2)
{
     if (r1.points != r2.points) return r1.points > r2.points;   //���������ͬ��ôֱ�Ӹ�������
     for (int i = 0; i < Maxn; i++)  //������ͬʱ�� ���ݾ������Ƚ�
         if (r1.was[i] != r2.was[i]) return r1.was[i] > r2.was[i];  //��������ʱ �ͷ��ؽ��
     return false;
}
// �ȱȽϷ����ڱȽ�����
bool Better2(const racer &r1, const racer &r2)
{
     if (r1.was[0] != r2.was[0]) return r1.was[0] > r2.was[0];//������ݵ�һ���ĸ����Ƚ�ֱ�ӿ�������
     return Better1(r1, r2);
}
// �ȱȽϵ�һ���Ĵ����������ͬ�����1��ͬ�ıȽ�
int main()
{
    cin >> t;
    while (t--) {   //t������
          cin >> n;
          for (int i = 0; i < n; i++) {  //n��������Ա
              string s;
			  cin >> s;        //��������
              short pnt = 0;    
              if (i < Maxb) pnt = bon[i]; // �����ǰ10�� ��������Ӧ�ķ���
              R[s].points += pnt;
			  R[s].was[i]++;
			  // ÿ�����ݶ����뵽ѡ��Struct��
          }
    }
	
    string w1 = R.begin()->first, w2 = R.begin()->first;
	//w1,w2��ָ��R�Ŀ�ʼ����string
	// ����map
    for (map <string, racer>::iterator it = R.begin(); it != R.end(); it++) {
        if (Better1(it->second, R[w1])) w1 = it->first;
		// ��һ������
        if (Better2(it->second, R[w2])) w2 = it->first;
		// �ڶ�������
    }
	
    cout << w1 << endl << w2 << endl;
    return 0;
}
