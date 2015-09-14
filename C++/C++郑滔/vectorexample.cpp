#include<iostream>
#include<vector>
using namespace std;

//日期类
class Date
{
	int year,month,day;
public:
	Date(int y, int m, int d){year=y;month=m;day=d;}
	~Date(){}
	void print(){cout<<year<<"年"<<month<<"月"<<day<<"日"<<endl;}
	bool equals(Date &d){if(year==d.year&&month==d.month&&day==d.day){return true;}else{return false;}}
};
//日期集合类
class Dates
{
	vector<Date> v;
public:
	Dates(){}
	~Dates(){}
	void append(Date &d){v.push_back(d);}//向vector里面添加日期
	void print(){for(int i=0;i<v.size();i++){v[i].print();}}//日期集合类输出函数
	void remove(Date &d)   //删除指定元素
	{
		vector<Date>::iterator iter;
		for(iter=v.begin();iter!=v.end();)
		{
			if((*iter).equals(d))
			{
				iter = v.erase(iter);//删除元素，返回值指向已经删除元素的下一个位置
			}
			else
			{
				++iter;
			}
		}

		/**错误遍历方法：
		 for(iter=v.begin();iter!=v.end();iter++){
		     if((*iter).equals(d))
			 {
			      v.erase(iter);
			 }
		 }
	     */
	}
};

void main(){
	Date d1(2014, 12, 25);
	Date d2(2014, 12, 26);
	Date d3(2014, 12, 27);
	Dates dates;
	dates.append(d1);
	dates.append(d2);
	dates.append(d3);
	dates.print();
	dates.remove(d2);//删除元素d2
	dates.print();//结果输出25和27号两个日期
}