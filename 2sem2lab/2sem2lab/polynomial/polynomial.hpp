#pragma once
#ifndef _POLYNOMIAL_
#define _POLYNOMIAL_

#include <string>
#include <sstream>
#include <regex>
#include "../big_int/big_int.hpp"
#include "../big_float/big_float.hpp"
#include "../linked_list/linked_list.hpp"

static std::regex polynomial_pattern(R"(\{([^{}]+?)\})");
static std::regex polynomial_data_pattern(R"(\[(\+|\-)\]\[(\d+\/\d+)\]x\^\[((-)?(\d+))\])");

class polynomial
{

public:

	struct polynomial_data
	{

	public:

		big_int degree;
		big_float coefficient;

		polynomial_data(big_int degree, big_float coefficient) : degree(degree), coefficient(coefficient)
		{

		}

		polynomial_data(bool is_default = true) : degree(0), coefficient(0)
		{

		}

		std::string to_string(unsigned int base) const
		{
			std::stringstream result = std::stringstream();

			result << "[" << (coefficient.is_negate() ? "-" : "+") <<
				"][" << big_float::abs(coefficient).to_string(base) <<
				"]x^[" << degree.to_string(base) << "]";

			return result.str();
		}

		big_float process_variable(const big_float& variable)
		{
			auto result = coefficient * pow(variable, degree);
			return result;
		}
	};

private:

	linked_list<polynomial_data> _polynomial_list;

#pragma region  Utility

	void sort()
	{
		_polynomial_list.sort([](polynomial_data a, polynomial_data b) { return a.degree > b.degree; });
	}


#pragma endregion

public:

#pragma region Constructors

	polynomial()
	{
		_polynomial_list = linked_list<polynomial_data>();
	}

	polynomial(const big_int& coefficient)
	{
		_polynomial_list = linked_list<polynomial_data>();
		_polynomial_list.add_value({ 1, big_float(coefficient) });
	}

	polynomial(const big_float& coefficient)
	{
		_polynomial_list = linked_list<polynomial_data>();
		_polynomial_list.add_value({ 1, coefficient });
	}

	polynomial(const big_float& coefficient, const big_int& exponent)
	{
		_polynomial_list = linked_list<polynomial_data>();
		_polynomial_list.add_value({ exponent, coefficient });
	}

	polynomial(const polynomial_data& other)
	{
		_polynomial_list = linked_list<polynomial_data>();
		_polynomial_list.add_value(other);
	}

	polynomial(const std::string& other)
	{
		_polynomial_list = linked_list<polynomial_data>();

		std::sregex_iterator iter(other.begin(), other.end(), polynomial_pattern);
		std::sregex_iterator end;

		if (!is_polynomial(other))
		{
			throw std::invalid_argument("Invalid number format! Use [<sign>][<numerator/denominator>]x^[<exponent>] with decimal format.");
		}

		if (iter != end)
		{
			while (iter != end)
			{
				auto match = *iter;
				auto data_matches = std::smatch();
				auto current = match.str();
				if (std::regex_search(current, data_matches, polynomial_data_pattern))
				{
					auto is_negate = data_matches[1].str() == "-";
					auto coefficient = big_float(data_matches[2].str());
					if (is_negate) coefficient = -coefficient;

					auto degree = big_int(data_matches[3].str());
					auto temp_data = polynomial_data(degree, coefficient);

					*this += temp_data;
				}

				++iter;
			}
		}
	}

	polynomial(const polynomial& other)
	{
		_polynomial_list = linked_list<polynomial_data>(other._polynomial_list);
	}

	~polynomial()
	{
		_polynomial_list.clear();
	}

#pragma endregion

#pragma region Relational Operators

	bool operator == (const polynomial& other) const
	{
		if (_polynomial_list.get_length() != other._polynomial_list.get_length()) return false;

		for (auto& value : other._polynomial_list)
		{
			auto data = _polynomial_list.find([value](polynomial_data x)
				{ 
				return x.degree == value.degree && x.coefficient == value.coefficient; 
				}
			);

			if (data == nullptr) return false;
		}

		return true;
	}

