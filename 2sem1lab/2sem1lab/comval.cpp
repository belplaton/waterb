#include "comval.h"

using namespace std;

class complex_value
{

private:

	double _real;
	double _imaginary;

public:

	complex_value(double real = 0, double imaginary = 0)
	{
		_real = real;
		_imaginary = imaginary;
	}

	inline complex_value operator + (const complex_value& other) const
	{
		return complex_value(_real + other._real, _imaginary + other._imaginary);
	}

	inline complex_value operator - (const complex_value& other) const
	{
		return complex_value(_real - other._real, _imaginary - other._imaginary);
	}

	inline complex_value operator * (const complex_value& other) const
	{
		double real = _real * other._real - _imaginary * other._imaginary;
		double imaginary = _real * other._imaginary + _imaginary * other._real;
		return complex_value(real, imaginary);
	}

	inline complex_value operator / (const complex_value& other) const
	{
		double div = other._real * other._real + other._imaginary * other._imaginary;
		double real = _real * other._imaginary + _imaginary * other._real;
		double imaginary = _imaginary * other._real - _real * other._imaginary;
		return complex_value(real, imaginary);
	}

	inline complex_value& operator += (const complex_value& other)
	{
		_real += other._real;
		_imaginary += other._imaginary;
		return *this;
	}

	inline complex_value& operator -= (const complex_value& other)
	{
		_real -= other._real;
		_imaginary -= other._imaginary;
		return *this;
	}

	inline complex_value& operator *= (const complex_value& other)
	{
		_real = _real * other._real - _imaginary * other._imaginary;
		_imaginary = _real * other._imaginary + _imaginary * other._real;
		return *this;
	}

	inline complex_value& operator /= (const complex_value& other)
	{
		double div = other._real * other._real + other._imaginary * other._imaginary;
		_real = (_real * other._imaginary + _imaginary * other._real) / div;
		_imaginary = (_imaginary * other._real - _real * other._imaginary) / div;
		return *this;
	}

	friend inline ostream& operator << (ostream& stream, const complex_value& other)
	{
		stream << other.to_string();
		return stream;
	}

	inline double modulus() const
	{
		return sqrt(_real * _real + _imaginary * _imaginary);
	}

	inline double argument() const
	{
		return atan2(_imaginary, _real);
	}

	inline string to_string() const
	{
		return std::to_string(_real)
			+ ((_imaginary < 0) ? '-' : '+')
			+ std::to_string(abs(_imaginary));
	}
};