#include<iostream>
#include<string>
#include<map>

using namespace std;
void main(){
	//��ʼ��һ��map
    map<string, int> MyMap;
	//�����ֵ��
	MyMap["first"]=1;
	MyMap["second"]=2;
	MyMap["third"]=3;
	MyMap["fourth"]=4;

	//����keyȡ��value
	cout<<MyMap["first"];
	cout<<MyMap["second"];
	cout<<MyMap["third"];
	cout<<MyMap["fourth"];




}