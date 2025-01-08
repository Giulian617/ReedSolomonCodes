// Ilie Dumitru

#ifndef RS_DECODE
#define RS_DECODE

#include "polynomial.hpp"
#include <cassert>
#include <map>

std::vector<FiniteField> interpolate(const std::vector<FiniteField>& values, const std::vector<int>& indices, int msgLen)
{
	Polynomial bit, total, generator, aux;

	total.coefficients.resize(1);
	total.coefficients[0]=1;
	bit.coefficients.resize(2);
	bit[1]=1;
	for(int i : indices)
	{
		bit[0]=-FiniteField(i);
		total=total*bit;
	}

	for(int i : indices)
	{
		bit[0]=-FiniteField(i);
		aux=(total/bit).first;
		aux*=values[i]/aux(i);
		generator=generator+aux;
	}

	std::vector<FiniteField> dec(msgLen);
	for(int i=0;i<msgLen;++i)
		dec[i]=generator(i);

	return dec;
}

struct FiniteFieldVectorComparator
{
	bool operator()(const std::vector<FiniteField>& a, const std::vector<FiniteField>& b) const
	{
		for(int i=0;i<(int)a.size();++i)
			if(a[i].polyId!=b[i].polyId)
				return a[i].polyId<b[i].polyId;
		return 0;
	}
};

std::vector<FiniteField> decode(const std::vector<FiniteField>& values, int msgLen)
{
	int blkLen=(int)values.size();
	std::map<std::vector<FiniteField>, int, FiniteFieldVectorComparator> cnt;
	bool ok=1;
	int i;

	assert(blkLen>=msgLen);

	std::vector<int> combi(msgLen);
	for(i=0;i<msgLen;++i)
		combi[i]=i;
	while(ok)
	{
		auto poss=interpolate(values, combi, msgLen);
		++cnt[poss];

		for(i=msgLen-1;i>-1 && combi[i]==blkLen-1-msgLen+i;--i);
		if(i==-1)
			ok=0;
		else
		{
			++combi[i];
			for(++i;i<msgLen;++i)
				combi[i]=combi[i-1]+1;
		}
	}

	const std::vector<FiniteField>* best=0;
	int maxCnt=0, howMany=0;

	for(std::pair<const std::vector<FiniteField>, int>& p : cnt)
	{
		if(p.second>maxCnt)
		{
			maxCnt=p.second;
			best=&p.first;
			howMany=1;
		}
		else if(p.second==maxCnt)
			++howMany;
	}

	if(howMany==1)
		return *best;
	return {}; // Mai mult de o solutie posibila "optima"
}

#endif // RS_DECODE
