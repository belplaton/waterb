#include <iostream>
#include <cmath>
#include <string>
#include <format>

class complex_value
{

private:

	double _real;
	double _imaginary;

public:

	complex_value(double real = 0, double imaginary = 0);

	// �������� ����������� �����
	inline complex_value operator + (const complex_value& other) const;

	// ��������� ����������� �����
	inline complex_value operator - (const complex_value& other) const;

	// ��������� ����������� �����
	inline complex_value operator * (const complex_value& other) const;

	// ������� ����������� �����
	inline complex_value operator / (const complex_value& other) const;

	// �������� � ����������� ������
	inline complex_value& operator += (const complex_value& other);

	// ��������� ������������ �����
	inline complex_value& operator -= (const complex_value& other);

	// ��������� �� ����������� �����
	inline complex_value& operator *= (const complex_value& other);

	// ������� ����������� �����
	inline complex_value& operator /= (const complex_value& other);

	// ��������� ����� ��������� ������������
	friend inline ostream& operator << (ostream& stream, const complex_value& other);

	// ������ ������������ �����
	inline double modulus() const;

	// �������� ������������ �����
	inline double argument() const;

	// ��������� ������������
	inline string to_string() const;
};