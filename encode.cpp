// Ilie Dumitru

#ifndef RS_ENCODE
#define RS_ENCODE

#include "polynomial.hpp"
#include <cassert>

std::vector<FiniteField> encode(const std::vector<FiniteField>& message, int blockLength)
{
	assert((int)message.size() < blockLength);
	assert(blockLength <= SIGMA);

	int N=(int)message.size();
	if(N==blockLength)
		return message;
	int i;
	std::vector<FiniteField> res=message;
	Polynomial bit, total, aux, generator;

	total.coefficients.resize(1);
	total.coefficients[0]=1;

	bit.coefficients.resize(2);
	bit[1]=1;
	for(i=0;i<N;++i)
	{
		bit[0]=-FiniteField(i);
		total=total*bit;
	}

	for(i=0;i<N;++i)
	{
		bit[0]=-FiniteField(i);
		aux=(total/bit).first;
		aux*=message[i]/aux(i);
		generator=generator+aux;
	}

	for(i=N;i<blockLength;++i)
		res.push_back(generator(i));

	return res;
}

#endif // RS_ENCODE
