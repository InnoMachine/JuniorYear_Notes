// 足球比赛
// n支队伍，确定输入为偶数
// 轮流比赛，给出对阵情况以及比分
// 胜3平1负0，最后按照得分，出线一半队伍
// 按照字典顺序输出出现队伍
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
	// 队名
	int pnts,sc,mis;
	// 得分，进球数，失球数
};
// 每只队的结构体
int n;
Team t[50]; 
void add(const string &s,int a,int b) // 得分，s的得分，对方得分
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
	// 遍历所有队伍找到和该名字相同的
}
// 将所有得分情况加入对应的队的记录中
bool less1(const Team &a,const Team &b)
{
	if (a.pnts!=b.pnts) return a.pnts>b.pnts;   //首先更具分数比较
	else if (a.sc-a.mis!=b.sc-b.mis) return a.sc-a.mis>b.sc-b.mis;  //比较纯的进球数
	else return a.sc>b.sc;  //比较进球数
}
// 。。。。。。
bool less2(const Team &a,const Team &b)  //比较名字............
{
	return a.nam<b.nam;
}
// 字典排序大小=。=
int main()
{
	string a,b;
	int c,d;
	cin>>n;
	for (int i=0;i<n;i++)    //输入所有队伍的名字
	cin>>t[i].nam; 
	cin.ignore();           //去掉最后一个换行符
	// 读取所有队名
	for (int i=0;i<n*(n-1)/2;i++)
	{
		getline(cin,a,'-');   //记住这个方法 啦啦
		getline(cin,b,' ');    //记住这个方法啦啦
		scanf("%d:%d",&c,&d);  //记住这个方法啦啦 
		cin.ignore();
		
		add(a,c,d);
		add(b,d,c);
	}
	// 读取所有分数，并且用add加入
	sort(t,t+n,less1);
	sort(t,t+n/2,less2);
	// 分别进行两次排序
	// 第一次对所有的排序，取出得分前一半的人
	// 第二次对出线的人排序，按照字典顺序
	for (int i=0;i<n/2;i++)
	cout<<t[i].nam<<endl;
	return 0;
}