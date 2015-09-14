#include <iostream>
#include <fstream>
#include "BinaryHandle.h"
using namespace std;


int main(int argc, char* argv[]){
	if (argc != 2){
		cout << "Parameter error,please input as follow:" << endl;
		cout << "BinaryIO output.dat" << endl;
		exit(1);
	}
	Student students[MAX_NUM];
	int count = 0;
	cout << "Please input students amount :" << endl;
	cin >> count;

	initStudentArray(students, count);
	writeBinaryFileWayOne(students, count, argv[1]);
	readBinaryFileWayOne(argv[1]);
	//writeBinaryFileWayTwo(students, count, argv[1]);
	//readBinaryFileWayTwo(argv[1]);
}