#pragma once

#include <iostream>
#include <cstdio>

#define Maxsize 101
#define Given 1

typedef struct {
	double U;
	int isConst;
	//1 means Given 
	//-1 means it is a vertex of constant current source 
	//0 means unkonwn
	double *Factor;
}Set_U;

//Definition of Edge
typedef struct _enode {
	int num;
	int Ver_From;
	int Ver_To;
	int isConst;//1 means Given 0 unknown
	double I;
	double R;
	struct _enode *next;
}ENode;
typedef ENode *PtrToEdge;


//Definition of Adjoin Vertex List
typedef struct _adjvNode {
	int Ver;
	double U;
	PtrToEdge firstedge;//in most case the firstedge keep empty
}AdjVList;
typedef AdjVList *PtrToAdjV;


//Definition of Graph
class Graph
{
private:
	int Nv;//number of vertex
	int Ne;//number of edge
	int Unkonwn;//number of unknown
	double *B;
	Set_U *SU;//to store the Factor
	PtrToAdjV adjv;
public:
	void InitG(); 
	void InsertV();
	void InsertE();
	void InsertC();
	void ShowG();
	void Arrange();
	void Solve();
};
typedef Graph* PtrToGraph;


class Determinant
{
private:
	double *Det;
	double det;
	int n;
public:
	void InitDet(Set_U *SU, int N);
	int GetN();
	double *GetD();
	double DetCalculate(double *Det, int n);
	double *Division(double *Det, int n, int i);
	double CalculateLinear(double *B, int i);
};


class Circuit
{
private:
	Graph G;
public:
	void ShowCircuit();
	void InitCircuit();
	void SolveCircuit();
};

