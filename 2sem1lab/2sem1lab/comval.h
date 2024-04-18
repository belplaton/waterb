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

	// Сложение комплексных чисел
	complex_value operator + (const complex_value& other) const;

	// Вычитание комплексных чисел
	complex_value operator - (const complex_value& other) const;

	// Умножение комплексных чисел
	complex_value operator * (const complex_value& other) const;

	// Деление комплексных чисел
	complex_value operator / (const complex_value& other) const;

	// Сложение с комплексным числом
	complex_value& operator += (const complex_value& other);

	// Вычитание комплексного числа
	complex_value& operator -= (const complex_value& other);

	// Умножение на комплексное число
	complex_value& operator *= (const complex_value& other);

	// Деление комплексных чисел
	complex_value& operator /= (const complex_value& other);

	// Потоковый вывод строковой визуализации
	friend std::ostream& operator << (std::ostream& stream, const complex_value& other);

	// Модуль комплексного числа
	double modulus() const;

	// Аргумент комплексного числа
	double argument() const;

	// Строковая визуализация
	std::string to_string() const;
};
