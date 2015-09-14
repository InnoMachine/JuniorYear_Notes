#include <fstream>
#include <iostream>

#include "txtHandle.h"

using namespace std;

//��ָ���ı��ж�ȡÿһ��token(token�Կո��Ʊ�������з��ȷָ�)
void readFile(char *inputFileName, Student *students, int count){
	ifstream fin;
	fin.open(inputFileName);
	if(!fin)                 //����ļ��Ƿ�򿪳ɹ�
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
	fin.close();            //�����ļ�������Ҫ�ر��ļ�	
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
	fout<<"ƽ���֣�"<<avg<<endl;
	fout.close();
}