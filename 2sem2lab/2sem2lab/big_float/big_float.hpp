#pragma once
#ifndef _BIGFLOAT_
#define _BIGFLOAT_

#include "../big_int/big_int.hpp"

class big_float
{

private:

	big_int _numerator;
	big_int _denominator;

public:

	friend class big_int;

#pragma region Constructors

	big_float()
	{
		_numerator = big_int(0);
		_denominator = big_int(1);
	}

	big_float(unsigned int digit)
	{
		_numerator = big_int(digit);
		_denominator = big_int(1);
	}

	big_float(const big_int& digit)
	{
		_numerator = big_int(digit);
		_denominator = big_int(1);
	}

	big_float(const big_int& numerator, const big_int& denominator)
	{
		if (denominator == 0)
		{
			throw std::invalid_argument("Denominator cant be 0");
		}

		_numerator = numerator;
		_denominator = denominator;

		optimize(this);
	}

	big_float(const std::string& numerator, const std::string& denominator, unsigned int base)
	{
		auto a = big_int(numerator, base);
		auto b = big_int(denominator, base);

		if (b == 0)
		{
			throw std::invalid_argument("Denominator cant be 0");
		}

		_numerator = a;
		_denominator = b;

		optimize(this);
	}

	big_float(const std::string& numerator, const std::string& denominator)
	{
		auto a = big_int(numerator, 10);
		auto b = big_int(denominator, 10);

		if (b == 0)
		{
			throw std::invalid_argument("Denominator cant be 0");
		}

		_numerator = a;
		_denominator = b;

		optimize(this);
	}

	big_float(const std::string& other)
	{
		auto is_negative = other.size() > 0 && (other[0] == '-');
		auto valid_number = true;

		auto is_slash = false;
		auto slash_index = -1;
		for (int i = is_negative; i < other.size(); i++)
		{
			if (!is_slash && other[i] == '/' && i != 0 && i != other.size() - 1)
			{
				slash_index = i;
				is_slash = true;
			}
			else if (!std::isdigit(other[i]))
			{
				valid_number = false;
				break;
			}

			if (is_slash && slash_index == other.size() - 1)
			{
				valid_number = false;
				break;
			}
		}

		if (!valid_number)
		{
			throw std::invalid_argument("Invalid number format! Use <sign><numerator>/<denominator> with decimal format.");
		}

		if (!is_slash)
		{
			_numerator = big_int(other.substr(is_negative, other.size()));
			_denominator = big_int(1);
		}
		else
		{
			_numerator = big_int(other.substr(is_negative, slash_index - is_negative), 10);
			_denominator = big_int(other.substr(slash_index + 1, other.size() - slash_index), 10);
		}

		if (is_negative) _denominator = -_denominator;

		optimize(this);
	}

	big_float(const big_float& other)
	{
		_numerator = big_int(other._numerator);
		_denominator = big_int(other._denominator);
	}


	~big_float()
	{

	}

#pragma endregion

#pragma region Relational Operators

	bool operator == (const big_float& other) const
	{
		return (_numerator == other._numerator) && (_denominator == other._denominator);
	}

	bool operator != (const big_float& other) const
	{
		return !(*this == other);
	}

	bool operator < (const big_float& other) const
	{
		if (big_int::is_negate(_denominator) && !big_int::is_negate(other._denominator)) return true;
		if (!big_int::is_negate(_denominator) && big_int::is_negate(other._denominator)) return false;

		auto op1 = _numerator * other._denominator;
		auto op2 = other._numerator * _denominator;

		return op1 < op2;
	}

	bool operator <= (const big_float& other) const
	{
		return (*this < other) || (*this == other);
	}

	bool operator > (const big_float& other) const
	{
		return !(*this <= other);
	}

	bool operator >= (const big_float& other) const
	{
		return !(*this < other);
	}

#pragma endregion

#pragma region Arithmetic Operators

#pragma region Big Float

	big_float operator + () const
	{
		return *this;
	}

	big_float operator - () const
	{
		auto temp = big_float(*this);
		temp._denominator = -temp._denominator;

		return temp;
	}

	big_float operator + (const big_float& other) const
	{
		auto temp = big_float(*this);
		temp += other;

		big_float::optimize(&temp);
		return temp;
	}

	big_float operator - (const big_float& other) const
	{
		auto temp = big_float(*this);
		temp -= other;

		big_float::optimize(&temp);
		return temp;
	}

	big_float operator / (const big_float& other) const
	{
		auto temp = big_float(*this);
		temp /= other;

		big_float::optimize(&temp);
		return temp;
	}

	big_float operator * (const big_float& other) const
	{
		auto temp = big_float(*this);
		temp *= other;

		big_float::optimize(&temp);
		return temp;
	}

	big_int operator / (const big_int& right)
	{
		auto temp = _denominator * right;
		return _numerator / temp;
	}

	big_int operator % (const big_int& right)
	{
		auto temp = _denominator * right;
		return _numerator % temp;
	}

#pragma endregion

#pragma region Big Int

	big_float operator + (const big_int& other) const
	{
		auto temp = big_float(*this);
		temp += other;

		big_float::optimize(&temp);
		return temp;
	}

	big_float operator - (const big_int& other) const
	{
		auto temp = big_float(*this);
		temp -= other;

		big_float::optimize(&temp);
		return temp;
	}

	big_float operator / (const big_int& other) const
	{
		auto temp = big_float(*this);
		temp /= other;

		big_float::optimize(&temp);
		return temp;
	}

