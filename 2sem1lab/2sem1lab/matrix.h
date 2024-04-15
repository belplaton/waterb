#pragma once

#include <cstdarg>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>

class column
{

	friend class matrix;

private:

	std::vector<double> _elements;
	size_t _size;

public:

	double operator [] (size_t index) const;

	column(size_t size = 0, std::vector<double> elements = std::vector<double>());

	column(const column& other);

	~column();

	column& operator = (const column& other);

};

class matrix
{

private:

	column* _elements;
	size_t _size;

public:

	matrix(size_t size, int count, ...);

	matrix(const matrix& other);

	~matrix();

	matrix& operator = (const matrix& other);

	matrix operator + (const matrix& other) const;

	matrix operator - (const matrix& other) const;

	matrix operator * (const matrix& other) const;

	matrix operator * (double value) const;

	column operator [] (size_t index) const;

	double determinant() const;

	matrix transpose() const;

	matrix inverse() const;

	// Строковая визуализация
	std::string to_string() const;

	// Потоковый вывод строковой визуализации
	friend std::ostream& operator << (std::ostream& stream, const matrix& other);
};