// Ilie Dumitru

#ifndef RS_FINITE_FIELD
#define RS_FINITE_FIELD

constexpr int SIGMA=256;

#include "precalc_finite_field_multiplication_table.cpp"

struct FiniteField
{
	int polyId;

	FiniteField(int polyId=0) : polyId(polyId) {}

	FiniteField operator+(FiniteField other) const
	{
		return FiniteField(polyId^other.polyId);
	}

	FiniteField operator-(FiniteField other) const
	{
		return FiniteField(polyId^other.polyId);
	}

	FiniteField operator-() const
	{
		return *this;
	}

	FiniteField operator*(FiniteField other) const
	{
		return ff_times[polyId][other.polyId];
	}

	FiniteField operator/(FiniteField other) const
	{
		return ff_times[polyId][ff_inv[other.polyId]];
	}

	FiniteField inv() const
	{
		return ff_inv[polyId];
	}

	bool operator==(FiniteField other) const
	{
		return polyId==other.polyId;
	}

	bool operator!=(FiniteField other) const
	{
		return polyId!=other.polyId;
	}

	FiniteField& operator+=(FiniteField other)
	{
		polyId^=other.polyId;
		return *this;
	}

	FiniteField& operator-=(FiniteField other)
	{
		polyId^=other.polyId;
		return *this;
	}

	FiniteField& operator*=(FiniteField other)
	{
		polyId=ff_times[polyId][other.polyId];
		return *this;
	}

	FiniteField& operator/=(FiniteField other)
	{
		polyId=ff_times[polyId][ff_inv[other.polyId]];
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& out, FiniteField f)
	{
		return out << f.polyId;
	}
};

#endif // RS_FINITE_FIELD
