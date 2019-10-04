#pragma once 

#include "Graph.h"

#define Full 1
#define Empty 1


typedef struct {
	int Ver;
	int Distance;
}QDataType;

class Queen 
{
private:
	int head;
	int tail;
	int length;
	QDataType *Data;
public:
	void InitQ(int num);
	int isFull();
	int isEmpty();
	int EnQueen(QDataType Data);
	QDataType* DeQueen();
};
typedef Queen* PtrToQueen;