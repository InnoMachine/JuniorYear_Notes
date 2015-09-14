#include <iostream>
#include <fstream>
#include "Student.h"
using namespace std;


void initStudentArray(Student* students, int count){
	cout << "**************************************************" << endl;
	cout << "Begin initializing the student data from console" << endl;
	Student  student;
	for (int i = 0; i < count; i++){
		cout << "Please input student id:" << endl;
		cin >> student.id;
		cout << "Please input student name:" << endl;
		cin >> student.name;
		cout << "Please input student score" << endl;
		cin >> student.score;
		students[i] = student;
	}
	cout << "Finish initializing the student data from console" << endl;
	cout << "**************************************************" << endl;
}


void writeBinaryFileWayOne(Student* students, int count, const char* outputFileName){
	cout << "Begin writing the student data to binary file" << endl;
	ofstream fout(outputFileName, ios::out | ios::binary);
	if (!fout){
		cerr << "Failed to open file" << endl;
		exit(1);
	}

	// write the student data one by one
	for (int i = 0; i < count; i++){
		Student tempStudent = students[i];
		fout.write((char*)&tempStudent, sizeof(Student));
	}

	fout.close();
	cout << "Finish writing the student data to binary file" << endl;
	cout << "**************************************************" << endl;
}

void readBinaryFileWayOne(const char* inputFileName){
	cout << "Begin reading the student data from binary file" << endl;
	ifstream fin(inputFileName, ios::in | ios::binary);
	if (!fin){
		cerr << "Failed to open file" << endl;
		exit(1);
	}
	cout << "The message you entered are as follow:" << endl;
	// read student data one by one
	double highestScore = 0;
	while (true){
		Student tempStudent;
		fin.read((char*)&tempStudent, sizeof(Student));
		if (fin.eof()){
			break;
		}
		cout << "ID:" << tempStudent.id <<"\tName:" <<tempStudent.name<<"\tScore:" << tempStudent.score << endl;
		if (tempStudent.score > highestScore){
			highestScore = tempStudent.score;
		}
	}

	fin.close();
	cout << "The highest score is  "<<highestScore << endl;
	cout << "Finish reading the students data from binary file " << endl;
	cout << "**************************************************" << endl;
}


void writeBinaryFileWayTwo(Student* students, int count, const char* outputFileName){
	cout << "Begin writing the student data to binary file" << endl;
	ofstream fout(outputFileName, ios::out | ios::binary);
	if (!fout){
		cerr << "Failed to open file" << endl;
		exit(1);
	}
	// write student count data
	fout.write((char*)&count, sizeof(int));

	// wirte the student array at once
	fout.write((char*)students, sizeof(Student)*count);
	fout.close();
	cout << "Finish writing the student data to binary file" << endl;
	cout << "**************************************************" << endl;
}


void readBinaryFileWayTwo(const char* inputFileName){
	cout << "Begin reading the student data from binary file" << endl;
	ifstream fin(inputFileName, ios::in | ios::binary);
	if (!fin){
		cerr << "Failed to open file" << endl;
		exit(1);
	}

	cout << "The message you entered are as follow:" << endl;
	int count = 0;
	fin.read((char*)&count, sizeof(int));
	// read student data at once
	Student students[MAX_NUM];
	double highestScore = 0;
	fin.read((char*)&students, sizeof(Student)*count);
	for (int i = 0; i < count; i++){
		Student tempStudent = students[i];
		cout << "ID:" << tempStudent.id << "\tName:" << tempStudent.name << "\tScore:" << tempStudent.score << endl;
		if (tempStudent.score > highestScore){
			highestScore = tempStudent.score;
		}
	}
	fin.close();
	cout << "The highest score is  " << highestScore << endl;
	cout << "Finish reading the students data from binary file " << endl;
	cout << "**************************************************" << endl;
}