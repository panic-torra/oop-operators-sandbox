﻿#include "stdafx.h"
#include "Rational.h"
#include <utility>
#include <stdexcept>


CRational::CRational(int numerator, int denominator)
	: m_numerator(numerator)
	, m_denominator(denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Denominator must not be equal to zero");
	}
	if (denominator < 0)
	{
		m_numerator = -m_numerator;
		m_denominator = -m_denominator;
	}
	Normalize();
}

int CRational::GetNumerator() const
{
	return m_numerator;
}

int CRational::GetDenominator() const
{
	return m_denominator;
}

void CRational::Normalize()
{
	const int gcd = GCD(abs(m_numerator), m_denominator);
	m_numerator /= gcd;
	m_denominator /= gcd;
}

unsigned GCD(unsigned a, unsigned b)
{
	while (b != 0)
	{
		std::swap(a, b);
		b = b % a;
	}
	return (a != 0) ? a : 1;
}

//////////////////////////////////////////////////////////////////////////
// TODO: 1. Реализовать метод ToDouble() согласно заданию
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 2. Реализовать унарный + и унарный -
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// TODO: 3. Реализовать бинарный +
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 4. Реализовать бинарный -
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 5. Реализовать оператор +=
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 6. Реализовать оператор -=
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 7. Реализовать оператор *
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 8. Реализовать оператор /
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
//////////////////////////////////////////////////////////////////////////
const CRational & CRational::operator/=(const CRational & divider)
{
	m_numerator *= divider.GetDenominator();
	m_denominator *= divider.GetNumerator();
	Normalize();
	return *this;
}

const CRational & CRational::operator/=(const int & divider)
{
	if (divider != 0)
	{
		m_denominator *= divider;
		Normalize();
	}
	return *this;
}



//////////////////////////////////////////////////////////////////////////
// TODO: 11. Реализовать операторы == и !=
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 12. Реализовать операторы <, >, <=, >=
//////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////
// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
//////////////////////////////////////////////////////////////////////////


