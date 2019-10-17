#include "Circuit.h"

using namespace std;

void Graph::InitG()
{
	int i;
	Ne = 0;
	cout << "please enter the number of vertexes\n";
	cin >> Nv;
	if (Nv >= Maxsize)
	{
		cout << "Error\n";
		return;
	}
	adjv = new AdjVList[Nv];
	for (i = 0; i < Nv; i++)
		adjv[i].Ver = i;
	for (i = 0; i < Nv; i++)
	{
		adjv[i].firstedge = new ENode;
		adjv[i].firstedge->next = nullptr;
		adjv[i].firstedge->I = 0;
		adjv[i].firstedge->R = -1;
		adjv[i].firstedge->Ver_From = -1;
		adjv[i].firstedge->Ver_To = -1;
	}
}

void Graph::InsertV()
{

	int cnt = 0;
	DataType U;
	int Ver;
	//initial Set_U
	SU = new Set_U[Nv];
	for (int i = 0; i < Nv; i++)
		SU[i].isConst = 0;
	cout << "please enter the amount of Frequence /HZ " << endl;
	cin >> Frequence;
	do {
		cout << "please enter the vertex to add volt\n";
		cin >> Ver;
		if (Ver >= 0 && Ver<Nv)
		{
			cout << "please enter the Volt\n";
			cin >> U;
			cnt = cnt + 1;
			adjv[Ver].U = U;
			adjv[Ver].Ver = Ver;
			SU[Ver].isConst = 1;
			SU[Ver].U = U;
		}
	} while (Ver >= 0 && Ver < Nv);
	//
	Unkonwn = Nv - cnt;
	B = new DataType[Unkonwn];
	for (int i = 0; i < Nv; i++)
	{
		SU[i].Factor = new DataType[Unkonwn];
		for (int j = 0; j < Unkonwn; j++)
			SU[i].Factor[j] = 0;
	}
	for (int j = 0; j < Unkonwn; j++)
		B[j] = 0;
}

void Graph::InsertE()
{
	//
	int i = 0;
	int cnt = 0;
	DataType R;
	int Ver_From, Ver_To;
	do {
		cout << "please enter the two vertexes to link\n";
		cin >> Ver_From >> Ver_To;
		if (Ver_From >= 0 && Ver_To >= 0 && Ver_From != Ver_To)
		{
			PtrToEdge E;
			PtrToEdge pE1 = adjv[Ver_From].firstedge;
			PtrToEdge pE2 = adjv[Ver_To].firstedge;
			cout << "Please enter the R\n";
			cin >> R;

			E = new ENode;
			E->num = cnt;
			E->next = nullptr;
			E->R = R;
			E->isConst = 0;
			E->Ver_From = Ver_From;
			E->Ver_To = Ver_To;
			for (pE1; pE1->next; pE1 = pE1->next);
			pE1->next = E;

			E = new ENode;
			E->num = cnt;
			E->next = nullptr;
			E->R = R;
			E->isConst = 0;
			E->Ver_From = Ver_From;
			E->Ver_To = Ver_To;
			for (pE2; pE2->next; pE2 = pE2->next);
			pE2->next = E;

			Ne = Ne + 1;
			cnt = cnt + 1;
		}

	} while ((Ver_From >= 0 && Ver_To >= 0) &&
		(Ver_From <= Nv && Ver_To <= Nv)
		&& (Ver_From != Ver_To));
}

