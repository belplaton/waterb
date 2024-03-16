#include "logval.h"

class logical_values_array
{

private:

	unsigned int _value;

public:

	logical_values_array(unsigned int value = 0)
	{
		_value = value;
	}

	inline unsigned int get_value() const
	{
		return _value;
	}

	inline logical_values_array inversion() const
	{
		return logical_values_array(~_value);
	}

	inline logical_values_array conjunction(const logical_values_array& other) const
	{
		return logical_values_array(_value & other.get_value());
	}

	inline logical_values_array disjunction(const logical_values_array& other) const
	{
		return logical_values_array(_value | other.get_value());
	}

	inline logical_values_array implication(const logical_values_array& other) const
	{
		return logical_values_array(inversion().get_value() | other.get_value());
	}

	inline logical_values_array coimplication(const logical_values_array& other) const
	{
		return logical_values_array(inversion().get_value() & other.get_value());
	}

	inline logical_values_array modulo_sum(const logical_values_array& other) const
	{
		return logical_values_array(_value ^ other._value);
	}

	inline logical_values_array equivalence(const logical_values_array& other) const
	{
		return modulo_sum(other).inversion();
	}

	inline logical_values_array pierce_arrow(const logical_values_array& other) const
	{
		return disjunction(other).inversion();
	}

	inline logical_values_array sheffer_stroke(const logical_values_array& other) const
	{
		return conjunction(other).inversion();
	}

	inline bool get_bit(int posisiton) const
	{
		// Сдвигаем нужный бит в самое право и выделяем его через побитовое умножение на 1 бит
		return (_value >> posisiton) & 1;
	}

	inline static bool equals(const logical_values_array& a, const logical_values_array& b)
	{
		// 0u - без знака при инверсии. ~0u - все битовые знаки - единицы
		return a.equivalence(b).get_value() == ~0u;
	}

	void to_string(char* binary_string, int string_size) const
	{
		int mask = 1 << (sizeof(unsigned char) * 8 - 1);

		for (int i = 0; i < string_size; i++)
		{
			binary_string[i] = (_value & mask) ? '1' : '0';
			mask >>= 1;
		}

		binary_string[string_size] = '\0';
	}

};