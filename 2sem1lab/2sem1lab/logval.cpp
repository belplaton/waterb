#include "logval.h"

logical_values_array::logical_values_array(unsigned int value)
{
	_value = value;
}

unsigned int logical_values_array::get_value() const
{
	return _value;
}

logical_values_array logical_values_array::inversion() const
{
	return logical_values_array(~_value);
}

logical_values_array logical_values_array::conjunction(const logical_values_array& other) const
{
	return logical_values_array(_value & other.get_value());
}

logical_values_array logical_values_array::disjunction(const logical_values_array& other) const
{
	return logical_values_array(_value | other.get_value());
}

logical_values_array logical_values_array::implication(const logical_values_array& other) const
{
	return logical_values_array(inversion().get_value() | other.get_value());
}

logical_values_array logical_values_array::coimplication(const logical_values_array& other) const
{
	return logical_values_array(inversion().get_value() & other.get_value());
}

logical_values_array logical_values_array::modulo_sum(const logical_values_array& other) const
{
	return logical_values_array(_value ^ other._value);
}

logical_values_array logical_values_array::equivalence(const logical_values_array& other) const
{
	return modulo_sum(other).inversion();
}

logical_values_array logical_values_array::pierce_arrow(const logical_values_array& other) const
{
	return disjunction(other).inversion();
}

logical_values_array logical_values_array::sheffer_stroke(const logical_values_array& other) const
{
	return conjunction(other).inversion();
}

bool logical_values_array::get_bit(int posisiton) const
{
	// Сдвигаем нужный бит в самое право и выделяем его через побитовое умножение на 1 бит
	return (_value >> posisiton) & 1;
}

bool logical_values_array::equals(const logical_values_array& a, const logical_values_array& b)
{
	// 0u - без знака при инверсии. ~0u - все битовые знаки - единицы
	return a.equivalence(b).get_value() == ~0u;
}

void logical_values_array::to_string(char* binary_string, int string_size) const
{
	int mask = 1 << (sizeof(unsigned char) * 8 - 1);

	for (int i = 0; i < string_size; i++)
	{
		binary_string[i] = (_value & mask) ? '1' : '0';
		mask >>= 1;
	}

	binary_string[string_size] = '\0';
}
