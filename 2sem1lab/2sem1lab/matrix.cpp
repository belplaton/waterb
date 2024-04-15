#include "matrix.h"

column::column(size_t size, std::vector<double> elements) : _size(size)
{
	_elements = *new std::vector<double>(_size);

	int elements_count = elements.size();

	for (auto i = 0; (i < elements_count) && (i < _size); i++)
	{
		_elements[i] = elements[i];
	}
}

column::column(const column& other) : _size(other._size)
{
	_elements = *new std::vector<double>(_size);

	for (auto i = 0; i < _size; i++)
	{
		_elements[i] = other._elements[i];
	}
}

column::~column()
{

}

double column::operator [] (size_t index) const
{
	if (index >= _size)
	{
		throw std::invalid_argument("Index out of range.");
	}

	return _elements[index];
}

column& column::operator = (const column& other)
{
	if (this == &other)
	{
		return *this;
	}

	_size = other._size;
	_elements = *new std::vector<double>(_size);
	for (auto i = 0; i < other._size; i++)
	{
		_elements[i] = other._elements[i];
	}

	return *this;
}

matrix::matrix(size_t size, int count, ...) : _size(size)
{
	_elements = new column[_size];

	va_list args;
	va_start(args, count);

	int k = 0;

	for (auto i = 0; (i < _size) && (i < count); i++)
	{
		auto col = va_arg(args, std::vector<double>);

		_elements[i] = *(new column(_size, col));
	}

	va_end(args);
}

matrix::matrix(const matrix& other) : _size(other._size)
{
	_elements = new column[_size];
	
	for (auto i = 0; i < _size; i++)
	{
		_elements[i] = *(new column(other._elements[i]));
	}
}

matrix::~matrix()
{
	for (auto i = 0; i < _size; i++)
	{
		delete[] &_elements[i];
	}

	delete[] _elements;
}

matrix& matrix::operator = (const matrix& other)
{
	if (this == &other)
	{
		return *this;
	}

	for (auto i = 0; i < _size; i++)
	{
		delete[] &_elements[i];
	}

	delete[] _elements;

	_size = other._size;
	_elements = new column[_size];
	for (auto i = 0; i < _size; i++)
	{
		_elements[i] = *(new column(other._elements[i]));
	}

	return *this;
}

matrix matrix::operator + (const matrix& other) const
{
	if (_size != other._size)
	{
		throw std::invalid_argument("Cannot add matrixes with different sizes.");
	}

	matrix result(_size, 0);

	for (auto i = 0; i < _size; i++)
	{
		for (auto j = 0; j < _size; j++)
		{
			result[i]._elements[j] = _elements[i][j] + other._elements[i][j];
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

	matrix result(_size, 0);

	for (auto i = 0; i < _size; i++)
	{
		for (auto j = 0; j < _size; j++)
		{
			result[i]._elements[j] = _elements[i][j] - other[i][j];
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

	matrix result(_size, 0);

	for (auto i = 0; i < _size; i++)
	{
		for (auto j = 0; j < _size; j++)
		{
			for (auto k = 0; k < _size; k++)
			{
				result[i]._elements[j] += _elements[i][k] * other[k][j];
			}
		}
	}

	return result;
}

matrix matrix::operator * (double value) const
{
	matrix result(_size, 0);

	for (auto i = 0; i < _size; i++)
	{
		for (auto j = 0; j < _size; j++)
		{
			result[i]._elements[j] = _elements[i][j] * value;
		}
	}

	return result;
}

column matrix::operator [] (size_t index) const
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

		// »щем точку не равную нулю
		while (pivot_j < _size && temp[pivot_j][i] == 0)
		{
			pivot_j++;
		}

		// Ќе найдено строки дл€ переставлени€ на главную диагональ, где элемент по столбцу не будет равен 0
		if (pivot_j == _size)
		{
			return 0.0;
		}

		// ѕомен€ть местами строку со строкой главной диагонали, где мы нашли нужный нам элемент не равный 0
		if (pivot_j != i)
		{
			std::swap(temp._elements[i], temp._elements[pivot_j]);
			det *= -1;
		}

		double pivot = temp[i][pivot_j];
		det *= pivot;

		// Ќормализируем, преобразуем элемент по главной диагонали в единицу
		for (auto j = i; j < _size; j++)
		{
			temp[i]._elements[j] /= pivot;
		}

		// ¬ычитаем из каждой строки ниже элемента по главной диагонали значени€, эту строку,
		// помноженную на некоторый множитель, чем €вл€етс€ значение под элементом необходимым нам
		for (auto k = i + 1; k < _size; k++)
		{
			double factor = temp[k][i];
			for (auto j = i; j < _size; j++)
			{
				temp[k]._elements[j] -= factor * temp[i][j];
			}
		}
	}

	return det;
}

matrix matrix::transpose() const
{
	matrix result(_size, 0);

	for (auto i = 0; i < _size; i++)
	{
		for (auto j = 0; j < _size; j++)
		{
			result[i]._elements[j] = _elements[j][i];
		}
	}

	return result;
}

matrix matrix::inverse() const
{
	matrix temp(*this);
	matrix single(_size, 0);

	for (auto i = 0; i < _size; i++)
	{
		single[i]._elements[i] = 1.0;
	}	

	for (auto i = 0; i < _size; i++)
	{
		int max_row = i;

		// ƒелаем так, чтобы на горизонтали вместо нул€ было число
		for (auto j = i + 1; j < _size; j++)
		{
			if (fabs(temp[j][i]) > fabs(temp[max_row][i]))
			{
				max_row = j;
			}
		}

		if (max_row != i)
		{
			std::swap(temp._elements[i], temp._elements[max_row]);
			std::swap(single._elements[i], single._elements[max_row]);
		}

		double pivot = temp[i][i];

		if (pivot == 0)
		{
			std::cout << "Matrix is singular" << std::endl;

			matrix empty(_size, 0);

			return empty;
		}

		// ѕриводим строку к виду с единицей в pivot
		for (auto j = 0; j < _size; j++)
		{
			temp[i]._elements[j] /= pivot;
			single[i]._elements[j] /= pivot;
		}

		// ¬ычитаем из каждой строки не равной текущей еЄ же, помноженнную на некоторый множитель, чтобы привести к нулю
		for (auto k = 0; k < _size; k++)
		{
			if (k != i)
			{
				auto factor = temp[k][i];
				for (auto j = 0; j < _size; j++)
				{
					temp[k]._elements[j] -= factor * temp[i][j];
					single[k]._elements[j] -= factor * single[i][j];
				}
			}
		}
	}

	return single;
}

std::ostream& operator << (std::ostream& stream, const matrix& other)
{
	stream << other.to_string();
	return stream;
}

std::string matrix::to_string() const
{
	std::string string_matrix;

	for (auto i = 0; i < _size; i++)
	{
		for (auto j = 0; j < _size; j++)
		{
			string_matrix += std::to_string(_elements[i][j]) + '\t';
		}
		string_matrix += '\n';
	}

	return string_matrix;
}

