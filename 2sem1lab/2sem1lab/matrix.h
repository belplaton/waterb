#pragma once

#include <cstdarg>
#include <vector>
#include <stdexcept>

class matrix
{

private:

	double** _elements;
	size_t _size;

public:

	matrix(size_t size, ...);

	matrix(const matrix& other);

	~matrix();

	matrix& operator = (const matrix& other);

	matrix operator + (const matrix& other) const;

	matrix operator - (const matrix& other) const;

	matrix operator * (const matrix& other) const;

	matrix operator * (double value) const;

	double* operator [] (size_t index) const;

	double determinant() const;

	matrix transpose() const;

	matrix inverse() const;
};