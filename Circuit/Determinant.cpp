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
	Det = new double[n*n];
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

double* Determinant::GetD()
{
	return Det;
}


double Determinant::DetCalculate(double *Det, int n)
{
	double ret = 0;
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


double *Determinant::Division(double *Det, int n, int i)
{
	int j, k;
	double* D = new double[(n - 1)*(n - 1)];
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

//Cramer's Rule
//To solve the linear equation and get the amount of Xi 
double Determinant::CalculateLinear(double *B,int i)
{
	double ret = 0;
	double *D = new double[n*n];
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