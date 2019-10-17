#include "Circuit.h"

using namespace std;

void Determinant::InitDet(Set_U *SU, int N)
{
	int i = 0;
	int cnt = 0;
	while (i < N)
	{
		if (SU[i].isConst == 0 || SU[i].isConst == -1)
			cnt = cnt + 1;
		i++;
	}
	i = 0;
	n = cnt;
	Det = new DataType[n*n];
	for (int j = 0; j < N; j++)
		for (int k = 0; k < n; k++)
		{
			if (1 == SU[j].isConst)
				k++;
			else
				Det[i++] = SU[j].Factor[k];
		}
	det = DetCalculate(Det, n);
}

int Determinant::GetN()
{
	return n;
}

DataType* Determinant::GetD()
{
	return Det;
}


DataType Determinant::DetCalculate(DataType*Det, int n)
{
	DataType ret = 0;
	if (n == 2)
		ret = Det[0] * Det[3] - Det[2] * Det[1];
	else
		for (int i = 0; i < n; i++)
		{
			if (i % 2 == 0)
				ret += Det[i*n] * DetCalculate(Division(Det, n, i), n - 1);
			else
				ret -= Det[i*n] * DetCalculate(Division(Det, n, i), n - 1);
		}

	return ret;
}


DataType*Determinant::Division(DataType*Det, int n, int i)
{
	int j, k;
	DataType* D = new DataType[(n - 1)*(n - 1)];
	k = 0;
	for (j = 0; j < (n - 1)*(n - 1); j++)
	{
		while (k%n == 0 || (k >= i * n&&k <= i * n + n - 1))
			k = k + 1;
		D[j] = Det[k];
		k = k + 1;
	}
	return D;
}

//To solve the linear equation and get the amount of Xi 
DataType Determinant::CalculateLinear(DataType*B,int i)
{
	DataType ret = 0;
	DataType*D = new DataType[n*n];
	for(int j=0;j<n;j++)
		for (int k = 0; k < n; k++)
		{
			if (j == i)
				D[j*n + k] = B[k];
			else
				D[j*n + k] = Det[j*n + k];
		}
	ret = DetCalculate(D, n) / det;
	return ret;
	
}
