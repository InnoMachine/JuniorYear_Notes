#include<iostream>
#include<string>
#include<map>

using namespace std;
void main(){
	//初始化一个map
    map<string, int> MyMap;
	//插入键值对
	MyMap["first"]=1;
	MyMap["second"]=2;
	MyMap["third"]=3;
	MyMap["fourth"]=4;

	//根据key取得value
	cout<<MyMap["first"];
	cout<<MyMap["second"];
	cout<<MyMap["third"];
	cout<<MyMap["fourth"];




}