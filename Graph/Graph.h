#pragma once

#include <iostream>
#include <cstdio>
#include "Queen.h"

#define Maxsize 101

typedef int WeightType;
typedef char DataType;

//Definition of Edge
typedef struct _enode{
	int Ver;
	WeightType Weight;
	struct _enode *next;
}ENode;
typedef ENode *PtrToEdge;

//Definition of Adjoin Vertex List
typedef struct _adjvNode {
	DataType Data;
	PtrToEdge firstedge;//in most case the firstedge keep empty
}AdjVList;
typedef AdjVList *PtrToAdjV;

//Definition of BFSTree
typedef struct _BFSnode{
	QDataType Path;
	struct _BFSnode *next;
}BTNode;

//Definition of DFSTree
typedef struct _DFSnode {
	int Ver;
	int Time;
	int Finish;
	struct _DFSnode *next;
}DTNode;

//Definition of Graph
class Graph
{
private:
	int Nv;//number of vertex
	int Ne;//number of edge
	PtrToAdjV adjv;
	int *Visited;
	BTNode *BRoot;
	int time;
	DTNode *DRoot;
public:
	void InitG();
	int InsertE();
	void ShowG();
	void InitVisited();
	void BFS();
	void ShowBFST();
	void DFS();
	void DFS_Visit(PtrToEdge u);
	void ShowDFST();
	~Graph();
};
typedef Graph* PtrToGraph;