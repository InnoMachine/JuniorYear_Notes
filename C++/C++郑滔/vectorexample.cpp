#include<iostream>
#include<vector>
using namespace std;

//������
class Date
{
	int year,month,day;
public:
	Date(int y, int m, int d){year=y;month=m;day=d;}
	~Date(){}
	void print(){cout<<year<<"��"<<month<<"��"<<day<<"��"<<endl;}
	bool equals(Date &d){if(year==d.year&&month==d.month&&day==d.day){return true;}else{return false;}}
};
//���ڼ�����
class Dates
{
	vector<Date> v;
public:
	Dates(){}
	~Dates(){}
	void append(Date &d){v.push_back(d);}//��vector�����������
	void print(){for(int i=0;i<v.size();i++){v[i].print();}}//���ڼ������������
	void remove(Date &d)   //ɾ��ָ��Ԫ��
	{
		vector<Date>::iterator iter;
		for(iter=v.begin();iter!=v.end();)
		{
			if((*iter).equals(d))
			{
				iter = v.erase(iter);//ɾ��Ԫ�أ�����ֵָ���Ѿ�ɾ��Ԫ�ص���һ��λ��
			}
			else
			{
				++iter;
			}
		}

		/**�������������
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
	dates.remove(d2);//ɾ��Ԫ��d2
	dates.print();//������25��27����������
}