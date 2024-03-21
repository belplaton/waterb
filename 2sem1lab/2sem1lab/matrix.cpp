#include "matrix.h"

matrix::matrix(size_t size, ...) : _size(size)
{
	_elements = new double* [_size];

	va_list args;
	va_start(args, _size);

	for (size_t i = 0; i < _size; i++)
	{
		_elements[i] = new double[_size];
		auto row = va_arg(args, std::vector<double>);
		auto row_size = row.size();

		for (size_t j = 0; j < _size; j++)
		{
			if (j < row_size)
			{
				_elements[i][j] = row[j];
			}
			else
			{
				_elements[i][j] = 0.0;
			}
		}
	}

	va_end(args);
}

matrix::matrix(const matrix& other) : _size(other._size)
{
	_elements = new double* [_size];
	
	for (size_t i = 0; i < _size; i++)
	{
		_elements[i] = new double[_size];

		for (size_t j = 0; j < _size; j++)
		{
			_elements[i][j] = other._elements[i][j];
		}
	}
}

matrix::~matrix()
{
	for (size_t i = 0; i < _size; i++)
	{
		delete[] _elements[i];
	}

	delete[] _elements;
}

matrix& matrix::operator = (const matrix& other)
{
	if (this == &other)
	{
		return *this;
	}

	for (size_t i = 0; i < _size; i++)
	{
		delete[] _elements[i];
	}

	delete[] _elements;

	_size = other._size;
	_elements = new double* [_size];

	for (size_t i = 0; i < _size; i++)
	{
		_elements[i] = new double[_size];

		for (size_t j = 0; j < _size; j++)
		{
			_elements[i][j] = other._elements[i][j];
		}
	}

	return *this;
}

matrix matrix::operator + (const matrix& other) const
{
	if (_size != other._size)
	{
		throw std::invalid_argument("Cannot add matrixes with different sizes.");
	}

	matrix result(_size);

	for (size_t i = 0; i < _size; i++)
	{
		for (size_t j = 0; j < _size; j++)
		{
			result._elements[i][j] = _elements[i][j] + other._elements[i][j];
		}
	}

	return result;
}


matrix matrix::operator - (const matrix& other) const
{
	if (_size != other._size)
	{
		throw std::invalid_argument("Cannot subtract matrixes with different sizes.");
	}

	matrix result(_size);

	for (size_t i = 0; i < _size; i++)
	{
		for (size_t j = 0; j < _size; j++)
		{
			result._elements[i][j] = _elements[i][j] - other._elements[i][j];
		}
	}

	return result;
}

matrix matrix::operator * (const matrix& other) const
{
	if (_size != other._size)
	{
		throw std::invalid_argument("Cannot multiply matrixes with different sizes.");
	}

	matrix result(_size);

	for (size_t i = 0; i < _size; i++)
	{
		for (size_t j = 0; j < _size; j++)
		{
			for (size_t k = 0; k < _size; k++)
			{
				result._elements[i][j] += _elements[i][k] * other._elements[k][j];
			}
		}
	}

	return result;
}

matrix matrix::operator * (double value) const
{
	matrix result(_size);

	for (size_t i = 0; i < _size; i++)
	{
		for (size_t j = 0; j < _size; j++)
		{
			result._elements[i][j] = _elements[i][j] * value;
		}
	}

	return result;
}

double* matrix::operator [] (size_t index) const
{
	if (index >= _size)
	{
		throw std::invalid_argument("Index out of range.");
	}

	return _elements[index];
}


double matrix::determinant() const
{
	if (_size == 0)
	{
		return 0.0;
	}

	if (_size == 1)
	{
		return _elements[0][0];
	}

	matrix temp(*this);

	double det = 1.0;

	for (size_t i = 0; i < _size; i++)
	{
		size_t pivot_j = i;

		// Ищем точку не равную нулю
		while (pivot_j < _size && temp._elements[pivot_j][i] == 0)
		{
			pivot_j++;
		}

		// Не найдено строки для переставления на главную диагональ, где элемент по столбцу не будет равен 0
		if (pivot_j == _size)
		{
			return 0.0;
		}

		// Поменять местами строку со строкой главной диагонали, где мы нашли нужный нам элемент не равный 0
		if (pivot_j != i)
		{
			std::swap(temp._elements[i], temp._elements[pivot_j]);
			det *= -1;
		}

		double pivot = temp._elements[i][pivot_j];
		det *= pivot;

		// Нормализируем, преобразуем элемент по главной диагонали в единицу
		for (size_t j = i; j < _size; j++)
		{
			temp._elements[i][j] /= pivot;
		}

		// Вычитаем из каждой строки ниже элемента по главной диагонали значения, эту строку,
		// помноженную на некоторый множитель, чем является значение под элементом необходимым нам
		for (size_t k = i + 1; k < _size; k++)
		{
			double factor = temp._elements[k][i];
			for (size_t j = i; j < _size; j++)
			{
				temp._elements[k][j] -= factor * temp._elements[i][j];
			}
		}
	}
}
