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
		cout<<"��������������з�ʽ���£�"<<endl;
		cout<<"FILE_IO inputFile.txt outputFile.txt";
		return -1;
	}
	
	readFile(argv[1], students, count);          //��ȡ�ļ�����ѧ����Ϣ�洢��������
	writeFile(argv[2], students, count);         //����ƽ���֣���ѧ����Ϣ������ļ���

	return 0;
}