	bool operator != (const polynomial & other) const
	{
		return !(*this == other);
	}

#pragma endregion

#pragma region Unary Operators

	polynomial operator + () const
	{
		return *this;
	}

	polynomial operator - () const
	{
		auto temp(*this);
		for (auto& element : temp._polynomial_list)
		{
			element.coefficient = -element.coefficient;
		}

		return temp;
	}

	static big_float diff(const polynomial_data& other, const big_float& variable)
	{
		auto temp = big_float();
		temp = other.coefficient * other.degree;
		temp *= pow(variable, other.degree - 1);

		return temp;
	}

	static big_float diff(const polynomial& other, const big_float& variable)
	{
		auto temp = big_float();

		for (auto& element : other._polynomial_list)
		{
			temp += diff(element, variable);
		}

		return temp;
	}

	static big_float integr(const polynomial_data& other, const big_float& variable)
	{
		auto temp = big_float();
		if (other.degree != -1)
		{
			temp = other.coefficient / (other.degree + 1);
			temp *= pow(variable, other.degree + 1);
		}
		else
		{
			auto eps = big_float("1/10");
			temp = other.coefficient * logn(variable, eps);
		}

		return temp;
	}

	static big_float integr(const polynomial& other, const big_float& variable)
	{
		auto temp = big_float();

		for (auto& element : other._polynomial_list)
		{
			temp += integr(element, variable);
		}

		return temp;
	}

#pragma endregion

#pragma region Assigment Arithmetic Operators

#pragma region Polynomial Data

	polynomial& operator += (const polynomial_data& other)
	{
		auto cmp = [other](polynomial_data x) { return x.degree == other.degree; };
		auto element = _polynomial_list.find(cmp);
		if (element != nullptr)
		{
			(*element).coefficient += other.coefficient;
		}
		else if (other.coefficient != 0)
		{
			_polynomial_list.add_value(other);
		}

		return *this;
	}

	polynomial& operator -= (const polynomial_data& other)
	{
		auto cmp = [other](polynomial_data x) { return x.degree == other.degree; };
		auto element = _polynomial_list.find(cmp);
		if (element != nullptr)
		{
			(*element).coefficient -= other.coefficient;
		}
		else if (other.coefficient != 0)
		{
			auto temp = polynomial_data(other.degree, -other.coefficient);
			_polynomial_list.add_value(temp);
		}

		return *this;
	}

	polynomial& operator *= (const polynomial_data& other)
	{
		for (auto& value : _polynomial_list)
		{
			value.coefficient *= other.coefficient;
			value.degree += other.degree;
		}

		return *this;
	}

	polynomial& operator /= (const polynomial_data& other)
	{
		for (auto& value : _polynomial_list)
		{
			value.coefficient /= other.coefficient;
			value.degree -= other.degree;
		}

		return *this;
	}

#pragma endregion

#pragma region Polymonial

	polynomial& operator += (const polynomial& other)
	{
		for (auto& value : other._polynomial_list)
		{
			*this += value;
		}

		return *this;
	}

	polynomial& operator -= (const polynomial& other)
	{
		for (auto& value : other._polynomial_list)
		{
			*this -= value;
		}

		return *this;
	}

	polynomial& operator *= (const polynomial& other)
	{
		for (auto& value : other._polynomial_list)
		{
			*this *= value;
		}

		return *this;
	}

	polynomial& operator /= (const polynomial& other)
	{
		for (auto& value : other._polynomial_list)
		{
			*this /= value;
		}

		return *this;
	}

#pragma endregion

#pragma region Big Float

	polynomial& operator += (const big_float& other)
	{
		auto value = polynomial_data(1, other);
		*this += value;

		return *this;
	}

