﻿// task1tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../task1/Rational.h"

BOOST_AUTO_TEST_CASE(Test_Greates_Common_Denominator)
{
	BOOST_CHECK_EQUAL(GCD(2, 3), 1u);
	BOOST_CHECK_EQUAL(GCD(3, 2), 1u);
	BOOST_CHECK_EQUAL(GCD(12, 8), 4u);
	BOOST_CHECK_EQUAL(GCD(8, 12), 4u);
	BOOST_CHECK_EQUAL(GCD(0, 2), 2u);
	BOOST_CHECK_EQUAL(GCD(2, 0), 2u);
	BOOST_CHECK_EQUAL(GCD(0, 0), 1u);
}

/*
  Рациональное число:
	равно нулю по умолчанию (0/1)
	может быть созданно из целого в формате (n / 1)
	может быть задано с указанием числителя и знаменателя
	хранится в нормализованном виде
	*/

void VerifyRational(const CRational & r, int expectedNumerator, int expectedDenominator)
{
	BOOST_CHECK_EQUAL(r.GetNumerator(), expectedNumerator);
	BOOST_CHECK_EQUAL(r.GetDenominator(), expectedDenominator);
}

BOOST_AUTO_TEST_SUITE(Rational_number)
	BOOST_AUTO_TEST_CASE(is_0_by_default)
	{
		VerifyRational(CRational(), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_from_integer)
	{
		VerifyRational(CRational(10), 10, 1);
		VerifyRational(CRational(-10), -10, 1);
		VerifyRational(CRational(0), 0, 1);
	}
	BOOST_AUTO_TEST_CASE(can_be_constructed_with_numerator_and_denominator)
	{
		VerifyRational(CRational(5, 2), 5, 2);
		VerifyRational(CRational(-5, 2), -5, 2);
		VerifyRational(CRational(5, -2), -5, 2);
		VerifyRational(CRational(-5, -2), 5, 2);
	}
	BOOST_AUTO_TEST_CASE(is_normalized_after_construction)
	{
		VerifyRational(CRational(6, 8), 3, 4);
		VerifyRational(CRational(6, -8), -3, 4);
		VerifyRational(CRational(-6, 8), -3, 4);
		VerifyRational(CRational(-6, -8), 3, 4);
		VerifyRational(CRational(-10, 20), -1, 2);
	}
	BOOST_AUTO_TEST_CASE(cant_have_zero_denominator)
	{
		BOOST_REQUIRE_THROW(CRational(1, 0), std::invalid_argument);
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 1. Реализовать метод ToDouble() согласно заданию
// Возвращает отношение числителя и знаменателя в виде числа double
// Пример использования:
//	CRational r(3, 5)
//	cout << r.ToDouble(); // Должно вывести 0.6
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(can_be_converted_to_double)
	{
		BOOST_CHECK_CLOSE_FRACTION(CRational(7, 8).ToDouble(), 0.875, 0.00001);
		BOOST_CHECK_CLOSE_FRACTION(CRational(8, 5).ToDouble(), 1.6, 0.00001);
		BOOST_CHECK_CLOSE_FRACTION(CRational(0).ToDouble(), 0, 0.00001);
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 2. Реализовать унарный + и унарный -
// Указание: см. материалы к лекции
// Пример использования:
//	const CRational r1(3, 5);
//	CRational r2 = -r1; // r2 должно стать -3/5
//	assert(r2.GetNumerator(), -3);
//	assert(r2.GetDenominator(), 5);
//	CRational r3 = +r2; // r3 также равно -3/5
//	assert(r3.GetNumerator(), -3);
//	assert(r3.GetDenominator(), 5);
// Унарный минус возвращает раицональное число без знака
// Унарный плюс возвращает рациональное число, равное текущему
// Реализация не должна допускать операции вроде:
//  -someRational = someOtherRational;
//	+someRational = someOtherRational;
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(has_unary_plus_that_returns_itself_without_changes)
	{
		VerifyRational(+CRational(1, 2), 1, 2);
		VerifyRational(+CRational(4, 3), 4, 3);
		VerifyRational(+CRational(0), 0, 1);
	}

	BOOST_AUTO_TEST_SUITE(has_unary_minus)
		BOOST_AUTO_TEST_CASE(that_returns_itself_with_inverted_sign)
		{
			VerifyRational(-CRational(7, 8), -7, 8);
			VerifyRational(-CRational(-7, 8), 7, 8);
			VerifyRational(-CRational(7, -8), 7, 8);
			VerifyRational(-CRational(-7, -8), -7, 8);
		}
		BOOST_AUTO_TEST_CASE(that_correctly_handles_0)
		{
			VerifyRational(-CRational(0), +0, 1);
			VerifyRational(-CRational(0), -0, 1);
		}
	BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 3. Реализовать бинарный +
// Возвращает результат сложения двух рациональных чисел, 
//	рационального числа с целым, целого числа с рациональным.
//	(1/2) + (1/6) = (2/3)
//	(1/2) + 1     = (3/2)
//	1 + (1/2)     = (3/2)
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_SUITE(has_binary_plus)
		BOOST_AUTO_TEST_CASE(that_works_with_rational)
		{
			VerifyRational(CRational(1, 2) + CRational(1, 6), 2, 3);
			VerifyRational(CRational(1, 2) + CRational(1, 2), 1, 1);
		}
		BOOST_AUTO_TEST_CASE(that_works_with_integer)
		{
			VerifyRational(CRational(1, 2) + 1, 3, 2);
			VerifyRational(1 + CRational(1, 2), 3, 2);
		}

	BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 4. Реализовать бинарный -
// Возвращает разность двух рациональных чисел, 
//	рационального числа и целого, либо целого числа и рационального:
//	(1/2) - (1/6) = (1/3)
//	(1/2) - 1     = (-1/2)
//	1 - (1/2)     = (1/2)
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_SUITE(has_binary_minus)
		BOOST_AUTO_TEST_CASE(that_works_with_rational)
		{
			VerifyRational(CRational(1, 2) - CRational(1, 6), 1, 3);
			VerifyRational(CRational(1, 2) - CRational(1, 2), 0, 1);
		}
		BOOST_AUTO_TEST_CASE(that_works_with_integer)
		{
			VerifyRational(CRational(1, 2) - 1, -1, 2);
			VerifyRational(1 - CRational(1, 2), 1, 2);
		}
	BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 5. Реализовать оператор +=
// Выполняет увеличение рационального числа на величину второго рационального,
//	либо целого числа:
//	(1/2) += (1/6)  → (2/3)
//	(1/2) += 1      → (3/2)
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_SUITE(has_sum_operation)
		BOOST_AUTO_TEST_CASE(that_works_with_rational)
		{
			CRational rational(1, 2);
			VerifyRational(rational += CRational(1, 6), 2, 3);
			VerifyRational(rational += CRational(1, 6), 5, 6);
		}
		BOOST_AUTO_TEST_CASE(that_works_with_integer)
		{
			CRational rational(1, 2);
			VerifyRational(rational += 1, 3, 2);
			VerifyRational(rational += 1, 5, 2);
		}
	BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 6. Реализовать оператор -=
// Выполняет уменьшение рационального числа на величину второго рационального либо целого числа :
// (1/2) -= (1/6)  → (1/3)
// (1/2) -= 1      → (-1/2)
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_SUITE(has_substraction_operator)
		BOOST_AUTO_TEST_CASE(that_works_with_rational)
		{
			CRational rational(1, 2);
			VerifyRational(rational -= CRational(1, 6), 1, 3);
			VerifyRational(rational -= CRational(1, 6), 1, 6);
		}
		BOOST_AUTO_TEST_CASE(that_works_with_integer)
		{
			CRational rational(1, 2);
			VerifyRational(rational -= 1, -1, 2);
			VerifyRational(rational -= 1, -3, 2);
		}
	BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 7. Реализовать оператор *
// Возвращает результат произведения рациональных чисел, 
//	рационального и целого, либо целого и рационального :
//	(1/2) * (2/3) = (1/3)
//	(1/2) * (-3)  = (-3/2)
//	7 * (2/3)     = (14/3)
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_SUITE(has_multiplication_operator)
		BOOST_AUTO_TEST_CASE(that_works_with_rational)
		{
			VerifyRational(CRational(1, 2) * CRational(2, 3), 1, 3);
			VerifyRational(CRational(1, 2) * CRational(0, 1), 0, 1);
		}
		BOOST_AUTO_TEST_CASE(that_works_with_integer)
		{
			VerifyRational(CRational(1, 2) * 0, 0, 1);
			VerifyRational(CRational(1, 2) * -3, -3, 2);
			VerifyRational(7 * CRational(2, 3), 14, 3);
		}
	BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 8. Реализовать оператор /
// Возвращает частное двух рациональных чисел, 
//	рационального и целого, целого и рационального :
//	(1/2) ⁄ (2/3) = (3/4)
//	(1/2) ⁄ 5     = (1/10)
//	7 ⁄ (2/3)     = (21/2)
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_SUITE(has_division_operator)
		BOOST_AUTO_TEST_CASE(that_works_with_rational)
		{
			VerifyRational(CRational(1, 2) / CRational(2, 3), 3, 4); 
			BOOST_REQUIRE_THROW(CRational(1, 2) / CRational(0, 1), std::invalid_argument);
		}
		BOOST_AUTO_TEST_CASE(that_works_with_integer)
		{
			BOOST_REQUIRE_THROW(CRational(1, 2) / 0, std::invalid_argument);
			VerifyRational(0 / CRational(1, 2), 0, 1);
			VerifyRational(CRational(1, 2) / 5, 1, 10);
			VerifyRational(7 / CRational(2, 3), 21, 2);
		}
	BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 9. Реализовать оператор *=
// Умножает значение первого рационального числа на другое рациональное, 
//	либо целое:
//	(1/2) *= (2/3) → (1/3)
//	(1/2) *= 3     → (3/2)
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_SUITE(has_unary_multiplication_operator)
		BOOST_AUTO_TEST_CASE(that_works_with_rational)
		{
			VerifyRational(CRational(1, 2) *= CRational(2, 3), 1, 3);
			VerifyRational(CRational(3, 4) *= CRational(4, 3), 1, 1);
		}
		BOOST_AUTO_TEST_CASE(that_works_with_integer)
		{
			VerifyRational(CRational(1, 2) *= 3, 3, 2);
			VerifyRational(CRational(1, 6) *= 0, 0, 1);
		}
	BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 10. Реализовать оператор /=
// Делит первое рациональное число на другое рациональное, 
//	либо целое:
//	(1/2) /= (2/3) → (3/4)
//	(3/4) /= (3/8) → (2/1)
//	(1/2) /= 3     → (1/6)
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_SUITE(has_unary_division_operator)
		BOOST_AUTO_TEST_CASE(that_works_with_rational)
		{
			VerifyRational(CRational(1, 2) /= CRational(2, 3), 3, 4);
			VerifyRational(CRational(3, 4) /= CRational(3, 8), 2, 1);
			VerifyRational(CRational(1, 2) /= CRational(1, 2), 1, 1);
			CRational rational(3, 2);
			rational /= rational;
			VerifyRational(rational, 1, 1);
			BOOST_REQUIRE_THROW(CRational(1, 6) /= CRational(0, 1), std::invalid_argument);
		}
		BOOST_AUTO_TEST_CASE(that_works_with_integer)
		{
			VerifyRational(CRational(1, 2) /= 3, 1, 6);
			BOOST_REQUIRE_THROW(CRational(1, 6) /= 0, std::invalid_argument);
		}
	BOOST_AUTO_TEST_SUITE_END()

//////////////////////////////////////////////////////////////////////////
// TODO: 11. Реализовать операторы == и !=
// Проверяют равенство (и неравенство) двух рациональных чисел, 
//	целого и рационального, рационального и целого:
//	(1/2) == (1/2) → true
//	(4/1) == 4     → true
//	3 == (3/1)     → true
//	(1/2) != (2/3) → true
//	(1/2) != 7     → true
//	3 != (2/3)     → true
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_SUITE(can_check_for_equality)
		BOOST_AUTO_TEST_CASE(rational_with_rational)
		{
			BOOST_CHECK(CRational(1, 2) == CRational(2, 4));
			BOOST_CHECK(!(CRational(1, 2) == CRational(1, 5)));
			BOOST_CHECK((CRational(1, 2) != CRational(8, 3)));
			BOOST_CHECK(!(CRational(1, 2) != CRational(1, 2)));
		}
		BOOST_AUTO_TEST_CASE(integer_with_rational)
		{
			BOOST_CHECK(CRational(0, 1) == 0);
			BOOST_CHECK(CRational(1, 2) != 2);
		}
		BOOST_AUTO_TEST_CASE(rational_with_integer)
		{
			BOOST_CHECK(2 == CRational(8, 4));
			BOOST_CHECK(-5 != CRational(8, 3));
		}
	BOOST_AUTO_TEST_SUITE_END()


//////////////////////////////////////////////////////////////////////////
// TODO: 12. Реализовать операторы <, >, <=, >=
// Сравнивают два рациональных числа, рациональное с целым, 
//	целое с рациональным:
//	(1/2) >= (1/3) → true
//	(1/2) <= (1/3) → false
//	(3/1) > 2      → true
//	(1/2) < 7      → true
//	3 <= (7/2)     → true
//	3 >= (8/2)     → false
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_SUITE(can_compare_with_operator_smaller)
		BOOST_AUTO_TEST_CASE(rational_with_rational)
		{
			BOOST_CHECK(!(CRational(1, 2) < CRational(1, 5)));
			BOOST_CHECK((CRational(1, 2) < CRational(8, 3)));
			BOOST_CHECK(!(CRational(1, 2) < CRational(1, 2)));
		}
		BOOST_AUTO_TEST_CASE(integer_with_rational)
		{
			BOOST_CHECK(!(CRational(1, 2) < -2));
			BOOST_CHECK((CRational(1, 2) < 2));
		}
		BOOST_AUTO_TEST_CASE(rational_with_integer)
		{
			BOOST_CHECK(!(2 < CRational(1, 5)));
			BOOST_CHECK((-5 < CRational(8, 3)));
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_SUITE(can_compare_with_operator_bigger_and_equal)
		BOOST_AUTO_TEST_CASE(rational_with_rational)
		{
			BOOST_CHECK(CRational(1, 2) >= CRational(1, 5));
			BOOST_CHECK(CRational(1, 2) >= CRational(1, 2));
			BOOST_CHECK(!(CRational(1, 2) >= CRational(8, 3)));
		}
		BOOST_AUTO_TEST_CASE(integer_with_rational)
		{
			BOOST_CHECK(CRational(1, 2) >= -2);
			BOOST_CHECK(!(CRational(1, 2) >= 2));
		}
		BOOST_AUTO_TEST_CASE(rational_with_integer)
		{
			BOOST_CHECK(2 >= CRational(1, 5));
			BOOST_CHECK(!(-5 >= CRational(8, 3)));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_compare_with_operator_bigger)
		BOOST_AUTO_TEST_CASE(rational_with_rational)
		{
			BOOST_CHECK(CRational(1, 2) > CRational(1, 5));
			BOOST_CHECK(!(CRational(1, 2) > CRational(1, 2)));
			BOOST_CHECK(!(CRational(1, 2) > CRational(8, 3)));
		}
		BOOST_AUTO_TEST_CASE(integer_with_rational)
		{
			BOOST_CHECK(CRational(1, 2) > -2);
			BOOST_CHECK(!(CRational(1, 2) > 2));
		}
		BOOST_AUTO_TEST_CASE(rational_with_integer)
		{
			BOOST_CHECK(2 > CRational(1, 5));
			BOOST_CHECK(!(-5 > CRational(8, 3)));
		}
	BOOST_AUTO_TEST_SUITE_END()


	BOOST_AUTO_TEST_SUITE(can_compare_with_operator_smaller_and_equal)
		BOOST_AUTO_TEST_CASE(rational_with_rational)
		{
			BOOST_CHECK(!(CRational(1, 2) <= CRational(1, 5)));
			BOOST_CHECK(CRational(1, 2) <= CRational(1, 2));
			BOOST_CHECK(CRational(1, 2) <= CRational(8, 3));
		}
		BOOST_AUTO_TEST_CASE(integer_with_rational)
		{
			BOOST_CHECK(!(CRational(1, 2) <= -2));
			BOOST_CHECK(CRational(1, 2) <= 2);
		}
		BOOST_AUTO_TEST_CASE(rational_with_integer)
		{
			BOOST_CHECK(!(2 <= CRational(1, 5)));
			BOOST_CHECK(-5 <= CRational(8, 3));
		}
	BOOST_AUTO_TEST_SUITE_END()


//////////////////////////////////////////////////////////////////////////
// TODO: 13. Реализовать оператор вывода рационального числа в выходной поток 
//	std::ostream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(has_operator_for_printing_to_ostream)
	{
		std::ostringstream output;
		output << CRational(1, 2);
		BOOST_CHECK_EQUAL(output.str(), "1/2");
		output.str("");
		output << "Hello " << CRational(1, 2) << " world!";
		BOOST_CHECK_EQUAL(output.str(), "Hello 1/2 world!");
		output.str("");
		output << CRational(3);
		BOOST_CHECK_EQUAL(output.str(), "3/1");
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 14. Реализовать оператор ввода рационального числа из входного потока 
//	std::istream в формате <числитель>/<знаменатель>, 
//	например: 7/15
//////////////////////////////////////////////////////////////////////////
	BOOST_AUTO_TEST_CASE(has_operator_for_getting_value_from_input)
	{
		CRational rational;
		std::stringstream input;
		input << "7/15 5:7";
		input >> rational;
		VerifyRational(rational, 7, 15);
		input >> rational;
		BOOST_CHECK(input.fail());
	}

//////////////////////////////////////////////////////////////////////////
// TODO: 15. Реализовать получения смешанной дроби из рационального числа 
// Например, рациональное число 9/4 может быть представлено в виде смешанной 
// дроби 2, 1/4
//////////////////////////////////////////////////////////////////////////
	void VerifyCompoundRational(const std::pair<int, CRational> compoundRational, int expectedInt, CRational expectedRational)
	{
		BOOST_CHECK_EQUAL(compoundRational.first, expectedInt);
		BOOST_CHECK_EQUAL(compoundRational.second, expectedRational);
	}

	BOOST_AUTO_TEST_CASE(has_a_method_to_get_a_compound_fraction)
	{
		auto compoundRational = CRational(1, 5).ToCompoundFraction();
		VerifyCompoundRational(compoundRational, 0, CRational(1, 5));

		compoundRational = CRational(9, 4).ToCompoundFraction();
		VerifyCompoundRational(compoundRational, 2, CRational(1, 4));

		compoundRational = CRational(-9, 4).ToCompoundFraction();
		VerifyCompoundRational(compoundRational, -2, CRational(-1, 4));
	}
BOOST_AUTO_TEST_SUITE_END()
