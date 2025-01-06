#include "polynomial.hpp"
using namespace std;

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
    test_polynomial_operations();
    return 0;
}
