#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <iostream>
#include <vector>
#include <utility>

class Polynomial
{
private:
    std::vector<double> coefficients;

public:
    Polynomial(const std::vector<double> &_coefficients = {}) : coefficients(_coefficients) {};
    int GetDegree() const;
    Polynomial &operator=(const Polynomial &);
    friend Polynomial operator-(const Polynomial &, const Polynomial &);
    friend Polynomial operator+(const Polynomial &, const Polynomial &);
    friend Polynomial operator*(const Polynomial &, const Polynomial &);
    friend std::pair<Polynomial, Polynomial> operator/(const Polynomial &, const Polynomial &);
    friend std::ostream &operator<<(std::ostream &, const Polynomial &);
};

#endif