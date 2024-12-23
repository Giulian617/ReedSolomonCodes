#include "polynomial.hpp"

int Polynomial::GetDegree() const
{
    return this->coefficients.size() - 1;
}

Polynomial &Polynomial::operator=(const Polynomial &other)
{
    if (this == &other)
        return *this;

    int degree_other = other.GetDegree();
    this->coefficients.resize(degree_other + 1);
    for (int i = 0; i <= degree_other; i++)
        this->coefficients[i] = other.coefficients[i];
    return *this;
};

Polynomial operator-(const Polynomial &p, const Polynomial &q)
{
    int degree_p = p.GetDegree(), degree_q = q.GetDegree();
    int smallest_degree = std::min(degree_p, degree_q);
    int largest_degree = std::max(degree_p, degree_q);
    Polynomial r(std::vector<double>(largest_degree + 1));

    for (int i = 0; i <= smallest_degree; i++)
        r.coefficients[i] = p.coefficients[i] - q.coefficients[i];

    if (degree_p > degree_q)
        for (int i = smallest_degree + 1; i <= largest_degree; i++)
            r.coefficients[i] = p.coefficients[i];
    else
        for (int i = smallest_degree + 1; i <= largest_degree; i++)
            r.coefficients[i] = q.coefficients[i];

    int degree_r = r.GetDegree();
    while (degree_r > 0 && r.coefficients[degree_r] == 0)
        degree_r--;
    r.coefficients.resize(degree_r + 1);

    return r;
};

Polynomial operator+(const Polynomial &p, const Polynomial &q)
{
    int degree_p = p.GetDegree(), degree_q = q.GetDegree();
    int smallest_degree = std::min(degree_p, degree_q);
    int largest_degree = std::max(degree_p, degree_q);
    Polynomial r(std::vector<double>(largest_degree + 1));

    for (int i = 0; i <= smallest_degree; i++)
        r.coefficients[i] = p.coefficients[i] + q.coefficients[i];

    if (degree_p > degree_q)
        for (int i = smallest_degree + 1; i <= largest_degree; i++)
            r.coefficients[i] = p.coefficients[i];
    else
        for (int i = smallest_degree + 1; i <= largest_degree; i++)
            r.coefficients[i] = q.coefficients[i];

    return r;
}

Polynomial operator*(const Polynomial &p, const Polynomial &q)
{
    int degree_p = p.GetDegree(), degree_q = q.GetDegree(), degree_r = degree_p + degree_q;
    Polynomial r(std::vector<double>(degree_r + 1));

    for (int i = 0; i <= degree_p; i++)
        for (int j = 0; j <= degree_q; j++)
            r.coefficients[i + j] += p.coefficients[i] * q.coefficients[j];

    return r;
};

std::pair<Polynomial, Polynomial> operator/(const Polynomial &p, const Polynomial &q)
{
    int degree_p = p.GetDegree(), degree_q = q.GetDegree();
    int degree_remainder = degree_p;
    Polynomial quotient(std::vector<double>(degree_p - degree_q + 1));
    Polynomial remainder = p;

    while (degree_remainder >= degree_q)
    {
        std::vector<double> aux(degree_remainder - degree_q + 1);
        aux[degree_remainder - degree_q] = remainder.coefficients[degree_remainder] / q.coefficients[degree_q];

        Polynomial aux_polynomial(aux);
        quotient = quotient + aux_polynomial;
        remainder = remainder - (q * aux_polynomial);

        degree_remainder = remainder.GetDegree();
    }

    return std::make_pair(quotient, remainder);
};

std::ostream &operator<<(std::ostream &out, const Polynomial &p)
{
    int degree_p = p.GetDegree();
    for (int i = degree_p; i >= 0; i--)
    {
        out << p.coefficients[i] << " * x^" << i;
        if (i > 0)
            out << " + ";
    }
    return out;
}
