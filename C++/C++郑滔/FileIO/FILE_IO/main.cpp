#include <fstream>
#include <iostream>

#include "txtHandle.h"

using namespace std;

int main(int argc, char* argv[]){
	int count;
	cout<<"Student count:"<<endl;
	cin>>count;
	Student students[MAX_NUM];
	if(argc !=3)
	{
		cout<<"输入参数错误，运行方式如下："<<endl;
		cout<<"FILE_IO inputFile.txt outputFile.txt";
		return -1;
	}
	
	readFile(argv[1], students, count);          //读取文件，把学生信息存储在数组中
	writeFile(argv[2], students, count);         //计算平均分，将学生信息输出到文件中

	return 0;
}

