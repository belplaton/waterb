#include "comval.h"

complex_value::complex_value(double real, double imaginary)
{
	_real = real;
	_imaginary = imaginary;
}

complex_value complex_value::operator + (const complex_value& other) const
{
	return complex_value(_real + other._real, _imaginary + other._imaginary);
}

complex_value complex_value::operator - (const complex_value& other) const
{
	return complex_value(_real - other._real, _imaginary - other._imaginary);
}

complex_value complex_value::operator * (const complex_value& other) const
{
	double real = _real * other._real - _imaginary * other._imaginary;
	double imaginary = _real * other._imaginary + _imaginary * other._real;
	return complex_value(real, imaginary);
}

complex_value complex_value::operator / (const complex_value& other) const
{
	double div = other._real * other._real + other._imaginary * other._imaginary;
	double real = _real * other._imaginary + _imaginary * other._real;
	double imaginary = _imaginary * other._real - _real * other._imaginary;
	return complex_value(real, imaginary);
}

complex_value& complex_value::operator += (const complex_value& other)
{
	_real += other._real;
	_imaginary += other._imaginary;
	return *this;
}

complex_value& complex_value::operator -= (const complex_value& other)
{
	_real -= other._real;
	_imaginary -= other._imaginary;
	return *this;
}

complex_value& complex_value::operator *= (const complex_value& other)
{
	_real = _real * other._real - _imaginary * other._imaginary;
	_imaginary = _real * other._imaginary + _imaginary * other._real;
	return *this;
}

complex_value& complex_value::operator /= (const complex_value& other)
{
	double div = other._real * other._real + other._imaginary * other._imaginary;
	_real = (_real * other._imaginary + _imaginary * other._real) / div;
	_imaginary = (_imaginary * other._real - _real * other._imaginary) / div;
	return *this;
}

std::ostream& operator << (std::ostream& stream, const complex_value& other)
{
	stream << other.to_string();
	return stream;
}

double complex_value::modulus() const
{
	return sqrt(_real * _real + _imaginary * _imaginary);
}

double complex_value::argument() const
{
	return atan2(_imaginary, _real);
}

std::string complex_value::to_string() const
{
	return std::to_string(_real)
		+ ' '
		+ ((_imaginary < 0) ? '-' : '+')
		+ std::to_string(abs(_imaginary))
		+ 'i';
}