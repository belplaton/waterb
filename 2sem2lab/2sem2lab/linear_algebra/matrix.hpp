#pragma once
#ifndef _MATRIX_
#define _MATRIX_

#include <vector>
#include "../big_float/big_float.hpp"
#include "linear_algebra.hpp"

class matrix
{

private:

	std::vector<linear_vector> _elements;

public:

#pragma region Indexators

	linear_vector& operator[](size_t index)
	{
		return _elements[index];
	}

	const linear_vector& operator[](size_t index) const
	{
		return _elements[index];
	}

#pragma endregion

#pragma region Constructors

	matrix()
	{
		_elements = std::vector<linear_vector>();
	}

	matrix(unsigned int size)
	{
		_elements = std::vector<linear_vector>(size);
		for (auto i = 0; i < size; i++)
		{
			_elements[i] = linear_vector(size);
		}
	}

	matrix(unsigned int row_size, unsigned int col_size)
	{
		_elements = std::vector<linear_vector>(row_size);
		for (auto i = 0; i < row_size; i++)
		{
			_elements[i] = linear_vector(col_size);
		}
	}

	matrix(const std::vector<linear_vector>& values)
	{
		auto size = 0;
		_elements = std::vector<linear_vector>(values.size());
		for (auto i = 0; i < values.size(); i++)
		{
			size = size < values[i].size() ? values[i].size() : size;
		}

		_elements = std::vector<linear_vector>(values.size());
		for (auto i = 0; i < values.size(); i++)
		{
			_elements[i] = linear_vector(values[i], size);
		}
	}

	matrix(const std::vector<linear_vector>& values, unsigned int col_size)
	{
		_elements = std::vector<linear_vector>(values.size());
		for (auto i = 0; i < values.size(); i++)
		{
			_elements[i] = linear_vector(values[i], col_size);
		}
	}

	matrix(const std::vector<std::vector<big_float>>& values)
	{
		auto size = 0;
		for (auto i = 0; i < values.size(); i++)
		{
			size = size < values[i].size() ? values[i].size() : size;
		}

		auto vectors = std::vector<linear_vector>();
		for (auto& value : values)
		{
			auto temp = linear_vector(value, size);
			vectors.push_back(temp);
		}

		_elements = std::vector<linear_vector>(vectors);
	}

	matrix(const std::vector<std::vector<big_float>>& values, unsigned int col_size)
	{
		auto vectors = std::vector<linear_vector>();
		for (auto& value : values)
		{
			auto temp = linear_vector(value, col_size);
			vectors.push_back(temp);
		}

		_elements = std::vector<linear_vector>(vectors);
	}

	matrix(const matrix& other)
	{
		auto vectors = std::vector<linear_vector>();
		for (auto i = 0; i < other.row_size(); i++)
		{
			auto temp = linear_vector(other[i]);
			vectors.push_back(temp);
		}

		_elements = std::vector<linear_vector>(vectors);
	}

	~matrix()
	{

	}

#pragma endregion

#pragma region IO Operators

	friend std::ostream& operator << (std::ostream& stream, const matrix& other)
	{
		stream << other.to_string(10);

		return stream;
	}

#pragma endregion

#pragma region Utility

	unsigned int row_size() const
	{
		return _elements.size();
	}

	unsigned int col_size() const
	{
		if (row_size() > 0)
		{
			return _elements[0].size();
		}

		return 0;
	}

	void row_resize(unsigned int size)
	{
		_elements.resize(size);
	}

	void col_resize(unsigned int size)
	{
		for (auto i = 0; i < _elements.size(); i++)
		{
			_elements[i].resize(size);
		}
	}

	void resize(unsigned int row_size, unsigned int col_size)
	{
		row_resize(row_size);
		col_resize(col_size);
	}

	big_float determinant() const
	{
		int n = _elements.size();
		if (n == 1)
		{
			return _elements[0][0];
		}
		if (n == 2)
		{
			return _elements[0][0] * _elements[1][1] - _elements[0][1] * _elements[1][0];
		}

		big_float det = 0;
		for (auto i = 0; i < n; i++)
		{
			auto submatrix = matrix(n - 1);
			for (auto j = 1; j < n; j++)
			{
				int subcol = 0;
				for (auto k = 0; k < n; ++k)
				{
					if (k == i) continue;
					submatrix[j - 1][subcol++] = _elements[j][k];
				}
			}
				
			auto sign = (i % 2 == 0) ? 1 : -1;
			det += sign * _elements[0][i] * submatrix.determinant();
		}

		return det;
	}

	std::string to_string(unsigned int base) const
	{
		std::string result;

		auto space = false;
		for (auto i = 0; i < _elements.size(); i++)
		{
			if (space) result += "\n";
			result += _elements[i].to_string(10);
			space = true;
		}

		return result;
	}

#pragma endregion

};

#endif // !_MATRIX_
