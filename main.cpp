#include "polynomial.hpp"
#include "encode.cpp"
#include "decode.cpp"
#include "BerlekampWelch.cpp"
using namespace std;

void testEncoding()
{
	std::vector<FiniteField> msg;

	msg.push_back(FiniteField(0)*FiniteField(0));
	msg.push_back(FiniteField(1)*FiniteField(1));
	msg.push_back(FiniteField(2)*FiniteField(2));

	auto enc=encode(msg, 6);
	for(FiniteField f : enc)
		std::cout<<f<<' ';
	std::cout<<'\n';
}

void testDecoding()
{
	std::vector<FiniteField> blk;

	FiniteField i;

	for(i.polyId=0;i.polyId<14;++i.polyId)
		blk.push_back(i*i);

	std::cout<<"Exp:";
	for(FiniteField f : blk)
		std::cout<<' '<<f;
	std::cout<<'\n';

	// Artificial errors
	blk[0]=5;
	blk[1]=5;
	blk[5]=56;
	blk[10]=71;

	std::vector<FiniteField> msg=decode(blk, 5);

	std::cout<<"Got:";
	for(FiniteField f : msg)
		std::cout<<' '<<f;
	std::cout<<'\n';
}

void testBerlekampWelch()
{
	std::vector<FiniteField> blk;

	FiniteField i;

	for(i.polyId=0;i.polyId<256;++i.polyId)
		blk.push_back(i*i);

	std::cout<<"Exp:";
	for(FiniteField f : blk)
		std::cout<<' '<<f;
	std::cout<<'\n';

	// Artificial errors
	blk[0]=5;
	blk[1]=5;
	blk[5]=56;
	blk[10]=71;

	std::vector<FiniteField> msg=decodeFast(blk, 235);

	std::cout<<"Got:";
	for(FiniteField f : msg)
		std::cout<<' '<<f;
	std::cout<<'\n';
}

void test_polynomial_operations()
{
	Polynomial p_0({9, 7, 3});
    Polynomial q_0({6, 2});
    cout << p_0.GetDegree() << '\n'
         << p_0 << '\n';
    cout << q_0.GetDegree() << '\n'
         << q_0 << '\n';
    cout << p_0 - q_0 << '\n';
    cout << p_0 + q_0 << '\n';
    cout << p_0 * q_0 << '\n';
    cout << '\n';
}

int main()
{
	ff_precalc();
	testDecoding();
	testBerlekampWelch();
	testEncoding();
    test_polynomial_operations();
    return 0;
}
