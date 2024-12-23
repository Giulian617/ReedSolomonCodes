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

    vector<Polynomial> p = {Polynomial({55, 61, 32, 6}), Polynomial({-1, 1, -2, 3, 2}), Polynomial({0, 2, -3, 1}), Polynomial({-5, 4, -1, 2, 3}), Polynomial({0, -3, 0, 0, 2}), Polynomial({-1.8, 1.5, -2.1, 3.2, 2.5})};
    vector<Polynomial> q = {Polynomial({9, 7, 3}), Polynomial({-1, 1, 1}), Polynomial({-1, 1}), Polynomial({1, 2, 1}), Polynomial({0, 2, 1}), Polynomial({-1.3, 1.1, 1.2})};

    for (int i = 0; i < p.size(); i++)
    {
        pair<Polynomial, Polynomial> ans = p[i] / q[i];
        cout << "numerator: " << p[i] << '\n';
        cout << "denominator: " << q[i] << '\n';
        cout << "quotient: " << ans.first << '\n';
        cout << "remainder: " << ans.second << '\n';
        cout << '\n';
    }
}

int main()
{
    test_polynomial_operations();
    return 0;
}