	big_float operator * (const big_int& other) const
	{
		auto temp = big_float(*this);
		temp *= other;

		big_float::optimize(&temp);
		return temp;
	}

	friend big_float operator + (const big_int left, const big_float& right)
	{
		auto result = big_float(left);
		result += right;
		return result;
	}

	friend big_float operator - (const big_int left, const big_float& right)
	{
		auto result = big_float(left);
		result -= right;
		return result;
	}

	friend big_float operator * (const big_int left, const big_float& right)
	{
		auto result = big_float(left);
		result *= right;
		return result;
	}

	friend big_float operator / (const big_int left, const big_float& right)
	{
		auto result = big_float(left);
		result /= right;
		return result;
	}

#pragma endregion

#pragma endregion

#pragma region Assigment Arithmetic Operators

#pragma region Big Float

	big_float& operator += (const big_float& other)
	{
		_numerator *= other._denominator;
		_numerator += other._numerator * _denominator;
		_denominator *= other._denominator;

		big_float::optimize(this);
		return *this;
	}

	big_float& operator -= (const big_float& other)
	{
		_numerator *= other._denominator;
		auto temp = (other._numerator * _denominator);
		_numerator -= temp;
		_denominator *= other._denominator;

		big_float::optimize(this);
		return *this;
	}

	big_float& operator *= (const big_float& other)
	{
		_numerator *= other._numerator;
		_denominator *= other._denominator;

		big_float::optimize(this);
		return *this;
	}

	big_float& operator /= (const big_float& other)
	{
		_numerator *= other._denominator;
		_denominator *= other._numerator;

		big_float::optimize(this);
		return *this;
	}

#pragma endregion

#pragma region Big Int

	big_float& operator += (const big_int& other)
	{
		_numerator += other * _denominator;

		big_float::optimize(this);
		return *this;
	}

	big_float& operator -= (const big_int& other)
	{
		_numerator -= other * _denominator;

		big_float::optimize(this);
		return *this;
	}

	big_float& operator *= (const big_int& other)
	{
		_numerator *= other;

		big_float::optimize(this);
		return *this;
	}

	big_float& operator /= (const big_int& other)
	{
		_denominator *= other;

		big_float::optimize(this);
		return *this;
	}

#pragma endregion

#pragma endregion

#pragma region IO Operators

	friend std::ostream& operator << (std::ostream& stream, const big_float& other)
	{
		stream << (big_int::is_negate(other._denominator) ? "-" : "") <<
			other._numerator.to_string(10) <<
			"/" <<
			big_int::abs(other._denominator).to_string(10);

		return stream;
	}

	friend std::istream& operator >> (std::istream& stream, big_float& number)
	{
		auto input = std::string();
		stream >> input;

		auto is_negative = input.size() > 0 && (input[0] == '-');
		auto valid_input = true;

		auto is_slash = false;
		for (int i = is_negative; i < input.size(); i++)
		{
			if (!is_slash && input[i] == '/' && i != 0 && i != input.size() - 1)
			{
				is_slash = true;
			}
			else if (!std::isdigit(input[i]))
			{
				valid_input = false;
				break;
			}
		}

		if (!valid_input || !is_slash)
		{
			stream.setstate(std::ios::failbit);
			return stream;
		}

		number = big_float(input);

		return stream;
	}

#pragma endregion

#pragma region Utility

	inline static void optimize(big_float* other)
	{
		auto min_divisor = gcd((*other)._numerator, (*other)._denominator);
		(*other)._numerator /= min_divisor;
		(*other)._denominator /= min_divisor;

		if ((*other)._numerator < 0)
		{
			(*other)._numerator = -(*other)._numerator;
			(*other)._denominator = -(*other)._denominator;
		}
	}

	inline static big_float abs(const big_float& other)
	{
		if (other < 0) return big_float(-other);
		return other;
	}

	std::string to_string(unsigned int base) const
	{
		if (base < 2 || base > 36)
		{
			throw std::invalid_argument("Invalid base.");
		}

	}

	friend big_float pow(const big_float& base, const big_int& exponent)
	{
		if (exponent == 0) return 1;
		if (exponent > 0)
		{
			auto result = big_float(base);
			result._numerator = pow(result._numerator, exponent);
			result._denominator = pow(result._denominator, exponent);

			return result;
		}
	}

	friend big_float pow(const big_float& base, const big_float& exponent)
	{
		if (exponent == 0) return 1;

	}

	friend big_float root(const big_float& base, const big_int& exponent, const big_float& epsilon)
	{
		if (base == 0 || base == 1) return base;

		if (exponent == 0)
		{
			throw std::invalid_argument("Cannot compute the 0th root.");
		}

		big_float x = 1;
		big_float prev_x;

		do
		{
			prev_x = x;
			auto s = pow(prev_x, exponent);
			auto numerator = s - base;
			auto k = pow(prev_x, exponent - 1);
			auto denominator = k * exponent;
			x = numerator / denominator;
			std::cout << x << "\t " << prev_x << "\t " << epsilon;
			std::cout << "\t " << (x - prev_x) << std::endl;
			std::cout << (big_float::abs(x - prev_x) >= epsilon) << std::endl;

		} while (big_float::abs(x - prev_x) >= epsilon); // Проверяем на достижение точности

		return x;
	}

#pragma endregion

};

#endif // ! _BIGFLOAT_
