// Ilie Dumitru (modificari partial)

#include "polynomial.hpp"

int Polynomial::GetDegree() const
{
    return this->coefficients.size() - 1;
}

Polynomial &Polynomial::operator=(const Polynomial &other)
{
    if (this == &other)
        return *this;

    this->coefficients = other.coefficients;
    return *this;
};

Polynomial operator-(const Polynomial &p, const Polynomial &q)
{
    int degree_p = p.GetDegree(), degree_q = q.GetDegree();
    int smallest_degree = std::min(degree_p, degree_q);
    int largest_degree = std::max(degree_p, degree_q);
    Polynomial r(std::vector<FiniteField>(largest_degree + 1));

    for (int i = 0; i <= smallest_degree; i++)
        r[i] = p[i] - q[i];

    if (degree_p > degree_q)
        for (int i = smallest_degree + 1; i <= largest_degree; i++)
            r[i] = p[i];
    else
        for (int i = smallest_degree + 1; i <= largest_degree; i++)
            r[i] = -q[i];

    while (!r.coefficients.empty() && r.coefficients.back() == 0)
        r.coefficients.pop_back();

    return r;
};

Polynomial operator+(const Polynomial &p, const Polynomial &q)
{
    int degree_p = p.GetDegree(), degree_q = q.GetDegree();
    int smallest_degree = std::min(degree_p, degree_q);
    int largest_degree = std::max(degree_p, degree_q);
    Polynomial r(std::vector<FiniteField>(largest_degree + 1));

    for (int i = 0; i <= smallest_degree; i++)
        r[i] = p[i] + q[i];

    if (degree_p > degree_q)
    {
		for (int i = smallest_degree + 1; i <= largest_degree; i++)
            r[i] = p[i];
	}
    else
    {
		for (int i = smallest_degree + 1; i <= largest_degree; i++)
            r[i] = q[i];
	}

	while (!r.coefficients.empty() && r.coefficients.back() == 0)
		r.coefficients.pop_back();

    return r;
}

Polynomial operator*(const Polynomial &p, const Polynomial &q)
{
    int degree_p = p.GetDegree(), degree_q = q.GetDegree(), degree_r = degree_p + degree_q;
    Polynomial r(std::vector<FiniteField>(degree_r + 1));

    for (int i = 0; i <= degree_p; i++)
        for (int j = 0; j <= degree_q; j++)
			r[i + j] += p[i] * q[j];

    return r;
};

std::pair<Polynomial, Polynomial> operator/(const Polynomial &p, const Polynomial &q)
{
    int degree_p = p.GetDegree(), degree_q = q.GetDegree();
    int degree_remainder = degree_p;
    int i;
    Polynomial quotient(std::vector<FiniteField>(degree_p - degree_q + 1));
    Polynomial remainder = p;

    while (degree_remainder >= degree_q)
    {
        FiniteField coef = remainder.coefficients[degree_remainder] / q.coefficients[degree_q];

        quotient[degree_remainder - degree_q] = coef;

        for (i = 0; i <= degree_q; ++i)
			remainder[degree_remainder - degree_q + i] -= coef * q[i];
		while (!remainder.coefficients.empty() && remainder.coefficients.back() == 0)
			remainder.coefficients.pop_back();
        degree_remainder = remainder.GetDegree();
    }

    return std::make_pair(quotient, remainder);
};

std::ostream &operator<<(std::ostream &out, const Polynomial &p)
{
    int degree_p = p.GetDegree();
    for (int i = degree_p; i >= 0; i--)
    {
        out << p[i] << " * x^" << i;
        if (i > 0)
            out << " + ";
    }
    return out;
}

FiniteField& Polynomial::operator[](int i)
{
	return coefficients[i];
}

const FiniteField& Polynomial::operator[](int i) const
{
	return coefficients[i];
}

Polynomial operator*(const Polynomial &p, FiniteField f)
{
	Polynomial q(p.coefficients);
	for (FiniteField& x : q.coefficients)
		x *= f;
	while (!q.coefficients.empty() && q.coefficients.back() == 0)
		q.coefficients.pop_back();
	return q;
}

Polynomial& Polynomial::operator*=(FiniteField f)
{
	for(FiniteField& x : coefficients)
		x*=f;
	while (!coefficients.empty() && coefficients.back() == 0)
		coefficients.pop_back();
	return *this;
}

FiniteField Polynomial::operator()(FiniteField x)
{
	FiniteField res=0, xp=1;
	for(FiniteField c : coefficients)
	{
		res+=c*xp;
		xp*=x;
	}
	return res;
}
