// �������
// n֧���飬ȷ������Ϊż��
// ����������������������Լ��ȷ�
// ʤ3ƽ1��0������յ÷֣�����һ�����
// �����ֵ�˳��������ֶ���
// http://codeforces.com/problemset/problem/19/A

#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#include <set>
#include <vector>
using namespace std;
struct Team{
	string nam;
	// ����
	int pnts,sc,mis;
	// �÷֣���������ʧ����
};
// ÿֻ�ӵĽṹ��
int n;
Team t[50]; 
void add(const string &s,int a,int b) // �÷֣�s�ĵ÷֣��Է��÷�
{
	for (int i=0;i<n;i++)
	if (t[i].nam==s)
	{
		if (a>b) t[i].pnts+=3;
		else if (a==b) t[i].pnts+=1;
		t[i].sc+=a;
		t[i].mis+=b;
		break;
	}
	// �������ж����ҵ��͸�������ͬ��
}
// �����е÷���������Ӧ�Ķӵļ�¼��
bool less1(const Team &a,const Team &b)
{
	if (a.pnts!=b.pnts) return a.pnts>b.pnts;   //���ȸ��߷����Ƚ�
	else if (a.sc-a.mis!=b.sc-b.mis) return a.sc-a.mis>b.sc-b.mis;  //�Ƚϴ��Ľ�����
	else return a.sc>b.sc;  //�ȽϽ�����
}
// ������������
bool less2(const Team &a,const Team &b)  //�Ƚ�����............
{
	return a.nam<b.nam;
}
// �ֵ������С=��=
int main()
{
	string a,b;
	int c,d;
	cin>>n;
	for (int i=0;i<n;i++)    //�������ж��������
	cin>>t[i].nam; 
	cin.ignore();           //ȥ�����һ�����з�
	// ��ȡ���ж���
	for (int i=0;i<n*(n-1)/2;i++)
	{
		getline(cin,a,'-');   //��ס������� ����
		getline(cin,b,' ');    //��ס�����������
		scanf("%d:%d",&c,&d);  //��ס����������� 
		cin.ignore();
		
		add(a,c,d);
		add(b,d,c);
	}
	// ��ȡ���з�����������add����
	sort(t,t+n,less1);
	sort(t,t+n/2,less2);
	// �ֱ������������
	// ��һ�ζ����е�����ȡ���÷�ǰһ�����
	// �ڶ��ζԳ��ߵ������򣬰����ֵ�˳��
	for (int i=0;i<n/2;i++)
	cout<<t[i].nam<<endl;
	return 0;
}