	polynomial& operator -= (const big_float& other)
	{
		auto value = polynomial_data(1, other);
		*this -= value;

		return *this;
	}

	polynomial& operator *= (const big_float& other)
	{
		auto value = polynomial_data(1, other);
		*this *= value;

		return *this;
	}

	polynomial& operator /= (const big_float& other)
	{
		auto value = polynomial_data(1, other);
		*this /= value;

		return *this;
	}

#pragma endregion

#pragma endregion

#pragma region Arithmetic Operators

#pragma region Polynomial Data

	polynomial operator + (const polynomial_data& other) const
	{
		auto temp = polynomial(*this);
		temp += other;

		return temp;
	}

	polynomial operator - (const polynomial_data& other) const
	{
		auto temp = polynomial(*this);
		temp -= other;

		return temp;
	}

	polynomial operator * (const polynomial_data& other) const
	{
		auto temp = polynomial(*this);
		temp += other;

		return temp;
	}

	polynomial operator / (const polynomial_data& other) const
	{
		auto temp = polynomial(*this);
		temp /= other;

		return temp;
	}

#pragma endregion

#pragma region Polynomial

	polynomial operator + (const polynomial& other) const
	{
		auto temp = polynomial(*this);
		temp += other;

		return temp;
	}

	polynomial operator - (const polynomial& other) const
	{
		auto temp = polynomial(*this);
		temp -= other;

		return temp;
	}

	polynomial operator * (const polynomial& other) const
	{
		auto temp = polynomial(*this);
		temp *= other;

		return temp;
	}

	polynomial operator / (const polynomial& other) const
	{
		auto temp = polynomial(*this);
		temp /= other;

		return temp;
	}

#pragma endregion

#pragma region Big Float

	polynomial operator + (const big_float& other) const
	{
		auto temp = polynomial(*this);
		temp += other;

		return temp;
	}

	polynomial operator - (const big_float& other) const
	{
		auto temp = polynomial(*this);
		temp -= other;

		return temp;
	}

	polynomial operator * (const big_float& other) const
	{
		auto temp = polynomial(*this);
		temp *= other;

		return temp;
	}

	polynomial operator / (const big_float& other) const
	{
		auto temp = polynomial(*this);
		temp /= other;

		return temp;
	}

#pragma endregion

#pragma endregion

#pragma region IO Operators

	friend std::ostream& operator << (std::ostream& stream, const polynomial& other)
	{
		stream << other.to_string(10);

		return stream;
	}

	friend std::istream& operator >> (std::istream& stream, polynomial& other)
	{
		auto input = std::string();
		stream >> input;

		if (!is_polynomial(input))
		{
			stream.setstate(std::ios::failbit);
			return stream;
		}

		other = polynomial(input);

		return stream;
	}

#pragma endregion

#pragma region Utility

	std::string to_string(unsigned int base)  const
	{
		std::stringstream result = std::stringstream();

		result << "(";
		auto space = false;
		for (auto& value : _polynomial_list)
		{
			if (space) result << " ";
			result << "{" << value.to_string(base) << "}";
			space = true;
		}

		result << ")";

		return result.str();
	}

	static bool is_polynomial(std::string value)
	{
		polynomial* result = nullptr;
		std::sregex_iterator iter(value.begin(), value.end(), polynomial_pattern);
		std::sregex_iterator end;

		if (iter != end)
		{
			while (iter != end)
			{
				auto match = *iter;
				auto data_matches = std::smatch();
				auto current = match.str();
				if (!std::regex_search(current, data_matches, polynomial_data_pattern))
				{
					return false;
				}

				++iter;
			}
		}
		else
		{
			return false;
		}

		return true;
	}

	big_float process_variable(const big_float& variable)
	{
		auto result = big_float();
		for (auto& element : _polynomial_list)
		{
			result += element.process_variable(variable);
		}

		return result;
	}

#pragma endregion

};

#endif // ! _POLYNOMIAL_
