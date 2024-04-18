#pragma once

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

	complex_value(const complex_value& other);

	~complex_value();

	// �������� ����������� �����
	complex_value operator + (const complex_value& other) const;

	// ��������� ����������� �����
	complex_value operator - (const complex_value& other) const;

	// ��������� ����������� �����
	complex_value operator * (const complex_value& other) const;

	// ������� ����������� �����
	complex_value operator / (const complex_value& other) const;

	// �������� � ����������� ������
	complex_value& operator += (const complex_value& other);

	// ��������� ������������ �����
	complex_value& operator -= (const complex_value& other);

	// ��������� �� ����������� �����
	complex_value& operator *= (const complex_value& other);

	// ������� ����������� �����
	complex_value& operator /= (const complex_value& other);

	// ��������� ����� ��������� ������������
	friend std::ostream& operator << (std::ostream& stream, const complex_value& other);

	// ������ ������������ �����
	double modulus() const;

	// �������� ������������ �����
	double argument() const;

	// ��������� ������������
	std::string to_string() const;
};
