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

	// Сложение комплексных чисел
	inline complex_value operator + (const complex_value& other) const;

	// Вычитание комплексных чисел
	inline complex_value operator - (const complex_value& other) const;

	// Умножение комплексных чисел
	inline complex_value operator * (const complex_value& other) const;

	// Деление комплексных чисел
	inline complex_value operator / (const complex_value& other) const;

	// Сложение с комплексным числом
	inline complex_value& operator += (const complex_value& other);

	// Вычитание комплексного числа
	inline complex_value& operator -= (const complex_value& other);

	// Умножение на комплексное число
	inline complex_value& operator *= (const complex_value& other);

	// Деление комплексных чисел
	inline complex_value& operator /= (const complex_value& other);

	// Потоковый вывод строковой визуализации
	friend inline ostream& operator << (ostream& stream, const complex_value& other);

	// Модуль комплексного числа
	inline double modulus() const;

	// Аргумент комплексного числа
	inline double argument() const;

	// Строковая визуализация
	inline string to_string() const;
};