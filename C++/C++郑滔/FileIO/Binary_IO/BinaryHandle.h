#ifndef _BINARY_HANDLE_H
#define _BINARY_HANDLE_H

#include "Student.h";

void initStudentArray(Student* students, int count);
void writeBinaryFileWayOne(Student* students, int count, const char* outputFileName);
void writeBinaryFileWayTwo(Student* students, int count, const char* outputFileName);
void readBinaryFileWayOne(const char* inputFileName);
void readBinaryFileWayTwo(const char* inputFileName);
#endif