void Graph::InsertC()
{
	int num;
	double I;
	int Ver_From, Ver_To;
	//
	do {
		cout << "please enter the Ver_From and Ver_To\n";
		cin >> Ver_From >> Ver_To;
		
		PtrToEdge pE1 = adjv[Ver_From].firstedge;
		PtrToEdge pE2 = adjv[Ver_To].firstedge;

		if (Ver_From >= 0 && Ver_To >= 0 && Ver_From != Ver_To)
		{	
			cout << "please enter the number of I\n";
			cin >> num;
			cout << "please enter the I\n";
			cin >> I;

			SU[Ver_From].isConst = -1;
			SU[Ver_To].isConst = -1;

			for (pE1; pE1->next; pE1 = pE1->next)
				if (pE1->Ver_To == Ver_To && num == pE1->num)
					break;
			for (pE2; pE2->next; pE2 = pE2->next)
				if (pE2->Ver_From == Ver_From && num == pE1->num)
					break;

			pE1->Ver_From = Ver_From;
			pE1->Ver_To = Ver_To;
			pE1->I = I;
			pE1->isConst = 1;

			pE2->Ver_From = Ver_From;
			pE2->Ver_To = Ver_To;
			pE2->I = I;
			pE2->isConst = 1;
		}
	} while (Ver_From >= 0 && Ver_To >= 0 && Ver_From != Ver_To);
}

void Graph::ShowG()
{
	int i;
	PtrToEdge pE;
	for (i = 0; i < Nv; i++)
	{
		cout << "The frequence of the U and I=" << Frequence << endl;
		cout << "*******************************\n";
		cout << "The volt of vertex" << i << " is " << adjv[i].U << endl;
		cout << "The current is from  to" << endl;
		for (pE = adjv[i].firstedge->next; pE; pE = pE->next)
		{
			cout << pE->Ver_From << "->" << pE->Ver_To << endl;
			cout << "R=" << pE->R << endl;
			cout << "I=" << pE->I << endl;
		}
	}
	cout << "*******************************\n";
}

//To figure out the Factor of U
//To get the linear equation
//U0[,……,]=[B0]    
//U1[,……,]=[B1]
//……	   ……	
void Graph::Arrange()
{
	int i;
	int cnt = 0;
	PtrToEdge E;
	for (i = 0; i < Nv; i++)
	{
		if (Given == SU[i].isConst)
			continue;
		//use Kirchhoff for each vertex the amount of I_in == I_out
		//I == (U_From-U_To)/R
		E = adjv[i].firstedge->next;
		for (E; E; E = E->next)
		{
			if (Given == E->isConst)
			{
				if (i == E->Ver_From)
					B[cnt] += E->I;
				else if (i == E->Ver_To)
					B[cnt] -= E->I;
			}
			else if(!E->isConst)
			{
				if (i == E->Ver_From)
				{
					SU[E->Ver_From].Factor[cnt] -= 1.0 / E->R;
					if (Given != SU[E->Ver_To].isConst)
						SU[E->Ver_To].Factor[cnt] += 1.0 / E->R;
					else
						B[cnt] -= SU[E->Ver_To].U / E->R;
				}
				else if (i == E->Ver_To)
				{
					SU[E->Ver_To].Factor[cnt] -= 1.0 / E->R;
					if (Given != SU[E->Ver_From].isConst)
						SU[E->Ver_From].Factor[cnt] += 1.0 / E->R;
					else
						B[cnt] -= SU[E->Ver_From].U / E->R;
				}
			}
		}
		cnt = cnt + 1;
	}

}

void Graph::Solve()
{
	int cnt = 0;
	Determinant _Det;
	PtrToEdge E;
	_Det.InitDet(SU,Nv);
	for (int i = 0; i < Nv; i++)
		if (Given != SU[i].isConst)
		{
			SU[i].U = _Det.CalculateLinear(B, cnt++);
			adjv[i].U = SU[i].U;
		}
			
	for (int i = 0; i < Nv; i++)
	{
		E = adjv[i].firstedge->next;
		for(E;E;E=E->next)
			if (!E->isConst)
				E->I = (adjv[E->Ver_From].U - adjv[E->Ver_To].U) / E->R;
	}
}


void Circuit::InitCircuit()
{
	G.InitG();
	cout << endl;
	G.InsertV();
	cout << endl;
	G.InsertE();
	cout << endl;
	G.InsertC();
	cout << endl;
}

void Circuit::ShowCircuit()
{
	G.ShowG();
}

void Circuit::SolveCircuit()
{
	G.Arrange();
	G.Solve();
}
