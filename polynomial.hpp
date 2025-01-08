// Ilie Dumitru (modificari)

#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <iostream>
#include <vector>
#include <utility>
#include "field.cpp"

class Polynomial
{
public:
    std::vector<FiniteField> coefficients;

public:
    Polynomial(const std::vector<FiniteField> &_coefficients = {}) : coefficients(_coefficients) {};
    int GetDegree() const;
    Polynomial &operator=(const Polynomial &);
    friend Polynomial operator-(const Polynomial &, const Polynomial &);
    friend Polynomial operator+(const Polynomial &, const Polynomial &);
    friend Polynomial operator*(const Polynomial &, const Polynomial &);
    friend std::pair<Polynomial, Polynomial> operator/(const Polynomial &, const Polynomial &);
    friend std::ostream &operator<<(std::ostream &, const Polynomial &);
    FiniteField& operator[](int i);
    const FiniteField& operator[](int i) const;
    friend Polynomial operator*(const Polynomial &, FiniteField);
    Polynomial& operator*=(FiniteField);
    FiniteField operator()(FiniteField);
};

#include "polynomial.cpp"

#endif
