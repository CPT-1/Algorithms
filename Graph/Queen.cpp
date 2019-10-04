#pragma once 

#include "Graph.h"
#include "Queen.h"

void Queen::InitQ(int num)
{
	head = 0;
	length = num;
	tail = 0;
	Data = new QDataType[num];
}

int Queen::isFull()
{
	if (tail == length)
		return Full;
	else return 0;
}

int Queen::isEmpty()
{
	if (head >= tail)
		return Empty;
	else return 0;
}

int Queen::EnQueen(QDataType Data)
{
	if (isFull() == Full)
	{
		printf("Full\n");
		return 0;
	}
	Queen::Data[tail] = Data;
	tail = tail + 1;
	return 1;
}

QDataType* Queen::DeQueen()
{
	if (isEmpty() == Empty)
	{
		printf("Empty\n");
		return nullptr;
	}
	head++;
	return &Data[head - 1];
}

