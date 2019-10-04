#include "Graph.h"
#include "Queen.h"

int main()
{
	Graph G;
	G.InitG();
	while (G.InsertE());
	G.ShowG();
	G.BFS();
	G.ShowBFST();
	G.DFS();
	G.ShowDFST();
	getchar(); getchar();
}