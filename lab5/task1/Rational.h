#pragma once
#include <iostream>

/*
Класс, моделирующий рациональное число
*/
class CRational final
{
public:
	CRational(int numerator = 0, int denominator = 1);

	// Возвращает числитель
	int GetNumerator() const;

	// Возвращает знаменатель
	int GetDenominator() const;

	double CRational::ToDouble() const;
	std::pair<int, CRational> ToCompoundFraction()const;

	const CRational CRational::operator+() const;
	const CRational CRational::operator-() const;

	const CRational & operator+=(const CRational & sum);

	const CRational & operator-=(const CRational & subtrahend);

	const CRational & CRational::operator*=(const CRational & multiplier);

	const CRational & operator/=(const CRational & divider);
private:
	int m_numerator;
	int m_denominator;

	// Нормализует рациональное число
	void Normalize();
};

// Вычисляет наибольший общий делитель (greatest common denominator) чисел a и b
unsigned GCD(unsigned a, unsigned b);

const CRational operator+(const CRational & left, const CRational & right);
const CRational operator-(const CRational & left, const CRational & right);

const CRational operator*(const CRational & left, const CRational & right);
const CRational operator/(const CRational & left, const CRational & right);

const bool operator ==(CRational const & left, CRational const & right);
const bool operator !=(CRational const & left, CRational const & right);

const bool operator <(CRational const & left, CRational const & right);
const bool operator >(CRational const & left, CRational const & right);
const bool operator >=(CRational const & left, CRational const & right);
const bool operator <=(CRational const & left, CRational const & right);

std::ostream & operator <<(std::ostream & output, const CRational & rational);
std::istream & operator >> (std::istream & input, CRational & rational);