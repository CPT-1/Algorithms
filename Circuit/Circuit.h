#pragma once

#include <iostream>
#include <cstdio>
#include <ccomplex>

#define Maxsize 101
#define Given 1 

typedef std::complex<double> DataType;
typedef struct {
	DataType U;
	int isConst;
	//1 means Given 
	//-1 means it is a vertex of constant current source 
	//0 means unkonwn
	DataType*Factor;
}Set_U;

//Definition of Edge
typedef struct _enode {
	int num;
	int Ver_From;
	int Ver_To;
	int isConst;	//1 means Given 0 unknown
	DataType I;
	//if R=-Xcj means the load is a capacitor
	//if R=XLj means the load is a coil
	//if R is a real num means the load is a resistor
	DataType R;		 
	struct _enode *next;
}ENode;
typedef ENode *PtrToEdge;


//Definition of Adjoin Vertex List
typedef struct _adjvNode {
	int Ver;
	DataType U;
	PtrToEdge firstedge;	//in most case the firstedge keep empty
}AdjVList;
typedef AdjVList *PtrToAdjV;


//Definition of Graph
class Graph
{
private:
	int Nv;		//number of vertex
	int Ne;		//number of edge
	int Unkonwn;	//number of unknown
	double Frequence;	//the f of I 
	DataType *B;
	Set_U *SU;		//to store the Factor
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
	DataType*Det;
	DataType det;
	int n;
public:
	void InitDet(Set_U *SU, int N);
	int GetN();
	DataType*GetD();
	DataType DetCalculate(DataType*Det, int n);
	DataType*Division(DataType*Det, int n, int i);
	DataType CalculateLinear(DataType*B, int i);
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

