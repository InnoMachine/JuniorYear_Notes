#include <fstream>
#include <iostream>

#include "txtHandle.h"

using namespace std;

//从指定文本中读取每一个token(token以空格、制表符、换行符等分割)
void readFile(char *inputFileName, Student *students, int count){
	ifstream fin;
	fin.open(inputFileName);
	if(!fin)                 //检查文件是否打开成功
	{
		cerr<<"Can not open the file."<<endl;
		exit(1);
	}

	Student student;
	//char token[100]
	for(int i=0; i!=count; i++){
		fin>>student.id>>student.name>>student.score;
		//fin>>token;
		students[i]=student;
	}
	fin.close();            //操作文件结束后要关闭文件	
}

void writeFile(char *outputFileName, Student *students, int count){
	ofstream fout;
	fout.open(outputFileName);
	double avg=0.0;
	for(int i=0; i!=count; i++){
		avg+=students[i].score;
		fout<<students[i].id<<"\t"<<students[i].name<<"\t"<<students[i].score<<endl;
	}
	avg/=count;
	fout<<"平均分："<<avg<<endl;
	fout.close();
}