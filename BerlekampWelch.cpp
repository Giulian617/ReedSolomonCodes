// Ilie Dumitru

#include "polynomial.hpp"

void debugPrint(const std::vector<std::vector<FiniteField> >& A, const std::vector<FiniteField>& b)
{
	int j, k;
	for(j=0;j<(int)A.size();++j)
	{
		for(k=0;k<(int)A[j].size();++k)
			printf("%d ", A[j][k].polyId);
		printf("-> %d\n", b[j].polyId);
	}
	printf("\n");
}

// Ax = b
std::vector<FiniteField> gaussianElim(std::vector<std::vector<FiniteField> > A, std::vector<FiniteField> b)
{
	int N=A.size(), M=A[0].size();
	int i, j, k;
	FiniteField coef;
	std::vector<int> pivoti(N, -1);
	std::vector<FiniteField> x(M, 0);

	for(i=0;i<N;++i)
	{
		// debugPrint(A, b);

		for(j=0;j<M && !A[i][j].polyId;++j);
		if(j==M)
		{
			// Redundanta prea multa
			return {};
		}

		pivoti[i]=j;
		coef=ff_inv[A[i][pivoti[i]].polyId];
		for(j=0;j<M;++j)
			A[i][j]*=coef;
		b[i]*=coef;

		for(k=i+1;k<N;++k)
		{
			coef=A[k][pivoti[i]];
			for(j=0;j<M;++j)
				A[k][j]-=A[i][j]*coef;
			b[k]-=b[i]*coef;
		}
	}

	// Ok
	for(i=N-1;i>-1;--i)
	{
		x[i]=b[i];
		for(j=i+1;j<N;++j)
			x[pivoti[i]]-=A[i][pivoti[j]]*x[pivoti[j]];
	}

	return x;
}

std::vector<FiniteField> decodeFast(const std::vector<FiniteField>& values, int msgLen)
{
	const int K=msgLen, N=(int)values.size();
	int i, j, e, q;
	std::vector<std::vector<FiniteField> > mat(N, std::vector<FiniteField>(N));
	std::vector<FiniteField> b(N), x;
	Polynomial Q, E, F;
	FiniteField a, aj;

	e=(N-K)/2;
	q=N-e-1;
	for(i=0;i<N;++i)
	{
		mat[i][0]=1;
		mat[i][N-1]=values[i];
		for(j=1;j<=q;++j)
			mat[i][j]=mat[i][j-1]*FiniteField(i);
		for(j=N-2;j>=N-e;--j)
			mat[i][j]=mat[i][j+1]*FiniteField(i);
		b[i]=-mat[i][N-e]*FiniteField(i);
	}

	// debugPrint(mat, b);

	for(;e>0;--e, ++q)
	{
		x=gaussianElim(mat, b);
		if(!x.empty())
		{
			Q.coefficients.resize(q+1);
			E.coefficients.resize(e+1);
			for(i=0;i<=q;++i)
				Q[i]=x[i];
			for(i=0;i<e;++i)
				E[i]=x[N-1-i];
			E[e]=1;

			auto divide=Q/E;
			if(divide.second.coefficients.empty())
			{
				std::swap(F, divide.first);
				x.resize(msgLen);
				for(i=0;i<msgLen;++i)
					x[i]=F(i);
				return x;
			}

			// Eroare necorectabila
			return {};
		}
		if(e>1)
			for(i=0;i<N;++i)
			{
				mat[i][q+1]=mat[i][q]*FiniteField(i);
				b[i]=-mat[i][N-e+1]*FiniteField(i);
			}
	}

	// Fara erori
	return values;
}
