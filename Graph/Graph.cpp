#include "Graph.h"

using namespace std;

void Graph::InitG()
{
	int i;
	Ne = 0;
	time = 0;
	BRoot = nullptr;
	DRoot = nullptr;
	cout << "please enter the number of vertexes\n";
	scanf_s("%d", &Nv); getchar();
	if (Nv >= Maxsize)
	{
		printf("Error\n");
		return;
	}
	adjv = new AdjVList[Nv];
	Visited = new int[Nv];
	printf("please enter the data\n");
	for (i = 0; i < Nv; i++)
	{
		scanf_s("%c", &adjv[i].Data); getchar();
		adjv[i].firstedge = new ENode;
		adjv[i].firstedge->next = NULL;
		adjv[i].firstedge->Weight = 0;
		adjv[i].firstedge->Ver = -1;
	}
}

int Graph::InsertE()
{
	int v1, v2;
	WeightType Weight;
	printf("please enter the two vertexes to link\n");
	scanf_s("%d %d", &v1, &v2); getchar();
	if ((v1 < 0 || v2 < 0) || (v1 >= Nv || v2 >= Nv))
	{
		printf("End\n");
		return 0;
	}
	printf("please enter the weight of edge\n");
	scanf_s("%d", &Weight);
	PtrToEdge E;
	PtrToEdge pE1 = adjv[v1].firstedge;
	PtrToEdge pE2 = adjv[v2].firstedge;

	E = new ENode;
	E->Weight = Weight;
	E->Ver = v2;
	E->next = NULL;
	for (pE1; pE1->next; pE1 = pE1->next);
	pE1->next = E;

	E = new ENode;
	E->Weight = Weight;
	E->Ver = v1;
	E->next = NULL;
	for (pE2; pE2->next; pE2 = pE2->next);
	pE2->next = E;

	Ne = Ne + 1;
	return 1;
}

void Graph::InitVisited()
{
	int i;
	for (i = 0; i < Nv; i++)
		Visited[i] = 0;
}

void Graph::BFS()
{
	int i;
	Queen Q;
	PtrToEdge E;
	QDataType source;
	BTNode *pB = BRoot;
	InitVisited();
	cout << "\nIn the BFSTree\n";
	printf("please enter the source of graph\n");
	scanf_s("%d", &source.Ver);
	source.Distance = 0;
	Q.InitQ(Nv);
	Q.EnQueen(source);
	Visited[source.Ver] = 1;
	while (Q.isEmpty()!=Empty)
	{
		QDataType temp = *Q.DeQueen();
		if (!BRoot)
		{
			BRoot = new BTNode;
			BRoot->Path = temp;
			BRoot->next = nullptr;
		}
		else
		{
			for (pB = BRoot; pB->next; pB = pB->next);
			BTNode* New = new BTNode;
			New->next = NULL;
			New->Path= temp;
			pB->next = New;
		}
		for (E=adjv[temp.Ver].firstedge->next;E;E=E->next)
		{
			if (!Visited[E->Ver])
			{
				QDataType t;
				t.Ver = E->Ver;
				t.Distance = temp.Distance + 1;
				Q.EnQueen(t);
				Visited[E->Ver] = 1;
			}
		}
	}
}

void Graph::ShowG()
{
	int i;
	PtrToEdge pE;
	for (i = 0; i < Nv; i++)
	{
		printf("The data of vertex%d is %c\n", i, adjv[i].Data);
		printf("It is linked with\tand the weight of edge is:\n");
		for (pE = adjv[i].firstedge->next; pE; pE = pE->next)
			printf("%d\t%d\n", pE->Ver, pE->Weight);
	}
}

void Graph::ShowBFST()
{
	BTNode *pB = BRoot;
	printf("The source is %d\n", BRoot->Path.Ver);
	printf("The path is\n");
	for (pB; pB; pB = pB->next)
		printf("The vertex is %d\t The distance is%d\n",
			pB->Path.Ver, pB->Path.Distance);
}

void Graph::DFS_Visit(PtrToEdge u)
{
	time++;
	Visited[u->Ver] = 1;
	DTNode *New = new DTNode;
	DTNode *p = DRoot;
	PtrToEdge E = adjv[u->Ver].firstedge->next;
	New->Time = time;
	New->Ver = u->Ver;
	New->next = nullptr;
	for (p; p->next; p = p->next);
		p->next = New;
	for (E; E; E = E->next)
		if (!Visited[E->Ver])
			DFS_Visit(E);
	New->Finish = time;
	time++;
}

void Graph::DFS()
{
	PtrToEdge E;
	DRoot = new DTNode;
	DRoot->next = nullptr;
	cout << "\nIn DFS \n";
	cout << "please enter the root\n";
	cin >> DRoot->Ver; getchar();
	DRoot->Time = time;
	InitVisited();
	Visited[DRoot->Ver] = 1;
	for (E = adjv[DRoot->Ver].firstedge->next; E; E = E->next)
		if (!Visited[E->Ver])
			DFS_Visit(E);
	DRoot->Finish = time;
}

void Graph::ShowDFST()
{
	DTNode *pD = DRoot;
	printf("The root is %d\n", DRoot->Ver);
	printf("The path is\n");
	for (pD; pD; pD = pD->next)
		printf("The vertex is %d\t The find time is%d\t The finish time is%d\n",
			pD->Ver, pD->Time,pD->Finish);
}

Graph::~Graph()
{
	delete[]adjv;
	delete BRoot;
	delete DRoot;
	delete Visited;
}